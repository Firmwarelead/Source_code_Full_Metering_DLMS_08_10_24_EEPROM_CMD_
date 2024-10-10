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
* File Name    : r_dlms_object_class64.c
* Version      : 2.00
* Version OCG  : 1.0.7 - Arp 20 2023 - d0ac0fea860855c7f58887c28dbc077146b8333f
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 24/04/2023 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_library_process.h"

#include "r_dlms_config.h"
#include "r_dlms_classes.h"
#include "r_dlms_class64.h"
#include "r_dlms_objects.h"
#include "r_dlms_type.h"

#include "r_dlms_usercode_class64.h"


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
AesGcmInvocationCounters	*gp_object_class64_unicast_ek_counter_to_be_reset = NULL;
AesGcmInvocationCounters	*gp_object_class64_broadcast_ek_counter_to_be_reset = NULL;
SecurityPolicy				*gp_object_class64_security_policy_to_be_updated = NULL;
SecurityPolicy				g_object_class64_security_policy_new_value = SECURITY_NONE;


/*---------------------------------------------------------------------------*/
/*Class 64 record table*/
/*---------------------------------------------------------------------------*/
const class64_child_record_t	g_objects_child_table_class64[] =
{
	/* 00 - Security Setup_Push */
	{ 
		{0,   0,   43,   0,   4,   255},
		(access_right_t *)g_objects_access_right_table[6],
		(class64_security_policy_t *)&g_assc2_security_context.security_policy,
		(class64_security_suite_t *)&g_assc2_security_context.security_suit,
		(FixedString *)&g_assc2_security_context.client_title,
		(FixedString *)&g_assc2_security_context.server_title,

	},

	/* 01 - Security Setup_FWU */
	{ 
		{0,   0,   43,   0,   5,   255},
		(access_right_t *)g_objects_access_right_table[8],
		(class64_security_policy_t *)&g_assc3_security_context.security_policy,
		(class64_security_suite_t *)&g_assc3_security_context.security_suit,
		(FixedString *)&g_assc3_security_context.client_title,
		(FixedString *)&g_assc3_security_context.server_title,

	},

	/* 02 - Security Setup_Meter Reader */
	{ 
		{0,   0,   43,   0,   2,   255},
		(access_right_t *)g_objects_access_right_table[6],
		(class64_security_policy_t *)&g_assc0_security_context.security_policy,
		(class64_security_suite_t *)&g_assc0_security_context.security_suit,
		(FixedString *)&g_assc0_security_context.client_title,
		(FixedString *)&g_assc0_security_context.server_title,

	},

	/* 03 - Security Setup_Utility Setting */
	{ 
		{0,   0,   43,   0,   3,   255},
		(access_right_t *)g_objects_access_right_table[6],
		(class64_security_policy_t *)&g_assc1_security_context.security_policy,
		(class64_security_suite_t *)&g_assc1_security_context.security_suit,
		(FixedString *)&g_assc1_security_context.client_title,
		(FixedString *)&g_assc1_security_context.server_title,

	},


};

const uint16_t 	g_objects_child_table_class64_length = sizeof(g_objects_child_table_class64) / sizeof(class64_child_record_t);

/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Class64CosemSetIndication
* Interface     : None R_DLMS_OBJECTS_Class64CosemSetIndication(
*               :     MgmtChannel mgmt_channel
*               :     CosemSetIndication_Params * p_params
*               : );
* Description   :
* Arguments     : MgmtChannel mgmt_channel            :
*               : CosemSetIndication_Params * p_params:
* Function Calls:
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_Class64CosemSetIndication(MgmtChannel mgmt_channel, CosemSetIndication_Params *p_params)
{
	/* Set-Request-Normal, class 64 object */
	if (p_params != NULL &&
		p_params->request_type == COSEM_SET_REQUEST_NORMAL &&
		p_params->cosem_attr_descriptor.length == 1 &&
		p_params->cosem_attr_descriptor.p_list != NULL &&
		p_params->cosem_attr_descriptor.p_list[0].cosem_attribute_descriptor.class_id == 64)
	{
		/* security_policy attribute on class 64 object */
		if (p_params->cosem_attr_descriptor.p_list[0].cosem_attribute_descriptor.attribute_id == 2) {
			/* Update security policy */
			if (gp_object_class64_security_policy_to_be_updated != NULL) {
				*gp_object_class64_security_policy_to_be_updated = g_object_class64_security_policy_new_value;
				gp_object_class64_security_policy_to_be_updated = NULL;
			}
		}
	}
}

/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Class64CosemActionIndication
* Interface     : None R_DLMS_OBJECTS_Class64CosemActionIndication(
*               :     MgmtChannel mgmt_channel               
*               :     CosemActionIndication_Params * p_params
*               : );
* Description   : 
* Arguments     : MgmtChannel mgmt_channel               :
*               : CosemActionIndication_Params * p_params:
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_Class64CosemActionIndication(MgmtChannel mgmt_channel, CosemActionIndication_Params *p_params)
{
	/* Action-Request-Normal, class 64 object */
	if (p_params != NULL &&
		p_params->request_type == COSEM_ACTION_REQUEST_NORMAL &&
		p_params->cosem_method_descriptor.length == 1 &&
		p_params->cosem_method_descriptor.p_list != NULL &&
		p_params->cosem_method_descriptor.p_list[0].class_id == 64)
	{
		/* security_activate method on class 64 object */
		if (p_params->cosem_method_descriptor.p_list[0].method_id == 1)
		{
			/* Update security policy */
			if (gp_object_class64_security_policy_to_be_updated != NULL) {
				*gp_object_class64_security_policy_to_be_updated = g_object_class64_security_policy_new_value;
				gp_object_class64_security_policy_to_be_updated = NULL;
			}
		}
		/* key_transfer method on class 64 object */
		else if (p_params->cosem_method_descriptor.p_list[0].method_id == 2)
		{
			/* Reset invocation counters */
			if (gp_object_class64_unicast_ek_counter_to_be_reset != NULL) {
				/* gp_object_class64_unicast_ek_counter_to_be_reset assigned when changed unicast key successful, else it is null */
				gp_object_class64_unicast_ek_counter_to_be_reset->encryption = 0;
				gp_object_class64_unicast_ek_counter_to_be_reset->decryption = 0;
				gp_object_class64_unicast_ek_counter_to_be_reset = NULL;
			}
			if (gp_object_class64_broadcast_ek_counter_to_be_reset != NULL) {
				/* gp_object_class64_broadcast_ek_counter_to_be_reset assigned when changed unicast key successful, else it is null */
				gp_object_class64_broadcast_ek_counter_to_be_reset->encryption = 0;
				gp_object_class64_broadcast_ek_counter_to_be_reset->decryption = 0;
				gp_object_class64_broadcast_ek_counter_to_be_reset = NULL;
			}
			if (g_dlms_security_is_key_tranferred)
			{
				R_DLMS_Security_FetchAllNewKey();
				g_dlms_security_is_key_tranferred = FALSE;
			}
			else
			{
			}

		}
	}
}

/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Class64Distributor
* Interface     : void R_DLMS_OBJECTS_Class64Distributor(
*               :     distributor_params_t * p_param,
*               : );
* Description   : User distributor function for GET/SET/ACTION service of class 64
* Arguments     : distributor_params_t * p_param: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_Class64Distributor(distributor_params_t *p_params)
{
	class64_child_record_t	* p_class64_obj = (class64_child_record_t *)p_params->p_child_record;
	void * p_object;
	uint16_t length;
	uint8_t result;
	uint16_t count;
	class64_action_data_t				action_data;
	class64_key_unwrapped_transfer_data_array_t * p_unwrapped_keys_transfer_data;
	uint8_t key_transfer_contain_unicast_key = FALSE;
	uint8_t key_transfer_contain_broadcast_key = FALSE;
	SecurityContext * p_security_context_array[] = {
		&g_assc2_security_context,
		&g_assc3_security_context,
		&g_assc0_security_context,
		&g_assc1_security_context,
		/* SECURITY_CONTEXT_ARRAY_LIST */ 
	};

	/*
	* ---------------------------
	* >>> IMPLEMENTATION NOTE <<<
	* ---------------------------
	*
	* Attr0 and Attr1 are handled on abstract class function already (READ ONLY). Please process other object attrs from attr no 2.
	* In default of processing, this function is called twice, BEFORE and AFTER the class distributor function call.
	* Check the value of (p_params->distributor_state) to know the calling to this function is in before or after class distributor
	*
	* Calling sequence with class distributor function is as below:
	*
	*    // User distributor function is called first with distribution state = DIST_BEFORE_CLASS_FUNCTION
	*    if (fp_user_func != NULL) {
	*    	if (p_params->handled == FALSE) {
	*    		p_params->distributor_state = DIST_BEFORE_CLASS_FUNCTION;
	*    		(*fp_user_func)(p_params);
	*    	}
	*    }
	*
	*    // Class distributor function is called in second with distribution state = DIST_UNDER_CLASS_FUNCTION
	*    if (fp_class_func != NULL) {
	*    	if (p_params->handled == FALSE) {
	*    		p_params->distributor_state = DIST_UNDER_CLASS_FUNCTION;
	*    		(*fp_class_func)(p_params);
	*    	}
	*    }
	*
	*    // User distributor function is called first with distribution state = DIST_AFTER_CLASS_FUNCTION
	*    if (fp_user_func != NULL) {
	*    	if (p_params->handled == FALSE) {
	*    		p_params->distributor_state = DIST_AFTER_CLASS_FUNCTION;
	*    		(*fp_user_func)(p_params);
	*    	}
	*    }
	*
	* To break the calling sequence above, on this function (user function), write below code at a desired location:
	*
	*    p_params->handled = TRUE;
	*
	*/
	
	if (p_params->req_type == REQ_TYPE_GET)
	{
		result = p_params->result.result.data_access;

		p_params->result.result.data_access = (DataAccessResult_Value)result;
	}
	else if(p_params->req_type == REQ_TYPE_SET)
	{
		result = p_params->result.result.data_access;

		p_params->result.result.data_access = (DataAccessResult_Value)result;
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		result = p_params->result.result.action;
		switch (p_params->descriptor.method.method_id)
		{
			case 1:
				if (p_params->distributor_state == DIST_AFTER_CLASS_FUNCTION)
				{

					switch(p_params->child_index)
					{
						case 0:
							gp_object_class64_security_policy_to_be_updated = (SecurityPolicy *)p_class64_obj->p_security_policy;
							g_object_class64_security_policy_new_value      = (SecurityPolicy)(*p_params->service_params.malloc.p_content);
							break;

						case 1:
							gp_object_class64_security_policy_to_be_updated = (SecurityPolicy *)p_class64_obj->p_security_policy;
							g_object_class64_security_policy_new_value      = (SecurityPolicy)(*p_params->service_params.malloc.p_content);
							break;

						case 2:
							gp_object_class64_security_policy_to_be_updated = (SecurityPolicy *)p_class64_obj->p_security_policy;
							g_object_class64_security_policy_new_value      = (SecurityPolicy)(*p_params->service_params.malloc.p_content);
							break;

						case 3:
							gp_object_class64_security_policy_to_be_updated = (SecurityPolicy *)p_class64_obj->p_security_policy;
							g_object_class64_security_policy_new_value      = (SecurityPolicy)(*p_params->service_params.malloc.p_content);
							break;


						default:
							break;
					}

				}
				else
				{
					/* Nothing code here */
				}
				break;
			case 2:
				if (p_params->distributor_state == DIST_AFTER_CLASS_FUNCTION)
				{
#if(CLASS_15_SUPPORT_AUTHENTICATION_BY_AES == FALSE)
#error "Please enable CLASS_15_SUPPORT_AUTHENTICATION_BY_AES because action 02, class 64 need it."
#endif					
					action_data.p_all = p_params->service_params.malloc.p_content;
					/* Create object for class64_key_unwrapped_transfer_data_array_t*/
					p_unwrapped_keys_transfer_data = R_DLMS_CLASSES_RedirectKeyTransferDataAction02(p_params, action_data.p_m2_key_transfer);
					/* Try to unwrap all keys inside before update, if any failure happen, action call is reject */
					for (count = 0; count < action_data.p_m2_key_transfer->length; count++)
					{
						if (p_security_context_array[p_params->child_index] == NULL ||
							R_Aes_128_Unwrap(
								p_security_context_array[p_params->child_index]->master_key.p_content,
								p_security_context_array[p_params->child_index]->master_key.length / 8,
								action_data.p_m2_key_transfer->p_content[count].key_wrapped.p_content,
								p_unwrapped_keys_transfer_data->p_content[count].key_unwrapped.p_content
							) != 0)
						{
							OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_READ_WRITE_DENIED, FALSE);
							OBIS_DISTRIBUTION_FAILED(p_params->result);
							return;
						}
						else
						{
							if(p_unwrapped_keys_transfer_data->p_content[count].key_id == 0)
							{
								key_transfer_contain_unicast_key = TRUE;
							}
							else if(p_unwrapped_keys_transfer_data->p_content[count].key_id == 1)
							{
								key_transfer_contain_broadcast_key = TRUE;
							}
							else
							{
								/* code */
							}
						}
					}
					switch(p_params->child_index)
					{
						case 0:
							result = R_DLMS_USER_ic64_obj00_meth02_action(p_params, p_unwrapped_keys_transfer_data);
							break;

						case 1:
							result = R_DLMS_USER_ic64_obj01_meth02_action(p_params, p_unwrapped_keys_transfer_data);
							break;

						case 2:
							result = R_DLMS_USER_ic64_obj02_meth02_action(p_params, p_unwrapped_keys_transfer_data);
							break;

						case 3:
							result = R_DLMS_USER_ic64_obj03_meth02_action(p_params, p_unwrapped_keys_transfer_data);
							break;


						default:
							break;
					}
					if (result == VAL_ACTION_RESULT_SUCCESS)
					{
						g_dlms_security_is_key_tranferred = TRUE;
						if(p_params->child_index < sizeof(p_security_context_array)/(sizeof(SecurityContext*)))
						{
							if(key_transfer_contain_unicast_key)
							{
								gp_object_class64_unicast_ek_counter_to_be_reset = p_security_context_array[p_params->child_index]->global_unicast_key.p_invocation_counters;
							}
							else
							{
								gp_object_class64_unicast_ek_counter_to_be_reset = NULL;
							}
							if(key_transfer_contain_broadcast_key)
							{
								gp_object_class64_broadcast_ek_counter_to_be_reset = p_security_context_array[p_params->child_index]->global_broadcast_key.p_invocation_counters;
							}
							else
							{
								gp_object_class64_broadcast_ek_counter_to_be_reset = NULL;
							}
							
						}
						else
						{
							
						}
					}
				}
				else
				{
					/* Nothing code here */
				}
				break;

			default:
				break;
		}
	
		p_params->result.result.action = (ActionResult_Value)result;
	}
	else
	{
	 /* Nothing code here */
	}
}

