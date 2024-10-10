/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : powermgmt.h
* Version      : 1.00
* Description  : Power Management Module
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 18.11.2012 
******************************************************************************/

#ifndef _POWERMGMT_H
#define _POWERMGMT_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"        /* GSCE Standard Typedef */

/******************************************************************************
Macro definitions
******************************************************************************/

#ifdef __DEBUG
#define PWR_FUNC                                    FAR_FUNC
#else
#define PWR_FUNC                                    FAR_FUNC
#endif

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum tagPowermgmtMode
{
    POWERMGMT_MODE1 = 1U,
    POWERMGMT_MODE2,
    POWERMGMT_MODE3,
    POWERMGMT_MODE4,
} powermgmt_mode_t;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/
PWR_FUNC void POWERMGMT_PollingProcessing(void);
PWR_FUNC powermgmt_mode_t POWERMGMT_GetMode(void);
PWR_FUNC void POWERMGMT_SetMode(powermgmt_mode_t mode);

/* Callback functions */
PWR_FUNC void POWERMGMT_VDD_InterruptCallback(void);         /* To be registered into interrupt VDDLVD driver */
PWR_FUNC void POWERMGMT_AC_InterruptCallback(void);          /* To be registered into interrupt EXLVD driver */
PWR_FUNC void POWERMGMT_RTC_Periodic_InterruptCallback(void);
PWR_FUNC void POWERMGMT_RTC_Alarm_InterruptCallback(void);

#endif /* _POWERMGMT_H */

