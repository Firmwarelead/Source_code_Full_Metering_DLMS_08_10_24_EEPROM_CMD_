/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class09.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS09_H
#define _R_DLMS_CLASS09_H
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

/* Specify action to be applied */
typedef enum tag_service_id_t
{
	ACTION_WRITE_ATTRIBUTE = 1,		/* Write attribute */
	ACTION_EXECUTE_METHOD,			/* Execute specific method */
} service_id_t;

/* Action_specification type */
typedef struct tag_script_action_spec_t
{
	service_id_t service_id;		/* Service id */
	uint16_t class_id;				/* Class id */
	uint8_t logical_name[6];		/* Logical name */
	int16_t index;					/* Index of attribute or specific method */
	FixedString parameter;		/* Parameter for ACTION/SET */
} script_action_t;

typedef OBIS_DECLARE_FIXED_ARRAY(script_action_t, script_actions_t);

/* Script type */
typedef struct tag_script_t
{
	uint16_t script_id;
	script_actions_t * p_actions;
} script_t;

typedef OBIS_DECLARE_FIXED_ARRAY(script_t, script_array_t);

/* class09 action data */
typedef union tag_class09_action_data_t
{
	void		*p_all;
	uint16_t	*p_m1_execute;
} class09_action_data_t;

/* child record for 1 object of class 09 */
typedef struct tag_class09_child_record_t
{
	uint8_t								logical_name[6];		/* Logical name (OBIS code) of the object. */
	access_right_t						*p_access_right;		/* Access right definition for 1 object    */
	script_array_t						*p_scripts;				/* Specifies the different scripts         */
} class09_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class09_child_record_t g_objects_child_table_class09[];			/* Import from objects : child table defintion for class 09 */
extern const uint16_t				g_objects_child_table_class09_length;		/* Import from objects : length of child table defintion of class 09 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass09(distributor_params_t *p_params);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass09ScriptDefinition, script_t);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass09ScriptsArray, script_array_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass09ScriptsArray, script_array_t);
script_array_t * R_DLMS_CLASSES_RedirectClass09ScriptsArray(distributor_params_t *p_params, script_array_t *p_object, uint16_t size_scripts, uint16_t size_actions_max, uint16_t size_parameter_max);
/* Define macro for redirect function of each attribute */
#define R_DLMS_IC09_REDIRECT_02(p_params, p_attribute, size_scripts, size_actions_max, size_parameter_max)			p_attribute = R_DLMS_CLASSES_RedirectClass09ScriptsArray(p_params, p_attribute, size_scripts, size_actions_max, size_parameter_max)

void R_DLMS_CLASSES_Class09Init(void);
void R_DLMS_CLASSES_Class09PollingProcessing(void);
void R_DLMS_CLASSES_Class09AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class09AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass09(distributor_params_t *p_params);

#endif /* _R_DLMS_CLASS09_H */

