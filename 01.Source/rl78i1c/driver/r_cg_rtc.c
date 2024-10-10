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
* Copyright (C) 2015, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_rtc.c
* Version      : Code Generator for RL78/I1C V1.01.07.02 [08 Nov 2021]
* Device(s)    : R5F10NPL(Dual)
* Tool-Chain   : CCRL
* Description  : This file implements device driver for RTC module.
* Creation Date: 2/22/2023
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"
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

/* Start user code for global. Do not edit comment generated here */
#define ABS(x)                  ((x) <  0  ? (-(x)) : (x))                          /* Get absolute value */

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_RTC_Create
* Description  : This function initializes the real-time clock module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Create(void)
{
    volatile uint8_t tmp;
    volatile uint16_t w_count;

    VRTCEN = 1U;    /* enables input clock supply */

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= RTC_STARTWAITTIME; w_count++)
    {
        NOP();
    }

    if ((_00_RTC_POWERON_RESET_OCCUR == RTCPORSR) && (LVDVRTCF == 0 ))
    {
        
        tmp = RCR2;
        tmp &= (uint8_t)~_01_RTC_COUNTER_NORMAL;
        RCR2 = tmp;
        RTCRMK = 1U;    /* disable INTRTCPRD interrupt */
        RTCRIF = 0U;    /* clear INTRTCPRD interrupt flag */
        RTCAMK0 = 1U;   /* disable INTRTCALM0 interrupt */
        RTCAIF0 = 0U;   /* clear INTRTCALM0 interrupt flag */
        RTCAMK1 = 1U;   /* disable INTRTCALM1 interrupt */
        RTCAIF1 = 0U;   /* clear INTRTCALM1 interrupt flag */
        /* Set INTRTCPRD low priority */
        RTCRPR1 = 1U;
        RTCRPR0 = 1U;
        /* Set INTRTCALM0 low priority */
        RTCAPR10 = 1U;
        RTCAPR00 = 1U;
        /* Set INTRTCALM1 low priority */
        RTCAPR11 = 1U;
        RTCAPR01 = 1U;
        tmp = RCR1;
        tmp &= (uint8_t)~_01_RTC_ALARM_ENABLE;
        RCR1 = tmp;
        tmp = RCR1;
        tmp &= (uint8_t)~_04_RTC_PERIODIC_ENABLE;
        RCR1 = tmp;
        tmp = RCR3;
        tmp |= _01_RTC_INPUT_ENABLE;
        RCR3 = tmp;

        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count <= RTC_6CLOCKWAITTIME; w_count++)
        {
            NOP();
        }

        tmp = RCR2;
        tmp &= (uint8_t)~_80_RTC_BINARY_MODE;
        RCR2 = tmp;

        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count <= RTC_STARTWAITTIME; w_count++)
        {
            NOP();
        }

        tmp = RCR2;
        tmp |= _02_RTC_RESET_WRITER_INITIALIZED;
        RCR2 = tmp;

        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count <= RTC_RESETWAITTIME; w_count++)
        {
            NOP();
        }

        RSECCNT = _00_RTC_CALENDER_COUNTER_10SEC | _00_RTC_CALENDER_COUNTER_1SEC;
        RMINCNT = _00_RTC_CALENDER_COUNTER_10MIN | _00_RTC_CALENDER_COUNTER_1MIN;
        RHRCNT = _00_RTC_CALENDER_COUNTER_AMHOUR | _00_RTC_CALENDER_COUNTER_10HOUR | _00_RTC_CALENDER_COUNTER_1HOUR;
        RWKCNT = _06_RTC_CALENDER_COUNTER_SATURWEEK;
        RDAYCNT = _00_RTC_CALENDER_COUNTER_10DAY | _01_RTC_CALENDER_COUNTER_1DAY;
        RMONCNT = _00_RTC_CALENDER_COUNTER_NOTHAVE_10MONTH | _01_RTC_CALENDER_COUNTER_1MONTH;
        RYRCNT = _0000_RTC_CALENDER_COUNTER_10YEAR | _0000_RTC_CALENDER_COUNTER_1YEAR;
        RSECAR0 = _00_RTC_CALENDER_RSECCNT_SEC_NOTCOMPARE0 | _00_RTC_CALENDER_ALARM0_10SEC | _00_RTC_CALENDER_ALARM0_1SEC;
        RMINAR0 = _00_RTC_CALENDER_RMINCNT_MIN_NOTCOMPARE0 | _00_RTC_CALENDER_ALARM0_10MIN | _00_RTC_CALENDER_ALARM0_1MIN;
        RHRAR0 = _00_RTC_CALENDER_RHRCNT_HOUR_NOTCOMPARE0 | _00_RTC_CALENDER_ALARM0_AM | 
             _00_RTC_CALENDER_ALARM0_10HOUR | _00_RTC_CALENDER_ALARM0_1HOUR;
        RWKAR0 = _00_RTC_CALENDER_RWKCNT_WEEK_NOTCOMPARE0 | _06_RTC_CALENDER_ALARM0_SATURWEEK;
        RDAYAR0 = _00_RTC_CALENDER_RDAYCNT_DAY_NOTCOMPARE0 | _00_RTC_CALENDER_ALARM0_10DAY | _01_RTC_CALENDER_ALARM0_1DAY;
        RMONAR0 = _00_RTC_CALENDER_RMONCNT_MONTH_NOTCOMPARE0 | _00_RTC_CALENDER_ALARM0_NOTHAVE_10MON | 
              _01_RTC_CALENDER_ALARM0_1MON;
        RYRAR0 = _0000_RTC_CALENDER_ALARM0_10YEAR | _0000_RTC_CALENDER_ALARM0_1YEAR;
        RSECAR1 = _00_RTC_CALENDER_RSECCNT_SEC_NOTCOMPARE1 | _00_RTC_CALENDER_ALARM1_10SEC | _00_RTC_CALENDER_ALARM1_1SEC;
        RMINAR1 = _00_RTC_CALENDER_RMINCNT_MIN_NOTCOMPARE1 | _00_RTC_CALENDER_ALARM1_10MIN | _00_RTC_CALENDER_ALARM1_1MIN;
        RHRAR1 = _00_RTC_CALENDER_RHRCNT_HOUR_NOTCOMPARE1 | _00_RTC_CALENDER_ALARM1_AM | 
             _00_RTC_CALENDER_ALARM1_10HOUR | _00_RTC_CALENDER_ALARM1_1HOUR;
        RWKAR1 = _00_RTC_CALENDER_RWKCNT_WEEK_NOTCOMPARE1 | _06_RTC_CALENDER_ALARM1_SATURWEEK;
        RDAYAR1 = _00_RTC_CALENDER_RDAYCNT_DAY_NOTCOMPARE1 | _00_RTC_CALENDER_ALARM1_10DAY | _01_RTC_CALENDER_ALARM1_1DAY;
        RMONAR1 = _00_RTC_CALENDER_RMONCNT_MONTH_NOTCOMPARE1 | _00_RTC_CALENDER_ALARM1_NOTHAVE_10MON | 
              _01_RTC_CALENDER_ALARM1_1MON;
        RYRAR1 = _0000_RTC_CALENDER_ALARM1_10YEAR | _0000_RTC_CALENDER_ALARM1_1YEAR;
        tmp = RCR1;
        tmp |= _D0_RTC_INTRTCPRD_CLOCK_7 | _00_RTC_1HZ_OUTPUT | _04_RTC_PERIODIC_ENABLE | _01_RTC_ALARM_ENABLE;
        RCR1 = tmp;
        tmp = RCR2;
        tmp |= _00_RTC_CALENDER_MODE | _40_RTC_24HOUR_MODE | _08_RTC_RTCOUT_ENABLE;
        RCR2 = tmp;

        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count <= RTC_6CLOCKWAITTIME; w_count++)
        {
            NOP();
        }

        RTCCR0 = _00_RTC_RTCICN0_DISABLE | _00_RTC_EVENT0_NOTDETECTED;
        RTCCR1 = _80_RTC_RTCICN1_ENABLE | _20_RTC_FILTER1_COUNT_ON | _00_RTC_EVENT1_NOTDETECTED | _00_RTC_CAPTURE1_NOEVENT;
        RTCCR2 = _80_RTC_RTCICN2_ENABLE | _20_RTC_FILTER2_COUNT_ON | _00_RTC_EVENT2_NOTDETECTED | _00_RTC_CAPTURE2_NOEVENT;
        RTCICNFEN = _40_RTC_RTCIC2_FILTER_250ON | _20_RTC_RTCIC1_FILTER_250ON;

        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count < RTC_6CLOCKWAITTIME; w_count++)
        {
            NOP();
        }
		
        RTCCR1 |= _02_RTC_CAPTURE1_FALLING;
        RTCCR2 |= _02_RTC_CAPTURE2_FALLING;
		
		/* Start the RTC once */
    	tmp = RCR2;
        tmp |= _01_RTC_COUNTER_NORMAL;
        RCR2 = tmp;
		
        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count <= RTC_STARTWAITTIME; w_count++)
        {
            NOP();
        }
		
		RTCPORSR = _01_RTC_POWERON_RESET_CHECK;
    }
    
    /* Set RTCOUT pin */
    P15 &= 0xFEU;
    PM15 &= 0xFEU;
    /* Set RTCIC1 pin */
    PM15 |= 0x02U;
    /* Set RTCIC2 pin */
    PM15 |= 0x04U;
}

/***********************************************************************************************************************
* Function Name: R_RTC_Start
* Description  : This function enables the real-time clock.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Start(void)
{
    volatile uint8_t tmp;
	volatile uint8_t w_count;
	
    RTCRIF = 0U;    /* clear INTRTCPRD interrupt flag */
    RTCRMK = 0U;    /* enable INTRTCPRD interrupt */
    RTCAIF0 = 0U;   /* clear INTRTCALM0 interrupt flag */
    RTCAMK0 = 0U;   /* enable INTRTCALM0 interrupt */
    RTCAIF1 = 0U;   /* clear INTRTCALM1 interrupt flag */
    RTCAMK1 = 0U;   /* enable INTRTCALM1 interrupt */
	
	#if 0
    /* Do not start the RTC, just mask the interrupt because in metering RTC shall start one when create */
    tmp = RCR2;
    tmp |= _01_RTC_COUNTER_NORMAL;
    RCR2 = tmp;
	/* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= RTC_STARTWAITTIME; w_count++)
    {
        NOP();
    }
	#endif /* 0 or 1 */
}

/***********************************************************************************************************************
* Function Name: R_RTC_Stop
* Description  : This function disables the real-time clock.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Stop(void)
{
    volatile uint8_t tmp;
    volatile uint16_t w_count;
	
	#if 0
	/* Do not stop/reset the RTC, just mask the interrupt because in metering RTC shall never stop */
    tmp = RCR2;
    tmp &= (uint8_t)~_01_RTC_COUNTER_NORMAL;
    RCR2 = tmp;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= RTC_STARTWAITTIME; w_count++)
    {
        NOP();
    }

    tmp = RCR2;
    tmp |= _02_RTC_RESET_WRITER_INITIALIZED;
    RCR2 = tmp;
	
    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= RTC_RESETWAITTIME; w_count++)
    {
        NOP();
    }
	#endif /* 0 or 1 */
	
    RTCRMK = 1U;    /* disable INTRTCPRD interrupt */
    RTCRIF = 0U;    /* clear INTRTCPRD interrupt flag */
    RTCAMK0 = 1U;   /* disable INTRTCALM0 interrupt */
    RTCAIF0 = 0U;   /* clear INTRTCALM0 interrupt flag */
    RTCAMK1 = 1U;   /* disable INTRTCALM1 interrupt */
    RTCAIF1 = 0U;   /* clear INTRTCALM1 interrupt flag */
}


/***********************************************************************************************************************
* Function Name: R_RTC_Set_CalendarCounterValue
* Description  : This function changes the calendar real-time clock value.
* Arguments    : counter_write_val -
*                    the expected real-time clock value(BCD code)
* Return Value : status -
*                    MD_OK or MD_BUSY1
***********************************************************************************************************************/
MD_STATUS R_RTC_Set_CalendarCounterValue(rtc_counter_value_t counter_write_val)
{
    MD_STATUS status = MD_OK;
    volatile uint16_t  w_count;
    volatile uint8_t tmp;

    tmp = RCR2;
    tmp &= (uint8_t)~_01_RTC_COUNTER_NORMAL;
    RCR2 = tmp;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < RTC_WAITTIME; w_count++)
    {
        NOP();
    }

    if (_01_RTC_COUNTER_NORMAL == (RCR2 & _01_RTC_COUNTER_NORMAL))
    {
        status = MD_BUSY1;
    }
    else
    {
        RSECCNT = counter_write_val.sec;
        RMINCNT = counter_write_val.min;
        RHRCNT = counter_write_val.hour;
        RWKCNT = counter_write_val.week;
        RDAYCNT = counter_write_val.day;
        RMONCNT = counter_write_val.month;
        RYRCNT = counter_write_val.year;
    }
	/* Read back to make sure value is set */
    for (w_count = 0; w_count < 4; w_count++)
    {
        tmp = RSECCNT;
        tmp = RMINCNT;
        tmp = RHRCNT;
        tmp = RWKCNT;
        tmp = RDAYCNT;
        tmp = RMONCNT;
        tmp = (uint8_t)RYRCNT;
    }
    
    /* Restart counting : START is bit 0 */
    tmp = RCR2;
    tmp |= _01_RTC_COUNTER_NORMAL;
    RCR2 = tmp;
    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= RTC_STARTWAITTIME; w_count++)
    {
        NOP();
    }
    return (status);
}


/***********************************************************************************************************************
* Function Name: R_RTC_Get_CalendarCounterValue
* Description  : This function reads the results of real-time clock and store them in the variables.
* Arguments    : counter_read_val -
*                    the expected real-time clock value(BCD code)
* Return Value : status -
*                    MD_OK or MD_ERROR
***********************************************************************************************************************/
MD_STATUS R_RTC_Get_CalendarCounterValue(rtc_counter_value_t * const counter_read_val)
{
    MD_STATUS status = MD_OK;
    volatile uint8_t tmp;

    tmp = RSR;
    tmp &= (uint8_t)~_02_RTC_SECOND_CARRY;
    RSR = tmp;
    counter_read_val->sec = RSECCNT;
    counter_read_val->min = RMINCNT;

    if ((RCR2 & 0x40) == 0x40)
    {
        counter_read_val->hour = RHRCNT & 0xBF;
    }
    else
    {
       counter_read_val->hour = RHRCNT; 
    }
    
    counter_read_val->week = RWKCNT;
    counter_read_val->day = RDAYCNT;
    counter_read_val->month = RMONCNT;
    counter_read_val->year = RYRCNT;
    if (_02_RTC_SECOND_CARRY == (RSR & _02_RTC_SECOND_CARRY))
    {
        status = MD_ERROR;
    }

    return (status);
}


/***********************************************************************************************************************
* Function Name: R_RTC_Set_CalendarAlarm0On
* Description  : This function start calendar alarm 0.
* Arguments    : enb_set -
*                    
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Set_CalendarAlarm0On(int8_t enb_set)
{
    volatile uint16_t  w_count;
    volatile uint8_t tmp;

    RTCAMK0 = 1U;   /* disable INTRTCALM0 interrupt */
    tmp = RCR1;
    tmp &= (uint8_t)~_01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
    if ((enb_set & RTC_RSECAR_ENB) == RTC_RSECAR_ENB)
    {
        RSECAR0 |= _80_RTC_CALENDER_RSECCNT_SEC_COMPARE0;
    }
    if ((enb_set & RTC_RMINAR_ENB) == RTC_RMINAR_ENB)
    {
        RMINAR0 |= _80_RTC_CALENDER_RMINCNT_MIN_COMPARE0;
    }
    if ((enb_set & RTC_RHRAR_ENB) == RTC_RHRAR_ENB)
    {
        RHRAR0 |= _80_RTC_CALENDER_RHRCNT_HOUR_COMPARE0;
    }
    if ((enb_set & RTC_RWKAR_ENB) == RTC_RWKAR_ENB)
    {
        RWKAR0 |= _80_RTC_CALENDER_RWKCNT_WEEK_COMPARE0;
    }
    if ((enb_set & RTC_RDAYAR_ENB) == RTC_RDAYAR_ENB)
    {
        RDAYAR0 |= _80_RTC_CALENDER_RDAYCNT_DAY_COMPARE0;
    }
    if ((enb_set & RTC_RMONAR_ENB) == RTC_RMONAR_ENB)
    {
        RMONAR0 |= _80_RTC_CALENDER_RMONCNT_MONTH_COMPARE0;
    }
    if ((enb_set & RTC_RYRAREN_ENB) == RTC_RYRAREN_ENB)
    {
        RYRAREN0 |= _80_RTC_CALENDER_RYRCNT_YEAR_COMPARE0;
    }

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < RTC_WAITTIME_ARSET; w_count++)
    {
        NOP();
    }

    tmp = RCR1;
    tmp |= _01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
    RTCAIF0 = 0U;   /* clear INTRTCALM0 interrupt flag */
    RTCAMK0 = 0U;   /* enable INTRTCALM0 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_RTC_Set_CalendarAlarm1On
* Description  : This function start calendar alarm 1.
* Arguments    : enb_set -
*                    
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Set_CalendarAlarm1On(int8_t enb_set)
{
    volatile uint16_t  w_count;
    volatile uint8_t tmp;

    RTCAMK1 = 1U;   /* disable INTRTCALM1 interrupt */
    tmp = RCR1;
    tmp &= (uint8_t)~_01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
    if ((enb_set & RTC_RSECAR_ENB) == RTC_RSECAR_ENB)
    {
        RSECAR1 |= _80_RTC_CALENDER_RSECCNT_SEC_COMPARE1;
    }
    if ((enb_set & RTC_RMINAR_ENB) == RTC_RMINAR_ENB)
    {
        RMINAR1 |= _80_RTC_CALENDER_RMINCNT_MIN_COMPARE1;
    }
    if ((enb_set & RTC_RHRAR_ENB) == RTC_RHRAR_ENB)
    {
        RHRAR1 |= _80_RTC_CALENDER_RHRCNT_HOUR_COMPARE1;
    }
    if ((enb_set & RTC_RWKAR_ENB) == RTC_RWKAR_ENB)
    {
        RWKAR1 |= _80_RTC_CALENDER_RWKCNT_WEEK_COMPARE1;
    }
    if ((enb_set & RTC_RDAYAR_ENB) == RTC_RDAYAR_ENB)
    {
        RDAYAR1 |= _80_RTC_CALENDER_RDAYCNT_DAY_COMPARE1;
    }
    if ((enb_set & RTC_RMONAR_ENB) == RTC_RMONAR_ENB)
    {
        RMONAR1 |= _80_RTC_CALENDER_RMONCNT_MONTH_COMPARE1;
    }
    if ((enb_set & RTC_RYRAREN_ENB) == RTC_RYRAREN_ENB)
    {
        RYRAREN1 |= _80_RTC_CALENDER_RYRCNT_YEAR_COMPARE1;
    }

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < RTC_WAITTIME_ARSET; w_count++)
    {
        NOP();
    }

    tmp = RCR1;
    tmp |= _01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
    RTCAIF1 = 0U;   /* clear INTRTCALM1 interrupt flag */
    RTCAMK1 = 0U;   /* enable INTRTCALM1 interrupt */
}


/***********************************************************************************************************************
* Function Name: R_RTC_Set_Alarm0Off
* Description  : This function stop alarm 0.
* Arguments    : None
* Return Value : status -
*                    MD_OK or MD_ERROR
***********************************************************************************************************************/
MD_STATUS R_RTC_Set_Alarm0Off(void)
{
    volatile uint16_t w_count;
    volatile uint8_t tmp;
    MD_STATUS status = MD_OK;

    RTCAIF0 = 0U;   /* clear INTRTCALM0 interrupt flag */
    RTCAMK0 = 0U;   /* enable INTRTCALM0 interrupt */
    tmp = RCR1;
    tmp &= (uint8_t)~_01_RTC_ALARM_ENABLE;
    RCR1 = tmp;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < RTC_WAITTIME_AROFF; w_count++)
    {
        NOP();
    }

    if (_01_RTC_ALARM_ENABLE == (RCR1 & _01_RTC_ALARM_ENABLE))
    {
        status = MD_ERROR;
    }

    RTCAIF0 = 0U;   /* clear INTRTCALM0 interrupt flag */

    return (status);
}
/***********************************************************************************************************************
* Function Name: R_RTC_Set_Alarm1Off
* Description  : This function stop alarm 1.
* Arguments    : None
* Return Value : status -
*                    MD_OK or MD_ERROR
***********************************************************************************************************************/
MD_STATUS R_RTC_Set_Alarm1Off(void)
{
    volatile uint16_t w_count;
    volatile uint8_t tmp;
    MD_STATUS status = MD_OK;

    RTCAIF1 = 0U;   /* clear INTRTCALM1 interrupt flag */
    RTCAMK1 = 0U;   /* enable INTRTCALM1 interrupt */
    tmp = RCR1;
    tmp &= (uint8_t)~_01_RTC_ALARM_ENABLE;
    RCR1 = tmp;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < RTC_WAITTIME_AROFF; w_count++)
    {
        NOP();
    }

    if (_01_RTC_ALARM_ENABLE == (RCR1 & _01_RTC_ALARM_ENABLE))
    {
        status = MD_ERROR;
    }

    RTCAIF1 = 0U;   /* clear INTRTCALM1 interrupt flag */

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_RTC_Set_CalendarAlarm0Value
* Description  : This function write calendar alarm 0 value.
* Arguments    : alarm_val -
*                    calendar alarm 0 value
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Set_CalendarAlarm0Value(rtc_alarm_value_t alarm_val)
{  
    volatile uint8_t tmp;
    volatile uint16_t w_count;

    tmp = RCR1;
    tmp &= (uint8_t)~_01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
    RSECAR0 = alarm_val.alarmws;
    RMINAR0 = alarm_val.alarmwm;
    RHRAR0 = alarm_val.alarmwh;
    RWKAR0 = alarm_val.alarmww;
    RDAYAR0 = alarm_val.alarmwd;
    RMONAR0 = alarm_val.alarmwmt;
    RYRAR0 = alarm_val.alarmwy;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < RTC_WAITTIME_ARSET; w_count++)
    {
        NOP();
    }

    tmp = RCR1;
    tmp |= _01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
}
/***********************************************************************************************************************
* Function Name: R_RTC_Set_CalendarAlarm1Value
* Description  : This function write calendar alarm 1 value.
* Arguments    : alarm_val -
*                    calendar alarm 1 value
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Set_CalendarAlarm1Value(rtc_alarm_value_t alarm_val)
{  
    volatile uint8_t tmp;
    volatile uint16_t w_count;

    tmp = RCR1;
    tmp &= (uint8_t)~_01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
    RSECAR1 = alarm_val.alarmws;
    RMINAR1 = alarm_val.alarmwm;
    RHRAR1 = alarm_val.alarmwh;
    RWKAR1 = alarm_val.alarmww;
    RDAYAR1 = alarm_val.alarmwd;
    RMONAR1 = alarm_val.alarmwmt;
    RYRAR1 = alarm_val.alarmwy;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < RTC_WAITTIME_ARSET; w_count++)
    {
        NOP();
    }

    tmp = RCR1;
    tmp |= _01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
}


/***********************************************************************************************************************
* Function Name: R_RTC_Get_CalendarAlarm0Value
* Description  : This function resd alarm 0 value.
* Arguments    : alarm_val -
*                    calendar alarm 0 value
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Get_CalendarAlarm0Value(rtc_alarm_value_t * const alarm_val)
{
    volatile uint8_t tmp;

    tmp = RCR1;
    tmp &= (uint8_t)~_01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
    alarm_val->alarmws = RSECAR0;
    alarm_val->alarmwm = RMINAR0;
    alarm_val->alarmwh = RHRAR0;
    alarm_val->alarmww = RWKAR0;
    alarm_val->alarmwd = RDAYAR0;
    alarm_val->alarmwmt = RMONAR0;
    alarm_val->alarmwy = RYRAR0;
    tmp = RCR1;
    tmp |= _01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
}
/***********************************************************************************************************************
* Function Name: R_RTC_Get_CalendarAlarm1Value
* Description  : This function resd alarm 1 value.
* Arguments    : alarm_val -
*                    calendar alarm 1 value
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Get_CalendarAlarm1Value(rtc_alarm_value_t * const alarm_val)
{
    volatile uint8_t tmp;

    tmp = RCR1;
    tmp &= (uint8_t)~_01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
    alarm_val->alarmws = RSECAR1;
    alarm_val->alarmwm = RMINAR1;
    alarm_val->alarmwh = RHRAR1;
    alarm_val->alarmww = RWKAR1;
    alarm_val->alarmwd = RDAYAR1;
    alarm_val->alarmwmt = RMONAR1;
    alarm_val->alarmwy = RYRAR1;
    tmp = RCR1;
    tmp |= _01_RTC_ALARM_ENABLE;
    RCR1 = tmp;
}


/***********************************************************************************************************************
* Function Name: R_RTC_Set_ConstPeriodInterruptOn
* Description  : This function enables constant-period interrupt.
* Arguments    : period -
*                    the constant period of INTRTCPRD
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_RTC_Set_ConstPeriodInterruptOn(rtc_int_period_t period)
{
    MD_STATUS status = MD_OK;

    if ((period < SEC1_256) || (period > SEC2S))
    {
        status = MD_ARGERROR;
    }
    else
    {
        RTCRMK = 1U;    /* disable INTRTCPRD interrupt */
        RCR1 = (RCR1 & _09_RTC_CLEAR_PERIOD) | period | _04_RTC_PERIODIC_ENABLE;
        RTCRIF = 0U;    /* clear INTRTCPRD interrupt flag */
        RTCRMK = 0U;    /* enable INTRTCPRD interrupt */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_RTC_Set_ConstPeriodInterruptOff
* Description  : This function disables constant-period interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Set_ConstPeriodInterruptOff(void)
{
    RCR1 = (RCR1 & (uint8_t)~_04_RTC_PERIODIC_ENABLE);
    RTCRIF = 0U;    /* clear INTRTCPRD interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_RTC_Set_RTCOUTOn
* Description  : This function set RTCOUT on.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Set_RTCOUTOn(void)
{
    volatile uint8_t tmp;

    tmp = RCR2;	
    tmp |= _08_RTC_RTCOUT_ENABLE;
    RCR2 = tmp;	
}

/***********************************************************************************************************************
* Function Name: R_RTC_Set_RTCOUTOff
* Description  : This function set RTCOUT off.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Set_RTCOUTOff(void)
{
    volatile uint8_t tmp;

    tmp = RCR2;	
    tmp &= (uint8_t)~_08_RTC_RTCOUT_ENABLE;
    RCR2 = tmp;	
}


/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_RTC_Restart
* Description  : This function restarts RTC counter.
* Arguments    : counter_write_val -
*                    counter write value
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Restart(rtc_counter_value_t counter_write_val)
{
    volatile uint8_t tmp;
    volatile uint16_t w_count;
    
    /* Supply clock to access RTC domain register */
    VRTCEN = 1U;
    
    /* Disable interrupts */
    RTCAMK0 = 1U;	// Alarm interrupt 0
    RTCAIF0 = 0U;
    RTCAMK1 = 1U;	// Alarm interrupt 1
    RTCAIF1 = 0U;
    RTCRMK = 1U;
    RTCRIF = 0U;
    

    /* Stop all counters : START is bit 0 */
    tmp = RCR2;
    tmp &= (uint8_t)~_01_RTC_COUNTER_NORMAL;
    RCR2 = tmp;
	
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_STARTWAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Set control registers */
    tmp = _40_RTC_24HOUR_MODE | _00_RTC_RTCOUT_DISABLE;
    RCR2 = tmp;      
	/* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }      
	/* Set time capture control register 0: exclude capture event */
	tmp = _00_RTC_RTCICN2_DISABLE | _00_RTC_FILTER2_OFF | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR0 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

    /* Set time capture control register 1: exclude capture event */
    tmp = _00_RTC_RTCICN2_DISABLE | _00_RTC_FILTER2_OFF | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR1 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

    /* Set time capture control register 2: exclude capture event */
    tmp = _00_RTC_RTCICN2_DISABLE | _20_RTC_FILTER2_COUNT_ON | _00_RTC_CAPTURE0_NOEVENT; 
    RTCCR2 = tmp;
	/* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Clear TCST */
    tmp = RTCCR0 & (uint8_t)~_04_RTC_EVENT0_DETECTED;
    RTCCR0 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    tmp = RTCCR1 & (uint8_t)~_04_RTC_EVENT1_DETECTED;
    RTCCR1 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    tmp = RTCCR2 & (uint8_t)~_04_RTC_EVENT2_DETECTED;
    RTCCR2 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Set time capture control register 0: exclude capture event */
    tmp = _00_RTC_RTCICN2_DISABLE | _00_RTC_FILTER2_OFF | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR0 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

    /* Set time capture control register 1: exclude capture event */
    tmp = _80_RTC_RTCICN2_ENABLE | _00_RTC_FILTER2_OFF | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR1 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

    /* Set time capture control register 2: exclude capture event */
    tmp = _80_RTC_RTCICN2_ENABLE | _20_RTC_FILTER2_COUNT_ON | _00_RTC_CAPTURE0_NOEVENT; 
    RTCCR2 = tmp;
	/* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Set time capture 0 event */
    tmp = RTCCR0 | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR0 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

    /* Set time capture 1 event */
    tmp = RTCCR1 | _02_RTC_CAPTURE0_FALLING;
    RTCCR1 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

    /* Set time capture 2 event */
    tmp = RTCCR2 | _03_RTC_CAPTURE0_BOTH; 
    RTCCR2 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Set counter values */
    RSECCNT = counter_write_val.sec;
    RMINCNT = counter_write_val.min;
    RHRCNT = counter_write_val.hour;
    RWKCNT = counter_write_val.week;
    RDAYCNT = counter_write_val.day;
    RMONCNT = counter_write_val.month;
    RYRCNT = counter_write_val.year;
    
    /* Read back to make sure value is set */
    for (w_count = 0; w_count < 4; w_count++)
    {
        tmp = RSECCNT;
        tmp = RMINCNT;
        tmp = RHRCNT;
        tmp = RWKCNT;
        tmp = RDAYCNT;
        tmp = RMONCNT;
        tmp = (uint8_t)RYRCNT;
    }
    
    /* Enable PRD interrupt */
    RTCRIF = 0U;    
    RTCRMK = 0U;
    
    /* Enable Alarm 0 interrupt */
    RTCAMK0 = 0U;
    RTCAIF0 = 0U;
    
    /* Enable Alarm 1 interrupt */
    RTCAMK1 = 0U;
    RTCAIF1 = 0U;

    /* Start RTC counting */
    tmp = RCR2;
    tmp |= _01_RTC_COUNTER_NORMAL;
    RCR2 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
}
/***********************************************************************************************************************
* Function Name: R_RTC_RestartTimeCapture0
* Description  : This function restarts RTC counter.
* Arguments    : counter_write_val -
*                    counter write value
* Return Value : None
***********************************************************************************************************************/
void R_RTC_RestartTimeCapture0(void)
{
    volatile uint8_t tmp;
	volatile uint16_t w_count;

    /* Set time capture control register 0: exclude capture event */
    tmp = _00_RTC_RTCICN2_DISABLE | _00_RTC_FILTER2_OFF | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR0 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

    /* Clear TCST */
    tmp = RTCCR0 & (uint8_t)~_04_RTC_EVENT0_DETECTED;
    RTCCR0 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Set time capture control register 0: exclude capture event */
    tmp = _00_RTC_RTCICN2_DISABLE | _00_RTC_FILTER2_OFF | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR0 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Set time capture 0 event */
    tmp = RTCCR0 | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR0 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
}

/***********************************************************************************************************************
* Function Name: R_RTC_RestartTimeCapture1
* Description  : This function restarts RTC counter.
* Arguments    : counter_write_val -
*                    counter write value
* Return Value : None
***********************************************************************************************************************/
void R_RTC_RestartTimeCapture1(void)
{
    volatile uint8_t tmp;
	volatile uint16_t w_count;

    /* Set time capture control register 1: exclude capture event */
    tmp = _00_RTC_RTCICN2_DISABLE | _00_RTC_FILTER2_OFF | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR1 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Clear TCST */
    tmp = RTCCR1 & (uint8_t)~_04_RTC_EVENT0_DETECTED;
    RTCCR1 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

    /* Set time capture control register 1: exclude capture event */
    tmp = _80_RTC_RTCICN2_ENABLE | _00_RTC_FILTER2_OFF | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR1 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

    /* Set time capture 1 event */
    tmp = RTCCR1 | _02_RTC_CAPTURE0_FALLING;
    RTCCR1 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
}

/***********************************************************************************************************************
* Function Name: R_RTC_RestartTimeCapture2
* Description  : This function restarts RTC time capture event.
* Arguments    : counter_write_val -
*                    counter write value
* Return Value : None
***********************************************************************************************************************/
void R_RTC_RestartTimeCapture2(void)
{
    volatile uint8_t tmp;
	volatile uint16_t w_count;

    /* Set time capture control register 2: exclude capture event */
    tmp = _00_RTC_RTCICN2_DISABLE | _20_RTC_FILTER2_COUNT_ON | _00_RTC_CAPTURE0_NOEVENT; 
    RTCCR2 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Clear TCST */
    tmp = RTCCR2 & (uint8_t)~_04_RTC_EVENT0_DETECTED;
    RTCCR2 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Set time capture control register 2: exclude capture event */
    tmp = _80_RTC_RTCICN2_ENABLE | _20_RTC_FILTER2_COUNT_ON | _00_RTC_CAPTURE0_NOEVENT; 
    RTCCR2 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

    /* Set time capture 2 event */
    tmp = RTCCR2 | _03_RTC_CAPTURE0_BOTH; 
    RTCCR2 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
}

/******************************************************************************
* Function Name: R_RTC_Get_TimeCapture0Value
* Description  : Get RTC time capture value of input channel 0
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_RTC_Get_TimeCapture0Value(rtc_capture_value_t * const counter_read_val)
{
    volatile uint8_t tmp;
	volatile uint16_t w_count;

    /* Set time capture 0 event */
    tmp = RTCCR0 | _00_RTC_CAPTURE0_NOEVENT;
    RTCCR0 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Read counter */
    counter_read_val->capturesec 	= RSECCP0;
    counter_read_val->capturemin 	= RMINCP0;
    if ((RCR2 & 0x40) == 0x40)
    {
        counter_read_val->capturehour  	= RHRCP0 & 0xBF;
    }
    else
    {
       counter_read_val->capturehour  	= RHRCP0; 
    }
    
    counter_read_val->captureday 	= RDAYCP0;
    counter_read_val->capturemonth 	= RMONCP0;

    /* Set time capture 0 event */
    tmp = RTCCR0 | _03_RTC_CAPTURE0_BOTH;
    RTCCR0 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }

}

/******************************************************************************
* Function Name: R_RTC_Get_TimeCapture1Value
* Description  : Get RTC time capture value of input channel 1
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_RTC_Get_TimeCapture1Value(rtc_capture_value_t * const counter_read_val)
{
    volatile uint8_t tmp;

    /* Set time capture 0 event */
//	tmp = RTCCR1 | _00_RTC_CAPTURE0_NOEVENT;
//	RTCCR1 = tmp;
    /* Change the waiting time according to the system */
//	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
//    {
//    	NOP();
//    }
    /* Read counter */
    counter_read_val->capturesec 	= RSECCP1;
    counter_read_val->capturemin 	= RMINCP1;
    if ((RCR2 & 0x40) == 0x40)
    {
        counter_read_val->capturehour  	= RHRCP1 & 0xBF;
    }
    else
    {
       counter_read_val->capturehour  	= RHRCP1;
    }
    counter_read_val->captureday 	= RDAYCP1;
    counter_read_val->capturemonth 	= RMONCP1;

    /* Set time capture 0 event */
//	tmp = RTCCR1 | _03_RTC_CAPTURE0_BOTH;
//	RTCCR1 = tmp;
    /* Change the waiting time according to the system */
//	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
//    {
//    	NOP();
//    }
}

/******************************************************************************
* Function Name: R_RTC_Get_TimeCapture2Value
* Description  : Get RTC time capture value of input channel 2
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_RTC_Get_TimeCapture2Value(rtc_capture_value_t * const counter_read_val)
{
    volatile uint8_t tmp;

    /* Set time capture 0 event */
//	tmp = RTCCR2 | _00_RTC_CAPTURE0_NOEVENT;
//	RTCCR2 = tmp;
//	while ((RTCCR2 & (uint8_t)~_04_RTC_EVENT0_NOTDETECTED) != (tmp & (uint8_t)~_04_RTC_EVENT0_NOTDETECTED));

    counter_read_val->capturesec 	= RSECCP2;
    counter_read_val->capturemin 	= RMINCP2;
    if ((RCR2 & 0x40) == 0x40)
    {
        counter_read_val->capturehour  	= RHRCP2 & 0xBF;
    }
    else
    {
       counter_read_val->capturehour  	= RHRCP2;
    }
    counter_read_val->captureday 	= RDAYCP2;
    counter_read_val->capturemonth 	= RMONCP2;

    /* Set time capture 0 event */
//	tmp = RTCCR2 | _03_RTC_CAPTURE0_BOTH;
//	RTCCR2 = tmp;
    /* Change the waiting time according to the system */
//	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
//    {
//    	NOP();
//    }
}
/******************************************************************************
* Function Name: uint16_t R_RTC_Get_RADJ_Waittime(void)
* Note         : THIS FUNCTION STRICTLY DEPEND ON THE MCU
*              : BELOW IMPLEMENTATION IS USED FOR RL78I1B ONLY
*              : WHEN CHANGE TO OTHER MCU, PLEASE RE-IMPLEMENT THIS FUNCTION
* Description  : 
* Arguments    : 
* Return Value : None
******************************************************************************/
uint16_t R_RTC_Get_RADJ_Waittime(void)
{   
    uint16_t waittime;

    switch (HOCODIV)
    {
        case 0: /*IS_MCU_RUN_AT_24MHZ*/
            waittime = RTC_RADJWAITTIME_24;
            break;
        case 1:/* IS_MCU_RUN_AT_12MHZ */
            waittime = RTC_RADJWAITTIME_12;
            break;
        case 2:/* IS_MCU_RUN_AT_06MHZ */
            waittime = RTC_RADJWAITTIME_06;
            break;
        case 3:/* IS_MCU_RUN_AT_03MHZ */
            waittime = RTC_RADJWAITTIME_03;
            break;
        default:
            waittime = RTC_RADJWAITTIME_24;
            break;
    }
    return waittime;
}
/******************************************************************************
* Function Name: R_RTC_Compensate
* Description  : This function compensate the error on sub-clock by a provided ppm
* Arguments    : float ppm: ppm error of sub-clock crystal
* Return Value : None
*******************************************************************************/
void R_RTC_Compensate(float32_t ppm)
{
    volatile uint8_t tmp;
	volatile uint16_t w_count;
    volatile uint16_t waittime;
    float32_t abs_ppm = ABS(ppm);
    uint8_t radj_reg = 0;
    
    /* Supply clock to access RTC domain register */
    VRTCEN = 1U;

    /* Clear adjustment first : PMADJ bit [7:6] */
    while ((RADJ & _C0_RTC_TIMER_ERROR_ADJUST_ALL) != 0)
    {
        RADJ &= (uint8_t)~_C0_RTC_TIMER_ERROR_ADJUST_ALL;
    }
    
    /* Enable automatic adj : AADJE bit 4 */
    tmp = RCR2;
    tmp |= _10_RTC_ADJUSTMENT_ENABLE;
    RCR2 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    
    /* Enable sub or add */
    if (ppm > 0.0f)
    {
        radj_reg |= _80_RTC_TIMER_ERROR_ADJUST_MINUS;       /* sub */
    }
    else
    {
        radj_reg |= _40_RTC_TIMER_ERROR_ADJUST_PLUS;        /* add */
    }
    
    tmp = RCR2;
    if (abs_ppm <= 32.043f)         /* 1 minutes adjustment */
    {
        tmp &= (uint8_t)~_20_RTC_CALENDER_10SECONDS;    
        radj_reg |= ( (uint8_t)(abs_ppm * (32768.0f * 60.0f / 1e6) + 0.5f) ) & 0x3F;
    }
    else if (abs_ppm <= 192.26f)    /* 10-second adjustment */
    {
        tmp |= _20_RTC_CALENDER_10SECONDS;    
        radj_reg |= ( (uint8_t)(abs_ppm * (32768.0f * 10.0f / 1e6) + 0.5f) ) & 0x3F;
    }
    else
    {
        /* Out of control !! no adj at all */
        tmp &= (uint8_t)~(_20_RTC_CALENDER_10SECONDS | _10_RTC_ADJUSTMENT_ENABLE);
        radj_reg = 0;
    }
    
    RCR2 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    waittime = R_RTC_Get_RADJ_Waittime();
    RADJ = radj_reg;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= waittime; w_count++)
    {
		NOP();
    }   
}

/******************************************************************************
* Function Name: R_RTC_StopCompensation
* Description  : Stop the rtc compensation 
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_RTC_StopCompensation(void)
{
    volatile uint8_t tmp;
	volatile uint16_t w_count;
    volatile uint16_t waittime;
    
    /* Supply clock to access RTC domain register */
    VRTCEN = 1U;
    
    /* AADJE bit 4, AADJP is bit 5 */
    tmp = RCR2;
    tmp &= (uint8_t)~(_20_RTC_CALENDER_10SECONDS | _10_RTC_ADJUSTMENT_ENABLE);
    RCR2 = tmp;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= RTC_WAITTIME; w_count++)
    {
    	NOP();
    }
    waittime = R_RTC_Get_RADJ_Waittime();
    RADJ = 0;
    /* Change the waiting time according to the system */
	for (w_count = 0U; w_count <= waittime; w_count++)
    {
        NOP();
    }
}
/* End user code. Do not edit comment generated here */
