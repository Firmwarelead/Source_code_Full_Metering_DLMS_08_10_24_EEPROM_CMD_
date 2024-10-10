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
* File Name    : r_dlms_class48.c
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
#include "r_dlms_class48.h"
#include "r_dlms_objects.h"
#include "r_dlms_wrapper_conversion_ip.h"
#include <string.h>

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


OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass48NeighborDiscoverySetup, class48_nbr_discovery_setup_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	/* Structure, 3 elements */
	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 3);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_object->RS_max_retry, sizeof(uint8_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_object->RS_retry_wait_time, sizeof(uint16_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_DOUBLE_LONG_UNSIGNED, (uint8_t *)&p_object->RA_send_period, sizeof(uint32_t));
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass48NeighborDiscoverySetupArray,
	class48_nbr_discovery_setup_array_t,
	R_DLMS_CLASSES_EncodeClass48NeighborDiscoverySetup
);
/* Declare redirect for complex data type */
class48_nbr_discovery_setup_array_t *R_DLMS_CLASSES_RedirectClass48NeighborDiscoverySetupArray(distributor_params_t *p_params, class48_nbr_discovery_setup_array_t *p_object, uint16_t array_size)
{
	class48_nbr_discovery_setup_array_t * p_clone;
	uint8_t * p_alloc, * p_head;
	uint16_t i;
	
	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	if (p_object == NULL)
	{
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone, class48_nbr_discovery_setup_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_FIXED_ARRAY(p_clone, array_size, class48_nbr_discovery_setup_t, p_alloc);
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone = (class48_nbr_discovery_setup_array_t *)R_DLMS_CLASSES_CreateFixedArray(
			p_params,
			(AbstractFixedArray *)p_object,
			sizeof(class48_nbr_discovery_setup_t),
			OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE
		);
	}

	return p_clone;
}

OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass48NeighborDiscoverySetupArray,
	class48_nbr_discovery_setup_array_t,
	R_DLMS_CLASSES_EncodeClass48NeighborDiscoverySetupArray,
	NULL,
	NULL
);

VariantArrayOctetString *R_DLMS_CLASSES_RedirectClass48Ipv6Array(distributor_params_t *p_params, VariantArrayOctetString *p_object, uint16_t array_size)
{
	VariantArrayOctetString * p_clone;
	uint8_t * p_alloc, * p_head;
	uint16_t count;
	
	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone, VariantArrayOctetString, p_alloc);
		OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone, array_size, OctetString, p_alloc);
		for (count = 0; count < array_size; count++)
		{
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone->p_content[count], 48, p_alloc);
			p_clone->p_content[count].length = 16;
		}
		p_clone->p_active = NULL;
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone = (VariantArrayOctetString *)R_DLMS_CLASSES_CreateVariantArray(
			p_params,
			(AbstractVariantArray *)p_object,
			sizeof(OctetString),
			OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE
		);
	}

	return p_clone;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class48Init
* Interface     : void R_DLMS_CLASSES_Class48Init(void)
* Description   : Initialize class 48
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class48Init(void)
{
	/* Put init code of class 48 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class48PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class48PollingProcessing(void)
* Description   : Polling process of class 48
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class48PollingProcessing(void)
{
	/* Put polling processing code of class 48 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class48AsscOpened
* Interface     : void R_DLMS_CLASSES_Class48AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 48
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class48AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 48 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class48AsscClosing
* Interface     : void R_DLMS_CLASSES_Class48AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 48
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class48AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 48 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass48
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass48(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 48
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass48(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass48,
		R_DLMS_OBJECTS_Class48Distributor,
		p_params
	);
}


/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass48
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass48(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 48
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass48(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class48_child_record_t	*p_class48_obj = (class48_child_record_t *)p_params->p_child_record;
	uint8_t					u8 = 0;
	uint16_t				u16 = 0;
	uint16_t				count;
	uint8_t					*p_alloc, *p_head;
	class48_action_data_t	action_data;
	VariantArrayOctetString	*p_array;
	OctetString				*p_ip_address = NULL;

	p_alloc = p_head = OBIS_MALLOC_GET_POINTER(p_params);

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			/* TODO : Put process code for each attrs of class 48 here, start from attr2 */
		case 2:		/* dl_reference */
			R_DLMS_CLASSES_DistributeFixedString(p_params, TAG_DATA_OCTET_STRING, p_class48_obj->p_dl_reference);
			break;
		case 3:		/* address_config_mode */
			R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class48_obj->p_address_config_mode);
			break;
		case 4:		/* unicast_IPv6_addresses */
			R_DLMS_CLASSES_DistributeVariantArrayOctetString(p_params, p_class48_obj->p_unicast_ipv6_addresses);
			break;
		case 5:		/* multicast_IPv6_addresses */
			R_DLMS_CLASSES_DistributeVariantArrayOctetString(p_params, p_class48_obj->p_multicast_ipv6_addresses);
			break;
		case 6:		/* gateway_IPv6_addresses */
			R_DLMS_CLASSES_DistributeVariantArrayOctetString(p_params, p_class48_obj->p_gateway_ipv6_addresses);
			break;
		case 7:		/* primary_DNS_address */
			R_DLMS_CLASSES_DistributeFixedString(p_params, TAG_DATA_OCTET_STRING, p_class48_obj->p_primary_dns_address);
			break;
		case 8:		/* secondary_DNS_address */
			R_DLMS_CLASSES_DistributeFixedString(p_params, TAG_DATA_OCTET_STRING, p_class48_obj->p_secondary_dns_address);
			break;
		case 9:		/* traffic_class */
			R_DLMS_CLASSES_DistributeUnsigned(p_params, p_class48_obj->p_traffic_class);
			break;
		case 10:	/* neighbor_discovery_setup */
			R_DLMS_CLASSES_DistributeClass48NeighborDiscoverySetupArray(p_params, p_class48_obj->p_neighbor_discovery_setup);
			break;
		default:
			break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		switch (p_params->descriptor.method.method_id)
		{
			/* TODO : Put process code for each method of class 48 here, start from method1 */
		case 1:	/* add_IPv6_address(data) */
		case 2:	/* remove_IPv6_address(data) */

				/* add & remove ip6 have the same client action data input */

			OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m1_add_ip6_address, class48_ip6_action_data_t, p_alloc);
			OBIS_MALLOC_ASSIGN_FIXED_STRING(&action_data.p_m1_add_ip6_address->IPv6_address, 16, p_alloc);
			OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
			p_params->service_params.created = TRUE;

			OBIS_DIST_DECODE_STRUCTURE_TYPE_DEF(u8, &count, 2, p_params->in_data);
			{
				OBIS_DIST_DECODE_THEN_ADVANCE_BUF(u16, &action_data.p_m1_add_ip6_address->IPv6_address_type, sizeof(uint8_t), TAG_DATA_ENUM, p_params->in_data);
				OBIS_DIST_DECODE_THEN_ADVANCE_BUF(u16, action_data.p_m1_add_ip6_address->IPv6_address.p_content, action_data.p_m1_add_ip6_address->IPv6_address.length, TAG_DATA_OCTET_STRING, p_params->in_data);
			}
			switch (action_data.p_m1_add_ip6_address->IPv6_address_type)
			{
			case 0:	/* unicast */
				p_array = p_class48_obj->p_unicast_ipv6_addresses;
				break;
			case 1:	/* multicast */
				p_array = p_class48_obj->p_multicast_ipv6_addresses;
				break;
			case 2:	/* gateway */
				p_array = p_class48_obj->p_gateway_ipv6_addresses;
				break;
			default:
				OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
				return;	/* Error here since IP6 address type not match unicast, multicast or gateway */
			}
			p_params->service_params.decode_success = TRUE;

			/* Check if buffer can be written */
			if (p_array == NULL ||
				R_DLMS_CLASSES_IsBufferWritable((uint8_t *)p_array) == FALSE) {
				OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_READ_WRITE_DENIED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
				break;
			}

			/* First, mark as not found ip6_action_data on target array */
			u8 = FALSE;

			/* Search thru all items on target array, find ip6_action_data */
			for (count = 0, u16 = 0;
				count < p_array->alloc_size && u16 < p_array->length;
				count++)
			{
				if (p_array->p_active == NULL || p_array->p_active[count] == TRUE) {
					if (p_array->p_content[count].length == action_data.p_m1_add_ip6_address->IPv6_address.length &&
						memcmp(p_array->p_content[count].p_content, action_data.p_m1_add_ip6_address->IPv6_address.p_content, action_data.p_m1_add_ip6_address->IPv6_address.length) == 0)
					{
						u8 = TRUE;
						break;
					}
					u16++;
				}
			}

			if (p_params->descriptor.method.method_id == 1) {
				/* add to the end of the list (if have empty slot) */
				if (u8 == FALSE &&
					p_array->length < p_array->alloc_size &&
					action_data.p_m1_add_ip6_address->IPv6_address.length <= p_array->p_content[p_array->length].alloc_size) {
					memset(p_array->p_content[p_array->length].p_content, 0, p_array->p_content[p_array->length].alloc_size);
					memcpy(p_array->p_content[p_array->length].p_content, action_data.p_m1_add_ip6_address->IPv6_address.p_content, action_data.p_m1_add_ip6_address->IPv6_address.length);
					p_array->p_content[p_array->length].length = action_data.p_m1_add_ip6_address->IPv6_address.length;
					if (p_array->p_active != NULL) {
						p_array->p_active[p_array->length] = TRUE;
					}
					p_array->length++;
					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SUCCESS, FALSE);
					OBIS_DISTRIBUTION_SUCCESS(p_params->result);
				}
				else {
					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_READ_WRITE_DENIED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
				}
			}
			else if (p_params->descriptor.method.method_id == 2) {

				/* if exist IP6 on target array, remove IP from the target array, move all subsequence items up */
				if (u8 == TRUE && p_array->length > 0) {
					/* move all subsequence items up */
					for (u16 = count; u16 < p_array->alloc_size - 1; u16++) {
						if (p_array->p_content[u16].alloc_size >= p_array->p_content[u16 + 1].length) {
							memset(p_array->p_content[u16].p_content, 0, p_array->p_content[u16].alloc_size);
							p_array->p_content[u16].length = p_array->p_content[u16 + 1].length;
							memcpy(p_array->p_content[u16].p_content, p_array->p_content[u16 + 1].p_content, p_array->p_content[u16 + 1].length);
							if (p_array->p_active != NULL) {
								p_array->p_active[u16] = p_array->p_active[u16 + 1];
							}
						}
						else {
							OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_READ_WRITE_DENIED, FALSE);
							OBIS_DISTRIBUTION_FAILED(p_params->result);
							break;
						}
					}
					/* remove last item */
					p_array->p_content[u16].length = 0;
					memset(p_array->p_content[u16].p_content, 0, p_array->p_content[u16].alloc_size);
					if (p_array->p_active != NULL) {
						p_array->p_active[u16] = FALSE;
					}
					/* reduce total items by 1 */
					p_array->length--;

					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SUCCESS, FALSE);
					OBIS_DISTRIBUTION_SUCCESS(p_params->result);
				}
				else {
					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_READ_WRITE_DENIED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
				}
			}
			break;

		default:
			break;
		}
	}
}

