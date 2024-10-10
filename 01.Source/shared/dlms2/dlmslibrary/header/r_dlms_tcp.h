/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_tcp.h
* Version      : 1.00
* Description  : Datalink TCP sublayer of DLMS Client
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_TCP_H
#define _R_DLMS_TCP_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_library_config.h"
#include "r_dlms_wpdu.h"
#include "r_dlms_tcp_wrapper.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/* Tcp result */
typedef enum
{
	TCP_OK = 0,
	TCP_ERROR
} TcpResult;

typedef enum
{
	TCP_DISCONNECTED = 0,	/* Disconnected */
	TCP_CONNECTED,			/* Connected */
} TcpState;

/*
 * Service callback for upper layer use
 */

/* TCP DATA confirm callback */
typedef EXTERN_C void (*R_TCP_DATA_CONFIRM_FUNC)(
	TcpChannel tcp_channel,
	WPort local_wport,
	WPort remote_wport,
	TcpPort local_tcp_port,
	TcpPort remote_tcp_port,
	IpAddressPtr local_ip_address,
	IpAddressPtr remote_ip_address,
	TcpResult result
);

/* TCP DATA indication callback */
typedef EXTERN_C void (*R_TCP_DATA_INDICATION_FUNC)(
	TcpChannel tcp_channel,
	WPort local_wport,
	WPort remote_wport,
	TcpPort local_tcp_port,
	TcpPort remote_tcp_port,
	IpAddressPtr local_ip_address,
	IpAddressPtr remote_ip_address,
	uint16_t data_length,
	uint8_t *data
);

/* TCP ABORT indication callback */
typedef EXTERN_C void (*R_TCP_ABORT_INDICATION_FUNC)(
	TcpChannel tcp_channel,
	WPort local_wport,
	WPort remote_wport,
	TcpPort local_tcp_port,
	TcpPort remote_tcp_port,
	IpAddressPtr local_ip_address,
	IpAddressPtr remote_ip_address,
	uint16_t reason_length,
	uint8_t *reason
);

/* TCP session timeout callback */
typedef EXTERN_C void (*R_TCP_DATA_SESSION_TIMEOUT_FUNC)(
	TcpChannel tcp_channel,
	WPort local_wport,
	TcpPort local_tcp_port,
	IpAddressPtr local_ip_address
);

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* Control */
EXTERN_C void 		R_TCP_Init(void);					/* For all channels */
EXTERN_C void		R_TCP_PollingProcessing(void);		/* For all channels */
EXTERN_C TcpResult  R_TCP_ConfigChannel(
	TcpChannel tcp_channel,
	WPort local_wport,
	uint8_t auto_update_config,
	TcpPortConfig *p_tcp_port_cfg,
	uint8_t *tcp_receive_buff,
	uint16_t tcp_receive_buff_length,
	uint16_t inactivity_ms,
	uint16_t interframe_ms
);

EXTERN_C WPort			R_TCP_GetSrcWPort(TcpChannel tcp_channel);
EXTERN_C TcpPort		R_TCP_GetSrcTcpPort(TcpChannel tcp_channel);
EXTERN_C IpAddressPtr	R_TCP_GetSrcIpAddress(TcpChannel tcp_channel);
EXTERN_C WPort			R_TCP_GetConnectedWPort(TcpChannel tcp_channel);
EXTERN_C TcpPort		R_TCP_GetConnectedTcpPort(TcpChannel tcp_channel);
EXTERN_C IpAddressPtr	R_TCP_GetConnectedIpAddress(TcpChannel tcp_channel);
EXTERN_C uint8_t		*R_TCP_GetReceivedApduBuffer(TcpChannel tcp_channel);
EXTERN_C uint16_t		R_TCP_GetReceivedApduBufferLength(TcpChannel tcp_channel);
EXTERN_C TcpResult		R_TCP_ActivateChannel(TcpChannel tcp_channel);
EXTERN_C TcpResult		R_TCP_DeactivateChannel(TcpChannel tcp_channel);
EXTERN_C TcpState		R_TCP_GetConnectionState(TcpChannel tcp_channel);
EXTERN_C TcpResult		R_TCP_Connect(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address);
EXTERN_C TcpResult		R_TCP_Disconnect(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address);

/* Callback registration */
EXTERN_C void	R_TCP_RegisterDataConfirm		    (R_TCP_DATA_CONFIRM_FUNC func);
EXTERN_C void	R_TCP_RegisterDataIndication	    (R_TCP_DATA_INDICATION_FUNC func);
EXTERN_C void	R_TCP_RegisterDataSessionTimeout	(R_TCP_DATA_SESSION_TIMEOUT_FUNC func);
EXTERN_C void	R_TCP_RegisterAbortIndication		(R_TCP_ABORT_INDICATION_FUNC func);

/* TCP DATA service API */
EXTERN_C TcpResult	R_TCP_DATA_Request(
	TcpChannel tcp_channel,
	WPort local_wport,
	WPort remote_wport,
	TcpPort local_tcp_port,
	TcpPort remote_tcp_port,
	IpAddressPtr local_ip_address,
	IpAddressPtr remote_ip_address,
	uint16_t data_length,
	uint8_t *data
);

#endif /* _R_DLMS_TCP_H */

