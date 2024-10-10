/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
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
* Copyright (C) 2016, 2019 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_12adc.c
* Version      : Code Generator for RL78/L1A V1.01.03.01 [17 May 2019]
* Device(s)    : R5F11MPG
* Tool-Chain   : CCRL
* Description  : This file implements device driver for ADC module.
* Creation Date: 8/25/2020
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_12adc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
const uint16_t g_12ad_adansa0_gui = _0000_AD_ADANSA0_GUI_VALUE;         /* AD GUI channel setting value*/
const uint16_t g_12ad_adexicr_gui = _0100_AD_ADEXICR_GUI_VALUE;         /* AD GUI channel setting value */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_12ADC_Create
* Description  : This function initializes AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_12ADC_Create(void)
{
    volatile uint16_t w_count;

    ADCRES = 1U;    /* reset A/D converter */
    ADCRES = 0U;    /* reset release of A/D converter */
    ADCEN = 1U;     /* enables input clock supply */
    ADCSR = _0000_AD_CONVERSION_DISABLE | _0000_AD_SCAN_MODE_SINGLE | _0000_AD_INTAD_DISABLE | 
            _0000_AD_CONVERSION_HIGH_SPEED | _0000_AD_TRIGGER_CONVERSION_DISABLE;
    ADMK = 1U;      /* disable INTAD interrupt */
    ADIF = 0U;      /* clear INTAD interrupt flag */
    /* Set INTAD low priority */
    ADPR1 = 1U;
    ADPR0 = 1U;
    /* Set VREFOUT pin */
    PMC2 |= 0x01U;
    PM2 |= 0x01U;
    /* Set ADC registers */
    ADCKS = _02_AD_CLK_DIVIDED_4;
    ADSLP = 1U;     /* standby state */
    NOP();
    ADCSR = _0000_AD_CONVERSION_DISABLE | _0000_AD_SCAN_MODE_SINGLE | _1000_AD_INTAD_ENABLE | 
            _0400_AD_CONVERSION_NORMAL | _0000_AD_TRIGGER_CONVERSION_DISABLE;//_0200_AD_TRIGGER_CONVERSION_ENABLE;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= CLEAR_SLEEP_WAITTIME; w_count++)
    {
        NOP();
    }

    ADSLP = 0U;     /* normal operation */
    ADHVREFCNT |= _03_AD_HIGH_REF_DISCHARGE;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= DISCHARGE_WAITTIME; w_count++)
    {
        NOP();
    }

    VREFAMPCNT = _10_AD_BGR_ON | _04_AD_VREFOUT_2_0;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= BRG_WAITTIME; w_count++)
    {
        NOP();
    }

    VREFAMPCNT &= (uint8_t)~_01_AD_OVERCURRENT_ENABLE;

    VREFAMPCNT |= _08_AD_HIGH_REF_VREFOUT;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= VREFAMP_WAITTIME; w_count++)
    {
        NOP();
    }

    ADHVREFCNT = _00_AD_SLEEP_NORMAL | _00_AD_LOW_REF_AVSS1 | _01_AD_HIGH_REF_AVREFP_VREFOUT;
    ADADC = _00_AD_MODE_ADDITION | _00_AD_CONVERSION_1TIME;
    ADCER = _0000_AD_DATA_FLUSH_RIGHT | _0000_AD_SELF_DIAGNOSIS_DISABLE | _0000_AD_SELF_DIAGNOSIS_ROTATION | 
            _0020_AD_AUTO_CLEAR_ENABLE;
    /* Set input sampling time value */
    ADSSTRT = _08_AD_SAMPLE_STATE_TEMPERATURE_VALUE;
    /* Set AD channel */
    ADANSA0 = _0000_AD_ANI5_NOT_SUBJECT | _0000_AD_ANI4_NOT_SUBJECT | _0000_AD_ANI3_NOT_SUBJECT | 
              _0000_AD_ANI2_NOT_SUBJECT | _0000_AD_ANI1_NOT_SUBJECT | _0000_AD_ANI0_NOT_SUBJECT;
    ADADS0 = _0000_AD_ANI5_NOT_ADD_AVERAGE | _0000_AD_ANI4_NOT_ADD_AVERAGE | _0000_AD_ANI3_NOT_ADD_AVERAGE | 
             _0000_AD_ANI2_NOT_ADD_AVERAGE | _0000_AD_ANI1_NOT_ADD_AVERAGE | _0000_AD_ANI0_NOT_ADD_AVERAGE;
    ADEXICR = _0000_AD_REF_VOLTAGE_DISABLE | _0100_AD_TEMPERATURE_ENABLE | _0000_AD_REF_ADD_AVERAGE_DISABLE | 
              _0000_AD_TEMPERATURE_ADD_AVERAGE_DISABLE;
}
/***********************************************************************************************************************
* Function Name: R_12ADC_Start
* Description  : This function starts AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_12ADC_Start(void)
{
    ADIF = 0U;      /* clear INTAD interrupt flag */
    ADMK = 0U;      /* enable INTAD interrupt */
    ADCSR |= _8000_AD_CONVERSION_ENABLE;
}
/***********************************************************************************************************************
* Function Name: R_12ADC_Stop
* Description  : This function stops AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_12ADC_Stop(void)
{
    ADCSR &= (uint16_t)~_8000_AD_CONVERSION_ENABLE;
    ADMK = 1U;      /* disable INTAD interrupt */
    ADIF = 0U;      /* clear INTAD interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_12ADC_Get_ValueResult
* Description  : This function gets AD converter result.
* Arguments    : channel -
*                    AD converter channel
*                buffer -
*                    buffer result
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_12ADC_Get_ValueResult(ad_channel_t channel, uint16_t * const buffer)
{
    MD_STATUS status = MD_OK;

    switch (channel)
    {

        case ADCHANNEL0:

            *buffer = (uint16_t)ADDR0;

            break;

        case ADCHANNEL1:

            *buffer = (uint16_t)ADDR1;

            break;

        case ADCHANNEL2:

            *buffer = (uint16_t)ADDR2;

            break;

        case ADCHANNEL3:

            *buffer = (uint16_t)ADDR3;

            break;

        case ADCHANNEL4:

            *buffer = (uint16_t)ADDR4;

            break;

        case ADCHANNEL5:

            *buffer = (uint16_t)ADDR5;

            break;

        case ADINTERREFVOLT:

            *buffer = (uint16_t)ADOCDR;

            break;

        case ADTEMPERSENSOR:

            *buffer = (uint16_t)ADTSDR;

            break;

        default:

            status = MD_ARGERROR;

            break;		    
    }

    return status;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
