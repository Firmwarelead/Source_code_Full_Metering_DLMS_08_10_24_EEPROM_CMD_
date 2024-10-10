/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_scheduler.h
* Version      : v1.0
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

#ifndef _R_DLMS_SCHEDULER_H
#define _R_DLMS_SCHEDULER_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"

/* Common */
#include "typedef.h"
#include "compiler.h"

#include "r_dlms_date_time.h"
#include "r_dlms_app.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

typedef enum tag_dlms_scheduler_id_t
{
	R_DLMS_SCHEUDLER_ID_BILLING,
	R_DLMS_SCHEUDLER_ID_IMAGE_ACTIVATE,
	R_DLMS_SCHEUDLER_ID_CHANGE_TARRIF,
	R_DLMS_SCHEUDLER_ID_PUSH_DATA_TO_HES,
	R_DLMS_SCHEUDLER_ID_PUSH_DATA_TO_IHD,
} r_dlms_scheduler_id_t;

typedef struct tag_r_dlms_scheduler_t
{
	uint8_t						enable;
	R_DLMS_RTC_T				rtc;
	rtc_flag_t					flag;
	uint16_t					script_id;
} r_dlms_scheduler_t;


/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
//#define R_DLMS_APPS_SCHEDULER_ENABLE					(TRUE)
/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
uint8_t R_DLMS_Scheduler_Backup ( uint8_t index, R_DLMS_RTC_T *p_date_time, uint16_t exe_flag );
uint8_t R_DLMS_Scheduler_Restore ( uint8_t scheduler_id,  R_DLMS_RTC_T * p_date_time, uint16_t * exe_flag );
rtc_flag_t R_DLMS_Scheduler_UpdateExecutionFlag(uint8_t schedule_id, R_DLMS_RTC_T *p_rtc_scheduler);
uint8_t R_DLMS_Scheduler_Create (uint8_t schedule_id, R_DLMS_RTC_T *p_rtc, uint16_t script_id, uint16_t execute_flag);
r_dlms_scheduler_t * R_DLMS_Scheduler_GetInfo (uint8_t scheduler_id);
void R_DLMS_Scheduler_OnDateTimeChanged_CallBack ( R_DLMS_RTC_T *p_current_time, rtc_flag_t * p_rtc_changed_flag );

void R_DLMS_Scheduler_Rewrite_Ack ( uint8_t schedule_id );

datetime_compare_result_t R_DLMS_Scheduler_Check (
	R_DLMS_RTC_T * p_date, 
	R_DLMS_RTC_T * p_current_time,
	rtc_flag_t * p_clock_changed_flag,
	rtc_flag_t * p_exe_flag
);


#endif /* _R_DLMS_SCHEDULER_H */