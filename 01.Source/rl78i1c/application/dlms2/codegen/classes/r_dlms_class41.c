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
* File Name    : r_dlms_class41.c
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
#include "r_dlms_class41.h"
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
* Function Name : R_DLMS_CLASSES_Class41Init
* Interface     : void R_DLMS_CLASSES_Class41Init(void)
* Description   : Initialize class 41
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class41Init(void)
{
	/* Put init code of class 41 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class41PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class41PollingProcessing(void)
* Description   : Polling process of class 41
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class41PollingProcessing(void)
{
	/* Put polling processing code of class 41 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class41AsscOpened
* Interface     : void R_DLMS_CLASSES_Class41AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 41
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class41AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 41 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class41AsscClosing
* Interface     : void R_DLMS_CLASSES_Class41AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 41
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class41AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 41 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass41
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass41(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 41
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass41(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass41,
		R_DLMS_OBJECTS_Class41Distributor,
		p_params
	);
}


/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass41
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass41(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 41
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass41(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class41_child_record_t	*p_class41_obj = (class41_child_record_t *)p_params->p_child_record;

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			/* TODO : Put process code for each attrs of class 41 here, start from attr2 */
		case 2:	/* TCP-UDP Port */
			R_DLMS_CLASSES_DistributeLongUnsigned(p_params, p_class41_obj->p_tcp_udp_port);
			break;
		case 3:	/* IP reference object (logical name) */
			R_DLMS_CLASSES_DistributeFixedString(p_params, TAG_DATA_OCTET_STRING, p_class41_obj->p_ip_reference);
			break;
		case 4:	/* (TCP only) Maximum Segment Size */
			R_DLMS_CLASSES_DistributeLongUnsigned(p_params, p_class41_obj->p_mss);
			break;
		case 5:	/* Number of simultaneous connnection */
			R_DLMS_CLASSES_DistributeUnsigned(p_params, p_class41_obj->p_nb_of_sim_conn);
			break;
		case 6:	/* Inactivity timeout (second) */
			R_DLMS_CLASSES_DistributeLongUnsigned(p_params, p_class41_obj->p_inactivity_time_out);
			break;
		default:
			break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		switch (p_params->descriptor.method.method_id)
		{
			/* TODO : Put process code for each method of class 41 here, start from method1 */
		case 1:
			break;

		default:
			break;
		}
	}
}

