/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************	
* File Name    : r_dlms_usercode_class15.c
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

#include <string.h>
#include <stddef.h>
#include "r_dlms_usercode_class15.h"

/* User application */
#include "r_dlms_app.h"
#include "r_dlms_security.h"
#include "r_dlms_cumulate.h"
#include "r_dlms_event.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/* User code variable */


/* User code function */

/******************************************************************************
Private global variables and functions
******************************************************************************/
/**********************************************************************
***********************************************************************
*******************     PRIVATE GLOBAL VARIABLES       ****************
***********************************************************************
***********************************************************************
* Declare detail value to assign to Exported global variables if      *
* that is complex data type (struct or array)                         *
**********************************************************************/
/******************************************************************************
* Function Name : R_DLMS_USER_ic15_Init
* Interface     : void R_DLMS_USER_ic15_Init(
*               :     void
*               : );
* Description   : This function to init default data for secret on emulated eeprom
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_DLMS_USER_ic15_Init(void)
{

}



/******************************************************************************
* Function Name : R_DLMS_USER_ic15_obj01_att07_set
* Description   : Object name       : Association LN_Meter Reader
*                 Object index      : 01
*                 Class             : 15
*                 Attribute order   : 07
*                 Attribute name    : LLSSecret
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 OctetString * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic15_obj01_att07_set(distributor_params_t * p_params, OctetString * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/*********************************************
	FixedString
	{
	    uint8_t   *p_content;
	    uint16_t   length;
	}
	*********************************************/

	/* This function use to change secret of this represented association */
	/* Secret usually stores  in data flash, so you need to change value in there */
	/* This representation association use mechanism: MECHANISM_ID1_LOW_SECURITY */
	/* If mechenism is MECHANISM_ID0_LOWEST_SECURITY, no use key */
	/* If mechenism is MECHANISM_ID1_LOW_SECURITY, length key is 8 */
	/* If mechenism is others, length key is 16 */
	/* API to access to key content(pointer): g_assc1.authentication_value.p_content */

	
	/* Start user code here */
	if (R_DLMS_Backup_LLSSecret_MR(p_attribute_set->p_content, p_attribute_set->length) == RLT_SUCCESS)
	{
		g_event_flag.bits.set_lls = TRUE;
		R_DLMS_Cumulative_PC();
		/* Restore new key */
		R_DLMS_Restore_LLSKeyMR();
	}
	else
	{
		/* Mark that set fail */
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic15_obj02_att07_set
* Description   : Object name       : Association LN_Utility Setting
*                 Object index      : 02
*                 Class             : 15
*                 Attribute order   : 07
*                 Attribute name    : LLSSecret
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 OctetString * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic15_obj02_att07_set(distributor_params_t * p_params, OctetString * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/*********************************************
	FixedString
	{
	    uint8_t   *p_content;
	    uint16_t   length;
	}
	*********************************************/

	/* This function use to change secret of this represented association */
	/* Secret usually stores  in data flash, so you need to change value in there */
	/* This representation association use mechanism: MECHANISM_ID2_HIGH_SECURITY */
	/* If mechenism is MECHANISM_ID0_LOWEST_SECURITY, no use key */
	/* If mechenism is MECHANISM_ID1_LOW_SECURITY, length key is 8 */
	/* If mechenism is others, length key is 16 */
	/* API to access to key content(pointer): g_assc2.authentication_value.p_content */

	
	/* Start user code here */
	if (R_DLMS_Backup_HLS_Key_US(p_attribute_set->p_content, p_attribute_set->length) == RLT_SUCCESS)
	{
		g_event_flag.bits.set_hls_us = TRUE;
		R_DLMS_Cumulative_PC();
		/* Restore new key */
		R_DLMS_Restore_HLSKeyUS();
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;											
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
/******************************************************************************
* Function Name : R_DLMS_USER_ic15_obj02_meth02_action
* Description   : Object name       : Association LN_Utility Setting
*                 Object index      : 02
*                 Class             : 15
*                 Method order      : 02
*                 Method name       : change_HLS_secret
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  OctetString * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic15_obj02_meth02_action(distributor_params_t * p_params, OctetString * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* The structure of the “new secret” depends on the security mechanism implemented.*
	* The “new secret” may contain additional check bits and it may be encrypted.*
	* p_data_from_client::= OctetString->This is new HLS secret.*
	* Length of HLS is 16 *
	* API to access to key content(pointer): g_assc2.authentication_value.p_content *
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if (R_DLMS_Backup_HLS_Key_US(p_data_from_client->p_content, p_data_from_client->length) == RLT_SUCCESS)
	{
		g_event_flag.bits.set_hls_us = TRUE;
		R_DLMS_Cumulative_PC();
		/* Restore new key */
		R_DLMS_Restore_HLSKeyUS();
	}
	else
	{
		return VAL_ACTION_RESULT_READ_WRITE_DENIED;												
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic15_obj04_att07_set
* Description   : Object name       : Association LN_Firmware upgrade 
*                 Object index      : 04
*                 Class             : 15
*                 Attribute order   : 07
*                 Attribute name    : LLSSecret
*                 Association access: {2, Utility Setting}; {4, Firmware upgrade }; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 OctetString * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic15_obj04_att07_set(distributor_params_t * p_params, OctetString * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/*********************************************
	FixedString
	{
	    uint8_t   *p_content;
	    uint16_t   length;
	}
	*********************************************/

	/* This function use to change secret of this represented association */
	/* Secret usually stores  in data flash, so you need to change value in there */
	/* This representation association use mechanism: MECHANISM_ID2_HIGH_SECURITY */
	/* If mechenism is MECHANISM_ID0_LOWEST_SECURITY, no use key */
	/* If mechenism is MECHANISM_ID1_LOW_SECURITY, length key is 8 */
	/* If mechenism is others, length key is 16 */
	/* API to access to key content(pointer): g_assc4.authentication_value.p_content */

	
	/* Start user code here */
	if (R_DLMS_Backup_HLS_Key_FW(p_attribute_set->p_content, p_attribute_set->length) == RLT_SUCCESS)
	{
		g_event_flag.bits.set_hls_fw = TRUE;
		R_DLMS_Cumulative_PC();
		/* Restore new key */
		R_DLMS_Restore_HLSKeyFW();
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;												
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
/******************************************************************************
* Function Name : R_DLMS_USER_ic15_obj04_meth02_action
* Description   : Object name       : Association LN_Firmware upgrade 
*                 Object index      : 04
*                 Class             : 15
*                 Method order      : 02
*                 Method name       : change_HLS_secret
*                 Association access: {2, Utility Setting}; {4, Firmware upgrade }; ;
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  OctetString * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic15_obj04_meth02_action(distributor_params_t * p_params, OctetString * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* The structure of the “new secret” depends on the security mechanism implemented.*
	* The “new secret” may contain additional check bits and it may be encrypted.*
	* p_data_from_client::= OctetString->This is new HLS secret.*
	* Length of HLS is 16 *
	* API to access to key content(pointer): g_assc4.authentication_value.p_content *
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if (R_DLMS_Backup_HLS_Key_FW(p_data_from_client->p_content, p_data_from_client->length) == RLT_SUCCESS)
	{
		g_event_flag.bits.set_hls_fw = TRUE;
		R_DLMS_Cumulative_PC();
		/* Restore new key */
		R_DLMS_Restore_HLSKeyFW();
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;													
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

