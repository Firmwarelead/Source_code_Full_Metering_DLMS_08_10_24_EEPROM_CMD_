/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_udp_wrapper_interface.h
* Version      : 1.00
* Description  : UDP wrapper interface
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.05.2016 
******************************************************************************/

#ifndef _R_DLMS_UDP_WRAPPER_INTERFACE_H
#define _R_DLMS_UDP_WRAPPER_INTERFACE_H

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

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* UDP Wrapper Interface APIs */
void R_UDP_WRP_UartPhyReceiveData(UdpChannel channel, uint8_t received_byte);
void R_UDP_WRP_UartPhySendEnd(UdpChannel channel);
void R_UDP_WRP_ReceiverTimeoutMilisecond(void);
uint8_t R_UDP_WRP_IsConnected(void);
#endif /* _R_DLMS_UDP_WRAPPER_INTERFACE_H */

