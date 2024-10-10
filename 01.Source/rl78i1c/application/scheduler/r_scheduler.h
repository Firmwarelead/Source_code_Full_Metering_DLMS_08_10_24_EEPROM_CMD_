/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_scheduler.h
* Version      : v1.0
* Description  : 
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 2021.02.24 New creation
***********************************************************************************************************************/

#ifndef _R_SCHEDULER_H
#define _R_SCHEDULER_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "typedef.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define MAX_SCHEDULER_NUMBER						(7)
#define MAX_SLOT_PER_EXE_TIME						(8)

#define SCHEDULE_EXE_TIME_MAX_SUPPORT_0				(MAX_SLOT_PER_EXE_TIME)
#define SCHEDULE_EXE_TIME_MAX_SUPPORT_1				(MAX_SLOT_PER_EXE_TIME)
#define SCHEDULE_EXE_TIME_MAX_SUPPORT_2				(MAX_SLOT_PER_EXE_TIME)
#define SCHEDULE_EXE_TIME_MAX_SUPPORT_3				(1)
#define SCHEDULE_EXE_TIME_MAX_SUPPORT_4				(1)
#define SCHEDULE_EXE_TIME_MAX_SUPPORT_5				(1)
#define SCHEDULE_EXE_TIME_MAX_SUPPORT_6				(2)

#define START_SLOT_EXE_TIME_0						(0)
#define START_SLOT_EXE_TIME_1						(START_SLOT_EXE_TIME_0 + SCHEDULE_EXE_TIME_MAX_SUPPORT_0)
#define START_SLOT_EXE_TIME_2						(START_SLOT_EXE_TIME_1 + SCHEDULE_EXE_TIME_MAX_SUPPORT_1)
#define START_SLOT_EXE_TIME_3						(START_SLOT_EXE_TIME_2 + SCHEDULE_EXE_TIME_MAX_SUPPORT_2)
#define START_SLOT_EXE_TIME_4						(START_SLOT_EXE_TIME_3 + SCHEDULE_EXE_TIME_MAX_SUPPORT_3)
#define START_SLOT_EXE_TIME_5						(START_SLOT_EXE_TIME_4 + SCHEDULE_EXE_TIME_MAX_SUPPORT_4)
#define START_SLOT_EXE_TIME_6						(START_SLOT_EXE_TIME_5 + SCHEDULE_EXE_TIME_MAX_SUPPORT_5)

#define SCHEDULE_EXECUTION_TIME_MAX_SUPPORT    		(START_SLOT_EXE_TIME_6 + SCHEDULE_EXE_TIME_MAX_SUPPORT_6)


/* Define info for storage data */
#define SCHEDULER_STORAGE_SIZE                      (sizeof(scheduler_t) - sizeof(r_scheduler_datetime_t *))

/* Define ID for scheduler slots */
#define SCHEDULER_ID_TARIFF                               (0)       /* Tariff slot */
#define SCHEDULER_ID_PERIODIC_CH0                         (1)       /* Periodic channel 0 */
#define SCHEDULER_ID_PERIODIC_CH1                         (2)       /* Periodic channel 1 */
#define SCHEDULER_ID_BILLING                              (3)       /* Periodic channel 1 */
#define SCHEDULER_ID_FW_ACTIVATION                        (4)       /* Firmware activation */
#define SCHEDULER_ID_ACTIVITY_CAL_ACT                     (5)       /* Activity calendar activation */
#define SCHEDULER_ID_ACTIVITY_CAL_SEASON                  (6)       /* Activity calendar activation */

#define SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX           (8)

/* Max demand setting range */
#define SCHEDULER_MAX_DEMAND_PERIOD_MIN                      (5)
#define SCHEDULER_MAX_DEMAND_PERIOD_MAX                      (60)
#define SCHEDULER_MAX_DEMAND_NUMBER_OF_PERIOD_MIN            (1)
#define SCHEDULER_MAX_DEMAND_NUMBER_OF_PERIOD_MAX            (15)

/* Default configuration for max demand */
#define SCHEDULER_DEFAULT_MAX_DEMAND_PERIOD                  (30)
#define SCHEDULER_DEFAULT_MAX_DEMAND_NUM_OF_PERIOD           (1)
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/



typedef struct tag_r_scheduler_flags_t
{
    uint16_t mdm           : 1;
    uint16_t blockload     : 1;
    uint16_t dailyload     : 1;
    uint16_t lcd_refresh   : 1;
    uint16_t lcd_scroll    : 1;
    uint16_t relay         : 1;
    uint16_t fw_activation : 1;
    uint16_t billing       : 1;
} r_scheduler_flags_t;

typedef struct tag_r_scheduler_datetime_t
{
	uint8_t Sec;        /* Second */
	uint8_t Min;        /* Minute */
	uint8_t Hour;       /* Hour */
	uint8_t Day;        /* Day */
	uint8_t Week;       /* Day of week, 1..7, 1 is Monday */
	uint8_t Month;      /* Month */
	uint8_t Year;       /* Year (ony 2 ending digit) */
    uint8_t Reserved;
} r_scheduler_datetime_t;

typedef struct tag_scheduler_t
{
	uint8_t					matched;	        /* Flag to check if RTC date time hit preset 'datetime' field */
    uint8_t                 number_of_exe_time;
	uint16_t				script_id;	        /* Associated script ID to trigger action */
	r_scheduler_datetime_t  *p_execution_time;	/* Preset date & time to check with RTC date time, support wildcards */
} scheduler_t;

typedef struct tag_scheduler_storage_t
{
	uint8_t					matched;	        /* Flag to check if RTC date time hit preset 'datetime' field */
    uint8_t                 number_of_exe_time;
	uint16_t				script_id;	        /* Associated script ID to trigger action */
} scheduler_storage_t;

typedef struct tag_scheduler_match_context_t
{
    void *p_snapshot;
    uint8_t exe_time_id;
} scheduler_match_context_t;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
extern r_scheduler_flags_t 	g_scheduler_flags;
extern scheduler_t		g_scheduler[MAX_SCHEDULER_NUMBER];
extern scheduler_match_context_t g_scheduler_match_context[MAX_SCHEDULER_NUMBER];
extern uint16_t         g_demand_number_of_period;
extern uint16_t 		g_demand_integration_period;
extern uint16_t 		g_blockload_period;

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
void	R_SCHEDULER_Init(void);
void	R_SCHEDULER_PollingProcessing(void);
uint8_t	R_SCHEDULER_Backup(void);
uint8_t	R_SCHEDULER_BackupByID(uint8_t schedule_id);
uint8_t	R_SCHEDULER_Restore(void);
uint8_t	R_SCHEDULER_RestoreByID(uint8_t schedule_id);
uint8_t R_SCHEDULER_Format(void);


int16_t R_SCHEDULER_ExecutionTimeArrayLengthGet(uint8_t schedule_id);
uint8_t R_SCHEDULER_ExecutionTimeArrayLengthSet(uint8_t schedule_id, uint16_t length);
uint8_t R_SCHEDULER_ExecutionTimeGet(uint8_t * p_data_out, uint8_t schedule_id,  uint16_t array_index);
uint8_t R_SCHEDULER_ExecutionTimeSet(uint8_t * p_data_in, uint8_t schedule_id,  uint16_t array_index);
uint8_t R_SCHEDULER_ExecutionDateGet(uint8_t * p_data_out, uint8_t schedule_id,  uint16_t array_index);
uint8_t R_SCHEDULER_ExecutionDateSet(uint8_t * p_data_in, uint8_t schedule_id,  uint16_t array_index);

#endif /* _R_SCHEDULER_H */