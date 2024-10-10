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
* File Name    : credit.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CA78K0R
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : EM Display Application Layer APIs
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver layer */
#include "r_cg_macrodriver.h"
#include "typedef.h"            /* GCSE Standard definitions */
#include "relay.h"
#include "event.h"
#include "wrp_app_mcu.h"
//#include "r_cg_wdt.h"
//#include <string.h>
//#include <stdio.h>
//#include <stdarg.h>           /* Variant argument */
//#include "em_keypad.h"
#include "storage.h"
#include "r_meter_format.h"
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define RELAY_PULSE_DURATION_COUNT  20000

#define RELAY_IS_STATUS_VALID(status)   (status == RELAY_CONNECTED || status == RELAY_DISCONNECTED)
#define RELAY_VALIDATE_AND_CORRECT_READ_STATUS(status, set_func) {  \
    if (status != RELAY_CONNECTED &&                                \
        status != RELAY_DISCONNECTED) {                             \
        status = RELAY_CONNECTED;                                   \
        set_func(status);                                           \
    }                                                               \
}

#ifndef STORAGE_EEPROM_MISC_RELAY_STATUS_ADDR
#define STORAGE_EEPROM_MISC_RELAY_STATUS_ADDR       (0xFC00)
#endif

/* EEPROM Addres mappping */
#define RELAY_STATUS_ADDR           (STORAGE_EEPROM_MISC_RELAY_STATUS_ADDR)
#define RELAY_STATUS_SIZE           (sizeof(uint8_t))

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/


/******************************************************************************
Private global variables and functions
******************************************************************************/


/***********************************************************************************************************************
* Function Name    : void CREDIT_PollingProcessing(void)
* Description      : 
* Arguments        : None
* Functions Called : None
* Return Value     : None
***********************************************************************************************************************/
void RELAY_PollingProcessing(void)
{

}
 
/***********************************************************************************************************************
* Function Name    : void RELAY_Initialize(void)
* Description      : 
* Arguments        : None
* Functions Called : None
* Return Value     : None
***********************************************************************************************************************/
void RELAY_Initialize(void)
{
}


/***********************************************************************************************************************
* Function Name    : void RELAY_SwitchOff(void)
* Description      : 
* Arguments        : None
* Functions Called : None
* Return Value     : None
***********************************************************************************************************************/    
void RELAY_SwitchOff(void)
{
//    uint16_t i;

//    RELAY_CT_PRESET    = RELAY_ON;       /* for J1 */
//    RELAY_CT_SET       = RELAY_OFF;      /* for J1 */
//    RELAY_SHUNT_PRESET = RELAY_ON;       /* for J2 */
//    RELAY_SHUNT_SET    = RELAY_OFF;      /* for J2 */
    
//    for (i = 0; i < RELAY_PULSE_DURATION_COUNT; i++)
//    {   
//        NOP();
//        NOP();
//    }
    
//    RELAY_CT_PRESET    = RELAY_OFF;      /* for J1 */
//    RELAY_CT_SET       = RELAY_OFF;      /* for J1 */
//    RELAY_SHUNT_PRESET = RELAY_OFF;      /* for J2 */
//    RELAY_SHUNT_SET    = RELAY_OFF;      /* for J2 */

	    P3_bit.no7=0;
	    P3_bit.no6=1;
	    MCU_Delay(20000);// 20 ms delay
	    P3_bit.no7=0;
	    P3_bit.no6=0;
    RELAY_SetStatus(RELAY_DISCONNECTED);
}

/***********************************************************************************************************************
* Function Name    : void RELAY_SwitchOn(void)
* Description      : 
* Arguments        : None
* Functions Called : None
* Return Value     : None
***********************************************************************************************************************/
void RELAY_SwitchOn(void)
{
//    uint16_t i;

//    RELAY_CT_PRESET    = RELAY_OFF;      /* for J1 */
//    RELAY_CT_SET       = RELAY_ON;       /* for J1 */
//    RELAY_SHUNT_PRESET = RELAY_OFF;      /* for J2 */
//    RELAY_SHUNT_SET    = RELAY_ON;       /* for J2 */
    
//    for (i = 0; i < RELAY_PULSE_DURATION_COUNT; i++)
//    {   
//        NOP();
//        NOP();
//    }
    
//    RELAY_CT_PRESET    = RELAY_OFF;      /* for J1 */
//    RELAY_CT_SET       = RELAY_OFF;      /* for J1 */
//    RELAY_SHUNT_PRESET = RELAY_OFF;      /* for J2 */
//    RELAY_SHUNT_SET    = RELAY_OFF;      /* for J2 */


	    P3_bit.no7=1;
	    P3_bit.no6=0;
	    MCU_Delay(20000);// 20 ms delay
	    P3_bit.no7=0;
	    P3_bit.no6=0;
	    
    RELAY_SetStatus(RELAY_CONNECTED);
}

/***********************************************************************************************************************
* Function Name    : void RELAY_GetStatus(void)
* Description      : 
* Arguments        : None
* Functions Called : None
* Return Value     : uint8_t RELAY_OFF/RELAY_ON
***********************************************************************************************************************/
uint8_t RELAY_GetStatus(void)
{
    uint8_t status;

    EPR_Read(
        RELAY_STATUS_ADDR,
        (uint8_t *)&status,
        RELAY_STATUS_SIZE
    );

    RELAY_VALIDATE_AND_CORRECT_READ_STATUS(
        status, 
        RELAY_SetStatus
    );

    return status;
}

void RELAY_SetStatus(uint8_t status)
{
    if (RELAY_IS_STATUS_VALID(status))
    {
        EPR_Write(
            RELAY_STATUS_ADDR,
            (uint8_t *)&status,
            RELAY_STATUS_SIZE
        );
    }
}

uint8_t RELAY_GetPreviousStatus(void)
{
    uint8_t status;

    EPR_Read(
        RELAY_STATUS_ADDR + (1 * RELAY_STATUS_SIZE),
        (uint8_t *)&status,
        RELAY_STATUS_SIZE
    );

    RELAY_VALIDATE_AND_CORRECT_READ_STATUS(
        status,
        RELAY_SetPreviousStatus
    );

    return status;
}


void RELAY_SetPreviousStatus(uint8_t status)
{
    if (RELAY_IS_STATUS_VALID(status))
    {
        EPR_Write(
            RELAY_STATUS_ADDR + (1 * RELAY_STATUS_SIZE),
            (uint8_t *)&status,
            RELAY_STATUS_SIZE
        );
    }
}