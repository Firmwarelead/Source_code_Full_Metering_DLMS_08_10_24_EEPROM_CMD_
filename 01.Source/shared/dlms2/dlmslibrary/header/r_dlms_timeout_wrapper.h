/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_timeout_wrapper.h
* Version      : 1.00
* Description  : Timeout wrapper for HDLC layer
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_TIMEOUT_WRAPPER_H
#define _R_DLMS_TIMEOUT_WRAPPER_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* Timer device driver APIs */
EXTERN_C void TIMEOUT_DEVICE_Init(void);	
EXTERN_C void TIMEOUT_DEVICE_Start(void);	
EXTERN_C void TIMEOUT_DEVICE_Stop(void);
EXTERN_C void TIMEOUT_DEVICE_WdtRestart(void);

/* Callback of 1ms interval timer from Driver */
EXTERN_C void R_DLMS_HdlcTimeoutMilisecondTimerCallback(void);
EXTERN_C void R_DLMS_UdpTimeoutMilisecondTimerCallback(void);
EXTERN_C void R_DLMS_TcpTimeoutMilisecondTimerCallback(void);

#endif /* _R_DLMS_TIMEOUT_WRAPPER_H */

