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
* File Name    : r_dlms_usercode_class08.c
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
#include "r_dlms_usercode_class08.h"

/* User application */
#include "r_dlms_date_time.h"
#include "r_dlms_app.h"
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
* Object name:      RTC Clock
* Object number:    00
* Object obis code: 0.0.1.0.0.255
***********************************************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_USER_ic08_obj00_att02_get
* Description   : Object name       : RTC Clock
*                 Object index      : 00
*                 Class             : 08
*                 Attribute order   : 02
*                 Attribute name    : time
*                 Association access: {0, Public Client}; {1, Meter Reader}; {2, Utility Setting}; {3, Push}; {4, Firmware upgrade }; ; 
*                 Group object		: Instantaneous, Programmable, Push, Block load, Daily load, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 date_time_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic08_obj00_att02_get(distributor_params_t * p_params, date_time_t * p_attribute_get)
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
	if(R_DLMS_RTC_Get_DateTime((uint8_t *)p_attribute_get) == RLT_SUCCESS)
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
* Function Name : R_DLMS_USER_ic08_obj00_att02_set
* Description   : Object name       : RTC Clock
*                 Object index      : 00
*                 Class             : 08
*                 Attribute order   : 02
*                 Attribute name    : time
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable, Push, Block load, Daily load, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 date_time_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic08_obj00_att02_set(distributor_params_t * p_params, date_time_t * p_attribute_set)
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
	if (R_DLMS_IsValidDateTime((date_time_t *)(void *)p_params->service_params.malloc.p_content) == RLT_SUCCESS)
	{
		if (R_DLMS_RTC_Set_DateTime((date_time_t *)p_attribute_set) == RLT_SUCCESS)
	    {
			R_DLMS_Cumulative_PC();
			g_event_flag.bits.set_rtc = TRUE;
	    }
	    else
	    {
	        return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	    }
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
* Function Name : R_DLMS_USER_ic08_obj00_att03_get
* Description   : Object name       : RTC Clock
*                 Object index      : 00
*                 Class             : 08
*                 Attribute order   : 03
*                 Attribute name    : time_zone
*                 Association access: {0, Public Client}; {1, Meter Reader}; {2, Utility Setting}; {3, Push}; {4, Firmware upgrade }; ; 
*                 Group object		: Instantaneous, Programmable, Push, Block load, Daily load, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 int16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic08_obj00_att03_get(distributor_params_t * p_params, int16_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:int16_t(long)
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
	//int16_t link_data = 0;
	/* Set value */
	//*((int16_t *)p_attribute_get) = link_data;

	/* Start user code here */
	*((int16_t *)p_attribute_get) = g_time_zone;
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic08_obj00_att03_set
* Description   : Object name       : RTC Clock
*                 Object index      : 00
*                 Class             : 08
*                 Attribute order   : 03
*                 Attribute name    : time_zone
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Instantaneous, Programmable, Push, Block load, Daily load, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 int16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic08_obj00_att03_set(distributor_params_t * p_params, int16_t * p_attribute_set)
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
	Data type:int16_t(long)
	*********************************************/


	
	/* Start user code here */
	if (R_DLMS_IsValidTimeZone(*p_attribute_set) == R_DATE_TIME_VALID)
	{
		if (R_DLMS_RTC_Change_TimeZone(*p_attribute_set) == RLT_SUCCESS)
		{
			/* Report event */
			R_DLMS_Cumulative_PC();
			g_event_flag.bits.set_rtc = TRUE;
		}
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
* Function Name : R_DLMS_USER_ic08_obj00_att04_get
* Description   : Object name       : RTC Clock
*                 Object index      : 00
*                 Class             : 08
*                 Attribute order   : 04
*                 Attribute name    : status
*                 Association access: {0, Public Client}; {1, Meter Reader}; {2, Utility Setting}; {3, Push}; {4, Firmware upgrade }; ; 
*                 Group object		: Instantaneous, Programmable, Push, Block load, Daily load, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic08_obj00_att04_get(distributor_params_t * p_params, uint8_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint8_t(unsigned)
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
	//uint8_t link_data = 0;
	/* Set value */
	//*((uint8_t *)p_attribute_get) = link_data;

	/* Start user code here */
	*((uint8_t *)p_attribute_get) = g_clock_status;
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic08_obj00_att05_get
* Description   : Object name       : RTC Clock
*                 Object index      : 00
*                 Class             : 08
*                 Attribute order   : 05
*                 Attribute name    : daylight_savings_begin
*                 Association access: {0, Public Client}; {1, Meter Reader}; {2, Utility Setting}; {3, Push}; {4, Firmware upgrade }; ; 
*                 Group object		: Instantaneous, Programmable, Push, Block load, Daily load, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 date_time_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic08_obj00_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get)
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
	date_time_t link_data = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0xFF};
	/* Set value */
	*((date_time_t *)p_attribute_get) = link_data;

	/* Start user code here */
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic08_obj00_att06_get
* Description   : Object name       : RTC Clock
*                 Object index      : 00
*                 Class             : 08
*                 Attribute order   : 06
*                 Attribute name    : daylight_savings_end
*                 Association access: {0, Public Client}; {1, Meter Reader}; {2, Utility Setting}; {3, Push}; {4, Firmware upgrade }; ; 
*                 Group object		: Instantaneous, Programmable, Push, Block load, Daily load, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 date_time_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic08_obj00_att06_get(distributor_params_t * p_params, date_time_t * p_attribute_get)
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
	date_time_t link_data = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0xFF};
	/* Set value */
	*((date_time_t *)p_attribute_get) = link_data;

	/* Start user code here */
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic08_obj00_att07_get
* Description   : Object name       : RTC Clock
*                 Object index      : 00
*                 Class             : 08
*                 Attribute order   : 07
*                 Attribute name    : daylight_savings_deviation
*                 Association access: {0, Public Client}; {1, Meter Reader}; {2, Utility Setting}; {3, Push}; {4, Firmware upgrade }; ; 
*                 Group object		: Instantaneous, Programmable, Push, Block load, Daily load, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 int8_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic08_obj00_att07_get(distributor_params_t * p_params, int8_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:int8_t(integer)
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
	int8_t link_data = 60;
	/* Set value */
	*((int8_t *)p_attribute_get) = link_data;

	/* Start user code here */
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic08_obj00_att08_get
* Description   : Object name       : RTC Clock
*                 Object index      : 00
*                 Class             : 08
*                 Attribute order   : 08
*                 Attribute name    : daylight_savings_enabled
*                 Association access: {0, Public Client}; {1, Meter Reader}; {2, Utility Setting}; {3, Push}; {4, Firmware upgrade }; ; 
*                 Group object		: Instantaneous, Programmable, Push, Block load, Daily load, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic08_obj00_att08_get(distributor_params_t * p_params, uint8_t * p_attribute_get)
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
	uint8_t link_data = FALSE;
	/* Set value */
	*((uint8_t *)p_attribute_get) = link_data;

	/* Start user code here */
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic08_obj00_att09_get
* Description   : Object name       : RTC Clock
*                 Object index      : 00
*                 Class             : 08
*                 Attribute order   : 09
*                 Attribute name    : clock_base
*                 Association access: {0, Public Client}; {1, Meter Reader}; {2, Utility Setting}; {3, Push}; {4, Firmware upgrade }; ; 
*                 Group object		: Instantaneous, Programmable, Push, Block load, Daily load, Event
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 clock_base_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic08_obj00_att09_get(distributor_params_t * p_params, clock_base_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	enum clock_base_t
	{
	      CLASS08_CLOCK_BASE_NOT_DEFINED = 0,
	      CLASS08_CLOCK_BASE_INTERNAL_CRYSTAL = 1,
	      CLASS08_CLOCK_BASE_MAINS_FREQUENCY_50_HZ = 2,
	      CLASS08_CLOCK_BASE_MAINS_FREQUENCY_60_HZ = 3,
	      CLASS08_CLOCK_BASE_GPS = 4,
	      CLASS08_CLOCK_BASE_RADIO_CONTROLLED = 5,
	} ;
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
	clock_base_t link_data = CLASS08_CLOCK_BASE_INTERNAL_CRYSTAL;
	*((clock_base_t *)p_attribute_get) = link_data;
	/* Start user code here */
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



