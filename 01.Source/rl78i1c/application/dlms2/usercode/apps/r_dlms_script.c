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
* File Name    : r_dlms_script.c
* Version      : <Version>
* Device(s)    : <'RL78/I1C'>
* Tool-Chain   : <'CCRL'>
* H/W Platform : <'RL78/I1C Energy Meter Platform'>
* Description  : <Description of file>
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 2018-03-29 New creation
/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"

#include "r_dlms_app.h"
#include "r_dlms_script.h"
#include "r_dlms_push.h"
#include "r_dlms_fw_upgrade.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tag_dlms_script_appsID_t
{
	uint16_t * 	p_table;
	uint8_t 	size;
} dlms_script_appsID_t;

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

const uint16_t table_script_id_billing[] =
{
	R_DLMS_SCRIPT_ID_BILLING
};

const uint16_t table_script_id_tariff[] =
{
	R_DLMS_SCRIPT_ID_TARRIFICATION
};

const uint16_t table_script_id_image_activate[] =
{
	R_DLMS_SCRIPT_ID_ACTIVATE_IMAGE
};

const uint16_t table_script_id_push[] =
{
	R_DLMS_SCRIPT_ID_PUSH_DATA_TO_HES,
	R_DLMS_SCRIPT_ID_PUSH_DATA_TO_IHD,
	R_DLMS_SCRIPT_ID_PUSH_MESSAGE_TO_IHD,
	R_DLMS_SCRIPT_ID_PUSH_MESSAGE_TO_HES,
	R_DLMS_SCRIPT_ID_PUSH_EVENT_TO_HES,
};


const dlms_script_appsID_t table_script_objects_data[] = 
{
	{ (uint16_t *)table_script_id_billing, 			sizeof(table_script_id_billing) 		/ sizeof(uint16_t)},
	{ (uint16_t *)table_script_id_tariff,			sizeof(table_script_id_tariff)			/ sizeof(uint16_t)},
	{ (uint16_t *)table_script_id_image_activate,	sizeof(table_script_id_image_activate) 	/ sizeof(uint16_t)},
	{ (uint16_t *)table_script_id_push, 			sizeof(table_script_id_push) 			/ sizeof(uint16_t)},
};
const uint16_t table_script_objects_data_size = sizeof(table_script_objects_data) / sizeof(dlms_script_appsID_t);

/******************************************************************************
* Function Name : R_DLMS_Script_GetScript_ID
* Interface     : void R_DLMS_Script_GetScript_ID(
*               :     uint16_t object_id, uint16_t script_id
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint16_t R_DLMS_Script_Get_AppsID(uint8_t object_id, uint16_t script_id)
{
	if (object_id >= table_script_objects_data_size)
	{
		return 0;
	}

	if (table_script_objects_data[(uint8_t)object_id].size > script_id)
	{
		return (table_script_objects_data[(uint8_t)object_id].p_table[script_id]);
	}
	else
	{
		return 0;
	}
}

/******************************************************************************
* Function Name : R_DLMS_Trigger_SetFlag
* Interface     : void R_DLMS_Trigger_SetFlag(
*               :     uint16_t flag_id
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_Script_Execute ( uint16_t script_app_id )
{
	uint8_t rlt = RLT_SUCCESS;

	switch ( script_app_id )
	{
		case R_DLMS_SCRIPT_ID_DUMMY:
			return RLT_SUCCESS;
		case R_DLMS_SCRIPT_ID_BILLING:
            // TODO
			break;
		case R_DLMS_SCRIPT_ID_TARRIFICATION:
			// Metering take care this action
			// This case is keep as dummy script for protocol purpose only
			break;
		case R_DLMS_SCRIPT_ID_ACTIVATE_IMAGE:
			rlt = R_DLMS_FWU_ImageActivate();
			break;
		case R_DLMS_SCRIPT_ID_PUSH_DATA_TO_HES:
			R_DLMS_Push_DataToHES();
			break;
		case R_DLMS_SCRIPT_ID_PUSH_DATA_TO_IHD:
			R_DLMS_Push_DataToIHD();
			break;
		case R_DLMS_SCRIPT_ID_PUSH_MESSAGE_TO_IHD:
			R_DLMS_Push_MessageToIHD();
			break;
		case R_DLMS_SCRIPT_ID_PUSH_MESSAGE_TO_HES:
			R_DLMS_Push_MessageToHES();
			break;
		case R_DLMS_SCRIPT_ID_PUSH_EVENT_TO_HES:
			R_DLMS_Push_EventToHES();
			break;
		default:
			break;
	}

	return rlt;
}