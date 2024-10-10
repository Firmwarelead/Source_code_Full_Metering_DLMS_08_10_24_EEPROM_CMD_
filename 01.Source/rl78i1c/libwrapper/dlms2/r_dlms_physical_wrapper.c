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
* File Name    : r_dlms_physical_wrapper.c
* Version      : 1.00
* Device(s)    : R5F564MLCxDC
* Tool-Chain   : CCRX
* H/W Platform : RX64M RSK+
* Description  : Physical wrapper layer of DLMS Client
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
#include "r_dlms_config.h"
#include "wrp_app_uart.h"
#include "r_dlms_physical_wrapper.h"

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

/******************************************************************************
* Function Name : r_phy_map_dlms_to_wrp_baud_rate
* Interface     : void r_phy_map_dlms_to_wrp_baud_rate(uart_baudrate_t dlms_baud_rate)
* Description   : Map DLMS phy baud rate to uart wrapper baud rate
* Arguments     : None
* Return Value  : None
******************************************************************************/
static wrp_uart_baud_rate_t r_phy_map_dlms_to_wrp_baud_rate(uart_baudrate_t dlms_baud_rate)
{
    switch(dlms_baud_rate)
    {
        case BAUDRATE_300:
            return WRP_UART_BAUD_RATE_300;
        case BAUDRATE_600:
            return WRP_UART_BAUD_RATE_600;
        case BAUDRATE_1200:
            return WRP_UART_BAUD_RATE_1200;
        case BAUDRATE_2400:
            return WRP_UART_BAUD_RATE_2400;
        case BAUDRATE_4800:
            return WRP_UART_BAUD_RATE_4800;
        case BAUDRATE_9600:
            return WRP_UART_BAUD_RATE_9600;
        case BAUDRATE_19200:
            return WRP_UART_BAUD_RATE_19200;
        case BAUDRATE_38400:
            return WRP_UART_BAUD_RATE_38400;
        default:
            return WRP_UART_BAUD_RATE_300;
    }
}

/******************************************************************************
* Function Name : R_PHY_DEVICE_Init
* Interface     : void R_PHY_DEVICE_Init(void)
* Description   : Initial PHY Driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_PHY_DEVICE_Init(PhyChannel phy_channel)
{
    if (phy_channel == 0) {
#if defined(HDLC_PHY_CH0_USE_IEC) && (HDLC_PHY_CH0_USE_IEC == TRUE)
        WRP_UART_Init();
#endif
    }
}

/******************************************************************************
* Function Name : R_PHY_DEVICE_Start
* Interface     : void R_PHY_DEVICE_Start(void)
* Description   : Start PHY Driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_PHY_DEVICE_Start(PhyChannel phy_channel)
{
    if (phy_channel == 0) {
#if defined(HDLC_PHY_CH0_USE_IEC) && (HDLC_PHY_CH0_USE_IEC == TRUE)		
        WRP_UART_Start();
#endif
    }
}

/******************************************************************************
* Function Name : R_PHY_DEVICE_Stop
* Interface     : void R_PHY_DEVICE_Stop(void)
* Description   : Stop PHY Driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_PHY_DEVICE_Stop(PhyChannel phy_channel)
{
    if (phy_channel == 0) {
#if defined(HDLC_PHY_CH0_USE_IEC) && (HDLC_PHY_CH0_USE_IEC == TRUE)
        WRP_UART_Stop();
#endif
    }
}

/******************************************************************************
* Function Name : R_PHY_DEVICE_ChangeBaudrate
* Interface     : void R_PHY_DEVICE_ChangeBaudrate(uart_baudrate_t baudrate)
* Description   : Change Baudrate of PHY device
* Arguments     : uart_baudrate_t baudrate: Desired baudrate
* Return Value  : None
******************************************************************************/
void R_PHY_DEVICE_ChangeBaudrate(PhyChannel phy_channel, uart_baudrate_t baudrate)
{
    if (phy_channel == 0) {
#if defined(HDLC_PHY_CH0_USE_IEC) && (HDLC_PHY_CH0_USE_IEC == TRUE)		
        WRP_UART_SetBaudRate(r_phy_map_dlms_to_wrp_baud_rate(baudrate));
#endif
    }
}

/******************************************************************************
* Function Name : R_PHY_DEVICE_ChangeSetting7E1
* Interface     : void R_PHY_DEVICE_ChangeSetting7E1(void)
* Description   : Change settings to 7E1
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_PHY_DEVICE_ChangeSetting7E1(PhyChannel phy_channel)
{
	if (phy_channel == 0) {
#if defined(HDLC_PHY_CH0_USE_IEC) && (HDLC_PHY_CH0_USE_IEC == TRUE)		
		WRP_UART_ConfigIECProtocol();
#endif
	}
}

/******************************************************************************
* Function Name : R_PHY_DEVICE_ChangeSetting8N1
* Interface     : void R_PHY_DEVICE_ChangeSetting8N1(void)
* Description   : Change setting to 8N1
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_PHY_DEVICE_ChangeSetting8N1(PhyChannel phy_channel)
{
	if (phy_channel == 0) {
#if defined(HDLC_PHY_CH0_USE_IEC) && (HDLC_PHY_CH0_USE_IEC == TRUE)		
		WRP_UART_ConfigHDLCProtocol();
#endif
	}
}

/******************************************************************************
* Function Name : R_PHY_DEVICE_SendData
* Interface     : uint8_t R_PHY_DEVICE_SendData(uint8_t *data, uint16_t length)
* Description   : PHY send data
* Arguments     : uint8_t * data : Data buffer to be sent
*               : uint16_t length: Length of buffer
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_PHY_DEVICE_SendData(PhyChannel phy_channel, uint8_t *data, uint16_t length)
{
    if (phy_channel == 0) {
        WRP_UART_SendData(data, length);
    }
    
	return 0;
}
