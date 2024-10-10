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
* File Name    : r_scheduler.c
* Version      : <Version>
* Device(s)    : <'RL78/I1C'>
* Tool-Chain   : <'CCRL'>
* H/W Platform : <'RL78/I1C Energy Meter Platform'>
* Description  : <Description of file>
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Drivers */
#include "r_cg_macrodriver.h"

/* EM */
#include "em_type.h"

/* Meter application */
#include "platform.h"
#include "r_scheduler.h"
#include "inst_read.h"
#include "r_meter_format.h"

/* Standard library */
#include <string.h>
#include "storage.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#define LCD_DELAY_TIME                                  (5)      /* Create delay time 5s */

/* Compute total minutes passed in a day */
#define TOTAL_MIN_PASSED_IN_DAY(hour, min)              (((uint16_t)hour * 60) + (min))
#define TOTAL_MIN_OFFSET_IN_DAY(hour, min)              (((uint16_t)hour * 60) + (min))

#if 1
    /* Get element from rtc_counter_value_t */
    #define GET_HOUR(p_rtc)         ((p_rtc)->hour)
    #define GET_MIN(p_rtc)          ((p_rtc)->min)
    #define GET_SEC(p_rtc)          ((p_rtc)->sec)
    #define GET_YEAR(p_rtc)         ((p_rtc)->year)
    #define GET_MONTH(p_rtc)        ((p_rtc)->month)
    #define GET_DAY(p_rtc)          ((p_rtc)->day)
    #define GET_WEEK(p_rtc)         ((p_rtc)->week)
#else
    #define GET_HOUR(p_rtc)         ((p_rtc)->rhrcnt)
    #define GET_MIN(p_rtc)          ((p_rtc)->rmincnt)
    #define GET_SEC(p_rtc)          ((p_rtc)->rseccnt)
    #define GET_YEAR(p_rtc)         ((p_rtc)->ryrcnt)
    #define GET_MONTH(p_rtc)        ((p_rtc)->rmtcnt)
    #define GET_DAY(p_rtc)          ((p_rtc)->rdaycnt)
    #define GET_WEEK(p_rtc)         ((p_rtc)->rwkcnt)
#endif

#define COPY_BACKUP_DATA(var1, var2)    {  \
                                            (var1).matched            = (var2).matched;    \
                                            (var1).number_of_exe_time = (var2).number_of_exe_time; \
                                            (var1).script_id          = (var2).script_id;  \
                                        }

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

const uint16_t g_exe_time_base_index[] = {
	START_SLOT_EXE_TIME_0,
	START_SLOT_EXE_TIME_1,
	START_SLOT_EXE_TIME_2,
	START_SLOT_EXE_TIME_3,
	START_SLOT_EXE_TIME_4,
	START_SLOT_EXE_TIME_5	
};

const uint16_t scheduler_exe_time_maximum_support[] = {
	SCHEDULE_EXE_TIME_MAX_SUPPORT_0,
	SCHEDULE_EXE_TIME_MAX_SUPPORT_1,
	SCHEDULE_EXE_TIME_MAX_SUPPORT_2,
	SCHEDULE_EXE_TIME_MAX_SUPPORT_3,
	SCHEDULE_EXE_TIME_MAX_SUPPORT_4,
	SCHEDULE_EXE_TIME_MAX_SUPPORT_5	
};

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

r_scheduler_flags_t g_scheduler_flags;

uint16_t g_demand_integration_period = SCHEDULER_DEFAULT_MAX_DEMAND_PERIOD;                  /* Max demand time of an intergration period. Unit: Minute */
const uint16_t g_fixed_interval_period = 15;                                                           /* Block load period.                         Unit: Minute */

/* Setting: sliding demand (>1, max 15) or block demand (=1) */
uint16_t g_demand_number_of_period = SCHEDULER_DEFAULT_MAX_DEMAND_NUM_OF_PERIOD;

r_scheduler_datetime_t g_scheduler_exe_time[SCHEDULE_EXECUTION_TIME_MAX_SUPPORT];

scheduler_match_context_t g_scheduler_match_context[MAX_SCHEDULER_NUMBER];

scheduler_t	g_scheduler[MAX_SCHEDULER_NUMBER] = 
{
  /* Matched, Number of scheduler time        , Script ID,   Scheduler datetime      */
    {  FALSE, SCHEDULE_EXE_TIME_MAX_SUPPORT_0 ,    1 ,    &g_scheduler_exe_time[START_SLOT_EXE_TIME_0]         },
    {  FALSE, SCHEDULE_EXE_TIME_MAX_SUPPORT_1 ,    2 ,    &g_scheduler_exe_time[START_SLOT_EXE_TIME_1]         },
    {  FALSE, SCHEDULE_EXE_TIME_MAX_SUPPORT_2 ,    3 ,    &g_scheduler_exe_time[START_SLOT_EXE_TIME_2]         },
    {  FALSE, SCHEDULE_EXE_TIME_MAX_SUPPORT_3 ,    4 ,    &g_scheduler_exe_time[START_SLOT_EXE_TIME_3]         },
    {  FALSE, SCHEDULE_EXE_TIME_MAX_SUPPORT_4 ,    5 ,    &g_scheduler_exe_time[START_SLOT_EXE_TIME_4]         },
    {  FALSE, SCHEDULE_EXE_TIME_MAX_SUPPORT_5 ,    6 ,    &g_scheduler_exe_time[START_SLOT_EXE_TIME_5]         },
    {  FALSE, SCHEDULE_EXE_TIME_MAX_SUPPORT_6 ,    6 ,    &g_scheduler_exe_time[START_SLOT_EXE_TIME_6]         },
};

static uint16_t g_lcd_display_count = 0;

const r_scheduler_datetime_t billing_schedule_default = {00, 00, 00, 1, 0xFF, 0xFF, 0xFF, 0xFF};
const r_scheduler_datetime_t common_schedule_default = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const r_scheduler_datetime_t tariff_exe_time_default[] =
{
	/* {Sec, Min, Hour, Day, Week, Month, Year, Reserved} */
	/* Default tariff slot 1 */
	{0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	/* Default tariff slot 2 */
	{0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	/* Default tariff slot 3 */
	{0x00, 0x00, 0x06, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	/* Default tariff slot 4 */
	{0x00, 0x00, 0x09, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	/* Default tariff slot 5 */
	{0x00, 0x00, 0x0C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	/* Default tariff slot 6 */
	{0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	/* Default tariff slot 7 */
	{0x00, 0x00, 0x12, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	/* Default tariff slot 8 */
	{0x00, 0x00, 0x15, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
};


/******************************************************************************
* Function Name: SCHEDULER_IsMDMPeriodChanged
* Description  : Scheduler checking Max Demand Period Is Changed Or Not
* Arguments    : rtc_counter_value_t *p_rtctime: RTC time from snapshot
* Return Value : uint8_t
*              :        1. Changed
*              :        0. No change
******************************************************************************/
static uint8_t SCHEDULER_IsMDMPeriodChanged(rtc_counter_value_t *p_rtctime)
{
    uint8_t     bChanged = 0;   /* Default is no change */
    uint16_t    rtc_time_frame, schedule_time_frame;

    if ( GET_SEC(p_rtctime) == 0 &&
         (GET_HOUR(p_rtctime) * 60 + GET_MIN(p_rtctime) ) % g_demand_integration_period == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************
* Function Name: static uint8_t ENERGY_BLOCKLOAD_IsPeriodChanged(ENERGY_RTC_DATE_TIME *rtctime)
* Description  : Scheduler checking Block load Is Changed Or Not           
* Arguments    : ENERGY_RTC_DATE_TIME *rtctime: RTC time from driver
* Return Value : uint8_t: period change status. 
*                               0: No change
*                               1: Change
******************************************************************************/
static uint8_t SCHEDULER_IsBlockloadPeriodChanged(rtc_counter_value_t *p_rtctime)
{
    if ( GET_SEC(p_rtctime) == 0 &&
         (GET_HOUR(p_rtctime) * 60 + GET_MIN(p_rtctime) ) % g_fixed_interval_period == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************
* Function Name: static uint8_t SCHEDULER_IsDailyLoadPeriodChanged(ENERGY_RTC_DATE_TIME *rtctime)
* Description  : Scheduler checking daily load           
* Arguments    : ENERGY_RTC_DATE_TIME *rtctime: RTC time from driver
* Return Value : uint8_t: period change status. 
*                               0: No change
*                               1: Change
******************************************************************************/
static uint8_t SCHEDULER_IsDailyLoadPeriodChanged(rtc_counter_value_t *p_rtctime)
{
    if ( GET_SEC(p_rtctime) == 0  &&
         GET_MIN(p_rtctime) == 0  &&
         GET_HOUR(p_rtctime) == 0
        )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}



uint8_t GetNumberDaysOfMonth(rtc_counter_value_t *p_rtc_value);
/******************************************************************************
* Function Name : GetNumberDaysOfMonth
* Interface     : uint8_t GetNumberDaysOfMonth(rtc_counter_value_t *p_rtc_value)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t GetNumberDaysOfMonth(rtc_counter_value_t *p_rtc_value)
{
    uint8_t	days = 0;	

    const uint8_t day_of_months[12] =
	{
		31,	/* Jan */
		28,	/* Feb, +1 if leap year */
		31,	/* Mar */
		30,	/* Apr */
		31,	/* May */
		30,	/* Jun */
		31,	/* Jul */
		31,	/* Aug */
		30,	/* Sep */
		31,	/* Oct */
		30,	/* Nov */
		31	/* Dec */
	};

    /*
	 * Get days of current month to check wildcard value 0xFD (2nd last day of month), 0xFE (last day of month)
	 * Leap year is checked as guideline from Microsoft for Excel.
	 * https://docs.microsoft.com/en-us/office/troubleshoot/excel/determine-a-leap-year
	 */
	if (p_rtc_value->month > 0 && p_rtc_value->month < 13)
	{
		days = day_of_months[p_rtc_value->month - 1];
		if (p_rtc_value->month == 2)
		{
			if (p_rtc_value->year % 400 == 0 || ((p_rtc_value->year % 4 == 0) && (p_rtc_value->year % 100 != 0)))
			{
				days++;				
			}
		}
	}

    return days;
}

/******************************************************************************
* Function Name : R_SCHEDULER_CalendarCheck
* Interface     : void R_SCHEDULER_CalendarCheck(rtc_counter_value_t *p_rtcvalue)
* Description   : 
* Arguments     : rtc_counter_value_t *p_rtcvalue: RTC value from snapshot (BCD format)
* Return Value  : None
******************************************************************************/
void R_SCHEDULER_CalendarCheck(rtc_counter_value_t *p_rtcvalue)
{
	uint8_t	i,j;
    uint8_t number_days_of_month;
	
	/* Turn 'matched' bit to TRUE if hit schedule */
	for (i = 0; i < MAX_SCHEDULER_NUMBER; i++)
	{
		if (g_scheduler[i].matched != TRUE)
		{
            for(j = 0; j < g_scheduler[i].number_of_exe_time; j++)
            {
                if (g_scheduler[i].p_execution_time[j].Sec   == 0xFF &&
                    g_scheduler[i].p_execution_time[j].Min   == 0xFF &&
                    g_scheduler[i].p_execution_time[j].Hour  == 0xFF &&
                    g_scheduler[i].p_execution_time[j].Day   == 0xFF &&
                    g_scheduler[i].p_execution_time[j].Week  == 0xFF &&
                    g_scheduler[i].p_execution_time[j].Month == 0xFF &&
                    g_scheduler[i].p_execution_time[j].Year  == 0xFF)
                {
                    continue;
                }

                if ((g_scheduler[i].p_execution_time[j].Sec   != 0xFF && g_scheduler[i].p_execution_time[j].Sec   != GET_SEC(p_rtcvalue)   ) ||
                    (g_scheduler[i].p_execution_time[j].Min   != 0xFF && g_scheduler[i].p_execution_time[j].Min   != GET_MIN(p_rtcvalue)   ) ||
                    (g_scheduler[i].p_execution_time[j].Hour  != 0xFF && g_scheduler[i].p_execution_time[j].Hour  != GET_HOUR(p_rtcvalue)  ) ||
                    (g_scheduler[i].p_execution_time[j].Week  != 0xFF && g_scheduler[i].p_execution_time[j].Week  != GET_WEEK(p_rtcvalue)  ) ||
                    (g_scheduler[i].p_execution_time[j].Month != 0xFF && g_scheduler[i].p_execution_time[j].Month != GET_MONTH(p_rtcvalue) ) ||
                    (g_scheduler[i].p_execution_time[j].Year  != 0xFF && g_scheduler[i].p_execution_time[j].Year  != GET_YEAR(p_rtcvalue) ) )
                {
                    continue;
                }
                
                if (g_scheduler[i].p_execution_time[j].Day != 0xFF)
                {
                    number_days_of_month = GetNumberDaysOfMonth(p_rtcvalue);

                    /* 2nd last day of month */
                    if (g_scheduler[i].p_execution_time[j].Day == 0xFD) {
                        if (GET_DAY(p_rtcvalue) != number_days_of_month - 1) {
                            continue;
                        }
                    }
                    /* last day of month */
                    else if (g_scheduler[i].p_execution_time[j].Day == 0xFE) {
                        if (GET_DAY(p_rtcvalue) != number_days_of_month) {
                            continue;
                        }
                    }
                    else if (g_scheduler[i].p_execution_time[j].Day != GET_DAY(p_rtcvalue)) {
                        continue;
                    }
                }

                g_scheduler[i].matched = TRUE;
                g_scheduler_match_context[i].exe_time_id = j;
                g_scheduler_match_context[i].p_snapshot = gp_inst_DataPop;
            }
		}
	}
}

void R_SCHEDULER_PollingProcessing(void);
/******************************************************************************
* Function Name : R_SCHEDULER_PollingProcessing
* Interface     : void R_SCHEDULER_PollingProcessing(void)
* Description   :
*                    Scheduler flags for TOU.
*                    Scheduler flags for Load Survey.
*                    Scheduler flags for Max Demand.
*                    Scheduler flags for LCD Display.
*                    Scheduler flags for Relay Ctrl.
*                    Scheduler flags for PUSH.
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_SCHEDULER_PollingProcessing(void)
{
    s_capture_em_data_t *p_inst_DataPop;
    rtc_counter_value_t rtc_counters;

    p_inst_DataPop = R_INST_DataPop();

    if (p_inst_DataPop != NULL)       /* Have snapshot? */
    {
        memcpy(&rtc_counters, &p_inst_DataPop->capture_time, sizeof(rtc_counter_value_t));

        /* Check scheduler for MDM. If MDM period is end, set the corresponding flag to TRUE (1) */
        if (g_scheduler_flags.mdm == 0) {
            if (SCHEDULER_IsMDMPeriodChanged(&rtc_counters) == 1) {
                g_scheduler_flags.mdm = 1;
            }
        }

        /* Check scheduler for block load. If block load period is end, set the corresponding flag to TRUE (1) */
        if (g_scheduler_flags.blockload == 0) {
            if (SCHEDULER_IsBlockloadPeriodChanged(&rtc_counters) == 1) {
                /* Blockload changed */
                g_scheduler_flags.blockload = 1;
            }
        }

        if (g_scheduler_flags.dailyload == 0)
        {
            if (SCHEDULER_IsDailyLoadPeriodChanged(&rtc_counters) == 1)
            {
                /* Dailyload changed */
                g_scheduler_flags.dailyload = 1;
            }
        }


        /* Scheduler for LCD Interval */
        g_scheduler_flags.lcd_refresh = TRUE;
        g_lcd_display_count++;
        if (g_lcd_display_count > (LCD_DELAY_TIME))
        {
            g_scheduler_flags.lcd_scroll = TRUE;
            g_lcd_display_count = 0;
        }

        /* Scheduler for FWU, PUSH and Billing */
        R_SCHEDULER_CalendarCheck(&rtc_counters);
        
    }

}

/******************************************************************************
* Function Name : R_SCHEDULER_Init
* Interface     : void R_SCHEDULER_Init(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_SCHEDULER_Init(void)
{
}

/******************************************************************************
* Function Name : R_SCHEDULER_Backup
* Interface     : uint8_t R_SCHEDULER_Backup(void)
* Description   : Backup for all scheduler data
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t	R_SCHEDULER_Backup(void)
{
	uint8_t i = 0;
	uint8_t j = 0;
    scheduler_storage_t schedule_backup;
	
	for (i = 0; i < MAX_SCHEDULER_NUMBER; i++)
	{
		/* Write data of scheduler to EEPROM */
        COPY_BACKUP_DATA(schedule_backup, g_scheduler[i]);

		EPR_Write(STORAGE_EEPROM_SCHEDULER_DATA_ADDR + i*SCHEDULER_STORAGE_SIZE, (uint8_t *)&schedule_backup, SCHEDULER_STORAGE_SIZE);
	}
	/* Write all execution time slots to EEPROM */
	EPR_Write(STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR,
			 (uint8_t *)g_scheduler_exe_time,
			 STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_SIZE);
    /* Write demand period settings */
    EPR_Write(STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_ADDR, (uint8_t *)&g_demand_integration_period, sizeof(g_demand_integration_period));
    EPR_Write(STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_ADDR, (uint8_t *)&g_demand_number_of_period, sizeof(g_demand_number_of_period));
	return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_SCHEDULER_BackupByID
* Interface     : uint8_t R_SCHEDULER_BackupByID(uint8_t schedule_id)
* Description   : Backup scheduler data by each ID
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t	R_SCHEDULER_BackupByID(uint8_t schedule_id)
{
    scheduler_storage_t schedule_backup;

	if (schedule_id >= MAX_SCHEDULER_NUMBER)
	{
		return STORAGE_ERROR;
	}
	else
	{
        COPY_BACKUP_DATA(schedule_backup, g_scheduler[schedule_id]);
		/* Write data of scheduler to EEPROM */
		EPR_Write(STORAGE_EEPROM_SCHEDULER_DATA_ADDR + schedule_id*SCHEDULER_STORAGE_SIZE, (uint8_t *)&schedule_backup, SCHEDULER_STORAGE_SIZE);

		/* Check pointer of execution time */	
		if(g_scheduler[schedule_id].p_execution_time == NULL)
		{
			return STORAGE_ERROR;
		}
		else
		{

		}
		/* Write execution time slots to EEPROM */		
		EPR_Write(STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR + g_exe_time_base_index[schedule_id] * sizeof(r_scheduler_datetime_t),
				  (uint8_t *)g_scheduler[schedule_id].p_execution_time,
				  sizeof(r_scheduler_datetime_t) * scheduler_exe_time_maximum_support[schedule_id]);
		
		return STORAGE_OK;
	}
}


/******************************************************************************
* Function Name : R_SCHEDULER_Restore
* Interface     : uint8_t R_SCHEDULER_Restore(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t	R_SCHEDULER_Restore(void)
{
	uint8_t i = 0;
	uint8_t j = 0;
    scheduler_storage_t schedule_backup = { 0, 0, 0};
	
	for (i = 0; i < MAX_SCHEDULER_NUMBER; i++)
	{
		/* Read data of scheduler to EEPROM */
		EPR_Read(STORAGE_EEPROM_SCHEDULER_DATA_ADDR + i*SCHEDULER_STORAGE_SIZE, (uint8_t *)&schedule_backup, SCHEDULER_STORAGE_SIZE);
        COPY_BACKUP_DATA(g_scheduler[i], schedule_backup);
	}
	/* Read all execution time slots to EEPROM */
	EPR_Read(STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR,
			 (uint8_t *)g_scheduler_exe_time,
			 STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_SIZE);

    /* Read demand period settings */
    EPR_Read(STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_ADDR, (uint8_t *)&g_demand_integration_period, sizeof(g_demand_integration_period));
    EPR_Read(STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_ADDR, (uint8_t *)&g_demand_number_of_period, sizeof(g_demand_number_of_period));
	return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_SCHEDULER_Restore
* Interface     : uint8_t R_SCHEDULER_Restore(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t	R_SCHEDULER_RestoreByID(uint8_t schedule_id)
{
	uint8_t i = 0;
	uint8_t j = 0;
    scheduler_storage_t schedule_backup = { 0, 0, 0};
	
	for (i = 0; i < MAX_SCHEDULER_NUMBER; i++)
	{
		/* Read data of scheduler to EEPROM */
		EPR_Read(STORAGE_EEPROM_SCHEDULER_DATA_ADDR + i*SCHEDULER_STORAGE_SIZE, (uint8_t *)&schedule_backup, SCHEDULER_STORAGE_SIZE);
        COPY_BACKUP_DATA(g_scheduler[i], schedule_backup);
	}
	/* Check pointer of execution time */
	if (g_scheduler[schedule_id].p_execution_time == NULL)
	{
		return STORAGE_ERROR;
	}
	else
	{
	}
	/* Read execution time slots to EEPROM */
	EPR_Read(STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR + g_exe_time_base_index[schedule_id] * sizeof(r_scheduler_datetime_t),
			 (uint8_t *)g_scheduler[schedule_id].p_execution_time,
			  sizeof(r_scheduler_datetime_t) * scheduler_exe_time_maximum_support[schedule_id]);

	return STORAGE_OK;
}
/******************************************************************************
* Function Name : R_SCHEDULER_Format
* Interface     : void R_SCHEDULER_Format(
*               :     void
*               : );
* Description   : format data, write default data to storage.
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_SCHEDULER_Format(void)
{
    uint8_t i = 0;
	uint8_t j = 0;
	scheduler_storage_t write_default_scheduler;
	uint8_t default_number_exe_time[MAX_SCHEDULER_NUMBER] = {8, 0, 0, 1, 0, 0};
    uint16_t default_demand_integration_period = SCHEDULER_DEFAULT_MAX_DEMAND_PERIOD;
    uint16_t default_demand_number_of_period = SCHEDULER_DEFAULT_MAX_DEMAND_NUM_OF_PERIOD;

	/* Write default value for billing scheduler */
	for (i = 0; i < MAX_SCHEDULER_NUMBER; i++)
	{
		/* Write default value for tariff scheduler */
		write_default_scheduler.number_of_exe_time = default_number_exe_time[i];
		write_default_scheduler.matched = FALSE;
		write_default_scheduler.script_id = i + 1;
		EPR_Write(STORAGE_EEPROM_SCHEDULER_DATA_ADDR + i*SCHEDULER_STORAGE_SIZE, (uint8_t *)&write_default_scheduler, SCHEDULER_STORAGE_SIZE);

		//Write execution time slots to EEPROM
		for (j = 0; j < default_number_exe_time[i]; j++)
		{
			switch (i)
			{
			case 0://index of tariff
				EPR_Write(STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR + (g_exe_time_base_index[i] + j) * sizeof(r_scheduler_datetime_t),
						  (uint8_t *)&tariff_exe_time_default[j],
						  sizeof(r_scheduler_datetime_t));
				break;
			case 3://index of billing
				EPR_Write(STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR + (g_exe_time_base_index[i] + j) * sizeof(r_scheduler_datetime_t),
						  (uint8_t *)&billing_schedule_default,
						  sizeof(r_scheduler_datetime_t));
				break;
			default://remaining
				EPR_Write(STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR + (g_exe_time_base_index[i] + j) * sizeof(r_scheduler_datetime_t),
						  (uint8_t *)&common_schedule_default,
						  sizeof(r_scheduler_datetime_t));
				break;
			}
		}
	}
    /* Write default demand period settings */
    EPR_Write(STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_ADDR, (uint8_t *)&default_demand_integration_period, sizeof(default_demand_integration_period));
    EPR_Write(STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_ADDR, (uint8_t *)&default_demand_number_of_period, sizeof(default_demand_number_of_period));
	
    return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_SCHEDULER_ExecutionTimeArrayLengthGet
* Interface     : int16_t R_SCHEDULER_ExecutionTimeArrayLengthGet(uint8_t schedule_id)
* Description   :
* Arguments     :
* Return Value  : int16_t
******************************************************************************/
int16_t R_SCHEDULER_ExecutionTimeArrayLengthGet(uint8_t schedule_id)
{
	if (schedule_id >= MAX_SCHEDULER_NUMBER)
	{
		return -1;
	}
	return g_scheduler[schedule_id].number_of_exe_time;
}

/******************************************************************************
* Function Name : R_SCHEDULER_ExecutionTimeArrayLengthSet
* Interface     : uint8_t R_SCHEDULER_ExecutionTimeArrayLengthSet(uint8_t schedule_id, uint16_t length)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_SCHEDULER_ExecutionTimeArrayLengthSet(uint8_t schedule_id, uint16_t length)
{
	if ((schedule_id >= MAX_SCHEDULER_NUMBER) || (length > scheduler_exe_time_maximum_support[schedule_id]))
	{
		return FALSE;
	}
	g_scheduler[schedule_id].number_of_exe_time = length;
	
	return TRUE;
}

/******************************************************************************
* Function Name : R_SCHEDULER_ExecutionTimeGet
* Interface     : uint8_t R_SCHEDULER_ExecutionTimeGet(uint8_t * p_data_out, uint8_t schedule_id,  uint16_t array_index)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_SCHEDULER_ExecutionTimeGet(uint8_t * p_data_out, uint8_t schedule_id,  uint16_t array_index)
{
	if (schedule_id >= MAX_SCHEDULER_NUMBER)
	{
		return FALSE;
	}

	p_data_out[0] = g_scheduler[schedule_id].p_execution_time[array_index].Hour;
	p_data_out[1] = g_scheduler[schedule_id].p_execution_time[array_index].Min;
	p_data_out[2] = g_scheduler[schedule_id].p_execution_time[array_index].Sec;

	return TRUE;
}

/******************************************************************************
* Function Name : R_SCHEDULER_ExecutionTimeSet
* Interface     : uint8_t R_SCHEDULER_ExecutionTimeSet(uint8_t * p_data_in, uint8_t schedule_id,  uint16_t array_index)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_SCHEDULER_ExecutionTimeSet(uint8_t * p_data_in, uint8_t schedule_id,  uint16_t array_index)
{
	if (schedule_id >= MAX_SCHEDULER_NUMBER)
	{
		return FALSE;
	}
	g_scheduler[schedule_id].p_execution_time[array_index].Hour = p_data_in[0];
	g_scheduler[schedule_id].p_execution_time[array_index].Min  = p_data_in[1];
	g_scheduler[schedule_id].p_execution_time[array_index].Sec  = p_data_in[2];

	return TRUE;
}

/******************************************************************************
* Function Name : R_SCHEDULER_ExecutionDateGet
* Interface     : uint8_t R_SCHEDULER_ExecutionDateGet(uint8_t * p_data_out, uint8_t schedule_id,  uint16_t array_index)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_SCHEDULER_ExecutionDateGet(uint8_t * p_data_out, uint8_t schedule_id,  uint16_t array_index)
{
	if (schedule_id >= MAX_SCHEDULER_NUMBER)
	{
		return FALSE;
	}
	
	p_data_out[0] = g_scheduler[schedule_id].p_execution_time[array_index].Year;
	p_data_out[1] = g_scheduler[schedule_id].p_execution_time[array_index].Month;
	p_data_out[2] = g_scheduler[schedule_id].p_execution_time[array_index].Week;
	p_data_out[3] = g_scheduler[schedule_id].p_execution_time[array_index].Day;
	
	return TRUE;
}

/******************************************************************************
* Function Name : R_SCHEDULER_ExecutionDateSet
* Interface     : uint8_t R_SCHEDULER_ExecutionDateSet(uint8_t * p_data_in, uint8_t schedule_id,  uint16_t array_index)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_SCHEDULER_ExecutionDateSet(uint8_t * p_data_in, uint8_t schedule_id,  uint16_t array_index)
{
	if (schedule_id >= MAX_SCHEDULER_NUMBER)
	{
		return FALSE;
	}
	
	g_scheduler[schedule_id].p_execution_time[array_index].Year  = p_data_in[0];
	g_scheduler[schedule_id].p_execution_time[array_index].Month = p_data_in[1];
	g_scheduler[schedule_id].p_execution_time[array_index].Week  = p_data_in[2];
	g_scheduler[schedule_id].p_execution_time[array_index].Day   = p_data_in[3];
	
	return TRUE;
}
