/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class71.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS71_H
#define _R_DLMS_CLASS71_H
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

typedef enum tag_class71_attribute_t
{
    CLASS71_ATTRIBUTE_02_MONITORED_VALUE = 2,
    CLASS71_ATTRIBUTE_03_THRESHOLD_ACTIVE,
    CLASS71_ATTRIBUTE_04_THRESHOLD_NORMAL,
    CLASS71_ATTRIBUTE_05_THRESHOLD_EMERGENCY,
    CLASS71_ATTRIBUTE_06_MIN_OVER_THRESHOLD_DURATION,
    CLASS71_ATTRIBUTE_07_MIN_UNDER_THRESHOLD_DURATION,
    CLASS71_ATTRIBUTE_08_EMERGENCY_PROFILE,
    CLASS71_ATTRIBUTE_09_EMERGENCY_PROFILE_GROUP_ID_LIST,
    CLASS71_ATTRIBUTE_10_EMERGENCY_PROFILE_ACTIVE,
    CLASS71_ATTRIBUTE_11_ACTIONS,
} class71_attribute_t;

typedef struct tag_class71_value_definition_t
{
	uint16_t 	class_id;
	FixedString logical_name;
	int8_t 		attribute_index;
} class71_value_definition_t;

typedef struct tag_class71_emergency_profile_t
{
	uint16_t 		*p_emergency_profile_id;
	FixedString		emergency_activation_time;
	uint32_t 		*p_emergency_duration;
} class71_emergency_profile_t;


typedef struct tag_class71_action_item_t
{
	FixedString 	script_logical_name;
	uint16_t 		*p_script_selector;
} class71_action_item_t;

typedef struct tag_class71_action_t
{
	class71_action_item_t *p_action_over_threshold;
	class71_action_item_t *p_action_under_threshold;
} class71_action_t;

/* child record for 1 object of class 71 */
typedef struct tag_class71_child_record_t
{
	uint8_t										logical_name[6];					/* Logical name (OBIS code) of the object. */
	access_right_t								*p_access_right;					/* Access right definition for 1 object    */
	class71_value_definition_t					*p_monitored_value;					/* Defines an attribute of an object to be monitored */
	choice_t									threshold_active;					/* Provides the active threshold value to which the attribute monitored is compared */
	choice_t									threshold_normal;					/* Provides the threshold value to which the attribute monitored is compared when in normal operation */
	choice_t									threshold_emergency;				/* Provides the threshold value to which the attribute monitored is compared when an emergency profile is active */
	uint32_t									*p_min_over_threshold_duration;		/* Defines minimal over threshold duration in seconds required to execute theover threshold action */
	uint32_t									*p_min_under_threshold_duration;	/* Defines minimal under threshold duration in seconds required to execute theunder threshold action */
	class71_emergency_profile_t					*p_emergency_profile ;				/* Emergency profile */
	FixedArrayUint16_t							*p_emergency_profile_group_id_list;	/* Defines a list of group id-s of the emergency profile */
	uint8_t										*p_emergency_profile_active;		/* Indicates that the emergency_profile is active */
	class71_action_t							*p_actions;
} class71_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class71_child_record_t g_objects_child_table_class71[];			/* Import from objects : child table defintion for class 71 */
extern const uint16_t				g_objects_child_table_class71_length;		/* Import from objects : length of child table defintion of class 71 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass71(distributor_params_t *p_params);

void R_DLMS_CLASSES_Class71Init(void);
void R_DLMS_CLASSES_Class71PollingProcessing(void);
void R_DLMS_CLASSES_Class71AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class71AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass71(distributor_params_t *p_params);
/* Distributor function */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass71MonitoredValue, class71_value_definition_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass71EmergencyProfile, class71_emergency_profile_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass71EmergencyProfileList, FixedArrayUint16_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass71Action, class71_action_t);
/* Redirect function */
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass71MonitoredValue, class71_value_definition_t);
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass71EmergencyProfile, class71_emergency_profile_t);
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass71Action, class71_action_t);
/* Declare redirect function */
/* Macro for simple attribute */
#define R_DLMS_IC71_REDIRECT_03(p_params, p_attribute)						R_DLMS_CLASSES_Redirect_ChoiceAttribute(p_params, &p_attribute)
#define R_DLMS_IC71_REDIRECT_04(p_params, p_attribute)						R_DLMS_CLASSES_Redirect_ChoiceAttribute(p_params, &p_attribute)
#define R_DLMS_IC71_REDIRECT_05(p_params, p_attribute)						R_DLMS_CLASSES_Redirect_ChoiceAttribute(p_params, &p_attribute)
#define R_DLMS_IC71_REDIRECT_06(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC71_REDIRECT_07(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC71_REDIRECT_10(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectBoolean(p_params, p_attribute)
/* Macro for complex attribute */			
#define R_DLMS_IC71_REDIRECT_02(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectClass71MonitoredValue(p_params, p_attribute)
#define R_DLMS_IC71_REDIRECT_08(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectClass71EmergencyProfile(p_params, p_attribute)
#define R_DLMS_IC71_REDIRECT_09(p_params, p_attribute, array_size)			p_attribute = R_DLMS_CLASSES_CreatNew_FixedArray_LongUnsigned(p_params, array_size)
#define R_DLMS_IC71_REDIRECT_11(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectClass71Action(p_params, p_attribute)

#endif /* _R_DLMS_CLASS71_H */

