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
* File Name    : r_dlms_class22.c
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
#include "r_dlms_class22.h"
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

/* Declare redirect for complex data type */


/* Attribute 02 */
/*************************************************/
/* Redirect function*/
OBIS_DECLARE_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectClass22ExeScript, class22_executed_script_t);

/* Encode */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass22ExeScript, class22_executed_script_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_object->script_logical_name, 6);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_object->script_selector, 2);
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

/* Decode */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass22ExeScript, class22_executed_script_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->script_logical_name, 6, TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->script_selector, 2, TAG_DATA_LONG_UNSIGNED, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}

OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass22ExeScript,
	class22_executed_script_t,
	R_DLMS_CLASSES_EncodeClass22ExeScript,
	R_DLMS_CLASSES_DecodeClass22ExeScript,
	R_DLMS_CLASSES_RedirectClass22ExeScript
);
/*************************************************/

/* Attribute 04 */
/* Encode */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass22ExeTimes, class22_exe_time_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_object->p_time, sizeof(time_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_object->p_date, sizeof(date_t));
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}
/* Decode */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass22ExeTimes, class22_exe_time_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->p_time, sizeof(time_t), TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->p_date, sizeof(date_t), TAG_DATA_OCTET_STRING, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}

OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass22ExeTimesArray,
	class22_exe_time_array_t,
	R_DLMS_CLASSES_EncodeClass22ExeTimes
);

OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass22ExeTimesArray,
	class22_exe_time_array_t,
	R_DLMS_CLASSES_DecodeClass22ExeTimes
);

class22_exe_time_array_t *R_DLMS_CLASSES_RedirectClass22ExeTimesArray(distributor_params_t *p_params, class22_exe_time_array_t *p_object, uint16_t array_size)
{
	class22_exe_time_array_t		*p_clone;
	uint8_t							*p_alloc, *p_head;
	uint16_t						count;

	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone, class22_exe_time_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_FIXED_ARRAY(p_clone, array_size, class22_exe_time_t, p_alloc);
		for (count = 0; count < array_size; count++)
		{
			OBIS_MALLOC_ASSIGN_OBJECT(p_clone->p_content[count].p_time, time_t, p_alloc);
			OBIS_MALLOC_ASSIGN_OBJECT(p_clone->p_content[count].p_date, date_t, p_alloc);
		}
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone = (class22_exe_time_array_t *)R_DLMS_CLASSES_CreateFixedArray(
			p_params,
			(AbstractFixedArray *)p_object,
			sizeof(class22_exe_time_t),
			OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE);
	}

	return p_clone;
}

OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass22ExeTimesArray,
	class22_exe_time_array_t,
	R_DLMS_CLASSES_EncodeClass22ExeTimesArray,
	R_DLMS_CLASSES_DecodeClass22ExeTimesArray,
	R_DLMS_CLASSES_RedirectClass22ExeTimesArray
);

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class22Init
* Interface     : void R_DLMS_CLASSES_Class22Init(void)
* Description   : Initialize class 22
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class22Init(void)
{
	/* Put init code of class 22 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class22PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class22PollingProcessing(void)
* Description   : Polling process of class 22
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class22PollingProcessing(void)
{
	/* Put polling processing code of class 22 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class22AsscOpened
* Interface     : void R_DLMS_CLASSES_Class22AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 22
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class22AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 22 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class22AsscClosing
* Interface     : void R_DLMS_CLASSES_Class22AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 22
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class22AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 22 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass22
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass22(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 22
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass22(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass22,
		R_DLMS_OBJECTS_Class22Distributor,
		p_params
	);
}


/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass22
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass22(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 22
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass22(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class22_child_record_t	*p_class22_obj = (class22_child_record_t *)p_params->p_child_record;

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			/* TODO : Put process code for each attrs of class 22 here, start from attr2 */
		case CLASS22_ATTRIBUTE_02_EXECUTED_SCRIPT:
			R_DLMS_CLASSES_DistributeClass22ExeScript(p_params, p_class22_obj->p_executed_script);
			break;

		case CLASS22_ATTRIBUTE_03_TYPE:
			R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class22_obj->p_type);
			break;

		case CLASS22_ATTRIBUTE_04_EXECUTION_TIME:
			R_DLMS_CLASSES_DistributeClass22ExeTimesArray(p_params, p_class22_obj->p_execution_time);
			break;

		default:
			break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		switch (p_params->descriptor.method.method_id)
		{
			/* TODO : Put process code for each method of class 22 here, start from method1 */
		default:
			break;
		}
	}
}
