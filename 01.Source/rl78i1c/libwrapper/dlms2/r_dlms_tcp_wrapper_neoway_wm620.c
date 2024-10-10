/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this
* software and to discontinue the availability of this software.
* By using this software, you agree to the additional terms and
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************
* File Name    : r_dlms_tcp_wrapper_neoway_wm620.c
* Version      : 1.00
* Device(s)    : Neoway WM620
* Tool-Chain   : CCRL
* H/W Platform : 
* Description  : TCP wrapper layer of DLMS Library on 3G Modem Neoway WM620
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.05.2016
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"
#include "r_cg_wdt.h"
#include "r_cg_rtc.h"

#include "typedef.h"
#include "wrp_app_mcu.h"
#include "wrp_app_uart.h"
#include "r_dlms_config.h"
#include "r_dlms_tcp_wrapper.h"
#include "r_dlms_tcp_wrapper_interface.h"
#include "r_dlms_tcp_wrapper_neoway_wm620.h"
#include "r_dlms_event.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "powermgmt.h"
#include "wrp_app_ext.h"
#include "r_dlms_com_wrapper_config.h"
#if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == TRUE) && (TCP_MODE_SELECTION == TCP_MODE_NEOWAY_WM620)

/******************************************************************************
Macro definitions
******************************************************************************/
#define     FIXED_METER_PUSH_DOMAIN                             "meter.dynu.net"
#define     GSM_CONNECTED                                       {;}
#define     TCP_DEVICE_MODULE_MOUNTING_HW_CHECK_SUPPORT         FALSE
#define     TCP_DEVICE_MODULE_POWER_CONTROL_SUPPORT             TRUE

#define     TCP_DEVICE_SOCKET_ID_NO_CONNECTION                  255

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
extern uint8_t	g_tcp_ch0_port_config_ip_addr_buffer[];

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

/* All data for TCP GSM Modem */
GsmModem			g_tcp_gsm_modem;							/* GSM Modem Information */
TimeoutChannel		g_tcp_gsm_interval_timer;					/* GSM Modem Interval Timer */
const TcpPort		g_tcp_dummy_remote_port = 4059;				/* Dummy remote station TCP port to bypass AARQ connection check */
const uint8_t		g_tcp_dummy_remote_ip[16];					/* Dummy remote station IP address to bypass AARQ connection check */
const IpAddress		g_tcp_dummy_remote_ip_addr = 
{
	(uint8_t *)g_tcp_dummy_remote_ip,
	16
};

/* For UART Port & GSM Modem Reply */
volatile uint8_t	g_tcp_device_send_end = TRUE;				/* Send end flag */
AtReply				g_tcp_at_reply;								/* AT reply */
TimeoutChannel		g_tcp_at_timeout_timer;						/* AT Commands timeout timer */
AtEvent				g_tcp_at_event;								/* AT event (listener) */
TimeoutChannel		g_tcp_at_event_timeout;						/* AT event interframe timeout */

/* ---------------------------------------------------------------------------
 * Unsolicted event handlers, parser & internal functions
 * ---------------------------------------------------------------------------
 */

/* Cmd inputs */
static uint16_t r_tcp_device_cmd_input_cgdcont(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length);
static uint16_t r_tcp_device_cmd_input_close_connect(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length);
static uint16_t r_tcp_device_cmd_input_tcpsetup(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length);
static uint16_t r_tcp_device_cmd_input_tcpclose(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length);

/* Reply handlers */
static uint8_t r_tcp_device_reply_check_cpin(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_cgreg(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_csq(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_xiic(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_tcplisten(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_close_connect(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_tcpsetup(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);

/* Event receiver entry & all handlers */
static uint16_t r_tcp_device_parse_u16(uint16_t *p_u16, uint8_t *p_str, uint16_t length);
static uint16_t r_tcp_device_parse_ip_address(uint8_t *p_ip_address, uint16_t * p_port_no, uint8_t *p_str, uint16_t length);
static uint8_t r_tcp_device_event_handler_cpin(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_cgreg(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_csq(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_cmee(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_xiic(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_pppstatus(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_tcpsetup(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_tcpclose(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_connect(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_closeclient(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_cops(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_erat(AtEvent *p_event);

static uint8_t r_tcp_device_receive_unsolicited_event(uint8_t rx_byte, uint8_t use_timeout);

/* Manage to send & check reply */
static void			r_tcp_device_send_cmd(AtCommand *p_cmd);
static void			r_tcp_device_prepare_cmd_reply(void);
static void			r_tcp_device_unregister_cmd_reply(void);
static AtCmdState	r_tcp_device_check_cmd_reply(AtCommand *p_cmd);
static void         r_tcp_device_start_at_runner_execution(AtRunner *p_runner);
static AtCmdResult	r_tcp_device_execute_at_runner(AtRunner *p_runner, uint8_t reset_if_fails);

/* AT Commands to boot up GSM Modem */

static uint8_t r_tcp_device_is_modem_mounted(void)
{
#if (TCP_DEVICE_MODULE_MOUNTING_HW_CHECK_SUPPORT == TRUE)
    if (GSM_CONNECTED == 1) {
        return FALSE;
    }
    else {
        return TRUE;
    }
#else
    return TRUE;
#endif
}

static void r_tcp_device_reset_network_status(void)
{
    memset(&g_tcp_gsm_modem.info.cell_info, 0, sizeof(g_tcp_gsm_modem.info.cell_info));
    g_tcp_gsm_modem.info.ps_status = 0;
    g_tcp_gsm_modem.info.network_status = 0;
}

static void r_tcp_device_acknowledge_event_received(void)
{
    g_tcp_at_event.received = FALSE;
    g_tcp_at_event.type = GSM_MODEM_EVENT_NONE;
    memset(g_tcp_at_event.prefix.buffer, 0, TCP_DEVICE_AT_EVENT_PREFIX_LENGTH);
    g_tcp_at_event.prefix.count = 0;
    memset(g_tcp_at_event.content.buffer, 0, TCP_DEVICE_AT_EVENT_CONTENT_LENGTH);
    g_tcp_at_event.content.count = 0;
    g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_PLUS;

}

static void r_tcp_device_process_cmee_code(uint16_t code)
{
    /* Put error processing here since this is common for ME device */
    if (code >= 10 && code <= 19)
    {
        if (code == 10) {
            g_tcp_gsm_modem.diag.sim_inserted = FALSE;
            g_tcp_gsm_modem.diag.sim_good = FALSE;
        }
        else {
            g_tcp_gsm_modem.diag.sim_inserted = TRUE;
            g_tcp_gsm_modem.diag.sim_good = FALSE;
        }
        /* Fall back to usim checking script if in other state */
        if (g_tcp_gsm_modem.state != GSM_MODEM_STATE_CHECK_USIM) {
            r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.sim);
            g_tcp_gsm_modem.state = GSM_MODEM_STATE_CHECK_USIM;
        }
    }
    else {
        /* TODO for rest of CMEE error code */
        NOP();
    }
}

static uint8_t r_tcp_device_is_valid_destination(TcpPort remote_port, IpAddressPtr remote_ip_address)
{
    /* Check remote_port */
    if (remote_port != 4059) {
        return FALSE;
    }

#if TCP_DEVICE_IP_CONFIGURATION == 0	/* IPv4 */

#elif TCP_DEVICE_IP_CONFIGURATION == 1	/* IPv6 */
    /* TODO: IPv6 */
#else
    
#endif
    
    /* No error, valid destination address */
    return TRUE;
}

static uint8_t r_tcp_device_update_cgreg_to_cell_info(GsmCgreg * p_cgreg)
{
    uint8_t status;

    /* Always update network status */
    g_tcp_gsm_modem.info.network_status = p_cgreg->stat;

    /* Update input CGREG info to part of cell info, error condition */
    if (g_tcp_gsm_modem.info.network_status == 1 ||
        g_tcp_gsm_modem.info.network_status == 5) {
        /* Clear all error */
        g_tcp_gsm_modem.diag.gprs_registration_failure = FALSE;
        g_tcp_gsm_modem.diag.gprs_registration_denied = FALSE;

        /* CS attachment:
        * 0: inactive
        * 1: incoming call
        * 2: active
        * Currently support inactive and active only, so when registered, consider active */
        g_tcp_gsm_modem.info.cs_attachment = 2;

        g_tcp_gsm_modem.info.cell_info.location_id = p_cgreg->lac;
        g_tcp_gsm_modem.info.cell_info.cell_id = p_cgreg->ci;

        status = TRUE;
    }
    else {
        if (g_tcp_gsm_modem.info.network_status == 0) {
            /* Registration failure */
            g_tcp_gsm_modem.diag.gprs_registration_failure = TRUE;
            g_tcp_gsm_modem.diag.gprs_registration_denied = FALSE;
        }
        else if (g_tcp_gsm_modem.info.network_status == 3) {
            /* Registration denied */
            g_tcp_gsm_modem.diag.gprs_registration_failure = FALSE;
            g_tcp_gsm_modem.diag.gprs_registration_denied = TRUE;
        }
        else {
            /* Unknown error */
            g_tcp_gsm_modem.diag.gprs_registration_failure = TRUE;
            g_tcp_gsm_modem.diag.gprs_registration_denied = TRUE;
        }

        r_tcp_device_reset_network_status();

        /* When there's error, skip updating the parameter and return result */
        status = FALSE;
    }

    /* Update capture time */
    R_RTC_Get_CalendarCounterValue(&g_tcp_gsm_modem.info.capture_time);

    return status;
}

static uint16_t r_tcp_device_parse_u16(uint16_t *p_u16, uint8_t *p_str, uint16_t length)
{
	/* "12345" -> 12345 */

	uint8_t  byte;
	uint8_t  *p_head = p_str;

	if (p_u16 == NULL || p_str == NULL) {
		return 0;
	}

	*p_u16 = 0;
	while (length > 0)
	{
		byte = *p_str++;
		if ('0' <= byte && byte <= '9') {
			*p_u16 *= 10;
			*p_u16 += byte - '0';
		}

		if (byte == '.' ||
			byte == ':' ||
			byte == ',' ||
			byte == '\r' ||
			byte == '\n')
		{
			break;
		}
		length--;
	}

	return (uint16_t)(p_str - p_head);
}
static uint16_t r_tcp_device_parse_u32(uint32_t *p_u32, uint8_t *p_str, uint16_t length)
{
    /* "12345" -> 12345 */

    uint8_t  byte;
    uint8_t  *p_head = p_str;

    if (p_u32 == NULL || p_str == NULL) {
        return 0;
    }

    *p_u32 = 0;
    while (length > 0)
    {
        byte = *p_str++;
        if ('0' <= byte && byte <= '9') {
            *p_u32 *= 10;
            *p_u32 += byte - '0';
        }

        if (byte == '.' ||
            byte == ':' ||
            byte == ',' ||
            byte == '\r' ||
            byte == '\n')
        {
            break;
        }
        length--;
    }

    return (uint16_t)(p_str - p_head);
}
static uint16_t r_tcp_device_parse_u32_hexstr(uint32_t *p_u32, uint8_t *p_str, uint16_t length)
{
    /* "0x12345678" -> 0x12345678 */

    uint8_t  byte;
    uint8_t  *p_head = p_str;

    if (p_u32 == NULL || p_str == NULL) {
        return 0;
    }

    *p_u32 = 0;
    while (length > 0)
    {
        byte = *p_str++;
        if (('a' <= byte && byte <= 'f') ||
            ('A' <= byte && byte <= 'F') ||
            ('0' <= byte && byte <= '9'))
        {
            *p_u32 <<= 4;
            if (byte >= 'a') {
                *p_u32 += 10 + (byte - 'a');
            }
            else if (byte >= 'A') {
                *p_u32 += 10 + (byte - 'A');
            }
            else {
                *p_u32 += byte - '0';
            }
        }

        if (byte == '.' ||
            byte == ':' ||
            byte == ',' ||
            byte == '\r' ||
            byte == '\n')
        {
            break;
        }
        length--;
    }

    return (uint16_t)(p_str - p_head);
}

static void r_tcp_device_start_at_runner_execution(AtRunner *p_runner)
{
    p_runner->index = 0;
    p_runner->reboot = TCP_DEVICE_AT_SCRIPT_RETRIES_MAX - 1;    /* Number of retries need to be > 0, checked when define macro */
    p_runner->retry = TCP_DEVICE_AT_COMMAND_RETRIES_MAX - 1;    /* Number of retries need to be > 0, checked when define macro */
    g_tcp_at_reply.state = AT_CMD_START;
}

/*
 * Cmd inputs
 */
static uint16_t r_tcp_device_cmd_input_cgdcont(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length)
{
    uint8_t buffer[TCP_DEVICE_MAX_APN_NAME_LENGTH+1];
    memcpy(buffer, p_modem->setting.apn_name.data, p_modem->setting.apn_name.size);
    buffer[p_modem->setting.apn_name.size] = 0; // Terminate the string

#if TCP_DEVICE_IP_CONFIGURATION == 0
	return (uint16_t)sprintf((char *)p_input_args, "\"IP\",\"%s\"", buffer);
#elif TCP_DEVICE_IP_CONFIGURATION == 1
	return (uint16_t)sprintf((char *)p_input_args, "\"IPV6\",\"%s\"", buffer);
#endif
}

static uint16_t r_tcp_device_cmd_input_close_connect(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length)
{
#if TCP_DEVICE_IP_CONFIGURATION == 0	/* IPv4 */
    // TODO: multiple TCP channel now fixed socket 1
    if (p_modem->remote[1].is_outbound == TRUE)
    {
        return (uint16_t)sprintf(
    		(char *)p_input_args,
    		"AT+TCPCLOSE=%u",
    		1                               // TODO: multiple TCP channel now fixed socket 1
        );
    }
    else
    {
        return (uint16_t)sprintf(
    		(char *)p_input_args,
    		"AT+CLOSECLIENT=%u",
    		1                               // TODO: multiple TCP channel now fixed socket 1
        );
    }
#elif TCP_DEVICE_IP_CONFIGURATION == 1	/* TODO: IPv6 */
    return 0;
#endif
}

static uint16_t r_tcp_device_cmd_input_tcpsetup(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length)
{
    uint8_t         * p_IpBuffer;
    uint16_t        remote_tcp_port;

    /* AT+TCPSETUP=1,10.205.6.30,4059 */    // TODO: multiple TCP channel now fixed socket 1 (not specified will get avaialble socket)
    p_IpBuffer = p_modem->remote[1].ip_buffer;
    remote_tcp_port = p_modem->remote[1].port_number;

#if TCP_DEVICE_IP_CONFIGURATION == 0	/* IPv4 */
    return (uint16_t)sprintf(
		(char *)p_input_args,
		"1,%d.%d.%d.%d,%d",             // TODO: multiple TCP channel now fixed socket 1
		p_IpBuffer[0],
		p_IpBuffer[1],
		p_IpBuffer[2],
		p_IpBuffer[3],
		remote_tcp_port
    );
#elif TCP_DEVICE_IP_CONFIGURATION == 1	/* IPv6 */
    return 0;
#endif
}

static uint16_t r_tcp_device_cmd_input_tcpclose(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length)
{
#if TCP_DEVICE_IP_CONFIGURATION == 0	/* IPv4 */
    return (uint16_t)sprintf(
		(char *)p_input_args,
		"%u",
		1                               // TODO: multiple TCP channel now fixed socket 1
    );
#elif TCP_DEVICE_IP_CONFIGURATION == 1	/* IPv6 */
    return 0;
#endif
}

/*
 * Reply handlers
 */
static uint8_t r_tcp_device_reply_check_xiic(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    uint8_t * p_pattern;
	
    /* AT+XIIC special handling to check reply
	 *	AT+XIIC=1 give 2 different event like format: +NEWIP:, +PPPSTATUS:
     *	AT+XIIC? give normal event like format: +XIIC:
	 * Event +NEWIP so not using p_event type check
	 * But checking p_msg for +PPPSTATUS or +XIIC and \r\n
    */
	
	/* Find if request format available */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "+PPPSTATUS");
	
	/* Next string */
	if (p_pattern != NULL) {
		p_pattern += 10;
	}
	else {
		/* Not found, try checking the query format */
	   	p_pattern = (uint8_t *)strstr((const char *)p_msg, "+XIIC");
		
		/* Next string */
		if (p_pattern != NULL) {
			p_pattern += 5;
		}
	}
	
	if (p_pattern != NULL) {
		/* Expected \r\n at the end */
		if (strstr((const char *)p_pattern, "\r\n") != NULL) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	else {
		return FALSE;
	}
}

static uint8_t r_tcp_device_reply_check_tcplisten(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    /* AT+TCPLISTEN=4059 (not having event handler yet)
	 * Received
	 *	+TCPLISTEN:0,OK			--> Start listen ok
	 *	+TCPLISTEN:bind error	--> Unknown cause
	 *	+CME ERROR: 3			--> PPP not setup before listening
	 *	Listening...			--> Already listening
	*/
	/* For +TCPLISTEN:bind error and +CME ERROR: 3, try again on modem reboot */
	if (strstr((const char *)p_msg, "+TCPLISTEN:0,OK\r\n") != NULL ||
		strstr((const char *)p_msg, "Listening...\r\n") != NULL) {
		return TRUE;
	}
    else
    {
	    return FALSE;
    }	
}

static uint8_t r_tcp_device_reply_check_cpin(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    if (p_event == NULL) {
        return FALSE;
    }

    if (p_event->type != GSM_MODEM_EVENT_CPIN &&
        p_event->type != GSM_MODEM_EVENT_CMEE) {
        return FALSE;
    }

    if (p_event->type == GSM_MODEM_EVENT_CPIN)
    {
        /* Work around: if CPIN event, after that, there would be another line OK\r\n
        * Need to wait for this one, else next command could cause error
        */
        if ((uint8_t *)strstr((const char *)p_msg, "OK\r\n") == NULL) {
            return FALSE;
        }

        /* If there's a +CPIN output, then SIM is inserted */
        g_tcp_gsm_modem.diag.sim_inserted = TRUE;

        /* Further check on CPIN status for sim failure detection */
        if (p_event->data.CPIN.status == GSM_MODEM_SIM_READY) {
            g_tcp_gsm_modem.diag.sim_good = TRUE;
        }
        else {
            g_tcp_gsm_modem.diag.sim_good = FALSE;
            return FALSE;
        }
    }
    else {
        /* If there's CMEE error for CPIN command, there should be SIM not inserted error */
        g_tcp_gsm_modem.diag.sim_inserted = FALSE;
        g_tcp_gsm_modem.diag.sim_good = FALSE;
        return FALSE;
    }

    return TRUE;
}

static uint8_t r_tcp_device_reply_check_cgreg(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    uint8_t * p_pattern;

    if (g_tcp_gsm_modem.diag.sim_inserted == FALSE ||
        g_tcp_gsm_modem.diag.sim_good == FALSE)
    {
        /* Stop further checks */
        return FALSE;
    }

    if (p_event == NULL) {
        return FALSE;
    }

    if (p_event->type != GSM_MODEM_EVENT_CGREG) {
        return FALSE;
    }
    
    /* Try again a few time when not registered within script retry (event update status) */
    if (p_event->data.CGREG.stat != 1 && p_event->data.CGREG.stat != 5) {
        return FALSE;
    }

    return TRUE;
}

static uint8_t r_tcp_device_reply_check_csq(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    if (p_event == NULL) {
        return FALSE;
    }

    if (p_event->type != GSM_MODEM_EVENT_CSQ) {
        return FALSE;
    }

    /* Try again a few time when no signal within script retry (event update status) */
    if (p_event->data.CSQ.rssi == 99 &&
        p_event->data.CSQ.ber == 99) {
        return FALSE;
    }

    return TRUE;
}

static uint8_t r_tcp_device_reply_check_close_connect(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    /* Get information from p_event */
    /* AT+CLOSECLIENT=1 (request) have special return ERROR (not event type when there's no active connection)
	 * Received
	 *	+CLOSECLIENT:1,remote link closed   --> Closeclient ok
	 *	ERROR	                            --> No remote client connecting (not event)=
	*/
    if (p_event == NULL) 
    {
		if (strstr((const char *)p_msg, "ERROR\r\n") == NULL) {
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
    else
    {
        if (p_event->type != GSM_MODEM_EVENT_CLOSECLIENT && p_event->type != GSM_MODEM_EVENT_TCPCLOSE) {
            return FALSE;
        }
        else {
            return TRUE;
        }
    }
}

static uint8_t r_tcp_device_reply_check_tcpsetup(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    /* Get information from p_event */
    if (p_event == NULL) {
        return FALSE;
    }

    if (p_event->type != GSM_MODEM_EVENT_TCPSETUP) {
        return FALSE;
    }

    return TRUE;
}

/*
 * Event receiver entry & all handlers
 */
static uint16_t r_tcp_device_parse_ip_address(uint8_t *p_ip_address, uint16_t * p_port_no, uint8_t *p_str, uint16_t length)
{
	/* 2001:EE0:26B:B723:6D43:69ED:898C:EEDD */
    /* 2001:0ee0:0100:8::8 */
    /* :: */
    /* ::1 */
    /* FF01::101 */
	/* 192.168.0.1 */

    /* Common for IPv4 and IPv6 parser */
	uint16_t u16 = 0;
	uint16_t ip_bytes = 0;
    uint16_t port_no = 0;
	uint8_t  byte, is_ipv6;
    uint8_t  parsing_port = FALSE;
    uint8_t  * p_colon, *p_dot;

    /* IPv6 parser variables */
    struct {
        uint8_t is_double_colon;            /* Double colon detected */
        uint8_t is_decimal_mode;            /* Decimal mode character: Port or ipv4 compatible address */
        uint8_t receiving_valid_char;       /* Is receiving valid character? */
        uint8_t square_bracket_pair;        /* Square bracket pair checker */
        uint8_t ip_temp_buffer[16];         /* Temporary buffer to hold converted IP before putting to output buffer */
        uint8_t * p_ip_temp;                /* Pointer to temporary buffer */
        uint16_t ip_bytes_at_double_colon;  /* The bytes index when double colon detected */
    } ipv6_parser;

	if (p_ip_address == NULL || p_str == NULL) {
		return 0;
	}

    p_dot   = memchr(p_str, '.', length);
    p_colon = memchr(p_str, ':', length);

    /* Cannot parse this string, wrong format */
    ASSERT_TRUE_RET_ZERO(
        p_dot == NULL && p_colon == NULL
    );

    if (p_dot == NULL) {
        /* Pure Ipv6 format */
        is_ipv6 = TRUE;
    }
    else if (p_colon == NULL) {
        /* Pure Ipv4 format no port information */
        is_ipv6 = FALSE;
    }
    else {
        if (p_dot > p_colon) {
            /* Mixed Ipv4 format */
            is_ipv6 = TRUE;
        }
        else {
            /* Ipv4 with port information */
            is_ipv6 = FALSE;
        }
    }

    /* Prepare output buffer */
    memset(p_ip_address, 0, is_ipv6 ? 16 : 4);

    /* Parse according to checked type */
    if (is_ipv6 == FALSE)
    {
        /* Parse IPv4 address */
        while (length > 0)
        {
            byte = *p_str++;

            if ('0' <= byte && byte <= '9') {
                u16 *= 10;
                u16 += byte - '0';
            }

            if (parsing_port == FALSE)
            {
                /* Parsing mode: address */
                /* Terminate one byte */
                if (byte == '.' || 
                    byte == ':' ||
                    length == 1)
                {
                    if (ip_bytes < 4)
                    {
                        *p_ip_address++ = (uint8_t)(u16);
                        ip_bytes++;
                    }
                    u16 = 0;

                    if (byte == ':') {
                        parsing_port = TRUE;
                    }
                }
            }
            else
            {
                /* Parsing mode: port (scan until end of string) */
                if (length == 1) {
                    port_no = u16;
                }
            }

            length--;
        }
    }
    else
    {
        /* Prepare Ipv6 parser */
        memset(&ipv6_parser, 0, sizeof(ipv6_parser));
        ipv6_parser.p_ip_temp = &ipv6_parser.ip_temp_buffer[0];

        /* Parse IPv6 address */
        while (length > 0)
        {
            byte = *p_str++;

            if (ipv6_parser.is_decimal_mode == FALSE)
            {
                if (('a' <= byte && byte <= 'f') ||
                    ('A' <= byte && byte <= 'F') ||
                    ('0' <= byte && byte <= '9'))
                {
                    u16 <<= 4;
                    if (byte >= 'a') {
                        u16 += 10 + (byte - 'a');
                    }
                    else if (byte >= 'A') {
                        u16 += 10 + (byte - 'A');
                    }
                    else {
                        u16 += byte - '0';
                    }
                    ipv6_parser.receiving_valid_char = TRUE;
                }
            }
            else {
                if ('0' <= byte && byte <= '9') {
                    u16 *= 10;
                    u16 += byte - '0';
                    ipv6_parser.receiving_valid_char = TRUE;
                }
            }

            /* Check for bracket pair */
            if (byte == '[' || byte == ']')
            {
                ipv6_parser.square_bracket_pair += byte;
            }

            if (parsing_port == FALSE)
            {
                /* Parsing mode: address */
                /* Terminate one byte */
                if (byte == ':' ||
                    byte == '.' ||
                    byte == ']' ||
                    length == 1)
                {
                    if (ip_bytes < 16)
                    {
                        if (ipv6_parser.receiving_valid_char == TRUE)
                        {
                            if (ipv6_parser.is_decimal_mode == FALSE) {
                                *ipv6_parser.p_ip_temp++ = (uint8_t)(u16 >> 8);
                                *ipv6_parser.p_ip_temp++ = (uint8_t)(u16);
                                ip_bytes += 2;
                            }
                            else {
                                *ipv6_parser.p_ip_temp++ = (uint8_t)(u16);
                                ip_bytes++;
                            }
                            ipv6_parser.receiving_valid_char = FALSE;
                        }
                        u16 = 0;
                    }

                    /* Check for double colon */
                    if (byte == ':')
                    {
                        /* If next byte also ':', then it's double colon */
                        if (*p_str == ':') {
                            if (ipv6_parser.is_double_colon == FALSE) {
                                p_str++;
                                length--;
                                ipv6_parser.is_double_colon = TRUE;
                                ipv6_parser.ip_bytes_at_double_colon = ip_bytes;
                            }
                            else {
                                /* Fatal error: the "::" can only appear once in an address */
                                return 0;
                            }
                        }

                        /* Check for ipv4 compatible address */
                        /* No need for further check if there's no dot */
                        if (p_dot != NULL)
                        {
                            /* Update the next colon position */
                            p_colon = memchr(p_str, ':', length);
                            if (p_colon == NULL) {
                                /* No more colon, so it's only ipv4 remaining */
                                ipv6_parser.is_decimal_mode = TRUE;
                            }
                            else {
                                /* Colon remaining, check if p_colon after the p_dot */
                                if (p_colon > p_dot) {
                                    /* If p_colon after p_dot, it could be the port information, so it's ok to switch over */
                                    ipv6_parser.is_decimal_mode = TRUE;
                                }
                            }
                        }
                    }

                    /* Check for port information */
                    if (byte == ']')
                    {
                        if (ipv6_parser.square_bracket_pair == ('[' + ']') &&
                            *p_str == ':') 
                        {
                            p_str++;
                            length--;
                            /* Correct pair of '[' and ']', the rest is port number */
                            ipv6_parser.is_decimal_mode = TRUE;
                            parsing_port = TRUE;
                        }
                        else {
                            /* Fatal error: not having '[' but having ']' */
                            return 0;
                        }
                    }
                }
            }
            else 
            {
                /* Parsing mode: port (scan until end of string) */
                if (length == 1) {
                    port_no = u16;
                }

                /* Fatal error: wrong bracket pairs received */
                if (ipv6_parser.square_bracket_pair != ('[' + ']')) {
                    return 0;
                }
            }

            length--;
        }

        if (ip_bytes != 16)
        {
            /* Process in case there's double colon: IPv6 specific */
            if (ipv6_parser.is_double_colon == TRUE) {
                /* Copy from left to "::" */
                memcpy(p_ip_address, ipv6_parser.ip_temp_buffer, ipv6_parser.ip_bytes_at_double_colon);

                /* 0 in between cleared by memset above */

                /*  Copy from "::" to right */
                memcpy(
                    p_ip_address + (16 - (ip_bytes - ipv6_parser.ip_bytes_at_double_colon)),
                    ipv6_parser.ip_temp_buffer + ipv6_parser.ip_bytes_at_double_colon,
                    ip_bytes - ipv6_parser.ip_bytes_at_double_colon
                );
            }
            else {
                return 0;
            }
        }
        else {
            memcpy(p_ip_address, ipv6_parser.ip_temp_buffer, ip_bytes);
        }
    }

    if (p_port_no != NULL)
    {
        *p_port_no = port_no;
    }

    /* Return either 4 or 16 indicate the ip length in bytes */
	return (uint16_t)(is_ipv6 ? 16 : 4);
}

static uint8_t r_tcp_device_event_handler_cpin(AtEvent *p_event)
{
    /*\r\n+CPIN: READY\r\n\r\nOK\r\n */
    /*\r\n+CPIN: SIM PIN\r\n\r\nOK\r\n */
    /*\r\n+CPIN: SIM PUK\r\n\r\nOK\r\n */
    uint8_t  *p_pattern;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;

    /* Start parsing when received end of line */
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }

    if ((uint8_t *)strstr((const char *)p_msg, "READY") != NULL) {
        p_event->data.CPIN.status = GSM_MODEM_SIM_READY;
    }
    else if ((uint8_t *)strstr((const char *)p_msg, "SIM PIN") != NULL) {
        p_event->data.CPIN.status = GSM_MODEM_SIM_PIN;
    }
    else if ((uint8_t *)strstr((const char *)p_msg, "SIM PUK") != NULL) {
        p_event->data.CPIN.status = GSM_MODEM_SIM_PUK;
    }
    else {
        return FALSE;
    }

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_cgreg(AtEvent *p_event)
{
    /* Format mode 2 only */
    /* Unsolicited when not registered:         +CGREG: <stat>\r\n */
    /* Query when not registered:               +CGREG: <n>,<stat>\r\n */
    /* Unsolicited when connected:              +CGREG: <stat>, <lac>, <ci>\r\n */
	/* Query:                                   +CGREG: <n>,<stat>, <lac>, <ci>\r\n */

	uint8_t  *p_pattern = NULL;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;
	uint16_t u16, temp;
    uint32_t temp32;
    uint8_t  is_query;

    /* Parse when detect end of line */
	/* "\r\n" */
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }

    /* Detect type of CGREG based on the number of ',' */
    temp = 0;
    for (u16 = 0; u16 < length; u16++)
    {
        if (p_msg[u16] == ',') {
            temp++;
        }
        else if (temp == ':'){
            /* Could be content of another event inside buffer, stopped now */
            break;
        }
    }

    /* Determine type of CGREG */
    if (temp == 0) {
        /* No ',': consider unsolicited + not registered */
        is_query = FALSE;
        p_event->data.CGREG.n = 2;
    }
    else if (temp == 1 || temp == 3) {
        /* Only 1 ',': consider query + not registered */
        is_query = TRUE;
    }
    else if (temp == 2) {
        /* Unsolicited, connected with lac and cid */
        is_query = FALSE;
    }
    else {
        /* Unknown format yet, to be checked here, consider not query */
        is_query = FALSE;
    }

	/* space */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, " ");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_msg++;
	length--;

    /* Parse the n */
    if (is_query) {
        /* <n> */
        u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
        if (u16 == 0) {
    	    return FALSE;
        }
        p_event->data.CGREG.n = (uint8_t)temp;

        p_msg += u16;
        length -= u16;
    } 
    else {
        /* If unsolicited mode then n must be 2 */
        p_event->data.CGREG.n = 2;
    }

	/* <stat> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGREG.stat = (uint8_t)temp;
    p_msg += u16 + 1;
    length -= u16 + 1;
    
    /* Only continue if this is mode 2 */
    if (p_event->data.CGREG.n != 2) {
        return TRUE;   
    }
    
    /* Only continue to parse if registered */
    if (p_event->data.CGREG.stat == 1 ||
        p_event->data.CGREG.stat == 5)
    {
    	/* [<lac>] */
        u16 = r_tcp_device_parse_u32_hexstr(&temp32, p_msg, length);
        if (u16 == 0) {
            return FALSE;
        }
        p_event->data.CGREG.lac = (uint16_t)temp32;
        p_msg += u16 + 1;
        length -= u16 + 1;

    	/* [<ci>] */
        u16 = r_tcp_device_parse_u32_hexstr(&temp32, p_msg, length);
        if (u16 == 0) {
            return FALSE;
        }
        p_event->data.CGREG.ci = temp32;
        p_msg += u16;
        length -= u16;
    	
        // /* [<AcT>] */
        // u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
        // if (u16 == 0) {
        //     return FALSE;
        // }
        // p_event->data.CGREG.AcT = temp;
        // p_msg += u16 + 1;
        // length -= u16 + 1;
    	
        // /* [<rac>] */
        // u16 = r_tcp_device_parse_u32_hexstr(&temp32, p_msg, length);
        // if (u16 == 0) {
        //     return FALSE;
        // }
        // p_event->data.CGREG.rac = temp32;
        
        p_msg += u16 - 1;
        length -= u16 - 1;
    }

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_csq(AtEvent *p_event)
{
	/* +CSQ: <rssi>,<ber>\r\n */

	uint8_t  *p_pattern = NULL;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;
	uint16_t u16, temp;

	/* "\r\n" */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
	if (p_pattern == NULL) {
		return FALSE;
	}

	/* space */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, " ");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_msg++;
	length--;

	/* rssi */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CSQ.rssi = (uint8_t)temp;

	/* ',' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* ber */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CSQ.ber = (uint8_t)temp;

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_xiic(AtEvent *p_event)
{
	/*
	* IPv4
	* ---------------------------------------------------
	* +XIIC:1,192.168.0.1\r\n	: the link is set up successfully
	* +XIIC:0,0.0.0.0\r\n		: the PPP link has not been set up 
	*/

	uint8_t  *p_pattern = NULL;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;
	uint16_t u16, temp;

    /* "\r\n" */
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }

    /* Prefix return IP of successful connection */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern != NULL) {
		u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
		if (u16 > 0) {
			p_event->data.XIIC.status = (uint8_t)temp;
		}
        /* Point to ip info (comma already skipped in parsing API) */
		p_msg += u16;
		length -= u16;
	}

	/* Parse IP address */
	if (p_event->data.XIIC.status == 1) {
		u16 = r_tcp_device_parse_ip_address(p_event->data.XIIC.local_ip_buffer, NULL, p_msg, length);
		if (u16 == 0) {
			return FALSE;
		}
	}

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_pppstatus(AtEvent *p_event)
{
	/*
	* PPP STATUS (query or unsolicited)
	* ---------------------------------------------------
	* +PPPSTATUS:OPENED\r\n
	* +PPPSTATUS:CLOSED\r\n
	*/

	uint8_t  *p_pattern = NULL;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;
	uint16_t u16, temp;

    /* "\r\n" */
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }

    /* "Expect OPENED or CLOSED only" */
    if ((uint8_t *)strstr((const char *)p_msg, "OPENED") == NULL)
    {
        /* Try to find CLOSED */
        if ((uint8_t *)strstr((const char *)p_msg, "CLOSED") == NULL)
        {
            /* Could not find either OPENED or CLOSED */
            return FALSE;
        }
        else
        {
            /* Found CLOSED */
            p_event->data.PPPSTATUS.is_closed = TRUE;
        }
    }
    else
    {
        /* Found OPENED */
        p_event->data.PPPSTATUS.is_closed = FALSE;
    }
    
	return TRUE;
}

static uint8_t r_tcp_device_event_handler_tcpsetup(AtEvent *p_event)
{
	uint8_t  *p_pattern = NULL;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;
	uint16_t u16, temp;

	/*
	* Message
	* ---------------------------------------------------
	* +TCPSETUP:1,OK\r\n    (1 is socket id, range from 0 to 5)
    * +TCPSETUP:1,FAIL\r\n  (server not started,the IP address is incorrect, or the SIM card is out of credit)
	* +TCPSETUP:ERROR\r\n   (The format or the AT command is incorrect)
	*/
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }

    u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
    if (u16 == 0) {
        /* If there's no socket ID, always means ERROR, socket id cleared to 255 */
        p_event->data.TCPSETUP.socket_id = TCP_DEVICE_SOCKET_ID_NO_CONNECTION;
        p_event->data.TCPSETUP.is_error = 1;
        return TRUE;
    }
    else
    {
        p_event->data.TCPSETUP.is_error = 0;
    }

    p_event->data.TCPSETUP.socket_id = (uint8_t)temp;

    p_msg += u16;
    length -= u16;

    /* status (OK or FAIL) */
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "OK");
    if (p_pattern == NULL) 
    {
        p_pattern = (uint8_t *)strstr((const char *)p_msg, "FAIL");
        if (p_pattern == NULL) 
        {
            /* Incomplete message */
            return FALSE;
        }
        else
        {
            p_event->data.TCPSETUP.is_socket_failed = 1;
        }
    }
    else 
    {
        p_event->data.TCPSETUP.is_socket_failed = 0;
    }

    return TRUE;
}

static uint8_t r_tcp_device_event_handler_tcpclose(AtEvent *p_event)
{
	uint8_t  *p_pattern = NULL;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;
	uint16_t u16, temp;

	/*
	* Message
	* ---------------------------------------------------
	* +TCPCLOSE:1,OK\r\n    		(local close socket, 1 is socket id, range from 0 to 5)
    * +TCPCLOSE:1,Link Closed\r\n   (remote close socket, 1 is socket id, range from 0 to 5)
	* +TCPCLOSE:ERROR\r\n   		(The format or the AT command is incorrect)
	*/
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }
	
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "ERROR");
	if (p_pattern != NULL)
	{
        /* If ERROR socket id cleared to 255 */
        p_event->data.TCPCLOSE.socket_id = TCP_DEVICE_SOCKET_ID_NO_CONNECTION;
        p_event->data.TCPCLOSE.is_error = 1;
	}
	else
	{
	    u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	    if (u16 == 0) {
			return FALSE;
	    }
	    else
	    {
	    	p_event->data.TCPCLOSE.socket_id = (uint8_t)temp;
	        p_event->data.TCPCLOSE.is_error = 0;

		    p_msg += u16;
		    length -= u16;

		    /* status (OK or Link Closed) */
		    p_pattern = (uint8_t *)strstr((const char *)p_msg, "OK");
		    if (p_pattern == NULL) 
		    {
		        p_pattern = (uint8_t *)strstr((const char *)p_msg, "Link Closed");
		        if (p_pattern == NULL) 
		        {
		            /* Incomplete message */
		            return FALSE;
		        }
		        else
		        {
		            p_event->data.TCPCLOSE.is_remote_close = 1;
		        }
		    }
		    else 
		    {
		        p_event->data.TCPCLOSE.is_remote_close = 0;
		    }
	    }
	}
	
    return TRUE;
}

static uint8_t r_tcp_device_event_handler_connect(AtEvent *p_event)
{
	uint8_t  *p_pattern = NULL;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;
	uint16_t u16, temp;

	/*
	* Message
	* ---------------------------------------------------
	* Connect AcceptSocket=1,ClientAddr=119.123.77.133
	*/
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }

    u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
    if (u16 == 0) {
        /* If there's no socket ID, format error */
        return FALSE;
    }
    else
    {
        p_event->data.CONNECT.socket_id = (uint8_t)temp;
    }

    p_msg += u16;
    length -= u16;

    p_pattern = (uint8_t *)strstr((const char *)p_msg, "ClientAddr=");
    if (p_pattern == NULL) {
        return FALSE;
    }

    /* Skip known string */
    p_msg += (p_pattern - p_msg) + 11;
    length -= (p_pattern - p_msg) + 11;

    /* Parsed IP */
	u16 = r_tcp_device_parse_ip_address(p_event->data.CONNECT.remote_ip_buffer, NULL, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
    p_msg += u16;
    length -= u16;

    return TRUE;
}

static uint8_t r_tcp_device_event_handler_closeclient(AtEvent *p_event)
{
	uint8_t  *p_pattern = NULL;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;
	uint16_t u16, temp;

	/*
	* Message
	* ---------------------------------------------------
	* +CLOSECLIENT:<socket>,remote link closed
    * +CLOSECLIENT:All remote link closed
    * +CLOSECLIENT:accept socket over
	*/
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }
	
	if (strstr((const char *)p_msg, "All remote link closed") != NULL ||
		strstr((const char *)p_msg, "accept socket over") != NULL ||
		(0))
	{
		//Valid message but not parsing now:
		// * Not issue AT+CLOSECLIENT without socket ID (All remote link closed
		// * In case max inbound socket, not care first
		p_event->data.CLOSECLIENT.socket_id = TCP_DEVICE_SOCKET_ID_NO_CONNECTION;
		return TRUE;
	}
	else if (strstr((const char *)p_msg, "remote link closed") != NULL )
	{
	    u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	    if (u16 == 0) {
			return FALSE;
	    }
	    else {
	        p_event->data.CLOSECLIENT.socket_id = (uint8_t)temp;
	    }
	}
	else {
		return FALSE;
	}
	
    return TRUE;
}

static uint8_t r_tcp_device_event_handler_cops(AtEvent *p_event)
{
	/* +COPS: <mode>[,<format 0>,<16-character long alphanumeric format <oper>>[,<AcT>]]\r\n */
    /* +COPS: <mode>[,<format 2>,<5-character numeric format (MCC/MNC) <oper>>[,<AcT>]]\r\n */

	uint8_t  *p_pattern = NULL;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;
	uint16_t u16, temp;

	/* space */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, " ");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_msg += 1;
	length -= 1;

	/* <mode> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.COPS.mode = (uint8_t)temp;

	/* ',' optional */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return TRUE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <format> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.COPS.format = (uint8_t)temp;

	/* ',"' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",\"");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern += 2;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <oper> */
    if (p_event->data.COPS.format == 0)
    {
    	u16 = 0;
    	while (u16 < TCP_DEVICE_MAX_OPERATOR_NAME_LENGTH &&
    		*p_msg != '\"')
    	{
    		p_event->data.COPS.operator.data[u16] = *p_msg;
    		u16++;
    		p_msg++;
    	}
    	if (u16 == TCP_DEVICE_MAX_OPERATOR_NAME_LENGTH) {
            p_event->data.COPS.operator.size = 0;
    		return FALSE;
    	}
        else {
            p_event->data.COPS.operator.size = u16;
        }
    }
    else if (p_event->data.COPS.format == 2)
    {
        u16 = r_tcp_device_parse_u16(&temp, p_msg, 3);
    	if (u16 == 0) {
    		return FALSE;
    	}
        p_event->data.COPS.mcc = temp;
    	p_msg += u16;
    	length -= u16;

        u16 = r_tcp_device_parse_u16(&temp, p_msg, 2);
    	if (u16 == 0) {
    		return FALSE;
    	}
        p_event->data.COPS.mnc = temp;
    	p_msg += u16;
    	length -= u16;
    }
    else
    {
        /* format 1 or unknown, not support, error here */
    }

	/* '"' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\"");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* ',' optional */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return TRUE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <AcT> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.COPS.act = (uint8_t)temp;

	/* "\r\n" */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
	if (p_pattern == NULL) {
		return FALSE;
	}

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_erat(AtEvent *p_event)
{
	/* +ERAT:<current rat>,<GPRS status>,<rat mode>,<prefer rat>\r\n */
    /* E.g. +ERAT:4,2,2,0\r\n */
    /* 
        <current rat>:
            0: GSM
            2: UTRAN
            3: GSM w/EGPRS
            4: UTRAN w/HSDPA
        <GPRS status>:
            0: GPRS
            1: EDGE
            2: HSDPA
            255: unknown
        <rat mode>:
            0: GSM only
            1: WCDMA only
            2: AUTO
        <prefer rat>:
            0: no preference
            1: GSM preferred (when rat mode=2)
            2: WCDMA preferred (when rat mode=2)
    */

	uint8_t  *p_pattern = NULL;
	uint8_t  *p_msg = p_event->content.buffer;
	uint16_t length = p_event->content.count;
	uint16_t u16, temp;

	/* <current rat> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_msg += u16;
	length -= u16;
	p_event->data.ERAT.current_rat = temp;

	/* <GPRS status> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_msg += u16;
	length -= u16;
	p_event->data.ERAT.gprs_status = temp;

	/* <rat mode> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_msg += u16;
	length -= u16;
	p_event->data.ERAT.rat_mode = temp;

	/* <prefer rat> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_msg += u16;
	length -= u16;
	p_event->data.ERAT.prefer_rat = temp;

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_cmee(AtEvent *p_event)
{
    uint8_t  *p_pattern = NULL;
    uint8_t  *p_msg = p_event->content.buffer;
    uint16_t length = p_event->content.count;
    uint16_t u16, temp;

    p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }

    /* Parse the error code */
    u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
    if (u16 == 0) {
        return FALSE;
    }
    p_event->data.CMEE.code = temp;

    return TRUE;
}

static void r_tcp_device_event_handler_default(AtEvent *p_event)
{
	/* Clear data output */
	memset(&p_event->data, 0, sizeof(GsmEventOutput));
	p_event->type = GSM_MODEM_EVENT_NONE;

	/* For easier on copy, paste and re-priority */
	if (0) { }

    else if (strstr((const char *)p_event->prefix.buffer, "+CME ERROR:") != NULL) {
        if (r_tcp_device_event_handler_cmee(p_event) == TRUE) {
            p_event->type = GSM_MODEM_EVENT_CMEE;
            r_tcp_device_process_cmee_code(p_event->data.CMEE.code);
        }
    }
    /* Event "+CPIN:" */
    else if (strstr((const char *)p_event->prefix.buffer, "+CPIN:") != NULL) {
        if (r_tcp_device_event_handler_cpin(p_event) == TRUE) {
            p_event->type = GSM_MODEM_EVENT_CPIN;
        }
    }
    else if (strstr((const char *)p_event->prefix.buffer, "+SIM DROP\r\n") != NULL) {
        /* Immediately fall back to usim checking state */
        p_event->type = GSM_MODEM_EVENT_SIM_DROP;
        g_tcp_gsm_modem.diag.sim_good = FALSE;
        g_tcp_gsm_modem.diag.sim_inserted = FALSE;
        r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.sim);
        g_tcp_gsm_modem.state = GSM_MODEM_STATE_CHECK_USIM;
    }
    /* Event "+CGREG:" */
    else if (strstr((const char *)p_event->prefix.buffer, "+CGREG:") != NULL) {
        if (r_tcp_device_event_handler_cgreg(p_event) == TRUE) {
            p_event->type = GSM_MODEM_EVENT_CGREG;
            g_tcp_gsm_modem.info.network_status = p_event->data.CGREG.stat;
            /* Not continue to process if SIM available and gsm is in converage */
            if (g_tcp_gsm_modem.diag.sim_inserted == TRUE &&
                g_tcp_gsm_modem.diag.sim_good == TRUE &&
                g_tcp_gsm_modem.diag.no_gsm_coverage == FALSE)
            {
                if (r_tcp_device_update_cgreg_to_cell_info(&p_event->data.CGREG) != TRUE &&
                    g_tcp_gsm_modem.state != GSM_MODEM_STATE_CHECK_GSM_COVERAGE)
                {
                    /* Immediately fall back to signal coverage checking state */
                    r_tcp_device_reset_network_status();
                    r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.signal);
                    g_tcp_gsm_modem.state = GSM_MODEM_STATE_CHECK_GSM_COVERAGE;
                }
            }
        }
    }
    /* Event "+XIIC:" join GPRS network */
    else if (strstr((const char *)p_event->prefix.buffer, "+XIIC:") != NULL) 
    {
        if (r_tcp_device_event_handler_xiic(p_event) == TRUE) {
            p_event->type = GSM_MODEM_EVENT_XIIC;
            memcpy(g_tcp_gsm_modem.local.ip_buffer, p_event->data.XIIC.local_ip_buffer, TCP_DEVICE_IP_SIZE);
            /* Copy data over link structure for OBIS */
            memcpy(g_tcp_ch0_port_config_ip_addr_buffer, p_event->data.XIIC.local_ip_buffer, TCP_DEVICE_IP_SIZE);
            if (p_event->data.XIIC.status == 1) {
                g_tcp_gsm_modem.diag.gprs_connection_drop = FALSE;
            }
			else {
                /* Try to check GPRS and establish connection again */
                r_tcp_device_reset_network_status();
                r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.net_reg);
                g_tcp_gsm_modem.state = GSM_MODEM_STATE_CHECK_NETWORK_REGISTRATION;
                g_tcp_gsm_modem.diag.gprs_connection_drop = TRUE;
			}
        }
    }
    /* Event "+PPPSTATUS:" status of PPP connection */
    else if (strstr((const char *)p_event->prefix.buffer, "+PPPSTATUS:") != NULL) 
    {
        if (r_tcp_device_event_handler_pppstatus(p_event) == TRUE) {
            p_event->type = GSM_MODEM_EVENT_PPPSTATUS;
            /* Try to establish connection again if PPP closed (detect closed only, unsolicited event) */
            if (p_event->data.PPPSTATUS.is_closed == 1)
            {
                g_tcp_gsm_modem.diag.gprs_connection_drop = TRUE;
                g_tcp_gsm_modem.diag.gprs_registration_failure = TRUE;
                g_tcp_gsm_modem.diag.gprs_registration_denied = TRUE;
                /* Not continue to process if SIM available and gsm is in converage */
                if (g_tcp_gsm_modem.diag.sim_inserted == TRUE &&
                    g_tcp_gsm_modem.diag.sim_good == TRUE && 
                    g_tcp_gsm_modem.diag.no_gsm_coverage == FALSE)
                {
                    /* Immediately fall back to signal coverage checking state */
                    r_tcp_device_reset_network_status();
                    r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.signal);
                    g_tcp_gsm_modem.state = GSM_MODEM_STATE_CHECK_GSM_COVERAGE;
                }
            }
            else
            {
                /* Status is opened, this only when established connection AT+XIIC successfully */
            }
        }
    }
    /* Event "+TCPSETUP:" Setting up TCP connection */
    else if (strstr((const char *)p_event->prefix.buffer, "+TCPSETUP:") != NULL) {
        if (r_tcp_device_event_handler_tcpsetup(p_event) == TRUE) {
            p_event->type = GSM_MODEM_EVENT_TCPSETUP;
            /* Check socket id overflow */
            if (p_event->data.TCPSETUP.socket_id == 1)          // TODO: multiple TCP channel now fixed socket 1
            {
				/* Only contain socket status when not error */
                if (p_event->data.TCPSETUP.is_error == 0)
				{
	                if (p_event->data.TCPSETUP.is_socket_failed == 0)
	                {
		                g_tcp_gsm_modem.diag.remote_destination_unreachable = FALSE;
                        /* Start timeout */
                        g_tcp_gsm_modem.remote[p_event->data.TCPSETUP.socket_id].is_timeout = FALSE;
						g_tcp_gsm_modem.remote[p_event->data.TCPSETUP.socket_id].timeout.count = g_tcp_gsm_modem.remote[p_event->data.TCPSETUP.socket_id].timeout.initial;
                        g_tcp_gsm_modem.remote[p_event->data.TCPSETUP.socket_id].timeout.enable = TRUE;
		            	// TODO: multiple TCP channel now fixed socket 1
		                R_TCP_DEVICE_ConnectConfirm(0, TRUE, NULL, 0);
	                }
		            else {
		                const uint8_t error_string[] = "Neoway WM620 Modem can not connect to server";
		                g_tcp_gsm_modem.diag.remote_destination_unreachable = TRUE;
		            	// TODO: multiple TCP channel now fixed socket 1
		                R_TCP_DEVICE_ConnectConfirm(0, FALSE, (uint8_t *)error_string, strlen((const char *)error_string));
                        /* Stop timeout */
                        g_tcp_gsm_modem.remote[p_event->data.TCPSETUP.socket_id].timeout.count = g_tcp_gsm_modem.remote[p_event->data.TCPSETUP.socket_id].timeout.initial;
                        g_tcp_gsm_modem.remote[p_event->data.TCPSETUP.socket_id].timeout.enable = FALSE;
		            }
				}
				else {
					/* Not updating status when error on TCPSETUP command */	
				}
            }
        }
    }
    /* Event "+TCPCLOSE:" Closed outbound TCP connection */
    else if (strstr((const char *)p_event->prefix.buffer, "+TCPCLOSE:") != NULL) {
        if (r_tcp_device_event_handler_tcpclose(p_event) == TRUE) {
            p_event->type = GSM_MODEM_EVENT_TCPCLOSE;
            /* Check socket id overflow */
            if (p_event->data.TCPCLOSE.socket_id == 1)   // TODO: multiple TCP channel now fixed socket 1
            {
                /* TODO: re-check when open more TCP channel, currently map directly to channel 0 */
				R_TCP_DEVICE_DisconnectConfirm(0, TRUE, NULL, 0);
                /* Stop timeout */
                g_tcp_gsm_modem.remote[p_event->data.TCPCLOSE.socket_id].timeout.count = g_tcp_gsm_modem.remote[p_event->data.TCPCLOSE.socket_id].timeout.initial;
                g_tcp_gsm_modem.remote[p_event->data.TCPCLOSE.socket_id].timeout.enable = FALSE;
            }
        }
    }
    /* Event "Connect AcceptSocket=" Setting up TCP connection */
    else if (strstr((const char *)p_event->prefix.buffer, "Connect AcceptSocket=") != NULL) {
        if (r_tcp_device_event_handler_connect(p_event) == TRUE) {
            p_event->type = GSM_MODEM_EVENT_CONNECT;
			/* ConnectIndication asserted in receive interrupt for fast incoming byte */
			/* All other status should be sync in interrupt, except remote address updating */
            /* Check socket id overflow */
            if (p_event->data.CONNECT.socket_id == 1)           // TODO: multiple TCP channel now fixed socket 1
            {
                /* ConnectIndication, is_outbound already marked in receive interrupt */
    		    memcpy(g_tcp_gsm_modem.remote[p_event->data.CONNECT.socket_id].ip_buffer, p_event->data.CONNECT.remote_ip_buffer, TCP_DEVICE_IP_SIZE);
            }
        }
    }
    /* Event "+CLOSECLIENT:" Closed inbound TCP connection */
    else if (strstr((const char *)p_event->prefix.buffer, "+CLOSECLIENT:") != NULL) {
        if (r_tcp_device_event_handler_closeclient(p_event) == TRUE) {
            p_event->type = GSM_MODEM_EVENT_CLOSECLIENT;
            /* Check socket id overflow */
            if (p_event->data.CLOSECLIENT.socket_id == 1)    // TODO: multiple TCP channel now fixed socket 1
            {
                /* TODO: re-check when open more TCP channel, currently map directly to channel 0 */
				R_TCP_DEVICE_DisconnectIndication(0, g_tcp_dummy_remote_port, (IpAddressPtr)&g_tcp_dummy_remote_ip_addr, TCP_DISCONNECT_REMOTE_REQ);
				R_TCP_DEVICE_AbortIndication(0, g_tcp_dummy_remote_port, (IpAddressPtr)&g_tcp_dummy_remote_ip_addr, (uint8_t *)"Remote disconnected", 19);   
                /* Stop timeout */
                g_tcp_gsm_modem.remote[p_event->data.CLOSECLIENT.socket_id].timeout.count = g_tcp_gsm_modem.remote[p_event->data.CLOSECLIENT.socket_id].timeout.initial;
                g_tcp_gsm_modem.remote[p_event->data.CLOSECLIENT.socket_id].timeout.enable = FALSE;
            }
        }
    }
    /* Event "+TCPLISTEN: not need to get the socket id, inbound connection will be in different socket" */
    /* Event "+TCPRECV: not yet supported" */
    /* Event "+TCPRECV(S): detected byte by byte" */
	/* Event "+CSQ:" */
	else if (strstr((const char *)p_event->prefix.buffer, "+CSQ:") != NULL) {
		if (r_tcp_device_event_handler_csq(p_event) == TRUE) {
			p_event->type = GSM_MODEM_EVENT_CSQ;
			g_tcp_gsm_modem.info.cell_info.signal_quality = p_event->data.CSQ.rssi;
			g_tcp_gsm_modem.info.cell_info.ber = p_event->data.CSQ.ber;
            /* Diagnostic gsm coverage based on rssi and ber */
            if (g_tcp_gsm_modem.info.cell_info.signal_quality == 99 &&
                g_tcp_gsm_modem.info.cell_info.ber == 99)
            {
                /* As in UM, both rssi and ber value 99 means no signal */
                g_tcp_gsm_modem.diag.no_gsm_coverage = TRUE;
                /* In case not in GSM check coverage, considered GPRS connection drop, jump back to GSM converage state */
                if (g_tcp_gsm_modem.state != GSM_MODEM_STATE_CHECK_GSM_COVERAGE) {
                    /* Assert related gprs error also */
                    g_tcp_gsm_modem.diag.gprs_connection_drop = TRUE;
                    g_tcp_gsm_modem.diag.gprs_registration_failure = TRUE;
                    g_tcp_gsm_modem.diag.gprs_registration_denied = TRUE;

                    r_tcp_device_reset_network_status();
                    g_tcp_gsm_modem.state = GSM_MODEM_STATE_CHECK_GSM_COVERAGE;
                }
            }
            else {
                /* Else, there's at least some signal */
                g_tcp_gsm_modem.diag.no_gsm_coverage = FALSE;
            }
		}
	}
	/* Event "+COPS:" Operator selection */
	else if (strstr((const char *)p_event->prefix.buffer, "+COPS:") != NULL) {
		if (r_tcp_device_event_handler_cops(p_event) == TRUE) {
			p_event->type = GSM_MODEM_EVENT_COPS;
            if (p_event->data.COPS.format == 0)
            {
                g_tcp_gsm_modem.info.operator = p_event->data.COPS.operator;
                R_RTC_Get_CalendarCounterValue(&g_tcp_gsm_modem.info.capture_time);
            }
            else if (p_event->data.COPS.format == 2)
            {
    			g_tcp_gsm_modem.info.cell_info.mcc = p_event->data.COPS.mcc;
    			g_tcp_gsm_modem.info.cell_info.mnc = p_event->data.COPS.mnc;
                R_RTC_Get_CalendarCounterValue(&g_tcp_gsm_modem.info.capture_time);
            }
            else
            {
                // Unhandled format value
            }
		}
	}
	/* Event "+ERAT:" Querying the Network Standards */
	else if (strstr((const char *)p_event->prefix.buffer, "+ERAT:") != NULL) {
		if (r_tcp_device_event_handler_erat(p_event) == TRUE) {
			p_event->type = GSM_MODEM_EVENT_ERAT;
            /* Mapping between current rat and ps attachment value, to be checked */
            /* Current rat
                    0: GSM
                    2: UTRAN
                    3: GSM w/EGPRS
                    4: UTRAN w/HSDPA
                PS attachment value:
                    (0) inactive,
                    (1) GPRS,
                    (2) EDGE,
                    (3) UMTS,
                    (4) HSDPA,
                    (5) LTE,
                    (6) CDMA
            */
            if (p_event->data.ERAT.current_rat == 0) {
                g_tcp_gsm_modem.info.ps_status = 0;
            }
            else if (p_event->data.ERAT.current_rat == 2) {
                g_tcp_gsm_modem.info.ps_status = 3;
            }
            else if (p_event->data.ERAT.current_rat == 3) {
                g_tcp_gsm_modem.info.ps_status = 2;
            }
            else if (p_event->data.ERAT.current_rat == 4) {
                g_tcp_gsm_modem.info.ps_status = 4;
            }
            else {
                //Unknown value
                g_tcp_gsm_modem.info.ps_status = 255;
            }
            R_RTC_Get_CalendarCounterValue(&g_tcp_gsm_modem.info.capture_time);
		}
	}
}

/*
 * Event receiver entry
 */
static void r_tcp_device_async_process_connect_event(uint8_t rx_byte)
{
	static uint8_t check_index = 0;
	static const uint8_t prefix[] = "Connect AcceptSocket=";
    uint8_t connect_socket_id;

    /* Special format unsolicited event (not following the format above) */
	if (check_index < sizeof(prefix) - 1)
	{
		if (rx_byte != prefix[check_index])
		{
            check_index = 0;
		}
        else
        {
			check_index++;
        }
	}
    else
    {
        /* Next byte after prefix is socket id */
        connect_socket_id = rx_byte - '0';

        if (connect_socket_id == 1)     // TODO: multiple TCP channel now fixed socket 1
        {
            /* Cast the irregular Connect format to event for later parsed incoming IP address in polling */
            g_tcp_at_event.prefix.count = sizeof(prefix) - 1;
            g_tcp_at_event.content.count = 0;
            memcpy(g_tcp_at_event.prefix.buffer, prefix, g_tcp_at_event.prefix.count);
            
            g_tcp_at_event.prefix.buffer[g_tcp_at_event.prefix.count] = 0;
            g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_CONTENT;
			
			/* Stop all current AT query */
			r_tcp_device_unregister_cmd_reply();
			
            /* Indicate to DLMS library connection for upcoming receiving byte (in case it come before polling processing) */
            g_tcp_gsm_modem.remote[connect_socket_id].is_outbound = FALSE;
			/* Start timeout */
            g_tcp_gsm_modem.remote[connect_socket_id].is_timeout = FALSE;
            g_tcp_gsm_modem.remote[connect_socket_id].timeout.count = g_tcp_gsm_modem.remote[connect_socket_id].timeout.initial;
            g_tcp_gsm_modem.remote[connect_socket_id].timeout.enable = TRUE;
            /* Acknowledge connect indication first with dummy address and port so incoming data can be processed */
            /* TODO: multi channel TCP, handle the socket_id and passed to connect indication */
            R_TCP_DEVICE_ConnectIndication(0, g_tcp_dummy_remote_port, (IpAddressPtr)&g_tcp_dummy_remote_ip_addr);
        }

        /* Reset the checking */
        check_index = 0;
    }
}

static void r_tcp_device_async_process_tcprecvs_event(uint8_t rx_byte)
{
	static uint8_t check_index = 0;
	static uint8_t socket_id = 0;
    static enum {
        PARSE_SOCKET,
        PARSE_LENGTH,
        PARSE_END,
    } content_parse_state;
    static uint16_t parsed_length = 0;

	static const uint8_t prefix[] = "+TCPRECV(S):";

	if (check_index < sizeof(prefix) - 1)
	{
		if (rx_byte != prefix[check_index])
		{
            check_index = 0;
		}
        else
        {
			check_index++;
        }
        
        content_parse_state = PARSE_SOCKET;
	}
    else
    {
        if (content_parse_state == PARSE_SOCKET)
        {
            /* End of socket_id info, prepare for receiving length info */
            if (rx_byte == ',')
            {
                parsed_length = 0;
                content_parse_state = PARSE_LENGTH;
            }
            else
            {
                /* Parse socket ID info */
                socket_id = rx_byte - '0';
                if (socket_id >= TCP_DEVICE_MAX_SOCKET)
                {
                    /* Unexpected socket ID, reset parsing */
                    check_index = 0;
                }
            }
        }
        else if (content_parse_state == PARSE_LENGTH)
        {
            /* Parse coming data length byte by byte */
    		if ('0' <= rx_byte && rx_byte <= '9') {
    			parsed_length *= 10;
    			parsed_length += rx_byte - '0';
    		}
            else
            {
                /* Wrong format */
                check_index = 0;
            }

            /* End parsing */
            if (rx_byte == ',')
            {
				/* Stop all current AT query */
				r_tcp_device_unregister_cmd_reply();
				
                /* Raise signal to route the upcoming data to DLMS library directly */
                g_tcp_gsm_modem.receiving_remain_bytes = parsed_length;
				g_tcp_gsm_modem.receiving_socket_id = socket_id;
                check_index = 0;
            }
        }
        else {
            /* Unexpected state */
            check_index = 0;
        }
    }
}

static uint8_t r_tcp_device_receive_unsolicited_event(uint8_t rx_byte, uint8_t use_timeout)
{
	uint8_t			result = FALSE;

	/*
	 * +<prefix>: <content>\r\n   
	 */

	/* Restart interframe timeout */
	if (use_timeout == TRUE) {
		g_tcp_at_event_timeout.count = g_tcp_at_event_timeout.initial;
		g_tcp_at_event_timeout.enable = TRUE;
	}
	else {
		g_tcp_at_event_timeout.enable = FALSE;
	}

	{
		switch (g_tcp_at_event.state)
		{
            case TCP_DEVICE_AT_EVENT_STATE_PLUS:			/* <plus> */
                if (rx_byte == '+') {
                    g_tcp_at_event.prefix.count = 0;
                    g_tcp_at_event.content.count = 0;
                    g_tcp_at_event.prefix.buffer[g_tcp_at_event.prefix.count++] = rx_byte;
                    g_tcp_at_event.prefix.buffer[g_tcp_at_event.prefix.count] = 0;
                    g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_PREFIX;
                }
                break;
            case TCP_DEVICE_AT_EVENT_STATE_PREFIX:			/* <prefix> */
				if (g_tcp_at_event.prefix.count < TCP_DEVICE_AT_EVENT_PREFIX_LENGTH) {
					g_tcp_at_event.prefix.buffer[g_tcp_at_event.prefix.count++] = rx_byte;
					g_tcp_at_event.prefix.buffer[g_tcp_at_event.prefix.count] = 0;
					if (rx_byte == ':') {
						g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_CONTENT;
					}
                    else if (rx_byte == '\n' && 
                            g_tcp_at_event.prefix.buffer[0] == '+' &&
                            memchr(g_tcp_at_event.prefix.buffer, ':', g_tcp_at_event.prefix.count) == NULL) 
                    {
                        /* Receive solicited message that not having ':' as prefix */
                        result = TRUE;
                        g_tcp_at_event.received = TRUE;
                    }
				}
				else {
                    r_tcp_device_acknowledge_event_received();
				}
				break;

			case TCP_DEVICE_AT_EVENT_STATE_CONTENT:			/* <content> */
				if (g_tcp_at_event.content.count < TCP_DEVICE_AT_EVENT_CONTENT_LENGTH) {
					g_tcp_at_event.content.buffer[g_tcp_at_event.content.count++] = rx_byte;
					g_tcp_at_event.content.buffer[g_tcp_at_event.content.count] = 0;
					if (rx_byte == '\n')
					{
						result = TRUE;
						g_tcp_at_event.received = TRUE;
					}
				}
				else {
                    r_tcp_device_acknowledge_event_received();
				}
				break;

			default:
                r_tcp_device_acknowledge_event_received();
				break;
		}
	}

	return (result);
}

/*
 * Manage to send & check reply
 */
static void r_tcp_device_send_cmd(AtCommand *p_cmd)
{
	uint16_t	length;
	uint8_t		input_args[TCP_DEVICE_DEFAULT_STRING_LENGTH];

	/* Send "p_cmd->p_cmd_str" SYNC first */
	if (strlen((const char *)p_cmd->p_cmd_str) > 0)
	{
		g_tcp_device_send_end = FALSE;
		WRP_UART0_SendData(p_cmd->p_cmd_str, strlen((const char *)p_cmd->p_cmd_str));
		while (g_tcp_device_send_end == FALSE);
	}
	
	/* Send additional input args get from the call of "p_cmd->fp_cmd_input" */
	if (p_cmd->fp_cmd_input != NULL) {
		memset(input_args, 0, TCP_DEVICE_DEFAULT_STRING_LENGTH);
		length = (*p_cmd->fp_cmd_input)(&g_tcp_gsm_modem, input_args, TCP_DEVICE_DEFAULT_STRING_LENGTH);
		if (length > 0) {
			g_tcp_device_send_end = FALSE;
			WRP_UART0_SendData(input_args, length);
			while (g_tcp_device_send_end == FALSE);
		}
	}

	/* Send \r\n as to complete the command input */
	g_tcp_device_send_end = FALSE;
	WRP_UART0_SendData((uint8_t *)"\r\n", 2);
	while (g_tcp_device_send_end == FALSE);
}

static void r_tcp_device_prepare_cmd_reply(void)
{
	g_tcp_at_reply.active = FALSE;
	memset(g_tcp_at_reply.buffer, 0, TCP_DEVICE_REPLY_BUFFER_MAX_LENGTH);
	g_tcp_at_reply.count = 0;
	g_tcp_at_reply.reply_ok = FALSE;
	g_tcp_at_reply.active = TRUE;
}

static void r_tcp_device_unregister_cmd_reply(void)
{
	g_tcp_at_reply.active = FALSE;
	g_tcp_at_reply.count = 0;
}

static uint8_t r_tcp_device_wait_send_prompt_sign_predicate(void)
{
    if (strstr((const char *)g_tcp_at_reply.buffer, (const char *)">\r\n") != NULL)
    {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

static uint8_t r_tcp_device_wait_send_predicate(void)
{
    uint8_t * pattern;
    /*
    * Check reply buffer to ensure data is pushed
    * Search for +TCPSEND and \r\n in reply buffer
    */
    if (g_tcp_at_reply.buffer != NULL)
    {
        pattern = (uint8_t *)strstr((const char *)g_tcp_at_reply.buffer, "+TCPSEND");
        if (pattern == NULL)
        {
            return FALSE;
        }

        pattern = (uint8_t *)strstr((const char *)pattern, "\r\n");
        if (pattern == NULL)
        {
            return FALSE;
        }

        return TRUE;
    }
    else {
        return FALSE;
    }
}

static AtCmdState r_tcp_device_check_cmd_reply(AtCommand *p_cmd)
{
	uint8_t  found_expected_reply = FALSE;
	uint8_t  reply_handler_ok = FALSE;
	AtEvent	 *p_event = NULL;
	uint16_t count = 0;

	/* Bypass expected reply check if NULL is specifed */
	if (p_cmd->p_expected_reply == NULL) {
		found_expected_reply = TRUE;
	}

	/* Bypass reply check if no handler is registered */
	if (p_cmd->fp_reply_handler == NULL) {
		reply_handler_ok = TRUE;
	}

	/* Emergency exit from power management */
	if (EVENT_IsLastGasp() == TRUE)
	{
		if (g_tcp_gsm_modem.state < GSM_MODEM_STATE_READY) {
			return AT_CMD_EMERGENCY_EXIT;
		}
	}

	/* Time out ? */
	if (g_tcp_at_reply.timeout == TRUE) {
		return AT_CMD_TIMEOUT;
	}

	/* Check for reply message, contain expected reply msg? */
	if (found_expected_reply == FALSE &&
		p_cmd->p_expected_reply != NULL &&
		strstr((const char *)g_tcp_at_reply.buffer, (const char *)p_cmd->p_expected_reply) != NULL)
	{
		found_expected_reply = TRUE;
	}

	/* Scan for the unsolicted event inside the reply */
	p_event = NULL;
    r_tcp_device_acknowledge_event_received();
	while (count < g_tcp_at_reply.count) {
		if (r_tcp_device_receive_unsolicited_event(g_tcp_at_reply.buffer[count], FALSE) == TRUE) {
			r_tcp_device_event_handler_default(&g_tcp_at_event);
			p_event = &g_tcp_at_event;
		}
		count++;
	}

	/* Check the reply handler ok */
	if (reply_handler_ok == FALSE && p_cmd->fp_reply_handler != NULL) {
		if ((*p_cmd->fp_reply_handler)(&g_tcp_gsm_modem, g_tcp_at_reply.buffer, g_tcp_at_reply.count, p_event) == TRUE) {
			reply_handler_ok = TRUE;
		}
	}

	if (p_event != NULL) {
        r_tcp_device_acknowledge_event_received();
	}

	if (found_expected_reply == TRUE && reply_handler_ok == TRUE) {
		return AT_CMD_REPLY_AS_EXPECTED;
	}

	return (g_tcp_at_reply.state);
}

static AtCmdResult r_tcp_device_execute_at_runner(AtRunner *p_runner, uint8_t reset_if_fails)
{
	AtCommand	*p_cmd = NULL;
	AtCmdState	state;
	AtCmdResult	result = AT_CMD_RESULT_WAIT_REPLY;

	if (p_runner->index < p_runner->length)
	{
		/* Get cmd & send out */
		p_cmd = (AtCommand *)&p_runner->p_commands[p_runner->index];

		switch (g_tcp_at_reply.state)
		{
			case AT_CMD_START:

				/* Prepare reply buffer */
				r_tcp_device_prepare_cmd_reply();
				g_tcp_at_event_timeout.enable = FALSE;
				//g_tcp_at_event.received = FALSE;
				//g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_PREFIX;
                r_tcp_device_acknowledge_event_received();

				/* Send, start timeout timer */
				r_tcp_device_send_cmd(p_cmd);
				g_tcp_at_reply.timeout = FALSE;
				g_tcp_at_timeout_timer.initial = p_cmd->timeout;
				g_tcp_at_timeout_timer.count = p_cmd->timeout;
				g_tcp_at_timeout_timer.enable = TRUE;

				g_tcp_at_reply.state = AT_CMD_SENT;
				break;

			case AT_CMD_SENT:

				/* Wait for reply or timeout happen */
				state = r_tcp_device_check_cmd_reply(p_cmd);
				if (state == AT_CMD_TIMEOUT ||
					state == AT_CMD_REPLY_AS_EXPECTED ||
					state == AT_CMD_EMERGENCY_EXIT)
				{
					///* Unregister cmd reply from UART rx interrupt */
					g_tcp_at_event_timeout.enable = FALSE;
					//g_tcp_at_event.received = FALSE;
					//g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_PREFIX;
                    r_tcp_device_acknowledge_event_received();
					r_tcp_device_unregister_cmd_reply();
				}
				g_tcp_at_reply.state = state;
				break;

			case AT_CMD_REPLY_AS_EXPECTED:
				g_tcp_at_reply.reply_ok = TRUE;

			case AT_CMD_TIMEOUT:

				/* Start delay after cmd (if any) */
				if (p_cmd->delay > 0) {
					g_tcp_at_reply.timeout = FALSE;
					g_tcp_at_timeout_timer.initial = p_cmd->delay;
					g_tcp_at_timeout_timer.count = p_cmd->delay;
					g_tcp_at_timeout_timer.enable = TRUE;
				}
				g_tcp_at_reply.state = AT_CMD_DELAY_AFTER_CMD;
				break;

			case AT_CMD_DELAY_AFTER_CMD:

				/* Emergency exit request from power management */
				if (EVENT_IsLastGasp() == TRUE)
				{
					if (g_tcp_gsm_modem.state < GSM_MODEM_STATE_READY) {
						g_tcp_at_reply.state = AT_CMD_EMERGENCY_EXIT;
						break;
					}
				}

				if (p_cmd->delay == 0 || g_tcp_at_reply.timeout == TRUE) {

					/* Check and jump to next command */
					if (g_tcp_at_reply.reply_ok == TRUE) {
						result = AT_CMD_RESULT_OK;
						p_runner->index++;
						p_runner->retry = TCP_DEVICE_AT_COMMAND_RETRIES_MAX - 1;
                        /* Modem replied, reset the error code but command need to have expected reply or reply handler */
                        if (p_cmd->p_expected_reply != NULL ||
                            p_cmd->fp_reply_handler != NULL) {
                            g_tcp_gsm_modem.diag.modem_reply_failure = FALSE;
                        }
					}
					else {	/* AT_CMD_TIMEOUT, retry until reset whole script */
						result = AT_CMD_RESULT_TIMED_OUT;
						if (p_runner->retry > 0) {
							p_runner->retry--;
						}
						else {
							if (reset_if_fails) {
								if (p_runner->reboot > 0) {
									p_runner->reboot--;
									p_runner->index = 0;
									p_runner->retry = TCP_DEVICE_AT_COMMAND_RETRIES_MAX - 1;
								}
								else {
                                    /* All commands time out, modem fail to reply */
                                    g_tcp_gsm_modem.diag.modem_reply_failure = TRUE;
									R_TCP_DEVICE_RebootGsmModem();
								}
							}
						}
					}
                    r_tcp_device_acknowledge_event_received();

					g_tcp_at_reply.state = AT_CMD_START;
				}

				break;

			case AT_CMD_EMERGENCY_EXIT:

				/* Stop whole script */
				p_runner->index = p_runner->length;
				g_tcp_at_reply.state = AT_CMD_START;

				break;

			default:
				g_tcp_at_reply.state = AT_CMD_START;
				break;
		}

		R_WDT_Restart();
	}
    else
    {
        /* End of script, terminate script */
        result = AT_CMD_RESULT_OK;
    }

	return (result);
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_Init
* Interface     : void R_TCP_DEVICE_Init(void)
* Description   : Initial TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_Init(TcpChannel tcp_channel)
{
	if (tcp_channel == 0) {

		/* Init & start UART port for Gsm Device */
		WRP_UART0_Init();
		WRP_UART0_SetBaudRate(WRP_UART_BAUD_RATE_9600);
		WRP_UART0_ConfigHDLCProtocol();
		WRP_UART0_Start();

		/* AT reply */
		g_tcp_device_send_end = TRUE;
		g_tcp_at_reply.active = FALSE;
		g_tcp_at_reply.count = 0;
		g_tcp_at_reply.timeout = FALSE;
		memset(g_tcp_at_reply.buffer, 0, TCP_DEVICE_REPLY_BUFFER_MAX_LENGTH);

		/* AT event */
        r_tcp_device_acknowledge_event_received();
		//g_tcp_at_event.received = FALSE;
		//g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_PLUS;

		/* AT event interframe timeout */
		g_tcp_at_event_timeout.initial = TCP_DEVICE_EVENT_INTERFRAME_TIMEOUT;
		g_tcp_at_event_timeout.count = 0;
		g_tcp_at_event_timeout.enable = FALSE;

		/*
		 * Init vars to manage gsm device
		 */
		 
		/* Initiailize settings (APN name restored by DLMS application) */
        memset(&g_tcp_gsm_modem.setting.quality_of_service, 0, sizeof(g_tcp_gsm_modem.setting.quality_of_service));

        /* Status diagnostic for 3G modem */
        memset(&g_tcp_gsm_modem.diag, 0, sizeof(g_tcp_gsm_modem.diag));
        /* By default, all error related to modem initialization and network are asserted */
        g_tcp_gsm_modem.diag.modem_mounted_count = TCP_DEVICE_MODEM_MOUNTED_CONFIRM_TIME;
        g_tcp_gsm_modem.diag.modem_mounted = FALSE;
        g_tcp_gsm_modem.diag.modem_reply_failure = TRUE;
        g_tcp_gsm_modem.diag.sim_inserted = FALSE;
        g_tcp_gsm_modem.diag.sim_good = FALSE;
        g_tcp_gsm_modem.diag.no_gsm_coverage = TRUE;
        g_tcp_gsm_modem.diag.gprs_registration_failure = TRUE;
        g_tcp_gsm_modem.diag.gprs_registration_denied = TRUE;
        g_tcp_gsm_modem.diag.gprs_connection_drop = TRUE;

		g_tcp_gsm_modem.state = GSM_MODEM_STATE_UNINITIALIZED;

		/* Boot command list */
		g_tcp_gsm_modem.boot.p_commands = g_tcp_device_boot_script;
		g_tcp_gsm_modem.boot.length = sizeof(g_tcp_device_boot_script) / sizeof(AtCommand);
		g_tcp_gsm_modem.boot.index = g_tcp_gsm_modem.boot.length;

        /* Sim command list */
        g_tcp_gsm_modem.sim.p_commands = g_tcp_device_query_sim;
        g_tcp_gsm_modem.sim.length = sizeof(g_tcp_device_query_sim) / sizeof(AtCommand);
        g_tcp_gsm_modem.sim.index = g_tcp_gsm_modem.sim.length;

        /* GSM signal coverage command list */
        g_tcp_gsm_modem.signal.p_commands = g_tcp_device_query_signal;
        g_tcp_gsm_modem.signal.length = sizeof(g_tcp_device_query_signal) / sizeof(AtCommand);
        g_tcp_gsm_modem.signal.index = g_tcp_gsm_modem.signal.length;

        /* Net registration command list */
        g_tcp_gsm_modem.net_reg.p_commands = g_tcp_device_network_registration;
        g_tcp_gsm_modem.net_reg.length = sizeof(g_tcp_device_network_registration) / sizeof(AtCommand);
        g_tcp_gsm_modem.net_reg.index = g_tcp_gsm_modem.net_reg.length;

        /* Connect command list */
        g_tcp_gsm_modem.connect.p_commands = g_tcp_device_establish_connection;
        g_tcp_gsm_modem.connect.length = sizeof(g_tcp_device_establish_connection) / sizeof(AtCommand);
        g_tcp_gsm_modem.connect.index = g_tcp_gsm_modem.connect.length;

		/* Listen command list */
		g_tcp_gsm_modem.listen.p_commands = g_tcp_device_socket1_listen_script;
		g_tcp_gsm_modem.listen.length = sizeof(g_tcp_device_socket1_listen_script) / sizeof(AtCommand);
		g_tcp_gsm_modem.listen.index = g_tcp_gsm_modem.listen.length;

		/* Query command list */
		g_tcp_gsm_modem.query.p_commands = g_tcp_device_query_info_and_setting;
		g_tcp_gsm_modem.query.length = sizeof(g_tcp_device_query_info_and_setting) / sizeof(AtCommand);
		g_tcp_gsm_modem.query.index = g_tcp_gsm_modem.query.length;

        /* Close timeout socket */
		g_tcp_gsm_modem.close_connect.p_commands = g_tcp_device_close_connection_at_commands;
		g_tcp_gsm_modem.close_connect.length = sizeof(g_tcp_device_close_connection_at_commands) / sizeof(AtCommand);
		g_tcp_gsm_modem.close_connect.index = g_tcp_gsm_modem.close_connect.length;

		/* Start boot up GSM Modem */
		R_TCP_DEVICE_RebootGsmModem();
	}
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_Start
* Interface     : void R_TCP_DEVICE_Start(void)
* Description   : Start TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_Start(TcpChannel tcp_channel)
{
	if (tcp_channel == 0) {
		/* Do nothing, let the UART port keep running for Gsm Modem */
	}
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_Stop
* Interface     : void R_TCP_DEVICE_Stop(void)
* Description   : Stop TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_Stop(TcpChannel tcp_channel)
{
	if (tcp_channel == 0) {
		/* Do nothing, let the UART port keep running for Gsm Modem */
	}
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_PollingProcess
* Interface     : void R_TCP_DEVICE_PollingProcess(void)
* Description   : Polling process of TCP device
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_PollingProcess(TcpChannel tcp_channel)
{
	if (tcp_channel == 0)
	{
        /* Stop further processing if modem is not mounted */
        if (g_tcp_gsm_modem.diag.modem_mounted == FALSE) {
            return;
        }

        /* Modem need small amount of time delay before sending any command over */
        if (g_tcp_gsm_modem.reboot_delay > 0) {
            return;
        }

		switch (g_tcp_gsm_modem.state)
		{
			case GSM_MODEM_STATE_INITIALIZED:
				/* Boot up H310 */
				if (r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.boot, TRUE) == AT_CMD_RESULT_OK) {
					if (g_tcp_gsm_modem.boot.index >= g_tcp_gsm_modem.boot.length) {
						r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.sim);
						g_tcp_gsm_modem.state = GSM_MODEM_STATE_CHECK_USIM;
					}
				}
				break;
            case GSM_MODEM_STATE_CHECK_USIM:
                /* SIM card checking */
                if (r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.sim, TRUE) == AT_CMD_RESULT_OK) {
                    if (g_tcp_gsm_modem.sim.index >= g_tcp_gsm_modem.sim.length) {
                        r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.signal);
                        g_tcp_gsm_modem.state = GSM_MODEM_STATE_CHECK_GSM_COVERAGE;
                    }
                }
                break;
            case GSM_MODEM_STATE_CHECK_GSM_COVERAGE:
                /* GSM coverage checking */
                if (r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.signal, TRUE) == AT_CMD_RESULT_OK) {
                    if (g_tcp_gsm_modem.signal.index >= g_tcp_gsm_modem.signal.length) {
                        r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.net_reg);
                        g_tcp_gsm_modem.state = GSM_MODEM_STATE_CHECK_NETWORK_REGISTRATION;
                    }
                }
                break;
            case GSM_MODEM_STATE_CHECK_NETWORK_REGISTRATION:
                /* Network registration checking */
                if (r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.net_reg, TRUE) == AT_CMD_RESULT_OK) {
                    if (g_tcp_gsm_modem.net_reg.index >= g_tcp_gsm_modem.net_reg.length) {
						/* Check APN configuration */
						if (g_tcp_gsm_modem.setting.apn_name.size == 0)
						{
							g_tcp_gsm_modem.diag.no_apn_configured = TRUE;
							return;
						}
						else
						{
							g_tcp_gsm_modem.diag.no_apn_configured = FALSE;
						}
                        r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.connect);
                        g_tcp_gsm_modem.state = GSM_MODEM_STATE_ESTABLISH_CONNECTION;
                    }
                }
                break;
            case GSM_MODEM_STATE_ESTABLISH_CONNECTION:
                if (r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.connect, TRUE) == AT_CMD_RESULT_OK) {
                    if (g_tcp_gsm_modem.connect.index >= g_tcp_gsm_modem.connect.length) {
                        r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.query);
                        g_tcp_gsm_modem.state = GSM_MODEM_STATE_BOOT_UP_QUERY_INFO;
                    }
                }
                break;
			case GSM_MODEM_STATE_BOOT_UP_QUERY_INFO:
				if (r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.query, TRUE) == AT_CMD_RESULT_OK) {
					if (g_tcp_gsm_modem.query.index >= g_tcp_gsm_modem.query.length) {
						r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.listen);
						g_tcp_gsm_modem.state = GSM_MODEM_STATE_START_LISTEN_SOCKET;
					}
				}
				break;

			case GSM_MODEM_STATE_START_LISTEN_SOCKET:
				/* Execute commands to listen TCP connection */
				if (r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.listen, TRUE) == AT_CMD_RESULT_OK) {
					if (g_tcp_gsm_modem.listen.index >= g_tcp_gsm_modem.listen.length) {
						g_tcp_gsm_modem.state = GSM_MODEM_STATE_READY;
                        g_tcp_gsm_interval_timer.enable = TRUE;
                        /* Temporarily disable the first breath until +MIPCALL:0 captured */
                        //R_TCP_DEVICE_FirstBreathEventHappenCallback();
                    }
				}
				break;

			case GSM_MODEM_STATE_READY:
				/*
				 * When no connection active, query Gsm Modem info
				 */
                // TODO: multiple TCP channel now fixed channel 0
				if (R_TCP_GetConnectionState(0) == TCP_DISCONNECTED)
				{
					if (g_tcp_gsm_modem.periodic_job == TRUE) {
						r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.query);
						g_tcp_gsm_modem.periodic_job = FALSE;
					}
					r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.query, TRUE);
				}
                else
                {
                    /* Does socket timeout reached? */
                    if (g_tcp_gsm_modem.remote[1].is_timeout == TRUE)
                    {
						/* Synchronously close connection */
						r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.close_connect);
						while(g_tcp_gsm_modem.close_connect.index < g_tcp_gsm_modem.close_connect.length)
						{
							if (r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.close_connect, TRUE) == AT_CMD_RESULT_TIMED_OUT)
							{
								break;
							}
							R_WDT_Restart();
						}
                        g_tcp_gsm_modem.remote[1].is_timeout = FALSE;
                    }
                }
				break;

			default:
				break;
		}

		/*
		 * Unsolicted event process
		 */
		if (g_tcp_at_event.received == TRUE)
		{
			r_tcp_device_event_handler_default(&g_tcp_at_event);
            r_tcp_device_acknowledge_event_received();
		}
	}

	R_WDT_Restart();
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_GetConfig
* Interface     : uint8_t R_TCP_DEVICE_GetConfig(
*               :     TcpChannel tcp_channel ,
*               :     TcpPortConfig* p_config,
*               : );
* Description   : Get config of TCP device (Port number, IP address), put to p_config
* Arguments     : TcpChannel tcp_channel :
*               : TcpPortConfig* p_config:
* Function Calls:
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_GetConfig(TcpChannel tcp_channel, TcpPortConfig* p_config)
{
	p_config->local_tcp_port = g_tcp_gsm_modem.local.port_number;
	p_config->local_ip_address = &g_tcp_gsm_modem.local.ip;
	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_SetConfig
* Interface     : uint8_t R_TCP_DEVICE_SetConfig(
*               :     TcpChannel tcp_channel ,
*               :     TcpPortConfig* p_config,
*               : );
* Description   : Set config of TCP device (Port number, IP address), read from p_config
* Arguments     : TcpChannel tcp_channel :
*               : TcpPortConfig* p_config:
* Function Calls:
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_SetConfig(TcpChannel tcp_channel, TcpPortConfig* p_config)
{
	/* No static IP support yet */
	return FALSE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_ConnectRequest
* Interface     : uint8_t R_TCP_DEVICE_ConnectRequest(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               : );
* Description   : Request a TCP connection to a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_ConnectRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address)
{
    uint16_t		fails_count;

	AtRunner runner_open = { g_tcp_device_connect_to_server_at_commands, sizeof(g_tcp_device_connect_to_server_at_commands) / sizeof(AtCommand), 0, 0, 0 };

    if (tcp_channel < TCP_DEVICE_MAX_SOCKET)
    {
        /* Diagnose destination, not affect push operation, just for raising diag code */
        if (r_tcp_device_is_valid_destination(remote_tcp_port, remote_ip_address) == FALSE)
        {
            /* Not allow to open the connection if remote destination is invalid and mark the error code */
            const uint8_t error_string[] = "Remote destination unknown";
            g_tcp_gsm_modem.diag.remote_destination_invalid = TRUE;
            R_TCP_DEVICE_ConnectConfirm(0, FALSE, (uint8_t *)error_string, strlen((const char *)error_string));
        }
        else 
        {
            /* Correct remote destination, try opening */
            g_tcp_gsm_modem.diag.remote_destination_invalid = FALSE;
            
            // TODO: multiple TCP channel now fixed socket 1
            /* Note: Currently push service call use R_TCP_WRP_TryOpenConnection to avoid pushing during active connection
		     * Before push, attempt to close the conection in case it opened in a timed out TCPSETUP operation
             */

            /* Open socket to remote */
            fails_count = 0;
            memcpy(g_tcp_gsm_modem.remote[1].ip_buffer, remote_ip_address->p_addr, TCP_DEVICE_IP_SIZE);
            g_tcp_gsm_modem.remote[1].port_number = remote_tcp_port;
			/* Update the requesting type */
			g_tcp_gsm_modem.remote[1].is_outbound = TRUE;
    		r_tcp_device_start_at_runner_execution(&runner_open);
    		while (runner_open.index < runner_open.length)
    		{
    			if (r_tcp_device_execute_at_runner(&runner_open, TRUE) == AT_CMD_RESULT_TIMED_OUT) {
    				fails_count++;
    			}

    			/* Fail 1 times script stop */
    			if (fails_count > 1) {
    				break;
    			}
    			R_WDT_Restart();
    		}
        }
    }

	// TODO, fixed DLMS TCP channel 0
    return (R_TCP_GetConnectionState(0));
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_ConnectResponse
* Interface     : uint8_t R_TCP_DEVICE_ConnectResponse(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               :     uint8_t result                ,
*               : );
* Description   : Response to a TCP connection from a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
*               : uint8_t result                : Connection req from remote station is accepted (TRUE) or reject (FALSE)
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_ConnectResponse(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t result)
{
	/*
	 * No need the response signal, TCP on GSM module is connected already
	 * Dummy TRUE to keep library run
	 */
	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_DisconnectRequest
* Interface     : uint8_t R_TCP_DEVICE_DisconnectRequest(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               : );
* Description   : Request a TCP disconnect signal to remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DisconnectRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address)
{
	uint16_t	fails_count;

	AtRunner runner = { g_tcp_device_close_server_connection_at_commands, sizeof(g_tcp_device_close_server_connection_at_commands) / sizeof(AtCommand), 0, 0, 0 };

    if (tcp_channel < TCP_DEVICE_MAX_SOCKET)
	{
		/* Update the requesting type */
		g_tcp_gsm_modem.remote[1].is_outbound = TRUE;
		
		r_tcp_device_start_at_runner_execution(&runner);
        fails_count = 0;
		while (runner.index < runner.length)
		{
			if (r_tcp_device_execute_at_runner(&runner, TRUE) == AT_CMD_RESULT_TIMED_OUT) {
				fails_count++;
			}
			
    		/* Fail 1 times script stop */
			if (fails_count > 1) {
				break;
			}
			R_WDT_Restart();
		}
	}

	// TODO, fixed channel DLMS TCP channel 0
	return (R_TCP_GetConnectionState(0));
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_DisconnectResponse
* Interface     : uint8_t R_TCP_DEVICE_DisconnectResponse(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               :     uint8_t result                ,
*               : );
* Description   : Response to a TCP disconnection from a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
*               : uint8_t result                : Disconnection req from remote station is accepted (TRUE) or reject (FALSE)
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DisconnectResponse(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t result)
{
	/* No need the response signal, dummy TRUE to keep library run */
	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_DataRequest
* Interface     : uint8_t R_TCP_DEVICE_DataRequest(
*               :     TcpChannel tcp_channel        ,
*               :     TcpPort remote_tcp_port       ,
*               :     IpAddressPtr remote_ip_address,
*               :     uint8_t * data                ,
*               :     uint16_t length               ,
*               : );
* Description   : Request to send data to a remote station (remote_tcp_port, remote_ip_address)
* Arguments     : TcpChannel tcp_channel        : Channel ID associated with TCP device
*               : TcpPort remote_tcp_port       : Remote station TCP port
*               : IpAddressPtr remote_ip_address: Remote station IP address
*               : uint8_t * data                : Input data buffer pointer
*               : uint16_t length               : Input data length
* Function Calls:
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DataRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t *data, uint16_t length)
{
	uint8_t		status = FALSE;
	uint8_t		buffer[TCP_DEVICE_DEFAULT_STRING_LENGTH];
	uint16_t	count = 0;
    
	if (tcp_channel < TCP_DEVICE_MAX_SOCKET)
	{
        if (g_tcp_gsm_modem.remote[1].is_outbound == FALSE)     // TODO: multiple TCP channel now fixed socket 1
        {
			/* Connection initiated by local */
            count = sprintf((char *)buffer, "AT+TCPSENDS=%u,%u\r\n", 1, length);
        }
        else
        {
			/* Connection initiated by remote */
            count = sprintf((char *)buffer, "AT+TCPSEND=%u,%u\r\n", 1, length);
        }
        /* Send command */
		g_tcp_device_send_end = FALSE;
        R_WDT_Restart();
		WRP_UART0_SendData(buffer, count);
		while (g_tcp_device_send_end == FALSE);

		/* Prepare reply buffer */
		r_tcp_device_prepare_cmd_reply();
        
		/* Wait until data prompt sign appear */
        WRP_EXT_HwDelay(500, r_tcp_device_wait_send_prompt_sign_predicate);
		
		/* Send out all bytes in HEX (either received the prompt or timeout) */
        status = TRUE;
		
		/* Send out all bytes in HEX */
		g_tcp_device_send_end = FALSE;
		WRP_UART0_SendData(data, length);
		while (g_tcp_device_send_end == FALSE);

		/* Wait for timeout or until receive send confirmed to terminate */
        status = WRP_EXT_HwDelay(4000, r_tcp_device_wait_send_predicate);

        if (status != WRP_EXT_HW_DELAY_TIMEOUT) {
            status = TRUE;
        }
        else {
            status = FALSE;
        }

		/* Unregister cmd reply from UART rx interrupt */
		g_tcp_at_event_timeout.enable = FALSE;
        r_tcp_device_acknowledge_event_received();
		r_tcp_device_unregister_cmd_reply();
//        g_tcp_gsm_modem.pushing_lastgasp = FALSE;
	}

    if (status == FALSE) {
        g_tcp_gsm_modem.diag.remote_data_sending_failure = TRUE;
    }
    else {
        g_tcp_gsm_modem.diag.remote_data_sending_failure = FALSE;
    }

    /* Reset socket timeout */
    // TODO: multiple TCP channel now fixed socket 1
    g_tcp_gsm_modem.remote[1].timeout.count = 
        g_tcp_gsm_modem.remote[1].timeout.initial;
	
	/* DataConfirm set in command, not in event handler 
	   as TCPSEND or TCPSEND(S) not have socket id information when error 
	*/

	/* Confirm as data request is finished, TODO: simultaneous operation */
	R_TCP_DEVICE_DataConfirm(0, status);

	return TRUE;
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_RebootGsmModem
* Interface     : void R_TCP_DEVICE_RebootGsmModem(void)
* Description   : Trigger to reboot Gsm Modem 
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_RebootGsmModem(void)
{
    uint16_t i;
	{
        /* When reboot, do power cycle, timer should be running at this point */
#if (TCP_DEVICE_MODULE_POWER_CONTROL_SUPPORT == TRUE)
        BIT_SELECT(P13, 0) = 1;                         /* Enable 5.0V supply to modem daughter board */
        BIT_SELECT(P5, 2) = 1;                          /* Turn off 5V-3.8V DC-DC converter on modem daughter board */
        BIT_SELECT(P0, 3) = 1;                          /* Modem On_Off pin high (by disabled transistor, let the pin pull high internally */
        WRP_EXT_HwDelay(100, NULL);                     /* Wait for cap to discharge */
        BIT_SELECT(P5, 2) = 0;                          /* Turn on 5V-3.8V DC-DC converter on modem daughter board */
        WRP_EXT_HwDelay(1, NULL);                       /* Wait for cap to charge in */
        BIT_SELECT(P0, 3) = 0;                          /* Pull modem On_Off pin low for 0.5s to 1s period */
        WRP_EXT_HwDelay(600, NULL);                     /* Wait safe value 0.6s */
        BIT_SELECT(P0, 3) = 1;                          /* Modem On_Off pin high (by disabled transistor, let the pin pull high internally */
#endif
		/* Reset all state & event receiver */
		/* Settting & Info */
		/* g_tcp_gsm_modem.setting is backup in EEPROM */
        memset(&g_tcp_gsm_modem.info, 0, sizeof(g_tcp_gsm_modem.info));
        //g_tcp_gsm_modem.setting.apn_name.size = strlen(TCP_DEVICE_DEFAULT_APN_NAME)
        //memcpy(g_tcp_gsm_modem.setting.apn_name, TCP_DEVICE_DEFAULT_APN_NAME, g_tcp_gsm_modem.setting.apn_name.size);

        /* Delay after modem reboot */
        g_tcp_gsm_modem.reboot_delay = TCP_DEVICE_DELAY_COMMAND_AFTER_REBOOT;

        /* Trigger */
        g_tcp_gsm_modem.periodic_job = FALSE;
        
        /* Local ipv6 & port number */
        g_tcp_gsm_modem.local.port_number = 4059;
        g_tcp_gsm_modem.local.ip.p_addr = g_tcp_gsm_modem.local.ip_buffer;
        g_tcp_gsm_modem.local.ip.size = TCP_DEVICE_IP_SIZE;
        memset(g_tcp_gsm_modem.local.ip_buffer, 0, TCP_DEVICE_IP_SIZE);

        /* Remote ip6 & port number */
        for (i = 0; i < TCP_DEVICE_MAX_SOCKET; i++)
        {
            g_tcp_gsm_modem.remote[i].port_number = 4059;
            g_tcp_gsm_modem.remote[i].ip.p_addr = g_tcp_gsm_modem.remote[i].ip_buffer;
            g_tcp_gsm_modem.remote[i].ip.size = TCP_DEVICE_IP_SIZE;
            memset(g_tcp_gsm_modem.remote[i].ip_buffer, 0, TCP_DEVICE_IP_SIZE);
            g_tcp_gsm_modem.remote[i].is_timeout = FALSE;
            g_tcp_gsm_modem.remote[i].is_outbound = FALSE;
            g_tcp_gsm_modem.remote[i].timeout.initial = TCP_DEVICE_INACTIVE_SOCKET_TIMEOUT;
            g_tcp_gsm_modem.remote[i].timeout.count = TCP_DEVICE_INACTIVE_SOCKET_TIMEOUT;
            g_tcp_gsm_modem.remote[i].timeout.enable = FALSE;
        }
        g_tcp_gsm_modem.receiving_remain_bytes = 0;
        g_tcp_gsm_modem.receiving_socket_id = TCP_DEVICE_SOCKET_ID_NO_CONNECTION;

        /* DNS Server */
        memset(g_tcp_gsm_modem.dns_server.primary, 0, TCP_DEVICE_IP_SIZE);
        memset(g_tcp_gsm_modem.dns_server.secondary, 0, TCP_DEVICE_IP_SIZE);

        g_tcp_gsm_modem.state = GSM_MODEM_STATE_INITIALIZED;

        /* Gsm Modem Interval timer, start after init */
        g_tcp_gsm_interval_timer.initial = TCP_DEVICE_PERIODIC_CHECK_INTERVAL_TIME;
        g_tcp_gsm_interval_timer.count = g_tcp_gsm_interval_timer.initial;
        g_tcp_gsm_interval_timer.enable = FALSE;

        /* Gsm Modem Timeout Timer for AT Commands */
        g_tcp_at_timeout_timer.initial = 0;
        g_tcp_at_timeout_timer.count = 0;
        g_tcp_at_timeout_timer.enable = FALSE;

        g_tcp_gsm_modem.pushing_lastgasp = FALSE;
		g_tcp_at_event.received = FALSE;

		/* Start boot up GSM Modem */
		r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.boot);
	}
}

/******************************************************************************
* Function Name : R_TCP_DEVICE_FirstBreathEventHappenCallback
* Interface     : void R_TCP_DEVICE_FirstBreathEventHappenCallback(void)
* Description   : Callback to announce Gsm Modem rebooted and IP changed
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_TCP_DEVICE_FirstBreathEventHappenCallback(void)
{
	/* Trigger to do PUSH as Gsm Modem has finished reboot and IP changed */
	//R_DLMS_EventReport_FirstBreath();
}

/*
 * Usage of TCP device service callbacks
 */

/*
* R_TCP_DEVICE_ConnectConfirm(TcpChannel tcp_channel, uint8_t result, uint8_t *reason, uint16_t reason_length);
* ---
* R_TCP_DEVICE_ConnectConfirm() is used to confirm about the last R_TCP_DEVICE_ConnectRequest() call,
* Normally it is called once remote station has response for the R_TCP_DEVICE_ConnectRequest()
*/

/*
* R_TCP_DEVICE_ConnectIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address);
* ---
* R_TCP_DEVICE_ConnectIndication() is used to indicate that there is a connection request event raised from remote station,
* This function shall be called once remote station sent connection request to this device
*/

/*
* R_TCP_DEVICE_DisconnectConfirm(TcpChannel tcp_channel, uint8_t result, uint8_t *reason, uint16_t reason_length);
* ---
* R_TCP_DEVICE_DisconnectConfirm() is used to confirm about the last R_TCP_DEVICE_DisconnectRequest() call,
* Normally it is called once remote station has response for the R_TCP_DEVICE_DisconnectRequest()
*/

/*
* R_TCP_DEVICE_DisconnectIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, TcpDisconnectReason reason);
* ---
* R_TCP_DEVICE_DisconnectIndication() is used to indicate that there is a disconnection request event raised from remote station,
* This function shall be called once remote station sent disconnection request to this device
*/

/*
* R_TCP_DEVICE_AbortIndication(TcpChannel tcp_channel, uint8_t *reason, uint16_t reason_length);
* ---
* R_TCP_DEVICE_AbortIndication() is used to indicate that there is an interruption event raised from local or from remote station,
* This function shall be called once there is an interruption happen between this device and remote station
*/

/*
* R_TCP_DEVICE_DataConfirm(TcpChannel tcp_channel, uint8_t result);
* ---
* R_TCP_DEVICE_DataConfirm() is used to confirm about the last R_TCP_DEVICE_DataRequest() call,
* Normally it is called once to confirm about the data transmition end on the R_TCP_DEVICE_DataRequest()
*/

/*
* R_TCP_DEVICE_DataIndication(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t *rx_buffer, uint16_t rx_buffer_length);
* ---
* R_TCP_DEVICE_DataIndication() is used to indicate that there is data received from remote station,
* It is able to put fragmented data to R_TCP_DEVICE_DataIndication() and call multiple time. WPDU is concat & process normally.
*/

/*
* R_TCP_DEVICE_DataErrorIndication(TcpChannel tcp_channel);
* ---
* R_TCP_DEVICE_DataErrorIndication() is used to indicate that there is data received error happen on this device
*/

/******************************************************************************
* Function Name : R_TCP_WRP_UartPhyReceiveData
* Interface     : void R_TCP_WRP_UartPhyReceiveData(TcpChannel channel, uint8_t received_byte)
* Description   :
* Arguments     : TcpChannel channel   :
*               : uint8_t received_byte:
* Function Calls:
* Return Value  : void
******************************************************************************/
void R_TCP_WRP_UartPhyReceiveData(TcpChannel channel, uint8_t received_byte)
{
    uint16_t i;

    /* channel argument is obsolete, the channel (or socket_id) is identify internally */

	/* PDU receiving after +TCPRECV or +TCPRECV(S), route directly to DLMS library */
    if (g_tcp_gsm_modem.receiving_socket_id != TCP_DEVICE_SOCKET_ID_NO_CONNECTION)
    {
        /* Check if receiving_socket_id is the first then route to DLMS library else discard receiving bytes */
        if (g_tcp_gsm_modem.receiving_socket_id == 1)       // TODO: multiple TCP channel now fixed socket 1
        {
    		R_TCP_DEVICE_DataIndication(
    			0,
    			4059,
    			(IpAddressPtr)&g_tcp_gsm_modem.remote[g_tcp_gsm_modem.receiving_socket_id].ip,
    			&received_byte,
    			1
    		);
        }

        /* Either route to DLMS library or not, still handle the receiving byte count */
        g_tcp_gsm_modem.receiving_remain_bytes--;
        if (g_tcp_gsm_modem.receiving_remain_bytes == 0)
        {
            /* Reset socket timeout */
            g_tcp_gsm_modem.remote[g_tcp_gsm_modem.receiving_socket_id].timeout.count = 
                g_tcp_gsm_modem.remote[g_tcp_gsm_modem.receiving_socket_id].timeout.initial;
            g_tcp_gsm_modem.receiving_socket_id = TCP_DEVICE_SOCKET_ID_NO_CONNECTION;
        }
    }
    else 
    {
	    /* Byte-by-byte processing events:  */
	    r_tcp_device_async_process_connect_event(received_byte);
	    r_tcp_device_async_process_tcprecvs_event(received_byte);
	
		/* Fill up the reply buffer */
		if (g_tcp_at_reply.active == TRUE) {
			if (g_tcp_at_reply.count < TCP_DEVICE_REPLY_BUFFER_MAX_LENGTH) {
				g_tcp_at_reply.buffer[g_tcp_at_reply.count++] = received_byte;
				g_tcp_at_reply.buffer[g_tcp_at_reply.count] = 0;	/* \0 terminate string */
			}
			else {
				g_tcp_at_reply.active = FALSE;
			}
		}
		else {
			/* Check for unsolicted events */
			r_tcp_device_receive_unsolicited_event(received_byte, TRUE);
		}
    }
}

/******************************************************************************
* Function Name : R_TCP_WRP_UartPhySendEnd
* Interface     : void R_TCP_WRP_UartPhySendEnd(TcpChannel channel)
* Description   : 
* Arguments     : TcpChannel channel:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_TCP_WRP_UartPhySendEnd(TcpChannel channel)
{
	if (channel == 0) {
		g_tcp_device_send_end = TRUE;
	}
}

/******************************************************************************
* Function Name : R_TCP_WRP_ReceiverTimeoutMilisecond
* Interface     : void R_TCP_WRP_ReceiverTimeoutMilisecond(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : void
******************************************************************************/
void R_TCP_WRP_ReceiverTimeoutMilisecond(void)
{
	static uint16_t ms_count = 0;
	
	/* No checking until modem state initialized by Init function */
	if (g_tcp_gsm_modem.state == GSM_MODEM_STATE_UNINITIALIZED)
	{
		return;
	}

	/* Check for interframe timeout */
	if (g_tcp_at_event_timeout.enable == TRUE)
	{
		if (g_tcp_at_event_timeout.count > 0) {
			g_tcp_at_event_timeout.count--;
		}
		else {
			g_tcp_at_event_timeout.enable = FALSE;
			
			/* Reset AT event listener to initial state, wait '+' */
            r_tcp_device_acknowledge_event_received();
		}
	}

	/* Interval timer for periodic tasks, interval is second unit */
	if (ms_count < 1000) {
		ms_count++;
	}
	else {
        /* Modem reboot delay time to send any command */
        if (g_tcp_gsm_modem.reboot_delay > 0) {
            g_tcp_gsm_modem.reboot_delay--;
        }

		if (g_tcp_gsm_interval_timer.enable == TRUE) {
			if (g_tcp_gsm_interval_timer.count > 0) {
				g_tcp_gsm_interval_timer.count--;
			}
			else {
				g_tcp_gsm_interval_timer.count = g_tcp_gsm_interval_timer.initial;
				g_tcp_gsm_modem.periodic_job = TRUE;
			}
		}

        /* Check if modem mounted on PCB */
        if (r_tcp_device_is_modem_mounted() ^ g_tcp_gsm_modem.diag.modem_mounted)
        {
            if (g_tcp_gsm_modem.diag.modem_mounted_count > 0) {
                g_tcp_gsm_modem.diag.modem_mounted_count--;
            }
            else {
                /* Reverse state of modem mounted */
                g_tcp_gsm_modem.diag.modem_mounted ^= 1;

                /* State change and modem mounted */
                if (g_tcp_gsm_modem.diag.modem_mounted == TRUE) {
                    /* Only reset modem if not in initialized state */
                    if (g_tcp_gsm_modem.state != GSM_MODEM_STATE_INITIALIZED)
                    {
                        R_TCP_DEVICE_RebootGsmModem();
                    }
                    /* modem removed detection immediately */
                    g_tcp_gsm_modem.diag.modem_mounted_count = 0;
                }
                else {
                    /* modem mounted detection with delay */
                    g_tcp_gsm_modem.diag.modem_mounted_count = TCP_DEVICE_MODEM_MOUNTED_CONFIRM_TIME;
                }
            }
        }

        /* Inactive socket timeout, oneshot mode */
        // TODO: multiple TCP channel now only socket 1
        if (g_tcp_gsm_modem.remote[1].timeout.enable == TRUE)
        {
			if (g_tcp_gsm_modem.remote[1].timeout.count > 0) {
				g_tcp_gsm_modem.remote[1].timeout.count--;
				if (g_tcp_gsm_modem.remote[1].timeout.count == 0)
				{
                    g_tcp_gsm_modem.remote[1].timeout.count = g_tcp_gsm_modem.remote[1].timeout.initial;
					g_tcp_gsm_modem.remote[1].timeout.enable = FALSE;
	                g_tcp_gsm_modem.remote[1].is_timeout = TRUE;
				}
			}
        }

		ms_count = 0;
	}

	/* Timeout timer for AT commands, oneshot mode */
	if (g_tcp_at_timeout_timer.enable == TRUE) {
		if (g_tcp_at_timeout_timer.count > 0) {
			g_tcp_at_timeout_timer.count--;
		}
		else {
			g_tcp_at_timeout_timer.enable = FALSE;
			g_tcp_at_reply.timeout = TRUE;
		}
	}
}

/******************************************************************************
* Function Name : R_TCP_WRP_IsConnected
* Interface     : uint8_t R_TCP_WRP_IsConnected(void)
* Description   : 
* Arguments     : None:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_TCP_WRP_IsConnected(void)
{
	if (g_tcp_gsm_modem.state == GSM_MODEM_STATE_READY) {
		return TRUE;
	}
	
	return FALSE;
}

/******************************************************************************
* Function Name : R_TCP_WRP_TryOpenConnection
* Interface     : uint8_t R_TCP_WRP_TryOpenConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
* Description   : 
* Arguments     : TcpPort remote_port: remote port to connect
*               : IpAddressPtr remote_ip_address: remote IP address to connect
* Return Value  : uint8_t: TRUE or FALSE
*               : TRUE: already connected or connect successfully
*               : FALSE: connection failed (timeout)
******************************************************************************/
uint8_t R_TCP_WRP_TryOpenConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
{
	if (R_TCP_WRP_IsConnected() == FALSE) {
		return FALSE;
	}
	
	if (R_TCP_GetConnectionState(0) == TCP_DISCONNECTED &&
		R_TCP_Connect(0, remote_port, remote_ip_address) == TCP_OK)
	{
		return TRUE;
	}

    return FALSE;
}

/******************************************************************************
* Function Name : R_TCP_WRP_TryCloseConnection
* Interface     : uint8_t R_TCP_WRP_TryCloseConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
* Description   : 
* Arguments     : TcpPort remote_port: remote port to disconnect
*               : IpAddressPtr remote_ip_address: remote IP address to disconnect
* Return Value  : uint8_t: TRUE or FALSE
*               : TRUE: already disconnected or disconnect successfully
*               : FALSE: disconnection failed
******************************************************************************/
uint8_t R_TCP_WRP_TryCloseConnection(TcpPort remote_port, IpAddressPtr remote_ip_address)
{
	if (R_TCP_GetConnectionState(0) == TCP_CONNECTED &&
		R_TCP_Disconnect(0, remote_port, remote_ip_address) == TCP_OK)
	{
		return TRUE;
	}

	return FALSE;
}

void R_TCP_WRP_InformPushingLastGasp(void)
{
    g_tcp_gsm_modem.pushing_lastgasp = TRUE;
}

/******************************************************************************
* Function Name : R_TCP_WRP_SelfTestIpParser
* Interface     : uint8_t R_TCP_WRP_SelfTestIpParser(void)
* Description   : Self testing function for IP address parsing API
* Arguments     : None
* Return Value  : uint8_t: 0 or 1
*               : 0: all test cases PASSED, function work correctly
*               : 1: one or some test cases FAILED
******************************************************************************/
uint16_t R_TCP_WRP_GetDnsServerIpAddressBuffer(uint8_t ** ip_address, uint8_t is_primary)
{
    if (is_primary) {
        *ip_address = g_tcp_gsm_modem.dns_server.primary;
    }
    else {
        *ip_address = g_tcp_gsm_modem.dns_server.secondary;
    }
    return TCP_DEVICE_IP_SIZE;
}


/******************************************************************************
* Function Name : R_TCP_WRP_SelfTestIpParser
* Interface     : uint8_t R_TCP_WRP_SelfTestIpParser(void)
* Description   : Self testing function for IP address parsing API
* Arguments     : None
* Return Value  : uint8_t: 0 or 1
*               : 0: all test cases PASSED, function work correctly
*               : 1: one or some test cases FAILED
******************************************************************************/
uint8_t R_TCP_WRP_SelfTestIpParser(void)
{
    uint8_t ip_buffer[16];
    uint16_t length, port_no;
    uint16_t i;
    uint8_t result;

    typedef struct tagTcpTestIpParser{
        const uint8_t * input_str;
        const uint8_t * output_ip_buffer;
        const uint16_t exp_port_no;
        uint16_t exp_length;
    } tcp_test_ip_parser;

    static const tcp_test_ip_parser test_vector[] = 
    {
        /* Normal Ipv4 */
        { (uint8_t *)"192.168.0.20"                                     , (uint8_t *)"\xc0\xa8\x00\x14"                                                     , 0     , 4 },
        { (uint8_t *)"192.168.0.20:4059"                                , (uint8_t *)"\xc0\xa8\x00\x14"                                                     , 4059  , 4 },
        { (uint8_t *)"255.255.255.255:4059"                             , (uint8_t *)"\xff\xff\xff\xff"                                                     , 4059  , 4 },
        { (uint8_t *)"255.255.255.255:65535"                            , (uint8_t *)"\xff\xff\xff\xff"                                                     , 65535 , 4 },
        /* Normal Ipv6 */
        { (uint8_t *)"::"                                               , (uint8_t *)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"     , 0     , 16},
        { (uint8_t *)"::1"                                              , (uint8_t *)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01"     , 0     , 16},
        { (uint8_t *)"FF01::101"                                        , (uint8_t *)"\xff\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x01"     , 0     , 16},
        { (uint8_t *)"2001:db8:3:4::"                                   , (uint8_t *)"\x20\x01\x0d\xb8\x00\x03\x00\x04\x00\x00\x00\x00\x00\x00\x00\x00"     , 0     , 16},
        { (uint8_t *)"2001:db8:3:4::5"                                  , (uint8_t *)"\x20\x01\x0d\xb8\x00\x03\x00\x04\x00\x00\x00\x00\x00\x00\x00\x05"     , 0     , 16},
        { (uint8_t *)"2001:db8:3:4::5:2"                                , (uint8_t *)"\x20\x01\x0d\xb8\x00\x03\x00\x04\x00\x00\x00\x00\x00\x05\x00\x02"     , 0     , 16},
        { (uint8_t *)"2001:0ee0:0100:8::8"                              , (uint8_t *)"\x20\x01\x0e\xe0\x01\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00\x08"     , 0     , 16},
        { (uint8_t *)"2402:3A80:1700:407::2"                            , (uint8_t *)"\x24\x02\x3a\x80\x17\x00\x04\x07\x00\x00\x00\x00\x00\x00\x00\x02"     , 0     , 16},
        { (uint8_t *)"2402:3A80:1700:0408::0002"                        , (uint8_t *)"\x24\x02\x3a\x80\x17\x00\x04\x08\x00\x00\x00\x00\x00\x00\x00\x02"     , 0     , 16},
        { (uint8_t *)"2402:3A80:1700:407:0:0:0:002"                     , (uint8_t *)"\x24\x02\x3a\x80\x17\x00\x04\x07\x00\x00\x00\x00\x00\x00\x00\x02"     , 0     , 16},
        { (uint8_t *)"2402:3A80:1700:0408:0:0:0:002"                    , (uint8_t *)"\x24\x02\x3a\x80\x17\x00\x04\x08\x00\x00\x00\x00\x00\x00\x00\x02"     , 0     , 16},
        { (uint8_t *)"2001:EE0:26B:B723:6D43:69ED:898C:EEDD"            , (uint8_t *)"\x20\x01\x0e\xe0\x02\x6b\xb7\x23\x6d\x43\x69\xed\x89\x8c\xee\xdd"     , 0     , 16},
        { (uint8_t *)"[2001:EE0:26B:B723:6D43:69ED:898C:EEDD]:4059"     , (uint8_t *)"\x20\x01\x0e\xe0\x02\x6b\xb7\x23\x6d\x43\x69\xed\x89\x8c\xee\xdd"     , 4059  , 16},
        /* Normal Ipv4 compatible and Ipv4 mapped IPv6 address */
        { (uint8_t *)"::192.168.0.20"                                   , (uint8_t *)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xc0\xa8\x00\x14"     , 0     , 16},
        { (uint8_t *)"::ffff:192.168.0.20"                              , (uint8_t *)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xc0\xa8\x00\x14"     , 0     , 16},
        { (uint8_t *)"[::ffff:192.168.0.20]:4059"                       , (uint8_t *)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xc0\xa8\x00\x14"     , 4059  , 16},
        /* Abnormal: convertable and correct Ipv4 */
        { (uint8_t *)"192.\t168.0\b.20\n\r"                             , (uint8_t *)"\xc0\xa8\x00\x14"                                                     , 0     , 4 },
        { (uint8_t *)"192.\t168.0\b.20\n\r:4_0-5>9"                     , (uint8_t *)"\xc0\xa8\x00\x14"                                                     , 4059  , 4 },
        /* Abnormal: convertable but NOT correct Ipv4 */
        { (uint8_t *)"192.1.6.8.0.20"                                   , (uint8_t *)"\xc0\x01\x06\x08"                                                     , 0     , 4 },
        { (uint8_t *)"192.1.6.8.0.20:256000"                            , (uint8_t *)"\xc0\x01\x06\x08"                                                     , 59392 , 4 },
        /* Abnormal: convertable and correct Ipv6 */
        { (uint8_t *)"2402:\b3A8\t0:17\n00:\r407::2\n\r"                , (uint8_t *)"\x24\x02\x3a\x80\x17\x00\x04\x07\x00\x00\x00\x00\x00\x00\x00\x02"     , 0     , 16},
        /* Abnormal: convertable but NOT correct Ipv6 */
        { (uint8_t *)"[2001:EE0:26B:B723:6D43:69ED:898C:EEDD]:256000"   , (uint8_t *)"\x20\x01\x0e\xe0\x02\x6b\xb7\x23\x6d\x43\x69\xed\x89\x8c\xee\xdd"     , 59392 , 16},
        { (uint8_t *)"2001:EE0:26B:B723:6D43:69ED:898C:EEDD:4059"       , (uint8_t *)"\x20\x01\x0e\xe0\x02\x6b\xb7\x23\x6d\x43\x69\xed\x89\x8c\xee\xdd"     , 0     , 16},
        { (uint8_t *)"[2001:EE0:26B:B723:6D43:69ED:898C:EEDD:4059"      , (uint8_t *)"\x20\x01\x0e\xe0\x02\x6b\xb7\x23\x6d\x43\x69\xed\x89\x8c\xee\xdd"     , 0     , 16},
        { (uint8_t *)"[2001:EE0:26B:B723:6D43:69ED:898C:EEDD[:4059"     , (uint8_t *)"\x20\x01\x0e\xe0\x02\x6b\xb7\x23\x6d\x43\x69\xed\x89\x8c\xee\xdd"     , 0     , 16},
        /* Abnormal: NOT convertable Ipv6 */
        { (uint8_t *)"2001:0ee0:0100:8::8::"                            , (uint8_t *)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"     , 0     , 0 },
        { (uint8_t *)"]2001:EE0:26B:B723:6D43:69ED:898C:EEDD]:4059"     , (uint8_t *)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"     , 0     , 0 },
        { (uint8_t *)"[[2001:EE0:26B:B723:6D43:69ED:898C:EEDD]:4059"    , (uint8_t *)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"     , 0     , 0 },
    };
    static const uint16_t num_of_test_cases = sizeof(test_vector) / sizeof(tcp_test_ip_parser);

    uint8_t * p_test_result;

    p_test_result = WRP_EXT_Heap_Malloc(num_of_test_cases);

    for (i = 0; i < num_of_test_cases; i++)
    {
        /* Debug: break at any test to check details */
        if (i == 0) {
            /* Set break point here to jump to details */
            NOP();
        }

        length = r_tcp_device_parse_ip_address((uint8_t *)ip_buffer, &port_no, (uint8_t *)test_vector[i].input_str, strlen((const char *)test_vector[i].input_str));
        if (length != test_vector[i].exp_length ||
            memcmp(ip_buffer, test_vector[i].output_ip_buffer, test_vector[i].exp_length) != 0 ||
            port_no != test_vector[i].exp_port_no)
        {
            p_test_result[i] = FALSE;
        }
        else {
            p_test_result[i] = TRUE;
        }
    }

    result = 0;
    for (i = 0; i < num_of_test_cases; i++)
    {
        if (p_test_result[i] != TRUE)
        {
            result = 1;
        }
    }

    WRP_EXT_Heap_Free(p_test_result);

    return result;
}

#endif /* #if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == FALSE) */