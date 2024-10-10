/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************	
* File Name    : r_dlms_class71.c
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_library_process.h"
#include "r_dlms_config.h"
#include "r_dlms_classes.h"
#include "r_dlms_class71.h"
#include "r_dlms_objects.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/


OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass71MonitoredValue, class71_value_definition_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 3);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_object->class_id, sizeof(uint16_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_object->logical_name.p_content, p_object->logical_name.length);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_INTEGER, (uint8_t *)&p_object->attribute_index, sizeof(int8_t));
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass71MonitoredValue, class71_value_definition_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 3, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->class_id, sizeof(uint16_t), TAG_DATA_LONG_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->logical_name.p_content, p_object->logical_name.length, TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->attribute_index, sizeof(int8_t), TAG_DATA_INTEGER, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}
/* Declare redirect for complex data type */
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass71MonitoredValue, class71_value_definition_t)
{
	class71_value_definition_t		*p_clone_obj;
	uint8_t							*p_alloc, *p_head;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class71_value_definition_t, p_alloc);
	OBIS_MALLOC_ASSIGN_FIXED_STRING(&p_clone_obj->logical_name, 6, p_alloc);

	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass71MonitoredValue,
	class71_value_definition_t,
    R_DLMS_CLASSES_EncodeClass71MonitoredValue,
    NULL,
	R_DLMS_CLASSES_RedirectClass71MonitoredValue
);

/* EMERGENCY_PROFILE */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass71EmergencyProfile, class71_emergency_profile_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 3);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)p_object->p_emergency_profile_id, sizeof(uint16_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, p_object->emergency_activation_time.p_content, p_object->emergency_activation_time.length);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_DOUBLE_LONG_UNSIGNED, (uint8_t *)p_object->p_emergency_duration, sizeof(uint32_t));
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass71EmergencyProfile, class71_emergency_profile_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 3, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->p_emergency_profile_id, sizeof(uint16_t), TAG_DATA_LONG_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->emergency_activation_time.p_content, p_object->emergency_activation_time.length, TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->p_emergency_duration, sizeof(uint32_t), TAG_DATA_DOUBLE_LONG_UNSIGNED, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}
/* Declare redirect for complex data type */
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass71EmergencyProfile, class71_emergency_profile_t)
{
	class71_emergency_profile_t		*p_clone_obj;
	uint8_t							*p_alloc, *p_head;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class71_emergency_profile_t, p_alloc);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj->p_emergency_profile_id, uint16_t, p_alloc);
	OBIS_MALLOC_ASSIGN_FIXED_STRING(&p_clone_obj->emergency_activation_time, 12, p_alloc);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj->p_emergency_duration, uint32_t, p_alloc);

	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass71EmergencyProfile,
	class71_emergency_profile_t,
    R_DLMS_CLASSES_EncodeClass71EmergencyProfile,
    R_DLMS_CLASSES_DecodeClass71EmergencyProfile,
	R_DLMS_CLASSES_RedirectClass71EmergencyProfile
);


/* EMERGENCY_PROFILE_GROUP_ID_LIST */

OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass71EmergencyProfileList,
	FixedArrayUint16_t,
	R_DLMS_CLASSES_EncodeLongUnsigned
);

OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass71EmergencyProfileList,
	FixedArrayUint16_t,
	R_DLMS_CLASSES_DecodeLongUnsigned
);
/* Declare redirect for complex data type */

OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass71EmergencyProfileList,
	FixedArrayUint16_t,
    R_DLMS_CLASSES_EncodeClass71EmergencyProfileList,
    R_DLMS_CLASSES_DecodeClass71EmergencyProfileList,
	R_DLMS_CLASSES_CreatNew_FixedArray_LongUnsigned
);

/* ACTION */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass71Action, class71_action_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
	{
		OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
		{
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_object->p_action_over_threshold->script_logical_name.p_content, p_object->p_action_over_threshold->script_logical_name.length);
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)p_object->p_action_over_threshold->p_script_selector, sizeof(uint16_t));
		}
		OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
		{
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_object->p_action_under_threshold->script_logical_name.p_content, p_object->p_action_under_threshold->script_logical_name.length);
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)p_object->p_action_under_threshold->p_script_selector, sizeof(uint16_t));
		}
	}
	

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass71Action, class71_action_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
	{
		OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
		{
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->p_action_over_threshold->script_logical_name.p_content, p_object->p_action_over_threshold->script_logical_name.length, TAG_DATA_OCTET_STRING, in_data);
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->p_action_over_threshold->p_script_selector, sizeof(uint16_t), TAG_DATA_LONG_UNSIGNED, in_data);
		}
		OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
		{
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->p_action_under_threshold->script_logical_name.p_content, p_object->p_action_under_threshold->script_logical_name.length, TAG_DATA_OCTET_STRING, in_data);
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->p_action_under_threshold->p_script_selector, sizeof(uint16_t), TAG_DATA_LONG_UNSIGNED, in_data);
		}
	}
	OBIS_TYPE_DECODER_FUNC_RET();
}
/* Declare redirect for complex data type */
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass71Action, class71_action_t)
{
	class71_action_t		*p_clone_obj;
	uint8_t					*p_alloc, *p_head;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class71_action_t, p_alloc);

	/* Create allocate for p_action_over_threshold*/
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj->p_action_over_threshold, class71_action_item_t, p_alloc);
	OBIS_MALLOC_ASSIGN_FIXED_STRING(&p_clone_obj->p_action_over_threshold->script_logical_name, 6, p_alloc);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj->p_action_over_threshold->p_script_selector, uint16_t, p_alloc);

	/* Create allocate for p_action_under_threshold*/
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj->p_action_under_threshold, class71_action_item_t, p_alloc);
	OBIS_MALLOC_ASSIGN_FIXED_STRING(&p_clone_obj->p_action_under_threshold->script_logical_name, 6, p_alloc);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj->p_action_under_threshold->p_script_selector, uint16_t, p_alloc);

	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass71Action,
	class71_action_t,
	R_DLMS_CLASSES_EncodeClass71Action,
	R_DLMS_CLASSES_DecodeClass71Action,
	R_DLMS_CLASSES_RedirectClass71Action
);

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class71Init
* Interface     : void R_DLMS_CLASSES_Class71Init(void)
* Description   : Initialize class 71
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class71Init(void)
{
	/* Put init code of class 71 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class71PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class71PollingProcessing(void)
* Description   : Polling process of class 71
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class71PollingProcessing(void)
{
	/* Put polling processing code of class 71 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class71AsscOpened
* Interface     : void R_DLMS_CLASSES_Class71AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 71
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class71AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 71 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class71AsscClosing
* Interface     : void R_DLMS_CLASSES_Class71AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 71
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class71AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 71 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass71
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass71(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 71
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass71(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass71,
		R_DLMS_OBJECTS_Class71Distributor,
		p_params
	);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass71
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass71(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 71
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass71(distributor_params_t *p_params)
{
	class71_child_record_t	*p_class71_obj = (class71_child_record_t *)p_params->p_child_record;

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			/* TODO : Put process code for each attrs of class 71 here, start from attr2 */
			case CLASS71_ATTRIBUTE_02_MONITORED_VALUE:
				R_DLMS_CLASSES_DistributeClass71MonitoredValue(p_params, p_class71_obj->p_monitored_value);
				break;
			case CLASS71_ATTRIBUTE_03_THRESHOLD_ACTIVE:
				R_DLMS_CLASSES_DistributeChoice(p_params, (choice_t *)&p_class71_obj->threshold_active);
				break;
			case CLASS71_ATTRIBUTE_04_THRESHOLD_NORMAL:
				R_DLMS_CLASSES_DistributeChoice(p_params, (choice_t *)&p_class71_obj->threshold_normal);
				break;
			case CLASS71_ATTRIBUTE_05_THRESHOLD_EMERGENCY:
				R_DLMS_CLASSES_DistributeChoice(p_params, (choice_t *)&p_class71_obj->threshold_emergency);
				break;
			case CLASS71_ATTRIBUTE_06_MIN_OVER_THRESHOLD_DURATION:
				R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class71_obj->p_min_over_threshold_duration);
				break;
			case CLASS71_ATTRIBUTE_07_MIN_UNDER_THRESHOLD_DURATION:
				R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class71_obj->p_min_under_threshold_duration);
				break;
			case CLASS71_ATTRIBUTE_08_EMERGENCY_PROFILE:
				R_DLMS_CLASSES_DistributeClass71EmergencyProfile(p_params, p_class71_obj->p_emergency_profile);
				break;
			case CLASS71_ATTRIBUTE_09_EMERGENCY_PROFILE_GROUP_ID_LIST:
				R_DLMS_CLASSES_DistributeClass71EmergencyProfileList(p_params, p_class71_obj->p_emergency_profile_group_id_list);
				break;
			case CLASS71_ATTRIBUTE_10_EMERGENCY_PROFILE_ACTIVE:
				R_DLMS_CLASSES_DistributeBoolean(p_params, p_class71_obj->p_emergency_profile_active);
				break;
			case CLASS71_ATTRIBUTE_11_ACTIONS:
				R_DLMS_CLASSES_DistributeClass71Action(p_params, p_class71_obj->p_actions);
				break;
			default:
				break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
        switch (p_params->descriptor.method.method_id)
		{
			default:
				break;
		}
	}
}

