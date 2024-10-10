/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class01.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS01_H
#define R_DLMS_USERCODE_CLASS01_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class01.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/* Index: 00; Name: Cumulative billing count; Logical name: 0.0.0.1.0.255 */
/* Attribute 02 */
#define  CLASS01_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 01; Name: Cumulative programming count ; Logical name: 0.0.96.2.0.255 */
/* Attribute 02 */
#define  CLASS01_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 02; Name: Cumulative tamper count; Logical name: 0.0.94.91.0.255 */
/* Attribute 02 */
#define  CLASS01_OBJ02_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ02_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 03; Name: Current rating; Logical name: 0.0.94.91.12.255 */
/* Attribute 02 */
#define  CLASS01_OBJ03_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ03_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 04; Name: Firmware version for meter; Logical name: 1.0.0.2.0.255 */
/* Attribute 02 */
#define  CLASS01_OBJ04_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ04_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 05; Name: Logical Device Name; Logical name: 0.0.42.0.0.255 */
/* Attribute 02 */
#define  CLASS01_OBJ05_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ05_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 06; Name: Manufacture Name; Logical name: 0.0.96.1.1.255 */
/* Attribute 02 */
#define  CLASS01_OBJ06_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ06_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 07; Name: Meter category; Logical name: 0.0.94.91.11.255 */
/* Attribute 02 */
#define  CLASS01_OBJ07_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ07_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 08; Name: Meter serial number; Logical name: 0.0.96.1.0.255 */
/* Attribute 02 */
#define  CLASS01_OBJ08_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ08_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 09; Name: Meter Type; Logical name: 0.0.94.91.9.255 */
/* Attribute 02 */
#define  CLASS01_OBJ09_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ09_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 10; Name: Meter Year of Manufacture; Logical name: 0.0.96.1.4.255 */
/* Attribute 02 */
#define  CLASS01_OBJ10_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ10_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 11; Name: DeviceID; Logical name: 0.0.96.1.2.255 */
/* Attribute 02 */
#define  CLASS01_OBJ11_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ11_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 12; Name: Available Billing Count; Logical name: 0.0.0.1.1.255 */
/* Attribute 02 */
#define  CLASS01_OBJ12_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ12_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 13; Name: Daily load capture period; Logical name: 1.0.0.8.5.255 */
/* Attribute 02 */
#define  CLASS01_OBJ13_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ13_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 14; Name: ESW; Logical name: 0.0.94.91.18.255 */
/* Attribute 02 */
#define  CLASS01_OBJ14_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ14_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 15; Name: Event code object Controll event; Logical name: 0.0.96.11.6.255 */
/* Attribute 02 */
#define  CLASS01_OBJ15_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ15_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 16; Name: Event code object current; Logical name: 0.0.96.11.1.255 */
/* Attribute 02 */
#define  CLASS01_OBJ16_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ16_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 17; Name: Event code object Non_Roller; Logical name: 0.0.96.11.5.255 */
/* Attribute 02 */
#define  CLASS01_OBJ17_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ17_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 18; Name: Event code object Other; Logical name: 0.0.96.11.4.255 */
/* Attribute 02 */
#define  CLASS01_OBJ18_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ18_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 19; Name: Event code object power; Logical name: 0.0.96.11.2.255 */
/* Attribute 02 */
#define  CLASS01_OBJ19_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ19_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 20; Name: Event code object Trans; Logical name: 0.0.96.11.3.255 */
/* Attribute 02 */
#define  CLASS01_OBJ20_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ20_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 21; Name: Event code object voltage; Logical name: 0.0.96.11.0.255 */
/* Attribute 02 */
#define  CLASS01_OBJ21_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ21_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 22; Name: Block load capture period ; Logical name: 1.0.0.8.4.255 */
/* Attribute 02 */
#define  CLASS01_OBJ22_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ22_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 23; Name: Current balance amount; Logical name: 0.0.94.96.24.255 */
/* Attribute 02 */
#define  CLASS01_OBJ23_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ23_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 24; Name: Current balance time; Logical name: 0.0.94.96.25.255 */
/* Attribute 02 */
#define  CLASS01_OBJ24_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ24_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 25; Name: Demand integration period ; Logical name: 1.0.0.8.0.255 */
/* Attribute 02 */
#define  CLASS01_OBJ25_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ25_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 26; Name: ESWF; Logical name: 0.0.94.91.26.255 */
/* Attribute 02 */
#define  CLASS01_OBJ26_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ26_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 27; Name: Last Token Recharge amount; Logical name: 0.0.94.96.21.255 */
/* Attribute 02 */
#define  CLASS01_OBJ27_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ27_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 28; Name: Last Token Recharge time; Logical name: 0.0.94.96.22.255 */
/* Attribute 02 */
#define  CLASS01_OBJ28_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ28_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 29; Name: Metering Mode; Logical name: 0.0.94.96.19.255 */
/* Attribute 02 */
#define  CLASS01_OBJ29_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ29_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 30; Name: Payment Mode; Logical name: 0.0.94.96.20.255 */
/* Attribute 02 */
#define  CLASS01_OBJ30_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ30_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 31; Name: Total amount at last recharge; Logical name: 0.0.94.96.23.255 */
/* Attribute 02 */
#define  CLASS01_OBJ31_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ31_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 32; Name: SMO 1; Logical name: 0.0.96.13.0.255 */
/* Attribute 02 */
#define  CLASS01_OBJ32_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ32_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 33; Name: SMO2; Logical name: 0.0.96.13.1.255 */
/* Attribute 02 */
#define  CLASS01_OBJ33_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ33_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/* Index: 34; Name: MR invocation counter; Logical name: 0.0.43.1.2.255 */
/* Attribute 02 */
#define  CLASS01_OBJ34_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ34_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 35; Name: US invocation counter; Logical name: 0.0.43.1.3.255 */
/* Attribute 02 */
#define  CLASS01_OBJ35_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ35_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 36; Name: Push invocation counter; Logical name: 0.0.43.1.4.255 */
/* Attribute 02 */
#define  CLASS01_OBJ36_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ36_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 37; Name: FWU invocation counter; Logical name: 0.0.43.1.5.255 */
/* Attribute 02 */
#define  CLASS01_OBJ37_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ37_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 38; Name: Active relay time object; Logical name: 1.0.96.128.25.255 */
/* Attribute 02 */
#define  CLASS01_OBJ38_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ38_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 39; Name: Passive relay time; Logical name: 1.0.96.128.30.255 */
/* Attribute 02 */
#define  CLASS01_OBJ39_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS01_OBJ39_ATTR02_SET_USERFUNCTION_ENABLE                  (TRUE)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const uint8_t g_dlms_ic01_obj07_att02_value[];
extern const uint8_t g_dlms_ic01_obj09_att02_value;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic01_obj00_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj00_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj01_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj01_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj02_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj02_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj03_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj03_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj04_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj04_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj05_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj05_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj06_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj06_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj07_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj07_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj08_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj08_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj09_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj09_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj10_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj10_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj11_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj11_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj12_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj12_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj13_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj13_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj14_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj14_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj15_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj15_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj16_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj16_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj17_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj17_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj18_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj18_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj19_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj19_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj20_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj20_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj21_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj21_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj22_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj22_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj23_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj23_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj24_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj24_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj25_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj25_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj26_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj26_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj27_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj27_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj28_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj28_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj29_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj29_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj30_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj30_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj31_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj31_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj32_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj32_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj33_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj33_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj34_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj34_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj35_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj35_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj36_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj36_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj37_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj37_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj38_att02_get(distributor_params_t * p_params, ActiveRelayTime_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj38_att02_set(distributor_params_t * p_params, ActiveRelayTime_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj39_att02_get(distributor_params_t * p_params, PassiveRelayTime_t * p_attribute_get);
uint8_t R_DLMS_USER_ic01_obj39_att02_set(distributor_params_t * p_params, PassiveRelayTime_t * p_attribute_get);

#endif /* R_DLMS_USERCODE_CLASS01_H */