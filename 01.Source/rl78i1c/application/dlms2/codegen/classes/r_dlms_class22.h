/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class22.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS22_H
#define _R_DLMS_CLASS22_H
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

typedef enum tag_class22_attribute_t
{
    CLASS22_ATTRIBUTE_02_EXECUTED_SCRIPT = 2,
    CLASS22_ATTRIBUTE_03_TYPE,
    CLASS22_ATTRIBUTE_04_EXECUTION_TIME,
} class22_attribute_t;

typedef enum tag_class22_exe_time_type_t
{
    CLASS22_EXE_TIME_TYPE_01 = 1,                               /* size of execution_time = 1; wildcard in date allowed */
    CLASS22_EXE_TIME_TYPE_02,                                   /* size of execution_time = n; all time values are the same, wildcards in date not allowed */
    CLASS22_EXE_TIME_TYPE_03,                                   /* size of execution_time = n; all time values are the same, wildcards in date are allowed */
    CLASS22_EXE_TIME_TYPE_04,                                   /* size of execution_time = n; time values may be different, wildcards in date not allowed */
    CLASS22_EXE_TIME_TYPE_05,                                   /* size of execution_time = n; time values may be different, wildcards in date are allowed */
} class22_exe_time_type_t;

/* Action item  type */
typedef struct tag_executed_script_t
{
	uint8_t script_logical_name[6];		                        /* The logical name of the "Script table" object  */
	uint16_t script_selector;				                    /* Script_identifier of the script to be executed */
} class22_executed_script_t;

/* Execution date time */
typedef struct tag_execution_time_date_t
{
	time_t *p_time;
	date_t *p_date;
} class22_exe_time_t;

/* register act mask array type */
typedef OBIS_DECLARE_FIXED_ARRAY(class22_exe_time_t, class22_exe_time_array_t);

/* child record for 1 object of class 22 */
typedef struct tag_class22_child_record_t
{
	uint8_t								logical_name[6];		/* Logical name (OBIS code) of the object. */
	access_right_t				        *p_access_right;		/* Access right definition for 1 object    */
    class22_executed_script_t			*p_executed_script;		/* Contains the LN of the "Script table" obj and the sc selector of the sc to be executed */
    class22_exe_time_type_t				*p_type;				/* Type of script */
	class22_exe_time_array_t		    *p_execution_time;			/* Specifies the time and the date when the script is executed */
} class22_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class22_child_record_t g_objects_child_table_class22[];			/* Import from objects : child table defintion for class 22 */
extern const uint16_t				g_objects_child_table_class22_length;		/* Import from objects : length of child table defintion of class 22 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass22(distributor_params_t *p_params);
/* Declare encode, decode, distribute function for complex data type */
/* Attribute 03 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass22ExeScript, class22_executed_script_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass22ExeScript, class22_executed_script_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass22ExeScript, class22_executed_script_t);

/*Attribute 04 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass22ExeTimes, class22_exe_time_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass22ExeTimes, class22_exe_time_t);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass22ExeTimesArray, class22_exe_time_array_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass22ExeTimesArray, class22_exe_time_array_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass22ExeTimesArray, class22_exe_time_array_t);

/* Redirect funtion */
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass22ExeScript, class22_executed_script_t);
class22_exe_time_array_t *R_DLMS_CLASSES_RedirectClass22ExeTimesArray(distributor_params_t *p_params, class22_exe_time_array_t *p_object, uint16_t array_size);


/* Delcare macro for redirect funtion */
/* Simple data type */
#define R_DLMS_IC22_REDIRECT_03(p_params, p_attribute)			            p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, p_attribute)
/* Complex data type */
#define R_DLMS_IC22_REDIRECT_02(p_params, p_attribute)			            p_attribute = R_DLMS_CLASSES_RedirectClass22ExeScript(p_params, p_attribute)
#define R_DLMS_IC22_REDIRECT_04(p_params, p_attribute, array_size)			p_attribute = R_DLMS_CLASSES_RedirectClass22ExeTimesArray(p_params, p_attribute, array_size)

void R_DLMS_CLASSES_Class22Init(void);
void R_DLMS_CLASSES_Class22PollingProcessing(void);
void R_DLMS_CLASSES_Class22AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class22AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass22(distributor_params_t *p_params);


#endif /* _R_DLMS_CLASS22_H */

