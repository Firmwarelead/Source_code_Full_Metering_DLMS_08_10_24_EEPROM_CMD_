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
* File Name    : r_dlms_tcp_wrapper_dummy.c
* Version      : 1.00
* Device(s)    : R5F564MLCxDC
* Tool-Chain   : CCRX
* H/W Platform : RX64M RSK+
* Description  : TCP wrapper layer of DLMS
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.05.2016
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"

#include "typedef.h"
#include "wrp_app_uart.h"
#include "wrp_app_mcu.h"
#include "r_cg_wdt.h"

#include "r_dlms_tcp.h"
#include "r_dlms_tcp_wrapper.h"
#include "r_dlms_tcp_wrapper_interface.h"

#include "r_dlms_wrapper_conversion_ip.h"

#include "r_dlms_config.h"

#include <string.h>
#include <stdio.h>              /* Standard IO */
#include <stdarg.h>             /* Variables argument */
#include "r_dlms_com_wrapper_config.h"
#if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == TRUE) && (TCP_MODE_SELECTION == TCP_MODE_USR_TCP232_MODULE)


/******************************************************************************
Macro definitions
******************************************************************************/
#define USR_TCP232_CONFIG_EN                { SET_BIT(P3, 1, 0U); }                      
#define USR_TCP232_CONFIG_DISABLE           { SET_BIT(P3, 1, 0U); }  
#define USR_TCP232_CONN_FLAG                ( BIT_SELECT( P0 , 5) )



#define TCP_WRP_RAW_DLMS_PORT               (4059)

#define UC_FLAG_DHCP                        (0x00)
#define UC_FLAG_STATIC_IP                   (0x80)

#define USR_TCP_DEBUG_ENABLE                (FALSE)

#if(defined( USR_TCP_DEBUG_ENABLE ) && USR_TCP_DEBUG_ENABLE == TRUE)
    #define MAX_DEBUG_BUFFER_INFO           (10)
    #define DEBUG_TRACE(va_fucn, va_params)                                 \
        {                                                                   \
            g_usr_debug[g_usr_debug_counter].func_id       = va_fucn;       \
            g_usr_debug[g_usr_debug_counter].params        = va_params;     \
			g_usr_debug_counter++;                                          \
            g_usr_debug_counter %=  MAX_DEBUG_BUFFER_INFO;                  \
        }
#else
    #define MAX_DEBUG_BUFFER_INFO           (1)
    #define DEBUG_TRACE(va_fucn, va_params)                {;}
#endif

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum tag_usr_tcp232_mode_t
{
    USR_TCP233_TRANSFER,
    USR_TCP233_CONFIGURE,
} usr_tcp232_mode_t;

typedef enum tag_usr_tcp232_workmode_t
{
    USR_TCP232_UDP,
    USR_TCP232_TCP_CLIENT,
    USR_TCP232_UDP_SERVER,
    USR_TCP232_TCP_SERVER,
    USR_TCP232_HTTPD_CLIENT
} usr_tcp232_workmode_t;

typedef struct tag_tcp232_basic_setting_t
{
    uint8_t ucSequenceNum;
    uint8_t ucCRC;
    uint8_t ucVersion;
    uint8_t ucFlags;
    uint8_t usLocationURLPort[2];
    uint8_t usHTTPServerPort[2];
    uint8_t ucUserFlag;
    uint8_t ulStaticIP[4];
    uint8_t ulGatewayIP[4];
    uint8_t ulSubnetMask[4];
    uint8_t ucModName[14];
    uint8_t ProtocolReserved[2];
    uint8_t username[6];
    uint8_t password[6];
    uint8_t ucNetSendTime;
    uint8_t uiId[2];
    union
    {
        uint8_t ucIdType;
        struct {
            uint8_t bit0_SendID_Conn    : 1;
            uint8_t bit1_SendID_Send    : 1;
            uint8_t bit2_RS485          : 1;
            uint8_t bit3                : 1;
            uint8_t bit4_Reset          : 1;
            uint8_t bit5_LinkState      : 1;
            uint8_t bit6_IndexFucntion  : 1;
            uint8_t bit7_SimilarRFC2217 : 1;
        } ucIDType_bits;
    };
    uint8_t mac_addrs[6];
    uint8_t DNSGatewayIP[4];
    uint8_t ucReserved[4];
} tcp232_basic_setting_t;

typedef struct tag_tcp232_basic_cfg_frame_t
{
    uint8_t                     SOF[2];
    tcp232_basic_setting_t      settings;
    uint8_t                     checkbit;
} tcp232_basic_cfg_frame_t;

typedef struct tag_tcp232_port_setting_t
{
    uint8_t ulBaudRate[4];
    uint8_t ucDataSize;
    uint8_t ucParity;
    uint8_t ucStopBits;
    uint8_t ucFlowControl;
    uint8_t ulTelnetTimeout[4];
    uint8_t usTelnetLocalPort[2];
    uint8_t usTelnetRemotePort[2];
    uint8_t uiTelnetURL[30];
    uint8_t ulTelnetIPAddr[4];
    uint8_t ucFlags;
    uint8_t ucWorkMode;
    uint8_t HTPucFlags;
    uint8_t tc_number;
    uint8_t uiPackLen[2];
    uint8_t ucPackTime;
    uint8_t ucTimeCount;
    uint8_t ucReserved[5];
} tcp232_port_setting_t;

typedef struct tag_tcp232_port_setting_frame_t
{
    uint8_t                     SOF[2];
    tcp232_port_setting_t       settings;
    uint8_t                     checkbit;
} tcp232_port_setting_frame_t;

typedef struct tag_tcp232_read_config_t
{
    uint8_t ucSequenceNum;
    uint8_t ucCRC;
    uint8_t ucVersion;
    uint8_t ucFlags01;
    uint8_t usLocationURLPort[2];
    uint8_t usHTTPServerPort[2];
    uint8_t ucUserFlag;
    uint8_t ulStaticIP[4];
    uint8_t ulGatewayIP[4];
    uint8_t ulSubnetMask[4];
    uint8_t ucModName[14];
    uint8_t ProtocolReserved[2];
    uint8_t username[6];
    uint8_t password[6];
    uint8_t ucNetSendTime;
    uint8_t uiId[2];
    uint8_t ucIdType;
    uint8_t mac_addrs[6];
    uint8_t DNS_Gateway_IP[4];
    uint8_t ucReserved0[4];
    uint8_t ulBaudRate[4];
    uint8_t ucDataSize;
    uint8_t ucParity;
    uint8_t ucStopBits;
    uint8_t ucFlowControl;
    uint8_t ulTelnetTimeout[4];
    uint8_t usTelnetLocalPort[2];
    uint8_t usTelnetRemotePort[2];
    uint8_t uiTelnetURL[30];
    uint8_t ulTelnetIPAddr[4];
    uint8_t ucFlags02;
    uint8_t ucWorkMode;
    uint8_t HTPucFlags;
    uint8_t tc_number;
    uint8_t uiPackLen[2];
    uint8_t ucPackTime;
    uint8_t ucTimeCount;
    uint8_t ucReserved1[5];
    uint8_t Current_IP[4];
    uint8_t Version;
} tcp232_read_config_t;


typedef struct
{
	uint16_t	initial;
	uint16_t	count;
	uint16_t	enable;
} tcp232_conn_timeout_t;

#if(defined( USR_TCP_DEBUG_ENABLE ) && USR_TCP_DEBUG_ENABLE == TRUE)
typedef struct tag_debug_usr_package_info_t
{
    uint8_t func_id;
    uint8_t params;
} debug_usr_package_info_t;
#endif

typedef enum tag_usr_step_t
{
    USR_MODULE_STEP_INIT,
    USR_MODULE_STEP_SET_CONFIG,
    USR_MODULE_STEP_GET_CONFIG,
    USR_MODULE_STEP_RESTART,
    USR_MODULE_STEP_SWITCH_TO_CONFIG_MODE,
    USR_MODULE_STEP_SWITCH_TO_TRANSFER_MODE,
    USR_MODULE_STEP_SENDING,
    USR_MODULE_STEP_RECEIVING,
    USR_MODULE_STEP_SEND_ETHERNET_CONFIG,
    USR_MODULE_STEP_SEND_SERIALPORT_CONFIG,
} usr_step_t;

typedef enum tag_usr_module_response_t
{
    USR_MODULE_RESPONSE_OK,
    USR_MODULE_RESPONSE_ERROR,
    USR_MODULE_RESPONSE_OTHER,
    USR_MODULE_RESPONSE_TIMEOUT
} usr_module_response_t;

typedef enum tag_usr_module_active_connect_state_t
{
    TCP_ACTIVE_CONNECTED,
    TCP_ACTIVE_DISCONNECTED
} usr_module_active_connect_state_t;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
extern volatile uint8_t g_client_connection_flag;
volatile usr_tcp232_mode_t g_usr_tcp232_mode;

/******************************************************************************
Private global variables and functions
******************************************************************************/
void R_USRTCP232_RESTART ( void );
uint8_t R_USRTCP232_WaitConfirmResponse ( void );
static void R_WRP_SendBuffer(uint8_t *buffer, uint16_t length);

static volatile uint8_t g_config_write_confirm_received = FALSE;

volatile uint8_t g_tcp_active_connect = FALSE;
volatile uint8_t g_tcp_active_connect_state = TCP_ACTIVE_DISCONNECTED;

volatile uint8_t g_tcp_module_operating_mode = USR_TCP232_TCP_SERVER;
volatile uint8_t g_tcp_connect_client_timeout = FALSE;

volatile uint8_t g_tcp_module_return_servermode = FALSE;

volatile uint8_t g_tcp_sync_mode = FALSE;

static uint8_t g_tcp_module_local_address_buffer[16] = {192, 168, 0, 20};
const IpAddress g_tcp_module_local_address =
{
    g_tcp_module_local_address_buffer,
    4
};
static uint8_t g_tcp_module_remote_address_buffer[16] = {192, 168, 0, 5};
const IpAddress g_tcp_module_remote_address =
{
    g_tcp_module_remote_address_buffer,
    4
};

#define MAX_TCP_BUFFER_SIZE		(140)
uint8_t g_tcp_usr_config_confirm_buffer[140];
static uint8_t g_buffer_byte_count = 0;
static uint8_t g_buffer_byte_total = 0;
volatile uint8_t g_wrp_send_end = TRUE;       /* Send end */


const uint8_t G_USR_TCP232_READCFG_COMMNAD[] = { 0x55, 0xBD };
const uint8_t G_USR_TCP232_RESTART_COMMNAD[] = { 0x55, 0xB1, 0x5A};


tcp232_conn_timeout_t g_tcp_client_conn_timeout;
tcp232_conn_timeout_t g_tcp_sync_timeout;

// uint8_t g_remote_ip[4] = {192, 168, 0, 5};
uint16_t g_remote_port = 4059;
uint16_t g_local_port = 4059;

usr_step_t g_usr_module_step;
usr_module_response_t g_usr_module_response;

#if(defined( USR_TCP_DEBUG_ENABLE ) && USR_TCP_DEBUG_ENABLE == TRUE)
debug_usr_package_info_t    g_usr_debug[MAX_DEBUG_BUFFER_INFO];
uint8_t                     g_usr_debug_counter = 0;
#endif /* USR_TCP_DEBUG_ENABLE */



/**********************************************
 * 
 *  Hardware connection
 * 
 *     Smart Meter        USR-TCP232-T2
 *     +---------+         +---------+  
 *     |         |         |         |    
 *     |   P0.5 -| <-----  |(Link)   | 
 *     |         |         |         |   
 *     |         |         |         |    
 *     +---------+         +---------+  
 * 
 **********************************************/

// Serial port setting protocol

/******************************************************************************
* Function Name : R_USR_TCP232_Calculate_Checkbit
* Interface     : uint8_t R_USR_TCP232_Calculate_Checkbit(
*               :     uint8_t *p_buffer, uint16_t length
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_USR_TCP232_Calculate_Checkbit ( uint8_t *p_buffer, uint16_t length )
{
    uint16_t pos;
    uint8_t checkbit = 0;

    if (p_buffer == NULL)
    {
        return 0;
    }
    for (pos = 0; pos < length; pos++)
    {
        checkbit += p_buffer[pos];
    }
    return checkbit;
}

/******************************************************************************
* Function Name : R_USRTCP232_GetConnectionState
* Interface     : uint8_t R_USRTCP232_GetConnectionState(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_USRTCP232_GetConnectionState ( void )
{
    if ( USR_TCP232_CONN_FLAG == 0 )
    {
        return TRUE;    /* Client connected */
    }
    else
    {
        return FALSE;   /* Client disconnected */
    }
}

/******************************************************************************
* Function Name : R_USRTCP232_SwitchToConfigMode
* Interface     : void R_USRTCP232_SwitchToConfigMode(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_USRTCP232_SwitchToConfigMode ( void )
{
    if (g_usr_tcp232_mode == USR_TCP233_TRANSFER)
    {
        g_usr_tcp232_mode = USR_TCP233_CONFIGURE;
        g_usr_module_step = USR_MODULE_STEP_SWITCH_TO_CONFIG_MODE;

        WRP_UART0_Stop();
        WRP_UART0_SetBaudRate(WRP_UART_BAUD_RATE_9600);
        WRP_UART0_ConfigHDLCProtocol();
        WRP_UART0_Start();
        
        g_buffer_byte_count = 0;
        g_buffer_byte_total = 1;
        g_config_write_confirm_received = FALSE;
        
        SET_BIT(P3, 1, 0U);

        R_USRTCP232_WaitConfirmResponse();
    }
}

/******************************************************************************
* Function Name : R_USRTCP232_SwitchToTransferMode
* Interface     : void R_USRTCP232_SwitchToTransferMode(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_USRTCP232_SwitchToTransferMode ( void )
{
    g_usr_module_step = USR_MODULE_STEP_SWITCH_TO_TRANSFER_MODE;
    g_usr_tcp232_mode = USR_TCP233_TRANSFER;

    WRP_UART0_Stop();
	WRP_UART0_SetBaudRate(WRP_UART_BAUD_RATE_19200);
	WRP_UART0_ConfigHDLCProtocol();
    WRP_UART0_Start();
    
    SET_BIT(P3, 1, 1U);
}


/******************************************************************************
* Function Name : R_USRTCP232_WaitConfirmResponse
* Interface     : void R_USRTCP232_WaitConfirmResponse(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_USRTCP232_WaitConfirmResponse ( void )
{
    volatile uint32_t count;

    // g_config_write_confirm_received = FALSE;
    /* Wait until receive cfgw confirm from module */
    count = 50;
    while (g_config_write_confirm_received == FALSE)
    {
        MCU_Delay(10000);
        R_WDT_Restart();
        
        count--;
        if (count == 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

/******************************************************************************
* Function Name : R_USRTCP232_ReadCnf
* Interface     : void R_USRTCP232_ReadCnf(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_USRTCP232_ReadCnf ( void )
{
    R_USRTCP232_SwitchToConfigMode();

    g_buffer_byte_count = 0;
    g_buffer_byte_total = 137;
    g_config_write_confirm_received = FALSE;

    /* Set configure */
    R_WRP_SendBuffer(
        (uint8_t *)&G_USR_TCP232_READCFG_COMMNAD, 
        sizeof(G_USR_TCP232_READCFG_COMMNAD)
    );

    /* Wait frame BE 4B from USR */
    R_USRTCP232_WaitConfirmResponse();

    // R_USRTCP232_SwitchToTransferMode();
}



/******************************************************************************
* Function Name : R_USRTCP232_SetMode
* Interface     : void R_USRTCP232_SetMode(
*               :     uint8_t work_mode
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_USRTCP232_SetMode ( uint8_t work_mode, IpAddressPtr remote_ip, uint16_t remote_port )
{
    tcp232_port_setting_frame_t port0_setting;      /* Setting Serial configure */
	uint16_t converted_len = 0;

	/* Req connection */
	if (g_usr_tcp232_mode == USR_TCP233_TRANSFER)
	{
		R_USRTCP232_SwitchToConfigMode();
	}
 
	g_usr_module_step = USR_MODULE_STEP_SEND_SERIALPORT_CONFIG;
    {
        port0_setting.SOF[0] = 0x55;
        port0_setting.SOF[1] = 0xBF;

        memset((uint8_t *)&port0_setting.settings, 0,  sizeof(tcp232_port_setting_t));

        #if 1       /* 19200 */
        //port0_setting.settings.ulBaudRate[0] = 0x00;
        port0_setting.settings.ulBaudRate[1] = 0x4B;
        //port0_setting.settings.ulBaudRate[2] = 0x00;
        //port0_setting.settings.ulBaudRate[3] = 0x00;
        #else       /* 9600 */
        port0_setting.settings.ulBaudRate[0] = 0x80;
        port0_setting.settings.ulBaudRate[1] = 0x25;
        //port0_setting.settings.ulBaudRate[2] = 0x00;
        //port0_setting.settings.ulBaudRate[3] = 0x00;
        #endif
        
        port0_setting.settings.ucDataSize = 8;
        port0_setting.settings.ucParity = 1;
        port0_setting.settings.ucStopBits = 1;

        memcpy(
            port0_setting.settings.usTelnetLocalPort,
            (uint8_t *)&remote_port,
            2
        );
        memcpy(
            port0_setting.settings.usTelnetRemotePort,
            (uint8_t *)&remote_port,
            2
        );
        
        memset(port0_setting.settings.uiTelnetURL, 0, 30);
        R_DLMS_ConvertIpAddressToString((uint8_t *) port0_setting.settings.uiTelnetURL, &converted_len, remote_ip);

        port0_setting.settings.ucWorkMode = work_mode; /* TCP client */

        port0_setting.settings.tc_number = 1;

        port0_setting.checkbit = R_USR_TCP232_Calculate_Checkbit(
						             (uint8_t *)&port0_setting.settings,
						             sizeof(tcp232_port_setting_t)
						        );
    }

    g_buffer_byte_count = 0;
    g_buffer_byte_total = 2;
    g_config_write_confirm_received = FALSE;
		
    /* Set configure */
    R_WRP_SendBuffer(
        (uint8_t *)&port0_setting, 
        sizeof(tcp232_port_setting_frame_t)
    );
    /* Wait frame BE 4B from USR */
    R_USRTCP232_WaitConfirmResponse();

    R_USRTCP232_RESTART();
	
	MCU_Delay(10000);
	R_WDT_Restart();
	MCU_Delay(10000);
	R_WDT_Restart();

}

/******************************************************************************
* Function Name : R_USRTCP232_RESTART
* Interface     : void R_USRTCP232_RESTART(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_USRTCP232_RESTART ( void )
{
    g_usr_module_step = USR_MODULE_STEP_RESTART;
    if (g_usr_tcp232_mode == USR_TCP233_TRANSFER)
	{
		R_USRTCP232_SwitchToConfigMode();
	}

    g_buffer_byte_count = 0;
    g_buffer_byte_total = 2;
    g_config_write_confirm_received = FALSE;
    
    R_WRP_SendBuffer(
        (uint8_t *)G_USR_TCP232_RESTART_COMMNAD, 
        sizeof(G_USR_TCP232_RESTART_COMMNAD)
    );

    R_USRTCP232_WaitConfirmResponse();

    MCU_Delay(10000);
	R_WDT_Restart();

    // R_USRTCP232_SwitchToTransferMode();
}

/******************************************************************************
* Function Name : R_USRTCP232_ClientMode_Timeout_Callback
* Interface     : void R_USRTCP232_ClientMode_Timeout_Callback(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_USRTCP232_ClientMode_Timeout_Callback ( void )
{
    g_tcp_connect_client_timeout = TRUE;
}
/******************************************************************************
* Function Name : R_USRTCP232_CheckConnectionState
* Interface     : void R_USRTCP232_CheckConnectionState(
*               :     voi
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_USRTCP232_CheckConnectionState ( void )
{
	static uint8_t counter = 0;
    uint8_t arbort_reason = 0x00;
    if (g_client_connection_flag == 1)
    {
        if (R_USRTCP232_GetConnectionState() == TRUE)
        {
            R_TCP_DEVICE_ConnectIndication(
                0, 
                TCP_WRP_RAW_DLMS_PORT,
                (IpAddressPtr)&g_tcp_module_remote_address            /* Remote IP Address */
            );
            if (g_tcp_active_connect == TRUE)
            {
                g_tcp_active_connect_state = TCP_ACTIVE_CONNECTED;
				g_tcp_module_return_servermode = FALSE;
            }
        }
        else
        {
            R_TCP_DEVICE_DisconnectIndication(
                0,
                TCP_WRP_RAW_DLMS_PORT,
                (IpAddressPtr)&g_tcp_module_remote_address,            /* Remote IP Address */
                TCP_DISCONNECT_REMOTE_REQ
            );
            R_TCP_DEVICE_AbortIndication(
                0,
                TCP_WRP_RAW_DLMS_PORT,
                (IpAddressPtr)&g_tcp_module_remote_address,            /* Remote IP Address */
                &arbort_reason,
                1
            );
            if ((g_tcp_active_connect == TRUE) &&
                (g_tcp_active_connect_state == TCP_ACTIVE_CONNECTED))
            {
				g_tcp_active_connect = FALSE;
            	g_tcp_active_connect_state = TCP_ACTIVE_DISCONNECTED;
            	g_tcp_module_return_servermode = TRUE;
            }
        }
        g_client_connection_flag = 0;
    }
}




// AT command


/******************************************************************************
* Function Name : R_WRP_SendBuffer
* Interface     : static void R_WRP_SendBuffer(uint8_t *buffer, uint16_t length)
* Description   : 
* Arguments     : uint8_t * buffer:
*               : uint16_t length :
* Function Calls: 
* Return Value  : static void
******************************************************************************/
static void R_WRP_SendBuffer(uint8_t *buffer, uint16_t length)
{
	g_wrp_send_end = FALSE;
	WRP_UART0_SendData(buffer, length);
	
	// R_WRP_RESET_INTERFRAME_TIMEOUT(g_interframe_timeout);
	while (g_wrp_send_end == FALSE);
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
        WRP_UART0_Init();
        WRP_UART0_SetBaudRate(WRP_UART_BAUD_RATE_9600);
        WRP_UART0_ConfigHDLCProtocol();
    }
    g_usr_module_step = USR_MODULE_STEP_INIT;
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
        WRP_UART0_Start();
    }
	R_USRTCP232_SwitchToTransferMode();
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
        WRP_UART0_Stop();
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
    if (tcp_channel == 0) {
        R_USRTCP232_CheckConnectionState();

        if (g_tcp_module_return_servermode == TRUE)
        {
			R_USRTCP232_ReadCnf();

            if (g_tcp_module_operating_mode == USR_TCP232_TCP_SERVER)
            {
				g_tcp_module_return_servermode = FALSE;
				g_tcp_active_connect = FALSE;
            }
			else
			{
				R_USRTCP232_SetMode(
	                USR_TCP232_TCP_SERVER, 
	                (IpAddressPtr)&g_tcp_module_local_address, 
	                g_local_port
            	);
				g_tcp_module_return_servermode = FALSE;
			}
			R_USRTCP232_SwitchToTransferMode();
        }
	}
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
    volatile uint32_t count;

	/* TODO: Get config of UDP module, port and ip */
	if (tcp_channel == 0) {
        R_USRTCP232_ReadCnf();
        R_USRTCP232_SwitchToTransferMode();
	}

	return 0;
}

const uint8_t g_user_name_pwd[] = "admin";
const uint8_t g_module_name[] = "TCP-233-T2";
const uint8_t g_mac_addr[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};

const uint8_t   g_static_ip_buffer[4] = { 20, 0, 168, 192 };
const IpAddress g_static_ip = { (uint8_t *)g_static_ip_buffer, 4 };

const uint8_t   g_Gateway_ip_buffer[4] = { 1, 0, 168, 192 };
const IpAddress g_Gateway_ip = { (uint8_t *)g_Gateway_ip_buffer, 4 };

const uint8_t   g_SubnetMask_ip_buffer[4] = { 0, 255, 255, 255 };
const IpAddress g_SubnetMask_ip = { (uint8_t *)g_SubnetMask_ip_buffer, 4 };

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
    volatile uint32_t count;
    tcp232_basic_cfg_frame_t T2_settting;           /* Setting IP, network */

	/* TODO: Set config of UDP module, port and ip */
	uint8_t ip_buffer[30];

	if (tcp_channel == 0) {
		
        R_USRTCP232_SwitchToConfigMode();

        /* Set ethernet config to module */
        {
            /* Copy setting */
            {
                T2_settting.SOF[0] = 0x55;
                T2_settting.SOF[1] = 0xBE;

                memset((uint8_t *)&T2_settting.settings, 0, sizeof(tcp232_basic_setting_t));

                T2_settting.settings.ucFlags = 0x80;      /* Static IP */

                memcpy(T2_settting.settings.ulStaticIP,     p_config->local_ip_address->p_addr, p_config->local_ip_address->size);
				R_DLMS_ReverseBuffer(T2_settting.settings.ulStaticIP, 4);
                memcpy(T2_settting.settings.ulGatewayIP,    g_Gateway_ip.p_addr,        g_Gateway_ip.size);
                memcpy(T2_settting.settings.ulSubnetMask,   g_SubnetMask_ip.p_addr,     g_SubnetMask_ip.size);

                memcpy(T2_settting.settings.username, g_user_name_pwd, 6);
                memcpy(T2_settting.settings.password, g_user_name_pwd, 6);
                memcpy(T2_settting.settings.ucModName, g_module_name, sizeof(g_module_name));

                T2_settting.settings.uiId[0] = 0x01;
                T2_settting.settings.ucIDType_bits.bit4_Reset = 0x01;
                T2_settting.settings.ucIDType_bits.bit5_LinkState = 0x01;
                //T2_settting.settings.ucIDType_bits.bit6_IndexFucntion = 0x01;
                // T2_settting.settings.ucIDType_bits.bit0_SendID_Conn = 0x01;

                //T2_settting.settings.usHTTPServerPort[0] = 0x2E;
                //T2_settting.settings.usHTTPServerPort[1] = 0x16;

                memcpy(T2_settting.settings.mac_addrs, g_mac_addr, 6);
                
                T2_settting.checkbit = R_USR_TCP232_Calculate_Checkbit(
                                (uint8_t *)&T2_settting.settings,
                                sizeof(tcp232_basic_setting_t)
                                );
            }

            g_buffer_byte_count = 0;
            g_buffer_byte_total = 2;
            g_config_write_confirm_received = FALSE;
            
            g_usr_module_step = USR_MODULE_STEP_SEND_ETHERNET_CONFIG;
            
            /* Set configure */
            R_WRP_SendBuffer(
                (uint8_t *)&T2_settting, 
                sizeof(tcp232_basic_cfg_frame_t)
            );
            
            R_USRTCP232_WaitConfirmResponse();

            R_USRTCP232_RESTART();
        }

        R_USRTCP232_ReadCnf();

        if (g_tcp_module_operating_mode == USR_TCP232_TCP_CLIENT)
        {
            R_USRTCP232_SetMode(
                USR_TCP232_TCP_SERVER, 
                p_config->local_ip_address, 
                p_config->local_tcp_port
            );
        }

        R_USRTCP232_SwitchToTransferMode();
	}
    return TRUE;
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
*               : IpAddressPtr remote_ip_address: Remote station IP address, use TCP_IP_ADDRESS_SIZE to get length
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_ConnectRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address)
{
	uint8_t retry_count;
    if ( tcp_channel == 0 )
    {
        if (g_tcp_active_connect == TRUE)
        {
			//for (retry_count = 0; retry_count < 2; retry_count++)
			{
            	R_USRTCP232_ReadCnf();

	            if (g_tcp_module_operating_mode == USR_TCP232_TCP_SERVER)
	            {
	                R_USRTCP232_SetMode(
	                    USR_TCP232_TCP_CLIENT, 
	                    remote_ip_address, 
	                    remote_tcp_port
	                );
	            }
				else
				{
					// break;
				}
			}
			R_USRTCP232_SwitchToTransferMode();
        }
    }
    return TRUE;
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
*               : IpAddressPtr remote_ip_address: Remote station IP address, use TCP_IP_ADDRESS_SIZE to get length
*               : uint8_t result                : Connection req from remote station is accepted (TRUE) or reject (FALSE)
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_ConnectResponse(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t result)
{
	/* TODO: Dummy to get library run */
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
*               : IpAddressPtr remote_ip_address: Remote station IP address, use TCP_IP_ADDRESS_SIZE to get length
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DisconnectRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address)
{
    if ( tcp_channel == 0 )
    {
        if (g_tcp_active_connect == TRUE)
        {
            R_USRTCP232_ReadCnf();

            if (g_tcp_module_operating_mode == USR_TCP232_TCP_CLIENT)
            {
                R_USRTCP232_SetMode(
                    USR_TCP232_TCP_SERVER,
                    remote_ip_address,
                    remote_tcp_port
                );
            }
            R_USRTCP232_SwitchToTransferMode();
        }
    }
    return TRUE;
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
*               : IpAddressPtr remote_ip_address: Remote station IP address, use TCP_IP_ADDRESS_SIZE to get length
*               : uint8_t result                : Disconnection req from remote station is accepted (TRUE) or reject (FALSE)
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DisconnectResponse(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t result)
{
	/* TODO: Dummy to get library run */
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
*               : IpAddressPtr remote_ip_address: Remote station IP address, use TCP_IP_ADDRESS_SIZE to get length
*               : uint8_t * data                : Input data buffer pointer
*               : uint16_t length               : Input data length
* Function Calls: 
* Return Value  : uint8_t, Success (TRUE) or fail (FALSE)
******************************************************************************/
uint8_t R_TCP_DEVICE_DataRequest(TcpChannel tcp_channel, TcpPort remote_tcp_port, IpAddressPtr remote_ip_address, uint8_t *data, uint16_t length)
{
    if (tcp_channel == 0) {
		if (g_usr_tcp232_mode == USR_TCP233_TRANSFER)
		{
			R_WRP_SendBuffer(data, length);
		}
        else
        {
            R_USRTCP232_SwitchToTransferMode();
            R_WRP_SendBuffer(data, length);
        }
    }

	return TRUE;
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
  * This function shall be called once there is an  interruption happen between this device and remote station
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
    static tcp232_read_config_t *p_config_read;
    if (g_usr_tcp232_mode == USR_TCP233_CONFIGURE)
    {
		if (g_buffer_byte_count < MAX_TCP_BUFFER_SIZE)
        {
			g_tcp_usr_config_confirm_buffer[g_buffer_byte_count++] = received_byte;
		}
		else
		{
			/* Fatal error: Please check buffer size! */
			g_buffer_byte_count++;
		}
		if (g_buffer_byte_count >= 2 )
		{
			if ((g_tcp_usr_config_confirm_buffer[g_buffer_byte_count-2] == 0x55) &&
		        (g_tcp_usr_config_confirm_buffer[g_buffer_byte_count-1] == 0xBD))
				{
					 p_config_read = (tcp232_read_config_t *)&g_tcp_usr_config_confirm_buffer[g_buffer_byte_count];
				}
		}
        if (g_buffer_byte_count >= g_buffer_byte_total)
        {
            g_config_write_confirm_received = TRUE;

            switch (g_usr_module_step)
            {
                case USR_MODULE_STEP_SWITCH_TO_CONFIG_MODE:
                    if (g_tcp_usr_config_confirm_buffer[0] == 'U')
                    {
                        g_usr_module_response = USR_MODULE_RESPONSE_OK;
                    }
                    else
                    {
                        g_usr_module_response = USR_MODULE_RESPONSE_ERROR;
                    }
                    break;
                case USR_MODULE_STEP_SEND_SERIALPORT_CONFIG:
                    if ((g_tcp_usr_config_confirm_buffer[0] == 0xBE) &&
                       (g_tcp_usr_config_confirm_buffer[1] == 0x4B))
                    {
                        g_usr_module_response = USR_MODULE_RESPONSE_OK;
                    }
                    else
                    {
                        g_usr_module_response = USR_MODULE_RESPONSE_ERROR;
                    }
					break;
            }

            // g_buffer_byte_count = 0;
        }
		if (g_buffer_byte_count >= 137)
		{
            g_tcp_module_operating_mode = p_config_read->ucWorkMode;
			NOP();
		}
    }
    else
    {
        R_USRTCP232_CheckConnectionState();
        R_TCP_DEVICE_DataIndication(
            0,                                      		/* TCP Channel */
            TCP_WRP_RAW_DLMS_PORT,                  		/* TCP Port */
            (IpAddressPtr)&g_tcp_module_remote_address,     /* Remote IP Address */
            &received_byte,                         		/* RX Buffer */
            1                                       		/* RX Buffer Length */
        );
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
    if (channel == 0)
    {
        R_TCP_DEVICE_DataConfirm(
            0,
            TRUE
        );
        g_wrp_send_end = TRUE;
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
    if (g_tcp_client_conn_timeout.enable == TRUE) {
		if (g_tcp_client_conn_timeout.count > 0) {
			g_tcp_client_conn_timeout.count--;
		}
		else {
			R_USRTCP232_ClientMode_Timeout_Callback();
			g_tcp_client_conn_timeout.enable = FALSE;
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
    /* TODO: Add implementation to check if meter connected to network */
    return TRUE;
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
    volatile uint32_t count;
    
    /* Waiting if there's any disconnect signal coming */
	count = 50;
	while(R_TCP_GetConnectionState(0) == TCP_CONNECTED)
	{
        R_USRTCP232_CheckConnectionState();

		MCU_Delay(10000);
        R_WDT_Restart();
        count--;
        if (count == 0)
        {
			NOP();
            break;
        }
	}

    if (R_TCP_GetConnectionState(0) == TCP_DISCONNECTED)
    {
		g_tcp_active_connect = TRUE;
        R_TCP_Connect(
            0,
            remote_port,
            remote_ip_address
        );
        /* Wait until connection establish with timeout */
		count = 100;
		while (g_tcp_active_connect_state == TCP_ACTIVE_DISCONNECTED)
		{
           	R_USRTCP232_CheckConnectionState();
			
			MCU_Delay(10000);
			R_WDT_Restart();
			
			count--;
			if (count == 0)
			{
				break;
			}
		}
    }
    
    return (R_TCP_GetConnectionState(0));
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
    volatile uint32_t count;
	
    if (R_TCP_GetConnectionState(0) == TCP_CONNECTED)
    {

    }
    
    return (R_TCP_GetConnectionState(0));
}

#endif /* #if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == FALSE) */