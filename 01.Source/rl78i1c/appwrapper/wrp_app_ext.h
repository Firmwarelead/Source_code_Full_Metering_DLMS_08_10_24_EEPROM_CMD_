/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : wrp_app_ext.h
* Version      : 1.00
* Description  : Wrapper App UART
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _WRAPPER_APP_EXT_H
#define _WRAPPER_APP_EXT_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "compiler.h"
#include <math.h>
#include <stddef.h>

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef uint8_t(*fp_predicate)(void);

/******************************************************************************
Macro definitions
******************************************************************************/
#define WRP_EXT_Absf(x)                      fabsf(x)   

#define WRP_EXT_HW_DELAY_TIMEOUT             0
#define WRP_EXT_HW_DELAY_PRED_TRUE           1
#define WRP_EXT_HW_DELAY_INVALID_ARGS        2
#define WRP_EXT_HW_DELAY_TIMER_STOPPED       3

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/
void WRP_EXT_SoftReset(void);
uint8_t WRP_EXT_Bcd2Dec(uint8_t x);
uint8_t WRP_EXT_Dec2Bcd(uint8_t x);

uint8_t WRP_EXT_HwDelayIsTimerRunning(void);
uint8_t WRP_EXT_HwDelay(uint16_t ms, fp_predicate p);
void WRP_EXT_HwDelayMillisecondTimerCallback(void);

void * WRP_EXT_Heap_Malloc(size_t size);
void            WRP_EXT_Heap_Free(void * ptr);

#endif /* _WRAPPER_APP_EXT_H */
