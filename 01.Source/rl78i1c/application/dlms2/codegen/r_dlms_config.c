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
* File Name    : r_dlms_config.c
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
#include "typedef.h"					/* Standard Definition */
#include "r_dlms_library_process.h"		/* DLMS Library DLMS_LIB_V23 */
#include "r_dlms_config.h"				/* DLMS Configuration */
#include "r_dlms_classes.h"             /* DLMS Classes */

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

/* --------------------------------------------------------
 * Library Configuration
 * --------------------------------------------------------
 */

 /******************************************************************************
HDLC configuration
******************************************************************************/
/*
 * Physical Channel 0 Setup
 */

#if defined(HDLC_CH0_ENABLE) && (HDLC_CH0_ENABLE == TRUE)

uint8_t	g_phy_ch0_rx_buffer[HDLC_CH0_FRAME_RX_INFO_SIZE + 20];

#if defined(DLMS_LIB_VERSION) && (DLMS_LIB_VERSION == LIB_V2_2)
#if defined(HDLC_CH0_FRAME_RX_WINDOWS_SIZE) && HDLC_CH0_FRAME_RX_WINDOWS_SIZE > 1
uint8_t	g_phy_ch0_apdu_buffer[HDLC_CH0_FRAME_RX_INFO_SIZE * HDLC_CH0_FRAME_RX_WINDOWS_SIZE];
#endif
#else
uint8_t	g_phy_ch0_apdu_buffer[DLMS_LIB_MAX_APDU_SIZE];
#endif//defined(DLMS_LIB_VERSION) && (DLMS_LIB_VERSION == LIB_V2_2)

const PhyChannelCfg g_phy_ch0 =
{
	HDLC_PHY_CH0_BAUDRATE,
	HDLC_PHY_CH0_USE_IEC,
	{
		HDLC_PHY_CH0_IEC_DEV_ADDR,
		HDLC_PHY_CH0_IEC_DEV_ID,
		HDLC_PHY_CH0_IEC_DEV_MANUFACTURE
	},
	HDLC_PHY_CH0_INTERFRAME_TIMEOUT,
	g_phy_ch0_rx_buffer, HDLC_CH0_FRAME_RX_INFO_SIZE + 20,
#if defined(DLMS_LIB_VERSION) && (DLMS_LIB_VERSION == LIB_V2_2)
#if defined(HDLC_CH0_FRAME_RX_WINDOWS_SIZE) && HDLC_CH0_FRAME_RX_WINDOWS_SIZE > 1
	g_phy_ch0_apdu_buffer, HDLC_CH0_FRAME_RX_INFO_SIZE * HDLC_CH0_FRAME_RX_WINDOWS_SIZE
#else
	NULL, 0
#endif
#else
	g_phy_ch0_apdu_buffer, DLMS_LIB_MAX_APDU_SIZE
#endif//defined(DLMS_LIB_VERSION) && (DLMS_LIB_VERSION == LIB_V2_2)
};

/*
* HDLC Channel 0_ Setup
*/

uint8_t	g_hdlc_ch0_tx_buffer[HDLC_CH0_FRAME_TX_INFO_SIZE + 20];
uint8_t	g_hdlc_ch0_unnumbered_buffer[HDLC_CH0_FRAME_UNNUMBERED_SIZE];

const HdlcChannelCfg g_hdlc_ch0 =
{
	/* {MAC Addr Scheme, Upper, Lower} */
	{
		HDLC_CH0_MAC_ADDR_SCHEME,
		HDLC_CH0_MAC_ADDR_UPPER,
		HDLC_CH0_MAC_ADDR_LOWER
	},

	{
		HDLC_CH0_FRAME_TX_INFO_SIZE,		/* max_info_field_length_transmit */
		HDLC_CH0_FRAME_RX_INFO_SIZE,		/* max_info_field_length_receive */
		HDLC_CH0_FRAME_TX_WINDOWS_SIZE,		/* window_size_transmit */
		HDLC_CH0_FRAME_RX_WINDOWS_SIZE		/* window_size_receive */
	},
	HDLC_CH0_INACTIVITY_TIMEOUT,
	g_hdlc_ch0_tx_buffer, HDLC_CH0_FRAME_TX_INFO_SIZE + 20,
	g_hdlc_ch0_unnumbered_buffer, HDLC_CH0_FRAME_UNNUMBERED_SIZE
};
#endif


/******************************************************************************
TCP configuration
******************************************************************************/
/*
* TCP Channel 0 Setup
*/

#if defined(TCP_PORT0_ENABLE) && (TCP_PORT0_ENABLE == TRUE)
uint8_t	g_tcp_ch0_rx_buffer[TCP_FRAME_INFO_SIZE + 10];
uint8_t	g_tcp_ch0_port_config_ip_addr_buffer[TCP_PORT0_IP_SIZE] = TCP_PORT0_IP;
const IpAddress g_tcp_ch0_port_config_ip_addr = { (uint8_t *)g_tcp_ch0_port_config_ip_addr_buffer, TCP_PORT0_IP_SIZE };
TcpPortConfig g_tcp_ch0_port_config =
{
	/* DLMS TCP Port (Blue book 12.1, page 218) */
	4059,
	/* IP address */
	(IpAddressPtr)&g_tcp_ch0_port_config_ip_addr
};

const TcpChannelCfg g_tcp_ch0 = {

	/* WPort */
	TCP_PORT0_WPORT,

	/* DLMS TCP Port Config Auto Update by Wrapper? */
	TCP_PORT0_AUTO_CONFIG_IP,

	/* DLMS TCP Port Config */
	&g_tcp_ch0_port_config,

	/* RX Buffer for TCP Port */
	g_tcp_ch0_rx_buffer, TCP_FRAME_INFO_SIZE + 10,

	/* Inactivity timeout */
	TCP_PORT0_INACTIVITY_TIMEOUT,
	
	/* interframe timeout (miliseconds) */
	TCP_PORT0_INTERFRAME_TIMEOUT
};

#endif


/******************************************************************************
UDP configuration
******************************************************************************/
/*
* UDP Channel 0 Setup
*/

#if defined(UDP_PORT0_ENABLE) && (UDP_PORT0_ENABLE == TRUE)
uint8_t	g_udp_ch0_rx_buffer[UDP_FRAME_INFO_SIZE + 10];
uint8_t	g_udp_ch0_port_config_ip_addr_buffer[UDP_PORT0_IP_SIZE] = UDP_PORT0_IP;
const IpAddress g_udp_ch0_port_config_ip_addr = { (uint8_t *)g_udp_ch0_port_config_ip_addr_buffer, UDP_PORT0_IP_SIZE };
UdpPortConfig g_udp_ch0_port_config =
{
	/* DLMS UDP Port (Blue book 12.1, page 218) */
	4059,
	/* IP address */
	(IpAddressPtr)&g_udp_ch0_port_config_ip_addr
};

const UdpChannelCfg g_udp_ch0 = {

	/* WPort */
	UDP_PORT0_WPORT,

	/* DLMS UDP Port Config Auto Update by Wrapper? */
	UDP_PORT0_AUTO_CONFIG_IP,

	/* DLMS UDP Port Config */
	&g_udp_ch0_port_config,

	/* RX Buffer for UDP Port */
	g_udp_ch0_rx_buffer, UDP_FRAME_INFO_SIZE + 10,

	/* Inactivity timeout */
	UDP_PORT0_INACTIVITY_TIMEOUT,
	
	/* interframe timeout (miliseconds) */
	UDP_PORT0_INTERFRAME_TIMEOUT
};

#endif


/******************************************************************************
Association configuration
******************************************************************************/
/*
* Key string
*/
uint8_t g_assc_shared_master_key[]= "RES_MasterKeyAll";
uint8_t g_assc_shared_global_unicast_key[]= "RES_UnicastAssc0";
AesGcmInvocationCounters g_assc_shared_global_unicast_key_counter = { 0, 0 };
uint8_t g_assc_shared_global_broadcast_key[]= "RES_BroadcastKey";
AesGcmInvocationCounters g_assc_shared_global_broadcast_key_counter = { 0, 0 };
uint8_t g_server_system_title[]= "REI00045";
uint8_t g_assc1_secret[]= "ABCDEFGH";
uint8_t g_assc2_secret[]= "RENESAS_P6wRJ21F";
uint8_t g_Challeng_Ass2[]= "1ENESAS_P6wRJ21F";
uint8_t g_assc3_secret[]= "ABCDEFGH";
uint8_t g_assc4_secret[]= "RENESAS_ABCDEFGH";
uint8_t g_assc4_client_system_title[]= "1RENESAS";


/*
* Security context
*/


/* Security name - g_assc1_security_context */
SecurityContext g_assc0_security_context = {

	/* [Dynamic, this value may be changed by security_activate (data) method of Class 64]
	* For initial value, please select one of following
	*/
	/*Select 1 in 4
	--------------------------------
	SECURITY_NONE,
	SECURITY_AUTHENTICATED,
	SECURITY_ENCRYPTED,
	SECURITY_AUTHENTICATED_ENCRYPTED
	--------------------------------*/
	SECURITY_ENCRYPTED,

	/* [Static, no change]
	* Security suite, currently the library just support AES-GCM-128 security suite
	* please set value as SECURITY_AES_SUIT
	*/
	SECURITY_AES_SUIT,

	/* [Dynamic, this field value is automatically updated by COSEM Open Request (AARQ)]
	* Client System title, sent from Client to Server for AES-GCM-128 IV
	* Please keep initial value as {NULL, 0}
	*/
	{ NULL, 0 },

	/* [Static, no change]
	* Server System title, is used to send from Server to Client for AES-GCM-128 IV
	* This field shoule be a 8-chars-string
	*/
	{ (uint8_t *)g_server_system_title, 8 },

	/* [Static, no change]
	* The master key (KEK) used to encrypt the messages that exchanging of encryption (global keys) & authen keys
	*/
	{ (uint8_t *)g_assc_shared_master_key, 16 },

	/* [Dynamic, value is changed by COSEM Open Request (AARQ), TRUE is set when Client send a Dedicated key inside AARQ]
	* Indicates to use Dedicated Keys (TRUE) or Global keys (FALSE) as encryption key for AES-GCM-128
	* Initial value for this field should be FALSE
	*/
	TRUE,

	/* [Dynamic, after AA is established, TRUE is set when Client use Boardcast key for its Encryption by AES-GCM-128]
	* Indicates to use Broadcast key (TRUE) or Unicast keys (FALSE) as encryption key for AES-GCM-128
	* Initial value for this field should be FALSE
	*/
	TRUE,

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Global Unicast Key, should be 16-chars-string
	*/
	{{ (uint8_t *)g_assc_shared_global_unicast_key, 16 }, &g_assc_shared_global_unicast_key_counter},

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Global Broadcast Key, should be 16-chars-string
	*/
	{{ (uint8_t *)g_assc_shared_global_broadcast_key, 16 }, &g_assc_shared_global_broadcast_key_counter},

	/* [Dynamic, value is changed by COSEM Open Request (AARQ), this field stores the dedicated key inside AARQ]
	* Please keep initial value as {NULL, 0}
	*/
	{ { NULL, 0 }, NULL },

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Authentication Key, should be 16-chars-string
	*/
	{ (uint8_t *)g_assc_shared_global_unicast_key, 16 },

	/* [Dynamic, update by AES-GCM-128 component
	* Frame counter of AES-GCM-128
	*/
	
};

/* Security name - g_assc2_security_context */
SecurityContext g_assc1_security_context = {

	/* [Dynamic, this value may be changed by security_activate (data) method of Class 64]
	* For initial value, please select one of following
	*/
	/*Select 1 in 4
	--------------------------------
	SECURITY_NONE,
	SECURITY_AUTHENTICATED,
	SECURITY_ENCRYPTED,
	SECURITY_AUTHENTICATED_ENCRYPTED
	--------------------------------*/
	SECURITY_AUTHENTICATED_ENCRYPTED,

	/* [Static, no change]
	* Security suite, currently the library just support AES-GCM-128 security suite
	* please set value as SECURITY_AES_SUIT
	*/
	SECURITY_AES_SUIT,

	/* [Dynamic, this field value is automatically updated by COSEM Open Request (AARQ)]
	* Client System title, sent from Client to Server for AES-GCM-128 IV
	* Please keep initial value as {NULL, 0}
	*/
	{ NULL, 0 },

	/* [Static, no change]
	* Server System title, is used to send from Server to Client for AES-GCM-128 IV
	* This field shoule be a 8-chars-string
	*/
	{ (uint8_t *)g_server_system_title, 8 },

	/* [Static, no change]
	* The master key (KEK) used to encrypt the messages that exchanging of encryption (global keys) & authen keys
	*/
	{ (uint8_t *)g_assc_shared_master_key, 16 },

	/* [Dynamic, value is changed by COSEM Open Request (AARQ), TRUE is set when Client send a Dedicated key inside AARQ]
	* Indicates to use Dedicated Keys (TRUE) or Global keys (FALSE) as encryption key for AES-GCM-128
	* Initial value for this field should be FALSE
	*/
	TRUE,

	/* [Dynamic, after AA is established, TRUE is set when Client use Boardcast key for its Encryption by AES-GCM-128]
	* Indicates to use Broadcast key (TRUE) or Unicast keys (FALSE) as encryption key for AES-GCM-128
	* Initial value for this field should be FALSE
	*/
	TRUE,

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Global Unicast Key, should be 16-chars-string
	*/
	{{ (uint8_t *)g_assc_shared_global_unicast_key, 16 }, &g_assc_shared_global_unicast_key_counter},

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Global Broadcast Key, should be 16-chars-string
	*/
	{{ (uint8_t *)g_assc_shared_global_broadcast_key, 16 }, &g_assc_shared_global_broadcast_key_counter},

	/* [Dynamic, value is changed by COSEM Open Request (AARQ), this field stores the dedicated key inside AARQ]
	* Please keep initial value as {NULL, 0}
	*/
	{ { NULL, 0 }, NULL },

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Authentication Key, should be 16-chars-string
	*/
	{ (uint8_t *)g_assc_shared_global_unicast_key, 16 },

	/* [Dynamic, update by AES-GCM-128 component
	* Frame counter of AES-GCM-128
	*/
	
};

/* Security name - g_assc3_security_context */
SecurityContext g_assc2_security_context = {

	/* [Dynamic, this value may be changed by security_activate (data) method of Class 64]
	* For initial value, please select one of following
	*/
	/*Select 1 in 4
	--------------------------------
	SECURITY_NONE,
	SECURITY_AUTHENTICATED,
	SECURITY_ENCRYPTED,
	SECURITY_AUTHENTICATED_ENCRYPTED
	--------------------------------*/
	SECURITY_ENCRYPTED,

	/* [Static, no change]
	* Security suite, currently the library just support AES-GCM-128 security suite
	* please set value as SECURITY_AES_SUIT
	*/
	SECURITY_AES_SUIT,

	/* [Dynamic, this field value is automatically updated by COSEM Open Request (AARQ)]
	* Client System title, sent from Client to Server for AES-GCM-128 IV
	* Please keep initial value as {NULL, 0}
	*/
	{ (uint8_t *)g_assc4_client_system_title, 8 },

	/* [Static, no change]
	* Server System title, is used to send from Server to Client for AES-GCM-128 IV
	* This field shoule be a 8-chars-string
	*/
	{ (uint8_t *)g_server_system_title, 8 },

	/* [Static, no change]
	* The master key (KEK) used to encrypt the messages that exchanging of encryption (global keys) & authen keys
	*/
	{ (uint8_t *)g_assc_shared_master_key, 16 },

	/* [Dynamic, value is changed by COSEM Open Request (AARQ), TRUE is set when Client send a Dedicated key inside AARQ]
	* Indicates to use Dedicated Keys (TRUE) or Global keys (FALSE) as encryption key for AES-GCM-128
	* Initial value for this field should be FALSE
	*/
	FALSE,

	/* [Dynamic, after AA is established, TRUE is set when Client use Boardcast key for its Encryption by AES-GCM-128]
	* Indicates to use Broadcast key (TRUE) or Unicast keys (FALSE) as encryption key for AES-GCM-128
	* Initial value for this field should be FALSE
	*/
	FALSE,

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Global Unicast Key, should be 16-chars-string
	*/
	{{ (uint8_t *)g_assc_shared_global_unicast_key, 16 }, &g_assc_shared_global_unicast_key_counter},

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Global Broadcast Key, should be 16-chars-string
	*/
	{{ (uint8_t *)g_assc_shared_global_broadcast_key, 16 }, &g_assc_shared_global_broadcast_key_counter},

	/* [Dynamic, value is changed by COSEM Open Request (AARQ), this field stores the dedicated key inside AARQ]
	* Please keep initial value as {NULL, 0}
	*/
	{ { NULL, 0 }, NULL },

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Authentication Key, should be 16-chars-string
	*/
	{ (uint8_t *)g_assc_shared_global_unicast_key, 16 },

	/* [Dynamic, update by AES-GCM-128 component
	* Frame counter of AES-GCM-128
	*/
	
};

/* Security name - g_assc4_security_context */
SecurityContext g_assc3_security_context = {

	/* [Dynamic, this value may be changed by security_activate (data) method of Class 64]
	* For initial value, please select one of following
	*/
	/*Select 1 in 4
	--------------------------------
	SECURITY_NONE,
	SECURITY_AUTHENTICATED,
	SECURITY_ENCRYPTED,
	SECURITY_AUTHENTICATED_ENCRYPTED
	--------------------------------*/
	SECURITY_AUTHENTICATED_ENCRYPTED,

	/* [Static, no change]
	* Security suite, currently the library just support AES-GCM-128 security suite
	* please set value as SECURITY_AES_SUIT
	*/
	SECURITY_AES_SUIT,

	/* [Dynamic, this field value is automatically updated by COSEM Open Request (AARQ)]
	* Client System title, sent from Client to Server for AES-GCM-128 IV
	* Please keep initial value as {NULL, 0}
	*/
	{ NULL, 0 },

	/* [Static, no change]
	* Server System title, is used to send from Server to Client for AES-GCM-128 IV
	* This field shoule be a 8-chars-string
	*/
	{ (uint8_t *)g_server_system_title, 8 },

	/* [Static, no change]
	* The master key (KEK) used to encrypt the messages that exchanging of encryption (global keys) & authen keys
	*/
	{ (uint8_t *)g_assc_shared_master_key, 16 },

	/* [Dynamic, value is changed by COSEM Open Request (AARQ), TRUE is set when Client send a Dedicated key inside AARQ]
	* Indicates to use Dedicated Keys (TRUE) or Global keys (FALSE) as encryption key for AES-GCM-128
	* Initial value for this field should be FALSE
	*/
	TRUE,

	/* [Dynamic, after AA is established, TRUE is set when Client use Boardcast key for its Encryption by AES-GCM-128]
	* Indicates to use Broadcast key (TRUE) or Unicast keys (FALSE) as encryption key for AES-GCM-128
	* Initial value for this field should be FALSE
	*/
	TRUE,

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Global Unicast Key, should be 16-chars-string
	*/
	{{ (uint8_t *)g_assc_shared_global_unicast_key, 16 }, &g_assc_shared_global_unicast_key_counter},

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Global Broadcast Key, should be 16-chars-string
	*/
	{{ (uint8_t *)g_assc_shared_global_broadcast_key, 16 }, &g_assc_shared_global_broadcast_key_counter},

	/* [Dynamic, value is changed by COSEM Open Request (AARQ), this field stores the dedicated key inside AARQ]
	* Please keep initial value as {NULL, 0}
	*/
	{ { NULL, 0 }, NULL },

	/* [Static, changable by key_transfer (data) action of Class 64]
	* Authentication Key, should be 16-chars-string
	*/
	{ (uint8_t *)g_assc_shared_global_unicast_key, 16 },

	/* [Dynamic, update by AES-GCM-128 component
	* Frame counter of AES-GCM-128
	*/
	
};

/*
* Association config
*/

const AssociationCfg g_assc0 = {

	/* Inidicate that ASSC is pre-established or not */
	FALSE,

	/* Target Client {MacDestAddr, WPort} */
	16/* 0x10*/, 16/* 0x0010*/,

	/* App Context (Ciphering or Not) */
	/*Select 1 in 4
	--------------------------------
	CONTEXT_ID1_LN_NO_CIPHERING,
	CONTEXT_ID2_SN_NO_CIPHERING,
	CONTEXT_ID3_LN_WITH_CIPHERING,
	CONTEXT_ID4_SN_WITH_CIPHERING,
	--------------------------------*/
	CONTEXT_ID1_LN_NO_CIPHERING,

	/*
	* Security context object
	* Set NULL if no use of Ciphering
	*/
	NULL,

	/* Mechanism (authentication) */
	/* Select 1 in 8
	-------------------------------------
	MECHANISM_ID0_LOWEST_SECURITY,
	MECHANISM_ID1_LOW_SECURITY,
	MECHANISM_ID2_HIGH_SECURITY,
	MECHANISM_ID3_HIGH_SECURITY_MD5,
	MECHANISM_ID4_HIGH_SECURITY_SHA1,
	MECHANISM_ID5_HIGH_SECURITY_GMAC,
	MECHANISM_ID6_HIGH_SECURITY_SHA256,
	MECHANISM_ID7_HIGH_SECURITY_ECDSA,
	-------------------------------------*/
	MECHANISM_ID0_LOWEST_SECURITY,

	/* LLS : Secret key, HLS (encryption key) */
	{ NULL, 0 },

	/* HLS (StoC) */
	{ NULL, 0 },

	/* DLMS Version Number */
	6,

	/*
	* Conformance Bits
	*/

	/* Byte 0 */
	/* multi-choice
	-----------------------------------------
	CONFORMANCE_BYTE0_GENERAL_PROTECTION		
	CONFORMANCE_BYTE0_GENERAL_BLOCK_TRANSFER	
	CONFORMANCE_BYTE0_SN_READ					
	CONFORMANCE_BYTE0_SN_WRITE				
	CONFORMANCE_BYTE0_SN_UNCONFIRMED_WRITE	
	CONFORMANCE_BYTE0_RESERVED6				
	CONFORMANCE_BYTE0_RESERVED7				
	CONFORMANCE_BYTE0_LN_ALL					
	CONFORMANCE_BYTE0_SN_ALL
	CONFORMANCE_BYTE0_NONE					
	-----------------------------------------*/
	CONFORMANCE_BYTE0_NONE,

	/* Byte 1 */
	/* Multi-choice
	--------------------------------------------
	CONFORMANCE_BYTE1_LN_ATTR0_SET 
	CONFORMANCE_BYTE1_LN_PRIORITY_MGMT
	CONFORMANCE_BYTE1_LN_ATTR0_GET
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_GET
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_SET
	CONFORMANCE_BYTE1_LN_BLOCK_TRANSFER_ACTION
	CONFORMANCE_BYTE1_MULTI_REFERENCES
	CONFORMANCE_BYTE1_SN_INFORMATION_REPORT	
	CONFORMANCE_BYTE1_LN_ALL
	CONFORMANCE_BYTE1_SN_ALL
	CONFORMANCE_BYTE1_NONE
	--------------------------------------------*/
	CONFORMANCE_BYTE1_NONE,

	/* Byte 2 */
	/* Multi-choice
	--------------------------------------------
	CONFORMANCE_BYTE2_DATA_NOTIFICATION				
	CONFORMANCE_BYTE2_LN_ACCESS						
	CONFORMANCE_BYTE2_SN_PARAMETERIZED_ACCESS		
	CONFORMANCE_BYTE2_LN_GET 
	CONFORMANCE_BYTE2_LN_SET 
	CONFORMANCE_BYTE2_LN_SELECTIVE_ACCESS 
	CONFORMANCE_BYTE2_LN_EVENT_NOTIFICATION 
	CONFORMANCE_BYTE2_LN_ACTION 
	CONFORMANCE_BYTE2_LN_ALL						
	CONFORMANCE_BYTE2_SN_ALL						
	CONFORMANCE_BYTE2_NONE,
	--------------------------------------------*/
	CONFORMANCE_BYTE2_LN_GET |
	CONFORMANCE_BYTE2_NONE,

	/* Virtual Application Association */
	/* Dummy value -> LN: 0x0007, SN: 0xFA00 */
	0x0007
};

const AssociationCfg g_assc1 = {

	/* Inidicate that ASSC is pre-established or not */
	FALSE,

	/* Target Client {MacDestAddr, WPort} */
	32/* 0x20*/, 32/* 0x0020*/,

	/* App Context (Ciphering or Not) */
	/*Select 1 in 4
	--------------------------------
	CONTEXT_ID1_LN_NO_CIPHERING,
	CONTEXT_ID2_SN_NO_CIPHERING,
	CONTEXT_ID3_LN_WITH_CIPHERING,
	CONTEXT_ID4_SN_WITH_CIPHERING,
	--------------------------------*/
	CONTEXT_ID3_LN_WITH_CIPHERING,

	/*
	* Security context object
	* Set NULL if no use of Ciphering
	*/
	&g_assc0_security_context,

	/* Mechanism (authentication) */
	/* Select 1 in 8
	-------------------------------------
	MECHANISM_ID0_LOWEST_SECURITY,
	MECHANISM_ID1_LOW_SECURITY,
	MECHANISM_ID2_HIGH_SECURITY,
	MECHANISM_ID3_HIGH_SECURITY_MD5,
	MECHANISM_ID4_HIGH_SECURITY_SHA1,
	MECHANISM_ID5_HIGH_SECURITY_GMAC,
	MECHANISM_ID6_HIGH_SECURITY_SHA256,
	MECHANISM_ID7_HIGH_SECURITY_ECDSA,
	-------------------------------------*/
	MECHANISM_ID1_LOW_SECURITY,

	/* LLS : Secret key, HLS (encryption key) */
	{ (uint8_t *)g_assc1_secret, 8 },

	/* HLS (StoC) */
	{ NULL, 0 },

	/* DLMS Version Number */
	6,

	/*
	* Conformance Bits
	*/

	/* Byte 0 */
	/* multi-choice
	-----------------------------------------
	CONFORMANCE_BYTE0_GENERAL_PROTECTION		
	CONFORMANCE_BYTE0_GENERAL_BLOCK_TRANSFER	
	CONFORMANCE_BYTE0_SN_READ					
	CONFORMANCE_BYTE0_SN_WRITE				
	CONFORMANCE_BYTE0_SN_UNCONFIRMED_WRITE	
	CONFORMANCE_BYTE0_RESERVED6				
	CONFORMANCE_BYTE0_RESERVED7				
	CONFORMANCE_BYTE0_LN_ALL					
	CONFORMANCE_BYTE0_SN_ALL
	CONFORMANCE_BYTE0_NONE					
	-----------------------------------------*/
	CONFORMANCE_BYTE0_NONE,

	/* Byte 1 */
	/* Multi-choice
	--------------------------------------------
	CONFORMANCE_BYTE1_LN_ATTR0_SET 
	CONFORMANCE_BYTE1_LN_PRIORITY_MGMT
	CONFORMANCE_BYTE1_LN_ATTR0_GET
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_GET
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_SET
	CONFORMANCE_BYTE1_LN_BLOCK_TRANSFER_ACTION
	CONFORMANCE_BYTE1_MULTI_REFERENCES
	CONFORMANCE_BYTE1_SN_INFORMATION_REPORT	
	CONFORMANCE_BYTE1_LN_ALL
	CONFORMANCE_BYTE1_SN_ALL
	CONFORMANCE_BYTE1_NONE
	--------------------------------------------*/
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_GET |
	CONFORMANCE_BYTE1_NONE,

	/* Byte 2 */
	/* Multi-choice
	--------------------------------------------
	CONFORMANCE_BYTE2_DATA_NOTIFICATION				
	CONFORMANCE_BYTE2_LN_ACCESS						
	CONFORMANCE_BYTE2_SN_PARAMETERIZED_ACCESS		
	CONFORMANCE_BYTE2_LN_GET 
	CONFORMANCE_BYTE2_LN_SET 
	CONFORMANCE_BYTE2_LN_SELECTIVE_ACCESS 
	CONFORMANCE_BYTE2_LN_EVENT_NOTIFICATION 
	CONFORMANCE_BYTE2_LN_ACTION 
	CONFORMANCE_BYTE2_LN_ALL						
	CONFORMANCE_BYTE2_SN_ALL						
	CONFORMANCE_BYTE2_NONE,
	--------------------------------------------*/
	CONFORMANCE_BYTE2_LN_GET |
	CONFORMANCE_BYTE2_LN_SELECTIVE_ACCESS |
	CONFORMANCE_BYTE2_NONE,

	/* Virtual Application Association */
	/* Dummy value -> LN: 0x0007, SN: 0xFA00 */
	0x0007
};

const AssociationCfg g_assc2 = {

	/* Inidicate that ASSC is pre-established or not */
	FALSE,

	/* Target Client {MacDestAddr, WPort} */
	48/* 0x30*/, 48/* 0x0030*/,

	/* App Context (Ciphering or Not) */
	/*Select 1 in 4
	--------------------------------
	CONTEXT_ID1_LN_NO_CIPHERING,
	CONTEXT_ID2_SN_NO_CIPHERING,
	CONTEXT_ID3_LN_WITH_CIPHERING,
	CONTEXT_ID4_SN_WITH_CIPHERING,
	--------------------------------*/
	CONTEXT_ID3_LN_WITH_CIPHERING,

	/*
	* Security context object
	* Set NULL if no use of Ciphering
	*/
	&g_assc1_security_context,

	/* Mechanism (authentication) */
	/* Select 1 in 8
	-------------------------------------
	MECHANISM_ID0_LOWEST_SECURITY,
	MECHANISM_ID1_LOW_SECURITY,
	MECHANISM_ID2_HIGH_SECURITY,
	MECHANISM_ID3_HIGH_SECURITY_MD5,
	MECHANISM_ID4_HIGH_SECURITY_SHA1,
	MECHANISM_ID5_HIGH_SECURITY_GMAC,
	MECHANISM_ID6_HIGH_SECURITY_SHA256,
	MECHANISM_ID7_HIGH_SECURITY_ECDSA,
	-------------------------------------*/
	MECHANISM_ID2_HIGH_SECURITY,

	/* LLS : Secret key, HLS (encryption key) */
	{ (uint8_t *)g_assc2_secret, 16 },

	/* HLS (StoC) */
	{ (uint8_t *)g_Challeng_Ass2, 16 },

	/* DLMS Version Number */
	6,

	/*
	* Conformance Bits
	*/

	/* Byte 0 */
	/* multi-choice
	-----------------------------------------
	CONFORMANCE_BYTE0_GENERAL_PROTECTION		
	CONFORMANCE_BYTE0_GENERAL_BLOCK_TRANSFER	
	CONFORMANCE_BYTE0_SN_READ					
	CONFORMANCE_BYTE0_SN_WRITE				
	CONFORMANCE_BYTE0_SN_UNCONFIRMED_WRITE	
	CONFORMANCE_BYTE0_RESERVED6				
	CONFORMANCE_BYTE0_RESERVED7				
	CONFORMANCE_BYTE0_LN_ALL					
	CONFORMANCE_BYTE0_SN_ALL
	CONFORMANCE_BYTE0_NONE					
	-----------------------------------------*/
	CONFORMANCE_BYTE0_GENERAL_BLOCK_TRANSFER |
	CONFORMANCE_BYTE0_NONE,

	/* Byte 1 */
	/* Multi-choice
	--------------------------------------------
	CONFORMANCE_BYTE1_LN_ATTR0_SET 
	CONFORMANCE_BYTE1_LN_PRIORITY_MGMT
	CONFORMANCE_BYTE1_LN_ATTR0_GET
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_GET
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_SET
	CONFORMANCE_BYTE1_LN_BLOCK_TRANSFER_ACTION
	CONFORMANCE_BYTE1_MULTI_REFERENCES
	CONFORMANCE_BYTE1_SN_INFORMATION_REPORT	
	CONFORMANCE_BYTE1_LN_ALL
	CONFORMANCE_BYTE1_SN_ALL
	CONFORMANCE_BYTE1_NONE
	--------------------------------------------*/
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_GET |
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_SET |
	CONFORMANCE_BYTE1_NONE,

	/* Byte 2 */
	/* Multi-choice
	--------------------------------------------
	CONFORMANCE_BYTE2_DATA_NOTIFICATION				
	CONFORMANCE_BYTE2_LN_ACCESS						
	CONFORMANCE_BYTE2_SN_PARAMETERIZED_ACCESS		
	CONFORMANCE_BYTE2_LN_GET 
	CONFORMANCE_BYTE2_LN_SET 
	CONFORMANCE_BYTE2_LN_SELECTIVE_ACCESS 
	CONFORMANCE_BYTE2_LN_EVENT_NOTIFICATION 
	CONFORMANCE_BYTE2_LN_ACTION 
	CONFORMANCE_BYTE2_LN_ALL						
	CONFORMANCE_BYTE2_SN_ALL						
	CONFORMANCE_BYTE2_NONE,
	--------------------------------------------*/
	CONFORMANCE_BYTE2_DATA_NOTIFICATION |
	CONFORMANCE_BYTE2_LN_GET |
	CONFORMANCE_BYTE2_LN_SET |
	CONFORMANCE_BYTE2_LN_SELECTIVE_ACCESS |
	CONFORMANCE_BYTE2_LN_ACTION |
	CONFORMANCE_BYTE2_NONE,

	/* Virtual Application Association */
	/* Dummy value -> LN: 0x0007, SN: 0xFA00 */
	0x0007
};

const AssociationCfg g_assc3 = {

	/* Inidicate that ASSC is pre-established or not */
	TRUE,

	/* Target Client {MacDestAddr, WPort} */
	64/* 0x40*/, 64/* 0x0040*/,

	/* App Context (Ciphering or Not) */
	/*Select 1 in 4
	--------------------------------
	CONTEXT_ID1_LN_NO_CIPHERING,
	CONTEXT_ID2_SN_NO_CIPHERING,
	CONTEXT_ID3_LN_WITH_CIPHERING,
	CONTEXT_ID4_SN_WITH_CIPHERING,
	--------------------------------*/
	CONTEXT_ID3_LN_WITH_CIPHERING,

	/*
	* Security context object
	* Set NULL if no use of Ciphering
	*/
	&g_assc2_security_context,

	/* Mechanism (authentication) */
	/* Select 1 in 8
	-------------------------------------
	MECHANISM_ID0_LOWEST_SECURITY,
	MECHANISM_ID1_LOW_SECURITY,
	MECHANISM_ID2_HIGH_SECURITY,
	MECHANISM_ID3_HIGH_SECURITY_MD5,
	MECHANISM_ID4_HIGH_SECURITY_SHA1,
	MECHANISM_ID5_HIGH_SECURITY_GMAC,
	MECHANISM_ID6_HIGH_SECURITY_SHA256,
	MECHANISM_ID7_HIGH_SECURITY_ECDSA,
	-------------------------------------*/
	MECHANISM_ID0_LOWEST_SECURITY,

	/* LLS : Secret key, HLS (encryption key) */
	{ (uint8_t *)g_assc3_secret, 8 },

	/* HLS (StoC) */
	{ NULL, 0 },

	/* DLMS Version Number */
	6,

	/*
	* Conformance Bits
	*/

	/* Byte 0 */
	/* multi-choice
	-----------------------------------------
	CONFORMANCE_BYTE0_GENERAL_PROTECTION		
	CONFORMANCE_BYTE0_GENERAL_BLOCK_TRANSFER	
	CONFORMANCE_BYTE0_SN_READ					
	CONFORMANCE_BYTE0_SN_WRITE				
	CONFORMANCE_BYTE0_SN_UNCONFIRMED_WRITE	
	CONFORMANCE_BYTE0_RESERVED6				
	CONFORMANCE_BYTE0_RESERVED7				
	CONFORMANCE_BYTE0_LN_ALL					
	CONFORMANCE_BYTE0_SN_ALL
	CONFORMANCE_BYTE0_NONE					
	-----------------------------------------*/
	CONFORMANCE_BYTE0_GENERAL_PROTECTION |
	CONFORMANCE_BYTE0_GENERAL_BLOCK_TRANSFER |
	CONFORMANCE_BYTE0_NONE,

	/* Byte 1 */
	/* Multi-choice
	--------------------------------------------
	CONFORMANCE_BYTE1_LN_ATTR0_SET 
	CONFORMANCE_BYTE1_LN_PRIORITY_MGMT
	CONFORMANCE_BYTE1_LN_ATTR0_GET
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_GET
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_SET
	CONFORMANCE_BYTE1_LN_BLOCK_TRANSFER_ACTION
	CONFORMANCE_BYTE1_MULTI_REFERENCES
	CONFORMANCE_BYTE1_SN_INFORMATION_REPORT	
	CONFORMANCE_BYTE1_LN_ALL
	CONFORMANCE_BYTE1_SN_ALL
	CONFORMANCE_BYTE1_NONE
	--------------------------------------------*/
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_GET |
	CONFORMANCE_BYTE1_NONE,

	/* Byte 2 */
	/* Multi-choice
	--------------------------------------------
	CONFORMANCE_BYTE2_DATA_NOTIFICATION				
	CONFORMANCE_BYTE2_LN_ACCESS						
	CONFORMANCE_BYTE2_SN_PARAMETERIZED_ACCESS		
	CONFORMANCE_BYTE2_LN_GET 
	CONFORMANCE_BYTE2_LN_SET 
	CONFORMANCE_BYTE2_LN_SELECTIVE_ACCESS 
	CONFORMANCE_BYTE2_LN_EVENT_NOTIFICATION 
	CONFORMANCE_BYTE2_LN_ACTION 
	CONFORMANCE_BYTE2_LN_ALL						
	CONFORMANCE_BYTE2_SN_ALL						
	CONFORMANCE_BYTE2_NONE,
	--------------------------------------------*/
	CONFORMANCE_BYTE2_DATA_NOTIFICATION |
	CONFORMANCE_BYTE2_LN_GET |
	CONFORMANCE_BYTE2_NONE,

	/* Virtual Application Association */
	/* Dummy value -> LN: 0x0007, SN: 0xFA00 */
	0x0007
};

const AssociationCfg g_assc4 = {

	/* Inidicate that ASSC is pre-established or not */
	FALSE,

	/* Target Client {MacDestAddr, WPort} */
	80/* 0x50*/, 80/* 0x0050*/,

	/* App Context (Ciphering or Not) */
	/*Select 1 in 4
	--------------------------------
	CONTEXT_ID1_LN_NO_CIPHERING,
	CONTEXT_ID2_SN_NO_CIPHERING,
	CONTEXT_ID3_LN_WITH_CIPHERING,
	CONTEXT_ID4_SN_WITH_CIPHERING,
	--------------------------------*/
	CONTEXT_ID3_LN_WITH_CIPHERING,

	/*
	* Security context object
	* Set NULL if no use of Ciphering
	*/
	&g_assc3_security_context,

	/* Mechanism (authentication) */
	/* Select 1 in 8
	-------------------------------------
	MECHANISM_ID0_LOWEST_SECURITY,
	MECHANISM_ID1_LOW_SECURITY,
	MECHANISM_ID2_HIGH_SECURITY,
	MECHANISM_ID3_HIGH_SECURITY_MD5,
	MECHANISM_ID4_HIGH_SECURITY_SHA1,
	MECHANISM_ID5_HIGH_SECURITY_GMAC,
	MECHANISM_ID6_HIGH_SECURITY_SHA256,
	MECHANISM_ID7_HIGH_SECURITY_ECDSA,
	-------------------------------------*/
	MECHANISM_ID2_HIGH_SECURITY,

	/* LLS : Secret key, HLS (encryption key) */
	{ (uint8_t *)g_assc4_secret, 16 },

	/* HLS (StoC) */
	{ (uint8_t *)g_Challeng_Ass2, 16 },

	/* DLMS Version Number */
	6,

	/*
	* Conformance Bits
	*/

	/* Byte 0 */
	/* multi-choice
	-----------------------------------------
	CONFORMANCE_BYTE0_GENERAL_PROTECTION		
	CONFORMANCE_BYTE0_GENERAL_BLOCK_TRANSFER	
	CONFORMANCE_BYTE0_SN_READ					
	CONFORMANCE_BYTE0_SN_WRITE				
	CONFORMANCE_BYTE0_SN_UNCONFIRMED_WRITE	
	CONFORMANCE_BYTE0_RESERVED6				
	CONFORMANCE_BYTE0_RESERVED7				
	CONFORMANCE_BYTE0_LN_ALL					
	CONFORMANCE_BYTE0_SN_ALL
	CONFORMANCE_BYTE0_NONE					
	-----------------------------------------*/
	CONFORMANCE_BYTE0_NONE,

	/* Byte 1 */
	/* Multi-choice
	--------------------------------------------
	CONFORMANCE_BYTE1_LN_ATTR0_SET 
	CONFORMANCE_BYTE1_LN_PRIORITY_MGMT
	CONFORMANCE_BYTE1_LN_ATTR0_GET
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_GET
	CONFORMANCE_BYTE1_BLOCK_TRANSFER_SET
	CONFORMANCE_BYTE1_LN_BLOCK_TRANSFER_ACTION
	CONFORMANCE_BYTE1_MULTI_REFERENCES
	CONFORMANCE_BYTE1_SN_INFORMATION_REPORT	
	CONFORMANCE_BYTE1_LN_ALL
	CONFORMANCE_BYTE1_SN_ALL
	CONFORMANCE_BYTE1_NONE
	--------------------------------------------*/
	CONFORMANCE_BYTE1_NONE,

	/* Byte 2 */
	/* Multi-choice
	--------------------------------------------
	CONFORMANCE_BYTE2_DATA_NOTIFICATION				
	CONFORMANCE_BYTE2_LN_ACCESS						
	CONFORMANCE_BYTE2_SN_PARAMETERIZED_ACCESS		
	CONFORMANCE_BYTE2_LN_GET 
	CONFORMANCE_BYTE2_LN_SET 
	CONFORMANCE_BYTE2_LN_SELECTIVE_ACCESS 
	CONFORMANCE_BYTE2_LN_EVENT_NOTIFICATION 
	CONFORMANCE_BYTE2_LN_ACTION 
	CONFORMANCE_BYTE2_LN_ALL						
	CONFORMANCE_BYTE2_SN_ALL						
	CONFORMANCE_BYTE2_NONE,
	--------------------------------------------*/
	CONFORMANCE_BYTE2_LN_GET |
	CONFORMANCE_BYTE2_LN_SET |
	CONFORMANCE_BYTE2_LN_ACTION |
	CONFORMANCE_BYTE2_NONE,

	/* Virtual Application Association */
	/* Dummy value -> LN: 0x0007, SN: 0xFA00 */
	0x0007
};



const AssociationCfg * gp_asscs[OBIS_NUMBER_OF_ASSOCIATION] = 
{ 	
	&g_assc0,
	&g_assc1,
	&g_assc2,
	&g_assc3,
	&g_assc4,

};
const uint16_t gp_asscs_size = sizeof(gp_asscs) / sizeof(AssociationCfg *);

/******************************************************************************
* Function Name : R_DLMS_CONFIG_Init
* Interface     : void R_DLMS_CONFIG_Init()
* Description   : Initialize config for DLMS
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_DLMS_CONFIG_Init(void)
{
	/*
	* Init for HDLC
	*/
	/* Config 2 PHY Channel */
#if defined(HDLC_CH0_ENABLE) && (HDLC_CH0_ENABLE == TRUE)
	R_DLMS_ConfigPhyChannel(0, (PhyChannelCfg *)&g_phy_ch0);
	R_DLMS_ActivatePhyChannel(0);

	/*
	* Config & active HDLC
	*/

	/* Config 1 HDLC channel */
	R_DLMS_ConfigHdlcChannel(0, (HdlcChannelCfg *)&g_hdlc_ch0);
	R_DLMS_ActivateChannel(DLMS_HDLC_CHANNEL_START_ID + 0);
#endif 


	/*
	* Init for TCP
	*/
#if defined(TCP_PORT0_ENABLE) && (TCP_PORT0_ENABLE == TRUE)
	R_DLMS_ConfigTcpChannel(0, (TcpChannelCfg *)&g_tcp_ch0);
	R_DLMS_ActivateChannel(DLMS_TCP_CHANNEL_START_ID + 0);
#endif


	/*
	* Init for UDP
	*/
#if defined(UDP_PORT0_ENABLE) && (UDP_PORT0_ENABLE == TRUE)
	R_DLMS_ConfigUdpChannel(0, (UdpChannelCfg *)&g_udp_ch0);
	R_DLMS_ActivateChannel(DLMS_UDP_CHANNEL_START_ID + 0);
#endif


	/*
	* Init for ASSOCIATION
	*/
	R_DLMS_ConfigAssociation(ASSOCIATION_ID_SAS_10H, &g_assc0);
	R_DLMS_ConfigAssociation(ASSOCIATION_ID_SAS_20H, &g_assc1);
	R_DLMS_ConfigAssociation(ASSOCIATION_ID_SAS_30H, &g_assc2);
	R_DLMS_ConfigAssociation(ASSOCIATION_ID_SAS_40H, &g_assc3);
	R_DLMS_ConfigAssociation(ASSOCIATION_ID_SAS_50H, &g_assc4);


}

/******************************************************************************
* Function Name : R_DLMS_CONFIG_PollingProcessing
* Interface     : void R_DLMS_CONFIG_PollingProcessing()
* Description   : Polling process for config of DLMS
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_DLMS_CONFIG_PollingProcessing(void)
{
	/*
	 * Put your code here to process the config of DLMS library and OBIS in runtime
	 */
}