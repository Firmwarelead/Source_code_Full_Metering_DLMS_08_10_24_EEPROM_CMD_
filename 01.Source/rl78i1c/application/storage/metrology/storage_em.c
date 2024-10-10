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
* File Name    : storage_em.c
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

/* Library */
#include <string.h>                 /* Compiler standard library */

/* MW */
#include "eeprom.h"                 /* EEPROM MW (Init/Read/Write) */

/* Metrology */
#include "em_core.h"

/* WRP */
#include "wrp_em_adc.h"
#include "wrp_em_sw_config.h"

/* Application */
#include "format_em.h"                 /* EEPROM Format Header */
#include "storage_em.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Storage Module State */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name    : uint8_t STORAGE_EM_Format(void)
* Description      : Format: clear all energy counter value in memory
*                  : Use with caution, all energy data may corrupt
*                  : Please note this API only clear in storage memory, not in RAM counter
* Arguments        : None
* Functions Called : None
* Return Value     : uint8_t
***********************************************************************************************************************/
uint8_t STORAGE_EM_Format(void)
{
    EM_OPERATION_DATA energy_data;

    memset(&energy_data, 0, sizeof(EM_OPERATION_DATA));

    STORAGE_EM_SetEnergyData(&energy_data);

    return EM_STORAGE_OK;
}
/***********************************************************************************************************************
* Function Name    : uint8_t STORAGE_EM_Restore(void)
* Description      : Restore metrology counter from eeprom to RAM
* Arguments        : None
* Functions Called : None
* Return Value     : uint8_t
***********************************************************************************************************************/
uint8_t STORAGE_EM_Restore(void)
{
    EM_OPERATION_DATA energy_data;

    /* Get from storage */
    if (STORAGE_EM_GetEnergyData(&energy_data) != EM_STORAGE_OK)
    {
        return EM_STORAGE_ERROR;
    }

    /* Set to metrology */
    EM_SetOperationData(&energy_data);

    return EM_STORAGE_OK;
}

/***********************************************************************************************************************
* Function Name    : uint8_t STORAGE_EM_Backup(void)
* Description      : Backup metrology counter from RAM to EEPROM
* Arguments        : None
* Functions Called : None
* Return Value     : uint8_t
***********************************************************************************************************************/
uint8_t STORAGE_EM_Backup(void)
{
    EM_OPERATION_DATA energy_data;

    /* Get from metrology */
    EM_GetOperationData(&energy_data);

    /* Set to storage */
    if (STORAGE_EM_SetEnergyData(&energy_data) != EM_STORAGE_OK)
    {
        return EM_STORAGE_ERROR;
    }

    return EM_STORAGE_OK;
}

/***********************************************************************************************************************
* Function Name    : uint8_t STORAGE_EM_GetEnergyData(EM_ENERGY_DATA * p_counter)
* Description      : Read from storage eeprom to counter
* Arguments        : EM_ENERGY_DATA * p_counter
* Functions Called : 
* Return Value     : Execution Status
*                  :    STORAGE_OK      Backup successfull
*                  :    STORAGE_ERROR   EPR operation failed
***********************************************************************************************************************/
uint8_t STORAGE_EM_GetEnergyData(EM_OPERATION_DATA * p_counter)
{
    EM_OPERATION_DATA energy_data;
    uint8_t status;

    /* Load from eeprom */
    status = EPR_Read(
        STORAGE_EEPROM_EM_ENERGY_DATA_ADDR,
        (uint8_t *)p_counter,
        STORAGE_EEPROM_EM_ENERGY_DATA_SIZE
    );

    if (status != EPR_OK)
    {
        return EM_STORAGE_ERROR;
    }

    /* Success */
    return EM_STORAGE_OK;
}

/***********************************************************************************************************************
* Function Name    : uint8_t STORAGE_EM_SetEnergyData(EM_OPERATION_DATA * p_counter)
* Description      : Set to metrology counter in storage eeprom
* Arguments        : None
* Functions Called : 
* Return Value     : Execution Status       
***********************************************************************************************************************/
uint8_t STORAGE_EM_SetEnergyData(EM_OPERATION_DATA * p_counter)
{
    EM_OPERATION_DATA energy_data;
    uint8_t status;

    /* Load from eeprom */
    status = EPR_Write(
        STORAGE_EEPROM_EM_ENERGY_DATA_ADDR,
        (uint8_t *)p_counter,
        STORAGE_EEPROM_EM_ENERGY_DATA_SIZE
    );

    if (status != EPR_OK)
    {
        return EM_STORAGE_ERROR;
    }

    /* Success */
    return EM_STORAGE_OK;
}
