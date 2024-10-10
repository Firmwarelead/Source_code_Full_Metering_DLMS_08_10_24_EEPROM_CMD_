/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_tcp_timeout.h
* Version      : 1.00
* Description  : Timeout for TCP layer
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_TCP_TIMEOUT_H
#define _R_DLMS_TCP_TIMEOUT_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_tcp.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum
{
	TCP_TIMEOUT_INACTIVITY = 0,
	TCP_TIMEOUT_SENDING,
	TCP_TIMEOUT_INTERFRAME
} TcpTimeoutType;

typedef EXTERN_C void (*R_TCP_TIMEOUT_HAPPEN_FUNC)(TcpChannel tcp_channel, TcpTimeoutType type);

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/*
 * Control
 */

/* Init all channels */
EXTERN_C void R_DLMS_TcpTimeoutInit(
	uint16_t inactivity,
	uint16_t sending,
	uint16_t interframe,
	R_TCP_TIMEOUT_HAPPEN_FUNC callback
);

EXTERN_C void R_DLMS_TcpTimeoutChangeSetting(
	TcpChannel tcp_channel,
	uint16_t inactivity,
	uint16_t sending,
	uint16_t interframe
);

EXTERN_C void R_DLMS_TcpTimeoutReset(TcpChannel tcp_channel, TcpTimeoutType type);
EXTERN_C void R_DLMS_TcpTimeoutStart(TcpChannel tcp_channel, TcpTimeoutType type);
EXTERN_C void R_DLMS_TcpTimeoutStop(TcpChannel tcp_channel, TcpTimeoutType type);

/* Callback of 1ms interval timer from Driver */
EXTERN_C void R_DLMS_TcpTimeoutMilisecondTimerCallback(void);

#endif /* _R_DLMS_TCP_TIMEOUT_H */

