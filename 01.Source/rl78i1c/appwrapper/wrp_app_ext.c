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
* File Name    : wrp_app_ext.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CubeSuite Version 1.5d
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : IIC Wrapper Layer Source File
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"   /* Macro Driver Definitions */
#include "r_cg_wdt.h"
#include "r_cg_tau.h"

/* Standard library */
#include <stdlib.h>


#include "wrp_app_ext.h"       /* Wrapper IIC header */

/* Bootloader */
#include "bl_operation.h"

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
static volatile uint16_t g_wrp_ext_sys_time = 0;

/******************************************************************************
* Function Name    : void WRP_EXT_SoftReset(void)
* Description      : Do MCU software reset
* Arguments        : None
* Return Value     : None
******************************************************************************/
void WRP_EXT_SoftReset(void)
{
    /* Inform bootloader before reset to avoid image recovery */
    BL_OPERATION_RequestUserReset();
    
    /* Write invalid value to WDTE register */
    WDTE = 0x00;

    /* Wait few clock cycle:
    * This will let the above instruction fetch in pipeline
    * and MCU reset before exitting this function 
    */
    NOP(); NOP(); NOP();
}

/******************************************************************************
* Function Name    : uint8_t WRP_EXT_Bcd2Dec(uint8_t x)
* Description      : Convert 1 BCD number to Decimal Number
* Arguments        : None
* Return Value     : uint8_t: converted number
******************************************************************************/
uint8_t WRP_EXT_Bcd2Dec(uint8_t x)
{
    x = (x & 0xF) + (x >> 4) * 10;

    return x;
}

/******************************************************************************
* Function Name    : uint8_t WRP_EXT_Dec2Bcd(uint8_t x)
* Description      : Convert 1 Decimal number to BCD Number
* Arguments        : None
* Return Value     : uint8_t: converted number
******************************************************************************/
uint8_t WRP_EXT_Dec2Bcd(uint8_t x)
{
    x = (x % 10) | (((x / 10) << 4) & 0xF0);

    return x;
}

/******************************************************************************
* Function Name    : uint8_t WRP_EXT_HwDelayIsTimerRunning(void)
* Description      : Check if hardware timer used for hardware delay is running
*                  : Used this function to prevent dead lock while waiting for system tick
* Arguments        : None
* Return Value     : uint8_t: TRUE, hardware timer is running, FALSE: stopped
******************************************************************************/
uint8_t WRP_EXT_HwDelayIsTimerRunning(void)
{
    return ((R_TAU0_IsChannelRunning(TAU_CHANNEL0) == 1) ? TRUE : FALSE);
}

/******************************************************************************
* Function Name    : uint8_t WRP_EXT_HwDelay(uint16_t ms, fp_predicate p)
* Description      : Delay ms amount of time until end of time or pred TRUE
*                  : Please take care of interrupt priority of hardware timer
*                  : Do not use this function inside an interrupt which has higher priority
* Arguments        : uint16_t ms: 0 or 0xFFFF will not be accepted
*                  : fp_predicate p: predicate function pointer
* Return Value     : uint8_t: return status accordingly
******************************************************************************/
uint8_t WRP_EXT_HwDelay(uint16_t ms, fp_predicate p)
{
    uint16_t begin, duration;

    /* This function can only accept < 0xFFFF value, as it cannot do compare with highest value */
    if (ms == 0xFFFF || ms == 0) {
        /* No delay operation */
        return WRP_EXT_HW_DELAY_INVALID_ARGS;
    }

    begin = g_wrp_ext_sys_time;
    do 
    {
        R_WDT_Restart();
        
        /* Confirm hardware timer is running */
        if (WRP_EXT_HwDelayIsTimerRunning() != TRUE)
        {
            return WRP_EXT_HW_DELAY_TIMER_STOPPED;
        }

        /* Check timeout */
        if (g_wrp_ext_sys_time < begin) {
            duration = (65535 - begin) + g_wrp_ext_sys_time;
        }
        else {
            duration = g_wrp_ext_sys_time - begin;
        }
        if (duration >= ms) {
            return WRP_EXT_HW_DELAY_TIMEOUT;
        }

        /* Check predicate function */
        if (p != NULL) {
            if (p() == 1) {
                return WRP_EXT_HW_DELAY_PRED_TRUE;
            }
        }
    } while (1);

    /* No return statement here as condition will not reached */
}

/******************************************************************************
* Function Name    : uint8_t WRP_EXT_Dec2Bcd(uint8_t x)
* Description      : Convert 1 Decimal number to BCD Number
* Arguments        : None
* Return Value     : uint8_t: converted number
******************************************************************************/
void WRP_EXT_HwDelayMillisecondTimerCallback(void)
{
    g_wrp_ext_sys_time++;
}

/******************************************************************************
* Function Name : WRP_EXT_Heap_Malloc
* Interface     : void NEAR_PTR * FAR_PTR WRP_EXT_Heap_Malloc(size_t size)
* Description   : Create a memory area with specific size
* Arguments     : size_t size: Requested size of memory to be created
* Return Value  : void NEAR_PTR *, returned memory buffer pointer
******************************************************************************/
void * WRP_EXT_Heap_Malloc(size_t size)
{
    void * ptr = malloc(size);

    return ptr;
}

/******************************************************************************
* Function Name : WRP_EXT_Heap_Free
* Interface     : void WRP_EXT_Heap_Free(void NEAR_PTR * ptr)
* Description   : Free the memory area that created by malloc()
* Arguments     : void NEAR_PTR * ptr: Pointer of area that memory created by malloc()
* Return Value  : None
******************************************************************************/
void WRP_EXT_Heap_Free(void * ptr)
{
    free(ptr);
}
