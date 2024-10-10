/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : startup.h
* Version      : 1.00
* Description  : Start-up Header file
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _START_UP
#define _START_UP

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "compiler.h"
#include "wrp_app_mcu.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
/* Status */
#define STARTUP_OK                  0       /* OK */
#define STARTUP_ERROR               1       /* Error */

/* Relationship between FLMODE and CPU clock:
 *  . 1-8MHz: LS mode, MODE0=0 (FLMODE register)
 *  . 1-24MHz: HS mode, MODE0=1 (FLMODE register)
 *  Changing: LS-->HS: 225 cycles
 *  Changing: HS-->LS: 30 cycles
*/

/* Worst case HS to LS */
#define FLASH_MODE_HS_TO_LS()       {\
                                        FLMWEN = 1U;\
                                        SET_BIT(FLMODE, 6, 0U);\
                                        FLMWEN = 0U;\
                                        MCU_Delay(30);\
                                    }

/* Worst case LS to HS */
#define FLASH_MODE_LS_TO_HS()       {\
                                        FLMWEN = 1U;\
                                        SET_BIT(FLMODE, 6, 1U);\
                                        FLMWEN = 0U;\
                                        MCU_Delay(50);\
                                    }

#define FLASH_MODE_IS_HS()          (BIT_SELECT(FLMODE, 6) == 1U)

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/
void start_peripheral_and_app(void);
void stop_peripheral(void);
void startup(void);

#endif /* _START_UP */

