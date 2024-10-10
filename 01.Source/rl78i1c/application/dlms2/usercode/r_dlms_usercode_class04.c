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
* File Name    : r_dlms_usercode_class04.c
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
#include "r_dlms_usercode_class04.h"

/* User application */
#include "compiler.h"
#include "r_max_demand.h"
#include "r_dlms_date_time.h"
#include "r_dlms_app.h"
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
* Object name:      Maximum Demand  kVA
* Object number:    00
* Object obis code: 1.0.9.6.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS04_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic04_obj00_att02_get
* Description   : Object name       : Maximum Demand  kVA
*                 Object index      : 00
*                 Class             : 04
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj00_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
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
	*(float32_t *)p_attribute_get->buffer = R_MDM_GetApparentMaxDemand();
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS04_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic04_obj00_att02_set
* Description   : Object name       : Maximum Demand  kVA
*                 Object index      : 00
*                 Class             : 04
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj00_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	return result;
}
#endif

/*******************************************************************************
* Class ID: 04
* Variable name: g_dlms_ic04_obj00_att03_Scaler_Unit
* Object name: Maximum Demand  kVA
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 04, atrribute - 03)*/
const scaler_unit_t g_dlms_ic04_obj00_att03_Scaler_Unit  = {3, PHY_UNIT_VOLT_AMPERE};


/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS04_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic04_obj00_att04_get
* Description   : Object name       : Maximum Demand  kVA
*                 Object index      : 00
*                 Class             : 04
*                 Attribute order   : 04
*                 Attribute name    : status
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj00_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Octet_String */
	/* Length: 2 */
	
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
	uint8_t link_data_value[] = "OK";
	/* Please update link_data_length after assign link_data_value */
	uint16_t link_data_length = 2;
	p_attribute_get->choice.size = link_data_length;
	memcpy(p_attribute_get->buffer, &link_data_value, link_data_length);

	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS04_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic04_obj00_att04_set
* Description   : Object name       : Maximum Demand  kVA
*                 Object index      : 00
*                 Class             : 04
*                 Attribute order   : 04
*                 Attribute name    : status
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj00_att04_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	return result;
}
#endif

/******************************************************************************
* Function Name : R_DLMS_USER_ic04_obj00_att05_get
* Description   : Object name       : Maximum Demand  kVA
*                 Object index      : 00
*                 Class             : 04
*                 Attribute order   : 05
*                 Attribute name    : capture_time
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 date_time_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj00_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	date_time_t
	{
	     uint8_t year_high;                    < HI and LO of year. Interpreted as long-unsigned,   >
	     uint8_t year_low;                     < Range is 0 -> 0xFFFF-1. 0xFFFF mean not specified. >
	     uint8_t month;                        < Month. Interpreted as unsigned. 1...12             >
	     uint8_t day_of_month;                 < Day. Interpreted as unsigned. 1...31               >
	     uint8_t day_of_week;                  < Week. Interpreted as unsigned. 1...7               >
	     uint8_t hour;                         < Hour. Interpreted as unsigned. 0...23              >
	     uint8_t minute;                       < Minute. Interpreted as unsigned. 0...59            >
	     uint8_t second;                       < Hour. Interpreted as unsigned. 0...59              >
	     uint8_t hundredths;                   < Hundredths. Interpreted as unsigned. 0...99        >
	     uint8_t deviation_high;               < Interpreted as long,                               >
	     uint8_t deviation_low;                < Range -720 -> 720, in minutes of local time to GMT.>
	     uint8_t clock_status;                 < The clock status for date time value.              >
	}
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
	//date_time_t link_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	/* Set value */
	//*((date_time_t *)p_attribute_get) = link_data;

	/* Start user code here */
	rtc_counter_value_t rtc_capture_time;
	/* Get max demand capture date time */
	R_MDM_GetMaxDemandCapturedTime(&rtc_capture_time);
	/* Convert rtc capture time to dlms time */
    if(R_DLMS_RTC_Convert_DriverRTC2DateTime(p_attribute_get, (rtc_counter_value_t *)&rtc_capture_time) == RLT_SUCCESS)
	{

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
* Function Name : R_DLMS_USER_ic04_obj00_meth01_action
* Description   : Object name       : Maximum Demand  kVA
*                 Object index      : 00
*                 Class             : 04
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj00_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Forces a reset of the object.
	* By invoking this method, the value is set to the default value.
	* The default value is an instance specific constant.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
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
    if(R_MDM_Reset() == MDM_RET_OK)
	{
		
	}
	else
	{
		return VAL_ACTION_RESULT_READ_WRITE_DENIED;
	}	
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Maximum Demand kW
* Object number:    01
* Object obis code: 1.0.1.6.0.255
***********************************************************************************************************/

/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS04_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic04_obj01_att02_get
* Description   : Object name       : Maximum Demand kW
*                 Object index      : 01
*                 Class             : 04
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj01_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get)
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
	*(float32_t *)p_attribute_get->buffer = R_MDM_GetActiveMaxDemand();
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS04_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic04_obj01_att02_set
* Description   : Object name       : Maximum Demand kW
*                 Object index      : 01
*                 Class             : 04
*                 Attribute order   : 02
*                 Attribute name    : value
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj01_att02_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	return result;
}
#endif

/*******************************************************************************
* Class ID: 04
* Variable name: g_dlms_ic04_obj01_att03_Scaler_Unit
* Object name: Maximum Demand kW
* Attribute order: 03
* Attribute name: Scaler_Unit
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Instantaneous
*******************************************************************************/
/*********************************************
scaler_unit_t
{
    int8_t             scaler;       This is the exponent (to the base of 10) of the multiplication factor.
    physical_unit_t    unit;         Enumeration defining the physical unit. See 4.5.3.6 for more detail.
} 
*********************************************/


/* Declare for variable of Scaler_Unit (class - 04, atrribute - 03)*/
const scaler_unit_t g_dlms_ic04_obj01_att03_Scaler_Unit  = {3, PHY_UNIT_WATT};


/* !!!IMPORTANT INFO: this attribute have "GET" access right for some associations, if you would like to disable this code(off for above macro), please check and change access right of this parallel */
#if defined(CLASS04_OBJ01_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS04_OBJ01_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic04_obj01_att04_get
* Description   : Object name       : Maximum Demand kW
*                 Object index      : 01
*                 Class             : 04
*                 Attribute order   : 04
*                 Attribute name    : status
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj01_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/* Configured Choice type: Octet_String */
	/* Length: 2 */
	
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
	uint8_t link_data_value[] = "OK";
	/* Please update link_data_length after assign link_data_value */
	uint16_t link_data_length = 2;
	p_attribute_get->choice.size = link_data_length;
	memcpy(p_attribute_get->buffer, &link_data_value, link_data_length);

	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 */
#if defined(CLASS04_OBJ01_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS04_OBJ01_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic04_obj01_att04_set
* Description   : Object name       : Maximum Demand kW
*                 Object index      : 01
*                 Class             : 04
*                 Attribute order   : 04
*                 Attribute name    : status
*                 Association access: ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 choice_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj01_att04_set(distributor_params_t * p_params, choice_t * p_attribute_set)
{
	uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	return result;
}
#endif

/******************************************************************************
* Function Name : R_DLMS_USER_ic04_obj01_att05_get
* Description   : Object name       : Maximum Demand kW
*                 Object index      : 01
*                 Class             : 04
*                 Attribute order   : 05
*                 Attribute name    : capture_time
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 date_time_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj01_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	date_time_t
	{
	     uint8_t year_high;                    < HI and LO of year. Interpreted as long-unsigned,   >
	     uint8_t year_low;                     < Range is 0 -> 0xFFFF-1. 0xFFFF mean not specified. >
	     uint8_t month;                        < Month. Interpreted as unsigned. 1...12             >
	     uint8_t day_of_month;                 < Day. Interpreted as unsigned. 1...31               >
	     uint8_t day_of_week;                  < Week. Interpreted as unsigned. 1...7               >
	     uint8_t hour;                         < Hour. Interpreted as unsigned. 0...23              >
	     uint8_t minute;                       < Minute. Interpreted as unsigned. 0...59            >
	     uint8_t second;                       < Hour. Interpreted as unsigned. 0...59              >
	     uint8_t hundredths;                   < Hundredths. Interpreted as unsigned. 0...99        >
	     uint8_t deviation_high;               < Interpreted as long,                               >
	     uint8_t deviation_low;                < Range -720 -> 720, in minutes of local time to GMT.>
	     uint8_t clock_status;                 < The clock status for date time value.              >
	}
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
	//date_time_t link_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	/* Set value */
	//*((date_time_t *)p_attribute_get) = link_data;

	/* Start user code here */
	rtc_counter_value_t rtc_capture_time;
	/* Get max demand capture date time */
	R_MDM_GetMaxDemandCapturedTime(&rtc_capture_time);
	/* Convert rtc capture time to dlms time */
    if(R_DLMS_RTC_Convert_DriverRTC2DateTime(p_attribute_get, (rtc_counter_value_t *)&rtc_capture_time) == RLT_SUCCESS)
	{

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
* Function Name : R_DLMS_USER_ic04_obj01_meth01_action
* Description   : Object name       : Maximum Demand kW
*                 Object index      : 01
*                 Class             : 04
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Instantaneous
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj01_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Forces a reset of the object.
	* By invoking this method, the value is set to the default value.
	* The default value is an instance specific constant.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
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
	* Please do these 2 code lines to report that your action status to client for 2 cases:													 *
	* 1. Action execute successfully:																										 *
	* 	OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SUCCESS, FALSE); (status :VAL_ACTION_RESULT_SUCCESS)							 *
	* 	OBIS_DISTRIBUTION_SUCCESS(p_params->result);																						 *
	* 2. if have any exception during executing action																						 *
	* 	OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);(status :VAL_ACTION_RESULT_TYPE_UNMATCHED(example))	 *
	* 	OBIS_DISTRIBUTION_FAILED(p_params->result);																							 *
	* 	*Note: in this case: please refer ActionResult_Value enum to put your case of exception corresponding with case by case.			 *
	*****************************************************************************************************************************************/
	/* Start user code here */
    if(R_MDM_Reset() == MDM_RET_OK)
	{
		
	}
	else
	{
		return VAL_ACTION_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


