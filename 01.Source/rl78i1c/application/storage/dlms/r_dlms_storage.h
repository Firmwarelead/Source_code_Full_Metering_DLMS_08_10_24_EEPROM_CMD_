/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_user_interface.h
* Version      : 1.00
* Description  :
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.03.2016
******************************************************************************/

#ifndef _R_DLMS_STORAGE_H
#define _R_DLMS_STORAGE_H


/**
* @defgroup DLMS_APPLICATION_STORAGE
* @brief  DLMS Application Contain the application for DLMS
*         
*
* Detail start here
* @{
*/

/**
 * @brief 
 * 
 * @file r_dlms_storage.h
 * @author Renesas Electronics Corporation 
 * @date 2018-03-12
 */

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "eeprom.h"
#include "r_dlms_format.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define E2PR_OK                                             EPR_OK

#define E2PR_DEVICE_PAGESIZE                                (EPR_DEVICE_PAGESIZE)
#define E2PR_READ(addr,buffer,size)                         EPR_Read(addr,buffer,size)
#define E2PR_WRITE(addr,buffer,size)                        EPR_Write(addr,buffer,size)


#define DFL_READ(addr,buffer,size)                          DATAFLASH_Read(addr,buffer,size)                /* DATAFLASH Read */
#define DFL_WRITE(addr,buffer,size)                         DATAFLASH_Write(addr,buffer,size)               /* DATAFLASH Write */


/******************************************************************************
Typedef definitions
******************************************************************************/

typedef struct tag_DLMS_STORAGE
{
    uint32_t    address;    /* Address of Config on EEPROM */
    uint16_t    length;     /* Length of Config on EEPROM  */
} DLMS_STORAGE;

typedef struct tagDLMS_STORAGE_MAP
{
    uint8_t     	*p_data;    /* Data buffer of Config */
	uint8_t			*p_default;	/* Default value (manufacture value) */
    DLMS_STORAGE	partition;
} DLMS_STORAGE_MAP;

typedef enum tag_STORAGE_ERROR_CODE_t
{
    R_STORAGE_SUCCESS = 0,
    R_STORAGE_FAIL,
} STORAGE_ERROR_CODE_t;

/* EEPROM Storage Header */
typedef struct tag_dlms_storage_header
{
    /* Total: 20 Bytes */
    uint32_t    header_code;                /* (4 bytes) Header Code (EM Formatted Header Code)  */
    uint16_t    usage;                      /* (2 bytes) Usage (number of bytes)                 */
    uint16_t    num_of_dlms_parameter;      /* (2 bytes) Number of DLMS parameter backup bytes   */
    uint16_t    num_of_energy_log;          /* (2 bytes) Number of EM Energy Data Log Record     */
    uint16_t    num_of_tamper_log;          /* (2 bytes) Number of EM Tamper Data Log Record     */
    uint16_t    cur_energy_log_index;       /* (2 bytes) Current Energy Log Index                */
    uint16_t    cur_tamper_log_index;       /* (2 bytes) Current Tamper Log Index                */
} dlms_storage_header_t;


typedef enum tag_STORAGE_ITEM_LIST
{
	SITEM_SERIAL_NUMBER,
	SITEM_YEAR_OF_MANUFACTURE,
	SITEM_TOTAL_PON,
	SITEM_TOTAL_BILLING_PON,
	SITEM_TAMPER_COUNTER,
	SITEM_BILLING_COUNTER,
	SITEM_PROGRAMMING_COUNTER,
	SITEM_LIMITER_THRESHOLD_NORMAL,
	SITEM_LIMITER_THRESHOLD_EMERGENCY,
	SITEM_LIMITER_MIN_OVER_THRESHOLD_DURATION,
	SITEM_LIMITER_MIN_UNDER_THRESHOLD_DURATION,
	SITEM_CONTROL_STATE,
	SITEM_CONTROL_MODE,
	SITEM_RELAY_STATUS,
	SITEM_BLOCKLOAD_CAPTURE_PERIOD,
	SITEM_MDI,
	SITEM_CURRENT_EVENT_CODE,
	SITEM_ESW,
	SITEM_ESWF,
	SITEM_TIMEZONE,
	SITEM_BILLING_SCHEDULE,
	SITEM_IMAGE_SCHEDULE,
	SITEM_TARIFF_SCHEDULE,
	SITEM_PUSH00_SCHEDULE,
	SITEM_PUSH01_SCHEDULE,
	SITEM_BILLING_SCHEDULER_FLAG,
	SITEM_TOD_ACT_TIME,
	SITEM_METER_MODE,
	SITEM_PAYMENT_MODE,
	SITEM_CLOCK_STATUS,
	STORAGE_ITEM_INVOCATION_COUNTER_EK0,
	STORAGE_ITEM_INVOCATION_COUNTER_EK1,
	STORAGE_ITEM_INVOCATION_COUNTER_EK2,
	STORAGE_ITEM_INVOCATION_COUNTER_EK3,
	STORAGE_ITEM_RELAY_PROGESS,
	STORATE_ITEM_CURRENT_LOGGING_TIME,
	STORAGE_ITEM_BILLING_EVENT_FLAG
} STORAGE_ITEM_LIST;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const DLMS_STORAGE_MAP g_storage_table[];
extern const uint16_t g_storage_table_size;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_EEPROM_Write (DLMS_STORAGE storage_map, uint8_t * p_buf);
uint8_t R_DLMS_EEPROM_Read (DLMS_STORAGE storage_map, uint8_t * p_buf);
uint8_t R_DLMS_DataFlash_Write (DLMS_STORAGE *p_storage_map, uint8_t * p_buf);
uint8_t R_DLMS_DataFlash_Read (DLMS_STORAGE *p_storage_map, uint8_t * p_buf);

// uint8_t R_DLMS_Storage_Backup_String_Length(VariantString *p_str, uint32_t address);
// uint8_t R_DLMS_Storage_Restore_String_Length(VariantString *p_str, uint32_t address);

uint8_t R_DLMS_Storage_Write_To_EEPROM_Only(DLMS_STORAGE_MAP * p_item, uint8_t *p_buff);

uint8_t R_DLMS_Storage_RestoreItem(DLMS_STORAGE_MAP *p_item);
uint8_t R_DLMS_Storage_BackupItem(DLMS_STORAGE_MAP *p_item);
uint8_t R_DLMS_Storage_RestoreList(DLMS_STORAGE_MAP * p_list, uint16_t list_size);
uint8_t R_DLMS_Storage_BackupList(DLMS_STORAGE_MAP * p_list, uint8_t list_size);

uint8_t R_DLMS_Storage_IsNull ( uint8_t *p_content, uint16_t length );

uint8_t R_DLMS_Storage_Backup(
	uint32_t			addr,
	uint32_t 			max_storage_size,
	uint8_t				*p_content,
	uint8_t				length
);

uint8_t R_DLMS_Storage_Init(void);
uint8_t R_DLMS_Storage_Format(void);
uint8_t R_DLMS_StorageRestore(void);
uint8_t R_DLMS_StorageBackup(void);

#endif /* _R_DLMS_STORAGE_H */
/** @} */