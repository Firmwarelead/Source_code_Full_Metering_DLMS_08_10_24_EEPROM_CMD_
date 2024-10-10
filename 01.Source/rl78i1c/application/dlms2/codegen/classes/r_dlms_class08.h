/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class08.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS08_H
#define _R_DLMS_CLASS08_H
#include "r_dlms_config.h"

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_classes.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/* Clock base */
typedef enum tag_clock_base_t
{
	CLASS08_CLOCK_BASE_NOT_DEFINED = 0,
	CLASS08_CLOCK_BASE_INTERNAL_CRYSTAL = 1,
	CLASS08_CLOCK_BASE_MAINS_FREQUENCY_50_HZ = 2,
	CLASS08_CLOCK_BASE_MAINS_FREQUENCY_60_HZ = 3,
	CLASS08_CLOCK_BASE_GPS = 4,
	CLASS08_CLOCK_BASE_RADIO_CONTROLLED = 5,
} clock_base_t;

typedef struct tag_class08_preset_adjusting_time_t
{
    date_time_t preset_time;
    date_time_t validity_interval_start;
    date_time_t validity_interval_end;
} class08_preset_adjusting_time_t;

typedef enum tag_class08_attribute_t
{
    CLASS08_ATTRIBUTE_02_TIME = 2,
    CLASS08_ATTRIBUTE_03_TIME_ZONE,
    CLASS08_ATTRIBUTE_04_STATUS,
    CLASS08_ATTRIBUTE_05_DAYLIGHT_SAVINGS_BEGIN,
    CLASS08_ATTRIBUTE_06_DAYLIGHT_SAVINGS_END,
    CLASS08_ATTRIBUTE_07_DAYLIGHT_SAVINGS_DEVIATION,
    CLASS08_ATTRIBUTE_08_DAYLIGHT_SAVINGS_ENABLED,
    CLASS08_ATTRIBUTE_09_CLOCK_BASE,
} class08_attribute_t;

typedef enum tag_class08_method_t
{
    CLASS08_METHOD_01_ADJUST_TO_QUARTER = 1,
    CLASS08_METHOD_02_ADJUST_TO_MEASURING_PERIOD,
    CLASS08_METHOD_03_ADJUST_TO_MINUTE,
    CLASS08_METHOD_04_ADJUST_TO_PRESET_TIME,
    CLASS08_METHOD_05_PRESET_ADJUSTING_TIME,
    CLASS08_METHOD_06_SHIFT_TIME,
} class08_method_t;

typedef union tag_class08_action_data_t
{
    void                            * p_all;
    int8_t                          * p_m1_adjust_to_quarter;
    int8_t                          * p_m2_adjust_to_measuring_period;
    int8_t                          * p_m3_adjust_to_minute;
    int8_t                          * p_m4_adjust_to_preset_time;
    class08_preset_adjusting_time_t * p_m5_preset_adjusting_time;
    int16_t                         * p_m6_shift_time;
} class08_action_data_t;

/* child record for 1 object of class 08 */
typedef struct tag_class08_child_record_t
{
	uint8_t								logical_name[6];				/* Logical name (OBIS code) of the object. */
	access_right_t						*p_access_right;				/* Access right definition for 1 object    */
	date_time_t							*p_time;						/* Contains the meter's local date and time, its deviation to UTC and the status */
	int16_t								*p_time_zone;					/* The deviation of local, normal time to UTC in minutes */
	uint8_t								*p_status;						/* The clock_status maintained by the meter */
	date_time_t							*p_daylight_savings_begin;		/* Defines the local switch date and time when the local time starts to deviate from the normal time. */
	date_time_t							*p_daylight_savings_end;		/* Defines the local switch date and time when the local time ends to deviate from the local normal time. */
	int8_t								*p_daylight_savings_deviation;	/* Contains the number of minutes by which the deviation in generalized time shall be corrected at daylight savings begin. */
	uint8_t								*p_daylight_savings_enabled;	/* Enable/Disable DST */
	clock_base_t						*p_clock_base;					/* Defines where the basic timing information comes from. */
} class08_child_record_t;
/* Define data type for data of method preset adjusting time (method 05) */
typedef struct tag_preset_adjusting_time_t
{
	date_time_t							* preset_time;
	date_time_t							* validity_interval_start;
	date_time_t							* validity_interval_end;
} preset_adjusting_time_t;
/******************************************************************************
Variable Externs
******************************************************************************/
extern const class08_child_record_t g_objects_child_table_class08[];			/* Import from objects : child table defintion for class 08 */
extern const uint16_t				g_objects_child_table_class08_length;		/* Import from objects : length of child table defintion of class 08 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass08(distributor_params_t *p_params);

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass18PresetAdjustingTime, class08_preset_adjusting_time_t);

void R_DLMS_CLASSES_Class08Init(void);
void R_DLMS_CLASSES_Class08PollingProcessing(void);
void R_DLMS_CLASSES_Class08AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class08AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass08(distributor_params_t *p_params);

/* Declare maro for redirection for each attributes */
#define R_DLMS_IC08_REDIRECT_02(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDateTime(p_params, p_attribute)
#define R_DLMS_IC08_REDIRECT_03(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectLong(p_params, p_attribute)
#define R_DLMS_IC08_REDIRECT_04(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectUnsigned(p_params, p_attribute)
#define R_DLMS_IC08_REDIRECT_05(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDateTime(p_params, p_attribute)
#define R_DLMS_IC08_REDIRECT_06(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDateTime(p_params, p_attribute)
#define R_DLMS_IC08_REDIRECT_07(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectInteger(p_params, p_attribute)
#define R_DLMS_IC08_REDIRECT_08(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectBoolean(p_params, p_attribute)
#define R_DLMS_IC08_REDIRECT_09(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, p_attribute)


#endif /* _R_DLMS_CLASS08_H */

