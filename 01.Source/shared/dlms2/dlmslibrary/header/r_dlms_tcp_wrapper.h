/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_tcp_wrapper.h
* Version      : 1.00
* Description  : TCP wrapper layer of DLMS
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.05.2016
******************************************************************************/

#ifndef _R_DLMS_TCP_WRAPPER_H
#define _R_DLMS_TCP_WRAPPER_H

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
typedef uint16_t	TcpPort;
typedef uint8_t		TcpChannel;

typedef struct tagTcpPortConfig
{
	TcpPort			local_tcp_port;
	IpAddressPtr	local_ip_address;
} TcpPortConfig;

typedef enum tagTcpDisconnectReason
{
	TCP_DISCONNECT_REMOTE_REQ = 0,	/* Remote req */
	TCP_DISCONNECT_ABORT			/* Abort */
} TcpDisconnectReason;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* TCP Device Driver APIs */
EXTERN_C void R_TCP_DEVICE_Init(TcpChannel tcp_channel);
EXTERN_C void R_TCP_DEVICE_Start(TcpChannel tcp_channel);
EXTERN_C void R_TCP_DEVICE_Stop(TcpChannel tcp_channel);
EXTERN_C void R_TCP_DEVICE_PollingProcess(TcpChannel tcp_channel);
EXTERN_C uint8_t R_TCP_DEVICE_GetConfig(TcpChannel tcp_channel, TcpPortConfig* p_config);
EXTERN_C uint8_t R_TCP_DEVICE_SetConfig(TcpChannel tcp_channel, TcpPortConfig* p_config);

/* TCP Device Service APIs */
EXTERN_C uint8_t R_TCP_DEVICE_ConnectRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address);
EXTERN_C uint8_t R_TCP_DEVICE_ConnectResponse(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t result);
EXTERN_C uint8_t R_TCP_DEVICE_DisconnectRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address);
EXTERN_C uint8_t R_TCP_DEVICE_DisconnectResponse(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t result);
EXTERN_C uint8_t R_TCP_DEVICE_DataRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t *data, uint16_t length);

/* TCP Device Service Callbacks */
EXTERN_C void	R_TCP_DEVICE_ConnectConfirm(TcpChannel tcp_channel, uint8_t result, uint8_t *reason, uint16_t reason_length);
EXTERN_C void	R_TCP_DEVICE_ConnectIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address);
EXTERN_C void	R_TCP_DEVICE_DisconnectConfirm(TcpChannel tcp_channel, uint8_t result, uint8_t *reason, uint16_t reason_length);
EXTERN_C void	R_TCP_DEVICE_DisconnectIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, TcpDisconnectReason reason);
EXTERN_C void	R_TCP_DEVICE_AbortIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t *reason, uint16_t reason_length);
EXTERN_C void	R_TCP_DEVICE_DataConfirm(TcpChannel tcp_channel, uint8_t result);
EXTERN_C void	R_TCP_DEVICE_DataIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t *rx_buffer, uint16_t rx_buffer_length);
EXTERN_C void	R_TCP_DEVICE_DataErrorIndication(TcpChannel tcp_channel);

#endif /* _R_DLMS_TCP_WRAPPER_H */

