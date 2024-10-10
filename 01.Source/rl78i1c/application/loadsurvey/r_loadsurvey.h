/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_loadsurvey.h
* Version      : v1.0
* Description  : 
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 2021.03.04 New creation
***********************************************************************************************************************/

#ifndef _R_LOADSURVEY_H
#define _R_LOADSURVEY_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"

#include "typedef.h"
#include "compiler.h"

/***********************************************************************************************************************
Configurations
***********************************************************************************************************************/

/*
 Name:                Block load capture period default
 Available values:    900,
                      1800
                      3800
*/
#define BLOCKLOAD_CAPTURE_PERIOD_DEFAULT	        (1800)  /* 30 min */



#define VRMS_AVERAGE_THRESHOLD					(75.0f)

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define R_BLOCKLOAD_CAPTURE_INTERVAL    (15)            /* Block load profile cature interval, Unit: mins */


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct 
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t week;
    uint8_t month;
    uint16_t year;
} r_loadsurvey_rtc_t;

/* 1Phase block load log */
typedef struct tag_one_block_storage
{
    uint16_t            NumberOfSample;
    float32_t           AverageVoltage;
    uint16_t            EnergykWhImport;
    uint16_t            EnergykVAhImport;
    uint16_t            EnergykWhExport;
    uint16_t            EnergykVAhExport;
} one_block_storage_t;

/* 1Phase daily load log */
typedef struct tag_one_daily_log_storage
{
    r_loadsurvey_rtc_t  CaptureTime      ;
    uint32_t            EnergykWhImport  ;
    uint32_t            EnergykVAhImport ;
    uint32_t            EnergykWhExport  ;
    uint32_t            EnergykVAhExport ;
} one_daily_log_storage;

/* 1Phase billing log */
typedef struct tag_one_billing_log_storage
{
    r_loadsurvey_rtc_t  CaptureTime                ;
    uint16_t           AveragePowerFactor         ;
    uint32_t           CumulativeEnergykWh        ;
    uint32_t           CumulativeEnergykWh_TZ1    ;
    uint32_t           CumulativeEnergykWh_TZ2    ;
    uint32_t           CumulativeEnergykWh_TZ3    ;
    uint32_t           CumulativeEnergykWh_TZ4    ;
    uint32_t           CumulativeEnergykWh_TZ5    ;
    uint32_t           CumulativeEnergykWh_TZ6    ;
    uint32_t           CumulativeEnergykWh_TZ7    ;
    uint32_t           CumulativeEnergykWh_TZ8    ;
    uint32_t           CumulativeEnergykVAh       ;
    uint32_t           CumulativeEnergykVAh_TZ1   ;
    uint32_t           CumulativeEnergykVAh_TZ2   ;
    uint32_t           CumulativeEnergykVAh_TZ3   ;
    uint32_t           CumulativeEnergykVAh_TZ4   ;
    uint32_t           CumulativeEnergykVAh_TZ5   ;
    uint32_t           CumulativeEnergykVAh_TZ6   ;
    uint32_t           CumulativeEnergykVAh_TZ7   ;
    uint32_t           CumulativeEnergykVAh_TZ8   ;
    uint32_t           MDkW                       ;
    r_loadsurvey_rtc_t  MDkWDateTime               ;
    uint32_t            MDkVA                      ;
    r_loadsurvey_rtc_t  MDkVADateTime              ;
    uint32_t            PowerONduration            ;
    uint32_t           CumulativeEnergykWh_Export ;
    uint32_t           CumulativeEnergykVAh_Export;
    uint32_t           CumulativeEnergykVArh_QI   ;
    uint32_t           CumulativeEnergykVArh_QII  ;
    uint32_t           CumulativeEnergykVArh_QIII ;
    uint32_t           CumulativeEnergykVArh_QIV  ;
} one_billing_log_storage;

/* 1Phase block load log */
typedef struct tag_block_load_t
{
    r_loadsurvey_rtc_t   CaptureTime;
    float32_t            AverageCurrent;
    float32_t            AverageVoltage;
    float32_t            EnergykWhImport;
    float32_t            EnergykVAhImport;
    float32_t            EnergykWhExport;
    float32_t            EnergykVAhExport;
} r_block_load_t;


/* 1Phase daily load log */
typedef struct tag_daily_load_t
{
    r_loadsurvey_rtc_t  CaptureTime;
    float32_t            EnergykWhImport;
    float32_t            EnergykVAhImport;
    float32_t            EnergykWhExport;
    float32_t            EnergykVAhExport;
} r_daily_load_t;

/* 1Phase billing log */
typedef struct tag_billing_load_t
{
    r_loadsurvey_rtc_t  CaptureTime                ;
    float32_t           AveragePowerFactor         ;
    float32_t           CumulativeEnergykWh        ;
    float32_t           CumulativeEnergykWh_TZ1    ;
    float32_t           CumulativeEnergykWh_TZ2    ;
    float32_t           CumulativeEnergykWh_TZ3    ;
    float32_t           CumulativeEnergykWh_TZ4    ;
    float32_t           CumulativeEnergykWh_TZ5    ;
    float32_t           CumulativeEnergykWh_TZ6    ;
    float32_t           CumulativeEnergykWh_TZ7    ;
    float32_t           CumulativeEnergykWh_TZ8    ;
    float32_t           CumulativeEnergykVAh       ;
    float32_t           CumulativeEnergykVAh_TZ1   ;
    float32_t           CumulativeEnergykVAh_TZ2   ;
    float32_t           CumulativeEnergykVAh_TZ3   ;
    float32_t           CumulativeEnergykVAh_TZ4   ;
    float32_t           CumulativeEnergykVAh_TZ5   ;
    float32_t           CumulativeEnergykVAh_TZ6   ;
    float32_t           CumulativeEnergykVAh_TZ7   ;
    float32_t           CumulativeEnergykVAh_TZ8   ;
    float32_t           MDkW                       ;
    r_loadsurvey_rtc_t  MDkWDateTime               ;
    float32_t           MDkVA                      ;
    r_loadsurvey_rtc_t  MDkVADateTime              ;
    uint32_t            PowerONduration            ;
    float32_t           CumulativeEnergykWh_Export ;
    float32_t           CumulativeEnergykVAh_Export;
    float32_t           CumulativeEnergykVArh_QI   ;
    float32_t           CumulativeEnergykVArh_QII  ;
    float32_t           CumulativeEnergykVArh_QIII ;
    float32_t           CumulativeEnergykVArh_QIV  ;
} r_billing_t;


/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
extern uint32_t g_billing_counter;                          /* Billing counter */
extern uint32_t g_blockload_capture_period;                 /* Profile capture period */
extern uint32_t g_meter_power_on_duration;
extern uint32_t g_billing_power_on_duration;

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

uint8_t R_BLOCKLOAD_Reset(void);
uint8_t R_DAILYLOAD_Reset(void);
uint8_t R_BILLING_Reset(void);

uint8_t R_BILLING_Capture(void);
uint8_t R_BILLING_ManualCapture(void);

uint8_t R_BLOCKLOAD_GetEntryByIndex(uint32_t entry_index, uint8_t multiplier, r_block_load_t *p_OutData);
uint8_t R_DAILYLOAD_GetEntryByIndex(uint32_t entry_index, r_daily_load_t *p_OutData);
uint8_t R_BILLING_GetEntryByIndex(uint32_t entry_index, r_billing_t *p_OutData);
uint8_t R_BILLING_Get_CurrentCycleBillingParameters(r_billing_t *p_OutData);

uint8_t R_BLOCKLOAD_GetEntryInUse(uint32_t *p_OutData, uint8_t divider);
uint8_t R_BLOCKLOAD_GetProfileEntry(uint32_t *p_OutData, uint8_t divider);
uint8_t R_DAILYLOAD_GetEntryInUse(uint32_t *p_OutData);
uint8_t R_DAILYLOAD_GetProfileEntry(uint32_t *p_OutData);
uint8_t R_BILLING_GetEntryInUse(uint32_t *p_OutData);
uint8_t R_BILLING_GetProfileEntry(uint32_t *p_OutData);

uint8_t R_BLOCKLOAD_Get_EntryId_ByDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint8_t              divider,
    uint32_t            *p_entry_id_out);
	
uint8_t R_BLOCKLOAD_Get_StartEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint8_t              divider,
    uint32_t            *p_entry_id_out);

uint8_t R_BLOCKLOAD_Get_EndEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint8_t              divider,
    uint32_t            *p_entry_id_out);

uint8_t R_DAILYLOAD_Get_StartEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint32_t            *p_entry_id_out);

uint8_t R_DAILYLOAD_Get_EndEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint32_t            *p_entry_id_out);

uint8_t R_BILLING_Get_StartEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint32_t            *p_entry_id_out);

uint8_t R_BILLING_Get_EndEntryId_FromDateTime(
    rtc_counter_value_t *p_request_rtc_start,
    uint32_t            *p_entry_id_out);

float32_t R_LOADSURVEY_GetCurrentAveragePF(void);
void R_BLOCKLOAD_GetAverageCurrent(float32_t *p_out_data);
void R_BLOCKLOAD_GetAverageVoltage(float32_t *p_out_data);

/* For Abnormal Case processing */
void R_BLOCKLOAD_Recover(void);
void R_DAILYLOAD_Recover(void);
void R_BILLING_Recover(void);
void R_LOADSURVEY_Recover(void);
void R_LOADSURVEY_AccumulateCurrentBlock(void);

void R_LOADSURVEY_PollingProcessing(void);

uint8_t R_BILLING_GetLastActiveEnergyImport(float32_t *p_cumulative_energy);

void R_BLOCKLOAD_AddSampleOfStandbyMode(float32_t v_rms);


uint8_t R_BLOCKLOAD_SetProfileCapturePeriod(uint16_t period);
uint8_t R_BLOCKLOAD_GetProfileCapturePeriod(uint16_t *p_period);

void R_LoadSurvey_FindNextDay(r_loadsurvey_rtc_t  *p_capture_time);

/* Storage function */
uint8_t R_LOADSURVEY_Format(void);
uint8_t R_LOADSURVEY_Backup(void);
uint8_t R_LOADSURVEY_Restore(void);

uint8_t R_BLOCKLOAD_Format(void);
uint8_t R_DAILYLOAD_Format(void);
uint8_t R_BILLING_Format(void);

uint8_t R_BLOCKLOAD_Backup(void);
uint8_t R_DAILYLOAD_Backup(void);
uint8_t R_BILLING_Backup(void);

uint8_t R_BLOCKLOAD_Restore(void);
uint8_t R_DAILYLOAD_Restore(void);
uint8_t R_BILLING_Restore(void);

#endif /* _R_LOADSURVEY_H */