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
* File Name    : r_dlms_class01.c
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
#include "r_dlms_class01.h"
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
* Function Name : R_DLMS_CLASSES_Class01Init
* Interface     : void R_DLMS_CLASSES_Class01Init(void)
* Description   : Initialize class 01
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class01Init(void)
{
	/* Put init code of class 01 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class01PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class01PollingProcessing(void)
* Description   : Polling process of class 01
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class01PollingProcessing(void)
{
	/* Put polling processing code of class 01 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class01AsscOpened
* Interface     : void R_DLMS_CLASSES_Class01AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 01
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class01AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 01 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class01AsscClosing
* Interface     : void R_DLMS_CLASSES_Class01AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 01
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class01AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 01 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass01
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass01(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 01
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass01(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass01,
#if(defined( USED_CLASS_01 ) && (USED_CLASS_01 == TRUE))
		R_DLMS_OBJECTS_Class01Distributor,
#else
		NULL,
#endif /* USED_CLASS_01 */	
		p_params
	);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass01
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass01(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 01
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass01(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class01_child_record_t	*p_class01_obj = (class01_child_record_t *)p_params->p_child_record;

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			case 2:	/* choice_t value */
				R_DLMS_CLASSES_DistributeChoice(p_params, &p_class01_obj->value);
				break;

			default:
				break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		/* Do nothing, shall be error */
	}
}

