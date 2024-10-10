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
* File Name    : r_dlms_udp_wrapper_raw.c
* Version      : 1.00
* Device(s)    : R5F564MLCxDC
* Tool-Chain   : CCRX
* H/W Platform : RX64M RSK+
* Description  : UDP wrapper layer of DLMS
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
#include "r_dlms_udp_wrapper.h"
#include "r_dlms_udp_wrapper_interface.h"
#include "r_dlms_com_wrapper_config.h"
#if defined(SUPPORT_UDP_PROFILE) && (SUPPORT_UDP_PROFILE == TRUE) && (UDP_MODE_SELECTION == UDP_MODE_RAW)

/******************************************************************************
Macro definitions
******************************************************************************/
#define UDP_WRP_RAW_DLMS_PORT               (4059)

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
const uint8_t   g_udp_local_ip_addr_buffer[4] = {192, 168, 0, 5};
const IpAddress g_udp_local_ip_addr = { (uint8_t *)g_udp_local_ip_addr_buffer, 4 };
const uint8_t   g_udp_remote_ip_addr_buffer[4] = {192, 168, 0, 10};
const IpAddress g_udp_remote_ip_addr = { (uint8_t *)g_udp_remote_ip_addr_buffer, 4 };

/******************************************************************************
* Function Name : R_UDP_DEVICE_Init
* Interface     : void R_UDP_DEVICE_Init(void)
* Description   : Initial PHY Driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_UDP_DEVICE_Init(UdpChannel udp_channel)
{
    if (udp_channel == 0) {
        WRP_UART0_Init();
        WRP_UART0_SetBaudRate(WRP_UART_BAUD_RATE_9600);
        WRP_UART0_ConfigHDLCProtocol();
    }
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_Start
* Interface     : void R_UDP_DEVICE_Start(void)
* Description   : Start PHY Driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_UDP_DEVICE_Start(UdpChannel udp_channel)
{
    if (udp_channel == 0) {
        WRP_UART0_Start();
    }
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_Stop
* Interface     : void R_UDP_DEVICE_Stop(void)
* Description   : Stop PHY Driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_UDP_DEVICE_Stop(UdpChannel udp_channel)
{
    if (udp_channel == 0) {
        WRP_UART0_Stop();
    }
}


/******************************************************************************
* Function Name : R_UDP_DEVICE_PollingProcess
* Interface     : void R_UDP_DEVICE_PollingProcess(void)
* Description   : Polling process of UDP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_UDP_DEVICE_PollingProcess(UdpChannel udp_channel)
{
	if (udp_channel == 0) {
		/* Do nothing */
	}
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_GetConfig
* Interface     : uint8_t R_UDP_DEVICE_GetConfig(
*               :     UdpChannel udp_channel ,
*               :     UdpPortConfig* p_config,
*               : );
* Description   :
* Arguments     : UdpChannel udp_channel :
*               : UdpPortConfig* p_config:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_UDP_DEVICE_GetConfig(UdpChannel udp_channel, UdpPortConfig* p_config)
{
	/* TODO: Get config of UDP module, port and ip */
	if (udp_channel == 0) {

	}

	return 0;
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_SetConfig
* Interface     : uint8_t R_UDP_DEVICE_SetConfig(
*               :     UdpChannel udp_channel ,
*               :     UdpPortConfig* p_config,
*               : );
* Description   :
* Arguments     : UdpChannel udp_channel :
*               : UdpPortConfig* p_config:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_UDP_DEVICE_SetConfig(UdpChannel udp_channel, UdpPortConfig* p_config)
{
	/* TODO: Set config of UDP module, port and ip */
	if (udp_channel == 0) {

	}

	return 0;
}

/******************************************************************************
* Function Name : R_UDP_DEVICE_SendData
* Interface     : uint8_t R_UDP_DEVICE_SendData(uint8_t *data, uint16_t length)
* Description   : PHY send data
* Arguments     : uint8_t * data : Data buffer to be sent
*               : uint16_t length: Length of buffer
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_UDP_DEVICE_SendData(UdpChannel udp_channel, UdpPort remote_udp_port, IpAddressPtr remote_ip_address, uint8_t *data, uint16_t length)
{
    if (udp_channel == 0) {
        WRP_UART0_SendData(data, length);
    }
    
	return 0;
}

/******************************************************************************
* Function Name : R_UDP_WRP_UartPhyReceiveData
* Interface     : void R_UDP_WRP_UartPhyReceiveData(UdpChannel channel, uint8_t received_byte)
* Description   : 
* Arguments     : UdpChannel channel   :
*               : uint8_t received_byte:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_UDP_WRP_UartPhyReceiveData(UdpChannel channel, uint8_t received_byte)
{
    R_UDP_DeviceReceiveEnd(
        0,                                      /* UDP Channel */
        UDP_WRP_RAW_DLMS_PORT,                  /* UDP Port */
		(IpAddressPtr)&g_udp_remote_ip_addr,	/* Remote IP Address */
        &received_byte,                         /* RX Buffer */
        1                                       /* RX Buffer Length */
    );
}

/******************************************************************************
* Function Name : R_UDP_WRP_UartPhySendEnd
* Interface     : void R_UDP_WRP_UartPhySendEnd(UdpChannel channel)
* Description   : 
* Arguments     : UdpChannel channel:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_UDP_WRP_UartPhySendEnd(UdpChannel channel)
{
    R_UDP_DeviceSendEnd(0);
}

/******************************************************************************
* Function Name : R_UDP_WRP_ReceiverTimeoutMilisecond
* Interface     : void R_UDP_WRP_ReceiverTimeoutMilisecond(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_UDP_WRP_ReceiverTimeoutMilisecond(void)
{
    
}

/******************************************************************************
* Function Name : R_UDP_WRP_IsConnected
* Interface     : uint8_t R_UDP_WRP_IsConnected(void)
* Description   :
* Arguments     : None:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_UDP_WRP_IsConnected(void)
{
	/* Direct connection so always TRUE */
	return TRUE;
}
#endif /* #if defined(SUPPORT_UDP_PROFILE) && (SUPPORT_UDP_PROFILE == TRUE) && (UDP_MODE_SELECTION == UDP_MODE_RAW) */