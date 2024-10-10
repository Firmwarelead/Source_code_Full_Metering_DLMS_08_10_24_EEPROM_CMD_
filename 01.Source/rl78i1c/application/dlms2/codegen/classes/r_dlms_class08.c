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
* File Name    : r_dlms_class08.c
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
#include "r_dlms_class08.h"
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


OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass18PresetAdjustingTime, class08_preset_adjusting_time_t)
{
    OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
    OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

    OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
    {
        OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->preset_time				, sizeof(date_time_t), TAG_DATA_OCTET_STRING, in_data);
        OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->validity_interval_start	, sizeof(date_time_t), TAG_DATA_OCTET_STRING, in_data);
        OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->validity_interval_end	, sizeof(date_time_t), TAG_DATA_OCTET_STRING, in_data);
    }

    OBIS_TYPE_DECODER_FUNC_RET();
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class08Init
* Interface     : void R_DLMS_CLASSES_Class08Init(void)
* Description   : Initialize class 08
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class08Init(void)
{
	/* Put init code of class 08 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class08PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class08PollingProcessing(void)
* Description   : Polling process of class 08
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class08PollingProcessing(void)
{
	/* Put polling processing code of class 08 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class08AsscOpened
* Interface     : void R_DLMS_CLASSES_Class08AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 08
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class08AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 08 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class08AsscClosing
* Interface     : void R_DLMS_CLASSES_Class08AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 08
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class08AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 08 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass08
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass08(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 08
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass08(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass08,
		R_DLMS_OBJECTS_Class08Distributor,
		p_params
	);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass08
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass08(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 08
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass08(distributor_params_t *p_params)
{
	class08_child_record_t	*p_class08_obj = (class08_child_record_t *)p_params->p_child_record;
    uint8_t                 * p_alloc, *p_head;
    class08_action_data_t   action_data;
    
    /* Get current malloc position */
    p_alloc = p_head = OBIS_MALLOC_GET_POINTER(p_params);

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
            /* TODO : Put process code for each attrs of class 08 here, start from attr2 */
			case CLASS08_ATTRIBUTE_02_TIME:
				R_DLMS_CLASSES_DistributeDateTimeAsOctetString(p_params, p_class08_obj->p_time);
				break;
            case CLASS08_ATTRIBUTE_03_TIME_ZONE:
				R_DLMS_CLASSES_DistributeLong(p_params, p_class08_obj->p_time_zone);
				break;
            case CLASS08_ATTRIBUTE_04_STATUS:
				R_DLMS_CLASSES_DistributeUnsigned(p_params, p_class08_obj->p_status);
				break;
            case CLASS08_ATTRIBUTE_05_DAYLIGHT_SAVINGS_BEGIN:
				R_DLMS_CLASSES_DistributeDateTimeAsOctetString(p_params, p_class08_obj->p_daylight_savings_begin);
				break;
            case CLASS08_ATTRIBUTE_06_DAYLIGHT_SAVINGS_END:
				R_DLMS_CLASSES_DistributeDateTimeAsOctetString(p_params, p_class08_obj->p_daylight_savings_end);
				break;
            case CLASS08_ATTRIBUTE_07_DAYLIGHT_SAVINGS_DEVIATION:
				R_DLMS_CLASSES_DistributeInteger(p_params, p_class08_obj->p_daylight_savings_deviation);
				break;
            case CLASS08_ATTRIBUTE_08_DAYLIGHT_SAVINGS_ENABLED:
				R_DLMS_CLASSES_DistributeBoolean(p_params, p_class08_obj->p_daylight_savings_enabled);
				break;
            case CLASS08_ATTRIBUTE_09_CLOCK_BASE:
				R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class08_obj->p_clock_base);
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
            /* TODO : Put process code for each method of class 08 here, start from method1 */
			case CLASS08_METHOD_01_ADJUST_TO_QUARTER:
            case CLASS08_METHOD_02_ADJUST_TO_MEASURING_PERIOD:
            case CLASS08_METHOD_03_ADJUST_TO_MINUTE:
            case CLASS08_METHOD_04_ADJUST_TO_PRESET_TIME:
                OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_all, int8_t, p_alloc);
                OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
                p_params->service_params.created = TRUE;

                if ( R_DLMS_CLASSES_DecodeInteger(action_data.p_all, p_params->in_data) == 0 )
                {
                    p_params->service_params.decode_success = FALSE;
                    OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
                    OBIS_DISTRIBUTION_FAILED(p_params->result);
                }
                break;
            case CLASS08_METHOD_05_PRESET_ADJUSTING_TIME:
                OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m5_preset_adjusting_time, class08_preset_adjusting_time_t, p_alloc);
                OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
                p_params->service_params.created = TRUE;

                if (R_DLMS_CLASSES_DecodeClass18PresetAdjustingTime(action_data.p_m5_preset_adjusting_time, p_params->in_data) == 0)
                {
                    p_params->service_params.decode_success = FALSE;
                    OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
                    OBIS_DISTRIBUTION_FAILED(p_params->result);
                }
                break;
            case CLASS08_METHOD_06_SHIFT_TIME:
                OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m6_shift_time, int16_t, p_alloc);
                OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
                p_params->service_params.created = TRUE;

                if ( R_DLMS_CLASSES_DecodeLong(action_data.p_m6_shift_time, p_params->in_data) == 0 )
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


