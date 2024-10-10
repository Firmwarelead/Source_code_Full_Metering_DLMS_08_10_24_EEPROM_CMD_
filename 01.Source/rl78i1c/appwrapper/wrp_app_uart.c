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
/* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.  */
/****************************************************************************** 
* File Name    : wrp_app_uart.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CubeSuite Version 1.5d
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : UART Wrapper Layer Source File
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"       /* Macro Driver Definitions */
#include "r_cg_sau.h"               /* UART Driver Serial definitions */

/* Wrapper/User */
#include "wrp_app_uart.h"          /* UART Wrapper header */

/* Application */
#include "platform.h"
#ifdef _DLMS
#include "r_dlms_config.h"
#include "r_dlms_physical_wrapper.h"
#include "r_dlms_udp_wrapper.h"
#include "r_dlms_tcp_wrapper.h"
#include "r_dlms_udp_wrapper_interface.h"
#include "r_dlms_tcp_wrapper_interface.h"
#endif
#include "r_meter_cmd.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Macro Definitions Checking
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
uint8_t g_received_byte;
uint8_t g_received_byte_1st;
	
/******************************************************************************
* Function Name    : void WRP_UART_Init(void)
* Description      : WRAPPER UART Initialization
* Arguments        : None
* Functions Called : WRP_UART_DRIVER_Init()
* Return Value     : None
******************************************************************************/
void WRP_UART_Init(void)
{
    WRP_UART_DRIVER_Init();
}

/******************************************************************************
* Function Name    : void WRP_UART_Start(void)
* Description      : WRAPPER UART Start
* Arguments        : None
* Functions Called : WRP_UART_DRIVER_Start()
* Return Value     : None
******************************************************************************/
void WRP_UART_Start(void)
{
    WRP_UART_DRIVER_Start();
    
    /* Start receive data byte */
    WRP_UART_ReceiveData(&g_received_byte, 1);
}

/******************************************************************************
* Function Name    : void WRP_UART_Stop(void)
* Description      : WRAPPER UART Stop
* Arguments        : None
* Functions Called : WRP_UART_DRIVER_Stop()
* Return Value     : None
******************************************************************************/
void WRP_UART_Stop(void)
{
    WRP_UART_DRIVER_Stop();
}

/******************************************************************************
* Function Name    : uint8_t WRP_UART_SendData(uint8_t *data, uint16_t length)
* Description      : WRAPPER UART Send Start
* Arguments        : uint8_t *data: Data buffer
*                  : uint16_t length: Length of buffer
* Functions Called : WRP_UART_DRIVER_SendData()
* Return Value     : None
******************************************************************************/
uint8_t WRP_UART_SendData(uint8_t *data, uint16_t length)
{
    if (WRP_UART_DRIVER_SendData(data, length) != MD_OK)
    {
        return WRP_UART_ERROR;  /* Error */
    }
    else
    {
        return WRP_UART_OK;     /* OK */
    }
}

/******************************************************************************
* Function Name    : uint8_t WRP_UART_ReceiveData(uint8_t *data, uint16_t length)
* Description      : WRAPPER UART Receive Start
* Arguments        : uint8_t *data: Data buffer
*                  : uint16_t length: Length of buffer
* Functions Called : WRP_UART_DRIVER_ReceiveData()
* Return Value     : None
******************************************************************************/
uint8_t WRP_UART_ReceiveData(uint8_t *data, uint16_t length)
{
    if (WRP_UART_DRIVER_ReceiveData(data, length) != MD_OK)
    {
        return WRP_UART_ERROR;  /* Error */
    }
    else
    {
        return WRP_UART_OK;     /* OK */
    }
}

/******************************************************************************
* Function Name    : uint8_t WRP_UART_CheckOperating(void)
* Description      : WRAPPER UART Check operating status
* Arguments        : None
* Functions Called : WRP_UART_DRIVER_CheckOperating
* Return Value     : uint8_t: operating status
*                  :    0: not operating
*                  :    1: operating
******************************************************************************/
uint8_t WRP_UART_CheckOperating(void)
{
    return WRP_UART_DRIVER_CheckOperating();
}

/******************************************************************************
* Function Name    : uint8_t WRP_UART_SetConfig(void)
* Description      : WRAPPER UART Set driver baud rate
* Arguments        : wrp_uart_length_t length: bit length of send byte
*                  : wrp_uart_parity_t parity: parity selection
*                  : wrp_uart_stopbits_t stopbits: number of stopbits
* Functions Called : WRP_UART_DRIVER_SetConfig
* Return Value     : None
******************************************************************************/
void WRP_UART_SetConfig(wrp_uart_length_t length, wrp_uart_parity_t parity, wrp_uart_stopbits_t stopbits)
{
    /* Map baudrate definition directly for this driver */
    WRP_UART_DRIVER_SetConfig((sau_std_length_t)length, (sau_std_parity_t)parity, (sau_std_stopbits_t)stopbits);
}

/******************************************************************************
* Function Name    : void WRP_UART_SendEndCallback(void)
* Description      : WRAPPER UART Send End Callback
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
void WRP_UART_SendEndCallback(void)
{
    /* Put application callback here */
    #ifdef _DLMS
    /* DLMS Transmit End */
    R_PHY_DeviceSendEnd(0);
    #endif /* _DLMS */
    R_METER_CMD_UART_SendEndCallback();
}

/******************************************************************************
* Function Name    : void WRP_UART_ReceiveEndCallback(void)
* Description      : WRAPPER UART Receive End Callback
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
void WRP_UART_ReceiveEndCallback(void)
{
    /* Put application callback here */
    #ifdef _DLMS
    /* DLMS Receive End */
    R_PHY_DeviceReceiveEnd(0, g_received_byte);
    #endif /* _DLMS */
    R_METER_CMD_UART_ReceiveEndCallback(0, g_received_byte);

    WRP_UART_ReceiveData(&g_received_byte, 1);
}

/******************************************************************************
* Function Name    : void WRP_UART0_Init(void)
* Description      : WRAPPER UART0 Initialization
* Arguments        : None
* Functions Called : WRP_UART0_DRIVER_Init()
* Return Value     : None
******************************************************************************/
void WRP_UART0_Init(void)
{
    WRP_UART0_DRIVER_Init();
}

/******************************************************************************
* Function Name    : void WRP_UART0_Start(void)
* Description      : WRAPPER UART Start
* Arguments        : None
* Functions Called : WRP_UART0_ReceiveData()
* Return Value     : None
******************************************************************************/
void WRP_UART0_Start(void)
{
    WRP_UART0_DRIVER_Start();
    
    /* Start receive data byte */
    WRP_UART0_ReceiveData(&g_received_byte_1st, 1);
}

/******************************************************************************
* Function Name    : void WRP_UART0_Stop(void)
* Description      : WRAPPER UART0 Stop
* Arguments        : None
* Functions Called : WRP_UART0_DRIVER_Stop()
* Return Value     : None
******************************************************************************/
void WRP_UART0_Stop(void)
{
    WRP_UART0_DRIVER_Stop();
}

/******************************************************************************
* Function Name    : uint8_t WRP_UART0_SendData(uint8_t *data, uint16_t length)
* Description      : WRAPPER UART0 Send Start
* Arguments        : uint8_t *data: Data buffer
*                  : uint16_t length: Length of buffer
* Functions Called : WRP_UART0_DRIVER_SendData()
* Return Value     : None
******************************************************************************/
uint8_t WRP_UART0_SendData(uint8_t *data, uint16_t length)
{
    if (WRP_UART0_DRIVER_SendData(data, length) != MD_OK)
    {
        return WRP_UART_ERROR;  /* Error */
    }
    else
    {
        return WRP_UART_OK;     /* OK */
    }
}

/******************************************************************************
* Function Name    : uint8_t WRP_UART0_ReceiveData(uint8_t *data, uint16_t length)
* Description      : WRAPPER UART0 Receive Start
* Arguments        : uint8_t *data: Data buffer
*                  : uint16_t length: Length of buffer
* Functions Called : WRP_UART0_DRIVER_ReceiveData()
* Return Value     : None
******************************************************************************/
uint8_t WRP_UART0_ReceiveData(uint8_t *data, uint16_t length)
{
    if (WRP_UART0_DRIVER_ReceiveData(data, length) != MD_OK)
    {
        return WRP_UART_ERROR;  /* Error */
    }
    else
    {
        return WRP_UART_OK;     /* OK */
    }
}

/******************************************************************************
* Function Name    : uint8_t WRP_UART0_CheckOperating(void)
* Description      : WRAPPER UART0 Check operating status
* Arguments        : None
* Functions Called : WRP_UART0_DRIVER_CheckOperating
* Return Value     : uint8_t: operating status
*                  :    0: not operating
*                  :    1: operating
******************************************************************************/
uint8_t WRP_UART0_CheckOperating(void)
{
    return WRP_UART0_DRIVER_CheckOperating();
}

/******************************************************************************
* Function Name    : uint8_t WRP_UART0_SetConfig(void)
* Description      : WRAPPER UART0 Set driver baud rate
* Arguments        : wrp_uart_length_t length: bit length of send byte
*                  : wrp_uart_parity_t parity: parity selection
*                  : wrp_uart_stopbits_t stopbits: number of stopbits
* Functions Called : WRP_UART0_DRIVER_SetConfig
* Return Value     : None
******************************************************************************/
void WRP_UART0_SetConfig(wrp_uart_length_t length, wrp_uart_parity_t parity, wrp_uart_stopbits_t stopbits)
{
    /* Map baudrate definition directly for this driver */
    WRP_UART0_DRIVER_SetConfig((sau_std_length_t)length, (sau_std_parity_t)parity, (sau_std_stopbits_t)stopbits);
}

/******************************************************************************
* Function Name    : void WRP_UART0_SendEndCallback(void)
* Description      : WRAPPER UART0 Send End Callback
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
void WRP_UART0_SendEndCallback(void)
{
    /* Put application callback here */
    #ifdef _DLMS
    /* DLMS Transmit End */
#if defined(SUPPORT_UDP_PROFILE) && (SUPPORT_UDP_PROFILE == TRUE)
    R_UDP_WRP_UartPhySendEnd(0);
#endif
#if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == TRUE)
    R_TCP_WRP_UartPhySendEnd(0);
#endif
    #endif /* _DLMS */
    
    R_METER_CMD_UART_SendEndCallback();
}

/******************************************************************************
* Function Name    : void WRP_UART0_ReceiveEndCallback(void)
* Description      : WRAPPER UART0 Receive End Callback
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
void WRP_UART0_ReceiveEndCallback(void)
{
    /* Put application callback here */
    /* Put application callback here */
    #ifdef _DLMS
    /* DLMS Transmit End */
#if defined(SUPPORT_UDP_PROFILE) && (SUPPORT_UDP_PROFILE == TRUE)
    R_UDP_WRP_UartPhyReceiveData(0, g_received_byte_1st);
#endif
#if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == TRUE)
    R_TCP_WRP_UartPhyReceiveData(0, g_received_byte_1st);
#endif
    #endif /* _DLMS */
    R_METER_CMD_UART_ReceiveEndCallback(1, g_received_byte_1st);
	
    WRP_UART0_ReceiveData(&g_received_byte_1st, 1);
}

/*****************************************************************************************
* function      : uint8_t WRP_UART_SetBaudRate(uint8_t new_baud_rate)
* description   : this function is used to change UART baudrate
* input         : uint8_t new_baud_rate
* output        : none
* return        : none
*******************************************************************************************/
void WRP_UART_SetBaudRate(wrp_uart_baud_rate_t new_baud_rate)
{
    WRP_UART_DRIVER_SetBaudRate((sau_std_baud_rate_t)new_baud_rate);
}

/*****************************************************************************************
* function		: void WRP_UART_ConfigHDLCProtocol(void)
* description	: Reconfigure UART to adapt with HDLC protocol
*				  Data bit : 8
*				  Stop bit : 1
*				  Parity   : None
* input			: none
* output		: none
* return 		: none
*****************************************************************************************/
void WRP_UART_ConfigHDLCProtocol(void)
{
	if (WRP_UART_DRIVER_CheckOperating() == 1)
	{
		WRP_UART_Stop();
		/* 8bits, even none, 1 stop bit */
		WRP_UART_SetConfig(WRP_UART_LENGTH_8, WRP_UART_PARITY_NONE, WRP_UART_STOPBITS_1);
		WRP_UART_Start();
	}
	else
	{
		WRP_UART_SetConfig(WRP_UART_LENGTH_8, WRP_UART_PARITY_NONE, WRP_UART_STOPBITS_1);
	}
}

/*****************************************************************************************
* function		: void WRP_UART_ConfigIECProtocol(void)
* description	: Reconfigure UART to adapt with IEC1107 protocol
*				  Data bit : 7
*				  Stop bit : 1
*				  Parity   : Even
* input			: none
* output		: none
* return 		: none
*****************************************************************************************/
void WRP_UART_ConfigIECProtocol(void)
{
	if (WRP_UART_DRIVER_CheckOperating() == 1)
	{
		WRP_UART_Stop();
		/* 7bits, even parity, 1 stop bit */
		WRP_UART_SetConfig(WRP_UART_LENGTH_7, WRP_UART_PARITY_EVEN, WRP_UART_STOPBITS_1);
		WRP_UART_Start();
	}
	else
	{
		/* 7bits, even parity, 1 stop bit */
		WRP_UART_SetConfig(WRP_UART_LENGTH_7, WRP_UART_PARITY_EVEN, WRP_UART_STOPBITS_1);
	}
}

/*****************************************************************************************
* function      : uint8_t WRP_UART0_SetBaudRate(uint8_t new_baud_rate)
* description   : this function is used to change UART baudrate
* input         : uint8_t new_baud_rate
* output        : none
* return        : none
*******************************************************************************************/
void WRP_UART0_SetBaudRate(wrp_uart_baud_rate_t new_baud_rate)
{
    WRP_UART0_DRIVER_SetBaudRate((sau_std_baud_rate_t)new_baud_rate);
}

/*****************************************************************************************
* function		: void WRP_UART0_ConfigHDLCProtocol(void)
* description	: Reconfigure UART0 to adapt with HDLC protocol
*				  Data bit : 8
*				  Stop bit : 1
*				  Parity   : None
* input			: none
* output		: none
* return 		: none
*****************************************************************************************/
void WRP_UART0_ConfigHDLCProtocol(void)
{
	if (WRP_UART0_DRIVER_CheckOperating() == 1)
	{
		WRP_UART0_Stop();
		/* 8bits, even none, 1 stop bit */
		WRP_UART0_SetConfig(WRP_UART_LENGTH_8, WRP_UART_PARITY_NONE, WRP_UART_STOPBITS_1);
		WRP_UART0_Start();
	}
	else
	{
		WRP_UART0_SetConfig(WRP_UART_LENGTH_8, WRP_UART_PARITY_NONE, WRP_UART_STOPBITS_1);
	}
}

/*****************************************************************************************
* function		: void WRP_UART0_ConfigIECProtocol(void)
* description	: Reconfigure UART0 to adapt with IEC1107 protocol
*				  Data bit : 7
*				  Stop bit : 1
*				  Parity   : Even
* input			: none
* output		: none
* return 		: none
*****************************************************************************************/
void WRP_UART0_ConfigIECProtocol(void)
{
	if (WRP_UART0_DRIVER_CheckOperating() == 1)
	{
		WRP_UART0_Stop();
		/* 7bits, even parity, 1 stop bit */
		WRP_UART0_SetConfig(WRP_UART_LENGTH_7, WRP_UART_PARITY_EVEN, WRP_UART_STOPBITS_1);
		WRP_UART0_Start();
	}
	else
	{
		/* 7bits, even parity, 1 stop bit */
		WRP_UART0_SetConfig(WRP_UART_LENGTH_7, WRP_UART_PARITY_EVEN, WRP_UART_STOPBITS_1);
	}
}