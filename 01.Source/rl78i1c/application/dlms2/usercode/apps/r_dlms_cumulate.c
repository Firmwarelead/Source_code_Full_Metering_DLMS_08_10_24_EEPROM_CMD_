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
* File Name    : r_dlms_cumulate.c
* Version      : <Version>
* Device(s)    : <'RL78/I1C'>
* Tool-Chain   : <'CCRL'>
* H/W Platform : <'RL78/I1C Energy Meter Platform'>
* Description  : <Description of file>
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Drivers */
#include "typedef.h"

/* Standard Lib */
#include <string.h>         /* String Standard Lib */

#include "r_dlms_app.h"
#include "r_dlms_storage.h"
#include "r_dlms_format.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define DO_SAFE_BACKUP_FOR_POWER_ON_DURATION		(TRUE)
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

uint32_t g_dlms_program_cnt;                          /* (2 bytes) Programming counter                       */

/* Storage infor */
const DLMS_STORAGE storage_info_program_cnt = {STORAGE_EEPROM_DLMS_PC_ADDR, STORAGE_EEPROM_DLMS_PC_SIZE};
const DLMS_STORAGE storage_info_billing_cnt = {STORAGE_EEPROM_DLMS_BILLING_COUNTER_ADDR, STORAGE_EEPROM_DLMS_BILLING_COUNTER_SIZE};

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/


/******************************************************************************
* Function Name : R_DLMS_Cumulative_PC
* Interface     : void R_DLMS_Cumulative_PC(
*               :     void
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_Cumulative_PC(void)
{
    g_dlms_program_cnt++;
	return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_CumulateRestore
* Interface     : void R_DLMS_CumulateRestore(
*               :     void
*               : );
* Description   : This function load data from storage to RAM, need to register in restore of DLMS storage
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_CumulateRestore(void)
{
	/* Programming counter                       */
	R_DLMS_EEPROM_Read(storage_info_program_cnt, (uint8_t *)&g_dlms_program_cnt);
}
/******************************************************************************
* Function Name : R_DLMS_CumulateBackup
* Interface     : void R_DLMS_CumulateBackup(
*               :     void
*               : );
* Description   : store data from RAM to storage
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_CumulateBackup(void)
{

}

/******************************************************************************
* Function Name : R_DLMS_CumulateFormat
* Interface     : void R_DLMS_CumulateFormat(
*               :     void
*               : );
* Description   : format data, write default data to storage.
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_CumulateFormat(void)
{

}