/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_tcp_wrapper_neoway_wm620.h
* Version      : 1.00
* Description  : TCP Wrapper Interface for Neoway WM620
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 29.05.2019
******************************************************************************/

#ifndef _R_DLMS_TCP_WRAPPER_NEOWAY_WM620_H
#define _R_DLMS_TCP_WRAPPER_NEOWAY_WM620_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"

#include "typedef.h"
#include "r_dlms_tcp_wrapper.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/* Config for Gsm Modem */
#define		TCP_DEVICE_IP_CONFIGURATION					(0)			/* 0 (IPv4), 1 (IPv6) */
#if TCP_DEVICE_IP_CONFIGURATION == 0
#define		TCP_DEVICE_IP_SIZE							(4)
#elif TCP_DEVICE_IP_CONFIGURATION == 1
#define		TCP_DEVICE_IP_SIZE							(16)
#endif
#define		TCP_DEVICE_DEFAULT_APN_NAME					"m3-world"	/* Default APN Name. Vinaphone APN name */
#define		TCP_DEVICE_PERIODIC_CHECK_INTERVAL_TIME		(120)		/* Interval time (s) to do periodic check and sync info with Gsm Modem. 2 minutes */
#define		TCP_DEVICE_MODEM_MOUNTED_CONFIRM_TIME		(2)			/* Time (s) to confirm modem mounted on socket. 2 seconds */
#define		TCP_DEVICE_DEFAULT_STRING_LENGTH			(128)		/* Default string length for vars on Gsm Modem */
#define		TCP_DEVICE_EVENT_INTERFRAME_TIMEOUT			(100)		/* Interframe timeout to reset unsolicted event detector */
#define		TCP_DEVICE_AT_COMMAND_RETRIES_MAX			(10)		/* Max retries before reset back to first index */
#define		TCP_DEVICE_AT_SCRIPT_RETRIES_MAX			(2)			/* Max retries of whole script before Gsm Device reboot */
#define     TCP_DEVICE_MAX_APN_NAME_LENGTH              (32)        /* Max length of APN name: fixed 32bytes length */
#define     TCP_DEVICE_MAX_PIN_CODE_LENGTH              (12)        /* Max length of PIN code: according to ISO 9564-1*/
#define     TCP_DEVICE_MAX_OPERATOR_NAME_LENGTH         (16)        /* Max length of operator name: according to 3GPP TS 27.007 */
#define     TCP_DEVICE_MAX_PDP_ADDRESS_LENGTH           (39)        /* Max length of PDP address: in case of IPv6 address */
#define     TCP_DEVICE_MAX_SOCKET                       (6)         /* Max socket supported by modem */
#define		TCP_DEVICE_DELAY_COMMAND_AFTER_REBOOT		(7)		    /* Time (s) delay to send AT command after reboot */
#define		TCP_DEVICE_INACTIVE_SOCKET_TIMEOUT		    (20)		/* Time (s) for socket timeout */

#if TCP_DEVICE_AT_COMMAND_RETRIES_MAX == 0 || \
    TCP_DEVICE_AT_SCRIPT_RETRIES_MAX == 0
#error "Retries time need to be larger than 0"
#endif

/* AT Reply */
#define		TCP_DEVICE_REPLY_BUFFER_MAX_LENGTH			(128)		/* Max length to receive the reply & unsolicted event */

/* AT Event, +<prefix>: <content>\r\n */
#define		TCP_DEVICE_AT_EVENT_PREFIX_LENGTH			(32)		/* Length for prefix of event */
#define		TCP_DEVICE_AT_EVENT_CONTENT_LENGTH			(96)		/* Length for content of event */
#define		TCP_DEVICE_AT_EVENT_STATE_PLUS				(0)			/* + */
#define		TCP_DEVICE_AT_EVENT_STATE_PREFIX			(1)			/* prefix */
#define		TCP_DEVICE_AT_EVENT_STATE_CONTENT			(2)			/* content */

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct tagGsmApnName
{
	uint8_t data[TCP_DEVICE_MAX_APN_NAME_LENGTH];
    uint16_t size;
} GsmApnName;
typedef struct tagGsmOperatorName
{
	uint8_t data[TCP_DEVICE_MAX_OPERATOR_NAME_LENGTH];
    uint16_t size;
} GsmOperatorName;

typedef struct tagTimeoutChannel
{
	uint16_t	initial;
	uint16_t	count;
	uint16_t	enable;
} TimeoutChannel;

typedef enum tagGsmSimStatus
{
    GSM_MODEM_SIM_FAULT,
    GSM_MODEM_SIM_READY,
    GSM_MODEM_SIM_PIN,
    GSM_MODEM_SIM_PUK,
} GsmSimStatus;

/* To scan +CPIN: output event */
typedef struct tagGsmCpin
{
    GsmSimStatus    status;
} GsmCpin;

/* To scan +CSQ: output event */
typedef struct tagGsmCsq
{
	uint8_t		rssi;			/* Mandatory */
	uint8_t		ber;			/* Mandatory */
} GsmCsq;

/* To scan +CGREG: output event */
typedef struct tagGsmCgreg
{
    uint8_t		n;				/* Mandatory */
    uint8_t		stat;			/* Mandatory */
    uint16_t	lac;			/* Optional */
    uint32_t	ci;			    /* Optional */
    // uint8_t		AcT;			/* Optional */
    // uint8_t		rac;			/* Optional */
} GsmCgreg;

/* To scan +XIIC: output event */
typedef struct tagGsmXiic
{
	uint8_t		status;					/* Mandatory */
	uint8_t		local_ip_buffer[16];	/* Mandatory (when established) / Optional (When not established) */
} GsmXiic;

/* To scan +PPPSTATUS: output event */
typedef struct tagGsmPppStatus
{
	uint8_t		is_closed;				/* Mandatory */
} GsmPppStatus;

typedef struct tagGsmTcpSetup
{
	uint8_t		socket_id;				/* Mandatory (for OK or FAIL) */
    uint8_t     is_error;               /* Mandatory when ERROR */
    uint8_t     is_socket_failed;       /* Mandatory when socket ID available */
} GsmTcpSetup;

typedef struct tagGsmTcpClose
{
	uint8_t		socket_id;				/* Mandatory */
    uint8_t     is_error;               /* Mandatory */
    uint8_t     is_remote_close;        /* Optional, if remote close connection instead from local */
} GsmTcpClose;

typedef struct tagGsmConnect
{
	uint8_t		socket_id;				/* Mandatory */
	uint8_t		remote_ip_buffer[16];	/* Optional */
} GsmConnect;

typedef struct tagGsmCloseClient
{
	uint8_t		socket_id;				/* Mandatory */
} GsmCloseClient;

typedef struct tagGsmTcpRecvs
{
	uint8_t		socket_id;				/* Mandatory */
    uint16_t	length;				    /* Mandatory */
} GsmTcpRecvs;

/* To scan +COPS: output event */
typedef struct tagGsmCops
{
	uint8_t	mode;
	uint8_t	format;
    GsmOperatorName operator;
	uint8_t	act;
    uint16_t mcc;
    uint16_t mnc;
} GsmCops;

/* To scan +ERAT: output event */
typedef struct tagGsmErat
{
	uint8_t	current_rat;
	uint8_t	gprs_status;
    uint8_t	rat_mode;
    uint8_t	prefer_rat;
} GsmErat;

/* To scan +CME ERROR: error report */
typedef struct tagGsmCmee
{
    uint16_t code;
} GsmCmee;

/* GSM Event Type */
typedef enum tagGsmEventType
{
	GSM_MODEM_EVENT_NONE = 0,
	GSM_MODEM_EVENT_CPIN,
	GSM_MODEM_EVENT_CSQ,
    GSM_MODEM_EVENT_CGREG,
	GSM_MODEM_EVENT_COPS,
	GSM_MODEM_EVENT_ERAT,
	GSM_MODEM_EVENT_CGATT,
	GSM_MODEM_EVENT_CGDCONT,
    GSM_MODEM_EVENT_CMEE,
    GSM_MODEM_EVENT_SIM_DROP,
    GSM_MODEM_EVENT_XIIC,
    GSM_MODEM_EVENT_PPPSTATUS,
    GSM_MODEM_EVENT_TCPSETUP,
    GSM_MODEM_EVENT_TCPCLOSE,
    GSM_MODEM_EVENT_CONNECT,
    GSM_MODEM_EVENT_CLOSECLIENT,
    GSM_MODEM_EVENT_TCPSEND,
    GSM_MODEM_EVENT_TCPSENDS,
    GSM_MODEM_EVENT_TCPRECV,
    GSM_MODEM_EVENT_TCPRECVS,
} GsmEventType;

/* Union for all kind of event output */
typedef union tagGsmEventOutput
{
	GsmCpin		    CPIN;
	GsmCsq		    CSQ;
    GsmCgreg	    CGREG;
	GsmCops		    COPS;
    GsmErat         ERAT;
    GsmCmee         CMEE;
    GsmXiic         XIIC;
    GsmPppStatus    PPPSTATUS;
    GsmTcpSetup     TCPSETUP;
    GsmTcpClose     TCPCLOSE;
    GsmConnect      CONNECT;
    GsmCloseClient  CLOSECLIENT; 
    GsmTcpRecvs     TCPRECVS;
} GsmEventOutput;

typedef enum tagAtCmdResult
{
	AT_CMD_RESULT_OK = 0,			/* AT command has reply as expectation */
	AT_CMD_RESULT_WAIT_REPLY,		/* AT command waiting for reply */
	AT_CMD_RESULT_TIMED_OUT,		/* AT command timed out, error */
} AtCmdResult;

typedef enum tagAtCmdState
{
	AT_CMD_START = 0,				/* AT command execution at start point */
	AT_CMD_SENT,					/* AT command has been sent and start waiting reply with timeout */
	AT_CMD_TIMEOUT,					/* AT command timed out (no reply) */
	AT_CMD_REPLY_AS_EXPECTED,		/* AT command has reply as expectation */
	AT_CMD_DELAY_AFTER_CMD,			/* AT command start delay after execution of a cmd */
	AT_CMD_EMERGENCY_EXIT			/* AT command need to exit all state as emergency request from power management */
} AtCmdState;

typedef struct tagAtReply
{
	uint8_t		buffer[TCP_DEVICE_REPLY_BUFFER_MAX_LENGTH + 1];			/* Buffer to store the reply, \0 terminate string */
	uint16_t	count;													/* Current usage on buffer */
	uint8_t		timeout;												/* Indicates that timeout happen or not (for async operation) */
	uint8_t		active;													/* Indicates that waiting reply is needed to run or not */
	uint8_t		reply_ok;												/* Indicates that AT command has reply and ok */
	AtCmdState	state;													/* AT Command State */
} AtReply;

typedef struct tagAtEvent
{
	uint8_t			received;										/* Inidicate that an unsolicted event is received */
	GsmEventType	type;											/* Type of event when received = TRUE and related handler parse success */
	uint8_t			state;											/* 0(+), 1(prefix:), 2(content), 3(\n) */
	struct {
		uint8_t		buffer[TCP_DEVICE_AT_EVENT_PREFIX_LENGTH + 1];	/* buffer of prefix (opcode), \0 terminate string*/
		uint16_t	count;											/* current number of bytes used on prefix buffer */
	} prefix;														/* Prefix, has '+' and ':' */
	struct {
		uint8_t		buffer[TCP_DEVICE_AT_EVENT_CONTENT_LENGTH + 1];	/* buffer of content, \0 terminate string*/
		uint16_t	count;											/* current number of bytes used on content buffer */
	} content;														/* Content */
	GsmEventOutput	data;											/* Data output of the event, after check & parse */
} AtEvent;

/* Forward declaration of GsmModem to use as pointer within below function pointers */
struct tagGsmModem;
typedef uint8_t(*fp_reply_handler_t)(struct tagGsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
typedef uint16_t(*fp_cmd_input_t)(struct tagGsmModem *p_modem, uint8_t *p_input_args, uint16_t length);

typedef struct tagAtCommand
{
	uint8_t				*p_cmd_str;				/* Command input string */
	fp_cmd_input_t		fp_cmd_input;			/* Command input string (use in combination with p_cmd_str for dynamic input args) */
	uint8_t				*p_expected_reply;		/* Expected reply msg */
	uint16_t			timeout;				/* Timeout */
	fp_reply_handler_t	fp_reply_handler;		/* Handler of the reply message if need more check or get output */
	uint16_t			delay;					/* Delay after send out command */
} AtCommand;

typedef struct tagAtRunner
{
	const AtCommand	*p_commands;				/* List of command to run */
	uint16_t		length;						/* Length of the command list */
	uint8_t			reboot;						/* Number of reboot count of script before reboot the whole Gsm Device */
	uint8_t			retry;						/* Number of retry of a command before jump back to start index (0) */
	uint16_t		index;						/* Current index to run the command on command list */
} AtRunner;

typedef enum tagGsmModemState
{
	GSM_MODEM_STATE_UNINITIALIZED = 0,			/* Modem not initialized */
	GSM_MODEM_STATE_INITIALIZED,				/* Modem is initialized by R_TCP_DEVICE_Init() */
    GSM_MODEM_STATE_CHECK_USIM,					/* Modem checking if USIM is inserted */
    GSM_MODEM_STATE_CHECK_GSM_COVERAGE,			/* Modem checking if modem in GSM coverage */
    GSM_MODEM_STATE_CHECK_NETWORK_REGISTRATION,	/* Modem checking for correct network registration */
    GSM_MODEM_STATE_ESTABLISH_CONNECTION,	    /* Establish wireless connection */
    GSM_MODEM_STATE_BOOT_UP_QUERY_INFO,			/* Modem query information & setting after boot up */
	GSM_MODEM_STATE_START_LISTEN_SOCKET,		/* Modem start script to listen TCP connection on Socket 1 */
	GSM_MODEM_STATE_READY,				        /* Modem is TCP's listening by AT+TCPLISTEN */
} GsmModemState;

typedef enum tagGsmModemSocketState
{
	GSM_MODEM_SOCKET_CLOSED,					/* Modem has TCP socket closed */
	GSM_MODEM_SOCKET_OPENED,					/* Modem has TCP socket closed */
    GSM_MODEM_SOCKET_RECEIVING_PDU,
} GsmModemSocketState;

/* Gsm Modem Setting */
typedef struct tagGsmModemSetting
{
	GsmApnName          apn_name;			        /* APN name */
	struct {
		struct {
			uint8_t		precedence;
			uint8_t		delay;
			uint8_t		reliability;
			uint8_t		peak;
			uint8_t		mean;
		} min;
		struct {
			uint8_t		precedence;
			uint8_t		delay;
			uint8_t		reliability;
			uint8_t		peak;
			uint8_t		mean;
		} req;
	}	quality_of_service;
} GsmModemSetting;

/* Gsm Modem Info */
typedef struct tagGsmModemInfo
{
	GsmOperatorName operator;	                            /* Operator name */
	uint8_t		    network_status;							/* Creg network status */
	uint8_t		    cs_attachment;							/* CS Attachment */
	uint8_t		    ps_status;								/* PS status */
	struct {
		uint32_t	cell_id;
		uint16_t	location_id;
		uint8_t		signal_quality;
		uint8_t		ber;
		uint16_t	mcc;
		uint16_t	mnc;
		uint32_t	channel_number;
	} cell_info;										            
	struct {
		struct {
			uint32_t	cell_id;
			uint8_t		signal_quality;
		} items[5];
		uint16_t	length;
	} adjacent_cells;
	rtc_counter_value_t	capture_time;						/* Captured time of all information, RTC Driver Calendar Date/Time */
} GsmModemInfo;

/* Gsm Diagnostic */
typedef struct tagGsmModemDiag
{
    uint16_t modem_mounted_count;
    uint8_t modem_mounted;
    uint8_t modem_reply_failure;
    uint8_t sim_inserted;
    uint8_t sim_good;
    uint8_t no_gsm_coverage;
    uint8_t gprs_registration_failure;
    uint8_t gprs_registration_denied;
    uint8_t no_apn_configured;
    uint8_t gprs_connection_drop;
    uint8_t remote_destination_invalid;
    uint8_t remote_destination_unreachable;
    uint8_t remote_data_sending_failure;
} GsmModemDiag;

/* Gsm Modem */
typedef struct tagGsmModem
{
	uint8_t					pushing_lastgasp;		/* Indicates that pushing is on-progress, no emergency exit */
    uint16_t                reboot_delay;

    GsmModemDiag            diag;
	GsmModemState			state;					/* Current state of Gsm Modem */

    AtRunner				boot;					/* Runner to boot GSM Modem */
    AtRunner				sim;				    /* Runner to check SIM availability */
    AtRunner				signal;				    /* Runner to check GSM coverage */
    AtRunner				net_reg;				/* Runner to check network registration */
    AtRunner				connect;				/* Runner to establish wireless connection on GSM modem */
	AtRunner				listen;					/* Runner to change GSM Modem to listen again */
	AtRunner				query;					/* Runner to query Gsm Modem information */
	AtRunner				close_connect;			/* Runner to close time out socket */

	GsmModemSetting			setting;				/* Gsm Modem Setting */
	GsmModemInfo			info;					/* Gsm Modem Information */

	uint8_t					periodic_job;			/* Trigger (TRUE/FALSE) for periodic jobs (on R_TCP_DEVICE_Polling) */

	struct {
		uint16_t			port_number;
		IpAddress			ip;
		uint8_t				ip_buffer[16];
	} local;										/* Local IP & port number */

	struct {
		uint16_t			port_number;
		IpAddress			ip;
		uint8_t				ip_buffer[16];

		uint8_t				is_outbound;
        uint8_t             is_timeout;
        TimeoutChannel      timeout;
        
	} remote[TCP_DEVICE_MAX_SOCKET];				/* Remote IP & port number (Neoway WM620 max 6 sockets) */

    /* Shared status for remote */
    uint8_t                 receiving_socket_id;    /* Async parsing of +TCPRECV(S) current socket ID */
    uint16_t 			    receiving_remain_bytes; /* Async parsing of +TCPRECV(S) remaining data length */
    
    struct {
        uint8_t				primary[16];
        uint8_t				secondary[16];
    } dns_server;									/* DNS server IP address */
} GsmModem;

/******************************************************************************
Variable Externs
******************************************************************************/
extern GsmModem				g_tcp_gsm_modem;

/******************************************************************************
Functions Prototypes
******************************************************************************/
void R_TCP_DEVICE_RebootGsmModem(void);
void R_TCP_DEVICE_FirstBreathEventHappenCallback(void);
uint16_t R_TCP_WRP_GetDnsServerIpAddressBuffer(uint8_t ** ip_address, uint8_t is_primary);

#endif /* _R_DLMS_TCP_WRAPPER_NEOWAY_WM620_H */

