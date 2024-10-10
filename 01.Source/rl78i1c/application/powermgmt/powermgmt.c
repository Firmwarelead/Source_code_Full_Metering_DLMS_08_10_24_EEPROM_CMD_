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
* File Name    : powermgmt.c
* Version      : 1.00
* Device(s)    : None
* Tool-Chain   : CubeSuite+
* H/W Platform : Unified Energy Meter Platform
* Description  : Power Management Module
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 24.06.2013
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"           /* CG Macro Driver */
#include "r_cg_userdefine.h"            /* CG User define */
#include "r_cg_cgc.h"                   /* CG CGC Driver */
#include "r_cg_rtc.h"                   /* CG RTC Driver */
#include "r_cg_sau.h"                   /* CG Serial Driver */
#include "r_cg_dsadc.h"                 /* CG DSADC Driver */
#include "r_cg_wdt.h"                   /* CG WDT Driver */
#include "r_cg_lcd.h"                   /* CG LCD Driver */
#include "r_cg_iica.h"                  /* CG COMP Driver */
#include "r_cg_lvd.h"                   /* CG LVD Driver */

/* Standard library */
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/* Wrapper/User */
#include "wrp_em_mcu.h"                    /* Wrapper/MCU */
#include "wrp_app_ext.h"
#include "wrp_em_sw_config.h"

/* MW/Core */
#include "em_main.h"                    /* Metrology main loading */
#include "em_core.h"                    /* EM Core APIs */

/* Application */
#include "platform.h"                   /* Platform information header file */
#include "startup.h"                    /* Start up header file */
#include "powermgmt.h"                  /* Power Management Header File */
#include "standby.h"
#include "r_lcd_display.h"              /* LCD display header file */
#include "em_display.h"                 /* LCD parameter header file */
#include "event.h"                      /* Event header file */
#include "r_tariff.h"
#include "r_loadsurvey.h"
#include "inst_read.h"
#include "r_abnormal_operating.h"
#include "storage.h"                    /* Storage header file */
#ifdef _DLMS
#include "r_dlms_event.h"
#endif
#include "key.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/* Control power management operation */
#define POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE                   TRUE        /* Default: True */
#define POWERMGMT_USING_DEBUG_CONTROL_FLAG                          FALSE       /* Default: False */
#define POWERMGMT_DISPLAY_LCD_DEBUG_SYMBOL                          FALSE       /* Default: False */
#define POWERMGMT_ENABLE_DEBUG_PRINT                                FALSE       /* Default: False */
#define POWERMGMT_DEBUG_PRINT_BAUDRATE                              SAU_STD_BAUD_RATE_19200
#define EM_SW_PROPERTY_OPERATION_DEFAULT_NM_VOLTAGE                 (220.0f)    /* Volt */
#define EM_SW_PROPERTY_OPERATION_NM_POWER_THRESHOLD                 (0.5f * EM_SW_PROPERTY_OPERATION_DEFAULT_NM_VOLTAGE)

#if (POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE)
#define POWERMGMT_STANDBY_CALCULATE_ENABLE_DELAY                    FALSE       /* Enable delay in Standby processing to observer current consumption */
#define POWERMGMT_STANDBY_DELAY_RELEASE_EVENT                       (3)         /* x amount of seconds to release NM standby event */
#define POWERMGMT_STANDBY_INTERVAL_HIGH                             (1)         /* Standby sampling interval when load detected (in seconds) */
#define POWERMGMT_STANDBY_INTERVAL_LOW                              (60)        /* Standby sampling interval when no load (in seconds) */
#endif /* POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE */

#if (POWERMGMT_USING_DEBUG_CONTROL_FLAG == TRUE)
/* Debug */
#define POWERMGMT_DIRECT_IS_VDD_LOW()                               (g_powermgmt_debug_flag.lvdvddf    == 1U)
#define POWERMGMT_DIRECT_IS_EXLVD_LOW()                             (g_powermgmt_debug_flag.lvdexlvdf  == 1U)
#else
/* Power mamnagement mode flag checking */
#define POWERMGMT_DIRECT_IS_VDD_LOW()                               (LVDVDDF    == 1U)
#define POWERMGMT_DIRECT_IS_EXLVD_LOW()                             (LVDEXLVDF  == 1U)
#endif /* POWERMGMT_USING_DEBUG_CONTROL_FLAG == TRUE */

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct
{
    uint8_t is_rtc_int                  :1;         /* Flag to detect RTC period wake up source */
    uint8_t is_alarm_int                :1;         /* Flag to detect RTC alarm wakeup source */
    uint8_t is_vdd_low                  :1;         /* Flag to detect VDD Voltage Low */
    uint8_t is_ac_low                   :1;         /* Flag to detect AC Power Low */

} powermgmt_int_flag_t;

typedef struct tagPowerMgmtStandByControl
{
    uint8_t interval;
    uint16_t delay_release_count;
} powermgmt_standby_control_t;

#if (POWERMGMT_USING_DEBUG_CONTROL_FLAG == TRUE)
typedef struct tagPowermgmtDebugFlag
{
    uint8_t lvdvddf;
    uint8_t lvdexlvdf;
} powermgmt_debug_flag;
#endif

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
/* From r_cg_systeminit.c */
extern void R_Systeminit(void);

#if (POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE)
/* Import from wrp_em_adc.c */
extern EM_SAMPLES g_wrp_adc_samples;
extern void (NEAR_PTR * g_wrp_adc_basic_signal_ready_cb_and_return)(void);
#endif

/* Import from r_cg_intp_user.c */
extern volatile uint8_t g_intp_case_open_flag;

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
static powermgmt_mode_t        g_powermgmt_current_mode = POWERMGMT_MODE1;
static powermgmt_int_flag_t    g_powermgmt_flag;

#if (POWERMGMT_USING_DEBUG_CONTROL_FLAG == TRUE)
static volatile powermgmt_debug_flag g_powermgmt_debug_flag;
#endif /* POWERMGMT_USING_DEBUG_CONTROL_FLAG == TRUE */

#if (POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE)
static powermgmt_standby_control_t g_powermgmt_standby_control;
#endif /* POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE */

static void eeprom_enable(void)
{
    SET_BIT(P3, 0, 1);
    IICA0EN = 1U;
    P6 &= 0xFCU;
    PM6 &= 0xFCU;
    R_IICA0_Start();
}
static void eeprom_disable(void)
{
    R_IICA0_Stop();
    P6 &= 0xFCU;
    PM6 |= 0x03U;
    IICA0EN = 0U;
    SET_BIT(P3, 0, 0);
}
static void standby_start(void)
{
    DSADCEN = 1U;
    MACEN = 1U;
    R_DSADC_BackupPhaseRegSetting();
    R_DSADC_StartCurrentChannels();
}
static void standby_stop(void)
{
    R_DSADC_Stop();
    R_DSADC_RestorePhaseRegSetting();
    DSADCEN = 0U;
    MACEN = 0U;
}
#if (POWERMGMT_ENABLE_DEBUG_PRINT == TRUE)
static void printf_uart0(const char *format, ...)
{
    #define CMD_PRINTF_MAX_STR_LENGTH       200

    uint8_t     buffer[CMD_PRINTF_MAX_STR_LENGTH];  /* max bytes */
    va_list     arg = NULL;
    uint16_t    usndone;
    uint16_t    send_length;
    uint8_t *   p_send_buffer;

    #ifdef __CA78K0R__
    /* Parse the argument list, print to buffer string */
    va_starttop(arg, format);
    #endif

    #ifdef __CCRL__
    va_start(arg, format);
    #endif

    /* Format the string */
    usndone = vsprintf((char *)buffer, (const char *)format, arg);
    buffer[CMD_PRINTF_MAX_STR_LENGTH-1] = 0;    /* Terminal string to prevent un-expected error */

    /* Send string */
    p_send_buffer = buffer;
    send_length = strlen((const char *)buffer);
    R_WDT_Restart();
    while (send_length > 0)
    {
        TXD0 = *p_send_buffer;
        while(SSR00 & 0x0040);

        R_WDT_Restart();

        p_send_buffer++;
        send_length--;
    }
    R_WDT_Restart();

    va_end(arg);
}
#else
#define printf_uart0              {;}
#endif /* #if (POWERMGMT_ENABLE_DEBUG_PRINT == TRUE) */

static void powermgmt_capture_rtc_calendar_counter_to_EventArgs(void)
{
    rtc_counter_value_t rtctime;
    
    R_RTC_Get_CalendarCounterValue(&rtctime);

    EventArgs.data.captured_time.Sec    = WRP_EXT_Bcd2Dec(rtctime.sec);
    EventArgs.data.captured_time.Min    = WRP_EXT_Bcd2Dec(rtctime.min);
    EventArgs.data.captured_time.Hour   = WRP_EXT_Bcd2Dec(rtctime.hour);
    EventArgs.data.captured_time.Day    = WRP_EXT_Bcd2Dec(rtctime.day);
    EventArgs.data.captured_time.Week   = WRP_EXT_Bcd2Dec(rtctime.week);
    EventArgs.data.captured_time.Month	= WRP_EXT_Bcd2Dec(rtctime.month);
    EventArgs.data.captured_time.Year   = WRP_EXT_Bcd2Dec(rtctime.year);
}

#if (POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE)
/******************************************************************************
* Function Name : standby_dsad_callback
* Interface     : static void standby_dsad_callback(void)
* Description   :
* Arguments     : None
* Return Value  : None
******************************************************************************/
static void NEAR_PTR standby_dsad_callback(void)
{
    EM_STANDBY_ADCInterruptCallback(g_wrp_adc_samples.i1, g_wrp_adc_samples.i2);
}

/******************************************************************************
* Function Name : POWERMGMT_SetSamplingInterval
* Interface     : static void POWERMGMT_SetSamplingInterval(void)
* Description   :
* Arguments     : None
* Return Value  : None
******************************************************************************/
PWR_FUNC static void POWERMGMT_SetSamplingInterval(uint8_t sec)
{
    uint16_t i;
    rtc_counter_value_t current_time;
    rtc_alarm_value_t setting_time;
    uint8_t set_new_time = FALSE;

    if ( (sec >= 1) && (sec <= 60) ) 
    {
        memset(&setting_time, 0, sizeof(rtc_counter_value_t));
        memset(&setting_time, 0, sizeof(rtc_alarm_value_t));

        R_RTC_Get_CalendarCounterValue(&current_time);

        /* Special case when setting 60s
        * If set the alarm time seconds equal to current seconds,
        * The interrupt for alarm will raise, making the interrupt duplicate
        */
        if (sec == 60) {
            if (g_powermgmt_standby_control.interval != sec) {
                /* Wait a while (>1s) */
                for (i = 0; i < 25; i++)
                {
                    MCU_Delay(50000);
                }
                setting_time.alarmws = current_time.sec;
                set_new_time = TRUE;
            }
        }
        else {
            /* Add next few seconds */
            setting_time.alarmws = WRP_EXT_Bcd2Dec(current_time.sec) + sec;
            setting_time.alarmws %= 60;
            setting_time.alarmws = WRP_EXT_Dec2Bcd(setting_time.alarmws);
            set_new_time = TRUE;
        }

        if (set_new_time == TRUE) {
            R_RTC_Set_CalendarAlarm0Value(setting_time);
			R_RTC_Set_CalendarAlarm0On(1);
        }
        g_powermgmt_standby_control.interval = sec;
    }
}

/******************************************************************************
* Function Name : POWERMGMT_StandBy_Calculate
* Interface     : static void POWERMGMT_StandBy_Calculate(void)
* Description   :
* Arguments     : None
* Return Value  : None
******************************************************************************/
PWR_FUNC static void POWERMGMT_StandBy_Calculate(void)
{
    float32_t power;
    EM_CALIBRATION calib = EM_GetCalibInfo();
    uint16_t i;

    standby_start();

    /* Debug only */
    #if (POWERMGMT_ENABLE_DEBUG_PRINT == 1)
    /* Turn on UART0 */
    SAU0EN = 1U;
    R_UART0_Create();
    R_UART0_SetBaudRate(POWERMGMT_DEBUG_PRINT_BAUDRATE);
    R_UART0_Start();

    /* Calculation time measurement timer */
    TAU0EN = 1U;
    LOADTEST_TAU_Init();
    LOADTEST_TAU_SetCKM0Divider(_0004_TAU_CKM0_fCLK_4);

    LOADTEST_TAU_Start();
    #endif /* #if (POWERMGMT_ENABLE_DEBUG_PRINT == 1) */
    
    g_wrp_adc_basic_signal_ready_cb_and_return = standby_dsad_callback;
    power = EM_STANDBY_CalculatePowerAndSignals(
        EM_SW_PROPERTY_OPERATION_DEFAULT_NM_VOLTAGE,
        calib.coeff.i1rms,
        calib.coeff.i2rms
    );
    
    #if (POWERMGMT_ENABLE_DEBUG_PRINT == 1)
    LOADTEST_TAU_Stop();
    #endif
    
    #if (POWERMGMT_STANDBY_CALCULATE_ENABLE_DELAY == TRUE)
    for (i = 0; i < POWERMGMT_STANDBY_DELAY_CYCLE_OF_CALCULATION; i++)
    {
        power = EM_STANDBY_CalculatePowerAndSignals(
            EM_SW_PROPERTY_OPERATION_DEFAULT_NM_VOLTAGE,
            calib.coeff.i1rms,
            calib.coeff.i2rms
        );
    }
    #endif /* #if (POWERMGMT_STANDBY_CALCULATE_ENABLE_DELAY == TRUE) */
    g_wrp_adc_basic_signal_ready_cb_and_return = NULL;

    /* In case not need pulse output, stop immediately to save power */
    standby_stop();
    
    /* Add energy to current tariff if greater than preset power */
    if (power >= EM_SW_PROPERTY_OPERATION_NM_POWER_THRESHOLD)
    {
        float32_t irms = (EM_STANDBY_GetCurrent1() >= EM_STANDBY_GetCurrent2()) ? \
                            EM_STANDBY_GetCurrent1() :\
                            EM_STANDBY_GetCurrent2();
        POWERMGMT_SetSamplingInterval(POWERMGMT_STANDBY_INTERVAL_HIGH);
        R_BLOCKLOAD_AddSampleOfStandbyMode(EM_SW_PROPERTY_OPERATION_DEFAULT_NM_VOLTAGE);
        /* Update energy to system */
        R_INST_UpdateEnergyByPowerAndTime(power, g_powermgmt_standby_control.interval);

        /* Logging need access EEPROM */
        eeprom_enable();
        
        /* NeutralMissing occur */
        if (g_event_state.neutral_missing.current_state == EVENT_STATE_RELEASE) 
        {
            /* Assert event */
            EVENT_NeutralMissing(EVENT_STATE_ENTER);
            
            /* Log event with custom parameters to EventArgs
            *       current RTC calendar counter, 
            *       default neutral missing voltage, 
            *       calculated standby irms, 
            *       PF 1 UNITY
            */
            powermgmt_capture_rtc_calendar_counter_to_EventArgs();
            EventArgs.data.voltage 			    = EM_SW_PROPERTY_OPERATION_DEFAULT_NM_VOLTAGE;
            EventArgs.data.ActiveEnergyImport   = R_TARIFF_GetImportActiveEnergyTotal();
            EventArgs.data.current              = irms;
            EventArgs.data.PF                   = 1;
            EVENT_Logging();
            
            /* Backup event state to prevent reset during sleep */
            EVENT_StorageBackup();
        }
        else {
            /* Same state, not assert event */
        }
    
        R_HANDLER_MeterWakeup();
        
        /* Backup processed state of applications */
        STORAGE_Backup(STORAGE_ITEM_SYS_STATE);
    }
    else
    {
        POWERMGMT_SetSamplingInterval(POWERMGMT_STANDBY_INTERVAL_LOW);
    }

    eeprom_disable();

    /* Debug only */
    #if (POWERMGMT_ENABLE_DEBUG_PRINT == 1)
    {
        uint16_t diff;
        float32_t calculation_time;
        float32_t kwh;
        rtc_counter_value_t rtctime;
        
        printf_uart0("\n\r");
        
        diff = LOADTEST_TAU_Diff();
        calculation_time = ((
                                ((float)diff * (float)(LOADTEST_TAU_GetCKM0Divider(0))) /
                                (float)(LOADTEST_CGC_GetClock())
                             ) / 1000.0f) * 1e6;
                             
        printf_uart0(">> Calculation time = %f (us)\n\r", calculation_time);
            
        printf_uart0(">> Measured power = %f\n\r", power);
        printf_uart0(">> Current 1      = %f\n\r", EM_STANDBY_GetCurrent1());
        printf_uart0(">> Current 2      = %f\n\r", EM_STANDBY_GetCurrent2());
        printf_uart0(">> Total sample   = %d\n\r", EM_STANDBY_GetTotalSample());
        
        eeprom_enable();
        kwh = R_TARIFF_GetImportActiveEnergyTotal();
        eeprom_disable();
        printf_uart0(">> KWh Counter    = %f\n\r", kwh);

        printf_uart0(">> Neutral missing state = %s \n\r", (g_event_state.neutral_missing.current_state == EVENT_STATE_ENTER) ? "Entered" : "Released" );
        
        /* Display current time for interval checking */
        R_RTC_Get_CalendarCounterValue(&rtctime);
        printf_uart0(">> Current time: %02x:%02x:%02x \n\r", rtctime.hour, rtctime.min, rtctime.sec);
        
        LOADTEST_TAU_DeInit();
    }
    #endif /* #if (POWERMGMT_ENABLE_DEBUG_PRINT == 1) */

    /* The started peripheral will be turn off in mode process again */
}
#endif /* POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE */

/******************************************************************************
* Function Name : POWERMGMT_SWDelayFor3Seconds
* Interface     : static void POWERMGMT_SWDelayFor3Seconds(void)
* Description   : Delay for 3 seconds in fIL clock (~15kHz) then switch back to fIH clock
* Arguments     : None
* Return Value  : None
******************************************************************************/
PWR_FUNC static void POWERMGMT_SWDelayFor3Seconds(void)
{
    uint16_t count;

    /* This delay assume that fSUB is selected as CPU clock before calling,
     * else, this will not function correctly
     * Which one is using as fSUB:
     * SELLOSC = 0: fSX (~32kHz)
     * SELLOSC = 1: fIL (~15kHz)
    */
    {
        R_CGC_FclkUseFsub();
        count = 5000;
    }

    #if 0
    /* If need to use fIL as HOCO clock */
    {
        R_CGC_FclkUseFil();
        count = 2500;
    }
    #endif

    /* Wait 3s */
    while(count > 0)
    {
        count--;
        R_WDT_Restart();
    }

    /* Switch to normal clock */
    R_CGC_FclkUseFih();
}

/******************************************************************************
* Function Name : POWERMGMT_DisplayLCDDebugSign
* Interface     : static void POWERMGMT_DisplayLCDDebugSign(void)
* Description   : Display Sign on LCD for debug purpose
* Arguments     : None
* Return Value  : None
******************************************************************************/
PWR_FUNC static void POWERMGMT_DisplayLCDDebugSign(void)
{
    #if (POWERMGMT_DISPLAY_LCD_DEBUG_SYMBOL == TRUE)
    if (g_powermgmt_is_lvdvdd_first == 0) { LCD_DisplaySpSign(S_BILL); }
    if (g_reset_flag & 0x01) { LCD_DisplaySpSign(S_DATE); }
    if (g_reset_flag & 0x10) { LCD_DisplaySpSign(S_TIME); }
    if (g_reset_flag & 0x02) { LCD_DisplaySpSign(S_EARTH);}
    if (g_reset_flag & 0x04) { LCD_DisplaySpSign(S_REV); }
    #endif /* POWERMGMT_DISPLAY_LCD_DEBUG_SYMBOL == TRUE */
}

/******************************************************************************
* Function Name : POWERMGMT_DisplayLCDParams
* Interface     : static void POWERMGMT_DisplayLCDParams(float32_t kwh);
* Description   : Display KWh when CPU wake up in STOP mode
* Arguments     : float32_t kwh : KWh counter
* Return Value  : None
******************************************************************************/
PWR_FUNC static void POWERMGMT_DisplayLCDParams(float32_t kwh)
{
    LCD_ClearAll();

    /* Display measured value */
    LCD_DisplayFloat(kwh);

    /* Display "kWh" sign */
    LCD_DisplaySpSign(S_34);
    LCD_DisplaySpSign(S_35);
    LCD_DisplaySpSign(S_36);
    LCD_DisplaySpSign(S_37);
    LCD_DisplaySpSign(S_40);
    
    /* display HR */
     LCD_DisplaySpSign(S_9C);
 LCD_DisplaySpSign(S_9B);
 LCD_DisplaySpSign(S_9E);
 LCD_DisplaySpSign(S_9F);
 LCD_DisplaySpSign(S_9G1);
 LCD_DisplaySpSign(S_9G2);
 LCD_DisplaySpSign(S_10A);
 LCD_DisplaySpSign(S_10B);
 LCD_DisplaySpSign(S_10E);
 LCD_DisplaySpSign(S_10F);
 LCD_DisplaySpSign(S_10G1);
 LCD_DisplaySpSign(S_10G2);
 LCD_DisplaySpSign(S_10K);

    /* For debug purpose, not used when release */
    POWERMGMT_DisplayLCDDebugSign();

    POWERMGMT_SWDelayFor3Seconds();

    LCD_ClearAll();
}

/******************************************************************************
* Function Name : POWERMGMT_DisplayLCDError
* Interface     : static void POWERMGMT_DisplayLCDError(float32_t code)
* Description   : Display error code on LCD for debug purpose
* Arguments     : float32_t code : error code
* Return Value  : None
******************************************************************************/
PWR_FUNC static void POWERMGMT_DisplayLCDError(float32_t code)
{
    LCD_ClearAll();

    /* Display error code */
    LCD_DisplayFloat(code);

    /* For debug purpose, not used when release */
    POWERMGMT_DisplayLCDDebugSign();

    POWERMGMT_SWDelayFor3Seconds();

    LCD_ClearAll();
}

PWR_FUNC static powermgmt_mode_t powermgmt_switch_mode1_mode4(void)
{
    EM_Stop();
    
    /* PowerFail occur */
    if (g_event_state.power_failed.current_state == EVENT_STATE_RELEASE)
    {
        /* Assert event */
        EVENT_PowerFail(EVENT_STATE_ENTER);
        /* Log event with last sync snapshot to EventArgs */
        EVENT_Logging();
        /* Backup event state to prevent reset during sleep */
        EVENT_StorageBackup();
        /* Abnormal handling before sleep (release-->occur) to backup the last snapshot */
        R_HANDLER_BeforeMeterSleep();
    }
    else {
        /* Same state, not assert event */
    }
    
    /* Backup system states and DLMS data */
    STORAGE_Backup(STORAGE_ITEM_SYS_STATE | STORAGE_ITEM_DLMS);
    
    /* clear all the flag */
    g_powermgmt_flag.is_alarm_int     = 0;

    /* clear external event flag */
    g_intp_case_open_flag = 0;
    
    #if (POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE)
    EM_STANDBY_Start();
    g_powermgmt_standby_control.delay_release_count = 0;
    /* First using interval that greater than threshold */
    POWERMGMT_SetSamplingInterval(POWERMGMT_STANDBY_INTERVAL_HIGH);
    #endif /* POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE */

    stop_peripheral();
    
    /* Stop clock supply to all peripherals */
    PER0 = 0x00U;
    PER1 = 0x00U;
    PER2 = 0x00U;
    
    R_WDT_Restart();
    
    return POWERMGMT_MODE4;
}

PWR_FUNC static powermgmt_mode_t powermgmt_switch_mode3_mode4(void)
{
    stop_peripheral();
    
    /* Stop clock supply to all peripherals */
    PER0 = 0x00U;
    PER1 = 0x00U;
    PER2 = 0x00U;
    
    R_WDT_Restart();
    
    return POWERMGMT_MODE4;
}

PWR_FUNC static powermgmt_mode_t powermgmt_switch_mode4_mode1(void)
{
    /* Stop standby and do storage backup to save accumulated energy */
    #if (POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE)
    /* Release the standby mode */
    EM_STANDBY_Stop();
    R_RTC_Set_Alarm0Off();
    
    /* Do a storage backup to store energy accumulated during sleep (if any) */
    eeprom_enable();
    STORAGE_Backup(STORAGE_ITEM_SYS_STATE);
    eeprom_disable();

    /* Do a release in case neutral missing detected */
    g_powermgmt_standby_control.delay_release_count = POWERMGMT_STANDBY_DELAY_RELEASE_EVENT * 2;

    #endif /* POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE */
    
    /* Do startup flow */
    R_Systeminit();
    em_startup();

    /* Start peripheral + application */
    start_peripheral_and_app();

    R_HANDLER_MeterWakeup();

    /* PowerFail release */
    if (g_event_state.power_failed.current_state == EVENT_STATE_ENTER)
    {
        /* Assert event */
        EVENT_PowerFail(EVENT_STATE_RELEASE);
        /* Log event with custom parameters to EventArgs: captured time (next polling may not yet sync snapshot to EventArgs) */
        powermgmt_capture_rtc_calendar_counter_to_EventArgs();
        /* Logging done in mode1 (next polling) */
    }
    else {
        /* Same state, not assert event */
    }
    
    R_WDT_Restart();
    
    return POWERMGMT_MODE1;
}

PWR_FUNC static powermgmt_mode_t powermgmt_switch_mode4_mode3(void)
{
    /* Turn on VRTC, will be turn off in mode4 */
    VRTCEN = 1U;

    /* Process the key interrupt */
    if (KEY_IsUpPressed() == 1 && g_powermgmt_flag.is_alarm_int != 1)
    {
        float32_t energy;

        /* Supply power to EEPROM for reading the total tariff energy */
        eeprom_enable();

        energy = R_TARIFF_GetImportActiveEnergyTotal();

        /* Turn off supply to EEPROM to save power, not wait until transition to mode4 again */
        eeprom_disable();

        /* Turn on LCD to display energy information */
        R_LCD_PowerOn(0);
        POWERMGMT_DisplayLCDParams(energy);
        R_LCD_PowerOff();

        /* Call KeyPollingProcessing to acknowledge the flag */
        KEY_PollingProcessing();
        
        eeprom_enable();
    }

    /* Process the cover interrupt */
    if (g_intp_case_open_flag == 1)
    {
        /* CaseOpen occur */
        if (g_event_state.case_open.current_state == EVENT_STATE_RELEASE)
        {
            /* Only log event if having VDD or VBAT not low */
            eeprom_enable();

            /* Assert event */
            EVENT_CaseOpen(EVENT_STATE_ENTER);
            /* Log event with custom parameters to EventArgs: captured time */
            powermgmt_capture_rtc_calendar_counter_to_EventArgs();
            EVENT_Logging();
            /* Backup event state to prevent reset during sleep */
            EVENT_StorageBackup();
                
            eeprom_disable();
        }
        else {
            /* Same state, not assert event */
        }

        g_intp_case_open_flag = 0;
    }

    /* Process standby mode */
    if (g_powermgmt_flag.is_alarm_int == 1)
    {
        #if (POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE)
        POWERMGMT_StandBy_Calculate();
        #endif /* POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE */
        g_powermgmt_flag.is_alarm_int = 0;
    }
    
    R_WDT_Restart();
    
    return POWERMGMT_MODE3;
}

/******************************************************************************
* Function Name : POWERMGMT_PollingProcessing
* Interface     : void POWERMGMT_PollingProcessing(void)
* Description   : Polling process for power modes
* Arguments     : None
* Return Value  : None
******************************************************************************/
PWR_FUNC void POWERMGMT_PollingProcessing(void)
{
    #ifdef POWER_MANAGEMENT_ENABLE

    switch (g_powermgmt_current_mode)
    {
        case POWERMGMT_MODE1:
            if (POWERMGMT_DIRECT_IS_EXLVD_LOW() == 1)
            {
                g_powermgmt_current_mode = powermgmt_switch_mode1_mode4();
            }
            else
            {
                /* Check for power switch if turn on when power low for short duration */
                if (POWER_SW == 0)
                {
                    /* Turn it off to conserve power */
                    POWER_SW = 1;
                }
            }
            break;
        case POWERMGMT_MODE3:
            /* After process_mode3, go back to mode4 */
            {
                g_powermgmt_current_mode = powermgmt_switch_mode3_mode4();
            }
            break;
        case POWERMGMT_MODE4:
            if (POWERMGMT_DIRECT_IS_EXLVD_LOW() == 0)
            {
                g_powermgmt_current_mode = powermgmt_switch_mode4_mode1();
            }
            else
            {
                if( KEY_IsUpPressed() == 1 ||
                    g_intp_case_open_flag == 1 ||
                    g_powermgmt_flag.is_alarm_int == 1)
                {
                    g_powermgmt_current_mode = powermgmt_switch_mode4_mode3();
                }
                else
                {
                    //Stay in mode 4
                }
            }
            break;
        default:
            g_powermgmt_current_mode = POWERMGMT_MODE1;
            break;
    }
    
    if (g_powermgmt_current_mode == POWERMGMT_MODE4)
    {
        /* Before going to sleep, check again if either VDD or EXLVD low */
        if (POWERMGMT_DIRECT_IS_EXLVD_LOW() == 1)
        {
            /* Going to sleep mode */
            NOP();
            NOP();
            NOP();
            STOP();
            NOP();
            NOP();
            NOP();
            R_WDT_Restart();
        }
        else
        {
            /* Both VDD and EXLVD not low, should return to state check */
        }
    }

    #endif /* POWER_MANAGEMENT_ENABLE */
}

/***********************************************************************************************************************
* Function Name : POWERMGMT_GetMode
* Interface     : powermgmt_mode_t POWERMGMT_GetMode(void)
* Arguments     : None
* Return Value  : powermgmt_mode_t: Current power management mode
***********************************************************************************************************************/
PWR_FUNC powermgmt_mode_t POWERMGMT_GetMode(void)
{
    #ifdef POWER_MANAGEMENT_ENABLE
    return g_powermgmt_current_mode;
    #else
    return POWERMGMT_MODE1;
    #endif /* POWER_MANAGEMENT_ENABLE */
}

/***********************************************************************************************************************
* Function Name : POWERMGMT_SetMode
* Interface     : uint8_t POWERMGMT_SetMode(void)
* Description   : Set current power management mode
* Arguments     : powermgmt_mode_t: Current power management mode to set
* Return Value  : None
***********************************************************************************************************************/
PWR_FUNC void POWERMGMT_SetMode(powermgmt_mode_t mode)
{
    #ifdef POWER_MANAGEMENT_ENABLE
    /* Check input parameter */
    if (mode < POWERMGMT_MODE1 || mode > POWERMGMT_MODE4)
    {
        return; /* Do nothing */
    }

    g_powermgmt_current_mode = mode;
    #endif /* POWER_MANAGEMENT_ENABLE */
}

/******************************************************************************
* Function Name : POWERMGMT_VDD_InterruptCallback
* Interface     : void POWERMGMT_VDD_InterruptCallback(void)
* Description   : Callback function which is registered into LVDEXLVD ISR
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
PWR_FUNC void POWERMGMT_VDD_InterruptCallback(void)
{
    if(POWERMGMT_DIRECT_IS_VDD_LOW() == 0)
    {
        g_powermgmt_flag.is_vdd_low = 0;
    }
    else
    {
        g_powermgmt_flag.is_vdd_low = 1;
    }
}

/******************************************************************************
* Function Name : POWERMGMT_AC_InterruptCallback
* Interface     : void POWERMGMT_AC_InterruptCallback(void)
* Description   : Callback function which is registered into LVDEXLVD ISR
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
PWR_FUNC void POWERMGMT_AC_InterruptCallback(void)
{
    if(POWERMGMT_DIRECT_IS_EXLVD_LOW() == 0)
    {
        g_powermgmt_flag.is_ac_low = 0;
    }
    else
    {
        g_powermgmt_flag.is_ac_low = 1;
        /* Quickly turn on power switch before power failed below MCU running threshold*/
        POWER_SW = 0;
    }
}

/******************************************************************************
* Function Name : POWERMGMT_RTC_Periodic_InterruptCallback
* Interface     : void POWERMGMT_RTC_Periodic_InterruptCallback(void)
* Description   : Callback from RTC Periodic ISR to power management
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
PWR_FUNC void POWERMGMT_RTC_Periodic_InterruptCallback(void)
{
    #if (POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE)
    /* Delay count to release neutral missing event */
    if (g_powermgmt_standby_control.delay_release_count > 0) {
        g_powermgmt_standby_control.delay_release_count--;
        if (g_powermgmt_standby_control.delay_release_count == 0) {
            if (g_event_state.neutral_missing.current_state == EVENT_STATE_ENTER) 
            {
                /* Assert event */
                EVENT_NeutralMissing(EVENT_STATE_RELEASE);
                /* EventArgs synced to snapshot, Logging done in mode1 (next polling) */
            } 
            else {
                /* Same state, not assert event */
            }
        }
    }
    #endif /* POWER_MANGEMENT_STANDBY_PROCESSING_ENABLE == TRUE */

    g_powermgmt_flag.is_rtc_int = 1;
}

/******************************************************************************
* Function Name : POWERMGMT_RTC_Alarm_InterruptCallback
* Interface     : void POWERMGMT_RTC_Alarm_InterruptCallback(void)
* Description   : Callback from RTC alarm ISR to power management
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
PWR_FUNC void POWERMGMT_RTC_Alarm_InterruptCallback(void)
{
    g_powermgmt_flag.is_alarm_int = 1;
}
