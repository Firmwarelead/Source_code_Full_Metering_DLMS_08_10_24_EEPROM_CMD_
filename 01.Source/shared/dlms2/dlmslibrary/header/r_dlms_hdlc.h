/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_hdlc.h
* Version      : 1.00
* Description  : HDLC Frame
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_HDLC_H
#define _R_DLMS_HDLC_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_physical.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/* Max 1 HDLC frame with no infomation */
#define		HDLC_FRAME_SIZE_NO_INFO			12
#define		HDLC_FRAME_SIZE_NO_INFO_MIN		9

/* Macro functions for address control */
#define		HDLC_EMPTY_ADDRESS(address)		{		\
	address.scheme = HDLC_ADDR_NONE;				\
	address.upper   = 0x0000;						\
	address.lower   = 0x0000;						\
}

#define		HDLC_IS_SCHEME_EXIST(src_scheme, dest_scheme)	((src_scheme & dest_scheme) != 0)

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum
{
	HDLC_ADDR_NONE = 0,
	HDLC_ADDR_1_BYTE = 1,
	HDLC_ADDR_2_BYTE = 2,
	HDLC_ADDR_4_BYTE = 4
} HdlcAddressScheme;

typedef struct
{
	HdlcAddressScheme	scheme;
	uint16_t			upper;
	uint16_t			lower;
} HdlcAddress;

typedef enum
{
	HDLC_FRAME_NONE = 0,
	HDLC_FRAME_I,
	HDLC_FRAME_RR,
	HDLC_FRAME_RNR,
	HDLC_FRAME_SNRM,
	HDLC_FRAME_DISC,
	HDLC_FRAME_UA,
	HDLC_FRAME_DM,
	HDLC_FRAME_FRMR,
	HDLC_FRAME_UI,
	
} HdlcFrameType;

typedef struct
{
	HdlcFrameType	frame_type;
	uint8_t			nr;
	uint8_t			pf;
	uint8_t			ns;
} HdlcControlByteInfo;

typedef struct
{
	uint8_t		type;
	uint8_t		segment;
	uint16_t	length;
} HdlcFrameFormat;

typedef struct
{
	uint8_t			valid;
	HdlcFrameFormat	frame_format;
	HdlcAddress 	dest_addr;
	HdlcAddress		src_addr;
	struct
	{
		uint8_t					byte;
		HdlcControlByteInfo		info;
	} control;
	uint16_t		hcs;
	uint8_t			*info;
	uint16_t		info_length;
	uint16_t		fcs;
} HdlcFrame;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

EXTERN_C uint8_t R_HDLC_IsAddrEqual(HdlcAddress src, HdlcAddress dest);

EXTERN_C uint8_t R_HDLC_MakeControlCode(
	HdlcFrameType	frame_type,
	uint8_t			nr,
	uint8_t			pf,
	uint8_t			ns
);

EXTERN_C uint16_t R_HDLC_Encode(
	uint8_t 		*buffer,
	uint8_t 		b_segment,
	HdlcAddress 	dest_addr,
	HdlcAddress 	src_addr,
	uint8_t			control,
	uint8_t			*info,
	uint16_t		info_length
);

EXTERN_C uint8_t* R_HDLC_Decode(uint8_t *buffer, uint16_t buffer_length, HdlcFrame *frame);

EXTERN_C void R_HDLC_ConfigFrameReceiverBuffer(PhyChannel phy_channel, uint8_t *frame_buff, uint16_t frame_buff_length, uint8_t *info_buff, uint16_t info_buff_length);
EXTERN_C void R_HDLC_ResetFrameReceiver(PhyChannel phy_channel);
EXTERN_C uint8_t *R_HDLC_GetFrameReceiverApduBuffer(PhyChannel phy_channel);
EXTERN_C uint16_t R_HDLC_GetFrameReceiverApduBufferUsage(PhyChannel phy_channel);
EXTERN_C uint16_t R_HDLC_GetFrameReceiverApduBufferLength(PhyChannel phy_channel);
EXTERN_C uint8_t* R_HDLC_GetFrameReceiverBuffer(PhyChannel phy_channel);
EXTERN_C uint16_t R_HDLC_GetFrameReceiverBufferUsage(PhyChannel phy_channel);
EXTERN_C uint8_t  R_HDLC_GetFrameReceiverSegmentUsage(PhyChannel phy_channel);
EXTERN_C HdlcFrame* R_HDLC_FrameReceiver(PhyChannel phy_channel, uint8_t byte);

#endif /* _R_DLMS_HDLC_H */

