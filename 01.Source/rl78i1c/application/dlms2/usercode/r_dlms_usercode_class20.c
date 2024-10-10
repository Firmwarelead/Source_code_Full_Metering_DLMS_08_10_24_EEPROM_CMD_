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
* File Name    : r_dlms_usercode_class20.c
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
#include "r_dlms_usercode_class20.h"

/* User application */
#include "r_dlms_app.h"
#include "r_activity_cal.h"
#include "r_dlms_cumulate.h"
#include "r_scheduler.h"
#include "r_dlms_date_time.h"
#include "r_activity_cal.h"

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
* Function Name : R_DLMS_USER_ic20_Init
* Interface     : void R_DLMS_USER_ic20_Init(
*               :     void
*               : );
* Description   : THis function to init data for calendar
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_DLMS_USER_ic20_Init(void)
{

}

/**********************************************************************************************************************
 * Function Name: calendar_name_get      
 * Description  : this is common function to get calendar name
 * Arguments    : p_params - service parameters,
 *                p_attribute_get - attribute get data,
 *                is_passive - determine that is active or passive.   
 * Return Value : uint8_t                     
 **********************************************************************************************************************/
 static uint8_t calendar_name_get(distributor_params_t * p_params,
 							   OctetString * p_attribute_get,
							   uint8_t is_passive)
 {
	r_act_cal_name_t calendar_name_get;

	/* Get calendar name from storage */
	calendar_name_get = R_ACT_CAL_Restore_CalendarName(is_passive);

	p_attribute_get->length = (uint16_t)calendar_name_get.len;
	memcpy(p_attribute_get->p_content, calendar_name_get.value, p_attribute_get->length);
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
 }

/**********************************************************************************************************************
 * Function Name: season_profile_array_get      
 * Description  : this is common function to get season profile arrau data
 * Arguments    : p_params - service parameters,
 *                p_attribute_get - attribute get data,
 *                is_passive - determine that is active or passive.   
 * Return Value : uint8_t                     
 **********************************************************************************************************************/
 static uint8_t season_profile_array_get(distributor_params_t * p_params,
 									  class20_season_profile_array_t * p_attribute_get,
									  uint8_t is_passive)
 {
	r_act_cal_season_profile_t season_profile;
	uint16_t i;// index in array 
    rtc_counter_value_t *p_rtc_time;
    
	/* Get season profile */
	season_profile = R_ACT_CAL_Restore_SeasonProfile(is_passive);
	/* Get length array */
	p_attribute_get->length = (uint16_t)season_profile.num;
	/* Loop all season profiles to get data */
	for(i = 0; i < p_attribute_get->length; i++)
	{
		/* Check length of season name */
		if(season_profile.entry[i].name.len > NAME_LENGTH_MAX)
		{
			return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
		}
		else
		{
			/* code */
		}
		
		/* Pass data for season profile name */
		p_attribute_get->p_content[i].season_profile_name.length = (uint16_t)season_profile.entry[i].name.len;
		memcpy(
			p_attribute_get->p_content[i].season_profile_name.p_content,
			season_profile.entry[i].name.value,
			p_attribute_get->p_content[i].season_profile_name.length);

		/* Convert and pass data for date time from rtc format to dlms format */    
		R_DLMS_RTC_Convert_RTC2DateTime2(
			&p_attribute_get->p_content[i].season_start,
			&season_profile.entry[i].start_time);

		/* Check length of week name */
		if(season_profile.entry[i].week.len > NAME_LENGTH_MAX)
		{
			return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
		}
		else
		{
			/* code */
		}

		/* Pass week profile name */
		p_attribute_get->p_content[i].week_profile_name.length = (uint16_t)season_profile.entry[i].week.len;
		memcpy(
			p_attribute_get->p_content[i].week_profile_name.p_content,
			season_profile.entry[i].week.value,
			p_attribute_get->p_content[i].week_profile_name.length);
	}
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
 }
/**********************************************************************************************************************
 * Function Name: week_profile_array_get      
 * Description  : this is common function to get week profile array data
 * Arguments    : p_params - service parameters,
 *                p_attribute_get - attribute get data,
 *                is_passive - determine that is active or passive.    
 * Return Value : uint8_t                     
 **********************************************************************************************************************/
 static uint8_t week_profile_array_get(distributor_params_t * p_params,
 									class20_week_profile_table_array_t * p_attribute_get,
									uint8_t is_passive)
 {
	uint16_t i;// index in array 
	r_act_cal_week_profile_t week_profile;

	/* Get week profile from storage */
	week_profile = R_ACT_CAL_Restore_WeekProfile(is_passive);

	/* Pass length of week profile */
	p_attribute_get->length = (uint16_t)week_profile.num;
	/* Loop all week profiles to get data */
	for(i = 0; i < p_attribute_get->length; i++)
	{
		if(week_profile.entry[i].name.len > NAME_LENGTH_MAX)
		{
			return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
		}
		/* Pass week profile name */
		p_attribute_get->p_content[i].week_profile_name.length = (uint16_t)week_profile.entry[i].name.len;
		memcpy(
			p_attribute_get->p_content[i].week_profile_name.p_content,
			week_profile.entry[i].name.value,
			p_attribute_get->p_content[i].week_profile_name.length);
		
		/* Pass week datas all */
		memcpy(
			p_attribute_get->p_content[i].data,
			week_profile.entry[i].data,
			7);//7 is number days in weeks, refer to class20, attribute 04 definition of blue book.
	}
	return VAL_DATA_ACCESS_RESULT_SUCCESS;

 }

 /**********************************************************************************************************************
 * Function Name: day_profile_array_get      
 * Description  : this is common function to get week profile array data
 * Arguments    : p_params - service parameters,
 *                p_attribute_get - attribute get data,
 *                is_passive - determine that is active or passive.     
 * Return Value : uint8_t                     
 **********************************************************************************************************************/
 static uint8_t day_profile_array_get(distributor_params_t * p_params,
 								   class20_day_profile_table_array_t * p_attribute_get,
								   uint8_t is_passive)
 {
	uint16_t i, j;// index in array 
	r_act_cal_day_profile_t day_profile;
	uint8_t action_script_logical_name[] = { 0,   0,   10,   0,  100, 255};

	/* Get day profile from storage */
	day_profile = R_ACT_CAL_Restore_DayProfile(is_passive);

	/* Pass number profile */
	p_attribute_get->length = (uint16_t)day_profile.num;
	/* Loop all day profiles to pass data */
	for(i = 0; i < p_attribute_get->length; i++)
	{
		/* Pass Day ID */
		p_attribute_get->p_content[i].day_id = day_profile.entry[i].dayID;

		/* Check number of action */
		if(day_profile.entry[i].numberOfAction > DAY_ACTION_ELEMENT_MAX)
		{
			return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
		}
		else
		{

		}
		/* Pass number of action */
		p_attribute_get->p_content[i].day_schedule.length = (uint16_t)day_profile.entry[i].numberOfAction;
		/* loop all schedule at i day profile  */
		for(j = 0; j < p_attribute_get->p_content[i].day_schedule.length; j++)
		{
			/* Pass start time data */
			p_attribute_get->p_content[i].day_schedule.p_content[j].start_time.hour = day_profile.entry[i].action[j].hour;
			p_attribute_get->p_content[i].day_schedule.p_content[j].start_time.minute = day_profile.entry[i].action[j].min;
			p_attribute_get->p_content[i].day_schedule.p_content[j].start_time.second = 0;
			p_attribute_get->p_content[i].day_schedule.p_content[j].start_time.hundredths = 0;

			/* Pass script logical name */
			memcpy(
				p_attribute_get->p_content[i].day_schedule.p_content[j].script_logical_name,
				action_script_logical_name,
				6);
			/* Pass script selector */
			p_attribute_get->p_content[i].day_schedule.p_content[j].script_selector = day_profile.entry[i].action[j].scriptID;
		}		
	}
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/****************************************************************************************************************************************************
*****************************************************************************************************************************************************
**
**    Start of application: PROGRAMMABLE
**
*****************************************************************************************************************************************************
****************************************************************************************************************************************************/
/***********************************************************************************************************
* Object name:      Activity calendar
* Object number:    00
* Object obis code: 0.0.13.0.0.255
***********************************************************************************************************/

/* Please update your array size following your setting change by asigning under variable */
/* For calendar_name_active */
const uint16_t r_dlms_ic20_obj00_att02_calendar_name_active_string_length = NAME_LENGTH_MAX;
/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att02_get
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 02
*                 Attribute name    : calendar_name_active
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 OctetString * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att02_get(distributor_params_t * p_params, OctetString * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	OctetString
	{
	    uint8_t   *p_content;
	    uint16_t   length;
	    uint16_t   alloc_size;
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
	/* Assign data link here */
	//uint8_t link_data_string[] =  "activec alendar name";
	/* Set length for string */
	/* !!! If change content of link_data_string, please update r_dlms_ic20_obj00_att02_calendar_name_active_string_length */
	//p_attribute_get->length = r_dlms_ic20_obj00_att02_calendar_name_active_string_length;
	/* Set value for string */
	//memcpy(p_attribute_get->p_content, &link_data_string, r_dlms_ic20_obj00_att02_calendar_name_active_string_length);

	/* Start user code here */
	return calendar_name_get(p_params, p_attribute_get, FALSE);
	/* End user code here */

}

/* Please update your array size following your setting change by asigning under variable */
/* For season_profile_active */
const uint16_t r_dlms_ic20_obj00_att03_array_length = SEASON_PROFILE_ELEMENT_MAX;
/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att03_get
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 03
*                 Attribute name    : season_profile_active
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class20_season_profile_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att03_get(distributor_params_t * p_params, class20_season_profile_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic20_obj00_att03_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic20_obj00_att03_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is array of {season profile}
	 class18_image_to_activate_info_t {
	    VariantString season_profile_name;
	    date_time_t season_start;
	    VariantString week_profile_name;
	}
	 class20_season_profile_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	       uint8_t* p_active;
	       uint16_t alloc_size;
	 }
	 p_content: this is pointer of variable class18_image_to_activate_info_t[]
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
	//uint8_t season_profile_name_content_element00_link[] = "season name 0";
	//date_time_t season_start_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//uint8_t week_profile_name_content_element00_link[] = "week name 0";


	/* Element 01 */
	//uint8_t season_profile_name_content_element01_link[] = "season name 1";
	//date_time_t season_start_link_element01 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//uint8_t week_profile_name_content_element01_link[] = "week name 1";


	/* Set length for this array */
	//p_attribute_get->length = r_dlms_ic20_obj00_att03_array_length;

	/* Set value for element at 0 */
	//memcpy(p_attribute_get->p_content[0].season_profile_name.p_content, &season_profile_name_content_element00_link, 13);
	//p_attribute_get->p_content[0].season_profile_name.length = 13;
	//p_attribute_get->p_content[0].season_start = season_start_link_element00;
	//memcpy(p_attribute_get->p_content[0].week_profile_name.p_content, &week_profile_name_content_element00_link, 11);
	//p_attribute_get->p_content[0].week_profile_name.length = 11;

	/* Set value for element at 1 */
	//memcpy(p_attribute_get->p_content[1].season_profile_name.p_content, &season_profile_name_content_element01_link, 13);
	//p_attribute_get->p_content[1].season_profile_name.length = 13;
	//p_attribute_get->p_content[1].season_start = season_start_link_element01;
	//memcpy(p_attribute_get->p_content[1].week_profile_name.p_content, &week_profile_name_content_element01_link, 11);
	//p_attribute_get->p_content[1].week_profile_name.length = 11;



	/* Start user code here */
	return season_profile_array_get(p_params, p_attribute_get, FALSE);
	/* End user code here */

}

/* Please update your array size following your setting change by asigning under variable */
/* For week_profile_table_active */
const uint16_t r_dlms_ic20_obj00_att04_array_length = WEEK_PROFILE_ELEMENT_MAX;
/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att04_get
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 04
*                 Attribute name    : week_profile_table_active
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class20_week_profile_table_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att04_get(distributor_params_t * p_params, class20_week_profile_table_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic20_obj00_att04_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic20_obj00_att04_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is array of {week profile}
	 class20_week_profile_table_t {
	    VariantString week_profile_name;
	    uint8_t Monday;
	    uint8_t Tuesday;
	    uint8_t Wednesday;
	    uint8_t Thursday;
	    uint8_t Friday;
	    uint8_t Saturday;
	    uint8_t Sunday;
	}
	 
	 {
	       uint8_t* p_content;
	       uint16_t length;
	       uint8_t* p_active;
	       uint16_t alloc_size;
	 }
	 p_content: this is pointer of variable class20_week_profile_table_t[]
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
	/* Assign link data */

	/* Element 00 */
	//uint8_t week_profile_name_content_element00_link[] = "week profile 1";


	/* Element 01 */
	//uint8_t week_profile_name_content_element01_link[] = "week profile 2";
	//class20_week_profile_table_t Content_array_data_link[] = { 
       	/* 0 *///{ { p_attribute_get->p_content[0].week_profile_name.p_content, 14, 14 }, 0, 0, 0, 0, 0, 0, 0 }, 
       	/* 1 *///{ { p_attribute_get->p_content[1].week_profile_name.p_content, 14, 14 }, 0, 0, 0, 0, 0, 0, 0 } };

	/* Set length of array */
	/* !!! If change content of Content_array_data_link, please update r_dlms_ic20_obj00_att04_array_length */
	//p_attribute_get->length = r_dlms_ic20_obj00_att04_array_length;
	/* Set value */
	//memcpy(p_attribute_get->p_content, &Content_array_data_link, r_dlms_ic20_obj00_att04_array_length*sizeof(class20_week_profile_table_t));

	//memcpy(p_attribute_get->p_content[0].week_profile_name.p_content, &week_profile_name_content_element00_link, 14);
	//p_attribute_get->p_content[0].week_profile_name.length = 14;

	//memcpy(p_attribute_get->p_content[1].week_profile_name.p_content, &week_profile_name_content_element01_link, 14);
	//p_attribute_get->p_content[1].week_profile_name.length = 14;



	/* Start user code here */
	return week_profile_array_get(p_params, p_attribute_get, FALSE);
	/* End user code here */

	/* Return result of this, please check again result value */
}

/* Please update your array size following your setting change by asigning under variable */
/* For day profile */
const uint16_t r_dlms_ic20_obj00_att05_day_profile_array_length = DAY_PROFILE_ELEMENT_MAX;
/* For day schedule maximum length */
const uint16_t r_dlms_ic20_obj00_att05_day_schedule_maximum_array_length = DAY_ACTION_ELEMENT_MAX;
/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att05_get
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 05
*                 Attribute name    : day_profile_table_active
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class20_day_profile_table_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att05_get(distributor_params_t * p_params, class20_day_profile_table_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic20_obj00_att05_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic20_obj00_att05_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	typedef struct tag_class20_day_profile_action_t
	{
	   time_t		start_time;
	   uint8_t		script_logical_name[6];	
	   uint16_t	script_selector;			
	} class20_day_profile_action_t;
	class20_day_profile_action_array_t	
	{
	   element_type	*p_content;		
	   uint16_t		length;			
	   uint8_t		*p_active;	
	   uint16_t		alloc_size;		
	};
	
	class20_day_profile_table_t
	{
	   uint8_t day_id;
	   class20_day_profile_action_array_t day_schedule;
	};
	
	class20_day_profile_table__array_t	
	{						
	    element_type	*p_content;		
	    uint16_t		length;			
	    uint8_t			*p_active;		
	    uint16_t		alloc_size;		
	};
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

	/* Day profile 0 linking data */
	/* Day ID */
	//uint8_t day_id_link_element00 = 0;
	/* Element of day schedule */
	/* Day profile action 00 */
	//time_t start_time_content_element00_of_day_schedule00_link = { 0, 0, 0, 0};
	//uint8_t script_logical_name_content_element00_of_day_schedule00_link[] = {0, 0, 10, 0, 100, 255};
	//uint16_t script_selector_content_element00_of_day_schedule00_link = 0;


	/* Set length for a cripts array and actions arrays */
	//p_attribute_get->length = r_dlms_ic20_obj00_att05_day_profile_array_length;

	/* Set value for a day profile action 00 */
	/* Set length */
	/* If having any change length of action, please consider to change the r_dlms_ic20_obj00_att05_day_schedule_maximum_array_length */
	/* And make sure that it is assigned the maximum length of all actions of all scripts */
	//p_attribute_get->p_content[0].day_schedule.length = 1;
	/* Set value */
	/* For day id */
	//p_attribute_get->p_content[0].day_id = day_id_link_element00;
	/* For action */
	/* Assign values to get data of action 00 */
	//p_attribute_get->p_content[0].day_schedule.p_content[0].start_time = start_time_content_element00_of_day_schedule00_link;
	//memcpy(&p_attribute_get->p_content[0].day_schedule.p_content[0].script_logical_name, &script_logical_name_content_element00_of_day_schedule00_link, 6);
	//p_attribute_get->p_content[0].day_schedule.p_content[0].script_selector = script_selector_content_element00_of_day_schedule00_link;


	/* Start user code here */
	return day_profile_array_get(p_params, p_attribute_get, FALSE);
	/* End user code here */

}

/* Please update your array size following your setting change by asigning under variable */
/* For calendar_name_passive */
const uint16_t r_dlms_ic20_obj00_att06_calendar_name_passive_string_length = NAME_LENGTH_MAX;
/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att06_get
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 06
*                 Attribute name    : calendar_name_passive
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 OctetString * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att06_get(distributor_params_t * p_params, OctetString * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	OctetString
	{
	    uint8_t   *p_content;
	    uint16_t   length;
	    uint16_t   alloc_size;
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
	/* Assign data link here */
	//uint8_t link_data_string[] =  "passive_name";
	/* Set length for string */
	/* !!! If change content of link_data_string, please update r_dlms_ic20_obj00_att06_calendar_name_passive_string_length */
	//p_attribute_get->length = r_dlms_ic20_obj00_att06_calendar_name_passive_string_length;
	/* Set value for string */
	//memcpy(p_attribute_get->p_content, &link_data_string, r_dlms_ic20_obj00_att06_calendar_name_passive_string_length);

	/* Start user code here */
	return calendar_name_get(p_params, p_attribute_get, TRUE);
	/* End user code here */

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att06_set
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 06
*                 Attribute name    : calendar_name_passive
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 OctetString * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att06_set(distributor_params_t * p_params, OctetString * p_attribute_set)
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
	OctetString
	{
	    uint8_t   *p_content;
	    uint16_t   length;
	    uint16_t   alloc_size;
	}
	*********************************************/


	
	/* Start user code here */
	r_act_cal_name_t calendar_name_set;

	/* Check length of name from client */
	if(p_attribute_set->length > NAME_LENGTH_MAX)
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* Pass length of name from client */
	calendar_name_set.len = (uint8_t)p_attribute_set->length;
	memcpy(calendar_name_set.value, p_attribute_set->p_content, p_attribute_set->length);
	/* Write calendar name to storage */
	if(R_ACT_CAL_Backup_CalendarName_Passive(&calendar_name_set) == TRUE)
	{
		R_DLMS_Cumulative_PC();
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/* Please update your array size following your setting change by asigning under variable */
/* For season_profile_passive */
const uint16_t r_dlms_ic20_obj00_att07_array_length = SEASON_PROFILE_ELEMENT_MAX;
/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att07_get
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 07
*                 Attribute name    : season_profile_passive
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class20_season_profile_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att07_get(distributor_params_t * p_params, class20_season_profile_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic20_obj00_att07_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic20_obj00_att07_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is array of {season profile}
	 class18_image_to_activate_info_t {
	    VariantString season_profile_name;
	    date_time_t season_start;
	    VariantString week_profile_name;
	}
	 class20_season_profile_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	       uint8_t* p_active;
	       uint16_t alloc_size;
	 }
	 p_content: this is pointer of variable class18_image_to_activate_info_t[]
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
	//uint8_t season_profile_name_content_element00_link[] = "season passive 1";
	//date_time_t season_start_link_element00 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//uint8_t week_profile_name_content_element00_link[] = "week passive 1";


	/* Element 01 */
	//uint8_t season_profile_name_content_element01_link[] = "season passive 2";
	//date_time_t season_start_link_element01 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//uint8_t week_profile_name_content_element01_link[] = "week passive 2";


	/* Set length for this array */
	//p_attribute_get->length = r_dlms_ic20_obj00_att07_array_length;

	/* Set value for element at 0 */
	//memcpy(p_attribute_get->p_content[0].season_profile_name.p_content, &season_profile_name_content_element00_link, 16);
	//p_attribute_get->p_content[0].season_profile_name.length = 16;
	//p_attribute_get->p_content[0].season_start = season_start_link_element00;
	//memcpy(p_attribute_get->p_content[0].week_profile_name.p_content, &week_profile_name_content_element00_link, 14);
	//p_attribute_get->p_content[0].week_profile_name.length = 14;

	/* Set value for element at 1 */
	//memcpy(p_attribute_get->p_content[1].season_profile_name.p_content, &season_profile_name_content_element01_link, 16);
	//p_attribute_get->p_content[1].season_profile_name.length = 16;
	//p_attribute_get->p_content[1].season_start = season_start_link_element01;
	//memcpy(p_attribute_get->p_content[1].week_profile_name.p_content, &week_profile_name_content_element01_link, 14);
	//p_attribute_get->p_content[1].week_profile_name.length = 14;



	/* Start user code here */
	return season_profile_array_get(p_params, p_attribute_get, TRUE);
	/* End user code here */

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att07_set
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 07
*                 Attribute name    : season_profile_passive
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class20_season_profile_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att07_set(distributor_params_t * p_params, class20_season_profile_array_t * p_attribute_set)
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
	 This is array of {season profile}
	 class18_image_to_activate_info_t {
	    VariantString season_profile_name;
	    date_time_t season_start;
	    VariantString week_profile_name;
	}
	 class20_season_profile_array_t
	 {
	       uint8_t* p_content;
	       uint16_t length;
	       uint8_t* p_active;
	       uint16_t alloc_size;
	 }
	 p_content: this is pointer of variable class18_image_to_activate_info_t[]
	*********************************************/


	
	/* Start user code here */
	r_act_cal_season_profile_t season_profile;
	uint16_t i;// index in array 

    rtc_counter_value_t         start_time; // Season start time for validation

	/* Check number of season profile from client */
	if(p_attribute_set->length > SEASON_PROFILE_ELEMENT_MAX)
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{

	}

    /* Currently, Season profile only support wildcard for year */
	for(i = 0; i < p_attribute_set->length; i++)
	{
		R_DLMS_RTC_Convert_DateTime2RTC2(
			&start_time,
			&p_attribute_set->p_content[i].season_start);

        if (
            start_time.sec   == 0xFF ||
            start_time.min   == 0xFF ||
            start_time.hour  == 0xFF ||
            start_time.day   == 0xFF ||
            start_time.month == 0xFF
        )
        {
            return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
        }
    }

	/* Pass length array */
	season_profile.num = (uint8_t)p_attribute_set->length;
	/* Loop all season profiles to pass data to set variable */
	for(i = 0; i < p_attribute_set->length; i++)
	{
		/* Check length of season name */
		if(p_attribute_set->p_content[i].season_profile_name.length > NAME_LENGTH_MAX)
		{
			return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
		}
		else
		{
			/* code */
		}
		
		/* Pass data for season profile name */
		season_profile.entry[i].name.len = p_attribute_set->p_content[i].season_profile_name.length;
		memcpy(
			season_profile.entry[i].name.value,
			p_attribute_set->p_content[i].season_profile_name.p_content,
			p_attribute_set->p_content[i].season_profile_name.length);

		/* Convert and pass data for date time from rtc format to dlms format */
		R_DLMS_RTC_Convert_DateTime2RTC2(
			&season_profile.entry[i].start_time,
			&p_attribute_set->p_content[i].season_start);

		/* Check length of week name */
		if(p_attribute_set->p_content[i].week_profile_name.length > NAME_LENGTH_MAX)
		{
			return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
		}
		else
		{
			/* code */
		}

		/* Pass week profile name */
		season_profile.entry[i].week.len = (uint8_t)p_attribute_set->p_content[i].week_profile_name.length;
		memcpy(
			season_profile.entry[i].week.value,
			p_attribute_set->p_content[i].week_profile_name.p_content,
			p_attribute_set->p_content[i].week_profile_name.length);
	}

	/* Write data to storage */
	if(R_ACT_CAL_Backup_SeasonProfile_Passive(&season_profile) == TRUE)
	{
		R_DLMS_Cumulative_PC();
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/* Please update your array size following your setting change by asigning under variable */
/* For week_profile_table_passive */
const uint16_t r_dlms_ic20_obj00_att08_array_length = WEEK_PROFILE_ELEMENT_MAX;
/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att08_get
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 08
*                 Attribute name    : week_profile_table_passive
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class20_week_profile_table_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att08_get(distributor_params_t * p_params, class20_week_profile_table_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic20_obj00_att08_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic20_obj00_att08_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is array of {week profile}
	 class20_week_profile_table_t {
	    VariantString week_profile_name;
	    uint8_t Monday;
	    uint8_t Tuesday;
	    uint8_t Wednesday;
	    uint8_t Thursday;
	    uint8_t Friday;
	    uint8_t Saturday;
	    uint8_t Sunday;
	}
	 
	 {
	       uint8_t* p_content;
	       uint16_t length;
	       uint8_t* p_active;
	       uint16_t alloc_size;
	 }
	 p_content: this is pointer of variable class20_week_profile_table_t[]
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
	/* Assign link data */

	/* Element 00 */
	//uint8_t week_profile_name_content_element00_link[] = "passive week 1";
	//class20_week_profile_table_t Content_array_data_link[] = { 
       	/* 0 *///{ { p_attribute_get->p_content[0].week_profile_name.p_content, 14, 14 }, 0, 0, 0, 0, 0, 0, 0 } };

	/* Set length of array */
	/* !!! If change content of Content_array_data_link, please update r_dlms_ic20_obj00_att08_array_length */
	//p_attribute_get->length = r_dlms_ic20_obj00_att08_array_length;
	/* Set value */
	//memcpy(p_attribute_get->p_content, &Content_array_data_link, r_dlms_ic20_obj00_att08_array_length*sizeof(class20_week_profile_table_t));

	//memcpy(p_attribute_get->p_content[0].week_profile_name.p_content, &week_profile_name_content_element00_link, 14);
	//p_attribute_get->p_content[0].week_profile_name.length = 14;



	/* Start user code here */
	return week_profile_array_get(p_params, p_attribute_get, TRUE);
	/* End user code here */

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att08_set
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 08
*                 Attribute name    : week_profile_table_passive
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class20_week_profile_table_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att08_set(distributor_params_t * p_params, class20_week_profile_table_array_t * p_attribute_set)
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
	 This is array of {week profile}
	 class20_week_profile_table_t {
	    VariantString week_profile_name;
	    uint8_t Monday;
	    uint8_t Tuesday;
	    uint8_t Wednesday;
	    uint8_t Thursday;
	    uint8_t Friday;
	    uint8_t Saturday;
	    uint8_t Sunday;
	}
	 
	 {
	       uint8_t* p_content;
	       uint16_t length;
	       uint8_t* p_active;
	       uint16_t alloc_size;
	 }
	 p_content: this is pointer of variable class20_week_profile_table_t[]
	*********************************************/


	
	/* Start user code here */
	uint16_t i;// index in array 
	r_act_cal_week_profile_t week_profile;

	/* Check number profile from client */
	if(p_attribute_set->length > WEEK_PROFILE_ELEMENT_MAX)
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	else
	{

	}
	/* Pass length of week profile */
	week_profile.num = (uint8_t)p_attribute_set->length;
	/* Loop all week profiles to get data */
	for(i = 0; i < p_attribute_set->length; i++)
	{
		/* Check length of week name */
		if(p_attribute_set->p_content[i].week_profile_name.length > NAME_LENGTH_MAX)
		{
			return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
		}
		/* Pass week profile name */
		week_profile.entry[i].name.len = (uint8_t)p_attribute_set->p_content[i].week_profile_name.length;
		memcpy(
			week_profile.entry[i].name.value,
			p_attribute_set->p_content[i].week_profile_name.p_content,
			p_attribute_set->p_content[i].week_profile_name.length);
		
		/* Pass week datas all */
		memcpy(
			week_profile.entry[i].data,
			p_attribute_set->p_content[i].data,
			7);//7 is number days in weeks, refer to class20, attribute 04 definition of blue book.
	}

	/* Write week profile to storage */
	if(R_ACT_CAL_Backup_WeekProfile_Passive(&week_profile) == TRUE)
	{
		R_DLMS_Cumulative_PC();
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/* Please update your array size following your setting change by asigning under variable */
/* For day profile */
const uint16_t r_dlms_ic20_obj00_att09_day_profile_array_length = DAY_PROFILE_ELEMENT_MAX;
/* For day schedule maximum length */
const uint16_t r_dlms_ic20_obj00_att09_day_schedule_maximum_array_length = DAY_ACTION_ELEMENT_MAX;
/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att09_get
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 09
*                 Attribute name    : day_profile_table_passive
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class20_day_profile_table_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att09_get(distributor_params_t * p_params, class20_day_profile_table_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic20_obj00_att09_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic20_obj00_att09_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	typedef struct tag_class20_day_profile_action_t
	{
	   time_t		start_time;
	   uint8_t		script_logical_name[6];	
	   uint16_t	script_selector;			
	} class20_day_profile_action_t;
	class20_day_profile_action_array_t	
	{
	   element_type	*p_content;		
	   uint16_t		length;			
	   uint8_t		*p_active;	
	   uint16_t		alloc_size;		
	};
	
	class20_day_profile_table_t
	{
	   uint8_t day_id;
	   class20_day_profile_action_array_t day_schedule;
	};
	
	class20_day_profile_table__array_t	
	{						
	    element_type	*p_content;		
	    uint16_t		length;			
	    uint8_t			*p_active;		
	    uint16_t		alloc_size;		
	};
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

	/* Day profile 0 linking data */
	/* Day ID */
	//uint8_t day_id_link_element00 = 0;
	/* Element of day schedule */
	/* Day profile action 00 */
	//time_t start_time_content_element00_of_day_schedule00_link = { 0, 0, 0, 0};
	//uint8_t script_logical_name_content_element00_of_day_schedule00_link[] = {0, 0, 10, 0, 100, 255};
	//uint16_t script_selector_content_element00_of_day_schedule00_link = 0;
	/* Day profile action 01 */
	//time_t start_time_content_element01_of_day_schedule00_link = { 0, 0, 0, 0};
	//uint8_t script_logical_name_content_element01_of_day_schedule00_link[] = {0, 0, 10, 0, 100, 255};
	//uint16_t script_selector_content_element01_of_day_schedule00_link = 0;


	/* Day profile 1 linking data */
	/* Day ID */
	//uint8_t day_id_link_element01 = 0;
	/* Element of day schedule */
	/* Day profile action 00 */
	//time_t start_time_content_element00_of_day_schedule01_link = { 0, 0, 0, 0};
	//uint8_t script_logical_name_content_element00_of_day_schedule01_link[] = {0, 0, 10, 0, 100, 255};
	//uint16_t script_selector_content_element00_of_day_schedule01_link = 0;
	/* Day profile action 01 */
	//time_t start_time_content_element01_of_day_schedule01_link = { 0, 0, 0, 0};
	//uint8_t script_logical_name_content_element01_of_day_schedule01_link[] = {0, 0, 10, 0, 100, 255};
	//uint16_t script_selector_content_element01_of_day_schedule01_link = 0;


	/* Set length for a cripts array and actions arrays */
	//p_attribute_get->length = r_dlms_ic20_obj00_att09_day_profile_array_length;

	/* Set value for a day profile action 00 */
	/* Set length */
	/* If having any change length of action, please consider to change the r_dlms_ic20_obj00_att09_day_schedule_maximum_array_length */
	/* And make sure that it is assigned the maximum length of all actions of all scripts */
	//p_attribute_get->p_content[0].day_schedule.length = 2;
	/* Set value */
	/* For day id */
	//p_attribute_get->p_content[0].day_id = day_id_link_element00;
	/* For action */
	/* Assign values to get data of action 00 */
	//p_attribute_get->p_content[0].day_schedule.p_content[0].start_time = start_time_content_element00_of_day_schedule00_link;
	//memcpy(&p_attribute_get->p_content[0].day_schedule.p_content[0].script_logical_name, &script_logical_name_content_element00_of_day_schedule00_link, 6);
	//p_attribute_get->p_content[0].day_schedule.p_content[0].script_selector = script_selector_content_element00_of_day_schedule00_link;
	/* Assign values to get data of action 01 */
	//p_attribute_get->p_content[0].day_schedule.p_content[1].start_time = start_time_content_element01_of_day_schedule00_link;
	//memcpy(&p_attribute_get->p_content[0].day_schedule.p_content[1].script_logical_name, &script_logical_name_content_element01_of_day_schedule00_link, 6);
	//p_attribute_get->p_content[0].day_schedule.p_content[1].script_selector = script_selector_content_element01_of_day_schedule00_link;

	/* Set value for a day profile action 01 */
	/* Set length */
	/* If having any change length of action, please consider to change the r_dlms_ic20_obj00_att09_day_schedule_maximum_array_length */
	/* And make sure that it is assigned the maximum length of all actions of all scripts */
	//p_attribute_get->p_content[1].day_schedule.length = 2;
	/* Set value */
	/* For day id */
	//p_attribute_get->p_content[1].day_id = day_id_link_element01;
	/* For action */
	/* Assign values to get data of action 00 */
	//p_attribute_get->p_content[1].day_schedule.p_content[0].start_time = start_time_content_element00_of_day_schedule01_link;
	//memcpy(&p_attribute_get->p_content[1].day_schedule.p_content[0].script_logical_name, &script_logical_name_content_element00_of_day_schedule01_link, 6);
	//p_attribute_get->p_content[1].day_schedule.p_content[0].script_selector = script_selector_content_element00_of_day_schedule01_link;
	/* Assign values to get data of action 01 */
	//p_attribute_get->p_content[1].day_schedule.p_content[1].start_time = start_time_content_element01_of_day_schedule01_link;
	//memcpy(&p_attribute_get->p_content[1].day_schedule.p_content[1].script_logical_name, &script_logical_name_content_element01_of_day_schedule01_link, 6);
	//p_attribute_get->p_content[1].day_schedule.p_content[1].script_selector = script_selector_content_element01_of_day_schedule01_link;


	/* Start user code here */
	return day_profile_array_get(p_params, p_attribute_get, TRUE);
	/* End user code here */

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att09_set
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 09
*                 Attribute name    : day_profile_table_passive
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class20_day_profile_table_array_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att09_set(distributor_params_t * p_params, class20_day_profile_table_array_t * p_attribute_set)
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
	typedef struct tag_class20_day_profile_action_t
	{
	   time_t		start_time;
	   uint8_t		script_logical_name[6];	
	   uint16_t	script_selector;			
	} class20_day_profile_action_t;
	class20_day_profile_action_array_t	
	{
	   element_type	*p_content;		
	   uint16_t		length;			
	   uint8_t		*p_active;	
	   uint16_t		alloc_size;		
	};
	
	class20_day_profile_table_t
	{
	   uint8_t day_id;
	   class20_day_profile_action_array_t day_schedule;
	};
	
	class20_day_profile_table__array_t	
	{						
	    element_type	*p_content;		
	    uint16_t		length;			
	    uint8_t			*p_active;		
	    uint16_t		alloc_size;		
	};
	*********************************************/


	/****************************************************************************************************************************************************************
	* typedef enum																																					*
	* {																																								*
	* 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	*  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	* } DataAccessResult_Value;																																		*
	* Please do these 2 code lines to report that your SET status to client for 2 cases:																			*
	* 1. SET execute successfully:																																	*
	* 	OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE); (status :VAL_DATA_ACCESS_RESULT_SUCCESS)									*
	* 	OBIS_DISTRIBUTION_SUCCESS(p_params->result);																												*
	* 2. if have any exception during executing SET																													*
	* 	OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED, FALSE);(status :VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED(example))		*
	* 	OBIS_DISTRIBUTION_FAILED(p_params->result);																													*
	* 	*Note: in this case: please refer DataAccessResult_Value enum to put your case of exception corresponding with case by case.								*
	*****************************************************************************************************************************************************************/
	/* Start user code here */
	uint16_t i, j;// index in array 
	r_act_cal_day_profile_t day_profile;
	uint8_t action_script_logical_name[] = { 0,   0,   10,   0,  100, 255};

	/* Check number day profile */
	if(p_attribute_set->length > DAY_PROFILE_ELEMENT_MAX)
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* Pass number profile */
	day_profile.num = (uint8_t)p_attribute_set->length;
	/* Loop all day profiles to pass data */
	for(i = 0; i < p_attribute_set->length; i++)
	{
		/* Pass Day ID */
		day_profile.entry[i].dayID = p_attribute_set->p_content[i].day_id;

		/* Check number of action */
		if(p_attribute_set->p_content[i].day_schedule.length > DAY_ACTION_ELEMENT_MAX)
		{
			return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
		}
		else
		{

		}
		/* Pass number of action */
		day_profile.entry[i].numberOfAction = (uint8_t)p_attribute_set->p_content[i].day_schedule.length;
		/* loop all schedule at i day profile  */
		for(j = 0; j < p_attribute_set->p_content[i].day_schedule.length; j++)
		{
			/* Pass start time data */
			day_profile.entry[i].action[j].hour = p_attribute_set->p_content[i].day_schedule.p_content[j].start_time.hour;
			day_profile.entry[i].action[j].min = p_attribute_set->p_content[i].day_schedule.p_content[j].start_time.minute;
			/* This meter no save for second and hundredseconds */

			/* Pass script logical name */
			/* This field does not allowed for writing in this meter configuration */

			/* Pass script selector */
			day_profile.entry[i].action[j].scriptID = p_attribute_set->p_content[i].day_schedule.p_content[j].script_selector;
		}		
	}
	/* Write day profile from client setting to storage */
	if(R_ACT_CAL_Backup_DayProfile_Passive(&day_profile) == TRUE)
	{
		R_DLMS_Cumulative_PC();
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
* Function Name : R_DLMS_USER_ic20_obj00_att10_get
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 10
*                 Attribute name    : activate_passive_calendar_time
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 date_time_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att10_get(distributor_params_t * p_params, date_time_t * p_attribute_get)
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
	uint8_t time_schedule[3];
	uint8_t date_schedule[4];
	uint16_t year;
	uint16_t length_array;


	/* Get length of execution time of billing */
	length_array = R_SCHEDULER_ExecutionTimeArrayLengthGet(5);//5 is scheduler id of activate calendar

	/* 
	 * If length of execution time of schedule is 0 or more than SCHEDULE_EXE_TIME_MAX_SUPPORT_3
	 * Return not specific value
	 */
	if(length_array <= 0 || length_array > SCHEDULE_EXE_TIME_MAX_SUPPORT_5)
	{
		date_time_t billing_datetime = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		                     0xFF, 0xFF, 0xFF, 0x80, 0x00, 0xFF};
		memcpy(p_attribute_get, &billing_datetime, 12);
		return VAL_DATA_ACCESS_RESULT_SUCCESS;
	}

	R_SCHEDULER_ExecutionTimeGet(time_schedule, SCHEDULER_ID_ACTIVITY_CAL_ACT, 0);//5 is scheduler id of activate calendar
	R_SCHEDULER_ExecutionDateGet(date_schedule, SCHEDULER_ID_ACTIVITY_CAL_ACT, 0);//5 is scheduler id of activate calendar
	
	/* Convert data date and time of schedule to data_time of passive active calendar */
	if (date_schedule[0] == 0xFF)
	{
		p_attribute_get->year_high = 0xFF;
		p_attribute_get->year_low = 0xFF;
	}
	else
	{
		year = 2000 + (uint16_t)date_schedule[0];
		p_attribute_get->year_high = (uint8_t)(year >> 8);
		p_attribute_get->year_low = (uint8_t)year;
	}
     
	p_attribute_get->month = date_schedule[1];         
	p_attribute_get->day_of_week = date_schedule[2];   
	p_attribute_get->day_of_month = date_schedule[3];  
	p_attribute_get->hour = time_schedule[0];          
	p_attribute_get->minute = time_schedule[1];        
	p_attribute_get->second = time_schedule[2];

    R_DLMS_RTC_Convert_DLMSWeekToDriverWeek(
        &p_attribute_get->day_of_week, 
        &p_attribute_get->day_of_week
    );

	/*
	 * According to DLMS bluebook
	 * A definition with "not specified" notation in all fields of the attribute will deactivate this automatism.
	 * Partial "not specified" notation in just some fields of date and time are not allowed.
	 */
	if ((date_schedule[0] & date_schedule[1] & date_schedule[2] & date_schedule[3] &
		 time_schedule[0] & time_schedule[1] & time_schedule[2]) == 0xFF)
	{
		p_attribute_get->hundredths = 0xFF;//As mention of bluebook, class22, attirbute 04  
		p_attribute_get->deviation_high = 0x80;//Not specified
		p_attribute_get->deviation_low = 0x00;//Not specified
		p_attribute_get->clock_status = 0xFF;//Not specified
	}
	else
	{
		p_attribute_get->hundredths = 0;//As mention of bluebook, class22, attirbute 04  
		p_attribute_get->deviation_high = (int8_t)(g_time_zone>>8);
    	p_attribute_get->deviation_low = (int8_t)g_time_zone;
		p_attribute_get->clock_status = g_clock_status;//Not specified
	}

	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic20_obj00_att10_set
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Attribute order   : 10
*                 Attribute name    : activate_passive_calendar_time
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 date_time_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att10_set(distributor_params_t * p_params, date_time_t * p_attribute_set)
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


	
	/* Start user code here */
    rtc_counter_value_t rtc_set_value;
    uint8_t write_result;

	uint16_t year;
	uint8_t time_schedule[4];
	uint8_t date_schedule[4];

	/* Convert DLMS data time to schedule date time */
	/* Date */
	year = (uint16_t)(p_attribute_set->year_high << 8) + p_attribute_set->year_low;
	if (year == 0xFFFF)
	{
		rtc_set_value.year = 0xFF;
	}
	else
	{
		rtc_set_value.year = year % 100;
	}

    if (p_attribute_set->day_of_week == 0xFF)
    {
        rtc_set_value.week = 0xFF;
    }
    else
    {
        R_DLMS_RTC_Convert_DLMSWeekToDriverWeek(&rtc_set_value.week, &p_attribute_set->day_of_week);
    }

	rtc_set_value.month = p_attribute_set->month;
	rtc_set_value.day = p_attribute_set->day_of_month;
	rtc_set_value.hour = p_attribute_set->hour;
	rtc_set_value.min = p_attribute_set->minute;
	rtc_set_value.sec = p_attribute_set->second;

    write_result = R_ACT_CAL_Set_ActivateTime(&rtc_set_value);

	if (write_result)
	{
		R_SCHEDULER_BackupByID(SCHEDULER_ID_ACTIVITY_CAL_ACT);//5 is scheduler id of activate calendar
		R_DLMS_Cumulative_PC();
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
* Function Name : R_DLMS_USER_ic20_obj00_meth01_action
* Description   : Object name       : Activity calendar
*                 Object index      : 00
*                 Class             : 20
*                 Method order      : 01
*                 Method name       : activate_passive_calendar
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* This method copies all attributes called …_passive to the corresponding attributes called …_active.
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
	if(R_ACT_CAL_RequestCopyPassiveToActive() == TRUE)
	{
		R_DLMS_Cumulative_PC();
	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


