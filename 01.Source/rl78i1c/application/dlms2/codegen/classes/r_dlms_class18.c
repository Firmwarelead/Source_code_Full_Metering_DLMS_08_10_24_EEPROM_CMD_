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
* File Name    : r_dlms_class18.c
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
#include "r_dlms_class18.h"
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

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass18ImageToActivateInfo, class18_image_to_activate_info_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 3);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_DOUBLE_LONG_UNSIGNED, (uint8_t *)p_object->p_size, 4);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, p_object->identification.p_content, p_object->identification.length);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, p_object->signature.p_content, p_object->signature.length);
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass18ImageToActivateInfoArray,
	class18_image_to_activate_info_array_t,
	R_DLMS_CLASSES_EncodeClass18ImageToActivateInfo
);
/* Declare redirect for complex data type */
class18_image_to_activate_info_array_t *R_DLMS_CLASSES_RedirectClass18ImageToActivateInfoArray(distributor_params_t *p_params, class18_image_to_activate_info_array_t *p_object, uint16_t array_size)
{
	class18_image_to_activate_info_array_t * p_clone;
	uint8_t * p_alloc, * p_head;
	uint16_t i;
	
	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone, class18_image_to_activate_info_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_FIXED_ARRAY(p_clone, array_size, class18_image_to_activate_info_t, p_alloc);
		for (i = 0; i < array_size; i++)
		{
			OBIS_MALLOC_ASSIGN_OBJECT(p_clone->p_content[i].p_size, uint32_t, p_alloc);
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone->p_content[i].identification, 64, p_alloc);
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone->p_content[i].signature, 64, p_alloc);
		}
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone = (class18_image_to_activate_info_array_t *)R_DLMS_CLASSES_CreateFixedArray(
			p_params,
			(AbstractFixedArray *)p_object,
			sizeof(class18_image_to_activate_info_t),
			OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE
		);
	}

	return p_clone;
}

OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass18ImageToActivateInfoArray,
	class18_image_to_activate_info_array_t,
	R_DLMS_CLASSES_EncodeClass18ImageToActivateInfoArray,
	NULL,
	NULL
);

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass18ImageTransferInitiate, class18_image_transfer_inititate_t)
{
    OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
    OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

    OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
    {
        OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(length, &p_object->image_identifier, TAG_DATA_OCTET_STRING, in_data);
        OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->p_size, 4, TAG_DATA_DOUBLE_LONG_UNSIGNED, in_data);
    }

    OBIS_TYPE_DECODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass18ImageBlockTransfer, class18_image_block_transfer_t)
{
    OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
    OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

    OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
    {
        OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)p_object->p_block_no, 4, TAG_DATA_DOUBLE_LONG_UNSIGNED, in_data);
        OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(length, &p_object->image_block_value, TAG_DATA_OCTET_STRING, in_data);
    }

    OBIS_TYPE_DECODER_FUNC_RET();
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class18Init
* Interface     : void R_DLMS_CLASSES_Class18Init(void)
* Description   : Initialize class 18
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class18Init(void)
{
	/* Put init code of class 18 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class18PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class18PollingProcessing(void)
* Description   : Polling process of class 18
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class18PollingProcessing(void)
{
	/* Put polling processing code of class 18 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class18AsscOpened
* Interface     : void R_DLMS_CLASSES_Class18AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 18
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class18AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 18 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class18AsscClosing
* Interface     : void R_DLMS_CLASSES_Class18AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 18
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class18AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 18 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass18
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass18(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 18
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass18(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass18,
		R_DLMS_OBJECTS_Class18Distributor,
		p_params
	);
}


/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass18
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass18(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 18
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass18(distributor_params_t *p_params)
{
	class18_child_record_t	*p_class18_obj = (class18_child_record_t *)p_params->p_child_record;
	uint8_t                 * p_alloc, *p_head;
	uint16_t				u16;
	class18_action_data_t   action_data;

	/* Get current malloc position */
	p_alloc = p_head = OBIS_MALLOC_GET_POINTER(p_params);

	if (p_params->req_type == REQ_TYPE_GET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			/* TODO : Put process code for each attrs of class 18 here, start from attr2 */

			// 2. Image Block Size                              (static)        double-long-unsigned
			// 3. Image Transferred Blocks Status               (dyn.)          bit-string
			// 4. Image First Not Transferred Block Number      (dyn.)          double-long-unsigned
			// 5. Image Transfer Enabled                        (static)        boolean
			// 6. Image Transfer Status                         (dyn.)          enum
			// 7. Image To Activate Info                        (dyn.)          array

		case CLASS18_ATTRIBUTE_02_BLOCK_SIZE:
			R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class18_obj->p_image_block_size);
			break;
		case CLASS18_ATTRIBUTE_03_BLOCK_TRANSFER_STATUS:
			R_DLMS_CLASSES_DistributeBitString(p_params, p_class18_obj->p_image_transferred_blocks_status);
			break;
		case CLASS18_ATTRIBUTE_04_FIRST_NOT_TRANSFERRED_BLOCK_NUMBER:
			R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class18_obj->p_image_first_not_transferred_block_number);
			break;
		case CLASS18_ATTRIBUTE_05_TRANSFER_ENABLED:
			R_DLMS_CLASSES_DistributeBoolean(p_params, p_class18_obj->p_image_transfer_enabled);
			break;
		case CLASS18_ATTRIBUTE_06_TRANSFER_STATUS:
			R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class18_obj->p_image_transfer_status);
			break;
		case CLASS18_ATTRIBUTE_07_IMAGES_TO_ACTIVATE_INFO:
			R_DLMS_CLASSES_DistributeClass18ImageToActivateInfoArray(p_params, p_class18_obj->p_image_to_activate_info);
			break;

		default:
			break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		p_params->service_params.decode_success = TRUE;
		OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SUCCESS, FALSE);
		OBIS_DISTRIBUTION_SUCCESS(p_params->result);

		switch (p_params->descriptor.method.method_id)
		{
			/* TODO : Put process code for each method of class 18 here, start from method1 */
		case CLASS18_METHOD_01_IMAGE_TRANSFER_INITIATE:
			/* Maximum 128 bytes image identifier supported */
			OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m1_image_transfer_initiate, class18_image_transfer_inititate_t, p_alloc);
			OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m1_image_transfer_initiate->p_size, uint32_t, p_alloc);
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&action_data.p_m1_image_transfer_initiate->image_identifier, 128, p_alloc);
			OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
			p_params->service_params.created = TRUE;

			if (R_DLMS_CLASSES_DecodeClass18ImageTransferInitiate(action_data.p_m1_image_transfer_initiate, p_params->in_data) == 0)
			{
				p_params->service_params.decode_success = FALSE;
				OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
			break;
		case CLASS18_METHOD_02_IMAGE_BLOCK_TRANSFER:
			/* Full malloc size remain to store image block data */
            OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m2_image_block_transfer, class18_image_block_transfer_t, p_alloc);
            OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m2_image_block_transfer->p_block_no, uint32_t, p_alloc);
			OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
			u16 = OBIS_MALLOC_REMAIN_SIZE(p_params);
            OBIS_MALLOC_ASSIGN_VARIANT_STRING(&action_data.p_m2_image_block_transfer->image_block_value, u16, p_alloc);
            OBIS_MALLOC_ADVANCE_BUFFER(p_params, u16);
            p_params->service_params.created = TRUE;

			if (R_DLMS_CLASSES_DecodeClass18ImageBlockTransfer(action_data.p_m2_image_block_transfer, p_params->in_data) == 0)
			{
				p_params->service_params.decode_success = FALSE;
				OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}

			break;
		case CLASS18_METHOD_03_IMAGE_VERIFY:
		case CLASS18_METHOD_04_IMAGE_ACTIVATE:
			OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_all, int8_t, p_alloc);
			OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
			p_params->service_params.created = TRUE;

			if (R_DLMS_CLASSES_DecodeInteger(action_data.p_all, p_params->in_data) == 0)
			{
				p_params->service_params.decode_success = FALSE;
				OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}

			break;

		default:
			break;
		}
	}
}

