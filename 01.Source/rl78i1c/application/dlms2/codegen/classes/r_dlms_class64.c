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
* File Name    : r_dlms_class64.c
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
#include "r_dlms_class64.h"
#include "r_dlms_objects.h"

#include <stddef.h>

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


#if defined(CLASS_64_VERSION) && CLASS_64_VERSION >= 1

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass64CertificateInfo, class64_certificate_info_t)
{
	structure_link_t encode_links[] = {
		{ TAG_DATA_ENUM			, (uint8_t *)&p_object->certificate_entity			, sizeof(uint8_t)					},
		{ TAG_DATA_ENUM			, (uint8_t *)&p_object->certificate_type			, sizeof(uint8_t)					},
		{ TAG_DATA_OCTET_STRING	, p_object->serial_number.p_content		, p_object->serial_number.length	},
		{ TAG_DATA_OCTET_STRING	, p_object->issuer.p_content			, p_object->issuer.length			},
		{ TAG_DATA_OCTET_STRING	, p_object->subject.p_content			, p_object->subject.length			},
		{ TAG_DATA_OCTET_STRING	, p_object->subject_alt_name.p_content	, p_object->subject_alt_name.length	},
	};

	uint16_t	count;

	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	/* Structure */
	length = sizeof(encode_links) / sizeof(structure_link_t);
	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, length);
	for (count = 0; count < length; count++)
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(
			u16,
			out_data,
			encode_links[count].type,
			encode_links[count].ptr,
			encode_links[count].size
		);
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass64CertificateInfo, class64_certificate_info_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	/* Structure, 6 elements */
	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 6, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->certificate_entity, sizeof(uint8_t), TAG_DATA_ENUM, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->certificate_type, sizeof(uint8_t), TAG_DATA_ENUM, in_data);
		OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(length, &p_object->serial_number, TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(length, &p_object->issuer, TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(length, &p_object->subject, TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(length, &p_object->subject_alt_name, TAG_DATA_OCTET_STRING, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}

OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass64CertificateInfoArray,
	class64_certificate_info_array_t,
	R_DLMS_CLASSES_EncodeClass64CertificateInfo
);

OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass64CertificateInfoArray,
	class64_certificate_info_array_t,
	R_DLMS_CLASSES_DecodeClass64CertificateInfo
);
class64_certificate_info_array_t *R_DLMS_CLASSES_RedirectClass64CertificateInfoArray(distributor_params_t *p_params, class64_certificate_info_array_t *p_object, uint16_t size)
{
	class64_certificate_info_array_t	*p_clone_obj;
	uint8_t								*p_alloc, *p_head;
	uint16_t							count;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);
	
	

	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class64_certificate_info_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone_obj, size, class64_certificate_info_t, p_alloc);
		for (count = 0; count < size; count++)
		{
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->p_content[count].serial_number, 30, p_alloc);
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->p_content[count].issuer, 30, p_alloc);
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->p_content[count].subject, 30, p_alloc);
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->p_content[count].subject_alt_name, 30, p_alloc);

		}
		p_clone_obj->p_active = NULL;
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone_obj = (class64_certificate_info_array_t *)R_DLMS_CLASSES_CreateVariantArray(
			p_params,
			(AbstractVariantArray *)p_object,
			sizeof(class64_certificate_info_t),
			OBIS_MALLOC_OPTION_CREATENEW
		);
		ASSERT_TRUE_RET_NULL(p_clone_obj == NULL);
	}

	return p_clone_obj;

}
OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass64CertificateInfoArray,
	class64_certificate_info_array_t,
	R_DLMS_CLASSES_EncodeClass64CertificateInfoArray,
	R_DLMS_CLASSES_DecodeClass64CertificateInfoArray,
	R_DLMS_CLASSES_RedirectClass64CertificateInfoArray
);

#endif
class64_key_unwrapped_transfer_data_array_t *R_DLMS_CLASSES_RedirectKeyTransferDataAction02(distributor_params_t *p_params, class64_key_transfer_data_array_t *p_wrapped_object)
{
	class64_key_unwrapped_transfer_data_array_t * p_clone;
	uint8_t * p_alloc, * p_head;
	uint16_t i;

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone, class64_key_unwrapped_transfer_data_array_t, p_alloc);
	OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone, p_wrapped_object->length, class64_key_unwrapped_transfer_data_t, p_alloc);
	for (i = 0; i < p_wrapped_object->length; i++)
	{
		OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone->p_content[i].key_unwrapped, 16, p_alloc);
		p_clone->p_content[i].key_unwrapped.length = 16;
		p_clone->p_content[i].key_id = p_wrapped_object->p_content[i].key_id;
		p_clone->p_active = NULL;
	}
	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	p_clone->length = p_wrapped_object->length;
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone;
}
/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class64Init
* Interface     : void R_DLMS_CLASSES_Class64Init(void)
* Description   : Initialize class 64
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class64Init(void)
{
	/* Put init code of class 64 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class64PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class64PollingProcessing(void)
* Description   : Polling process of class 64
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class64PollingProcessing(void)
{
	/* Put polling processing code of class 64 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class64AsscOpened
* Interface     : void R_DLMS_CLASSES_Class64AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 64
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class64AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 64 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class64AsscClosing
* Interface     : void R_DLMS_CLASSES_Class64AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 64
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class64AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 64 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass64
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass64(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 64
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass64(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass64,
		R_DLMS_OBJECTS_Class64Distributor,
		p_params
	);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass64
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass64(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 64
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass64(distributor_params_t *p_params)
{
	class64_child_record_t	*p_class64_obj = (class64_child_record_t *)p_params->p_child_record;
	MandatoryString			method_invocation_str;
	uint8_t					u8, mask;
	uint16_t				u16, count;

	uint8_t					*p_alloc, *p_head;
	class64_action_data_t	action_data;

	p_alloc = p_head = OBIS_MALLOC_GET_POINTER(p_params);

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
            /* TODO : Put process code for each attrs of class 64 here, start from attr2 */
			case 2:	/* security_policy */
				R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class64_obj->p_security_policy);
				break;
			case 3:	/* security_suite */
				R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class64_obj->p_security_suite);
				break;
			case 4:	/* client_system_title */
				R_DLMS_CLASSES_DistributeFixedString(p_params, TAG_DATA_OCTET_STRING, p_class64_obj->p_client_system_title);
				break;
			case 5:	/* server_system_title */
				R_DLMS_CLASSES_DistributeFixedString(p_params, TAG_DATA_OCTET_STRING, p_class64_obj->p_server_system_title);
				break;
#if defined(CLASS_64_VERSION) && CLASS_64_VERSION >= 1
			case 6:	/* certificates */
				R_DLMS_CLASSES_DistributeClass64CertificateInfoArray(p_params, p_class64_obj->p_certificates);
				break;
#endif
			default:
				break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		method_invocation_str = p_params->in_data;

        switch (p_params->descriptor.method.method_id)
		{
			/* method 1, 4, 5 use the same data input, enum */
			case 1:	/* security_activate(data) */
#if defined(CLASS_64_VERSION) && CLASS_64_VERSION >= 1
			case 4:	/* generate_key_pair(data) */
			case 5:	/* generate_certificate_request(data) */
#endif
				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m1_security_activate, class64_security_activate_data_t, p_alloc);
				OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
				p_params->service_params.created = TRUE;

				if (R_DLMS_CLASSES_DecodeEnum(action_data.p_m1_security_activate, method_invocation_str) == 0)
				{
					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
					break;
				}
				else if (p_params->descriptor.method.method_id == 1)
				{
					/* Prevent of changing the security policy to mask off protections that had added */
#if defined(CLASS_64_VERSION)
#if	CLASS_64_VERSION == 0
					/* Only allow first 2 bits */
					(*action_data.p_m1_security_activate) &= 0x03;
					u8   = (*action_data.p_m1_security_activate);
					mask = (*p_class64_obj->p_security_policy) & 0x03;
					if ((u8 & mask) < mask) {
						OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TEMPORARY_FAILURE, FALSE);
						OBIS_DISTRIBUTION_FAILED(p_params->result);
						break;
					}
#elif CLASS_64_VERSION == 1
					/* Only allow last 6 bits */
					(*action_data.p_m1_security_activate) &= 0xFC;
					u8   = (*action_data.p_m1_security_activate);
					mask = (*p_class64_obj->p_security_policy) & 0xFC;
					if ((u8 & mask) < mask) {
						OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TEMPORARY_FAILURE, FALSE);
						OBIS_DISTRIBUTION_FAILED(p_params->result);
						break;
					}
#endif
#endif
				}

				p_params->service_params.decode_success = TRUE;
				break;

			/* method 2, 3 use the same data input, array of structure (class64_key_transfer_data_t) */
			case 2:	/* global_key_transfer(data) */
#if defined(CLASS_64_VERSION) && CLASS_64_VERSION >= 1
			case 3:	/* key_agreement(data) */
#endif
				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m2_key_transfer, class64_key_transfer_data_array_t, p_alloc);
				OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(action_data.p_m2_key_transfer, 4, class64_key_transfer_data_t, p_alloc);
				for (count = 0; count < action_data.p_m2_key_transfer->alloc_size; count++) {
					OBIS_MALLOC_ASSIGN_VARIANT_STRING(&action_data.p_m2_key_transfer->p_content[count].key_wrapped, 96, p_alloc);
				}
				p_params->service_params.created = TRUE;

				OBIS_DIST_DECODE_ARRAY_TYPE_DEF(u8, &action_data.p_m2_key_transfer->length, 4, method_invocation_str);
				for (count = 0; count < action_data.p_m2_key_transfer->length; count++) {
					OBIS_DIST_DECODE_STRUCTURE_TYPE_DEF(u8, &u16, 2, method_invocation_str);
					{
						OBIS_DIST_DECODE_THEN_ADVANCE_BUF(u16, &action_data.p_m2_key_transfer->p_content[count].key_id, sizeof(uint8_t), TAG_DATA_ENUM, method_invocation_str);
						OBIS_DIST_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(u16, &action_data.p_m2_key_transfer->p_content[count].key_wrapped, TAG_DATA_OCTET_STRING, method_invocation_str);
					}
				}
				p_params->service_params.decode_success = TRUE;
				OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
				break;

#if defined(CLASS_64_VERSION) && CLASS_64_VERSION >= 1
			case 6:	/* import_certificate(data) */
				
				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m6_import_certificate, class64_import_certificate_data_t, p_alloc);
				OBIS_MALLOC_ASSIGN_VARIANT_STRING(action_data.p_m6_import_certificate, 448, p_alloc);
				p_params->service_params.created = TRUE;

				if (R_DLMS_CLASSES_DecodeOctetString(action_data.p_m6_import_certificate, method_invocation_str) == 0)
				{
					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
					break;
				}
				else {
					p_params->service_params.decode_success = TRUE;
				}

				break;

			/* method 7, 8 use the same data input, structure (class64_export_certificate_data_t) */
			case 7:
			case 8:
				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m7_export_certificate, class64_export_certificate_data_t, p_alloc);
				OBIS_DIST_DECODE_STRUCTURE_TYPE_DEF(u8, &u16, 2, method_invocation_str);
				{
					OBIS_DIST_DECODE_THEN_ADVANCE_BUF(u16, &action_data.p_m7_export_certificate->type, sizeof(uint8_t), TAG_DATA_ENUM, method_invocation_str);
					if (action_data.p_m7_export_certificate->type == 0) {			/* by entity */
						OBIS_DIST_DECODE_STRUCTURE_TYPE_DEF(u8, &u16, 3, method_invocation_str);
						{
							OBIS_DIST_DECODE_THEN_ADVANCE_BUF(u16, &action_data.p_m7_export_certificate->options.by_entity.entity, sizeof(uint8_t), TAG_DATA_ENUM, method_invocation_str);
							OBIS_DIST_DECODE_THEN_ADVANCE_BUF(u16, &action_data.p_m7_export_certificate->options.by_entity.type  , sizeof(uint8_t), TAG_DATA_ENUM, method_invocation_str);
							OBIS_MALLOC_ASSIGN_VARIANT_STRING(&action_data.p_m7_export_certificate->options.by_entity.title, 192, p_alloc);
							OBIS_DIST_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(u16, &action_data.p_m7_export_certificate->options.by_entity.title, TAG_DATA_OCTET_STRING, method_invocation_str);
						}
					}
					else if (action_data.p_m7_export_certificate->type == 1) {	/* by serial */
						OBIS_DIST_DECODE_STRUCTURE_TYPE_DEF(u8, &u16, 2, method_invocation_str);
						{
							OBIS_MALLOC_ASSIGN_VARIANT_STRING(&action_data.p_m7_export_certificate->options.by_serial.serial_number, 192, p_alloc);
							OBIS_DIST_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(u16, &action_data.p_m7_export_certificate->options.by_serial.serial_number, TAG_DATA_OCTET_STRING, method_invocation_str);
							OBIS_MALLOC_ASSIGN_VARIANT_STRING(&action_data.p_m7_export_certificate->options.by_serial.issuer, 192, p_alloc);
							OBIS_DIST_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(u16, &action_data.p_m7_export_certificate->options.by_serial.issuer, TAG_DATA_OCTET_STRING, method_invocation_str);
						}
					}
					else {
						OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
						OBIS_DISTRIBUTION_FAILED(p_params->result);
						break;
					}
				}
				p_params->service_params.created = TRUE;
				p_params->service_params.decode_success = TRUE;
				break;
#endif
			default:
				break;
		}
	}
}

