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
* File Name    : r_meter_cmd.c
* Version      : 1.00
* Device(s)    : 
* Tool-Chain   : 
* H/W Platform : 
* Description  : Meter CMD: general processing function
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "typedef.h"                /* GSCE Standard Typedef */
#include "r_cg_macrodriver.h"       /* Macro Driver Definitions */
#include "r_cg_wdt.h"               /* WDT Driver */
#include "r_cg_sau.h"
#include "r_cg_tau.h"
/* Standard library */
#include <stdlib.h>
#include <string.h>         /* String Standard Lib */
/* Wrapper */
#include "wrp_app_uart.h"          /* Wrapper UART Layer */
#include "storage.h"        /* Storage Header File */
/* Application */
#include "r_meter_cmd.h"            /* CMD Prompt Middleware Layer */
#include "r_meter_cmd_share.h"      /* CMD Prompt Middleware Layer */
//#include "r_aes_hwip.h"
#include "eeprom.h"             /* EEPROM MW Layer */
#if (defined METER_ENABLE_PROPRIETARY_METER_COMMAND) && (METER_ENABLE_PROPRIETARY_METER_COMMAND == TRUE)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum tagReceiveState
{
    WAITING_FIRST_CHAR,
    WAITING_FRAME_TYPE,
    WAITING_LENGTH,
    WAITING_BUFFER,
    WAITING_END_CHAR,
    PROCESSING_PACKAGE,
} MeterCmdReceiveState_t;

typedef enum tagMeterCmdAuthenticationStatus
{
    METER_CMD_AUTHENTICATION_PASSED = 1,
    METER_CMD_AUTHENTICATION_FAILED = 2,
} MeterCmdAuthenticationStatus_t;

typedef struct tagMeterCmdInfo
{
    uint8_t is_unlock;
    uint8_t encrypt_key_length;
    uint8_t * p_encrypt_key;

    struct tagMeterCmdInforReceiver
    {
        MeterCmdReceiveState_t state;
        MeterCmdFrameType_t frame_type;
        uint8_t port;
        uint8_t buffer_length;
        uint8_t buffer_pos;
        uint8_t * p_buffer;
    } receiver;

    struct tagMeterCmdInfoSender 
    {
        uint8_t is_sent;
    } sender;

} MeterCmdInfo;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define METER_CMD_FIRST_BYTE                                (0x02)
#define METER_CMD_FINAL_BYTE                                (0x03)

#define R_METER_CMD_PUT_BYTE_TO_RECV_BUFFER(byte) {\
    g_meter_cmd_info.receiver.p_buffer[g_meter_cmd_info.receiver.buffer_pos++] = byte;\
}

#define METER_CMD_ENCODE_FRAME_HEADER(buffer, frame_type)          {\
    *(buffer + 0) = METER_CMD_FIRST_BYTE;   \
    *(buffer + 1) = frame_type;    \
}

#define METER_CMD_ENCODE_FRAME_LENGTH(buffer, length)   {\
    *(buffer + 2) = length + METER_CMD_COMMAND_CODE_SIZE + METER_CMD_RESP_FRAME_RET_SIZE + METER_CMD_MESSAGE_LENGTH_SIZE + METER_CMD_CRC_SIZE; \
}

#define METER_CMD_ENCODE_FRAME_COMMAND_CODE(buffer, command)  {\
    *(buffer + 3) = command;\
}

#define METER_CMD_ENCODE_FRAME_RET_CODE(buffer, ret)  {\
    *(buffer + 4) = ret; \
}

#define METER_CMD_ENCODE_FRAME_CRC(buffer, send_size, crc) {\
    buffer[send_size - 3]  = *((uint8_t *)&crc + 1);    \
    buffer[send_size - 2]  = *((uint8_t *)&crc + 0);    \
}

#define METER_CMD_ENCODE_FRAME_FOOTER(buffer, send_size)     {\
    buffer[send_size - 1]  = METER_CMD_FINAL_BYTE;              \
}

#define METER_CMD_ENCODE_FRAME_COMMAND_CODE(buffer, command) {\
    *(buffer + 3) = command;\
}

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
static const uint8_t g_meter_cmd_enc_key[16] = R_METER_CMD_AUTHENTICATION_KEY;
static MeterCmdInfo g_meter_cmd_info;
uint8_t g_meter_cmd_receive_buffer[256];

 extern uint8_t g_uart2_rx_buff[256]; 
extern volatile uint8_t UART2_Ideal_Timer;
extern uint16_t rx;
uint8_t eeprom_buff[256];
/***********************************************************************************************************************
* Function Name: r_meter_cmd_decrypt
* Description  : Wrapper for the AES decryption which used to decrypt the authentication
* Arguments    : uint8_t * in_buffer
*              : uint8_t * out_buffer
*              : uint8_t * key
*              : uint16_t num_of_block
* Return Value : None
***********************************************************************************************************************/
//static void r_meter_cmd_decrypt(uint8_t * in_buffer, uint8_t * out_buffer, uint8_t * key, uint16_t num_of_block)
//{
//    R_Aes_Init();

//    R_Aes_128_Ecbdec(in_buffer, out_buffer, key, num_of_block);

//    R_Aes_Close();
//}

/***********************************************************************************************************************
* Function Name: r_meter_cmd_calculate_crc
* Description  : Calculate the CRC for meter command communication
* Arguments    : uint8_t * buffer
*              : uint8_t size
* Return Value : uint16_t: crc calculated value for the block
***********************************************************************************************************************/
static uint16_t r_meter_cmd_calculate_crc(const uint8_t * buffer, uint8_t size)
{
    /* Must backup the CRCD because it maybe using in other application */
    uint16_t backup_CRCD = CRCD;
    uint16_t result;

    CRCD = 0xFFFF;
    
    while (size)
    {
        CRCIN = *buffer++;
        size--;
    }

    result = CRCD ^ 0xFFFF;

    /* Restore value of CRCD for other application */
    CRCD = backup_CRCD;

    return result;
}

/***********************************************************************************************************************
* Function Name: r_meter_cmd_send_buffer
* Description  : Wrapper to send data through uart
* Arguments    : uint8_t * reply_buffer
*              : uint16_t length
* Return Value : None
***********************************************************************************************************************/
static void r_meter_cmd_send_buffer(uint8_t * reply_buffer, uint16_t length)
{
    /* Send the reply message */
    if (g_meter_cmd_info.receiver.port == 0) {
        WRP_UART_SendData(reply_buffer, length);
    }
    else {
        WRP_UART0_SendData(reply_buffer, length);
    }

    /* Wait until finish sending */
    g_meter_cmd_info.sender.is_sent = FALSE;
    while (g_meter_cmd_info.sender.is_sent == FALSE)
    {
        R_WDT_Restart();
    }
}

/***********************************************************************************************************************
* Function Name: r_meter_cmd_pack_frame
* Description  : Fill frame information after data buffer encoded by sub modules
* Arguments    : MeterCmdFrameInfo * p_frame_info
* Return Value : None
***********************************************************************************************************************/
void r_meter_cmd_pack_frame(MeterCmdFrameInfo * p_frame_info)
{
    /* Calculate send size */
    p_frame_info->raw_buffer.size = METER_CMD_HEADER_SIZE + 
        p_frame_info->data_buffer.length + 
        METER_CMD_FOOTER_SIZE;
    
    if (p_frame_info->frame_type == FRAME_TYPE_RESPONSE) {
        p_frame_info->raw_buffer.size += METER_CMD_LENGTH_RES_FRAME_MIN_SIZE;
    }
    else if (p_frame_info->frame_type == FRAME_TYPE_REQUEST) {
        p_frame_info->raw_buffer.size += METER_CMD_LENGTH_REQ_FRAME_MIN_SIZE;
    }
    else {
        p_frame_info->raw_buffer.size += METER_CMD_LENGTH_REQ_FRAME_MIN_SIZE;
    }

    /* Add the header */
    METER_CMD_ENCODE_FRAME_HEADER(p_frame_info->raw_buffer.data, p_frame_info->frame_type);

    /* Add length */
    METER_CMD_ENCODE_FRAME_LENGTH(p_frame_info->raw_buffer.data, p_frame_info->data_buffer.length);

    /* Add command code and ret code */
    METER_CMD_ENCODE_FRAME_COMMAND_CODE(p_frame_info->raw_buffer.data, p_frame_info->code);
    if (p_frame_info->frame_type == FRAME_TYPE_RESPONSE) {
        METER_CMD_ENCODE_FRAME_RET_CODE(p_frame_info->raw_buffer.data, p_frame_info->ret);
    }

    /* Calculate message CRC */
    p_frame_info->crc = r_meter_cmd_calculate_crc(
        p_frame_info->raw_buffer.data + METER_CMD_FIRST_CODE_SIZE,
        p_frame_info->raw_buffer.size - (METER_CMD_FIRST_CODE_SIZE + METER_CMD_CRC_SIZE + METER_CMD_FINAL_CODE_SIZE)
    );

    /* Add crc */
    METER_CMD_ENCODE_FRAME_CRC(p_frame_info->raw_buffer.data, p_frame_info->raw_buffer.size, p_frame_info->crc);

    /* Add the footer */
    METER_CMD_ENCODE_FRAME_FOOTER(p_frame_info->raw_buffer.data, p_frame_info->raw_buffer.size);
}

/***********************************************************************************************************************
* Function Name: r_meter_cmd_check_frame_crc
* Description  : Calculate the frame CRC and compare with embedded CRC in frame
* Arguments    : MeterCmdFrameInfo * p_frame_info
* Return Value : uint8_t
***********************************************************************************************************************/
static uint8_t r_meter_cmd_check_frame_crc(const MeterCmdFrameInfo * p_frame_info)
{
    uint16_t crc;
    uint16_t embedded_crc;

    crc = r_meter_cmd_calculate_crc(
        p_frame_info->raw_buffer.data + METER_CMD_FIRST_CODE_SIZE,
        p_frame_info->raw_buffer.size - (METER_CMD_FIRST_CODE_SIZE + METER_CMD_FINAL_CODE_SIZE + METER_CMD_CRC_SIZE)
    );
    embedded_crc = p_frame_info->crc;

    if (memcmp(&crc, &embedded_crc, sizeof(crc)) == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/***********************************************************************************************************************
* Function Name: r_meter_cmd_process_authentication
* Description  : Authenticate and decide to unlock the application or not
* Arguments    : MeterCmdDataBuffer * p_req_buffer
*              : MeterCmdFrameInfo * p_frame_info
* Return Value : uint8_t
***********************************************************************************************************************/
static uint8_t r_meter_cmd_process_authentication(MeterCmdDataBuffer * p_req_buffer, MeterCmdFrameInfo * p_frame_info)
{
    uint8_t i, count, at_pos, dot_pos[2];
    uint8_t * p_dec_buffer;
    MeterCmdAuthenticationStatus_t authentication_status;

    /* This is the only command that need encryption
    * To read the content, need to decrypt first using AES-128 in ECB mode
    * So the length must be multiple of 16 bytes (128bits)
    */
    if ((p_req_buffer->length % 16) != 0) {
        /* Expected length incorrect */
        R_METER_CMD_PackAndSendErrorCode(p_frame_info, METER_CMD_ERROR_INCORRECT_ARGUMENT_LENGTH);
        return 0;
    }

    /* Start decrypting the content, re-use the send buffer for decrypting buffer */
    p_dec_buffer = p_frame_info->raw_buffer.data;
//    r_meter_cmd_decrypt(p_req_buffer->data, p_dec_buffer, g_meter_cmd_info.p_encrypt_key, p_req_buffer->length / 16);

    /* Mark frame as success */
    p_frame_info->ret = METER_CMD_OK;

//    /* Mark validation default failed */
//    g_meter_cmd_info.is_unlock = FALSE;
//    authentication_status = METER_CMD_AUTHENTICATION_FAILED;

//    /* Validation method: check for valid renesas group email
//    * 1: one '@' character
//    * 2: two '.' character before '@'
//    * 3: two characters between the last '.' before '@' and '@'
//    * 4: no less than 1 character between '.'
//    * 5: domain must be renesas.com
//    */
//    count = 0;
//    for (i = 0; i < p_req_buffer->length; i++)
//    {
//        if (p_dec_buffer[i] == '@') {
//            count++;
//            /* There's more than 1 '@' char? */
//            if (count > 1) {
//                goto METER_CMD_AUTHENTICATION_FINAL;
//            }
//            at_pos = i;
//            break;
//        }
//    }

//    /* Cannot find '@' char? */
//    if (count < 1) {
//        goto METER_CMD_AUTHENTICATION_FINAL;
//    }

//    count = 0;
//    for (i = 0; i < at_pos; i++)
//    {
//        if (p_dec_buffer[i] == '.')
//        {
//            count++;
//            /* There's more than 2 '.' char before '@'? */
//            if (count > 2) {
//                goto METER_CMD_AUTHENTICATION_FINAL;
//            }
//            dot_pos[count - 1] = i;
//        }
//    }

//    /* Not enough 2 '.' char? */
//    if (count < 2) {
//        goto METER_CMD_AUTHENTICATION_FINAL;
//    }

//    /* Less than 2 char between the last '.' before '@' and '@' ? */
//    if ((at_pos - dot_pos[1] - 1) != 2) {
//        goto METER_CMD_AUTHENTICATION_FINAL;
//    }

//    /* Less then 2 char between each '.' before '@' ? */
//    if (((dot_pos[0] - 0 - 1) < 2) ||
//        ((dot_pos[1] - dot_pos[0] - 1) < 2))
//    {
//        goto METER_CMD_AUTHENTICATION_FINAL;
//    }

//    /* Invalid domain? */
//    if (memcmp(&p_dec_buffer[at_pos + 1], (uint8_t *)"renesas.com", 11) != 0) {
//        goto METER_CMD_AUTHENTICATION_FINAL;
//    }

    g_meter_cmd_info.is_unlock = TRUE;
    authentication_status = METER_CMD_AUTHENTICATION_PASSED;

METER_CMD_AUTHENTICATION_FINAL:
    R_METER_CMD_EncodeUInt8ToBuffer(&p_frame_info->data_buffer, (uint8_t)authentication_status);
    R_METER_CMD_PackAndSendResFrame(p_frame_info);
    return 0;
}

/***********************************************************************************************************************
* Function Name: r_meter_cmd_process_command
* Description  : Parse received frame and call to corresponding sub modules
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_meter_cmd_process_command(void)
{
    MeterCmdCode_t cmd;
    uint8_t raw_buffer[METER_CMD_SEND_BUFFER_MAX_SIZE];
    uint8_t * p_encode, *p_send_buffer;
    uint8_t data_length;
    MeterCmdFrameInfo req_info;
    MeterCmdFrameInfo res_info;

    /* Decode receive buffer */
    METER_CMD_GET_REQ_FRAME_INFO(
        g_meter_cmd_info.receiver.p_buffer,
        g_meter_cmd_info.receiver.buffer_length,
        g_meter_cmd_info.receiver.frame_type,
        req_info
    );

    /* Check overall frame content correctness */
    if (r_meter_cmd_check_frame_crc(&req_info) != TRUE) {
        return;
    }

    /* Pass the command code to send frame info */
    METER_CMD_INITIATE_RES_FRAME_INFO(req_info, raw_buffer, res_info);

    /* Check authentication status */
    if ((g_meter_cmd_info.is_unlock == FALSE) && (req_info.code != METER_CMD_CODE_AUTHENTICATION))
    {
        R_METER_CMD_PackAndSendErrorCode(&res_info, METER_CMD_ERROR_APPLICATION_LOCKED);
        return;
    }

    if (g_meter_cmd_info.receiver.frame_type != FRAME_TYPE_REQUEST) {
        R_METER_CMD_PackAndSendErrorCode(&res_info, METER_CMD_ERROR_UNEXPECTED_FRAME_TYPE);
        return;
    }

    /* Call to separate command processor and get the reply buffer */
    switch (req_info.code)
    {
        case METER_CMD_CODE_AUTHENTICATION:
            /* Note: internal command */
            r_meter_cmd_process_authentication(&req_info.data_buffer, &res_info);
            break;
        #if (defined SUPPORT_COMMAND_CALIBRATION) && (SUPPORT_COMMAND_CALIBRATION == TRUE)
        case METER_CMD_CODE_CALIBRATION:
            R_METER_CMD_ProcessCmdCalibration(&req_info.data_buffer, &res_info);
            break;
        #endif
        #if (defined SUPPORT_COMMAND_MEMORY_FORMAT) && (SUPPORT_COMMAND_MEMORY_FORMAT == TRUE)
        case METER_CMD_CODE_MEMORY_FORMAT:
            R_METER_CMD_ProcessCmdMemoryFormat(&req_info.data_buffer, &res_info);
            break;
        #endif
        #if (defined SUPPORT_COMMAND_SIGNAL_LOGGING) && (SUPPORT_COMMAND_SIGNAL_LOGGING == TRUE)
        case METER_CMD_CODE_SIGLOG:
            R_METER_CMD_ProcessCmdSigLog(&req_info.data_buffer, &res_info);
            break;
        #endif
        #if (defined SUPPORT_COMMAND_ONCHIP_MEMORY_ACCESS) && (SUPPORT_COMMAND_ONCHIP_MEMORY_ACCESS == TRUE)
        case METER_CMD_CODE_OCMEM_ACCESS:
            R_METER_CMD_ProcessCmdOcMemAccess(&req_info.data_buffer, &res_info);
            break;
        #endif
        #if (defined SUPPORT_COMMAND_PLATFORM_ACCESS) && (SUPPORT_COMMAND_PLATFORM_ACCESS == TRUE)
        case METER_CMD_CODE_PLATFORM_ACCESS:
            METER_CMD_ProcessCmdPlatformAccess(&req_info.data_buffer, &res_info);
            break;
        #endif
        default:
            /* Unsupported command */
            R_METER_CMD_PackAndSendErrorCode(&res_info, METER_CMD_ERROR_UNSUPPORTED_COMMAND_CODE);
            break;
    }
}

/***********************************************************************************************************************
* Function Name: R_METER_CMD_PackAndSendResFrame
* Description  : Fill frame information after data buffer encoded by sub modules and send back received UART port
* Arguments    : MeterCmdFrameInfo * p_frame_info
* Return Value : None
***********************************************************************************************************************/
void R_METER_CMD_PackAndSendResFrame(MeterCmdFrameInfo * p_frame_info)
{
     r_meter_cmd_pack_frame(p_frame_info);
     
     r_meter_cmd_send_buffer(
         p_frame_info->raw_buffer.data,
         p_frame_info->raw_buffer.size
     );

     METER_CMD_RESET_DATA_BUFFER(p_frame_info->data_buffer);
}

/***********************************************************************************************************************
* Function Name: R_METER_CMD_PackAndSendErrorCode
* Description  : Make a error coded frame and send back (ignore data if any)
* Arguments    : MeterCmdFrameInfo * p_frame_info
*              : MeterCmdRet_t ret
* Return Value : None
***********************************************************************************************************************/
void R_METER_CMD_PackAndSendErrorCode(MeterCmdFrameInfo * p_frame_info, MeterCmdRet_t ret)
{
     p_frame_info->ret = ret;
     p_frame_info->data_buffer.length = 0;
     R_METER_CMD_PackAndSendResFrame(p_frame_info);
}

/***********************************************************************************************************************
* Function Name: R_METER_CMD_Init
* Description  : Initialize the meter command application
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_METER_CMD_Init(void)
{
    memset(&g_meter_cmd_info, 0, sizeof(g_meter_cmd_info));

    /* Add variable initialization after clear all to 0 */
    g_meter_cmd_info.p_encrypt_key = (uint8_t *)g_meter_cmd_enc_key;
    g_meter_cmd_info.encrypt_key_length = 16;
}

/***********************************************************************************************************************
* Function Name: R_METER_CMD_PollingProcessing
* Description  : Polling processing for meter command application
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_METER_CMD_PollingProcessing(void)
{
    if (g_meter_cmd_info.receiver.state == PROCESSING_PACKAGE)
    {
        /* Buffer valid for access? */
        if (g_meter_cmd_info.receiver.p_buffer != NULL)
        {
            r_meter_cmd_process_command();
        }

        /* Reset communication state */
        g_meter_cmd_info.receiver.state = WAITING_FIRST_CHAR;
    }
}

/***********************************************************************************************************************
* Function Name: R_METER_CMD_UART_SendEndCallback
* Description  : UART send end call back for meter command application
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_METER_CMD_UART_SendEndCallback(void)
{
    g_meter_cmd_info.sender.is_sent = TRUE;
}

/***********************************************************************************************************************
* Function Name: R_METER_CMD_UART_ReceiveEndCallback
* Description  : UART receive end call back for meter command application
* Arguments    : uint8_t receive_port
*              : uint8_t received_byte
* Return Value : None
***********************************************************************************************************************/
void R_METER_CMD_UART_ReceiveEndCallback(uint8_t receive_port, uint8_t received_byte)
{
    if (g_meter_cmd_info.receiver.state == PROCESSING_PACKAGE) {
        return;   
    }
    
    switch (g_meter_cmd_info.receiver.state)
    {
        case WAITING_FIRST_CHAR:
            if (received_byte == METER_CMD_FIRST_BYTE) {
                g_meter_cmd_info.receiver.state = WAITING_FRAME_TYPE;
            }
            break;
        case WAITING_FRAME_TYPE:
            g_meter_cmd_info.receiver.frame_type = (MeterCmdFrameType_t)received_byte;
            if (g_meter_cmd_info.receiver.frame_type == FRAME_TYPE_REQUEST ||
                g_meter_cmd_info.receiver.frame_type == FRAME_TYPE_RESPONSE ||
                g_meter_cmd_info.receiver.frame_type == FRAME_TYPE_NOTIFICATION)
            {
                g_meter_cmd_info.receiver.state = WAITING_LENGTH;
            } 
            else {
                g_meter_cmd_info.receiver.state = WAITING_FIRST_CHAR;
            }
            break;
        case WAITING_LENGTH:
            g_meter_cmd_info.receiver.buffer_pos = 0;

            /* Open the data reply_buffer: frame_type || data length || data || CRC || */
            g_meter_cmd_info.receiver.buffer_length = METER_CMD_HEADER_FOOTER_SIZE + received_byte;
            g_meter_cmd_info.receiver.p_buffer = g_meter_cmd_receive_buffer;

            /* Cannot open reply_buffer, terminate communication since there's no reply_buffer for further processing */
            if (g_meter_cmd_info.receiver.p_buffer != NULL) {
                R_METER_CMD_PUT_BYTE_TO_RECV_BUFFER(METER_CMD_FIRST_BYTE)
                R_METER_CMD_PUT_BYTE_TO_RECV_BUFFER(g_meter_cmd_info.receiver.frame_type);
                R_METER_CMD_PUT_BYTE_TO_RECV_BUFFER(received_byte);
                g_meter_cmd_info.receiver.state = WAITING_BUFFER;
            }
            else {
                g_meter_cmd_info.receiver.state = WAITING_FIRST_CHAR;
            }
            break;
        case WAITING_BUFFER:
            R_METER_CMD_PUT_BYTE_TO_RECV_BUFFER(received_byte);
            /* Check for received length, include 1 extra byte of frame frame_type */
            if (g_meter_cmd_info.receiver.buffer_pos >= (g_meter_cmd_info.receiver.buffer_length - 1)) {
                g_meter_cmd_info.receiver.state = WAITING_END_CHAR;
            }
            break;
        case WAITING_END_CHAR:
            if (received_byte == METER_CMD_FINAL_BYTE) {
                R_METER_CMD_PUT_BYTE_TO_RECV_BUFFER(METER_CMD_FINAL_BYTE);
                g_meter_cmd_info.receiver.state = PROCESSING_PACKAGE;
                g_meter_cmd_info.receiver.port = receive_port;
            }
            else {
                g_meter_cmd_info.receiver.state = WAITING_FIRST_CHAR;
            }
            break;
        default:
            g_meter_cmd_info.receiver.state = WAITING_FIRST_CHAR;
            break;
    }
}

void EEPROM_commands_PollingProcessing(void) {
    if ((rx > 0) && (UART2_Ideal_Timer > 50)) {
        uint32_t address = ((uint32_t)g_uart2_rx_buff[2] << 16) |
                           ((uint32_t)g_uart2_rx_buff[3] << 8) |
                           (uint32_t)g_uart2_rx_buff[4];
        uint16_t length = (g_uart2_rx_buff[5] << 8) | g_uart2_rx_buff[6];
        uint16_t W_length = g_uart2_rx_buff[5];
        uint8_t command = g_uart2_rx_buff[1];
        uint8_t Reply[2] = {0x03, command};
        uint8_t days = g_uart2_rx_buff[2];

        if (g_uart2_rx_buff[0] == 0x03) {
            switch (command) {
                case 0xAA:  // EEPROM Erase Command
                    P6_bit.no2 = 0;
                    EEPROM_Erase(address, length);
                    R_UART2_Send(Reply, 2);
                    P6_bit.no2 = 1;
                    break;

                case 0xBB:  // EEPROM Write Command
                    memcpy(eeprom_buff, &g_uart2_rx_buff[6], W_length);  // Use memcpy for better performance
                    P6_bit.no2 = 0;
                    EPR_Write(address, eeprom_buff, W_length);
                    R_UART2_Send(Reply, 2);
                    P6_bit.no2 = 1;
                    memset(eeprom_buff, 0, sizeof(eeprom_buff));  // Efficient memory clearing
                    break;

                case 0xCC:  // EEPROM Read Command
                    EPR_Read(address, eeprom_buff, length);
                    R_UART2_Send(eeprom_buff, length);
                    break;
                default:
                    // Handle unrecognized commands, potentially return an error code
                    break;
            }
        }else if (g_uart2_rx_buff[0] == 0x02) { 
            switch (g_uart2_rx_buff[1]) 
	    {
	  case 0xA2: //Reset Flash/ EEPROM Erase
		{
                    uint8_t Reply[1] = {0xA2};
                    EEPROM_Erase_All();
		    MCU_Delay(10000);
                    R_UART2_Send(Reply, 1);
                    R_WDT_Restart();

                    MCU_Delay(50000);
                   memset(g_uart2_rx_buff, 0, 5); 
                    rx = 0;
                    break;
                }
		default:  // Unrecognized command 
                break;
	    }
	}

        // Reset the UART buffer and control variables
        memset(g_uart2_rx_buff, 0, sizeof(g_uart2_rx_buff));  // Clear the entire buffer
        rx = 0;
        UART2_Ideal_Timer = 0;
    }
}


#endif /* #if (defined METER_ENABLE_PROPRIETARY_METER_COMMAND) && (METER_ENABLE_PROPRIETARY_METER_COMMAND == TRUE) */
