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
/* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.  */
/****************************************************************************** 
* File Name    : wrp_em_adc_ram.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CubeSuite Version 1.5d
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : ADC Wrapper for RL78/I1C Platform
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"
#include "r_cg_dsadc.h"

/* Wrapper */
#include "wrp_em_sw_config.h"           /* EM Software Config */
#include "wrp_em_adc.h"                 /* Wrapper ADC definitions */

/* Middleware */
#include "em_type.h"
#include "em_core.h"

/* Standard library */
#include <string.h>

/* Application */
#include "platform.h"
#include "bl_operation.h"

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct
{
    int16_t pos;        /* Position */
    uint16_t step;      /* Step */
    int32_t *p_value;   /* Array of signals */
} shift_circle_t;

/******************************************************************************
Macro definitions
******************************************************************************/
#define EM_ADC_CHANNEL_RESULT_REG_ADDR_VOLTAGE              (&(JOIN(DSADCR, EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_VOLTAGE)))
#define EM_ADC_CHANNEL_RESULT_REG_ADDR_PHASE                (&(JOIN(DSADCR, EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_PHASE)))
#define EM_ADC_CHANNEL_RESULT_REG_ADDR_NEUTRAL              (&(JOIN(DSADCR, EM_ADC_CURRENT_DRIVER_CHANNEL_OPTIMIZATION_NEUTRAL)))

#if (defined METER_WRAPPER_ADC_COPY_NEUTRAL_SAMPLE)
#define EM_ADC_DRIVER_READ_NEUTRAL() {\
    *((uint16_t *)&g_wrp_adc_samples.i2) = *((uint16_t *)EM_ADC_CHANNEL_RESULT_REG_ADDR_NEUTRAL); \
    *((uint8_t *)&g_wrp_adc_samples.i2 + 0x02) = *((uint8_t *)EM_ADC_CHANNEL_RESULT_REG_ADDR_NEUTRAL + 0x02); \
    *((int8_t *)&g_wrp_adc_samples.i2 + 0x03) = (*((int8_t *)EM_ADC_CHANNEL_RESULT_REG_ADDR_NEUTRAL + 0x02)) >> 7; \
}
#else
#define EM_ADC_DRIVER_READ_NEUTRAL() {;}
#endif

#define EM_ADC_DRIVER_READ_ALL()    {\
                                        /* Voltage channel */\
                                        *((uint16_t *)&g_wrp_adc_samples.v)         = *((uint16_t *)EM_ADC_CHANNEL_RESULT_REG_ADDR_VOLTAGE);\
                                        *((uint8_t *)&g_wrp_adc_samples.v + 0x02)   = *((uint8_t *)EM_ADC_CHANNEL_RESULT_REG_ADDR_VOLTAGE + 0x02);\
                                        *((int8_t *)&g_wrp_adc_samples.v + 0x03)    = (*((int8_t *)EM_ADC_CHANNEL_RESULT_REG_ADDR_VOLTAGE + 0x02)) >> 7;\
                                        /* Phase channel */\
                                        *((uint16_t *)&g_wrp_adc_samples.i1)        = *((uint16_t *)EM_ADC_CHANNEL_RESULT_REG_ADDR_PHASE);\
                                        *((uint8_t *)&g_wrp_adc_samples.i1 + 0x02)  = *((uint8_t *)EM_ADC_CHANNEL_RESULT_REG_ADDR_PHASE + 0x02);\
                                        *((int8_t *)&g_wrp_adc_samples.i1 + 0x03)   = (*((int8_t *)EM_ADC_CHANNEL_RESULT_REG_ADDR_PHASE + 0x02)) >> 7;\
                                        /* Neutral channel */\
                                        EM_ADC_DRIVER_READ_NEUTRAL();\
                                    }

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/* Sample storage of wrapper */
extern EM_SAMPLES g_wrp_adc_samples;

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

#pragma section text WrpRamTx

/* Sub-functions */
static void EM_ADC_DoPhaseDelay(
    int32_t *signal,
    shift_circle_t *p_circle
);

/******************************************************************************
* Function Name    : static void EM_ADC_DoPhaseDelay(
*                  :    int32_t *signal, 
*                  :    int32_t *p_circle
*                  : )
* Description      : Shift input signal as expected step
* Arguments        : *signal  : Signal income then outcome
*                  : *p_circle: Circle structure used to control the phase
* Functions Called : TBD
* Return Value     : None
******************************************************************************/
static void EM_ADC_DoPhaseDelay(
    int32_t *signal,
    shift_circle_t *p_circle
)
{
    int16_t push_pos;
    int16_t pop_pos;
    
    push_pos = p_circle->pos;
    if (push_pos <= 0)
    {
        pop_pos = p_circle->step;
    }
    else
    {
        pop_pos = push_pos - 1;
    }

    /* PUSH: Add the signal into the data circle at circlepos position */
    p_circle->p_value[push_pos] = *signal;

    /* POP: Get the signal from data circle from (pos + steps) position */
    *signal = p_circle->p_value[pop_pos];
    
    /* Scroll the circle, scroll left */
    push_pos--;
    if (push_pos == -1)
    {
        push_pos = p_circle->step;
    }

    p_circle->pos = push_pos;
}

/******************************************************************************
* Function Name    : void EM_ADC_InterruptCallback(void)
* Description      : ADC Interrupt callback processing
* Arguments        : None
* Functions Called : TBD
* Return Value     : None
******************************************************************************/
void EM_ADC_RAM_InterruptCallback(void)
{
    uint16_t        v_mask, i1_mask, i2_mask;

    /* Read all dsad result to buffer */
    EM_ADC_DRIVER_READ_ALL();

    /************************************************************
    * Noisy bit masking
    *  - Find the signal mask
    *************************************************************/
    #ifdef EM_ENABLE_NOISY_BIT_MASKING
    /* Find the mask of V, I1, I2 for signal accumulation */
    v_mask      = (int16_t)(g_wrp_adc_samples.v       >> 16);
    i1_mask     = (int16_t)(g_wrp_adc_samples.i1      >> 16);
    #ifdef METER_WRAPPER_ADC_COPY_NEUTRAL_SAMPLE
    i2_mask     = (int16_t)(g_wrp_adc_samples.i2      >> 16);
    #endif /* METER_WRAPPER_ADC_COPY_NEUTRAL_SAMPLE */

    if (v_mask == 0x0000)
    {
        /* Mask off the noise, 4 low-bits */
        *((uint8_t *)&g_wrp_adc_samples.v) &= EM_MASK_OFF_NOISY_BITS_POSITIVE;
    }
    else if (v_mask == 0xffff)
    {
        /* Mask off the noise, 4 low-bits */
        *((uint8_t *)&g_wrp_adc_samples.v) |= EM_MASK_OFF_NOISY_BITS_NEGATIVE;
    }

    if (i1_mask == 0x0000)
    {
        /* Mask off the noise, 4 low-bits */
        *((uint8_t *)&g_wrp_adc_samples.i1) &= EM_MASK_OFF_NOISY_BITS_POSITIVE;
    }
    else if (i1_mask == 0xffff)
    {
        /* Mask off the noise, 4 low-bits */
        *((uint8_t *)&g_wrp_adc_samples.i1) |= EM_MASK_OFF_NOISY_BITS_NEGATIVE;
    }

    #ifdef METER_WRAPPER_ADC_COPY_NEUTRAL_SAMPLE
    if (i2_mask == 0x0000)
    {
        /* Mask off the noise, 4 low-bits */
        *((uint8_t *)&g_wrp_adc_samples.i2) &= EM_MASK_OFF_NOISY_BITS_POSITIVE;
    }
    else if (i2_mask == 0xffff)
    {
        /* Mask off the noise, 4 low-bits */
        *((uint8_t *)&g_wrp_adc_samples.i2) |= EM_MASK_OFF_NOISY_BITS_NEGATIVE;
    }
    #endif /* METER_WRAPPER_ADC_COPY_NEUTRAL_SAMPLE */
    #endif /* EM_ENABLE_NOISY_BIT_MASKING */
    
    /* Phase adjustment for each channel if enabled */
    #if (EM_ADC_DELAY_STEP_VOLTAGE_CHANNEL > 0)
    EM_ADC_DoPhaseDelay(
        &g_wrp_adc_samples.v,
        &g_wrp_adc_voltage_circle
    );
    #endif
    
    #if (EM_ADC_DELAY_STEP_PHASE_CHANNEL > 0)
    EM_ADC_DoPhaseDelay(
        &g_wrp_adc_samples.i1,
        &g_wrp_adc_phase_circle
    );
    #endif
    
    #if (EM_ADC_DELAY_STEP_NEUTRAL_CHANNEL > 0)
    EM_ADC_DoPhaseDelay(
        &g_wrp_adc_samples.i2,
        &g_wrp_adc_neutral_circle
    );
    #endif
    
    /* Integrate the signal if using Rogowski coil */
    #if (METER_ENABLE_INTEGRATOR_ON_SAMPLE == 1)
    #ifndef __DEBUG
        g_datalog_sample_before_integrate_i1 = g_wrp_adc_samples.i1;
        g_datalog_sample_before_integrate_i2 = g_wrp_adc_samples.i2;
    #endif
    /* Integrate the signal from Rogowski coil, API will append later */
    g_wrp_adc_samples.i1 = EM_ADC_Integrator0(g_wrp_adc_samples.i1);
    g_wrp_adc_samples.i2 = EM_ADC_Integrator1(g_wrp_adc_samples.i2);
    
    #endif
    
    {
        {
            /* Normal processing */
            EM_ADC_RAM_IntervalProcessing(&g_wrp_adc_samples);
        }
    }
}
