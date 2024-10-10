/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_standby.h
* Version      : 1.00
* Description  : Standby library header file
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 24.06.2011 1.00    First Release
******************************************************************************/

#ifndef _STANDBY_H
#define _STANDBY_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t EM_STANDBY_Start(void);
uint8_t EM_STANDBY_Stop(void);

/* Calculate power when wakeup from standby */
float32_t EM_STANDBY_CalculatePowerAndSignals(
	float32_t voltage,
	float32_t i1_coeff,
	float32_t i2_coeff
);
float32_t EM_STANDBY_GetCurrent1(void);
float32_t EM_STANDBY_GetCurrent2(void);
uint16_t EM_STANDBY_GetTotalSample(void);

/* Interrupt callback function */
void EM_STANDBY_ADCInterruptCallback(int32_t i1, int32_t i2);

#endif /* _STANDBY_H */
