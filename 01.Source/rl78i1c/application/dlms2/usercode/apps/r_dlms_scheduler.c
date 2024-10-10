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
* File Name    : r_dlms_scheduler.c
* Version      : v1.0
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : <Description of file>
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 2018-05-09 10:45:13 New Created

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "typedef.h"

#include "r_dlms_app.h"
#include "r_dlms_scheduler.h"
#include "r_dlms_storage.h"
#include "r_dlms_script.h"

#include <string.h>
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
r_dlms_scheduler_t		g_schedule[MAX_SCHEDULER_NUMBER];

const uint16_t          g_exe_flag_init[] = { 
            0x0000 | RTC_BIT_MONTH | RTC_BIT_DAY | RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND,      // YEAR
            0x0000 | RTC_BIT_DAY | RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND,                      // MONTH
            0x0000 | RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND,                                    // WEEK
            0x0000 | RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND,                                    // DAY
            0x0000 | RTC_BIT_MINUTE | RTC_BIT_SECOND,                                                   // HOUR
            0x0000 | RTC_BIT_SECOND,                                                                    // MINUTE
};
const uint8_t g_exe_flag_init_length = sizeof(g_exe_flag_init) / sizeof(uint16_t);

datetime_compare_result_t R_DLMS_Scheduler_CompareYear (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
);

datetime_compare_result_t R_DLMS_Scheduler_CompareMonth (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
);

datetime_compare_result_t R_DLMS_Scheduler_CompareDay (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
);

datetime_compare_result_t R_DLMS_Scheduler_CompareHour (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
);

datetime_compare_result_t R_DLMS_Scheduler_CompareMinute (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
);

datetime_compare_result_t R_DLMS_Scheduler_CompareSecond (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
);

#if(defined( R_DLMS_APPS_SCHEDULER_ENABLE ) && R_DLMS_APPS_SCHEDULER_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_Scheduler_BackupDateTime
* Interface     : void R_DLMS_Scheduler_BackupDateTime(
*               :     date_t *p_date, time_t *p_time
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Scheduler_Backup (
	uint8_t index,
	R_DLMS_RTC_T *p_date_time,
	uint16_t exe_flag
)
{
	uint8_t rlt = RLT_SUCCESS;  // Default is OK

	uint32_t addr;
	uint32_t size;

	// Backup with index
	{
		addr = STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR + (sizeof(R_DLMS_RTC_T) * index);
		rlt = E2PR_WRITE(
			addr,
			(uint8_t *)p_date_time,
			sizeof(R_DLMS_RTC_T)
		);
		addr = STORAGE_EEPROM_SCHEDULER_SAS_EXECUTION_FLAG_ADDR + (sizeof(uint16_t) * index);
		rlt = E2PR_WRITE(
			addr,
			(uint8_t *)&exe_flag,
			sizeof(uint16_t)
		);
	}

	return rlt;
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_Restore
* Interface     : void R_DLMS_Scheduler_BackupDateTime(
*               :     date_t *p_date, time_t *p_time
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Scheduler_Restore (
	uint8_t scheduler_id,
	R_DLMS_RTC_T * p_rtc,
	uint16_t *p_execute_flag
)
{
    uint8_t rlt = RLT_SUCCESS;  // Default is OK

    uint32_t addr;
    uint32_t size;

    if ((p_rtc == NULL) ||
		(p_execute_flag == NULL))
    {
        return RLT_ERR; /* NG */
    }

    // Restore with index
    {
        addr = STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR + (sizeof(R_DLMS_RTC_T) * scheduler_id);
        rlt = E2PR_READ(
            addr,
            (uint8_t *)p_rtc,
            sizeof(R_DLMS_RTC_T)
        );
        addr = STORAGE_EEPROM_SCHEDULER_SAS_EXECUTION_FLAG_ADDR + (sizeof(uint16_t) * scheduler_id);
        rlt = E2PR_READ(
            addr,
            (uint8_t *)p_execute_flag,
            sizeof(uint16_t)
        );
    }

    return rlt;
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_GetInfo
* Interface     : r_dlms_scheduler_t *  R_DLMS_Scheduler_GetInfo(
*               :     uint8_t scheduler_id
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
r_dlms_scheduler_t * R_DLMS_Scheduler_GetInfo (uint8_t scheduler_id)
{
	if (scheduler_id < MAX_SCHEDULER_NUMBER)
	{
		return &g_schedule[scheduler_id];
	}
	else
	{
		return NULL;
	}
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_Ack_Executing
* Interface     : void R_DLMS_Scheduler_Ack_Executing(
*               :     uint8_t scheduler_id
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_Scheduler_Ack_Executing(uint8_t schedule_id)
{
	date_time_params_t *p_profile = R_DLMS_RTC_Get_TimeProfile();
	r_dlms_scheduler_t *p_scheduler;
	if (schedule_id >= MAX_SCHEDULER_NUMBER)
	{
		return;
	}
    p_scheduler = &g_schedule[schedule_id];

	R_DLMS_Scheduler_Backup(schedule_id, &p_scheduler->rtc, p_scheduler->flag.bytes);
	R_DLMS_RTC_OldTime_Backup(&p_profile->date_time.current);
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_Rewrite_Ack
* Interface     : void R_DLMS_Scheduler_Rewrite_Ack(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_Scheduler_Rewrite_Ack ( uint8_t schedule_id )
{
    uint8_t i;

    for (i = sizeof(R_DLMS_RTC_T) - 1; i > 0; i--)
    {
        if ( *((uint8_t *)&g_schedule[schedule_id].rtc + i) != 0xFF)
        {
            if ( (6-i) < g_exe_flag_init_length)
            {
                g_schedule[schedule_id].flag.bytes = g_exe_flag_init[6 - i];
            }
            break;
        }
    }
    R_DLMS_Scheduler_Backup(schedule_id, &g_schedule[schedule_id].rtc, g_schedule[schedule_id].flag.bytes);
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_UpdateExecutionFlag
* Interface     : rtc_flag_t R_DLMS_Scheduler_UpdateExecutionFlag(
*               :     uint8_t schedule_id, R_DLMS_RTC_T *p_rtc
*               : );
* Description   :
* Arguments     :
* Return Value  : rtc_flag_t
******************************************************************************/
rtc_flag_t R_DLMS_Scheduler_UpdateExecutionFlag(uint8_t schedule_id, R_DLMS_RTC_T *p_rtc_scheduler)
{
	rtc_flag_t return_flag;
	rtc_flag_t change_flag;

	R_DLMS_RTC_T virtual_time;

	date_time_params_t *p_current_time;

	uint8_t compare_scheduler_result;

	return_flag.bytes = 0;

	if 	((g_schedule == NULL)  ||
		( schedule_id >= MAX_SCHEDULER_NUMBER ))
	{
		return return_flag;
	}

	memset((uint8_t *)&change_flag, 0xFF, sizeof(rtc_flag_t));

	compare_scheduler_result = R_DLMS_RTC_Compare((uint8_t *)p_rtc_scheduler, (uint8_t *)&(g_schedule[schedule_id].rtc));

	if ( compare_scheduler_result == 0)
	{
		return g_schedule[schedule_id].flag;
	}
	else
	{
		p_current_time = R_DLMS_RTC_Get_TimeProfile();
		
		if (R_DLMS_Scheduler_Check(
			p_rtc_scheduler,
			&p_current_time->date_time.current,
			&change_flag,
			&return_flag
		) == TRUE)
		{
			/* TODO: Execution Script */
			memcpy(&(g_schedule[schedule_id].rtc), p_rtc_scheduler , sizeof(R_DLMS_RTC_T));
			R_DLMS_Script_Execute(g_schedule[schedule_id].script_id);
			R_DLMS_Scheduler_Ack_Executing(schedule_id);
		}
	
		g_schedule[schedule_id].flag.bytes = return_flag.bytes;
	}

	return return_flag;
}

/******************************************************************************
* Function Name : R_DLMS_Sched_Init
* Interface     : void R_DLMS_Sched_Init(
*               :     void
*               : );
* Description   : Restore all scheduler data
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_Scheduler_Create (uint8_t schedule_id, R_DLMS_RTC_T *p_rtc, uint16_t script_id, uint16_t execute_flag)
{
	uint8_t rlt = RLT_SUCCESS;
	rtc_flag_t flag;
	R_DLMS_RTC_T current_clock;

	if 	((g_schedule == NULL)  ||
		( schedule_id >= MAX_SCHEDULER_NUMBER ))
	{
		return RLT_ERR; /* Invalid */
	}

	memcpy(&(g_schedule[schedule_id].rtc), p_rtc , sizeof(R_DLMS_RTC_T));

	g_schedule[schedule_id].flag.bytes = execute_flag;
	g_schedule[schedule_id].script_id = script_id;
	g_schedule[schedule_id].enable = TRUE;

	if ((g_schedule[schedule_id].rtc.Year < 18) ||
		(script_id == 0xFFFF))
	{
		g_schedule[schedule_id].enable = FALSE;
	}

	if ((g_schedule[schedule_id].rtc.Year  == 0xFF) && 
		(g_schedule[schedule_id].rtc.Month == 0xFF) && 
		(g_schedule[schedule_id].rtc.Day   == 0xFF) &&
		(g_schedule[schedule_id].rtc.Hour  == 0xFF) &&
		(g_schedule[schedule_id].rtc.Min   == 0xFF) &&
		(g_schedule[schedule_id].rtc.Sec   == 0xFF) )
	{
		g_schedule[schedule_id].enable = FALSE;
	}

	//R_DLMS_RTC_Get_Drv_DateTime(&current_clock);
	//flag.bytes = 0xFF;
	//R_DLMS_Scheduler_OnDateTimeChanged_CallBack(&current_clock, &flag);

	return rlt;// OK
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_Check
* Interface     : void R_DLMS_Scheduler_Check(
*               :     R_DLMS_RTC_T * p_date, 
*               :     R_DLMS_RTC_T * p_current_time,
*               :     rtc_flag_t * p_clock_changed_flag,
*               :     rtc_flag_t * p_exe_flag
*               : );
* Description   : 
* Arguments     : R_DLMS_RTC_T * p_date;                [Input]         Scheduler date time. It's may include wildcard.
*               : R_DLMS_RTC_T * p_current_time;        [Input]         RTC date. All fields are explicitly specified.
*               : rtc_flag_t * p_clock_changed_flag;    [Input]         RTC changed event, It's flag from system RTC.
*               : rtc_flag_t * p_exe_flag               [Input/Output]  Flag indicate action is executed.
* Function Calls: 
* Return Value  : Date time compare result
*               :     DT_CPM_RESULT_EARLY,          DateTime compare result: Early
*               :     DT_CPM_RESULT_ON_SCHEDULE,    Datetime compare reso
******************************************************************************/
datetime_compare_result_t R_DLMS_Scheduler_Check (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
)
{
    return R_DLMS_Scheduler_CompareYear (p_date, p_current_time, p_clock_changed_flag, p_exe_flag);
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_CompareYear
* Interface     : void R_DLMS_Scheduler_CompareYear(
*               :     R_DLMS_RTC_T * p_date, 
*               :     R_DLMS_RTC_T * p_current_time,
*               :     rtc_flag_t * p_clock_changed_flag,
*               :     rtc_flag_t * p_exe_flag
*               : );
* Description   : 
* Arguments     : R_DLMS_RTC_T * p_date;                [Input]         Scheduler date time. It's may include wildcard.
*               : R_DLMS_RTC_T * p_current_time;        [Input]         RTC date. All fields are explicitly specified.
*               : rtc_flag_t * p_clock_changed_flag;    [Input]         RTC changed event, It's flag from system RTC.
*               : rtc_flag_t * p_exe_flag               [Input/Output]  Flag indicate action is executed.
* Function Calls: 
* Return Value  : Date time compare result
*               :     DT_CPM_RESULT_EARLY,          DateTime compare result: Early
*               :     DT_CPM_RESULT_ON_SCHEDULE,    Datetime compare reso
******************************************************************************/
datetime_compare_result_t R_DLMS_Scheduler_CompareYear (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
)
{
    if (p_clock_changed_flag->bits.year == 1)
    {
        if (p_date->Year == RTC_NOT_SPECIFIED)
        {
            p_exe_flag->bytes &= (0x0000 | RTC_BIT_YEAR);
            if (p_exe_flag->bits.year == 0)
            {
                return R_DLMS_Scheduler_CompareMonth (p_date, p_current_time, p_clock_changed_flag, p_exe_flag);
            }
        }
        else if (p_exe_flag->bits.year == 0)
        {
            if (p_date->Year > p_current_time->Year)
            { 
                /* STOP */
                p_exe_flag->bytes = ~(RTC_BIT_YEAR | 0x0000);
                return DT_CPM_RESULT_EARLY;
            }
            else
            {   
                /* START */
                p_exe_flag->bytes = (RTC_BIT_YEAR | 0x0000);
                if (p_date->Year < p_current_time->Year)
                {
                    p_exe_flag->bytes = 0xFFFF;
                    return DT_CPM_RESULT_ON_SCHEDULE;
                }
            }
        }
    }

    return R_DLMS_Scheduler_CompareMonth (p_date, p_current_time, p_clock_changed_flag, p_exe_flag);
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_CompareMonth
* Interface     : void R_DLMS_Scheduler_CompareMonth(
*               :     R_DLMS_RTC_T * p_date, 
*               :     R_DLMS_RTC_T * p_current_time,
*               :     rtc_flag_t * p_clock_changed_flag,
*               :     rtc_flag_t * p_exe_flag
*               : );
* Description   : 
* Arguments     : R_DLMS_RTC_T * p_date;                [Input]         Scheduler date time. It's may include wildcard.
*               : R_DLMS_RTC_T * p_current_time;        [Input]         RTC date. All fields are explicitly specified.
*               : rtc_flag_t * p_clock_changed_flag;    [Input]         RTC changed event, It's flag from system RTC.
*               : rtc_flag_t * p_exe_flag               [Input/Output]  Flag indicate action is executed.
* Function Calls: 
* Return Value  : Date time compare result
*               :     DT_CPM_RESULT_EARLY,          DateTime compare result: Early
*               :     DT_CPM_RESULT_ON_SCHEDULE,    Datetime compare reso
******************************************************************************/
datetime_compare_result_t R_DLMS_Scheduler_CompareMonth (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
)
{
    if (p_clock_changed_flag->bits.month == 1)
    {
        if (p_date->Month == RTC_NOT_SPECIFIED)
        {
            /* PASS ALL NEXT STEP */
            p_exe_flag->bytes &= ~(RTC_BIT_DAY | RTC_BIT_WEEK | RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND);
            if (p_exe_flag->bits.month == 0)
            {
                return R_DLMS_Scheduler_CompareDay(p_date, p_current_time, p_clock_changed_flag, p_exe_flag);;
            }
        }
        else if (p_exe_flag->bits.month == 0)
        {
            if (p_date->Month > p_current_time->Month)
            {
                /* STOP */
                p_exe_flag->bytes |= (RTC_BIT_DAY | RTC_BIT_WEEK | RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND);
                return DT_CPM_RESULT_EARLY;
            }
            else 
            {   
                /* START */
                p_exe_flag->bytes &= ~ (RTC_BIT_MONTH |RTC_BIT_DAY | RTC_BIT_WEEK | RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND);
                p_exe_flag->bits.month = 1;
                if (p_date->Month < p_current_time->Month)
                {
                    p_exe_flag->bytes |= (RTC_BIT_DAY | RTC_BIT_WEEK | RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND);
                    return DT_CPM_RESULT_ON_SCHEDULE;
                }
            }
        }
    }
    return R_DLMS_Scheduler_CompareDay(p_date, p_current_time, p_clock_changed_flag, p_exe_flag);
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_CompareDay
* Interface     : void R_DLMS_Scheduler_CompareDay(
*               :     R_DLMS_RTC_T * p_date, 
*               :     R_DLMS_RTC_T * p_current_time,
*               :     rtc_flag_t * p_clock_changed_flag,
*               :     rtc_flag_t * p_exe_flag
*               : );
* Description   : 
* Arguments     : R_DLMS_RTC_T * p_date;                [Input]         Scheduler date time. It's may include wildcard.
*               : R_DLMS_RTC_T * p_current_time;        [Input]         RTC date. All fields are explicitly specified.
*               : rtc_flag_t * p_clock_changed_flag;    [Input]         RTC changed event, It's flag from system RTC.
*               : rtc_flag_t * p_exe_flag               [Input/Output]  Flag indicate action is executed.
* Function Calls: 
* Return Value  : Date time compare result
*               :     DT_CPM_RESULT_EARLY,          DateTime compare result: Early
*               :     DT_CPM_RESULT_ON_SCHEDULE,    Datetime compare reso
******************************************************************************/
datetime_compare_result_t R_DLMS_Scheduler_CompareDay (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
)
{
    uint8_t ndays;
    uint8_t last_day;

    if (p_clock_changed_flag->bits.day == 1)
    {
        if (p_date->Day == RTC_NOT_SPECIFIED)
        {
            /* PASS ALL NEXT STEP */
            p_exe_flag->bytes &= ~( RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND);
            if (p_exe_flag->bits.day == 0)
            {
                return R_DLMS_Scheduler_CompareHour (p_date, p_current_time, p_clock_changed_flag, p_exe_flag);;
            }
        }
        else if (p_date->Day == RTC_DAY_LAST_OF_MONTH)
        {
            if (p_date->Week == RTC_NOT_SPECIFIED)
            {
                /* Case 1: The last calendar day of the month */
                ndays = R_DLMS_NumberDayOfMonth(p_current_time->Month, p_current_time->Year);
                if (p_date->Day == ndays)
                {
                    p_exe_flag->bits.hour = 0;
                    p_exe_flag->bits.minute = 0;
                    p_exe_flag->bits.second = 0;
                }
            }
            else if (p_date->Week <= RTC_WEEK_SUN)
            {
                /* Case 2: The last occurrence of the weekday specified in the month */
                if (p_date->Day == p_current_time->Day)
                {
                    last_day = p_current_time->Day + 7;
                    ndays = R_DLMS_NumberDayOfMonth(p_current_time->Month, p_current_time->Year);
                    if (last_day > ndays)
                    {
                        p_exe_flag->bits.hour = 0;
                        p_exe_flag->bits.minute = 0;
                        p_exe_flag->bits.second = 0;
                    }
                }
            }
        }
        else if (p_exe_flag->bits.day == 0)
        {
            if (p_date->Day > p_current_time->Day)
            {
                /* STOP */
                p_exe_flag->bytes |= (RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND);
                return DT_CPM_RESULT_EARLY;
            }
            else
            {
                /* START */
                p_exe_flag->bytes &= ~(RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND);
                p_exe_flag->bits.day = 1;
                if (p_date->Day < p_current_time->Day)
                {
                    p_exe_flag->bytes |= (RTC_BIT_HOUR | RTC_BIT_MINUTE | RTC_BIT_SECOND);
                    return DT_CPM_RESULT_ON_SCHEDULE;
                }
            }
        }
    }
    return R_DLMS_Scheduler_CompareHour (p_date, p_current_time, p_clock_changed_flag, p_exe_flag);
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_CompareHour
* Interface     : void R_DLMS_Scheduler_CompareHour(
*               :     R_DLMS_RTC_T * p_date, 
*               :     R_DLMS_RTC_T * p_current_time,
*               :     rtc_flag_t * p_clock_changed_flag,
*               :     rtc_flag_t * p_exe_flag
*               : );
* Description   : 
* Arguments     : R_DLMS_RTC_T * p_date;                [Input]         Scheduler date time. It's may include wildcard.
*               : R_DLMS_RTC_T * p_current_time;        [Input]         RTC date. All fields are explicitly specified.
*               : rtc_flag_t * p_clock_changed_flag;    [Input]         RTC changed event, It's flag from system RTC.
*               : rtc_flag_t * p_exe_flag               [Input/Output]  Flag indicate action is executed.
* Function Calls: 
* Return Value  : Date time compare result
*               :     DT_CPM_RESULT_EARLY,          DateTime compare result: Early
*               :     DT_CPM_RESULT_ON_SCHEDULE,    Datetime compare reso
******************************************************************************/
datetime_compare_result_t R_DLMS_Scheduler_CompareHour (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
)
{
    if (p_clock_changed_flag->bits.hour == 1)
    {
        if ((p_date->Hour == RTC_NOT_SPECIFIED))
        {
            p_exe_flag->bits.second = 0;
            p_exe_flag->bits.minute = 0;
            if (p_exe_flag->bits.hour == 0)
            {
                return R_DLMS_Scheduler_CompareMinute (p_date, p_current_time, p_clock_changed_flag, p_exe_flag);;
            }
        }
        else if (p_exe_flag->bits.hour == 0)
        {
            if (p_date->Hour > p_current_time->Hour)
            {
                /* STOP */
                p_exe_flag->bits.minute = 1;
                p_exe_flag->bits.second = 1;
                return DT_CPM_RESULT_EARLY;
            }
            else
            {
                /* START */
                p_exe_flag->bits.hour = 1;
                p_exe_flag->bits.minute = 0;
                p_exe_flag->bits.second = 0;
                if (p_date->Hour < p_current_time->Hour)
                {
                    p_exe_flag->bits.minute = 1;
                    p_exe_flag->bits.second = 1;
                    return DT_CPM_RESULT_ON_SCHEDULE;
                }
            }
        }
    }
    return R_DLMS_Scheduler_CompareMinute (p_date, p_current_time, p_clock_changed_flag, p_exe_flag);
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_CompareMinute
* Interface     : void R_DLMS_Scheduler_CompareMinute(
*               :     R_DLMS_RTC_T * p_date, 
*               :     R_DLMS_RTC_T * p_current_time,
*               :     rtc_flag_t * p_clock_changed_flag,
*               :     rtc_flag_t * p_exe_flag
*               : );
* Description   : 
* Arguments     : R_DLMS_RTC_T * p_date;                [Input]         Scheduler date time. It's may include wildcard.
*               : R_DLMS_RTC_T * p_current_time;        [Input]         RTC date. All fields are explicitly specified.
*               : rtc_flag_t * p_clock_changed_flag;    [Input]         RTC changed event, It's flag from system RTC.
*               : rtc_flag_t * p_exe_flag               [Input/Output]  Flag indicate action is executed.
* Function Calls: 
* Return Value  : Date time compare result
*               :     DT_CPM_RESULT_EARLY,          DateTime compare result: Early
*               :     DT_CPM_RESULT_ON_SCHEDULE,    Datetime compare reso
******************************************************************************/
datetime_compare_result_t R_DLMS_Scheduler_CompareMinute (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
)
{
    if (p_clock_changed_flag->bits.minute == 1)
    {
        if (p_date->Min == RTC_NOT_SPECIFIED)
        {
            p_exe_flag->bits.second = 0;
            if (p_exe_flag->bits.minute == 0)
            {
                return R_DLMS_Scheduler_CompareSecond (p_date, p_current_time, p_clock_changed_flag, p_exe_flag);;
            }
        }
        else if (p_exe_flag->bits.minute == 0)
        {
            if (p_date->Min > p_current_time->Min)
            {
                /* STOP */
                p_exe_flag->bits.second = 1;
                return DT_CPM_RESULT_EARLY;
            }
            else
            {
                /* START */
                p_exe_flag->bits.minute = 1;
                p_exe_flag->bits.second = 0;
                if (p_date->Min < p_current_time->Min)
                {
                    p_exe_flag->bits.second = 1;
                    return DT_CPM_RESULT_ON_SCHEDULE;
                }
            }
        }
    }
    return R_DLMS_Scheduler_CompareSecond (p_date, p_current_time, p_clock_changed_flag, p_exe_flag);
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_CompareSecond
* Interface     : void R_DLMS_Scheduler_CompareSecond(
*               :     R_DLMS_RTC_T * p_date, 
*               :     R_DLMS_RTC_T * p_current_time,
*               :     rtc_flag_t * p_clock_changed_flag,
*               :     rtc_flag_t * p_exe_flag
*               : );
* Description   : 
* Arguments     : R_DLMS_RTC_T * p_date;                [Input]         Scheduler date time. It's may include wildcard.
*               : R_DLMS_RTC_T * p_current_time;        [Input]         RTC date. All fields are explicitly specified.
*               : rtc_flag_t * p_clock_changed_flag;    [Input]         RTC changed event, It's flag from system RTC.
*               : rtc_flag_t * p_exe_flag               [Input/Output]  Flag indicate action is executed.
* Function Calls: 
* Return Value  : Date time compare result
*               :     DT_CPM_RESULT_EARLY,          DateTime compare result: Early
*               :     DT_CPM_RESULT_ON_SCHEDULE,    Datetime compare reso
******************************************************************************/
datetime_compare_result_t R_DLMS_Scheduler_CompareSecond (
	R_DLMS_RTC_T * p_date,
	R_DLMS_RTC_T * p_current_time,
    rtc_flag_t * p_clock_changed_flag,
    rtc_flag_t * p_exe_flag
)
{
    /* SEC */
    if ((p_clock_changed_flag->bits.second == 1) && (p_exe_flag->bits.second == 0))
    {
        if (p_date->Sec == RTC_NOT_SPECIFIED)
        {
            return DT_CPM_RESULT_ON_SCHEDULE;
        }
        if (p_date->Sec > p_current_time->Sec)
        {
            return DT_CPM_RESULT_EARLY;
        }
        else
        {
            p_exe_flag->bits.second = 1;
            return DT_CPM_RESULT_ON_SCHEDULE;
        }
    }

    /* Return OK */
    return DT_CPM_RESULT_EARLY;
}

/******************************************************************************
* Function Name : R_DLMS_Scheduler_OnDateTimeChanged_CallBack
* Interface     : void R_DLMS_Scheduler_OnDateTimeChanged_CallBack(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_Scheduler_OnDateTimeChanged_CallBack ( R_DLMS_RTC_T *p_current_time, rtc_flag_t * p_rtc_changed_flag )
{
	uint8_t schedule_id;
	datetime_compare_result_t check_result;
	uint16_t old_flag_value;

#if(defined( R_DLMS_USE_ASYNCHRONOUS_BILLING_MECHANISM ) && R_DLMS_USE_ASYNCHRONOUS_BILLING_MECHANISM == TRUE)
	/* Billing scheduler is now controlled by r_dlms_datalog.c */
	if (g_schedule[R_DLMS_SCHEUDLER_ID_BILLING].enable == TRUE)
	{
		g_schedule[R_DLMS_SCHEUDLER_ID_BILLING].enable = FALSE;
	}
#endif /* R_DLMS_USE_ASYNCHRONOUS_BILLING_MECHANISM */

	for ( schedule_id = 0 ; schedule_id < MAX_SCHEDULER_NUMBER; schedule_id++)
	{
		if ((g_schedule[schedule_id].enable == TRUE) && (p_current_time->Month != 0))
		{
			old_flag_value = g_schedule[schedule_id].flag.bytes | RTC_BIT_SECOND;
			check_result = R_DLMS_Scheduler_Check(
					&g_schedule[schedule_id].rtc, 
					p_current_time, 
					p_rtc_changed_flag, 
					&g_schedule[schedule_id].flag
				);
			if (old_flag_value != (g_schedule[schedule_id].flag.bytes | RTC_BIT_SECOND))
			{
				R_DLMS_Scheduler_Backup(schedule_id, &g_schedule[schedule_id].rtc, g_schedule[schedule_id].flag.bytes);
			}
			if (check_result == TRUE)
			{
				/* TODO: Execution Script */
				R_DLMS_Script_Execute(g_schedule[schedule_id].script_id);
				R_DLMS_Scheduler_Ack_Executing(schedule_id);
			}
		}
	}
}

#endif