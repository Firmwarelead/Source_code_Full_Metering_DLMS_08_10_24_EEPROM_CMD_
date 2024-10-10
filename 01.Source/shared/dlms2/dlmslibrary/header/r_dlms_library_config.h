/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_callback.h
* Version      : 1.00
* Description  : DLMS Library Configuration
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_LIBRARY_CONFIG_H
#define _R_DLMS_LIBRARY_CONFIG_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/

/*
* Specify APDU size support by Server
*/
#define		DLMS_LIB_MAX_APDU_SIZE			            832

/*
* Specify SNRM empty info field use default params (128, 128, 1, 1) or
* it want to connect with maximum Server capability
*/
#define     DLMS_HDLC_SNRM_INFO_EMPTY_DEFAULT_USE       (0)

/*
* Specify how many channel support on Connection Manager
*/
#define     DLMS_MAX_HDLC_CHANNEL_SUPPORT	            1
#define     DLMS_MAX_PHY_CHANNEL_SUPPORT	            1
#define		DLMS_MAX_UDP_CHANNEL_SUPPORT	            1
#define		DLMS_MAX_TCP_CHANNEL_SUPPORT	            1

/*
* Specify how many association support by Server
*/
#define     DLMS_MAX_ASSOCIATION_SUPPORT                6

/*
* Specify AARQ is always Authentication & Encryption mode (SC-AE) or not
* If DLMS_LIB_AARQ_ALWAYS_SCAE == 1 (or macro not defined), AARQ is assumed as SC-AE
* If DLMS_LIB_AARQ_ALWAYS_SCAE == 0, AARQ follows meter policy setting on security context
*/
#define		DLMS_LIB_AARQ_ALWAYS_SCAE					(0)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

#define ASSERT_TRUE_RET_ZERO(condition)		{ if ((condition)) { return 0; } }
#define ASSERT_TRUE_RET(condition)			{ if ((condition)) { return; } }

#endif /* _R_DLMS_LIBRARY_CONFIG_H */

