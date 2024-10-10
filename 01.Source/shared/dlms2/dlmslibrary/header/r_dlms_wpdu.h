/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_wpdu.h
* Version      : 1.00
* Description  : WPDU Frame
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_WPDU_H
#define _R_DLMS_WPDU_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_udp_wrapper.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

typedef uint16_t	WPort;

typedef struct tagWpduFrame
{
	uint8_t			valid;

	uint16_t		version;
	WPort			src_wport;
	WPort			dest_wport;
	uint16_t		length;

	uint8_t			*info;
	uint16_t		info_length;

} WpduFrame;

typedef uint8_t	WpduChannel;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

EXTERN_C uint16_t R_WPDU_Encode(
	uint16_t	version,
	WPort		src_port,
	WPort		dest_port,
	uint8_t		*buffer,
	uint16_t	buffer_length
);

EXTERN_C void R_WPDU_ConfigFrameReceiverBuffer(WpduChannel wpdu_channel, uint8_t *frame_buff, uint16_t frame_buff_length);
EXTERN_C void R_WPDU_ResetFrameReceiver(WpduChannel wpdu_channel);
EXTERN_C uint8_t* R_WPDU_GetFrameReceiverBuffer(WpduChannel wpdu_channel);
EXTERN_C uint16_t R_WPDU_GetFrameReceiverBufferUsage(WpduChannel wpdu_channel);
EXTERN_C WpduFrame* R_WPDU_FrameReceiver(WpduChannel wpdu_channel, uint8_t byte);

#endif /* _R_DLMS_WPDU_H */

