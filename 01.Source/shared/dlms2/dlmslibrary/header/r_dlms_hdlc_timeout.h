/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_hdlc_timeout.h
* Version      : 1.00
* Description  : Timeout for HDLC layer
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_HDLC_TIMEOUT_H
#define _R_DLMS_HDLC_TIMEOUT_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_mac.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum
{
	HDLC_TIMEOUT_INACTIVITY = 0,
	HDLC_TIMEOUT_INTERFRAME
} HdlcTimeoutType;

typedef EXTERN_C void (*R_HDLC_INACTIVITY_TIMEOUT_HAPPEN_FUNC)(HdlcChannel hdlc_channel);
typedef EXTERN_C void (*R_HDLC_INTERFRAME_TIMEOUT_HAPPEN_FUNC)(PhyChannel phy_channel);
typedef EXTERN_C void (*R_HDLC_SENDING_TIMEOUT_HAPPEN_FUNC)(HdlcChannel hdlc_channel);

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
EXTERN_C void R_DLMS_HdlcTimeoutInit(
	uint16_t inactivity,
	uint16_t interframe,
	uint16_t sending,
	R_HDLC_INACTIVITY_TIMEOUT_HAPPEN_FUNC inactivity_callback,
	R_HDLC_INTERFRAME_TIMEOUT_HAPPEN_FUNC interframe_callback,
	R_HDLC_SENDING_TIMEOUT_HAPPEN_FUNC sending_timeout_callback
);

EXTERN_C void R_DLMS_HdlcTimeoutInactivityChangeSetting(HdlcChannel hdlc_channel, uint16_t inactivity);
EXTERN_C void R_DLMS_HdlcTimeoutInactivityReset(HdlcChannel hdlc_channel);
EXTERN_C void R_DLMS_HdlcTimeoutInactivityStart(HdlcChannel hdlc_channel);
EXTERN_C void R_DLMS_HdlcTimeoutInactivityStop(HdlcChannel hdlc_channel);

EXTERN_C void R_DLMS_HdlcTimeoutSendingChangeSetting(HdlcChannel hdlc_channel, uint16_t sending);
EXTERN_C void R_DLMS_HdlcTimeoutSendingReset(HdlcChannel hdlc_channel);
EXTERN_C void R_DLMS_HdlcTimeoutSendingStart(HdlcChannel hdlc_channel);
EXTERN_C void R_DLMS_HdlcTimeoutSendingStop(HdlcChannel hdlc_channel);

EXTERN_C void R_DLMS_HdlcTimeoutInterframeChangeSetting(PhyChannel phy_channel, uint16_t iterframe);
EXTERN_C void R_DLMS_HdlcTimeoutInterframeReset(PhyChannel phy_channel);
EXTERN_C void R_DLMS_HdlcTimeoutInterframeStart(PhyChannel phy_channel);
EXTERN_C void R_DLMS_HdlcTimeoutInterframeStop(PhyChannel phy_channel);
EXTERN_C uint16_t R_DLMS_HdlcTimeoutInterframeGetSetting(PhyChannel phy_channel);

/* Callback of 1ms interval timer from Driver */
EXTERN_C void R_DLMS_HdlcTimeoutMilisecondTimerCallback(void);

#endif /* _R_DLMS_TIMEOUT_H */

