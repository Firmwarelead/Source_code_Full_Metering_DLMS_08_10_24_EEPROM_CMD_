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
* Version      : Version
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : 
************************************************************************************************************************
* History      : DD.MM.YYYY     Version     Description
*                29.03.2018     v.1.0.0     New Creation
***********************************************************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Drivers */
#include "r_cg_macrodriver.h"
#include "typedef.h"

#include "r_dlms_app.h"
#include "r_dlms_event.h"
#include "r_dlms_push.h"
#include "r_dlms_factory_config.h"

#include "r_nameplate.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define R_APP_PC_ENABLE             (1)
/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
extern uint8_t g_server_system_title[]; 			// = "REI00045";

/******************************************************************************
Private global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_Backup_SMO1
* Interface     : uint8_t R_DLMS_Backup_SMO1(
*               :     uint8_t *p_buffer, uint16_t length
*               : );
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_Backup_SMO(st_app_smo_t *p_message, uint32_t eeprom_address)
{
	DLMS_STORAGE portion;

	portion.address = eeprom_address;
	portion.length = sizeof(st_app_smo_t);

	return R_DLMS_EEPROM_Write(portion, (void *)p_message);
}

/******************************************************************************
* Function Name : R_DLMS_Restore_SMS
* Interface     : st_app_smo_t R_DLMS_Restore_SMS(
*               :     void
*               : );
* Description   :
* Arguments     :
* Return Value  : st_app_smo_t
******************************************************************************/
st_app_smo_t R_DLMS_Restore_SMO (
	uint32_t eeprom_address
)
{
	DLMS_STORAGE portion;
	st_app_smo_t message;

	portion.address = eeprom_address;
	portion.length = sizeof(st_app_smo_t);

	R_DLMS_EEPROM_Read(portion, (void *)&message);

	return message;
}

/******************************************************************************
* Function Name : R_DLMS_Backup_SMO1
* Interface     : uint8_t R_DLMS_Backup_SMO1(
*               :     st_app_smo_t *p_message
*               : );
* Description   :
* Arguments     : st_app_smo_t *p_message
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_Backup_SMO1(st_app_smo_t *p_message)
{
	return R_DLMS_Backup_SMO(p_message, STORAGE_EEPROM_DLMS_SMO_1_LEN_ADDR); 
}

/******************************************************************************
* Function Name : R_DLMS_Backup_SMO2
* Interface     : uint8_t R_DLMS_Backup_SMO1(
*               :     st_app_smo_t *p_message
*               : );
* Description   :
* Arguments     : st_app_smo_t *p_message
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_Backup_SMO2(st_app_smo_t *p_message)
{
	return R_DLMS_Backup_SMO(p_message, STORAGE_EEPROM_DLMS_SMO_2_LEN_ADDR); 
}

/******************************************************************************
* Function Name : R_DLMS_Restore_SMO1
* Interface     : uint8_t R_DLMS_Restore_SMO1(
*               :     
*               : );
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
st_app_smo_t R_DLMS_Restore_SMO1(void)
{
	return R_DLMS_Restore_SMO(STORAGE_EEPROM_DLMS_SMO_1_LEN_ADDR);
}
/******************************************************************************
* Function Name : R_DLMS_Restore_SMO2
* Interface     : uint8_t R_DLMS_Restore_SMO2(
*               :     
*               : );
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
st_app_smo_t R_DLMS_Restore_SMO2(void)
{
	return R_DLMS_Restore_SMO(STORAGE_EEPROM_DLMS_SMO_2_LEN_ADDR);
}

/******************************************************************************
* Function Name : R_DLMS_App_Format
* Interface     : void R_DLMS_App_Format(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_App_Format(void)
{
}

/******************************************************************************
* Function Name : R_DLMS_App_Init
* Interface     : void R_DLMS_App_Init(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_App_Init ( void )
{	
    uint8_t buffer[100];
    uint16_t len;

	/* Restore max demand integration period */
	R_DLMS_RTC_Init();

	/* Update system title */
	{
        R_NAMEPLATE_GetByID(NAMEPLATE_ID_FLAGID, buffer, &len);  /* Get nameplate Flag ID */
		memcpy(g_server_system_title, buffer, 3);
	
		R_NAMEPLATE_GetByID(NAMEPLATE_ID_SN, buffer, &len);      /* Get nameplate serial number */
		memcpy( g_server_system_title + 3, buffer+11 , 5);
	}

    /* LOAD DLMS Event module */
    R_DLMS_EVENT_Init();
}

/******************************************************************************
* Function Name : R_DLMS_App_PollingProcessing
* Interface     : void R_DLMS_App_PollingProcessing(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_App_PollingProcessing ( void )
{
	/* NOTE:  R_DLMS_WRP_TakeEnergySnapshot should be called 1 time before R_DLMS_Datalog_PollingProcessing */
	/* Initial value of g_haft_sec_tick == 2, R_DLMS_WRP_TakeEnergySnapshot will run for the 1st call */
}



/* END: DLMS APPLICATION PROCESS */
