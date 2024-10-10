/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
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
* Copyright (C) 2013, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : startup.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   :
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Start-up source File
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"   /* CG Macro Driver */
#include "r_cg_userdefine.h"    /* CG User Define */
#include "r_cg_port.h"          /* Port Driver*/
#include "r_cg_cgc.h"           /* CG CGC Driver */
#include "r_cg_rtc.h"           /* CG RTC Driver */
#include "r_cg_sau.h"           /* CG Serial Driver */
#include "r_cg_tau.h"           /* CG Timer Driver */
#include "r_cg_dsadc.h"         /* CG DSADC Driver */
#include "r_cg_wdt.h"           /* CG WDT Driver */
#include "r_cg_lcd.h"           /* CG LCD Driver */
#include "r_cg_iica.h"          /* CG COMP Driver */
#include "r_cg_lvd.h"           /* CG LVD Driver */
#include "r_cg_intp.h"          /* CG Interrupt Driver*/
#include "r_cg_12adc.h"         /* CG 10bit ADC Driver */
#include "r_cg_tmps.h"          /* CG Temperature Sensor Driver */

/* Standard library */
#include <stddef.h>
#include <stdlib.h>

/* Wrapper/User */
#include "wrp_app_uart.h"

/* Bootloader */
#include "bl_core.h"
#include "bl_main.h"

/* Metrology */
#include "em_core.h"            /* EM Core APIs */

/* Application */
#include "platform.h"           /* Default Platform Information Header */
#include "config_storage.h"     /* Interface */
#include "startup.h"            /* Startup Header File */
#include "dataflash.h"
#include "r_lcd_display.h"
#include "em_display.h"         /* EM Display */
#include "storage.h"
#include "event.h"              /* Event Header File */
#include "relay.h"              /* Relay management module */
#include "r_load_ctrl.h"
#include "r_meter_cmd.h"
#include "powermgmt.h"
#ifdef _DLMS
#include "r_dlms_main.h"		/* DLMS 2.0 */
#include "r_dlms_app.h"
#endif
#include "rtc_compensation.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tagStartupDiag
{
    uint8_t storage_init;
} startup_diag_t;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/
extern const uint16_t g_cnst_REL_sizeof_sysheap;
/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

startup_diag_t g_startup_diag;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name    : void start_peripheral_and_app(void)
* Description      : Start-up no checking, just diag code
* Arguments        : None
* Return Value     : Execution Status
*                  :    STARTUP_OK              Start-up Ok
*                  :    STARTUP_ERROR           Startup error
***********************************************************************************************************************/
void start_peripheral_and_app(void)
{
    /*****************************************************************
    * Initial all
    ******************************************************************/
    /* Start other peripherals */
    if ((RCR2 & _01_RTC_COUNTER_NORMAL) != _01_RTC_COUNTER_NORMAL)
    {
        /* RTC not running, set period and start RTC */
        R_RTC_Set_ConstPeriodInterruptOn(SEC1_2);
        R_RTC_Start();
    }
    else
    {
        /* RTC is running, not start it again to prevent missing interrupt, but ensure it's interrupt mask is off */
        RTCRMK = 0U;
        RTCAMK0 = 0U;
        RTCAMK1 = 0U;
    }

    /* LCD */
    R_LCD_PowerOn(1);

    /* Key */
    R_INTC1_Start();
    R_INTC3_Start();
    R_INTRTCIC2_Start();
    R_INTRTCIC1_Start();

    /* Timer */
    R_TAU0_Channel0_Start();

    /* LVD */
    R_LVD_Start_EXLVD();
    R_LVD_Start_VBAT();
    R_LVD_Start_VRTC();


    /* Init storage to prepare data for application before init application */
    g_startup_diag.storage_init = STORAGE_Init(0);

    /* Start other application */
    R_INST_SetSnapshotCaptureState(1);
    R_SCHEDULER_Init();
    R_TARIFF_Init();
    R_MDM_Init();
    EVENT_Init();

    #if(defined( R_LOAD_CONTROL_ENABLE ) && R_LOAD_CONTROL_ENABLE == TRUE)
        R_LOAD_CTRL_Init();
        R_LIMITER_Init();
    #endif /* R_LOAD_CONTROL_ENABLE */
    
    WRP_UART_Start();
    
    #ifdef _DLMS
    R_DLMS_MAIN_Init();

    #endif /* _DLMS */
    R_METER_CMD_Init();

    /* Inform power on event */
    EVENT_PowerOn();

    RTC_COMP_Init();
}

/***********************************************************************************************************************
* Function Name    : void stop_peripheral(void)
* Description      : Stop peripheral, but not stop application
* Arguments        : None
* Return Value     : Execution Status
*                  :    STARTUP_OK              Start-up Ok
*                  :    STARTUP_ERROR           Startup error
***********************************************************************************************************************/
void stop_peripheral(void)
{
    /* Note: VRTCEN manage outside of this API */
    LCD_ClearAll();
    R_LCD_PowerOff();
    R_IICA0_Stop();
    R_UART0_Stop();
    R_UART2_Stop();
    R_TAU0_Channel0_Stop();
    R_TAU0_Channel2_Stop();
    R_INTC1_Stop();
    R_INTC3_Stop();
    /* Leave RTCIC (LCD scroll and Case open) running */
    R_PORT_StopCreate();
    R_12ADC_Stop();
    R_TMPS_Stop();
    /* RTC keep running, only mask off RTC periodic interrupt */
    RTCRMK = 1U; //Not using R_RTC_Stop(); it included stop counting, alarm and reset bit set
    R_DSADC_Stop();
    R_LVD_Stop_VBAT();
    R_LVD_Stop_VRTC();

    /* Switch to LS for larger operating range */
    if (FLASH_MODE_IS_HS() == 1)
    {
        FLASH_MODE_HS_TO_LS();
        //BL_UpdateFslDescriptor(1, 6);   /* Wide-voltage, 6Mhz */
    }
}

/***********************************************************************************************************************
* Function Name    : void startup(void)
* Description      : Start-up energy meter
* Arguments        : None
* Functions Called : State selection for startup
* Return Value     : Execution Status
*                  :    STARTUP_OK              Start-up Ok
*                  :    STARTUP_ERROR           Startup error
***********************************************************************************************************************/
void startup(void)
{
    uint8_t *p;
    
    start_peripheral_and_app();

    /* Sample checking normal or bankswap */
    //if (g_bl_bankswap_startup)
    //{
    //    /* Bank swap startup */
    //}
    //else
    //{
    //    /* Normal startup */
    //}

    /* Common: initialize relay */
    #ifdef RELAY_CONTROL_ENABLE
    RELAY_Initialize();
    #endif
#if(defined(R_DLMS_APPS_MALLOC_USING) && (R_DLMS_APPS_MALLOC_USING == TRUE))
	/*
	 * Allocate almost of heap RAM (margin 8 bytes) as a "big chunk" to make all free() calls
	 * in between the "big chunk" act as to reform the "big chunk".
	 * This helps some nested malloc() easier to success on requesting a bigger demand, in nested calls.
	 * https://www.embedded.com/print/4007638
	 */
	p = malloc(g_cnst_REL_sizeof_sysheap - 8);
	if (p != NULL) {
		free(p);
		p = NULL;
	}
#endif
}

