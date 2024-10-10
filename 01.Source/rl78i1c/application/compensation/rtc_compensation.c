/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2012 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : rtc_compensation.c
* Version      : 
* Device(s)    : RL78/I1C
* Tool-Chain   : CA78K0R
* Description  : This file implements source file for RTC temperature compensation.
* Creation Date: 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
/* Driver layer */
#include "r_cg_macrodriver.h"
#include "r_cg_12adc.h"
#include "r_cg_tmps.h"
#include "r_cg_rtc.h"
#include "r_cg_wdt.h"

/* Code Standard */
#include "typedef.h"            /* GSCE Standard Typedef */

/* MW, WRP layer */
#include "wrp_em_mcu.h"
#include "wrp_app_mcu.h"
#include "wrp_app_ext.h"

/* Application layer */
#include "dataflash.h"
#include "config_format.h"
#include "rtc_compensation.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Start temperature of crystal profile */
#define RTC_COMPENSATION_START_TEMP             (25)

/* Default setting of temperature sensor */
#define TMPS_VBGR                               (2.00f)                 /* Band-gap internal reference voltage default: 1.50V */
#define ADC_STEPS								(4095.0f)				/* Total number of steps for 12bit SAR ADC */	

/* Define max value of RTC minute counter */
#if (RTC_CONST_PERIOD == 500)
    #define RTC_COMP_ONE_MINUTE_COUNT    120
#elif (RTC_CONST_PERIOD == 1000)
    #define RTC_COMP_ONE_MINUTE_COUNT    60
#else
    #error "RTC constant period must be 0.5s or 1s"
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/* Imported from rtc_crystal_profile.c */
extern const rtc_freq_error_t   g_rtc_crystal_profile[];
extern const uint16_t           g_crystal_profile_size;

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
unsigned int 	g_comp_flag_ad_conversion_end = 0;
uint16_t temps_buffer = 0;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/* Variables */
static volatile uint8_t                 g_comp_flag_start = 0;

/* Private function prototypes */
static float32_t RTC_COMP_LookupFreqErr(int16_t temp);                                              /* Lookup frequency error from measured temperature */
static float32_t RTC_COMP_Interpolate(int16_t temp);                                                /* Interpolate to get freq error at unspecific temperature */
static uint16_t RTC_COMP_GetSensorADCValue(void);                                                   /* Read ADC value */
static float32_t RTC_COMP_GetSensorVoltageValue(uint16_t temps_counter);                            /* Convert from ADC value to voltage value */
#ifndef __DEBUG
static
#endif
float32_t RTC_COMP_GetTemperature(uint8_t *out_mode, uint16_t *out_counter, float32_t * out_vs);    /* Get the current temperature reading */

/***********************************************************************************************************************
* Function Name: static float32_t RTC_COMP_LookupFreqErr(int16_t temp)
* Description  : Get the frequency error from measured temperature
* Arguments    : temp : measure temperature
* Return Value : frequency error
***********************************************************************************************************************/
static float32_t RTC_COMP_LookupFreqErr(int16_t temp)
{
    uint16_t                i;
    const rtc_freq_error_t  *p_max;
    const rtc_freq_error_t  *p_min;

    /* Calculate temperature value will be used to scan */
    if (temp < RTC_COMPENSATION_START_TEMP)
    {
        temp = 2 * RTC_COMPENSATION_START_TEMP - temp;
    }
    
    /* Get max, min input temperature */
    p_min = &g_rtc_crystal_profile[0];
    p_max = &g_rtc_crystal_profile[g_crystal_profile_size - 1]; 
    
    /* Check threshold temperature */
    if (temp >= (p_max->temperature))
    {
        return p_max->ppm;
    }
    else if (temp <= (p_min->temperature))
    {
        return p_min->ppm;
    }
    
    /* 
     * Scan temperature and choose frequency error 
     */
    
    /* Scan to choose the same temperature */
    for (i = 0; i < g_crystal_profile_size; i++)
    {
        if (temp == g_rtc_crystal_profile[i].temperature)
        {
            return g_rtc_crystal_profile[i].ppm;
        }
    }
    
    /* No the same temperature in profile, do interpolation */
    return RTC_COMP_Interpolate(temp);
}

/***********************************************************************************************************************
* Function Name: static float32_t RTC_COMP_Interpolate(int16_t temp)
* Description  : Do interpolation to get ppm value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static float32_t RTC_COMP_Interpolate(int16_t temp)
{
    float32_t               ppm = 0;
    uint16_t                i;
    const rtc_freq_error_t  *temp1 = NULL;  /* Near point 1, used to linear interpolate */
    const rtc_freq_error_t  *temp2 = NULL;  /* Near point 2, used to linear interpolate */
    
    /* Scan positive branch until meet the temperature larger than measured temperature */
    for (i = 1; i < g_crystal_profile_size; i++)
    {
        if (g_rtc_crystal_profile[i].temperature >= temp)
        {
            /* Get temp1 value */
            temp1 = &g_rtc_crystal_profile[i - 1];
            
            /* Get temp2 value */
            temp2 = &g_rtc_crystal_profile[i];
            
            break;
        }
    }
    
    /* Apply linear interpolation formula */
    if (temp1 != NULL && temp2 != NULL)
    {
        ppm = temp1->ppm + (temp2->ppm - temp1->ppm) * (temp - temp1->temperature) / (temp2->temperature - temp1->temperature);
    }
    
    return ppm;
}

/***********************************************************************************************************************
* Function Name: void RTC_COMP_Init(void)
* Description  : Initialize rtc compensation
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void RTC_COMP_Init(void)
{
    g_comp_flag_start = 1;
}

/***********************************************************************************************************************
* Function Name: static uint16_t RTC_COMP_GetSensorVoltageValue(void)
* Description  : Get measured voltage from Internal Sensor
* Arguments    : mode : Operation mode of Internal Sensor
* Return Value : uint16_t : voltage value
***********************************************************************************************************************/
static uint16_t RTC_COMP_GetSensorADCValue(void)
{
    uint16_t    temps_counter;
    float32_t   vs;
    uint8_t     i;
    
    R_12ADC_Start();
	
	//Wait for ADC stabilization
	MCU_Delay(50);
    //while (R_ADC_IsBusy() == 1);
    
    /* Read the temperature result counter then convert */
    R_12ADC_Get_ValueResult(ADTEMPERSENSOR, &temps_counter);
    
    return temps_counter;
}


/***********************************************************************************************************************
* Function Name: static float32_t RTC_COMP_GetSensorVoltageValue(void)
* Description  : Get measured voltage from Internal Sensor
* Arguments    : mode : Operation mode of Internal Sensor
* Return Value : float32_t : voltage value
***********************************************************************************************************************/
static float32_t RTC_COMP_GetSensorVoltageValue(uint16_t temps_counter)
{
    return (( (float32_t)temps_counter * TMPS_VBGR ) / ADC_STEPS);
}

/***********************************************************************************************************************
* Function Name : RTC_COMP_GetTemperature
* Interface     : float32_t RTC_COMP_GetTemperature(uint8_t *out_mode, uint16_t *out_counter, float32_t * out_vs)
* Description   : Get the temperature from temperature sensor module
* Arguments     : None
* Return Value  : float32_t: Acquired temperature value
***********************************************************************************************************************/
#ifndef __DEBUG
static
#endif
float32_t RTC_COMP_GetTemperature(uint8_t *out_mode, uint16_t *out_counter, float32_t * out_vs)
{
    float32_t   temps_degree;
    uint16_t    temps_counter;
    float32_t   vs;
    uint8_t     mode;
    uint8_t     selected_mode;
    /* 
     * Get the reading
     */
    R_TMPS_Start();
    //R_TMPS_SetMode(TMPS_MODE2);
	
	g_comp_flag_ad_conversion_end = 0;
	
	/* Read the temperature result counter then convert */
     //while(g_comp_flag_ad_conversion_end == 0)
     {
	     R_WDT_Restart();
     }
	 MCU_Delay(50);
    
    /* Read ADC result register */
    temps_counter = RTC_COMP_GetSensorADCValue();
	
	g_comp_flag_ad_conversion_end = 0;
    
    /* Stop the TMPS to conserve power */
    R_TMPS_Stop();
    
    /* Convert to voltage value */
    vs = RTC_COMP_GetSensorVoltageValue(temps_counter);
    
    /* Get the temperature with following formula 
     *                     (Vs - v1)     (V)
     * degree.C = 1000 * ----------------------- + t1
     *                      (Slope)   (mv/deg.c)
    */
    temps_degree = (1000.0f * ((vs - TMPS_MODE2_V1) / TMPS_MODE2_SLOPE)) + TMPS_MODE2_T1;
    
    
    /* Output additional information */
    if (out_mode != NULL)
    {
        //*out_mode = TMPS_MODE2;
    }
    
    if (out_counter != NULL)
    {
        *out_counter = temps_counter;
    }
    
    if (out_vs != NULL)
    {
        *out_vs = vs;
    }
    
    /* Return the read temperature */
    return temps_degree;
}


/***********************************************************************************************************************
* Function Name: void RTC_COMP_PollingProcessing(void)
* Description  : RTC compensation polling processing
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void RTC_COMP_PollingProcessing(void)
{
    uint8_t     mode;
    uint16_t    temps_counter;
    float32_t   vs;
    float32_t   ppm, ppm_offset;
    float32_t   temps_degree;
    
    /* Elapsed a period of compensation? */
    if (g_comp_flag_start)
    {
        /* 
         * STEP 1: Get the temperature value
         */
        temps_degree = RTC_COMP_GetTemperature(&mode, &temps_counter, &vs);
        
        /*
         * STEP 2: Look up ppm value on crystal profile,
         * based the the temperature has been read
         */
        ppm = RTC_COMP_LookupFreqErr((int16_t)temps_degree);
        
        /*
         * STEP 3: Adding center frequency error offset,
         * based on user manual calibration input
         */
        #if 0
        /* Read offset from calibration information */
        RTC_COMPENSATION_MEM_Read(  RTC_COMPENSATION_PPM_ADDR, 
                                    (uint8_t *)&ppm_offset, 
                                    sizeof(ppm_offset));
        #else
        /* Read offset from hard-coded information in header */
        ppm_offset = RTC_COMPENSATION_PPM_OFFSET;
        
        #endif
        
        ppm += ppm_offset;
        
        /*
         * STEP 4: Choose dynamic range, based on ppm has been calculated
         * then do compensation on RCR2 and RADJ register
         */
        R_RTC_Compensate(ppm);

        #ifdef __DEBUG
        {
            rtc_calendarcounter_value_t     rtctime;
            uint8_t period, action;
            float32_t actual_ppm;
            
            period = (BIT_SELECT(RCR2,5) == 1) ? 10 : 60;
            action = RADJ>>6;
            actual_ppm = (float)(RADJ & 0x3F)/(32768.0f * period) * 1e6f;
            
            if (actual_ppm == 0.0f)
            {
                return; 
            }
            
            R_RTC_Get_CalendarCounterValue(&rtctime);
            DEBUG_Printf((uint8_t *)"\n\r--- RTC compensation event ---\n\r");
            DEBUG_Printf(   (uint8_t *)"Current RTC time: %02x/%02x/20%02x %02x:%02x:%02x\n\r",
                            rtctime.rdaycnt,
                            rtctime.rmoncnt,
                            rtctime.ryrcnt,
                            rtctime.rhrcnt,
                            rtctime.rmincnt,
                            rtctime.rseccnt);
            DEBUG_Printf((uint8_t *)"\n\rTemperature sensor reading:");
            DEBUG_Printf((uint8_t *)"\n\r - ADC Counter: %04d", temps_counter);
            DEBUG_Printf((uint8_t *)"\n\r - Read Voltage: %.3f (V)", vs);
            DEBUG_Printf((uint8_t *)"\n\r - Temperature: %.3f (deg.C)\n\r", temps_degree);
            DEBUG_Printf((uint8_t *)"\n\rRTC error calculation:");
            DEBUG_Printf((uint8_t *)"\n\r - RTC error @ %.03f deg.C : %.3f (ppm)\n\r", temps_degree, ppm);
            DEBUG_Printf((uint8_t *)"\n\rRTC Compensation setting:");
            DEBUG_Printf((uint8_t *)"\n\r - Period: %d (seconds)", period);
            DEBUG_Printf((uint8_t *)"\n\r - Resolution: %.4f (ppm)\n\r", (period == 10) ? 3.0517f : 0.5086f);
            DEBUG_Printf((uint8_t *)"\n\rRADJ Value: 0x%2X", RADJ);
            DEBUG_Printf((uint8_t *)"\n\r - Compensate by: %s", (action == 0) ? "None" :
                                                                ((action == 1) ? "Add" : "Substract"));
            DEBUG_Printf((uint8_t *)"\n\r - Actual compensate value: %.3f (ppm)", actual_ppm);
            DEBUG_Printf((uint8_t *)"\n\r - Compensation error: %.3f (%%)", ((WRP_EXT_Absf(ppm) - WRP_EXT_Absf(actual_ppm))/ WRP_EXT_Absf(ppm)) * 100.0f);
            DEBUG_AckNewLine();
        }
        #endif
        
        /* Clear as ack */
        g_comp_flag_start = 0;
    }
}

/***********************************************************************************************************************
* Function Name: void RTC_COMP_ConstInterruptCallback(void)
* Description  : RTC Const Period Callback for minute counting
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void RTC_COMP_ConstInterruptCallback(void)
{
    static uint16_t second_counter = 0;
    static uint16_t minute_counter = 0;
    
    second_counter++;
    if (second_counter >= RTC_COMP_ONE_MINUTE_COUNT)
    {       
        minute_counter++;
        if (minute_counter >= RTC_COMPENSATION_PERIOD)
        {
            /* Mark to trigger a start to do compensation */
			//EI();
            g_comp_flag_start = 1;
            
            /* Next counting */
            minute_counter = 0;
        }
        
        /* Next counting */
        second_counter = 0;
    }   
}
