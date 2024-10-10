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
* File Name    : r_dlms_object_class03.c
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
#include "r_dlms_class03.h"
#include "r_dlms_objects.h"
#include "r_dlms_type.h"

#include "r_dlms_usercode_class03.h"

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
/*Class 03 record table*/
/*---------------------------------------------------------------------------*/
const class03_child_record_t	g_objects_child_table_class03[] =
{
	/* 00 - Cumulative Energy kVAh Export */
	{ 
		{1,   0,   10,   8,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj00_att03_Scaler_Unit,

	},

	/* 01 - Cumulative Energy kWh Export */
	{ 
		{1,   0,   2,   8,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj01_att03_Scaler_Unit,

	},

	/* 02 - Cumulative power ON  */
	{ 
		{0,   0,   94,   91,   14,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj02_att03_Scaler_Unit,

	},

	/* 03 - Neutral current rms */
	{ 
		{1,   0,   91,   7,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj03_att03_Scaler_Unit,

	},

	/* 04 - Active Power   */
	{ 
		{1,   0,   1,   7,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj04_att03_Scaler_Unit,

	},

	/* 05 - Apparent Power */
	{ 
		{1,   0,   9,   7,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj05_att03_Scaler_Unit,

	},

	/* 06 - Cumulative Energy kVAh */
	{ 
		{1,   0,   9,   8,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj06_att03_Scaler_Unit,

	},

	/* 07 - Cumulative Energy kWh */
	{ 
		{1,   0,   1,   8,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj07_att03_Scaler_Unit,

	},

	/* 08 - Frequency */
	{ 
		{1,   0,   14,   7,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj08_att03_Scaler_Unit,

	},

	/* 09 - Phase current rms */
	{ 
		{1,   0,   11,   7,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj09_att03_Scaler_Unit,

	},

	/* 10 - Signed Power Factor */
	{ 
		{1,   0,   13,   7,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj10_att03_Scaler_Unit,

	},

	/* 11 - Voltage rms */
	{ 
		{1,   0,   12,   7,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj11_att03_Scaler_Unit,

	},

	/* 12 - Average voltage average of integration period */
	{ 
		{1,   0,   12,   27,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj12_att03_Scaler_Unit,

	},

	/* 13 - AverageCurrent average of integration period */
	{ 
		{1,   0,   11,   27,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj13_att03_Scaler_Unit,

	},

	/* 14 - AvgPF For Billing */
	{ 
		{1,   0,   13,   0,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj14_att03_Scaler_Unit,

	},

	/* 15 - Billing date */
	{ 
		{0,   0,   0,   1,   2,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_OCTET_STRING(12), NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj15_att03_Scaler_Unit,

	},

	/* 16 - Block Energy kVAh */
	{ 
		{1,   0,   9,   29,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj16_att03_Scaler_Unit,

	},

	/* 17 - Block Energy kVAh Export */
	{ 
		{1,   0,   10,   29,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj17_att03_Scaler_Unit,

	},

	/* 18 - Block Energy kWh */
	{ 
		{1,   0,   1,   29,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj18_att03_Scaler_Unit,

	},

	/* 19 - Block Energy kWh Export */
	{ 
		{1,   0,   2,   29,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj19_att03_Scaler_Unit,

	},

	/* 20 - Cumulative Energy kVAh TZ1 */
	{ 
		{1,   0,   9,   8,   1,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj20_att03_Scaler_Unit,

	},

	/* 21 - Cumulative Energy kVAh TZ2 */
	{ 
		{1,   0,   9,   8,   2,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj21_att03_Scaler_Unit,

	},

	/* 22 - Cumulative Energy kWh TZ3 */
	{ 
		{1,   0,   1,   8,   3,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj22_att03_Scaler_Unit,

	},

	/* 23 - Cumulative Energy kVAh TZ3 */
	{ 
		{1,   0,   9,   8,   3,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj23_att03_Scaler_Unit,

	},

	/* 24 - Cumulative Energy kVAh TZ4 */
	{ 
		{1,   0,   9,   8,   4,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj24_att03_Scaler_Unit,

	},

	/* 25 - Cumulative Energy kWh TZ1  */
	{ 
		{1,   0,   1,   8,   1,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj25_att03_Scaler_Unit,

	},

	/* 26 - Cumulative Energy kWh TZ2 */
	{ 
		{1,   0,   1,   8,   2,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj26_att03_Scaler_Unit,

	},

	/* 27 - Cumulative Energy kWh TZ4 */
	{ 
		{1,   0,   1,   8,   4,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj27_att03_Scaler_Unit,

	},

	/* 28 - Current rms */
	{ 
		{1,   0,   94,   91,   14,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj28_att03_Scaler_Unit,

	},

	/* 29 - Total billing power ON duration */
	{ 
		{0,   0,   94,   91,   13,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_DOUBLE_LONG_UNSIGNED, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj29_att03_Scaler_Unit,

	},

	/* 30 - Cumulative Energy kWh  */
	{ 
		{1,   0,   1,   9,   0,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj30_att03_Scaler_Unit,

	},

	/* 31 - Cumulative Energy kWh TZ5 */
	{ 
		{1,   0,   1,   8,   5,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj31_att03_Scaler_Unit,

	},

	/* 32 - Cumulative energy kWh TZ6 */
	{ 
		{1,   0,   1,   8,   6,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj32_att03_Scaler_Unit,

	},

	/* 33 - Cumulative energy kVAh TZ5 */
	{ 
		{1,   0,   9,   8,   5,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj33_att03_Scaler_Unit,

	},

	/* 34 - Cumulative energy kVAh TZ6 */
	{ 
		{1,   0,   9,   8,   6,   255},
		(access_right_t *)g_objects_access_right_table[0],
		CHOICE(CHOICE_FLOAT32, NULL),
		(scaler_unit_t *)&g_dlms_ic03_obj34_att03_Scaler_Unit,

	},


};

const uint16_t 	g_objects_child_table_class03_length = sizeof(g_objects_child_table_class03) / sizeof(class03_child_record_t);



/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Class03Distributor
* Interface     : void R_DLMS_OBJECTS_Class03Distributor(
*               :     distributor_params_t * p_param,
*               : );
* Description   : User distributor function for GET/SET/ACTION service of class 03
* Arguments     : distributor_params_t * p_param: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_Class03Distributor(distributor_params_t *p_params)
{
	class03_child_record_t	* p_class03_obj = (class03_child_record_t *)p_params->p_child_record;
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
#if defined(CLASS03_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 0:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj00_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 1:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj01_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 2:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj02_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 3:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj03_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 4:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj04_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 5:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj05_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 6:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj06_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 7:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj07_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 8:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj08_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 9:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj09_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 10:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj10_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 11:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj11_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 12:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj12_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 13:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj13_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 14:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj14_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 15:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj15_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 16:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj16_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 17:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj17_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ18_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ18_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 18:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj18_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ19_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ19_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 19:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj19_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ20_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ20_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 20:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj20_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ21_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ21_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 21:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj21_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ22_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ22_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 22:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj22_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ23_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ23_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 23:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj23_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ24_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ24_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 24:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj24_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ25_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ25_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 25:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj25_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ26_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ26_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 26:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj26_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ27_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ27_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 27:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj27_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ28_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ28_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 28:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj28_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ29_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ29_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 29:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj29_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ30_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ30_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 30:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj30_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ31_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ31_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 31:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj31_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ32_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ32_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 32:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj32_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ33_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ33_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 33:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj33_att02_get(p_params, &p_class03_obj->value);
							break;

#endif
#if defined(CLASS03_OBJ34_ATTR02_GET_USERFUNCTION_ENABLE) && (CLASS03_OBJ34_ATTR02_GET_USERFUNCTION_ENABLE == TRUE)
						case 34:
							/* Clone new attribute */
							R_DLMS_IC03_REDIRECT_02(p_params, p_class03_obj->value);
							/* APPLICATION */
							result = R_DLMS_USER_ic03_obj34_att02_get(p_params, &p_class03_obj->value);
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
#if defined(CLASS03_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 0:
							result = R_DLMS_USER_ic03_obj00_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 1:
							result = R_DLMS_USER_ic03_obj01_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 2:
							result = R_DLMS_USER_ic03_obj02_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 3:
							result = R_DLMS_USER_ic03_obj03_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 4:
							result = R_DLMS_USER_ic03_obj04_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 5:
							result = R_DLMS_USER_ic03_obj05_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 6:
							result = R_DLMS_USER_ic03_obj06_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 7:
							result = R_DLMS_USER_ic03_obj07_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 8:
							result = R_DLMS_USER_ic03_obj08_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 9:
							result = R_DLMS_USER_ic03_obj09_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 10:
							result = R_DLMS_USER_ic03_obj10_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 11:
							result = R_DLMS_USER_ic03_obj11_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 12:
							result = R_DLMS_USER_ic03_obj12_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 13:
							result = R_DLMS_USER_ic03_obj13_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 14:
							result = R_DLMS_USER_ic03_obj14_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 15:
							result = R_DLMS_USER_ic03_obj15_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 16:
							result = R_DLMS_USER_ic03_obj16_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 17:
							result = R_DLMS_USER_ic03_obj17_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ18_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ18_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 18:
							result = R_DLMS_USER_ic03_obj18_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ19_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ19_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 19:
							result = R_DLMS_USER_ic03_obj19_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ20_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ20_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 20:
							result = R_DLMS_USER_ic03_obj20_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ21_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ21_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 21:
							result = R_DLMS_USER_ic03_obj21_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ22_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ22_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 22:
							result = R_DLMS_USER_ic03_obj22_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ23_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ23_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 23:
							result = R_DLMS_USER_ic03_obj23_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ24_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ24_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 24:
							result = R_DLMS_USER_ic03_obj24_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ25_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ25_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 25:
							result = R_DLMS_USER_ic03_obj25_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ26_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ26_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 26:
							result = R_DLMS_USER_ic03_obj26_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ27_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ27_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 27:
							result = R_DLMS_USER_ic03_obj27_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ28_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ28_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 28:
							result = R_DLMS_USER_ic03_obj28_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ29_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ29_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 29:
							result = R_DLMS_USER_ic03_obj29_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ30_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ30_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 30:
							result = R_DLMS_USER_ic03_obj30_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ31_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ31_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 31:
							result = R_DLMS_USER_ic03_obj31_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ32_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ32_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 32:
							result = R_DLMS_USER_ic03_obj32_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ33_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ33_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 33:
							result = R_DLMS_USER_ic03_obj33_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
							break;

#endif
							
#if defined(CLASS03_OBJ34_ATTR02_SET_USERFUNCTION_ENABLE) && (CLASS03_OBJ34_ATTR02_SET_USERFUNCTION_ENABLE == TRUE)
						case 34:
							result = R_DLMS_USER_ic03_obj34_att02_set(p_params, (void *)p_params->service_params.malloc.p_content);
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

