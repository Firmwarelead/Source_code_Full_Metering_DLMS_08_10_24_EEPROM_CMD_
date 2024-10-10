/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : storage.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Storage Source File
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"       /* CG Macro Driver */
#include "r_cg_wdt.h"               /* CG WDT Driver */

/* Library */
#include <string.h>                 /* Compiler standard library */

/* MW */
#include "eeprom.h"                 /* EEPROM MW (Init/Read/Write) */
#include "config_storage.h"

/* EMSDK */
#include "storage.h"                /* Storage Header File */
#include "storage_em.h"

/* Application */
#include "event.h"
#include "r_meter_format.h"                 /* EEPROM Format Header */
#include "r_scheduler.h"
#include "r_nameplate.h"
#include "r_loadsurvey.h"
#include "r_load_ctrl.h"

#ifdef _DLMS
#include "r_dlms_format.h"
#include "r_dlms_storage.h"
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Storage Module State */
typedef enum tagStorageState
{
    STORAGE_STATE_UNINITIALIZED = 0,        /* Uninitialized */
    STORAGE_STATE_INITIALIZED               /* Initialized */
} STORAGE_STATE;

/* External module table */
typedef uint8_t(*STORAGE_FUNC_INIT)(void);
typedef uint8_t(*STORAGE_FUNC_FORMAT)(void);
typedef uint8_t(*STORAGE_FUNC_BACKUP)(void);
typedef uint8_t(*STORAGE_FUNC_RESTORE)(void);

typedef struct tagModuleInfo
{
    uint8_t * module_name;
    uint8_t item_group;
    STORAGE_FUNC_FORMAT func_format;
    STORAGE_FUNC_BACKUP func_backup;
    STORAGE_FUNC_RESTORE func_restore;
} STORAGE_MODULE_INFO;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Storage Header Code Mask */
/* "SPEM" ASCII code ("53,50,45,4D" Hex) */
#define STORAGE_EEPROM_HEADER_CODE_MASK                 0x5350454D  

/* Storage Header Code Test */
/* "HEHE" ASCII code ("48,45,48,45" Hex) */
#define STORAGE_EEPROM_HEADER_CODE_TEST                 0x48454845  

#define STORAGE_EEPROM_CHECK_SELECTION_RET_ERROR(sel)   {   \
    if (sel == STORAGE_ITEM_NONE) {                         \
        return STORAGE_ERROR;                               \
    }                                                       \
}

#define STORAGE_EEPROM_CHECK_STATE_RET_ERROR()          {   \
    /* Check Storage State */                               \
    if (g_storage_state != STORAGE_STATE_INITIALIZED) {     \
        /* Device is not initialized */                     \
        return STORAGE_ERROR;                               \
    }                                                       \
}

#define STORAGE_CHECK_STATUS_AND_RET_ERROR(status) {\
    if (status == STORAGE_ERROR) {                                   \
        return STORAGE_ERROR;                                     \
    }                                                             \
}

#define STORAGE_INVOKE_AND_CHECK_ERROR_MODULE_FORMAT(index) {\
    if (g_storage_module_info[index].func_format != NULL) {           \
        status = g_storage_module_info[index].func_format();          \
        STORAGE_CHECK_STATUS_AND_RET_ERROR(status);\
    }                                                                 \
}
#define STORAGE_INVOKE_AND_CHECK_ERROR_MODULE_BACKUP(index) {\
    if (g_storage_module_info[index].func_backup != NULL) {           \
        status = g_storage_module_info[index].func_backup();          \
        STORAGE_CHECK_STATUS_AND_RET_ERROR(status);\
    }                                                                 \
}
#define STORAGE_INVOKE_AND_CHECK_ERROR_MODULE_RESTORE(index) {\
    if (g_storage_module_info[index].func_restore != NULL) {           \
        status = g_storage_module_info[index].func_restore();          \
        STORAGE_CHECK_STATUS_AND_RET_ERROR(status);\
    }                                                                 \
}

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* Variables */
static STORAGE_STATE    g_storage_state = STORAGE_STATE_UNINITIALIZED;  /* Storage State */

static const STORAGE_MODULE_INFO g_storage_module_info[] = {
    { "Event"       , STORAGE_ITEM_SYS_STATE    , EVENT_StorageFormat   , EVENT_StorageBackup   , EVENT_StorageRestore  },
    { "Scheduler"   , STORAGE_ITEM_SYS_STATE    , R_SCHEDULER_Format    , NULL                  , R_SCHEDULER_Restore   },
	{ "Tariff"      , STORAGE_ITEM_SYS_STATE    , R_TARIFF_Format       , R_TARIFF_Backup       , R_TARIFF_Restore      },
	{ "ActCal"      , STORAGE_ITEM_SYS_STATE    , R_ACT_CAL_Format      , R_ACT_CAL_Backup      , R_ACT_CAL_Restore     },      // Activity calendar
	{ "MaxDemand"   , STORAGE_ITEM_SYS_STATE    , R_MDM_Format          , R_MDM_Backup          , R_MDM_Restore         },
    { "BL"          , STORAGE_ITEM_SYS_STATE    , R_LOADSURVEY_Format   , R_LOADSURVEY_Backup   , R_LOADSURVEY_Restore  },
    { "EmEnergy"    , STORAGE_ITEM_SYS_STATE    , NULL                  , STORAGE_EM_Backup     , NULL                  },
#if(defined( R_LOAD_CONTROL_ENABLE ) && R_LOAD_CONTROL_ENABLE == TRUE)
    { "LoadCtrl"    , STORAGE_ITEM_SYS_STATE    , R_LOAD_CTRL_Format    , R_LOAD_CTRL_Backup    , R_LOAD_CTRL_Restore   },      // Load control
#endif /* R_LOAD_CONTROL_ENABLE */    
#ifdef _DLMS    
    { "DLMS"    , STORAGE_ITEM_DLMS         , R_DLMS_Storage_Format , R_DLMS_StorageBackup  , R_DLMS_StorageRestore   },
#endif
};
static const uint16_t g_storage_module_info_size = sizeof(g_storage_module_info) / sizeof(STORAGE_MODULE_INFO);

STR_FUNC static uint8_t storage_check_read_write(void)
{
    uint32_t    header_code_test;
    uint32_t    backup_header_code;

    /* Backup the current header code */
    if (EPR_Read(STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR,
        (uint8_t *)&backup_header_code,
        STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE) != EPR_OK)
    {
        return STORAGE_ERROR;   /* Write error */
    }

    /* write the header code test to check write */
    header_code_test = STORAGE_EEPROM_HEADER_CODE_TEST;
    if (EPR_Write(STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR,
        (uint8_t *)&header_code_test,
        STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE) != EPR_OK)
    {
        return STORAGE_ERROR;   /* Write error */
    }

    /* If write success,
    * Re-read the header code on EEPROM and compare with STORAGE_EEPROM_HEADER_CODE_TEST
    * to check data validity */
    if (EPR_Read(STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR,
        (uint8_t *)&header_code_test,
        STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE) != EPR_OK)
    {
        return STORAGE_ERROR;   /* Read error */
    }

    /* Next check validity */
    if (header_code_test != STORAGE_EEPROM_HEADER_CODE_TEST) {
        return STORAGE_ERROR;   /* Data validity error */
    }

    /* Restore the header code */
    if (EPR_Write(STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR,
        (uint8_t *)&backup_header_code,
        STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE) != EPR_OK)
    {
        return STORAGE_ERROR;   /* Write error */
    }

    return STORAGE_OK;
}

STR_FUNC static uint8_t storage_check_global_format(void)
{
    uint32_t header_code;

    /* Check header code */
    if (EPR_Read(STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR,
        (uint8_t *)&header_code,
        STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE) != EPR_OK)
    {
        return STORAGE_ERROR;   /* Read error */
    }

    if (header_code != STORAGE_EEPROM_HEADER_CODE_MASK) {
        /* Check validity */
        return STORAGE_NOT_FORMATTED;
    }

    return STORAGE_OK;
}

STR_FUNC static uint8_t storage_global_write_format_code(void)
{
    uint32_t    formatted_header_code;

    /* Format the header */
    /* Write initial EEPROM Header */
    formatted_header_code = STORAGE_EEPROM_HEADER_CODE_MASK;
    if (EPR_Write(STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR,
        (uint8_t *)&formatted_header_code,
        STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE) != EPR_OK)
    {
        return STORAGE_ERROR;
    }

    /* Formatted */
    return STORAGE_OK;
}

/***********************************************************************************************************************
* Function Name    : uint8_t R_STORAGE_ClearMeterArea()
* Description      : Clear all data of meter storage to zero to prepare for format
* Arguments        : None
* Functions Called : 
* Return Value     : None
***********************************************************************************************************************/
STR_FUNC static uint8_t R_STORAGE_ClearMeterArea(void)
{
    uint32_t    eeprom_addr;
    uint8_t     empty_page[STORAGE_EEPROM_PAGESIZE];
    uint16_t    size;

    /* Create empty_page */
    memset(empty_page, 0, sizeof(empty_page));

    /* Clear Whole DLMS EEPROM */
    eeprom_addr = STORAGE_EEPROM_GLOBAL_LAST_ADDR;
    while (eeprom_addr < STORAGE_EEPROM_METER_FORMAT_LAST_ADDR)
    {
        if ((STORAGE_EEPROM_METER_FORMAT_LAST_ADDR - eeprom_addr) < STORAGE_EEPROM_PAGESIZE) {
            size = STORAGE_EEPROM_METER_FORMAT_LAST_ADDR - eeprom_addr;
        }
        else {
            size = STORAGE_EEPROM_PAGESIZE;
        }

        if (EPR_Write(eeprom_addr, empty_page, size) != EPR_OK)
        {
            return STORAGE_ERROR;
        }

        eeprom_addr += size;

        R_WDT_Restart();
    }

    /* Formatted */
    return STORAGE_OK;
}

/***********************************************************************************************************************
* Function Name    : uint8_t STORAGE_Init(uint8_t is_checking)
* Description      : Storage Initialization
* Arguments        : None
* Functions Called : EPR_Init()
*                  : EPR_Read()
*                  : EPR_Write()
*                  : STORAGE_ReadEEPROMHeader()
* Return Value     : Execution Status
*                  :    STORAGE_OK      Normal end
*                  :    STORAGE_ERROR   Error occurred
*                  :                    Read/Write error or data validity error
***********************************************************************************************************************/
STR_FUNC uint8_t STORAGE_Init(uint8_t is_checking)
{
    uint8_t status;
    uint16_t i;

    g_storage_state = STORAGE_STATE_UNINITIALIZED;  /* Uninitialized */
    
    /* EEPROM Driver Initialization */
    EPR_Init();
    
    /* Do a sample write-read cycle to confirm memory access is ok */
    if (is_checking) {
        status = storage_check_read_write();
        if (status != STORAGE_OK) {
            return STORAGE_ERROR;
        }
    }

    /* STORAGE module successfully initialized */
    g_storage_state = STORAGE_STATE_INITIALIZED;

    /* 
     * Check format signal from middleware that data flash is formatted or not
     * Because name plate storage data in data flash, so need to format if it is triggered
     */
    if(g_DATAFLASH_FormatTrigger != FALSE)//== TRUE, mean format trigger
    {
        if(R_NAMEPLATE_Format() != FALSE)//==TRUE, format successfully
        {
            g_DATAFLASH_FormatTrigger = FALSE;
        }
        else
        {
            return STORAGE_ERROR;
        }
    }
    else
    {
        /* Do nothing */
    }
    
    /* Check for global format header code */
    status = storage_check_global_format();
    if ((status != STORAGE_OK) && (status != STORAGE_NOT_FORMATTED)) {
        return STORAGE_ERROR;
    }
    else if (status == STORAGE_NOT_FORMATTED) {
        /* Call clear all eeprom area for meter application */
        if(R_STORAGE_ClearMeterArea() != STORAGE_OK)
        {
            return STORAGE_ERROR;
        }
        else
        {
            
        }
        
        /* Call format separately */
        status = STORAGE_Format(STORAGE_ITEM_ALL);
        STORAGE_CHECK_STATUS_AND_RET_ERROR(status);

        /* Write back to confirm global format code */
        storage_global_write_format_code();
    }
    else 
    {

    }
    /* Restore for all data of application */
    STORAGE_Restore(STORAGE_ITEM_ALL);
    /* Return storage format checking result */
    return status;  
}

/***********************************************************************************************************************
* Function Name    : uint8_t STORAGE_Format(void)
* Description      : Storage Format EEPROM Device to store data
* Arguments        : None
* Functions Called : EPR_Write()
* Return Value     : Execution Status
*                  :    STORAGE_OK          Formatted successfull, device is ready to store data
*                  :    STORAGE_ERROR       Storage device is not initialized
*                  :                        Or, error occurred when write data to EEPROM
***********************************************************************************************************************/
STR_FUNC uint8_t STORAGE_Format(uint8_t selection)
{
    uint8_t                 status;
    uint8_t j, mask;
    uint16_t i;

    /* Check parameter and state */
    STORAGE_EEPROM_CHECK_SELECTION_RET_ERROR(selection);
    STORAGE_EEPROM_CHECK_STATE_RET_ERROR();

    for (j = 0; j < 8; j++)
    {
        mask = selection & (1 << j);
        if (mask != 0) {
            for (i = 0; i < g_storage_module_info_size; i++)
            {
                if (g_storage_module_info[i].item_group == mask) {
                    STORAGE_INVOKE_AND_CHECK_ERROR_MODULE_FORMAT(i);
                }
            }
        }
    }

    /* Formatted */
    return STORAGE_OK;
}


/***********************************************************************************************************************
* Function Name    : uint8_t STORAGE_Backup(uint8_t selection)
* Description      : Storage Backup (from EM Core to EEPROM)
* Note             : When STORAGE_ERROR is returned, maybe some data on selected item
*                  : (of [selection] parameter) have been stored to EEPROM
* Arguments        : uint8_t selection: Backup item selection
*                  :      STORAGE_ITEM_SYS_STATE    Select EM System State
*                  :      STORAGE_ITEM_RTC_TIME     Select RTC Time
*                  :      STORAGE_ITEM_ALL          Select all above items
* Functions Called : STORAGE_ReadEEPROMHeader()
*                  : EPR_Write()
*                  : EM_GetConfig()
*                  : EM_GetCalibInfo()
*                  : EM_GetState()
*                  : RTC_CounterGet()
*                  : STORAGE_UpdateEEPROMHeader()
* Return Value     : Execution Status
*                  :    STORAGE_OK      Backup successfull
*                  :    STORAGE_ERROR   Storage device is not initialized or not formatted
*                  :                    Or, error occurred when write EEPROM
*                  :                    Or, selection = 0 (STORAGE_ITEM_NONE)
***********************************************************************************************************************/
STR_FUNC uint8_t STORAGE_Backup(uint8_t selection)
{
    uint8_t status;
    uint8_t j, mask;
    uint16_t i;

    /* Check parameter and state */
    STORAGE_EEPROM_CHECK_SELECTION_RET_ERROR(selection);
    STORAGE_EEPROM_CHECK_STATE_RET_ERROR();

    for (j = 0; j < 8; j++)
    {
        mask = selection & (1 << j);
        if (mask != 0) {
            for (i = 0; i < g_storage_module_info_size; i++)
            {
                if (g_storage_module_info[i].item_group == mask) {
                    STORAGE_INVOKE_AND_CHECK_ERROR_MODULE_BACKUP(i);
                }
            }
        }
    }

    /* Success */
    return STORAGE_OK;
}

/***********************************************************************************************************************
* Function Name    : uint8_t STORAGE_Restore(uint8_t selection)
* Description      : Storage Restore (from EEPROM to EM Core)
* Arguments        : uint8_t selection: Restore item selection
*                  :      STORAGE_ITEM_SYS_STATE    Select EM System State
*                  :      STORAGE_ITEM_RTC_TIME     Select RTC Time
*                  :      STORAGE_ITEM_ALL          Select all above items
* Functions Called : STORAGE_ReadEEPROMHeader()
*                  : EPR_Read()
*                  : EM_SetConfig()
*                  : EM_SetCalibInfo()
*                  : EM_SetState()
*                  : RTC_CounterSet()
* Return Value     : Execution Status
*                  :    STORAGE_OK                  Restore successfull
*                  :    STORAGE_ERROR_DATA_CORRUPT  Related data on EEPROM of selected item is corrupt
*                  :    STORAGE_ERROR               Storage device is not initialized or not formatted
*                  :                                Or, error occurred when read EEPROM,
*                  :                                Or, selection = 0 (STORAGE_ITEM_NONE)
***********************************************************************************************************************/
STR_FUNC uint8_t STORAGE_Restore(uint8_t selection)
{
    uint8_t status;
    uint8_t j, mask;
    uint16_t i;

    /* Check parameter and state */
    STORAGE_EEPROM_CHECK_SELECTION_RET_ERROR(selection);
    STORAGE_EEPROM_CHECK_STATE_RET_ERROR();

    for (j = 0; j < 8; j++)
    {
        mask = selection & (1 << j);
        if (mask != 0) {
            for (i = 0; i < g_storage_module_info_size; i++)
            {
                if (g_storage_module_info[i].item_group == mask) {
                    STORAGE_INVOKE_AND_CHECK_ERROR_MODULE_RESTORE(i);
                }
            }
        }
    }

    /* Success */
    return STORAGE_OK;
}
