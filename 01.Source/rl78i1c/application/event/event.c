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
* File Name    : event.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CubeSuite Version 1.5d
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Event processing source File
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"   /* CG Macro Driver */
#include "r_cg_rtc.h"           /* CG RTC Driver */
#include "r_cg_wdt.h"

#include <math.h>

/* Wrapper/User */
#include "wrp_app_ext.h"

/* MW/Core */
#include "em_core.h"        /* EM Core APIs */
//#include "em_event.h"
#include "em_display.h"

/* Application */
#include "platform.h"
#include "storage.h"        /* Storage Header File */
#include "event.h"          /* Event Header File */
//#include "powermgmt.h"      /* Power Management Header File */
#include <string.h>         /* String Standard Lib */
#include "r_lcd_display.h"
#include "r_meter_format.h"
#include "r_scheduler.h"    /* Scheduler */
#include "inst_read.h"
#include "r_tariff.h"
#include "key.h"
#include "r_load_ctrl.h"

/* Bootloader */
//#include "bl_image.h"

#include "relay.h"

/* DLMS Event */
#ifdef _DLMS
#include "r_dlms_event.h"
#include "r_dlms_push.h"
#include "r_dlms_config.h"
#include "r_dlms_tcp_wrapper_interface.h"
#include "r_dlms_udp_wrapper_interface.h"
#endif

/******************************************************************************
Macro definitions
******************************************************************************/
/* Common */
#define MAX(x, y)   ((x) < (y) ? (   y) : (x))  /* Get max value */



#define ROLLOVER_PROFILE                (TRUE)
#define NON_ROLLOVER_PROFILE            (FALSE)

/* EEPROM Storage mapping */
#define EVENT_EEPROM_BACKUP_EVENT_STATE_ADDR            (STORAGE_EEPROM_EVENT_LOG_EVENT_STATE_ADDR)
#define EVENT_EEPROM_BACKUP_EVENT_TAMPER_COUNTER_ADDR   (STORAGE_EEPROM_EVENT_LOG_TAMPER_COUNTER_ADDR)
#define EVENT_EEPROM_BACKUP_EVENT_TABLE_HEADER_ADDR     (STORAGE_EEPROM_EVENT_LOG_TABLE_INFO_ADDR)


#define EVENT_CHECK_TAMPER_UPDATING_MODE(mode, power, current_state, o_mode, o_power) {     \
    if (mode == EVENT_TAMPER_UPDATE_BY_SPECIFIED_POWER) {                                   \
        if (current_state == EVENT_STATE_ENTER) {                                           \
            o_mode = EVENT_TAMPER_UPDATE_BY_SPECIFIED_POWER;                                \
            if (o_power < power) {                                                          \
                o_power = power;                                                            \
            }                                                                               \
        }                                                                                   \
    }                                                                                       \
}

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct tagComnPersistentTime
{
    /* EM */
    /* ENERGY monitoring */
    uint8_t   comn_remove_occur;            /* Comn module removal occurred*/
    uint8_t   comn_remove_restore;          /* Comn module removal restored*/

} COMN_PERSISTENT_TIME;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
/* Import from wrp_em_adc.c */
extern volatile uint8_t g_dc_immunity_state;
/* Import from inst_read.c */
extern float32_t g_inst_read_fixed_power_output_value;
extern uint8_t g_inst_read_is_fixed_power_output;

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/
/* Variables */
float32_t g_event_overload_threshold;

EVENT_INFO g_event_state;
EVENT_FLAG g_event_flag;
EVENT_REQUEST_FLAG g_event_request_flag;
EVENT_ARGS_T EventArgs;

EVENT_PERSISTENT_TIME g_event_persistent_time = 
{
  /* EM */
    /* ENERGY monitoring */
    1, /* Low Voltage Occurred */
    1, /* Low Voltage Restored*/
    1, /* Over Voltage Occurred*/
    1, /* Over Voltage Restored*/
    1, /* Over Current Occurred*/
    1, /* Over Current Restored*/
    1, /* Current Reverse Occured*/
    1, /* Current Reverse Restored*/
    1, /* Overload Occurred*/
    1, /* Overload Restored*/
    1, /* Frequency out of range */
    1, /* Low power factor Occurred*/
    1, /* Low power factor Restored*/

    /* ENERGY tamper */
    1, /* Neutral missing Occurred */
    1, /* Neutral missing Restored*/
    1, /* Earth Connected Occurred*/
    1, /* Earth Connected Restored*/
    1, /* DC detection Occurred*/
    1, /* DC detection Restored*/

    /* Power management */
    1, /* Power Failures Occurred */
    1, /* Power Failures Restored*/
    1, /* Case open */
    1, /* Magnetic Occurred*/
    1 /* Magnetic Restored*/

};

COMN_PERSISTENT_TIME g_comn_persistent_time = 
{
    1,  /* Comn module removal occurred*/
    1   /* Comn module removal restored*/

}; //TODO

RELAY_PERSISTENT_TIME g_relay_persistent_time =
{
    1,  /* Relay Disconnect */
    1   /* Relay Reconnect */

}; //TODO

uint32_t    g_tamper_counter;

static EVENT_PLUGIN_CALLBACK gp_event_plugin_callback[1];
const uint8_t gp_event_plugin_callback_size = sizeof(gp_event_plugin_callback)/sizeof(EVENT_PLUGIN_CALLBACK);

static EventTableHeader_t gEventTableHeaders[] =
{
/* StartPosistion , EntriesInUse */
    {      0         ,     0         },
    {      0         ,     0         },
    {      0         ,     0         },
    {      0         ,     0         },
    {      0         ,     0         },
    {      0         ,     0         },
    {      0         ,     0         },
};

static const EventTableConfig_t gEventTableConfigs[] = 
{
/* EEPROM Table Start Address                  EEPROM Max entries                 Is Roll Over?          (Size of 1 record)             */
/* E.g.                                                                                                                                 */
/*  0x059E                                      50                                 TRUE                     64                          */
    {STORAGE_EEPROM_EVENT_LOG_VOLTAGE_ADDR      , VOLTAGE_EVENTS_MAX_ENTRIES       , ROLLOVER_PROFILE      , sizeof(EVENT_PARAMS_T      )},
    {STORAGE_EEPROM_EVENT_LOG_CURRENT_ADDR      , CURRENT_EVENTS_MAX_ENTRIES       , ROLLOVER_PROFILE      , sizeof(EVENT_PARAMS_T      )},
    {STORAGE_EEPROM_EVENT_LOG_POWER_ADDR        , POWER_EVENTS_MAX_ENTRIES         , ROLLOVER_PROFILE      , sizeof(EVENT_PARAMS_SHORT_T)},
    {STORAGE_EEPROM_EVENT_LOG_TRANSACTION_ADDR  , TRANS_EVENTS_MAX_ENTRIES         , ROLLOVER_PROFILE      , sizeof(EVENT_PARAMS_SHORT_T)},
    {STORAGE_EEPROM_EVENT_LOG_OTHER_ADDR        , OTHER_EVENTS_MAX_ENTRIES         , ROLLOVER_PROFILE      , sizeof(EVENT_PARAMS_T      )},
    {STORAGE_EEPROM_EVENT_LOG_NONROLLOVER_ADDR  , NON_ROLLOVER_EVENTS_MAX_ENTRIES  , NON_ROLLOVER_PROFILE  , sizeof(EVENT_PARAMS_SHORT_T)},
    {STORAGE_EEPROM_EVENT_LOG_CONTROL_ADDR      , CONTROL_EVENTS_MAX_ENTRIES       , ROLLOVER_PROFILE      , sizeof(EVENT_PARAMS_SHORT_T)},
};

/******************************************************************************
Private global variables and functions
******************************************************************************/

void  EVENT_ExtractDataForLogging(
    EVENT_ARGS_T *pEventArgsData
);

uint8_t EVENT_DetermineEventStatus(
        uint8_t               condition,
        EVENT_ONE_EVENT_TICK *pEventStatus,
        uint8_t               event_persistent_time_occur ,
        uint8_t               event_persistent_time_restore
);

/******************************************************************************
* Function Name : EVENT_RegisterPluginCallback
* Interface     : void EVENT_RegisterPluginCallback(uint8_t slot, EVENT_PLUGIN_CALLBACK p_fn_callback)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void EVENT_RegisterPluginCallback(uint8_t slot, EVENT_PLUGIN_CALLBACK p_fn_callback)
{
    gp_event_plugin_callback[slot] = p_fn_callback;
}

/******************************************************************************
* Function Name : EVENT_FowardToPluginFn
* Interface     : void EVENT_FowardToPluginFn(EVENT_ARGS_T *pEvent_arg)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void EVENT_FowardToPluginFn(EVENT_ARGS_T *pEvent_arg)
{
    uint8_t i;
    for (i = 0; i < gp_event_plugin_callback_size; i++)
    {
        if (gp_event_plugin_callback[i] != NULL)
        {
            gp_event_plugin_callback[i](pEvent_arg);
        }
    }
}

/******************************************************************************
* Function Name : EVENT_IsNotifyConnectionEstablished
* Interface     : uint8_t EVENT_IsNotifyConnectionEstablished(void)
* Description   : Return state of TCP/UPD connection
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t EVENT_IsNotifyConnectionEstablished(void)
{
#if defined(__DEBUG)
    return TRUE;
#elif defined (_DLMS)
#if SUPPORT_UDP_PROFILE
    /* UDP */
    return R_UDP_WRP_IsConnected();
#else
    /* TCP */
    return R_TCP_WRP_IsConnected();
#endif
#else
    return TRUE;
#endif
}

/******************************************************************************
* Function Name : EVENT_IsLastGasp
* Interface     : uint8_t EVENT_IsLastGasp(void)
* Description   : Polling check lasp gasp
* Arguments     : None
* Function Calls: None
* Return Value  : uint8_t, 0 is not happen, 1 is happen
******************************************************************************/
uint8_t EVENT_IsLastGasp(void)
{
    return FALSE;//TODO (g_event_state.voltage_sag == EVENT_STATE_ENTER);
}

/******************************************************************************
* Function Name : EVENT_IsCurrentReversed
* Interface     : uint8_t EVENT_IsCurrentReversed(void)
* Description   : Check state of current reversed event
* Arguments     : None
* Function Calls: None
* Return Value  : uint8_t, 0 is not happen, 1 is happen
******************************************************************************/
uint8_t EVENT_IsCurrentReversed(void)
{
    return (g_event_state.cur_rev.current_state == EVENT_STATE_ENTER);
}

/******************************************************************************
* Function Name : EVENT_IsNeutralMissingHappen
* Interface     : uint8_t EVENT_IsNeutralMissingHappen(void)
* Description   : Polling check neutral missing status
* Arguments     : None
* Function Calls: None
* Return Value  : uint8_t, 0 is not happen, 1 is happen
******************************************************************************/
uint8_t EVENT_IsNeutralMissingHappen(void)
{
    return (g_event_state.neutral_missing.current_state == EVENT_STATE_ENTER);
}

/******************************************************************************
* Function Name : EVENT_IsEarthLoad
* Interface     : uint8_t EVENT_IsEarthLoad(void)
* Description   : Polling check earth load
* Arguments     : None
* Function Calls: None
* Return Value  : uint8_t, 0 is not happen, 1 is happen
******************************************************************************/
uint8_t EVENT_IsEarthLoad(void)
{
    return (g_event_state.earth_load.current_state == EVENT_STATE_ENTER);
}

/******************************************************************************
* Function Name : EVENT_IsCaseOpen
* Interface     : uint8_t EVENT_IsCaseOpen(void)
* Description   : Polling check case open
* Arguments     : None
* Function Calls: None
* Return Value  : uint8_t, 0 is not happen, 1 is happen
******************************************************************************/
uint8_t EVENT_IsCaseOpen(void)
{
    return (g_event_state.case_open.current_state == EVENT_STATE_ENTER);
}

/******************************************************************************
* Function Name : EVENT_IsMagnetic
* Interface     : uint8_t EVENT_IsMagnetic(void)
* Description   : Polling check magnetic
* Arguments     : None
* Function Calls: None
* Return Value  : uint8_t, 0 is not happen, 1 is happen
******************************************************************************/
uint8_t EVENT_IsMagnetic(void)
{
    return (g_event_state.magnet.current_state == EVENT_STATE_ENTER);
}

/******************************************************************************
* Function Name    : void EVENT_NeutralMissing(EVENT_STATE_T state)
* Description      : Event Callback for Neutral missing
* Arguments        : EVENT_STATE_T state: OCCURED or RECOVERED
* Functions Called : None
* Return Value     : None
******************************************************************************/
void EVENT_NeutralMissing(EVENT_STATE_T state)
{
    g_event_flag.bits.is_neutral_missing = 1;
    g_event_state.neutral_missing.current_state = state;
}

/******************************************************************************
* Function Name    : void EVENT_PowerFail(EVENT_STATE_T state)
* Description      : Event Callback for Power Fail
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
void EVENT_PowerFail(EVENT_STATE_T state)
{
    g_event_flag.bits.is_power_failed = 1;
    g_event_state.power_failed.current_state = state;
}

/******************************************************************************
* Function Name    : void EVENT_CaseOpen(EVENT_STATE_T state)
* Description      : Event Callback for Case Open
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
void EVENT_CaseOpen(EVENT_STATE_T state)
{
    g_event_flag.bits.is_case_open = 1;
    g_event_state.case_open.current_state = state;
}

/******************************************************************************
* Function Name    : void EVENT_PowerOn(void)
* Description      : Event Callback for Power On
* Arguments        : None
* Functions Called : None
* Return Value     : None
******************************************************************************/
void EVENT_PowerOn(void)
{
    //g_event_flag.is_power_on = 1;

    /* If sag happened, then meter reset, sag won't be release, so trigger release sag on enough power */
    //TODO: Rechecked when having powermgmt if (POWERMGMT_IsVDDLow() != TRUE) {
    //  EVENT_EM_SagVoltage(EM_EVENT_CALLBACK_STATE_RELEASE);
    //}
}

/******************************************************************************
* Function Name : EVENT_IsAllEventProcessed
* Interface     : uint8_t EVENT_IsAllEventProcessed(void)
* Description   : Check whether all happened events are processed or not.
* Arguments     : None
* Function Calls: None
* Return Value  : uint8_t
******************************************************************************/
uint8_t EVENT_IsAllEventProcessed(void)
{
	/* EM process */
	if ( *((uint16_t *)&g_event_flag) != 0)
	{
		return FALSE;
	}
	/* ACK all is OK */
	return TRUE;
}

/******************************************************************************
* Function Name: void EVENT_DetermineEventStatus(void)
* Description  : Process to determine event status
* Arguments    : None
* Return Value : None
******************************************************************************/
uint8_t EVENT_DetermineEventStatus(uint8_t condition, EVENT_ONE_EVENT_TICK *pEventStatus, uint8_t event_persistent_time_occur, uint8_t event_persistent_time_restore)
{
	uint8_t change = FALSE;

    if (condition)
    {   
        if (pEventStatus->occurred_count <= event_persistent_time_occur) 
            { 
                pEventStatus->occurred_count++;
            }
        pEventStatus->restored_count = 0;                                                                                                   
    }
    else
    {
        if (pEventStatus->restored_count <= event_persistent_time_restore) 
            { 
                pEventStatus->restored_count++;
            }
        pEventStatus->occurred_count = 0;
    }                   

    if ((pEventStatus->occurred_count > event_persistent_time_occur) &&
        (pEventStatus->current_state ==  EVENT_STATE_RELEASE))                 
    {                                                                               
        pEventStatus->current_state = EVENT_STATE_ENTER;
		change = TRUE; 
        pEventStatus->restored_count = 0;
    }

    if ((pEventStatus->restored_count > event_persistent_time_restore) &&
        (pEventStatus->current_state ==  EVENT_STATE_ENTER))         
    {                                                                               
        pEventStatus->current_state = EVENT_STATE_RELEASE;
		change = TRUE;
        pEventStatus->occurred_count = 0;
    }

	return change;
}


/******************************************************************************
* Function Name : EVENT_ExtractDataForLogging
* Interface     : void EVENT_ExtractDataForLogging(EventArgs *pEventArgsData)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void EVENT_ExtractDataForLogging(EVENT_ARGS_T *pEventArgs)
{
    EM_PF_SIGN pf_sign;
    
    /* Get Snapshot Of Meter Data from gp_inst_LastDataPop*/
    pEventArgs->data.captured_time.Sec      = (gp_inst_DataPop->capture_time.sec);
    pEventArgs->data.captured_time.Min      = (gp_inst_DataPop->capture_time.min);
    pEventArgs->data.captured_time.Hour     = (gp_inst_DataPop->capture_time.hour);
    pEventArgs->data.captured_time.Day      = (gp_inst_DataPop->capture_time.day);
    pEventArgs->data.captured_time.Week     = (gp_inst_DataPop->capture_time.week);
    pEventArgs->data.captured_time.Month    = (gp_inst_DataPop->capture_time.month);
    pEventArgs->data.captured_time.Year     = ((uint8_t)gp_inst_DataPop->capture_time.year);

    pEventArgs->data.voltage 			= gp_inst_DataPop->value.vrms;

    // Notes: 
    //    gp_inst_DataPop->value.active_energy_total_import    : Import only
    //    R_TARIFF_GetImportActiveEnergyTotal()                : Check mode and (add export for MODE_FORWARDED_ONLY)
    pEventArgs->data.ActiveEnergyImport = R_TARIFF_GetImportActiveEnergyTotal();
    
    if (gp_inst_DataPop->value.selected_line == EM_LINE_PHASE)
    {
        pEventArgs->data.current 		= gp_inst_DataPop->value.irms;
        pEventArgs->data.PF 			= gp_inst_DataPop->value.power_factor;
        pf_sign                         = gp_inst_DataPop->value.power_factor_sign;
    }
    else
    {
        pEventArgs->data.current 		= gp_inst_DataPop->value.irms2;
        pEventArgs->data.PF 			= gp_inst_DataPop->value.power_factor2;
        pf_sign                         = gp_inst_DataPop->value.power_factor_sign2;
    }
    
    /* Indian standard representation sign of PF */
    pEventArgs->data.PF = fabsf(pEventArgs->data.PF);
    if (pf_sign == PF_SIGN_LEAD_C)
    {
        pEventArgs->data.PF = -pEventArgs->data.PF;
    }
}

/******************************************************************************
* Function Name: void EVENT_Detector(void)
* Description  : Process to detect event
* Arguments    : None
* Return Value : None
* Notes        : Please check if gp_inst_DataPop not null before call this function
******************************************************************************/
void EVENT_Detector(void)
{
    float32_t       i1, i2, ratio, max, sub;
    float32_t       voltage, irms, freq, pf;
    float32_t       act1, act2, react1, react2;
    uint8_t         is_state_enter;

    /* Prepare data for checking */

    /* Select the current channel that is considered better value */
    i1 = gp_inst_DataPop->value.irms;
    i2 = gp_inst_DataPop->value.irms2;
	
	act1 = gp_inst_DataPop->value.active_power;
    act2 = gp_inst_DataPop->value.active_power2;
	
	react1 = gp_inst_DataPop->value.reactive_power;
	react2 = gp_inst_DataPop->value.reactive_power2;
	
    EVENT_ExtractDataForLogging(&EventArgs);

    /* Start of checking code */

    
    /***********************
    * 1 min interval
    ***********************/
    if (gp_inst_DataPop->capture_time.sec == 0)
    {
        g_event_request_flag.min_interval = TRUE;
    }

    /***********************
    * Earth loading
    ***********************/
    /* Check ELT Condition */
    if (i1 >= EVENT_TAMPER_ELT_START_IRMS ||               /* ELT: Earth Load Threshold */
        i2 >= EVENT_TAMPER_ELT_START_IRMS)                 /* ELT: Earth Load Threshold */
    {
        /* Get difference percentage */
        max = MAX(i1, i2);
        sub = i1 - i2;

        /* Checking to issue earth connected event */
        g_event_flag.bits.is_earth_connected = EVENT_DetermineEventStatus(
                                                (((WRP_EXT_Absf(sub) * 100.0f) / max) >= EVENT_CONFIG_EARTH_DIFF_THRESHOLD),
                                                    &g_event_state.earth_load,
                                                    g_event_persistent_time.earth_occur,
                                                    g_event_persistent_time.earth_restore
                                                );
    }
    /***********************
    * DC Detection
    ***********************/
    /* Checking DC detection flag under wrp_em_adc */
    g_event_flag.bits.is_dc_detected = EVENT_DetermineEventStatus(
                                                (g_dc_immunity_state == 1),
                                                &g_event_state.dc_detected,
                                                g_event_persistent_time.dc_occur,
                                                g_event_persistent_time.dc_restore
                                            );
	
    /***********************
    * Low voltage & Over voltage
    ***********************/
    voltage = gp_inst_DataPop->value.vrms;//EM_GetVoltageRMS();

    /* Low voltage */
    g_event_flag.bits.is_low_voltage = EVENT_DetermineEventStatus(
                                            (voltage < EVENT_CONFIG_LOW_VOLTAGE_THRESHOLD),
                                            &g_event_state.low_voltage,
                                            g_event_persistent_time.low_voltage_occur,
                                            g_event_persistent_time.low_voltage_restore
                                        );
	
    /* Over voltage */
    g_event_flag.bits.is_over_voltage = EVENT_DetermineEventStatus(
                                            (voltage > EVENT_CONFIG_OVER_VOLTAGE_THRESHOLD),
                                            &g_event_state.over_voltage,
                                            g_event_persistent_time.over_voltage_occur,
                                            g_event_persistent_time.over_voltage_restore
                                        );

    /***********************
    * Over Current
    ***********************/
   
    irms = (gp_inst_DataPop->value.selected_line == EM_LINE_PHASE) ? i1 : i2;
    
    #if (EVENT_LOAD_CONTROL == FALSE)
        g_event_flag.bits.is_over_current = EVENT_DetermineEventStatus(
                                                    (irms > EVENT_CONFIG_OVER_CURRENT_THRESHOLD),
                                                    &g_event_state.over_current,
                                                    g_event_persistent_time.over_current_occur,
                                                    g_event_persistent_time.over_current_restore
                                                );
    #else
        g_event_flag.bits.is_over_current = R_LOAD_CTRL_Determine_OverCurrentEventStatus
                                            (
                                                (irms > EVENT_CONFIG_OVER_CURRENT_THRESHOLD),
                                                &is_state_enter
                                            );
        g_event_state.over_current.current_state = (is_state_enter == TRUE)?EVENT_STATE_ENTER:EVENT_STATE_RELEASE;
    #endif /* EVENT_LOAD_CONTROL */

	
    /***********************
    * Frequency out of range
    ***********************/
    freq = gp_inst_DataPop->value.freq;

    g_event_request_flag.is_freq_out_range = EVENT_DetermineEventStatus(
                                                    (freq < EVENT_CONFIG_FREQ_LOW_THRESHOLD || freq > EVENT_CONFIG_FREQ_HIGH_THRESHOLD),
                                                    &g_event_state.freq_out_range,
                                                    g_event_persistent_time.freq_out_range,
                                                    g_event_persistent_time.freq_out_range
                                                );

    /***********************
    * Low PF
    ***********************/
    if (WRP_EXT_Absf(act1) != 0.0f ||
		WRP_EXT_Absf(act2) != 0.0f ||
		WRP_EXT_Absf(react1) != 0.0f ||
		WRP_EXT_Absf(react2) != 0.0f )
    {
        if ( gp_inst_DataPop->value.selected_line == EM_LINE_NEUTRAL)
        {
            pf = WRP_EXT_Absf(gp_inst_DataPop->value.power_factor2);
        }   
        else
        {
            pf = WRP_EXT_Absf(gp_inst_DataPop->value.power_factor);
        }
        
        g_event_flag.bits.is_low_pf = EVENT_DetermineEventStatus(
                                                (pf < EVENT_CONFIG_PF_LOW_THRESHOLD),
                                                &g_event_state.low_pf,
                                                g_event_persistent_time.low_power_pf_occur,
                                                g_event_persistent_time.low_power_pf_restore
                                            );

    }

    /***********************
    * Current reversed
    ***********************/
    

    g_event_flag.bits.is_cur_rev = EVENT_DetermineEventStatus(
                                                (act1 < 0.0f || act2 < 0.0f),
                                                &g_event_state.cur_rev,
                                                g_event_persistent_time.current_rev_occur,
                                                g_event_persistent_time.current_rev_restore
                                            );

    /***********************
    * Overload
    ***********************/
    #if (EVENT_LOAD_CONTROL == FALSE)
        g_event_flag.bits.is_overload = EVENT_DetermineEventStatus(
                                    (WRP_EXT_Absf(act1) > g_event_overload_threshold || 
                                        WRP_EXT_Absf(act2) > g_event_overload_threshold),
                                    &g_event_state.overload,
                                    g_event_persistent_time.overload_occur,
                                    g_event_persistent_time.overload_restore
                                );
    #else
        g_event_flag.bits.is_overload = R_LOAD_CTRL_Determine_OverLoadEventStatus
                                            (
                                                (WRP_EXT_Absf(act1) > g_event_overload_threshold || 
                                                    WRP_EXT_Absf(act2) > g_event_overload_threshold),
                                                &is_state_enter
                                            );
        g_event_state.overload.current_state = (is_state_enter == TRUE)?EVENT_STATE_ENTER:EVENT_STATE_RELEASE;
    #endif /* EVENT_LOAD_CONTROL */

    /***********************
    * Magnet
    ***********************/
    g_event_flag.bits.is_magnet = EVENT_DetermineEventStatus(
                                            (MAGNET == 0),
                                            &g_event_state.magnet,
                                            g_event_persistent_time.magnet_occur,
                                            g_event_persistent_time.magnet_restore
                                        );

    /***********************
    * Case open
    ***********************/
    g_event_flag.bits.is_case_open = EVENT_DetermineEventStatus(
                                            (CASE == 0),
                                            &g_event_state.case_open,
                                            g_event_persistent_time.case_open,
                                            g_event_persistent_time.case_open
                                        );

    /* Load Control for case open */
    #if (defined( EVENT_LOAD_CONTROL ) && EVENT_LOAD_CONTROL == TRUE)
    if (g_event_flag.bits.is_case_open)
    {
        if (g_event_state.case_open.current_state == EVENT_STATE_ENTER) {
            R_LOADCTRL_LocalMgmt_Disconn(R_LOADCONTROL_LOCAL_SIGNAL_CASEOPEN);
        }
        else {
            R_LOADCTRL_LocalMgmt_Reconn(R_LOADCONTROL_LOCAL_SIGNAL_CASEOPEN);
        }
    }    
    #endif /* EVENT_LOAD_CONTROL */

    /* End of checking code */
}
/*****************************************************************************
* Function Name : EVENT_Distributor() 
* Interface     : void EVENT_Distributor(
*               :     void
*               : );
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void EVENT_Distributor(void)
{
    /**************************
        When firmware activation 
    **************************/
    if (g_scheduler[SCHEDULER_ID_FW_ACTIVATION].matched == TRUE)
    {   
        g_event_request_flag.is_fw_activation = 1;
        g_scheduler[SCHEDULER_ID_FW_ACTIVATION].matched = FALSE;
    }

    /***********************
        MaxDemand End
    ***********************/
    if (g_scheduler_flags.mdm == 1)
    {
        g_event_request_flag.is_max_demand_end = 1;
        g_scheduler_flags.mdm = FALSE;
    }

    /***********************
        TARIFF CHANGE
    ***********************/
    /* When tariff changed */
    if (g_scheduler[SCHEDULER_ID_TARIFF].matched == TRUE)
    {
        g_event_request_flag.is_tariff_changed = 1;
        g_scheduler[SCHEDULER_ID_TARIFF].matched = FALSE;
    }

    /*************************
        When 0.5S scheduler refresh LCD display request occured
     *************************/
    if (g_scheduler_flags.lcd_refresh == 1)
    {   
        g_event_request_flag.is_lcd_refresh = 1;
        g_scheduler_flags.lcd_refresh = FALSE;
    }

    /*************************
        When 5S scheduler scroll LCD display request occured 
	*************************/
    if (g_scheduler_flags.lcd_scroll == 1)
    {   
        g_event_request_flag.is_lcd_scroll = 1;
        g_scheduler_flags.lcd_scroll = FALSE;
    }

    /*************************
        When billing request 
    *************************/
    if (g_scheduler[SCHEDULER_ID_BILLING].matched == TRUE)
    {   
        g_event_request_flag.is_billing_request = 1;
        g_scheduler[SCHEDULER_ID_BILLING].matched = FALSE;
    }

    /*************************
        When blockload request 
    *************************/
    if (g_scheduler_flags.blockload == 1)
    {   
        g_event_request_flag.is_blockload_request = 1;
        g_scheduler_flags.blockload = FALSE;
    }

    /*************************
        When daily load request 
    *************************/
    if (g_scheduler_flags.dailyload == 1)
    {   
        g_event_request_flag.is_dailyload_request = 1;
        g_event_request_flag.act_cal_week_profile_change = 1;
        g_scheduler_flags.dailyload = FALSE;
    }


	/* TODO Need to uncomment all lines below after merge to master branch */
    /*************************
        When Push request 
    *************************/
    if (g_scheduler[SCHEDULER_ID_PERIODIC_CH0].matched == TRUE)
    {   
        g_event_request_flag.periodic_msg_1 = 1;
        g_scheduler[SCHEDULER_ID_PERIODIC_CH0].matched = FALSE;
    }
    /*************************
        When Activity Calendar activation request 
    *************************/
    if (g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_ACT].matched == TRUE)
    {   
        g_event_request_flag.is_cal_active_req = 1;
        g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_ACT].matched = FALSE;
    }

    if (g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_SEASON].matched == TRUE)
    {   
        g_event_request_flag.act_cal_season_change = 1;
        g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_SEASON].matched = FALSE;
    }

    /*************************
        When rtc failed
    *************************/

}

/***********************************************************************************************************************
* Function Name : EVENT_StorageWrite
* Description   : Add event log and backup the event state of paired event. 
*               : Only 1 is logged, for array of log, do it on other application
*               : Note: currently support power failed event log only
* Arguments     : SINGLE_PAIR_EVENTLOG_T * p_event_info
* Return Value  : None
***********************************************************************************************************************/
void EVENT_StorageWrite(EVENT_ARGS_T * pEventArgs)
{

    uint32_t TableStartAddress;
    uint32_t EntryLogSize;
    uint8_t is_log;

    uint32_t WritePositionIndex;
    uint32_t WriteAddr;

    EventTableConfig_t TableConfig;
    EventTableHeader_t TableHeader;

    EVENT_PARAMS_SHORT_T short_log;

    if (pEventArgs->data.code == 0)
    {
        return;
    }

    /* EEPROM Address */
    TableConfig = gEventTableConfigs[pEventArgs->type];
    TableHeader = gEventTableHeaders[pEventArgs->type];
    EntryLogSize = TableConfig.LogSize;

    WritePositionIndex = (TableHeader.StartPosition + TableHeader.EntriesInUse) % TableConfig.MaxEntries;

    /* Calculation index */
    {
        if (TableConfig.IsRollover == FALSE && (TableHeader.EntriesInUse >= TableConfig.MaxEntries))
        {
            /* Do not log if buffer is none rollover and full already */
            return;
        }

        if (TableHeader.EntriesInUse >= TableConfig.MaxEntries)
        {
            TableHeader.EntriesInUse = TableConfig.MaxEntries;
            TableHeader.StartPosition = (TableHeader.StartPosition + 1) % TableConfig.MaxEntries;
        }
        else
        {
            TableHeader.EntriesInUse++;
        }
    }

    WriteAddr = TableConfig.TableStartAddr + WritePositionIndex * EntryLogSize;
    /* Write the log */
    EPR_Write(
        WriteAddr,
        (uint8_t *)(void *)&pEventArgs->data,
        EntryLogSize
    );

    gEventTableHeaders[pEventArgs->type] = TableHeader;
}


/******************************************************************************
* Function Name : EVENT_AccumulateTamperCounter
* Interface     : void EVENT_AccumulateTamperCounter(EVENT_ARGS_T *pEventArgs)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void EVENT_AccumulateTamperCounter(EVENT_ARGS_T *pEventArgs)
{
    /* Increase Tamper Counter */
    if ((pEventArgs->type == EVENT_TYPE_VOLTAGE_RELATED) ||
        (pEventArgs->type == EVENT_TYPE_OTHERS) ||
        (pEventArgs->type == EVENT_TYPE_CURRENT_RELATED))
    {
        if (pEventArgs->status == EVENT_STATE_ENTER)
        {
            g_tamper_counter++;
            pEventArgs->data.TamperCounter = g_tamper_counter;
        }
    }
}

/*****************************************************************************
* Function Name : EVENT_Logging 
* Interface     : void EVENT_Logging(
*               :     void
*               : );
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void EVENT_Logging(void)
{
    uint8_t bit_id1 = 0;
    uint32_t mask = 1u;
    uint8_t  found_bit = FALSE;
    uint32_t indicator_event_mask_bit = 0x000FFFFF;
    uint32_t event_indicator_flag;
    
     /* Get list of indicator flag */
    event_indicator_flag = g_event_flag.value & indicator_event_mask_bit;

    do
    {
        /* code */
        //Get bit ID
        if ((event_indicator_flag & mask) == 0) 
        {
            found_bit = FALSE;
        }
        else
        {   
            found_bit = TRUE;
            g_event_flag.value &= ~ mask;
        }
        bit_id1 ++;
        event_indicator_flag &= ~ mask;
        mask = mask << 1;

        if ( found_bit == TRUE)
        {
            switch (bit_id1)
            {
            case 1: // low voltage   
                if( g_event_state.low_voltage.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_LOW_VOLTAGE_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_LOW_VOLTAGE_RESTORATION;
                }
                EventArgs.type              = (EVENT_TYPE_T)0;
                EventArgs.esw_bit_number    = 4;
                break;

            case 2: // over voltage (voltage swell) 
                if( g_event_state.over_voltage.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_OVERVOLTAGE_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_OVERVOLTAGE_RESTORATION;
                }
                EventArgs.type              = (EVENT_TYPE_T)0;
                EventArgs.esw_bit_number    = 3;
                break;

            case 3: // over current
                if( g_event_state.over_current.current_state== EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_OVER_CURRENT_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_OVER_CURRENT_RESTORATION;
                }
                EventArgs.type              = (EVENT_TYPE_T)1;
                EventArgs.esw_bit_number    = 11;
                break;

            case 4: // current reverse
                if( g_event_state.cur_rev.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_CURRENT_REVERSE_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_CURRENT_REVERSE_RESTORATION;
                }
                EventArgs.type              = (EVENT_TYPE_T)1;
                EventArgs.esw_bit_number    = 0xFF;
                break;

            case 5: // overload
                if( g_event_state.overload.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_OVERLOAD_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_OVERLOAD_RESTORATION;
                }
                EventArgs.type              = (EVENT_TYPE_T)4;
                EventArgs.esw_bit_number    = 0xFF;
                break;

            case 6: // low power factor
                if( g_event_state.low_pf.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = 0;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = 0;
                }
                EventArgs.type              = (EVENT_TYPE_T)4;
                EventArgs.esw_bit_number    = 0xFF;
                break;

            case 7: // Neutral Missing 
                if( g_event_state.neutral_missing.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_NEUTRAL_MISSING_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_NEUTRAL_MISSING_RESTORATION;
                }
                EventArgs.type              = (EVENT_TYPE_T)4;
                EventArgs.esw_bit_number    = 0xFF;
                break;

            case 8: // Earth connected 
                if( g_event_state.earth_load.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_EARTH_LOADING_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_EARTH_LOADING_RESTORATION;
                }
                EventArgs.type              = (EVENT_TYPE_T)1;
                EventArgs.esw_bit_number    = 51;
                break;

            case 9: // DC detectiom
                if( g_event_state.dc_detected.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_NEUTRAL_DISTURBANCE_HF_AND_DC_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_NEUTRAL_DISTURBANCE_HF_AND_DC_RESTORATION;
                }
                EventArgs.type              = (EVENT_TYPE_T)4;
                EventArgs.esw_bit_number    = 82;
                break;

            case 10: // power failures occur (voltage sag) (last gasp)/ power failures restore ( first breath)
                if( g_event_state.power_failed.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_POWER_FAILURE_OCCURRENCE;
                    EventArgs.esw_bit_number = 85;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_POWER_FAILURE_RESTORATION;
                    EventArgs.esw_bit_number = 86;
                }
                EventArgs.type = (EVENT_TYPE_T)2;
                break;

            case 11: // magnetic
                if( g_event_state.magnet.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_INFLUENCE_OF_PERMANENT_MAGNET_OR_ACDC_ELECTROMAGNET_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_INFLUENCE_OF_PERMANENT_MAGNET_OR_ACDC_ELECTROMAGNET_RESTORATION;
                } 
                EventArgs.type              = (EVENT_TYPE_T)4;
                EventArgs.esw_bit_number    = 81;
                break;

            case 12: // case open
                if( g_event_state.case_open.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_METER_COVER_OPENING_OCCURRENCE;
                    EventArgs.type          = (EVENT_TYPE_T)5;
                    EventArgs.esw_bit_number = 83;
                }
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    // No event code and type to log for case open release event
                    EventArgs.data.code     = 0;
                    EventArgs.type          = EVENT_TYPE_UNKNOWN;
                    EventArgs.esw_bit_number = 0xFF;
                }
                break;

            case 13: // post-paid mode/ pre-paid mode 
                if( g_event_state.paid_mode.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_POSTPAID_MODE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_PREPAID_MODE;
                } 
                EventArgs.type              = (EVENT_TYPE_T)4;
                EventArgs.esw_bit_number    = 0xFF;
                break;

            case 14: // forwarded only mode/ import and export mode
                if( g_event_state.meter_mode.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_FORWARDED_ONLY_MODE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_IMPORT_AND_EXPORT_MODE;
                } 
                EventArgs.type              = (EVENT_TYPE_T)4;
                EventArgs.esw_bit_number    = 0xFF;
                break;

			case 15:    // Increase in billing counter: none
				EventArgs.type              = (EVENT_TYPE_T)0xFF;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_INCREASE_BILLING_COUNTER;
				EventArgs.esw_bit_number    = 87;
				break;
				
			
			case 16:// set RTC: 151
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_REAL_TIME_CLOCK_DATE_AND_TIME;
				EventArgs.esw_bit_number    = 0xFF;
				break;	
				
			case 17:// set Demand Integration Period: 152	
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_DEMAND_INTEGRATION_PERIOD;
				EventArgs.esw_bit_number    = 0xFF;
				break;
				
			case 18:// set Profile Capture Period: 153
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_PROFILE_CAPTURE_PERIOD;
				EventArgs.esw_bit_number    = 0xFF;
				break;
				
			case 19:// set SAS for Billing Dates: 154
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_SINGLEACTION_SCHEDULE_FOR_BILLING_DATES;
				EventArgs.esw_bit_number    = 0xFF;
				break;
				
			case 20:// MD reset: 166
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_MD_RESET;
				EventArgs.esw_bit_number    = 0xFF;
				break;
            default:
                
                break;
            }

            /* Extract data from snapshot (only extract when event happend) */
            EVENT_FowardToPluginFn(&EventArgs);
            EVENT_AccumulateTamperCounter(&EventArgs);
            EVENT_StorageWrite(&EventArgs);
            
        }

        if ( bit_id1 > 20)
        {
            bit_id1 = 1;
            mask = 1u;
        }
    
    } while ( event_indicator_flag !=0 );
    
}

/*****************************************************************************
* Function Name : EVENT_CheckAndTriggerTamperEnergyAccumulation 
* Interface     : void EVENT_CheckAndTriggerTamperEnergyAccumulation(void)
* Description   : Check for tamper event the need fixed power pulse output and energy update
*               : In case multiple tamper, highest tamper power is selected
*               : If there's tamper power, inform instantaneous snapshot to:
*               :   * Stop metrology actual energy accumulating in timer
*               :   * Update energy directly by fixed power every 1s in snapshot RTC interrupt
*               :   * Update pulse output by fixed power value
*               : If no tamper power needed, inform instantaneous snapshot to:
*               :   * Normal metrology actual energy accumulating in timer
*               :   * Update pulse output by actual read power value
* Arguments     : None
* Return Value  : None
******************************************************************************/
void EVENT_CheckAndTriggerTamperEnergyAccumulation(void)
{
    /* Default update energy normally with no specified power */
    r_event_tamper_update_mode update_mode = EVENT_TAMPER_UPDATE_NORMAL;
    float32_t specified_power = 0.0f;

    /* Earthing */
    EVENT_CHECK_TAMPER_UPDATING_MODE(
        EVENT_TAMPER_EARTHING_ENERGY_UPDATE_MODE,
        EVENT_TAMPER_EARTHING_SPECIFIED_POWER,
        g_event_state.earth_load.current_state,
        update_mode, specified_power
    );
    /* Magnet */
    EVENT_CHECK_TAMPER_UPDATING_MODE(
        EVENT_TAMPER_MAGNET_ENERGY_UPDATE_MODE,
        EVENT_TAMPER_MAGNET_SPECIFIED_POWER,
        g_event_state.magnet.current_state,
        update_mode, specified_power
    );
    /* Case open */
    EVENT_CHECK_TAMPER_UPDATING_MODE(
        EVENT_TAMPER_CASE_OPEN_ENERGY_UPDATE_MODE,
        EVENT_TAMPER_CASE_OPEN_SPECIFIED_POWER,
        g_event_state.case_open.current_state,
        update_mode, specified_power
    );
    /* DC Detection */
    EVENT_CHECK_TAMPER_UPDATING_MODE(
        EVENT_TAMPER_DC_DETECTION_ENERGY_UPDATE_MODE,
        EVENT_TAMPER_DC_DETECTION_SPECIFIED_POWER,
        g_event_state.dc_detected.current_state,
        update_mode, specified_power
    );

    /* Update pulse one time in case specified power */
    if (update_mode == EVENT_TAMPER_UPDATE_BY_SPECIFIED_POWER &&
        EM_GetEnergyAccumulationMode() == 3)
    {
        /* Energy accumulation mode 0, continue using last calculated power in metrology */
        EM_SetEnergyAccumulationMode(0);
        /* Set tamper power */
        EM_SetEnergyAccumulationPower(specified_power, 0.0f, specified_power);
    }
    else if (update_mode == EVENT_TAMPER_UPDATE_NORMAL &&
             EM_GetEnergyAccumulationMode() == 0)
    {
        /* Set normal power */
        EM_SetEnergyAccumulationPower(gp_inst_DataPop->value.active_power, gp_inst_DataPop->value.reactive_power, gp_inst_DataPop->value.apparent_power);
        /* Energy accumulation mode 3, update using normal power, from next */
        EM_SetEnergyAccumulationMode(3);
    }
}

/******************************************************************************
* Function Name    : void EVENT_PollingProcessing(void)
* Description      : Event Polling Processing
* Arguments        : None
* Functions Called : EVENT_BackupSystemAndRTC()
*                  : DEBUG_Printf()
*                  : DEBUG_AckNewLine()
*                  : RTC_CounterGet()
*                  : EVENT_AddEnergyLog()
*                  : STORAGE_AddEnergyLog()
* Return Value     : None
******************************************************************************/
void EVENT_PollingProcessing(void)
{
    uint8_t status;

    if (gp_inst_DataPop != NULL)
    {
        /* Start of checking code */
        EVENT_Detector();
    }

    EVENT_Logging();
        
    EVENT_Distributor();
    
    EVENT_CheckAndTriggerTamperEnergyAccumulation();
}

/******************************************************************************
* Function Name    : uint8_t EVENT_StorageFormat(void)
* Description      : 
* Arguments        : None
* Functions Called : None
* Return Value     : 
******************************************************************************/
uint8_t EVENT_StorageFormat(void)
{
    uint32_t    eeprom_addr;
    uint8_t     empty_page[STORAGE_EEPROM_PAGESIZE];
    uint16_t    size;

    /* Create empty_page */
    memset(empty_page, 0, sizeof(empty_page));

    /* Clear Whole EEPROM */
    eeprom_addr = STORAGE_EEPROM_EVENT_LOG_NONROLLOVER_ADDR;
    while (eeprom_addr < STORAGE_EEPROM_EVENT_LOG_LAST_ADDR)
    {
        if ((STORAGE_EEPROM_EVENT_LOG_LAST_ADDR - eeprom_addr) < STORAGE_EEPROM_PAGESIZE) {
            size = STORAGE_EEPROM_EVENT_LOG_LAST_ADDR - eeprom_addr;
        }
        else {
            size = STORAGE_EEPROM_PAGESIZE;
        }

        if (EPR_Write(eeprom_addr, empty_page, size) != EPR_OK)
        {
            return STORAGE_ERROR;
        }

        eeprom_addr += size;

        R_WDT_Restart();
    }

    /* Formatted */
    return STORAGE_OK;
}

/******************************************************************************
* Function Name    : uint8_t EVENT_StorageRestore(void)
* Description      :
* Arguments        : None
* Functions Called : None
* Return Value     :
******************************************************************************/
uint8_t EVENT_StorageRestore(void)
{   

    if (EPR_Read(
                EVENT_EEPROM_BACKUP_EVENT_STATE_ADDR,
                (uint8_t *)&g_event_state,
                sizeof(EVENT_INFO)
            ) != EPR_OK)
    {
        return STORAGE_ERROR;
    }

    if (EPR_Read(
                EVENT_EEPROM_BACKUP_EVENT_TAMPER_COUNTER_ADDR,
                (uint8_t *)&g_tamper_counter,
                sizeof(g_tamper_counter)
            ) != EPR_OK)
    {
        return STORAGE_ERROR;
    }


    if (EPR_Read(
                EVENT_EEPROM_BACKUP_EVENT_TABLE_HEADER_ADDR,
                (uint8_t *)&gEventTableHeaders[0],
                sizeof(gEventTableHeaders)
            ) != EPR_OK)
    {
        return STORAGE_ERROR;
    }

    return STORAGE_OK;
}
/******************************************************************************
* Function Name    : uint8_t EVENT_StorageBackup(void)
* Description      :
* Arguments        : None
* Functions Called : None
* Return Value     :
******************************************************************************/
uint8_t EVENT_StorageBackup(void)
{
    if (EPR_Write(
                EVENT_EEPROM_BACKUP_EVENT_STATE_ADDR,
                (uint8_t *) &g_event_state,
                sizeof(EVENT_INFO)
            ) != EPR_OK)
        {
            return STORAGE_ERROR;
        }

    if (EPR_Write(
                EVENT_EEPROM_BACKUP_EVENT_TAMPER_COUNTER_ADDR,
                (uint8_t *) &g_tamper_counter,
                sizeof(g_tamper_counter)
            ) != EPR_OK)
        {
            return STORAGE_ERROR;
        }
    
    if (EPR_Write(
                EVENT_EEPROM_BACKUP_EVENT_TABLE_HEADER_ADDR,
                (uint8_t *) &gEventTableHeaders,
                sizeof(gEventTableHeaders)
            ) != EPR_OK)
        {
            return STORAGE_ERROR;
        }

    return STORAGE_OK;
}

/******************************************************************************
* Function Name    : uint8_t EVENT_Init(void)
* Description      : Event Init
* Arguments        : None
* Functions Called : None
* Return Value     : Execution status
*                  : EVENT_OK       Success
*                  : EVENT_ERROR    Register event failed
******************************************************************************/
uint8_t EVENT_Init(void)
{
    /* Reset event flag */
    memset(&g_event_flag, 0, sizeof(EVENT_FLAG));

    /* Success all */
    return EVENT_OK;
}
/**********************************************************************************************************************
 * Function Name: R_EVENT_EntriesInUseGet      
 * Description  : Function to get entries in use
 * Arguments    : event_type - enum type of event to get, 
 *                p_data_out -  pointer of entries in use to get.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                  
 **********************************************************************************************************************/ 
uint8_t R_EVENT_EntriesInUseGet(EVENT_TYPE_T event_type, uint32_t * p_data_out)
{
    if ((uint8_t)event_type > (uint8_t)LAST_EVENT_TYPE)
    {
        return FALSE;
    }
    
    (*p_data_out) = gEventTableHeaders[(uint8_t)event_type].EntriesInUse;

	return TRUE;
}


/**********************************************************************************************************************
 * Function Name: R_EVENT_ProfileEntriesGet      
 * Description  : Function to get profile entries
 * Arguments    : event_type - enum type of event to get, 
 *                p_data_out -  pointer of profile entries to get.
 * Return Value : TRUE - get successfully, FALSE - get unsuccessfully.                  
 **********************************************************************************************************************/ 
uint8_t R_EVENT_ProfileEntriesGet(EVENT_TYPE_T event_type, uint32_t * p_data_out)
{
    if ((uint8_t)event_type > (uint8_t)LAST_EVENT_TYPE)
    {
        return FALSE;
    }
    
    (*p_data_out) = gEventTableConfigs[(uint8_t)event_type].MaxEntries;

	return TRUE;
}


/**********************************************************************************************************************
 * Function Name: R_EVENT_ResetLog      
 * Description  : Function to execute Clear log 
 * Arguments    : event_type - enum type of event to execute clear log.
 * Return Value : TRUE - action successfully, FALSE - action unsuccessfully.                  
 **********************************************************************************************************************/ 
uint8_t R_EVENT_ResetLog(EVENT_TYPE_T event_type)
{
    if (event_type > LAST_EVENT_TYPE)
    {
        return FALSE;
    }

    gEventTableHeaders[event_type].StartPosition = 0;
    gEventTableHeaders[event_type].EntriesInUse = 0;
    
    return TRUE;
}

/******************************************************************************
* Function Name : R_EVENT_GetEntry
* Interface     : EVENT_PARAMS_T R_EVENT_GetEntry(
*               :     EVENT_TYPE_T EventType, uint32_t EntryIndex
*               : );
* Description   :
* Arguments     :
* Return Value  : EVENT_PARAMS_T
******************************************************************************/
EVENT_PARAMS_T R_EVENT_GetEntry(EVENT_TYPE_T EventType, uint16_t EntryIndex)
{
    EventTableConfig_t TableConfig;
    EventTableHeader_t TableHeader;
    uint32_t EntryLogSize;
    uint32_t ReadPositionIndex;
    uint32_t ReadAddr;

    EVENT_PARAMS_T EntryData;

    memset(&EntryData, 0, sizeof(EVENT_PARAMS_T));

    /* EEPROM Address */
    TableConfig = gEventTableConfigs[EventType];
    TableHeader = gEventTableHeaders[EventType];
    EntryLogSize = TableConfig.LogSize;

    ReadPositionIndex = (TableHeader.StartPosition + EntryIndex) % TableConfig.MaxEntries;
    ReadAddr = TableConfig.TableStartAddr + (ReadPositionIndex * EntryLogSize);

    /* Write the log */
    EPR_Read(
        ReadAddr,
        (uint8_t *)(void *)&EntryData,
        EntryLogSize
    );

    return EntryData;
}



/******************************************************************************
* Function Name: float32_t EVENT_GetOverLoadThreshold(void)
* Description  : Energy Event Get over load threshold
* Arguments    : None
* Return Value : float32_t current value
******************************************************************************/
float32_t EVENT_GetOverLoadThreshold(void)
{
    return g_event_overload_threshold;
}

/******************************************************************************
* Function Name: void EVENT_SetOverLoadThreshold(float32_t value)
* Description  : Energy Event Set over load threshold
* Arguments    : float32_t value: set value
* Return Value : None
******************************************************************************/
void EVENT_SetOverLoadThreshold(float32_t value)
{
    g_event_overload_threshold = value;
}


