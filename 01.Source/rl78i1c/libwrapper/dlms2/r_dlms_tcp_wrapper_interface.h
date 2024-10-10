/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_tcp_wrapper_interface.h
* Version      : 1.00
* Description  : UDP wrapper interface
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.05.2016 
******************************************************************************/

#ifndef _R_DLMS_TCP_WRAPPER_INTERFACE_H
#define _R_DLMS_TCP_WRAPPER_INTERFACE_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_tcp_wrapper.h"

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

/* TCP Wrapper Interface APIs */
void R_TCP_WRP_UartPhyReceiveData(TcpChannel channel, uint8_t received_byte);
void R_TCP_WRP_UartPhySendEnd(TcpChannel channel);
void R_TCP_WRP_ReceiverTimeoutMilisecond(void);
uint8_t R_TCP_WRP_IsConnected(void);

/* TCP Connection Control Interface APIs */
uint8_t R_TCP_WRP_TryOpenConnection(TcpPort remote_port, IpAddressPtr remote_ip_address);
uint8_t R_TCP_WRP_TryCloseConnection(TcpPort remote_port, IpAddressPtr remote_ip_address);

#endif /* _R_DLMS_TCP_WRAPPER_INTERFACE_H */

