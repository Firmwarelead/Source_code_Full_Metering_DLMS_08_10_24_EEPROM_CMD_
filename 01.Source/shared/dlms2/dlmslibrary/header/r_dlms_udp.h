/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_mac.h
* Version      : 1.00
* Description  : Datalink UDP sublayer of DLMS Client
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_UDP_H
#define _R_DLMS_UDP_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_library_config.h"
#include "r_dlms_wpdu.h"
#include "r_dlms_udp_wrapper.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/* Udp result */
typedef enum
{
	UDP_OK = 0,
	UDP_ERROR
} UdpResult;

/*
 * Service callback for upper layer use
 */

/* UDP DATA confirm callback */
typedef EXTERN_C void (*R_UDP_DATA_CONFIRM_FUNC)(
	UdpChannel udp_channel,
	WPort local_wport,
	WPort remote_wport,
	UdpPort local_udp_port,
	UdpPort remote_udp_port,
	IpAddressPtr local_ip_address,
	IpAddressPtr remote_ip_address,
	UdpResult result
);

/* UDP DATA confirm callback */
typedef EXTERN_C void (*R_UDP_DATA_INDICATION_FUNC)(
	UdpChannel udp_channel,
	WPort local_wport,
	WPort remote_wport,
	UdpPort local_udp_port,
	UdpPort remote_udp_port,
	IpAddressPtr local_ip_address,
	IpAddressPtr remote_ip_address,
	uint16_t data_length,
	uint8_t *data
);

/* UDP session timeout callback */
typedef EXTERN_C void (*R_UDP_DATA_SESSION_TIMEOUT_FUNC)(
	UdpChannel udp_channel,
	WPort local_wport,
	UdpPort local_udp_port,
	IpAddressPtr local_ip_address
);

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* Control */
EXTERN_C void 		R_UDP_Init(void);					/* For all channels */
EXTERN_C void		R_UDP_PollingProcessing(void);		/* For all channels */
EXTERN_C UdpResult  R_UDP_ConfigChannel(
	UdpChannel udp_channel,
	WPort local_wport,
	uint8_t auto_update_config,
	UdpPortConfig *p_udp_port_cfg,
	uint8_t *udp_receive_buff,
	uint16_t udp_receive_buff_length,
	uint16_t inactivity_ms,
	uint16_t interframe_ms
);

EXTERN_C WPort			R_UDP_GetSrcWPort(UdpChannel udp_channel);
EXTERN_C UdpPort		R_UDP_GetSrcUdpPort(UdpChannel udp_channel);
EXTERN_C IpAddressPtr	R_UDP_GetSrcIpAddress(UdpChannel udp_channel);
EXTERN_C WPort			R_UDP_GetConnectedWPort(UdpChannel udp_channel);
EXTERN_C UdpPort		R_UDP_GetConnectedUdpPort(UdpChannel udp_channel);
EXTERN_C IpAddressPtr	R_UDP_GetConnectedIpAddress(UdpChannel udp_channel);
EXTERN_C uint8_t		*R_UDP_GetReceivedApduBuffer(UdpChannel udp_channel);
EXTERN_C uint16_t		R_UDP_GetReceivedApduBufferLength(UdpChannel udp_channel);
EXTERN_C UdpResult		R_UDP_ActivateChannel(UdpChannel udp_channel);
EXTERN_C UdpResult		R_UDP_DeactivateChannel(UdpChannel udp_channel);

/* Callback registration */
EXTERN_C void	R_UDP_RegisterDataConfirm		    (R_UDP_DATA_CONFIRM_FUNC func);
EXTERN_C void	R_UDP_RegisterDataIndication	    (R_UDP_DATA_INDICATION_FUNC func);
EXTERN_C void	R_UDP_RegisterDataSessionTimeout	(R_UDP_DATA_SESSION_TIMEOUT_FUNC func);

/* UDP DATA service API */
EXTERN_C UdpResult	R_UDP_DATA_Request(
	UdpChannel udp_channel,
	WPort local_wport,
	WPort remote_wport,
	UdpPort local_udp_port,
	UdpPort remote_udp_port,
	IpAddressPtr local_ip_address,
	IpAddressPtr remote_ip_address,
	uint16_t data_length,
	uint8_t *data
);

#endif /* _R_DLMS_UDP_H */

