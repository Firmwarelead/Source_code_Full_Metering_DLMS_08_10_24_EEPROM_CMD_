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
* File Name    : r_dlms_usercode_class22.c
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
#include "r_dlms_usercode_class22.h"

/* User application */
#include "r_dlms_app.h"
#include "r_scheduler.h"
#include "r_dlms_cumulate.h"
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

void R_DLMS_USER_ic22_Init(void)
{

}
/**********************************************************************************************************************
 * Function Name: execution_time_get      
 * Description  : Function to get data of execution time of schedule_id
 * Arguments    : p_params - service parameters
 *                p_attribute_get - attribute get data,
 *                schedule_id - schedule id would like to get
 * Return Value : void                   
 **********************************************************************************************************************/
static uint8_t execution_time_get(distributor_params_t * p_params,
 							   class22_exe_time_array_t * p_attribute_get,
							   uint8_t schedule_id)
{
	uint8_t get_time_result = TRUE;
	uint8_t get_date_result = TRUE;
	int16_t length_value;
	uint8_t date_schedule[4];
	uint16_t i;// index window in array 
	uint16_t year;
	/* Get length execution time array */
	length_value = R_SCHEDULER_ExecutionTimeArrayLengthGet(schedule_id);
	if(length_value < 0)
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{
		p_attribute_get->length = (uint16_t)length_value;
	}
	/* Loop all array to get data */
	for(i = 0; i < p_attribute_get->length; i++)
	{
		/* Get time */
		get_time_result = R_SCHEDULER_ExecutionTimeGet((uint8_t *)p_attribute_get->p_content[i].p_time, schedule_id, i);
		if(get_time_result == FALSE)
		{
			break;
		}
		p_attribute_get->p_content[i].p_time->hundredths = 0;//As DLMS Bluebooth, this field shall be 0 as default value.
		
		/* Get date */
		get_date_result = R_SCHEDULER_ExecutionDateGet(date_schedule, schedule_id, i);
		if(get_date_result == FALSE)
		{
			break;
		}
		/* Convert date schedule to dlms date */
		if(date_schedule[0] == 0xFF)
		{
			p_attribute_get->p_content[i].p_date->year_high = 0xFF;
			p_attribute_get->p_content[i].p_date->year_low = 0xFF;
		}
		else
		{
			year = 2000 + (uint16_t)date_schedule[0];
			p_attribute_get->p_content[i].p_date->year_high = (uint8_t)(year>>8);
			p_attribute_get->p_content[i].p_date->year_low = (uint8_t)year;
		}
		p_attribute_get->p_content[i].p_date->month = date_schedule[1];
		p_attribute_get->p_content[i].p_date->day_of_week = date_schedule[2];
		p_attribute_get->p_content[i].p_date->day_of_month = date_schedule[3];

        R_DLMS_RTC_Convert_DLMSWeekToDriverWeek(
            &p_attribute_get->p_content[i].p_date->day_of_week,     /* Dest */
            &p_attribute_get->p_content[i].p_date->day_of_week      /* Src */
        );

	}
	if((get_time_result == TRUE) && (get_date_result == TRUE))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;												
	}
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/**********************************************************************************************************************
 * Function Name: execution_time_set      
 * Description  : Function to set data of execution time of schedule_id
 * Arguments    : p_params - service parameters
 *                p_attribute_set - attribute set data,
 *                schedule_id - schedule id would like to get
 * Return Value : uint8_t                   
 **********************************************************************************************************************/
static uint8_t execution_time_set(distributor_params_t * p_params,
 							   class22_exe_time_array_t * p_attribute_set,
							   uint8_t schedule_id)
{
	uint8_t set_time_result = TRUE;
	uint8_t set_date_result = TRUE;
	uint16_t year;
	uint8_t date_schedule[4];
	uint16_t i;// index window in array 
	/* Get length window array */
	if (R_SCHEDULER_ExecutionTimeArrayLengthSet(schedule_id, p_attribute_set->length) == TRUE)
	{
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* Loop all window array to set data */
	for(i = 0; i < p_attribute_set->length; i++)
	{
		/* Set time */
		/* For time, not set for hundreds second */
		set_time_result = R_SCHEDULER_ExecutionTimeSet((uint8_t *)p_attribute_set->p_content[i].p_time, schedule_id, i);
		if(set_time_result == FALSE)
		{
			break;
		}
		
		/* Set date */
		/* Convert DLMS date to schedule date */
    	year = (uint16_t)(p_attribute_set->p_content[i].p_date->year_high << 8) + p_attribute_set->p_content[i].p_date->year_low;
		if (year == 0xFFFF)
		{
			date_schedule[0] = 0xFF;
		}
		else
		{
			date_schedule[0] = year % 100;
		}
		date_schedule[1] = p_attribute_set->p_content[i].p_date->month;
		date_schedule[2] = p_attribute_set->p_content[i].p_date->day_of_week;
		date_schedule[3] = p_attribute_set->p_content[i].p_date->day_of_month;

        R_DLMS_RTC_Convert_DLMSWeekToDriverWeek(&date_schedule[2], &date_schedule[2]);

		/* Set data */
		set_date_result = R_SCHEDULER_ExecutionDateSet(date_schedule, schedule_id, i);
		if(set_date_result == FALSE)
		{
			break;
		}
	}
	if((set_time_result == TRUE) && (set_date_result == TRUE))
	{
		/* Write data to storage */
		R_SCHEDULER_BackupByID(schedule_id);
		if(schedule_id == 3)//For set date time of billing
		{
			g_event_flag.bits.set_billing_dates = TRUE;
		}
		else
		{
			
		}
		R_DLMS_Cumulative_PC();
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;											
	}
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
/****************************************************************************************************************************************************
*****************************************************************************************************************************************************
**
**    Start of application: NONE
**
*****************************************************************************************************************************************************
****************************************************************************************************************************************************/
/***********************************************************************************************************
* Object name:      Schedule for push - SM to IHD Push
* Object number:    00
* Object obis code: 0.3.15.0.4.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 22
* Variable name: g_dlms_ic22_obj00_att02_executed_script
* Object name: Schedule for push - SM to IHD Push
* Attribute order: 02
* Attribute name: executed_script
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
 This is structure of script, please set following  this.
 class22_executed_script_t
 {
     uint8_t script_logical_name[6];
     uint16_t script_selector;
 };
*********************************************/


/* Declare for variable of executed_script (class - 22, atrribute - 02)*/
const class22_executed_script_t g_dlms_ic22_obj00_att02_executed_script  = { {0, 0, 10, 0, 108, 255}, 2 };


/*******************************************************************************
* Class ID: 22
* Variable name: g_dlms_ic22_obj00_att03_type
* Object name: Schedule for push - SM to IHD Push
* Attribute order: 03
* Attribute name: type
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
typedef enum tag_class22_exe_time_type_t
{
    CLASS22_EXE_TIME_TYPE_01 = 1, ||size of execution_time = 1; wildcard in date allowed                                    ||
    CLASS22_EXE_TIME_TYPE_02,     ||size of execution_time = n; all time values are the same, wildcards in date not allowed ||
    CLASS22_EXE_TIME_TYPE_03,     ||size of execution_time = n; all time values are the same, wildcards in date are allowed ||
    CLASS22_EXE_TIME_TYPE_04,     ||size of execution_time = n; time values may be different, wildcards in date not allowed ||
    CLASS22_EXE_TIME_TYPE_05,     ||size of execution_time = n; time values may be different, wildcards in date are allowed ||
};
*********************************************/


/* Declare for variable of type (class - 22, atrribute - 03)*/
const class22_exe_time_type_t g_dlms_ic22_obj00_att03_type  = CLASS22_EXE_TIME_TYPE_01;


/* Please update your array size following your setting change by asigning under variable */
/* For execution_time */
const uint16_t r_dlms_ic22_obj00_att04_array_length = SCHEDULE_EXECUTION_TIME_MAX_SUPPORT;
/******************************************************************************
* Function Name : R_DLMS_USER_ic22_obj00_att04_get
* Description   : Object name       : Schedule for push - SM to IHD Push
*                 Object index      : 00
*                 Class             : 22
*                 Attribute order   : 04
*                 Attribute name    : execution_time
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class22_exe_time_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic22_obj00_att04_get(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic22_obj00_att04_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic22_obj00_att04_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is array of image to activate info
	 class22_exe_time_t {
	    time_t* p_time;
	    date_t* p_date;
	}
	 class22_exe_time_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class22_exe_time_t[]
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
	/* Please add at least one element of this array to get refer code */

	/* Start user code here */
	return execution_time_get(p_params, p_attribute_get, 2);//2 is index of SM->IHD scheduler
	/* End user code here */

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic22_obj00_att04_set
* Description   : Object name       : Schedule for push - SM to IHD Push
*                 Object index      : 00
*                 Class             : 22
*                 Attribute order   : 04
*                 Attribute name    : execution_time
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class22_exe_time_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic22_obj00_att04_set(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_set)
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
	 This is array of image to activate info
	 class22_exe_time_t {
	    time_t* p_time;
	    date_t* p_date;
	}
	 class22_exe_time_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class22_exe_time_t[]
	*********************************************/


	
	/* Start user code here */
	return execution_time_set(p_params, p_attribute_set, 2);//2 is index of SM->IHD scheduler
	/* End user code here */
}



/***********************************************************************************************************
* Object name:      Single Action Schedule - SM to HES Push
* Object number:    01
* Object obis code: 0.0.15.0.4.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 22
* Variable name: g_dlms_ic22_obj01_att02_executed_script
* Object name: Single Action Schedule - SM to HES Push
* Attribute order: 02
* Attribute name: executed_script
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
 This is structure of script, please set following  this.
 class22_executed_script_t
 {
     uint8_t script_logical_name[6];
     uint16_t script_selector;
 };
*********************************************/


/* Declare for variable of executed_script (class - 22, atrribute - 02)*/
const class22_executed_script_t g_dlms_ic22_obj01_att02_executed_script  = { {0, 0, 10, 0, 108, 255}, 2 };


/*******************************************************************************
* Class ID: 22
* Variable name: g_dlms_ic22_obj01_att03_type
* Object name: Single Action Schedule - SM to HES Push
* Attribute order: 03
* Attribute name: type
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
typedef enum tag_class22_exe_time_type_t
{
    CLASS22_EXE_TIME_TYPE_01 = 1, ||size of execution_time = 1; wildcard in date allowed                                    ||
    CLASS22_EXE_TIME_TYPE_02,     ||size of execution_time = n; all time values are the same, wildcards in date not allowed ||
    CLASS22_EXE_TIME_TYPE_03,     ||size of execution_time = n; all time values are the same, wildcards in date are allowed ||
    CLASS22_EXE_TIME_TYPE_04,     ||size of execution_time = n; time values may be different, wildcards in date not allowed ||
    CLASS22_EXE_TIME_TYPE_05,     ||size of execution_time = n; time values may be different, wildcards in date are allowed ||
};
*********************************************/


/* Declare for variable of type (class - 22, atrribute - 03)*/
const class22_exe_time_type_t g_dlms_ic22_obj01_att03_type  = CLASS22_EXE_TIME_TYPE_01;


/* Please update your array size following your setting change by asigning under variable */
/* For execution_time */
const uint16_t r_dlms_ic22_obj01_att04_array_length = SCHEDULE_EXECUTION_TIME_MAX_SUPPORT;
/******************************************************************************
* Function Name : R_DLMS_USER_ic22_obj01_att04_get
* Description   : Object name       : Single Action Schedule - SM to HES Push
*                 Object index      : 01
*                 Class             : 22
*                 Attribute order   : 04
*                 Attribute name    : execution_time
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class22_exe_time_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic22_obj01_att04_get(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic22_obj01_att04_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic22_obj01_att04_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is array of image to activate info
	 class22_exe_time_t {
	    time_t* p_time;
	    date_t* p_date;
	}
	 class22_exe_time_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class22_exe_time_t[]
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
	/* Please add at least one element of this array to get refer code */

	/* Start user code here */
	return execution_time_get(p_params, p_attribute_get, 1);//1 is index of SM->HES scheduler
	/* End user code here */

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic22_obj01_att04_set
* Description   : Object name       : Single Action Schedule - SM to HES Push
*                 Object index      : 01
*                 Class             : 22
*                 Attribute order   : 04
*                 Attribute name    : execution_time
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class22_exe_time_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic22_obj01_att04_set(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_set)
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
	 This is array of image to activate info
	 class22_exe_time_t {
	    time_t* p_time;
	    date_t* p_date;
	}
	 class22_exe_time_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class22_exe_time_t[]
	*********************************************/


	
	/* Start user code here */
	return execution_time_set(p_params, p_attribute_set, 1);//1 is index of SM->HES scheduler
	/* End user code here */
}



/***********************************************************************************************************
* Object name:      Single action schedule- Billing
* Object number:    02
* Object obis code: 0.0.15.0.0.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 22
* Variable name: g_dlms_ic22_obj02_att02_executed_script
* Object name: Single action schedule- Billing
* Attribute order: 02
* Attribute name: executed_script
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Programmable
*******************************************************************************/
/*********************************************
 This is structure of script, please set following  this.
 class22_executed_script_t
 {
     uint8_t script_logical_name[6];
     uint16_t script_selector;
 };
*********************************************/


/* Declare for variable of executed_script (class - 22, atrribute - 02)*/
const class22_executed_script_t g_dlms_ic22_obj02_att02_executed_script  = { {0, 0, 10, 0, 107, 255}, 1 };


/*******************************************************************************
* Class ID: 22
* Variable name: g_dlms_ic22_obj02_att03_type
* Object name: Single action schedule- Billing
* Attribute order: 03
* Attribute name: type
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Programmable
*******************************************************************************/
/*********************************************
typedef enum tag_class22_exe_time_type_t
{
    CLASS22_EXE_TIME_TYPE_01 = 1, ||size of execution_time = 1; wildcard in date allowed                                    ||
    CLASS22_EXE_TIME_TYPE_02,     ||size of execution_time = n; all time values are the same, wildcards in date not allowed ||
    CLASS22_EXE_TIME_TYPE_03,     ||size of execution_time = n; all time values are the same, wildcards in date are allowed ||
    CLASS22_EXE_TIME_TYPE_04,     ||size of execution_time = n; time values may be different, wildcards in date not allowed ||
    CLASS22_EXE_TIME_TYPE_05,     ||size of execution_time = n; time values may be different, wildcards in date are allowed ||
};
*********************************************/


/* Declare for variable of type (class - 22, atrribute - 03)*/
const class22_exe_time_type_t g_dlms_ic22_obj02_att03_type  = CLASS22_EXE_TIME_TYPE_01;


/* Please update your array size following your setting change by asigning under variable */
/* For execution_time */
const uint16_t r_dlms_ic22_obj02_att04_array_length = SCHEDULE_EXECUTION_TIME_MAX_SUPPORT;
/******************************************************************************
* Function Name : R_DLMS_USER_ic22_obj02_att04_get
* Description   : Object name       : Single action schedule- Billing
*                 Object index      : 02
*                 Class             : 22
*                 Attribute order   : 04
*                 Attribute name    : execution_time
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class22_exe_time_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic22_obj02_att04_get(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic22_obj02_att04_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic22_obj02_att04_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is array of image to activate info
	 class22_exe_time_t {
	    time_t* p_time;
	    date_t* p_date;
	}
	 class22_exe_time_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class22_exe_time_t[]
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


	/* Element 00 */
	//time_t time_link_element00 = { 0, 0, 0, 0};
	//date_t date_link_element00 = { 0, 0, 0, 0, 0};



	/* Set value for element at 0*/
	//memcpy(p_attribute_get->p_content[0].p_time, &time_link_element00, 4);
	//memcpy(p_attribute_get->p_content[0].p_date, &date_link_element00, 5);

	/* Set length for this array */
	//p_attribute_get->length = r_dlms_ic22_obj02_att04_array_length;


	/* Start user code here */
	return execution_time_get(p_params, p_attribute_get, 3);//3 is index of billing scheduler
	/* End user code here */

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic22_obj02_att04_set
* Description   : Object name       : Single action schedule- Billing
*                 Object index      : 02
*                 Class             : 22
*                 Attribute order   : 04
*                 Attribute name    : execution_time
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class22_exe_time_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic22_obj02_att04_set(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_set)
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
	 This is array of image to activate info
	 class22_exe_time_t {
	    time_t* p_time;
	    date_t* p_date;
	}
	 class22_exe_time_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class22_exe_time_t[]
	*********************************************/


	
	/* Start user code here */
	return execution_time_set(p_params, p_attribute_set, 3);//3 is index of billing scheduler
	//TODO need to enable when apply r_dlms_event.c g_dlms_event_flag.external_event_7 = TRUE;
	/* End user code here */
}



/***********************************************************************************************************
* Object name:      Single Action Schedule -Image Activation
* Object number:    03
* Object obis code: 0.0.15.0.2.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 22
* Variable name: g_dlms_ic22_obj03_att02_executed_script
* Object name: Single Action Schedule -Image Activation
* Attribute order: 02
* Attribute name: executed_script
* Association access: {1, Meter Reader}; {2, Utility Setting}; {4, Firmware upgrade }; ;
* Group object		: Programmable
*******************************************************************************/
/*********************************************
 This is structure of script, please set following  this.
 class22_executed_script_t
 {
     uint8_t script_logical_name[6];
     uint16_t script_selector;
 };
*********************************************/


/* Declare for variable of executed_script (class - 22, atrribute - 02)*/
const class22_executed_script_t g_dlms_ic22_obj03_att02_executed_script  = { {0, 0, 10, 0, 107, 255}, 1 };


/*******************************************************************************
* Class ID: 22
* Variable name: g_dlms_ic22_obj03_att03_type
* Object name: Single Action Schedule -Image Activation
* Attribute order: 03
* Attribute name: type
* Association access: {1, Meter Reader}; {2, Utility Setting}; {4, Firmware upgrade }; ;
* Group object		: Programmable
*******************************************************************************/
/*********************************************
typedef enum tag_class22_exe_time_type_t
{
    CLASS22_EXE_TIME_TYPE_01 = 1, ||size of execution_time = 1; wildcard in date allowed                                    ||
    CLASS22_EXE_TIME_TYPE_02,     ||size of execution_time = n; all time values are the same, wildcards in date not allowed ||
    CLASS22_EXE_TIME_TYPE_03,     ||size of execution_time = n; all time values are the same, wildcards in date are allowed ||
    CLASS22_EXE_TIME_TYPE_04,     ||size of execution_time = n; time values may be different, wildcards in date not allowed ||
    CLASS22_EXE_TIME_TYPE_05,     ||size of execution_time = n; time values may be different, wildcards in date are allowed ||
};
*********************************************/


/* Declare for variable of type (class - 22, atrribute - 03)*/
const class22_exe_time_type_t g_dlms_ic22_obj03_att03_type  = CLASS22_EXE_TIME_TYPE_01;


/* Please update your array size following your setting change by asigning under variable */
/* For execution_time */
const uint16_t r_dlms_ic22_obj03_att04_array_length = SCHEDULE_EXECUTION_TIME_MAX_SUPPORT;
/******************************************************************************
* Function Name : R_DLMS_USER_ic22_obj03_att04_get
* Description   : Object name       : Single Action Schedule -Image Activation
*                 Object index      : 03
*                 Class             : 22
*                 Attribute order   : 04
*                 Attribute name    : execution_time
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {4, Firmware upgrade }; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class22_exe_time_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic22_obj03_att04_get(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic22_obj03_att04_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic22_obj03_att04_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is array of image to activate info
	 class22_exe_time_t {
	    time_t* p_time;
	    date_t* p_date;
	}
	 class22_exe_time_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class22_exe_time_t[]
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


	/* Element 00 */
	//time_t time_link_element00 = { 0, 0, 0, 0};
	//date_t date_link_element00 = { 0, 0, 0, 0, 0};



	/* Set value for element at 0*/
	//memcpy(p_attribute_get->p_content[0].p_time, &time_link_element00, 4);
	//memcpy(p_attribute_get->p_content[0].p_date, &date_link_element00, 5);

	/* Set length for this array */
	//p_attribute_get->length = r_dlms_ic22_obj03_att04_array_length;


	/* Start user code here */
	return execution_time_get(p_params, p_attribute_get, 4);//4 is index of image activate scheduler
	/* End user code here */

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic22_obj03_att04_set
* Description   : Object name       : Single Action Schedule -Image Activation
*                 Object index      : 03
*                 Class             : 22
*                 Attribute order   : 04
*                 Attribute name    : execution_time
*                 Association access: {2, Utility Setting}; {4, Firmware upgrade }; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class22_exe_time_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic22_obj03_att04_set(distributor_params_t * p_params, class22_exe_time_array_t * p_attribute_set)
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
	 This is array of image to activate info
	 class22_exe_time_t {
	    time_t* p_time;
	    date_t* p_date;
	}
	 class22_exe_time_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	 }
	 p_content: this is pointer of variable class22_exe_time_t[]
	*********************************************/

	/* Start user code here */
	return execution_time_set(p_params, p_attribute_set, 4);//4 is index of image activate scheduler
	/* End user code here */
}



