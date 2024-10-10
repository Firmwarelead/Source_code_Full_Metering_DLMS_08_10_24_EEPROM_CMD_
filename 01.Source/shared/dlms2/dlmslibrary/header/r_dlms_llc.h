/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_llc.h
* Version      : 1.00
* Description  : DLMS Client LLC
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 08.06.2016 
******************************************************************************/

#ifndef _R_DLMS_LLC_H
#define _R_DLMS_LLC_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_mac.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define LLC_COSEM_CLIENT_DEST_LSAP	0xE6
#define LLC_COSEM_CLIENT_SRC_LSAP	0xE6
#define LLC_COSEM_CLIENT_QUALITY	0x00

#define LLC_COSEM_SERVER_DEST_LSAP	0xE6
#define LLC_COSEM_SERVER_SRC_LSAP	0xE7
#define LLC_COSEM_SERVER_QUALITY	0x00

/******************************************************************************
Typedef definitions
******************************************************************************/

/*
 * All DL definition is same as MAC sub-layer, just re-use
 * Only the DL-DATA service have some additional parameters
 */

 typedef enum
{
	DL_OK = 0,
	DL_ERROR,
} DlResult;

/* DL Channel */
typedef HdlcChannel DlChannel;

/* DL LSAP address */
typedef uint8_t DlAddress;

/* DL DATA indication callback */
typedef EXTERN_C void (*R_DL_DATA_INDICATION_FUNC)(
	DlChannel dl_channel,
	DlAddress dest_lsap,
	DlAddress src_lsap,
	uint8_t llc_quality,
	MacAddress dest_msap,
	MacAddress src_msap,
	MacFrameType frame_type,
	uint8_t *data,
	uint16_t data_length
);

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

EXTERN_C void		R_DL_Init(void);
EXTERN_C uint16_t	R_DL_GetNegotiatedTransmitSize(DlChannel dl_channel);
EXTERN_C void		R_DL_RegisterDataIndication(R_DL_DATA_INDICATION_FUNC func);

/* DATA service API */
EXTERN_C DlResult R_DL_DATA_Request(
	DlChannel dl_channel,
	DlAddress dest_lsap,
	DlAddress src_lsap,
	uint8_t llc_quality,
	MacAddress dest_msap,
	MacAddress src_msap,
	MacFrameType frame_type,
	uint8_t *data,
	uint16_t data_length
);

#endif /* _R_DLMS_LLC_H */

