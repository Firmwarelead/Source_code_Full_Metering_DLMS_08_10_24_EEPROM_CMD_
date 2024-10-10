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
* File Name    : r_cg_12adc.h
* Version      : Code Generator for RL78/L1A V1.01.03.01 [17 May 2019]
* Device(s)    : R5F11MPG
* Tool-Chain   : CCRL
* Description  : This file implements device driver for ADC module.
* Creation Date: 8/25/2020
***********************************************************************************************************************/
#ifndef ADC_H
#define ADC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    A/D Control Register (ADCSR) 
*/
/* A/D conversion operation control (ADST) */
#define _0000_AD_CONVERSION_DISABLE                     (0x0000U) /* stops A/D conversion process */
#define _8000_AD_CONVERSION_ENABLE                      (0x8000U) /* starts A/D conversion process */
/* Scan mode select bit (ADCS) */
#define _0000_AD_SCAN_MODE_SINGLE                       (0x0000U) /* single scan mode */
#define _4000_AD_SCAN_MODE_CONTINUOUS                   (0x4000U) /* continuous scan mode */
/* Scan end interrupt enable bit (ADIE) */
#define _0000_AD_INTAD_DISABLE                          (0x0000U) /* disables INTAD generation upon scan completion */
#define _1000_AD_INTAD_ENABLE                           (0x1000U) /* enables INTAD  generation upon scan completion */
/* A/D conversion select bit (ADHSC) */
#define _0000_AD_CONVERSION_HIGH_SPEED                  (0x0000U) /* high-speed conversion */
#define _0400_AD_CONVERSION_NORMAL                      (0x0400U) /* normal conversion */
/* Trigger start enable bit (TRGE) */
#define _0000_AD_TRIGGER_CONVERSION_DISABLE             (0x0000U) /* disables A/D conversion to be started by trigger */
#define _0200_AD_TRIGGER_CONVERSION_ENABLE              (0x0200U) /* enables A/D conversion to be started by trigger */
/* Trigger select bit (EXTRG) */
#define _0000_AD_SYNCHRONOUS_TRIGGER                    (0x0000U) /* A/D conversion is started by synchronous trigger */
#define _0100_AD_ASYNCHRONOUS_TRIGGER                   (0x0100U) /* A/D conversion is started by asynchronous trigger */

/*
    A/D channel select register A0 (ADANSA0) 
*/
/* A/D conversion channel select bit 5 (ANSA05) */
#define _0000_AD_ANI5_NOT_SUBJECT                 (0x0000U) /* ANI5 is not subjected to conversion */
#define _0020_AD_ANI5_SUBJECT                     (0x0020U) /* ANI5 is subjected to conversion */
/* A/D conversion channel select bit 4 (ANSA04) */
#define _0000_AD_ANI4_NOT_SUBJECT                 (0x0000U) /* ANI4 is not subjected to conversion */
#define _0010_AD_ANI4_SUBJECT                     (0x0010U) /* ANI4 is subjected to conversion */
/* A/D conversion channel select bit 3 (ANSA03) */
#define _0000_AD_ANI3_NOT_SUBJECT                 (0x0000U) /* ANI3 is not subjected to conversion */
#define _0008_AD_ANI3_SUBJECT                     (0x0008U) /* ANI3 is subjected to conversion */
/* A/D conversion channel select bit 2 (ANSA02) */
#define _0000_AD_ANI2_NOT_SUBJECT                 (0x0000U) /* ANI2 is not subjected to conversion */
#define _0004_AD_ANI2_SUBJECT                     (0x0004U) /* ANI2 is subjected to conversion */
/* A/D conversion channel select bit 1 (ANSA01) */
#define _0000_AD_ANI1_NOT_SUBJECT                 (0x0000U) /* ANI1 is not subjected to conversion */
#define _0002_AD_ANI1_SUBJECT                     (0x0002U) /* ANI1 is subjected to conversion */
/* A/D conversion channel select bit 0 (ANSA00) */
#define _0000_AD_ANI0_NOT_SUBJECT                 (0x0000U) /* ANI0 is not subjected to conversion */
#define _0001_AD_ANI0_SUBJECT                     (0x0001U) /* ANI0 is subjected to conversion */

/*
    A/D-converted value addition/average function channel select register 0 (ADADS0) 
*/
/* A/D-converted value addition/average channel 5 select (ADS05) */
#define _0000_AD_ANI5_NOT_ADD_AVERAGE             (0x0000U) /* ANI5 is not selected addition/average mod */
#define _0020_AD_ANI5_ADD_AVERAGE                 (0x0020U) /* ANI5 is selected addition/average mod */
/* A/D-converted value addition/average channel 4 select (ADS04) */
#define _0000_AD_ANI4_NOT_ADD_AVERAGE             (0x0000U) /* ANI4 is not selected addition/average mod */
#define _0010_AD_ANI4_ADD_AVERAGE                 (0x0010U) /* ANI4 is selected addition/average mod */
/* A/D-converted value addition/average channel 3 select (ADS03) */
#define _0000_AD_ANI3_NOT_ADD_AVERAGE             (0x0000U) /* ANI3 is not selected addition/average mod */
#define _0008_AD_ANI3_ADD_AVERAGE                 (0x0008U) /* ANI3 is selected addition/average mod */
/* A/D-converted value addition/average channel 2 select (ADS02) */
#define _0000_AD_ANI2_NOT_ADD_AVERAGE             (0x0000U) /* ANI2 is not selected addition/average mod */
#define _0004_AD_ANI2_ADD_AVERAGE                 (0x0004U) /* ANI2 is selected addition/average mod */
/* A/D-converted value addition/average channel 1 select (ADS01) */
#define _0000_AD_ANI1_NOT_ADD_AVERAGE             (0x0000U) /* ANI1 is not selected addition/average mod */
#define _0002_AD_ANI1_ADD_AVERAGE                 (0x0002U) /* ANI1 is selected addition/average mod */
/* A/D-converted value addition/average channel 0 select (ADS00) */
#define _0000_AD_ANI0_NOT_ADD_AVERAGE             (0x0000U) /* ANI0 is not selected addition/average mod */
#define _0001_AD_ANI0_ADD_AVERAGE                 (0x0001U) /* ANI0 is selected addition/average mod */

/*
    A/D-converted Value Addion/Average Count Select Register (ADADC) 
*/
/* Average mode enable bit (AVEE) */
#define _00_AD_MODE_ADDITION                            (0x00U) /* addition mode is selected */
#define _80_AD_MODE_AVERAGE                             (0x80U) /* average mode is selected */
/* Addition count select bit (ADC) */
#define _00_AD_CONVERSION_1TIME                         (0x00U) /* 1-time conversion (no addition; same as normal conversion) */
#define _01_AD_CONVERSION_2TIME                         (0x01U) /* 2-time conversion (addition once) */
#define _02_AD_CONVERSION_3TIME                         (0x02U) /* 3-time conversion (addition twice) */
#define _03_AD_CONVERSION_4TIME                         (0x03U) /* 4-time conversion (addition three times) */
#define _05_AD_CONVERSION_16TIME                        (0x05U) /* 16-time conversion (addition 15 times) */

/*
    A/D Control Extended Register (ADCER) 
*/
/* A/D data register format select bit (ADRFMT) */
#define _0000_AD_DATA_FLUSH_RIGHT                       (0x0000U) /* flush-right is selected for the A/D data register format */
#define _8000_AD_DATA_FLUSH_LEFT                        (0x8000U) /* flush-left is selected for the A/D data register format */
/* Self-diagnosis enable bit (DIAGM) */
#define _0000_AD_SELF_DIAGNOSIS_DISABLE                 (0x0000U) /* disables self-diagnosis of 12-bit A/D converter. */
#define _0800_AD_SELF_DIAGNOSIS_ENABLE                  (0x0800U) /* enables self-diagnosis of 12-bit A/D converter. */
/* Self-diagnosis mode select bit (DIAGLD) */
#define _0000_AD_SELF_DIAGNOSIS_ROTATION                (0x0000U) /* rotation mode for self-diagnosis voltage */
#define _0400_AD_SELF_DIAGNOSIS_FIXED                   (0x0400U) /* fixed mode for self-diagnosis voltage */
/* Self-diagnosis conversion voltage select bit (DIAGVAL) */
#define _0100_AD_SELF_DIAGNOSIS_0_V                     (0x0100U) /* uses the voltage of 0 V for self-diagnosis */
#define _0200_AD_SELF_DIAGNOSIS_1_2_V                   (0x0200U) /* uses the voltage of reference power supply × 1/2 for self-diagnosis */
#define _0300_AD_SELF_DIAGNOSIS_REF_V                   (0x0300U) /* uses the voltage of reference power supply for self-diagnosis. */
/* A/D data register automatic clearing enable bit (ACE) */
#define _0000_AD_AUTO_CLEAR_DISABLE                     (0x0000U) /* disables automatic clearing */
#define _0020_AD_AUTO_CLEAR_ENABLE                      (0x0020U) /* enables automatic clearing */

/*
    A/D Conversion Start Trigger Select Register (ADSTRGR) 
*/
/* A/D conversion start trigger select bit (TRSA5,TRSA4,TRSA3,TRSA2,TRSA1,TRSA0) */
#define _0000_AD_TRIGGER_ADTRG                          (0x0000U) /* external trigger input pin (ADTRG) */
#define _3000_AD_TRIGGER_ELCTRG0                        (0x3000U) /* event output signal from event link controller (ELCTRG0) */
#define _3F00_AD_TRIGGER_SOURCE                         (0x3F00U) /* trigger source deselection */

/*
    A/D Conversion Extended Input Control Register (ADEXICR) 
*/
/* Internal reference voltage A/D conversion select bit (OCSA) */
#define _0000_AD_REF_VOLTAGE_DISABLE                    (0x0000U) /* A/D conversion of internal reference voltage is not performed */
#define _0200_AD_REF_VOLTAGE_ENABLE                     (0x0200U) /* A/D conversion of internal reference voltage is performed */
/* Temperature sensor output A/D conversion select bit (TSSA) */
#define _0000_AD_TEMPERATURE_DISABLE                    (0x0000U) /* A/D conversion of temperature sensor output is not performed */
#define _0100_AD_TEMPERATURE_ENABLE                     (0x0100U) /* A/D conversion of temperature sensor output is performed */
/* Internal reference voltage A/D-converted value addition/average mode select bit (OCSAD) */
#define _0000_AD_REF_ADD_AVERAGE_DISABLE                (0x0000U) /* internal reference voltage A/D-converted value addition/average mode is not selected */
#define _0002_AD_REF_ADD_AVERAGE_ENABLE                 (0x0002U) /* internal reference voltage A/D-converted value addition/average mode is selected */
/* Temperature sensor output A/D-converted value addition/average mode select (TSSAD) */
#define _0000_AD_TEMPERATURE_ADD_AVERAGE_DISABLE        (0x0000U) /* temperature sensor output A/D-converted value addition/average mode is not selected. */
#define _0001_AD_TEMPERATURE_ADD_AVERAGE_ENABLE         (0x0001U) /* temperature sensor output A/D-converted value addition/average mode is selected. */

/*
    A/D sample-and-hold circuit control register (ADSHCR) 
*/
/* ANI2 channel-dedicated sample-and-hold circuit bypass select bit (SHANS2) */
#define _0000_AD_ANI2_SAMPLE_HOLD_BYPASS          (0x0000U) /* bypass the dedicated sample-and-hold circuits */
#define _0400_AD_ANI2_SAMPLE_HOLD_USE             (0x0400U) /* use the dedicated sample-and-hold circuits */
/* ANI1 channel-dedicated sample-and-hold circuit bypass select bit (SHANS1) */
#define _0000_AD_ANI1_SAMPLE_HOLD_BYPASS          (0x0000U) /* bypass the dedicated sample-and-hold circuits */
#define _0200_AD_ANI1_SAMPLE_HOLD_USE             (0x0200U) /* use the dedicated sample-and-hold circuits */
/* ANI0 channel-dedicated sample-and-hold circuit bypass select bit (SHANS0) */
#define _0000_AD_ANI0_SAMPLE_HOLD_BYPASS          (0x0000U) /* bypass the dedicated sample-and-hold circuits */
#define _0100_AD_ANI0_SAMPLE_HOLD_USE             (0x0100U) /* use the dedicated sample-and-hold circuits */

/*
    A/D high-potential/how-potential reference voltage control register (ADHVREFCNT) 
*/
/* Sleep bit (ADSLP) */
#define _00_AD_SLEEP_NORMAL                             (0x00U) /* normal operation */
#define _80_AD_SLEEP_STANDBY                            (0x80U) /* standby state */
/* Low-potential reference voltage select bit (LVSEL) */
#define _00_AD_LOW_REF_AVSS1                      (0x00U) /* selects AVSS1 as low-potential reference voltage */
#define _10_AD_LOW_REF_AVREFM                           (0x10U) /* AVREFM is selected as the low-potential reference voltage */
/* High-potential reference voltage select bit (HVSEL1,HVSEL0) */
#define _00_AD_HIGH_REF_AVDD                            (0x00U) /* AVDD is selected as the high-potential reference voltage */
#define _01_AD_HIGH_REF_AVREFP_VREFOUT                  (0x01U) /* AVREFP or VREFOUT is selected as the high-potential reference voltage */
#define _02_AD_HIGH_REF_VBGR                            (0x02U) /* VBGR is selected as the high-potential reference voltage. */
#define _03_AD_HIGH_REF_DISCHARGE                       (0x03U) /* discharges the internal reference voltage (the high-potential reference voltage is not selected) */

/*
    A/D Conversion Clock Control Register (ADCKS) 
*/
/* A/D conversion clock select bit (ADCKS1,ADCKS0) */
#define _00_AD_CLK_NOT_DIVIDED                          (0x00U) /* system clock not divided (f1) */
#define _01_AD_CLK_DIVIDED_2                            (0x01U) /* system clock divided by 2 (f2) */
#define _02_AD_CLK_DIVIDED_4                            (0x02U) /* system clock divided by 4 (f4) */
#define _03_AD_CLK_DIVIDED_8                            (0x03U) /* system clock divided by 8 (f8) */

/*
    Voltage reference control register (VREFAMPCNT) 
*/
/* BGR enable (BGREN) */
#define _00_AD_BGR_OFF                            (0x00U) /* the power supply for the BGR block is turned off */
#define _10_AD_BGR_ON                             (0x10U) /* the power supply for the BGR block is turned on */
/* VREFADCG enable (VREFADCEN) */
#define _00_AD_HIGH_REF_AVREFP                    (0x00U) /* select AVREFP as the high-potential reference voltage */
#define _08_AD_HIGH_REF_VREFOUT                   (0x08U) /* select VREFOUT as the high-potential reference voltage */
/* VREFOUT output voltage control (VREFADCG1, VREFADCG0) */
#define _00_AD_VREFOUT_1_5                        (0x00U) /* 1.5 V */
#define _04_AD_VREFOUT_2_0                        (0x04U) /* 2.0 V */
#define _06_AD_VREFOUT_2_5                        (0x06U) /* 2.5 V */
/* OLDET enable (OLDETEN) */
#define _00_AD_OVERCURRENT_DISABLE                (0x00U) /* disable detection of overcurrents */
#define _01_AD_OVERCURRENT_ENABLE                 (0x01U) /* enable detection of overcurrents */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _001A_AD_SAMPLE_HOLD_VALUE                (0x001AU) /* sample-and-hold circuit sampling time setting bit */
#define _08_AD_SAMPLE_STATE_TEMPERATURE_VALUE     (0x08U) /* A/D sampling state register T */
#define _F0_AD_SAMPLE_STATE_T_VALUE                     (0xF0U) /* A/D sampling state register T */
#define _0000_AD_ADANSA0_GUI_VALUE                      (0x0000U)
#define _0100_AD_ADEXICR_GUI_VALUE                      (0x0100U)
#define CLEAR_SLEEP_WAITTIME                      (13U) /* change the waiting time according to the system */
#define DISCHARGE_WAITTIME                        (2U) /* change the waiting time according to the system */
#define BRG_WAITTIME                              (400U) /* change the waiting time according to the system */
#define VREFAMP_WAITTIME                          (4000U) /* change the waiting time according to the system */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    ADCHANNEL0,
    ADCHANNEL1,
    ADCHANNEL2,
    ADCHANNEL3,
    ADCHANNEL4,
    ADCHANNEL5,
    ADINTERREFVOLT,
    ADTEMPERSENSOR
} ad_channel_t;

typedef enum
{
    SEL_ADANSA0,
    SEL_ADEXICR
} ad_sel_registers_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_12ADC_Create(void);
void R_12ADC_Start(void);
void R_12ADC_Stop(void);
MD_STATUS R_12ADC_Get_ValueResult(ad_channel_t channel, uint16_t * const buffer);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
