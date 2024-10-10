/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_ctrl
* Version      : 0.1
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
#ifndef _R_DLMS_CTRL_H
#define _R_DLMS_CTRL_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define R_LOAD_CONTROL_ENABLE		                            (TRUE)

#define R_LOAD_CONTROL_LOCAL_MAX_FUNCTIONS        3

#define REPORT_ENABLE_DISABLE_LOAD_LIMIT_FN_BY_RELAY_STATE		(TRUE)

#define HDLC_PORT_IS_LOCAL_LOAD_CONTROL							(FALSE)

/* 
 *     Define data type of load limit, available setting:
 * 
 *     +-------------+---------------------------+------------+
 *     |   Option    | Datatype                  |            |
 *     |-------------+---------------------------+------------|
 *     |     0       | Integer	(Unsigned8)		 | Unit = kW  |
 *     |     1       | Float	(Float32)	     | Unit = W   |
 *     |-------------+---------------------------+------------|
 * 
 */
#define R_LOAD_LIMIT_DATA_TYPE					  1

#if (R_LOAD_LIMIT_DATA_TYPE == 0)
	typedef int8_t limit_threshold_type_t;
#else
	typedef float32_t limit_threshold_type_t;
#endif /* R_LOAD_LIMIT_DATA_TYPE */



/*********************************************************************************************************************** 
 * CONFIGURE
 ***********************************************************************************************************************/

/* Time Interval between auto-reconnection attempt */
#define TIME_INTERVAL_DEFAULT						(120)			/* 2 (min) */
#define LOCK_OUT_TIME_DEFAULT						(300)           /* 5 (min) */

/* Number of Auto reconnection attempts */
#define NO_OF_REPETITIONS_DEFAULT					(4)

#define LIMITER_DURATION_DEFAULT	                (TIME_INTERVAL_DEFAULT)

#define LOADCTRL_STATE_DEFAULT						(2)
#define LOADCTRL_MODE_DEFAULT						(6)

#if(defined( R_LOAD_LIMIT_DATA_TYPE ) && R_LOAD_LIMIT_DATA_TYPE == 0)
	/* Integer - kW */ 
	#define LIMITER_THRESHOLD_NORMAL_DEFAULT	        (2)		/* 2 kW */
	#define LIMITER_THRESHOLD_EMERGENCY_DEFAULT	        (2)		/* 2 kW */
#else
	/* Float - W */
	#define LIMITER_THRESHOLD_NORMAL_DEFAULT	        (2200.0f)		/* 2200W */
	#define LIMITER_THRESHOLD_EMERGENCY_DEFAULT	        (2200.0f)		/* 2200W */
#endif /* R_LOAD_LIMIT_DATA_TYPE */

/* 
 * Relay activation date and time:
 * Format = { 
 *             year_high, year_low, month, day_of_month, day_of_week, 
 * 	           hour, minute, second, hundredths, deviation_high, deviation_low, clock_status 
 * }
 */
#define RELAY_ACTIVATION_DATE_AND_TIME_DEFAULT		{ 0x07, 0xE2, 0x01, 0x01, 0x01, 12 , 34, 56, 0x00, 0x01, 0xA4, 0x00 }


/***********************************************************************************************************************
Return code
***********************************************************************************************************************/
#define LOADCTRL_RET_OK                     (0x00)              /* Load control app return OK */
#define LOADCTRL_RET_ERROR                  (0x80)              /* Load control app return ERROR */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/* Load Limit Function Status (Class 70) */
typedef enum tag_ctrl_state_t
{
    CTRL_STATE_DISC = 0,
    CTRL_STATE_CONN,
    CTRL_STATE_READY
} ctrl_state_t;


/* Load limit value.in kW (Class 71) */

typedef enum tag_ctrl_local_trigger_signal_t
{
	R_LOADCONTROL_LOCAL_SIGNAL_CASEOPEN,
	R_LOADCONTROL_LOCAL_SIGNAL_OVER_LOAD,
	R_LOADCONTROL_LOCAL_SIGNAL_OVER_CURRENT,
} r_ctrl_local_trigger_signal_t;

typedef struct tagRelaySignalInfo
{
	/* Over current */
	uint8_t		is_over_current						:1;
	uint8_t		over_current_continous				:1;
	/* Over load */
    uint8_t 	is_overload        					:1;
	uint8_t 	overload_continous					:1;

	uint8_t 	wait_over_current_restoration 		:1;
	uint8_t 	wait_over_load_restoration 			:1;
    
	uint32_t	over_current_occur_count;
	uint32_t	over_current_release_count;

    uint32_t	overload_occur_count;
	uint32_t	overload_release_count;
} RelaySignalInfo_t;

typedef struct tagRelayAutoDisconnectParameter_t
{
	uint16_t 	lockout_period;
	uint16_t 	delay_interval;
	uint8_t 	retry_count;
} RelayAutoDisconnectParameter_t;

typedef struct tagRelayProfileFlag
{
	uint8_t 	IsRelayTimeActivated				:1;
	uint8_t 	IsEmergencyProfileActivated			:1;
} RelayProfileFlag_t;

typedef struct tagRelayProgessStatus
{
	uint8_t 			mode;
	uint8_t 			mode_old;
	uint8_t				reconnection_count;
	RelaySignalInfo_t 	signal_info;
	RelayProfileFlag_t	flag;
	uint8_t 			reserved;
} RelayProgessStatus_t;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/* Load Limit Function Status */
extern uint8_t 						g_load_ctrl_state;
extern uint8_t 						g_load_ctrl_mode;
extern uint8_t 						g_load_ctrl_relay_status;

extern limit_threshold_type_t 		g_limiter_active;
extern limit_threshold_type_t 		g_limiter_normal;
extern limit_threshold_type_t 		g_limiter_emergency;

extern ctrl_state_t 				g_load_ctrl_local_state_info[];

extern RelayProgessStatus_t 		g_ctrl_relay_progess;

extern uint8_t g_load_ctrl_manual_reconn_flag;

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
uint8_t R_LOAD_CTRL_GetOutputState(void);
uint8_t R_LOAD_CTRL_SetMode(uint8_t mode);
uint8_t R_LOAD_CTRL_SetState(ctrl_state_t state);

uint8_t R_LOAD_CTRL_RemoteDisc(void);
uint8_t R_LOAD_CTRL_RemoteReconn(void);

/* Deprecated: will redirect to R_LOADCTRL_LocalMgmt_xxxx API
* Call below 2 API will use local_func_index 0
*/
uint8_t R_LOAD_CTRL_LocalDisconn(void);
uint8_t R_LOAD_CTRL_LocalReconn(void);

uint8_t R_LOADCTRL_LocalMgmt_Disconn(uint8_t local_func_index);
uint8_t R_LOADCTRL_LocalMgmt_Reconn(uint8_t local_func_index);

uint8_t R_LOAD_CTRL_ManDisconn(void);
uint8_t R_LOAD_CTRL_ManReconn(void);

void R_LOAD_CTRL_ActivateEmergencyProfile(void);

uint8_t R_LIMITER_Set_NormalThreashold(float32_t value);
uint8_t R_LIMITER_Restore_ThreasholdNormal(float32_t *value);
uint8_t R_LIMITER_Set_EmergencyThreashold(float32_t value);
uint8_t R_LIMITER_Restore_ThreasholdEmergency(float32_t *value);
uint8_t R_LIMITER_Backup_MinOverThresholdDuration(uint32_t value);
uint8_t R_LIMITER_Restore_MinOverThresholdDuration(uint32_t *value);
uint8_t R_LIMITER_Backup_MinUnderThresholdDuration(uint32_t value);

uint8_t R_LIMITER_Get_OverThresholdDuration(uint32_t *const p_data);
uint8_t R_LIMITER_Set_OverThresholdDuration(uint32_t value_input);

uint8_t R_LIMITER_Get_UnderThresholdDuration(uint32_t *const p_data);
uint8_t R_LIMITER_Set_UnderThresholdDuration(uint32_t value_input);

uint8_t R_LOAD_CTRL_Determine_OverCurrentEventStatus(uint8_t state, uint8_t * p_is_occur);
uint8_t R_LOAD_CTRL_Determine_OverLoadEventStatus(uint8_t state, uint8_t * p_is_occur);

uint8_t R_LOAD_CTRL_Restore(void);
uint8_t R_LOAD_CTRL_Backup(void);
uint8_t R_LOAD_CTRL_Format(void);

void R_LOAD_CTRL_Init(void);
void R_LOAD_CTRL_PollingProcess(void);
void R_LIMITER_Init(void);
void R_LIMITER_PollingProcessing(void);


#endif /* _R_DLMS_CTRL_H */