/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_mgmt.h
* Version      : 1.00
* Description  : DLMS Connection Manager
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 06.12.2017
******************************************************************************/

#ifndef _R_DLMS_MGMT_H
#define _R_DLMS_MGMT_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_library_config.h"
#include "r_dlms_mac.h"
#include "r_dlms_udp.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define DLMS_MGMT_CHANNEL_UNDEFINED		(0xFF)
#define DLMS_PHY_CHANNEL_START_ID		(0)
#define DLMS_HDLC_CHANNEL_START_ID		(0)
#define DLMS_UDP_CHANNEL_START_ID		(DLMS_HDLC_CHANNEL_START_ID + DLMS_MAX_HDLC_CHANNEL_SUPPORT)
#define DLMS_TCP_CHANNEL_START_ID		(DLMS_UDP_CHANNEL_START_ID + DLMS_MAX_UDP_CHANNEL_SUPPORT)
#define DLMS_MGMT_TOTAL_CHANNEL			(DLMS_MAX_HDLC_CHANNEL_SUPPORT + DLMS_MAX_UDP_CHANNEL_SUPPORT + DLMS_MAX_TCP_CHANNEL_SUPPORT)
#define DLMS_MGMT_CHANNEL_START_ID		DLMS_HDLC_CHANNEL_START_ID
#define DLMS_ASSC_CHANNEL_START_ID		(0)

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef uint8_t	MgmtChannel;

typedef enum tagChannelType
{
	CHANNEL_TYPE_NONE = 0,
	CHANNEL_TYPE_HDLC,
	CHANNEL_TYPE_UDP,
	CHANNEL_TYPE_TCP,
} ChannelType;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

EXTERN_C void R_MGMT_Init(void);
EXTERN_C void R_MGMT_PollingProcessing(void);
EXTERN_C ChannelType R_MGMT_GetChannelType(MgmtChannel channel);

#endif /* _R_DLMS_MGMT_H */

