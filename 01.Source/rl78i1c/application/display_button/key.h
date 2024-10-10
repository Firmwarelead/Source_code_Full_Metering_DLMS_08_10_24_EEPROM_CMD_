/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : key.h
* Version      : 1.00
* Description  : KEY Interface Header file
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _KEY_H
#define _KEY_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
#ifndef KEY_PRESSED
#define KEY_PRESSED     1
#endif

#define     KEY_UP      (BIT_SELECT(P15,2))   //* Changed to follow case of meter for button( different with schematic)
#define     MAGNET      (BIT_SELECT(P7,7))
#define     CASE        (BIT_SELECT(P15,1))   //* Changed to follow case of meter for case open( different with schematic)
#define     POWER_SW    (BIT_SELECT(P3,1))
//#define     KEY_DOWN    (BIT_SELECT(P15,2))

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/
/* Key Polling Processing */
void KEY_PollingProcessing(void);

/* Callback */
void KEY_DownPressed(void);
void KEY_MidPressed(void);
void KEY_UpPressed(void);

/* Check */
uint8_t KEY_IsUpPressed(void);

#endif /* _KEY_H */

