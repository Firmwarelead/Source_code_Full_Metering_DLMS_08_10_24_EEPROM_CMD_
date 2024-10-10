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
* File Name    : r_abnormal_operating.c
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
#include "typedef.h"

/* Driver */
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"

/* Standard library */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* Utilities */
#include "eeprom.h"

#include "em_core.h"

/* Wrapper */
#include "wrp_app_ext.h"

/* Application */
#include "inst_read.h"
#include "r_loadsurvey.h"
#include "r_tariff.h"
#include "r_max_demand.h"
#include "r_abnormal_operating.h"
#include "r_meter_format.h"
#include "r_activity_cal.h"

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
meter_wakeup_data_t g_meter_wakekup_data;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/* Function prototype */
static void R_HANDLER_BackupLastSnapshot(void);
static int8_t CompareDate(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2);

/******************************************************************************
* Function Name : CompareDate
* Interface     : int8_t CompareDate(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2)
* Description   :
* Arguments     :
* Return Value  : int8_t
******************************************************************************/
static int8_t CompareDate(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2)
{   
    if (p_rtc_1->year == p_rtc_2->year &&
        p_rtc_1->month == p_rtc_2->month &&
        p_rtc_1->day == p_rtc_2->day
        )   
    {
        return 0;
    }

    if (p_rtc_1->year < p_rtc_2->year)
    {
        return (-1);
    }
    if (p_rtc_1->month < p_rtc_2->month)
    {
        return (-1);
    }
    if (p_rtc_1->day < p_rtc_2->day)
    {
        return (-1);
    }

    return (1);
}

/******************************************************************************
* Function Name : R_HANDLER_BackupBeforeApplyNewRTCValue
* Interface     : void R_HANDLER_BackupBeforeApplyNewRTCValue(rtc_counter_value_t *p_rtc_value)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_HANDLER_BackupBeforeApplyNewRTCValue(const rtc_counter_value_t *p_rtc_value)
{
	rtc_counter_value_t rtc_dec_value;
	
	rtc_dec_value.sec	= WRP_EXT_Bcd2Dec(p_rtc_value->sec);
	rtc_dec_value.min	= WRP_EXT_Bcd2Dec(p_rtc_value->min);
	rtc_dec_value.hour	= WRP_EXT_Bcd2Dec(p_rtc_value->hour);
	rtc_dec_value.day	= WRP_EXT_Bcd2Dec(p_rtc_value->day);
	rtc_dec_value.week	= WRP_EXT_Bcd2Dec(p_rtc_value->week);
	rtc_dec_value.month = WRP_EXT_Bcd2Dec(p_rtc_value->month);
	rtc_dec_value.year	= WRP_EXT_Bcd2Dec(p_rtc_value->year);
	
    memcpy(&g_meter_wakekup_data.rtc_old, &gp_inst_LastDataPop->capture_time, sizeof(rtc_counter_value_t));
    memcpy(&g_meter_wakekup_data.rtc_new, &rtc_dec_value, sizeof(rtc_counter_value_t));

    /* Sync last snapshot energy to tariff for un processed snapshot */
    g_tariff.last_read_energy_counter_snapshot.active_imp = gp_inst_LastDataPop->value.active_energy_total_import;
    g_tariff.last_read_energy_counter_snapshot.active_exp = gp_inst_LastDataPop->value.active_energy_total_export;
    g_tariff.last_read_energy_counter_snapshot.reactive_cap_imp = gp_inst_LastDataPop->value.reactive_energy_lead_total_import;
    g_tariff.last_read_energy_counter_snapshot.reactive_cap_exp = gp_inst_LastDataPop->value.reactive_energy_lead_total_export;
    g_tariff.last_read_energy_counter_snapshot.reactive_ind_imp = gp_inst_LastDataPop->value.reactive_energy_lag_total_import;
    g_tariff.last_read_energy_counter_snapshot.reactive_ind_exp = gp_inst_LastDataPop->value.reactive_energy_lag_total_export;
    g_tariff.last_read_energy_counter_snapshot.apparent_imp = gp_inst_LastDataPop->value.apparent_energy_total_import;
    g_tariff.last_read_energy_counter_snapshot.apparent_exp = gp_inst_LastDataPop->value.apparent_energy_total_export;

    R_LOADSURVEY_AccumulateCurrentBlock();

    R_HANDLER_BackupLastSnapshot();
}


/******************************************************************************
* Function Name : R_HANDLER_AfterApplyNewRTCValue
* Interface     : void R_HANDLER_AfterApplyNewRTCValue(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_HANDLER_AfterApplyNewRTCValue(void)
{
    uint8_t compare_result;
	
    R_HANDLER_GetBackupData(&g_meter_wakekup_data.snapshot_old);

    g_meter_wakekup_data.status = CompareDate(
                                        &g_meter_wakekup_data.rtc_old,
                                        &g_meter_wakekup_data.rtc_new
                                    );
    /* Find and apply new day profile + tariff */
    R_ACT_CAL_FindAndActiveNewSeason(&g_meter_wakekup_data.rtc_new);

    /* Check integration period according to time frame in new RTC value and conclude max demand  */
    R_MDM_NextPeriod(&g_meter_wakekup_data.rtc_new);

    R_LOADSURVEY_Recover();
}

/******************************************************************************
* Function Name : R_HANDLER_MeterWakeup
* Interface     : void R_HANDLER_MeterWakeup(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_HANDLER_MeterWakeup(void)
{
    rtc_counter_value_t rtctime;
    EM_OPERATION_DATA em_energy_data;

    R_RTC_Get_CalendarCounterValue(&rtctime);

    /* Pop out all snapshot in queue */
    R_INST_DataPopAll();

    /* Get previous time and energy to shared gp_inst_LastDataPop */
    R_HANDLER_GetBackupData(gp_inst_LastDataPop);

    /* Process like before setting new RTC value */
    R_HANDLER_BackupBeforeApplyNewRTCValue(&rtctime);

    /* Time changed from previous backup to current time */

    /* Process like after setting new RTC value */
    R_HANDLER_AfterApplyNewRTCValue();

    /* Sync new time and (updated) energy to last snapshot then do backup */
	gp_inst_LastDataPop->capture_time.sec	= WRP_EXT_Bcd2Dec(rtctime.sec);
	gp_inst_LastDataPop->capture_time.min	= WRP_EXT_Bcd2Dec(rtctime.min);
	gp_inst_LastDataPop->capture_time.hour	= WRP_EXT_Bcd2Dec(rtctime.hour);
	gp_inst_LastDataPop->capture_time.day	= WRP_EXT_Bcd2Dec(rtctime.day);
	gp_inst_LastDataPop->capture_time.week	= WRP_EXT_Bcd2Dec(rtctime.week);
	gp_inst_LastDataPop->capture_time.month = WRP_EXT_Bcd2Dec(rtctime.month);
	gp_inst_LastDataPop->capture_time.year	= WRP_EXT_Bcd2Dec(rtctime.year);
        
    EM_GetOperationData(&em_energy_data);
    gp_inst_LastDataPop->value.active_energy_total_import = em_energy_data.energy_counter.active_imp + em_energy_data.remainder.active_imp;
    gp_inst_LastDataPop->value.active_energy_total_export = em_energy_data.energy_counter.active_exp + em_energy_data.remainder.active_exp;
    gp_inst_LastDataPop->value.reactive_energy_lag_total_import = em_energy_data.energy_counter.reactive_cap_imp + em_energy_data.remainder.reactive_cap_imp;
    gp_inst_LastDataPop->value.reactive_energy_lag_total_export = em_energy_data.energy_counter.reactive_cap_exp + em_energy_data.remainder.reactive_cap_exp;
    gp_inst_LastDataPop->value.reactive_energy_lead_total_import = em_energy_data.energy_counter.reactive_ind_imp + em_energy_data.remainder.reactive_ind_imp;
    gp_inst_LastDataPop->value.reactive_energy_lead_total_export = em_energy_data.energy_counter.reactive_ind_exp + em_energy_data.remainder.reactive_ind_exp;
    gp_inst_LastDataPop->value.apparent_energy_total_import = em_energy_data.energy_counter.apparent_imp + em_energy_data.remainder.apparent_imp;
    gp_inst_LastDataPop->value.apparent_energy_total_export = em_energy_data.energy_counter.apparent_exp + em_energy_data.remainder.apparent_exp;

    R_HANDLER_BackupLastSnapshot();
}

/******************************************************************************
* Function Name : R_HANDLER_BackupLastSnapshot
* Interface     : static void R_HANDLER_BackupLastSnapshot(void)
* Description   :
* Arguments     :
* Return Value  : static void
******************************************************************************/
static void R_HANDLER_BackupLastSnapshot(void)
{
    EPR_Write(STORAGE_EEPROM_COMMON_SNAPSHOT_VALUE_ADDR, 
        (uint8_t *)gp_inst_LastDataPop,
        sizeof(s_capture_em_data_t)
    );
}

/******************************************************************************
* Function Name : R_HANDLER_GetBackupData
* Interface     : uint8_t R_HANDLER_GetBackupData(meter_data_at_wakeup_t *p_data)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_HANDLER_GetBackupData(s_capture_em_data_t *p_data)
{
    if (p_data == NULL)
    {
        return FALSE;
    }
    
    if (
        EPR_Read(STORAGE_EEPROM_COMMON_SNAPSHOT_VALUE_ADDR, 
            (uint8_t *)p_data,
            sizeof(s_capture_em_data_t)
        ) != EPR_OK
    )
    {
        return FALSE;
    }

    return TRUE;
}

/******************************************************************************
* Function Name : R_HANDLER_BeforeMeterSleep
* Interface     : void R_HANDLER_BeforeMeterSleep(uint8_t *p_rtc_at_sleep)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_HANDLER_BeforeMeterSleep(void)
{
    /* Pop out all snapshot in queue */
    R_INST_DataPopAll();

    /* Store meter snapshot value before sleep */
    R_HANDLER_BackupLastSnapshot();
}
