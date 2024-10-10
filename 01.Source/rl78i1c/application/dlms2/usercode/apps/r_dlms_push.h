/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_user_interface.h
* Version      : 1.02
* Description  :
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.03.2016
******************************************************************************/
// 2018-03-29 New create

#ifndef _R_DLMS_PUSH_H
#define _R_DLMS_PUSH_H

/**
* @defgroup DLMS_APPLICATION_PUSH
* @brief  DLMS Application Contain the application for DLMS
*         
*
* Detail start here
* @{
*/

/**
 * @brief 
 * 
 * @file r_dlms_push.h
 * @author Renesas Electronics Corporation 
 * @date 2018-03-12
 */

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"           /* Macro Driver Definitions */
/* Application */
#include "eeprom.h"                     /* EEPROM MW Layer */
#include "storage.h"                    /* Storage Header File */
#include "config_storage.h"             /* Storage Header File */

#include "r_dlms_date_time.h"
#include "r_dlms_udp_wrapper.h"
/******************************************************************************
Macro definitions
******************************************************************************/

#define R_DLMS_PUSH_ENABLE   (0)

#define PUSH_MAX_WINDOW_SUPPORT		(4)
#define PUSH_OBJECT_NUMBER          5
#define TRIGGER_SOURCE_NUMBER       5

/* For Push trigger ID */
#define PUSH_ID_0           (0)            /* Push ID */
#define PUSH_ID_1           (1)            /* Push ID */
#define PUSH_ID_2           (2)            /* Push ID */
#define PUSH_ID_3           (3)            /* Push ID */
#define PUSH_ID_4           (4)            /* Push ID */
#define PUSH_ID_5           (5)            /* Push ID */

#define WINDOWS_ACTIVE (0)
#define WINDOWS_INACTIVE (1)

#define R_DLMS_Push_DataToHES()				R_DLMS_Push_SetFlag(R_DLMS_PUSH_ID_DATA_TO_HES)
#define R_DLMS_Push_MessageToIHD()			R_DLMS_Push_SetFlag(R_DLMS_PUSH_ID_MESSAGE_TO_IHD)
#define R_DLMS_Push_MessageToHES()			R_DLMS_Push_SetFlag(R_DLMS_PUSH_ID_MESSAGE_TO_HES)
#define R_DLMS_Push_DataToIHD()				R_DLMS_Push_SetFlag(R_DLMS_PUSH_ID_DATA_TO_IHD)
#define R_DLMS_Push_EventToHES()			R_DLMS_Push_SetFlag(R_DLMS_PUSH_ID_EVENT_TO_HES)



#define PUSH_DESTINATION_SERVICE_DEFAULT	        (PUSH_TRANSPORT_SERVICE_TCP)
/*
 * Value of default destination IP address - PUSH_DESTINATION_ADDRESS_DEFAULT
 * Ipv4 format: { a, b, c, d }, 
 *     example: PUSH_DESTINATION_ADDRESS_DEFAULT   { 192, 168 , 0, 5 }
 * Ipv6 format: { a, b, c, d, ..., z}(16 bytes),
 *     example: PUSH_DESTINATION_ADDRESS_DEFAULT   { 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }
 * Note: if destination address change type (IPv4 <-> IPv6), please change PUSH_DESTINATION_ADDRESS_DEFAULT_SIZE value between 4 (IPv4) and 16 (IPv6) 
 */
#define PUSH_DESTINATION_ADDRESS_DEFAULT	        { 192, 168 , 0, 5 }
#define PUSH_DESTINATION_ADDRESS_DEFAULT_SIZE       (4) //IPv4 = (4), Ipv6 = (16)


#define PUSH_DESTINATION_PORT_DEFAULT	            4059
#define PUSH_NUMBER_OF_RETRIES_DEFAULT				3

/* Default push window: 0h-> 20h */
#define PUSH_WINDOW_START_TIME_DEFAULT				{  00,  00,  00,   0xFF,  0xFF, 0xFF,  0xFF }		/* Sec, Min, Hour, Day, Week, Month, Year */
#define PUSH_WINDOW_END_TIME_DEFAULT				{  00,  00,  20,   0xFF,  0xFF, 0xFF,  0xFF }		/* Sec, Min, Hour, Day, Week, Month, Year */


#define R_PUSH_EEPROM_READ(struct_addr_size, p_buf )       ( EPR_Read ( (struct_addr_size).address, (uint8_t *)(p_buf), (struct_addr_size).length) )
#define R_PUSH_EEPROM_WRITE(struct_addr_size, p_buf )      ( EPR_Write( (struct_addr_size).address, (uint8_t *)(p_buf), (struct_addr_size).length) )


/******************************************************************************
Typedef definitions
******************************************************************************/

typedef enum tag_push_action_result
{
	PUSH_RESULT_SUCCESS = 0,
	PUSH_RESULT_FAILED
} push_action_result;

typedef enum tag_push_call_error_code_t
{
    PUSH_CALL_ERR_NONE = 0,									/* No error (success) */
    PUSH_CALL_ERR_CAN_NOT_OPEN_CONNECTION,					/* Can not open connection (TCP port, UDP port) */
    PUSH_CALL_ERR_DATA_NOTIFICATION_SERVICE_NOT_AVAILABLE,	/* Data Notication service is not available */
    PUSH_CALL_ERR_DATA_NOTIFICATION_FAILED,					/* Data Notication invoke failed */
    PUSH_CALL_ERR_PUSH_SETUP_NULL,							/* Push setup is empty for this channel */
    PUSH_CALL_ERR_CONNECTION_TIMEOUT,						/* Open connection timeout */
    PUSH_CALL_ERR_TRANSPORT_SERVICE_UNSUPPORTED,			/* Transport service unsupported */
    PUSH_CALL_ERR_WINDOW_INACTIVE,							/* Communication window is inactive */
    PUSH_CALL_ERR_OTHER,									/* Other */
} push_call_error_code_t;


typedef enum tag_r_dlms_push_id_t
{
	R_DLMS_PUSH_ID_DATA_TO_HES = 0,
	R_DLMS_PUSH_ID_MESSAGE_TO_IHD,
	R_DLMS_PUSH_ID_MESSAGE_TO_HES,
	R_DLMS_PUSH_ID_DATA_TO_IHD,
	R_DLMS_PUSH_ID_EVENT_TO_HES
} r_dlms_push_id_t ;

typedef enum tag_push_transport_service_t
{
	PUSH_TRANSPORT_SERVICE_TCP,
	PUSH_TRANSPORT_SERVICE_UDP,
	PUSH_TRANSPORT_SERVICE_FTP,
	PUSH_TRANSPORT_SERVICE_MTP,
	PUSH_TRANSPORT_SERVICE_SMS,
	PUSH_TRANSPORT_SERVICE_HDLC,
	PUSH_TRANSPORT_SERVICE_M_Bus,
	PUSH_TRANSPORT_SERVICE_ZigBee,
} push_transport_service_t;

typedef enum tag_push_message_type_t
{
	PUSH_MESSAGE_TYPE_A_XDR_ENC_xDLMS_APDU = 0,
	PUSH_MESSAGE_TYPE_XML_ENC_xDLMS_APDU = 1,
} push_message_type_t;

typedef enum tag_push_flag_status_t
{
    PUSH_STATUS_NONE = 0,
    PUSH_STATUS_TRIGGED,
    PUSH_STATUS_RANDOMISATION_START,
    PUSH_STATUS_RETRY,
    PUSH_STATUS_OTHER,  /* Dont change this end line */
} push_flag_status_t;

typedef enum tag_push_dest_format_type_t
{
	HEX_TYPE_IPv4,
	ASCCI_TYPE_IPv4,
	HEX_TYPE_IPv6,
	ASCCI_TYPE_IPv6,
} push_dest_format_type_t;

typedef struct tag_push_ip_address_t
{
	uint8_t		buffer[16];
	uint8_t		size;
	uint8_t		format_type;
	uint16_t	port;
} push_ip_address_t;

typedef union tag_push_dest_address_cnfg_t
{
	push_ip_address_t 	ip_port;
	HdlcAddress			hldc;
} push_dest_address_cnfg_t;

typedef struct tag_push_destination_t
{
    push_transport_service_t	service;
    push_message_type_t			message;
    push_dest_address_cnfg_t	config;
} push_destination_t;

typedef struct tag_push_window_t
{
	R_DLMS_RTC_T start;
	R_DLMS_RTC_T end;
} push_window_t;

typedef struct tag_push_config_t
{
    uint8_t 				state;
    uint8_t 				enable;

    push_destination_t 		destination;

	push_window_t 			*p_window;
	uint8_t 				num_of_window;

    uint16_t 				delay_start;
    uint16_t 				delay_retry;
    uint8_t  				retried_num;

    uint16_t 				delay_start_max;
    uint16_t 				delay_retry_max;
    uint8_t  				retried_num_max;
} push_config_t;


typedef struct tag_PUSH_STORAGE_ADDR_AND_SIZE
{
    uint32_t    address;    /* Address of item on EEPROM */
    uint16_t    length;     /* Allocation size of item on EEPROM  */
} PUSH_STORAGE_ADDR_AND_SIZE;

/******************************************************************************
Variable Externs
******************************************************************************/
extern push_config_t g_push_setup[PUSH_OBJECT_NUMBER];
/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_Push_Convert_StringToDestAddr(
	push_transport_service_t	trans_service,				// [In]
	uint8_t						*p_buff,					// [In]
	uint16_t					length,						// [In]
	push_dest_address_cnfg_t	*config						// [Out]
);

uint8_t R_DLMS_Push_Convert_DestConfigToString(
	push_transport_service_t	trans_service,				// [Input]
	push_dest_address_cnfg_t	*config,					// [Input]
	uint8_t						*p_buff,					// [Out]
	uint16_t					*p_len						// [Out]
);

uint8_t R_DLMS_Push_Backup_DestinationSetup(
	uint8_t		push_channel,
	push_destination_t *p_dest_cfg
);

uint8_t R_DLMS_Push_Restore_DestinationSetup ( 
	uint8_t push_channel,
	push_destination_t *p_dest_cfg
);

uint8_t R_DLMS_Push_Backup_CommWin ( 
    uint8_t		    push_channel,
    push_window_t   *p_push_window,
    uint8_t         num_of_window
 );

uint8_t R_DLMS_Push_Backup_RandomisationStartInterval(
	uint8_t		push_channel,
	uint16_t	value
);

uint8_t R_DLMS_Push_Backup_NumberOfRetry(
	uint8_t		push_channel,
	uint8_t		value
);

uint8_t R_DLMS_Push_Backup_RepetitionDelay(
	uint8_t		push_channel,
	uint16_t    value
);

uint8_t R_DLMS_Push_Restore_CommWin(uint8_t push_channel);
uint8_t R_DLMS_Push_Restore_NumberOfRetry(
	uint8_t		push_channel
);

void R_DLMS_Push_Enable(uint8_t push_channel);
push_config_t * R_DLMS_Push_GetConfig ( uint8_t push_channel );

void R_DLMS_Push_SetFlag(uint8_t push_id);

push_call_error_code_t R_DLMS_Push_ServiceCall(uint8_t push_channel);
uint8_t R_DLMS_Push_CheckWindow(push_config_t *p_push_setup);

void R_DLMS_Push_Format(void);
void R_DLMS_Push_Init(void);
void R_DLMS_Push_PollingProcessing(void);

uint8_t R_DLMS_Push_Set_RandomisationStartInterval(uint8_t push_channel, uint16_t value);
uint8_t R_DLMS_Push_Set_NumberOfRetry(uint8_t push_channel, uint8_t value);
uint8_t R_DLMS_Push_Set_RepetitionDelay(uint8_t push_channel, uint16_t value);
#endif /* _R_DLMS_PUSH_H */
/** @} */
