/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class07.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS07_H
#define _R_DLMS_CLASS07_H
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

typedef OBIS_DECLARE_VARIANT_ARRAY(choice_t, class07_buffer_array_t);

/* Class 07 object definition type */
#if defined(CLASS_07_VERSION) && CLASS_07_VERSION >= 1
typedef struct tag_class07_obj_def_t
{
	uint16_t 		class_id;				/* Class ID          */
	FixedString		logical_name;			/* The logical name  */
	uint8_t			attribute_index;		/* Atrribute index   */
	uint16_t		data_index;				/* Data index		 */
} class07_obj_def_t;
#else
typedef struct tag_class07_obj_def_t
{
	uint16_t 		class_id;				/* Class ID          */
	FixedString		logical_name;			/* The logical name  */
	uint8_t			attribute_index;		/* Atrribute index   */
	// uint16_t		data_index;				/* Data index		 */
} class07_obj_def_t;
#endif

/* class06 object definition array type */
typedef OBIS_DECLARE_FIXED_ARRAY(class07_obj_def_t, class07_obj_def_array_t);

/* class07 action data */
typedef union tag_class07_action_data_t
{
	void	*p_all;
	int8_t	*p_m1_reset;
	int8_t	*p_m2_capture;
#if defined(CLASS_07_VERSION) && CLASS_07_VERSION == 0
	void	*p_m3_get_buffer_by_range;
	void	*p_m4_get_buffer_by_index;
#endif
} class07_action_data_t;
typedef enum tag_class07_sort_method_t
{
	FIFO = 1,
	LIFO,
	LARGEST,
	SMALLEST,
	NEAREST_TO_ZERO,
	FAREST_FROM_ZERO
} class07_sort_method_t;
/* child record for 1 object of class 07 */
typedef struct tag_class07_child_record_t
{
	uint8_t								logical_name[6];			/* [1] Logical name (OBIS code) of the object.	*/
	access_right_t						*p_access_right;			/* Access right definition for 1 object			*/
	class07_buffer_array_t				*p_buffer;					/* [2] Buffer									*/
	class07_obj_def_array_t				*p_capture_objects;		/* [3] Capture object list						*/
	uint32_t							*p_capture_period;			/* [4] Capture period							*/
	class07_sort_method_t				*p_sort_method;				/* [5] Sort method								*/
	class07_obj_def_t					*p_sort_object;				/* [6] Sort object								*/
	uint32_t							*p_entries_in_use;			/* [7] Entries in used 							*/
	uint32_t							*p_profile_entries;			/* [8] Profile entries							*/
} class07_child_record_t;

/* Selective access */

typedef struct tag_class07_range_descriptor_t
{
	class07_obj_def_t 		*p_capture_object_definition;
	choice_t 				*p_from_value;
	choice_t 				*p_to_value;
	class07_obj_def_array_t *p_array_selected_value;
} class07_range_descriptor_t;

typedef struct tag_class07_entry_descriptor_t
{
	uint32_t from_entry;
	uint32_t to_entry;
	uint16_t from_value;
	uint16_t to_value;
} class07_entry_descriptor_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class07_child_record_t g_objects_child_table_class07[];			/* Import from objects : child table defintion for class 07 */
extern const uint16_t				g_objects_child_table_class07_length;		/* Import from objects : length of child table defintion of class 07 */

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t * R_DLMS_CLASSES_Class07_DecodeSelectiveAccess ( distributor_params_t *p_params );

void R_DLMS_CLASSES_DistributeAbstractClass07(distributor_params_t *p_params);

void R_DLMS_CLASSES_Class07Init(void);
void R_DLMS_CLASSES_Class07PollingProcessing(void);
void R_DLMS_CLASSES_Class07AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class07AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass07(distributor_params_t *p_params);

/* Declare for encode, decode, distribute for redirect function for complex data type */
/* Buffer */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_Distribute_Class07_Buffer_Array, class07_buffer_array_t);
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_Redirect_Class07_Buffer_Array, class07_buffer_array_t);
/* Capture object */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_Distribute_Obj_Def_Array, class07_obj_def_array_t);
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_Redirect_Class07_Obj_Def_Array, class07_obj_def_array_t);
/* Sort object */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_Distribute_Class07_Obj_Def, class07_obj_def_t);
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_Redirect_Class07_Obj_Def, class07_obj_def_t);
/* Declare redirection use in class object */
/* Simple data type */
#define R_DLMS_IC07_REDIRECT_04(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC07_REDIRECT_05(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, p_attribute)
#define R_DLMS_IC07_REDIRECT_07(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC07_REDIRECT_08(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
/* Complex data type */
#define R_DLMS_IC07_REDIRECT_02(p_params, p_attribute)			;//p_attribute = R_DLMS_CLASSES_Redirect_Class07_Buffer_Array(p_params, p_attribute)
#define R_DLMS_IC07_REDIRECT_03(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_Redirect_Class07_Obj_Def_Array(p_params, p_attribute)
#define R_DLMS_IC07_REDIRECT_06(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_Redirect_Class07_Obj_Def(p_params, p_attribute)

#endif /* _R_DLMS_CLASS07_H */

