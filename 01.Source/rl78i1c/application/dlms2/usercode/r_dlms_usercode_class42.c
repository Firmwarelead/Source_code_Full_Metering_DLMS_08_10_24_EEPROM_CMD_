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
* File Name    : r_dlms_usercode_class42.c
* Version      : 1.00
* Version OCG  : OBIS code generator 1.0.5 - Jul 09 2021
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : user code of class 42
******************************************************************************
* History : DD.MM.YYYY Version Description
* Generated date: 04/08/2021
*
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

#include <string.h>
#include <stddef.h>
#include "r_dlms_usercode_class42.h"


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
* Object name:      IPv4 for TCP0
* Object number:    00
* Object obis code: 0.0.25.1.0.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 42
* Variable name: g_dlms_ic42_obj00_att02_Dl_reference
* Object name: IPv4 for TCP0
* Attribute order: 02
* Attribute name: Dl_reference
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
This value get from TCP-UDP config,
please do not change if IP refer object change Logical name by manual
*********************************************/

const uint8_t g_dlms_ic42_obj00_Dl_reference[] = {0, 0, 0, 0, 0, 0};

/* Declare for variable of Dl_reference (class - 42, atrribute - 02)*/
const FixedString g_dlms_ic42_obj00_att02_Dl_reference  = { (uint8_t *)&g_dlms_ic42_obj00_Dl_reference, 6 };


/******************************************************************************
* Description   : Object name		: IPv4 for TCP0
*				  Object index		: 00
*				  Class				: 42
*				  Attribute order	: 3
*				  Attribute name	: IP reference
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
******************************************************************************/
/*
* This IP value is gotten from g_tcp_ch0.p_tcp_port_config->local_ip_address->p_addr r_dlm_config.c
* If you have your Ipv4, please mapping it to Ip inside config in under function
*/
/******************************************************************************
* Function Name : R_DLMS_USER_ic42_obj00_att03_ChangeIpv4
* Description   : Object name		: IPv4 for TCP0
*				  Object index		: 00
*				  Class				: 42
*				  Attribute order	: 03
*				  Attribute name	: IP_address
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic42_obj00_att03_ChangeIpv4(void)
{
	/* This function to assign your device ip to meter configuration IPv4
	* IP will be gotten ans set for g_tcp_ch0.p_tcp_port_config->local_ip_address->p_addr
	* This function is called inside init user function inside r_dlms_user.c
	* IPv4 inside configuration is pointer of buffer of uint8_t (uint8_t[4])
	* Call your IPv4 is your_ip_address
	* Case 1: your_ip_address is uint32_t 
	* => R_DLMS_Ipv4_ConverterUint32ToByteArray(&your_ip_address, g_tcp_ch0.p_tcp_port_config->local_ip_address->p_addr);
	* Case 2: your_ip_address is uint8_t[4]
	* => memcpy(g_tcp_ch0.p_tcp_port_config->local_ip_address->p_addr, &your_ip_address, 4);
	*/

	/* Start user code here */
	/* End user code here */
}


/*******************************************************************************
* Class ID: 42
* Variable name: g_dlms_ic42_obj00_att04_multicast_IP_address
* Object name: IPv4 for TCP0
* Attribute order: 04
* Attribute name: multicast_IP_address
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
 This is element definition
 ipv4::uint32_t

 This is array definition
 {
       uint8_t* p_content;
       uint16_t length;
       uint8_t* p_active;
       uint16_t alloc_size;
 }
 p_content: this is pointer of uint32_t[]
*********************************************/


/* Declare for variable of multicast_IP_address (class - 42, atrribute - 04)*/
const VariantArrayUint32_t g_dlms_ic42_obj00_att04_multicast_IP_address  = { NULL, 0, NULL, 0 };


/*******************************************************************************
* Class ID: 42
* Variable name: g_dlms_ic42_obj00_att05_option_array
* Object name: IPv4 for TCP0
* Attribute order: 05
* Attribute name: option_array
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
 This is element definition
Ip_option_data {
    uint8_t type;
    uint8_t length;
    FixedString data;
}

 This is array definition
 class42_ip_option_array_t
 {
       uint8_t* p_content;
       uint16_t length;
 }
 p_content: this is pointer of variable class42_ip_option_t[]
*********************************************/


/* Declare for variable of option_array (class - 42, atrribute - 05)*/
const class42_ip_option_array_t g_dlms_ic42_obj00_att05_option_array  = { NULL, 0 };


/*******************************************************************************
* Class ID: 42
* Variable name: g_dlms_ic42_obj00_att06_subnet_mask
* Object name: IPv4 for TCP0
* Attribute order: 06
* Attribute name: subnet_mask
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of subnet_mask (class - 42, atrribute - 06)*/
const uint32_t g_dlms_ic42_obj00_att06_subnet_mask  = 0;// {IPv4: 0.0.0.0}


/*******************************************************************************
* Class ID: 42
* Variable name: g_dlms_ic42_obj00_att07_gateway_ipv4_address
* Object name: IPv4 for TCP0
* Attribute order: 07
* Attribute name: gateway_ipv4_address
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of gateway_ipv4_address (class - 42, atrribute - 07)*/
const uint32_t g_dlms_ic42_obj00_att07_gateway_ipv4_address  = 0;// {IPv4: 0.0.0.0}


/*******************************************************************************
* Class ID: 42
* Variable name: g_dlms_ic42_obj00_att08_use_DHCP_flag
* Object name: IPv4 for TCP0
* Attribute order: 08
* Attribute name: use_DHCP_flag
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint8_t(boolean)
*********************************************/


/* Declare for variable of use_DHCP_flag (class - 42, atrribute - 08)*/
const uint8_t g_dlms_ic42_obj00_att08_use_DHCP_flag  = FALSE;


/*******************************************************************************
* Class ID: 42
* Variable name: g_dlms_ic42_obj00_att09_primary_DNS_address
* Object name: IPv4 for TCP0
* Attribute order: 09
* Attribute name: primary_DNS_address
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of primary_DNS_address (class - 42, atrribute - 09)*/
const uint32_t g_dlms_ic42_obj00_att09_primary_DNS_address  = 0;// {IPv4: 0.0.0.0}


/*******************************************************************************
* Class ID: 42
* Variable name: g_dlms_ic42_obj00_att10_secondary_DNS_address
* Object name: IPv4 for TCP0
* Attribute order: 10
* Attribute name: secondary_DNS_address
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of secondary_DNS_address (class - 42, atrribute - 10)*/
const uint32_t g_dlms_ic42_obj00_att10_secondary_DNS_address  = 0;// {IPv4: 0.0.0.0}




