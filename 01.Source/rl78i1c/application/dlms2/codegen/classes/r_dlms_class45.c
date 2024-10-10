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
* File Name    : r_dlms_class45.c
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
#include "r_dlms_class45.h"
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

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass45QualityOfService, quality_of_service_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
	{
		OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 5);
		{
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->p_default->precedence, 			sizeof(uint8_t));
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->p_default->delay, 				sizeof(uint8_t));
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->p_default->reliability, 		sizeof(uint8_t));
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->p_default->peak_throughput, 	sizeof(uint8_t));
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->p_default->mean_throughput, 	sizeof(uint8_t));
		}
		OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 5);
		{
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->p_requested->precedence, 		sizeof(uint8_t));
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->p_requested->delay, 			sizeof(uint8_t));
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->p_requested->reliability, 		sizeof(uint8_t));
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->p_requested->peak_throughput, 	sizeof(uint8_t));
			OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->p_requested->mean_throughput, 	sizeof(uint8_t));
		}
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass45QualityOfService, quality_of_service_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
	{
		OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 5, in_data);
		{
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->p_default->precedence,			sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->p_default->delay,				sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->p_default->reliability,			sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->p_default->peak_throughput,		sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->p_default->mean_throughput,		sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
		}
		OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 5, in_data);
		{
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->p_requested->precedence,			sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->p_requested->delay,				sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->p_requested->reliability,		sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->p_requested->peak_throughput,	sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
			OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->p_requested->mean_throughput,	sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
		}
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}


OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass45QualityOfService, quality_of_service_t)
{
	quality_of_service_t	*p_clone_obj;
	uint8_t					*p_alloc, *p_head;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);
	
	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, quality_of_service_t, p_alloc);
	/* Create allocate for default*/
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj->p_default, qos_element_t, p_alloc);

	/* Create allocate for requested*/
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj->p_requested, qos_element_t, p_alloc);

	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass45QualityOfService,
	quality_of_service_t,
	R_DLMS_CLASSES_EncodeClass45QualityOfService,
	R_DLMS_CLASSES_DecodeClass45QualityOfService,
	R_DLMS_CLASSES_RedirectClass45QualityOfService
);


/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class45Init
* Interface     : void R_DLMS_CLASSES_Class45Init(void)
* Description   : Initialize class 45
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class45Init(void)
{
	/* Put init code of class 45 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class45PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class45PollingProcessing(void)
* Description   : Polling process of class 45
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class45PollingProcessing(void)
{
	/* Put polling processing code of class 45 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class45AsscOpened
* Interface     : void R_DLMS_CLASSES_Class45AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 45
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class45AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 45 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class45AsscClosing
* Interface     : void R_DLMS_CLASSES_Class45AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 45
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class45AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 45 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass45
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass45(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 45
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass45(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass45,
		R_DLMS_OBJECTS_Class45Distributor,
		p_params
	);
}


/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass45
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass45(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 45
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass45(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class45_child_record_t	*p_class45_obj = (class45_child_record_t *)p_params->p_child_record;

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
            /* TODO : Put process code for each attrs of class 45 here, start from attr2 */
			case 2:	
				R_DLMS_CLASSES_DistributeOctetString(p_params, p_class45_obj->p_apn);
				break;
			case 3:	
				R_DLMS_CLASSES_DistributeLongUnsigned(p_params, p_class45_obj->p_pin_code);
				break;
			case 4:	
				R_DLMS_CLASSES_DistributeClass45QualityOfService(p_params, p_class45_obj->p_quality_of_service);
				break;

			default:
				break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
        switch (p_params->descriptor.method.method_id)
		{

		}
	}
}

