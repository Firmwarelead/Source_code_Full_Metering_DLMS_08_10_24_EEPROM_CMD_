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
* File Name    : r_dlms_type.c
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
#include "r_dlms_type.h"


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


/************************************************************************
* Encode, decode, redirect functions of ActiveRelayTime
************************************************************************/
/******************************************************************************
* Function Name   : R_DLMS_Encode_ActiveRelayTime
* Interface       : uint16_t R_DLMS_Encode_ActiveRelayTime(
*                 :     MandatoryString	out_data,
*                 :     ActiveRelayTime_t * p_encode_data
*                 : );
* Description     : Encode ActiveRelayTime_t value
* Arguments       : MandatoryString	out_data	: Buffer to store output data
*                 : ActiveRelayTime_t * p_encode_data		: Point to the variable contains value
* Return Value    : uint16_t, Actual encoded length
*                 :     0 mean error.
*                 :     > 0 is success, its value is actual used length of [buf]
******************************************************************************/
uint16_t R_DLMS_Encode_ActiveRelayTime(MandatoryString out_data, ActiveRelayTime_t * p_encode_data)
{
	uint16_t	length;								/* Output of common encoding API */
	uint8_t		u8;									/* Common for length encode */
	uint8_t		* p_head = out_data.p_content;		/* Temp pointer for length calc */

	/* Check input parameter */
	ASSERT_TRUE_RET_ZERO(
		out_data.p_content == NULL ||
		out_data.length == 0 ||
		p_encode_data == NULL
	);

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 3);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_DOUBLE_LONG_UNSIGNED, (uint8_t *)&p_encode_data->duration, 4);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_DOUBLE_LONG_UNSIGNED, (uint8_t *)&p_encode_data->lockout_period, 4);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_encode_data->number_of_repeat, 1);
	}
	return (uint16_t)(out_data.p_content - p_head);
}

/******************************************************************************
* Function Name : R_DLMS_Decode_ActiveRelayTime
* Interface     : uint16_t R_DLMS_Decode_ActiveRelayTime(
*               :     ActiveRelayTime_t * p_decode_data,
*               :     MandatoryString in_data,
*               : );
* Description   : Decode ActiveRelayTime_t value
* Arguments     : ActiveRelayTime_t * p_decode_data: Point to the scaler_unit value
*               : MandatoryString in_data      : Buffer of encoded data
* Function Calls: None
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_Decode_ActiveRelayTime(ActiveRelayTime_t * p_decode_data, MandatoryString in_data)
{
	uint16_t	length;							/* Output of common decoding API */
	uint8_t		u8;								/* Common for length decode */
	uint8_t		* p_head = in_data.p_content;	/* Temp pointer for length calc */

	/* Check input parameter */
	ASSERT_TRUE_RET_ZERO(
		p_decode_data == NULL ||
		in_data.p_content == NULL ||
		in_data.length == 0
	);

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 3, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_decode_data->duration, 4, TAG_DATA_DOUBLE_LONG_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_decode_data->lockout_period, 4, TAG_DATA_DOUBLE_LONG_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_decode_data->number_of_repeat, 1, TAG_DATA_UNSIGNED, in_data);
	}

	return (uint16_t)(in_data.p_content - p_head);
}

/******************************************************************************
* Function Name : R_DLMS_Redirect_ActiveRelayTime
* Interface     : ActiveRelayTime_t * R_DLMS_Redirect_ActiveRelayTime(
*               :     distributor_params_t * p_params,
*               :     ActiveRelayTime_t *p_object,
*               : );
* Description   : Create or redirect one ActiveRelayTime_t object
* Arguments     : distributor_params_t *p_params
*               : ActiveRelayTime_t * p_object: Pointer of ActiveRelayTime_t which was created
* Function Calls: None
* Return Value  : ActiveRelayTime_t *
******************************************************************************/
ActiveRelayTime_t * R_DLMS_Redirect_ActiveRelayTime(distributor_params_t *p_params, ActiveRelayTime_t * p_object)
{
	ActiveRelayTime_t	 * p_clone_obj;
	uint8_t  * p_alloc, * p_head;
	
	
	
	/* Get start pointer of malloc which was reserved */
	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, ActiveRelayTime_t, p_alloc);



	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}
/************************************************************************
* Encode, decode, redirect functions of PassiveRelayTime
************************************************************************/
/******************************************************************************
* Function Name   : R_DLMS_Encode_PassiveRelayTime
* Interface       : uint16_t R_DLMS_Encode_PassiveRelayTime(
*                 :     MandatoryString	out_data,
*                 :     PassiveRelayTime_t * p_encode_data
*                 : );
* Description     : Encode PassiveRelayTime_t value
* Arguments       : MandatoryString	out_data	: Buffer to store output data
*                 : PassiveRelayTime_t * p_encode_data		: Point to the variable contains value
* Return Value    : uint16_t, Actual encoded length
*                 :     0 mean error.
*                 :     > 0 is success, its value is actual used length of [buf]
******************************************************************************/
uint16_t R_DLMS_Encode_PassiveRelayTime(MandatoryString out_data, PassiveRelayTime_t * p_encode_data)
{
	uint16_t	length;								/* Output of common encoding API */
	uint8_t		u8;									/* Common for length encode */
	uint8_t		* p_head = out_data.p_content;		/* Temp pointer for length calc */

	/* Check input parameter */
	ASSERT_TRUE_RET_ZERO(
		out_data.p_content == NULL ||
		out_data.length == 0 ||
		p_encode_data == NULL
	);

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 4);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_DOUBLE_LONG_UNSIGNED, (uint8_t *)&p_encode_data->duration, 4);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_DOUBLE_LONG_UNSIGNED, (uint8_t *)&p_encode_data->lockout_period, 4);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_encode_data->number_of_repeat, 1);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, p_encode_data->execution_time.p_content, p_encode_data->execution_time.length);
	}
	return (uint16_t)(out_data.p_content - p_head);
}

/******************************************************************************
* Function Name : R_DLMS_Decode_PassiveRelayTime
* Interface     : uint16_t R_DLMS_Decode_PassiveRelayTime(
*               :     PassiveRelayTime_t * p_decode_data,
*               :     MandatoryString in_data,
*               : );
* Description   : Decode PassiveRelayTime_t value
* Arguments     : PassiveRelayTime_t * p_decode_data: Point to the scaler_unit value
*               : MandatoryString in_data      : Buffer of encoded data
* Function Calls: None
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_Decode_PassiveRelayTime(PassiveRelayTime_t * p_decode_data, MandatoryString in_data)
{
	uint16_t	length;							/* Output of common decoding API */
	uint8_t		u8;								/* Common for length decode */
	uint8_t		* p_head = in_data.p_content;	/* Temp pointer for length calc */

	/* Check input parameter */
	ASSERT_TRUE_RET_ZERO(
		p_decode_data == NULL ||
		in_data.p_content == NULL ||
		in_data.length == 0
	);

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 4, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_decode_data->duration, 4, TAG_DATA_DOUBLE_LONG_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_decode_data->lockout_period, 4, TAG_DATA_DOUBLE_LONG_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_decode_data->number_of_repeat, 1, TAG_DATA_UNSIGNED, in_data);
		OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(length, &p_decode_data->execution_time, TAG_DATA_OCTET_STRING, in_data);
	}

	return (uint16_t)(in_data.p_content - p_head);
}

/******************************************************************************
* Function Name : R_DLMS_Redirect_PassiveRelayTime
* Interface     : PassiveRelayTime_t * R_DLMS_Redirect_PassiveRelayTime(
*               :     distributor_params_t * p_params,
*               :     PassiveRelayTime_t *p_object,
*               : );
* Description   : Create or redirect one PassiveRelayTime_t object
* Arguments     : distributor_params_t *p_params
*               : PassiveRelayTime_t * p_object: Pointer of PassiveRelayTime_t which was created
* Function Calls: None
* Return Value  : PassiveRelayTime_t *
******************************************************************************/
PassiveRelayTime_t * R_DLMS_Redirect_PassiveRelayTime(distributor_params_t *p_params, PassiveRelayTime_t * p_object)
{
	PassiveRelayTime_t	 * p_clone_obj;
	uint8_t  * p_alloc, * p_head;
	
	uint16_t length = 0;
	
	/* Get start pointer of malloc which was reserved */
	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, PassiveRelayTime_t, p_alloc);

	OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->execution_time, 12, p_alloc);


	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}
