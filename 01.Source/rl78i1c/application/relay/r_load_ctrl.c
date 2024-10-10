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
* Copyright (C) 2013, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_load_ctrl.c
* Version      : v1.0.0
* Device(s)    : <'RL78/I1C'>
* Tool-Chain   : <'CCRL'>
* H/W Platform : <'RL78/I1C Energy Meter Platform'>
* Description  : Load switch control application for Smart Meter
************************************************************************************************************************
* History      : DD.MM.YYYY     Version     Description
*                20.03.2018     v.1.0.0     New creation
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/

/* Common */
#include "typedef.h"

/* Meter Application */
#include "em_measurement.h"
#include "relay.h"
#include "event.h"
#include "r_load_ctrl.h"
#include "storage.h"

/* Wrapper functions */
#include "wrp_app_ext.h"

/* Standard library */
#include <string.h>

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#define DO_DISCONNECT()             RELAY_SwitchOff()
#define DO_RECONNECT()              RELAY_SwitchOn()


#define COUNTER_ENABLED			(1)
#define COUNTER_DISABLED		(0)


#define DIRECTION_UP			(1)
#define DIRECTION_DOWN			(0)

/* Local management function request */
#define CHECK_MAX_CHANNEL_RET_ERROR(ch, max)        if (ch >= max) return LOADCTRL_RET_ERROR;
#define MODIFY_TYPE_STATE(state, channel)           {                                                           \
                                                        g_load_ctrl_local_state_info[##channel##]= state;       \
                                                    }

#define REMOTE_RECONNECT_DELAY_COUNT_x10ms          (3000)
#define RESET_REMOTE_RECONNECT_DELAY_COUNT()        { g_load_ctrl_info.remote_reconn_delay_count = REMOTE_RECONNECT_DELAY_COUNT_x10ms ; }
#define RESTART_REMOTE_RECONNECT_DELAY_COUNT()      { g_load_ctrl_info.remote_reconn_delay_count = 0 ; }
#define IS_REMOTE_RECONNECT_DELAY_COUNT_END()       ( g_load_ctrl_info.remote_reconn_delay_count >= REMOTE_RECONNECT_DELAY_COUNT_x10ms )


typedef enum tag_loadctrl_timer_counter_id_t
{
	COUNTER_ID_LOAD_CTRL,
	COUNTER_ID_LOCKOUT_PERIOD,
	COUNTER_ID_AUTO_RECONNECT_INTERVAL,
	COUNTER_ID_OVER_CURRENT
} loadctrl_timer_counter_id_t;

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tag_load_ctrl_info_t
{
    uint8_t local_state_change;
    uint8_t remote_state_change;
    uint8_t manual_state_change;
    ctrl_state_t remote_new_state;
    ctrl_state_t manual_new_state;
    uint16_t remote_reconn_delay_count;
} r_load_ctrl_info_t;


typedef struct tag_storage_info_t
{
    uint32_t    address;    /* Address of Config on EEPROM */
    uint16_t    length;     /* Length of Config on EEPROM  */
} relay_storage_info_t;

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/* Private functions */
void r_load_ctrl_mode0_enter(void);
void R_LOAD_CTRL_UpdateLimiterThreshold(void);

/* Load Limit Function Status */
uint8_t 					g_load_ctrl_state = 2;
uint8_t 					g_load_ctrl_mode = 1;
uint8_t 					g_load_ctrl_relay_status;

/* Load limit value.in W */
limit_threshold_type_t		g_limiter_normal;
limit_threshold_type_t		g_limiter_emergency;

uint32_t 					g_limiter_min_over_threshold_duration;
uint32_t 					g_limiter_min_under_threshold_duration;

/* Flag for manual reconnect (press LCD scroll button and hold 2s */
uint8_t g_load_ctrl_manual_reconn_flag = FALSE;

/* LOAD SWITCH CONTROL */

/* 
 * Local functions state
 * 		Signal 0: Event - Case Open
 * 		Signal 1: Event - Overload (Power > Threshold)
 * 		Signal 2: Event - Overcurrent (I > 105 Imax)
 */
ctrl_state_t 				            g_load_ctrl_local_state_info[R_LOAD_CONTROL_LOCAL_MAX_FUNCTIONS];
static r_load_ctrl_info_t 		        g_load_ctrl_info;

/* LOAD SWITCH CONTROL */
/* Local functions state */
ctrl_state_t 				            g_load_ctrl_local_state_info[R_LOAD_CONTROL_LOCAL_MAX_FUNCTIONS];
static r_load_ctrl_info_t 		        g_load_ctrl_info;

RelayProgessStatus_t 					g_ctrl_relay_progess;
RelayAutoDisconnectParameter_t 			g_ctrl_relay_params = 
{
	LOCK_OUT_TIME_DEFAULT, 	        /* uint16_t 	lockout_period; (second) */
	TIME_INTERVAL_DEFAULT, 	        /* uint8_t 		delay_interval; (second) */
	NO_OF_REPETITIONS_DEFAULT, 		/* uint8_t		retry_counter; */
};

/* Storage map */
const relay_storage_info_t g_storage_info_limiter_normal                        = {STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_ADDR, sizeof(limit_threshold_type_t)};
const relay_storage_info_t g_storage_info_limiter_emergency                     = {STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_EMERGENCY_ADDR, sizeof(limit_threshold_type_t)};
const relay_storage_info_t g_storage_info_limiter_min_over_threshold_duration   = {STORAGE_EEPROM_LOAD_CTRL_MIN_OVER_DURATION_ADDR, STORAGE_EEPROM_LOAD_CTRL_MIN_OVER_DURATION_SIZE};
const relay_storage_info_t g_storage_info_limiter_min_under_threshold_duration  = {STORAGE_EEPROM_LOAD_CTRL_MIN_UNDER_DURATION_ADDR, STORAGE_EEPROM_LOAD_CTRL_MIN_UNDER_DURATION_SIZE};
const relay_storage_info_t g_storage_info_ctrl_control_state                    = {STORAGE_EEPROM_LOAD_CTRL_STATE_ADDR, STORAGE_EEPROM_LOAD_CTRL_STATE_SIZE};
const relay_storage_info_t g_storage_info_ctrl_control_mode                     = {STORAGE_EEPROM_LOAD_CTRL_MODE_ADDR, STORAGE_EEPROM_LOAD_CTRL_MODE_SIZE};
const relay_storage_info_t g_storage_info_ctrl_relay_status                     = {STORAGE_EEPROM_LOAD_CTRL_RELAY_STATUS_ADDR, STORAGE_EEPROM_LOAD_CTRL_RELAY_STATUS_SIZE};
const relay_storage_info_t g_storage_info_ctrl_relay_progess                    = {STORAGE_EEPROM_LOAD_CTRL_RELAY_PROGRESS_STATUS_ADDR, STORAGE_EEPROM_LOAD_CTRL_RELAY_PROGRESS_STATUS_SIZE};

/* Default value */
const limit_threshold_type_t g_limiter_normal_default 			= (limit_threshold_type_t)LIMITER_THRESHOLD_NORMAL_DEFAULT;
const limit_threshold_type_t g_limiter_emergency_default 		= (limit_threshold_type_t)LIMITER_THRESHOLD_EMERGENCY_DEFAULT;
const uint32_t  g_limiter_duration_default 			            = LIMITER_DURATION_DEFAULT;
const uint8_t	g_load_ctrl_state_default	                    = LOADCTRL_STATE_DEFAULT;
const uint8_t	g_ctrl_mode_default					            = LOADCTRL_MODE_DEFAULT;


typedef struct tag_relay_timer_counter_t
{
	uint8_t		enable;
	uint32_t	value;
} r_relay_timer_counter_t;

/* 
 * RTC 0.5s interrupts Counter
 *    [0] 		: Limiter over/under threshold period
 *    [1] 		: Lock out period (30min = 1800s)
 */
#define COUNTER_NUMBER                 (3)
static r_relay_timer_counter_t relay_timer_counter[COUNTER_NUMBER];

/* TIMER COUNTER */

void timer_counter_descrease_each_sec(void);
/******************************************************************************
* Function Name : timer_counter_descrease_each_sec
* Interface     : void timer_counter_descrease_each_sec(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void timer_counter_descrease_each_sec(void)
{
    uint8_t counter_id;

    for (counter_id = 0; counter_id < COUNTER_NUMBER; counter_id++)
    {
        if ((relay_timer_counter[counter_id].enable == TRUE) && (relay_timer_counter[counter_id].value > 0))
        {
            relay_timer_counter[counter_id].value--;
        }
    }
}

/******************************************************************************
* Function Name : timer_counter_disable
* Interface     : void timer_counter_disable(uint8_t counter_id)
* Description   :
* Arguments     : uint8_t counter_id
* Return Value  : void
******************************************************************************/
void timer_counter_disable(uint8_t counter_id)
{
	if (counter_id < COUNTER_NUMBER)
	{
		relay_timer_counter[counter_id].enable = FALSE;
	}
}

/******************************************************************************
* Function Name : timer_counter_enable
* Interface     : void timer_counter_enable(uint8_t counter_id)
* Description   :
* Arguments     : uint8_t counter_id
* Return Value  : void
******************************************************************************/
void timer_counter_enable(uint8_t counter_id)
{
	if (counter_id < COUNTER_NUMBER)
	{
		relay_timer_counter[counter_id].enable = TRUE;
	}
}

/******************************************************************************
* Function Name : timer_counter_get_value
* Interface     : void timer_counter_get_value(uint8_t counter_id)
* Description   :
* Arguments     : uint8_t counter_id
* Return Value  : Current value of counter[counter_id] 
*                 (uint32_t)  
******************************************************************************/
uint32_t timer_counter_get_value(uint8_t counter_id)
{
	if (counter_id < COUNTER_NUMBER)
	{
		return relay_timer_counter[counter_id].value;
	}
	else 
	{
		return 0;
	}
}

/******************************************************************************
* Function Name : timer_counter_set_value
* Interface     : void timer_counter_set_value(uint8_t counter_id , uint32_t value)
* Description   :
* Arguments     : uint8_t counter_id , uint32_t value
* Return Value  : None
******************************************************************************/
void timer_counter_set_value(uint8_t counter_id , uint32_t value)
{
	if (counter_id < COUNTER_NUMBER)
	{
		if (relay_timer_counter[counter_id].enable == FALSE)
		{
			relay_timer_counter[counter_id].value = value;
			relay_timer_counter[counter_id].enable = TRUE;
		}
	}
}

/******************************************************************************
* Function Name : timer_counter_start
* Interface     : void timer_counter_start(uint8_t counter_id , uint32_t value)
* Description   :
* Arguments     : uint8_t counter_id , uint32_t value
* Return Value  : None
******************************************************************************/
void timer_counter_start(uint8_t counter_id , uint32_t value)
{
	if (counter_id < COUNTER_NUMBER)
	{
		relay_timer_counter[counter_id].value = value;
		relay_timer_counter[counter_id].enable = TRUE;
	}
}


static uint8_t g_check_state_at_init_flag = FALSE;

/******************************************************************************
* Function Name : r_load_ctrl_local_mgmt_polling_processing
* Interface     : void r_load_ctrl_local_mgmt_polling_processing(void)
* Description   : Polling processing for local management function
* Arguments     : None
* Function Calls: TBD
* Return Value  : None
******************************************************************************/
void r_load_ctrl_local_mgmt_polling_processing(void)
{
    uint16_t i;
    uint16_t conn_count;
	static uint8_t mode0_locker = FALSE;

    /* State changes? */
    if ((g_load_ctrl_info.local_state_change == TRUE) || (g_check_state_at_init_flag == TRUE))
    {
        if (g_load_ctrl_mode == 0 && mode0_locker == FALSE)
        {
            r_load_ctrl_mode0_enter();
			mode0_locker = TRUE;
            return;
        }
		else
		{
		 	mode0_locker = FALSE;
		}
		
        /* Summarize the number of ready local functions */
        conn_count = 0;
        for (i = 0; i < R_LOAD_CONTROL_LOCAL_MAX_FUNCTIONS; i++)
        {
            if (g_load_ctrl_local_state_info[i] == CTRL_STATE_CONN) {
                conn_count++;
            }
        }

        /* Is all local function confirm to connect? */
        if (conn_count >= R_LOAD_CONTROL_LOCAL_MAX_FUNCTIONS) {
            /* All confirm to connect */
            if ((g_load_ctrl_mode == 5) || (g_load_ctrl_mode == 6) || (g_check_state_at_init_flag == TRUE))
            {
                if (g_load_ctrl_state == CTRL_STATE_READY) {
                    DO_RECONNECT();
                    /* Change the state also */
                    R_LOAD_CTRL_SetState(CTRL_STATE_CONN);
                }
                g_check_state_at_init_flag = FALSE;
            }
        }
        else {
            /* Some not confirm to connect */
            if (g_load_ctrl_state == CTRL_STATE_CONN) {
                DO_DISCONNECT();
                R_LOAD_CTRL_SetState(CTRL_STATE_READY);
            }
            /* No state setting, ready also has load disconnected */
        }

        /* Acknowledge */
        g_check_state_at_init_flag = FALSE;
        g_load_ctrl_info.local_state_change = FALSE;
    }
}

/******************************************************************************
* Function Name : r_load_ctrl_remote_polling_processing
* Interface     : void r_load_ctrl_remote_polling_processing(void)
* Description   : Polling processing for remote request
* Arguments     : None
* Function Calls: TBD
* Return Value  : None
******************************************************************************/
void r_load_ctrl_remote_polling_processing(void)
{
    /* State changes? */
    if (g_load_ctrl_info.remote_state_change == TRUE)
    {
        if  (g_load_ctrl_info.remote_new_state == CTRL_STATE_CONN) {
            DO_RECONNECT();
            R_LOAD_CTRL_SetState(g_load_ctrl_info.remote_new_state);
        }
        else {
            DO_DISCONNECT();
            R_LOAD_CTRL_SetState(g_load_ctrl_info.remote_new_state);
        }

        /* Only remote reconnect has delay count */
        RESTART_REMOTE_RECONNECT_DELAY_COUNT();

        /* Acknowledge */
        g_load_ctrl_info.remote_state_change = FALSE;
    }
}

/******************************************************************************
* Function Name : r_load_ctrl_manual_polling_processing
* Interface     : void r_load_ctrl_manual_polling_processing(void)
* Description   : Polling processing for manual request
* Arguments     : None
* Function Calls: TBD
* Return Value  : None
******************************************************************************/
void r_load_ctrl_manual_polling_processing(void) 
{
    /* State changes? */
    if (g_load_ctrl_info.manual_state_change == TRUE)
    {
        if (g_load_ctrl_info.manual_new_state == CTRL_STATE_CONN) {
            DO_RECONNECT();
            R_LOAD_CTRL_SetState(g_load_ctrl_info.manual_new_state);
        }
        else {
            DO_DISCONNECT();
            R_LOAD_CTRL_SetState(g_load_ctrl_info.manual_new_state);
        }

        /* Recheck immediately */
        RESET_REMOTE_RECONNECT_DELAY_COUNT();

        /* Acknowledge */
        g_load_ctrl_info.manual_state_change = FALSE;
    }
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_GetOutputState
* Interface     : uint8_t R_LOAD_CTRL_GetOutputState(
*               :     void
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : Current status of relay:
*                   1: RELAY_CONNECTED
*                   0: RELAY_DISCONNECTED
******************************************************************************/
uint8_t R_LOAD_CTRL_GetOutputState(void)
{
    return RELAY_GetStatus();
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_RemoteDisc
* Interface     : void R_LOAD_CTRL_RemoteDisc(
*               :     void
*               : );
* Description   : Remote disconnect. Remotely, via a communication channel;
* Arguments     :
* Function Calls:
* Return Value  : 0 is OK
******************************************************************************/
uint8_t R_LOAD_CTRL_RemoteDisc(void)
{
    /* Mode checking */
    if (g_load_ctrl_mode == 0)
    {
        r_load_ctrl_mode0_enter();
    }
    else
    {
        DO_DISCONNECT();
        R_LOAD_CTRL_SetState(CTRL_STATE_DISC);
    }

    /* Return OK */
    return LOADCTRL_RET_OK;
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_RemoteReconn
* Interface     : void R_LOAD_CTRL_RemoteReconn(
*               :     void
*               : );
* Description   : Remote reconnect. Remotely, via a communication channel;
* Arguments     : 
* Function Calls: 
* Return Value  : 0 is OK
******************************************************************************/
uint8_t R_LOAD_CTRL_RemoteReconn(void)
{
	uint8_t return_code = LOADCTRL_RET_OK;
    
    /* Mode checking */
    if (g_load_ctrl_mode == 0)
    {
        r_load_ctrl_mode0_enter();
    }
    else if (g_load_ctrl_state != CTRL_STATE_DISC)
    {
        /* Not allow remote reconnect if previous state is not DISC */
        return_code = LOADCTRL_RET_ERROR;
    }
    else
    {
        switch ( g_load_ctrl_mode )
        {
            case 1:
            case 3:
            case 5:
            case 6:
                g_load_ctrl_info.remote_state_change = TRUE;
                g_load_ctrl_info.remote_new_state = CTRL_STATE_READY;
                break;
            case 2:
            case 4:
                g_load_ctrl_info.remote_state_change = TRUE;
                g_load_ctrl_info.remote_new_state = CTRL_STATE_CONN;
                break;
            default:
                break;
        }
        r_load_ctrl_remote_polling_processing();
    }

    /* Return OK */
    return LOADCTRL_RET_OK;
}


/******************************************************************************
* Function Name : R_LOAD_CTRL_LocalDisconn
* Interface     : uint8_t R_LOAD_CTRL_LocalDisconn(
*               :     void
*               : );
* Description   : Locally, by a function of the meter, e.g. limiter, prepayment 
* Arguments     : 
* Function Calls: 
* Return Value  : 0 is OK
******************************************************************************/
uint8_t R_LOAD_CTRL_LocalDisconn (void)
{
    /* This API is deprecated: for backward compatibility only
    * Calling this API will transfer signal directly to local channel 0
    */
    return R_LOADCTRL_LocalMgmt_Disconn(0);
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_LocalReconn
* Interface     : uint8_t R_LOAD_CTRL_LocalReconn(
*               :     void
*               : );
* Description   : Locally, by a function of the meter, e.g. limiter, prepayment 
* Arguments     :
* Function Calls: 
* Return Value  : 0 is OK
******************************************************************************/
uint8_t R_LOAD_CTRL_LocalReconn (void)
{
    /* This API is deprecated: for backward compatibility only
    * Calling this API will transfer signal directly to local channel 0
    */
    return R_LOADCTRL_LocalMgmt_Reconn(0);
}

/******************************************************************************
* Function Name : R_LOADCTRL_LocalMgmt_Disconn
* Interface     : uint8_t R_LOADCTRL_LocalMgmt_Disconn(uint8_t local_func_index)
* Description   : Local function management disconnection request
* Arguments     : uint8_t local_func_index: index of local function
* Function Calls: TBD
* Return Value  : 0 is OK
******************************************************************************/
uint8_t R_LOADCTRL_LocalMgmt_Disconn(uint8_t local_func_index)
{
    uint8_t return_code = LOADCTRL_RET_OK;

    /* Check max supported index */
    CHECK_MAX_CHANNEL_RET_ERROR(local_func_index, R_LOAD_CONTROL_LOCAL_MAX_FUNCTIONS);
    /* Raise request */
    MODIFY_TYPE_STATE(CTRL_STATE_DISC, local_func_index);
    g_load_ctrl_info.local_state_change = TRUE;

    return return_code;
}

/******************************************************************************
* Function Name : R_LOADCTRL_LocalMgmt_Reconn
* Interface     : uint8_t R_LOADCTRL_LocalMgmt_Reconn(uint8_t local_func_index)
* Description   : Local function management reconnection request
* Arguments     : uint8_t local_func_index: index of local function
* Function Calls: TBD
* Return Value  : 0 is OK
******************************************************************************/
uint8_t R_LOADCTRL_LocalMgmt_Reconn(uint8_t local_func_index)
{
    uint8_t return_code = LOADCTRL_RET_OK;

    /* Check max supported index */
    CHECK_MAX_CHANNEL_RET_ERROR(local_func_index, R_LOAD_CONTROL_LOCAL_MAX_FUNCTIONS);
    /* Raise request */
    MODIFY_TYPE_STATE(CTRL_STATE_CONN, local_func_index);
    g_load_ctrl_info.local_state_change = TRUE;

    return return_code;
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_ManDisconn
* Interface     : uint8_t R_LOAD_CTRL_ManDisconn(
*               :     void
*               : );
* Description   : Manual_disconnect. Manually, using e.g. a push button.
* Arguments     : 
* Function Calls: 
* Return Value  : 0 is OK
******************************************************************************/
uint8_t R_LOAD_CTRL_ManDisconn (void)
{
    uint8_t return_code = LOADCTRL_RET_OK;
    /* Mode checking */
    if (g_load_ctrl_mode == 0)
    {
        r_load_ctrl_mode0_enter();
    }
    else
    {
        // USER CODE
        if ((g_load_ctrl_mode == 1) || (g_load_ctrl_mode == 2) || (g_load_ctrl_mode == 5))
        {
            g_load_ctrl_info.manual_new_state = CTRL_STATE_READY;
            g_load_ctrl_info.manual_state_change = TRUE;
        }
        else {
            return_code = LOADCTRL_RET_ERROR;
        }
    }
    return return_code;
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_ManReconn
* Interface     : uint8_t R_LOAD_CTRL_ManReconn(
*               :     void
*               : );
* Description   : Manual_reconnect. Manually, using e.g. a push button.
*               : 
* Arguments     : 
* Function Calls: 
* Return Value  : 0 is OK
******************************************************************************/
uint8_t R_LOAD_CTRL_ManReconn (void)
{
    uint8_t return_code = LOADCTRL_RET_OK;
    /* Mode checking */
    if (g_load_ctrl_mode == 0)
    {
        r_load_ctrl_mode0_enter();
    }
    else
    {
        if (g_load_ctrl_state == CTRL_STATE_READY) {
            g_load_ctrl_info.manual_new_state = CTRL_STATE_CONN;
            g_load_ctrl_info.manual_state_change = TRUE;
        }
        else {
            return_code = LOADCTRL_RET_ERROR;
        }
    }
    return 0;
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_SetMode
* Interface     : void R_LOAD_CTRL_SetMode(
*               :     uint8_t mode
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_LOAD_CTRL_SetMode( uint8_t mode )
{
	uint8_t return_code = LOADCTRL_RET_OK;

    /* In Mode (0) the disconnect control object is always in [connected] state. */
    if (mode == 0)
    {
        r_load_ctrl_mode0_enter();
    }

    /* Update mode */
    g_load_ctrl_mode = mode;

    g_load_ctrl_info.local_state_change = TRUE;

    /* Write Control mode */
    EPR_Write(g_storage_info_ctrl_control_mode.address, (uint8_t *)&g_load_ctrl_mode, g_storage_info_ctrl_control_mode.length);
    /* Return OK */
	return return_code;
}

/******************************************************************************
* Function Name : r_load_ctrl_mode0_enter
* Interface     : void r_load_ctrl_mode0_enter(
*               :     void
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void r_load_ctrl_mode0_enter (void)
{
    /* In Mode(0) the Ctrl obj is always in connnected state */
    DO_RECONNECT();
    R_LOAD_CTRL_SetState(CTRL_STATE_CONN);
}


/******************************************************************************
* Function Name : R_LOAD_CTRL_SetState
* Interface     : void R_LOAD_CTRL_SetState(
*               :     uint8_t state
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_LOAD_CTRL_SetState ( ctrl_state_t state )
{
    uint8_t return_code = LOADCTRL_RET_OK;

    g_load_ctrl_state = state;
    /* Write Control state */
    return EPR_Write(g_storage_info_ctrl_control_state.address, (uint8_t *)&g_load_ctrl_state, g_storage_info_ctrl_control_state.length);
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_LocalControl_PollingProcessing
* Interface     : void R_LOAD_CTRL_LocalControl_PollingProcessing(
*               :     void
*               : );
* Description   : Do the following tasks
*               : + Check and activate Passive Relay Time profile
*               : + Local Auto reconnection
*               : + Local disconnection & Event handling
* Arguments     : <none>
* Return Value  : void
******************************************************************************/
void R_LOAD_CTRL_LocalControl_PollingProcessing(void)
{
	/* 
	 * Working mode:
	 *    0: Normal, 
	 *    1: Attempt at reconecting/Lockout
	 *    2: Reconnected
	 */

	/* Auto reconnection */
	{
		/* Mode switching  */
		{
			/* Relay output status = 1? */
			if (( g_load_ctrl_local_state_info[R_LOADCONTROL_LOCAL_SIGNAL_OVER_LOAD] != CTRL_STATE_CONN ||
				g_load_ctrl_local_state_info[R_LOADCONTROL_LOCAL_SIGNAL_OVER_CURRENT] != CTRL_STATE_CONN))
			{
				/* Trigger auto reconnect process */
				g_ctrl_relay_progess.mode = 1;
                if (g_ctrl_relay_progess.mode_old != g_ctrl_relay_progess.mode)
                {
    				if (g_ctrl_relay_progess.reconnection_count < g_ctrl_relay_params.retry_count)
    				{
    					g_ctrl_relay_progess.reconnection_count++;
    					timer_counter_start( 
    						COUNTER_ID_AUTO_RECONNECT_INTERVAL , 
    						g_ctrl_relay_params.delay_interval
    					);
    				}
    				else
    				{
    					/* Enter lockout period */
    					timer_counter_start( 
    						COUNTER_ID_AUTO_RECONNECT_INTERVAL , 
    						g_ctrl_relay_params.lockout_period
    					);
    					g_ctrl_relay_progess.reconnection_count = 0;
    				}
                }
			}
		}

		/* Mode processing */
		if (g_ctrl_relay_progess.mode == 0) /* Normal operation */
		{
			/* Waiting mode. Do nothing */
		}
		else if (g_ctrl_relay_progess.mode == 1)	/* Attempt at reconnecting */
		{
			/* Waiting interval period */
			if (timer_counter_get_value(COUNTER_ID_AUTO_RECONNECT_INTERVAL) == 0)
			{
				/* Auto re-connect */
				R_LOADCTRL_LocalMgmt_Reconn(R_LOADCONTROL_LOCAL_SIGNAL_OVER_LOAD);
				R_LOADCTRL_LocalMgmt_Reconn(R_LOADCONTROL_LOCAL_SIGNAL_OVER_CURRENT);
				g_ctrl_relay_progess.mode = 2;
			}
		}
		else if (g_ctrl_relay_progess.mode == 2)	/* Waiting for Load stabilization */
		{
			/* Start counter to check if load is stable. */
			if (g_load_ctrl_state == CTRL_STATE_CONN &&
				g_ctrl_relay_progess.signal_info.is_overload == FALSE &&
				g_ctrl_relay_progess.signal_info.is_over_current == FALSE)
			{
                g_ctrl_relay_progess.flag.IsEmergencyProfileActivated = FALSE;
				g_ctrl_relay_progess.reconnection_count = 0;
				g_ctrl_relay_progess.mode = 0;
			}
		}
	}

	/* Update threshold profile */
	if (g_ctrl_relay_progess.mode_old != g_ctrl_relay_progess.mode)
	{
		/* Update Overload threshold */
		R_LOAD_CTRL_UpdateLimiterThreshold();
		g_ctrl_relay_progess.mode_old = g_ctrl_relay_progess.mode;
	}
}



/******************************************************************************
* Function Name : R_LOAD_CTRL_Determine_OverCurrentEventStatus
* Interface     : uint8_t R_LOAD_CTRL_Determine_OverCurrentEventStatus(uint8_t state, uint8_t * p_is_occur)
* Description   :
* Arguments     :
*                   state       : INPUT
*                   p_is_occur  : OUTPUT
* Return Value  : uint8_t change
******************************************************************************/
uint8_t R_LOAD_CTRL_Determine_OverCurrentEventStatus(uint8_t state, uint8_t * p_is_occur)
{
	uint16_t interval_set;
    static uint8_t old_state = FALSE;
    uint8_t change = FALSE;

    uint32_t duration_occur = g_limiter_min_over_threshold_duration;
    uint32_t duration_restore = g_limiter_min_under_threshold_duration;

    if (state == TRUE)
    {   
        if (g_ctrl_relay_progess.signal_info.over_current_occur_count <= duration_occur)
        {
            g_ctrl_relay_progess.signal_info.over_current_occur_count++;
        }
        g_ctrl_relay_progess.signal_info.over_current_release_count = 0;
    }
    else
    {
        if (g_ctrl_relay_progess.signal_info.over_current_release_count <= duration_restore)
        {
            g_ctrl_relay_progess.signal_info.over_current_release_count++;
        }
        g_ctrl_relay_progess.signal_info.over_current_occur_count = 0;
    }

    /* Occurrence */
    if (g_ctrl_relay_progess.signal_info.over_current_occur_count > duration_occur)        
    {   
        R_LOADCTRL_LocalMgmt_Disconn(R_LOADCONTROL_LOCAL_SIGNAL_OVER_CURRENT);
        g_ctrl_relay_progess.flag.IsEmergencyProfileActivated = TRUE;

        if (g_ctrl_relay_progess.signal_info.is_over_current == FALSE)
        {
            g_ctrl_relay_progess.signal_info.is_over_current = TRUE;
            g_ctrl_relay_progess.signal_info.wait_over_current_restoration = TRUE;
            
            *p_is_occur = TRUE;
            change = TRUE;
        }
    }

    /* Restoration */
    if (g_ctrl_relay_progess.signal_info.over_current_release_count > duration_restore)
    {
        if (g_ctrl_relay_progess.signal_info.wait_over_current_restoration)
        {
            if (RELAY_GetStatus() == RELAY_DISCONNECTED)
            {
                /* Reset */
                g_ctrl_relay_progess.signal_info.over_current_release_count = 0;
            }
            else
            {
                g_ctrl_relay_progess.signal_info.is_over_current = FALSE;
                g_ctrl_relay_progess.signal_info.wait_over_current_restoration = FALSE;

                *p_is_occur = FALSE;
                change = TRUE;
            }
        }
    }

    return change;
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_Determine_OverLoadEventStatus
* Interface     : uint8_t R_LOAD_CTRL_Determine_OverLoadEventStatus(uint8_t state, uint8_t * p_is_occur)
* Description   :
* Arguments     :
*                   state       : INPUT
*                   p_is_occur  : OUTPUT
* Return Value  : uint8_t change
******************************************************************************/
uint8_t R_LOAD_CTRL_Determine_OverLoadEventStatus(uint8_t state, uint8_t * p_is_occur)
{
	uint16_t interval_set;
    static uint8_t old_state = FALSE;
    uint8_t change = FALSE;

    uint32_t duration_occur = g_limiter_min_over_threshold_duration;
    uint32_t duration_restore = g_limiter_min_under_threshold_duration;

    if (state == TRUE)
    {   
        if (g_ctrl_relay_progess.signal_info.overload_occur_count <= duration_occur)
        {
            g_ctrl_relay_progess.signal_info.overload_occur_count++;
        }
        g_ctrl_relay_progess.signal_info.overload_release_count = 0;
    }
    else
    {
        if (g_ctrl_relay_progess.signal_info.overload_release_count <= duration_restore)
        {
            g_ctrl_relay_progess.signal_info.overload_release_count++;
        }
        g_ctrl_relay_progess.signal_info.overload_occur_count = 0;
    }

    /* Occurrence */
    if (g_ctrl_relay_progess.signal_info.overload_occur_count > duration_occur)        
    {                      
        R_LOADCTRL_LocalMgmt_Disconn(R_LOADCONTROL_LOCAL_SIGNAL_OVER_LOAD);
        g_ctrl_relay_progess.flag.IsEmergencyProfileActivated = TRUE;

        if (g_ctrl_relay_progess.signal_info.is_overload == FALSE)
        {
            g_ctrl_relay_progess.signal_info.is_overload = TRUE;
            g_ctrl_relay_progess.signal_info.wait_over_load_restoration = TRUE;
            
            *p_is_occur = TRUE;
            change = TRUE;
        }
    }

    /* Restoration */
    if (g_ctrl_relay_progess.signal_info.overload_release_count > duration_restore)
    {
        if (g_ctrl_relay_progess.signal_info.wait_over_load_restoration)
        {
            if (RELAY_GetStatus() == RELAY_DISCONNECTED)
            {
                /* Reset */
                g_ctrl_relay_progess.signal_info.overload_release_count = 0;
            }
            else
            {
                g_ctrl_relay_progess.signal_info.is_overload = FALSE;
                g_ctrl_relay_progess.signal_info.wait_over_load_restoration = FALSE;

                *p_is_occur = FALSE;
                change = TRUE;
            }
        }
    }

    return change;
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_ActivateEmergencyProfile
* Interface     : void R_LOAD_CTRL_ActivateEmergencyProfile(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_LOAD_CTRL_ActivateEmergencyProfile(void)
{
    g_ctrl_relay_progess.flag.IsEmergencyProfileActivated = TRUE;
}

void R_LOAD_CTRL_ActivateNormalProfile(void);
/******************************************************************************
* Function Name : R_LOAD_CTRL_ActivateNormalProfile
* Interface     : void R_LOAD_CTRL_ActivateNormalProfile(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_LOAD_CTRL_ActivateNormalProfile(void)
{
    g_ctrl_relay_progess.flag.IsEmergencyProfileActivated = FALSE;
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_UpdateLimiterThreshold
* Interface     : void R_LOAD_CTRL_UpdateLimiterThreshold(
*               :     void
*               : );
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_LOAD_CTRL_UpdateLimiterThreshold(void)
{
	if (g_ctrl_relay_progess.flag.IsEmergencyProfileActivated == FALSE)
	{
#if (defined( R_LOAD_LIMIT_DATA_TYPE ) && R_LOAD_LIMIT_DATA_TYPE == 0)
		EVENT_SetOverLoadThreshold(g_limiter_normal * 1000.0f);		/* Threshold is Unsigned Integer (kW) */
#else
		EVENT_SetOverLoadThreshold(g_limiter_normal);				/* Threshold is Float (W) */
#endif
	}
	else
	{
#if (defined( R_LOAD_LIMIT_DATA_TYPE ) && R_LOAD_LIMIT_DATA_TYPE == 0)
		EVENT_SetOverLoadThreshold(g_limiter_emergency * 1000.0f);	/* Threshold is Unsigned Integer (kW) */
#else
		EVENT_SetOverLoadThreshold(g_limiter_emergency);				/* Threshold is Float (W) */
#endif
	}
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_Init
* Interface     : void R_LOAD_CTRL_Init(
*               :     void
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_LOAD_CTRL_Init ( void )
{
    memset(&g_load_ctrl_local_state_info[0], CTRL_STATE_CONN, sizeof(g_load_ctrl_local_state_info));

    /* Trigger to rescan local state after initialization */
    g_check_state_at_init_flag = TRUE;

    /* Recheck immediately */
    RESET_REMOTE_RECONNECT_DELAY_COUNT();
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_PollingProcess
* Interface     : void R_LOAD_CTRL_PollingProcess(
*               :     void
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_LOAD_CTRL_PollingProcess (void)
{
    uint8_t status = RELAY_GetStatus();
    uint8_t old_status = RELAY_GetPreviousStatus();

    if (gp_inst_DataPop != NULL)
    {
        timer_counter_descrease_each_sec();
    }

    /* Check RELAY & current (A) */
    if (status != old_status)
    {
        if (status == RELAY_CONNECTED)
        {
            g_event_flag.bits.relay_status_changed = TRUE;
        }
        else
        {
            g_event_flag.bits.relay_status_changed = TRUE;
        }
        RELAY_SetPreviousStatus(status);
    }

    r_load_ctrl_local_mgmt_polling_processing();
    r_load_ctrl_remote_polling_processing();
    r_load_ctrl_manual_polling_processing();

    /* Explananation:
    * The below routine like a workaround for current implementation
    * On testing: after remote reconnect, currently it's expected to recovered by limiter
    * But in fact, limiter only has role to actuate the relay when over or under threshold
    * So if we scan the state directly, it will switch directly to connection state if all local function is ready
    * This small routine below will add a small 'remote reconnect delay time'
    *   + Each calling, it will delay a fix small amount of time until reaching the defined timing
    *   + To prevent halting other application, it will wait in 10ms period, so please be cautious about the uint16_t capacity
    */
    if (g_load_ctrl_info.remote_reconn_delay_count < REMOTE_RECONNECT_DELAY_COUNT_x10ms) {
        /* Wait only 10ms each to prevent stopping other  */
        WRP_EXT_HwDelay(10, NULL);
        g_load_ctrl_info.remote_reconn_delay_count++;
        /* Trigger to re-scan ready state */
        if (g_load_ctrl_info.remote_reconn_delay_count >= REMOTE_RECONNECT_DELAY_COUNT_x10ms)
        {
            g_load_ctrl_info.local_state_change = TRUE;
        }
    }

	R_LOAD_CTRL_LocalControl_PollingProcessing(); 

    /* Reconnect mannual */
    if (g_load_ctrl_manual_reconn_flag != FALSE)
    {
        /* LCD scroll button is pressed and held in 2 second
         * g_load_ctrl_manual_reconn_flag will be raised in RTC periodic
         */
        R_LOAD_CTRL_ManReconn();
        g_load_ctrl_manual_reconn_flag = FALSE;
    }
    else
    {

    }
}

/******************************************************************************
* Function Name : R_LIMITER_Set_NormalThreashold
* Interface     : uint8_t R_LIMITER_Set_NormalThreashold(
*               :     float32_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_LIMITER_Set_NormalThreashold ( float32_t value )
{
	g_limiter_normal = (limit_threshold_type_t)value;
	R_LOAD_CTRL_UpdateLimiterThreshold();
    /* Back up new Limiter normal */
    EPR_Write(g_storage_info_limiter_normal.address, (uint8_t *)&g_limiter_normal, g_storage_info_limiter_normal.length);
    return TRUE;
}

/******************************************************************************
* Function Name : R_LIMITER_Set_EmergencyThreashold
* Interface     : uint8_t R_LIMITER_Set_EmergencyThreashold(
*               :     float32_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_LIMITER_Set_EmergencyThreashold ( float32_t value )
{
	g_limiter_emergency = (limit_threshold_type_t)value;
	R_LOAD_CTRL_UpdateLimiterThreshold();
    /* Write new Limiter emergency */
    EPR_Write(g_storage_info_limiter_emergency.address, (uint8_t *)&g_limiter_emergency, g_storage_info_limiter_emergency.length);
    return TRUE;
}


/******************************************************************************
* Function Name : R_LIMITER_Init
* Interface     : void R_LIMITER_Init(
*               :     void
*               : );
* Description   : 
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_LIMITER_Init(void)
{
	R_LOAD_CTRL_UpdateLimiterThreshold();
}

/******************************************************************************
* Function Name : R_LIMITER_Get_OverThresholdDuration
* Interface     : uint8_t R_LIMITER_Get_OverThresholdDuration(uint32_t *p_data)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_LIMITER_Get_OverThresholdDuration(uint32_t *const p_data)
{
    *p_data = g_limiter_min_over_threshold_duration;
    
    return TRUE;
}

/******************************************************************************
* Function Name : R_LIMITER_Set_OverThresholdDuration
* Interface     : uint8_t R_LIMITER_Set_OverThresholdDuration(uint32_t value_input)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_LIMITER_Set_OverThresholdDuration(uint32_t value_input)
{
    g_limiter_min_over_threshold_duration = value_input;
    g_event_persistent_time.overload_occur = (uint8_t)value_input;
    return TRUE;
}

/******************************************************************************
* Function Name : R_LIMITER_Get_UnderThresholdDuration
* Interface     : uint8_t R_LIMITER_Get_UnderThresholdDuration(uint32_t *p_data)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_LIMITER_Get_UnderThresholdDuration(uint32_t *const p_data)
{
    *p_data = g_limiter_min_under_threshold_duration;
    
    return TRUE;
}

/******************************************************************************
* Function Name : R_LIMITER_Set_UnderThresholdDuration
* Interface     : uint8_t R_LIMITER_Set_UnderThresholdDuration(uint32_t value_input)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_LIMITER_Set_UnderThresholdDuration(uint32_t value_input)
{
    g_limiter_min_under_threshold_duration = value_input;
    g_event_persistent_time.overload_restore = (uint8_t)value_input;
    return TRUE;
}


/******************************************************************************
* Function Name : R_LOAD_CTRL_Restore
* Interface     : uint8_t R_LOAD_CTRL_Restore(
*               :     void
*               : );
* Description   : This function load data from storage to RAM
* Arguments     : 
* Function Calls: 
* Return Value  : Return if storage action is success or not.
*                       STORAGE_OK (0)      : OK   
*                       other value         : NOT OK   
******************************************************************************/
uint8_t R_LOAD_CTRL_Restore(void)
{
    uint8_t storage_return_code = STORAGE_OK;
    uint8_t result_code = STORAGE_OK;

    /* Limiter normal */
    storage_return_code = EPR_Read(
        g_storage_info_limiter_normal.address, 
        (uint8_t *)&g_limiter_normal, 
        g_storage_info_limiter_normal.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Limiter emergency */
    storage_return_code = EPR_Read(
        g_storage_info_limiter_emergency.address, 
        (uint8_t *)&g_limiter_emergency, 
        g_storage_info_limiter_emergency.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }
    /* Limiter over duration(min) */
    storage_return_code = EPR_Read(
        g_storage_info_limiter_min_over_threshold_duration.address, 
        (uint8_t *)&g_limiter_min_over_threshold_duration, 
        g_storage_info_limiter_min_over_threshold_duration.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Limiter under duration(min) */
    storage_return_code = EPR_Read(
        g_storage_info_limiter_min_under_threshold_duration.address, 
        (uint8_t *)&g_limiter_min_under_threshold_duration, 
        g_storage_info_limiter_min_under_threshold_duration.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Control state */
    storage_return_code = EPR_Read(
        g_storage_info_ctrl_control_state.address, 
        (uint8_t *)&g_load_ctrl_state, 
        g_storage_info_ctrl_control_state.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Control mode */
    storage_return_code = EPR_Read(
        g_storage_info_ctrl_control_mode.address, 
        (uint8_t *)&g_load_ctrl_mode, 
        g_storage_info_ctrl_control_mode.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Control relay status */
    storage_return_code = EPR_Read(
        g_storage_info_ctrl_relay_status.address, 
        (uint8_t *)&g_load_ctrl_relay_status, 
        g_storage_info_ctrl_relay_status.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Relay progess status */
    storage_return_code = EPR_Read(
        g_storage_info_ctrl_relay_status.address, 
        (uint8_t *)&g_ctrl_relay_progess, 
        g_storage_info_ctrl_relay_status.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }
    
    /* Validate restore data. Set default value for invalid value */
    if (g_limiter_normal == 0)
    {
        g_limiter_normal = LIMITER_THRESHOLD_NORMAL_DEFAULT;
    }
    if (g_limiter_emergency == 0)
    {
        g_limiter_emergency = LIMITER_THRESHOLD_NORMAL_DEFAULT;
    }
    if (g_limiter_min_over_threshold_duration == 0)
    {
        g_limiter_min_over_threshold_duration = LIMITER_DURATION_DEFAULT;
    }
    
    if (g_limiter_min_under_threshold_duration == 0)
    {
        g_limiter_min_under_threshold_duration = LIMITER_DURATION_DEFAULT;
    }

    if (result_code != STORAGE_OK)
    {
        return STORAGE_ERROR;
    }

    return STORAGE_OK;
}
/******************************************************************************
* Function Name : R_LOAD_CTRL_Backup
* Interface     : void R_LOAD_CTRL_Restore(
*               :     void
*               : );
* Description   : store data from RAM to storage
* Arguments     : 
* Function Calls: 
* Return Value  : Return if storage action is success or not.
*                       STORAGE_OK (0)      : OK   
*                       other value         : NOT OK   
******************************************************************************/
uint8_t R_LOAD_CTRL_Backup(void)
{
    uint8_t storage_return_code = STORAGE_OK;
    uint8_t result_code = STORAGE_OK;

    /* Control relay status */
    storage_return_code = EPR_Write(
        g_storage_info_ctrl_relay_status.address, 
        (uint8_t *)&g_load_ctrl_relay_status, 
        g_storage_info_ctrl_relay_status.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Relay progess status */
    storage_return_code = EPR_Write(
        g_storage_info_ctrl_relay_progess.address, 
        (uint8_t *)&g_ctrl_relay_progess, 
        g_storage_info_ctrl_relay_progess.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    if (result_code != STORAGE_OK)
    {
        return STORAGE_ERROR;
    }

    return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_LOAD_CTRL_Format
* Interface     : uint8_t R_LOAD_CTRL_Restore(
*               :     void
*               : );
* Description   : format data, write default data to storage.
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_LOAD_CTRL_Format(void)
{
    uint8_t storage_return_code = STORAGE_OK;
    uint8_t result_code = STORAGE_OK;

    /* Limiter normal */
    storage_return_code = EPR_Write(
        g_storage_info_limiter_normal.address, 
        (uint8_t *)&g_limiter_normal_default, 
        g_storage_info_limiter_normal.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Limiter emergency */
    storage_return_code = EPR_Write(
        g_storage_info_limiter_emergency.address, 
        (uint8_t *)&g_limiter_emergency_default, 
        g_storage_info_limiter_emergency.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Limiter over duration(min) */
    storage_return_code = EPR_Write(
        g_storage_info_limiter_min_over_threshold_duration.address, 
        (uint8_t *)&g_limiter_duration_default, 
        g_storage_info_limiter_min_over_threshold_duration.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Limiter under duration(min) */
    storage_return_code = EPR_Write(
        g_storage_info_limiter_min_under_threshold_duration.address, 
        (uint8_t *)&g_limiter_duration_default, 
        g_storage_info_limiter_min_under_threshold_duration.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    /* Control state */
    storage_return_code = EPR_Write(
        g_storage_info_ctrl_control_state.address, 
        (uint8_t *)&g_load_ctrl_state_default, 
        g_storage_info_ctrl_control_state.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }
   
    /* Control mode */
    EPR_Write(
        g_storage_info_ctrl_control_mode.address, 
        (uint8_t *)&g_ctrl_mode_default, 
        g_storage_info_ctrl_control_mode.length
    );
    if (storage_return_code != STORAGE_OK)
    {
        result_code = storage_return_code;
    }

    if (result_code != STORAGE_OK)
    {
        return STORAGE_ERROR;
    }
    
    return STORAGE_OK;
}
