/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this
* software and to discontinue the availability of this software.
* By using this software, you agree to the additional terms and
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************
* File Name    : r_dlms_tcp_wrapper_dummy.c
* Version      : 1.00
* Device(s)    : R5F564MLCxDC
* Tool-Chain   : CCRX
* H/W Platform : RX64M RSK+
* Description  : TCP wrapper layer of DLMS
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.05.2016
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"

#include "typedef.h"
#include "wrp_app_uart.h"
#include "r_dlms_config.h"
#include "r_dlms_tcp_wrapper.h"
#include "r_dlms_tcp_wrapper_interface.h"
#include "r_dlms_com_wrapper_config.h"

#if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == FALSE)

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
const uint8_t   g_tcp_local_ip_addr_buffer[] = { 192, 168, 0, 20 };
const IpAddress g_tcp_local_ip_addr = { (uint8_t *)g_tcp_local_ip_addr_buffer, 4 };
const uint8_t   g_tcp_remote_ip_addr_buffer[] = { 192, 168, 0, 10 };
const IpAddress g_tcp_remote_ip_addr = { (uint8_t *)g_tcp_remote_ip_addr_buffer, 4 };

/******************************************************************************
* Function Name : R_TCP_DEVICE_Init
* Interface     : void R_TCP_DEVICE_Init(void)
* Description   : Initial TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_Init(TcpChannel tcp_channel)
{
    
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_Start
* Interface     : void R_TCP_DEVICE_Start(void)
* Description   : Start TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_Start(TcpChannel tcp_channel)
{
	if (tcp_channel == 0) {
#if defined(R_UART0_USE) && (R_UART0_USE == TRUE)
		WRP_UART0_Start();
#endif
		R_TCP_DEVICE_ConnectIndication(tcp_channel, 4059, (IpAddressPtr)&g_tcp_remote_ip_addr);
		R_TCP_DEVICE_ConnectRequest(tcp_channel, 4059, (IpAddressPtr)&g_tcp_remote_ip_addr);
	}
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_Stop
* Interface     : void R_TCP_DEVICE_Stop(void)
* Description   : Stop TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_Stop(TcpChannel tcp_channel)
{
	if (tcp_channel == 0) {
#if defined(R_UART0_USE) && (R_UART0_USE == TRUE)
		WRP_UART0_Stop();
#endif
		R_TCP_DEVICE_DisconnectIndication(tcp_channel, 4059, (IpAddressPtr)&g_tcp_remote_ip_addr, TCP_DISCONNECT_REMOTE_REQ);
		R_TCP_DEVICE_DisconnectRequest(tcp_channel, 4059, (IpAddressPtr)&g_tcp_remote_ip_addr);
	}
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_PollingProcess
* Interface     : void R_TCP_DEVICE_PollingProcess(void)
* Description   : Polling process of TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_PollingProcess(TcpChannel tcp_channel)
{
    
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_GetConfig
* Interface     : uint8_t R_TCP_DEVICE_GetConfig(
*               :     TcpChannel tcp_channel ,
*               :     TcpPortConfig* p_config,
*               : );
* Description   : Get config of TCP device (Port number, IP address), put to p_config
* Arguments     : TcpChannel tcp_channel :
*               : TcpPortConfig* p_config:
* Function Calls:
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_GetConfig(TcpChannel tcp_channel, TcpPortConfig* p_config)
{
	return FALSE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_SetConfig
* Interface     : uint8_t R_TCP_DEVICE_SetConfig(
*               :     TcpChannel tcp_channel ,
*               :     TcpPortConfig* p_config,
*               : );
* Description   : Set config of TCP device (Port number, IP address), read from p_config
* Arguments     : TcpChannel tcp_channel :
*               : TcpPortConfig* p_config:
* Function Calls:
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_SetConfig(TcpChannel tcp_channel, TcpPortConfig* p_config)
{
	return FALSE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_ConnectRequest
* Interface     : uint8_t R_TCP_DEVICE_ConnectRequest(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               : );
* Description   : Request a TCP connection to a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_ConnectRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address)
{
	/* TODO: Dummy to get library run */
	R_TCP_DEVICE_ConnectConfirm(tcp_channel, TRUE, NULL, 0);
    return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_ConnectResponse
* Interface     : uint8_t R_TCP_DEVICE_ConnectResponse(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               :     uint8_t result                ,
*               : );
* Description   : Response to a TCP connection from a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
*               : uint8_t result                : Connection req from remote station is accepted (TRUE) or reject (FALSE)
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_ConnectResponse(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t result)
{
	/* TODO: Dummy to get library run */
	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_DisconnectRequest
* Interface     : uint8_t R_TCP_DEVICE_DisconnectRequest(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               : );
* Description   : Request a TCP disconnect signal to remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DisconnectRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address)
{
	/* TODO: Dummy to get library run */
	R_TCP_DEVICE_DisconnectConfirm(tcp_channel, TRUE, NULL, 0);
	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_DisconnectResponse
* Interface     : uint8_t R_TCP_DEVICE_DisconnectResponse(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               :     uint8_t result                ,
*               : );
* Description   : Response to a TCP disconnection from a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
*               : uint8_t result                : Disconnection req from remote station is accepted (TRUE) or reject (FALSE)
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DisconnectResponse(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t result)
{
	/* TODO: Dummy to get library run */
	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_DataRequest
* Interface     : uint8_t R_TCP_DEVICE_DataRequest(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               :     uint8_t * data                ,
*               :     uint16_t length               ,
*               : );
* Description   : Request to send data to a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
*               : uint8_t * data                : Input data buffer pointer
*               : uint16_t length               : Input data length
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DataRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t *data, uint16_t length)
{
	if (tcp_channel == 0) {
	}

	return TRUE;
}

/*
 * Usage of TCP device service callbacks
 */

 /*
  * R_TCP_DEVICE_ConnectConfirm(TcpChannel tcp_channel, uint8_t result, uint8_t *reason, uint16_t reason_length);
  * ---
  * R_TCP_DEVICE_ConnectConfirm() is used to confirm about the last R_TCP_DEVICE_ConnectRequest() call,
  * Normally it is called once remote station has response for the R_TCP_DEVICE_ConnectRequest()
  */
 
 /*
  * R_TCP_DEVICE_ConnectIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address);
  * ---
  * R_TCP_DEVICE_ConnectIndication() is used to indicate that there is a connection request event raised from remote station,
  * This function shall be called once remote station sent connection request to this device
  */

 /*
  * R_TCP_DEVICE_DisconnectConfirm(TcpChannel tcp_channel, uint8_t result, uint8_t *reason, uint16_t reason_length);
  * ---
  * R_TCP_DEVICE_DisconnectConfirm() is used to confirm about the last R_TCP_DEVICE_DisconnectRequest() call,
  * Normally it is called once remote station has response for the R_TCP_DEVICE_DisconnectRequest()
  */

 /*
  * R_TCP_DEVICE_DisconnectIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, TcpDisconnectReason reason);
  * ---
  * R_TCP_DEVICE_DisconnectIndication() is used to indicate that there is a disconnection request event raised from remote station,
  * This function shall be called once remote station sent disconnection request to this device
  */

 /*
  * R_TCP_DEVICE_AbortIndication(TcpChannel tcp_channel, uint8_t *reason, uint16_t reason_length);
  * ---
  * R_TCP_DEVICE_AbortIndication() is used to indicate that there is an interruption event raised from local or from remote station,
  * This function shall be called once there is an  interruption happen between this device and remote station
  */

 /*
  * R_TCP_DEVICE_DataConfirm(TcpChannel tcp_channel, uint8_t result);
  * ---
  * R_TCP_DEVICE_DataConfirm() is used to confirm about the last R_TCP_DEVICE_DataRequest() call,
  * Normally it is called once to confirm about the data transmition end on the R_TCP_DEVICE_DataRequest()
  */

 /*
  * R_TCP_DEVICE_DataIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t *rx_buffer, uint16_t rx_buffer_length);
  * ---
  * R_TCP_DEVICE_DataIndication() is used to indicate that there is data received from remote station,
  * It is able to put fragmented data to R_TCP_DEVICE_DataIndication() and call multiple time. WPDU is concat & process normally.
  */

 /*
  * R_TCP_DEVICE_DataErrorIndication(TcpChannel tcp_channel);
  * ---
  * R_TCP_DEVICE_DataErrorIndication() is used to indicate that there is data received error happen on this device
  */


/******************************************************************************
* Function Name : R_TCP_WRP_UartPhyReceiveData
* Interface     : void R_TCP_WRP_UartPhyReceiveData(TcpChannel channel, uint8_t received_byte)
* Description   : 
* Arguments     : TcpChannel channel   :
*               : uint8_t received_byte:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_TCP_WRP_UartPhyReceiveData(TcpChannel channel, uint8_t received_byte)
{
    
}

/******************************************************************************
* Function Name : R_TCP_WRP_UartPhySendEnd
* Interface     : void R_TCP_WRP_UartPhySendEnd(TcpChannel channel)
* Description   : 
* Arguments     : TcpChannel channel:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_TCP_WRP_UartPhySendEnd(TcpChannel channel)
{
    
}

/******************************************************************************
* Function Name : R_TCP_WRP_ReceiverTimeoutMilisecond
* Interface     : void R_TCP_WRP_ReceiverTimeoutMilisecond(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_TCP_WRP_ReceiverTimeoutMilisecond(void)
{
    
}

/******************************************************************************
* Function Name : R_TCP_WRP_IsConnected
* Interface     : uint8_t R_TCP_WRP_IsConnected(void)
* Description   : 
* Arguments     : None:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_TCP_WRP_IsConnected(void)
{
    /* TODO: Add implementation to check if meter connected to network */
    return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_WRP_TryOpenConnection
* Interface     : uint8_t R_TCP_WRP_TryOpenConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
* Description   : 
* Arguments     : TcpPort remote_port: remote port to connect
*               : IpAddressPtr remote_ip_address: remote IP address to connect
* Return Value  : uint8_t: TRUE or FALSE
*               : TRUE: already connected or connect successfully
*               : FALSE: connection failed (timeout)
******************************************************************************/
uint8_t R_TCP_WRP_TryOpenConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
{
    return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_WRP_TryCloseConnection
* Interface     : uint8_t R_TCP_WRP_TryCloseConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
* Description   : 
* Arguments     : TcpPort remote_port: remote port to disconnect
*               : IpAddressPtr remote_ip_address: remote IP address to disconnect
* Return Value  : uint8_t: TRUE or FALSE
*               : TRUE: already disconnected or disconnect successfully
*               : FALSE: disconnection failed
******************************************************************************/
uint8_t R_TCP_WRP_TryCloseConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
{
    return TRUE;
}

#endif /* #if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == FALSE) */