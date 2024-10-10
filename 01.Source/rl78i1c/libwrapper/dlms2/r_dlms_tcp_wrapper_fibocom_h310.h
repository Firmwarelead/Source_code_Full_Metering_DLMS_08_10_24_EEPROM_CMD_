/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_tcp_wrapper_fibocom_h310.h
* Version      : 1.00
* Description  : TCP Wrapper Interface for H310
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 29.05.2019
******************************************************************************/

#ifndef _R_DLMS_TCP_WRAPPER_FIBOCOM_H310_H
#define _R_DLMS_TCP_WRAPPER_FIBOCOM_H310_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_rtc.h"

#include "typedef.h"
#include "r_dlms_tcp_wrapper.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/* Config for Gsm Modem */
#define		TCP_DEVICE_IP_CONFIGURATION					(1)			/* 0 (IPv4), 1 (IPv6) */
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

#if TCP_DEVICE_AT_COMMAND_RETRIES_MAX == 0 || \
    TCP_DEVICE_AT_SCRIPT_RETRIES_MAX == 0
#error "Retries time need to be larger than 0"
#endif

/* AT Reply */
#define		TCP_DEVICE_REPLY_BUFFER_MAX_LENGTH			(128)		/* Max length to receive the reply & unsolicted event */

/* AT Event, +<prefix>: <content>\r\n */
#define		TCP_DEVICE_AT_EVENT_PREFIX_LENGTH			(16)		/* Length for prefix of event */
#define		TCP_DEVICE_AT_EVENT_CONTENT_LENGTH			(96)		/* Length for content of event */
#define		TCP_DEVICE_AT_EVENT_STATE_PLUS				(0)			/* + */
#define		TCP_DEVICE_AT_EVENT_STATE_PREFIX			(1)			/* prefix */
#define		TCP_DEVICE_AT_EVENT_STATE_CONTENT			(2)			/* content */

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct tagTimeoutChannel		TimeoutChannel;
typedef enum   tagAtCmdResult			AtCmdResult;
typedef enum   tagAtCmdState			AtCmdState;
typedef struct tagAtReply				AtReply;
typedef struct tagAtEvent				AtEvent;
typedef struct tagAtCommand				AtCommand;
typedef struct tagAtRunner				AtRunner;

typedef enum tagGsmModemState			GsmModemState;
typedef enum tagGsmModemSocket2State	GsmModemSocket2State;
typedef struct tagGsmCpin				GsmCpin;
typedef struct tagGsmCsq				GsmCsq;
typedef struct tagGsmCreg				GsmCreg;
typedef struct tagGsmCgreg				GsmCgreg;
typedef struct tagGsmMipcall			GsmMipcall;
typedef struct tagGsmMipodm				GsmMipodm;
typedef struct tagGsmMipstat			GsmMipstat;
typedef struct tagGsmCgqMin				GsmCgqMin;
typedef struct tagGsmCgqReq				GsmCgqReq;
typedef struct tagGsmCops				GsmCops;
typedef struct tagGsmCgatt				GsmCgatt;
typedef struct tagGsmCgdcont			GsmCgdcont;
typedef struct tagGsmMsdns              GsmMsdns;
typedef struct tagGsmCced               GsmCced;
typedef struct tagGsmCmee               GsmCmee;
typedef enum tagGsmEventType			GsmEventType;
typedef enum tagGsmSimStatus            GsmSimStatus;
typedef union tagGsmEventOutput			GsmEventOutput;
typedef struct tagGsmModemSetting		GsmModemSetting;
typedef struct tagGsmModemInfo			GsmModemInfo;
typedef struct tagGsmModemDiag			GsmModemDiag;
typedef struct tagGsmModem				GsmModem;

typedef uint8_t(*fp_reply_handler_t)(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
typedef uint16_t(*fp_cmd_input_t)(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length);

struct tagTimeoutChannel
{
	uint16_t	initial;
	uint16_t	count;
	uint16_t	enable;
};

enum tagGsmSimStatus
{
    GSM_MODEM_SIM_FAULT,
    GSM_MODEM_SIM_READY,
    GSM_MODEM_SIM_PIN,
    GSM_MODEM_SIM_PUK,
};

/* To scan +CPIN: output event */
struct tagGsmCpin
{
    GsmSimStatus    status;
};

/* To scan +CSQ: output event */
struct tagGsmCsq
{
	uint8_t		rssi;			/* Mandatory */
	uint8_t		ber;			/* Mandatory */
};

/* To scan +CREG: output event */
struct tagGsmCreg
{
	uint8_t		n;				/* Mandatory */
	uint8_t		stat;			/* Mandatory */
	uint8_t		lac[2];			/* Optional */
	uint8_t		ci[4];			/* Optional */
	uint8_t		AcT;			/* Optional */
};

/* To scan +CGREG: output event */
struct tagGsmCgreg
{
    uint8_t		n;				/* Mandatory */
    uint8_t		stat;			/* Mandatory */
    uint16_t	lac;			/* Optional */
    uint32_t	ci;			    /* Optional */
    uint8_t		AcT;			/* Optional */
    uint8_t		rac;			/* Optional */
};

/* To scan +MIPCALL: output event */
struct tagGsmMipcall
{
	uint8_t		status;					/* Mandatory */
	uint8_t		local_ip_buffer[16];	/* Mandatory (when execute) / Optional (When read) */
};

/* To scan +MIPODM: output event */
struct tagGsmMipodm
{
	uint8_t		socket_id;				/* Mandatory */
	uint8_t		state;					/* Mandatory */
	uint8_t		remote_ip_buffer[16];	/* Optional */
	uint16_t	remote_port;			/* Optional */
};

/* To scan +MIPSTAT: output event */
struct tagGsmMipstat
{
	uint8_t		socket_id;			/* Mandatory */
	uint8_t		n;					/* Mandatory */
	uint16_t	ack_bytes;			/* Optional */
};

/* To scan +CGQMIN: output event */
struct tagGsmCgqMin {
	uint8_t		cid;
	uint8_t		precedence;
	uint8_t		delay;
	uint8_t		reliability;
	uint8_t		peak;
	uint8_t		mean;
};

/* To scan +CGQREQ: output event */
struct tagGsmCgqReq {
	uint8_t		cid;
	uint8_t		precedence;
	uint8_t		delay;
	uint8_t		reliability;
	uint8_t		peak;
	uint8_t		mean;
};

/* To scan +COPS: output event */
struct tagGsmCops
{
	uint8_t	mode;
	uint8_t	format;
	uint8_t	operator[TCP_DEVICE_MAX_OPERATOR_NAME_LENGTH];
	uint8_t	act;
};

/* To scan +CGATT: output event */
struct tagGsmCgatt
{
	uint8_t	state;
};

/* To scan +CGDCONT: output event */
struct tagGsmCgdcont
{
	uint8_t cid;
	uint8_t pdp_type[8];
	uint8_t apn[TCP_DEVICE_MAX_APN_NAME_LENGTH];
	uint8_t	pdp_addr[TCP_DEVICE_MAX_PDP_ADDRESS_LENGTH];
	uint8_t d_comp;
	uint8_t h_comp;
};

/* To scan +MSDNS: output event */
struct tagGsmMsdns
{
    uint8_t primary_dns_address[16];
    uint8_t secondary_dns_address[16];
};

/* To scan +CME ERROR: error report */
struct tagGsmCmee
{
    uint16_t code;
};

/* To scan +CCED: output event */
struct tagGsmCced
{
    uint16_t mcc;
    uint16_t mnc;
    uint16_t lac;
    uint32_t cid;
    uint32_t dl_uarfcn;
    uint16_t psc;
    uint16_t rscp;
    uint16_t ecn0;
    uint16_t rxlev;
    uint16_t s_qual;
    uint16_t s_intrasearch;
    uint16_t s_intersearch;
    uint16_t s_search_rat;
    uint16_t activecellcounter;
    uint16_t ncellgsmcounter;
    uint16_t sys_mode;
};

/* GSM Event Type */
enum tagGsmEventType
{
	GSM_MODEM_EVENT_NONE = 0,
	GSM_MODEM_EVENT_CPIN,
	GSM_MODEM_EVENT_CSQ,
	GSM_MODEM_EVENT_CREG,
    GSM_MODEM_EVENT_CGREG,
	GSM_MODEM_EVENT_MIPCALL,
	GSM_MODEM_EVENT_MIPODM,
	GSM_MODEM_EVENT_MIPSTAT,
	GSM_MODEM_EVENT_CGQMIN,
	GSM_MODEM_EVENT_CGQREQ,
	GSM_MODEM_EVENT_COPS,
	GSM_MODEM_EVENT_CGATT,
	GSM_MODEM_EVENT_CGDCONT,
    GSM_MODEM_EVENT_MSDNS,
    GSM_MODEM_EVENT_CMEE,
    GSM_MODEM_EVENT_SIM_DROP,
};

/* Union for all kind of event output */
union tagGsmEventOutput
{
	GsmCpin		CPIN;
	GsmCsq		CSQ;
	GsmCreg		CREG;
    GsmCgreg	CGREG;
	GsmMipcall	MIPCALL;
	GsmMipodm	MIPODM;
	GsmMipstat	MIPSTAT;
	GsmCgqMin	CGQMIN;
	GsmCgqReq	CGQREQ;
	GsmCops		COPS;
	GsmCgatt	CGATT;
	GsmCgdcont	CGDCONT;
    GsmMsdns    MSDNS;
    GsmCmee     CMEE;
};

enum tagAtCmdResult
{
	AT_CMD_RESULT_OK = 0,			/* AT command has reply as expectation */
	AT_CMD_RESULT_WAIT_REPLY,		/* AT command waiting for reply */
	AT_CMD_RESULT_TIMED_OUT,		/* AT command timed out, error */
};

enum tagAtCmdState
{
	AT_CMD_START = 0,				/* AT command execution at start point */
	AT_CMD_SENT,					/* AT command has been sent and start waiting reply with timeout */
	AT_CMD_TIMEOUT,					/* AT command timed out (no reply) */
	AT_CMD_REPLY_AS_EXPECTED,		/* AT command has reply as expectation */
	AT_CMD_DELAY_AFTER_CMD,			/* AT command start delay after execution of a cmd */
	AT_CMD_EMERGENCY_EXIT			/* AT command need to exit all state as emergency request from power management */
};

struct tagAtReply
{
	uint8_t		buffer[TCP_DEVICE_REPLY_BUFFER_MAX_LENGTH + 1];			/* Buffer to store the reply, \0 terminate string */
	uint16_t	count;													/* Current usage on buffer */
	uint8_t		timeout;												/* Indicates that timeout happen or not (for async operation) */
	uint8_t		active;													/* Indicates that waiting reply is needed to run or not */
	uint8_t		reply_ok;												/* Indicates that AT command has reply and ok */
	AtCmdState	state;													/* AT Command State */
};

struct tagAtEvent
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
};

struct tagAtCommand
{
	uint8_t				*p_cmd_str;				/* Command input string */
	fp_cmd_input_t		fp_cmd_input;			/* Command input string (use in combination with p_cmd_str for dynamic input args) */
	uint8_t				*p_expected_reply;		/* Expected reply msg */
	uint16_t			timeout;				/* Timeout */
	fp_reply_handler_t	fp_reply_handler;		/* Handler of the reply message if need more check or get output */
	uint16_t			delay;					/* Delay after send out command */
};

struct tagAtRunner
{
	const AtCommand	*p_commands;				/* List of command to run */
	uint16_t		length;						/* Length of the command list */
	uint8_t			reboot;						/* Number of reboot count of script before reboot the whole Gsm Device */
	uint8_t			retry;						/* Number of retry of a command before jump back to start index (0) */
	uint16_t		index;						/* Current index to run the command on command list */
};

enum tagGsmModemState
{
	GSM_MODEM_STATE_UNINITIALIZED = 0,			/* Modem not initialized */
	GSM_MODEM_STATE_INITIALIZED,				/* Modem is initialized by R_TCP_DEVICE_Init() */
    GSM_MODEM_STATE_CHECK_USIM,					/* Modem checking if USIM is inserted */
    GSM_MODEM_STATE_CHECK_GSM_COVERAGE,			/* Modem checking if modem in GSM coverage */
    GSM_MODEM_STATE_CHECK_NETWORK_REGISTRATION,	/* Modem checking for correct network registration */
    GSM_MODEM_STATE_ESTABLISH_CONNECTION,	    /* Establish wireless connection */
    GSM_MODEM_STATE_BOOT_UP_QUERY_INFO,			/* Modem query information & setting after boot up */
	GSM_MODEM_STATE_START_LISTEN_SOCKET1,		/* Modem start script to listen TCP connection on Socket 1 */
	GSM_MODEM_STATE_TCP_LISTENING,				/* Modem is TCP's listening by AT+MIPODM */
	GSM_MODEM_STATE_TCP_REMOTE_CONNECTED,		/* Modem is TCP's remote connected */
	GSM_MODEM_STATE_TCP_REMOTE_DISCONNECTED,	/* Modem is TCP's remote disconnected */
};

enum tagGsmModemSocket2State
{
	GSM_MODEM_SOCKET2_UNINITIALIZED = 0,		/* Modem has TCP socket 2 uninitialized */
	GSM_MODEM_SOCKET2_CLOSED,					/* Modem has TCP socket 2 closed */
	GSM_MODEM_SOCKET2_OPENED,					/* Modem has TCP socket 2 closed */
};

/* Gsm Modem Setting */
struct tagGsmModemSetting
{
	uint8_t			apn_name[TCP_DEVICE_MAX_APN_NAME_LENGTH+1];			/* APN name */
	uint8_t			pin[TCP_DEVICE_MAX_PIN_CODE_LENGTH+1];				/* Pin code */
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
};

/* Gsm Modem Info */
struct tagGsmModemInfo
{
	uint8_t		operator[TCP_DEVICE_MAX_OPERATOR_NAME_LENGTH+1];	/* Operator name */
	uint8_t		network_status;										/* Creg network status */
	uint8_t		cs_attachment;										/* TODO: Check AT command of H310 to get CS attachment */
	uint8_t		ps_status;											/* PS status */
	struct {
		uint32_t	cell_id;
		uint16_t	location_id;
		uint8_t		signal_quality;
		uint8_t		ber;
		uint16_t	mcc;
		uint16_t	mnc;
		uint32_t	channel_number;
	} cell_info;										/* TODO: Check AT command of H310 to get data */
	struct {
		struct {
			uint32_t	cell_id;
			uint8_t		signal_quality;
		} items[5];
		uint16_t	length;
	} adjacent_cells;									/* TODO: Check AT command of H310 to get data */
	rtc_counter_value_t	capture_time;						/* Captured time of all information, RTC Driver Calendar Date/Time */
};

/* Gsm Diagnostic */
struct tagGsmModemDiag
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
};

/* Gsm Modem */
struct tagGsmModem
{
	uint8_t					test_id;				/* Trigger to do some tests */
	void					*ptr;					/* Generic pointer for sharing of AT command input */
	uint8_t					pushing_lastgasp;		/* Indicates that pushing is on-progress, no emergency exit */
    
    GsmModemDiag            diag;
	GsmModemState			state;					/* Current state of Gsm Modem */
	GsmModemSocket2State	socket2_state;			/* Current socket 2 state of Gsm Modem */

	AtRunner				boot;					/* Runner to boot GSM Modem */
    AtRunner				sim;				    /* Runner to check SIM availability */
    AtRunner				signal;				    /* Runner to check GSM coverage */
    AtRunner				net_reg;				/* Runner to check network registration */
    AtRunner				connect;				/* Runner to establish wireless connection on GSM modem */
	AtRunner				listen;					/* Runner to change GSM Modem to listen again */
	AtRunner				query;					/* Runner to query Gsm Modem information */

	GsmModemSetting			setting;				/* Gsm Modem Setting */
	GsmModemInfo			info;					/* Gsm Modem Information */

	uint8_t					periodic_job;			/* Trigger (TRUE/FALSE) for periodic jobs (on R_TCP_DEVICE_Polling) */

	struct {
		uint16_t			port_number;
		IpAddress			ip;
		uint8_t				ip_buffer[TCP_DEVICE_IP_SIZE];
	} local;										/* Local IP & port number */

	struct {
		uint16_t			port_number;
		IpAddress			ip;
		uint8_t				ip_buffer[TCP_DEVICE_IP_SIZE];
	} remote;										/* Remote IP & port number */

    struct {
        uint8_t				primary[TCP_DEVICE_IP_SIZE];
        uint8_t				secondary[TCP_DEVICE_IP_SIZE];
    } dns_server;									/* DNS server IP address */
};

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

#endif /* _R_DLMS_TCP_WRAPPER_FIBOCOM_H310_H */

