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
* File Name    : r_activity_cal.c
* Version      : v1.00.1
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Smart Meter Platform
* Description  : This file handle backup/restore activity calender from EEPROM
*                Process copy from passive buffer to active buffer
*                Check schedule to activate TOD profile
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 2018-04-03               v1.0.0  New creation
// 2018-08-13 10:03:00      v1.0.1  Add scheduler check
//                                  Add CRC calculation
// 2019-07-09 16:16:01      Fixing issue "Event wrongly logging 2 times for Activity Calendar time zones in profile generic Transaction related events (0.0.99.98.3.255)"

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Drivers */
#include "typedef.h"
#include "r_cg_macrodriver.h"        /* MD Macro Driver */
#include "r_cg_crc.h"

/* EM/SDK */
#include "eeprom.h"

/* Meter Application */
#include "event.h"
#include "storage.h"
#include "r_tariff.h"
#include "r_scheduler.h"
#include "r_activity_cal.h"

/* Standard Lib */
#include <string.h>         /* String Standard Lib */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#define CHECK_ZERO_RETURN(eql)				if ( (eql) == 0) 		{ return; }
#define CHECK_NOT_FOUND_RETURN(eql)			if ( (eql) == 0xFF)		{ return; }

#define ACTIVE_PROFILE_START_ADDRESS 		(STORAGE_EEPROM_CAL_NAME_ACTIVE_ADDR)
#define ACTIVITY_CALENDAR_PROFILE_SIZE		((STORAGE_EEPROM_CAL_NAME_PASSIVE_ADDR) - (STORAGE_EEPROM_CAL_NAME_ACTIVE_ADDR))
#define PASSIVE_PROFILE_START_ADDRESS		(STORAGE_EEPROM_CAL_NAME_PASSIVE_ADDR)
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum tag_activity_cal_state_t
{
	ACTIVITY_CAL_NONE,
	ACTIVITY_CAL_ACTIVE_TO_PASSIVE_INITIATED,
	ACTIVITY_CAL_CALCULATE_PASSIVE_CRC,
	ACTIVITY_CAL_COPING,
	ACTIVITY_CAL_COPIED,
	ACTIVITY_CAL_VERIFY_INITIATED,
	ACTIVITY_CAL_VERIFING,
	ACTIVITY_CAL_VERIFIED,
	ACTIVITY_CAL_ACTIVATED,
	ACTIVITY_CAL_ERROR_DATA
} activity_cal_state_t;

typedef struct tag_act_cal_storage_location_size_t
{
    uint32_t addr;
    uint16_t size;
} act_cal_storage_location_size_t;

typedef struct tag_act_cal_operation_state_t
{
    uint8_t passive_to_act_copy_state;
    uint8_t activate_flag;
    uint8_t season_state;
} act_cal_operation_state_t;
 
/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global CONST
***********************************************************************************************************************/

const act_cal_storage_location_size_t eeprom_cal_process_state  = { STORAGE_EEPROM_CAL_PROCESSING_STATE_ADDR, 		STORAGE_EEPROM_CAL_PROCESSING_STATE_SIZE};
const act_cal_storage_location_size_t eeprom_activate_time      = { STORAGE_EEPROM_CAL_ACTIVATION_TIME_ADDR,		STORAGE_EEPROM_CAL_ACTIVATION_TIME_SIZE};
const act_cal_storage_location_size_t eeprom_activate_state     = { STORAGE_EEPROM_CAL_ACTIVE_STATE_ADDR, 			STORAGE_EEPROM_CAL_ACTIVE_STATE_SIZE};
const act_cal_storage_location_size_t eeprom_season_state       = { STORAGE_EEPROM_CAL_SEASON_STATE_ADDR, 			STORAGE_EEPROM_CAL_SEASON_STATE_SIZE};

const r_act_cal_name_t 			G_CALENDAR_NAME_DEFAULT = {
	sizeof(TOD_CALENDAR_NAME_8BYTES_DEFAULT) - 1,
	TOD_CALENDAR_NAME_8BYTES_DEFAULT
};

const r_act_cal_season_profile_t 	G_SEASON_PROFILE_DEFAULT = {
	TOD_NUMBER_SEASON_DEFAULT,
	{
		/* Season 01 */
		{
			/* Season name */
			{ sizeof(TOD_SEASON_NAME_00_8BYTES_DEFAULT) - 1, TOD_SEASON_NAME_00_8BYTES_DEFAULT },
			TOD_SEASON_00_START_TIME,
			{ sizeof(TOD_WEEK_NAME_00_8BYTES_DEFAULT) - 1, TOD_WEEK_NAME_00_8BYTES_DEFAULT}
		},
		/* Season 02 */
		{
			/* Season name */
			{ sizeof(TOD_SEASON_NAME_01_8BYTES_DEFAULT) - 1, TOD_SEASON_NAME_01_8BYTES_DEFAULT },
			TOD_SEASON_01_START_TIME,
			{ sizeof(TOD_WEEK_NAME_01_8BYTES_DEFAULT) - 1, TOD_WEEK_NAME_01_8BYTES_DEFAULT}
		}
	}
};

const r_act_cal_week_profile_t G_WEEK_PROFILE_DEFAULT =
{
	TOD_NUMBER_WEEK_DEFAULT,
	{
		/* Week 0 */
		{ 
			/* Name */
			{ sizeof(TOD_WEEK_NAME_00_8BYTES_DEFAULT) - 1, TOD_WEEK_NAME_00_8BYTES_DEFAULT },
			/* Data[7] */
			{
				TOD_WEEK_PROFILE_0_Mo,
				TOD_WEEK_PROFILE_0_Tu,
				TOD_WEEK_PROFILE_0_We,
				TOD_WEEK_PROFILE_0_Th,
				TOD_WEEK_PROFILE_0_Fr,
				TOD_WEEK_PROFILE_0_Sa,
				TOD_WEEK_PROFILE_0_Su
			}
		},
		/* Week 1 */
		{
			/* Name */
			{ sizeof(TOD_WEEK_NAME_01_8BYTES_DEFAULT) - 1, TOD_WEEK_NAME_01_8BYTES_DEFAULT },
			/* Data[7] */
			{
				TOD_WEEK_PROFILE_1_Mo,
				TOD_WEEK_PROFILE_1_Tu,
				TOD_WEEK_PROFILE_1_We,
				TOD_WEEK_PROFILE_1_Th,
				TOD_WEEK_PROFILE_1_Fr,
				TOD_WEEK_PROFILE_1_Sa,
				TOD_WEEK_PROFILE_1_Su
			}
		},
	}
};


const r_act_cal_day_profile_t G_DAY_PROFILE_DEFAULT =
{
	TOD_NUMBER_DAY_PROFILE,			/* Number of day profile */
	{
		{
			0,											/* Day profile ID */
			TOD_DAY_PROFILE_NUMBER_ACTION,				/* Number of action */
			{
				/* Hour,  Min, ScriptID */
				{ TOD_DAY_PROFILE_TIMESLOT0,	TOD_DAY_PROFILE_ACTIVE_SLOT0 },
				{ TOD_DAY_PROFILE_TIMESLOT1,	TOD_DAY_PROFILE_ACTIVE_SLOT1 },
				{ TOD_DAY_PROFILE_TIMESLOT2,	TOD_DAY_PROFILE_ACTIVE_SLOT2 },
				{ TOD_DAY_PROFILE_TIMESLOT3,	TOD_DAY_PROFILE_ACTIVE_SLOT3 },
				{ TOD_DAY_PROFILE_TIMESLOT4,	TOD_DAY_PROFILE_ACTIVE_SLOT4 },
				{ TOD_DAY_PROFILE_TIMESLOT5,	TOD_DAY_PROFILE_ACTIVE_SLOT5 },

			}
		},
		{
			1,											/* Day profile ID */
			TOD_DAY_PROFILE_NUMBER_ACTION,				/* Number of action */
			{
				{ TOD_DAY_PROFILE_TIMESLOT0,	TOD_DAY_PROFILE_ACTIVE_SLOT0 },
				{ TOD_DAY_PROFILE_TIMESLOT1,	TOD_DAY_PROFILE_ACTIVE_SLOT1 },
				{ TOD_DAY_PROFILE_TIMESLOT2,	TOD_DAY_PROFILE_ACTIVE_SLOT2 },
				{ TOD_DAY_PROFILE_TIMESLOT3,	TOD_DAY_PROFILE_ACTIVE_SLOT3 },
				{ TOD_DAY_PROFILE_TIMESLOT4,	TOD_DAY_PROFILE_ACTIVE_SLOT4 },
				{ TOD_DAY_PROFILE_TIMESLOT5,	TOD_DAY_PROFILE_ACTIVE_SLOT5 },
			}
		}
	}
};

/***********************************************************************************************************************
Private global variables
***********************************************************************************************************************/

// Private variable
uint8_t					g_tod_process_state	= ACTIVITY_CAL_NONE;
uint32_t				g_bytes_offset = 0;
volatile uint16_t		g_tod_current_crc[2];
uint8_t 				g_tod_init_flag = FALSE;
uint8_t                 g_tod_activate_trigger_ack_flag = TRUE;
uint8_t                 g_cal_first_activate_after_formating = FALSE;

uint8_t  is_new_cal_profile_active = FALSE;

/***********************************************************************************************************************
Private global functions
***********************************************************************************************************************/

/* Function prototype */
uint8_t R_ACT_CAL_FindActiveSeason(
    r_act_cal_season_profile_t *p_season_profile,
    rtc_counter_value_t        *p_current_time  ,
    r_act_cal_season_t         *p_active_season
);

void R_ACT_CAL_FindChangedTimeslotThenCaptureTariffEnergy(rtc_counter_value_t *p_input_time);

void R_ACT_CAL_ApplyNewSeasonProfile(
    r_act_cal_season_profile_t *p_season_profile
);

void R_ACT_CAL_FindWeekProfileFromActiveSeason(
    r_act_cal_season_t          *p_season_profile,
    r_act_cal_week_t            *p_week_profile_out
);

void R_ACT_CAL_FindWeekProfileFromActiveSeason(
    r_act_cal_season_t          *p_season_profile, 
    r_act_cal_week_t            *p_week_profile_out
);

uint8_t R_ACT_CAL_FindActiveDayProfileFromWeekProfile(
    r_act_cal_week_t            *p_week_profile, 
    uint8_t                     day_of_week,
    r_act_cal_day_t             *p_day_profile
);

static void R_ACT_CAL_ApplyActiveDayProfile(
    r_act_cal_day_t             *p_profile
);


/******************************************************************************
* Function Name : R_ACT_CAL_Get_ActivationTime
* Interface     : uint8_t R_ACT_CAL_Get_ActivationTime(
*               :     rtc_counter_value_t *p_data_out
*               : );
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_ACT_CAL_Get_ActivationTime(rtc_counter_value_t *p_data_out)
{
    memcpy(
        p_data_out, 
        &g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_ACT].p_execution_time[0],
        sizeof(rtc_counter_value_t)
    );

	return TRUE;
}

/******************************************************************************
* Function Name : R_ACT_CAL_Set_ActivateTime
* Interface     : void R_ACT_CAL_Set_ActivateTime(
*               :     R_DLMS_RTC_T rtc
*               : );
* Description   : Set activation time
* Arguments     : rtc_counter_value_t *p_data_in
* Return Value  : TRUE  : SET and backup all are OK
*               : FALSE : EEPROM Write failed
******************************************************************************/
uint8_t R_ACT_CAL_Set_ActivateTime(rtc_counter_value_t *p_data_in)
{
	uint8_t result_value = FALSE;
    int32_t timezone_transferred;

    uint8_t array_len = 1;
    uint8_t element_index = 0;

    uint8_t date_schedule[4];
    uint8_t time_schedule[4];

    date_schedule[0] = p_data_in->year;
    date_schedule[1] = p_data_in->month;
	date_schedule[2] = p_data_in->week;
	date_schedule[3] = p_data_in->day;
	/* Time */
	time_schedule[0] = p_data_in->hour;
	time_schedule[1] = p_data_in->min;
	time_schedule[2] = p_data_in->sec;

    R_SCHEDULER_ExecutionTimeArrayLengthSet(SCHEDULER_ID_ACTIVITY_CAL_ACT, array_len);
    R_SCHEDULER_ExecutionDateSet(date_schedule, SCHEDULER_ID_ACTIVITY_CAL_ACT, element_index);
    R_SCHEDULER_ExecutionTimeSet(time_schedule, SCHEDULER_ID_ACTIVITY_CAL_ACT, element_index);

	return TRUE;
}

/******************************************************************************
* Function Name : R_ACT_CAL_RequestCopyPassiveToActive
* Interface     : uint8_t R_ACT_CAL_RequestCopyPassiveToActive(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_ACT_CAL_RequestCopyPassiveToActive ( void )
{
	g_tod_process_state = ACTIVITY_CAL_ACTIVE_TO_PASSIVE_INITIATED;
	g_tod_activate_trigger_ack_flag = TRUE;
	return TRUE;
}

/******************************************************************************
* Function Name : R_ACT_CAL_Backup_CalendarName
* Interface     : uint8_t R_ACT_CAL_Backup_CalendarName(
*               :     st_season_t
*               : );
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_ACT_CAL_Backup_CalendarName_Passive(r_act_cal_name_t *p_calendar_name)
{
    EPR_Write(
        STORAGE_EEPROM_CAL_NAME_PASSIVE_ADDR,
        (void *)p_calendar_name,
        sizeof(r_act_cal_name_t)
    );

	return TRUE;
}

/******************************************************************************
* Function Name : R_ACT_CAL_Restore_CalendarName
* Interface     : uint8_t R_ACT_CAL_Restore_CalendarName(
*               :     uint8_t is_passive
*               : );
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
r_act_cal_name_t R_ACT_CAL_Restore_CalendarName(uint8_t is_passive)
{
	r_act_cal_name_t 	calendar_name;

    uint32_t eppr_addr;
    uint16_t eppr_size;

	eppr_addr = 0;
	eppr_size = sizeof(r_act_cal_name_t);

	if (is_passive == TRUE)
	{
		eppr_addr = STORAGE_EEPROM_CAL_NAME_PASSIVE_ADDR;
	}
    else
    {
        eppr_addr = STORAGE_EEPROM_CAL_NAME_ACTIVE_ADDR;
    }

	EPR_Read(eppr_addr, (void *)&calendar_name, eppr_size);

	if (calendar_name.len > NAME_LENGTH_MAX)
	{
		calendar_name.len = NAME_LENGTH_MAX;
		g_tod_process_state = ACTIVITY_CAL_ERROR_DATA;
	}

	return calendar_name;
}


/******************************************************************************
* Function Name : R_ACT_CAL_Backup_SeasonProfile_Passive
* Interface     : uint8_t R_ACT_CAL_Backup_SeasonProfile_Passive(
*               :     
*               : );
* Description   :
* Arguments     :
* Return Value  :
******************************************************************************/
uint8_t R_ACT_CAL_Backup_SeasonProfile_Passive(r_act_cal_season_profile_t 	*p_profile)
{
	uint8_t result_value = FALSE;
    uint32_t eppr_addr;
    uint16_t eppr_size;

	eppr_addr = STORAGE_EEPROM_CAL_SEASON_PASSIVE_ADDR;
	eppr_size = sizeof(r_act_cal_season_profile_t);

	if (p_profile == NULL)
	{
		return result_value;
	}

    if (EPR_Write(eppr_addr, (void *)p_profile, eppr_size) == EPR_OK)
    {
        result_value = TRUE;
    }

	return result_value;
}

/******************************************************************************
* Function Name : R_ACT_CAL_Restore_Season
* Interface     : r_act_cal_season_t R_ACT_CAL_Restore_Season(
*               :     uint8_t season_index, uint8_t is_passive
*               : );
* Description   :
* Arguments     :
* Return Value  : r_act_cal_season_t
******************************************************************************/
r_act_cal_season_profile_t R_ACT_CAL_Restore_SeasonProfile(uint8_t is_passive)
{
	r_act_cal_season_profile_t 	profile;

    uint32_t eppr_addr = STORAGE_EEPROM_CAL_SEASON_ACTIVE_ADDR;
    uint16_t eppr_size = sizeof(r_act_cal_season_profile_t);

	if (is_passive == TRUE)
	{
		eppr_addr = STORAGE_EEPROM_CAL_SEASON_PASSIVE_ADDR;
	}

	EPR_Read(eppr_addr, (void *)&profile, eppr_size);

	if (profile.num > SEASON_PROFILE_ELEMENT_MAX)
	{
		profile.num = SEASON_PROFILE_ELEMENT_MAX;
		g_tod_process_state = ACTIVITY_CAL_ERROR_DATA;
	}

	return profile;
}

/******************************************************************************
* Function Name : R_ACT_CAL_Backup_Week_Passive
* Interface     : uint8_t R_ACT_CAL_Backup_Week_Passive(
*               :     
*               : );
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_ACT_CAL_Backup_WeekProfile_Passive(r_act_cal_week_profile_t *p_profile)
{
	uint8_t result_value = FALSE;
    uint32_t eppr_addr;
    uint16_t eppr_size;

	if (p_profile == NULL)
	{
		return result_value;
	}

    eppr_addr = STORAGE_EEPROM_CAL_WEEK_PASSIVE_ADDR;
    eppr_size = sizeof(r_act_cal_week_profile_t);

	if (EPR_Write(eppr_addr, (void *)p_profile, eppr_size) == EPR_OK)
    {
        result_value = TRUE;
    }

	return result_value;
}

/******************************************************************************
* Function Name : R_ACT_CAL_Restore_WeekProfile
* Interface     : r_act_cal_season_t R_ACT_CAL_Restore_WeekProfile(
*               :     uint8_t is_passive
*               : );
* Description   :
* Arguments     :
* Return Value  : r_act_cal_season_t
******************************************************************************/
r_act_cal_week_profile_t R_ACT_CAL_Restore_WeekProfile(uint8_t is_passive)
{
	r_act_cal_week_profile_t 	profile;

	uint32_t eppr_addr;
	uint32_t eppr_size = sizeof(r_act_cal_week_profile_t);

	if (is_passive == TRUE)
	{
		eppr_addr = STORAGE_EEPROM_CAL_WEEK_PASSIVE_ADDR;
	}
    else
    {
		eppr_addr = STORAGE_EEPROM_CAL_WEEK_ACTIVE_ADDR;
    }

	EPR_Read(eppr_addr, (void *)&profile, eppr_size);

	if (profile.num > WEEK_PROFILE_ELEMENT_MAX)
	{
		profile.num = WEEK_PROFILE_ELEMENT_MAX;
		g_tod_process_state = ACTIVITY_CAL_ERROR_DATA;
	}

	return profile;
}


/******************************************************************************
* Function Name : R_ACT_CAL_Backup_Day_Passive
* Interface     : uint8_t R_ACT_CAL_Backup_Day_Passive(
*               :     
*               : );
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_ACT_CAL_Backup_DayProfile_Passive(r_act_cal_day_profile_t *p_profile)
{
	uint8_t result_value = FALSE;
    uint32_t eppr_addr;
    uint32_t eppr_size;

	if (p_profile == NULL)
	{
		return result_value;
	}

	eppr_addr = STORAGE_EEPROM_CAL_DAY_PASSIVE_ADDR;
	eppr_size = sizeof(r_act_cal_day_profile_t);

	if (EPR_Write(eppr_addr, (void *)p_profile, eppr_size) == EPR_OK)
    {
        result_value = TRUE;
    }

	return result_value;
}

/******************************************************************************
* Function Name : R_ACT_CAL_Restore_DayProfile
* Interface     : r_act_cal_day_profile_t R_ACT_CAL_Restore_DayProfile(
*               :     uint8_t is_passive
*               : );
* Description   :
* Arguments     :
* Return Value  : r_act_cal_day_profile_t
******************************************************************************/
r_act_cal_day_profile_t R_ACT_CAL_Restore_DayProfile(uint8_t is_passive)
{
	r_act_cal_day_profile_t 	profile;

	uint32_t eppr_addr;
	uint32_t eppr_size = sizeof(r_act_cal_day_profile_t);

	if (is_passive == TRUE)
	{
		eppr_addr = STORAGE_EEPROM_CAL_DAY_PASSIVE_ADDR;
	}
    else
    {
		eppr_addr = STORAGE_EEPROM_CAL_DAY_ACTIVE_ADDR;
    }

	EPR_Read(eppr_addr, (void *)&profile, eppr_size);

	if (profile.num > DAY_PROFILE_ELEMENT_MAX)
	{
		profile.num = DAY_PROFILE_ELEMENT_MAX;
		g_tod_process_state = ACTIVITY_CAL_ERROR_DATA;
	}

	return profile;
}

/******************************************************************************
* Function Name : R_ACT_CAL_Format
* Interface     : uint8_t R_ACT_CAL_Format(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_ACT_CAL_Format(void)
{
	uint8_t numOfElement;
	uint8_t numOfAction;
	uint8_t i, j;

	/* 02 Calendar name */
	R_ACT_CAL_Backup_CalendarName_Passive((void *)&G_CALENDAR_NAME_DEFAULT);
	/* 03 Season profile */
	R_ACT_CAL_Backup_SeasonProfile_Passive((void *)&G_SEASON_PROFILE_DEFAULT);
	/* 04 Week profile */
	R_ACT_CAL_Backup_WeekProfile_Passive((void *)&G_WEEK_PROFILE_DEFAULT);
	/* 05 Day profile */
	R_ACT_CAL_Backup_DayProfile_Passive((void *)&G_DAY_PROFILE_DEFAULT);

	/* ACTIVE_PROFILE */
	g_tod_process_state = ACTIVITY_CAL_ACTIVE_TO_PASSIVE_INITIATED;
	g_tod_activate_trigger_ack_flag = FALSE;
    
	EPR_Write(eeprom_cal_process_state.addr, 	(uint8_t *)&g_tod_process_state, sizeof(uint8_t));

    /* Formatted */
	return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_ACT_CAL_Restore
* Interface     : uint8_t R_ACT_CAL_Restore(
*               :     void
*               : );
* Description   :
* Return Value  :
******************************************************************************/
uint8_t R_ACT_CAL_Restore(void)
{
	uint8_t i;
	uint8_t checking_week_day_id[7];
	uint8_t checking_week_ok = FALSE;
	uint8_t checking_dayID;

	/* Restore TOD processing state */
	EPR_Read(eeprom_cal_process_state.addr, (uint8_t *)&g_tod_process_state, eeprom_cal_process_state.size);
	//EPR_Read(eeprom_activate_time.addr, (uint8_t *)&g_tod_activate_time, eeprom_activate_time.size);

    return STORAGE_OK;
}



/******************************************************************************
* Function Name : R_ACT_CAL_Backup
* Interface     : uint8_t R_ACT_CAL_Backup(void)
* Description   : 
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
uint8_t	R_ACT_CAL_Backup(void)
{
	/* Write data of Tariff state: g_tariff to EEPROM */
	return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_ACT_CAL_Init
* Interface     : void R_ACT_CAL_Init(
*               :     void
*               : );
* Description   :
* Return Value  :
******************************************************************************/
void R_ACT_CAL_Init ( void )
{
	if (g_tod_process_state == ACTIVITY_CAL_COPIED)
	{
		g_tod_init_flag = TRUE;
	}
}




void R_ACT_CAL_CopyPassiveToActive(void);
/******************************************************************************
* Function Name : R_ACT_CAL_CopyPassiveToActive
* Interface     : void R_ACT_CAL_CopyPassiveToActive(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_ACT_CAL_CopyPassiveToActive(void)
{
	#define COPY_BLOCK_SIZE		(32)

	uint16_t block_size = 0;
	
	uint8_t buff[COPY_BLOCK_SIZE + 1];
	uint32_t temp;

	uint16_t i;

    /* Activation process */
	switch ( g_tod_process_state )
	{
		case ACTIVITY_CAL_ACTIVE_TO_PASSIVE_INITIATED:
			g_bytes_offset = 0;
			g_tod_current_crc[0] = 0x0001;
			g_tod_process_state = (uint8_t)ACTIVITY_CAL_CALCULATE_PASSIVE_CRC;
			break;
		case ACTIVITY_CAL_CALCULATE_PASSIVE_CRC:

			block_size = COPY_BLOCK_SIZE;

			if ((g_bytes_offset + (uint32_t)block_size) > (uint32_t)(ACTIVITY_CALENDAR_PROFILE_SIZE))
			{
				temp = ACTIVITY_CALENDAR_PROFILE_SIZE;
				block_size = (uint16_t)((uint32_t)(ACTIVITY_CALENDAR_PROFILE_SIZE) - g_bytes_offset);
			}

			{
				CRCD = g_tod_current_crc[0];

				temp = g_bytes_offset + PASSIVE_PROFILE_START_ADDRESS;
				EPR_Read( (temp), (uint8_t *)buff, block_size);
				for ( i = 0; i < block_size; i++ )
				{
					CRCIN = buff[i];
				}
				g_bytes_offset += block_size;

				g_tod_current_crc[0] = CRCD;
			}

			if (g_bytes_offset >= (uint32_t)(ACTIVITY_CALENDAR_PROFILE_SIZE))
			{
				g_bytes_offset = 0;
				g_tod_process_state = (uint8_t)ACTIVITY_CAL_COPING;
			}

			break;

		case ACTIVITY_CAL_COPING:
			block_size = COPY_BLOCK_SIZE;
			if ((g_bytes_offset + (uint32_t)block_size) > (uint32_t)(ACTIVITY_CALENDAR_PROFILE_SIZE))
			{
				temp = ACTIVITY_CALENDAR_PROFILE_SIZE;
				block_size = (uint16_t)((uint32_t)(ACTIVITY_CALENDAR_PROFILE_SIZE) - g_bytes_offset);
			}

			{
				temp = g_bytes_offset + PASSIVE_PROFILE_START_ADDRESS;
				EPR_Read( (temp), (uint8_t *)buff, block_size);
				temp = g_bytes_offset + ACTIVE_PROFILE_START_ADDRESS;
				EPR_Write( (temp), (uint8_t *)buff, block_size);
				g_bytes_offset += block_size;
			}

			if (g_bytes_offset >= (uint32_t)(ACTIVITY_CALENDAR_PROFILE_SIZE))
			{
				g_bytes_offset = 0;
				g_tod_process_state = (uint8_t)ACTIVITY_CAL_VERIFY_INITIATED;
			}
			break;
		case ACTIVITY_CAL_VERIFY_INITIATED:
			g_bytes_offset = 0;
			g_tod_current_crc[1] = 0x0001;
			g_tod_process_state = (uint8_t)ACTIVITY_CAL_VERIFING;
			break;
		case ACTIVITY_CAL_VERIFING:
			block_size = COPY_BLOCK_SIZE;

			if ((g_bytes_offset + (uint32_t)block_size) > (uint32_t)(ACTIVITY_CALENDAR_PROFILE_SIZE))
			{
				temp = ACTIVITY_CALENDAR_PROFILE_SIZE;
				block_size = (uint16_t)((uint32_t)(ACTIVITY_CALENDAR_PROFILE_SIZE) - g_bytes_offset);
			}

			{
				CRCD = g_tod_current_crc[1];

				temp = g_bytes_offset + ACTIVE_PROFILE_START_ADDRESS;
				EPR_Read( (temp), (uint8_t *)buff, block_size);
				for ( i = 0; i < block_size; i++ )
				{
					CRCIN = buff[i];
				}
				g_bytes_offset += block_size;

				g_tod_current_crc[1] = CRCD;
			}

			if (g_bytes_offset >= (uint32_t)(ACTIVITY_CALENDAR_PROFILE_SIZE))
			{
				if (g_tod_current_crc[0] == g_tod_current_crc[1])
				{
					g_tod_process_state = (uint8_t)ACTIVITY_CAL_VERIFIED;
				}
				else
				{
					g_tod_process_state = (uint8_t)ACTIVITY_CAL_ACTIVE_TO_PASSIVE_INITIATED;
				}
				g_bytes_offset = 0;
			}
			break;
		case ACTIVITY_CAL_VERIFIED:
			g_tod_process_state = (uint8_t)ACTIVITY_CAL_COPIED;
			
			if (g_tod_activate_trigger_ack_flag == TRUE)
			{
                g_event_flag.bits.set_calendar = TRUE;
				g_tod_activate_trigger_ack_flag = FALSE;
			}
			else
			{
				/* Not report event when format memory */
                g_cal_first_activate_after_formating = TRUE;
			}
			
			/* Backup TOD processing state when success */
			EPR_Write(eeprom_cal_process_state.addr, (uint8_t *)&g_tod_process_state, eeprom_cal_process_state.size);

            is_new_cal_profile_active = TRUE;

			break;
    }
}

static int8_t R_ACT_CAL_CompareDate(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2);
/******************************************************************************
* Function Name : R_ACT_CAL_CompareDate
* Interface     : int8_t R_ACT_CAL_CompareDate(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2)
* Description   :
* Arguments     :
* Return Value  : int8_t
*                       (-1)      p_rtc_1   <  p_rtc_2  
*                       (0)                    p_rtc_12  
*                       (1)                    p_rtc_2  <  p_rtc_1
******************************************************************************/
static int8_t R_ACT_CAL_CompareDate(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2)
{   
	int8_t diff = 0;
    if (p_rtc_1->year == p_rtc_2->year &&
        p_rtc_1->month == p_rtc_2->month &&
        p_rtc_1->day == p_rtc_2->day
        )   
    {
        return 0;
    }
	
    if (p_rtc_1->year != 0xFF && p_rtc_2->year != 0xFF)
    {
        diff = p_rtc_1->year - p_rtc_2->year;
        if (diff != 0)
        {
            return (diff);
        }
    }

    if (p_rtc_1->month != 0xFF && p_rtc_2->month != 0xFF)
    {
        diff = p_rtc_1->month - p_rtc_2->month;
        if (diff != 0)
        {
            return (diff);
        }
    }

    if (p_rtc_1->day != 0xFF && p_rtc_2->day != 0xFF)
    {
        diff = (p_rtc_1->day - p_rtc_2->day);
        if (diff != 0)
        {
            return (diff);
        }
    }

    return (0);
}
/******************************************************************************
* Function Name : R_ACT_CAL_CompareDateTime
* Interface     : int8_t R_ACT_CAL_CompareDateTime(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2)
* Description   :
* Arguments     :
* Return Value  : int8_t  (-1) Backward, (1) Forward
******************************************************************************/
static int8_t R_ACT_CAL_CompareDateTime(rtc_counter_value_t *p_rtc_1, rtc_counter_value_t *p_rtc_2)
{
    int16_t compare_result = R_ACT_CAL_CompareDate(p_rtc_1, p_rtc_2);
    uint32_t total_time1, total_time2;
    
    if (compare_result < 0)
    {
        return (-1);
    }
    else if (compare_result > 0)
    {
        return (1);
    }
    
    if (p_rtc_1->sec != 0xFF && p_rtc_2->sec != 0xFF)
    {
        total_time1 = p_rtc_1->sec;
        total_time2 = p_rtc_2->sec;
    }

    if (p_rtc_1->min != 0xFF && p_rtc_2->min != 0xFF)
    {
        total_time1 += p_rtc_1->min * 60;
        total_time2 += p_rtc_2->min * 60;
    }

    if (p_rtc_1->hour != 0xFF && p_rtc_2->hour != 0xFF)
    {
        total_time1 += p_rtc_1->hour * 60 * 60;
        total_time2 += p_rtc_2->hour * 60 * 60;
    }
    
    if (total_time1 == total_time2)
    {
        return (0);
    }
    else if (total_time1 > total_time2)
    {
        return (1);
    }

    return (-1);
}

/******************************************************************************
* Function Name : R_ACT_CAL_FindActiveSeason
* Interface     : void R_ACT_CAL_FindActiveSeason(
*                        r_act_cal_season_profile_t *p_season_profile, 
*                        rtc_counter_value_t *p_current_time, 
*                        r_act_cal_season_t *p_active_season
*                 )
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
uint8_t R_ACT_CAL_FindActiveSeason(
    r_act_cal_season_profile_t *p_season_profile, 
    rtc_counter_value_t *p_current_time, 
    r_act_cal_season_t *p_active_season
)
{
    uint8_t i;
    uint8_t found = FALSE;
    uint8_t skip_count = 0;

    if (p_season_profile == NULL)
    {
        return FALSE;
    }

    for (i = 0; i < p_season_profile->num; i++)
    {
        if (p_season_profile->entry[i].start_time.hour == 0xFF &&
            p_season_profile->entry[i].start_time.min == 0xFF &&
            p_season_profile->entry[i].start_time.sec == 0xFF &&
            p_season_profile->entry[i].start_time.year == 0xFF &&
            p_season_profile->entry[i].start_time.month == 0xFF &&
            p_season_profile->entry[i].start_time.day == 0xFF)
            {
                skip_count++;
                continue;
            }
            
        /* Check if RTC > season start time */
        if (R_ACT_CAL_CompareDateTime(
                &p_season_profile->entry[i].start_time,
                p_current_time
            ) <= 0)
        {
            /* RTC > season start time => In range */
            *p_active_season = p_season_profile->entry[i];
            found = TRUE;
        }
    }
    
    if (skip_count >= p_season_profile->num)
    {
        /* All seasons are 0xFF, not activated */
        return FALSE;
    }
    
    if (found)
    {
        /* Example case:
        
        Season 1: Start from 2/2
        Season 2: Start from 6/6
        
        RTC = 3/3
        
        => 3/3 is Season 1
        
        1/1        2/2         6/6           31/12
                   | Season 1 |   Season 2     |
        
        */
        
        return TRUE;
    }
    else
    {
        /* Example case:
        
        Season 1: Start from 2/2
        Season 2: Start from 6/6
        
        => From 1/1 to 2/2 is belong to the last season.
        
        1/1        2/2         6/6           31/12
               X  | Season 1 |   Season 2     |
        
        */
        
        *p_active_season = p_season_profile->entry[p_season_profile->num - 1];
        return TRUE;
    }
    
}

/******************************************************************************
 * Function Name: R_ACT_CAL_FindChangedTimeslotThenCaptureTariffEnergy
 * Description  : Check if new time is on different timeslot and conclude the tariff
 *              : This API work in condition that 
 *              :   timeslot sorted in chronological order
 *              :   Not overlap each other
 *              :   No unspecified timeslot in between
 * Arguments    : rtc_counter_value_t * p_input_time: checking time in decimal
 * Return Value : void
******************************************************************************/
void R_ACT_CAL_FindChangedTimeslotThenCaptureTariffEnergy(rtc_counter_value_t *p_input_time)
{
    int8_t      i;
    uint16_t    real_minute, timeslot_minute, current_timeslot;
    uint16_t    number_timeslot = g_scheduler[SCHEDULER_ID_TARIFF].number_of_exe_time;
    r_scheduler_datetime_t * p_execution_time = g_scheduler[SCHEDULER_ID_TARIFF].p_execution_time;

    /* Find the slot matched the input_time  */
    for (i = number_timeslot - 1; i >= 0; i--)
    {
        real_minute = ((uint16_t)p_input_time->hour) * 60 + p_input_time->min;
        timeslot_minute = ((uint16_t)p_execution_time[i].Hour) * 60 + p_execution_time[i].Min;
        if (real_minute >= timeslot_minute)
        {
            /* Matched slot */
            break;
        }
        else
        {
            /* Not matched, continue checking other slot */
        }
    }

    /* Not found? : occur when the rtc time change from 23:59 to 00:00 and the first slot not start from 00:00 */
    if (i == -1)
    {
        current_timeslot = number_timeslot - 1;
    }
    else
    {
        current_timeslot = i;
    }

    /* Check if tariff slot changed */
    if (g_tariff_lookup_timeslot_tariff_number[current_timeslot] != g_tariff.current_tariff_no)
    {
        /* Tariff slot changed, capture current tariff slot and start accumulate on new slot */
        g_scheduler_match_context[SCHEDULER_ID_TARIFF].exe_time_id = current_timeslot;
        g_event_request_flag.is_tariff_changed = 1;
        R_TARIFF_PollingProcessing();
    }
    else
    {
        /* Not changed, continue to accumulate energy for this timeslot */
    }
}


/******************************************************************************
* Function Name : R_ACT_CAL_FindAndActiveNewSeason
* Interface     : void R_ACT_CAL_FindAndActiveNewSeason(rtc_counter_value_t *p_rtctime)
* Description   :
* Arguments     : rtc_counter_value_t *p_rtctime
* Return Value  : void
******************************************************************************/
void R_ACT_CAL_FindAndActiveNewSeason(rtc_counter_value_t *p_rtctime)
{
    r_act_cal_season_profile_t  season_profile;
    r_act_cal_season_t          active_season;
    r_act_cal_week_profile_t    week_profile;
    r_act_cal_week_t            active_week_profile;
    r_act_cal_day_t             active_day_profile;

    uint8_t find_result;

    season_profile = R_ACT_CAL_Restore_SeasonProfile(ACTIVE_PROFILE);
    find_result = R_ACT_CAL_FindActiveSeason(
        &season_profile,
        p_rtctime,
        &active_season
    );
    if (find_result == FALSE)
    {
        return;
    }

    R_ACT_CAL_FindWeekProfileFromActiveSeason(
        &active_season,                                             /* Input */
        &active_week_profile                                        /* Output */
    );

    find_result = R_ACT_CAL_FindActiveDayProfileFromWeekProfile(
        &active_week_profile,                                       /* Input */
        p_rtctime->week,                                            /* Input */
        &active_day_profile                                         /* Output */
    );

    if (find_result == TRUE)
    {
        R_ACT_CAL_ApplyActiveDayProfile(&active_day_profile);
    }

    R_ACT_CAL_FindChangedTimeslotThenCaptureTariffEnergy(p_rtctime);
}

/******************************************************************************
* Function Name : R_ACT_CAL_ApplyNewSeasonProfile
* Interface     : void R_ACT_CAL_ApplyNewSeasonProfile(uint8_t season_id)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_ACT_CAL_ApplyNewSeasonProfile(r_act_cal_season_profile_t *p_season_profile)
{
    uint8_t i;

    if (p_season_profile == NULL)
    {
        return;
    }

    g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_SEASON].number_of_exe_time = p_season_profile->num;
    for (i = 0; i < p_season_profile->num; i++)
    {
        g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_SEASON].p_execution_time[i].Year  = p_season_profile->entry[i].start_time.year;
        g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_SEASON].p_execution_time[i].Month = p_season_profile->entry[i].start_time.month;
        g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_SEASON].p_execution_time[i].Week  = p_season_profile->entry[i].start_time.week;
        g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_SEASON].p_execution_time[i].Day   = p_season_profile->entry[i].start_time.day;

        g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_SEASON].p_execution_time[i].Hour = p_season_profile->entry[i].start_time.month;
        g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_SEASON].p_execution_time[i].Min  = p_season_profile->entry[i].start_time.week;
        g_scheduler[SCHEDULER_ID_ACTIVITY_CAL_SEASON].p_execution_time[i].Sec  = p_season_profile->entry[i].start_time.day;
    }

}

/******************************************************************************
* Function Name : R_ACT_CAL_FindWeekProfileFromActiveSeason
* Interface     : void R_ACT_CAL_FindWeekProfileFromActiveSeason(
*                           r_act_cal_season_profile_t *p_season_profile,
*                           r_act_cal_week_profile_t *p_week_profile_out)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_ACT_CAL_FindWeekProfileFromActiveSeason(
    r_act_cal_season_t *p_season_profile, 
    r_act_cal_week_t *p_week_profile_out
)
{
    uint8_t i;
    r_act_cal_name_t active_week_name;

    r_act_cal_week_profile_t week_profile_active;

    uint8_t entry_id = 0xFF;

    memcpy(&active_week_name, &p_season_profile->week, sizeof(r_act_cal_name_t));
    
    // Load week profile
    memset(&week_profile_active, 0, sizeof(r_act_cal_week_profile_t));
    week_profile_active = R_ACT_CAL_Restore_WeekProfile( ACTIVE_PROFILE);
    
    for (i = 0; i < week_profile_active.num ; i++)
    {
        if (active_week_name.len == week_profile_active.entry[i].name.len)
        {
            if (memcmp(active_week_name.value, week_profile_active.entry[i].name.value, active_week_name.len) == 0)
            {
                entry_id = i;
                break;
            }
        }
    }

    CHECK_NOT_FOUND_RETURN(entry_id);
    if (entry_id > 2)
    {
        g_tod_process_state = ACTIVITY_CAL_ERROR_DATA;
        return;
    }
    
    *p_week_profile_out = week_profile_active.entry[entry_id];
}

/******************************************************************************
* Function Name : R_ACT_CAL_FindActiveDayProfileFromWeekProfile
* Interface     : void R_ACT_CAL_FindActiveDayProfileFromWeekProfile(
                        r_act_cal_week_t *p_week_profile, 
                        r_act_cal_day_t *p_day_profile)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
uint8_t R_ACT_CAL_FindActiveDayProfileFromWeekProfile(
    r_act_cal_week_t *p_week_profile,
    uint8_t day_of_week,
    r_act_cal_day_t *p_day_profile
)
{
    uint8_t i;
    r_act_cal_day_profile_t day_profile;
    
	uint8_t day_profile_id	= 0xFF;

    day_profile_id = p_week_profile->data[day_of_week];
		
    // Load day profile
    day_profile = R_ACT_CAL_Restore_DayProfile(ACTIVE_PROFILE);
    
    for (i = 0; i < day_profile.num; i++)
    {
        if (day_profile.entry[i].dayID == day_profile_id)
        {
            memcpy(p_day_profile, &day_profile.entry[i], sizeof(r_act_cal_day_t));
            return TRUE;
        }
    }

    return FALSE;
}

/******************************************************************************
* Function Name : R_ACT_CAL_ApplyActiveDayProfile
* Interface     : void R_ACT_CAL_ApplyActiveDayProfile()
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void R_ACT_CAL_ApplyActiveDayProfile(r_act_cal_day_t *p_profile)
{
	uint8_t i;

    g_scheduler[SCHEDULER_ID_TARIFF].number_of_exe_time = p_profile->numberOfAction;
    
    for (i = 0; i < p_profile->numberOfAction; i++)
    {
        memset(&g_scheduler[SCHEDULER_ID_TARIFF].p_execution_time[i], 0xFF, sizeof(r_scheduler_datetime_t));

        g_scheduler[SCHEDULER_ID_TARIFF].p_execution_time[i].Hour = p_profile->action[i].hour;
        g_scheduler[SCHEDULER_ID_TARIFF].p_execution_time[i].Min = p_profile->action[i].min;
        g_scheduler[SCHEDULER_ID_TARIFF].p_execution_time[i].Sec = 0x00;

        /* Set slot number to tariff */
        if (i <= SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX)
        {
            g_tariff_lookup_timeslot_tariff_number[i] = p_profile->action[i].scriptID;
            
            if (g_tariff_lookup_timeslot_tariff_number[i] > 0 )
            {
                g_tariff_lookup_timeslot_tariff_number[i]--;
            }
            else
            {
                /* No change if scriptID already 0 (consider abnormal, scriptID should start from 1 */
            }
        }
    }
}

/******************************************************************************
* Function Name : R_ACT_CAL_PollingProcessing
* Interface     : void R_ACT_CAL_PollingProcessing(
*               :     void
*               : );
* Description   :
* Return Value  :
******************************************************************************/
void R_ACT_CAL_PollingProcessing(void)
{
    r_act_cal_season_profile_t  season_profile;
    r_act_cal_season_t          active_season;
    r_act_cal_week_profile_t    week_profile;
    r_act_cal_week_t            active_week_profile;
    r_act_cal_day_t             active_day_profile;

    uint8_t find_result;

    /******************************************************************************* 
     * EVENT: Copy passive to active profile
     * WHEN:  Happend when RTC meet activation time
     * DO:    (1) Copy passive profile to active profile
     *        (2) Active new profile for the first time
    *******************************************************************************/
    if (g_event_request_flag.is_cal_active_req)
    {
        g_tod_process_state = ACTIVITY_CAL_ACTIVE_TO_PASSIVE_INITIATED;
        g_event_request_flag.is_cal_active_req = FALSE;
    }

    R_ACT_CAL_CopyPassiveToActive();

    /******************************************************************************* 
     * EVENT: New calendar profile is active
     * WHEN:  Happend when copy passive to active profile is finished
     * DO:    
    *******************************************************************************/
    if (is_new_cal_profile_active)
    {
        R_ACT_CAL_FindAndActiveNewSeason(&gp_inst_LastDataPop->capture_time);

        if (g_cal_first_activate_after_formating == TRUE)
        {
            /* After activating passive calendar to active calendar bill should generate */
            g_event_request_flag.is_billing_request = 1;
            g_cal_first_activate_after_formating = FALSE;
        }
    
        is_new_cal_profile_active = FALSE;
    }


    /******************************************************************************* 
     * EVENT: Season change
     * WHEN:  Happend when RTC meet season start time
     * DO:    (1) Get new season profile
     *        (2) Get week profile of active season
    *******************************************************************************/
    if (g_event_request_flag.act_cal_season_change)
    {
        season_profile = R_ACT_CAL_Restore_SeasonProfile(ACTIVE_PROFILE);
        active_season = season_profile.entry[g_scheduler_match_context->exe_time_id];

        R_ACT_CAL_FindWeekProfileFromActiveSeason(
            &active_season,                                             /* Input */
            &active_week_profile                                        /* Output */
        );

        g_event_request_flag.act_cal_season_change = FALSE;
    }

    /******************************************************************************* 
     * EVENT: Day of week Change
     * WHEN:  Happend at 00:00:00 every day 
     * DO:    (1) Find active day from file from active week profile
     *        (2) Set active day profile to scheduler for tariff
    *******************************************************************************/
    if (g_event_request_flag.act_cal_week_profile_change)
    {
        find_result = R_ACT_CAL_FindActiveDayProfileFromWeekProfile(
            &active_week_profile,                                       /* Input */
            gp_inst_LastDataPop->capture_time.week,                     /* Input */
            &active_day_profile                                         /* Output */
        );

        if (find_result == TRUE)
        {
            R_ACT_CAL_ApplyActiveDayProfile(&active_day_profile);
        }

        g_event_request_flag.act_cal_week_profile_change = FALSE;
    }
}
