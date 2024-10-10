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
* File Name    : r_dlms_class03.c
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
#include "r_dlms_class03.h"
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


/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class03Init
* Interface     : void R_DLMS_CLASSES_Class03Init(void)
* Description   : Initialize class 03
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class03Init(void)
{
	/* Put init code of class 03 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class03PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class03PollingProcessing(void)
* Description   : Polling process of class 03
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class03PollingProcessing(void)
{
	/* Put polling processing code of class 03 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class03AsscOpened
* Interface     : void R_DLMS_CLASSES_Class03AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 03
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class03AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 03 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class03AsscClosing
* Interface     : void R_DLMS_CLASSES_Class03AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 03
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class03AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 03 here */
}
/******************************************************************************
* Function Name   : R_DLMS_CLASSES_EncodeScalerUnit
* Interface       : uint16_t R_DLMS_CLASSES_EncodeScalerUnit(
*                 :     MandatoryString	out_data,
*                 :     scaler_unit_t   *p_scaler_unit
*                 : );
* Description     : Encode scaler_unit_t value
* Arguments       : MandatoryString	out_data	: Buffer to store output data
*                 : scaler_unit_t *p_scaler_unit: Point to the scaler_unit value
* Function Calls  : None
* Return Value    : uint16_t, Actual encoded length
*                 :     0 mean error.
*                 :     > 0 is success, its value is actual used length of [buf]
******************************************************************************/
uint16_t R_DLMS_CLASSES_EncodeScalerUnit(MandatoryString out_data, scaler_unit_t *p_scaler_unit)
{
	uint16_t	length;								/* Output of common encoding API */
	uint16_t	count;								/* Counter for loop */
	uint8_t		u8;									/* Common for length encode */
	uint8_t		*p_head = out_data.p_content;		/* Temp pointer for length calc */

													/* Check input parameter */
	ASSERT_TRUE_RET_ZERO(
		out_data.p_content == NULL ||
		out_data.length == 0 ||
		p_scaler_unit == NULL
	);

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_INTEGER, (uint8_t *)&p_scaler_unit->scaler, sizeof(int8_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_ENUM, (uint8_t *)&p_scaler_unit->unit, 1);
	}

	return (uint16_t)(out_data.p_content - p_head);
}
/* For classes 3,4,5 */
/******************************************************************************
* Function Name : R_DLMS_CLASSES_DecodeScalerUnit
* Interface     : uint16_t R_DLMS_CLASSES_DecodeScalerUnit(
*               :     scaler_unit_t * p_scaler_unit,
*               :     MandatoryString in_data      ,
*               : );
* Description   : Decode scaler_unit_t value
* Arguments     : scaler_unit_t * p_scaler_unit: Point to the scaler_unit value
*               : MandatoryString in_data      : Buffer of encoded data
* Function Calls: None
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_CLASSES_DecodeScalerUnit(scaler_unit_t *p_scaler_unit, MandatoryString	in_data)
{
	uint16_t	length;							/* Output of common decoding API */
	uint8_t		u8;								/* Common for length decode */
	uint8_t		*p_head = in_data.p_content;	/* Temp pointer for length calc */

												/* Check input parameter */
	ASSERT_TRUE_RET_ZERO(
		p_scaler_unit == NULL ||
		in_data.p_content == NULL ||
		in_data.length == 0
	);

	/* Structure, 2 elements */
	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_scaler_unit->scaler, sizeof(int8_t), TAG_DATA_INTEGER, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_scaler_unit->unit, 1, TAG_DATA_ENUM, in_data);
	}

	return (uint16_t)(in_data.p_content - p_head);
}
/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass03
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass03(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 03
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass03(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass03,
#if(defined( USED_CLASS_03 ) && (USED_CLASS_03 == TRUE))
		R_DLMS_OBJECTS_Class03Distributor,
#else
		NULL,
#endif /* USED_CLASS_03 */	
		p_params
	);
}

/* Declare redirect for complex data type */
OBIS_DECLARE_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectScalerUnit, scaler_unit_t);
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeScalerUnit,
	scaler_unit_t,
	R_DLMS_CLASSES_EncodeScalerUnit,
	R_DLMS_CLASSES_DecodeScalerUnit,
	R_DLMS_CLASSES_RedirectScalerUnit
);
/******************************************************************************
* Function Name : R_DLMS_CLASSES_Redirect_Att03
* Description   : Abstract class distributor function for class 03
* Arguments     : distributor_params_t * p_params - 
*				  pointer of parameter
*				  scaler_unit_t * p_attributte - 
*				  Pointer of current attribute
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Redirect_Att03(distributor_params_t * p_params, scaler_unit_t * p_attributte)
{
	scaler_unit_t * p_data;
	p_data = R_DLMS_CLASSES_RedirectScalerUnit(p_params, p_attributte);
	p_attributte = p_data;
}
/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass03
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass03(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 03
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass03(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class03_child_record_t	*p_class03_obj = (class03_child_record_t *)p_params->p_child_record;
	class03_action_data_t	action_data;

	uint8_t					*p_alloc, *p_head;
	
	p_alloc = p_head = OBIS_MALLOC_GET_POINTER(p_params);

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			case 2:	/* [class01 inherit] choice_t value */
				R_DLMS_CLASSES_DistributeAbstractClass01(p_params);
				break;

			case 3:	/* scaler_unit_t *p_scaler_unit */
				R_DLMS_CLASSES_DistributeScalerUnit(p_params, p_class03_obj->p_scaler_unit);
				break;

			default:
				break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		switch (p_params->descriptor.method.method_id)
		{
			case 1:	/* reset (data), data ::= integer (0) */

				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m1_reset, int8_t, p_alloc);
				OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
				p_params->service_params.created = TRUE;

				if (R_DLMS_CLASSES_DecodeInteger(action_data.p_m1_reset, p_params->in_data) == 0) {
					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
					break;
				}
				else {
					p_params->service_params.decode_success = TRUE;
				}

				break;

			default:
				break;
		}
	}
}

