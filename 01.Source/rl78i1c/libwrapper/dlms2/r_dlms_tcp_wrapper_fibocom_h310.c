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
* File Name    : r_dlms_tcp_wrapper_fibocom_h310.c
* Version      : 1.00
* Device(s)    : Fibocom H310
* Tool-Chain   : CCRL
* H/W Platform : Velankani Meter
* Description  : TCP wrapper layer of DLMS Library on 3G Modem Fibocom H310
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
#include "r_dlms_com_wrapper_config.h"
#if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == TRUE) && (TCP_MODE_SELECTION == TCP_MODE_FIBOCOM_H310)
#include "r_dlms_tcp_wrapper.h"
#include "r_dlms_tcp_wrapper_interface.h"
#include "r_dlms_tcp_wrapper_fibocom_h310.h"
#include "r_dlms_event.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "powermgmt.h"
#include "wrp_app_ext.h"
#inlcude "r_dlms_app.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define     FIXED_METER_PUSH_DOMAIN                             "meter.dynu.net"
#define     GSM_CONNECTED                                       BIT_SELECT(P3, 3)
#define     TCP_DEVICE_MODULE_MOUNTING_HW_CHECK_SUPPORT         TRUE
#define     TCP_DEVICE_MODULE_POWER_CONTROL_SUPPORT             TRUE

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

/* Adapt with old implementation from Velankani */
uint16_t			signalStrength = 0;

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

/* For waiting predicate condition checking */
AtCommand   * gp_tcp_current_waiting_cmd = NULL;
uint8_t     * gp_tcp_send_expected_buffer = NULL;
uint8_t     * gp_cmd_buffer = NULL;

/* ---------------------------------------------------------------------------
 * Unsolicted event handlers, parser & internal functions
 * ---------------------------------------------------------------------------
 */

/* Cmd inputs */
static uint16_t r_tcp_device_cmd_input_cgdcont(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length);
static uint16_t r_tcp_device_cmd_input_mipodm(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length);
static uint16_t r_tcp_device_cmd_input_cgqmin(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length);
static uint16_t r_tcp_device_cmd_input_cgqreq(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length);
static uint16_t r_tcp_device_cmd_input_mipopen2(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length);

/* Reply handlers */
static uint8_t r_tcp_device_reply_check_mipcall(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_mping(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_mipopen_socket2(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_mipclose_socket2(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_mipopen_socket1(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_mipclose_socket1(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_msdns(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_cced(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_cpin(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_cgdcont(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_cgreg(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);
static uint8_t r_tcp_device_reply_check_csq(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event);

/* Event receiver entry & all handlers */
static uint16_t r_tcp_device_parse_u16(uint16_t *p_u16, uint8_t *p_str, uint16_t length);
static uint16_t r_tcp_device_parse_ip_address(uint8_t *p_ip_address, uint16_t * p_port_no, uint8_t *p_str, uint16_t length);
static uint8_t r_tcp_device_event_handler_cpin(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_cgreg(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_csq(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_mipcall(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_mipodm(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_mipstat(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_msdns(AtEvent *p_event);
static uint8_t r_tcp_device_event_handler_cmee(AtEvent *p_event);
static uint8_t r_tcp_device_receive_unsolicted_event(uint8_t rx_byte, uint8_t use_timeout);

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
    /* TODO: Add IP check code in case IPv4 */
#elif TCP_DEVICE_IP_CONFIGURATION == 1	/* IPv6 */
    /* Checking:
    * Address not null
    * Must be 16 bytes
    * Push using unicast address, first 3 MSBit must be 001 */
    if (remote_ip_address == NULL ||
        remote_ip_address->size != 16 ||
       (remote_ip_address->p_addr[0] & 0xE0) != 0x20)
    {
        return FALSE;
    }
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
        /* Update parameters */
        /* Act value
                0 GSM
                2 UTRAN1
                3 GSM w / EGPRS
                4 UTRAN w / HSDPA
                5 UTRAN w / HSUPA
                6 UTRAN w / HSDPA and HSUPA
            PS attachment value:
                (0) inactive,
                (1) GPRS,
                (2) EDGE,
                (3) UMTS,
                (4) HSDPA,
                (5) LTE,
                (6) CDMA
        */
        if (p_cgreg->AcT == 3) {
            /* 3G SIM force using GSM, connected in EDGE mode, direct map to ps_status  */
            g_tcp_gsm_modem.info.ps_status = 2;
        }
        else if (p_cgreg->AcT == 6) {
            /* 3G SIM connected is considered HSDPA */
            g_tcp_gsm_modem.info.ps_status = 4;
        }
        else {
            /* 3G SIM by default is UMTS */
            g_tcp_gsm_modem.info.ps_status = 3;
        }
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
#if TCP_DEVICE_IP_CONFIGURATION == 0
	return (uint16_t)sprintf((char *)p_input_args, "\"IP\",\"%s\"", p_modem->setting.apn_name);
#elif TCP_DEVICE_IP_CONFIGURATION == 1
	return (uint16_t)sprintf((char *)p_input_args, "\"IPV6\",\"%s\"", p_modem->setting.apn_name);
#endif
}

static uint16_t r_tcp_device_cmd_input_mipodm(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length)
{
#if TCP_DEVICE_IP_CONFIGURATION == 0
	return (uint16_t)sprintf((char *)p_input_args, "4059,\"0.0.0.0\",0,0");
#elif TCP_DEVICE_IP_CONFIGURATION == 1
	return (uint16_t)sprintf((char *)p_input_args, "4059,\"::\",0,2");
#endif
}

static uint16_t r_tcp_device_cmd_input_cgqmin(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length)
{
	/* CGQMIN = <cid>[,<precedence>[,<delay>[,<reliability.>[,<peak>[,<mean>]]]]] */
	return (uint16_t)sprintf(
		(char *)p_input_args,
		"%d,%d,%d,%d,%d",
		p_modem->setting.quality_of_service.min.precedence,
		p_modem->setting.quality_of_service.min.delay,
		p_modem->setting.quality_of_service.min.reliability,
		p_modem->setting.quality_of_service.min.peak,
		p_modem->setting.quality_of_service.min.mean
	);
}

static uint16_t r_tcp_device_cmd_input_cgqreq(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length)
{
	/* CGQREQ = <cid>[,<precedence>[,<delay>[,<reliability.>[,<peak>[,<mean>]]]]] */
	return (uint16_t)sprintf(
		(char *)p_input_args,
		"%d,%d,%d,%d,%d",
		p_modem->setting.quality_of_service.req.precedence,
		p_modem->setting.quality_of_service.req.delay,
		p_modem->setting.quality_of_service.req.reliability,
		p_modem->setting.quality_of_service.req.peak,
		p_modem->setting.quality_of_service.req.mean
	);
}

static uint16_t r_tcp_device_cmd_input_mipopen2(GsmModem *p_modem, uint8_t *p_input_args, uint16_t length)
{
    /* AT+MIPOPEN=2,80,\"google.com.vn\",80,0*/
    /* AT+MIPOPEN=2,4059,\"1.2.3.4\",4059,0*/
    /* 0 (address from library), 1 (google), 2 (remote address) */
    #define PUSH_LOCATION	(1)

    uint8_t         * p_IpBuffer;
    uint16_t        remote_tcp_port;
    uint16_t		i;

    /* AT+MIPOPEN=2,4059,\"1.2.3.4\",4059,0*/
    p_IpBuffer = p_modem->remote.ip_buffer;
    remote_tcp_port = p_modem->remote.port_number;

#if TCP_DEVICE_IP_CONFIGURATION == 0	/* IPv4 */
#if PUSH_LOCATION == 0
	return (uint16_t)sprintf(
		(char *)p_input_args,
		"64059,\"%d.%d.%d.%d\",%d,2",
		p_IpBuffer[0],
		p_IpBuffer[1],
		p_IpBuffer[2],
		p_IpBuffer[3],
		remote_tcp_port
	);
#elif PUSH_LOCATION == 1
    return (uint16_t)sprintf(
        (char *)p_input_args,
        "64059,\"google.com\",80,2"
    );
#elif PUSH_LOCATION == 2
    return (uint16_t)sprintf(
		(char *)p_input_args,
		"64059,\"%d.%d.%d.%d\",%d,2",
		p_IpBuffer[0],
		p_IpBuffer[1],
		p_IpBuffer[2],
		p_IpBuffer[3],
		4059
	);
#endif
#elif TCP_DEVICE_IP_CONFIGURATION == 1	/* IPv6 */
    /* Check if all IP value is zero */
    for (i = 0; i < 16; i++)
    {
        if (p_IpBuffer[i] != 0) {
            break;
        }
    }

    /* If the IP buffer not all 0s, push will proceed with requested IP */
    if (i != 16) {
        return (uint16_t)sprintf(
            (char *)p_input_args,
            "64059,\"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x\",%d,2",
            p_IpBuffer[0],
            p_IpBuffer[1],
            p_IpBuffer[2],
            p_IpBuffer[3],
            p_IpBuffer[4],
            p_IpBuffer[5],
            p_IpBuffer[6],
            p_IpBuffer[7],
            p_IpBuffer[8],
            p_IpBuffer[9],
            p_IpBuffer[10],
            p_IpBuffer[11],
            p_IpBuffer[12],
            p_IpBuffer[13],
            p_IpBuffer[14],
            p_IpBuffer[15],
            remote_tcp_port
        );
    }
    /* Else, open socket with predefined domain name and default DLMS port 4059 */
    else {
        return (uint16_t)sprintf(
            (char *)p_input_args,
            "64059,\"" FIXED_METER_PUSH_DOMAIN "\",4059,2"
        );
    }
#endif
}

/*
 * Reply handlers
 */
static uint8_t r_tcp_device_reply_check_mipcall(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
	if (p_event != NULL &&
		p_event->type == GSM_MODEM_EVENT_MIPCALL &&
		p_event->data.MIPCALL.status == 1) {
		return TRUE;
	}

	return FALSE;
}

static uint8_t r_tcp_device_reply_check_msdns(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    uint8_t * original_msg = p_msg; /* For debug */

    /* The reply MSDNS include all socket, which causing buffer not enough, 
    * So the check reply only scan for first socket, then wait some fixed delay
    */
    p_msg = (uint8_t *)strstr((const char *)p_msg, "+MSDNS: 1");
    if (p_msg == NULL) {
        return FALSE;
    }
    p_msg = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_msg == NULL) {
        return FALSE;
    }

    return TRUE;
}


static uint8_t r_tcp_device_reply_check_cced(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    /* +CCED:<cr><lf>
    *  <mcc>,<mnc>,<lac>,<ci>,<dl_uarfcn>,
    <psc>,<rscp>,<ecn0>,<rxlev>,<s_qual>,<s_intrasearch>,
    <s_intersearch>,<s_search_rat>,<activecellcounter>,
    <ncellgsmcounter>,<sys_mode>
    */

    uint8_t  *p_pattern = NULL;
    uint16_t u16, temp;
    uint32_t temp32;
    GsmCced  cced;

    /* Start parsing when receive OK after requesting CCED */
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "OK\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }

    /* Initialize info buffer */
    memset(&cced, 0, sizeof(cced));

    /* CCED */
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "+CCED:\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }
    /* Skip all characters before +CCED, and jump to value string */
    p_msg = p_pattern + 8;
    length -= (p_pattern - p_msg) + 8;

    /* mcc */
    u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
    if (u16 == 0) {
        return FALSE;
    }

    cced.mcc = (uint16_t)temp;
    p_msg += u16;
    length -= u16;

    /* mnc */
    u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
    if (u16 == 0) {
        return FALSE;
    }

    cced.mnc = (uint16_t)temp;
    p_msg += u16;
    length -= u16;

    /* lac */
    u16 = r_tcp_device_parse_u32_hexstr(&temp32, p_msg, length);
    if (u16 == 0) {
        return FALSE;
    }

    cced.lac = (uint16_t)temp32;
    p_msg += u16;
    length -= u16;

    /* cid */
    u16 = r_tcp_device_parse_u32_hexstr(&temp32, p_msg, length);
    if (u16 == 0) {
        return FALSE;
    }

    cced.cid = temp32;
    p_msg += u16;
    length -= u16;


    /* dl_uarfcn */
    u16 = r_tcp_device_parse_u32(&temp32, p_msg, length);
    if (u16 == 0) {
        return FALSE;
    }

    cced.dl_uarfcn = temp32;
    p_msg += u16;
    length -= u16;

    /* TODO: parsing, currently no need to link
    *  <psc>    : primary scrambling code
    *  <rscp>   : received signal code power level
    *  <ecno>   : carrier to noise ratio in dB
    *  <rxlev>  : RX level value for base station selection in dB
    *  <s_qual>, <s_intrasearch>, <s_intersearch>, <s_search_rat>, <activecellcounter>
    *  <ncellgsmcounter>, <sys_mode>
    */
    
    /* The rest temporarily unsupported yet */

    /* Copy output to gsm cell info */
    g_tcp_gsm_modem.info.cell_info.cell_id = cced.cid;
    g_tcp_gsm_modem.info.cell_info.location_id = cced.lac;
    g_tcp_gsm_modem.info.cell_info.mcc = cced.mcc;
    g_tcp_gsm_modem.info.cell_info.mnc = cced.mnc;
    g_tcp_gsm_modem.info.cell_info.channel_number = cced.dl_uarfcn;

    /* Update capture time */
    R_RTC_Get_CalendarCounterValue(&g_tcp_gsm_modem.info.capture_time);

    return TRUE;
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

static uint8_t r_tcp_device_reply_check_cgdcont(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    uint8_t * p_pattern;

    /* Check when end of line */
    p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_pattern == NULL) {
        return FALSE;
    }

    /* Check for message:
    + Error 148: reconfigure CGDCONT while having connection
    + Error 148: reconfigure CGDCONT while having connection
    */
    if (strstr((const char *)p_msg, "+CME ERROR: 148\r\n") == NULL &&
        strstr((const char *)p_msg, "OK") == NULL) {
        return TRUE;
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

    if (p_event->data.CSQ.rssi == 99 &&
        p_event->data.CSQ.ber == 99) {
        return FALSE;
    }

    return TRUE;
}

static uint8_t r_tcp_device_reply_check_mping(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
    uint8_t * original_msg = p_msg; /* For debug */
    
    p_msg = (uint8_t *)strstr((const char *)p_msg, "+MPINGSTAT: ");
    if (p_msg == NULL) {
        return FALSE;
    }
    p_msg = (uint8_t *)strstr((const char *)p_msg, "\r\n");
    if (p_msg == NULL) {
        return FALSE;
    }

    return TRUE;
}

static uint8_t r_tcp_device_reply_check_mipopen_socket2(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
	p_msg = (uint8_t *)strstr((const char *)p_msg, "+MIPOPEN: ");
	if (p_msg == NULL) {
		return FALSE;
	}
	p_msg = (uint8_t *)strstr((const char *)p_msg, "2");
	if (p_msg == NULL) {
		return FALSE;
	}
	p_msg = (uint8_t *)strstr((const char *)p_msg, "\r\n");
	if (p_msg == NULL) {
		return FALSE;
	}

	return TRUE;
}

static uint8_t r_tcp_device_reply_check_mipclose_socket2(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
	if (strstr((const char *)p_msg, "+CME ERROR: 3\r\n") != NULL ||
		strstr((const char *)p_msg, "OK\r\n\r\n+MIPCLOSE: 2,0\r\n") != NULL) {
		return TRUE;
	}

	return FALSE;
}

static uint8_t r_tcp_device_reply_check_mipopen_socket1(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
	p_msg = (uint8_t *)strstr((const char *)p_msg, "+MIPOPEN: ");
	if (p_msg == NULL) {
		return FALSE;
	}
	p_msg = (uint8_t *)strstr((const char *)p_msg, "1");
	if (p_msg == NULL) {
		return FALSE;
	}
	p_msg = (uint8_t *)strstr((const char *)p_msg, "\r\n");
	if (p_msg == NULL) {
		return FALSE;
	}

	return TRUE;
}

static uint8_t r_tcp_device_reply_check_mipclose_socket1(GsmModem *p_modem, uint8_t *p_msg, uint16_t length, AtEvent *p_event)
{
	if (strstr((const char *)p_msg, "+CME ERROR: 3\r\n") != NULL ||
		strstr((const char *)p_msg, "OK\r\n\r\n+MIPCLOSE: 1,0\r\n") != NULL) {
		return TRUE;
	}

	return FALSE;
}

/*
 * Event receiver entry & all handlers
 */
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
    /* Unsolicited when connected:              +CGREG: <stat>,"<lac>","<ci>",<AcT>,"<rac>"\r\n */
	/* Query:                                   +CGREG: <n>,<stat>,"<lac>","<ci>",<AcT>,"<rac>"\r\n */

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

    /* Dtermine type of CGREG */
    if (temp == 0) {
        /* No ',': consider unsolicited + not registered */
        is_query = FALSE;
        p_event->data.CREG.n = 2;
    }
    else if (temp == 1) {
        /* Only 1 ',': consider query + not registered */
        is_query = TRUE;
    }
    else {
        /* More than 4 ',': consider query */
        is_query = (temp > 4);
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
        p_event->data.CREG.n = (uint8_t)temp;

        p_msg += u16;
        length -= u16;
    } 
    else {
        /* If unsolicited mode then n must be 2 */
        p_event->data.CREG.n = 2;
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
    if (p_event->data.CREG.n != 2) {
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
    	
        /* [<AcT>] */
        u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
        if (u16 == 0) {
            return FALSE;
        }
        p_event->data.CGREG.AcT = temp;
        p_msg += u16 + 1;
        length -= u16 + 1;
    	
        /* [<rac>] */
        u16 = r_tcp_device_parse_u32_hexstr(&temp32, p_msg, length);
        if (u16 == 0) {
            return FALSE;
        }
        p_event->data.CGREG.rac = temp32;
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

static uint8_t r_tcp_device_event_handler_mipcall(AtEvent *p_event)
{
	/*
	* +MIPCALL: <local_ip_address>\r\n
	* +MIPCALL: <status>,<local_ip_address>\r\n
	* +MIPCALL: <status>\r\n
	*
	* IPv6
	* ---------------------------------------------------
	* +MIPCALL: 2001:EE0:26B:B723:6D43:69ED:898C:EEDD\r\n
	* +MIPCALL: 1,2001:EE0:26B:B723:6D43:69ED:898C:EEDD\r\n
	* +MIPCALL: 0\r\n
	*
	* IPv4
	* ---------------------------------------------------
	* +MIPCALL: 192.168.0.1\r\n
	* +MIPCALL: 1,192.168.0.1\r\n
	* +MIPCALL: 0\r\n
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

	/* space */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, " ");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_msg += 1;
	length -= 1;

	/* Default, connected */
	p_event->data.MIPCALL.status = 1;

	/* MIPCALL Failure ? "0\r\n" */
	if (length > 2 &&
		p_msg[0] == '0' &&
		p_msg[1] == '\r' &&
		p_msg[2] == '\n') {
		p_event->data.MIPCALL.status = 0;
		return TRUE;
	}

	/* Has <status> field as 1?*/
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern != NULL) {
		u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
		if (u16 > 0) {
			p_event->data.MIPCALL.status = (uint8_t)temp;
		}
		p_pattern++;
		u16 = (uint16_t)(p_pattern - p_msg);
		p_msg += u16;
		length -= u16;
	}

	/* Parse IP address */
	if (p_event->data.MIPCALL.status == 1) {
		u16 = r_tcp_device_parse_ip_address(p_event->data.MIPCALL.local_ip_buffer, NULL, p_msg, length);
		if (u16 == 0) {
			return FALSE;
		}
	}

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_mipodm(AtEvent *p_event)
{
	/*
	* +MIPODM: <socket_ID>,<state>[,remote_ip_address>,<remote_port>]\r\n
	*
	* IPv6
	* ---------------------------------------------------------
	* +MIPODM: 1,1,2001:ee0:252:eadb:39ab:459b:5eed:6db9,49200\r\n
	*
	* IPv4
	* ---------------------------------------------------------
	* +MIPODM: 1,1,192.168.0.1,49200\r\n
	*/

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

	/* <socket_ID> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.MIPODM.socket_id = (uint8_t)temp;

	/* ',' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <state> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.MIPODM.state = (uint8_t)temp;

	/* ',' optional */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return TRUE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <remote_ip_address> */
	u16 = r_tcp_device_parse_ip_address(p_event->data.MIPODM.remote_ip_buffer, NULL, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}

	/* ',' mandatory */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* Parse port number */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.MIPODM.remote_port = temp;

	/* "\r\n" */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
	if (p_pattern == NULL) {
		return FALSE;
	}

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_mipstat(AtEvent *p_event)
{
	/* +MIPSTAT: <socket_ID>,<n>[,<act_bytes>]\r\n */

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

	/* <socket_ID> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.MIPSTAT.socket_id = (uint8_t)temp;

	/* ',' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <n> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.MIPSTAT.n = (uint8_t)temp;

	/* ',' optional */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return TRUE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <act_bytes> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.MIPSTAT.ack_bytes = temp;

	/* "\r\n" */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
	if (p_pattern == NULL) {
		return FALSE;
	}

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_cgqmin_and_cgqmin(AtEvent *p_event)
{
	/* +CGQMIN: <cid>,<precedence>,<delay>,<reliability>,<peak>,<mean>\r\n */

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

	/* <cid> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGQMIN.cid = (uint8_t)temp;

	/* ',' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <precedence> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGQMIN.precedence = (uint8_t)temp;

	/* ',' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <delay> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGQMIN.delay = (uint8_t)temp;

	/* ',' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <reliability> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGQMIN.reliability = (uint8_t)temp;

	/* ',' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <peak> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGQMIN.peak = (uint8_t)temp;

	/* ',' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <mean> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGQMIN.mean = (uint8_t)temp;

	/* "\r\n" */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
	if (p_pattern == NULL) {
		return FALSE;
	}

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_cops(AtEvent *p_event)
{
	/* +COPS: <mode>[,<format>,<oper>[,<AcT>]]\r\\n */

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
	u16 = 0;
	while (u16 < TCP_DEVICE_MAX_OPERATOR_NAME_LENGTH &&
		*p_msg != '\"')
	{
		p_event->data.COPS.operator[u16] = *p_msg;
		u16++;
		p_msg++;
	}
	if (u16 == TCP_DEVICE_MAX_OPERATOR_NAME_LENGTH) {
		return FALSE;
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

static uint8_t r_tcp_device_event_handler_cgatt(AtEvent *p_event)
{
	/* +CGATT: <state>\r\n */

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

	/* <state> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGATT.state = (uint8_t)temp;

	/* "\r\n" */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
	if (p_pattern == NULL) {
		return FALSE;
	}

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_cgdcont(AtEvent *p_event)
{
	/* +CGDCONT: <cid>,<PDP_type>,<APN>,<PDP_addr>,<d_comp>,<h_comp>[,<pd1>[,�[,pdN]]]\r\n */

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

	/* <cid> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGDCONT.cid = (uint8_t)temp;

	/* ',"' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",\"");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern += 2;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <PDP_type> */
	u16 = 0;
	while (u16 < 8 && *p_msg != '\"')
	{
		p_event->data.CGDCONT.pdp_type[u16] = *p_msg;
		u16++;
		p_msg++;
	}
	if (u16 == 8) {
		return FALSE;
	}

	/* '","' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\",\"");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern += 3;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <apn> */
	u16 = 0;
	while (u16 < TCP_DEVICE_MAX_APN_NAME_LENGTH &&
		*p_msg != '\"')
	{
		p_event->data.CGDCONT.apn[u16] = *p_msg;
		u16++;
		p_msg++;
	}
	if (u16 == TCP_DEVICE_MAX_APN_NAME_LENGTH) {
		return FALSE;
	}

	/* '","' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\",\"");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern += 3;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <PDP_addr> */
	u16 = 0;
	while (u16 < TCP_DEVICE_MAX_PDP_ADDRESS_LENGTH &&
		*p_msg != '\"')
	{
		p_event->data.CGDCONT.pdp_addr[u16] = *p_msg;
		u16++;
		p_msg++;
	}
	if (u16 == TCP_DEVICE_MAX_PDP_ADDRESS_LENGTH) {
		return FALSE;
	}

	/* '",' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern += 2;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <d_comp> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGDCONT.d_comp = (uint8_t)temp;

	/* ',' */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, ",");
	if (p_pattern == NULL) {
		return FALSE;
	}
	p_pattern++;
	u16 = (uint16_t)(p_pattern - p_msg);
	p_msg += u16;
	length -= u16;

	/* <h_comp> */
	u16 = r_tcp_device_parse_u16(&temp, p_msg, length);
	if (u16 == 0) {
		return FALSE;
	}
	p_event->data.CGDCONT.h_comp = (uint8_t)temp;

	/* "\r\n" */
	p_pattern = (uint8_t *)strstr((const char *)p_msg, "\r\n");
	if (p_pattern == NULL) {
		return FALSE;
	}

	return TRUE;
}

static uint8_t r_tcp_device_event_handler_msdns(AtEvent *p_event)
{
    /* +MSDNS: 1,<Primary_DNS_server_IP>,<Secondary_DNS_server_IP><CR><LF> */
    uint8_t  *p_pattern = NULL;
    uint8_t  *p_msg = p_event->content.buffer;
    uint16_t length = p_event->content.count;
    uint16_t u16, temp;
    uint8_t  *p_primary_start, *p_primary_end;
    uint8_t  *p_secondary_start, *p_secondary_end;

    /* Check socket "1" */
    p_msg = (uint8_t *)strstr((const char *)p_msg, "1");
    if (p_msg == NULL) {
        return FALSE;
    }
    
    /* start '"' of primary dns server */
    p_msg = (uint8_t *)strstr((const char *)p_msg, "\"");
    if (p_msg == NULL) {
        return FALSE;
    }
    p_msg += 1;
    p_primary_start = p_msg;

    /* end '"' of primary dns server */
    p_msg = (uint8_t *)strstr((const char *)p_msg, "\"");
    if (p_msg == NULL) {
        return FALSE;
    }
    p_primary_end = p_msg - 1;
    p_msg += 1;
    
    /* Primary and Secondary address separator */
    p_msg = (uint8_t *)strstr((const char *)p_msg, ",");
    if (p_msg == NULL) {
        return FALSE;
    }

    /* start '"' of primary dns server */
    p_msg = (uint8_t *)strstr((const char *)p_msg, "\"");
    if (p_msg == NULL) {
        return FALSE;
    }
    p_msg += 1;
    p_secondary_start = p_msg;

    /* end '"' of primary dns server */
    p_msg = (uint8_t *)strstr((const char *)p_msg, "\"");
    if (p_msg == NULL) {
        return FALSE;
    }
    p_secondary_end = p_msg - 1;
    p_msg += 1;
    
    
    u16 = r_tcp_device_parse_ip_address(
        p_event->data.MSDNS.primary_dns_address,
        NULL,
        p_primary_start,
        p_primary_end - p_primary_start + 1
    );

    if (u16 == 0) {
        return FALSE;
    }

    u16 = r_tcp_device_parse_ip_address(
        p_event->data.MSDNS.secondary_dns_address,
        NULL,
        p_secondary_start,
        p_secondary_end - p_secondary_start + 1
    );

    if (u16 == 0) {
        return FALSE;
    }

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
    /* Event "+MIPCALL:" join GPRS network */
    else if (strstr((const char *)p_event->prefix.buffer, "+MIPCALL:") != NULL) {
        if (r_tcp_device_event_handler_mipcall(p_event) == TRUE) {
            p_event->type = GSM_MODEM_EVENT_MIPCALL;
            memcpy(g_tcp_gsm_modem.local.ip_buffer, p_event->data.MIPCALL.local_ip_buffer, TCP_DEVICE_IP_SIZE);
            /* Bootup Gsm Modem again to join network if lost IP */
            if (p_event->data.MIPCALL.status == 0)
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
            else {
                g_tcp_gsm_modem.diag.gprs_connection_drop = FALSE;
            }
        }
    }
	/* Event "+MIPSTAT:" TCP disconnect */
	else if (strstr((const char *)p_event->prefix.buffer, "+MIPSTAT:") != NULL)
	{
		if (r_tcp_device_event_handler_mipstat(p_event) == TRUE)
		{
			p_event->type = GSM_MODEM_EVENT_MIPSTAT;

			/* Socket 1 disconnected */
			if (p_event->data.MIPSTAT.socket_id == 1 &&
				p_event->data.MIPSTAT.n == 1) {
				if (g_tcp_gsm_modem.state == GSM_MODEM_STATE_TCP_LISTENING) {
					g_tcp_gsm_modem.state = GSM_MODEM_STATE_TCP_REMOTE_DISCONNECTED;
				}
				else if (g_tcp_gsm_modem.state == GSM_MODEM_STATE_TCP_REMOTE_CONNECTED) {
					R_TCP_DEVICE_DisconnectIndication(0, g_tcp_dummy_remote_port, (IpAddressPtr)&g_tcp_dummy_remote_ip_addr, TCP_DISCONNECT_REMOTE_REQ);
					R_TCP_DEVICE_AbortIndication(0, g_tcp_dummy_remote_port, (IpAddressPtr)&g_tcp_dummy_remote_ip_addr, (uint8_t *)"Remote disconnected", 19);
					g_tcp_gsm_modem.state = GSM_MODEM_STATE_TCP_REMOTE_DISCONNECTED;
				}
			}
		}
	}
	/* Event "+MIPODM:", TCP remote connect */
	else if (strstr((const char *)p_event->prefix.buffer, "+MIPODM:") != NULL)
	{
		if (r_tcp_device_event_handler_mipodm(p_event) == TRUE)
		{
			p_event->type = GSM_MODEM_EVENT_MIPODM;

			/*
			 * TCP connect state is highly check and processed on UART RX interrupt
			 * Here just store the remote IP address and remote port number
			 */
			memcpy(g_tcp_gsm_modem.remote.ip_buffer, p_event->data.MIPODM.remote_ip_buffer, TCP_DEVICE_IP_SIZE);
			g_tcp_gsm_modem.remote.port_number = p_event->data.MIPODM.remote_port;
		}
	}
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
            /* Adaptation with Velankani old UDP wrapper */
            if (R_TCP_WRP_IsConnected() == TRUE) {
                signalStrength = g_tcp_gsm_modem.info.cell_info.signal_quality;
            }
		}
	}
	/* Event "+CGQMIN:" Quality of Service Profile (Min Acceptable) */
	else if (strstr((const char *)p_event->prefix.buffer, "+CGQMIN:") != NULL) {
		if (r_tcp_device_event_handler_cgqmin_and_cgqmin(p_event) == TRUE) {
			p_event->type = GSM_MODEM_EVENT_CGQMIN;
			g_tcp_gsm_modem.setting.quality_of_service.min.precedence  = p_event->data.CGQMIN.precedence;
			g_tcp_gsm_modem.setting.quality_of_service.min.delay       = p_event->data.CGQMIN.delay;
			g_tcp_gsm_modem.setting.quality_of_service.min.reliability = p_event->data.CGQMIN.reliability;
			g_tcp_gsm_modem.setting.quality_of_service.min.peak        = p_event->data.CGQMIN.peak;
			g_tcp_gsm_modem.setting.quality_of_service.min.mean        = p_event->data.CGQMIN.mean;
		}
	}
	/* Event "+CGQREQ:" Quality of Service Profile (Requested) */
	else if (strstr((const char *)p_event->prefix.buffer, "+CGQREQ:") != NULL) {
		if (r_tcp_device_event_handler_cgqmin_and_cgqmin(p_event) == TRUE) {
			p_event->type = GSM_MODEM_EVENT_CGQREQ;
			g_tcp_gsm_modem.setting.quality_of_service.req.precedence  = p_event->data.CGQREQ.precedence;
			g_tcp_gsm_modem.setting.quality_of_service.req.delay       = p_event->data.CGQREQ.delay;
			g_tcp_gsm_modem.setting.quality_of_service.req.reliability = p_event->data.CGQREQ.reliability;
			g_tcp_gsm_modem.setting.quality_of_service.req.peak        = p_event->data.CGQREQ.peak;
			g_tcp_gsm_modem.setting.quality_of_service.req.mean        = p_event->data.CGQREQ.mean;
		}
	}
	/* Event "+COPS:" Operator selection */
	else if (strstr((const char *)p_event->prefix.buffer, "+COPS:") != NULL) {
		if (r_tcp_device_event_handler_cops(p_event) == TRUE) {
			p_event->type = GSM_MODEM_EVENT_COPS;
			memset(g_tcp_gsm_modem.info.operator, 0, sizeof(g_tcp_gsm_modem.info.operator));
			memcpy(g_tcp_gsm_modem.info.operator, (const char *)p_event->data.COPS.operator, strlen((const char *)p_event->data.COPS.operator));
		}
	}
	/* Event "+CGATT:" PS attachment status */
	else if (strstr((const char *)p_event->prefix.buffer, "+CGATT:") != NULL) {
		if (r_tcp_device_event_handler_cgatt(p_event) == TRUE) {
			p_event->type = GSM_MODEM_EVENT_CGATT;
			g_tcp_gsm_modem.info.ps_status = p_event->data.CGATT.state;
		}
	}
	/* Event "+CGDCONT:" PDP context */
	else if (strstr((const char *)p_event->prefix.buffer, "+CGDCONT:") != NULL) {
		if (r_tcp_device_event_handler_cgdcont(p_event) == TRUE) {
			p_event->type = GSM_MODEM_EVENT_CGDCONT;
			memset(g_tcp_gsm_modem.setting.apn_name, 0, TCP_DEVICE_MAX_APN_NAME_LENGTH);
			memcpy(g_tcp_gsm_modem.setting.apn_name, p_event->data.CGDCONT.apn, strlen((const char *)p_event->data.CGDCONT.apn));
		}
	}
	/* Event "+MSDNS:" DNS Query */
	else if (strstr((const char *)p_event->prefix.buffer, "+MSDNS:") != NULL) {
		if (r_tcp_device_event_handler_msdns(p_event) == TRUE) {
			p_event->type = GSM_MODEM_EVENT_MSDNS;
            memcpy(g_tcp_gsm_modem.dns_server.primary   , p_event->data.MSDNS.primary_dns_address   , TCP_DEVICE_IP_SIZE);
            memcpy(g_tcp_gsm_modem.dns_server.secondary , p_event->data.MSDNS.secondary_dns_address , TCP_DEVICE_IP_SIZE);
		}
	}
}

/*
 * Event receiver entry
 */
static uint8_t r_tcp_device_receive_unsolicted_event(uint8_t rx_byte, uint8_t use_timeout)
{
	uint8_t			result = FALSE;

	/* High priority for TCP connect request */
	static uint8_t  tcp_connect_check_index = 0;
	static uint8_t  tcp_connect_request = FALSE;
	const uint8_t	tcp_connect_prefix[] = "+MIPODM:";
	/*
	 * +<prefix>: <content>\r\n
	 */

	/* Restart interframe timeout */
	if (use_timeout == TRUE) {
		g_tcp_at_event_timeout.enable = TRUE;
		g_tcp_at_event_timeout.count = g_tcp_at_event_timeout.initial;
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

                    tcp_connect_check_index = 1;
                    tcp_connect_request = TRUE;
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
                        //g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_PLUS;
                    }
					/* Check if not TCP connect request */
					if (tcp_connect_check_index < sizeof(tcp_connect_prefix) - 1)
					{
						if (tcp_connect_request == TRUE &&
							g_tcp_at_event.prefix.buffer[tcp_connect_check_index] != tcp_connect_prefix[tcp_connect_check_index])
						{
							tcp_connect_request = FALSE;
						}
						tcp_connect_check_index++;
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
						//g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_PLUS;

						if (tcp_connect_request == TRUE) {
							if (g_tcp_gsm_modem.state == GSM_MODEM_STATE_TCP_LISTENING) {
								R_TCP_DEVICE_ConnectIndication(0, g_tcp_dummy_remote_port, (IpAddressPtr)&g_tcp_dummy_remote_ip_addr);
								g_tcp_gsm_modem.state = GSM_MODEM_STATE_TCP_REMOTE_CONNECTED;
							}
							tcp_connect_request = FALSE;
						}
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
	g_tcp_device_send_end = FALSE;
	WRP_UART0_SendData(p_cmd->p_cmd_str, strlen((const char *)p_cmd->p_cmd_str));
	while (g_tcp_device_send_end == FALSE);

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
    /*
    * Check reply buffer to ensure data is pushed
    * +MIPPUSH: 2,0,<length>
    */
    if (g_tcp_at_reply.buffer != NULL &&
        gp_tcp_send_expected_buffer != NULL &&
        strstr((const char *)g_tcp_at_reply.buffer, (const char *)gp_tcp_send_expected_buffer) != NULL)
    {
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
		if (g_tcp_gsm_modem.state < GSM_MODEM_STATE_TCP_LISTENING) {
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
		if (r_tcp_device_receive_unsolicted_event(g_tcp_at_reply.buffer[count], FALSE) == TRUE) {
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
		//g_tcp_at_event.received = FALSE;
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
					if (g_tcp_gsm_modem.state < GSM_MODEM_STATE_TCP_LISTENING) {
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

		g_tcp_gsm_modem.test_id = 0;
		g_tcp_gsm_modem.ptr = NULL;

        /* Status diagnostic for 3G modem */
        memset(&g_tcp_gsm_modem.diag, 0, sizeof(g_tcp_gsm_modem.diag));
        /* By default, all error related to modem initialization and network are asserted */
        g_tcp_gsm_modem.diag.modem_mounted_count = TCP_DEVICE_MODEM_MOUNTED_CONFIRM_TIME;
        //g_tcp_gsm_modem.diag.modem_mounted = FALSE;  // Clear by memset
        g_tcp_gsm_modem.diag.modem_reply_failure = TRUE;
        //g_tcp_gsm_modem.diag.sim_inserted = FALSE; // Clear by memset
        //g_tcp_gsm_modem.diag.sim_good = FALSE; // Clear by memset
        g_tcp_gsm_modem.diag.no_gsm_coverage = TRUE;
        g_tcp_gsm_modem.diag.gprs_registration_failure = TRUE;
        g_tcp_gsm_modem.diag.gprs_registration_denied = TRUE;
        g_tcp_gsm_modem.diag.gprs_connection_drop = TRUE;

		g_tcp_gsm_modem.state = GSM_MODEM_STATE_UNINITIALIZED;
        g_tcp_gsm_modem.socket2_state = GSM_MODEM_SOCKET2_UNINITIALIZED;

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
						if (strlen((const char *)g_tcp_gsm_modem.setting.apn_name) == 0)
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
						g_tcp_gsm_modem.state = GSM_MODEM_STATE_START_LISTEN_SOCKET1;
					}
				}
				break;

			case GSM_MODEM_STATE_START_LISTEN_SOCKET1:
				/* Execute commands to listen TCP connection */
				if (r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.listen, TRUE) == AT_CMD_RESULT_OK) {
					if (g_tcp_gsm_modem.listen.index >= g_tcp_gsm_modem.listen.length) {
						g_tcp_gsm_modem.state = GSM_MODEM_STATE_TCP_LISTENING;
                        g_tcp_gsm_interval_timer.enable = TRUE;
                        /* Temporarily disable the first breath until +MIPCALL:0 captured */
                        //R_TCP_DEVICE_FirstBreathEventHappenCallback();
                        /* Force updating the signal strength */
                        signalStrength = g_tcp_gsm_modem.info.cell_info.signal_quality;
                    }
				}
				break;

			case GSM_MODEM_STATE_TCP_LISTENING:
				/*
				 * Wait for TCP remote connect unsolicted event
				 * During waiting here, query Gsm Modem info (if any)
				 */
				if (g_tcp_gsm_modem.periodic_job == TRUE) {
					R_RTC_Get_CalendarCounterValue(&g_tcp_gsm_modem.info.capture_time);
					r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.query);
					g_tcp_gsm_modem.periodic_job = FALSE;
				}
				r_tcp_device_execute_at_runner(&g_tcp_gsm_modem.query, TRUE);
				break;

			case GSM_MODEM_STATE_TCP_REMOTE_CONNECTED:
				/* (Online Data Mode) Wait for remote disconnect event */
				break;

			case GSM_MODEM_STATE_TCP_REMOTE_DISCONNECTED:
				/* Switch back to GSM_MODEM_STATE_JOIN_GPRS to execute command to listen TCP connection again */
				r_tcp_device_start_at_runner_execution(&g_tcp_gsm_modem.listen);
				g_tcp_gsm_modem.state = GSM_MODEM_STATE_START_LISTEN_SOCKET1;
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
	uint8_t			status = FALSE;

	AtRunner runner = { g_tcp_device_open_socket2_at_commands, sizeof(g_tcp_device_open_socket2_at_commands) / sizeof(AtCommand), 0, 0, 0 };

	/* TCP Channel 0 & listen on Socket 1 complete */
	if (tcp_channel == 0 &&
		g_tcp_gsm_modem.state == GSM_MODEM_STATE_TCP_LISTENING &&
		g_tcp_gsm_modem.socket2_state != GSM_MODEM_SOCKET2_OPENED)
	{
        /* Diagnose destination, not affect push operation, just for raising diag code */
        if (r_tcp_device_is_valid_destination(remote_tcp_port, remote_ip_address) == FALSE)
        {
            /* Not allow to open the connection if remote destination is invalid and mark the error code */
            const uint8_t error_string[] = "Remote destination unknown";
            g_tcp_gsm_modem.diag.remote_destination_invalid = TRUE;
            R_TCP_DEVICE_ConnectConfirm(tcp_channel, FALSE, (uint8_t *)error_string, strlen((const char *)error_string));
        }
        else 
        {   
            /* Correct remote destination, try opening */
            g_tcp_gsm_modem.diag.remote_destination_invalid = FALSE;
    		status = TRUE;
            fails_count = 0;
            memcpy(g_tcp_gsm_modem.remote.ip_buffer, remote_ip_address->p_addr, 16);
            g_tcp_gsm_modem.remote.port_number = remote_tcp_port;
    		r_tcp_device_start_at_runner_execution(&runner);
    		while (runner.index < runner.length)
    		{
    			if (r_tcp_device_execute_at_runner(&runner, TRUE) == AT_CMD_RESULT_TIMED_OUT) {
    				fails_count++;
    			}

    			/* Fail 2 times script stop */
    			if (fails_count > 1) {
    				status = FALSE;
    				break;
    			}
    			R_WDT_Restart();
    		}

            if (status == TRUE) {
                g_tcp_gsm_modem.diag.remote_destination_unreachable = FALSE;
                g_tcp_gsm_modem.socket2_state = GSM_MODEM_SOCKET2_OPENED;
                R_TCP_DEVICE_ConnectConfirm(tcp_channel, status, NULL, 0);
            }
            else {
                const uint8_t error_string[] = "Fibocom H310 Modem can not open socket 2";

                g_tcp_gsm_modem.diag.remote_destination_unreachable = TRUE;

                /* Emergergency exit: no need to open socket 1 again, prepare to sleep */
                if (EVENT_IsLastGasp() == TRUE) {
                    R_TCP_DEVICE_ConnectConfirm(tcp_channel, FALSE, (uint8_t *)error_string, strlen((const char *)error_string));
                    return FALSE;
                }

                /* Resume socket 1 listening */
                fails_count = 0;
                runner.p_commands = g_tcp_device_socket1_listen_script;
                runner.length = sizeof(g_tcp_device_socket1_listen_script) / sizeof(AtCommand);
                r_tcp_device_start_at_runner_execution(&runner);
                while (runner.index < runner.length) {
                    if (r_tcp_device_execute_at_runner(&runner, TRUE) == AT_CMD_RESULT_TIMED_OUT) {
                        fails_count++;
                    }
                    /* Fail x+1 times script stop */
                    if (fails_count > 3) {
                        status = FALSE;
                        break;
                    }
                    R_WDT_Restart();
                }

                R_TCP_DEVICE_ConnectConfirm(tcp_channel, status, (uint8_t *)error_string, strlen((const char *)error_string));
            }
        }
	}

    return (status);
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
	uint8_t		status = FALSE;

	AtRunner runner = { g_tcp_device_close_socket2_at_commands, sizeof(g_tcp_device_close_socket2_at_commands) / sizeof(AtCommand), 0, 0, 0 };

	/* TCP Channel 0 & listen on Socket 1 complete */
	if (tcp_channel == 0 &&
		g_tcp_gsm_modem.state == GSM_MODEM_STATE_TCP_LISTENING &&
		g_tcp_gsm_modem.socket2_state == GSM_MODEM_SOCKET2_OPENED)
	{
		status = TRUE;
		r_tcp_device_start_at_runner_execution(&runner);
        fails_count = 0;
		while (runner.index < runner.length)
		{
			if (r_tcp_device_execute_at_runner(&runner, TRUE) == AT_CMD_RESULT_TIMED_OUT) {
				fails_count++;
			}
			if (fails_count > 2) {
				status = FALSE;
				break;
			}
			R_WDT_Restart();
		}

        /* Emergergency exit: no need to open socket 1 again, prepare to sleep */
        if (EVENT_IsLastGasp() == TRUE) {
            R_TCP_DEVICE_DisconnectConfirm(tcp_channel, TRUE, NULL, 0);
            return TRUE;
        }

		/* Resume socket 1 listening */
		runner.p_commands = g_tcp_device_socket1_listen_script;
		runner.length = sizeof(g_tcp_device_socket1_listen_script) / sizeof(AtCommand);
        fails_count = 0;
        r_tcp_device_start_at_runner_execution(&runner);
		while (runner.index < runner.length) {
			if (r_tcp_device_execute_at_runner(&runner, TRUE) == AT_CMD_RESULT_TIMED_OUT) {
				fails_count++;
			}
            if (fails_count > 2) {
                status = FALSE;
                break;
            }
			R_WDT_Restart();
		}

		if (status == TRUE) {
			g_tcp_gsm_modem.socket2_state = GSM_MODEM_SOCKET2_CLOSED;
			R_TCP_DEVICE_DisconnectConfirm(tcp_channel, status, NULL, 0);
		}
		else {
			const uint8_t error_string[] = "Fibocom H310 Modem can not close socket 2";
			R_TCP_DEVICE_DisconnectConfirm(tcp_channel, status, (uint8_t *)error_string, strlen((const char *)error_string));
		}
	}

	return (status);
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

	const uint8_t at_mipsend[] = "AT+MIPSEND=2,";

	/* TCP Channel 0 */
	if (tcp_channel == 0)
	{
		if (g_tcp_gsm_modem.state == GSM_MODEM_STATE_TCP_REMOTE_CONNECTED)
		{
			g_tcp_device_send_end = FALSE;
			WRP_UART0_SendData(data, length);
			while (g_tcp_device_send_end == FALSE);

			status = TRUE;
		}
		else if (g_tcp_gsm_modem.socket2_state == GSM_MODEM_SOCKET2_OPENED)
		{
			/* Prepare reply buffer */
			r_tcp_device_prepare_cmd_reply();
			g_tcp_at_event_timeout.enable = FALSE;
			g_tcp_at_event.received = FALSE;
			g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_PREFIX;

			/* AT+MIPSEND=2,<length>\r\n (Hex Data Mode, Fixed Length, Auto Push) */
			g_tcp_device_send_end = FALSE;
			WRP_UART0_SendData((uint8_t *)at_mipsend, strlen((char *)at_mipsend));
			while (g_tcp_device_send_end == FALSE);
			memset(buffer, 0, 16);
			count = sprintf((char *)buffer, "%d\r\n", length);
			g_tcp_device_send_end = FALSE;
			WRP_UART0_SendData(buffer, count);
			while (g_tcp_device_send_end == FALSE);

			/* Wait for until data prompt sign appear */
            status = WRP_EXT_HwDelay(500, r_tcp_device_wait_send_prompt_sign_predicate);
			
			/* Send out all bytes in HEX */
			g_tcp_device_send_end = FALSE;
			WRP_UART0_SendData(data, length);
			while (g_tcp_device_send_end == FALSE);

            sprintf((char *)buffer, "+MIPSEND: 2,0,2048\r\n", length);
            gp_tcp_send_expected_buffer = buffer;

			/* Wait for timeout or until receive send confirmed to terminate */
            status = WRP_EXT_HwDelay(4000, r_tcp_device_wait_send_predicate);

            if (status != WRP_EXT_HW_DELAY_TIMEOUT) {
                status = TRUE;
                WRP_EXT_HwDelay(500, NULL);
            }
            else {
                status = FALSE;
            }

			/* Unregister cmd reply from UART rx interrupt */
			g_tcp_at_event_timeout.enable = FALSE;
			//g_tcp_at_event.received = FALSE;
			//g_tcp_at_event.state = TCP_DEVICE_AT_EVENT_STATE_PREFIX;
            r_tcp_device_acknowledge_event_received();
			r_tcp_device_unregister_cmd_reply();
		}

        g_tcp_gsm_modem.pushing_lastgasp = FALSE;
	}

    if (status == FALSE) {
        g_tcp_gsm_modem.diag.remote_data_sending_failure = TRUE;
    }
    else {
        g_tcp_gsm_modem.diag.remote_data_sending_failure = FALSE;
    }

	/* Confirm as data request is finished */
	R_TCP_DEVICE_DataConfirm(tcp_channel, status);

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
	{
        /* When reboot, do power cycle */
#if (TCP_DEVICE_MODULE_POWER_CONTROL_SUPPORT == TRUE)
        BIT_SELECT(P5, 3) = 0;
        MCU_Delay(5000);
        BIT_SELECT(P5, 3) = 1;
#endif
		/* Reset all state & event receiver */
		/* Settting & Info */
		/* g_tcp_gsm_modem.setting is backup in EEPROM */
        //memset(&g_tcp_gsm_modem.setting, 0, sizeof(g_tcp_gsm_modem.setting));
        memset(&g_tcp_gsm_modem.info, 0, sizeof(g_tcp_gsm_modem.info));
        //memcpy(g_tcp_gsm_modem.setting.apn_name, TCP_DEVICE_DEFAULT_APN_NAME, strlen(TCP_DEVICE_DEFAULT_APN_NAME));

        /* Trigger */
        g_tcp_gsm_modem.periodic_job = FALSE;

        /* Local ipv6 & port number */
        g_tcp_gsm_modem.local.port_number = 4059;
        g_tcp_gsm_modem.local.ip.p_addr = g_tcp_gsm_modem.local.ip_buffer;
        g_tcp_gsm_modem.local.ip.size = TCP_DEVICE_IP_SIZE;
        memset(g_tcp_gsm_modem.local.ip_buffer, 0, TCP_DEVICE_IP_SIZE);

        /* Remote ip6 & port number */
        g_tcp_gsm_modem.remote.port_number = 4059;
        g_tcp_gsm_modem.remote.ip.p_addr = g_tcp_gsm_modem.remote.ip_buffer;
        g_tcp_gsm_modem.remote.ip.size = TCP_DEVICE_IP_SIZE;
        memset(g_tcp_gsm_modem.remote.ip_buffer, 0, TCP_DEVICE_IP_SIZE);

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

        /* Adaptation with previous velankani implementation: clear signal strength indicator */
        signalStrength = 0;

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
	R_DLMS_EventReport_FirstBreath();
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
	if (channel == 0)
	{
		/* TCP Data Indication when have "Online Data Mode" */
		if (g_tcp_gsm_modem.state == GSM_MODEM_STATE_TCP_REMOTE_CONNECTED)
		{
			R_TCP_DEVICE_DataIndication(
				channel,
				g_tcp_dummy_remote_port,
				(IpAddressPtr)&g_tcp_dummy_remote_ip_addr,
				&received_byte,
				1
			);
		}

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
			r_tcp_device_receive_unsolicted_event(received_byte, TRUE);
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
	if (g_tcp_gsm_modem.state == GSM_MODEM_STATE_TCP_LISTENING) {
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
#if(defined(R_DLMS_APPS_MALLOC_USING) && (R_DLMS_APPS_MALLOC_USING == TRUE))
    p_test_result = WRP_EXT_Heap_Malloc(num_of_test_cases);
#else
	uint8_t test_result_buffer[sizeof(test_vector) / sizeof(tcp_test_ip_parser)];
	p_test_result = test_result_buffer;
#endif

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
#if(defined(R_DLMS_APPS_MALLOC_USING) && (R_DLMS_APPS_MALLOC_USING == TRUE))
    WRP_EXT_Heap_Free(p_test_result);
#endif

    return result;
}

#endif /* #if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == FALSE) */