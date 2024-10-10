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
* File Name    : r_dlms_class70.c
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
#include "r_dlms_class70.h"
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
* Function Name : R_DLMS_CLASSES_Class70Init
* Interface     : void R_DLMS_CLASSES_Class70Init(void)
* Description   : Initialize class 70
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class70Init(void)
{
	/* Put init code of class 70 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class70PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class70PollingProcessing(void)
* Description   : Polling process of class 70
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class70PollingProcessing(void)
{
	/* Put polling processing code of class 70 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class70AsscOpened
* Interface     : void R_DLMS_CLASSES_Class70AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 70
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class70AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 70 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class70AsscClosing
* Interface     : void R_DLMS_CLASSES_Class70AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 70
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class70AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 70 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass70
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass70(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 70
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass70(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass70,
		R_DLMS_OBJECTS_Class70Distributor,
		p_params
	);
}


/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass70
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass70(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 70
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass70(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class70_child_record_t	*p_class70_obj = (class70_child_record_t *)p_params->p_child_record;
    uint8_t                 * p_alloc, *p_head;
    class70_action_data_t    action_data;

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
            /* TODO : Put process code for each attrs of class 70 here, start from attr2 */
			case CLASS70_ATTRIBUTE_02_OUTPUT_STATE:
				R_DLMS_CLASSES_DistributeBoolean(p_params, p_class70_obj->p_output_state);
				break;
			case CLASS70_ATTRIBUTE_03_CONTROL_STATE:
				R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class70_obj->p_control_state);
				break;
			case CLASS70_ATTRIBUTE_04_CONTROL_MODE:
				R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class70_obj->p_control_mode);
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
            /* TODO : Put process code for each method of class 70 here, start from method1 */
			case CLASS70_METHOD_01_REMOTE_DISCONNECT:
            case CLASS70_METHOD_02_REMOTE_RECONNECT:
                OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_all, int8_t, p_alloc);
                OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
                p_params->service_params.created = TRUE;

                if (R_DLMS_CLASSES_DecodeInteger(action_data.p_all, p_params->in_data) == 0)
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

                break;

			default:
				break;
		}
	}
}

