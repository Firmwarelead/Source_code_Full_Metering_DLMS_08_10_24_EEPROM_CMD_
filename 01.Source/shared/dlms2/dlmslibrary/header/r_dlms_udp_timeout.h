/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_udp_timeout.h
* Version      : 1.00
* Description  : Timeout for UDP layer
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_UDP_TIMEOUT_H
#define _R_DLMS_UDP_TIMEOUT_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_udp.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum
{
	UDP_TIMEOUT_INACTIVITY = 0,
	UDP_TIMEOUT_SENDING,
	UDP_TIMEOUT_INTERFRAME
} UdpTimeoutType;

typedef EXTERN_C void (*R_UDP_TIMEOUT_HAPPEN_FUNC)(UdpChannel udp_channel, UdpTimeoutType type);

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
EXTERN_C void R_DLMS_UdpTimeoutInit(
	uint16_t inactivity,
	uint16_t sending,
	uint16_t interframe,
	R_UDP_TIMEOUT_HAPPEN_FUNC callback
);

EXTERN_C void R_DLMS_UdpTimeoutChangeSetting(
	UdpChannel udp_channel,
	uint16_t inactivity,
	uint16_t sending,
	uint16_t interframe
);

EXTERN_C void R_DLMS_UdpTimeoutReset(UdpChannel udp_channel, UdpTimeoutType type);
EXTERN_C void R_DLMS_UdpTimeoutStart(UdpChannel udp_channel, UdpTimeoutType type);
EXTERN_C void R_DLMS_UdpTimeoutStop(UdpChannel udp_channel, UdpTimeoutType type);

/* Callback of 1ms interval timer from Driver */
EXTERN_C void R_DLMS_UdpTimeoutMilisecondTimerCallback(void);

#endif /* _R_DLMS_UDP_TIMEOUT_H */

