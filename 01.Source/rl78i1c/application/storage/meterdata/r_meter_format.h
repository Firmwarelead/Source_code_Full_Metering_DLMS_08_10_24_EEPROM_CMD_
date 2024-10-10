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
* File Name    : r_meter_format.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Storage Format Header file

* Note         : NEED TO CHANGE THIS FILE WHEN
*              :   . EM CORE TYPE DEFINITION IS CHANGED, OR
*              :   . EEPROM START ADDRESS IS CHANGED
* Caution      : DATA ALIGNMENT
*              :    DATA ALIGNMENT ON THIS FORMAT IS 2-BYTES ALIGNMENT, EVEN ADDRESS.
*              :    PLEASE DON'T CHANGE TO OTHER ALIGNMENT SETTING.
*              :    WHEN CHANGE THE DATA ALIGNMENT SETTING, IT WILL DAMAGE THE FORMAT
*              :    ON EEPROM
*              :
*              : BIT FIELD FORMAT
*              :    BIT FIELD FORMAT IS FROM LSB FIRST
*              :    PLEASE DON'T CHANGE THIS SETTING ON THE COMPILE OPTION (IF SUPPORTED)

***********************************************************************************************************************/

#ifndef _STORAGE_FORMAT_H
#define _STORAGE_FORMAT_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "typedef.h"        /* GSCE Standard Typedef */

/* Middleware */
#include "em_type.h"        /* EM Core Type Definitions */
#include "em_constraint.h"

/* Application */
#include "eeprom.h"         /* EEPROM MW */
#include "r_tariff.h"
#include "r_max_demand.h"
#include "event.h"
#include "r_scheduler.h"
#include "inst_read.h"
#include "r_activity_cal.h"

/******************************************************************************
Macro definitions for Typedef
******************************************************************************/
#define SUPPORT_UNIT_CODE_LEN               (20)
#define SUPPORT_FW_VER_LEN                  (11)
#define SUPPORT_METER_TYPE_LEN              (4)

/* User define */
#define SUPPORT_DEVICEID_LEN (11)
#define BLOCKLOAD_PARTITION (50000)
#define DAILY_PARTITION (1000)
#define BILLING_PARTITION (2000)


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/*====================================================================================================================*/
/* EEPROM Information */
#define STORAGE_EEPROM_START_ADDR 						EPR_DEVICE_START_ADDR   /* EEPROM Start address */ //0x0000
#define STORAGE_EEPROM_SIZE 							EPR_DEVICE_SIZE              /* EEPROM Size */  //0x10000
#define STORAGE_EEPROM_PAGESIZE 						EPR_DEVICE_PAGESIZE      /* EEPROM Page Size */ // 0x80 ie 128 byte


/*====================================================================================================================*/

#define STORAGE_EEPROM_SUB_MODULE_EM_CORE       (1)
#define STORAGE_EEPROM_SUB_MODULE_GLOBAL        (1)
#define STORAGE_EEPROM_SUB_MODULE_COMMON        (1)
#define STORAGE_EEPROM_SUB_MODULE_ENERGY        (1)
#define STORAGE_EEPROM_SUB_MODULE_ENERGY_MDM    (1)
#define STORAGE_EEPROM_SUB_MODULE_ENERGY_TARIFF (1)
#define STORAGE_EEPROM_SUB_MODULE_SCHEDULER     (1)
#define STORAGE_EEPROM_SUB_MODULE_EVENT_LOG     (1)
#define STORAGE_EEPROM_SUB_MODULE_BLOCKLOAD     (1)
#define STORAGE_EEPROM_SUB_MODULE_DAILYLOAD     (1)
#define STORAGE_EEPROM_SUB_MODULE_BILLING       (1)	
#define STORAGE_EEPROM_SUB_MODULE_CAL           (1)

#if(defined( R_LOAD_CONTROL_ENABLE ) && R_LOAD_CONTROL_ENABLE == TRUE)
    #define STORAGE_EEPROM_SUB_MODULE_LOAD_CTRL     (1)	
#else
    #define STORAGE_EEPROM_SUB_MODULE_LOAD_CTRL     (0)	
#endif

/*****************************************
* Sub module: EM_CORE
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_EM_CORE == 1)

    /* Partition */
    #define STORAGE_EEPROM_EM_CORE_PARTITION_ADDR (STORAGE_EEPROM_START_ADDR + 0)    // 0x0000
    #define STORAGE_EEPROM_EM_CORE_PARTITION_SIZE (sizeof(uint8_t) * 256  )      // 1*256=256


	/* Sub module EM_CORE last address */
    #define STORAGE_EEPROM_EM_CORE_LAST_ADDR (STORAGE_EEPROM_EM_CORE_PARTITION_ADDR + STORAGE_EEPROM_EM_CORE_PARTITION_SIZE) // 0x0000 + 100= 0x0100


#endif /* EM_CORE */


/*****************************************
* Sub module: Global
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_GLOBAL == 1)

    /* Header Code */
    #define STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR (STORAGE_EEPROM_START_ADDR + 256)   // 0x0000 + 0x100--- 0x100
    #define STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE (sizeof(uint32_t) )       //4

    /*  Sub module Global padding */
    #define STORAGE_EEPROM_GLOBAL_PADDING_ADDR (STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR + STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE)  //0x104
    #define STORAGE_EEPROM_GLOBAL_PADDING_SIZE (10)//10

	/* Sub module Global last address */
    #define STORAGE_EEPROM_GLOBAL_LAST_ADDR (STORAGE_EEPROM_GLOBAL_PADDING_ADDR + STORAGE_EEPROM_GLOBAL_PADDING_SIZE)  // 0x104 + 0xA = 0x10E

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_GLOBAL_LAST_ADDR)   // 0x10E
    
#endif /* Global */


/*****************************************
* Sub module: Common
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_COMMON == 1)

    /* Rtc */
    #define STORAGE_EEPROM_COMMON_RTC_ADDR (STORAGE_EEPROM_GLOBAL_LAST_ADDR) // 0x10E
    #define STORAGE_EEPROM_COMMON_RTC_SIZE (sizeof(rtc_counter_value_t))//8 byte 
    /* Snapshot_value */
    #define STORAGE_EEPROM_COMMON_SNAPSHOT_VALUE_ADDR (STORAGE_EEPROM_COMMON_RTC_ADDR + STORAGE_EEPROM_COMMON_RTC_SIZE)//0x116
    #define STORAGE_EEPROM_COMMON_SNAPSHOT_VALUE_SIZE (sizeof(EM_INST_READ_PARAMS) * 2 )//117*2 bytes(0xEA)

	/* Sub module Common last address */
    #define STORAGE_EEPROM_COMMON_LAST_ADDR (STORAGE_EEPROM_COMMON_SNAPSHOT_VALUE_ADDR + STORAGE_EEPROM_COMMON_SNAPSHOT_VALUE_SIZE)//0x200

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_COMMON_LAST_ADDR)//0x200
#endif /* Common */

/*****************************************
* Sub module: Energy_MDM
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_ENERGY_MDM == 1)

    /* State */
    #define STORAGE_EEPROM_ENERGY_MDM_STATE_ADDR (STORAGE_EEPROM_START_ADDR + 512)//0x00+200=0x200
    #define STORAGE_EEPROM_ENERGY_MDM_STATE_SIZE (sizeof(r_mdm_t))//16+8+16+8+2=50 bytes

    /* Moving Average buffer */
    #define STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_ADDR (STORAGE_EEPROM_ENERGY_MDM_STATE_ADDR + STORAGE_EEPROM_ENERGY_MDM_STATE_SIZE)//0x232
    #define STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_SIZE (sizeof(r_mdm_counter_t) * 15 )//16*15=240 bytes(0xF0)
    /* Max value capture time */
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_CAPTURE_TIME_ADDR (STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_ADDR + STORAGE_EEPROM_ENERGY_MDM_MOVING_AVERAGE_BUFFER_SIZE)//0x322
    #define STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_CAPTURE_TIME_SIZE (sizeof(rtc_counter_value_t))//8 bytes
    /* Current max value */
    #define STORAGE_EEPROM_ENERGY_MDM_CURRENT_MAX_VALUE_ADDR (STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_CAPTURE_TIME_ADDR + STORAGE_EEPROM_ENERGY_MDM_MAX_VALUE_CAPTURE_TIME_SIZE)//0x32A
    #define STORAGE_EEPROM_ENERGY_MDM_CURRENT_MAX_VALUE_SIZE (sizeof(r_mdm_counter_t))//4+4+4+4=16 bytes
    /*  Sub module Energy_MDM padding */
    #define STORAGE_EEPROM_ENERGY_MDM_PADDING_ADDR (STORAGE_EEPROM_ENERGY_MDM_CURRENT_MAX_VALUE_ADDR + STORAGE_EEPROM_ENERGY_MDM_CURRENT_MAX_VALUE_SIZE)//0x33A
    #define STORAGE_EEPROM_ENERGY_MDM_PADDING_SIZE (10)

	/* Sub module Energy_MDM last address */
    #define STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR (STORAGE_EEPROM_ENERGY_MDM_PADDING_ADDR + STORAGE_EEPROM_ENERGY_MDM_PADDING_SIZE)//0x344

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR)//0x344

#endif /* Energy_MDM */


/*****************************************
* Sub module: Energy_Tariff
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_ENERGY_TARIFF == 1)

    /* State */
    #define STORAGE_EEPROM_ENERGY_TARIFF_STATE_ADDR (STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR)//0x344
    #define STORAGE_EEPROM_ENERGY_TARIFF_STATE_SIZE (sizeof(r_tariff_t))//4+1+32+32+32=101 bytes
    /* Tz */
    #define STORAGE_EEPROM_ENERGY_TARIFF_TZ_ADDR (STORAGE_EEPROM_ENERGY_TARIFF_STATE_ADDR + STORAGE_EEPROM_ENERGY_TARIFF_STATE_SIZE)//0x3A9
    #define STORAGE_EEPROM_ENERGY_TARIFF_TZ_SIZE (sizeof(r_tariff_counter_t) * 16 )//4+4+4+4+4+4+4+4=32 bytes,32*16=512
    /* Lookup Timeslot-tariff_number */
    #define STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_ADDR (STORAGE_EEPROM_ENERGY_TARIFF_TZ_ADDR + STORAGE_EEPROM_ENERGY_TARIFF_TZ_SIZE)//0x5A9
    #define STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_SIZE (sizeof(uint8_t) * 16 )//16
    /*  Sub module Energy_Tariff padding */
    #define STORAGE_EEPROM_ENERGY_TARIFF_PADDING_ADDR (STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_ADDR + STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_SIZE)//0x5B9
    #define STORAGE_EEPROM_ENERGY_TARIFF_PADDING_SIZE (10)

	/* Sub module Energy_Tariff last address */
    #define STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR (STORAGE_EEPROM_ENERGY_TARIFF_PADDING_ADDR + STORAGE_EEPROM_ENERGY_TARIFF_PADDING_SIZE)//0x5C3

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR)

#endif /* Energy_Tariff */


/*****************************************
* Sub module: Scheduler
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_SCHEDULER == 1)

    /* Data */
    #define STORAGE_EEPROM_SCHEDULER_DATA_ADDR (STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR)//0x5C3
    #define STORAGE_EEPROM_SCHEDULER_DATA_SIZE (sizeof(scheduler_storage_t) * MAX_SCHEDULER_NUMBER)//4*7=28 bytes
    /* SAS date time */
    #define STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR (STORAGE_EEPROM_SCHEDULER_DATA_ADDR + STORAGE_EEPROM_SCHEDULER_DATA_SIZE)//0x5DF
    #define STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_SIZE (sizeof(r_scheduler_datetime_t) * SCHEDULE_EXECUTION_TIME_MAX_SUPPORT)//8*29=232 bytes
    /* SAS execution flag */
    #define STORAGE_EEPROM_SCHEDULER_SAS_EXECUTION_FLAG_ADDR (STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_ADDR + STORAGE_EEPROM_SCHEDULER_SAS_DATE_TIME_SIZE)//0x6C7
    #define STORAGE_EEPROM_SCHEDULER_SAS_EXECUTION_FLAG_SIZE (sizeof(uint16_t) * MAX_SCHEDULER_NUMBER)//2*7=14 bytes
    /* Demand Integration Period */
    #define STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_ADDR (STORAGE_EEPROM_SCHEDULER_SAS_EXECUTION_FLAG_ADDR + STORAGE_EEPROM_SCHEDULER_SAS_EXECUTION_FLAG_SIZE)//0x6D5
    #define STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_SIZE (sizeof(uint16_t))//2 bytes
    /* Demand Number of Period */
    #define STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_ADDR (STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_ADDR + STORAGE_EEPROM_SCHEDULER_DEMAND_INTEGRATION_PERIOD_SIZE)//0x6D7
    #define STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_SIZE (sizeof(uint16_t))//2
    /*  Sub module Scheduler padding */
    #define STORAGE_EEPROM_SCHEDULER_PADDING_ADDR (STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_ADDR + STORAGE_EEPROM_SCHEDULER_DEMAND_NUMBER_OF_PERIOD_SIZE)//0x6D9
    #define STORAGE_EEPROM_SCHEDULER_PADDING_SIZE (10)

	/* Sub module Scheduler last address */
    #define STORAGE_EEPROM_SCHEDULER_LAST_ADDR (STORAGE_EEPROM_SCHEDULER_PADDING_ADDR + STORAGE_EEPROM_SCHEDULER_PADDING_SIZE)//0x6E3

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_SCHEDULER_LAST_ADDR)//0x6E3

#endif /* Scheduler */


/*****************************************
* Sub module: Event_Log
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_EVENT_LOG == 1)

    /* Header code */
    #define STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_ADDR (STORAGE_EEPROM_START_ADDR + 1820)//0x00+0x71C=0x71C
    #define STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_SIZE (sizeof(uint32_t) )//2

    /* Event State */
    #define STORAGE_EEPROM_EVENT_LOG_EVENT_STATE_ADDR (STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_ADDR + STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_SIZE)//0x71E
    #define STORAGE_EEPROM_EVENT_LOG_EVENT_STATE_SIZE (sizeof(EVENT_INFO))//43 bytes
    /* Tamper Counter */
    #define STORAGE_EEPROM_EVENT_LOG_TAMPER_COUNTER_ADDR (STORAGE_EEPROM_EVENT_LOG_EVENT_STATE_ADDR + STORAGE_EEPROM_EVENT_LOG_EVENT_STATE_SIZE)//0x749
    #define STORAGE_EEPROM_EVENT_LOG_TAMPER_COUNTER_SIZE (sizeof(uint32_t))//4
    /* Table info */
    #define STORAGE_EEPROM_EVENT_LOG_TABLE_INFO_ADDR (STORAGE_EEPROM_EVENT_LOG_TAMPER_COUNTER_ADDR + STORAGE_EEPROM_EVENT_LOG_TAMPER_COUNTER_SIZE)//0x74D
    #define STORAGE_EEPROM_EVENT_LOG_TABLE_INFO_SIZE (sizeof(EventTableHeader_t) * 7 )//4*7=28 bytes
    /* Voltage */
    #define STORAGE_EEPROM_EVENT_LOG_VOLTAGE_ADDR (STORAGE_EEPROM_EVENT_LOG_TABLE_INFO_ADDR + STORAGE_EEPROM_EVENT_LOG_TABLE_INFO_SIZE)//0x769
    #define STORAGE_EEPROM_EVENT_LOG_VOLTAGE_SIZE (sizeof(EVENT_PARAMS_T) * VOLTAGE_EVENTS_MAX_ENTRIES)//30*50=1500 bytes
    /* Current */
    #define STORAGE_EEPROM_EVENT_LOG_CURRENT_ADDR (STORAGE_EEPROM_EVENT_LOG_VOLTAGE_ADDR + STORAGE_EEPROM_EVENT_LOG_VOLTAGE_SIZE)//0xD45
    #define STORAGE_EEPROM_EVENT_LOG_CURRENT_SIZE (sizeof(EVENT_PARAMS_T) * CURRENT_EVENTS_MAX_ENTRIES)//30*50=1500 bytes
    /* Power */
    #define STORAGE_EEPROM_EVENT_LOG_POWER_ADDR (STORAGE_EEPROM_EVENT_LOG_CURRENT_ADDR + STORAGE_EEPROM_EVENT_LOG_CURRENT_SIZE)//0x1321
    #define STORAGE_EEPROM_EVENT_LOG_POWER_SIZE (sizeof(EVENT_PARAMS_SHORT_T) * POWER_EVENTS_MAX_ENTRIES)//10*20=200 bytes
    /* Transaction */
    #define STORAGE_EEPROM_EVENT_LOG_TRANSACTION_ADDR (STORAGE_EEPROM_EVENT_LOG_POWER_ADDR + STORAGE_EEPROM_EVENT_LOG_POWER_SIZE)//0x13E9
    #define STORAGE_EEPROM_EVENT_LOG_TRANSACTION_SIZE (sizeof(EVENT_PARAMS_SHORT_T) * TRANS_EVENTS_MAX_ENTRIES)//10*50=500 bytes
    /* Other */
    #define STORAGE_EEPROM_EVENT_LOG_OTHER_ADDR (STORAGE_EEPROM_EVENT_LOG_TRANSACTION_ADDR + STORAGE_EEPROM_EVENT_LOG_TRANSACTION_SIZE)//0x15DD
    #define STORAGE_EEPROM_EVENT_LOG_OTHER_SIZE (sizeof(EVENT_PARAMS_T) * OTHER_EVENTS_MAX_ENTRIES)//30*50=1500 bytes
    /* Nonrollover */
    #define STORAGE_EEPROM_EVENT_LOG_NONROLLOVER_ADDR (STORAGE_EEPROM_EVENT_LOG_OTHER_ADDR + STORAGE_EEPROM_EVENT_LOG_OTHER_SIZE)//0x1BB9
    #define STORAGE_EEPROM_EVENT_LOG_NONROLLOVER_SIZE (sizeof(EVENT_PARAMS_SHORT_T) * NON_ROLLOVER_EVENTS_MAX_ENTRIES)//10*1=10 bytes
    /* Control */
    #define STORAGE_EEPROM_EVENT_LOG_CONTROL_ADDR (STORAGE_EEPROM_EVENT_LOG_NONROLLOVER_ADDR + STORAGE_EEPROM_EVENT_LOG_NONROLLOVER_SIZE)//0x1BC3
    #define STORAGE_EEPROM_EVENT_LOG_CONTROL_SIZE (sizeof(EVENT_PARAMS_SHORT_T) * CONTROL_EVENTS_MAX_ENTRIES)//10*50=500 bytes
    /*  Sub module Event_Log padding */
    #define STORAGE_EEPROM_EVENT_LOG_PADDING_ADDR (STORAGE_EEPROM_EVENT_LOG_CONTROL_ADDR + STORAGE_EEPROM_EVENT_LOG_CONTROL_SIZE)//0x1BF5
    #define STORAGE_EEPROM_EVENT_LOG_PADDING_SIZE (10)

	/* Sub module Event_Log last address */
    #define STORAGE_EEPROM_EVENT_LOG_LAST_ADDR (STORAGE_EEPROM_EVENT_LOG_PADDING_ADDR + STORAGE_EEPROM_EVENT_LOG_PADDING_SIZE)//0x1BF5

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_EVENT_LOG_LAST_ADDR)

#endif /* Event_Log */


/*****************************************
* Sub module: Blockload
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_BLOCKLOAD == 1)

    /* Partition */
    #define STORAGE_EEPROM_BLOCKLOAD_PARTITION_ADDR (STORAGE_EEPROM_START_ADDR + 8000)//0x00+0x1F40=0x1F40
    #define STORAGE_EEPROM_BLOCKLOAD_PARTITION_SIZE (sizeof(uint8_t) * BLOCKLOAD_PARTITION  )//50000 bytes


	/* Sub module Blockload last address */
    #define STORAGE_EEPROM_BLOCKLOAD_LAST_ADDR (STORAGE_EEPROM_BLOCKLOAD_PARTITION_ADDR + STORAGE_EEPROM_BLOCKLOAD_PARTITION_SIZE)//0xE290

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_BLOCKLOAD_LAST_ADDR)//0xE290

#endif /* Blockload */


/*****************************************
* Sub module: Dailyload
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_DAILYLOAD == 1)

    /* Partition */
    #define STORAGE_EEPROM_DAILYLOAD_PARTITION_ADDR (STORAGE_EEPROM_BLOCKLOAD_LAST_ADDR)//0xE290
    #define STORAGE_EEPROM_DAILYLOAD_PARTITION_SIZE (sizeof(uint8_t) * DAILY_PARTITION)//1000 bytes
    /*  Sub module Dailyload padding */
    #define STORAGE_EEPROM_DAILYLOAD_PADDING_ADDR (STORAGE_EEPROM_DAILYLOAD_PARTITION_ADDR + STORAGE_EEPROM_DAILYLOAD_PARTITION_SIZE)//0xE678
    #define STORAGE_EEPROM_DAILYLOAD_PADDING_SIZE (10)

	/* Sub module Dailyload last address */
    #define STORAGE_EEPROM_DAILYLOAD_LAST_ADDR (STORAGE_EEPROM_DAILYLOAD_PADDING_ADDR + STORAGE_EEPROM_DAILYLOAD_PADDING_SIZE)//0xE682

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_DAILYLOAD_LAST_ADDR)//0xE682

#endif /* Dailyload */


/*****************************************
* Sub module: Billing
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_BILLING == 1)

    /* Partition */
    #define STORAGE_EEPROM_BILLING_PARTITION_ADDR (STORAGE_EEPROM_DAILYLOAD_LAST_ADDR)//0xE682
    #define STORAGE_EEPROM_BILLING_PARTITION_SIZE (sizeof(uint8_t) * BILLING_PARTITION)//2000 bytes
    /*  Sub module Billing padding */
    #define STORAGE_EEPROM_BILLING_PADDING_ADDR (STORAGE_EEPROM_BILLING_PARTITION_ADDR + STORAGE_EEPROM_BILLING_PARTITION_SIZE)//0xEE52
    #define STORAGE_EEPROM_BILLING_PADDING_SIZE (10)

	/* Sub module Billing last address */
    #define STORAGE_EEPROM_BILLING_LAST_ADDR (STORAGE_EEPROM_BILLING_PADDING_ADDR + STORAGE_EEPROM_BILLING_PADDING_SIZE)//0xEE5C

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_BILLING_LAST_ADDR)//0xEE5C

#endif /* Billing */


/*****************************************
* Sub module: Cal
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_CAL == 1)

    /* Name_active */
    #define STORAGE_EEPROM_CAL_NAME_ACTIVE_ADDR (STORAGE_EEPROM_BILLING_LAST_ADDR)//0xEE5C
    #define STORAGE_EEPROM_CAL_NAME_ACTIVE_SIZE (sizeof(r_act_cal_name_t))//2 byte
    /* Season_active */
    #define STORAGE_EEPROM_CAL_SEASON_ACTIVE_ADDR (STORAGE_EEPROM_CAL_NAME_ACTIVE_ADDR + STORAGE_EEPROM_CAL_NAME_ACTIVE_SIZE)//0xEE5E
    #define STORAGE_EEPROM_CAL_SEASON_ACTIVE_SIZE (sizeof(r_act_cal_season_profile_t))//85 bytes
    /* Week_active */
    #define STORAGE_EEPROM_CAL_WEEK_ACTIVE_ADDR (STORAGE_EEPROM_CAL_SEASON_ACTIVE_ADDR + STORAGE_EEPROM_CAL_SEASON_ACTIVE_SIZE)//0xEEB3
    #define STORAGE_EEPROM_CAL_WEEK_ACTIVE_SIZE (sizeof(r_act_cal_week_profile_t))//49 bytes
    /* Day_active */
    #define STORAGE_EEPROM_CAL_DAY_ACTIVE_ADDR (STORAGE_EEPROM_CAL_WEEK_ACTIVE_ADDR + STORAGE_EEPROM_CAL_WEEK_ACTIVE_SIZE)//0xEEE4
    #define STORAGE_EEPROM_CAL_DAY_ACTIVE_SIZE (sizeof(r_act_cal_day_profile_t))//137 bytes
    /* Name_passive */
    #define STORAGE_EEPROM_CAL_NAME_PASSIVE_ADDR (STORAGE_EEPROM_CAL_DAY_ACTIVE_ADDR + STORAGE_EEPROM_CAL_DAY_ACTIVE_SIZE)//0xEF6D
    #define STORAGE_EEPROM_CAL_NAME_PASSIVE_SIZE (sizeof(r_act_cal_name_t))//17 bytes
    /* season_passive */
    #define STORAGE_EEPROM_CAL_SEASON_PASSIVE_ADDR (STORAGE_EEPROM_CAL_NAME_PASSIVE_ADDR + STORAGE_EEPROM_CAL_NAME_PASSIVE_SIZE)//0xEF7E
    #define STORAGE_EEPROM_CAL_SEASON_PASSIVE_SIZE (sizeof(r_act_cal_season_profile_t))//85 bytes
    /* week_passive */
    #define STORAGE_EEPROM_CAL_WEEK_PASSIVE_ADDR (STORAGE_EEPROM_CAL_SEASON_PASSIVE_ADDR + STORAGE_EEPROM_CAL_SEASON_PASSIVE_SIZE)//0xEFD3
    #define STORAGE_EEPROM_CAL_WEEK_PASSIVE_SIZE (sizeof(r_act_cal_week_profile_t))//49 bytes
    /* day_passive */
    #define STORAGE_EEPROM_CAL_DAY_PASSIVE_ADDR (STORAGE_EEPROM_CAL_WEEK_PASSIVE_ADDR + STORAGE_EEPROM_CAL_WEEK_PASSIVE_SIZE)//0xF004
    #define STORAGE_EEPROM_CAL_DAY_PASSIVE_SIZE (sizeof(r_act_cal_day_profile_t))//137 bytes
    /* activation_time */
    #define STORAGE_EEPROM_CAL_ACTIVATION_TIME_ADDR (STORAGE_EEPROM_CAL_DAY_PASSIVE_ADDR + STORAGE_EEPROM_CAL_DAY_PASSIVE_SIZE)//0xF08D
    #define STORAGE_EEPROM_CAL_ACTIVATION_TIME_SIZE (sizeof(rtc_counter_value_t))//8 bytes
    /* exe_state */
    #define STORAGE_EEPROM_CAL_EXE_STATE_ADDR (STORAGE_EEPROM_CAL_ACTIVATION_TIME_ADDR + STORAGE_EEPROM_CAL_ACTIVATION_TIME_SIZE)//0xF095
    #define STORAGE_EEPROM_CAL_EXE_STATE_SIZE (sizeof(uint8_t))// 1 byte
    /* processing_state */
    #define STORAGE_EEPROM_CAL_PROCESSING_STATE_ADDR (STORAGE_EEPROM_CAL_EXE_STATE_ADDR + STORAGE_EEPROM_CAL_EXE_STATE_SIZE)//0xF096
    #define STORAGE_EEPROM_CAL_PROCESSING_STATE_SIZE (sizeof(uint8_t))//1 byte
    /* active_state */
    #define STORAGE_EEPROM_CAL_ACTIVE_STATE_ADDR (STORAGE_EEPROM_CAL_PROCESSING_STATE_ADDR + STORAGE_EEPROM_CAL_PROCESSING_STATE_SIZE)//0xF097
    #define STORAGE_EEPROM_CAL_ACTIVE_STATE_SIZE (sizeof(uint8_t))//1 byte
    /* season_state */
    #define STORAGE_EEPROM_CAL_SEASON_STATE_ADDR (STORAGE_EEPROM_CAL_ACTIVE_STATE_ADDR + STORAGE_EEPROM_CAL_ACTIVE_STATE_SIZE)//0xF098
    #define STORAGE_EEPROM_CAL_SEASON_STATE_SIZE (sizeof(uint8_t))//1 byte
    /* activation_time_long */
    #define STORAGE_EEPROM_CAL_ACTIVATION_TIME_LONG_ADDR (STORAGE_EEPROM_CAL_SEASON_STATE_ADDR + STORAGE_EEPROM_CAL_SEASON_STATE_SIZE)//0xF099
    #define STORAGE_EEPROM_CAL_ACTIVATION_TIME_LONG_SIZE (sizeof(uint8_t) * 12 )//12 bytes

	/* Sub module Cal last address */
    #define STORAGE_EEPROM_CAL_LAST_ADDR (STORAGE_EEPROM_CAL_ACTIVATION_TIME_LONG_ADDR + STORAGE_EEPROM_CAL_ACTIVATION_TIME_LONG_SIZE)//0xF0A5

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_CAL_LAST_ADDR)//0xF0A5

#endif /* Cal */


/*****************************************
* Sub module: Load ctrl
******************************************/
#if (STORAGE_EEPROM_SUB_MODULE_LOAD_CTRL == 1)

    /* state */
    #define STORAGE_EEPROM_LOAD_CTRL_STATE_ADDR (STORAGE_EEPROM_CAL_LAST_ADDR)//0xF0A5
    #define STORAGE_EEPROM_LOAD_CTRL_STATE_SIZE (sizeof(uint8_t))//1 byte
    /* mode */
    #define STORAGE_EEPROM_LOAD_CTRL_MODE_ADDR (STORAGE_EEPROM_LOAD_CTRL_STATE_ADDR + STORAGE_EEPROM_LOAD_CTRL_STATE_SIZE)//0xF0A6
    #define STORAGE_EEPROM_LOAD_CTRL_MODE_SIZE (sizeof(uint8_t))//1 byte
    /* threshold normal */
    #define STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_ADDR (STORAGE_EEPROM_LOAD_CTRL_MODE_ADDR + STORAGE_EEPROM_LOAD_CTRL_MODE_SIZE)//0xF0A7
    #define STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_SIZE (sizeof(uint32_t))// 4 bytes
    
    
    #define STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_ADDR    (STORAGE_EEPROM_LOAD_CTRL_MODE_ADDR + STORAGE_EEPROM_LOAD_CTRL_MODE_SIZE)//0xF0AB                                                                 //(STORAGE_EEPROM_LOAD_CTRL_MODE_ADDR + STORAGE_EEPROM_LOAD_CTRL_MODE_SIZE)
    #define STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_SIZE (sizeof(uint32_t))// 4 bytes
    
    
    
    
    /* threshold emergency */
    #define STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_EMERGENCY_ADDR (STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_ADDR + STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_NORMAL_SIZE)//0xF0AF
    #define STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_EMERGENCY_SIZE (sizeof(uint32_t))//4 bytes
    /* min over duration */
    #define STORAGE_EEPROM_LOAD_CTRL_MIN_OVER_DURATION_ADDR (STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_EMERGENCY_ADDR + STORAGE_EEPROM_LOAD_CTRL_THRESHOLD_EMERGENCY_SIZE)//0xF0B3
    #define STORAGE_EEPROM_LOAD_CTRL_MIN_OVER_DURATION_SIZE (sizeof(uint32_t))//4 bytes
    /* min under duration */
    #define STORAGE_EEPROM_LOAD_CTRL_MIN_UNDER_DURATION_ADDR (STORAGE_EEPROM_LOAD_CTRL_MIN_OVER_DURATION_ADDR + STORAGE_EEPROM_LOAD_CTRL_MIN_OVER_DURATION_SIZE)//0xF0B7
    #define STORAGE_EEPROM_LOAD_CTRL_MIN_UNDER_DURATION_SIZE (sizeof(uint32_t))//4 bytes
    /* Relay status */
    #define STORAGE_EEPROM_LOAD_CTRL_RELAY_STATUS_ADDR (STORAGE_EEPROM_LOAD_CTRL_MIN_UNDER_DURATION_ADDR + STORAGE_EEPROM_LOAD_CTRL_MIN_UNDER_DURATION_SIZE)//0xF0BB
    #define STORAGE_EEPROM_LOAD_CTRL_RELAY_STATUS_SIZE (sizeof(uint8_t))//1 byte
    /* Relay Progress Status */
    #define STORAGE_EEPROM_LOAD_CTRL_RELAY_PROGRESS_STATUS_ADDR (STORAGE_EEPROM_LOAD_CTRL_RELAY_STATUS_ADDR + STORAGE_EEPROM_LOAD_CTRL_RELAY_STATUS_SIZE)//0xF0BC
    #define STORAGE_EEPROM_LOAD_CTRL_RELAY_PROGRESS_STATUS_SIZE (sizeof(RelayProgessStatus_t))//22 bytes

	/* Sub module Load ctrl last address */
    #define STORAGE_EEPROM_LOAD_CTRL_LAST_ADDR (STORAGE_EEPROM_LOAD_CTRL_RELAY_PROGRESS_STATUS_ADDR + STORAGE_EEPROM_LOAD_CTRL_RELAY_PROGRESS_STATUS_SIZE)//0xF0D2

    #undef STORAGE_EEPROM_METER_FORMAT_LAST_ADDR
    #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_LOAD_CTRL_LAST_ADDR)

#endif /* Load ctrl */


/*====================================================================================================================*/

// #define STORAGE_EEPROM_METER_FORMAT_LAST_ADDR	(STORAGE_EEPROM_LOAD_CTRL_LAST_ADDR)

STATIC_ASSERT(STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR    > 0x00FF                                 );
STATIC_ASSERT(STORAGE_EEPROM_COMMON_RTC_ADDR            >= STORAGE_EEPROM_GLOBAL_LAST_ADDR       );
STATIC_ASSERT(STORAGE_EEPROM_ENERGY_MDM_STATE_ADDR      >= STORAGE_EEPROM_COMMON_RTC_ADDR        );
STATIC_ASSERT(STORAGE_EEPROM_ENERGY_TARIFF_STATE_ADDR   >= STORAGE_EEPROM_ENERGY_MDM_LAST_ADDR   );
STATIC_ASSERT(STORAGE_EEPROM_SCHEDULER_DATA_ADDR        >= STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR);
STATIC_ASSERT(STORAGE_EEPROM_EVENT_LOG_HEADER_CODE_ADDR >= STORAGE_EEPROM_SCHEDULER_LAST_ADDR    );
STATIC_ASSERT(STORAGE_EEPROM_BLOCKLOAD_PARTITION_ADDR   >= STORAGE_EEPROM_EVENT_LOG_LAST_ADDR    );
STATIC_ASSERT(STORAGE_EEPROM_DAILYLOAD_PARTITION_ADDR   >= STORAGE_EEPROM_BLOCKLOAD_LAST_ADDR    );
STATIC_ASSERT(STORAGE_EEPROM_BILLING_PARTITION_ADDR     >= STORAGE_EEPROM_DAILYLOAD_LAST_ADDR    );
STATIC_ASSERT(STORAGE_EEPROM_CAL_NAME_ACTIVE_ADDR       >= STORAGE_EEPROM_BILLING_LAST_ADDR      );

#if (STORAGE_EEPROM_SUB_MODULE_LOAD_CTRL == 1)
STATIC_ASSERT(STORAGE_EEPROM_LOAD_CTRL_STATE_ADDR       >= STORAGE_EEPROM_CAL_LAST_ADDR          );
#endif

/*************************************************************************************************************************
 * DATAFLASH
 *************************************************************************************************************************/
#define STORAGE_CONFIG_NAMEPLATE_START_ADDR   (0x0000)
#define STORAGE_CONFIG_SUB_MODULE_NAMEPLATE (1)	

/*****************************************
* Sub module: Nameplate
******************************************/
#if (STORAGE_CONFIG_SUB_MODULE_NAMEPLATE == 1)

    /* FlagID */
    #define STORAGE_CONFIG_NAMEPLATE_FLAGID_ADDR (STORAGE_CONFIG_NAMEPLATE_START_ADDR + 512)//0x200
    #define STORAGE_CONFIG_NAMEPLATE_FLAGID_SIZE (sizeof(uint8_t) * 3  )//3 bytes

    /* MSN_Len */
    #define STORAGE_CONFIG_NAMEPLATE_MSN_LEN_ADDR (STORAGE_CONFIG_NAMEPLATE_FLAGID_ADDR + STORAGE_CONFIG_NAMEPLATE_FLAGID_SIZE)//0x203
    #define STORAGE_CONFIG_NAMEPLATE_MSN_LEN_SIZE (sizeof(uint8_t))//1byte
    /* MSN */
    #define STORAGE_CONFIG_NAMEPLATE_MSN_ADDR (STORAGE_CONFIG_NAMEPLATE_MSN_LEN_ADDR + STORAGE_CONFIG_NAMEPLATE_MSN_LEN_SIZE)//0x204
    #define STORAGE_CONFIG_NAMEPLATE_MSN_SIZE (sizeof(uint8_t) * 16 )//16 bytes
    /* Category */
    #define STORAGE_CONFIG_NAMEPLATE_CATEGORY_ADDR (STORAGE_CONFIG_NAMEPLATE_MSN_ADDR + STORAGE_CONFIG_NAMEPLATE_MSN_SIZE)//0x214
    #define STORAGE_CONFIG_NAMEPLATE_CATEGORY_SIZE (sizeof(uint8_t) * 2 )//2 byte
    /* MeterType */
    #define STORAGE_CONFIG_NAMEPLATE_METERTYPE_ADDR (STORAGE_CONFIG_NAMEPLATE_CATEGORY_ADDR + STORAGE_CONFIG_NAMEPLATE_CATEGORY_SIZE)//0x216
    #define STORAGE_CONFIG_NAMEPLATE_METERTYPE_SIZE (sizeof(uint8_t))//1 byte
    /* Ib */
    #define STORAGE_CONFIG_NAMEPLATE_IB_ADDR (STORAGE_CONFIG_NAMEPLATE_METERTYPE_ADDR + STORAGE_CONFIG_NAMEPLATE_METERTYPE_SIZE)//0x217
    #define STORAGE_CONFIG_NAMEPLATE_IB_SIZE (sizeof(uint8_t))//1 byte
    /* IMax */
    #define STORAGE_CONFIG_NAMEPLATE_IMAX_ADDR (STORAGE_CONFIG_NAMEPLATE_IB_ADDR + STORAGE_CONFIG_NAMEPLATE_IB_SIZE)//0x218
    #define STORAGE_CONFIG_NAMEPLATE_IMAX_SIZE (sizeof(uint8_t))//1 byte
    /* Year */
    #define STORAGE_CONFIG_NAMEPLATE_YEAR_ADDR (STORAGE_CONFIG_NAMEPLATE_IMAX_ADDR + STORAGE_CONFIG_NAMEPLATE_IMAX_SIZE)//0x219
    #define STORAGE_CONFIG_NAMEPLATE_YEAR_SIZE (sizeof(uint8_t))// 1 byte
    /* ManufacturerNameLen */
    #define STORAGE_CONFIG_NAMEPLATE_MANUFACTURERNAMELEN_ADDR (STORAGE_CONFIG_NAMEPLATE_YEAR_ADDR + STORAGE_CONFIG_NAMEPLATE_YEAR_SIZE)//0x21A
    #define STORAGE_CONFIG_NAMEPLATE_MANUFACTURERNAMELEN_SIZE (sizeof(uint8_t))//1 byte
    /* ManufacturerName */
    #define STORAGE_CONFIG_NAMEPLATE_MANUFACTURERNAME_ADDR (STORAGE_CONFIG_NAMEPLATE_MANUFACTURERNAMELEN_ADDR + STORAGE_CONFIG_NAMEPLATE_MANUFACTURERNAMELEN_SIZE)//0x21B
    #define STORAGE_CONFIG_NAMEPLATE_MANUFACTURERNAME_SIZE (sizeof(uint8_t) * 50 )//50 bytes

	/* Sub module Nameplate last address */
    #define STORAGE_CONFIG_NAMEPLATE_LAST_ADDR (STORAGE_CONFIG_NAMEPLATE_MANUFACTURERNAME_ADDR + STORAGE_CONFIG_NAMEPLATE_MANUFACTURERNAME_SIZE)//0x24D



#endif /* Nameplate */

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

#endif /* _STORAGE_FORMAT_H */

