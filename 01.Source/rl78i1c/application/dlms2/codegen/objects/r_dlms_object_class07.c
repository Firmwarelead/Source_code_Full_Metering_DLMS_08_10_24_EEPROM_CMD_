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
* File Name    : r_dlms_object_class07.c
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
#include "r_dlms_class07.h"
#include "r_dlms_objects.h"
#include "r_dlms_type.h"

#include "r_dlms_usercode_class07.h"

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
/*Class 07 record table*/
/*---------------------------------------------------------------------------*/
const class07_child_record_t	g_objects_child_table_class07[] =
{
	/* 00 - Billing profile */
	{ 
		{1,   0,   98,   1,   0,   255},
		(access_right_t *)g_objects_access_right_table[6],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj00_att03_capture_objects,
		NULL,
		(class07_sort_method_t *)&g_dlms_ic07_obj00_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj00_att06_sort_object,
		NULL,
		NULL,

	},

	/* 01 - Billing Scaler Profile */
	{ 
		{1,   0,   94,   91,   6,   255},
		(access_right_t *)g_objects_access_right_table[0],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj01_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj01_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj01_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj01_att06_sort_object,
		(uint32_t *)&g_dlms_ic07_obj01_att07_entries_in_use,
		(uint32_t *)&g_dlms_ic07_obj01_att08_profile_entries,

	},

	/* 02 - Block Load Profile */
	{ 
		{1,   0,   99,   1,   0,   255},
		(access_right_t *)g_objects_access_right_table[6],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj02_att03_capture_objects,
		NULL,
		(class07_sort_method_t *)&g_dlms_ic07_obj02_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj02_att06_sort_object,
		NULL,
		NULL,

	},

	/* 03 - Block Load Scaler Profile */
	{ 
		{1,   0,   94,   91,   4,   255},
		(access_right_t *)g_objects_access_right_table[0],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj03_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj03_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj03_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj03_att06_sort_object,
		(uint32_t *)&g_dlms_ic07_obj03_att07_entries_in_use,
		(uint32_t *)&g_dlms_ic07_obj03_att08_profile_entries,

	},

	/* 04 - Daily Load Profile */
	{ 
		{1,   0,   99,   2,   0,   255},
		(access_right_t *)g_objects_access_right_table[6],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj04_att03_capture_objects,
		NULL,
		(class07_sort_method_t *)&g_dlms_ic07_obj04_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj04_att06_sort_object,
		NULL,
		NULL,

	},

	/* 05 - Daily Load Scaler Profile */
	{ 
		{1,   0,   94,   91,   5,   255},
		(access_right_t *)g_objects_access_right_table[0],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj05_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj05_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj05_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj05_att06_sort_object,
		(uint32_t *)&g_dlms_ic07_obj05_att07_entries_in_use,
		(uint32_t *)&g_dlms_ic07_obj05_att08_profile_entries,

	},

	/* 06 - Event Scaler Profile */
	{ 
		{1,   0,   94,   91,   7,   255},
		(access_right_t *)g_objects_access_right_table[0],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj06_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj06_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj06_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj06_att06_sort_object,
		(uint32_t *)&g_dlms_ic07_obj06_att07_entries_in_use,
		(uint32_t *)&g_dlms_ic07_obj06_att08_profile_entries,

	},

	/* 07 - Event profile Control */
	{ 
		{0,   0,   99,   98,   6,   255},
		(access_right_t *)g_objects_access_right_table[6],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj07_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj07_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj07_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj07_att06_sort_object,
		NULL,
		NULL,

	},

	/* 08 - Event profile Current */
	{ 
		{0,   0,   99,   98,   1,   255},
		(access_right_t *)g_objects_access_right_table[6],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj08_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj08_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj08_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj08_att06_sort_object,
		NULL,
		NULL,

	},

	/* 09 - Event profile non roll over */
	{ 
		{0,   0,   99,   98,   5,   255},
		(access_right_t *)g_objects_access_right_table[6],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj09_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj09_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj09_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj09_att06_sort_object,
		NULL,
		NULL,

	},

	/* 10 - Event profile Other */
	{ 
		{0,   0,   99,   98,   4,   255},
		(access_right_t *)g_objects_access_right_table[6],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj10_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj10_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj10_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj10_att06_sort_object,
		NULL,
		NULL,

	},

	/* 11 - Event profile Power */
	{ 
		{0,   0,   99,   98,   2,   255},
		(access_right_t *)g_objects_access_right_table[6],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj11_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj11_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj11_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj11_att06_sort_object,
		NULL,
		NULL,

	},

	/* 12 - Event profile Trans */
	{ 
		{0,   0,   99,   98,   3,   255},
		(access_right_t *)g_objects_access_right_table[6],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj12_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj12_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj12_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj12_att06_sort_object,
		NULL,
		NULL,

	},

	/* 13 - Event profile Voltage */
	{ 
		{0,   0,   99,   98,   0,   255},
		(access_right_t *)g_objects_access_right_table[6],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj13_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj13_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj13_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj13_att06_sort_object,
		NULL,
		NULL,

	},

	/* 14 - Instant parameters snapshot */
	{ 
		{1,   0,   94,   91,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj14_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj14_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj14_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj14_att06_sort_object,
		(uint32_t *)&g_dlms_ic07_obj14_att07_entries_in_use,
		(uint32_t *)&g_dlms_ic07_obj14_att08_profile_entries,

	},

	/* 15 - Instant Scaler Profile */
	{ 
		{1,   0,   94,   91,   3,   255},
		(access_right_t *)g_objects_access_right_table[0],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj15_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj15_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj15_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj15_att06_sort_object,
		(uint32_t *)&g_dlms_ic07_obj15_att07_entries_in_use,
		(uint32_t *)&g_dlms_ic07_obj15_att08_profile_entries,

	},

	/* 16 - Name Plate Profile */
	{ 
		{0,   0,   94,   91,   10,   255},
		(access_right_t *)g_objects_access_right_table[0],
		NULL,
		(class07_obj_def_array_t *)&g_dlms_ic07_obj16_att03_capture_objects,
		(uint32_t *)&g_dlms_ic07_obj16_att04_capture_period,
		(class07_sort_method_t *)&g_dlms_ic07_obj16_att05_sort_method,
		(class07_obj_def_t *)&g_dlms_ic07_obj16_att06_sort_object,
		(uint32_t *)&g_dlms_ic07_obj16_att07_entries_in_use,
		(uint32_t *)&g_dlms_ic07_obj16_att08_profile_entries,

	},


};

const uint16_t 	g_objects_child_table_class07_length = sizeof(g_objects_child_table_class07) / sizeof(class07_child_record_t);



/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Class07Distributor
* Interface     : void R_DLMS_OBJECTS_Class07Distributor(
*               :     distributor_params_t * p_param,
*               : );
* Description   : User distributor function for GET/SET/ACTION service of class 07
* Arguments     : distributor_params_t * p_param: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_Class07Distributor(distributor_params_t *p_params)
{
	class07_child_record_t	* p_class07_obj = (class07_child_record_t *)p_params->p_child_record;
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
			case 2:
				if (p_params->distributor_state == DIST_AFTER_CLASS_FUNCTION)
				{
					p_params->handled = FALSE;

					switch(p_params->child_index)
					{
						case 0:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj00_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 1:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj01_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 2:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj02_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 3:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj03_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 4:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj04_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 5:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj05_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 6:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj06_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 7:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj07_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 8:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj08_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 9:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj09_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 10:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj10_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 11:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj11_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 12:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj12_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 13:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj13_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 14:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj14_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 15:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj15_att02_get(p_params, p_class07_obj->p_buffer);
							break;

						case 16:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_02(p_params, p_class07_obj->p_buffer);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj16_att02_get(p_params, p_class07_obj->p_buffer);
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
			case 4:
				if (p_params->distributor_state == DIST_BEFORE_CLASS_FUNCTION)
				{
					p_params->handled = FALSE;

					switch(p_params->child_index)
					{
						case 0:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_04(p_params, p_class07_obj->p_capture_period);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj00_att04_get(p_params, p_class07_obj->p_capture_period);
							break;

						case 2:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_04(p_params, p_class07_obj->p_capture_period);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj02_att04_get(p_params, p_class07_obj->p_capture_period);
							break;

						case 4:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_04(p_params, p_class07_obj->p_capture_period);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj04_att04_get(p_params, p_class07_obj->p_capture_period);
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
			case 7:
				if (p_params->distributor_state == DIST_BEFORE_CLASS_FUNCTION)
				{
					p_params->handled = FALSE;

					switch(p_params->child_index)
					{
						case 0:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_07(p_params, p_class07_obj->p_entries_in_use);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj00_att07_get(p_params, p_class07_obj->p_entries_in_use);
							break;

						case 2:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_07(p_params, p_class07_obj->p_entries_in_use);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj02_att07_get(p_params, p_class07_obj->p_entries_in_use);
							break;

						case 4:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_07(p_params, p_class07_obj->p_entries_in_use);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj04_att07_get(p_params, p_class07_obj->p_entries_in_use);
							break;

						case 7:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_07(p_params, p_class07_obj->p_entries_in_use);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj07_att07_get(p_params, p_class07_obj->p_entries_in_use);
							break;

						case 8:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_07(p_params, p_class07_obj->p_entries_in_use);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj08_att07_get(p_params, p_class07_obj->p_entries_in_use);
							break;

						case 9:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_07(p_params, p_class07_obj->p_entries_in_use);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj09_att07_get(p_params, p_class07_obj->p_entries_in_use);
							break;

						case 10:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_07(p_params, p_class07_obj->p_entries_in_use);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj10_att07_get(p_params, p_class07_obj->p_entries_in_use);
							break;

						case 11:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_07(p_params, p_class07_obj->p_entries_in_use);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj11_att07_get(p_params, p_class07_obj->p_entries_in_use);
							break;

						case 12:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_07(p_params, p_class07_obj->p_entries_in_use);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj12_att07_get(p_params, p_class07_obj->p_entries_in_use);
							break;

						case 13:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_07(p_params, p_class07_obj->p_entries_in_use);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj13_att07_get(p_params, p_class07_obj->p_entries_in_use);
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
			case 8:
				if (p_params->distributor_state == DIST_BEFORE_CLASS_FUNCTION)
				{
					p_params->handled = FALSE;

					switch(p_params->child_index)
					{
						case 0:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_08(p_params, p_class07_obj->p_profile_entries);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj00_att08_get(p_params, p_class07_obj->p_profile_entries);
							break;

						case 2:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_08(p_params, p_class07_obj->p_profile_entries);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj02_att08_get(p_params, p_class07_obj->p_profile_entries);
							break;

						case 4:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_08(p_params, p_class07_obj->p_profile_entries);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj04_att08_get(p_params, p_class07_obj->p_profile_entries);
							break;

						case 7:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_08(p_params, p_class07_obj->p_profile_entries);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj07_att08_get(p_params, p_class07_obj->p_profile_entries);
							break;

						case 8:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_08(p_params, p_class07_obj->p_profile_entries);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj08_att08_get(p_params, p_class07_obj->p_profile_entries);
							break;

						case 9:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_08(p_params, p_class07_obj->p_profile_entries);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj09_att08_get(p_params, p_class07_obj->p_profile_entries);
							break;

						case 10:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_08(p_params, p_class07_obj->p_profile_entries);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj10_att08_get(p_params, p_class07_obj->p_profile_entries);
							break;

						case 11:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_08(p_params, p_class07_obj->p_profile_entries);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj11_att08_get(p_params, p_class07_obj->p_profile_entries);
							break;

						case 12:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_08(p_params, p_class07_obj->p_profile_entries);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj12_att08_get(p_params, p_class07_obj->p_profile_entries);
							break;

						case 13:
							/* Clone new attribute */
							R_DLMS_IC07_REDIRECT_08(p_params, p_class07_obj->p_profile_entries);
							/* APPLICATION */
							result = R_DLMS_USER_ic07_obj13_att08_get(p_params, p_class07_obj->p_profile_entries);
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
							result = R_DLMS_USER_ic07_obj00_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 2:
							result = R_DLMS_USER_ic07_obj02_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 4:
							result = R_DLMS_USER_ic07_obj04_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 7:
							result = R_DLMS_USER_ic07_obj07_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 8:
							result = R_DLMS_USER_ic07_obj08_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 9:
							result = R_DLMS_USER_ic07_obj09_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 10:
							result = R_DLMS_USER_ic07_obj10_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 11:
							result = R_DLMS_USER_ic07_obj11_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 12:
							result = R_DLMS_USER_ic07_obj12_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 13:
							result = R_DLMS_USER_ic07_obj13_meth01_action(p_params, (void *)p_params->service_params.malloc.p_content);
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

					switch(p_params->child_index)
					{
						case 0:
							result = R_DLMS_USER_ic07_obj00_meth02_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 2:
							result = R_DLMS_USER_ic07_obj02_meth02_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 4:
							result = R_DLMS_USER_ic07_obj04_meth02_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 7:
							result = R_DLMS_USER_ic07_obj07_meth02_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 8:
							result = R_DLMS_USER_ic07_obj08_meth02_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 9:
							result = R_DLMS_USER_ic07_obj09_meth02_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 10:
							result = R_DLMS_USER_ic07_obj10_meth02_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 11:
							result = R_DLMS_USER_ic07_obj11_meth02_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 12:
							result = R_DLMS_USER_ic07_obj12_meth02_action(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

						case 13:
							result = R_DLMS_USER_ic07_obj13_meth02_action(p_params, (void *)p_params->service_params.malloc.p_content);
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
	
		p_params->result.result.action = (ActionResult_Value)result;
	}
	else
	{
	 /* Nothing code here */
	}
}

