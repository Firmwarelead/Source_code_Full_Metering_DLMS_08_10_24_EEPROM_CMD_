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
* File Name    : r_dlms_push.c
* Version      : 1.02
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Handle push processing
*                Backup and restore Push setups
*                Invoke DataNotification service (DLMS 2.0 Library)
*                Receive push trigger
*                
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 2018-03-29               [0] New create
//
// 2018-08-01 17:17:38      [1]
//                          Support SET config for IPv4 format "192.168.0.20:8000" for example
//                          Support SET window, delay time and number of retry
//                          Make new structure for push setup
//                          Renamed push_id to push_channel
//                          Moved push process from OBJECT to application
//
// 13.11.2019               Default Destination address is NULL, Installer of Factory enter destination address.
// 14.11.2019              	Update push process as follows:
//               			+ No push attempt if Destination Address in Push setup is not valid. 
//              		   	+ Return R_DLMS_Push_ServiceCall error when socket can't open.
//              		  	+ Fix Multiple push communication window
//              		  	+ Remove convert_length;
//              		  	+ Remove unused variable
//              		  	+ Correct intial variable of push process
//							+ If no communication window is active when invoking the push method, 
//						 	  the delay starts at the beginning of the next communication window. 
//						    + Added for loop to check communication window.
// 14.11.2019				Added "instant push when trigger" option for India. Randomization start interval = 0.

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Common */
#include "r_cg_macrodriver.h"           /* Macro Driver Definitions */

#include "wrp_app_mcu.h"
#include "wrp_app_ext.h"

/* DLMS OBIS layer */
#include "r_dlms_classes.h"
#include "r_dlms_objects.h"
#include "r_dlms_class40.h"

/* DLMS Application */
#include "r_dlms_app.h"
#include "r_dlms_push.h"
#include "r_dlms_date_time.h"
#include "r_dlms_storage.h"
#include "r_dlms_event.h"

#include "r_dlms_factory_config.h"


/* DLMS wrapper */
#include "r_dlms_udp_wrapper.h"
#include "r_dlms_udp_wrapper_interface.h"
#include "r_dlms_tcp_wrapper.h"
#include "r_dlms_tcp_wrapper_interface.h"

#include "r_dlms_wrapper_conversion_ip.h"

/* Standard libary */
#include <string.h>
#include "event.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef R_DLMS_PUSH_OBJECT_MAXNUMBER
#define R_DLMS_PUSH_OBJECT_MAXNUMBER (PUSH_OBJECT_NUMBER)
#endif

#define CLASS40_ASSOCIATION_ID_PC                   (ASSOCIATION_ID_SAS_10H)
#define CLASS40_ASSOCIATION_ID_MR                   (ASSOCIATION_ID_SAS_20H)
#define CLASS40_ASSOCIATION_ID_US                   (ASSOCIATION_ID_SAS_30H)
#define CLASS40_ASSOCIATION_ID_PUSH                 (ASSOCIATION_ID_SAS_40H)
#define CLASS40_ASSOCIATION_ID_FIRMWARE_UPGRADE     (ASSOCIATION_ID_SAS_50H)
#define CLASS40_ASSOCIATION_ID_IHD                  (ASSOCIATION_ID_SAS_60H)
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

push_window_t g_push_window[PUSH_OBJECT_NUMBER][PUSH_MAX_WINDOW_SUPPORT];
push_config_t g_push_setup[PUSH_OBJECT_NUMBER];

extern AsscConnectionSession *gp_dlms_CurrentSection;

void R_DLMS_OBJECTS_Class40_EncodeCapturedData ( distributor_params_t	*p_params );

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

const PUSH_STORAGE_ADDR_AND_SIZE eeprom_map_dest			= { STORAGE_EEPROM_DLMS_PUSH_PROTOCOL_ADDR,     sizeof(uint8_t)	};
const PUSH_STORAGE_ADDR_AND_SIZE eeprom_map_ip_config		= { STORAGE_EEPROM_DLMS_PUSH_IP_CONFIG_ADDR,    sizeof(push_dest_address_cnfg_t)	};
const PUSH_STORAGE_ADDR_AND_SIZE eeprom_map_message_type	= { STORAGE_EEPROM_DLMS_PUSH_MESSAGE_TYPE_ADDR, sizeof(uint8_t) };


/******************************************************************************
* Function Name : R_DLMS_Push_GetConfig
* Interface     : uint8_t R_DLMS_Push_GetConfig(
*               :     push_config_t *p_cnfg
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
push_config_t * R_DLMS_Push_GetConfig ( uint8_t push_channel )
{
    if (push_channel < PUSH_OBJECT_NUMBER)
    {
        return &g_push_setup[push_channel];
    }
    else
    {
        return NULL;
    }
}

/******************************************************************************
* Function Name : R_DLMS_Push_SetFlag
* Interface     : void R_DLMS_Push_SetFlag( uint16_t trigger_set, uint16_t trigger_clear )
* Description   : Push trigger IF
* Arguments     : void
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_DLMS_Push_SetFlag(uint8_t push_channel)
{
    if ((g_push_setup[push_channel].state == (uint8_t) PUSH_STATUS_NONE) && 
        (push_channel < PUSH_OBJECT_NUMBER))
    {
        g_push_setup[push_channel].state = (uint8_t) PUSH_STATUS_TRIGGED;
    }
}


void R_DLMS_Push_Enable(uint8_t push_channel)
{
    if (push_channel < PUSH_OBJECT_NUMBER)
    {
        g_push_setup[push_channel].enable = TRUE;
    }
    else
    {
        return;
    }
}

/******************************************************************************
* Function Name : R_DLMS_Push_Format
* Interface     : void R_DLMS_Push_Format(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_Push_Format(void)
{
    uint8_t             push_channel;
	uint8_t             push_retry;

	push_destination_t	dest_cfg;

    push_destination_t  push_destination_default = 
    {
        PUSH_DESTINATION_SERVICE_DEFAULT,
        PUSH_MESSAGE_TYPE_A_XDR_ENC_xDLMS_APDU,
        {
            { 
                PUSH_DESTINATION_ADDRESS_DEFAULT,		// 16 bytes of Ip address
                PUSH_DESTINATION_ADDRESS_DEFAULT_SIZE,	//0, // NULL to disable Destination and Push during Factory
                0, 										// format: 0: encoding byte by byte, 1: ASCCI encoding
                PUSH_DESTINATION_PORT_DEFAULT			// Port
            }
        }
    };

	push_window_t 		push_window_default = 
	{
		/* Sec, Min, Hour, Day, Week, Month, Year */
		PUSH_WINDOW_START_TIME_DEFAULT,		/* Start time */
		PUSH_WINDOW_END_TIME_DEFAULT		/* End time */
	};

    /* Inital default value of push destination on EEPROM */
    
    for ( push_channel = 0 ; push_channel < R_DLMS_PUSH_OBJECT_MAXNUMBER ; push_channel++ )
    {
		g_push_setup[push_channel].p_window = g_push_window[push_channel];
		R_DLMS_Push_Backup_DestinationSetup(
			push_channel,
			&push_destination_default
		);
		 
		if (R_DLMS_Push_Restore_DestinationSetup ( 
			push_channel,
			&dest_cfg
		) == PUSH_RESULT_SUCCESS)
		{
			memcpy((uint8_t *)&g_push_setup[push_channel].destination, (uint8_t *)&dest_cfg, sizeof(push_destination_t));
		}
         
		R_DLMS_Push_Backup_CommWin(
			push_channel,
			&push_window_default,
			1
		);
         
		push_retry = R_DLMS_Push_Restore_CommWin(push_channel);
		
		push_retry = PUSH_NUMBER_OF_RETRIES_DEFAULT;
		push_retry = R_DLMS_Push_Backup_NumberOfRetry(push_channel, push_retry);
		push_retry = R_DLMS_Push_Restore_NumberOfRetry(push_channel);

	}
}
/******************************************************************************
* Function Name : R_DLMS_Push_Backup_DestinationSetup
* Interface     : uint8_t R_DLMS_Push_Backup_DestinationSetups(
*               :     uint8_t push_channel, uint16_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Backup_DestinationSetup(
	uint8_t		push_channel,
	push_destination_t *p_dest_cfg
)
{
	uint8_t result_error_code = PUSH_RESULT_SUCCESS;

	push_transport_service_t	transport_service;
	push_dest_address_cnfg_t	cfg;
	push_message_type_t			mesage_type;

	PUSH_STORAGE_ADDR_AND_SIZE info;

	if (push_channel >= R_DLMS_PUSH_OBJECT_MAXNUMBER)
	{
		return PUSH_RESULT_FAILED;
	}

	if (p_dest_cfg == NULL)
	{
		return PUSH_RESULT_FAILED;
	}
	else
	{
		transport_service = p_dest_cfg->service;
		memcpy((uint8_t *)&cfg, (uint8_t *)&p_dest_cfg->config, sizeof(push_dest_address_cnfg_t));
		mesage_type = p_dest_cfg->message;

		if (( transport_service != PUSH_TRANSPORT_SERVICE_TCP) &&
			( transport_service != PUSH_TRANSPORT_SERVICE_UDP) )
			{
				return PUSH_RESULT_FAILED;
			}
		if (mesage_type != 0)
		{
			return PUSH_RESULT_FAILED;
		}
	}

	/* Backup transport service */
	info.address = eeprom_map_dest.address + eeprom_map_dest.length * push_channel;
	info.length = eeprom_map_dest.length;
	R_PUSH_EEPROM_WRITE(info, (uint8_t *)&transport_service);

	/* Backup address */
	info.address = eeprom_map_ip_config.address + eeprom_map_ip_config.length * push_channel;
	info.length = eeprom_map_ip_config.length;
	R_PUSH_EEPROM_WRITE(info, (uint8_t *)&cfg);

	/* Backup message type */
	info.address = eeprom_map_message_type.address + eeprom_map_message_type.length * push_channel;
	info.length = eeprom_map_message_type.length;
	R_PUSH_EEPROM_WRITE(info, (uint8_t *)&mesage_type);

	return result_error_code;
}


/******************************************************************************
* Function Name : R_DLMS_Push_Restore_DestinationSetup
* Interface     : uint8_t R_DLMS_Push_Restore_DestinationSetup(
*               :     
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Restore_DestinationSetup ( 
	uint8_t push_channel,
	push_destination_t *p_dest_cfg
)
{
	uint8_t result_error_code = PUSH_RESULT_SUCCESS;

	push_transport_service_t	transport_service;
	push_dest_address_cnfg_t	cfg;
	push_message_type_t			mesage_type;

	PUSH_STORAGE_ADDR_AND_SIZE info;

	if (push_channel >= R_DLMS_PUSH_OBJECT_MAXNUMBER)
	{
		return PUSH_RESULT_FAILED;
	}

	{
		/* Restore transport service */
		info.address = eeprom_map_dest.address + eeprom_map_dest.length * push_channel;
		info.length = eeprom_map_dest.length;
		R_PUSH_EEPROM_READ(info, (uint8_t *)&transport_service);

		/* Restore address */
		info.address = eeprom_map_ip_config.address + eeprom_map_ip_config.length * push_channel;
		info.length = eeprom_map_ip_config.length;
		R_PUSH_EEPROM_READ(info, (uint8_t *)&cfg);

		/* Restore message type */
		info.address = eeprom_map_message_type.address + eeprom_map_message_type.length * push_channel;
		info.length = eeprom_map_message_type.length;
		R_PUSH_EEPROM_READ(info, (uint8_t *)&mesage_type);
	}

	/* Everything is OK */
	if (p_dest_cfg != NULL)
	{
		p_dest_cfg->service = transport_service;
		memcpy((uint8_t *)&p_dest_cfg->config, (uint8_t *)&cfg, sizeof(push_dest_address_cnfg_t));
		p_dest_cfg->message = mesage_type;
	}

	return result_error_code;
}


/******************************************************************************
* Function Name : R_DLMS_Push_Backup_CommWin
* Interface     : uint8_t R_DLMS_Push_Backup_CommWin(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Backup_CommWin ( 
    uint8_t		    push_channel,
    push_window_t   *p_push_window,
    uint8_t         num_of_window
)
{
	uint8_t result_error_code = PUSH_RESULT_SUCCESS;

	PUSH_STORAGE_ADDR_AND_SIZE memmap                 = { STORAGE_EEPROM_DLMS_PUSH_WINDOW_ADDR,           sizeof(push_window_t)*PUSH_MAX_WINDOW_SUPPORT  };
	PUSH_STORAGE_ADDR_AND_SIZE memmap_num_of_window   = { STORAGE_EEPROM_DLMS_PUSH_NUM_OF_WINDOW_ADDR,    sizeof(uint8_t)         };
	uint8_t window_index;

	if (push_channel >= R_DLMS_PUSH_OBJECT_MAXNUMBER)
	{
		return PUSH_RESULT_FAILED;
	}

	if (num_of_window > PUSH_MAX_WINDOW_SUPPORT)
	{
		return PUSH_RESULT_FAILED;
	}

	if ( p_push_window != NULL )
	{
		memmap.address += memmap.length * push_channel;
		for ( window_index = 0; window_index < num_of_window; window_index++)
		{
			memmap.address += window_index * sizeof(push_window_t);
			memmap.length = sizeof(push_window_t);
			R_PUSH_EEPROM_WRITE(memmap, (uint8_t *)&p_push_window[window_index]);
			memcpy( 
				(uint8_t *)&g_push_setup[push_channel].p_window[window_index], 
				(uint8_t *)&p_push_window[window_index], 
				sizeof(push_window_t)
			);
		}

		memmap_num_of_window.address += memmap_num_of_window.length * push_channel;
		R_PUSH_EEPROM_WRITE(memmap_num_of_window, (uint8_t *)&num_of_window);
		g_push_setup[push_channel].num_of_window = num_of_window;
	}
	return result_error_code;
}

/******************************************************************************
* Function Name : R_DLMS_Push_Restore_CommWin
* Interface     : uint8_t R_DLMS_Push_Restore_CommWin(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Restore_CommWin ( uint8_t push_channel )
{
    uint8_t result_error_code = PUSH_RESULT_SUCCESS;
    
    PUSH_STORAGE_ADDR_AND_SIZE memmap                 = { STORAGE_EEPROM_DLMS_PUSH_WINDOW_ADDR,           sizeof(push_window_t)*PUSH_MAX_WINDOW_SUPPORT };
    PUSH_STORAGE_ADDR_AND_SIZE memmap_num_of_window   = { STORAGE_EEPROM_DLMS_PUSH_NUM_OF_WINDOW_ADDR,    sizeof(uint8_t)         };
    uint8_t window_index;

    uint8_t num_of_window;
    push_window_t window[PUSH_MAX_WINDOW_SUPPORT];

    if (push_channel >= R_DLMS_PUSH_OBJECT_MAXNUMBER)
    {
        return PUSH_RESULT_FAILED;
    }
    memmap_num_of_window.address += memmap_num_of_window.length * push_channel;
    R_PUSH_EEPROM_READ(memmap_num_of_window, (uint8_t *)&num_of_window);
    if (num_of_window > PUSH_MAX_WINDOW_SUPPORT)
    {
        num_of_window = 0;
        R_PUSH_EEPROM_WRITE(memmap_num_of_window, (uint8_t *)&num_of_window);
    }
    g_push_setup[push_channel].num_of_window = num_of_window;

    if ( num_of_window > 0 )
    {
        memmap.address += memmap.length * push_channel;
        memmap.length = sizeof(push_window_t);
        for ( window_index = 0; window_index < num_of_window; window_index++)
        {
			memmap.address += window_index * ( sizeof(push_window_t) );
            R_PUSH_EEPROM_READ(memmap, (uint8_t *)&window[window_index]);
            memcpy( &g_push_setup[push_channel].p_window[window_index], (uint8_t *)&window[window_index], sizeof(push_window_t));
        }
    }
    
    return result_error_code;
}

/******************************************************************************
* Function Name : R_DLMS_Push_Backup_RandomisationStartInterval
* Interface     : void R_DLMS_Push_Backup_RandomisationStartIntervals(
*               :     uint8_t push_channel, uint16_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_Push_Backup_RandomisationStartInterval (
    uint8_t		push_channel, 
    uint16_t	value
)
{
	uint8_t result_error_code = PUSH_RESULT_SUCCESS;

	PUSH_STORAGE_ADDR_AND_SIZE eeprom_map = { STORAGE_EEPROM_DLMS_RAND_INTERVAL_ADDR, sizeof(uint16_t) };
    
    if (push_channel >= R_DLMS_PUSH_OBJECT_MAXNUMBER)
    {
        return PUSH_RESULT_FAILED;
    }
    
    eeprom_map.address += eeprom_map.length * push_channel;
	R_PUSH_EEPROM_WRITE(eeprom_map, (uint8_t *)&value);

    g_push_setup[push_channel].delay_start_max = value;

	return result_error_code;
}
/******************************************************************************
* Function Name : R_DLMS_Push_Set_RandomisationStartInterval
* Interface     : void R_DLMS_Push_Set_RandomisationStartInterval(
*               :     uint8_t push_channel, uint16_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Set_RandomisationStartInterval(uint8_t push_channel, uint16_t value)
{	
	if (push_channel >= R_DLMS_PUSH_OBJECT_MAXNUMBER)
    {
        return PUSH_RESULT_FAILED;
    }
	
    g_push_setup[push_channel].delay_start_max = value;
	/* Write  data for number of retry */
	return R_DLMS_Push_Backup_RandomisationStartInterval(push_channel, g_push_setup[push_channel].delay_start_max);
}
/******************************************************************************
* Function Name : R_DLMS_Push_Restore_RandomisationStartInterval
* Interface     : void R_DLMS_Push_Restore_RandomisationStartIntervals(
*               :     uint8_t push_channel, uint16_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  : 
******************************************************************************/
uint8_t R_DLMS_Push_Restore_RandomisationStartInterval ( uint8_t push_channel )
{
	uint8_t result_error_code = PUSH_RESULT_SUCCESS;
    uint16_t value;

	PUSH_STORAGE_ADDR_AND_SIZE eeprom_map = { STORAGE_EEPROM_DLMS_RAND_INTERVAL_ADDR, sizeof(uint16_t) };
    
    if (push_channel >= R_DLMS_PUSH_OBJECT_MAXNUMBER)
    {
        return PUSH_RESULT_FAILED;
    }
    
	eeprom_map.address += eeprom_map.length * push_channel;
	R_PUSH_EEPROM_READ(eeprom_map, (uint8_t *)&value);

    g_push_setup[push_channel].delay_start_max = value;

	return result_error_code;
}


/******************************************************************************
* Function Name : R_DLMS_Push_Backup_NumberOfRetry
* Interface     : void R_DLMS_Push_Backup_NumberOfRetry(
*               :     uint8_t push_channel, uint16_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Backup_NumberOfRetry(
	uint8_t		push_channel,
	uint8_t		value
)
{
	uint8_t result_error_code = PUSH_RESULT_SUCCESS;

	PUSH_STORAGE_ADDR_AND_SIZE eeprom_map = { STORAGE_EEPROM_DLMS_NUMBER_RETRY_ADDR, sizeof(uint8_t) };
    
    if (push_channel >= R_DLMS_PUSH_OBJECT_MAXNUMBER)
    {
        return PUSH_RESULT_FAILED;
    }
    
	eeprom_map.address += eeprom_map.length * push_channel;
	result_error_code = R_PUSH_EEPROM_WRITE(eeprom_map, (uint8_t *)&value);

	g_push_setup[push_channel].retried_num_max = value;

	return result_error_code;
}
/******************************************************************************
* Function Name : R_DLMS_Push_Set_NumberOfRetry
* Interface     : void R_DLMS_Push_Set_NumberOfRetry(
*               :     uint8_t push_channel, uint8_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Set_NumberOfRetry(uint8_t push_channel, uint8_t value)
{
    g_push_setup[push_channel].retried_num_max = value;
	/* Write  data for number of retry */
	return R_DLMS_Push_Backup_NumberOfRetry(push_channel, g_push_setup[push_channel].retried_num_max);
}

/******************************************************************************
* Function Name : R_DLMS_Push_Restore_NumberOfRetry
* Interface     : void R_DLMS_Push_Restore_NumberOfRetry(
*               :     uint8_t push_channel, uint16_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Restore_NumberOfRetry(
	uint8_t		push_channel
)
{
	uint8_t result_error_code;
    uint8_t value;

	PUSH_STORAGE_ADDR_AND_SIZE eeprom_map = { STORAGE_EEPROM_DLMS_NUMBER_RETRY_ADDR, sizeof(uint8_t) };
	eeprom_map.address += eeprom_map.length * push_channel;
	result_error_code = R_PUSH_EEPROM_READ(eeprom_map, (uint8_t *)&value);

    g_push_setup[push_channel].retried_num_max = value;

	return result_error_code;
}

/******************************************************************************
* Function Name : R_DLMS_Push_Backup_NumberOfRetry
* Interface     : void R_DLMS_Push_Backup_NumberOfRetry(
*               :     uint8_t push_channel, uint16_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Backup_RepetitionDelay(
	uint8_t		push_channel,
	uint16_t    value
)
{
	uint8_t result_error_code;

	PUSH_STORAGE_ADDR_AND_SIZE eeprom_map = { STORAGE_EEPROM_DLMS_RETRY_DELAY_TIME_ADDR, sizeof(uint16_t) };
	eeprom_map.address += eeprom_map.length * push_channel;
	result_error_code = R_PUSH_EEPROM_WRITE(eeprom_map, (uint8_t *)&value);
	g_push_setup[push_channel].delay_retry_max = value;

	return result_error_code;
}
/******************************************************************************
* Function Name : R_DLMS_Push_Set_RepetitionDelay
* Interface     : void R_DLMS_Push_Set_RepetitionDelay(
*               :     uint8_t push_channel, uint16_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Set_RepetitionDelay(uint8_t push_channel, uint16_t value)
{
    g_push_setup[push_channel].delay_retry_max = value;

	/* Write to storage */
	return R_DLMS_Push_Backup_RepetitionDelay(push_channel, g_push_setup[push_channel].delay_retry_max);
}

/******************************************************************************
* Function Name : R_DLMS_Push_Restore_RepetitionDelay
* Interface     : void R_DLMS_Push_Restore_RepetitionDelay(
*               :     uint8_t push_channel, uint16_t value
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Restore_RepetitionDelay(
	uint8_t		push_channel
)
{
	uint8_t result_error_code;
    uint16_t value;

	PUSH_STORAGE_ADDR_AND_SIZE eeprom_map = { STORAGE_EEPROM_DLMS_RETRY_DELAY_TIME_ADDR, sizeof(uint16_t) };
	eeprom_map.address += eeprom_map.length * push_channel;
	result_error_code = R_PUSH_EEPROM_READ(eeprom_map, (uint8_t *)&value);

    g_push_setup[push_channel].delay_retry_max = value;

	return result_error_code;
}

/******************************************************************************
* Function Name : R_DLMS_Push_IPtoOctetString
* Interface     : void R_DLMS_Push_IPtoOctetString(
*               :     uint8_t *ip, uint8_t * p_buff, uint16_t *p_len
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Convert_DestConfigToString(
	push_transport_service_t	trans_service,				// [Input]
	push_dest_address_cnfg_t	*config,					// [Input]
	uint8_t						*p_buff,					// [Out]
	uint16_t					*p_len						// [Out]
)
{
	uint8_t result = PUSH_RESULT_SUCCESS;
	uint8_t i;
	uint8_t *p_pos = p_buff;
	uint8_t len = 0;
    uint16_t conversion_len = 60;

	uint8_t *p_local_ip_address;

	uint8_t number[3];
	uint8_t address_size = 4;

	uint16_t *p_port;
	
    uint8_t     ipbuff[16];
    IpAddress ipaddress = {ipbuff, 16};

	// [Notes]
	//
	// + Input
	//      IP configure, profile = TCP or UPD
	//			config = { {192, 168, 0, 20} , 8080 }
	//
	// + Output
	//		p_buff = "192.168.0.20:8080"

	switch ( trans_service )
	{
		case PUSH_TRANSPORT_SERVICE_TCP:
		case PUSH_TRANSPORT_SERVICE_UDP:
			if  (config->ip_port.format_type == 0 && (config->ip_port.size == 16 || config->ip_port.size == 4))
			{
				memcpy(p_buff, config->ip_port.buffer, config->ip_port.size);
				memcpy(p_buff + config->ip_port.size, (uint8_t *)&config->ip_port.port + 1, 1);
				memcpy(p_buff + config->ip_port.size + 1, (uint8_t *)&config->ip_port.port, 1);
				*p_len = config->ip_port.size + 2;
			}
			else if (config->ip_port.size == 16 || config->ip_port.size == 4)
			{
				*p_len = 0;
				memcpy( ipaddress.p_addr, config->ip_port.buffer, config->ip_port.size);
	            ipaddress.size = config->ip_port.size;
	            if (ipaddress.size == 16)
	            {
	                *p_buff++ = '[';
	                *p_len = 1;
	            }
	            if (R_DLMS_ConvertIpAddressToString( p_buff, &conversion_len, &ipaddress ) == FALSE)
	            {
	                return PUSH_RESULT_FAILED;
	            }
				p_buff += conversion_len;
	            *p_len += conversion_len;
	            if (ipaddress.size == 16)
	            {
	                *p_buff++ = ']';
	                *p_len += 1;
	            }
                *p_buff++ = ':';
                *p_len += 1;
	            conversion_len = R_DLMS_ConvertU16ToString(config->ip_port.port, p_buff);
                p_buff += conversion_len;
                *p_len += conversion_len;
			}
			else
			{
				*p_len = 0;
			}
			break;
		case PUSH_TRANSPORT_SERVICE_HDLC:
            *p_len = 0;
            break;
		default:
			break;
	}

	return result;
}

/******************************************************************************
* Function Name : R_DLMS_Push_IPtoOctetString
* Interface     : void R_DLMS_Push_IPtoOctetString(
*               :     uint8_t *ip, uint8_t * p_buff, uint16_t *p_len
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_Convert_StringToDestAddr(
	push_transport_service_t	trans_service,				// [In]
	uint8_t						*p_buff,					// [In]
	uint16_t					length,						// [In]
	push_dest_address_cnfg_t	*config						// [Out]
)
{
	uint8_t     i;

	uint32_t    num = 0;
	uint8_t     step = 0;
	uint8_t     *p_local_ip_address;
	uint16_t    *p_port;
    uint8_t     ipbuff[16];
    IpAddress   ipaddress = {ipbuff, 16};
    uint8_t     convert_length = 60;

    uint8_t     ipv6_bracket = FALSE;
	// [Notes]
	// INPUT
    //
    // Type 1:
	//      IPv4  
    //            "192.168.0.20:4059"   = 49,57,50,46,49,54,56,46,48,46,50,48,58,52,48,53,57 (Decimal string)
	//            "192.168.0.20"
	//            "0.0.0.0"
	//            "0.0.0.1"
    //      IPv6
	//            "[2606:2800:220:1:248:1893:25c8:1946]:4059"
	//            "[2001:0db8::1:0:0:1]:4059"
    //            "[2001:41c0::1]:4059" 
	//            "2606:2800:220:1:248:1893:25c8:1946"
	//            "2001:41c0::645:a65e:60ff:feda:589d"
	//            "2001:0db8::1:0:0:1"
	//            "2001:41c0::1"        
	//            "2606::1"
	//            "1000::1"
	//            "::1"
	//            "::"
    // Type 2:
    //      IPv4
    //            { 192, 168, 0, 20}     = 192, 168, 0 , 20 (Decimal string)
    //            { 192, 168, 0, 20, 15, 219}
    //              
    //      IPv6  { 0x02, 0x00, 0x00, 0x00 }
    //            { 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56, 0x78, 0xab, 0xcd, 0xef, 0x43 }
    //
	// Output
	//      config = { IP_ADDRESS = {192, 168, 0, 20} , PORT = 4059 }

	switch ( trans_service )
	{
		case PUSH_TRANSPORT_SERVICE_TCP:
		case PUSH_TRANSPORT_SERVICE_UDP:
            if (*p_buff == '[')
            {
                p_buff++;
				length--;
                ipv6_bracket = TRUE;
            }
            convert_length = R_DLMS_ConvertStringToIpAddress(
                &ipaddress,
                p_buff,
                length
            );
            if (convert_length == 0xFF)
            {
                memcpy(&config->ip_port.buffer, ipaddress.p_addr, ipaddress.size);
                config->ip_port.size = ipaddress.size;
                p_buff += ipaddress.size;
                memcpy((uint8_t *)(void *)&config->ip_port.port, p_buff, 2);
                R_DLMS_ReverseBuffer((void *)&config->ip_port.port, 2);
				config->ip_port.format_type = 0;
            }
            else if (convert_length > 0)
            {
				config->ip_port.format_type = 1;
                memcpy(config->ip_port.buffer, ipaddress.p_addr, 16);
                config->ip_port.size = ipaddress.size;
                if (config->ip_port.size == 4)
                {
					p_buff += convert_length;
                    if (*p_buff == 0 || *p_buff != ':' || (convert_length+1) >= length)
                    {
                        config->ip_port.port = 4059;
					}
                    else
					{
						p_buff++;
						length--;
						memset(ipbuff, 0, 16);
						memcpy(ipbuff, p_buff, length - convert_length);
                        R_DLMS_ConvertStringToU16( &config->ip_port.port , ipbuff );
                    }
                }
                else if (config->ip_port.size == 16)
				{
					if (ipv6_bracket == FALSE)
					{
						config->ip_port.port = 4059;
					}
					else
					{
						p_buff += convert_length + 1;
						length--;
						if (*(p_buff) == 0 || convert_length >= length || *(p_buff) != ':')
						{
							config->ip_port.port = 4059;
						}
						else
						{
							p_buff++;
							length--;
							memset(ipbuff, 0, 16);
							memcpy(ipbuff, p_buff, length - convert_length);
                    		R_DLMS_ConvertStringToU16( &config->ip_port.port , ipbuff );
						}
					}
				}
            }
			break;
		case PUSH_TRANSPORT_SERVICE_HDLC:
			return PUSH_RESULT_FAILED;
		default:
			break;
	}

	return PUSH_RESULT_SUCCESS;
}


extern const class40_child_record_t g_objects_child_table_class40[];
extern const uint16_t g_objects_child_table_class40_length;
/******************************************************************************
* Function Name : R_DLMS_Push_FindChildRecord
* Interface     : class40_child_record_t * R_DLMS_Push_FindChildRecord(
*               :     uint8_t push_channel, uint8_t * child_index
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Push_FindChildRecord (
    uint8_t                 push_channel,       // Input
    uint16_t                *p_child_index      // Output
)
{
    uint8_t i;
    uint8_t found_object = FALSE;

    for ( i = 0; i < g_objects_child_table_class40_length; i++ )
    {
        if (g_objects_child_table_class40[i].logical_name[1] == push_channel)
        {
            *p_child_index  = (uint16_t) i;
            found_object = TRUE;
			break;
        }
    }
    
    if (found_object == FALSE)
    {
        return PUSH_RESULT_FAILED;
    }

    return PUSH_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_Push_ClearNoneRestorationlBits
* Interface     : void R_DLMS_Push_ClearNoneRestorationlBits(
*               :     uint8_t push_channel
*               : );
* Description   : Clear special notification bits when ESF pushed
*               : These bits don't have clear events. 
*               : Current implementation will clear these bit when ESF pushed or PUSH INVOKE IS FAILED.
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_DLMS_Push_ClearNoneRestorationlBits(uint8_t push_channel)
{
	/* Last gasp bit pushed */
	// if (push_channel == R_DLMS_PUSH_ID_EVENT_TO_HES) //  ESW pushed == ESW.bit85 pushed
	// {	
    //     R_DLMS_EventAck_LastGaspPushed();
    // }

    /* In billing counter bit pushed */
    if (push_channel == R_DLMS_PUSH_ID_EVENT_TO_HES) //  ESW pushed == ESW.bit87 pushed
    {
        // TODO linkage to new application to clear esw bit
        //R_DLMS_EventAck_IncreaseInBillingCounterPushed();
	}

	/* First breath bit pushed */
	if (push_channel == R_DLMS_PUSH_ID_EVENT_TO_HES) //  ESW pushed == ESW.bit86 pushed
    {
        // // TODO linkage to new application to clear esw bit
	    //R_DLMS_EventAck_FirstBreathPushed();
	}
}


/******************************************************************************
* Function Name : R_DLMS_Push_CheckDestinationAddress
* Interface     : uint8_t R_DLMS_Push_CheckDestinationAddress(
*               :     uint8_t push_channel
*               : );
* Description   : Verify push destination address
* Arguments     : uint8_t push_channel
* Return Value  : TRUE: 	Push destination address is valid 
* 				: FALSE: 	Push destination address is not valid 
******************************************************************************/
uint8_t R_DLMS_Push_CheckDestinationAddress(uint8_t push_channel)
{
    uint8_t             tcp_result_open;
    uint8_t             tcp_result_close;
    uint8_t             is_destination_address_valid;

    uint8_t             ipbuff[16];
    IpAddress           ipaddress = {ipbuff, 16};
    // uint16_t            port; // Port is 4059 by default.

	/* Get destianation address from push setup */
    // port                = g_push_setup[push_channel].destination.config.ip_port.port;
    ipaddress.p_addr    = g_push_setup[push_channel].destination.config.ip_port.buffer;
    ipaddress.size      = g_push_setup[push_channel].destination.config.ip_port.size;

	/* Currently, this function only verify the length of IPv4 or IPv6 */
    if (ipaddress.size == 4 || ipaddress.size == 16)
    {
		is_destination_address_valid = TRUE;
    }
    else
    {
		is_destination_address_valid = FALSE;
    }

	/* Todo: Verify destination address other than IPv4 and IPv6 */
	{
		
	}

    return (is_destination_address_valid);
}


/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Class40_EncodeCapturedData
* Interface     : void R_DLMS_OBJECTS_Class40_EncodeCapturedData(
*               :     MandatoryString out_data
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_OBJECTS_Class40_EncodeCapturedData ( distributor_params_t	*p_params )
{

	class40_child_record_t	*p_class40_obj;

	uint8_t u8;
	uint8_t *p_head;
	uint8_t *p_found_obj;

	distributor_result_t	encode_capture_obj_result;
	uint16_t				encode_captured_obj_length;

	MandatoryString		captured_obj_buff;
	uint16_t			captured_object_index;

	uint8_t				buffer[256];
	malloc_buffer_t		malloc = { buffer, 0, 256 };

	uint16_t from_value = 0;
	uint16_t to_value;

	class40_push_object_t * p_captured_object;

    if (p_params->child_index > g_objects_child_table_class40_length)
    {
        return;
    }

    p_class40_obj = (class40_child_record_t	*)&g_objects_child_table_class40[p_params->child_index];

	to_value = p_class40_obj->p_push_object_list->length;

	p_head = p_params->out_data.p_content;

	p_params->service_type.get = COSEM_GET_REQUEST_NORMAL;
	p_params->selective_access.use = FALSE;

	// ENCODE
	// OBIS_DIST_ENCODE_ARRAY_TYPE_DEF(u8, p_params->out_data, 1);
	
	p_found_obj = p_params->out_data.p_content + 1;
	OBIS_DIST_ENCODE_STRUCTURE_TYPE_DEF(u8, p_params->out_data, p_class40_obj->p_push_object_list->length);
	*p_found_obj = 0;

	captured_obj_buff.p_content = p_params->out_data.p_content;
	captured_obj_buff.length = p_params->out_data.length;

	for (captured_object_index = from_value; captured_object_index < to_value; captured_object_index++)
	{
		p_captured_object = p_class40_obj->p_push_object_list->p_content + captured_object_index;

		p_params->descriptor.attr.class_id = p_captured_object->class_id;
		p_params->descriptor.attr.attribute_id = p_captured_object->attribute_index;

		memcpy((uint8_t *)&p_params->descriptor.attr.instance_id, (uint8_t *)p_captured_object->logical_name.p_content, 6);

		encode_capture_obj_result = R_DLMS_CLASSES_InvokeDistribution(
			p_params->connected_assc_id,
			REQ_TYPE_GET,
			&p_params->descriptor,
			&p_params->selective_access,
			&p_params->service_type,
			p_params->p_library_descriptor,
			captured_obj_buff,
			captured_obj_buff,
			(uint16_t *)&encode_captured_obj_length,
			&malloc
		);
		if (encode_capture_obj_result.result.data_access == VAL_DATA_ACCESS_RESULT_SUCCESS)
		{
			*p_found_obj += 1;
			captured_obj_buff.p_content += encode_captured_obj_length;
			p_params->out_data.length += encode_captured_obj_length;
		}
		else
		{
			// [Error] Can't encode object.
			// 
			// Program reach here means Push object list or Object is not correct.
			// Please check if below object is implemented:
			//		p_captured_object->class_id
			//		p_captured_object->logical_name
			//		p_captured_object->attribute_index
			NOP();
		}
	}

	// RETURN
	{
		*p_params->p_out_encoded_len = (uint16_t)(captured_obj_buff.p_content - p_head);
		if (*p_params->p_out_encoded_len > 0) {
			OBIS_DATA_ACCESS_RESULT( p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE );
			OBIS_DISTRIBUTION_SUCCESS(p_params->result);
		}
	}
	
}

/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Class40_Push
* Interface     : void R_DLMS_OBJECTS_Class40_Push(
*               :     distributor_params_t *p_params
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
push_call_error_code_t R_DLMS_Push_ServiceCall ( uint8_t push_channel )
{
	int16_t result_error_code;

	int16_t current_asso_id;
	MgmtChannel channel;
	WPort remote_wport;
	static LongInvokeIdAndPriority long_invoke_id;

	MgmtChannel mgmt_channel;

	distributor_params_t	push_distributor_params;

	/* Push time */
	date_time_t current_time;

	/* Push APDU buffer */
	#define PUSH_APDU_SIZE		(256)
	uint8_t                     push_apdu_buffer[PUSH_APDU_SIZE];
#if (DLMS_LIB_VERSION >= LIB_V2_3)
	uint8_t                     push_apdu_tbuf[PUSH_APDU_SIZE + 64];
#endif /* DLMS_LIB_VERSION >=LIB_V2_3 */
	uint16_t                    push_apdu_size = PUSH_APDU_SIZE;
	uint16_t 			        encoded_length;

	SecurityOptionElement		*p_security_element = NULL;
	AdditionalServiceParams		additional_service_params;
	ApduDispatchContext			apdu_dispatch_context;

	CosemDataNotificationRequest_Params params;

	AsscConnectionSession currentSection;
	uint8_t tcp_result;

	uint8_t ipbuff[16];
	IpAddress ipaddress = {ipbuff, 16};
	uint16_t port;

	memset(&push_distributor_params, 0, sizeof(distributor_params_t));
	memset(&additional_service_params, 0, sizeof(AdditionalServiceParams));
	memset(&apdu_dispatch_context, 0, sizeof(ApduDispatchContext));

	long_invoke_id.bits.invoke_id++;                /* Invoke id auto increase */
	long_invoke_id.bits.priority = 0;               /* Normal */
	long_invoke_id.bits.service_class = 0;          /* Unconfirm */
	long_invoke_id.bits.self_descriptive = 0;       /* Not self descriptive */

	params.long_invoke_id = long_invoke_id.u32;
	params.priority = TRUE;

	params.time.use = FALSE;

	R_DLMS_RTC_Get_DateTime((uint8_t *)&current_time);

	params.time.p_content = (uint8_t *)&current_time;
	params.time.length = sizeof(date_time_t);

	if (R_DLMS_Push_CheckWindow(&g_push_setup[push_channel]) == WINDOWS_INACTIVE)
	{
		return PUSH_CALL_ERR_WINDOW_INACTIVE;
	}
	/* Check negotiated conformance for data notification */

	/* Enable push in HDLC, current connected association */
	if (gp_dlms_CurrentSection == NULL || 
		(gp_dlms_CurrentSection != NULL && R_MGMT_GetChannelType(gp_dlms_CurrentSection->mgmt_channel_id) == CHANNEL_TYPE_TCP))
	{
		push_distributor_params.connected_assc_id = CLASS40_ASSOCIATION_ID_PUSH;
		push_distributor_params.p_assc_session = &currentSection;
		currentSection.p_assc_config = (const AssociationCfg *)gp_asscs[CLASS40_ASSOCIATION_ID_PUSH];
	}
	else
	{
		push_distributor_params.connected_assc_id = gp_dlms_CurrentSection->connected_assc_id;
		push_distributor_params.p_assc_session = gp_dlms_CurrentSection;
		currentSection.p_assc_config = (const AssociationCfg *)gp_dlms_CurrentSection->p_assc_config;
	}

	/* Push to established association */
	if ( (push_distributor_params.p_assc_session->p_assc_config->conformance_byte2 & CONFORMANCE_BYTE2_DATA_NOTIFICATION) != 0)
	{
		/* Data Notification is supported */
		remote_wport = push_distributor_params.p_assc_session->p_assc_config->remote_wport;
	}
	else
	{
		/* Data Notification is not supported */
		return PUSH_CALL_ERR_DATA_NOTIFICATION_SERVICE_NOT_AVAILABLE;
	}

	push_distributor_params.in_data.p_content = NULL;
	push_distributor_params.in_data.length = 0;

	push_distributor_params.out_data.p_content = push_apdu_buffer;
	push_distributor_params.out_data.length = PUSH_APDU_SIZE;

	push_distributor_params.p_out_encoded_len = &encoded_length;

	R_DLMS_Push_FindChildRecord(push_channel, &push_distributor_params.child_index);
	/* Build PDU */
	R_DLMS_OBJECTS_Class40_EncodeCapturedData( &push_distributor_params );
//	push_apdu_buffer[0] = 0x09; // Octet String
//	push_apdu_buffer[1] = 17; // Mesasge Length
//	memcpy(&push_apdu_buffer[2], "ServerPushMessage", 17);  // Message content
//	encoded_length = 19;

	params.notification_body.p_content = push_apdu_buffer;
	params.notification_body.length = encoded_length;

	apdu_dispatch_context.attribute_access_right = 0;
	apdu_dispatch_context.method_access_right = 0;
	apdu_dispatch_context.p_additional_params = &additional_service_params;
	apdu_dispatch_context.p_security_context = currentSection.p_assc_config->p_security_context;
#if (DLMS_LIB_VERSION >= LIB_V2_3)
	apdu_dispatch_context.tbuf.p_content = push_apdu_tbuf;
	apdu_dispatch_context.tbuf.length = PUSH_APDU_SIZE + 64;
#endif /* DLMS_LIB_VERSION >=LIB_V2_3 */
	/* Work arround to disable cipher when security policy is SECURITY_NONE */
	if (apdu_dispatch_context.p_security_context->security_policy != SECURITY_NONE)
	{
		p_security_element = R_APDU_PushProtectionLayer(&additional_service_params.security_options);
		ASSERT_TRUE_RET_VAL(p_security_element == NULL, PUSH_CALL_ERR_PUSH_SETUP_NULL);
		p_security_element->protection_type = PROTECTION_GENERAL_GLO_CIPHERING;
		/* PUSH with minimum security by security policy configured on security context object */
		p_security_element->security_control = R_APDU_BuildSecurityControlByte(currentSection.p_assc_config->p_security_context, 0, 0);
	}
	params.p_dispatch_context = &apdu_dispatch_context;

	/* [Dependency] DLMS Lib2.0: Data Notification Service */
	switch ( g_push_setup[push_channel].destination.service )
	{
		case PUSH_TRANSPORT_SERVICE_TCP:
			mgmt_channel = DLMS_TCP_CHANNEL_START_ID + 0;
			port = g_push_setup[push_channel].destination.config.ip_port.port;
			ipaddress.p_addr = g_push_setup[push_channel].destination.config.ip_port.buffer;
			ipaddress.size = g_push_setup[push_channel].destination.config.ip_port.size;
			R_COSEM_DATA_NOTIFICATION_SetTcpDestination(
				mgmt_channel,
				remote_wport,
				port,
				&ipaddress
			);
			tcp_result = R_TCP_WRP_TryOpenConnection(port, &ipaddress);
			
			if (tcp_result == TRUE)
			{
				// WRP_EXT_HwDelay(50, EVENT_IsLastGasp);			// Use this function if meter have Last Gasp event.
				WRP_EXT_HwDelay(50, NULL);
				
				result_error_code = R_COSEM_DATA_NOTIFICATION_Request(DLMS_TCP_CHANNEL_START_ID + 0, &params);
				/* The connection is leaved open until client want to close */
				R_TCP_WRP_TryCloseConnection(port, &ipaddress);
				if (result_error_code == FALSE)
				{
					return PUSH_CALL_ERR_DATA_NOTIFICATION_FAILED;
				}
			}
			else
			{
				return PUSH_CALL_ERR_CAN_NOT_OPEN_CONNECTION;
			}
			
			break;
		case PUSH_TRANSPORT_SERVICE_UDP:
			mgmt_channel = DLMS_UDP_CHANNEL_START_ID + 0;
			port = g_push_setup[push_channel].destination.config.ip_port.port;
			ipaddress.p_addr = g_push_setup[push_channel].destination.config.ip_port.buffer;
			ipaddress.size = g_push_setup[push_channel].destination.config.ip_port.size;
			R_COSEM_DATA_NOTIFICATION_SetUdpDestination(
				mgmt_channel,
				remote_wport,
				port,
				&ipaddress
			);
			result_error_code = R_COSEM_DATA_NOTIFICATION_Request(DLMS_UDP_CHANNEL_START_ID + 0, &params);
			break;
		case PUSH_TRANSPORT_SERVICE_HDLC:
			return PUSH_CALL_ERR_TRANSPORT_SERVICE_UNSUPPORTED;
		default:
			return PUSH_CALL_ERR_TRANSPORT_SERVICE_UNSUPPORTED;
	}

	return PUSH_CALL_ERR_NONE;
}


/******************************************************************************
* Function Name : R_DLMS_Push_CheckWindow
* Interface     : uint8_t R_DLMS_Push_CheckWindow(
*               :     push_config_t *p_push_setup
*               : );
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_Push_CheckWindow(push_config_t *p_push_setup)
{
	uint8_t 				window_status = WINDOWS_INACTIVE;
	int8_t                  match_result1;
	int8_t                  match_result2;
	date_time_params_t *    p_rtc_profile;
	uint16_t				window_index;

	if (p_push_setup == NULL)
	{
		return window_status;
	}

	/* Check window status */
	if (p_push_setup->num_of_window == 0)
	{
		window_status = WINDOWS_ACTIVE;
	}
	else
	{
		window_status = WINDOWS_INACTIVE;
		/* 
		 * Check whether the window is active or inactive
		 * by compare window setting with current date_time
		 */

		/* Get current date time */
		p_rtc_profile = R_DLMS_RTC_Get_TimeProfile();
	
		for ( window_index = 0; window_index < p_push_setup->num_of_window; window_index++)
		{
			/* Start time */
			match_result1 = R_DLMS_RTC_Compare( (uint8_t *)&p_rtc_profile->date_time.current, (uint8_t *)&p_push_setup->p_window[window_index].start);
			/* End time */
			match_result2 = R_DLMS_RTC_Compare( (uint8_t *)&p_rtc_profile->date_time.current, (uint8_t *)&p_push_setup->p_window[window_index].end);
			
			if (match_result1 >= 0 && match_result2 <= 0)
			{
				window_status = WINDOWS_ACTIVE;
				break;
			}
			else
			{
				window_status = WINDOWS_INACTIVE;
			}
		}
		
	} /* End check window */

	return window_status;
}

/******************************************************************************
* Function Name : R_USER_PushHandler_MessageSent
* Interface     : void R_USER_PushHandler_MessageSent(
*               :     uint8_t push_channel
*               : );
* Description   :
* Arguments     : uint8_t push_channel
* Return Value  : void
******************************************************************************/
void R_USER_PushHandler_MessageSent(uint8_t push_channel)
{
	/* Special event: ESW is pushed, Clear related bits */
	R_DLMS_Push_ClearNoneRestorationlBits(push_channel);
}

/******************************************************************************
* Function Name : R_USER_PushHandler_MessageCannotPush
* Interface     : void R_USER_PushHandler_MessageCannotPush(
*               :     uint8_t push_channel
*               : );
* Description   : This is user function to handle futher process when push message can't send:
*               :      + Push IP is not configured or Window is inactive;
*               :  and 
*               :      + Push process reached Max number of retry.
* Arguments     : uint8_t push_channel
* Return Value  : void
******************************************************************************/
void R_USER_PushHandler_MessageCannotPush(uint8_t push_channel)
{						
	/* Reached maximum nuber of retry, can't push ESW, clear related events */
	R_DLMS_Push_ClearNoneRestorationlBits(push_channel);
}

/******************************************************************************
* Function Name : R_DLMS_Push_Init
* Interface     : void R_DLMS_Push_Init(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_Push_Init ( void )
{
    uint8_t push_channel;
	push_destination_t dest_cfg;
	
	//R_DLMS_Push_Format();
    for ( push_channel = 0 ; push_channel < R_DLMS_PUSH_OBJECT_MAXNUMBER ; push_channel++ )
    {
        g_push_setup[push_channel].p_window = g_push_window[push_channel];

		if (R_DLMS_Push_Restore_DestinationSetup ( 
				push_channel,
				&dest_cfg
			) == PUSH_RESULT_SUCCESS)
			{
				memcpy((uint8_t *)&g_push_setup[push_channel].destination, (uint8_t *)&dest_cfg, sizeof(push_destination_t));
			}
        R_DLMS_Push_Restore_CommWin(push_channel);
        R_DLMS_Push_Restore_RepetitionDelay(push_channel);
        R_DLMS_Push_Restore_RandomisationStartInterval(push_channel);
        R_DLMS_Push_Restore_NumberOfRetry(push_channel);
		
		R_DLMS_Push_Enable(push_channel);
    }
}

/******************************************************************************
* Function Name : R_DLMS_Push_PollingProcessing
* Interface     : void R_DLMS_Push_PollingProcessing( void )
* Description   : Push polling processing
* Arguments     : void
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_DLMS_Push_PollingProcessing(void)
{
    /* Put polling processing code for all objects of Class 40 here */

    uint8_t                 window_status = WINDOWS_INACTIVE;
    int8_t                  match_result;
   
    uint8_t                 push_channel;

    push_call_error_code_t  invoke_result;
    static int32_t          seed;                   /* To generate random number */

    date_time_t             mDateTime;

	uint8_t                 g_push_status;

	uint8_t                 rand_interval;
	
	uint8_t                 retry_delay_time;
    uint8_t                 counter_id;
	date_time_params_t *    p_rtc_profile;
    
    push_config_t           *p_push_setup;
	if (g_event_request_flag.periodic_msg_1 == TRUE)
	{
		R_DLMS_Push_SetFlag(0);
		g_event_request_flag.periodic_msg_1 = FALSE;
	}
	else if (g_event_request_flag.periodic_msg_2 == TRUE)
	{
		R_DLMS_Push_SetFlag(1);
		g_event_request_flag.periodic_msg_2 = FALSE;
	}
	else if (g_event_request_flag.event_alert == TRUE)
	{
		R_DLMS_Push_SetFlag(1);
		g_event_request_flag.event_alert = FALSE;
	}
    #define PUSH_PROCESSING_ENABLE (1)

    #ifdef PUSH_PROCESSING_ENABLE
    /* Check if there is any push trigger */
    for ( push_channel = 0 ; push_channel < R_DLMS_PUSH_OBJECT_MAXNUMBER; push_channel++ )
    {
        p_push_setup = &g_push_setup[push_channel];
        if (p_push_setup->enable == TRUE)
        {
			g_push_status = p_push_setup->state;
            counter_id = R_DLMS_RTC_COUNTER_ID_PUSH0 + push_channel;

            if  ( (g_push_status == (uint8_t) PUSH_STATUS_TRIGGED)             ||
                  (g_push_status == (uint8_t) PUSH_STATUS_RANDOMISATION_START) ||
                  (g_push_status == (uint8_t) PUSH_STATUS_RETRY)
                )
            {
                window_status = R_DLMS_Push_CheckWindow(p_push_setup);

#if 0
				/* Todo: Custom Pseudorandom Number Generator algorithm */
				
				/* Inital state for Pseudorandom number generator */
				seed++;

				/* ----- Pseudorandom Number Generator --------- */
				/* Xorshift */
				seed ^= seed << 13;
				seed ^= seed >> 17;
				seed ^= seed << 5;

				/* The state word must be initialized to non-zero */
				if (seed == 0)
				{
					seed = (uint16_t)&window_status;
				}

				if (p_push_setup->delay_start_max == 0)
				{
					/* If the randomisation_start_interval is set to 0 no delay is active. */
					seed = 0;
				}
				/* ---------------------------------------------- */
#else
				/* India may no need randomisation_start_interval */
				seed = 0;
#endif

            }

            if (g_push_status == PUSH_STATUS_TRIGGED)
            {
                if (R_DLMS_Push_CheckDestinationAddress(push_channel) == TRUE)
				{
					if (window_status == WINDOWS_ACTIVE)
					{
						/* TODO: push operation is started after randomly delayed within the interval.*/
						p_push_setup->delay_start = p_push_setup->delay_start_max;
						if (p_push_setup->delay_start > 0)
						{
							/* The randomisation_start_interval is only active for the first push attempt. */
							rand_interval =  (uint32_t) seed % (p_push_setup->delay_start);

							/* Start the counter  */
							R_DLMS_RTC_Counter_Reset(counter_id);
							R_DLMS_RTC_Counter_SetValue(counter_id, rand_interval);
						}
						else
						{
							R_DLMS_RTC_Counter_Reset(counter_id);
							R_DLMS_RTC_Counter_SetValue(counter_id, 0);
						}

						p_push_setup->retried_num = p_push_setup->retried_num_max; 

						/* Change push status */
						p_push_setup->state = PUSH_STATUS_RANDOMISATION_START;
					}
				}	
				else
				{
					/* No push attempt if Destination Address in Push setup is not valid */
				}
            }

            if (g_push_status == (uint8_t) PUSH_STATUS_RANDOMISATION_START)
            {
                if ( R_DLMS_RTC_Counter_GetValue(counter_id) == 0)
                {
					if (window_status == WINDOWS_INACTIVE)		
					{
						/* 
						 * If no communication window is active when invoking the push method, 
						 * the delay starts at the beginning of the next communication window. 
						 */

						/* Restart the state, holding trigger state until communication window is active */
						g_push_status = PUSH_STATUS_TRIGGED;
					}
					else
					{
						/* Attempt 1st push */
						p_push_setup->state = PUSH_STATUS_RETRY;
                    	// Counter value is already == 0
					}
                }
            }
            
            if (g_push_status == (uint8_t) PUSH_STATUS_RETRY)
            {
                if ( R_DLMS_RTC_Counter_GetValue(counter_id) == 0 )
                {
                    if (window_status == WINDOWS_ACTIVE)
                    {
                        /* Try to push */
                        invoke_result = R_DLMS_Push_ServiceCall(push_channel);
                        
                        /* end push ? */
                        if ( invoke_result == PUSH_CALL_ERR_NONE )
                        {
							R_USER_PushHandler_MessageSent(push_channel);

                            R_DLMS_RTC_Counter_Reset(counter_id);
                            R_DLMS_RTC_Counter_SetValue(counter_id, 0);
                            R_DLMS_RTC_Counter_Disable(counter_id);
                        
							/* 
							 * After a successful push operation no further push 
							 * attempts are made until the push operation is triggered again 
							 */
                            p_push_setup->state = PUSH_STATUS_NONE;
                            return;
                        }
                    }
					else
					{
						/* 
						 * Communication window is inactive, 
						 * It is handled like an unsuccessful push attempt. 
						 * Do nothing, continue next step to countdown number_of_retries.
						 */
					}

					/* Check the number of retries */
                    if (p_push_setup->retried_num > 0)
                    {
                        p_push_setup->retried_num--;

                        p_push_setup->state = PUSH_STATUS_RETRY;

						if (p_push_setup->num_of_window == 0)
						{
							/* 
							 * If no communication_window is defined, 
							 * the randomisation_start_interval is active for every push attempt.
							 */
							p_push_setup->delay_retry = (uint32_t) seed % (p_push_setup->delay_start);
						}
						else
						{
                        	p_push_setup->delay_retry = p_push_setup->delay_retry_max; 
						}

                        R_DLMS_RTC_Counter_Reset(counter_id);
						R_DLMS_RTC_Counter_SetValue(counter_id,  p_push_setup->delay_retry);
                    }
                    else
                    {
						/* Push attemp reach the maximum number of retries */
						R_USER_PushHandler_MessageCannotPush(push_channel);

                        R_DLMS_RTC_Counter_Reset(counter_id);
                        R_DLMS_RTC_Counter_SetValue(counter_id, 0);
                        R_DLMS_RTC_Counter_Disable(counter_id);
                        
                        p_push_setup->state = PUSH_STATUS_NONE;
                    }
                }
            }

            if (g_push_status >= (uint8_t) PUSH_STATUS_OTHER)
            {
                R_DLMS_RTC_Counter_Disable(counter_id);
                p_push_setup->state = PUSH_STATUS_NONE;
            }
        }

    }
    #endif
}