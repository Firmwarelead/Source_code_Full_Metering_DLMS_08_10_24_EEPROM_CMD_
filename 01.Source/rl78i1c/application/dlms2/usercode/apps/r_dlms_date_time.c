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
* File Name    : r_dlms_datetime.c
* Version      : <Version>
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : 
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 2018-03-20 			New creation
// 2019-07-16 14:13:32 	RESOLVE issue: On class 71 object, relay is triggered just half of time amount set by 
//														Min over/under threshold duration” attribute value

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Data type definition */
#include "typedef.h"

/* Driver */
#include "r_cg_macrodriver.h"   /* CG Macro Driver */
#include "r_cg_rtc.h"           /* CG RTC Driver */

/* Wrapper */
#include "wrp_app_ext.h"

/* Meter application */
#include "event.h"
#include "r_meter_format.h"
#include "r_abnormal_operating.h"

/* DLMS 2.0 Library */
#include "r_dlms_classes.h"

/* DLMS Application */
#include "r_dlms_app.h"
#include "r_dlms_date_time.h"
#include "r_dlms_storage.h"
#include "r_dlms_scheduler.h"
#include "r_dlms_cumulate.h"

#include "r_dlms_factory_config.h"

/* Standard library */
#include <string.h>

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
typedef enum tag_dlms_datetime_struct_pos
{
    DLMS_CLOCK_YEAR_H_POS = 0,
    DLMS_CLOCK_YEAR_L_POS,
    DLMS_CLOCK_MON_POS ,
    DLMS_CLOCK_DAY_POS,
    DLMS_CLOCK_WEEK_POS,
    DLMS_CLOCK_HOUR_POS,
    DLMS_CLOCK_MIN_POS,
    DLMS_CLOCK_SEC_POS,
    DLMS_CLOCK_HUNDREDTH_POS,
    DLMS_CLOCK_DEVIATION_H_POS,
    DLMS_CLOCK_DEVIATION_L_POS,
    DLMS_CLOCK_STATUS_POS,
} dlms_datetime_struct_pos;


/* Common macro */
/// @cond FOO
#define __UINT8_TO_UINT16(high_byte, low_byte)    (high_byte << 8 | low_byte)

/// @endcond

#define DLMS_VALIDATE_ALARM_VALUE(value, rtc_alarm, rtc_enb)		\
	if (value == RTC_NOT_SPECIFIED) \
	{\
		rtc_enb = 0; \
	} \
	else \
	{ \
		rtc_enb = 1; \
		rtc_alarm = WRP_EXT_Dec2Bcd(value); \
	}

#define COMBINE_U16(high_byte, low_byte)        (high_byte << 8 | low_byte)

#define R_DLMS_TIME_MATCHED         (0)
#define R_DLMS_TIME_UNMATCHED       (1)

#define R_SCRIPT_NUMBER             5



/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/


typedef enum tag_date_compare_result_t {
    DATE_MATCHED = 0,
    DATE_NEW_IS_DATE1,
    DATE_NEW_IS_DATE2,
    DATE_UNMATCHED,
    DATE_FORMAT_ERROR,
    DATE_WILDCARD_ERROR
} date_compare_result_t;

typedef struct tag_r_dlms_script_t
{
    uint16_t data;
} r_dlms_script_t;

typedef enum tag_scheduler_id_t
{
    SCH_ID_BILLING = 0,
    SCH_ID_IMAGE,
    SCH_ID_PUSH
} scheduler_id_t;

typedef enum tag_script_id_t
{
    SCRIPT_ID_MD_RESET = 0,
    SCRIPT_ID_IMAGE_ACTIVATION,
    SCRIPT_ID_PUSh
} script_id_t;

typedef struct tag_r_dlms_rtc_sec_counter_t
{
	uint8_t		* enable;
	uint32_t	* value;
	uint8_t		alloc_size;
} r_dlms_rtc_sec_counter_t;

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

date_time_params_t  g_DLMS_RTC_params;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

uint8_t R_DLMS_IsValidDateTime(
	date_time_t *p_date_time
);


R_DLMS_RTC_T g_old_time;
R_DLMS_RTC_T g_new_time;

int16_t g_time_zone;
uint8_t g_clock_status;

const DLMS_STORAGE storage_info_time_zone = {STORAGE_EEPROM_DLMS_TIMEZONE_ADDR, STORAGE_EEPROM_DLMS_TIMEZONE_SIZE};
const DLMS_STORAGE storage_info_clock_status = {STORAGE_EEPROM_DLMS_CLOCK_STATUS_ADDR, STORAGE_EEPROM_DLMS_CLOCK_STATUS_SIZE};
const uint16_t g_dlms_timezone_default 				= R_DLMS_TIME_ZONE_DEFAULT;

/*! The number day of month */
const int nDayOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};     

/* RL78/G13 Day Of Week Driver */
const uint8_t g_DayOfWeek[7] = {7,1,2,3,4,5,6};

/* DLMS Week 
 * range 1…7, 0xFF
 * 1 is Monday
 * 0xFF = not specified
 * 
 * RTC week
 * 
 * 0		1		2		3			4		5		6
 * Sunday, Monday, Tuesday, Wednesd, Thursday, Friday, Saturday
*/
const uint8_t g_DLMS_WEEK_2_RTC_WEEK[8] = {0,1,2,3,4,5,6,0};

uint8_t rtc_tick_flag;

/* 
 * RTC 0.5s interrupts Counter
 *    [0] 		: Limiter over/under threshold period
 *    [1->5] 	: Push period timer
 *    [6] 		: Lock out period (30min = 1800s)
 */
#define DLMS_RTC_SEC_COUNTER_NUMBER		(9)
uint8_t		counter_enable[DLMS_RTC_SEC_COUNTER_NUMBER];
uint32_t	counter_value[DLMS_RTC_SEC_COUNTER_NUMBER];
r_dlms_rtc_sec_counter_t counter =
{
	counter_enable,
	counter_value,
	DLMS_RTC_SEC_COUNTER_NUMBER
};

static uint8_t g_timezone_is_changed = FALSE;

/******************************************************************************
* Function Name : R_DLMS_RTC_Drv_PeriodCallBack
* Interface     : void R_DLMS_RTC_Drv_PeriodCallBack(
*               :     void
*               : );
* Description   : This function is called for each 0.5s RTC interrupts
*				: Counter is count 1 per 2 interrupts
* Arguments     : <None>
* Return Value  : <None>
******************************************************************************/
void R_DLMS_RTC_Drv_PeriodCallBack ( void )
{
	static uint8_t decoupled_tick;
	uint8_t counter_id;

	if (decoupled_tick == 0)
	{
		decoupled_tick++;
	}
	else
	{
		for (counter_id = 0; counter_id < counter.alloc_size; counter_id++)
		{
			if ((counter.enable[counter_id] == TRUE) && (counter.value[counter_id] > 0))
			{
				counter.value[counter_id]--;
			}
		}
		decoupled_tick = 0;
	}
    rtc_tick_flag = TRUE;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_Counter_Reset
* Interface     : void R_DLMS_RTC_Counter_Reset(
*               :     uint8_t counter_id
*               : );
* Description   :
* Arguments     :
* Return Value  :
******************************************************************************/
void R_DLMS_RTC_Counter_Disable ( uint8_t counter_id )
{
	if (counter_id < counter.alloc_size)
	{
		counter.enable[counter_id] = FALSE;
	}
}
void R_DLMS_RTC_Counter_Enable ( uint8_t counter_id )
{
	if (counter_id < counter.alloc_size)
	{
		counter.enable[counter_id] = TRUE;
	}
}
uint32_t R_DLMS_RTC_Counter_GetValue ( uint8_t counter_id )
{
	if (counter_id < counter.alloc_size)
	{
		return counter.value[counter_id];
	}
	else 
	{
		return 0;
	}
}
void R_DLMS_RTC_Counter_SetValue(uint8_t counter_id , uint32_t value)
{
	if (counter_id < counter.alloc_size)
	{
		if (counter.enable[counter_id] == FALSE)
		{
			counter.value[counter_id] = value;
			counter.enable[counter_id] = TRUE;
		}
	}
}
void R_DLMS_RTC_Counter_Start(uint8_t counter_id , uint32_t value)
{
	if (counter_id < counter.alloc_size)
	{
		counter.value[counter_id] = value;
		counter.enable[counter_id] = TRUE;
	}
}

/******************************************************************************
* Function Name : R_DLMS_RTC_DrvDateTime_Get
* Interface     : void R_DLMS_RTC_DrvDateTime_Get (
*               :     date_time_t * p_date_time
*               : );
* Description   : Get date time from MCU Driver RTC
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_RTC_Get_Drv_DateTime (
    R_DLMS_RTC_T * p_rtc_time
)
{
	rtc_counter_value_t r_rtc;

    /* Check parameters */
    if (p_rtc_time == NULL)
    {
        return RLT_ERR; // Params error
    }

    /* Get by RTC driver IF */
    R_RTC_Get_CalendarCounterValue(&r_rtc);
    
    /* Convert all to decimal */
    p_rtc_time->Sec		= WRP_EXT_Bcd2Dec(r_rtc.sec);
    p_rtc_time->Min		= WRP_EXT_Bcd2Dec(r_rtc.min);
    p_rtc_time->Hour	= WRP_EXT_Bcd2Dec(r_rtc.hour);
    p_rtc_time->Day		= WRP_EXT_Bcd2Dec(r_rtc.day);
    p_rtc_time->Week	= g_DayOfWeek[WRP_EXT_Bcd2Dec(r_rtc.week)];
    p_rtc_time->Month	= WRP_EXT_Bcd2Dec(r_rtc.month);
    p_rtc_time->Year	= WRP_EXT_Bcd2Dec(r_rtc.year);

    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_SetRTC
* Interface     : void R_DLMS_SetRTC(
*               :     date_time_t * p_date_time
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_RTC_Set_Drv_DateTime (
    R_DLMS_RTC_T * p_app_rtc_time
)
{
	rtc_counter_value_t rtctime;
	rtc_counter_value_t *p_rtctime = &rtctime;

	uint16_t year;		/* For year calculation */

    /* Check parameters */
    if (p_app_rtc_time == NULL)
    {
        return 1; // Params error
    }

    memcpy( (uint8_t *)p_rtctime, (uint8_t *)p_app_rtc_time, sizeof(R_DLMS_RTC_T));

	if (p_app_rtc_time->Week < 1 || p_app_rtc_time->Week > 7)
	{
		year = 2000 + (p_app_rtc_time->Year);
		p_app_rtc_time->Week = R_DLMS_RTC_wday(year, p_app_rtc_time->Month, p_app_rtc_time->Day);
	}
	p_app_rtc_time->Week = g_DLMS_WEEK_2_RTC_WEEK[p_app_rtc_time->Week];
    
    /* Set by RTC driver IF */
   

    /* Convert all to BCD */
	p_rtctime->sec	= WRP_EXT_Dec2Bcd(p_app_rtc_time->Sec);
	p_rtctime->min	= WRP_EXT_Dec2Bcd(p_app_rtc_time->Min);
	p_rtctime->hour	= WRP_EXT_Dec2Bcd(p_app_rtc_time->Hour);
	p_rtctime->day	= WRP_EXT_Dec2Bcd(p_app_rtc_time->Day);
	p_rtctime->week	= WRP_EXT_Dec2Bcd(p_app_rtc_time->Week);
	p_rtctime->month= WRP_EXT_Dec2Bcd(p_app_rtc_time->Month);
	p_rtctime->year	= WRP_EXT_Dec2Bcd(p_app_rtc_time->Year);
	
    /* Disable snapshot capture */
    R_INST_SetSnapshotCaptureState(0);

    /* Pop out all snapshot in queue */
    R_INST_DataPopAll();

	R_HANDLER_BackupBeforeApplyNewRTCValue(p_rtctime);

    R_RTC_Set_CalendarCounterValue(rtctime);

    /* Re-enable snapshot capture */
    R_INST_SetSnapshotCaptureState(1);

    R_HANDLER_AfterApplyNewRTCValue();

    return 0;
}

/******************************************************************************
* Function Name : R_USER_SetRTCAlarm
* Interface     : void R_USER_SetRTCAlarm(date_time_t *p_date_time)
* Description   :
* Created date  : 2018-03-21
* Arguments     : date_time_t * p_date_time:
* Function Calls:
* Return Value  : None
******************************************************************************/
void R_DLMS_RTC_Set_Drv_Alarm(R_DLMS_RTC_T *p_date_time)
{
	rtc_alarm_value_t rtc_alarm;			/* RTC alarm value for Driver IF */
	rtc_alarm_value_t rtc_alarm_old;

	uint8_t i;
	
	uint16_t year;
	uint16_t year_rtc;

    /* TODO: R_DLMS_RTC_Set_Drv_Alarm currently not used and driver API no longer compatible 
    * Need:     Porting code to match with new driver API and test again when use this API
    */

	// /* Get original date_time first */
	// R_RTC_Get_AlarmValue(&rtc_alarm, &control);

	// /* Convert the date time to RTC Alarm Control */
	// {
	// 	DLMS_VALIDATE_ALARM_VALUE(p_date_time->Sec, rtc_alarm.rseccnt, control.sec_enb);
	// 	DLMS_VALIDATE_ALARM_VALUE(p_date_time->Min, rtc_alarm.rmincnt, control.min_enb);
	// 	DLMS_VALIDATE_ALARM_VALUE(p_date_time->Hour, rtc_alarm.rhrcnt, control.hr_enb);

	// 	DLMS_VALIDATE_ALARM_VALUE(p_date_time->Day, rtc_alarm.rdaycnt, control.day_enb);
	// 	DLMS_VALIDATE_ALARM_VALUE(p_date_time->Week, rtc_alarm.rwkcnt, control.wk_enb);
	// 	DLMS_VALIDATE_ALARM_VALUE(p_date_time->Month, rtc_alarm.rmoncnt, control.mon_enb);
	// 	DLMS_VALIDATE_ALARM_VALUE(p_date_time->Year, rtc_alarm.ryrcnt, control.yr_enb);
	// }

	// /* Set to RTC driver by IF */
	// R_RTC_Set_AlarmValue(rtc_alarm, control);
}

/******************************************************************************
* Function Name : R_DLMS_RTC_IsDateTimeDiff
* Interface     : uint8_t R_DLMS_RTC_IsDateTimeDiff(
*               :     date_time_t * current,
*               :     date_time_t * old
*               : );
* Description   : Detetect the change in RTC date time
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_RTC_IsDateTimeDiff(
	date_time_params_t * params
)
{
    R_DLMS_RTC_T *p_current = &params->date_time.current;
    R_DLMS_RTC_T *p_old     = &params->date_time.old;
    rtc_flag_t * result = &params->change_flag;

	params->change_flag.bytes = 0;

	if (p_current->Year > p_old->Year)
	{
		result->bytes |= RTC_BIT_YEAR_IS_CHANGED | RTC_BIT_MONTH_IS_CHANGED | RTC_BIT_DAY_IS_CHANGED | RTC_BIT_WEEK_IS_CHANGED | \
						RTC_BIT_HOUR_IS_CHANGED | RTC_BIT_MINUTE_IS_CHANGED | RTC_BIT_SECOND_IS_CHANGED;
	}
	else if (p_current->Year < p_old->Year)
	{
		return result->bytes;
	}
	if (p_current->Month > p_old->Month)
	{
		result->bytes |= RTC_BIT_MONTH_IS_CHANGED | RTC_BIT_DAY_IS_CHANGED | RTC_BIT_WEEK_IS_CHANGED | \
						RTC_BIT_HOUR_IS_CHANGED | RTC_BIT_MINUTE_IS_CHANGED | RTC_BIT_SECOND_IS_CHANGED;
	}
	else if (p_current->Month < p_old->Month)
	{
		return result->bytes;
	}
	if (p_current->Day > p_old->Day)
	{
		result->bytes |= RTC_BIT_DAY_IS_CHANGED | RTC_BIT_WEEK_IS_CHANGED | \
						RTC_BIT_HOUR_IS_CHANGED | RTC_BIT_MINUTE_IS_CHANGED | RTC_BIT_SECOND_IS_CHANGED;
	}
	else if (p_current->Day < p_old->Day)
	{
		return result->bytes;
	}
	if (p_current->Hour > p_old->Hour)
	{
		result->bytes |= RTC_BIT_HOUR_IS_CHANGED | RTC_BIT_MINUTE_IS_CHANGED | RTC_BIT_SECOND_IS_CHANGED;
	}
	else if (p_current->Hour < p_old->Hour)
	{
		return result->bytes;
	}
	if (p_current->Min > p_old->Min)
	{
		result->bytes |= RTC_BIT_MINUTE_IS_CHANGED | RTC_BIT_SECOND_IS_CHANGED;
	}
	else if (p_current->Min < p_old->Min)
	{
		return result->bytes;
	}
	if (p_current->Sec > p_old->Sec)
	{
		result->bytes |= RTC_BIT_SECOND_IS_CHANGED;
	}

	return result->bytes; /* OK */
}


/******************************************************************************
* Function Name : R_DLMS_RTC_CompareDateTime
* Interface     : Integer8 R_DLMS_RTC_CompareDateTime(
*               :     Unsigned8 *p_src_date_time,
*               :     Unsigned8 *p_des_date_time
*               : );
* Description   : Compare date time
* Arguments     : Unsigned8 * p_src_date_time: Src date
*               : Unsigned8 * p_des_date_time: Des date
* Function Calls: None
* Return Value  : Integer8, -1: src < des, 1: src > des, 0: src = des
******************************************************************************/
int8_t R_DLMS_RTC_CompareDateTime(
	uint8_t *p_src_date_time,
	uint8_t *p_des_date_time
)
{
	uint8_t	i;
	int8_t	result = 1;

	/*
	 * Checking following:
	 * year_high, year_low, month, day_of_month
	 * hour, minute, second, hundredths of second
	 */
	for (i = 0; i < 9; i++)
	{
		/* skip day_of_week */
		if (i == 4)
		{
			continue;
		}

		if (p_src_date_time[i] != RTC_NOT_SPECIFIED &&
			p_des_date_time[i] != RTC_NOT_SPECIFIED)
		{
			if (p_src_date_time[i] < p_des_date_time[i])
			{
				return -1;
			}
			else if (p_src_date_time[i] > p_des_date_time[i])
			{
				return 1;
			}
			result = 0;
		}
	}

	/* all equal */
	return result;
}
/******************************************************************************
* Function Name : R_DLMS_RTC_Compare
* Interface     : int8_t R_DLMS_RTC_Compare(
*               :     uint8_t *p_src_date_time,
*               :     uint8_t *p_des_date_time
*               : );
* Description   : Compare date time
* Arguments     : uint8_t * p_src_date_time: Src date (R_DLMS_RTC_T)
*               : uint8_t * p_des_date_time: Des date (R_DLMS_RTC_T)
* Function Calls: None
* Return Value  : int8_t, -1: src < des, 1: src > des, 0: src = des
******************************************************************************/
int8_t R_DLMS_RTC_Compare(
	uint8_t *p_src_date_time,
	uint8_t *p_des_date_time
)
{
	int8_t	i;
	int8_t	result = 1;

	/*
	 * Checking following:
	 * Year, Month, Week, Day
	 * Hour, Min, Sec
	 */
	for (i = 6; i >= 0; i--)
	{
		/* skip day_of_week */
		if (i == 4)
		{
			continue;
		}
		if (p_src_date_time[i] != RTC_NOT_SPECIFIED &&
			p_des_date_time[i] != RTC_NOT_SPECIFIED)
		{
			if (p_src_date_time[i] < p_des_date_time[i])
			{
				return -1;
			}
			else if (p_src_date_time[i] > p_des_date_time[i])
			{
				return 1;
			}
			result = 0;
		}
	}

	/* all equal */
	return result;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_Compare
* Interface     : int8_t R_DLMS_RTC_Compare(
*               :     uint8_t *p_src_date_time,
*               :     uint8_t *p_des_date_time
*               : );
* Description   : Compare date time
* Arguments     : uint8_t * p_src_date_time: Src date (R_DLMS_RTC_T)
*               : uint8_t * p_des_date_time: Des date (R_DLMS_RTC_T)
* Function Calls: None
* Return Value  : int8_t, -1: src < des, 1: src > des, 0: src = des
******************************************************************************/
int8_t R_DLMS_RTC_DayCompare(
	uint8_t *p_src_date_time,
	uint8_t *p_des_date_time
)
{
	int8_t	i;
	int8_t	result = 1;

	/*
	 * Checking following:
	 * Year, Month, Week, Day
	 * Hour, Min, Sec
	 */
	for (i = 6; i >= 3; i--)
	{	
        /* skip day_of_week */
		if (i == 4)
		{
			continue;
		} 
		if (p_src_date_time[i] != RTC_NOT_SPECIFIED &&
			p_des_date_time[i] != RTC_NOT_SPECIFIED)
		{
			if (p_src_date_time[i] < p_des_date_time[i])
			{
				return -1;
			}
			else if (p_src_date_time[i] > p_des_date_time[i])
			{
				return 1;
			}
			result = 0;
		}
	}

	/* all equal */
	return result;
}




/******************************************************************************
* Function Name : R_DLMS_RTC_GetDateTime
* Interface     : void R_DLMS_RTC_GetDateTime(
*               :
*               : );
* Description   : Get date time for RTC
* Arguments     : [Out] date_time_t * rdatetime
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_RTC_Get_DateTime(uint8_t * p_date_time)
{
    uint8_t rlt = RLT_SUCCESS;
    uint16_t year;
	rtc_status_t status;
    R_DLMS_RTC_T rtctime; /* RTC value for Driver IF */

    rlt |= R_DLMS_RTC_Get_Drv_DateTime(&rtctime);

    year = rtctime.Year + 2000;
    /* Convert to date_time_t to DLMS structure */
    p_date_time[DLMS_CLOCK_YEAR_H_POS]      = (uint8_t)(year>>8);
    p_date_time[DLMS_CLOCK_YEAR_L_POS]      = (uint8_t)year;
    p_date_time[DLMS_CLOCK_MON_POS]         = (uint8_t)rtctime.Month;   /* Month */
    p_date_time[DLMS_CLOCK_DAY_POS]         = (uint8_t)rtctime.Day;     /* Day */
    p_date_time[DLMS_CLOCK_WEEK_POS]        = (uint8_t)rtctime.Week;    /* Friday */
    p_date_time[DLMS_CLOCK_HOUR_POS]        = (uint8_t)rtctime.Hour;    /* Hour */
    p_date_time[DLMS_CLOCK_MIN_POS]         = (uint8_t)rtctime.Min;     /* Minute */
    p_date_time[DLMS_CLOCK_SEC_POS]         = (uint8_t)rtctime.Sec;     /* Second */
    p_date_time[DLMS_CLOCK_HUNDREDTH_POS]   = (uint8_t)0;

	/* Time-zone */

    p_date_time[DLMS_CLOCK_DEVIATION_H_POS] = (uint8_t)(g_time_zone>>8);
    p_date_time[DLMS_CLOCK_DEVIATION_L_POS] = (uint8_t)g_time_zone;

	/* Check clock status */
	status.byte = g_clock_status;
	if (R_DLMS_IsValidDateTime((date_time_t *)p_date_time) != R_DATE_TIME_VALID)
	{
		status.bits.invalid = TRUE;
	}
    p_date_time[DLMS_CLOCK_STATUS_POS] = status.byte;

    return rlt;
}

/******************************************************************************
* Function Name : R_DLMS_SetDateTime
* Interface     : void R_DLMS_SetDateTime(
*               :     date_time_t * p_date_time
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_RTC_Set_DateTime( date_time_t * p_date_time )
{
	uint8_t rlt = RLT_SUCCESS;

	uint8_t  i;							/* Counter */
	uint8_t  status;					/* Status of operation */
	uint16_t timeout;					/* Timeout counter to ensure the system not crash */
	R_DLMS_RTC_T set_value;			/* RTC value for Driver IF */
	date_time_t original_date_time;
	uint8_t  *p_u8;

	int16_t * p_time_zone;

	date_time_params_t * p_profile;
	uint8_t * p_check_value;
	uint8_t * p_origin_value;

	/* Check parameters */
	if (p_date_time == NULL)
	{
		return RLT_ERR_NULL; /* Params error */
	}

	/* 
	*  Set procedure:
	*       [DLMS_Class_DateTime] --> [DLMS_App_Date_Time] --> [RTC_Driver]
	*
	*   1. Check Validation(DLMS Class DateTime)
	*   2. Convert DLMS_Class_DateTime to DLMS_App_Date_Time
	*   3. Set DLMS_App_Date_Time to the driver
	*/

	status = R_DLMS_IsValidDateTime(p_date_time);

	if (status == RLT_SUCCESS)
	{
		R_DLMS_RTC_Convert_DateTime2RTC(&set_value, p_date_time);
		p_profile = R_DLMS_RTC_Get_TimeProfile();

		/* For not specified value, get origin value of meter */
		for (i = 0; i < sizeof(R_DLMS_RTC_T); i++)
		{
			p_check_value = (uint8_t *)&set_value + i;
			p_origin_value = (uint8_t *)&p_profile->date_time.current + i;
			if ( *p_check_value == 0xFF)
			{
				*p_check_value = *p_origin_value;
			}
		}

		/* Set to by RTC driver IF */
		R_DLMS_RTC_Set_Drv_DateTime(&set_value);

		/* Update time zone */
		timeout = (uint16_t)(p_date_time->deviation_high<<8) + p_date_time->deviation_low;
		if (timeout != 0x8000)			// Specified
		{
			p_time_zone = (int16_t *)&timeout;
            g_time_zone = timeout;
            /* write new time zone to storage */
	        R_DLMS_EEPROM_Write(storage_info_time_zone, (uint8_t *)&g_time_zone);
		}
	}
	else
	{
		rlt = RLT_ERR_INVALID_PARAMETER;  /* Invalid date time */
	}

	g_clock_status = p_date_time->clock_status;

    /* Write new clock status */
	R_DLMS_EEPROM_Write(storage_info_clock_status, (uint8_t *)&g_clock_status);

    R_DLMS_RTC_Get_Drv_DateTime(&g_DLMS_RTC_params.date_time.current);

	return rlt;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_Convert_RTC_To_DateAndTime
* Interface     : void R_DLMS_RTC_Convert_RTC_To_DateAndTime(
*               :     R_DLMS_RTC_T *p_rtc, date_t *p_date, time_t *p_time
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_RTC_Convert_RTC_To_DateAndTime(
	R_DLMS_RTC_T *p_rtc, date_t *p_date, time_t *p_time
)
{
	uint16_t year;

	if ((p_date == NULL) ||
		(p_time == NULL))
	{
		return; /* NG */
	}

	if (p_rtc->Year == 0xFF)
	{
		year = 0xFFFF;
	}
	else
	{
		year = p_rtc->Year + 2000;
	}
	p_date->year_low = (uint8_t)year;
	p_date->year_high = (uint8_t)(year >> 8);

	p_date->month = p_rtc->Month;
	p_date->day_of_month = p_rtc->Day;
	p_date->day_of_week = p_rtc->Week;

	p_time->hour	= p_rtc->Hour;
	p_time->minute	= p_rtc->Min;
	p_time->second	= p_rtc->Sec;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_Convert_DateAndTime_To_RTC
* Interface     : void R_DLMS_RTC_Convert_DateAndTime_To_RTC(
*               :     date_t *p_date, time_t *p_time, R_DLMS_RTC_T *p_rtc
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_RTC_Convert_DateAndTime_To_RTC (
	date_t *p_date, time_t *p_time, R_DLMS_RTC_T *p_rtc
)
{
	uint16_t year;

	if ((p_date == NULL) ||
		(p_time == NULL))
    {
        return; /* NG */
    }

    year = (uint16_t) (p_date->year_high << 8) + p_date->year_low;
    if (year == 0xFFFF)
    {
        p_rtc->Year = 0xFF;
    }
    else
    {
        p_rtc->Year = year % 100;
    }
    p_rtc->Month    = p_date->month;
    p_rtc->Day      = p_date->day_of_month;
    p_rtc->Week     = p_date->day_of_week;

    p_rtc->Hour     = p_time->hour;
    p_rtc->Min      = p_time->minute;
    p_rtc->Sec      = p_time->second;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_Convert_DLMSWeekToDriverWeek
* Interface     : uint8_t R_DLMS_RTC_Convert_DLMSWeekToDriverWeek(uint8_t *p_dest, uint8_t *p_src)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_RTC_Convert_DLMSWeekToDriverWeek(uint8_t *p_dest, uint8_t *p_src)
{
    if (*p_src == 0xFF)
    {
        *p_dest = 0xFF;
    }
    else
    {
        (*p_dest) = g_DLMS_WEEK_2_RTC_WEEK[(*p_src)];
    }

    return TRUE;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_Convert_DriverWeekToDLMSWeek
* Interface     : uint8_t R_DLMS_RTC_Convert_DriverWeekToDLMSWeek(uint8_t *p_dest, uint8_t *p_src)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_RTC_Convert_DriverWeekToDLMSWeek(uint8_t *p_dest, uint8_t *p_src)
{
    (*p_dest) = g_DayOfWeek[(*p_src)];

    return TRUE;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_Convert_DriverRTC2DateTime
* Interface     : void R_DLMS_RTC_Convert_DriverRTC2DateTime(
*               :     r_calendar * rtc,
*               :     date_time_t * p_date_time
*               : );
* Description   : Convert RTC date time structure to DLMS date time structure
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_RTC_Convert_DriverRTC2DateTime(
	date_time_t					 * p_dt,			// Outout
	rtc_counter_value_t	         * p_date_time
)
{
	R_DLMS_RTC_T rtc_time;

	rtc_time.Sec = (p_date_time->sec);
	rtc_time.Min = (p_date_time->min);
	rtc_time.Hour = (p_date_time->hour);
	rtc_time.Day = (p_date_time->day);
	rtc_time.Week = g_DayOfWeek[p_date_time->week];
	rtc_time.Month = (p_date_time->month);
	rtc_time.Year = (p_date_time->year);

	R_DLMS_RTC_Convert_RTC2DateTime(p_dt, &rtc_time);

	return RLT_SUCCESS;
}
/******************************************************************************
* Function Name : R_DLMS_RTC_Convert_RTC2DateTime
* Interface     : void R_DLMS_RTC_Convert_RTC2DateTime(
*               :     date_time_t * p_date_time, 
*               :     R_DLMS_RTC_T * rtc
*               : );
* Description   : Convert RTC date time structure to DLMS date time structure
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_RTC_Convert_RTC2DateTime (
    date_time_t * p_date_time,
    R_DLMS_RTC_T * rtc
)
{
    uint8_t rlt = RLT_SUCCESS;
	int16_t timezone;

    /* Variables */
    uint16_t year;		/* For year calculation */

    year = 2000 + (rtc->Year);

	if (rtc->Year == 0xFF || rtc->Day == 0xFF || rtc->Month == 0xFF)
	{
		p_date_time->day_of_week	= 0xFF;
	}
	else if ((rtc->Week == 0) || ((rtc->Week > 7)))
	{
		p_date_time->day_of_week = R_DLMS_RTC_wday(year, rtc->Month, rtc->Day);
	}
	else
	{
		p_date_time->day_of_week    = rtc->Week;
	}

    p_date_time->day_of_month   = rtc->Day;
    p_date_time->month          = rtc->Month;
    p_date_time->year_low       = (uint8_t)year;
    p_date_time->year_high      = (uint8_t)(year>>8);
    p_date_time->hour           = rtc->Hour;
    p_date_time->minute         = rtc->Min;
    p_date_time->second         = rtc->Sec;
    p_date_time->hundredths     = 0;

    if (rtc->Year == 0xFF)
    {
        p_date_time->year_low       = 0xFF;
        p_date_time->year_high      = 0xFF;
    }

    p_date_time->deviation_high = (int8_t)(g_time_zone >> 8);
    p_date_time->deviation_low = (int8_t)(g_time_zone);

	p_date_time->clock_status = g_clock_status;

    /* Return OK */
    return rlt;
}
/******************************************************************************
* Function Name : R_DLMS_RTC_Convert_DateTime2RTC
* Interface     : void R_DLMS_RTC_Convert_DateTime2RTC(
*               :     R_DLMS_RTC_T * rtc, 
*               :     date_time_t * p_date_time
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_RTC_Convert_DateTime2RTC (
    R_DLMS_RTC_T * rtc,
    date_time_t * p_date_time
)
{
    uint8_t rlt = RLT_SUCCESS;
    uint16_t year;

    year = (uint16_t)(p_date_time->year_high << 8) + p_date_time->year_low;
    if (year == 0xFFFF)
    {
        rtc->Year = 0xFF;
    }
    else
    {
        rtc->Year = year % 100;
    }

    /* Convert from decimal counter to BCD */
    rtc->Day = p_date_time->day_of_month;
    rtc->Week = p_date_time->day_of_week;
    rtc->Month = p_date_time->month;
    
    rtc->Hour = p_date_time->hour;
    rtc->Min = p_date_time->minute;
    rtc->Sec = p_date_time->second;
    /* Return OK */
    return rlt;
}


void R_DLMS_RTC_ConvertToLocalTimeZone(R_DLMS_RTC_T *p_date_time_data, int32_t timezone);
/******************************************************************************
* Function Name : R_DLMS_RTC_ConvertToLocalTimeZone
* Interface     : void R_DLMS_RTC_ConvertToLocalTimeZone(date_time_t *p_date_time_data)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_DLMS_RTC_ConvertToLocalTimeZone(R_DLMS_RTC_T *p_date_time_data, int32_t timezone)
{
	int32_t diff;

    /* Check if the transmitted time contains the daylight saving deviation */
	{
		diff = (int32_t)p_date_time_data->Hour * 60 + p_date_time_data->Min;
		diff = diff + (int32_t)(g_time_zone - timezone);

		if (diff > 24*60)
		{
			diff = diff - 24 * 60;
			R_DLMS_RTC_Find_NextDay(p_date_time_data);
		}
		else if (diff < 0)
		{
			diff = 24 * 60 + diff;
			R_DLMS_RTC_Find_PrevDay(p_date_time_data);
		}

		if (diff < 0)
		{
			diff = -diff;
		}

		p_date_time_data->Hour = (uint8_t)(diff / 60);
		p_date_time_data->Min = (uint8_t)(diff % 60);
	}

}


/******************************************************************************
* Function Name : R_DLMS_RTC_Convert_RTC2DateTime2
* Interface     : void R_DLMS_RTC_Convert_RTC2DateTime2(
*               :     date_time_t * p_date_time, 
*               :     rtc_counter_value_t * rtc
*               : );
* Description   : Convert RTC date time structure to DLMS date time structure
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_RTC_Convert_RTC2DateTime2 (
    date_time_t * p_date_time,
    rtc_counter_value_t * rtc
)
{
    uint8_t rlt = RLT_SUCCESS;
	int16_t timezone;

    /* Variables */
    uint16_t year;		/* For year calculation */

    year = 2000 + (rtc->year);

	if (rtc->year == 0xFF || rtc->day == 0xFF || rtc->month == 0xFF)
	{
		p_date_time->day_of_week	= 0xFF;
	}
	else if ((rtc->week == 0) || ((rtc->week > 7)))
	{
		p_date_time->day_of_week = R_DLMS_RTC_wday(year, rtc->month, rtc->day);
	}
	else
	{
		p_date_time->day_of_week    = rtc->week;
	}

    p_date_time->day_of_month   = rtc->day;
    p_date_time->month          = rtc->month;
    p_date_time->year_low       = (uint8_t)year;
    p_date_time->year_high      = (uint8_t)(year>>8);
    p_date_time->hour           = rtc->hour;
    p_date_time->minute         = rtc->min;
    p_date_time->second         = rtc->sec;
    p_date_time->hundredths     = 0;

    if (rtc->year == 0xFF)
    {
        p_date_time->year_low       = 0xFF;
        p_date_time->year_high      = 0xFF;
    }
    p_date_time->deviation_high = (int8_t)(g_time_zone >> 8);
    p_date_time->deviation_low = (int8_t)g_time_zone;

	p_date_time->clock_status = g_clock_status;

    /* Return OK */
    return rlt;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_Convert_DateTime2RTC2
* Interface     : void R_DLMS_RTC_Convert_DateTime2RTC2(
*               :     rtc_counter_value_t * rtc, 
*               :     date_time_t * p_date_time
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_RTC_Convert_DateTime2RTC2 (
    rtc_counter_value_t * rtc,
    date_time_t * p_date_time
)
{
    uint8_t rlt = RLT_SUCCESS;
    uint16_t year;

    year = (uint16_t)(p_date_time->year_high << 8) + p_date_time->year_low;
    if (year == 0xFFFF)
    {
        rtc->year = 0xFF;
    }
    else
    {
        rtc->year = year % 100;
    }

    /* Convert from decimal counter to BCD */
    rtc->day = p_date_time->day_of_month;
    rtc->week = p_date_time->day_of_week;
    rtc->month = p_date_time->month;
    
    rtc->hour = p_date_time->hour;
    rtc->min = p_date_time->minute;
    rtc->sec = p_date_time->second;
    /* Return OK */
    return rlt;
}

/******************************************************************************
* Function Name : R_DLMS_GetDate
* Interface     : void R_DLMS_GetDate(
*               :     date_t * rdate
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_GetDate( date_t * rdate)
{
	uint16_t year;
    R_DLMS_RTC_T rtctime;

	/* API to get date time from driver */
	R_DLMS_RTC_Get_Drv_DateTime(&rtctime);

	/* Convert date time to DLMS structure */
    rdate->year_high    =   0;
    rdate->year_low     =   rtctime.Year;
    rdate->day_of_week  =   rtctime.Week;
    rdate->day_of_month =   rtctime.Day;
    rdate->month        =   rtctime.Month;
}

/******************************************************************************
* Function Name : R_DLMS_GetTime
* Interface     : void R_DLMS_GetTime(
*               :     void
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_GetTime (time_t * rtime)
{
    R_DLMS_RTC_T rtctime;

	/* API to get date time from driver */
	R_DLMS_RTC_Get_Drv_DateTime(&rtctime);

    rtime->hour = rtctime.Hour;
    rtime->minute = rtctime.Min;
    rtime->second = rtctime.Sec;
    rtime->hundredths = 0;
}

/******************************************************************************
* Function Name : R_DLMS_DATE_Next
* Interface     : void R_DLMS_DATE_Next(
*               :     date_time_t *pDateTime
*               : );
* Description   :
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_RTC_Find_NextDay(R_DLMS_RTC_T *pDateTime)
{
    uint16_t ndays;
	uint16_t year;

	year = pDateTime->Year + 2000;

    /*=======================================================================*/
    ndays = nDayOfMonth[pDateTime->Month-1];
    if (pDateTime->Month==2)
    {
        if ( ( ((year)%100==0) && ((year)%400==0) ) ||
             (  (year)%4==0 ) )
        {
            ndays = 29;
        }
    }

    pDateTime->Day += 1;
    pDateTime->Week += 1;
    if (pDateTime->Week > 7)
    {
        pDateTime->Week = 1;
    }

    if ( pDateTime->Day > ndays )
    {
        pDateTime->Day = 1;
        pDateTime->Month++;
    }
    if ( pDateTime->Month > 12 )
    {
        pDateTime->Month = 1;
		pDateTime->Year++;
		if (year > 99)
		{
			year = 0;
		}
    }
    /*=======================================================================*/

}

/******************************************************************************
* Function Name : R_DLMS_DATE_Prev
* Interface     : void R_DLMS_DATE_Prev(
*               :     date_time_t *pDateTime
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_RTC_Find_PrevDay(R_DLMS_RTC_T *pDateTime)
{
	uint16_t year = pDateTime->Year + 2000;

    /* Get yesterday's (previous) date */
    if (pDateTime->Day==1)
    {
        if ( pDateTime->Month == 4 || pDateTime->Month == 6 || pDateTime->Month == 9 || pDateTime->Month == 11 )
        {
            pDateTime->Day = 31;
            pDateTime->Month--;
        }
        else if (pDateTime->Month == 3)
        {
            if(( (year) %4)==0)
            {
                pDateTime->Day = 29;
            }
            else
            {
                pDateTime->Day = 28;
            }
            pDateTime->Month--;
        }
        else if(pDateTime->Month==1)
        {
            pDateTime->Day = 31;
			if (year > 2000)
			{
				pDateTime->Year--;
			}
        }
        else if(pDateTime->Month==2)
        {
            pDateTime->Day = 31;
            pDateTime->Month--;
        }
        else
        {
            pDateTime->Day = 30;
            pDateTime->Month--;
        }
    }
    else
    {
        pDateTime->Day--;
    }
}

/******************************************************************************
* Function Name : R_DLMS_IsValidTimeZone
* Interface     : uint8_t R_DLMS_IsValidTimeZone(
*               :     int16_t deviation
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_IsValidTimeZone ( int16_t deviation )
{
	if ( ( (deviation >= (-720)) && (deviation <= 720) ) || deviation == 0x8000)
	{
		return R_DATE_TIME_VALID;
	}
	return R_DATE_TIME_INVALID;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_Change_TimeZone
* Interface     : void R_DLMS_RTC_Change_TimeZone(
*               :     int16_t time_zone_new
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_RTC_Change_TimeZone (int16_t time_zone_new)
{
    uint8_t rlt = RLT_SUCCESS;
    uint16_t year;
    int32_t diff;
    int16_t time_zone_diff;

    R_DLMS_RTC_T current_local_time;

    int16_t time_zone_old;


    time_zone_old = g_time_zone;

    time_zone_diff = time_zone_new - time_zone_old;

    R_DLMS_RTC_Get_Drv_DateTime(&current_local_time);

    diff = (int32_t)current_local_time.Hour * 60 + current_local_time.Min;
    diff = diff + (int32_t)time_zone_diff;

    if (diff > 24*60)
    {
        diff = diff - 24 * 60;
        R_DLMS_RTC_Find_NextDay(&current_local_time);
    }
    else if (diff < 0)
    {
        diff = 24 * 60 + diff;
        R_DLMS_RTC_Find_PrevDay(&current_local_time);
    }

    if (diff < 0)
    {
        diff = -diff;
    }

    current_local_time.Hour = (uint8_t)(diff / 60);
    current_local_time.Min = (uint8_t)(diff % 60);

    // Update date
    R_DLMS_RTC_Set_Drv_DateTime(&current_local_time);

    // Update time zone
	g_time_zone = time_zone_new;
    /* write new time zone to storage */
	R_DLMS_EEPROM_Write(storage_info_time_zone, (uint8_t *)&g_time_zone);

    g_timezone_is_changed = TRUE;

    return rlt;
}


/******************************************************************************
* Function Name : R_DLMS_wday
* Interface     : void R_DLMS_wday(
*               :     uint16_t year, uint16_t month, uint16_t day
*               : );
* Description   : Calculate day of week from day-month-year
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_RTC_wday ( uint16_t year, uint8_t month, uint8_t day )
{
    uint16_t adjustment, mm, yy;
    /* Rosetta Code */
    adjustment = (14 - month) / 12;
    mm = month + 12 * adjustment - 2;
    yy = year - adjustment;

    adjustment = (day + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;
    if(adjustment == 0)
    {
        adjustment = 7;
    }

    return (adjustment);
}


/******************************************************************************
* Function Name : R_USER_IsValidDate
* Interface     : uint8_t R_USER_IsValidDate(
*               :     uint8_t *p_date,
*               : );
* Description   : Check valid date time or not
* Arguments     : uint8_t *p_date
* Function Calls: None
* Return Value  : uint8_t, 0: invalid, 1 : valid
******************************************************************************/
uint8_t R_DLMS_IsValidDate(date_t *p_date)
{
    uint16_t ret = RLT_SUCCESS;	// Invalid
    uint16_t year, month, day, dweek;
    uint8_t weekday;
    uint16_t ndays; /* Number day of month */

    // if(date.month >= DATE_MONTH_DAYLIGHT_SAVINGS_END) // Month
    // {
    //     date.month = RTC_NOT_SPECIFIED;
    // }
    
    // if(date.day_of_month >= DATE_DAY_2ND_LAST_OF_MONTH) // day of month
    // {
    //     date.day_of_month = RTC_NOT_SPECIFIED;
    // }

    /*==============================================*/
    year = COMBINE_U16(p_date->year_high, p_date->year_low);
    month = p_date->month;
    day = p_date->day_of_month;
    dweek = p_date->day_of_week;

    if (year == 0xFFFF) // Not specific year
    {
        year = 2018;
    }

    if (p_date->month == RTC_NOT_SPECIFIED)
    {
        month = 2;
    }

	if ((month > 12) || (month == 0))
	{ 
		return RLT_ERR_INVALID_DATA;
	}

    if (p_date->day_of_month == RTC_NOT_SPECIFIED)
    {
        day = 28;
    }

	if ((day > 31) || (day == 0))
	{ 
		return RLT_ERR_INVALID_DATA;
	}
    /*==============================================*/
    /* Check year */
    if (year < 2000)
    {
        return RLT_ERR_INVALID_DATA; /* 1: Invalid */
    }

    /* Check day and month */
    if (p_date->day_of_month != RTC_NOT_SPECIFIED)
    {
        ndays = nDayOfMonth[month-1];
        if (month==2)
        {
            if ( ( (year%100==0) && (year%400==0) ) ||
                (  year%4==0 ) )
            {
                ndays = 29;
            }
        }

        if ((day > ndays) || (day == 0))
        {
            return RLT_ERR_INVALID_DATA; /* 1: Invalid */
        }
    }

    /* Check day of week */
    if (dweek != RTC_NOT_SPECIFIED)
    {
		if ((dweek == 0) || (dweek > 7))
		{
			return RLT_ERR_INVALID_DATA; /* 1: Invalid */
		}
        weekday = R_DLMS_RTC_wday(year, month, day);
        if (dweek != weekday)
        {
            return RLT_ERR_INVALID_DATA; /* 1: Invalid */
        }
    }
    /*==============================================*/
    return RLT_SUCCESS; // 0: Valid
}

/******************************************************************************
* Function Name : R_OBIS_IsValidTime
* Interface     : uint8_t R_OBIS_IsValidTime(
*               :     uint8_t *p_time,
*               : );
* Description   : Check valid date time or not
* Arguments     : uint8_t *p_time
* Function Calls: None
* Return Value  : uint8_t, 0: invalid, 1 : valid
******************************************************************************/
uint8_t R_DLMS_IsValidTime(time_t *p_time)
{
    if (p_time->hour > 23 && p_time->hour < RTC_NOT_SPECIFIED) // hour
    {
        return RLT_ERR_INVALID_DATA; /* 1: Invalid */
    }

    if (p_time->minute > 59 && p_time->minute < RTC_NOT_SPECIFIED) // minute
    {
        return RLT_ERR_INVALID_DATA; /* 1: Invalid */
    }
    if (p_time->second > 59 && p_time->second < RTC_NOT_SPECIFIED) // second
    {
        return RLT_ERR_INVALID_DATA; /* 1: Invalid */
    }

    if (p_time->hundredths > 99 && p_time->hundredths < RTC_NOT_SPECIFIED) // hundred
    {
        return RLT_ERR_INVALID_DATA; /* 1: Invalid */
    }
    return RLT_SUCCESS; // 0: Valid
}


/******************************************************************************
* Function Name : R_DLMS_IsValidDateTime
* Interface     : void R_DLMS_IsValidDateTime(
*               :     date_time_t *p_date_time
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_IsValidDateTime (
    date_time_t *p_date_time
)
{
    date_t r_date;
    time_t r_time;
    uint8_t deviation_high, deviation_low;
    int16_t deviation;
	rtc_status_t	status;

    r_date.year_high = p_date_time->year_high;
    r_date.year_low = p_date_time->year_low;
    r_date.month = p_date_time->month;
    r_date.day_of_month = p_date_time->day_of_month;
    r_date.day_of_week = p_date_time->day_of_week;

    r_time.hour = p_date_time->hour;
    r_time.minute = p_date_time->minute;
    r_time.second = p_date_time->second;
    r_time.hundredths = p_date_time->hundredths;

    if (R_DLMS_IsValidDate(&r_date) != RLT_SUCCESS)
    {
        return RLT_ERR_INVALID_DATA; /* Invalid */
    }

    if (R_DLMS_IsValidTime(&r_time) != RLT_SUCCESS)
    {
        return RLT_ERR_INVALID_DATA; /* Invalid */
    }

    deviation = (int16_t)COMBINE_U16(p_date_time->deviation_high, p_date_time->deviation_low);
	if (R_DLMS_IsValidTimeZone ( deviation ) != R_DATE_TIME_VALID)
	{
        return RLT_ERR_INVALID_DATA;   // Invalid
	}

	status.byte = p_date_time->clock_status;
	// if (status.bits.invalid == 1)
	// {
	// 	return RLT_ERR_INVALID_DATA;	/* Invalid */
	// }

    return R_DATE_TIME_VALID; /* Valid */
}


/******************************************************************************
* Function Name : R_DLMS_NumberDayOfMonth
* Interface     : void R_DLMS_NumberDayOfMonth(
*               :     uint8_t month, uint16_t year
*               : );
* Description   : Get the number of days in a month
* Arguments     : uint8_t month, uint16_t year
* Function Calls: 
* Return Value  : The number of days in a month
******************************************************************************/
uint8_t R_DLMS_NumberDayOfMonth (
    uint8_t month, uint16_t year
)
{
    /* Check day and month */
    uint8_t ndays = nDayOfMonth[month];
    if (month==2)
    {
        if ( ( (year%100==0) && (year%400==0) ) ||
            (  year%4==0 ) )
        {
            ndays = 29;
        }
    }
    return ndays;
}




/******************************************************************************
* Function Name : R_OBIS_RTC_Alarm_InterrruptCallback
* Interface     : void R_OBIS_RTC_Alarm_InterrruptCallback(void)
* Description   : RTC alarm interrup callback for single action schedule
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_DLMS_Alarm_InterrruptCallback(void)
{
    /* Update flag to start push */
    // R_DLMS_Push_SetFlag(PUSH_ID_0);
}


/******************************************************************************
* Function Name : R_DLMS_RTC_Get_Params
* Interface     : date_time_params_t * R_DLMS_RTC_Get_Params(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
date_time_params_t * R_DLMS_RTC_Get_Params ( void )
{
    return &g_DLMS_RTC_params;
}

/******************************************************************************
* Function Name : R_DLMS_DateTime_Exec
* Interface     : void R_DLMS_DateTime_Exec(
*               :     date_flag_t pchangeFlg
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_RTC_Checking (
    date_time_params_t * params
)
{
    uint8_t sched;      /* Scheduler */

    uint32_t timeout;

    uint32_t bl_period;

    /* The default format is HH:MM */

    timeout = (params->date_time.current.Hour * 60 ) + params->date_time.current.Min;

    /* =================== */

    /* B. Load survey profile -------------------------------------------------- */
    // 1. Min is changed.

	R_DLMS_Scheduler_OnDateTimeChanged_CallBack(&params->date_time.current, &params->change_flag);

    /* ==================== */
    /* Clear all flag */
    // params->change_flag.bytes = 0;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_OldTime_Restore
* Interface     : void R_DLMS_RTC_OldTime_Restore(
*               :     R_DLMS_RTC_T * p_old_time
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_RTC_OldTime_Restore ( R_DLMS_RTC_T * p_old_time )
{
	E2PR_READ(
		STORAGE_EEPROM_DLMS_OLD_TIME_ADDR,
		(uint8_t *)p_old_time,
		sizeof(R_DLMS_RTC_T)
	);
}

/******************************************************************************
* Function Name : R_DLMS_RTC_OldTime_Restore
* Interface     : void R_DLMS_RTC_OldTime_Restore(
*               :     R_DLMS_RTC_T * p_old_time
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_RTC_OldTime_Backup ( R_DLMS_RTC_T * p_old_time )
{
	E2PR_WRITE(
		STORAGE_EEPROM_DLMS_OLD_TIME_ADDR,
		(uint8_t *)p_old_time,
		sizeof(R_DLMS_RTC_T)
	);
}


/******************************************************************************
* Function Name : R_DLMS_RTC_Get_TimeProfile
* Interface     : void R_DLMS_RTC_Get_TimeProfile(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
date_time_params_t * R_DLMS_RTC_Get_TimeProfile ( void )
{
	return &g_DLMS_RTC_params;
}

/******************************************************************************
* Function Name : R_DLMS_RTC_Init
* Interface     : void R_DLMS_RTC_Init(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_RTC_Init ( void )
{

}

/******************************************************************************
* Function Name : R_DLMS_Event_Polling
* Interface     : void R_DLMS_Event_Polling(
*               :     void
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_RTC_PollingProcessing(void)
{   

}

/******************************************************************************
* Function Name : R_DLMS_RTC_Restore
* Interface     : void R_DLMS_RTC_Restore(
*               :     void
*               : );
* Description   : This function load data from storage to RAM, need to register in restore of DLMS storage
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_RTC_Restore(void)
{
	/* Time zone */
	R_DLMS_EEPROM_Read(storage_info_time_zone, (uint8_t *)&g_time_zone);
	/* Clock status */
	R_DLMS_EEPROM_Read(storage_info_clock_status, (uint8_t *)&g_clock_status);
}
/******************************************************************************
* Function Name : R_DLMS_RTC_Backup
* Interface     : void R_DLMS_RTC_Backup(
*               :     void
*               : );
* Description   : store data from RAM to storage
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_RTC_Backup(void)
{
	/* Time zone */
	R_DLMS_EEPROM_Write(storage_info_time_zone, (uint8_t *)&g_time_zone);
	/* Clock status */
	R_DLMS_EEPROM_Write(storage_info_clock_status, (uint8_t *)&g_clock_status);

}

/******************************************************************************
* Function Name : R_DLMS_RTC_Format
* Interface     : void R_DLMS_RTC_Format(
*               :     void
*               : );
* Description   : format data, write default data to storage.
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_RTC_Format(void)
{
	/* Time zone */
	R_DLMS_EEPROM_Write(storage_info_time_zone, (uint8_t *)&g_dlms_timezone_default);
}