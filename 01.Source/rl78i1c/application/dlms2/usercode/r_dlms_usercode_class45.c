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
* File Name    : r_dlms_usercode_class45.c
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

#include <string.h>
#include <stddef.h>
#include "r_dlms_usercode_class45.h"
#include "r_dlms_com_wrapper_config.h"
#include "r_dlms_format.h"

#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
#include "r_dlms_tcp_wrapper_neoway_wm620.h"
#endif


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

/* User code variable */


/* User code function */

/******************************************************************************
Private global variables and functions
******************************************************************************/
/**********************************************************************
***********************************************************************
*******************     PRIVATE GLOBAL VARIABLES       ****************
***********************************************************************
***********************************************************************
* Declare detail value to assign to Exported global variables if      *
* that is complex data type (struct or array)                         *
**********************************************************************/



/***********************************************************************************************************
* Object name:      GPRS Modem Setup
* Object number:    01
* Object obis code: 0.0.25.4.0.255
***********************************************************************************************************/

/* Please update your array size following your setting change by asigning under variable */
/* For APN */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
const uint16_t r_dlms_ic45_obj00_att02_APN_string_length = TCP_DEVICE_MAX_APN_NAME_LENGTH;
#else
const uint16_t r_dlms_ic45_obj00_att02_APN_string_length = 0;
#endif /* TCP_MODE_SELECTION of GSM modem */

/******************************************************************************
* Function Name : R_DLMS_USER_ic45_obj00_att02_get
* Description   : Object name       : GPRS Modem Setup
*                 Object index      : 00
*                 Class             : 45
*                 Attribute order   : 02
*                 Attribute name    : APN
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 OctetString * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic45_obj00_att02_get(distributor_params_t * p_params, OctetString * p_attribute_get)
{

	/*********************************************
	OctetString
	{
	    uint8_t   *p_content;
	    uint16_t   length;
	    uint16_t   alloc_size;
	}
	*********************************************/

	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign data link here */
	// uint8_t link_data_string[] =  "";
	// /* Set length for string */
	// /* !!! If change content of link_data_string, please update r_dlms_ic45_obj01_att02_APN_string_length */
	// p_attribute_get->length = r_dlms_ic45_obj01_att02_APN_string_length;
	// /* Set value for string */
	// memcpy(p_attribute_get->p_content, &link_data_string, r_dlms_ic45_obj01_att02_APN_string_length);

	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
	p_attribute_get->length = g_tcp_gsm_modem.setting.apn_name.size;
	memcpy(p_attribute_get->p_content, &g_tcp_gsm_modem.setting.apn_name.data[0], p_attribute_get->length);
#else
	p_attribute_get->length = 0;
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic45_obj00_att02_set
* Description   : Object name       : GPRS Modem Setup
*                 Object index      : 00
*                 Class             : 45
*                 Attribute order   : 02
*                 Attribute name    : APN
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 OctetString * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic45_obj00_att02_set(distributor_params_t * p_params, OctetString * p_attribute_set)
{
	/*********************************************
	OctetString
	{
	    uint8_t   *p_content;
	    uint16_t   length;
	    uint16_t   alloc_size;
	}
	*********************************************/


	/****************************************************************************************************************************************************************
	* typedef enum																																					*
	* {																																								*
	* 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	*  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	* } DataAccessResult_Value;																																		*
	* Please do these 2 code lines to report that your SET status to client for 2 cases:																			*
	* 1. SET execute successfully:																																	*
	* 	OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE); (status :VAL_DATA_ACCESS_RESULT_SUCCESS)									*
	* 	OBIS_DISTRIBUTION_SUCCESS(p_params->result);																												*
	* 2. if have any exception during executing SET																													*
	* 	OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED, FALSE);(status :VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED(example))		*
	* 	OBIS_DISTRIBUTION_FAILED(p_params->result);																													*
	* 	*Note: in this case: please refer DataAccessResult_Value enum to put your case of exception corresponding with case by case.								*
	*****************************************************************************************************************************************************************/
	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
	if (p_attribute_set->length <= r_dlms_ic45_obj01_att02_APN_string_length)
	{
		/* 
		 * Get new value from DLMS
		 */
		/* Apply new value */
		memcpy(&g_tcp_gsm_modem.setting.apn_name.data[0], p_attribute_set->p_content, p_attribute_set->length);
        g_tcp_gsm_modem.setting.apn_name.size = p_attribute_set->length;

		/* Backup to EEPROM */
        EPR_Write(STORAGE_EEPROM_DLMS_MODEM_SETTING_APN_NAME_ADDR, (uint8_t *)&g_tcp_gsm_modem.setting.apn_name, sizeof(g_tcp_gsm_modem.setting.apn_name));

		/* Trigger to reset Gsm Modem */
		R_TCP_DEVICE_RebootGsmModem();
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
#else
	/* Not mark as error and not set to any place */
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic45_obj00_att03_get
* Description   : Object name       : GPRS Modem Setup
*                 Object index      : 00
*                 Class             : 45
*                 Attribute order   : 03
*                 Attribute name    : PIN_code
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic45_obj00_att03_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
{

	/*********************************************
	Data type:uint16_t(long-unsigned)
	*********************************************/

	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	uint16_t link_data = 1234;
	/* Set value */
	*((uint16_t *)p_attribute_get) = link_data;

	/* Start user code here */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic45_obj00_att03_set
* Description   : Object name       : GPRS Modem Setup
*                 Object index      : 00
*                 Class             : 45
*                 Attribute order   : 03
*                 Attribute name    : PIN_code
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic45_obj00_att03_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
{
	/*********************************************
	Data type:uint16_t(long-unsigned)
	*********************************************/


	/****************************************************************************************************************************************************************
	* typedef enum																																					*
	* {																																								*
	* 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	*  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	* } DataAccessResult_Value;																																		*
	* Please do these 2 code lines to report that your SET status to client for 2 cases:																			*
	* 1. SET execute successfully:																																	*
	* 	OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE); (status :VAL_DATA_ACCESS_RESULT_SUCCESS)									*
	* 	OBIS_DISTRIBUTION_SUCCESS(p_params->result);																												*
	* 2. if have any exception during executing SET																													*
	* 	OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED, FALSE);(status :VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED(example))		*
	* 	OBIS_DISTRIBUTION_FAILED(p_params->result);																													*
	* 	*Note: in this case: please refer DataAccessResult_Value enum to put your case of exception corresponding with case by case.								*
	*****************************************************************************************************************************************************************/
	/* Start user code here */
	/* Do nothing, dummy only */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic45_obj00_att04_get
* Description   : Object name       : GPRS Modem Setup
*                 Object index      : 00
*                 Class             : 45
*                 Attribute order   : 04
*                 Attribute name    : quality_of_service
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 quality_of_service_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic45_obj00_att04_get(distributor_params_t * p_params, quality_of_service_t * p_attribute_get)
{

	/*********************************************
	 This is structure of quality of service, please set following  this.
	 quality_of_service_t
	 {
	       qos_element_t * p_default;
	       qos_element_t * p_requested;
	 };
	 This is structure of qos element, please set following  this.
	 qos_element_t
	 {
	       uint8_t precedence;
	       uint8_t delay;
	       uint8_t reliability;
	       uint8_t peak_throughput;
	       uint8_t mean_throughput;
	 };
	*********************************************/

	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Link data here */
	// /* Default */
	// uint8_t precedence_of_default_link = 0;
	// uint8_t delay_of_default_link = 0;
	// uint8_t reliability_of_default_link = 0;
	// uint8_t peak_throughput_of_default_link = 0;
	// uint8_t mean_throughput_of_default_link = 0;

	// /* Requested */
	// uint8_t precedence_of_requested_link = 0;
	// uint8_t delay_of_requested_link = 0;
	// uint8_t reliability_of_requested_link = 0;
	// uint8_t peak_throughput_of_requested_link = 0;
	// uint8_t mean_throughput_of_requested_link = 0;

	// /* Set data link to p_get_attribute */
	// /* Default */
	// p_attribute_get->p_default->precedence = precedence_of_default_link;
	// p_attribute_get->p_default->delay = delay_of_default_link;
	// p_attribute_get->p_default->reliability = reliability_of_default_link;
	// p_attribute_get->p_default->peak_throughput = peak_throughput_of_default_link;
	// p_attribute_get->p_default->mean_throughput = mean_throughput_of_default_link;
	// /* Requested */
	// p_attribute_get->p_requested->precedence = precedence_of_requested_link;
	// p_attribute_get->p_requested->delay = delay_of_requested_link;
	// p_attribute_get->p_requested->reliability = reliability_of_requested_link;
	// p_attribute_get->p_requested->peak_throughput = peak_throughput_of_requested_link;
	// p_attribute_get->p_requested->mean_throughput = mean_throughput_of_requested_link;
	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
	p_attribute_get->p_default->precedence = g_tcp_gsm_modem.setting.quality_of_service.min.precedence;
	p_attribute_get->p_default->delay = g_tcp_gsm_modem.setting.quality_of_service.min.delay;
	p_attribute_get->p_default->reliability = g_tcp_gsm_modem.setting.quality_of_service.min.reliability;
	p_attribute_get->p_default->peak_throughput = g_tcp_gsm_modem.setting.quality_of_service.min.peak;
	p_attribute_get->p_default->mean_throughput = g_tcp_gsm_modem.setting.quality_of_service.min.mean;
    
	p_attribute_get->p_requested->precedence = g_tcp_gsm_modem.setting.quality_of_service.req.precedence;
	p_attribute_get->p_requested->delay = g_tcp_gsm_modem.setting.quality_of_service.req.delay;
	p_attribute_get->p_requested->reliability = g_tcp_gsm_modem.setting.quality_of_service.req.reliability;
	p_attribute_get->p_requested->peak_throughput = g_tcp_gsm_modem.setting.quality_of_service.req.peak;
	p_attribute_get->p_requested->mean_throughput = g_tcp_gsm_modem.setting.quality_of_service.req.mean;
#else
    /* Default */
    memset(p_attribute_get->p_default, 0, sizeof(qos_element_t));
    memset(p_attribute_get->p_requested, 0, sizeof(qos_element_t));
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic45_obj00_att04_set
* Description   : Object name       : GPRS Modem Setup
*                 Object index      : 00
*                 Class             : 45
*                 Attribute order   : 04
*                 Attribute name    : quality_of_service
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 quality_of_service_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic45_obj00_att04_set(distributor_params_t * p_params, quality_of_service_t * p_attribute_set)
{
	/*********************************************
	 This is structure of quality of service, please set following  this.
	 quality_of_service_t
	 {
	       qos_element_t * p_default;
	       qos_element_t * p_requested;
	 };
	 This is structure of qos element, please set following  this.
	 qos_element_t
	 {
	       uint8_t precedence;
	       uint8_t delay;
	       uint8_t reliability;
	       uint8_t peak_throughput;
	       uint8_t mean_throughput;
	 };
	*********************************************/


	/****************************************************************************************************************************************************************
	* typedef enum																																					*
	* {																																								*
	* 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	* 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	* 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	*  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	* } DataAccessResult_Value;																																		*
	* Please do these 2 code lines to report that your SET status to client for 2 cases:																			*
	* 1. SET execute successfully:																																	*
	* 	OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE); (status :VAL_DATA_ACCESS_RESULT_SUCCESS)									*
	* 	OBIS_DISTRIBUTION_SUCCESS(p_params->result);																												*
	* 2. if have any exception during executing SET																													*
	* 	OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED, FALSE);(status :VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED(example))		*
	* 	OBIS_DISTRIBUTION_FAILED(p_params->result);																													*
	* 	*Note: in this case: please refer DataAccessResult_Value enum to put your case of exception corresponding with case by case.								*
	*****************************************************************************************************************************************************************/
	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
	g_tcp_gsm_modem.setting.quality_of_service.min.precedence = p_attribute_set->p_default->precedence;
	g_tcp_gsm_modem.setting.quality_of_service.min.delay = p_attribute_set->p_default->delay;
	g_tcp_gsm_modem.setting.quality_of_service.min.reliability = p_attribute_set->p_default->reliability;
	g_tcp_gsm_modem.setting.quality_of_service.min.peak = p_attribute_set->p_default->peak_throughput;
	g_tcp_gsm_modem.setting.quality_of_service.min.mean = p_attribute_set->p_default->mean_throughput;
    
	g_tcp_gsm_modem.setting.quality_of_service.req.precedence = p_attribute_set->p_requested->precedence;
	g_tcp_gsm_modem.setting.quality_of_service.req.delay = p_attribute_set->p_requested->delay;
	g_tcp_gsm_modem.setting.quality_of_service.req.reliability = p_attribute_set->p_requested->reliability;
	g_tcp_gsm_modem.setting.quality_of_service.req.peak = p_attribute_set->p_requested->peak_throughput;
	g_tcp_gsm_modem.setting.quality_of_service.req.mean = p_attribute_set->p_requested->mean_throughput;
    
	/* Trigger to reset Gsm Modem */
	R_TCP_DEVICE_RebootGsmModem();
#else
	/* Not mark as error and not set to any place */
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



