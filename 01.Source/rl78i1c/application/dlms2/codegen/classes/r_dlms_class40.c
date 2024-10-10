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
* File Name    : r_dlms_class40.c
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
#include "r_dlms_class40.h"
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

/* PUSH OBJECTS LIST */

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass40PushObjectList, class40_push_object_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	/* Structure, 4 elements */
	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 4);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_object->class_id, sizeof(uint16_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_object->logical_name.p_content, p_object->logical_name.length);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_INTEGER, (uint8_t *)&p_object->attribute_index, sizeof(int8_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_object->data_index, sizeof(uint16_t));
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass40PushObjectList, class40_push_object_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	/* Structure, 4 elements */
	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 4, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->class_id, sizeof(uint8_t), TAG_DATA_LONG_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->logical_name.p_content, p_object->logical_name.length, TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->attribute_index, sizeof(int8_t), TAG_DATA_INTEGER, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->data_index, sizeof(uint8_t), TAG_DATA_LONG_UNSIGNED, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}
class40_push_object_array_t *R_DLMS_CLASSES_RedirectClass40PushObjectList(distributor_params_t *p_params, class40_push_object_array_t *p_object, uint16_t array_size)
{
	class40_push_object_array_t					*p_clone_obj;
	uint8_t										*p_alloc, *p_head;
	uint16_t 									i;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);
	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class40_push_object_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_FIXED_ARRAY(p_clone_obj, array_size, class40_push_object_t, p_alloc);
		for (i = 0; i < array_size; i++)
		{
			OBIS_MALLOC_ASSIGN_FIXED_STRING(&(p_clone_obj->p_content[i].logical_name), 6, p_alloc);
		}
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone_obj = (class40_push_object_array_t *)R_DLMS_CLASSES_CreateFixedArray(
			p_params,
			(AbstractFixedArray *)p_object,
			sizeof(class40_push_object_t),
			OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE);
	}
	return p_clone_obj;
}
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass40PushObjectList,
	class40_push_object_t,
	R_DLMS_CLASSES_EncodeClass40PushObjectListArray,
	R_DLMS_CLASSES_DecodeClass40PushObjectListArray,
	NULL
);

OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass40PushObjectListArray,
	class40_push_object_array_t,
	R_DLMS_CLASSES_EncodeClass40PushObjectList
);

OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass40PushObjectListArray,
	class40_push_object_array_t,
	R_DLMS_CLASSES_DecodeClass40PushObjectList
);

OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass40PushObjectListArray,
	class40_push_object_array_t,
	R_DLMS_CLASSES_EncodeClass40PushObjectListArray,
	R_DLMS_CLASSES_DecodeClass40PushObjectListArray,
	R_DLMS_CLASSES_RedirectClass40PushObjectList
);

/* SEND DESTINATION AND METHOD */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass40SendDestAndMethod, class40_send_destination_and_method_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	/* Structure, 2 elements */
	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 3);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_ENUM, (uint8_t *)&p_object->transport_service, sizeof(uint8_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_object->destination.p_content, p_object->destination.length);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_ENUM, (uint8_t *)&p_object->message, sizeof(uint8_t));
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass40SendDestAndMethod, class40_send_destination_and_method_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	/* Structure, 2 elements */
	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 3, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->transport_service, sizeof(uint8_t), TAG_DATA_ENUM, in_data);
		OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(u16, &p_object->destination, TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->message, sizeof(uint8_t), TAG_DATA_ENUM, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}

OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass40SendDestAndMethod, class40_send_destination_and_method_t)
{
	class40_send_destination_and_method_t		*p_clone_obj;
	uint8_t										*p_alloc, *p_head;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class40_send_destination_and_method_t, p_alloc);
	OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->destination, 48, p_alloc);

	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}

OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass40SendDestAndMethod,
	class40_send_destination_and_method_t,
	R_DLMS_CLASSES_EncodeClass40SendDestAndMethod,
	R_DLMS_CLASSES_DecodeClass40SendDestAndMethod,
	R_DLMS_CLASSES_RedirectClass40SendDestAndMethod
);

/* Attribute 4 Communication window array */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass40CommunicationWindow, class40_comm_window_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	/* Structure, 2 elements */
	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)&p_object->start_time, sizeof(date_time_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)&p_object->end_time, sizeof(date_time_t));
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass40CommunicationWindow, class40_comm_window_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	/* Structure, 2 elements */
	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->start_time, sizeof(date_time_t), TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->end_time, sizeof(date_time_t), TAG_DATA_OCTET_STRING, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}


class40_comm_window_array_t *R_DLMS_CLASSES_RedirectClass40CommunicationWindowArray(distributor_params_t *p_params, class40_comm_window_array_t *p_object, uint16_t array_size)
{
	class40_comm_window_array_t					*p_clone_obj;
	uint8_t										*p_alloc, *p_head;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);
	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class40_comm_window_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_FIXED_ARRAY(p_clone_obj, array_size, class40_comm_window_t, p_alloc);

		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone_obj = (class40_comm_window_array_t *)R_DLMS_CLASSES_CreateFixedArray(
			p_params,
			(AbstractFixedArray *)p_object,
			sizeof(class40_comm_window_t),
			OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE);
	}
	return p_clone_obj;
}

OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass40CommunicationWindowArray,
	class40_comm_window_array_t,
	R_DLMS_CLASSES_EncodeClass40CommunicationWindow
);

OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass40CommunicationWindowArray,
	class40_comm_window_array_t,
	R_DLMS_CLASSES_DecodeClass40CommunicationWindow
);

OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass40CommunicationWindowArray,
	class40_comm_window_array_t,
	R_DLMS_CLASSES_EncodeClass40CommunicationWindowArray,
	R_DLMS_CLASSES_DecodeClass40CommunicationWindowArray,
	R_DLMS_CLASSES_RedirectClass40CommunicationWindowArray
);

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class40Init
* Interface     : void R_DLMS_CLASSES_Class40Init(void)
* Description   : Initialize class 40
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class40Init(void)
{
	/* Put init code of class 40 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class40PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class40PollingProcessing(void)
* Description   : Polling process of class 40
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class40PollingProcessing(void)
{
	/* Put polling processing code of class 40 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class40AsscOpened
* Interface     : void R_DLMS_CLASSES_Class40AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 40
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class40AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 40 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class40AsscClosing
* Interface     : void R_DLMS_CLASSES_Class40AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 40
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class40AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 40 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass40
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass40(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 40
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass40(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass40,
		R_DLMS_OBJECTS_Class40Distributor,
		p_params
	);
}


/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass40
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass40(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 40
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass40(distributor_params_t *p_params)
{
	class40_child_record_t	*p_class40_obj = (class40_child_record_t *)p_params->p_child_record;
	uint8_t					*p_alloc, *p_head;
	class40_action_data_t   action_data;

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		p_head = p_params->out_data.p_content;

		switch (p_params->descriptor.attr.attribute_id)
		{
			/* TODO : Put process code for each attrs of class 40 here, start from attr2 */
		case CLASS40_ATTRIBUTE_02_PUSH_OBJECT_LIST:
			R_DLMS_CLASSES_DistributeClass40PushObjectListArray(p_params, p_class40_obj->p_push_object_list);
			break;
		case CLASS40_ATTRIBUTE_03_SEND_DESTINATION_AND_METHOD:
			R_DLMS_CLASSES_DistributeClass40SendDestAndMethod(p_params, p_class40_obj->p_send_destination_and_method);
			break;
		case CLASS40_ATTRIBUTE_04_COMMUNICATION_WINDOW:
			R_DLMS_CLASSES_DistributeClass40CommunicationWindowArray(p_params, p_class40_obj->p_communication_window);
			break;
		case CLASS40_ATTRIBUTE_05_RANDOMISATION_START_INTERVAL:
			R_DLMS_CLASSES_DistributeLongUnsigned(p_params, p_class40_obj->p_randomisation_start_interval);
			break;
		case CLASS40_ATTRIBUTE_06_NUMBER_OF_RETRIES:
			R_DLMS_CLASSES_DistributeUnsigned(p_params, p_class40_obj->p_number_of_retries);
			break;
		case CLASS40_ATTRIBUTE_07_REPETITION_DELAY:
			R_DLMS_CLASSES_DistributeLongUnsigned(p_params, p_class40_obj->p_repetition_delay);
			break;
		default:
			break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		/* Get current malloc position */
		p_alloc = p_head = OBIS_MALLOC_GET_POINTER(p_params);

		switch (p_params->descriptor.method.method_id)
		{
			/* TODO : Put process code for each method of class 40 here, start from method1 */
		case CLASS40_METHOD_01_PUSH:
			OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_all, int8_t, p_alloc);
			OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
			p_params->service_params.created = TRUE;

			if (R_DLMS_CLASSES_DecodeInteger(action_data.p_all, p_params->in_data) == 0)
			{
				p_params->service_params.decode_success = FALSE;
				OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
			else
			{
				p_params->service_params.decode_success = TRUE;
				OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SUCCESS, FALSE);
				OBIS_DISTRIBUTION_SUCCESS(p_params->result);
			}
			break;

		default:
			break;
		}
	}
}

