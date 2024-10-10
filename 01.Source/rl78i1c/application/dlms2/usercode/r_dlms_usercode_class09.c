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
* File Name    : r_dlms_usercode_class09.c
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
#include "r_dlms_usercode_class09.h"

/* User application */
#include "event.h"
#include "r_dlms_script.h"
#include "r_dlms_app.h"
#include "r_max_demand.h"
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



/***********************************************************************************************************
* Object name:      Image Activation Script table 
* Object number:    00
* Object obis code: 0.0.10.0.107.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 09
* Variable name: g_dlms_ic09_obj00_att02_scripts
* Object name: Image Activation Script table 
* Attribute order: 02
* Attribute name: scripts
* Association access: {1, Meter Reader}; {2, Utility Setting}; {4, Firmware upgrade }; ;
* Group object		: FWU
*******************************************************************************/
/*********************************************
enum service_id_t
{
      ACTION_WRITE_ATTRIBUTE = 1,
      ACTION_EXECUTE_METHOD,
};

struct script_action_t
{
      service_id_t service_id;
      uint16_t class_id;
      uint8_t logical_name[6];
      int16_t index;
      FixedString parameter;
};
array script_actions_t
{
      script_action_t   *p_content;
      uint16_t          length;
}

struct script_t
{
      uint16_t           script_id;
      script_actions_t   *p_actions;
};

array script_array_t
{
      script_t   *p_content;
      uint16_t    length;
}
*********************************************/

/* Component value of each element array */
/* Script 00 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj00_att02_parameter_content_element00_of_actions00[] = {0x00};
/* Script action array 00 */
const script_action_t g_obj00_att02_actions_element00[] =
{
	{ ACTION_EXECUTE_METHOD, 18, { 0, 0, 44, 0, 0, 255 }, 4, { (uint8_t *)&g_dlms_obj00_att02_parameter_content_element00_of_actions00, 4 } }
};
/* Define script actions 00 */
const script_actions_t g_dlms_action_specification00_attr02_data00_array = { (script_action_t *)&g_obj00_att02_actions_element00, 1 };


/* Element array value */
const script_t g_dlms_ic09_obj00_scripts_array_content[] = 
{
   { 1, (script_actions_t *)&g_dlms_action_specification00_attr02_data00_array }
};
/* Declare for variable of scripts (class - 09, atrribute - 02)*/
const script_array_t g_dlms_ic09_obj00_att02_scripts  = { (script_t *)&g_dlms_ic09_obj00_scripts_array_content, 1 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic09_obj00_meth01_action
* Description   : Object name       : Image Activation Script table 
*                 Object index      : 00
*                 Class             : 09
*                 Method order      : 01
*                 Method name       : execute
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  uint16_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic09_obj00_meth01_action(distributor_params_t * p_params, uint16_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Executes the script specified in parameter data.
	* If data matches one of the script_identifiers in the script table,
	*  then the corresponding action_specification is executed.
	* p_data_from_client ::= long-unsigned(uint16_t)
	* This is table of scrpts which you configured.
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x00
	| 0		| 1						| EXECUTE_METHOD	| 18			| 0.0.44.0.0.255	| 4 	| 0x00
	----------------------------------------------------------------------------------------------------------

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
	if(R_DLMS_Script_Execute(R_DLMS_SCRIPT_ID_ACTIVATE_IMAGE) == RLT_SUCCESS)
	{
		
	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Push script table
* Object number:    01
* Object obis code: 0.0.10.0.108.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 09
* Variable name: g_dlms_ic09_obj01_att02_scripts
* Object name: Push script table
* Attribute order: 02
* Attribute name: scripts
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
enum service_id_t
{
      ACTION_WRITE_ATTRIBUTE = 1,
      ACTION_EXECUTE_METHOD,
};

struct script_action_t
{
      service_id_t service_id;
      uint16_t class_id;
      uint8_t logical_name[6];
      int16_t index;
      FixedString parameter;
};
array script_actions_t
{
      script_action_t   *p_content;
      uint16_t          length;
}

struct script_t
{
      uint16_t           script_id;
      script_actions_t   *p_actions;
};

array script_array_t
{
      script_t   *p_content;
      uint16_t    length;
}
*********************************************/

/* Component value of each element array */
/* Script 00 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj01_att02_parameter_content_element00_of_actions00[] = {0x01};
/* Script action array 00 */
const script_action_t g_obj01_att02_actions_element00[] =
{
	{ ACTION_EXECUTE_METHOD, 40, { 0, 0, 25, 9, 0, 255 }, 1, { (uint8_t *)&g_dlms_obj01_att02_parameter_content_element00_of_actions00, 4 } }
};
/* Define script actions 00 */
const script_actions_t g_dlms_action_specification01_attr02_data00_array = { (script_action_t *)&g_obj01_att02_actions_element00, 1 };

/* Script 01 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj01_att02_parameter_content_element00_of_actions01[] = {0x01};
/* Script action array 01 */
const script_action_t g_obj01_att02_actions_element01[] =
{
	{ ACTION_EXECUTE_METHOD, 40, { 0, 1, 25, 9, 0, 255 }, 1, { (uint8_t *)&g_dlms_obj01_att02_parameter_content_element00_of_actions01, 4 } }
};
/* Define script actions 01 */
const script_actions_t g_dlms_action_specification01_attr02_data01_array = { (script_action_t *)&g_obj01_att02_actions_element01, 1 };

/* Script 02 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj01_att02_parameter_content_element00_of_actions02[] = {0x01};
/* Script action array 02 */
const script_action_t g_obj01_att02_actions_element02[] =
{
	{ ACTION_EXECUTE_METHOD, 40, { 0, 2, 25, 9, 0, 255 }, 1, { (uint8_t *)&g_dlms_obj01_att02_parameter_content_element00_of_actions02, 4 } }
};
/* Define script actions 02 */
const script_actions_t g_dlms_action_specification01_attr02_data02_array = { (script_action_t *)&g_obj01_att02_actions_element02, 1 };

/* Script 03 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj01_att02_parameter_content_element00_of_actions03[] = {0x01};
/* Script action array 03 */
const script_action_t g_obj01_att02_actions_element03[] =
{
	{ ACTION_EXECUTE_METHOD, 40, { 0, 3, 25, 9, 0, 255 }, 1, { (uint8_t *)&g_dlms_obj01_att02_parameter_content_element00_of_actions03, 4 } }
};
/* Define script actions 03 */
const script_actions_t g_dlms_action_specification01_attr02_data03_array = { (script_action_t *)&g_obj01_att02_actions_element03, 1 };

/* Script 04 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj01_att02_parameter_content_element00_of_actions04[] = {0x01};
/* Script action array 04 */
const script_action_t g_obj01_att02_actions_element04[] =
{
	{ ACTION_EXECUTE_METHOD, 40, { 0, 4, 25, 9, 0, 255 }, 1, { (uint8_t *)&g_dlms_obj01_att02_parameter_content_element00_of_actions04, 4 } }
};
/* Define script actions 04 */
const script_actions_t g_dlms_action_specification01_attr02_data04_array = { (script_action_t *)&g_obj01_att02_actions_element04, 1 };


/* Element array value */
const script_t g_dlms_ic09_obj01_scripts_array_content[] = 
{
   { 1, (script_actions_t *)&g_dlms_action_specification01_attr02_data00_array }, 
   { 2, (script_actions_t *)&g_dlms_action_specification01_attr02_data01_array }, 
   { 3, (script_actions_t *)&g_dlms_action_specification01_attr02_data02_array }, 
   { 4, (script_actions_t *)&g_dlms_action_specification01_attr02_data03_array }, 
   { 5, (script_actions_t *)&g_dlms_action_specification01_attr02_data04_array }
};
/* Declare for variable of scripts (class - 09, atrribute - 02)*/
const script_array_t g_dlms_ic09_obj01_att02_scripts  = { (script_t *)&g_dlms_ic09_obj01_scripts_array_content, 5 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic09_obj01_meth01_action
* Description   : Object name       : Push script table
*                 Object index      : 01
*                 Class             : 09
*                 Method order      : 01
*                 Method name       : execute
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  uint16_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic09_obj01_meth01_action(distributor_params_t * p_params, uint16_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Executes the script specified in parameter data.
	* If data matches one of the script_identifiers in the script table,
	*  then the corresponding action_specification is executed.
	* p_data_from_client ::= long-unsigned(uint16_t)
	* This is table of scrpts which you configured.
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x01
	| 0		| 1						| EXECUTE_METHOD	| 40			| 0.0.25.9.0.255	| 1 	| 0x01
	----------------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x01
	| 1		| 2						| EXECUTE_METHOD	| 40			| 0.1.25.9.0.255	| 1 	| 0x01
	----------------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x01
	| 2		| 3						| EXECUTE_METHOD	| 40			| 0.2.25.9.0.255	| 1 	| 0x01
	----------------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x01
	| 3		| 4						| EXECUTE_METHOD	| 40			| 0.3.25.9.0.255	| 1 	| 0x01
	----------------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x01
	| 4		| 5						| EXECUTE_METHOD	| 40			| 0.4.25.9.0.255	| 1 	| 0x01
	----------------------------------------------------------------------------------------------------------

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
	uint8_t return_value;
	switch (*p_data_from_client)
	{
	case 0:
		return_value = R_DLMS_Script_Execute(R_DLMS_SCRIPT_ID_PUSH_DATA_TO_HES);
		break;
	case 1:
		return_value = R_DLMS_Script_Execute(R_DLMS_SCRIPT_ID_PUSH_MESSAGE_TO_IHD);
		break;
	case 2:
		return_value = R_DLMS_Script_Execute(R_DLMS_SCRIPT_ID_PUSH_MESSAGE_TO_HES);
		break;
	case 3:
		return_value = R_DLMS_Script_Execute(R_DLMS_SCRIPT_ID_PUSH_DATA_TO_IHD);
		break;
	case 4:
		return_value = R_DLMS_Script_Execute(R_DLMS_SCRIPT_ID_PUSH_EVENT_TO_HES);
		break;
	default:
		break;
	}

	if (return_value == RLT_SUCCESS)
	{

	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Tariffication Script Table
* Object number:    02
* Object obis code: 0.0.10.0.100.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 09
* Variable name: g_dlms_ic09_obj02_att02_scripts
* Object name: Tariffication Script Table
* Attribute order: 02
* Attribute name: scripts
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
enum service_id_t
{
      ACTION_WRITE_ATTRIBUTE = 1,
      ACTION_EXECUTE_METHOD,
};

struct script_action_t
{
      service_id_t service_id;
      uint16_t class_id;
      uint8_t logical_name[6];
      int16_t index;
      FixedString parameter;
};
array script_actions_t
{
      script_action_t   *p_content;
      uint16_t          length;
}

struct script_t
{
      uint16_t           script_id;
      script_actions_t   *p_actions;
};

array script_array_t
{
      script_t   *p_content;
      uint16_t    length;
}
*********************************************/

/* Component value of each element array */
/* Script 00 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj02_att02_parameter_content_element00_of_actions00[] = {0x00};
/* Script action array 00 */
const script_action_t g_obj02_att02_actions_element00[] =
{
	{ ACTION_EXECUTE_METHOD, 0, { 0, 0, 0, 0, 0, 0 }, 0, { (uint8_t *)&g_dlms_obj02_att02_parameter_content_element00_of_actions00, 4 } }
};
/* Define script actions 00 */
const script_actions_t g_dlms_action_specification02_attr02_data00_array = { (script_action_t *)&g_obj02_att02_actions_element00, 1 };

/* Script 01 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj02_att02_parameter_content_element00_of_actions01[] = {0x00};
/* Script action array 01 */
const script_action_t g_obj02_att02_actions_element01[] =
{
	{ ACTION_EXECUTE_METHOD, 0, { 0, 0, 0, 0, 0, 0 }, 0, { (uint8_t *)&g_dlms_obj02_att02_parameter_content_element00_of_actions01, 4 } }
};
/* Define script actions 01 */
const script_actions_t g_dlms_action_specification02_attr02_data01_array = { (script_action_t *)&g_obj02_att02_actions_element01, 1 };

/* Script 02 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj02_att02_parameter_content_element00_of_actions02[] = {0x00};
/* Script action array 02 */
const script_action_t g_obj02_att02_actions_element02[] =
{
	{ ACTION_EXECUTE_METHOD, 0, { 0, 0, 0, 0, 0, 0 }, 0, { (uint8_t *)&g_dlms_obj02_att02_parameter_content_element00_of_actions02, 4 } }
};
/* Define script actions 02 */
const script_actions_t g_dlms_action_specification02_attr02_data02_array = { (script_action_t *)&g_obj02_att02_actions_element02, 1 };

/* Script 03 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj02_att02_parameter_content_element00_of_actions03[] = {0x00};
/* Script action array 03 */
const script_action_t g_obj02_att02_actions_element03[] =
{
	{ ACTION_EXECUTE_METHOD, 0, { 0, 0, 0, 0, 0, 0 }, 0, { (uint8_t *)&g_dlms_obj02_att02_parameter_content_element00_of_actions03, 4 } }
};
/* Define script actions 03 */
const script_actions_t g_dlms_action_specification02_attr02_data03_array = { (script_action_t *)&g_obj02_att02_actions_element03, 1 };

/* Script 04 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj02_att02_parameter_content_element00_of_actions04[] = {0x00};
/* Script action array 04 */
const script_action_t g_obj02_att02_actions_element04[] =
{
	{ ACTION_EXECUTE_METHOD, 0, { 0, 0, 0, 0, 0, 0 }, 0, { (uint8_t *)&g_dlms_obj02_att02_parameter_content_element00_of_actions04, 4 } }
};
/* Define script actions 04 */
const script_actions_t g_dlms_action_specification02_attr02_data04_array = { (script_action_t *)&g_obj02_att02_actions_element04, 1 };

/* Script 05 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj02_att02_parameter_content_element00_of_actions05[] = {0x00};
/* Script action array 05 */
const script_action_t g_obj02_att02_actions_element05[] =
{
	{ ACTION_EXECUTE_METHOD, 0, { 0, 0, 0, 0, 0, 0 }, 0, { (uint8_t *)&g_dlms_obj02_att02_parameter_content_element00_of_actions05, 4 } }
};
/* Define script actions 05 */
const script_actions_t g_dlms_action_specification02_attr02_data05_array = { (script_action_t *)&g_obj02_att02_actions_element05, 1 };


/* Element array value */
const script_t g_dlms_ic09_obj02_scripts_array_content[] = 
{
   { 1, (script_actions_t *)&g_dlms_action_specification02_attr02_data00_array }, 
   { 2, (script_actions_t *)&g_dlms_action_specification02_attr02_data01_array }, 
   { 3, (script_actions_t *)&g_dlms_action_specification02_attr02_data02_array }, 
   { 4, (script_actions_t *)&g_dlms_action_specification02_attr02_data03_array }, 
   { 5, (script_actions_t *)&g_dlms_action_specification02_attr02_data04_array }, 
   { 6, (script_actions_t *)&g_dlms_action_specification02_attr02_data05_array }
};
/* Declare for variable of scripts (class - 09, atrribute - 02)*/
const script_array_t g_dlms_ic09_obj02_att02_scripts  = { (script_t *)&g_dlms_ic09_obj02_scripts_array_content, 6 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic09_obj02_meth01_action
* Description   : Object name       : Tariffication Script Table
*                 Object index      : 02
*                 Class             : 09
*                 Method order      : 01
*                 Method name       : execute
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  uint16_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic09_obj02_meth01_action(distributor_params_t * p_params, uint16_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Executes the script specified in parameter data.
	* If data matches one of the script_identifiers in the script table,
	*  then the corresponding action_specification is executed.
	* p_data_from_client ::= long-unsigned(uint16_t)
	* This is table of scrpts which you configured.
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x00
	| 0		| 1						| EXECUTE_METHOD	| 0			| 0.0.0.0.0.0	| 0 	| 0x00
	----------------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x00
	| 1		| 2						| EXECUTE_METHOD	| 0			| 0.0.0.0.0.0	| 0 	| 0x00
	----------------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x00
	| 2		| 3						| EXECUTE_METHOD	| 0			| 0.0.0.0.0.0	| 0 	| 0x00
	----------------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x00
	| 3		| 4						| EXECUTE_METHOD	| 0			| 0.0.0.0.0.0	| 0 	| 0x00
	----------------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x00
	| 4		| 5						| EXECUTE_METHOD	| 0			| 0.0.0.0.0.0	| 0 	| 0x00
	----------------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x00
	| 5		| 6						| EXECUTE_METHOD	| 0			| 0.0.0.0.0.0	| 0 	| 0x00
	----------------------------------------------------------------------------------------------------------

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

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      MD Reset
* Object number:    03
* Object obis code: 0.0.10.0.1.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 09
* Variable name: g_dlms_ic09_obj03_att02_scripts
* Object name: MD Reset
* Attribute order: 02
* Attribute name: scripts
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
enum service_id_t
{
      ACTION_WRITE_ATTRIBUTE = 1,
      ACTION_EXECUTE_METHOD,
};

struct script_action_t
{
      service_id_t service_id;
      uint16_t class_id;
      uint8_t logical_name[6];
      int16_t index;
      FixedString parameter;
};
array script_actions_t
{
      script_action_t   *p_content;
      uint16_t          length;
}

struct script_t
{
      uint16_t           script_id;
      script_actions_t   *p_actions;
};

array script_array_t
{
      script_t   *p_content;
      uint16_t    length;
}
*********************************************/

/* Component value of each element array */
/* Script 00 */
/* Parameters belong to script action 00 */
const uint8_t g_dlms_obj03_att02_parameter_content_element00_of_actions00[] = {0x00};
/* Script action array 00 */
const script_action_t g_obj03_att02_actions_element00[] =
{
	{ ACTION_EXECUTE_METHOD, 7, { 1, 0, 98, 1, 0, 255 }, 2, { (uint8_t *)&g_dlms_obj03_att02_parameter_content_element00_of_actions00, 4 } }
};
/* Define script actions 00 */
const script_actions_t g_dlms_action_specification03_attr02_data00_array = { (script_action_t *)&g_obj03_att02_actions_element00, 1 };


/* Element array value */
const script_t g_dlms_ic09_obj03_scripts_array_content[] = 
{
   { 1, (script_actions_t *)&g_dlms_action_specification03_attr02_data00_array }
};
/* Declare for variable of scripts (class - 09, atrribute - 02)*/
const script_array_t g_dlms_ic09_obj03_att02_scripts  = { (script_t *)&g_dlms_ic09_obj03_scripts_array_content, 1 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic09_obj03_meth01_action
* Description   : Object name       : MD Reset
*                 Object index      : 03
*                 Class             : 09
*                 Method order      : 01
*                 Method name       : execute
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  uint16_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic09_obj03_meth01_action(distributor_params_t * p_params, uint16_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Executes the script specified in parameter data.
	* If data matches one of the script_identifiers in the script table,
	*  then the corresponding action_specification is executed.
	* p_data_from_client ::= long-unsigned(uint16_t)
	* This is table of scrpts which you configured.
	----------------------------------------------------------------------------------------------------------
	| No.	| script indentifier	| service ID		| Class ID	| Logical name	| Index	| 0x00
	| 0		| 1						| EXECUTE_METHOD	| 7			| 1.0.98.1.0.255	| 2 	| 0x00
	----------------------------------------------------------------------------------------------------------

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
	uint8_t return_value;
	return_value = R_DLMS_Script_Execute(R_DLMS_SCRIPT_ID_BILLING);
	if(return_value == RLT_SUCCESS)
	{
		R_MDM_Reset();
		g_event_flag.bits.md_reset = TRUE;
	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;
	}
	
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


