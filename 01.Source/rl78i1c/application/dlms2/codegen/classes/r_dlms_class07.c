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
* File Name    : r_dlms_class07.c
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
#include "r_dlms_class07.h"
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

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class07_DecodeSelectiveAccess
* Interface     : uint8_t R_DLMS_CLASSES_Class07_DecodeSelectiveAccess(
*               :
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t * R_DLMS_CLASSES_Class07_DecodeSelectiveAccess(distributor_params_t *p_params)
{
	uint8_t u8;
	uint16_t u16;
	uint16_t i;
	uint16_t temp_length;
	uint16_t element_number;

	class07_obj_def_t *p_objs;
	uint16_t object_index;

	class07_range_descriptor_t * p_out_range_descriptor;
	class07_entry_descriptor_t * p_out_entry_descriptor;

	uint8_t *p_alloc, *p_alloc_head;
	p_alloc = p_alloc_head = OBIS_MALLOC_GET_POINTER(p_params);

	// class07_obj_def_t 		*p_capture_object_definition;
	// choice_t 				*p_from_value;
	// choice_t 				*p_to_value;
	// class07_obj_def_array_t *p_array_selected_value;

	if (p_params->selective_access.use == TRUE)
	{
		switch (p_params->selective_access.access_selector)
		{
		case 1: /* range_descriptor */

				/*
				* Decode the range descriptor
				*
				* range_descriptor ::= structure
				* {
				*     restricting_object: capture_object_definition
				*     from_value : CHOICE(string), CHOICE(Float32) or CHOICE(Float32)
				*     from_value : CHOICE(string), CHOICE(Float32) or CHOICE(Float32)
				*     selected_values : array(null)
				* }
				*/

			OBIS_MALLOC_ASSIGN_OBJECT(p_out_range_descriptor, class07_range_descriptor_t, p_alloc);
			OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &u16, 4, p_params->selective_access.raw_access_parameters);
			{
				OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &u16, 4, p_params->selective_access.raw_access_parameters);
				{
					OBIS_MALLOC_ASSIGN_OBJECT(p_out_range_descriptor->p_capture_object_definition, class07_obj_def_t, p_alloc);
					OBIS_MALLOC_ASSIGN_FIXED_STRING(&p_out_range_descriptor->p_capture_object_definition->logical_name, 6, p_alloc);

					p_objs = p_out_range_descriptor->p_capture_object_definition;
					OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_objs->class_id, 2, TAG_DATA_LONG_UNSIGNED, p_params->selective_access.raw_access_parameters);
					OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)p_objs->logical_name.p_content, 6, TAG_DATA_OCTET_STRING, p_params->selective_access.raw_access_parameters);
					OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_objs->attribute_index, 1, TAG_DATA_INTEGER, p_params->selective_access.raw_access_parameters);
					OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_objs->data_index, 2, TAG_DATA_LONG_UNSIGNED, p_params->selective_access.raw_access_parameters);
				}

				OBIS_MALLOC_ASSIGN_OBJECT(p_out_range_descriptor->p_from_value, choice_t, p_alloc);
				p_out_range_descriptor->p_from_value->buffer = p_alloc;
				p_out_range_descriptor->p_from_value->choice.type = (attr_type_t)*p_params->selective_access.raw_access_parameters.p_content;
				p_out_range_descriptor->p_from_value->choice.size = 12;
				p_alloc += 12;
				u16 = R_DLMS_CLASSES_DecodeChoice(p_out_range_descriptor->p_from_value, p_params->selective_access.raw_access_parameters);
				OBIS_ADVANCE_BUFFER(p_params->selective_access.raw_access_parameters, u16);

				OBIS_MALLOC_ASSIGN_OBJECT(p_out_range_descriptor->p_to_value, choice_t, p_alloc);
				p_out_range_descriptor->p_to_value->buffer = p_alloc;
				p_out_range_descriptor->p_to_value->choice.type = (attr_type_t)*p_params->selective_access.raw_access_parameters.p_content;
				p_out_range_descriptor->p_to_value->choice.size = 12;
				p_alloc += 12;
				u16 = R_DLMS_CLASSES_DecodeChoice(p_out_range_descriptor->p_to_value, p_params->selective_access.raw_access_parameters);
				OBIS_ADVANCE_BUFFER(p_params->selective_access.raw_access_parameters, u16);

				OBIS_MALLOC_ASSIGN_OBJECT(p_out_range_descriptor->p_array_selected_value, class07_obj_def_array_t, p_alloc);
				OBIS_MALLOC_ASSIGN_FIXED_ARRAY(
					p_out_range_descriptor->p_array_selected_value,
					4,
					class07_obj_def_t,
					p_alloc
				);

				OBIS_DECODE_ARRAY_TYPE_DEF(u8, (uint16_t *)&element_number, 4, p_params->selective_access.raw_access_parameters);
				p_out_range_descriptor->p_array_selected_value->length = element_number;

				for (i = 0; i < element_number; i++)
				{
					OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &temp_length, 4, p_params->selective_access.raw_access_parameters);
					p_objs = &p_out_range_descriptor->p_array_selected_value->p_content[i];
					OBIS_MALLOC_ASSIGN_FIXED_STRING(&p_objs->logical_name, 6, p_alloc);
					OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_objs->class_id, 2, TAG_DATA_LONG_UNSIGNED, p_params->selective_access.raw_access_parameters);
					OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)p_objs->logical_name.p_content, 6, TAG_DATA_OCTET_STRING, p_params->selective_access.raw_access_parameters);
					OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_objs->attribute_index, 1, TAG_DATA_INTEGER, p_params->selective_access.raw_access_parameters);
					OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_objs->data_index, 2, TAG_DATA_LONG_UNSIGNED, p_params->selective_access.raw_access_parameters);
				}
			}
			p_params->service_params.decode_success = TRUE;
			return (uint8_t *)p_out_range_descriptor;
		case 2: /* entry_descriptor */
			OBIS_MALLOC_ASSIGN_OBJECT(p_out_entry_descriptor, class07_entry_descriptor_t, p_alloc);
			OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &u16, 4, p_params->selective_access.raw_access_parameters);
			{
				OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_out_entry_descriptor->from_entry, 4, TAG_DATA_DOUBLE_LONG_UNSIGNED, p_params->selective_access.raw_access_parameters);
				OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_out_entry_descriptor->to_entry, 4, TAG_DATA_DOUBLE_LONG_UNSIGNED, p_params->selective_access.raw_access_parameters);
				OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_out_entry_descriptor->from_value, 2, TAG_DATA_LONG_UNSIGNED, p_params->selective_access.raw_access_parameters);
				OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_out_entry_descriptor->to_value, 2, TAG_DATA_LONG_UNSIGNED, p_params->selective_access.raw_access_parameters);
			}
			p_params->service_params.decode_success = TRUE;
			return (uint8_t *)p_out_entry_descriptor;
		default:
			break;
		}
	}

	return NULL;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class07Init
* Interface     : void R_DLMS_CLASSES_Class07Init(void)
* Description   : Initialize class 07
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class07Init(void)
{
	/* Put init code of class 07 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class07PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class07PollingProcessing(void)
* Description   : Polling process of class 07
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class07PollingProcessing(void)
{
	/* Put polling processing code of class 07 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class07AsscOpened
* Interface     : void R_DLMS_CLASSES_Class07AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 07
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class07AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 07 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class07AsscClosing
* Interface     : void R_DLMS_CLASSES_Class07AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 07
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class07AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 07 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass07
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass07(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 07
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass07(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass07,
		R_DLMS_OBJECTS_Class07Distributor,
		p_params
	);
}
/* Declare redirect for complex data type */
/* Buffer */
OBIS_DECLARE_REDIRECT_FUNC(R_DLMS_CLASSES_Redirect_Class07_Buffer_Array, class07_buffer_array_t);
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_Distribute_Class07_Buffer_Array,
	class07_buffer_array_t,
	NULL,
	NULL,
	R_DLMS_CLASSES_Redirect_Class07_Buffer_Array
)
/* capture objects */
OBIS_DECLARE_REDIRECT_FUNC(R_DLMS_CLASSES_Redirect_Class07_Obj_Def_Array, class07_obj_def_array_t);
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_Distribute_Obj_Def_Array,
	class07_obj_def_array_t,
	NULL,
	NULL,
	R_DLMS_CLASSES_Redirect_Class07_Obj_Def_Array
)
/* sort object */
OBIS_DECLARE_REDIRECT_FUNC(R_DLMS_CLASSES_Redirect_Class07_Obj_Def, class07_obj_def_t);
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_Distribute_Class07_Obj_Def,
	class07_obj_def_t,
	NULL,
	NULL,
	R_DLMS_CLASSES_Redirect_Class07_Obj_Def
)
/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass07
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass07(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 07
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass07(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class07_child_record_t	*p_class07_obj = (class07_child_record_t *)p_params->p_child_record;
	uint8_t 				class07_obj_def_index;
	class07_obj_def_t		*p_class07_obj_def;
	static uint16_t 		class07_total_transfered = 0;
	uint8_t 				*p_head;
	uint8_t 				u8;
	uint16_t 				u16;

	uint8_t					*p_alloc, *p_alloc_head;
	class07_action_data_t	action_data;

	p_alloc = p_alloc_head = OBIS_MALLOC_GET_POINTER(p_params);

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			/* TODO : Put process code for each attrs of class 07 here, start from attr2 */
		case 2: /* Buffer */
			if (p_params->req_type == REQ_TYPE_GET)
			{
				R_DLMS_CLASSES_Class07_DecodeSelectiveAccess(p_params);
			}
			break;
		case 3: /* Capture object list */
			if (p_params->req_type == REQ_TYPE_GET)
				if (p_class07_obj->p_capture_objects != NULL)
				{
					p_head = p_params->out_data.p_content;
					if (p_params->service_type.get == COSEM_GET_REQUEST_NORMAL)
					{
						class07_total_transfered = 0;
						/* Array header */
						OBIS_DIST_ENCODE_ARRAY_TYPE_DEF(u8, p_params->out_data, p_class07_obj->p_capture_objects->length);
					}

					for (class07_obj_def_index = 0; class07_obj_def_index < p_class07_obj->p_capture_objects->length; class07_obj_def_index++)
					{
						if (class07_total_transfered >= p_class07_obj->p_capture_objects->length)
						{
							break;
						}
						p_class07_obj_def = p_class07_obj->p_capture_objects->p_content + class07_total_transfered;
#if defined(CLASS_07_VERSION) && CLASS_07_VERSION >= 1
						if(p_params->out_data.length < 18)
						{
							break;
						}
						else
						{
							/* nothing*/
						}
						/* Structure, 4 elements */
						OBIS_DIST_ENCODE_STRUCTURE_TYPE_DEF(u8, p_params->out_data, 4);
						{
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_class07_obj_def->class_id, sizeof(uint16_t));
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_class07_obj_def->logical_name.p_content, p_class07_obj_def->logical_name.length);
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_INTEGER, (uint8_t *)&p_class07_obj_def->attribute_index, sizeof(uint8_t));
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_class07_obj_def->data_index, sizeof(uint16_t));
						}
#else
						if(p_params->out_data.length < 15)
						{
							break;
						}
						else
						{
							/* nothing*/
						}
						/* Structure, 3 elements */
						OBIS_DIST_ENCODE_STRUCTURE_TYPE_DEF(u8, p_params->out_data, 3);
						{

							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_class07_obj_def->class_id, sizeof(uint16_t));
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_class07_obj_def->logical_name.p_content, p_class07_obj_def->logical_name.length);
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_INTEGER, (uint8_t *)&p_class07_obj_def->attribute_index, sizeof(uint8_t));
							// OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_class07_obj_def->data_index, sizeof(uint16_t));
						}
#endif
						class07_total_transfered++;
					}

					if (class07_total_transfered < p_class07_obj->p_capture_objects->length)
					{
						*p_params->p_out_encoded_len = (uint16_t)(p_params->out_data.p_content - p_head);
						if (*p_params->p_out_encoded_len > 0) {
							OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, TRUE);
							OBIS_DISTRIBUTION_SUCCESS(p_params->result);
						}
					}
					else
					{
						class07_total_transfered = 0;
						*p_params->p_out_encoded_len = (uint16_t)(p_params->out_data.p_content - p_head);
						if (*p_params->p_out_encoded_len > 0) {
							OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
							OBIS_DISTRIBUTION_SUCCESS(p_params->result);
						}
					}
				}
				else if (p_params->req_type == REQ_TYPE_SET)
				{
					/* Do nothing */
				}
			break;
		case 4:
			R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class07_obj->p_capture_period);
			break;
		case 5:
			R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class07_obj->p_sort_method);
			break;
		case 6:
			if (p_params->req_type == REQ_TYPE_GET)
			{
				if (p_class07_obj->p_sort_object != NULL)
				{
					/* Init */
					p_head = p_params->out_data.p_content;

					/* Encode */
					p_class07_obj_def = p_class07_obj->p_sort_object;
#if defined(CLASS_07_VERSION) && CLASS_07_VERSION >= 1
					/* Structure, 4 elements */
					OBIS_DIST_ENCODE_STRUCTURE_TYPE_DEF(u8, p_params->out_data, 4);
					{
						OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_class07_obj_def->class_id, sizeof(uint16_t));
						OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_class07_obj_def->logical_name.p_content, p_class07_obj_def->logical_name.length);																
						OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_INTEGER, (uint8_t *)&p_class07_obj_def->attribute_index, sizeof(uint8_t));
						OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_class07_obj_def->data_index, sizeof(uint16_t));
					}
#else
					/* Structure, 3 elements */
					OBIS_DIST_ENCODE_STRUCTURE_TYPE_DEF(u8, p_params->out_data, 3);
					{

						OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_class07_obj_def->class_id, sizeof(uint16_t));
						OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_class07_obj_def->logical_name.p_content, p_class07_obj_def->logical_name.length);
						OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_INTEGER, (uint8_t *)&p_class07_obj_def->attribute_index, sizeof(uint8_t));
						// OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_class07_obj_def->data_index, sizeof(uint16_t));
					}
#endif
					/* Ack */
					*p_params->p_out_encoded_len = (uint16_t)(p_params->out_data.p_content - p_head);
					if (*p_params->p_out_encoded_len > 0) {
						OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
						OBIS_DISTRIBUTION_SUCCESS(p_params->result);
					}
				}
				else
				{
					/* FATAL ERROR */
				}
			}
			break;
		case 7:
			R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class07_obj->p_entries_in_use);
			break;
		case 8:
			R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class07_obj->p_profile_entries);
			break;
		default:
			break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		switch (p_params->descriptor.method.method_id)
		{
			/* TODO : Put process code for each method of class 07 here, start from method1 */
		case 1:	/* reset(data) */
		case 2:	/* capture(data) */

				/*
				* Method 1 and method 2 have the same action parameter input.
				* Below code just do decode to buffer pointed by p_m1_reset,
				* but actually buffer is shared to method 2 also, p_m2_capture.
				*/

			OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m1_reset, int8_t, p_alloc);
			OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_alloc_head));
			p_params->service_params.created = TRUE;

			if (R_DLMS_CLASSES_DecodeInteger(action_data.p_m1_reset, p_params->in_data) == 0)
			{
				OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
				break;
			}
			else {
				p_params->service_params.decode_success = TRUE;
			}

			break;

#if (defined(CLASS_07_VERSION) && (CLASS_07_VERSION == 0))
		case 3:	/* get_buffer_by_range (data), no support */
			break;
		case 4:	/* get_buffer_by_index (data), no support */
			break;
#endif

		default:
			break;
		}
	}
}

