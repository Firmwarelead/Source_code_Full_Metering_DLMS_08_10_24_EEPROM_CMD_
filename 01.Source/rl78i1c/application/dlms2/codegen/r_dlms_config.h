/******************************************************************************
  Copyright (C) 2019 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_config.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef _R_DLMS_CONFIG_H
#define _R_DLMS_CONFIG_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_library_process.h"


/* --------------------------------------------------------
 * Library Configuration
 * --------------------------------------------------------
 */
#define LIB_V2_2									(0)
#define LIB_V2_3									(1)

#define DLMS_LIB_VERSION							LIB_V2_3
/******************************************************************************
HDLC configuration
******************************************************************************/
/*
* HDLC channel 0
*/
#define HDLC_CH0_ENABLE      (TRUE)

#if defined(HDLC_CH0_ENABLE) && (HDLC_CH0_ENABLE == TRUE)
/* Shared config for all Physical & HDLC Channels */
#define		HDLC_CH0_FRAME_RX_WINDOWS_SIZE					(1)															/* Specify windows size that physical channel can handle on receive */
#define		HDLC_CH0_FRAME_TX_WINDOWS_SIZE					(1)															/* Specify windows size that physical channel can handle on transmit */

/* Physical */
#define		HDLC_PHY_CH0_BAUDRATE						PHY_BAUDRATE_9600											/* Baudrate of HDLC Channel, from PHY_BAUDRATE_300 to PHY_BAUDRATE_38400 */
#define		HDLC_PHY_CH0_USE_IEC						FALSE														/* Indicate HDLC channel use mode E or not : TRUE or FALSE */
#define		HDLC_PHY_CH0_IEC_DEV_ADDR					"REN001"													/* When mode E is used. Specify Mode E Device Address */
#define		HDLC_PHY_CH0_IEC_DEV_ID						"001"														/* When mode E is used. Specify Mode E Device Id */
#define		HDLC_PHY_CH0_IEC_DEV_MANUFACTURE			"REN"														/* When mode E is used. Specify Mode E Device Manufacture */
#define		HDLC_PHY_CH0_INTERFRAME_TIMEOUT				500															/* Specify interframe timeout, in ms */

/* Channel setting */
#define		HDLC_CH0_MAC_ADDR_SCHEME					(HdlcAddressScheme)(HDLC_ADDR_1_BYTE | HDLC_ADDR_2_BYTE | HDLC_ADDR_4_BYTE)	/* MAC Address Scheme support on meter, can be a mix of {1 byte, 2 bytes, 4 bytes} */
#define		HDLC_CH0_MAC_ADDR_UPPER						0x0001														/* Upper address (logical HDLC device address) */
#define		HDLC_CH0_MAC_ADDR_LOWER						0x0100														/* Lower address (physical HDLC device address). When 2 bytes or 4 bytes mode is selected, please set value (!= 0) to lower addr, else keep it as 0x0000. */
#define		HDLC_CH0_INACTIVITY_TIMEOUT					20000

/* Config Definition & Check */
#define		HDLC_CH0_FRAME_RX_INFO_SIZE			(DLMS_LIB_MAX_APDU_SIZE / HDLC_CH0_FRAME_RX_WINDOWS_SIZE)		/* [FIXED] please not change */
#define		HDLC_CH0_FRAME_TX_INFO_SIZE			(DLMS_LIB_MAX_APDU_SIZE / HDLC_CH0_FRAME_TX_WINDOWS_SIZE)		/* [FIXED] please not change */
#define		HDLC_CH0_FRAME_UNNUMBERED_SIZE		(DLMS_LIB_MAX_APDU_SIZE / 6)								/* [FIXED] please not change */
#if defined(HDLC_CH0_FRAME_RX_INFO_SIZE) && defined(HDLC_CH0_FRAME_RX_WINDOWS_SIZE)
#if (HDLC_CH0_FRAME_RX_INFO_SIZE * HDLC_CH0_FRAME_RX_WINDOWS_SIZE > DLMS_LIB_MAX_APDU_SIZE)
#error "HDLC_CH0_FRAME_RX_INFO_SIZE and HDLC_CH0_FRAME_RX_WINDOWS_SIZE multiply together can not larger than DLMS_LIB_MAX_APDU_SIZE"
#endif
#endif
#if defined(HDLC_CH0_FRAME_TX_INFO_SIZE) && defined(HDLC_CH0_FRAME_TX_WINDOWS_SIZE)
#if (HDLC_CH0_FRAME_TX_INFO_SIZE * HDLC_CH0_FRAME_TX_WINDOWS_SIZE > DLMS_LIB_MAX_APDU_SIZE)
#error "HDLC_CH0_FRAME_TX_INFO_SIZE and HDLC_CH0_FRAME_TX_WINDOWS_SIZE multiply together can not larger than DLMS_LIB_MAX_APDU_SIZE"
#endif
#endif

extern const HdlcChannelCfg g_hdlc_ch0;
extern const PhyChannelCfg g_phy_ch0;

#endif


/******************************************************************************
TCP configuration
******************************************************************************/

#define SUPPORT_TCP_PROFILE                            (TRUE)

#define	TCP_FRAME_INFO_SIZE							(832)
/*
 * TCP Channel 0
 */
#define TCP_PORT0_ENABLE      (TRUE)

#if defined(TCP_PORT0_ENABLE) && (TCP_PORT0_ENABLE == TRUE)
/*
 * Shared config for all TCP channels 
 */

#define		TCP_PORT0_AUTO_CONFIG_IP					(FALSE)														/* Inidicate TCP port IP6 is automatically get from TCP Wrapper */

/* Initial TCP port IP. When auto config is FALSE, IP is set to Wrapper, otherwise below IP value will be got & overwritten from TCP Wrapper */
#define		TCP_PORT0_IP								{\
                                                        0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                        0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x34	\
                                                        }
								
#define		TCP_PORT0_IP_SIZE							16
#define		TCP_PORT0_WPORT								0x0001																/* TCP WPort (logical device address) */
#define		TCP_PORT0_INACTIVITY_TIMEOUT				20000													/* Specify inactivity timeout, in ms */
#define		TCP_PORT0_INTERFRAME_TIMEOUT				200

extern TcpPortConfig g_tcp_ch0_port_config;
extern const TcpChannelCfg g_tcp_ch0;	
extern uint8_t	g_tcp_ch0_port_config_ip_addr_buffer[];
#endif


/******************************************************************************
UDP configuration
******************************************************************************/

#define SUPPORT_UDP_PROFILE                            (FALSE)

#define	UDP_FRAME_INFO_SIZE							(832)
/*
 * UDP Channel 0
 */
#define UDP_PORT0_ENABLE      (FALSE)

#if defined(UDP_PORT0_ENABLE) && (UDP_PORT0_ENABLE == TRUE)
/*
 * Shared config for all UDP channels 
 */

#define		UDP_PORT0_AUTO_CONFIG_IP					(TRUE)														/* Inidicate UDP port IP6 is automatically get from UDP Wrapper */

/* Initial UDP port IP. When auto config is FALSE, IP is set to Wrapper, otherwise below IP value will be got & overwritten from UDP Wrapper */
#define		UDP_PORT0_IP								{\
                                                        0x20,0x01,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                        0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x34	\
                                                        }
								
#define		UDP_PORT0_IP_SIZE							16
#define		UDP_PORT0_WPORT								0x0001																/* UDP WPort (logical device address) */
#define		UDP_PORT0_INACTIVITY_TIMEOUT				20000													/* Specify inactivity timeout, in ms */
#define		UDP_PORT0_INTERFRAME_TIMEOUT				200

extern UdpPortConfig g_udp_ch0_port_config;
extern const UdpChannelCfg g_udp_ch0;	
extern uint8_t	g_udp_ch0_port_config_ip_addr_buffer[];
#endif


/******************************************************************************
Association configuration
******************************************************************************/
/*
* Class 15 authentication support
*/
/* Select Class15 HLS Authentication Method: AES, MD5, SHA1 and GMAC */
#define CLASS_15_SUPPORT_AUTHENTICATION_BY_AES	    (TRUE)
#define CLASS_15_SUPPORT_AUTHENTICATION_BY_MD5	    (FALSE)
#define CLASS_15_SUPPORT_AUTHENTICATION_BY_SHA1	    (FALSE)
#define CLASS_15_SUPPORT_AUTHENTICATION_BY_GMAC     (FALSE)
#define CLASS_15_SUPPORT_AUTHENTICATION_BY_SHA256	(FALSE)

/*
* Association
*/
#define		OBIS_NUMBER_OF_ASSOCIATION					(5)

#if !defined(OBIS_NUMBER_OF_ASSOCIATION) || OBIS_NUMBER_OF_ASSOCIATION > DLMS_MAX_ASSOCIATION_SUPPORT
#error No define of number association or value > DLMS_MAX_ASSOCIATION_SUPPORT
#endif


typedef enum tag_association_id_t
{
	ASSOCIATION_ID_SAS_10H,	//Public Client
	ASSOCIATION_ID_SAS_20H,	//Meter Reader
	ASSOCIATION_ID_SAS_30H,	//Utility Setting
	ASSOCIATION_ID_SAS_40H,	//Push
	ASSOCIATION_ID_SAS_50H,	//Firmware upgrade 

} association_id_t;


extern const AssociationCfg g_assc0;
extern const AssociationCfg g_assc1;
extern const AssociationCfg g_assc2;
extern const AssociationCfg g_assc3;
extern const AssociationCfg g_assc4;


extern const AssociationCfg * gp_asscs[];
extern const uint16_t gp_asscs_size;

/*
* Security context
*/
extern SecurityContext g_assc0_security_context;
extern SecurityContext g_assc1_security_context;
extern SecurityContext g_assc2_security_context;
extern SecurityContext g_assc3_security_context;


/*
* Key string
*/
extern uint8_t g_assc_shared_master_key[];
extern uint8_t g_assc_shared_global_unicast_key[];
extern AesGcmInvocationCounters g_assc_shared_global_unicast_key_counter;
extern uint8_t g_assc_shared_global_broadcast_key[];
extern AesGcmInvocationCounters g_assc_shared_global_broadcast_key_counter;
extern uint8_t g_server_system_title[];
extern uint8_t g_assc1_secret[];
extern uint8_t g_assc2_secret[];
extern uint8_t g_Challeng_Ass2[];
extern uint8_t g_assc3_secret[];
extern uint8_t g_assc4_secret[];
extern uint8_t g_assc4_client_system_title[];


/******************************************************************************
Class version selection
******************************************************************************/
#define CLASS_07_VERSION	    (1)
#define CLASS_15_VERSION	    (1)
#define CLASS_47_VERSION	    (0)
#define CLASS_64_VERSION	    (0)


/******************************************************************************
Configuration function
******************************************************************************/
void R_DLMS_CONFIG_Init(void);
void R_DLMS_CONFIG_PollingProcessing(void);

#endif /* _R_DLMS_CONFIG_H */