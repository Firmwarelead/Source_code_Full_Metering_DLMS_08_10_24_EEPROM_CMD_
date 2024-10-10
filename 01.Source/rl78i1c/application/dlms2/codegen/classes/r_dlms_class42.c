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
* File Name    : r_dlms_class42.c
* Version      : 1.00
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Processing for OBIS Class 42
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 27.03.2018 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_library_process.h"
#include "r_dlms_config.h"
#include "r_dlms_classes.h"
#include "r_dlms_class42.h"
#include "r_dlms_objects.h"
#include "r_dlms_usercode_class42.h"

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

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass42IpOption, class42_ip_option_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	/* Structure, 3 elements */
	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 3);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->type, sizeof(uint8_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->length, sizeof(uint8_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)p_object->data.p_content, (uint16_t)p_object->data.length);
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass42IpOptionArray,
	class42_ip_option_array_t,
	R_DLMS_CLASSES_EncodeClass42IpOption
);

class42_ip_option_array_t *R_DLMS_CLASSES_Redirect_IpOptionArray(distributor_params_t *p_params, class42_ip_option_array_t *p_object, uint16_t size)
{
	class42_ip_option_array_t		*p_clone_obj;
	uint8_t							*p_alloc, *p_head;
	uint16_t						count;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);
	
	

	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class42_ip_option_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone_obj, size, class42_ip_option_t, p_alloc);
		for (count = 0; count < size; count++)
		{
			OBIS_MALLOC_ASSIGN_FIXED_STRING(&p_clone_obj->p_content[count].data, CLASS42_SUPPORT_MAX_ACTION_DATA, p_alloc);
		}
		p_clone_obj->p_active = NULL;
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone_obj = (class42_ip_option_array_t *)R_DLMS_CLASSES_CreateVariantArray(
			p_params,
			(AbstractVariantArray *)p_object,
			sizeof(class42_ip_option_t),
			OBIS_MALLOC_OPTION_CREATENEW
		);
		ASSERT_TRUE_RET_NULL(p_clone_obj == NULL);
	}

	return p_clone_obj;

}

OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass42IpOptionArray,
	class42_ip_option_array_t,
	R_DLMS_CLASSES_EncodeClass42IpOptionArray,
	NULL,
    NULL
);


/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class42Init
* Interface     : void R_DLMS_CLASSES_Class42Init(void)
* Description   : Initialize class 42
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class42Init(void)
{
	/* Put init code of class 42 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class42PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class42PollingProcessing(void)
* Description   : Polling process of class 42
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class42PollingProcessing(void)
{
	/* Put polling processing code of class 42 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class42AsscOpened
* Interface     : void R_DLMS_CLASSES_Class42AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 42
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class42AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 42 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class42AsscClosing
* Interface     : void R_DLMS_CLASSES_Class42AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 42
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class42AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 42 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass42
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass42(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 42
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass42(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass42,
		R_DLMS_OBJECTS_Class42Distributor,
		p_params
	);
}
void R_DLMS_Ipv4_ConverterByteArrayToUint32(uint8_t * p_u8, uint32_t * p_u32)
{
	uint8_t * p_IPv4_Buffer;
	p_IPv4_Buffer = (uint8_t *)p_u32;
	*p_IPv4_Buffer++ = p_u8[3];
	*p_IPv4_Buffer++ = p_u8[2];
	*p_IPv4_Buffer++ = p_u8[1];
	*p_IPv4_Buffer++ = p_u8[0];
}
void R_DLMS_Ipv4_ConverterUint32ToByteArray(uint32_t * p_u32, uint8_t * p_u8)
{
	uint8_t * p_IPv4_Buffer;
	p_IPv4_Buffer = (uint8_t *)p_u32;
	p_u8[3] = *p_IPv4_Buffer++;
	p_u8[2] = *p_IPv4_Buffer++;
	p_u8[1] = *p_IPv4_Buffer++;
	p_u8[0] = *p_IPv4_Buffer++;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass42
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass42(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 42
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass42(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class42_child_record_t	*p_class42_obj = (class42_child_record_t *)p_params->p_child_record;
	uint8_t					*p_alloc, *p_head;
	class42_action_data_t	action_data;
	uint16_t				action_decoded_length = 0;
	uint32_t ipv4_address;
	uint8_t * p_IPv4_Buffer;
	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			/* TODO : Put process code for each attrs of class 42 here, start from attr2 */
			case 2:	/* DL_reference */
				R_DLMS_CLASSES_DistributeFixedString(p_params, TAG_DATA_OCTET_STRING, p_class42_obj->p_dl_reference);
				break;
			case 3:	/* IP_address */
				R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class42_obj->p_ip_address);
				break;
			case 4:	/* multicast_IP_address */
				R_DLMS_CLASSES_DistributeVariantArrayDoubleLongUnsigned(p_params, p_class42_obj->p_multicast_ip_address);
				break;
			case 5:	/* IP_Option */
				R_DLMS_CLASSES_DistributeClass42IpOptionArray(p_params, p_class42_obj->p_option_array);
				break;
			case 6:	/* Subnet_mask */
				R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class42_obj->p_subnet_mask);
				break;
			case 7:	/* gateway_IP_address */
				R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class42_obj->p_gateway_ipv4_address);
				break;
			case 8:	/* use_DHCP_flag */
				R_DLMS_CLASSES_DistributeBoolean(p_params, p_class42_obj->p_use_dhcp_flag);
				break;
			case 9:	/* primary_DNS_address */
				R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class42_obj->p_primary_dns_address);
				break;
			case 10:	/* primary_DNS_address */
				R_DLMS_CLASSES_DistributeDoubleLongUnsigned(p_params, p_class42_obj->p_secondary_dns_address);
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
			/* TODO : Put process code for each method of class 42 here, start from method1 */
			case 1:
			case 2:
				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_ip_address, uint32_t, p_alloc);
				OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
				p_params->service_params.created = TRUE;
				action_decoded_length = R_DLMS_CLASSES_DecodeDoubleLongUnsigned(action_data.p_ip_address, p_params->in_data);
				break;
			case 3:
				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_data, uint8_t, p_alloc);
				OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
				p_params->service_params.created = TRUE;
				action_decoded_length = R_DLMS_CLASSES_DecodeUnsigned(action_data.p_data, p_params->in_data);
				break;
				
			default:
				action_decoded_length = 0;
				break;
		}
		
		if (action_decoded_length == 0)
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
	}
}

