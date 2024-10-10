/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class20.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS20_H
#define _R_DLMS_CLASS20_H
#include "r_dlms_config.h"

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_classes.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define CLASS20_SUPPORT_MAX_LENGTH_CAL_NAME			(30)
#define CLASS20_SUPPORT_MAX_LENGTH_SEASON_NAME		(30)
#define CLASS20_SUPPORT_MAX_LENGTH_WEEK_NAME		(30)
#define CLASS20_SUPPORT_MAX_LENGTH_DAY_NAME			(30)
#define CLASS20_SUPPORT_MAX_SEASON_NAME		(30)
#define CLASS20_SUPPORT_MAX_WEEK_NAME		(30)

/******************************************************************************
Typedef definitions
******************************************************************************/

/* Season profile table */
typedef struct tag_class20_season_profile_t
{
	VariantString		season_profile_name;
	date_time_t			season_start;
	VariantString		week_profile_name;
} class20_season_profile_t;

/* Array of season profile */
typedef OBIS_DECLARE_VARIANT_ARRAY(class20_season_profile_t, class20_season_profile_array_t);

typedef enum tag_class20_week_profile_data_id_t
{
	CLASS20_WEEK_DATA_MONDAY,
	CLASS20_WEEK_DATA_TUESDAY,
	CLASS20_WEEK_DATA_WEDNESDAY,
	CLASS20_WEEK_DATA_THURSDAY,
	CLASS20_WEEK_DATA_FRIDAY,
	CLASS20_WEEK_DATA_SATURDAY,
	CLASS20_WEEK_DATA_SUNDAY
} class20_week_profile_data_id_t;

/* Week profile table */
typedef struct tag_class20_week_profile_table_t
{
	VariantString	week_profile_name;
	union
	{
		struct
		{
			uint8_t	Monday;				/* The day_profile id valid on Monday */
			uint8_t Tuesday;			/* The day_profile id valid on Tuesday */
			uint8_t Wednesday; 			/* The day_profile id valid on Wednesday */
			uint8_t Thursday;			/* The day_profile id valid on Thursday */
			uint8_t Friday;				/* The day_profile id valid on Friday */
			uint8_t Saturday; 			/* The day_profile id valid on Saturday */
			uint8_t Sunday;				/* The day_profile id valid on Sunday */
		};
		uint8_t data[7];
	};
} class20_week_profile_table_t;

/* Array of week profile table */
typedef OBIS_DECLARE_VARIANT_ARRAY(class20_week_profile_table_t, class20_week_profile_table_array_t);

/* Day profile table */
typedef struct tag_class20_day_profile_action_t
{
	time_t		start_time;
	uint8_t		script_logical_name[6];		/* The logical name of the Script table object  */
	uint16_t	script_selector;			/* Script_identifier of the script to be executed */
} class20_day_profile_action_t;

typedef OBIS_DECLARE_VARIANT_ARRAY(class20_day_profile_action_t, class20_day_profile_action_array_t);

typedef struct tag_class20_day_profile_table_t
{
	uint8_t day_id;
	class20_day_profile_action_array_t day_schedule;
} class20_day_profile_table_t;

typedef OBIS_DECLARE_VARIANT_ARRAY(class20_day_profile_table_t, class20_day_profile_table_array_t);

/* Malloc */

/* child record for 1 object of class 20 */
typedef struct tag_class20_child_record_t
{
	uint8_t								logical_name[6];						/* Logical name (OBIS code) of the object. */
	access_right_t						*p_access_right;						/* Access right definition for 1 object */
	VariantString						*p_calendar_name_active;				/* Typically contains an identifier */
	class20_season_profile_array_t		*p_season_profile_active;				/* Contains a list of seasons defined by their starting date and a specific week_profile to be executed */
	class20_week_profile_table_array_t	*p_week_profile_table_active;			/* Contains an array of week_profiles to be used in the different seasons */
	class20_day_profile_table_array_t	*p_day_profile_table_active;			/* Contains an array of day_profiles, identified by their day_id */
	VariantString						*p_calendar_name_passive;				/* Typically contains an identifier */
	class20_season_profile_array_t		*p_season_profile_passive;				/* Contains a list of seasons defined by their starting date and a specific week_profile to be executed */
	class20_week_profile_table_array_t	*p_week_profile_table_passive;			/* Contains an array of week_profiles to be used in the different seasons */
	class20_day_profile_table_array_t	*p_day_profile_table_passive;			/* Contains an array of day_profiles, identified by their day_id */
	date_time_t							*p_activate_passive_calendar_time;		/* Defines the time when the object itself calls the specific method activate_passive_calendar */
} class20_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class20_child_record_t g_objects_child_table_class20[];			/* Import from objects : child table defintion for class 20 */
extern const uint16_t				g_objects_child_table_class20_length;		/* Import from objects : length of child table defintion of class 20 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass20(distributor_params_t *p_params);

/* Function to encode/decode attribute */
/* Calender name */
#define R_DLMS_CLASSES_DistributeClass20_CalendarName(p_params, p_calendar_name)	R_DLMS_CLASSES_DistributeVariantString(p_params, TAG_DATA_OCTET_STRING, p_calendar_name)
/* Season profile */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass20_SeasonProfileTable, class20_season_profile_array_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass20_SeasonProfileTable, class20_season_profile_array_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass20_SeasonProfileTable, class20_season_profile_array_t);
/* Week profile */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass20_WeekProfileTable, class20_week_profile_table_array_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass20_WeekProfileTable, class20_week_profile_table_array_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass20_WeekProfileTable, class20_week_profile_table_array_t);
/* Day profile */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass20_DayProfileTable, class20_day_profile_table_array_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass20_DayProfileTable, class20_day_profile_table_array_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass20_DayProfileTable, class20_day_profile_table_array_t);


/* Redirect function */
VariantString *R_DLMS_CLASSES_RedirectClass20_Calender_Name(distributor_params_t *p_params, VariantString *p_object, uint16_t size);
class20_season_profile_array_t *R_DLMS_CLASSES_RedirectClass20_SeasonProfileTable(distributor_params_t *p_params, class20_season_profile_array_t *p_object, uint16_t size);
class20_week_profile_table_array_t *R_DLMS_CLASSES_RedirectClass20_WeekProfileTable(distributor_params_t *p_params, class20_week_profile_table_array_t *p_object, uint16_t size);
class20_day_profile_table_array_t *R_DLMS_CLASSES_RedirectClass20_DayProfileTable(distributor_params_t *p_params, class20_day_profile_table_array_t *p_object, uint16_t size_day_profile_table, uint16_t size_max_day_schedule);
class20_day_profile_table_array_t *R_DLMS_CLASSES_RedirectClass20_DayProfileTable_EstimateDayScheduleSize(distributor_params_t *p_params, class20_day_profile_table_array_t *p_object, uint16_t size_day_profile_table);
/* Simple data type*/
#define R_DLMS_IC20_REDIRECT_02(p_params, p_attribute, size)			p_attribute = R_DLMS_CLASSES_RedirectClass20_Calender_Name(p_params, p_attribute, size)
#define R_DLMS_IC20_REDIRECT_06(p_params, p_attribute, size)			p_attribute = R_DLMS_CLASSES_RedirectClass20_Calender_Name(p_params, p_attribute, size)
#define R_DLMS_IC20_REDIRECT_10(p_params, p_attribute)					p_attribute = R_DLMS_CLASSES_RedirectDateTime(p_params, p_attribute)

/* Complex data type */
#define R_DLMS_IC20_REDIRECT_03(p_params, p_attribute, array_size)											p_attribute = R_DLMS_CLASSES_RedirectClass20_SeasonProfileTable(p_params, p_attribute, array_size)
#define R_DLMS_IC20_REDIRECT_04(p_params, p_attribute, array_size)											p_attribute = R_DLMS_CLASSES_RedirectClass20_WeekProfileTable(p_params, p_attribute, array_size)
#define R_DLMS_IC20_REDIRECT_05(p_params, p_attribute, size_day_profile_table, size_max_day_schedule)		p_attribute = R_DLMS_CLASSES_RedirectClass20_DayProfileTable(p_params, p_attribute, size_day_profile_table, size_max_day_schedule)
#define R_DLMS_IC20_REDIRECT_07(p_params, p_attribute, array_size)											p_attribute = R_DLMS_CLASSES_RedirectClass20_SeasonProfileTable(p_params, p_attribute, array_size)
#define R_DLMS_IC20_REDIRECT_08(p_params, p_attribute, array_size)											p_attribute = R_DLMS_CLASSES_RedirectClass20_WeekProfileTable(p_params, p_attribute, array_size)
#define R_DLMS_IC20_REDIRECT_09(p_params, p_attribute, size_day_profile_table, size_max_day_schedule)		p_attribute = R_DLMS_CLASSES_RedirectClass20_DayProfileTable(p_params, p_attribute, size_day_profile_table, size_max_day_schedule)

void R_DLMS_CLASSES_Class20Init(void);
void R_DLMS_CLASSES_Class20PollingProcessing(void);
void R_DLMS_CLASSES_Class20AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class20AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass20(distributor_params_t *p_params);


#endif /* _R_DLMS_CLASS20_H */

