/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class01.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS01_H
#define _R_DLMS_CLASS01_H
#include "r_dlms_config.h"

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_classes.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/
/* child record for 1 data object definition */
typedef struct tag_class01_child_record_t
{
	uint8_t			logical_name[6];	/* Logical name (OBIS code) of the object. */
	access_right_t	*p_access_right;	/* Access right definition for 1 object    */
	choice_t		value;			/* Value                                   */
} class01_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/

extern const class01_child_record_t g_objects_child_table_class01[];			/* Import from objects : child table defintion for class 01 */
extern const uint16_t				g_objects_child_table_class01_length;		/* Import from objects : length of child table defintion of class 01 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass01(distributor_params_t *p_params);

#define R_DLMS_IC01_REDIRECT_02(p_params, attribute)			R_DLMS_CLASSES_Redirect_ChoiceAttribute(p_params, &attribute)

void R_DLMS_CLASSES_Class01Init(void);
void R_DLMS_CLASSES_Class01PollingProcessing(void);
void R_DLMS_CLASSES_Class01AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class01AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass01(distributor_params_t *p_params);

#endif /* _R_DLMS_CLASS01_H */

