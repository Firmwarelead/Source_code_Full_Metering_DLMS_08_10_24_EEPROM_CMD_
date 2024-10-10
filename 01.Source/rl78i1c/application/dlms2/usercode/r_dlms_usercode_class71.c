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
* File Name    : r_dlms_usercode_class71.c
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
#include "r_dlms_usercode_class71.h"

/* User application */
#include "r_dlms_app.h"
#include "r_dlms_cumulate.h"

#include "r_load_ctrl.h"

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
* Object name:      Load limit value in kW
* Object number:    00
* Object obis code: 0.0.17.0.0.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 71
* Variable name: g_dlms_ic71_obj00_att02_monitored_value
* Object name: Load limit value in kW
* Attribute order: 02
* Attribute name: monitored_value
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Programmable
*******************************************************************************/
/*********************************************
 This is structure of send destinationa and methods, please set following  this.
 class71_value_definition_t
 {
       uint16_t class_id;
       FixedString logical_name;
       int8_t attribute_index;
 };
*********************************************/

/* Destination content value */
const uint8_t g_dlms_ic71_obj00_att02_logical_name[] = {1, 0, 1, 7, 0, 255};

/* Declare for variable of monitored_value (class - 71, atrribute - 02)*/
const class71_value_definition_t g_dlms_ic71_obj00_att02_monitored_value  = { 3, { (uint8_t *)&g_dlms_ic71_obj00_att02_logical_name, 6 }, 2 };


/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS71_OBJ00_ATTR03_GET_USERFUNCTION_ENABLE) && (CLASS71_OBJ00_ATTR03_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att03_get
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 03
*                 Attribute name    : threshold_active
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att03_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 0;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
	float32_t threshold = EVENT_GetOverLoadThreshold();
#if (defined(R_LOAD_LIMIT_DATA_TYPE) && R_LOAD_LIMIT_DATA_TYPE == 0)
    p_attribute_get->choice = TAG_DATA_INTEGER;
	p_attribute_get->length = 1;
	*(uint8_t *)p_attribute_get->buffer = (uint8_t)(threshold/1000.0f);
#else
	*(float32_t *)p_attribute_get->buffer = threshold;
#endif//defined(R_LOAD_LIMIT_DATA_TYPE) && R_LOAD_LIMIT_DATA_TYPE == 0
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS71_OBJ00_ATTR03_SET_USERFUNCTION_ENABLE) && (CLASS71_OBJ00_ATTR03_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att03_set
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 03
*                 Attribute name    : threshold_active
*                 Association access: ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att03_set(distributor_params_t * p_params, choice_t * p_attribute_set)
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
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS71_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS71_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att04_get
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 04
*                 Attribute name    : threshold_normal
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 0;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
#if (defined(R_LOAD_LIMIT_DATA_TYPE) && R_LOAD_LIMIT_DATA_TYPE == 0)
    p_attribute_get->choice = TAG_DATA_INTEGER;
	p_attribute_get->length = 1;
	*(int8_t *)p_attribute_get->buffer = g_limiter_normal;
#else
	*(float32_t *)p_attribute_get->buffer = g_limiter_normal;
#endif//defined(R_LOAD_LIMIT_DATA_TYPE) && R_LOAD_LIMIT_DATA_TYPE == 0
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
* !!!IMPORTANT INFO: this attribute have "SET" access right for some association, if you would like to disable this code(off for above macro), please check and change access right of this parallel
 */
#if defined(CLASS71_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS71_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att04_set
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 04
*                 Attribute name    : threshold_normal
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att04_set(distributor_params_t * p_params, choice_t * p_attribute_set)
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
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	if (R_LIMITER_Set_NormalThreashold(*(float32_t *)p_attribute_set->buffer) == TRUE)
	{	
		R_DLMS_Cumulative_PC();
		g_event_flag.bits.set_loadlimit = TRUE;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS71_OBJ00_ATTR05_GET_USERFUNCTION_ENABLE) && (CLASS71_OBJ00_ATTR05_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att05_get
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 05
*                 Attribute name    : threshold_emergency
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att05_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Float32 */
	/* Length: 4 */
	
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
	/* TODO Please assign your data here */
	/* Assign link data here */
	//float32_t link_data_value = 0;
	/* Set value */
	//memcpy(p_attribute_get->buffer, &link_data_value, 4);

	/* Start user code here */
#if (defined(R_LOAD_LIMIT_DATA_TYPE) && R_LOAD_LIMIT_DATA_TYPE == 0)
    p_attribute_get->choice = TAG_DATA_INTEGER;
	p_attribute_get->length = 1;
	*(int8_t *)p_attribute_get->buffer = g_limiter_emergency;
#else
	*(float32_t *)p_attribute_get->buffer = g_limiter_emergency;
#endif//defined(R_LOAD_LIMIT_DATA_TYPE) && R_LOAD_LIMIT_DATA_TYPE == 0
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
* !!!IMPORTANT INFO: this attribute have "SET" access right for some association, if you would like to disable this code(off for above macro), please check and change access right of this parallel
 */
#if defined(CLASS71_OBJ00_ATTR05_SET_USERFUNCTION_ENABLE) && (CLASS71_OBJ00_ATTR05_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att05_set
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 05
*                 Attribute name    : threshold_emergency
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att05_set(distributor_params_t * p_params, choice_t * p_attribute_set)
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
	choice_t
	{
	    struct tag_choice 
	    {
	        attr_type_t	 type;     / Type of the choice /   
	        int16_t      size;     / Size of choosen type /
	    } choice;			      
	    void *buffer;		       / Buffer of choosen type /
	}
	 Need to operate for buffer, just assign value for buffer following choice type.
	Choice type: choice_t
	*********************************************/


	
	/* Start user code here */
	if (R_LIMITER_Set_EmergencyThreashold(*(float32_t *)p_attribute_set->buffer) == TRUE)
	{
		R_DLMS_Cumulative_PC();
		g_event_flag.bits.set_loadlimit = TRUE;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att06_get
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 06
*                 Attribute name    : min_over_threshold_duration
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att06_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

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
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 0;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
    R_LIMITER_Get_OverThresholdDuration(p_attribute_get);

	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att06_set
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 06
*                 Attribute name    : min_over_threshold_duration
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att06_set(distributor_params_t * p_params, uint32_t * p_attribute_set)
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
	Data type:uint32_t(double-long-unsigned)
	*********************************************/


	
	/* Start user code here */
    R_LIMITER_Set_OverThresholdDuration(*p_attribute_set);
	R_DLMS_Cumulative_PC();
	g_event_flag.bits.set_loadlimit = TRUE;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att07_get
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 07
*                 Attribute name    : min_under_threshold_duration
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

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
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 0;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
    R_LIMITER_Get_UnderThresholdDuration(p_attribute_get);
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att07_set
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 07
*                 Attribute name    : min_under_threshold_duration
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att07_set(distributor_params_t * p_params, uint32_t * p_attribute_set)
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
	Data type:uint32_t(double-long-unsigned)
	*********************************************/


	
	/* Start user code here */
    R_LIMITER_Set_UnderThresholdDuration(*p_attribute_set);
	R_DLMS_Cumulative_PC();
	g_event_flag.bits.set_loadlimit = TRUE;
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/*******************************************************************************
* Class ID: 71
* Variable name: g_dlms_ic71_obj00_att08_emergency_profile
* Object name: Load limit value in kW
* Attribute order: 08
* Attribute name: emergency_profile
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Programmable
*******************************************************************************/
/*********************************************
 This is structure of send destinationa and methods, please set following  this.
 class71_emergency_profile_t
 {
       uint16_t * p_emergency_profile_id;
       FixedString emergency_activation_time;
       uint32_t * p_emergency_duration;
 };
*********************************************/

/* Destination content value */
const uint16_t g_dlms_ic71_obj00_att08_emergency_profile_id = 0;
const uint8_t g_dlms_ic71_obj00_att08_emergency_activation_time[] = { 7, 226, 4, 26, 4, 9, 44, 3, 0, 1, 164, 0};
const uint32_t g_dlms_ic71_obj00_att08_emergency_duration = 0;
/* Declare for variable of emergency_profile (class - 71, atrribute - 08)*/
const class71_emergency_profile_t g_dlms_ic71_obj00_att08_emergency_profile  = 
{
	(uint16_t *)&g_dlms_ic71_obj00_att08_emergency_profile_id,
	{ (uint8_t *)&g_dlms_ic71_obj00_att08_emergency_activation_time, 12 },
	(uint32_t *)&g_dlms_ic71_obj00_att08_emergency_duration
};


/*******************************************************************************
* Class ID: 71
* Variable name: g_dlms_ic71_obj00_att09_emergency_profile_group_id_list
* Object name: Load limit value in kW
* Attribute order: 09
* Attribute name: emergency_profile_group_id_list
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Programmable
*******************************************************************************/
/*********************************************
 This is element definition
 uint16_t

 This is array definition
 FixedArrayUint16_t
 {
       uint8_t* p_content;
       uint16_t length;
 }
 p_content: this is pointer of variable uint16_t[]
*********************************************/

/* array content */
const uint16_t g_dlms_ic71_obj00_att09_emergency_profile_group_id_list_content[] = { 2, 3 };
/* Declare for variable of emergency_profile_group_id_list (class - 71, atrribute - 09)*/
const FixedArrayUint16_t g_dlms_ic71_obj00_att09_emergency_profile_group_id_list  = { (uint16_t *)&g_dlms_ic71_obj00_att09_emergency_profile_group_id_list_content, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic71_obj00_att10_get
* Description   : Object name       : Load limit value in kW
*                 Object index      : 00
*                 Class             : 71
*                 Attribute order   : 10
*                 Attribute name    : emergency_profile_active
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att10_get(distributor_params_t * p_params, uint8_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint8_t(boolean)
	*********************************************/

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
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint8_t link_data = FALSE;
	/* Set value */
	//*((uint8_t *)p_attribute_get) = link_data;

	/* Start user code here */
	*p_attribute_get = g_ctrl_relay_progess.flag.IsEmergencyProfileActivated;
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/*******************************************************************************
* Class ID: 71
* Variable name: g_dlms_ic71_obj00_att11_actions
* Object name: Load limit value in kW
* Attribute order: 11
* Attribute name: actions
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous, Programmable
*******************************************************************************/
/*********************************************
 This is structure of action, please set following  this.
 class71_action_t
 {
       class71_action_item_t action_over_threshold;
       class71_action_item_t action_under_threshold;
 };
 This is structure of action item, please set following  this.
 class71_action_item_t
 {
       uint8_t script_logical_name[6];
       uint16_t script_selector;
 };
*********************************************/

/* Action over threshold */
const uint8_t g_dlms_ic71_obj00_att11_script_logical_name_content_of_action_over_threshold[] = { 0, 0, 10, 0, 107, 255 };
const uint16_t g_dlms_ic71_obj00_att11_script_selector_of_action_over_threshold = 1;
const class71_action_item_t g_dlms_ic71_obj00_att11_action_over_threshold = { { (uint8_t *)&g_dlms_ic71_obj00_att11_script_logical_name_content_of_action_over_threshold, 6 }, (uint16_t *)&g_dlms_ic71_obj00_att11_script_selector_of_action_over_threshold };
/* Action under threshold */
const uint8_t g_dlms_ic71_obj00_att11_script_logical_name_content_of_action_under_threshold[] = { 0, 0, 10, 0, 107, 255 };
const uint16_t g_dlms_ic71_obj00_att11_script_selector_of_action_under_threshold = 1;
const class71_action_item_t g_dlms_ic71_obj00_att11_action_under_threshold = { { (uint8_t *)&g_dlms_ic71_obj00_att11_script_logical_name_content_of_action_under_threshold, 6 }, (uint16_t *)&g_dlms_ic71_obj00_att11_script_selector_of_action_under_threshold };
/* Declare for variable of actions (class - 71, atrribute - 11)*/
const class71_action_t g_dlms_ic71_obj00_att11_actions  = 
{ 
	(class71_action_item_t *)&g_dlms_ic71_obj00_att11_action_over_threshold, /* action over threshold */
	(class71_action_item_t *)&g_dlms_ic71_obj00_att11_action_under_threshold/* action under threshold */
};





