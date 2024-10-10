/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class70.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS70_H
#define _R_DLMS_CLASS70_H
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

#define CLASS70_OUTPUT_STATE_CONNECTED		(TRUE)
#define CLASS70_OUTPUT_STATE_DISCONNECTED	(FALSE)

typedef enum tag_class70_attribute_t
{
    CLASS70_ATTRIBUTE_02_OUTPUT_STATE = 2,
    CLASS70_ATTRIBUTE_03_CONTROL_STATE,
    CLASS70_ATTRIBUTE_04_CONTROL_MODE,
} class70_attribute_t;

typedef enum tag_class70_method_t
{
    CLASS70_METHOD_01_REMOTE_DISCONNECT = 1,
    CLASS70_METHOD_02_REMOTE_RECONNECT,
} class70_method_t;

typedef union tag_class70_action_data_t
{
    void    * p_all;
    int8_t  * p_m1_remote_disconnect;
    int8_t  * p_m2_remote_reconnect;
} class70_action_data_t;

typedef enum tag_class70_control_state_t
{
	CLASS70_CTRL_STATE_DISCONNECTED,
	CLASS70_CTRL_STATE_CONNECTED,
	CLASS70_CTRL_STATE_READY_FOR_RECONNECTION
} class70_control_state_t;

typedef enum tag_class70_control_mode_t
{
	CLASS70_CTRL_MODE_0,
	CLASS70_CTRL_MODE_1,
	CLASS70_CTRL_MODE_2,
	CLASS70_CTRL_MODE_3,
	CLASS70_CTRL_MODE_4,
	CLASS70_CTRL_MODE_5,
	CLASS70_CTRL_MODE_6,
} class70_control_mode_t;

/* child record for 1 object of class 70 */
typedef struct tag_class70_child_record_t
{
	uint8_t								logical_name[6];		/* Logical name (OBIS code) of the object. */
	access_right_t						*p_access_right;		/* Access right definition for 1 object    */
	uint8_t								*p_output_state;		/* Shows the actual physical state of the device connection the supply */
    class70_control_state_t				*p_control_state;		/* Shows the actual physical state of the device connection the supply. */
    class70_control_mode_t				*p_control_mode;		/* Configures the behaviour of the disconnect control object for all triggers */
} class70_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class70_child_record_t g_objects_child_table_class70[];			/* Import from objects : child table defintion for class 70 */
extern const uint16_t				g_objects_child_table_class70_length;		/* Import from objects : length of child table defintion of class 70 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass70(distributor_params_t *p_params);

void R_DLMS_CLASSES_Class70Init(void);
void R_DLMS_CLASSES_Class70PollingProcessing(void);
void R_DLMS_CLASSES_Class70AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class70AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass70(distributor_params_t *p_params);

/* Declare redirect function */
/* Macro for simple attribute */
#define R_DLMS_IC70_REDIRECT_02(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectBoolean(p_params, p_attribute)
#define R_DLMS_IC70_REDIRECT_03(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, p_attribute)
#define R_DLMS_IC70_REDIRECT_04(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, p_attribute)

#endif /* _R_DLMS_CLASS70_H */

