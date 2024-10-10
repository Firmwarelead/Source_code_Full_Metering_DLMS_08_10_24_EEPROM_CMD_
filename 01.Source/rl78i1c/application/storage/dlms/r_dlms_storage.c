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
* Copyright (C) 2013, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_dlms_storage.c
* Version      : v1.0.0
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : <RL78/I1C Energy Meter Platform
* Description  : 
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 29.03.2018 New creation
// 09.01.2019 Revise backup/restore list API
//            Ultilize meter storage function, use storage sub module

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"   /* CG Macro Driver */
#include "r_cg_rtc.h"           /* CG RTC Driver */
#include "r_cg_wdt.h"           /* CG WDT Driver */
#include "eeprom.h"             /* EEPROM MW Layer */
#include "dataflash.h"

/* Common */
#include "typedef.h"

/* Meter application */
#include "storage.h"

/* DLMS Application */
#include "r_dlms_classes.h"
#include "r_dlms_objects.h"
#include "r_dlms_event.h"
#include "r_dlms_cumulate.h"

#include "r_dlms_storage.h"
#include "r_dlms_app.h"
#include "r_dlms_security.h"	/* Secret keys storage */
#include "r_dlms_com_wrapper_config.h"
#include <string.h>

#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
#include "r_dlms_tcp_wrapper_neoway_wm620.h"
#endif

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#define R_DLMS_STORAGE_OK                  0       /* OK */
#define R_DLMS_STORAGE_ERROR               1       /* Error */
#define R_DLMS_STORAGE_ERROR_DATA_CORRUPT  2       /* Data Storage in EEPROM is corrupted */


/* EEPROM Information */
#define METER_E2PROM_SIZE                   (2048)

#define DLMS_E2PROM_SIZE                    EPR_DEVICE_SIZE - METER_E2PROM_SIZE         /* DLMS EEPROM Size */
#define DLMS_E2PROM_PAGESIZE                EPR_DEVICE_PAGESIZE                         /* DLMS EEPROM Page Size */

#define DLMS_E2PROM_HEADER_CODE_MASK        (STORAGE_EEPROM_CURRENT_VERISON)            /* Storage Header Code Mask */
#define DLMS_E2PROM_HEADER_CODE_TEST        0x48454845                                  /* Storage Header Code Test */


/* Dataflash Infomation */
#define METER_DATAFLASH_SIZE                (2048)

#define DLMS_DATAFLASH_SIZE                 EPR_DEVICE_SIZE - METER_E2PROM_SIZE         /* DLMS EEPROM Size */
#define DLMS_DATAFLASH_PAGESIZE             EPR_DEVICE_PAGESIZE                         /* DLMS EEPROM Page Size */

#define DLMS_DATAFLASH_HEADER_CODE_MASK     (STORAGE_DATAFLASH_CURRENT_VERISON)         /* Storage Header Code Mask */
#define DLMS_DATAFLASH_HEADER_CODE_TEST     0x48454845                                  /* Storage Header Code Test */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Storage Module State */
typedef enum tagStorageState
{
    STORAGE_STATE_UNINITIALIZED = 0,        /* Uninitialized */
    STORAGE_STATE_INITIALIZED               /* Initialized */
} STORAGE_STATE;
/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/
STORAGE_STATE           g_dlms_storage_state;

dlms_storage_header_t   g_dlms_storage_header;

/* Import from cstart.asm */
extern const uint16_t ram_start_addr;
extern const uint16_t ram_end_addr;

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private variables and functions
***********************************************************************************************************************/

/******************************************************************************
* Function Name : R_USER_Storage_Write
* Interface     : void R_USER_Storage_Write(
*               :     DLMS_STORAGE_MAP storage_map
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_EEPROM_Write (DLMS_STORAGE storage_map, uint8_t * p_buf)
{
    if (p_buf == NULL)
    {
        return 1; // NG
    }

    if (E2PR_WRITE(
        storage_map.address,
        (uint8_t *) p_buf,
        storage_map.length
        ) != E2PR_OK)
    {
        return RLT_ERR;   // NG
    }

    return RLT_SUCCESS; /* OK */
}

/******************************************************************************
* Function Name : R_USER_Storage_Read
* Interface     : void R_USER_Storage_Read(
*               :     
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_EEPROM_Read (DLMS_STORAGE storage_map, uint8_t * p_buf)
{
    if (p_buf == NULL)
    {
        return 1; // NG
    }

    if (E2PR_READ(
        storage_map.address,
        (uint8_t *) p_buf,
        storage_map.length
        ) != E2PR_OK)
    {
        return RLT_ERR;   // NG
    }

    return RLT_SUCCESS;       /* OK */
}

/******************************************************************************
* Function Name : R_USER_Storage_Write
* Interface     : void R_USER_Storage_Write(
*               :     DLMS_STORAGE_MAP storage_map
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_DataFlash_Write (DLMS_STORAGE *p_storage_map, uint8_t * p_buf)
{
    if (p_buf == NULL)
    {
        return 1; // NG
    }

    if (DFL_WRITE(
        p_storage_map->address,
        (uint8_t *) p_buf,
        p_storage_map->length
        ) != DATAFLASH_OK)
    {
        return RLT_ERR;   // NG
    }

    return RLT_SUCCESS; /* OK */
}

/******************************************************************************
* Function Name : R_USER_Storage_Read
* Interface     : void R_USER_Storage_Read(
*               :     
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_DataFlash_Read (DLMS_STORAGE *p_storage_map, uint8_t * p_buf)
{
    if (p_buf == NULL)
    {
        return 1; // NG
    }

    if (DFL_READ(
        p_storage_map->address,
        (uint8_t *) p_buf,
        p_storage_map->length
        ) != DATAFLASH_OK)
    {
        return RLT_ERR;   // NG
    }

    return RLT_SUCCESS;       /* OK */
}
/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/******************************************************************************
* Function Name : R_Storage_IsBufferWritable
* Interface     : uint8_t R_Storage_IsBufferWritable(uint8_t *p_buffer)
* Description   :
* Arguments     : uint8_t * p_buffer:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_Storage_IsBufferWritable(uint8_t *p_buffer)
{
	if ((uint16_t)p_buffer >= ram_start_addr && (uint16_t)p_buffer <= ram_end_addr) {
		return TRUE;
	}

	return FALSE;
}




/******************************************************************************
* Function Name : R_DLMS_Storage_IsNull
* Interface     : uint8_t R_DLMS_Storage_IsNull(
*               :     uint8_t *p_content, uint16_t length
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Storage_IsNull ( uint8_t *p_content, uint16_t length )
{
    uint32_t sum;
    uint16_t i;
    if (p_content == NULL)
    {
        return TRUE;
    }

    for (i = 0; i < length; i++)
    {
        if (p_content[i] != 0)
        {
            break;
        }
    }
    if (i >= length)
    {
        return TRUE;
    }

    for (i = 0; i < length; i++)
    {
        if (p_content[i] != 0xFF)
        {
            break;
        }
    }
    if (i >= length)
    {
        return TRUE;
    }

    return FALSE;
}


/******************************************************************************
* Function Name: uint8_t ENERGY_StorageBackup(void)
* Description  : Backup energy storage sub module
* Arguments    : None
* Return Value : uint8_t status (according to storage.h)
******************************************************************************/
uint8_t R_DLMS_StorageBackup(void)
{
    /* Cumulative params */
    R_DLMS_CumulateBackup();
    /* Event */
    R_DLMS_EventBackup();
    /* Security */
    R_DLMS_Security_Backup();
    return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_DLMS_StorageRestore
* Interface     : uint8_t R_DLMS_StorageRestore(
*               :     void
*               : );
* Description   :
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_StorageRestore(void)
{
    /* Restore storage for all dlms application */
    /* RTC date time */
    R_DLMS_RTC_Restore();
    /* For cumulative params */
    R_DLMS_CumulateRestore();
    /* Event */
    R_DLMS_EventRestore();
    /* For association and security */
    R_DLMS_Security_Restore();
    /* Push */
    /* TODO - FWU */


    
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)

    EPR_Read(STORAGE_EEPROM_DLMS_MODEM_SETTING_APN_NAME_ADDR, (uint8_t *)&g_tcp_gsm_modem.setting.apn_name, sizeof(g_tcp_gsm_modem.setting.apn_name));

#endif /* TCP_MODE_SELECTION of GSM modem */

    return STORAGE_OK;
}

/******************************************************************************
* Function Name: uint8_t ENERGY_StorageInit(void)
* Description  : Initialize energy storage sub module
* Arguments    : None
* Return Value : uint8_t status (according to storage.h)
******************************************************************************/
uint8_t R_DLMS_Storage_Init(void)
{
    return STORAGE_OK;
}

/******************************************************************************
* Function Name: uint8_t R_DLMS_Storage_Format(void)
* Description  : Format DLMS storage sub module
* Arguments    : None
* Return Value : uint8_t status (according to storage.h)
******************************************************************************/
uint8_t R_DLMS_Storage_Format(void)
{
    uint32_t    eeprom_addr;
    uint8_t     empty_page[STORAGE_EEPROM_PAGESIZE];
    uint16_t    size;
    uint16_t    item_index;

    /* Create empty_page */
    memset(empty_page, 0, sizeof(empty_page));

    /* Clear Whole DLMS EEPROM */
    eeprom_addr = STORAGE_EEPROM_DLMS_CODE_ADDR;
    while (eeprom_addr < STORAGE_EEPROM_DLMS_LAST_ADDR)
    {
        if ((STORAGE_EEPROM_DLMS_LAST_ADDR - eeprom_addr) < STORAGE_EEPROM_PAGESIZE) {
            size = STORAGE_EEPROM_DLMS_LAST_ADDR - eeprom_addr;
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

    /* Write default value */
    /* RTC date time */
    R_DLMS_RTC_Format();
    /* Event */
    R_DLMS_EventFormat();
    /* Push format */
    R_DLMS_Push_Format();
    /* Security */
    R_DLMS_Security_Format();

    R_DLMS_App_Format();
    

	/* Force re-initiate all data when format success */
	R_DLMS_OBJECTS_Init();

    /* Formatted */
    return STORAGE_OK;
}