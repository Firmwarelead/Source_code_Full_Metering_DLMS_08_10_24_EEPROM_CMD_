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
* File Name    : r_meter_cmd_siglog.c
* Version      : 1.00
* Device(s)    : 
* Tool-Chain   : 
* H/W Platform : 
* Description  : Meter CMD - Signal logging 
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"   /* Macro Driver Definitions */
#include "r_cg_dsadc.h"         /* DSADC Driver */
#include "r_cg_sau.h"
#include "r_cg_wdt.h"           /* WDT Driver */

#include "typedef.h"            /* GSCE Standard Typedef */

#include <stdlib.h>
#include <string.h>

/* Middleware */
#include "em_core.h"

/* Wrapper */
#include "wrp_app_mcu.h"
#include "wrp_em_sw_config.h"

/* Application */
#include "r_meter_cmd.h"
#include "r_meter_cmd_share.h"

#if (defined METER_ENABLE_PROPRIETARY_METER_COMMAND) && (METER_ENABLE_PROPRIETARY_METER_COMMAND == TRUE)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Information used for communication only */
#define EXPECTED_SIGLOG_ARGS_LENGTH                 (   sizeof(uint16_t) +\
                                                        sizeof(uint16_t) \
)

#define METER_CMD_SIGLOG_RET_OK                         (0x01)
#define METER_CMD_SIGLOG_ERROR_MAX_SIGNALS              (0x02)
#define METER_CMD_SIGLOG_ERROR_INVALID_SIGNALS          (0x03)
#define METER_CMD_SIGLOG_ERROR_ZERO_ARGUMENTS           (0x04)

#define ELEVATED_UART_BAUD_RATE                         (1500000)

#if (METER_CMD_SIGLOG_SUPPORTED_NUM_OF_SIGNALS > 9)
#error "Invalid supported number of signals, the current elevated baudrate support 9 channel only
#endif

#define METER_CMD_SIGLOG_UART_mn_TX_CH0                 00
#define METER_CMD_SIGLOG_UART_mn_TX_CH1                 02
#define METER_CMD_SIGLOG_UART_mn_TX_CH2                 10
#define METER_CMD_SIGLOG_UART_mn_TX_CH3                 12

#define METER_CMD_SIGLOG_UART_m_CH0                     0
#define METER_CMD_SIGLOG_UART_m_CH1                     0
#define METER_CMD_SIGLOG_UART_m_CH2                     1
#define METER_CMD_SIGLOG_UART_m_CH3                     1

#define METER_CMD_SIGLOG_UART_SEND(byte)                {\
    JOIN(TXD, METER_CMD_SIGLOG_UART_CHANNEL) = byte;\
}
#define METER_CMD_SIGLOG_WAIT_UNTIL_SENT()              {\
    while(JOIN(SSR, JOIN(METER_CMD_SIGLOG_UART_mn_TX_CH, METER_CMD_SIGLOG_UART_CHANNEL)) & 0x0040);\
}
#define METER_CMD_SIGLOG_UART_START()                   {\
    JOIN(JOIN(R_UART, METER_CMD_SIGLOG_UART_CHANNEL), _Start());\
}
#define METER_CMD_SIGLOG_UART_STOP()                    {\
    JOIN(JOIN(R_UART, METER_CMD_SIGLOG_UART_CHANNEL), _Stop());\
}

#define METER_CMD_SIGLOG_UART_BACKUP_BAUDRATE_SETTING(sps, sdr) {\
    (sps) = JOIN(SPS, JOIN(METER_CMD_SIGLOG_UART_m_CH, METER_CMD_SIGLOG_UART_CHANNEL));\
    (sdr) = JOIN(SDR, JOIN(METER_CMD_SIGLOG_UART_mn_TX_CH, METER_CMD_SIGLOG_UART_CHANNEL));\
}
#define METER_CMD_SIGLOG_UART_APPLY_1_5MBAUD(div) {\
    if (JOIN(SMR, JOIN(METER_CMD_SIGLOG_UART_mn_TX_CH, METER_CMD_SIGLOG_UART_CHANNEL)) & 0x8000) {                                      \
        JOIN(SPS, JOIN(METER_CMD_SIGLOG_UART_m_CH, METER_CMD_SIGLOG_UART_CHANNEL)) &= 0xFF0F;                                           \
        JOIN(SPS, JOIN(METER_CMD_SIGLOG_UART_m_CH, METER_CMD_SIGLOG_UART_CHANNEL)) |= (div << 4);   \
    }                                                                                                                                   \
    else {                                                                                                                              \
        JOIN(SPS, JOIN(METER_CMD_SIGLOG_UART_m_CH, METER_CMD_SIGLOG_UART_CHANNEL)) &= 0xFFF0;                                           \
        JOIN(SPS, JOIN(METER_CMD_SIGLOG_UART_m_CH, METER_CMD_SIGLOG_UART_CHANNEL)) |= div;          \
    }                                                                                                                                   \
    JOIN(SDR, JOIN(METER_CMD_SIGLOG_UART_mn_TX_CH, METER_CMD_SIGLOG_UART_CHANNEL)) = 0x0200;                                            \
}
#define METER_CMD_SIGLOG_UART_DISABLE_INTERRUPT() {\
    JOIN(STMK, METER_CMD_SIGLOG_UART_CHANNEL) = 1U;\
}
#define METER_CMD_SIGLOG_UART_RESTORE_BAUDRATE_SETTING(sps, sdr) {\
    JOIN(SPS, JOIN(METER_CMD_SIGLOG_UART_m_CH, METER_CMD_SIGLOG_UART_CHANNEL)) = (sps);\
    JOIN(SDR, JOIN(METER_CMD_SIGLOG_UART_mn_TX_CH, METER_CMD_SIGLOG_UART_CHANNEL)) = (sdr);\
}
/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/
/* Import from wrp_em_adc.c */
extern EM_SAMPLES g_wrp_adc_samples;
extern void (NEAR_PTR * g_wrp_adc_signal_ready_cb_and_return)(void);

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
static uint32_t s_send_count;
static uint16_t s_signal_mask;
static uint16_t s_sets_of_sample;

/***********************************************************************************************************************
* Function Name: r_meter_cmd_send_signal_uart_sync
* Description  : Send a 4 byte buffer to uart in synchronous mode
* Arguments    : uint8_t * buffer: send buffer, need to be 4 byte
* Return Value : None
***********************************************************************************************************************/
void r_meter_cmd_send_signal_uart_sync(uint8_t * buffer)
{
    /* Send 4 byte synchronously (one signal) */
    METER_CMD_SIGLOG_UART_SEND((*buffer++));
    METER_CMD_SIGLOG_WAIT_UNTIL_SENT();
    METER_CMD_SIGLOG_UART_SEND((*buffer++));
    METER_CMD_SIGLOG_WAIT_UNTIL_SENT();
    METER_CMD_SIGLOG_UART_SEND((*buffer++));
    METER_CMD_SIGLOG_WAIT_UNTIL_SENT();
    METER_CMD_SIGLOG_UART_SEND((*buffer++));
    METER_CMD_SIGLOG_WAIT_UNTIL_SENT();
}

/***********************************************************************************************************************
* Function Name: r_meter_cmd_send_samples
* Description  : Signal logging ADC Interrupt end processing to send signal over uart line
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void NEAR_PTR r_meter_cmd_send_samples(void)
{
    EM_SAMPLES * p_samples = &g_wrp_adc_samples;

    if (s_sets_of_sample == 0) {
        return;
    }
    s_sets_of_sample--;
    s_send_count++;

#if 1
    if (s_signal_mask & 0x0001) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&METER_CMD_SIGLOG_VALUE_SIGNAL1); }
    if (s_signal_mask & 0x0002) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&METER_CMD_SIGLOG_VALUE_SIGNAL2); }
    if (s_signal_mask & 0x0004) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&METER_CMD_SIGLOG_VALUE_SIGNAL3); }
    if (s_signal_mask & 0x0008) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&METER_CMD_SIGLOG_VALUE_SIGNAL4); }
    if (s_signal_mask & 0x0010) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&METER_CMD_SIGLOG_VALUE_SIGNAL5); }
    if (s_signal_mask & 0x0020) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&METER_CMD_SIGLOG_VALUE_SIGNAL6); }
    if (s_signal_mask & 0x0040) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&METER_CMD_SIGLOG_VALUE_SIGNAL7); }
    if (s_signal_mask & 0x0080) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&METER_CMD_SIGLOG_VALUE_SIGNAL8); }
    if (s_signal_mask & 0x0100) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&METER_CMD_SIGLOG_VALUE_SIGNAL9); }
#else
    /* Debug */
    if (s_signal_mask & 0x0001) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&s_send_count); }
    if (s_signal_mask & 0x0002) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&s_send_count); }
    if (s_signal_mask & 0x0004) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&s_send_count); }
    if (s_signal_mask & 0x0008) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&s_send_count); }
    if (s_signal_mask & 0x0010) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&s_send_count); }
    if (s_signal_mask & 0x0020) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&s_send_count); }
    if (s_signal_mask & 0x0040) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&s_send_count); }
    if (s_signal_mask & 0x0080) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&s_send_count); }
    if (s_signal_mask & 0x0100) { r_meter_cmd_send_signal_uart_sync((uint8_t *)&s_send_count); }
#endif
}

/***********************************************************************************************************************
* Function Name: R_METER_CMD_ProcessCmdSigLog
* Description  : Entry function to process for signal logging command
* Arguments    : MeterCmdDataBuffer * p_req_buffer
*              : MeterCmdFrameInfo * p_frame_info
* Return Value : uint8_t: 0: if ok, others: error
***********************************************************************************************************************/
uint8_t R_METER_CMD_ProcessCmdSigLog(MeterCmdDataBuffer * p_req_buffer, MeterCmdFrameInfo * p_frame_info)
{
    /* Length: args */
    /* Arguments layout
     * 1byte: number of signals to log
     * 2byte: sets of samples
    */
    uint8_t is_param_good = FALSE;
    uint16_t i, temp, selection_check;
    uint16_t signal_selection, sets_of_sample, num_of_signals, sps_divider;
    struct {
        uint16_t sps;
        uint16_t sdr;
        uint16_t tps;
    } backup_reg;

    /* Check parameter length */
    METER_CMD_CHECK_EXPECTED_LENGTH(EXPECTED_SIGLOG_ARGS_LENGTH);

    if (HOCODIV == 0) { sps_divider = 2;}
    if (HOCODIV == 1) { sps_divider = 1;}
    if (HOCODIV == 2) { sps_divider = 0;}

    /* Get calibration parameters */
    signal_selection = R_METER_CMD_DecodeBufferToUInt16(p_req_buffer);
    sets_of_sample = R_METER_CMD_DecodeBufferToUInt16(p_req_buffer);

    temp = 1;
    num_of_signals = 0;
    for (i = 0; i < 16; i++)
    {
        if (temp & signal_selection) {
            num_of_signals++;
        }
        temp <<= 1;
    }

    temp = 1;
    for (i = 0; i < (METER_CMD_SIGLOG_SUPPORTED_NUM_OF_SIGNALS - 1); i++)
    {
        temp |= (temp << 1);
    }

    p_frame_info->ret = METER_CMD_OK;
    if ((num_of_signals > METER_CMD_SIGLOG_SUPPORTED_NUM_OF_SIGNALS) ||
        ((num_of_signals > 4) && HOCODIV == 2) ||
        ((num_of_signals > 8) && HOCODIV == 1)) {
        R_METER_CMD_EncodeUInt8ToBuffer(&p_frame_info->data_buffer, METER_CMD_SIGLOG_ERROR_MAX_SIGNALS);
    }
    else if ((signal_selection & (~temp)) != 0) {
        R_METER_CMD_EncodeUInt8ToBuffer(&p_frame_info->data_buffer, METER_CMD_SIGLOG_ERROR_INVALID_SIGNALS);
    }
    else if ((num_of_signals == 0) ||
             (sets_of_sample == 0)) {
        R_METER_CMD_EncodeUInt8ToBuffer(&p_frame_info->data_buffer, METER_CMD_SIGLOG_ERROR_ZERO_ARGUMENTS);
    }
    else {
        is_param_good = TRUE;
        R_METER_CMD_EncodeUInt8ToBuffer(&p_frame_info->data_buffer, METER_CMD_SIGLOG_RET_OK);
    }

    /* Encode max number of signals */
    R_METER_CMD_EncodeUInt8ToBuffer(&p_frame_info->data_buffer, METER_CMD_SIGLOG_SUPPORTED_NUM_OF_SIGNALS);

    /* Encode sampling rate */
    R_METER_CMD_EncodeUInt16ToBuffer(&p_frame_info->data_buffer, 3906);

    /* Encode elevated baudrate */
    R_METER_CMD_EncodeUInt32ToBuffer(&p_frame_info->data_buffer, ELEVATED_UART_BAUD_RATE);

    /* Send reply buffer */
    R_METER_CMD_PackAndSendResFrame(p_frame_info);

    /* Raise signal if parameter is correct */
    if (is_param_good == TRUE)
    {
        /* Reconfigure the driver for transfer */
        METER_CMD_SIGLOG_UART_STOP();
        /* Backup and apply new baudrate settings */
        METER_CMD_SIGLOG_UART_BACKUP_BAUDRATE_SETTING(backup_reg.sps, backup_reg.sdr);
        METER_CMD_SIGLOG_UART_APPLY_1_5MBAUD(sps_divider);
        METER_CMD_SIGLOG_UART_START();
        METER_CMD_SIGLOG_UART_DISABLE_INTERRUPT();

        /* Delay around 500ms */
        for (i = 0; i < 10; i++)
        {
            MCU_Delay(50000);
            R_WDT_Restart();
        }

        /* Assign transfer parameters */
        s_sets_of_sample = sets_of_sample;
        s_signal_mask = signal_selection;
        s_send_count = 0;
        /* Attach to DSAD background process */
        g_wrp_adc_signal_ready_cb_and_return = r_meter_cmd_send_samples;

        /* Lock application, wait until finish sending signal */
        while (s_sets_of_sample > 0)
        {
            R_WDT_Restart();
        }

        /* Detach from DSAD background process */
        g_wrp_adc_signal_ready_cb_and_return = NULL;

        /* Restart application uart driver */
        METER_CMD_SIGLOG_UART_STOP();
        /* Restore backed-up baudrate settings */
        METER_CMD_SIGLOG_UART_RESTORE_BAUDRATE_SETTING(backup_reg.sps, backup_reg.sdr);
        METER_CMD_SIGLOG_UART_START();
    }

    return 0;
}

#endif