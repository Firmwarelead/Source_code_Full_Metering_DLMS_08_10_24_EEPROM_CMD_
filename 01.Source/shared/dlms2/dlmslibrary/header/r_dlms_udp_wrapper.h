/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_udp_wrapper.h
* Version      : 1.00
* Description  : UDP wrapper layer of DLMS
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.05.2016 
******************************************************************************/

#ifndef _R_DLMS_UDP_WRAPPER_H
#define _R_DLMS_UDP_WRAPPER_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_ip.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef uint16_t	UdpPort;
typedef uint8_t		UdpChannel;

typedef struct tagUdpPortConfig
{
	UdpPort			local_udp_port;
	IpAddressPtr	local_ip_address;
} UdpPortConfig;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* UDP Device Driver APIs */
EXTERN_C void R_UDP_DEVICE_Init(UdpChannel udp_channel);
EXTERN_C void R_UDP_DEVICE_Start(UdpChannel udp_channel);
EXTERN_C void R_UDP_DEVICE_Stop(UdpChannel udp_channel);
EXTERN_C void R_UDP_DEVICE_PollingProcess(UdpChannel udp_channel);
EXTERN_C uint8_t R_UDP_DEVICE_GetConfig(UdpChannel udp_channel, UdpPortConfig* p_config);
EXTERN_C uint8_t R_UDP_DEVICE_SetConfig(UdpChannel udp_channel, UdpPortConfig* p_config);
EXTERN_C uint8_t R_UDP_DEVICE_SendData(UdpChannel udp_channel, UdpPort remote_udp_port, IpAddressPtr remote_ip_address, uint8_t *data, uint16_t length);

/* UDP Device Driver callback, register to lower layer (UART, SCI, etc.) */
EXTERN_C void	R_UDP_DeviceSendEnd(UdpChannel udp_channel);
EXTERN_C void	R_UDP_DeviceReceiveEnd(
	UdpChannel udp_channel,
	UdpPort remote_udp_port,
	IpAddressPtr remote_ip_address,
	uint8_t *rx_buffer,
	uint16_t rx_buffer_length
);
EXTERN_C void	R_UDP_DeviceReceiveError(UdpChannel udp_channel);

#endif /* _R_DLMS_PHYSICAL_WRAPPER_H */

