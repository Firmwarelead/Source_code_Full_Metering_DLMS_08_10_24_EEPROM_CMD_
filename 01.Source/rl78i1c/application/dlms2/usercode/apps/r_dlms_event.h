/***********************************************************************************************************************
Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_event.h
* Version      : Version
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 2018-03-29 			New create
// 2019-07-04 16:56:45	DEPRECATED R_DLMS_EventReport_LastGasp due to fast push

#ifndef _R_DLMS_EVENT_H
#define _R_DLMS_EVENT_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "typedef.h"

/* MW/Core */
#include "em_core.h"        /* EM Core APIs */

/* Meter Event application */
#include "event.h"

/* DLMS Apps */
#include "r_dlms_app.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* CONFIGURATION */
#define EVENT_ESW_LENGTH			(128)
#define EVENT_ESW_BUFFER_LENGTH		(EVENT_ESW_LENGTH/8)
#define EVENT_PROFILE_NUMBER		(7)

/* API FOR USAGE */
#define EVENT_OCCURRENCE				(EVENT_STATE_ENTER)
#define EVENT_RESTORATION				(EVENT_STATE_RELEASE)

#define EVENT_STATE_IS_OCCUR_MASK		(0x01)
#define EVENT_STATE_NON_PUSH			(0x02)
#define EVENT_STATE_NULL				(0xFF)

#define EVENT_OCCURRENCE_NON_PUSH		(EVENT_OCCURRENCE	| EVENT_STATE_NON_PUSH)
#define EVENT_RESTORATION_NON_PUSH		(EVENT_RESTORATION	| EVENT_STATE_NON_PUSH)

/* Special event bits */
#define EVENT_BIT_NULL				(255)
#define EVENT_BIT_NOT_SPECIFIED		(255)
#define EVENT_ID_NULL 				(0xFFFF)

/* For event push */
#define EVENT_BIT_STATUS_SET        (0)
#define EVENT_BIT_STATUS_CLEAR      (1)

#define EVENT_OCCURRENCE				(EVENT_STATE_ENTER)
#define EVENT_RESTORATION				(EVENT_STATE_RELEASE)
#define EVENT_STATE_IS_OCCUR_MASK		(0x01)
#define EVENT_STATE_NON_PUSH			(0x02)
#define EVENT_STATE_NULL				(0xFF)
#define EVENT_OCCURRENCE_NON_PUSH		(EVENT_OCCURRENCE	| EVENT_STATE_NON_PUSH)
#define EVENT_RESTORATION_NON_PUSH		(EVENT_RESTORATION	| EVENT_STATE_NON_PUSH)

/******************************************************************
 * Event Status Bit definition
 ******************************************************************/

/******************************************************************************************************
 * Event Status Bit Mapping
 ******************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tagEventNonRolloverEventLog
{
    EVENT_NAME_T type;
    EVENT_STATE_T status;
    EVENT_DATE_TIME_T captured_time;

} NON_ROLLOVER_EVENTLOG_T;

typedef struct tagEventSinglePairEventLog
{
    EVENT_NAME_T type;
    EVENT_STATE_T status;
    EVENT_DATE_TIME_T captured_time;

} SINGLE_PAIR_EVENTLOG_T;

typedef union tag_dlms_event_occurence_t
{
	struct dlms_event_occurence_bit_t
	{
		uint8_t is_occur:1;
		uint8_t is_nopush:1;
		uint8_t reserved1:1;
		uint8_t reserved2:1;
		uint8_t reserved3:1;
		uint8_t reserved4:1;
		uint8_t reserved5:1;
		uint8_t reserved6:1;
	} bits;
	uint8_t byte;
} dlms_event_occurence_t;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
extern uint8_t g_dlms_ESW[];
extern uint8_t g_dlms_ESWF[];
extern uint16_t g_dlms_current_event_code[EVENT_PROFILE_NUMBER];
/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

uint8_t R_DLMS_EVENT_IsEventFlagLogged(void);
void R_DLMS_Event_DirectInvoke_LastGasp(void);
void R_DLMS_EventAck_LastGaspPushed(void);
uint16_t R_DLMS_GetTheLastEventCode(EVENT_TYPE_T type);

void EVENT_OnEventCallBack(EVENT_ARGS_T *pEvent_arg);

/* Storage related API */
void R_DLMS_EventRestore(void);
void R_DLMS_EventBackup(void);
void R_DLMS_EventFormat(void);

/* Common */
void R_DLMS_EVENT_Init(void);
void R_DLMS_Event_PollingProcessing (void);

#endif /* _R_DLMS_EVENT_H */