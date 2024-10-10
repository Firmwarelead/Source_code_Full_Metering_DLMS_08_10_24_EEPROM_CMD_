/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_activity_cal.h
* Version      : v1.0
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

#ifndef _R_ACT_CAL_H
#define _R_ACT_CAL_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"

#include "typedef.h"

#include <string.h>
#include <stddef.h>
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#ifndef TRUE
#define TRUE (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif

#define ACTIVE_PROFILE			(FALSE)
#define PASSIVE_PROFILE			(TRUE)

#define R_ACT_CAL_ALLOC_SIZE_CAL_NAME			(STORAGE_EEPROM_DLMS_CALENDAR_SEASON_NUM_ADDR)
#define R_ACT_CAL_ALLOC_SIZE_SEASON_NAME		(20)
#define R_ACT_CAL_ALLOC_SIZE_WEEK_NAME			(20)
#define R_ACT_CAL_ALLOC_SIZE_DAY_NAME			(20)

/* [Configured] */
#define CALENDER_NAME_ACTIVE_START_ADDR				(STORAGE_EEPROM_DLMS_CALENDAR_NAME_ADDR)
#define CALENDER_NAME_ACTIVE_MAX_LENGTH				(STORAGE_EEPROM_DLMS_CALENDAR_NAME_SIZE)
#define CALENDER_NAME_PASSIVE_START_ADDR			(STORAGE_EEPROM_DLMS_CALENDAR_NAME_PASSIVE_ADDR)
#define CALENDER_NAME_PASSIVE_MAX_LENGTH			(STORAGE_EEPROM_DLMS_CALENDAR_NAME_PASSIVE_SIZE)

#define NAME_LENGTH_MAX			       (16)
#define SEASON_PROFILE_ELEMENT_MAX		(2)
#define WEEK_PROFILE_ELEMENT_MAX		(2)
#define DAY_PROFILE_ELEMENT_MAX			(4)
#define DAY_ACTION_ELEMENT_MAX			(8)

/* Calendar */
#define TOD_CALENDAR_NAME_8BYTES_DEFAULT			"calendar_0"

/* Calendar season */
#define TOD_NUMBER_SEASON_DEFAULT					1
#define TOD_SEASON_NAME_00_8BYTES_DEFAULT			"season_0"
#define TOD_SEASON_NAME_01_8BYTES_DEFAULT			"season_1"

#define TOD_SEASON_00_START_TIME					{ 0x00, 0x00, 0x00, 0x01, 0xFF, 0x01, 0xFFFF }
#define TOD_SEASON_01_START_TIME					{ 0x00, 0x00, 0x00, 0x01, 0xFF, 0x06, 0xFFFF }

#define TOD_WEEK_NAME_00_8BYTES_DEFAULT				"week_0"
#define TOD_WEEK_NAME_01_8BYTES_DEFAULT				"week_1"

/* Week profile table */
#define TOD_NUMBER_WEEK_DEFAULT						1

#define TOD_WEEK_PROFILE_0_Mo						0
#define TOD_WEEK_PROFILE_0_Tu						0
#define TOD_WEEK_PROFILE_0_We						0
#define TOD_WEEK_PROFILE_0_Th						0
#define TOD_WEEK_PROFILE_0_Fr						0
#define TOD_WEEK_PROFILE_0_Sa						0
#define TOD_WEEK_PROFILE_0_Su						0

#define TOD_WEEK_PROFILE_1_Mo						1
#define TOD_WEEK_PROFILE_1_Tu						1
#define TOD_WEEK_PROFILE_1_We						1
#define TOD_WEEK_PROFILE_1_Th						1
#define TOD_WEEK_PROFILE_1_Fr						1
#define TOD_WEEK_PROFILE_1_Sa						1
#define TOD_WEEK_PROFILE_1_Su						1

/* Day profile table */
#define TOD_NUMBER_DAY_PROFILE						1

#define TOD_DAY_PROFILE_NUMBER_ACTION				6

#define TOD_DAY_PROFILE_TIMESLOT0					00, 00
#define TOD_DAY_PROFILE_TIMESLOT1					06, 00
#define TOD_DAY_PROFILE_TIMESLOT2					12, 00
#define TOD_DAY_PROFILE_TIMESLOT3					13, 00
#define TOD_DAY_PROFILE_TIMESLOT4					18, 00
#define TOD_DAY_PROFILE_TIMESLOT5					20, 00

#define TOD_DAY_PROFILE_ACTIVE_SLOT0				1
#define TOD_DAY_PROFILE_ACTIVE_SLOT1				2
#define TOD_DAY_PROFILE_ACTIVE_SLOT2				3
#define TOD_DAY_PROFILE_ACTIVE_SLOT3				4
#define TOD_DAY_PROFILE_ACTIVE_SLOT4				5
#define TOD_DAY_PROFILE_ACTIVE_SLOT5				6

#define TOD_ACTIVATION_TIME_DEFAULT					{ 0x00, 0x00, 0x00, 0x05, 0xFF, 0x03, 0x13 }		/* 00h00 Mar 5th, 2019 */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/* Calendar name */
typedef struct tag_tod_name_t
{
	uint8_t						len;
	uint8_t						value[NAME_LENGTH_MAX];
} r_act_cal_name_t;

/* Calendar Season Profile */
typedef struct tag_tod_storage_season_t
{
	r_act_cal_name_t			name;
	rtc_counter_value_t         start_time;
	r_act_cal_name_t			week;
} r_act_cal_season_t;

typedef struct tag_tod_season_profile_t
{
	uint8_t 					num;
	r_act_cal_season_t			entry[SEASON_PROFILE_ELEMENT_MAX];
} r_act_cal_season_profile_t;

/* Calendar Week Profile */
typedef struct tag_tod_storage_week_t
{
	r_act_cal_name_t			name;
	uint8_t 					data[7];
} r_act_cal_week_t;

typedef struct tag_week_profile_t
{
	uint8_t						num;
	r_act_cal_week_t			entry[WEEK_PROFILE_ELEMENT_MAX];
} r_act_cal_week_profile_t;

/* Calendar Day Profile */
typedef struct tag_tod_storage_action_t
{
	uint8_t						hour;
	uint8_t						min;
	uint16_t					scriptID;
} r_act_cal_action_t;

typedef struct tag_tod_storage_day_t
{
	uint8_t						dayID;
	uint8_t 					numberOfAction;
	r_act_cal_action_t			action[DAY_ACTION_ELEMENT_MAX];
} r_act_cal_day_t;

typedef struct tag_tod_day_profile_t
{
	uint8_t 					num;								// Number of entries in day profile table
	r_act_cal_day_t				entry[DAY_PROFILE_ELEMENT_MAX];		// Elements of day profile table
} r_act_cal_day_profile_t;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

/* Special API */
uint8_t R_ACT_CAL_Set_ActivateTime(rtc_counter_value_t *p_data_in);
uint8_t R_ACT_CAL_Get_ActivationTime(rtc_counter_value_t *p_data_out);
uint8_t R_ACT_CAL_RequestCopyPassiveToActive(void);

void R_ACT_CAL_FindAndActiveNewSeason(rtc_counter_value_t *p_rtctime);

/* Backup Function */
uint8_t R_ACT_CAL_Backup_CalendarName_Passive(r_act_cal_name_t *p_calendar_name);
uint8_t R_ACT_CAL_Backup_SeasonProfile_Passive(r_act_cal_season_profile_t *p_profile);
uint8_t R_ACT_CAL_Backup_WeekProfile_Passive(r_act_cal_week_profile_t *p_profile);
uint8_t R_ACT_CAL_Backup_DayProfile_Passive(r_act_cal_day_profile_t *p_profile);

/* Restore Function */
r_act_cal_name_t 				R_ACT_CAL_Restore_CalendarName		(uint8_t is_passive);
r_act_cal_season_profile_t 	    R_ACT_CAL_Restore_SeasonProfile	    (uint8_t is_passive);
r_act_cal_week_profile_t 		R_ACT_CAL_Restore_WeekProfile		(uint8_t is_passive);
r_act_cal_day_profile_t 		R_ACT_CAL_Restore_DayProfile		(uint8_t is_passive);

/* General API */
uint8_t R_ACT_CAL_Format(void);
uint8_t R_ACT_CAL_Restore(void);
uint8_t R_ACT_CAL_Backup(void);

void R_ACT_CAL_Init(void);
void R_ACT_CAL_PollingProcessing(void);
#endif /* _R_ACT_CAL_H */