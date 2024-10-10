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
* File Name    : r_dlms_object_class01.c
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
#include "r_dlms_class01.h"
#include "r_dlms_objects.h"
#include "r_dlms_type.h"

#include "r_dlms_usercode_class01.h"

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
/*Class 01 record table*/
/*---------------------------------------------------------------------------*/
const class01_child_record_t	g_objects_child_table_class01[] =
{
	/* 00 - Cumulative billing count */
	{ 
		{0,   0,   0,   1,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),

	},

	/* 01 - Cumulative programming count  */
	{ 
		{0,   0,   96,   2,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_LONG_UNSIGNED, NULL),

	},

	/* 02 - Cumulative tamper count */
	{ 
		{0,   0,   94,   91,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),

	},

	/* 03 - Current rating */
	{ 
		{0,   0,   94,   91,   12,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_OCTET_STRING(5), NULL),

	},

	/* 04 - Firmware version for meter */
	{ 
		{1,   0,   0,   2,   0,   255},
		(access_right_t *)g_objects_access_right_table[1],
		CHOICE(CHOICE_OCTET_STRING(8), NULL),

	},

	/* 05 - Logical Device Name */
	{ 
		{0,   0,   42,   0,   0,   255},
		(access_right_t *)g_objects_access_right_table[2],
		CHOICE(CHOICE_OCTET_STRING(8), NULL),

	},

	/* 06 - Manufacture Name */
	{ 
		{0,   0,   96,   1,   1,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_OCTET_STRING(41), NULL),

	},

	/* 07 - Meter category */
	{ 
		{0,   0,   94,   91,   11,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_OCTET_STRING(2), NULL),

	},

	/* 08 - Meter serial number */
	{ 
		{0,   0,   96,   1,   0,   255},
		(access_right_t *)g_objects_access_right_table[3],
		CHOICE(CHOICE_OCTET_STRING(16), NULL),

	},

	/* 09 - Meter Type */
	{ 
		{0,   0,   94,   91,   9,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_UNSIGNED, NULL),

	},

	/* 10 - Meter Year of Manufacture */
	{ 
		{0,   0,   96,   1,   4,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_OCTET_STRING(4), NULL),

	},

	/* 11 - DeviceID */
	{ 
		{0,   0,   96,   1,   2,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_OCTET_STRING(19), NULL),

	},

	/* 12 - Available Billing Count */
	{ 
		{0,   0,   0,   1,   1,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_UNSIGNED, NULL),

	},

	/* 13 - Daily load capture period */
	{ 
		{1,   0,   0,   8,   5,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),

	},

	/* 14 - ESW */
	{ 
		{0,   0,   94,   91,   18,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_BIT_STRING(128), NULL),

	},

	/* 15 - Event code object Controll event */
	{ 
		{0,   0,   96,   11,   6,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_LONG_UNSIGNED, NULL),

	},

	/* 16 - Event code object current */
	{ 
		{0,   0,   96,   11,   1,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_LONG_UNSIGNED, NULL),

	},

	/* 17 - Event code object Non_Roller */
	{ 
		{0,   0,   96,   11,   5,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_LONG_UNSIGNED, NULL),

	},

	/* 18 - Event code object Other */
	{ 
		{0,   0,   96,   11,   4,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_LONG_UNSIGNED, NULL),

	},

	/* 19 - Event code object power */
	{ 
		{0,   0,   96,   11,   2,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_LONG_UNSIGNED, NULL),

	},

	/* 20 - Event code object Trans */
	{ 
		{0,   0,   96,   11,   3,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_LONG_UNSIGNED, NULL),

	},

	/* 21 - Event code object voltage */
	{ 
		{0,   0,   96,   11,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_LONG_UNSIGNED, NULL),

	},

	/* 22 - Block load capture period  */
	{ 
		{1,   0,   0,   8,   4,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_LONG_UNSIGNED, NULL),

	},

	/* 23 - Current balance amount */
	{ 
		{0,   0,   94,   96,   24,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),

	},

	/* 24 - Current balance time */
	{ 
		{0,   0,   94,   96,   25,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_OCTET_STRING(12), NULL),

	},

	/* 25 - Demand integration period  */
	{ 
		{1,   0,   0,   8,   0,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_LONG_UNSIGNED, NULL),

	},

	/* 26 - ESWF */
	{ 
		{0,   0,   94,   91,   26,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_BIT_STRING(128), NULL),

	},

	/* 27 - Last Token Recharge amount */
	{ 
		{0,   0,   94,   96,   21,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),

	},

	/* 28 - Last Token Recharge time */
	{ 
		{0,   0,   94,   96,   22,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_OCTET_STRING(12), NULL),

	},

	/* 29 - Metering Mode */
	{ 
		{0,   0,   94,   96,   19,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_UNSIGNED, NULL),

	},

	/* 30 - Payment Mode */
	{ 
		{0,   0,   94,   96,   20,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_UNSIGNED, NULL),

	},

	/* 31 - Total amount at last recharge */
	{ 
		{0,   0,   94,   96,   23,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),

	},

	/* 32 - SMO 1 */
	{ 
		{0,   0,   96,   13,   0,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_OCTET_STRING(100), NULL),

	},

	/* 33 - SMO2 */
	{ 
		{0,   0,   96,   13,   1,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_OCTET_STRING(10), NULL),

	},

	/* 34 - MR invocation counter */
	{ 
		{0,   0,   43,   1,   2,   255},
		(access_right_t *)g_objects_access_right_table[5],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),

	},

	/* 35 - US invocation counter */
	{ 
		{0,   0,   43,   1,   3,   255},
		(access_right_t *)g_objects_access_right_table[5],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),

	},

	/* 36 - Push invocation counter */
	{ 
		{0,   0,   43,   1,   4,   255},
		(access_right_t *)g_objects_access_right_table[5],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),

	},

	/* 37 - FWU invocation counter */
	{ 
		{0,   0,   43,   1,   5,   255},
		(access_right_t *)g_objects_access_right_table[5],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),

	},

	/* 38 - Active relay time object */
	{ 
		{1,   0,   96,   128,   25,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_STRUCTURE, NULL),

	},

	/* 39 - Passive relay time */
	{ 
		{1,   0,   96,   128,   30,   255},
		(access_right_t *)g_objects_access_right_table[4],
		CHOICE(CHOICE_STRUCTURE, NULL),

	},


};

const uint16_t 	g_objects_child_table_class01_length = sizeof(g_objects_child_table_class01) / sizeof(class01_child_record_t);



/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Class01Distributor
* Interface     : void R_DLMS_OBJECTS_Class01Distributor(
*               :     distributor_params_t * p_param,
*               : );
* Description   : User distributor function for GET/SET/ACTION service of class 01
* Arguments     : distributor_params_t * p_param: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_Class01Distributor(distributor_params_t *p_params)
{
	class01_child_record_t	* p_class01_obj = (class01_child_record_t *)p_params->p_child_record;
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
				if (p_params->distributor_state == DIST_BEFORE_CLASS_FUNCTION)
				{
					p_params->handled = FALSE;

					switch(p_params->child_index)
					{
#if defined(CLASS01_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 0:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj00_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 1:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj01_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 2:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj02_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 3:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj03_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 4:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj04_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 5:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj05_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 6:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj06_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 7:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj07_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 8:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj08_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 9:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj09_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 10:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj10_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 11:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj11_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 12:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj12_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 13:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj13_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 14:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj14_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 15:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj15_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 16:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj16_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 17:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj17_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ18_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ18_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 18:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj18_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ19_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ19_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 19:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj19_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ20_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ20_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 20:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj20_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ21_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ21_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 21:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj21_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ22_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ22_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 22:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj22_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ23_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ23_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 23:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj23_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ24_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ24_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 24:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj24_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ25_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ25_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 25:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj25_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ26_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ26_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 26:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj26_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ27_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ27_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 27:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj27_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ28_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ28_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 28:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj28_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ29_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ29_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 29:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj29_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ30_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ30_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 30:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj30_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ31_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ31_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 31:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj31_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ32_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ32_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 32:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj32_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ33_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ33_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 33:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj33_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ34_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ34_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 34:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj34_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ35_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ35_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 35:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj35_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ36_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ36_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 36:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj36_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ37_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ37_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 37:
							/* Clone new attribute */
							R_DLMS_IC01_REDIRECT_02(p_params, p_class01_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic01_obj37_att02_get(p_params, &p_class01_obj->value);
							break;

#endif
#if defined(CLASS01_OBJ38_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ38_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 38:
							/* Clone new attribute */
							p_object = R_DLMS_Redirect_ActiveRelayTime(p_params, NULL);
							ASSERT_TRUE_RET(p_object == NULL);
							/* Call user function to assign value to object */
							result = R_DLMS_USER_ic01_obj38_att02_get(p_params, (ActiveRelayTime_t *)p_object);
							/* Encode data object */
							length = R_DLMS_Encode_ActiveRelayTime(p_params->out_data, (ActiveRelayTime_t *)p_object);
							*p_params->p_out_encoded_len = length;
							p_params->handled = TRUE;
							break;

#endif
#if defined(CLASS01_OBJ39_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS01_OBJ39_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 39:
							/* Clone new attribute */
							p_object = R_DLMS_Redirect_PassiveRelayTime(p_params, NULL);
							ASSERT_TRUE_RET(p_object == NULL);
							/* Call user function to assign value to object */
							result = R_DLMS_USER_ic01_obj39_att02_get(p_params, (PassiveRelayTime_t *)p_object);
							/* Encode data object */
							length = R_DLMS_Encode_PassiveRelayTime(p_params->out_data, (PassiveRelayTime_t *)p_object);
							*p_params->p_out_encoded_len = length;
							p_params->handled = TRUE;
							break;

#endif

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
			case 2:
				if ((p_params->distributor_state == DIST_AFTER_CLASS_FUNCTION)&&
			      (p_params->service_params.decode_success == TRUE))
				{
					p_params->service_params.sync = FALSE;

					switch(p_params->child_index)
					{
#if defined(CLASS01_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 0:
							result = R_DLMS_USER_ic01_obj00_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 1:
							result = R_DLMS_USER_ic01_obj01_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 2:
							result = R_DLMS_USER_ic01_obj02_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 3:
							result = R_DLMS_USER_ic01_obj03_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 4:
							result = R_DLMS_USER_ic01_obj04_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 5:
							result = R_DLMS_USER_ic01_obj05_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 6:
							result = R_DLMS_USER_ic01_obj06_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 7:
							result = R_DLMS_USER_ic01_obj07_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 8:
							result = R_DLMS_USER_ic01_obj08_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 9:
							result = R_DLMS_USER_ic01_obj09_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 10:
							result = R_DLMS_USER_ic01_obj10_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 11:
							result = R_DLMS_USER_ic01_obj11_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 12:
							result = R_DLMS_USER_ic01_obj12_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 13:
							result = R_DLMS_USER_ic01_obj13_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 14:
							result = R_DLMS_USER_ic01_obj14_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 15:
							result = R_DLMS_USER_ic01_obj15_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 16:
							result = R_DLMS_USER_ic01_obj16_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 17:
							result = R_DLMS_USER_ic01_obj17_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ18_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ18_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 18:
							result = R_DLMS_USER_ic01_obj18_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ19_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ19_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 19:
							result = R_DLMS_USER_ic01_obj19_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ20_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ20_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 20:
							result = R_DLMS_USER_ic01_obj20_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ21_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ21_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 21:
							result = R_DLMS_USER_ic01_obj21_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ22_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ22_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 22:
							result = R_DLMS_USER_ic01_obj22_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ23_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ23_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 23:
							result = R_DLMS_USER_ic01_obj23_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ24_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ24_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 24:
							result = R_DLMS_USER_ic01_obj24_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ25_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ25_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 25:
							result = R_DLMS_USER_ic01_obj25_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ26_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ26_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 26:
							result = R_DLMS_USER_ic01_obj26_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ27_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ27_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 27:
							result = R_DLMS_USER_ic01_obj27_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ28_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ28_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 28:
							result = R_DLMS_USER_ic01_obj28_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ29_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ29_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 29:
							result = R_DLMS_USER_ic01_obj29_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ30_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ30_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 30:
							result = R_DLMS_USER_ic01_obj30_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ31_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ31_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 31:
							result = R_DLMS_USER_ic01_obj31_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ32_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ32_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 32:
							result = R_DLMS_USER_ic01_obj32_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ33_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ33_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 33:
							result = R_DLMS_USER_ic01_obj33_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ34_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ34_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 34:
							result = R_DLMS_USER_ic01_obj34_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ35_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ35_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 35:
							result = R_DLMS_USER_ic01_obj35_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ36_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ36_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 36:
							result = R_DLMS_USER_ic01_obj36_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ37_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ37_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 37:
							result = R_DLMS_USER_ic01_obj37_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ38_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ38_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 38:
							p_object = R_DLMS_Redirect_ActiveRelayTime(p_params, NULL);
							ASSERT_TRUE_RET(p_object == NULL);
							R_DLMS_Decode_ActiveRelayTime((ActiveRelayTime_t *)p_object, p_params->in_data);
							result = R_DLMS_USER_ic01_obj38_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS01_OBJ39_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS01_OBJ39_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 39:
							p_object = R_DLMS_Redirect_PassiveRelayTime(p_params, NULL);
							ASSERT_TRUE_RET(p_object == NULL);
							R_DLMS_Decode_PassiveRelayTime((PassiveRelayTime_t *)p_object, p_params->in_data);
							result = R_DLMS_USER_ic01_obj39_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							

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

