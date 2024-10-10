/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_obis_ic.h
* Version      : 1.00
* Description  :
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 21.02.2013
******************************************************************************/
#ifndef _R_DLMS_DATE_TIME_H
#define _R_DLMS_DATE_TIME_H

/**
* @defgroup Date time
* @brief  DLMS Application Contain the application for DLMS
*         the more is start here
*
* Detail start here
* @{
*/

/**
 * @brief contains API prototype declaration of date time
 * 
 * @file r_dlms_date_time.h
 * @author Renesas Electronics Corporation 
 * @date 2018-03-12
 */

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"

/* Driver */
#include "r_cg_macrodriver.h"   /* CG Macro Driver */
#include "r_cg_rtc.h"           /* CG RTC Driver */

/* */
#include "r_dlms_classes.h"

/******************************************************************************
Macro definitions
******************************************************************************/

#define TO_YEAR99(yr)                       (((yr)==0xFFFF)?0xFF:((yr)%100))
#define TO_YEAR(yr)                         (((yr)==0xFF)?0xFFFF:((yr)+2000))
#define GET_YEAR(high_byte,low_byte)        ((high_byte << 8 | low_byte))
#define GET_YEAR99(high_byte,low_byte)      TO_YEAR99(GET_YEAR(high_byte,low_byte))
#define YEAR_TO_HIGH_LOW(yr,high_byte,low_byte)      { high_byte = (uint8_t)yr >> 8; low_byte = (uint8_t)yr; }


#define R_DATE_TIME_VALID           (0)
#define R_DATE_TIME_INVALID         (1)


#define RTC_BIT_DAY_IS_CHANGED				(0x0001)
#define RTC_BIT_WEEK_IS_CHANGED				(0x0002)
#define RTC_BIT_MONTH_IS_CHANGED			(0x0004)
#define RTC_BIT_YEAR_IS_CHANGED				(0x0008)
#define RTC_BIT_HOUR_IS_CHANGED				(0x0010)
#define RTC_BIT_MINUTE_IS_CHANGED			(0x0020)
#define RTC_BIT_SECOND_IS_CHANGED			(0x0040)

#define RTC_BIT_DAY							(0x0001)
#define RTC_BIT_WEEK						(0x0002)
#define RTC_BIT_MONTH						(0x0004)
#define RTC_BIT_YEAR						(0x0008)
#define RTC_BIT_HOUR						(0x0010)
#define RTC_BIT_MINUTE						(0x0020)
#define RTC_BIT_SECOND						(0x0040)

#define RTC_NOT_SPECIFIED					(0xFF)
#define RTC_DAY_LAST_OF_MONTH				(0xFA)
#define RTC_WEEK_SUN						(0x06)


#define DATE_TIME_NOT_SPECIFIED				{					\
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												0x80, 			\
												0x00, 			\
												NOT_SPECIFIED	\
											}


/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct tag_r_date_time_t
{
	uint8_t Sec;       /* Second */
	uint8_t Min;       /* Minute */
	uint8_t Hour;      /* Hour */
	uint8_t Day;       /* Day */
	uint8_t Week;      /* Day of week */
	uint8_t Month;     /* Month */
	uint8_t Year;      /* Year (ony 2 ending digit) */
} r_date_time_t;

typedef struct tag_rtc_flag_bit_t
{
    uint16_t day          : 1;
    uint16_t week         : 1;
    uint16_t month        : 1;
    uint16_t year         : 1;
    uint16_t hour         : 1;
    uint16_t minute       : 1;
    uint16_t second       : 1;
    uint16_t format_error : 1;
    uint16_t wildcard_error : 1;
} rtc_flag_bit_t;

typedef union tag_rtc_flag_t
{
    rtc_flag_bit_t bits;   ///< Date flag description (bits)
    uint16_t bytes;        ///< Date flag description (bytes)
} rtc_flag_t;


typedef union tag_rtc_status_t
{
	struct
	{
		uint8_t invalid					:1;
		uint8_t doubtful				:1;
		uint8_t different_clock_base	:1;
		uint8_t invalid_clock_status	:1;
		uint8_t reserved1				:1;
		uint8_t reserved2				:1;
		uint8_t reserved3				:1;
		uint8_t daylight_saving_active	:1;
	} bits;
	uint8_t byte;
} rtc_status_t;

/* RTC Date Time */
typedef struct tag_R_DLMS_APP_RTC_T
{
	/* Total: 8 bytes */
	uint8_t Sec;        /* Second */
	uint8_t Min;        /* Minute */
	uint8_t Hour;       /* Hour */
	uint8_t Day;        /* Day */
	uint8_t Week;       /* Day of week */
	uint8_t Month;      /* Month */
	uint8_t Year;       /* Year (ony 2 ending digit) */
} R_DLMS_RTC_T;

typedef struct tag_date_time_params_t
{
    struct{
        R_DLMS_RTC_T current;
        R_DLMS_RTC_T old;
    } date_time;
	date_time_t 	dlms_date_time;
	uint8_t 		converted;
    rtc_flag_t 		change_flag;
	rtc_status_t	status;
} date_time_params_t;

typedef enum tag_datetime_compare_result_t{
    DT_CPM_RESULT_EARLY = FALSE,
    DT_CPM_RESULT_ON_SCHEDULE = TRUE,
} datetime_compare_result_t;



#define R_DLMS_RTC_NORMAL_COUNTER_ID	(0)

typedef enum tag_dlms_rtc_counter_id_t
{
	R_DLMS_RTC_COUNTER_ID_LOAD_CTRL,
	R_DLMS_RTC_COUNTER_ID_PUSH0,
	R_DLMS_RTC_COUNTER_ID_PUSH1,
	R_DLMS_RTC_COUNTER_ID_PUSH2,
	R_DLMS_RTC_COUNTER_ID_PUSH3,
	R_DLMS_RTC_COUNTER_ID_PUSH4,
	R_DLMS_RTC_COUNTER_ID_LOAD_CTRL_LOCKOUT_PERIOD,
	R_DLMS_RTC_COUNTER_ID_LOAD_CTRL_AUTO_RECONNECT_INTERVAL,
	R_DLMS_RTC_COUNTER_ID_OVER_CURRENT
} r_dlms_rtc_counter_id_t;
/******************************************************************************
Variable Externs
******************************************************************************/
extern int16_t g_time_zone;
extern uint8_t g_clock_status;
/******************************************************************************
Functions Prototypes
******************************************************************************/

uint8_t R_DLMS_RTC_wday ( uint16_t year, uint8_t month, uint8_t day );
uint8_t R_DLMS_NumberDayOfMonth ( uint8_t month, uint16_t year );

uint8_t R_DLMS_RTC_Convert_DriverRTC2DateTime(date_time_t * p_dt, rtc_counter_value_t *p_date_time);
uint8_t R_DLMS_RTC_Convert_RTC2DateTime2(date_time_t * p_date_time, rtc_counter_value_t * rtc);
uint8_t R_DLMS_RTC_Convert_DateTime2RTC2(rtc_counter_value_t * rtc, date_time_t * p_date_time);
uint8_t R_DLMS_RTC_Convert_RTC2DateTime(date_time_t * p_date_time, R_DLMS_RTC_T * rtc);
uint8_t R_DLMS_RTC_Convert_DateTime2RTC(R_DLMS_RTC_T * rtc, date_time_t * p_date_time);
void R_DLMS_RTC_Convert_DateAndTime_To_RTC(date_t *p_date, time_t *p_time, R_DLMS_RTC_T *p_rtc);
void R_DLMS_RTC_Convert_RTC_To_DateAndTime(R_DLMS_RTC_T *p_rtc, date_t *p_date, time_t *p_time);

uint8_t R_DLMS_RTC_Convert_DLMSWeekToDriverWeek(uint8_t *p_dest, uint8_t *p_src);
uint8_t R_DLMS_RTC_Convert_DriverWeekToDLMSWeek(uint8_t *p_dest, uint8_t *p_src);

uint8_t R_DLMS_RTC_IsDateTimeDiff( date_time_params_t * params );

void R_DLMS_RTC_Find_NextDay(R_DLMS_RTC_T *pDateTime);
void R_DLMS_RTC_Find_PrevDay(R_DLMS_RTC_T *pDateTime);
uint8_t R_DLMS_NumberDayOfMonth ( uint8_t month, uint16_t year );

uint8_t R_DLMS_RTC_Get_Drv_DateTime( R_DLMS_RTC_T * p_rtc_time );

uint8_t R_DLMS_RTC_Change_TimeZone (int16_t time_zone_new);

uint8_t R_DLMS_RTC_Get_DateTime(uint8_t * p_date_time);
uint8_t R_DLMS_RTC_Set_DateTime( date_time_t * p_date_time );

void R_DLMS_RTC_OldTime_Restore ( R_DLMS_RTC_T * p_old_time );
void R_DLMS_RTC_OldTime_Backup ( R_DLMS_RTC_T * p_old_time );


uint8_t R_DLMS_IsValidDate(date_t *p_date);
uint8_t R_DLMS_IsValidTime(time_t *p_time);
uint8_t R_DLMS_IsValidDateTime ( date_time_t *p_date_time );
uint8_t R_DLMS_IsValidTimeZone ( int16_t deviation );

/* Counter */
void R_DLMS_RTC_Drv_PeriodCallBack ( void );
#define  R_DLMS_RTC_Counter_Reset(counter_id)		R_DLMS_RTC_Counter_Disable(counter_id)
void R_DLMS_RTC_Counter_Enable ( uint8_t counter_id );
void R_DLMS_RTC_Counter_Disable ( uint8_t counter_id );
uint32_t R_DLMS_RTC_Counter_GetValue ( uint8_t counter_id );
void R_DLMS_RTC_Counter_SetValue ( uint8_t counter_id , uint32_t value);
void R_DLMS_RTC_Counter_Start(uint8_t counter_id , uint32_t value);

date_time_params_t * R_DLMS_RTC_Get_TimeProfile ( void );

int8_t R_DLMS_RTC_CompareDateTime( uint8_t *p_src_date_time, uint8_t *p_des_date_time );

int8_t R_DLMS_RTC_Compare(uint8_t *p_src_date_time, uint8_t *p_des_date_time);
int8_t R_DLMS_RTC_DayCompare(
	uint8_t *p_src_date_time,
	uint8_t *p_des_date_time
);

/* Main Application */
void R_DLMS_RTC_Init ( void );
void R_DLMS_RTC_PollingProcessing(void);

void R_DLMS_RTC_Restore(void);
void R_DLMS_RTC_Backup(void);
void R_DLMS_RTC_Format(void);

#endif /* _R_DLMS_DATE_TIME_H */
