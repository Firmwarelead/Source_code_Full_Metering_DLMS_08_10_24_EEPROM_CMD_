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
* File Name    : r_dlms_usercode_class47.c
* Version      : 1.00
* Version OCG  : OBIS code generator 1.0.5 - Jul 09 2021
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : user code of class 47
******************************************************************************
* History : DD.MM.YYYY Version Description
* Generated date: 09/08/2021
*
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

#include <string.h>
#include <stddef.h>
#include "r_dlms_usercode_class47.h"
#include "r_dlms_com_wrapper_config.h"
#include "r_dlms_app.h"
#include "r_dlms_date_time.h"

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
* Object name:      GSM Diagnostic
* Object number:    00
* Object obis code: 0.0.25.6.0.255
***********************************************************************************************************/

/* Please update your array size following your setting change by asigning under variable */
/* For Operator */

#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
const uint16_t r_dlms_ic47_obj00_att02_Operator_string_length = TCP_DEVICE_MAX_OPERATOR_NAME_LENGTH;
#else
const uint16_t r_dlms_ic47_obj00_att02_Operator_string_length = 0;
#endif /* TCP_MODE_SELECTION of GSM modem */

/******************************************************************************
* Function Name : R_DLMS_USER_ic47_obj00_att02_get
* Description   : Object name       : GSM Diagnostic
*                 Object index      : 00
*                 Class             : 47
*                 Attribute order   : 02
*                 Attribute name    : Operator
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 OctetString * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic47_obj00_att02_get(distributor_params_t * p_params, OctetString * p_attribute_get)
{

	/*********************************************
	OctetString
	{
	    uint8_t   *p_content;
	    uint16_t   length;
	    uint16_t   alloc_size;
	}
	*********************************************/

	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
	p_attribute_get->length = g_tcp_gsm_modem.info.operator.size;
	memcpy(p_attribute_get->p_content, &g_tcp_gsm_modem.info.operator.data[0], p_attribute_get->length);
#else
	p_attribute_get->length = 0;
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;

}

/******************************************************************************
* Function Name : R_DLMS_USER_ic47_obj00_att03_get
* Description   : Object name       : GSM Diagnostic
*                 Object index      : 00
*                 Class             : 47
*                 Attribute order   : 03
*                 Attribute name    : Status
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class47_status_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic47_obj00_att03_get(distributor_params_t * p_params, class47_status_t * p_attribute_get)
{

	/*********************************************
enum tag_class47_status_t
{
	CLASS47_STATUS_NOT_REGISTERED 				= 0,
	CLASS47_STATUS_REGISTERED_HOME_NETWORK 		= 1,
	CLASS47_STATUS_NOT_REGISTERED_SEARCHING 	= 2,
	CLASS47_STATUS_REGISTRATION_DENIED 			= 3,
	CLASS47_STATUS_UNKNOWN 						= 4,
	CLASS47_STATUS_REGISTERED_ROAMING			= 5,
	// Other: (6) -> (255) reserved
}
	*********************************************/

	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	// class47_status_t link_data = CLASS47_STATUS_NOT_REGISTERED;//Please link you enum here, this is just default value.
	// *((class47_status_t *)p_attribute_get) = link_data;
	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
	*p_attribute_get = (class47_status_t)g_tcp_gsm_modem.info.network_status;
#else
	*p_attribute_get = CLASS47_STATUS_NOT_REGISTERED;
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic47_obj00_att04_get
* Description   : Object name       : GSM Diagnostic
*                 Object index      : 00
*                 Class             : 47
*                 Attribute order   : 04
*                 Attribute name    : cs_attachment
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class47_cs_attachment_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic47_obj00_att04_get(distributor_params_t * p_params, class47_cs_attachment_t * p_attribute_get)
{

	/*********************************************
enum tag_class47_cs_attachment_t
{
	CLASS47_CS_ATTACHMENT_INACTIVE		= 0,
	CLASS47_CS_ATTACHMENT_INCOMING_CALL	= 1,
	CLASS47_CS_ATTACHMENT_ACTIVE			= 2,
	// Other: (3) -> (255) reserved
}
	*********************************************/

	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	// class47_cs_attachment_t link_data = CLASS47_CS_ATTACHMENT_INACTIVE;//Please link you enum here, this is just default value.
	// *((class47_cs_attachment_t *)p_attribute_get) = link_data;
	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
	*p_attribute_get = (class47_cs_attachment_t)g_tcp_gsm_modem.info.cs_attachment;
#else
	*p_attribute_get = CLASS47_CS_ATTACHMENT_INACTIVE;
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic47_obj00_att05_get
* Description   : Object name       : GSM Diagnostic
*                 Object index      : 00
*                 Class             : 47
*                 Attribute order   : 05
*                 Attribute name    : ps_status
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class47_ps_status_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic47_obj00_att05_get(distributor_params_t * p_params, class47_ps_status_t * p_attribute_get)
{

	/*********************************************
enum tag_class47_ps_status_t
{
	CLASS47_PS_STATUS_INACTIVE		= 0,
	CLASS47_PS_STATUS_GPRS			= 1,
	CLASS47_PS_STATUS_EDGE			= 2,
	CLASS47_PS_STATUS_UMTS			= 3,
	CLASS47_PS_STATUS_HSDPA			= 4,
	CLASS47_PS_STATUS_LTE			= 5,
	CLASS47_PS_STATUS_CDMA			= 6,
	// Other: (7) -> (255) reserved
}
	*********************************************/

	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	// class47_ps_status_t link_data = CLASS47_PS_STATUS_INACTIVE;//Please link you enum here, this is just default value.
	// *((class47_ps_status_t *)p_attribute_get) = link_data;
	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
	*p_attribute_get = (class47_ps_status_t)g_tcp_gsm_modem.info.ps_status;
#else
	*p_attribute_get = CLASS47_PS_STATUS_INACTIVE;
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic47_obj00_att06_get
* Description   : Object name       : GSM Diagnostic
*                 Object index      : 00
*                 Class             : 47
*                 Attribute order   : 06
*                 Attribute name    : cell_info
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class47_cell_info_type_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic47_obj00_att06_get(distributor_params_t * p_params, class47_cell_info_type_t * p_attribute_get)
{
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */

	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)

#if CLASS_47_VERSION == 0
	p_attribute_get->cell_ID			= (uint16_t)g_tcp_gsm_modem.info.cell_info.cell_id;
#elif CLASS_47_VERSION == 1
	p_attribute_get->cell_ID			= g_tcp_gsm_modem.info.cell_info.cell_id;
#endif
	p_attribute_get->location_ID		= g_tcp_gsm_modem.info.cell_info.location_id;
	p_attribute_get->signal_quality	    = g_tcp_gsm_modem.info.cell_info.signal_quality;
	p_attribute_get->ber				= g_tcp_gsm_modem.info.cell_info.ber;
#if CLASS_47_VERSION == 1
	p_attribute_get->mcc				= g_tcp_gsm_modem.info.cell_info.mcc;
	p_attribute_get->mnc				= g_tcp_gsm_modem.info.cell_info.mnc;
	p_attribute_get->channel_number	    = g_tcp_gsm_modem.info.cell_info.channel_number;
#endif

#else
	memset(p_attribute_get, 0 , sizeof(class47_cell_info_type_t));
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/* Please update your array size following your setting change by asigning under variable */
/* For adjacent_cells */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
const uint16_t r_dlms_ic47_obj00_att07_array_length = 5;
#else
const uint16_t r_dlms_ic47_obj00_att07_array_length = 0;
#endif
/******************************************************************************
* Function Name : R_DLMS_USER_ic47_obj00_att07_get
* Description   : Object name       : GSM Diagnostic
*                 Object index      : 00
*                 Class             : 47
*                 Attribute order   : 07
*                 Attribute name    : adjacent_cells
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class47_adjacent_cells_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic47_obj00_att07_get(distributor_params_t * p_params, class47_adjacent_cells_t * p_attribute_get)
{
	/*
	 * Not implemented(default), r_dlms_ic47_obj00_att07_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic47_obj00_att07_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	 This is element definition

	 This is array definition
	 {
	       uint8_t* p_content;
	       uint16_t length;
	       uint8_t* p_active;
	       uint16_t alloc_size;
	 }
	 p_content: this is pointer of class20_day_profile_table_t[]
	*********************************************/

	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Please add at least one element of this array to get refer code */

	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
    uint16_t count;
    
    /* Get number of adjacent cells with user application */
	p_attribute_get->length = g_tcp_gsm_modem.info.adjacent_cells.length;
	for (count = 0; count < p_attribute_get->length; count++) {
#if CLASS_47_VERSION == 0
		p_attribute_get->p_content[count].cell_ID = (uint16_t)g_tcp_gsm_modem.info.adjacent_cells.items[count].cell_id;
#elif CLASS_47_VERSION == 1
		p_attribute_get->p_content[count].cell_ID = g_tcp_gsm_modem.info.adjacent_cells.items->cell_id;
#endif
		p_attribute_get->p_content[count].signal_quality = g_tcp_gsm_modem.info.adjacent_cells.items[count].signal_quality;
	}
#else
	p_attribute_get->length = 0;
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic47_obj00_att08_get
* Description   : Object name       : GSM Diagnostic
*                 Object index      : 00
*                 Class             : 47
*                 Attribute order   : 08
*                 Attribute name    : capture_time
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 date_time_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_USER_ic47_obj00_att08_get(distributor_params_t * p_params, date_time_t * p_attribute_get)
{

	/*********************************************
	date_time_t
	{
	     uint8_t year_high;                    < HI and LO of year. Interpreted as long-unsigned,   >
	     uint8_t year_low;                     < Range is 0 -> 0xFFFF-1. 0xFFFF mean not specified. >
	     uint8_t month;                        < Month. Interpreted as unsigned. 1...12             >
	     uint8_t day_of_month;                 < Day. Interpreted as unsigned. 1...31               >
	     uint8_t day_of_week;                  < Week. Interpreted as unsigned. 1...7               >
	     uint8_t hour;                         < Hour. Interpreted as unsigned. 0...23              >
	     uint8_t minute;                       < Minute. Interpreted as unsigned. 0...59            >
	     uint8_t second;                       < Hour. Interpreted as unsigned. 0...59              >
	     uint8_t hundredths;                   < Hundredths. Interpreted as unsigned. 0...99        >
	     uint8_t deviation_high;               < Interpreted as long,                               >
	     uint8_t deviation_low;                < Range -720 -> 720, in minutes of local time to GMT.>
	     uint8_t clock_status;                 < The clock status for date time value.              >
	}
	*********************************************/

	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	// date_time_t link_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	// /* Set value */
	// *((date_time_t *)p_attribute_get) = link_data;

	/* Start user code here */
#if (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)
    if(R_DLMS_RTC_Convert_DriverRTC2DateTime(p_attribute_get, &g_tcp_gsm_modem.info.capture_time) == RLT_SUCCESS)
	{
        /* Successful operation */
	}
    else
	{
		return VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT;
	}
#else
	date_time_t link_data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	/* Set value */
	*((date_time_t *)p_attribute_get) = link_data;
#endif /* TCP_MODE_SELECTION of GSM modem */
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



