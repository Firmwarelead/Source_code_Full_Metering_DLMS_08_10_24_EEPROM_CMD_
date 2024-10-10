/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class04.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS04_H
#define _R_DLMS_CLASS04_H
#include "r_dlms_config.h"
#include "r_dlms_class03.h"
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
/* child record for 1 extended register object definition */
typedef struct tag_class04_child_record_t
{
	uint8_t			logical_name[6];	/* Logical name (OBIS code) of the object. */
	access_right_t	*p_access_right;	/* Access right definition for 1 object    */
	choice_t		value;				/* Value                                   */
	scaler_unit_t	*p_scaler_unit;		/* Scaler, unit                            */
	choice_t		status;				/* Status                                  */
	date_time_t		*p_capture_time;	/* Capture time buffer                     */
} class04_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class04_child_record_t g_objects_child_table_class04[];			/* Import from objects : child table defintion for class 04 */
extern const uint16_t				g_objects_child_table_class04_length;		/* Import from objects : length of child table defintion of class 04 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass04(distributor_params_t *p_params);

#define R_DLMS_IC04_REDIRECT_02(p_params, attribute)			R_DLMS_CLASSES_Redirect_ChoiceAttribute(p_params, &attribute)
#define R_DLMS_IC04_REDIRECT_03(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectScalerUnit(p_params, p_attribute)
#define R_DLMS_IC04_REDIRECT_04(p_params, p_attribute)			R_DLMS_CLASSES_Redirect_ChoiceAttribute(p_params, &p_attribute)
#define R_DLMS_IC04_REDIRECT_05(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDateTime(p_params, p_attribute)

/******** Declare for complex data type ***********/

void R_DLMS_CLASSES_Class04Init(void);
void R_DLMS_CLASSES_Class04PollingProcessing(void);
void R_DLMS_CLASSES_Class04AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class04AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass04(distributor_params_t *p_params);

#endif /* _R_DLMS_CLASS04_H */

