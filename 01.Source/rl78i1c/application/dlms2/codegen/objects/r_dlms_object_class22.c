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
* File Name    : r_dlms_object_class22.c
* Version      : 2.00
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 03/01/2023 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_library_process.h"

#include "r_dlms_config.h"
#include "r_dlms_classes.h"
#include "r_dlms_class22.h"
#include "r_dlms_objects.h"
#include "r_dlms_type.h"

#include "r_dlms_usercode_class22.h"

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



/*---------------------------------------------------------------------------*/
/*Class 22 record table*/
/*---------------------------------------------------------------------------*/
const class22_child_record_t	g_objects_child_table_class22[] =
{
	/* 00 - Schedule for push - SM to IHD Push */
	{ 
		{0,   3,   15,   0,   4,   255},
		(access_right_t *)g_objects_access_right_table[16],
		(class22_executed_script_t *)&g_dlms_ic22_obj00_att02_executed_script,
		(class22_exe_time_type_t *)&g_dlms_ic22_obj00_att03_type,
		NULL,

	},

	/* 01 - Single Action Schedule - SM to HES Push */
	{ 
		{0,   0,   15,   0,   4,   255},
		(access_right_t *)g_objects_access_right_table[16],
		(class22_executed_script_t *)&g_dlms_ic22_obj01_att02_executed_script,
		(class22_exe_time_type_t *)&g_dlms_ic22_obj01_att03_type,
		NULL,

	},

	/* 02 - Single action schedule- Billing */
	{ 
		{0,   0,   15,   0,   0,   255},
		(access_right_t *)g_objects_access_right_table[16],
		(class22_executed_script_t *)&g_dlms_ic22_obj02_att02_executed_script,
		(class22_exe_time_type_t *)&g_dlms_ic22_obj02_att03_type,
		NULL,

	},

	/* 03 - Single Action Schedule -Image Activation */
	{ 
		{0,   0,   15,   0,   2,   255},
		(access_right_t *)g_objects_access_right_table[17],
		(class22_executed_script_t *)&g_dlms_ic22_obj03_att02_executed_script,
		(class22_exe_time_type_t *)&g_dlms_ic22_obj03_att03_type,
		NULL,

	},


};

const uint16_t 	g_objects_child_table_class22_length = sizeof(g_objects_child_table_class22) / sizeof(class22_child_record_t);



/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Class22Distributor
* Interface     : void R_DLMS_OBJECTS_Class22Distributor(
*               :     distributor_params_t * p_param,
*               : );
* Description   : User distributor function for GET/SET/ACTION service of class 22
* Arguments     : distributor_params_t * p_param: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_Class22Distributor(distributor_params_t *p_params)
{
	class22_child_record_t	* p_class22_obj = (class22_child_record_t *)p_params->p_child_record;
	void * p_object;
	uint16_t length;
	uint8_t result;

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
		switch (p_params->descriptor.attr.attribute_id)
		{
			case 4:
				if (p_params->distributor_state == DIST_BEFORE_CLASS_FUNCTION)
				{
					p_params->handled = FALSE;

					switch(p_params->child_index)
					{
						case 0:
							/* Clone new attribute */
							R_DLMS_IC22_REDIRECT_04(p_params, p_class22_obj->p_execution_time, r_dlms_ic22_obj00_att04_array_length);
							/* APPLICATION */
							result = R_DLMS_USER_ic22_obj00_att04_get(p_params, p_class22_obj->p_execution_time);
							break;

						case 1:
							/* Clone new attribute */
							R_DLMS_IC22_REDIRECT_04(p_params, p_class22_obj->p_execution_time, r_dlms_ic22_obj01_att04_array_length);
							/* APPLICATION */
							result = R_DLMS_USER_ic22_obj01_att04_get(p_params, p_class22_obj->p_execution_time);
							break;

						case 2:
							/* Clone new attribute */
							R_DLMS_IC22_REDIRECT_04(p_params, p_class22_obj->p_execution_time, r_dlms_ic22_obj02_att04_array_length);
							/* APPLICATION */
							result = R_DLMS_USER_ic22_obj02_att04_get(p_params, p_class22_obj->p_execution_time);
							break;

						case 3:
							/* Clone new attribute */
							R_DLMS_IC22_REDIRECT_04(p_params, p_class22_obj->p_execution_time, r_dlms_ic22_obj03_att04_array_length);
							/* APPLICATION */
							result = R_DLMS_USER_ic22_obj03_att04_get(p_params, p_class22_obj->p_execution_time);
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

			default:
				break;
		}
		p_params->result.result.data_access = (DataAccessResult_Value)result;
	}
	else if(p_params->req_type == REQ_TYPE_SET)
	{
		result = p_params->result.result.data_access;
		switch (p_params->descriptor.attr.attribute_id)
		{
			case 4:
				if ((p_params->distributor_state == DIST_AFTER_CLASS_FUNCTION)&&
			      (p_params->service_params.decode_success == TRUE))
				{
					p_params->service_params.sync = FALSE;

					switch(p_params->child_index)
					{
						case 0:
							result = R_DLMS_USER_ic22_obj00_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

							
						case 1:
							result = R_DLMS_USER_ic22_obj01_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

							
						case 2:
							result = R_DLMS_USER_ic22_obj02_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

							
						case 3:
							result = R_DLMS_USER_ic22_obj03_att04_set(p_params, (void *)p_params->service_params.malloc.p_content);
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

			default:
				break;
		}
		p_params->result.result.data_access = (DataAccessResult_Value)result;
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		result = p_params->result.result.action;
	
		p_params->result.result.action = (ActionResult_Value)result;
	}
	else
	{
	 /* Nothing code here */
	}
}

