/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_format.h
* Version      : Version
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

/* Start user code for version control. Do not edit comment generated here */
// 2018-03-29 New creation

// 2018-03-29
//				Change offset to 0x0400, so the metrology have more space. Later for 3P
//				Change storage structure of activity calendar:
//				Add reserved space

// EEPROM
// (Generated on 2018-06-05 14:40:41)		New generate
// (Update    on 2018-08-02 11:36:26)		Add IP for Push setup
// (update    on 2018-08-08 08:31:45)		Separate buffer info of Event table into 6 parts
// (update    on 2018-08-14 13:52:23)		Add billing date items
// (update    on 2018-08-15 13:03:52)		Add backup process state for TOD
// (update    on 2018-08-28 09:40:09)		Add backup items for Block load and Daily load (KWh and KVAh, import and export)
// (update    on 2018-11-07 13:35:44)		Add more reserved space for event log
// (update    on 2019-01-09 11:25:59)		Add last memory address
// (update    on 2019-01-16 14:13:21)		Restructure activity calendar profile, group invidual element into struct
// (update    on 2019-02-20 14:50:04)		Add Block load capture enable flag
// (update    on 2019-09-18 15:41:53)		Demolish day_id sharing table

/* End user code. Do not edit comment generated here */

#ifndef _R_DLMS_STORAGE_MAP_H
#define _R_DLMS_STORAGE_MAP_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"

/* Common */
#include "typedef.h"
#include "compiler.h"

/* DLMS Application */
#include "r_dlms_storage.h"
#include "r_dlms_app.h"
#include "r_dlms_push.h"
#include "r_dlms_scheduler.h"
#include "r_dlms_event.h"
#include "r_meter_format.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Start user code for macro. Do not edit comment generated here */
												/* 0xFE000000 + (Version = v02.01.04) */
#define STORAGE_EEPROM_CURRENT_VERISON			(0xFE020104)
												/* 0xFE000000 + (Version = v02.01.03) */
#define STORAGE_DATAFLASH_CURRENT_VERISON		(0xFE020103)


/* End user code. Do not edit comment generated here */
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/


/* Start user code for typedef. Do not edit comment generated here */

#define ONE_EVENT_FULL_LOG         ONE_EVENT_ENERGY_DATA_LOG
#define ONE_EVENT_SHORT_LOG        ONE_EVENT_ID_LOG

/* RTC Date Time */
typedef struct tag_STORAGE_RTC_DATE_TIME
{
	/* Total: 8 bytes */
	uint8_t Sec;        /* Second */
	uint8_t Min;        /* Minute */
	uint8_t Hour;       /* Hour */
	uint8_t Day;        /* Day */
	uint8_t Week;       /* Day of week */
	uint8_t Month;      /* Month */
	uint8_t Year;       /* Year (ony 2 ending digit) */

	uint8_t reserved;   /* Reserved Byte (Padding) - NO USE */

} STORAGE_RTC_DATE_TIME;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
EEPROM MEMORY MAP
***********************************************************************************************************************/


/* Generated on : Wednesday, January 15, 2020 */
/* root */
/***********************************************************************************************************************
EEPROM_DLMS MEMORY MAP
***********************************************************************************************************************/


/*--------------------------------------------------------------------------------------*/
/* GROUP: EEPROM BASE , Address = 0x0000 */
//#define STORAGE_EEPROM_DLMS_EEPROM_BASE_GROUP    		(STORAGE_EEPROM_METER_FORMAT_LAST_ADDR)
#define STORAGE_EEPROM_DLMS_EEPROM_BASE_GROUP    		(STORAGE_EEPROM_LOAD_CTRL_LAST_ADDR)//0xF0D2 //change by mrityunjay
/*--------------------------------------------------------------------------------------*/
/* GROUP: Header , Address = 0xF0D2 */
#define STORAGE_EEPROM_DLMS_HEADER_GROUP                             (STORAGE_EEPROM_DLMS_EEPROM_BASE_GROUP)

/* Code, 0xF0D2 */
#define STORAGE_EEPROM_DLMS_CODE_ADDR                                (STORAGE_EEPROM_DLMS_HEADER_GROUP)
#define STORAGE_EEPROM_DLMS_CODE_SIZE                                (0)

/* Usage, 0xF0D2 */
#define STORAGE_EEPROM_DLMS_USAGE_ADDR                               (STORAGE_EEPROM_DLMS_CODE_ADDR + STORAGE_EEPROM_DLMS_CODE_SIZE)//0xF0D2
#define STORAGE_EEPROM_DLMS_USAGE_SIZE                               (sizeof(uint16_t))// 2 bytes

/* PADDING */
#define STORAGE_EEPROM_DLMS_HEADER_GROUP_END_ADDR (STORAGE_EEPROM_DLMS_USAGE_ADDR + STORAGE_EEPROM_DLMS_USAGE_SIZE)//0xF0D4
#define STORAGE_EEPROM_DLMS_HEADER_GROUP_PADDING (0x007A)//122 byte

/*--------------------------------------------------------------------------------------*/
/* GROUP: Parameter , Address = 0xF14E */
#define STORAGE_EEPROM_DLMS_PARAMETER_GROUP      (STORAGE_EEPROM_DLMS_HEADER_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_HEADER_GROUP_PADDING)//0xF14E

/* Billing counter , 0xF14E */
#define STORAGE_EEPROM_DLMS_BILLING_COUNTER_ADDR                     (STORAGE_EEPROM_DLMS_PARAMETER_GROUP)//0xF14E
#define STORAGE_EEPROM_DLMS_BILLING_COUNTER_SIZE                     (sizeof(uint32_t))// 4 bytes

/* Tamper counter, 0xF152 */
#define STORAGE_EEPROM_DLMS_TAMPER_COUNTER_ADDR                      (STORAGE_EEPROM_DLMS_BILLING_COUNTER_ADDR + STORAGE_EEPROM_DLMS_BILLING_COUNTER_SIZE)//0xF152
#define STORAGE_EEPROM_DLMS_TAMPER_COUNTER_SIZE                      (sizeof(uint32_t))// 4 bytes

/* PC, 0xF156 */
#define STORAGE_EEPROM_DLMS_PC_ADDR                                  (STORAGE_EEPROM_DLMS_TAMPER_COUNTER_ADDR + STORAGE_EEPROM_DLMS_TAMPER_COUNTER_SIZE)//0xF156
#define STORAGE_EEPROM_DLMS_PC_SIZE                                  (sizeof(uint32_t))// 4 bytes

/* Blockload period, 0xF15A */
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_PERIOD_ADDR                    (STORAGE_EEPROM_DLMS_PC_ADDR + STORAGE_EEPROM_DLMS_PC_SIZE)//0xF15A
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_PERIOD_SIZE                    (sizeof(uint32_t))// 4 bytes

/* Timezone, 0xF15E */
#define STORAGE_EEPROM_DLMS_TIMEZONE_ADDR                            (STORAGE_EEPROM_DLMS_BLOCKLOAD_PERIOD_ADDR + STORAGE_EEPROM_DLMS_BLOCKLOAD_PERIOD_SIZE)//0xF15E
#define STORAGE_EEPROM_DLMS_TIMEZONE_SIZE                            (sizeof(uint16_t))// 2 bytes

/* Old time, 0xF160 */
#define STORAGE_EEPROM_DLMS_OLD_TIME_ADDR                            (STORAGE_EEPROM_DLMS_TIMEZONE_ADDR + STORAGE_EEPROM_DLMS_TIMEZONE_SIZE)//0xF160
#define STORAGE_EEPROM_DLMS_OLD_TIME_SIZE                            (sizeof(uint8_t) * 8)// 1 byte

/* ESW, 0xF161 */
#define STORAGE_EEPROM_DLMS_ESW_ADDR                                 (STORAGE_EEPROM_DLMS_OLD_TIME_ADDR + STORAGE_EEPROM_DLMS_OLD_TIME_SIZE)//0xF161
#define STORAGE_EEPROM_DLMS_ESW_SIZE                                 (sizeof(uint8_t) * 16)// 2 bytes

/* ESWF, 0xF163 */
#define STORAGE_EEPROM_DLMS_ESWF_ADDR                                (STORAGE_EEPROM_DLMS_ESW_ADDR + STORAGE_EEPROM_DLMS_ESW_SIZE)//0xF163
#define STORAGE_EEPROM_DLMS_ESWF_SIZE                                (sizeof(uint8_t) * 16)// 2 bytes

/* EventCode, 0xF165 */
#define STORAGE_EEPROM_EVENTCODE_ADDR                                (STORAGE_EEPROM_DLMS_ESWF_ADDR + STORAGE_EEPROM_DLMS_ESWF_SIZE)//0xF165
#define STORAGE_EEPROM_EVENTCODE_SIZE                                (sizeof(uint16_t) * EVENT_PROFILE_NUMBER)//2*7=14 bytes

/* SMO_1_LEN, 0xF173 */
#define STORAGE_EEPROM_DLMS_SMO_1_LEN_ADDR                           (STORAGE_EEPROM_EVENTCODE_ADDR + STORAGE_EEPROM_EVENTCODE_SIZE)//0xF173
#define STORAGE_EEPROM_DLMS_SMO_1_LEN_SIZE                           (sizeof(uint8_t))//1 byte

/* SMO_1, 0xF174 */
#define STORAGE_EEPROM_DLMS_SMO_1_ADDR                               (STORAGE_EEPROM_DLMS_SMO_1_LEN_ADDR + STORAGE_EEPROM_DLMS_SMO_1_LEN_SIZE)//0xF173
#define STORAGE_EEPROM_DLMS_SMO_1_SIZE                               (sizeof(uint8_t) * 128)//128 bytes

/* SMO_1_Padding, 0xF1F4 */
#define STORAGE_EEPROM_DLMS_SMO_1_PADDING_ADDR                       (STORAGE_EEPROM_DLMS_SMO_1_ADDR + STORAGE_EEPROM_DLMS_SMO_1_SIZE)//0xF1F4
#define STORAGE_EEPROM_DLMS_SMO_1_PADDING_SIZE                       (sizeof(uint8_t))//1 byte

/* SMO_2_LEN, 0xF1F5 */
#define STORAGE_EEPROM_DLMS_SMO_2_LEN_ADDR                           (STORAGE_EEPROM_DLMS_SMO_1_PADDING_ADDR + STORAGE_EEPROM_DLMS_SMO_1_PADDING_SIZE)//0xF1F5
#define STORAGE_EEPROM_DLMS_SMO_2_LEN_SIZE                           (sizeof(uint8_t))//1 byte

/* SMO_2, 0xF1F6 */
#define STORAGE_EEPROM_DLMS_SMO_2_ADDR                               (STORAGE_EEPROM_DLMS_SMO_2_LEN_ADDR + STORAGE_EEPROM_DLMS_SMO_2_LEN_SIZE)//0xF1F6
#define STORAGE_EEPROM_DLMS_SMO_2_SIZE                               (sizeof(uint8_t) * 128)//128 bytes

/* SMO_2_Padding, 0xF276 */
#define STORAGE_EEPROM_DLMS_SMO_2_PADDING_ADDR                       (STORAGE_EEPROM_DLMS_SMO_2_ADDR + STORAGE_EEPROM_DLMS_SMO_2_SIZE)//0xF276
#define STORAGE_EEPROM_DLMS_SMO_2_PADDING_SIZE                       (sizeof(uint8_t))//1 byte

/* Billing date, 0xF277 */
#define STORAGE_EEPROM_DLMS_BILLING_DATE_ADDR                        (STORAGE_EEPROM_DLMS_SMO_2_PADDING_ADDR + STORAGE_EEPROM_DLMS_SMO_2_PADDING_SIZE)//0xF276
#define STORAGE_EEPROM_DLMS_BILLING_DATE_SIZE                        (sizeof(R_DLMS_RTC_T))// 7 bytes

/* Blockload state, 0xF27E */
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_STATE_ADDR                     (STORAGE_EEPROM_DLMS_BILLING_DATE_ADDR + STORAGE_EEPROM_DLMS_BILLING_DATE_SIZE)//0xF27E
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_STATE_SIZE                     (sizeof(uint8_t)) //1 byte

/* Kwh block, 0xF27F */
#define STORAGE_EEPROM_DLMS_KWH_BLOCK_ADDR                           (STORAGE_EEPROM_DLMS_BLOCKLOAD_STATE_ADDR + STORAGE_EEPROM_DLMS_BLOCKLOAD_STATE_SIZE)//0xF27F
#define STORAGE_EEPROM_DLMS_KWH_BLOCK_SIZE                           (sizeof(uint32_t))// 4 byte

/* Kvah block, 0xF283 */
#define STORAGE_EEPROM_DLMS_KVAH_BLOCK_ADDR                          (STORAGE_EEPROM_DLMS_KWH_BLOCK_ADDR + STORAGE_EEPROM_DLMS_KWH_BLOCK_SIZE)//0xF283
#define STORAGE_EEPROM_DLMS_KVAH_BLOCK_SIZE                          (sizeof(uint32_t))//4 bytes

/* Voltage average block, 0xF287 */
#define STORAGE_EEPROM_DLMS_VOLTAGE_AVERAGE_BLOCK_ADDR               (STORAGE_EEPROM_DLMS_KVAH_BLOCK_ADDR + STORAGE_EEPROM_DLMS_KVAH_BLOCK_SIZE)//0xF287
#define STORAGE_EEPROM_DLMS_VOLTAGE_AVERAGE_BLOCK_SIZE               (sizeof(uint32_t))//4 bytes

/* Current average block, 0xF28B */
#define STORAGE_EEPROM_DLMS_CURRENT_AVERAGE_BLOCK_ADDR               (STORAGE_EEPROM_DLMS_VOLTAGE_AVERAGE_BLOCK_ADDR + STORAGE_EEPROM_DLMS_VOLTAGE_AVERAGE_BLOCK_SIZE)//0xF28B 
#define STORAGE_EEPROM_DLMS_CURRENT_AVERAGE_BLOCK_SIZE               (sizeof(uint32_t))//4 bytes

/* Kwh block export, 0xF28F  */
#define STORAGE_EEPROM_DLMS_KWH_BLOCK_EXPORT_ADDR                    (STORAGE_EEPROM_DLMS_CURRENT_AVERAGE_BLOCK_ADDR + STORAGE_EEPROM_DLMS_CURRENT_AVERAGE_BLOCK_SIZE)//0xF28F
#define STORAGE_EEPROM_DLMS_KWH_BLOCK_EXPORT_SIZE                    (sizeof(uint32_t))//4 bytes

/* Kvah block export, 0xF293 */
#define STORAGE_EEPROM_DLMS_KVAH_BLOCK_EXPORT_ADDR                   (STORAGE_EEPROM_DLMS_KWH_BLOCK_EXPORT_ADDR + STORAGE_EEPROM_DLMS_KWH_BLOCK_EXPORT_SIZE)//0xF293
#define STORAGE_EEPROM_DLMS_KVAH_BLOCK_EXPORT_SIZE                   (sizeof(uint32_t))//4 bytes

/* Kwh day, 0xF297 */
#define STORAGE_EEPROM_DLMS_KWH_DAY_ADDR                             (STORAGE_EEPROM_DLMS_KVAH_BLOCK_EXPORT_ADDR + STORAGE_EEPROM_DLMS_KVAH_BLOCK_EXPORT_SIZE)//0xF297
#define STORAGE_EEPROM_DLMS_KWH_DAY_SIZE                             (sizeof(uint32_t))//4 bytes

/* Kvah day, 0xF29B */
#define STORAGE_EEPROM_DLMS_KVAH_DAY_ADDR                            (STORAGE_EEPROM_DLMS_KWH_DAY_ADDR + STORAGE_EEPROM_DLMS_KWH_DAY_SIZE)//0xF29B
#define STORAGE_EEPROM_DLMS_KVAH_DAY_SIZE                            (sizeof(uint32_t))//4 bytes

/* Kwh day export, 0xF29F */
#define STORAGE_EEPROM_DLMS_KWH_DAY_EXPORT_ADDR                      (STORAGE_EEPROM_DLMS_KVAH_DAY_ADDR + STORAGE_EEPROM_DLMS_KVAH_DAY_SIZE)//0xF29F
#define STORAGE_EEPROM_DLMS_KWH_DAY_EXPORT_SIZE                      (sizeof(uint32_t))//4 bytes

/* Kvah day export, 0xF2A3 */
#define STORAGE_EEPROM_DLMS_KVAH_DAY_EXPORT_ADDR                     (STORAGE_EEPROM_DLMS_KWH_DAY_EXPORT_ADDR + STORAGE_EEPROM_DLMS_KWH_DAY_EXPORT_SIZE)//0xF2A3
#define STORAGE_EEPROM_DLMS_KVAH_DAY_EXPORT_SIZE                     (sizeof(uint32_t))//4 bytes

/* Old time blockload, 0xF2A7 */
#define STORAGE_EEPROM_DLMS_OLD_TIME_BLOCKLOAD_ADDR                  (STORAGE_EEPROM_DLMS_KVAH_DAY_EXPORT_ADDR + STORAGE_EEPROM_DLMS_KVAH_DAY_EXPORT_SIZE)//0xF2A7
#define STORAGE_EEPROM_DLMS_OLD_TIME_BLOCKLOAD_SIZE                  (sizeof(R_DLMS_RTC_T))//7 bytes

/* Blockload capture enable, 0xF2AE */
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_CAPTURE_ENABLE_ADDR            (STORAGE_EEPROM_DLMS_OLD_TIME_BLOCKLOAD_ADDR + STORAGE_EEPROM_DLMS_OLD_TIME_BLOCKLOAD_SIZE)//0xF2AE
#define STORAGE_EEPROM_DLMS_BLOCKLOAD_CAPTURE_ENABLE_SIZE            (sizeof(uint8_t))//1 byte

/* Meter mode, 0xF2AF */
#define STORAGE_EEPROM_DLMS_METER_MODE_ADDR                          (STORAGE_EEPROM_DLMS_BLOCKLOAD_CAPTURE_ENABLE_ADDR + STORAGE_EEPROM_DLMS_BLOCKLOAD_CAPTURE_ENABLE_SIZE)//0xF2AF
#define STORAGE_EEPROM_DLMS_METER_MODE_SIZE                          (sizeof(uint8_t))//1 byte

/* Payment mode, 0xF2B0 */
#define STORAGE_EEPROM_DLMS_PAYMENT_MODE_ADDR                        (STORAGE_EEPROM_DLMS_METER_MODE_ADDR + STORAGE_EEPROM_DLMS_METER_MODE_SIZE)//0xF2B0
#define STORAGE_EEPROM_DLMS_PAYMENT_MODE_SIZE                        (sizeof(uint8_t))//1 byte

/* Clock status, 0xF2B1 */
#define STORAGE_EEPROM_DLMS_CLOCK_STATUS_ADDR                        (STORAGE_EEPROM_DLMS_PAYMENT_MODE_ADDR + STORAGE_EEPROM_DLMS_PAYMENT_MODE_SIZE)//0xF2B1
#define STORAGE_EEPROM_DLMS_CLOCK_STATUS_SIZE                        (sizeof(uint8_t))//1 byte

/* billing_events, 0xF2B2 */
#define STORAGE_EEPROM_DLMS_BILLING_EVENTS_ADDR                      (STORAGE_EEPROM_DLMS_CLOCK_STATUS_ADDR + STORAGE_EEPROM_DLMS_CLOCK_STATUS_SIZE)//0xF2B2
#define STORAGE_EEPROM_DLMS_BILLING_EVENTS_SIZE                      (sizeof(uint16_t))//2 bytes

/* PADDING */
#define STORAGE_EEPROM_DLMS_PARAMETER_GROUP_END_ADDR (STORAGE_EEPROM_DLMS_BILLING_EVENTS_ADDR + STORAGE_EEPROM_DLMS_BILLING_EVENTS_SIZE)//0xF2B4
#define STORAGE_EEPROM_DLMS_PARAMETER_GROUP_PADDING (0x000A)

/*--------------------------------------------------------------------------------------*/
/* GROUP: Push , Address = 0xF2BC */
#define STORAGE_EEPROM_DLMS_PUSH_GROUP           (STORAGE_EEPROM_DLMS_PARAMETER_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_PARAMETER_GROUP_PADDING)//0xF2BC

/* Push status, 0xF2BC */
#define STORAGE_EEPROM_DLMS_PUSH_STATUS_ADDR                         (STORAGE_EEPROM_DLMS_PUSH_GROUP)//0xF2BC
#define STORAGE_EEPROM_DLMS_PUSH_STATUS_SIZE                         (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)//1*5 bytes

/* Push trigger, 0xF2C1 */
#define STORAGE_EEPROM_DLMS_PUSH_TRIGGER_ADDR                        (STORAGE_EEPROM_DLMS_PUSH_STATUS_ADDR + STORAGE_EEPROM_DLMS_PUSH_STATUS_SIZE)//0xF2C1
#define STORAGE_EEPROM_DLMS_PUSH_TRIGGER_SIZE                        (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)//5 bytes

/* Rand interval, 0xF2C6 */
#define STORAGE_EEPROM_DLMS_RAND_INTERVAL_ADDR                       (STORAGE_EEPROM_DLMS_PUSH_TRIGGER_ADDR + STORAGE_EEPROM_DLMS_PUSH_TRIGGER_SIZE)//0xF2C6
#define STORAGE_EEPROM_DLMS_RAND_INTERVAL_SIZE                       (sizeof(uint16_t) * PUSH_OBJECT_NUMBER)//2*5=10 bytes

/* Number retry, 0xF2D0 */
#define STORAGE_EEPROM_DLMS_NUMBER_RETRY_ADDR                        (STORAGE_EEPROM_DLMS_RAND_INTERVAL_ADDR + STORAGE_EEPROM_DLMS_RAND_INTERVAL_SIZE)//0xF2D0
#define STORAGE_EEPROM_DLMS_NUMBER_RETRY_SIZE                        (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)//5 bytes

/* Retry delay time, 0xF2D5 */
#define STORAGE_EEPROM_DLMS_RETRY_DELAY_TIME_ADDR                    (STORAGE_EEPROM_DLMS_NUMBER_RETRY_ADDR + STORAGE_EEPROM_DLMS_NUMBER_RETRY_SIZE)//0xF2D5
#define STORAGE_EEPROM_DLMS_RETRY_DELAY_TIME_SIZE                    (sizeof(uint16_t) * PUSH_OBJECT_NUMBER)//2*5=10 bytes

/* Push_protocol, 0xF2DF */
#define STORAGE_EEPROM_DLMS_PUSH_PROTOCOL_ADDR                       (STORAGE_EEPROM_DLMS_RETRY_DELAY_TIME_ADDR + STORAGE_EEPROM_DLMS_RETRY_DELAY_TIME_SIZE)//0xF2DF
#define STORAGE_EEPROM_DLMS_PUSH_PROTOCOL_SIZE                       (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)// 5 bytes

/* Push_ip_config, 0xF2E4 */
#define STORAGE_EEPROM_DLMS_PUSH_IP_CONFIG_ADDR                      (STORAGE_EEPROM_DLMS_PUSH_PROTOCOL_ADDR + STORAGE_EEPROM_DLMS_PUSH_PROTOCOL_SIZE)//0xF2E4
#define STORAGE_EEPROM_DLMS_PUSH_IP_CONFIG_SIZE                      (sizeof(uint8_t) * 20 * PUSH_OBJECT_NUMBER)//1*20*5=100 bytes

/* Push_message_type, 0xF348 */
#define STORAGE_EEPROM_DLMS_PUSH_MESSAGE_TYPE_ADDR                   (STORAGE_EEPROM_DLMS_PUSH_IP_CONFIG_ADDR + STORAGE_EEPROM_DLMS_PUSH_IP_CONFIG_SIZE)//0xF348
#define STORAGE_EEPROM_DLMS_PUSH_MESSAGE_TYPE_SIZE                   (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)// 5 bytes

/* Push_port, 0xF34D */
#define STORAGE_EEPROM_DLMS_PUSH_PORT_ADDR                           (STORAGE_EEPROM_DLMS_PUSH_MESSAGE_TYPE_ADDR + STORAGE_EEPROM_DLMS_PUSH_MESSAGE_TYPE_SIZE)//0xF34D
#define STORAGE_EEPROM_DLMS_PUSH_PORT_SIZE                           (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)// 5 bytes

/* Push_window, 0xF352 */
#define STORAGE_EEPROM_DLMS_PUSH_WINDOW_ADDR                         (STORAGE_EEPROM_DLMS_PUSH_PORT_ADDR + STORAGE_EEPROM_DLMS_PUSH_PORT_SIZE)//0xF352
#define STORAGE_EEPROM_DLMS_PUSH_WINDOW_SIZE                         (sizeof(push_window_t) * PUSH_OBJECT_NUMBER * PUSH_MAX_WINDOW_SUPPORT)//14*5*4=280 bytes

/* Push_num_of_window, 0xF46A */
#define STORAGE_EEPROM_DLMS_PUSH_NUM_OF_WINDOW_ADDR                  (STORAGE_EEPROM_DLMS_PUSH_WINDOW_ADDR + STORAGE_EEPROM_DLMS_PUSH_WINDOW_SIZE)//0xF46A
#define STORAGE_EEPROM_DLMS_PUSH_NUM_OF_WINDOW_SIZE                  (sizeof(uint8_t) * PUSH_OBJECT_NUMBER)// 5 bytes

/* PADDING */
#define STORAGE_EEPROM_DLMS_PUSH_GROUP_END_ADDR  (STORAGE_EEPROM_DLMS_PUSH_NUM_OF_WINDOW_ADDR + STORAGE_EEPROM_DLMS_PUSH_NUM_OF_WINDOW_SIZE)//0xF46F
#define STORAGE_EEPROM_DLMS_PUSH_GROUP_PADDING   (0x000A)


/*--------------------------------------------------------------------------------------*/
/* GROUP: Comm Profile , Address = 0xF479 */
#define STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP   (STORAGE_EEPROM_DLMS_PUSH_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_PUSH_GROUP_PADDING)//0xF479

/* Tcpupd port, 0xF479 */
#define STORAGE_EEPROM_DLMS_TCPUPD_PORT_ADDR                         (STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP)//0xF479
#define STORAGE_EEPROM_DLMS_TCPUPD_PORT_SIZE                         (sizeof(uint32_t))// 4 bytes

/* Ipv4 address, 0xF47D */
#define STORAGE_EEPROM_DLMS_IPV4_ADDRESS_ADDR                        (STORAGE_EEPROM_DLMS_TCPUPD_PORT_ADDR + STORAGE_EEPROM_DLMS_TCPUPD_PORT_SIZE)//0xF47D
#define STORAGE_EEPROM_DLMS_IPV4_ADDRESS_SIZE                        (sizeof(uint8_t) * 4)//4 bytes

/* Ipv6 address, 0xF481 */
#define STORAGE_EEPROM_DLMS_IPV6_ADDRESS_ADDR                        (STORAGE_EEPROM_DLMS_IPV4_ADDRESS_ADDR + STORAGE_EEPROM_DLMS_IPV4_ADDRESS_SIZE)//0xF481
#define STORAGE_EEPROM_DLMS_IPV6_ADDRESS_SIZE                        (sizeof(uint8_t) * 16)//16 bytes

/* MAC address, 0xF491 */
#define STORAGE_EEPROM_DLMS_MAC_ADDRESS_ADDR                         (STORAGE_EEPROM_DLMS_IPV6_ADDRESS_ADDR + STORAGE_EEPROM_DLMS_IPV6_ADDRESS_SIZE)//0xF491
#define STORAGE_EEPROM_DLMS_MAC_ADDRESS_SIZE                         (sizeof(uint8_t) * 4)// 4 bytes

/* Hdlc comm_speed , 0xF495 */
#define STORAGE_EEPROM_DLMS_HDLC_COMM_SPEED_ADDR                     (STORAGE_EEPROM_DLMS_MAC_ADDRESS_ADDR + STORAGE_EEPROM_DLMS_MAC_ADDRESS_SIZE)//0xF495
#define STORAGE_EEPROM_DLMS_HDLC_COMM_SPEED_SIZE                     (sizeof(uint8_t))//1 byte

/* Hdlc windows_size_tx, 0xF496 */
#define STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_TX_ADDR                (STORAGE_EEPROM_DLMS_HDLC_COMM_SPEED_ADDR + STORAGE_EEPROM_DLMS_HDLC_COMM_SPEED_SIZE)//0xF496
#define STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_TX_SIZE                (sizeof(uint16_t))// 2 bytes 

/* Hdlc windows_size_rx, 0xF498 */
#define STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_RX_ADDR                (STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_TX_ADDR + STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_TX_SIZE)//0xF498
#define STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_RX_SIZE                (sizeof(uint16_t))// 2 bytes

/* Hdlc max_info_length_tx, 0xF49A */
#define STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_TX_ADDR             (STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_RX_ADDR + STORAGE_EEPROM_DLMS_HDLC_WINDOWS_SIZE_RX_SIZE)//0xF49A
#define STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_TX_SIZE             (sizeof(uint16_t))// 2 bytes

/* Hdlc max_info_length_rx, 0xF49C */
#define STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_RX_ADDR             (STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_TX_ADDR + STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_TX_SIZE)//0xF49C
#define STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_RX_SIZE             (sizeof(uint16_t))// 2 bytes

/* Hdlc inter_octet_timeout, 0xF49E */
#define STORAGE_EEPROM_DLMS_HDLC_INTER_OCTET_TIMEOUT_ADDR            (STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_RX_ADDR + STORAGE_EEPROM_DLMS_HDLC_MAX_INFO_LENGTH_RX_SIZE)//0xF49E
#define STORAGE_EEPROM_DLMS_HDLC_INTER_OCTET_TIMEOUT_SIZE            (sizeof(uint16_t))// 2 bytes

/* Hdlc inactivity_timeout, 0xF4A0 */
#define STORAGE_EEPROM_DLMS_HDLC_INACTIVITY_TIMEOUT_ADDR             (STORAGE_EEPROM_DLMS_HDLC_INTER_OCTET_TIMEOUT_ADDR + STORAGE_EEPROM_DLMS_HDLC_INTER_OCTET_TIMEOUT_SIZE)//0xF4A0
#define STORAGE_EEPROM_DLMS_HDLC_INACTIVITY_TIMEOUT_SIZE             (sizeof(uint16_t))// 2 bytes

/* Hdlc device_address, 0xF4A2 */
#define STORAGE_EEPROM_DLMS_HDLC_DEVICE_ADDRESS_ADDR                 (STORAGE_EEPROM_DLMS_HDLC_INACTIVITY_TIMEOUT_ADDR + STORAGE_EEPROM_DLMS_HDLC_INACTIVITY_TIMEOUT_SIZE)//0xF4A2
#define STORAGE_EEPROM_DLMS_HDLC_DEVICE_ADDRESS_SIZE                 (sizeof(uint16_t))// 2 bytes

/* PADDING */
#define STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP_END_ADDR (STORAGE_EEPROM_DLMS_HDLC_DEVICE_ADDRESS_ADDR + STORAGE_EEPROM_DLMS_HDLC_DEVICE_ADDRESS_SIZE)//0xF4A4
#define STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP_PADDING (0x0014)

/*--------------------------------------------------------------------------------------*/
/* GROUP: Firmware upgrade  , Address = 0xF4B8 */
#define STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP (STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_COMM_PROFILE_GROUP_PADDING)//0xF4B8

/* Img block size, 0xF4B8 */
#define STORAGE_EEPROM_DLMS_IMG_BLOCK_SIZE_ADDR                      (STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP)//0xF4B8
#define STORAGE_EEPROM_DLMS_IMG_BLOCK_SIZE_SIZE                      (sizeof(uint32_t))// 4 bytes

/* Img bitstring, 0xF4BC */
#define STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR                       (STORAGE_EEPROM_DLMS_IMG_BLOCK_SIZE_ADDR + STORAGE_EEPROM_DLMS_IMG_BLOCK_SIZE_SIZE)//0xF4BC
#define STORAGE_EEPROM_DLMS_IMG_BITSTRING_SIZE                       (sizeof(uint8_t) * 512)//512 bytes

/* Img bitstring length, 0xF6BC */
#define STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_ADDR                (STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR + STORAGE_EEPROM_DLMS_IMG_BITSTRING_SIZE)//0xF6BC
#define STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_SIZE                (sizeof(uint16_t))// 2 bytes

/* Img status, 0xF6BE */
#define STORAGE_EEPROM_DLMS_IMG_STATUS_ADDR                          (STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_ADDR + STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_SIZE)//0xF6BE
#define STORAGE_EEPROM_DLMS_IMG_STATUS_SIZE                          (sizeof(uint8_t))// 1 byte

/* Img size, 0xF6BF */
#define STORAGE_EEPROM_DLMS_IMG_SIZE_ADDR                            (STORAGE_EEPROM_DLMS_IMG_STATUS_ADDR + STORAGE_EEPROM_DLMS_IMG_STATUS_SIZE)//0xF6BF
#define STORAGE_EEPROM_DLMS_IMG_SIZE_SIZE                            (sizeof(uint32_t))// 4 bytes

/* Img identification length, 0xF6C3 */
#define STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_ADDR           (STORAGE_EEPROM_DLMS_IMG_SIZE_ADDR + STORAGE_EEPROM_DLMS_IMG_SIZE_SIZE)//0xF6C3
#define STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_SIZE           (sizeof(uint16_t))// 2 bytes

/* Img identification, 0xF6C5 */
#define STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_ADDR                  (STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_ADDR + STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_SIZE)//0xF6C5
#define STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE                  (sizeof(uint8_t) * 48)//48 bytes

/* Img signature, 0xF6F5 */
#define STORAGE_EEPROM_DLMS_IMG_SIGNATURE_ADDR                       (STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_ADDR + STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE)//0xF6F5
#define STORAGE_EEPROM_DLMS_IMG_SIGNATURE_SIZE                       (sizeof(uint8_t) * 4)//4 bytes

/* PADDING */
#define STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP_END_ADDR (STORAGE_EEPROM_DLMS_IMG_SIGNATURE_ADDR + STORAGE_EEPROM_DLMS_IMG_SIGNATURE_SIZE)//0xF6F9
#define STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP_PADDING (0x0010)

/*--------------------------------------------------------------------------------------*/
/* Asosciation secret key , //0xF709 group */
#define STORAGE_EEPROM_DLMS_ASOSCIATION_SECRET_KEY_GROUP     (STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_FIRMWARE_UPGRADE_GROUP_PADDING)//0xF709

/* LLS Secret MR len , //0xF709 */
#define STORAGE_EEPROM_DLMS_LLS_SECRET_MR_LEN_ADDR           STORAGE_EEPROM_DLMS_ASOSCIATION_SECRET_KEY_GROUP//0xF709
#define STORAGE_EEPROM_DLMS_LLS_SECRET_MR_LEN_SIZE           ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 =1 byte*/

/* LLS Secret MR , //0xF70A */
#define STORAGE_EEPROM_DLMS_LLS_SECRET_MR_ADDR               STORAGE_EEPROM_DLMS_LLS_SECRET_MR_LEN_ADDR + STORAGE_EEPROM_DLMS_LLS_SECRET_MR_LEN_SIZE//0xF70A
#define STORAGE_EEPROM_DLMS_LLS_SECRET_MR_SIZE               ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 =16 bytes*/

/* HLS Key US len , 0xF71A */
#define STORAGE_EEPROM_DLMS_HLS_KEY_US_LEN_ADDR              STORAGE_EEPROM_DLMS_LLS_SECRET_MR_ADDR + STORAGE_EEPROM_DLMS_LLS_SECRET_MR_SIZE//0xF71A
#define STORAGE_EEPROM_DLMS_HLS_KEY_US_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* HLS Key US  , 0xF71B */
#define STORAGE_EEPROM_DLMS_HLS_KEY_US_ADDR                  STORAGE_EEPROM_DLMS_HLS_KEY_US_LEN_ADDR + STORAGE_EEPROM_DLMS_HLS_KEY_US_LEN_SIZE//0xF71B
#define STORAGE_EEPROM_DLMS_HLS_KEY_US_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* HLS Key FW len , 0xF72B */
#define STORAGE_EEPROM_DLMS_HLS_KEY_FW_LEN_ADDR              STORAGE_EEPROM_DLMS_HLS_KEY_US_ADDR + STORAGE_EEPROM_DLMS_HLS_KEY_US_SIZE//0xF72B
#define STORAGE_EEPROM_DLMS_HLS_KEY_FW_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* HLS Key FW , 0xF72C */
#define STORAGE_EEPROM_DLMS_HLS_KEY_FW_ADDR                  STORAGE_EEPROM_DLMS_HLS_KEY_FW_LEN_ADDR + STORAGE_EEPROM_DLMS_HLS_KEY_FW_LEN_SIZE //0xF72C
#define STORAGE_EEPROM_DLMS_HLS_KEY_FW_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Asso key 3 len , 0xF73C */
#define STORAGE_EEPROM_DLMS_ASSO_KEY_3_LEN_ADDR              STORAGE_EEPROM_DLMS_HLS_KEY_FW_ADDR + STORAGE_EEPROM_DLMS_HLS_KEY_FW_SIZE//0xF73C
#define STORAGE_EEPROM_DLMS_ASSO_KEY_3_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Asso key 3 , 0xF73D */
#define STORAGE_EEPROM_DLMS_ASSO_KEY_3_ADDR                  STORAGE_EEPROM_DLMS_ASSO_KEY_3_LEN_ADDR + STORAGE_EEPROM_DLMS_ASSO_KEY_3_LEN_SIZE//0xF73D
#define STORAGE_EEPROM_DLMS_ASSO_KEY_3_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Asso key 4 len , 0xF74D */
#define STORAGE_EEPROM_DLMS_ASSO_KEY_4_LEN_ADDR              STORAGE_EEPROM_DLMS_ASSO_KEY_3_ADDR + STORAGE_EEPROM_DLMS_ASSO_KEY_3_SIZE//0xF74D
#define STORAGE_EEPROM_DLMS_ASSO_KEY_4_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Asso key 4 , 0xF74E */
#define STORAGE_EEPROM_DLMS_ASSO_KEY_4_ADDR                  STORAGE_EEPROM_DLMS_ASSO_KEY_4_LEN_ADDR + STORAGE_EEPROM_DLMS_ASSO_KEY_4_LEN_SIZE//0xF74E
#define STORAGE_EEPROM_DLMS_ASSO_KEY_4_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/*--------------------------------------------------------------------------------------*/
/* HLS key , 0xF75E group */
#define STORAGE_EEPROM_DLMS_HLS_KEY_GROUP            (STORAGE_EEPROM_DLMS_ASSO_KEY_4_ADDR + STORAGE_EEPROM_DLMS_ASSO_KEY_4_SIZE)//0xF75E

/* Master key len , 0xF75E */
#define STORAGE_EEPROM_DLMS_MASTER_KEY_LEN_ADDR              STORAGE_EEPROM_DLMS_HLS_KEY_GROUP//0xF75E
#define STORAGE_EEPROM_DLMS_MASTER_KEY_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Master key , 0xF75F */
#define STORAGE_EEPROM_DLMS_MASTER_KEY_ADDR                  STORAGE_EEPROM_DLMS_MASTER_KEY_LEN_ADDR + STORAGE_EEPROM_DLMS_MASTER_KEY_LEN_SIZE//0xF75F
#define STORAGE_EEPROM_DLMS_MASTER_KEY_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Unicast key len , 0xF76F */
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_LEN_ADDR             STORAGE_EEPROM_DLMS_MASTER_KEY_ADDR + STORAGE_EEPROM_DLMS_MASTER_KEY_SIZE//0xF76F
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_LEN_SIZE             ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Unicast key , 0xF770 */
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_ADDR                 STORAGE_EEPROM_DLMS_UNICAST_KEY_LEN_ADDR + STORAGE_EEPROM_DLMS_UNICAST_KEY_LEN_SIZE//0xF770
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_SIZE                 ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Invocation Counter EK0, 0xF780 */
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK0_ADDR      STORAGE_EEPROM_DLMS_UNICAST_KEY_ADDR + STORAGE_EEPROM_DLMS_UNICAST_KEY_SIZE//0xF780
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK0_SIZE      (sizeof(uint32_t) * 2)//8 bytes

/* Broadcast key len , 0xF788 */
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_LEN_ADDR           STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK0_ADDR + STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK0_SIZE//0xF788
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_LEN_SIZE           ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Broadcast key , 0xF789 */
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_ADDR               STORAGE_EEPROM_DLMS_BROADCAST_KEY_LEN_ADDR + STORAGE_EEPROM_DLMS_BROADCAST_KEY_LEN_SIZE//0xF789
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_SIZE               ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Invocation Counter EK1, 0xF799 */
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK1_ADDR      STORAGE_EEPROM_DLMS_BROADCAST_KEY_ADDR + STORAGE_EEPROM_DLMS_BROADCAST_KEY_SIZE//0xF799
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK1_SIZE      (sizeof(uint32_t) * 2)// 8 bytes

/* Authen key len , 0xF7A1 */
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_LEN_ADDR              STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK1_ADDR + STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK1_SIZE//0xF7A1
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_LEN_SIZE              ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Authen key , 0xF7A2 */
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_ADDR                  STORAGE_EEPROM_DLMS_AUTHEN_KEY_LEN_ADDR + STORAGE_EEPROM_DLMS_AUTHEN_KEY_LEN_SIZE//0xF7A2
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_SIZE                  ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Unicast key IHD , 0xF7B2 */
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_ADDR             STORAGE_EEPROM_DLMS_AUTHEN_KEY_ADDR + STORAGE_EEPROM_DLMS_AUTHEN_KEY_SIZE//0xF7B2
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_SIZE             ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* Unicast key IHD len , 0xF7C2 */
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_LEN_ADDR         STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_ADDR + STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_SIZE//0xF7C2
#define STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_LEN_SIZE         ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Invocation Counter EK2, 0xF7C3 */
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK2_ADDR      STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_LEN_ADDR + STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_LEN_SIZE//0xF7C3
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK2_SIZE      (sizeof(uint32_t) * 2)//8 bytes

/* Broadcast key IHD len , 0xF7CB */
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_LEN_ADDR       STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK2_ADDR + STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK2_SIZE//0xF7CB
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_LEN_SIZE       ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Broadcast key IHD , 0xF7CC */
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_ADDR           STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_LEN_ADDR + STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_LEN_SIZE//0xF7CC
#define STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_SIZE           ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */


/* Invocation Counter EK3, 0xF7DC */
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK3_ADDR      STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_ADDR + STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_SIZE//0xF7DC
#define STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK3_SIZE      (sizeof(uint32_t) * 2)// 8 bytes

/* Authen key IHD len , 0xF7E4 */
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_LEN_ADDR          STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK3_ADDR + STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK3_SIZE//0xF7E4
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_LEN_SIZE          ( sizeof(uint8_t) * 1 )    /* 1 (Bytes) x 1 */

/* Authen key IHD , 0xF7E5 */
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_ADDR              STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_LEN_ADDR + STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_LEN_SIZE//0xF7E5
#define STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_SIZE              ( sizeof(uint8_t) * 16 )    /* 1 (Bytes) x 16 */

/* PADDING */
#define STORAGE_EEPROM_DLMS_ASSOCIATION_SECRET_KEY_GROUP_END_ADDR (STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_ADDR + STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_SIZE)//0xF7F5
#define STORAGE_EEPROM_DLMS_ASSOCIATION_SECRET_KEY_GROUP_PADDING (0x000A)
/*--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------*/
/* GROUP: Modem Setting , Address = 0xF7FF */
#define STORAGE_EEPROM_DLMS_MODEM_SETTING_GROUP                 (STORAGE_EEPROM_DLMS_ASSOCIATION_SECRET_KEY_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_ASSOCIATION_SECRET_KEY_GROUP_PADDING)//0xF7FF

/* APN Name, 0xF7FF */
#define STORAGE_EEPROM_DLMS_MODEM_SETTING_APN_NAME_ADDR         (STORAGE_EEPROM_DLMS_MODEM_SETTING_GROUP)//0xF7FF
#define STORAGE_EEPROM_DLMS_MODEM_SETTING_APN_NAME_SIZE         (64)    /* Reserved size 64 */

#define STORAGE_EEPROM_DLMS_MODEM_SETTING_GROUP_END_ADDR       (STORAGE_EEPROM_DLMS_MODEM_SETTING_APN_NAME_ADDR + STORAGE_EEPROM_DLMS_MODEM_SETTING_APN_NAME_SIZE)//0xF83F
#define STORAGE_EEPROM_DLMS_MODEM_SETTING_GROUP_PADDING        (0x000A)



/*--------------------------------------------------------------------------------------*/

#define STORAGE_EEPROM_DLMS_LAST_ADDR                       (STORAGE_EEPROM_DLMS_MODEM_SETTING_GROUP_END_ADDR + STORAGE_EEPROM_DLMS_MODEM_SETTING_GROUP_PADDING)//0xF849

/***********************************************************************************************************************
EEPROM BACKUP/RESTORE MACRO
***********************************************************************************************************************/


/***********************************************************************************************************************
DATAFLASH MEMORY MAP
***********************************************************************************************************************/




#endif /* _R_DLMS_STORAGE_MAP_H */
