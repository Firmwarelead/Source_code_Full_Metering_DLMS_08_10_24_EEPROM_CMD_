/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : wrp_app_uart.h
* Version      : 1.00
* Description  : Wrapper App UART
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _WRAPPER_APP_UART_H
#define _WRAPPER_APP_UART_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_cg_sau.h"

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum tagWrpUartBaudRate
{
    WRP_UART_BAUD_RATE_300,
    WRP_UART_BAUD_RATE_600,
    WRP_UART_BAUD_RATE_1200,
    WRP_UART_BAUD_RATE_2400,
    WRP_UART_BAUD_RATE_4800,
    WRP_UART_BAUD_RATE_9600,
    WRP_UART_BAUD_RATE_19200,
    WRP_UART_BAUD_RATE_38400,
    WRP_UART_BAUD_RATE_57600,
    WRP_UART_BAUD_RATE_115200,

} wrp_uart_baud_rate_t;

typedef enum tagWrpUartLength
{
    WRP_UART_LENGTH_7 = _0002_SAU_LENGTH_7,
    WRP_UART_LENGTH_8 = _0003_SAU_LENGTH_8,
    WRP_UART_LENGTH_9 = _0001_SAU_LENGTH_9,
} wrp_uart_length_t;

typedef enum tagWrpUartParity
{
    WRP_UART_PARITY_NONE = _0000_SAU_PARITY_NONE,
    WRP_UART_PARITY_ODD = _0300_SAU_PARITY_ODD,
    WRP_UART_PARITY_EVEN = _0200_SAU_PARITY_EVEN,
} wrp_uart_parity_t;

typedef enum tagWrpUartStopBits
{
    WRP_UART_STOPBITS_1 = _0010_SAU_STOP_1,
    WRP_UART_STOPBITS_2 = _0020_SAU_STOP_2,
} wrp_uart_stopbits_t;

/******************************************************************************
Macro definitions
******************************************************************************/
#define WRP_UART_OK     0   /* OK */
#define WRP_UART_ERROR  1   /* Error */

/* Interface mapping, for each driver,
 * we must re-map again about the UART_DRIVER interface */
 
/* Initialization */
#define     WRP_UART_DRIVER_Init()                      {;}
#define     WRP_UART0_DRIVER_Init()                     {;}

/* Primary channel */
#define     WRP_UART_DRIVER_Start()                                 R_UART2_Start()
#define     WRP_UART_DRIVER_Stop()                                  R_UART2_Stop()
#define     WRP_UART_DRIVER_SendData(data, length)                  R_UART2_Send(data, length)
#define     WRP_UART_DRIVER_ReceiveData(data, length)               R_UART2_Receive(data, length)
#define     WRP_UART_DRIVER_CheckOperating()                        R_UART2_CheckOperating()
#define		WRP_UART_DRIVER_SetBaudRate(baud)	                    R_UART2_SetBaudRate((sau_std_baud_rate_t)baud)
#define     WRP_UART_DRIVER_SetConfig(length, parity, stopbits)     R_UART2_SetConfig(length, parity, stopbits)

/* Secondary channel */
#define     WRP_UART0_DRIVER_Start()                                R_UART0_Start()
#define     WRP_UART0_DRIVER_Stop()                                 R_UART0_Stop()
#define     WRP_UART0_DRIVER_SendData(data, length)                 R_UART0_Send(data, length)
#define     WRP_UART0_DRIVER_ReceiveData(data, length)              R_UART0_Receive(data, length)
#define		WRP_UART0_DRIVER_CheckOperating()                       R_UART0_CheckOperating()
#define		WRP_UART0_DRIVER_SetBaudRate(new_baud_rate)	            R_UART0_SetBaudRate((sau_std_baud_rate_t)new_baud_rate)
#define		WRP_UART0_DRIVER_SetConfig(length, parity, stopbits)    R_UART0_SetConfig(length, parity, stopbits)

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/
/* UART Wrapper Controller */
void    WRP_UART_Init(void);
void    WRP_UART_Start(void);
void    WRP_UART_Stop(void);
uint8_t WRP_UART_SendData(uint8_t *data, uint16_t length);
uint8_t WRP_UART_ReceiveData(uint8_t *data, uint16_t length);
uint8_t WRP_UART_CheckOperating(void);
void    WRP_UART_SetBaudRate(wrp_uart_baud_rate_t new_baud_rate);
void    WRP_UART_SetConfig(wrp_uart_length_t length, wrp_uart_parity_t parity, wrp_uart_stopbits_t stopbits);
void    WRP_UART_ConfigIECProtocol(void);
void    WRP_UART_ConfigHDLCProtocol(void);

void    WRP_UART0_Init(void);
void    WRP_UART0_Start(void);
void    WRP_UART0_Stop(void);
uint8_t WRP_UART0_SendData(uint8_t *data, uint16_t length);
uint8_t WRP_UART0_ReceiveData(uint8_t *data, uint16_t length);
uint8_t WRP_UART0_CheckOperating(void);
void    WRP_UART0_SetBaudRate(wrp_uart_baud_rate_t new_baud_rate);
void    WRP_UART0_SetConfig(wrp_uart_length_t length, wrp_uart_parity_t parity, wrp_uart_stopbits_t stopbits);
void    WRP_UART0_ConfigIECProtocol(void);
void    WRP_UART0_ConfigHDLCProtocol(void);

/*
 * Callback Registration
 * Callback, put 2 below interfaces to the serial user callback
 *      Send End Callback   : WRP_UART_SendEndCallback
 *      Receive End Callback: WRP_UART_ReceiveEndCallback
 */
void    WRP_UART_SendEndCallback(void);
void    WRP_UART_ReceiveEndCallback(void);

void    WRP_UART0_SendEndCallback(void);
void    WRP_UART0_ReceiveEndCallback(void);

#endif /* _WRAPPER_APP_UART_H */
