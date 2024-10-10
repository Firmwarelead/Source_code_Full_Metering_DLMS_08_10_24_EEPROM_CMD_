/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2015, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_rtc_user.c
* Version      : Code Generator for RL78/I1C V1.01.07.02 [08 Nov 2021]
* Device(s)    : R5F10NPL(Dual)
* Tool-Chain   : CCRL
* Description  : This file implements device driver for RTC module.
* Creation Date: 2/22/2023
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"
/* Start user code for include. Do not edit comment generated here */
#include "em_core.h"
#include "inst_read.h"
#include "config_storage.h"
#include "platform.h"
#include "em_display.h"
#include "event.h"
#include "key.h"
#include "powermgmt.h"
#ifdef _DLMS
#include "r_dlms_date_time.h"
#endif
#include "rtc_compensation.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
volatile uint16_t g_user_app_stable_run_count = 0;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_rtc_periodicinterrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __CCRL__
#pragma interrupt r_rtc_periodicinterrupt
#endif /* __CCRL__ */
#ifdef __ICCRL78__
__interrupt
#endif /* __ICCRL78__ */
void r_rtc_periodicinterrupt(void)
{
    volatile uint8_t tmp;
    EI();
    
    VRTCEN = 1U;

    tmp = RSR;
    tmp &= (uint8_t)~_04_RTC_PERIODIC_INTERRUPT; 	/* clear PF */
    RSR = tmp;
    r_rtc_callback_periodic();
}

/***********************************************************************************************************************
* Function Name: r_rtc_callback_periodic
* Description  : This function is real-time clock interrupt service handler.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_rtc_callback_periodic(void)
{
    /* Start user code. Do not edit comment generated here */
    EM_RTC_CalibInterruptCallback();
    
    INST_READ_RTC_InterruptCallBack();
    
    CONFIG_RtcCallback();
	
    #ifdef _DLMS
	R_DLMS_RTC_Drv_PeriodCallBack();
    #endif

    
    POWERMGMT_RTC_Periodic_InterruptCallback();
    
    #if (R_DLMS_APPS_LOADCONTROL_ENABLE == TRUE)
    {
        static uint8_t count = 0;
        if (KEY_UP == 1)
        {
            count++;
            /* Press continuously 2 seconds */
            if (count >= 4)
            {
                /* Recover the relay */
                g_load_ctrl_manual_reconn_flag = TRUE;
                count = 0;
            }
        }
        else
        {
            count = 0;
        }
    }
    #endif

    RTC_COMP_ConstInterruptCallback();

    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_rtc_alarm0interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __CCRL__
#pragma interrupt r_rtc_alarm0interrupt
#endif /* __CCRL__ */
#ifdef __ICCRL78__
__interrupt
#endif /* __ICCRL78__ */
void r_rtc_alarm0interrupt(void)
{
    volatile uint8_t tmp;

    //RTCAIF0 = 0;    /* Clear the interrupt request flag */
    r_rtc_callback_alarm0();
}

/***********************************************************************************************************************
* Function Name: r_rtc_callback_alarm0
* Description  : This function is real-time clock interrupt service handler.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_rtc_callback_alarm0(void)
{
    /* Start user code. Do not edit comment generated here */
    POWERMGMT_RTC_Alarm_InterruptCallback();
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_rtc_alarm1interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __CCRL__
#pragma interrupt r_rtc_alarm1interrupt
#endif /* __CCRL__ */
#ifdef __ICCRL78__
__interrupt
#endif /* __ICCRL78__ */
void r_rtc_alarm1interrupt(void)
{
    volatile uint8_t tmp;

    //RTCAIF1 = 0;    /* Clear the interrupt request flag */
	r_rtc_callback_alarm1();
}

/***********************************************************************************************************************
* Function Name: r_rtc_callback_alarm1
* Description  : This function is real-time clock interrupt service handler.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_rtc_callback_alarm1(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
