/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class03.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS03_H
#define R_DLMS_USERCODE_CLASS03_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class03.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/* Index: 00; Name: Cumulative Energy kVAh Export; Logical name: 1.0.10.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 01; Name: Cumulative Energy kWh Export; Logical name: 1.0.2.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 02; Name: Cumulative power ON ; Logical name: 0.0.94.91.14.255 */
/* Attribute 02 */
#define  CLASS03_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 03; Name: Neutral current rms; Logical name: 1.0.91.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 04; Name: Active Power  ; Logical name: 1.0.1.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 05; Name: Apparent Power; Logical name: 1.0.9.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 06; Name: Cumulative Energy kVAh; Logical name: 1.0.9.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 07; Name: Cumulative Energy kWh; Logical name: 1.0.1.8.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 08; Name: Frequency; Logical name: 1.0.14.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 09; Name: Phase current rms; Logical name: 1.0.11.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 10; Name: Signed Power Factor; Logical name: 1.0.13.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 11; Name: Voltage rms; Logical name: 1.0.12.7.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 12; Name: Average voltage average of integration period; Logical name: 1.0.12.27.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 13; Name: AverageCurrent average of integration period; Logical name: 1.0.11.27.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 14; Name: AvgPF For Billing; Logical name: 1.0.13.0.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 15; Name: Billing date; Logical name: 0.0.0.1.2.255 */
/* Attribute 02 */
#define  CLASS03_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 16; Name: Block Energy kVAh; Logical name: 1.0.9.29.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 17; Name: Block Energy kVAh Export; Logical name: 1.0.10.29.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 18; Name: Block Energy kWh; Logical name: 1.0.1.29.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ18_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ18_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 19; Name: Block Energy kWh Export; Logical name: 1.0.2.29.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ19_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ19_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 20; Name: Cumulative Energy kVAh TZ1; Logical name: 1.0.9.8.1.255 */
/* Attribute 02 */
#define  CLASS03_OBJ20_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ20_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 21; Name: Cumulative Energy kVAh TZ2; Logical name: 1.0.9.8.2.255 */
/* Attribute 02 */
#define  CLASS03_OBJ21_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ21_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 22; Name: Cumulative Energy kWh TZ3; Logical name: 1.0.1.8.3.255 */
/* Attribute 02 */
#define  CLASS03_OBJ22_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ22_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 23; Name: Cumulative Energy kVAh TZ3; Logical name: 1.0.9.8.3.255 */
/* Attribute 02 */
#define  CLASS03_OBJ23_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ23_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 24; Name: Cumulative Energy kVAh TZ4; Logical name: 1.0.9.8.4.255 */
/* Attribute 02 */
#define  CLASS03_OBJ24_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ24_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 25; Name: Cumulative Energy kWh TZ1 ; Logical name: 1.0.1.8.1.255 */
/* Attribute 02 */
#define  CLASS03_OBJ25_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ25_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 26; Name: Cumulative Energy kWh TZ2; Logical name: 1.0.1.8.2.255 */
/* Attribute 02 */
#define  CLASS03_OBJ26_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ26_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 27; Name: Cumulative Energy kWh TZ4; Logical name: 1.0.1.8.4.255 */
/* Attribute 02 */
#define  CLASS03_OBJ27_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ27_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 28; Name: Current rms; Logical name: 1.0.94.91.14.255 */
/* Attribute 02 */
#define  CLASS03_OBJ28_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ28_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 29; Name: Total billing power ON duration; Logical name: 0.0.94.91.13.255 */
/* Attribute 02 */
#define  CLASS03_OBJ29_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ29_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 30; Name: Cumulative Energy kWh ; Logical name: 1.0.1.9.0.255 */
/* Attribute 02 */
#define  CLASS03_OBJ30_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ30_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 31; Name: Cumulative Energy kWh TZ5; Logical name: 1.0.1.8.5.255 */
/* Attribute 02 */
#define  CLASS03_OBJ31_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ31_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 32; Name: Cumulative energy kWh TZ6; Logical name: 1.0.1.8.6.255 */
/* Attribute 02 */
#define  CLASS03_OBJ32_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ32_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 33; Name: Cumulative energy kVAh TZ5; Logical name: 1.0.9.8.5.255 */
/* Attribute 02 */
#define  CLASS03_OBJ33_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ33_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 34; Name: Cumulative energy kVAh TZ6; Logical name: 1.0.9.8.6.255 */
/* Attribute 02 */
#define  CLASS03_OBJ34_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS03_OBJ34_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const scaler_unit_t g_dlms_ic03_obj00_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj01_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj02_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj03_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj04_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj05_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj06_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj07_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj08_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj09_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj10_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj11_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj12_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj13_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj14_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj15_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj16_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj17_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj18_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj19_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj20_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj21_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj22_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj23_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj24_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj25_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj26_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj27_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj28_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj29_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj30_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj31_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj32_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj33_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic03_obj34_att03_Scaler_Unit;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic03_obj00_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj00_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj01_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj01_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj02_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj02_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj03_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj03_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj04_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj04_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj05_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj05_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj06_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj06_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj07_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj07_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj08_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj08_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj09_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj09_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj10_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj10_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj11_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj11_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj12_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj12_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj13_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj13_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj14_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj14_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj15_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj15_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj16_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj16_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj17_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj17_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj18_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj18_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj19_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj19_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj20_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj20_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj21_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj21_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj22_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj22_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj23_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj23_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj24_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj24_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj25_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj25_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj26_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj26_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj27_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj27_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj28_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj28_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj29_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj29_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj30_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj30_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj31_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj31_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj32_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj32_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj33_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj33_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj34_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic03_obj34_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);

#endif /* R_DLMS_USERCODE_CLASS03_H */