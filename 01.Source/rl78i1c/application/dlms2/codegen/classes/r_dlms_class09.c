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
* File Name    : r_dlms_class09.c
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
#include "r_dlms_class09.h"
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


OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass09ScriptDefinition, script_t)
{
	uint16_t				count;
	script_action_t			*p_action;
	distributor_result_t	result;

	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	/* Structure, 2 elements */
	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
	{
		/* 1st element */
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_object->script_id, sizeof(uint16_t));

		/* 2nd element */
		OBIS_ENCODE_ARRAY_TYPE_DEF(u8, out_data, p_object->p_actions->length);
		for (count = 0; count < p_object->p_actions->length; count++) {
			p_action = p_object->p_actions->p_content + count;
			OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 5);
			{
				OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_ENUM, (uint8_t *)&p_action->service_id, 1);
				OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_action->class_id, 2);
				OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)&p_action->logical_name, 6);
				OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_INTEGER, (uint8_t *)&p_action->index, 1);
				OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_action->parameter.p_content, p_action->parameter.length);
			}
		}
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass09ScriptsArray,
	script_array_t,
	R_DLMS_CLASSES_EncodeClass09ScriptDefinition
);

script_array_t * R_DLMS_CLASSES_RedirectClass09ScriptsArray(distributor_params_t *p_params, script_array_t *p_object, uint16_t size_scripts, uint16_t size_actions_max, uint16_t size_parameter_max)
{
	script_array_t * p_clone;
	uint8_t * p_alloc, * p_head;
	uint16_t i;
	uint16_t j;

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	if (p_object == NULL)
	{
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone, script_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_FIXED_ARRAY(p_clone, size_scripts, script_t, p_alloc);

		for (i = 0; i < size_scripts; i++)
		{
			OBIS_MALLOC_ASSIGN_OBJECT(p_clone->p_content[i].p_actions, script_actions_t, p_alloc);
			OBIS_MALLOC_ASSIGN_FIXED_ARRAY( p_clone->p_content[i].p_actions, size_actions_max, script_action_t, p_alloc);
			for(j = 0; j < size_actions_max; j++)
			{
				OBIS_MALLOC_ASSIGN_FIXED_STRING(&(p_clone->p_content[i].p_actions->p_content[j].parameter), size_parameter_max, p_alloc);
			}
		}
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone = (script_array_t *)R_DLMS_CLASSES_CreateFixedArray(
			p_params,
			(AbstractFixedArray *)p_object,
			sizeof(script_t),
			OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE
		);
	}

	return p_clone;
}

OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass09ScriptsArray,
	script_array_t,
	R_DLMS_CLASSES_EncodeClass09ScriptsArray,
	NULL,
	R_DLMS_CLASSES_RedirectClass09ScriptsArray
);

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class09Init
* Interface     : void R_DLMS_CLASSES_Class09Init(void)
* Description   : Initialize class 09
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class09Init(void)
{
	/* Put init code of class 09 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class09PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class09PollingProcessing(void)
* Description   : Polling process of class 09
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class09PollingProcessing(void)
{
	/* Put polling processing code of class 09 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class09AsscOpened
* Interface     : void R_DLMS_CLASSES_Class09AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 09
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class09AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 09 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class09AsscClosing
* Interface     : void R_DLMS_CLASSES_Class09AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 09
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class09AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 09 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass09
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass09(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 09
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass09(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass09,
		R_DLMS_OBJECTS_Class09Distributor,
		p_params
	);
}



/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass09
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass09(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 09
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass09(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class09_child_record_t	*p_class09_obj = (class09_child_record_t *)p_params->p_child_record;
	uint8_t					*p_alloc, *p_head;
	class09_action_data_t	action_data;

	p_alloc = p_head = OBIS_MALLOC_GET_POINTER(p_params);

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
            /* TODO : Put process code for each attrs of class 09 here, start from attr2 */

			case 2: /* Script */
				R_DLMS_CLASSES_DistributeClass09ScriptsArray(p_params, p_class09_obj->p_scripts);
				break;

			default:
				break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		switch (p_params->descriptor.method.method_id)
		{
			case 1:	/* execute (data) */

				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m1_execute, uint16_t, p_alloc);
				OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
				p_params->service_params.created = TRUE;

				if (R_DLMS_CLASSES_DecodeLongUnsigned(action_data.p_m1_execute, p_params->in_data) == 0)
				{
					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
					break;
				}
				else {
					p_params->service_params.decode_success = TRUE;
				}

				break;

			default:
				break;
		}
	}
}


