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
* File Name    : r_dlms_event.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : <Supported platform, e.g 'RL78/I1C Energy Meter Platform'>
* Description  : <Description of file>
************************************************************************************************************************
* History      : 2018-03-12 New creation
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Typedef */
#include "typedef.h"

/* Driver */
#include "r_cg_macrodriver.h"   /* CG Macro Driver */
#include "r_cg_rtc.h"           /* CG RTC Driver */

/* MW/Core */
#include "em_core.h"        /* EM Core APIs */

/* Meter application */
#include "event.h"
#include "r_meter_format.h"

/* DLMS Application */
#include "r_dlms_date_time.h"
#include "r_dlms_event.h"
#include "r_dlms_push.h"
#include "r_dlms_storage.h"
#include "r_dlms_cumulate.h"
#include "r_dlms_factory_config.h"

#include <string.h>

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define BIT_STRING_SET_BIT(__bit_string, __bit_number)    ( __bit_string[ __bit_number / 8] |=  (0x80 >> ( __bit_number % 8)) )
#define BIT_STRING_CLR_BIT(__bit_string, __bit_number)    ( __bit_string[ __bit_number / 8] &=~ (0x80 >> ( __bit_number % 8)) )

#define EVENT_FLAG_NUMBER       (1)
#define DATA_NOTIFY_NUMBER      (1)


#define DLMS_EVENT_CHECK_FLAG(eventflag, callbackfunc) \
			if (eventflag == TRUE)\
			{\
				callbackfunc();\
				/* ACK */\
				eventflag = FALSE;\
			}


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tag_event_flag_t
{
    uint16_t      code;
    uint16_t      script;
} event_flag_t;

typedef struct tag_event_table_item_t
{
    uint8_t      event_ID;
    uint8_t      bit_map;
} event_table_item_t;

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
uint8_t g_dlms_ESW[EVENT_ESW_BUFFER_LENGTH];      /* Event status word (128 bits) */
uint8_t g_dlms_ESWF[EVENT_ESW_BUFFER_LENGTH];     /* Event status word filter (128 bits) */

/* Storage infor */
const DLMS_STORAGE r_storage_info_ESW = {STORAGE_EEPROM_DLMS_ESW_ADDR, STORAGE_EEPROM_DLMS_ESW_SIZE};
const DLMS_STORAGE r_storage_info_ESWF = {STORAGE_EEPROM_DLMS_ESWF_ADDR, STORAGE_EEPROM_DLMS_ESWF_SIZE};
/* Default value */
const uint8_t g_eswf_default[] = R_DLMS_ESWF_DEFAULT;

uint16_t g_dlms_current_event_code[EVENT_PROFILE_NUMBER];

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

#if(defined( R_DLMS_APPS_EVENT_POLLING_ENABLE ) && R_DLMS_APPS_EVENT_POLLING_ENABLE == TRUE)

/******************************************************************************
* Function Name : R_DLMS_Event_DirectInvoke_LastGasp
* Interface     : void R_DLMS_Event_DirectInvoke_LastGasp(
*               :     void
*               : );
* Description   : Directly push on last gasp
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_Event_DirectInvoke_LastGasp ( void )
{
	/* For push */
    uint8_t index;
    uint8_t event_push_filter;
	push_config_t *p_push_config;

	/* Set ESW */
	BIT_STRING_CLR_BIT(g_dlms_ESW, R_EVENT_BIT_FIRST_BREATH);
	BIT_STRING_SET_BIT(g_dlms_ESW, R_EVENT_BIT_LAST_GASP);

	/* Check ESWF */
	event_push_filter = g_dlms_ESWF[R_EVENT_BIT_LAST_GASP/8] & (0x80 >> (R_EVENT_BIT_LAST_GASP % 8));

	/* PUSH_DATA_OUT */
	if (event_push_filter != 0)
	{
		R_DLMS_Push_ServiceCall(R_DLMS_PUSH_ID_EVENT_TO_HES);
		BIT_STRING_CLR_BIT(g_dlms_ESW, R_EVENT_BIT_LAST_GASP);		// Last gasp can't retry, clear immediately
	}
}

/******************************************************************************
* Function Name : R_DLMS_EventAck_LastGaspPushed
* Interface     : void R_DLMS_EventAck_LastGaspPushed(
*               :     void
*               : );
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_DLMS_EventAck_LastGaspPushed(void)
{
	/* Clear ESW */
	BIT_STRING_CLR_BIT(g_dlms_ESW, R_EVENT_BIT_LAST_GASP);
}

/******************************************************************************
* Function Name : R_DLMS_Event_FirstBreath
* Interface     : void R_DLMS_Event_FirstBreath(
*               :     void
*               : );
* Description   : 
* Arguments     : 
* Function Calls:
* Return Value  : 
******************************************************************************/
void R_DLMS_Event_FirstBreath ( void )
{

}

/******************************************************************************
* Function Name : R_DLMS_Event_PollingProcessing
* Interface     : void R_DLMS_Event_PollingProcessing(
*               :     void
*               : );
* Description   : 
* Arguments     : 
* Function Calls: R_DLMS_OBJECTS_Class01PollingProcessing
* Return Value  : 
******************************************************************************/
void R_DLMS_Event_PollingProcessing (void)
{
	uint8_t bit_id2 = 0;
    uint32_t mask = 1u;
    uint8_t  found_bit = FALSE;
    uint32_t action_event_mask_bit = 0xFFF00000;
    uint32_t event_action_flag;

    /* Get list of action flag */
    event_action_flag = g_event_flag.value & action_event_mask_bit;

    do
    {
        /* code */
        //Get bit ID
        if ((event_action_flag & mask) == 0) 
        {
            found_bit = FALSE;
        }
        else
        {   
            found_bit = TRUE;
            g_event_flag.value &= ~ mask;
        }
        bit_id2 ++;
        event_action_flag &= ~ mask;  
        mask = mask << 1;

        if ( found_bit == TRUE)
        {
            switch (bit_id2)
            {
            case 21: // comm module removal
                if( g_event_state.comm_module.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_PLUG_IN_COMM_MODULE_REMOVAL_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_PLUG_IN_COMM_MODULE_REMOVAL_RESTORATION;
                } 
                EventArgs.type              = (EVENT_TYPE_T)4;
                EventArgs.esw_bit_number    = 0xFF;
                break;

            case 22: // Relay disc/ reconnect
                if( g_event_state.relay_status.current_state == EVENT_STATE_ENTER)
                {
                    EventArgs.status        = EVENT_STATE_ENTER;
                    EventArgs.data.code     = EVENT_ID_LOAD_SWITCH_STATUS_DISCONNECTED_OCCURRENCE;
                } 
                else
                {
                    EventArgs.status        = EVENT_STATE_RELEASE;
                    EventArgs.data.code     = EVENT_ID_LOAD_SWITCH_STATUS_CONNECTED_OCCURRENCE;
                }  
                EventArgs.type              = (EVENT_TYPE_T)6;
                EventArgs.esw_bit_number    = 84;
                break;
				
			case 23:// set Activity Calendar for Time Zones: 155
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_ACTIVITY_CALENDAR_FOR_TIME_ZONES;
				EventArgs.esw_bit_number    = 0xFF;
				break;	
			
			case 24: // New firmware activated: 157
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_NEW_FIRMWARE_ACTIVATED;
				EventArgs.esw_bit_number    = 0xFF;
				break;
				
			case 25:// Load limit (kW) set: 158
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_LOAD_LIMIT_KW_SET;
				EventArgs.esw_bit_number    = 0xFF;
				break;
							
			case 26:// Enable, load limit function: 159
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_ENABLED_LOAD_LIMIT_FUNCTION;
				EventArgs.esw_bit_number    = 0xFF;
				break;
						
			case 27:// Disable, load limit function: 160
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_DISABLED_LOAD_LIMIT_FUNCTION;
				EventArgs.esw_bit_number    = 0xFF;
				break;	
				
			case 28:/* LLS secret (MR) change: 161*/
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_LLS_SECRET_MR_CHANGE;
				EventArgs.esw_bit_number    = 0xFF;
				break;
				
			case 29:/* HLS key (US) change: 162*/
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_HLS_KEY_US_CHANGE;
				EventArgs.esw_bit_number    = 0xFF;
				break;
				
			case 30:/* HLS key (FW) change: 163*/
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_HLS_KEY_FW_CHANGE; 
				EventArgs.esw_bit_number    = 0xFF;
				break;
				
			case 31:// Global key change: 164
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_GLOBAL_KEY_CHANGE;
				EventArgs.esw_bit_number    = 0xFF;
				break;	
				
			case 32:// ESWF change: 165
				EventArgs.type              = (EVENT_TYPE_T)3;	
				EventArgs.status            = EVENT_STATE_ENTER;
				EventArgs.data.code         = EVENT_ID_ESWFCHANGE;
				EventArgs.esw_bit_number    = 0xFF;
				break;
	
            default:
                
                break;
            }
            EVENT_AccumulateTamperCounter(&EventArgs);
            EVENT_OnEventCallBack(&EventArgs);
            EVENT_StorageWrite(&EventArgs);
            
        }

        if ( bit_id2 > 32)
        {
            bit_id2 = 1;
            mask = 1u;
        }
    
    } while ( event_action_flag !=0 );
	
}
/******************************************************************************
* Function Name : R_DLMS_EventBackup
* Interface     : void R_DLMS_EventBackup(
*               :     void
*               : );
* Description   : store data from RAM to storage
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_EventBackup(void)
{
	/* Event status word */
	R_DLMS_EEPROM_Write(r_storage_info_ESW, (uint8_t *)&g_dlms_ESW);
}
/******************************************************************************
* Function Name : R_DLMS_EventRestore
* Interface     : void R_DLMS_EventRestore(
*               :     void
*               : );
* Description   : This function load data from storage to RAM, need to register in restore of DLMS storage
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_EventRestore(void)
{
	/* Event status word */
	R_DLMS_EEPROM_Read(r_storage_info_ESW, (uint8_t *)&g_dlms_ESW);
	/* Event status word filter */
	R_DLMS_EEPROM_Read(r_storage_info_ESWF, (uint8_t *)&g_dlms_ESWF);
}

/******************************************************************************
* Function Name : R_DLMS_EventFormat
* Interface     : void R_DLMS_EventFormat(
*               :     void
*               : );
* Description   : format data, write default data to storage.
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_DLMS_EventFormat(void)
{
    /* Event status word filter */
	R_DLMS_EEPROM_Write(r_storage_info_ESWF, (uint8_t *)&g_eswf_default);
}

/******************************************************************************
* Function Name : R_DLMS_GetTheLastEventCode
* Description   : format data, write default data to storage.
* Arguments     : EVENT_TYPE_T type - type of event to get the last event code
* Function Calls: 
* Return Value  : uint16_t - event code result
******************************************************************************/
uint16_t R_DLMS_GetTheLastEventCode(EVENT_TYPE_T type)
{
    uint32_t entry_in_use;
    EVENT_PARAMS_T event_entry;

    /* Get entry in use of event type */
    if(R_EVENT_EntriesInUseGet(type, &entry_in_use) != FALSE)
    {
        if(entry_in_use == 0)
        {
            return 0;
        }
        else
        {
            event_entry = R_EVENT_GetEntry(type, (uint16_t)(entry_in_use - 1));
            return event_entry.code;
        }
    }
    else
    {
        return 0;
    }
    /**/
}
#endif /* R_DLMS_APPS_EVENT_POLLING_ENABLE */


/******************************************************************************
* Function Name : EVENT_OnEventCallBack
* Interface     : void EVENT_OnEventCallBack(EVENT_ARGS_T *pEvent_arg)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void EVENT_OnEventCallBack(EVENT_ARGS_T *pEvent_arg)
{
    uint16_t position_of_byte;
    uint8_t  old_byte_value;
    uint8_t  new_byte_value;
    uint16_t event_push_filter;

    if (pEvent_arg->esw_bit_number == EVENT_BIT_NULL)
    {
        return;
    }

    position_of_byte =  pEvent_arg->esw_bit_number / 8;
    
    /* Backup old status first */
    old_byte_value = g_dlms_ESW[position_of_byte];

    if (pEvent_arg->status == EVENT_STATE_ENTER)
    {
        BIT_STRING_SET_BIT(g_dlms_ESW, pEvent_arg->esw_bit_number);
    }
    else
    {
        BIT_STRING_CLR_BIT(g_dlms_ESW, pEvent_arg->esw_bit_number);
    }

    /* 
     * [Event status word filter (ESWF)]
        *     Bit value '1' in ESWF string indicates that the event is supported and; 
        *     Bit value '0' indicates the event is not supported for Event Push
        */
    event_push_filter = g_dlms_ESWF[position_of_byte] & (0x80 >> (pEvent_arg->esw_bit_number % 8));

    old_byte_value &= event_push_filter;
    new_byte_value = g_dlms_ESW[position_of_byte] & event_push_filter;

    /*  
     * Whenever there is a change of status of 
     *      any one event mapped in to ESW the smart meter shall push
     */
    if (old_byte_value != new_byte_value)
    {
        /* PUSH_DATA_OUT */
        R_DLMS_Push_EventToHES();
    }

}

/******************************************************************************
* Function Name : R_DLMS_EVENT_Init
* Interface     : void R_DLMS_EVENT_Init(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_DLMS_EVENT_Init(void)
{
    EVENT_RegisterPluginCallback(0, EVENT_OnEventCallBack);
}