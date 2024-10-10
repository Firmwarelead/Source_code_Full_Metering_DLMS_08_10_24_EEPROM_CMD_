/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************	
* File Name    : r_dlms_classes.c
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_library_process.h"
#include "r_dlms_config.h"
#include "r_dlms_classes.h"
#include "r_dlms_objects.h"
#include <string.h>

#include "r_dlms_class01.h"
#include "r_dlms_class03.h"
#include "r_dlms_class04.h"
#include "r_dlms_class07.h"
#include "r_dlms_class08.h"
#include "r_dlms_class09.h"
#include "r_dlms_class15.h"
#include "r_dlms_class18.h"
#include "r_dlms_class20.h"
#include "r_dlms_class22.h"
#include "r_dlms_class23.h"
#include "r_dlms_class40.h"
#include "r_dlms_class41.h"
#include "r_dlms_class45.h"
#include "r_dlms_class48.h"
#include "r_dlms_class64.h"
#include "r_dlms_class70.h"
#include "r_dlms_class71.h"

#include"r_dlms_wrapper_conversion_ip.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define CLASSES_CLIENT_MIN_PDU_SIZE				(128)							/* TODO: Adjust this size enough to response AARE to Client */
#if defined(DLMS_LIB_MAX_APDU_SIZE) && (DLMS_LIB_MAX_APDU_SIZE > 128)
#define CLASSES_DISTRIBUTION_BUFFER_SIZE		(DLMS_LIB_MAX_APDU_SIZE - 64)
#else
#error "Library APDU size too small"
#endif
#define CLASSES_TEMPORARY_BUFFER_SIZE			(832)
#define CLASSES_MEMLINKS_MAX_ITEMS				(8)
#define CHILD_RECORD_RAM_CLONE_ENABLE			(FALSE)
#define CLASSES_ENCODER_SESSION_MAX_REENTRANT	(3)
#define CLASSES_DEFAULT_MAX_SEND_PDU_SIZE		(DLMS_LIB_MAX_APDU_SIZE)

/******************************************************************************
Typedef definitions
******************************************************************************/

/* To store the stage of complex type encoder (array of structure, array of array) for an assc session */
typedef struct tagEncoderSession
{
	uint16_t reentrant_count;
	uint8_t  partial[CLASSES_ENCODER_SESSION_MAX_REENTRANT];
	uint16_t loop_index[CLASSES_ENCODER_SESSION_MAX_REENTRANT];
	uint16_t element_index[CLASSES_ENCODER_SESSION_MAX_REENTRANT];
} EncoderSession;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/* Import from cstart.asm */
extern const uint16_t ram_start_addr;
extern const uint16_t ram_end_addr;

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
/* Var to diag max usage on memlinks */
uint8_t		g_dlms_diag_memlinks_max_usage = 0;
uint16_t	g_dlms_diag_malloc_temporary_buffer_max_usage = 0;

/* --------------------------------------------------------
 * Vars to link with library
 * --------------------------------------------------------
 */

/* Store information for each connected session to each association support by library */
AsscConnectionSession		g_classes_assc_connection_session[DLMS_MAX_ASSOCIATION_SUPPORT];

/* Store index of array being encoded by block transfer, for each association */
uint8_t						g_classes_array_encoder_fatal_error = FALSE;
uint16_t 					g_classes_complex_distributor_current_assc_id = 0;
EncoderSession 				g_classes_array_encoder_session[DLMS_MAX_ASSOCIATION_SUPPORT];

/* --------------------------------------------------------
 * Vars for Classes Distribution
 * --------------------------------------------------------
 */
const uint16_t						g_classes_total_number_objects = 125;
const uint16_t						g_classes_total_number_objects_each_assc[OBIS_NUMBER_OF_ASSOCIATION] = {8, 125, 125, 12, 9};
const uint16_t						g_classes_max_number_of_attrs = 11;
const uint16_t						g_classes_max_number_of_methods = 6;
const e_master_table_class_index_t	g_dlms_master_class_indexes[] = {

/* 0, 1, 2 */		MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_CLASS_01, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 3, 4, 5 */		MASTER_TABLE_INDEX_CLASS_03, 	MASTER_TABLE_INDEX_CLASS_04, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 6, 7, 8 */		MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_CLASS_07, 	MASTER_TABLE_INDEX_CLASS_08, 	
/* 9, 10, 11 */		MASTER_TABLE_INDEX_CLASS_09, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 12, 13, 14 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 15, 16, 17 */	MASTER_TABLE_INDEX_CLASS_15, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 18, 19, 20 */	MASTER_TABLE_INDEX_CLASS_18, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_CLASS_20, 	
/* 21, 22, 23 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_CLASS_22, 	MASTER_TABLE_INDEX_CLASS_23, 	
/* 24, 25, 26 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 27, 28, 29 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 30, 31, 32 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 33, 34, 35 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 36, 37, 38 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 39, 40, 41 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_CLASS_40, 	MASTER_TABLE_INDEX_CLASS_41, 	
/* 42, 43, 44 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 45, 46, 47 */	MASTER_TABLE_INDEX_CLASS_45, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 48, 49, 50 */	MASTER_TABLE_INDEX_CLASS_48, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 51, 52, 53 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 54, 55, 56 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 57, 58, 59 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 60, 61, 62 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 63, 64, 65 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_CLASS_64, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 66, 67, 68 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_RESERVE, 	
/* 69, 70, 71 */	MASTER_TABLE_INDEX_RESERVE, 	MASTER_TABLE_INDEX_CLASS_70, 	MASTER_TABLE_INDEX_CLASS_71 };
const uint16_t					g_biggest_class_id_number = 71;

/* Master table */
/* Mapping table between master_index to this please refer to r_dlms_classes.h file */
const master_record_t		g_classes_master_table[] =
{
	/*
	*----------------------------------------------
	* "IC Name"
	* {
	*    Class Version, Number of attrs, Number of methods,
	*    Class Distributor Function,
	*    Child-list size,
	*    Child-pointer
	* }
	*----------------------------------------------
	*/
	/*Index in g_dlms_master_class_indexes - 0 */
	/* 01 - Data */
	{
		0, 2, 0,
		R_DLMS_CLASSES_DistributeClass01,
		(uint16_t *)&g_objects_child_table_class01_length,
		(child_record_t *)&g_objects_child_table_class01,
		sizeof(class01_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 1 */
	/* 03 - Register */
	{
		0, 3, 1,
		R_DLMS_CLASSES_DistributeClass03,
		(uint16_t *)&g_objects_child_table_class03_length,
		(child_record_t *)&g_objects_child_table_class03,
		sizeof(class03_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 2 */
	/* 04 - Extend register */
	{
		0, 5, 1,
		R_DLMS_CLASSES_DistributeClass04,
		(uint16_t *)&g_objects_child_table_class04_length,
		(child_record_t *)&g_objects_child_table_class04,
		sizeof(class04_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 3 */
	/* 07 - Profile generic */
	{
		1, 8, 2,
		R_DLMS_CLASSES_DistributeClass07,
		(uint16_t *)&g_objects_child_table_class07_length,
		(child_record_t *)&g_objects_child_table_class07,
		sizeof(class07_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 4 */
	/* 08 - Clock */
	{
		0, 9, 6,
		R_DLMS_CLASSES_DistributeClass08,
		(uint16_t *)&g_objects_child_table_class08_length,
		(child_record_t *)&g_objects_child_table_class08,
		sizeof(class08_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 5 */
	/* 09 - Script table */
	{
		0, 2, 1,
		R_DLMS_CLASSES_DistributeClass09,
		(uint16_t *)&g_objects_child_table_class09_length,
		(child_record_t *)&g_objects_child_table_class09,
		sizeof(class09_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 6 */
	/* 15 - Association LN */
	{
		1, 9, 4,
		R_DLMS_CLASSES_DistributeClass15,
		(uint16_t *)&g_objects_child_table_class15_length,
		(child_record_t *)&g_objects_child_table_class15,
		sizeof(class15_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 7 */
	/* 18 - Image transfer */
	{
		0, 7, 4,
		R_DLMS_CLASSES_DistributeClass18,
		(uint16_t *)&g_objects_child_table_class18_length,
		(child_record_t *)&g_objects_child_table_class18,
		sizeof(class18_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 8 */
	/* 20 - Activity calendar */
	{
		0, 10, 1,
		R_DLMS_CLASSES_DistributeClass20,
		(uint16_t *)&g_objects_child_table_class20_length,
		(child_record_t *)&g_objects_child_table_class20,
		sizeof(class20_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 9 */
	/* 22 - single action shcedule */
	{
		0, 4, 0,
		R_DLMS_CLASSES_DistributeClass22,
		(uint16_t *)&g_objects_child_table_class22_length,
		(child_record_t *)&g_objects_child_table_class22,
		sizeof(class22_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 10 */
	/* 23 - IEC HDLC setup */
	{
		1, 9, 0,
		R_DLMS_CLASSES_DistributeClass23,
		(uint16_t *)&g_objects_child_table_class23_length,
		(child_record_t *)&g_objects_child_table_class23,
		sizeof(class23_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 11 */
	/* 40 - Push setup */
	{
		0, 7, 1,
		R_DLMS_CLASSES_DistributeClass40,
		(uint16_t *)&g_objects_child_table_class40_length,
		(child_record_t *)&g_objects_child_table_class40,
		sizeof(class40_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 12 */
	/* 41 - TCP-UDP setup */
	{
		0, 6, 0,
		R_DLMS_CLASSES_DistributeClass41,
		(uint16_t *)&g_objects_child_table_class41_length,
		(child_record_t *)&g_objects_child_table_class41,
		sizeof(class41_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 13 */
	/* 45 - GPRS modem setup */
	{
		0, 4, 0,
		R_DLMS_CLASSES_DistributeClass45,
		(uint16_t *)&g_objects_child_table_class45_length,
		(child_record_t *)&g_objects_child_table_class45,
		sizeof(class45_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 14 */
	/* 48 - IPv6 setup */
	{
		0, 10, 2,
		R_DLMS_CLASSES_DistributeClass48,
		(uint16_t *)&g_objects_child_table_class48_length,
		(child_record_t *)&g_objects_child_table_class48,
		sizeof(class48_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 15 */
	/* 64 - Security setup */
	{
		0, 5, 2,
		R_DLMS_CLASSES_DistributeClass64,
		(uint16_t *)&g_objects_child_table_class64_length,
		(child_record_t *)&g_objects_child_table_class64,
		sizeof(class64_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 16 */
	/* 70 - Disconnect control */
	{
		0, 4, 2,
		R_DLMS_CLASSES_DistributeClass70,
		(uint16_t *)&g_objects_child_table_class70_length,
		(child_record_t *)&g_objects_child_table_class70,
		sizeof(class70_child_record_t)
	},
	/*Index in g_dlms_master_class_indexes - 17 */
	/* 71 - Limiter */
	{
		0, 11, 0,
		R_DLMS_CLASSES_DistributeClass71,
		(uint16_t *)&g_objects_child_table_class71_length,
		(child_record_t *)&g_objects_child_table_class71,
		sizeof(class71_child_record_t)
	}
};
const uint16_t			g_classes_total_master_table_elements = sizeof(g_classes_master_table) / sizeof(master_record_t);
/* --------------------------------------------------------
 * Functions for Classes Distribution
 * --------------------------------------------------------
 */

/******************************************************************************
* Function Name   : R_DLMS_CLASSES_CompareObisCode
* Interface       : static uint8_t R_DLMS_CLASSES_CompareObisCode(
*                 :     uint8_t *obis_code,
*                 :     uint8_t *input_code
*                 : );
* Description     : Compare OBIS Code
* Arguments       : uint8_t * obis_code : Source obis code (in obis list)
*                 : uint8_t * input_code: Input obis code (from request)
* Function Calls  : None
* Return Value    : static uint8_t, result of comparision
*                 :     0    means un-match
*                 :     1    means matched.
******************************************************************************/
uint8_t R_DLMS_CLASSES_CompareObisCode(uint8_t *obis_code, uint8_t *input_code)
{
	uint8_t i;

	/*
	* Compare for first 5 byte only
	* The f element present the selection (VZ or historic value)
	*/
	for (i = 0; i < 5; i++) {
		if (*obis_code++ != *input_code++) {
			return FALSE;	/* Un-matched */
		}
	}

	return TRUE;	/* Matched */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_FindChildRecordByIndex
* Interface     : child_record_t *R_DLMS_CLASSES_FindChildRecordByIndex(
*               :     uint16_t class_id,
*               :     uint16_t child_index
*               : );
* Description   : Get a child record, based on master index and child index
* Arguments     : uint16_t class_id: class ID
*               : uint16_t child_index : Child index
* Function Calls: None
* Return Value  : child_record_t *, pointer of a child record
*               : NULL if not found
******************************************************************************/
child_record_t *R_DLMS_CLASSES_FindChildRecordByIndex(uint16_t class_id, uint16_t child_index)
{
	master_record_t	*p_master_record;	/* Pointer to master record in g_MasterTable */
	child_record_t	*p_child_record;	/* Pointer to child record in a specified master record */
	uint16_t master_index;

	if (class_id > g_biggest_class_id_number)
	{
		return NULL;	/* master index is out of range */
	}
	else
	{
		/* Nothing here*/
	}
	/* Translate class id to master index*/
	master_index = (uint16_t)g_dlms_master_class_indexes[class_id]; 
	/* Check master_index that it was defined or not */
	if (master_index >= g_classes_total_master_table_elements)
	{
		return NULL;
	}
	else
	{
		/* Nothing here*/
	}
	/* Find in master table first */
	p_master_record = (master_record_t *)(g_classes_master_table + master_index);
	

	/*
	* If found master record, next find object in child table by index
	*/
	if (child_index >= *(p_master_record->child_list_size))
	{
		return NULL;
	}

	/*
	 * TODO: Buffer check for odd and even data alignment on below code
	 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
	 */
	p_child_record = (child_record_t *)(void *)(
		((uint8_t *)p_master_record->child_list_pointer) +
		(child_index * p_master_record->child_item_size)
	);

	return (p_child_record);
}


/******************************************************************************
* Function Name : R_DLMS_CLASSES_CheckObjectVisibility
* Interface     : uint8_t R_DLMS_CLASSES_CheckObjectVisibility(
*               :     AsscChannel assc_id,
*               :     uint16_t class_id,
*               :     uint16_t child_index,
*               : );
* Description   : Check object visibility for a specified association
* Arguments     : AsscChannel assc_id
*               :    - Association id
*               : uint16_t class_id
*               :    - Master id (class id) of object
*               : uint16_t child_index
*               :    - Child id of object
* Function Calls: None
* Return Value  : uint8_t,
*               :     OBIS_AR_OBJ_IS_INVISIBLE    Object is invisible
*               :     OBIS_AR_OBJ_IS_VISIBLE      Object is visible
******************************************************************************/
uint8_t R_DLMS_CLASSES_CheckObjectVisibility(AsscChannel assc_id, uint16_t class_id, uint16_t child_index)
{
	child_record_t *p_child_record;

	/*
	* Find OBIS object in child table by
	* visibility, obis code, access right.
	*/
	p_child_record = R_DLMS_CLASSES_FindChildRecordByIndex(class_id, child_index);
	if (p_child_record == NULL)
	{
		return OBIS_AR_OBJ_IS_INVISIBLE;		/* Not found the object */
	}

	/*
	* Check the access_right object by the association number
	*/
	if (p_child_record->p_access_right == NULL)
	{
		return OBIS_AR_OBJ_IS_VISIBLE;		/* OK, object is visible */
	}
	else if (
		(g_classes_access_right_none.attributes.length >= p_child_record->p_access_right[assc_id].attributes.length &&
		 memcmp(
			g_classes_access_right_none.attributes.p_list,
			p_child_record->p_access_right[assc_id].attributes.p_list,
			p_child_record->p_access_right[assc_id].attributes.length) != 0) ||
		(g_classes_access_right_none.methods.length >= p_child_record->p_access_right[assc_id].methods.length &&
		 memcmp(
			g_classes_access_right_none.methods.p_list,
			p_child_record->p_access_right[assc_id].methods.p_list,
			p_child_record->p_access_right[assc_id].methods.length) != 0)
	)
	{
		return OBIS_AR_OBJ_IS_VISIBLE;		/* OK, object is visible */
	}
	else
	{
		return OBIS_AR_OBJ_IS_INVISIBLE;
	}
}

/******************************************************************************
* Function Name   : R_DLMS_CLASSES_GetAccessRightValue
* Interface       : uint16_t R_DLMS_CLASSES_GetAccessRightValue(
*                 :     req_type_t req_type,
*                 :     uint8_t req_id,
*                 :     access_right_t *p_access_right
*                 : );
* Description     : Get access right value for object
* Arguments       : req_type_t req_type -
*                 :     Requested type on object (GET/SET/ACTION)
*                 : uint8_t req_id -
*                 :     Requested id on object (attribute id or method id)
*                 : access_right_t * p_access_right -
*                 :     Access right pointer of object
* Function Calls  : None
* Return Value    : uint8_t, access right value as defined by macros in
*                 : r_dlms_obis_objects.h
******************************************************************************/
uint8_t R_DLMS_CLASSES_GetAccessRightValue(req_type_t req_type, uint8_t req_id, access_right_t *p_access_right)
{
	uint8_t access_right_value = 0;	/* Initial as no access */

	/* Check req_type value */
	if (req_type != REQ_TYPE_GET &&
		req_type != REQ_TYPE_SET &&
		req_type != REQ_TYPE_ACTION)
	{
		return 0;	/* No access */
	}

	/* Get the access_right_value base on req_id & req_type */
	/* For Attribute? */
	if (req_type == REQ_TYPE_GET || req_type == REQ_TYPE_SET)
	{
		/*
		* For attribute only,
		 * we propose that attribute 0 can be read for all association
		*/
		if (p_access_right == NULL) {
			if (req_id <= OBIS_AR_ATTR_MAX_QUANTITY_SUPPORT) {
				access_right_value = OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE;
			}
			else {
				access_right_value = OBIS_AR_ATTR_NO_ACCESS;
			}
		}
		else if (req_id == 0) {
			access_right_value = OBIS_AR_ATTR_READ;
		}
		else if (req_id <= p_access_right->attributes.length) {
			access_right_value = p_access_right->attributes.p_list[req_id - 1];
		}
		else {
			access_right_value = OBIS_AR_ATTR_NO_ACCESS;
		}
	}
	else
	{
		/*
		* For method 0, denied
		*/
		if (p_access_right == NULL)
		{
			if (req_id <= OBIS_AR_METHOD_MAX_QUANTITY_SUPPORT) {
				access_right_value = OBIS_AR_METHOD_ACCESS;
			}
			else {
				access_right_value = OBIS_AR_METHOD_NO_ACCESS;
			}
		}
		else if (req_id == 0) {
			access_right_value = OBIS_AR_METHOD_NO_ACCESS;
		}
		else if (req_id <= p_access_right->methods.length) {
			access_right_value = p_access_right->methods.p_list[req_id - 1];
		}
		else {
			access_right_value = OBIS_AR_METHOD_NO_ACCESS;
		}
	}

	return (access_right_value);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_GetAndCheckAccessRight
* Interface     : static uint8_t R_DLMS_CLASSES_GetAndCheckAccessRight(
*               :     void *p_library_descriptor,
*               :     req_type_t req_type,
*               :     uint8_t req_id,
*               :     access_right_t *access_right
*               : );
* Description   : Get access right of attribute and method, based on its id.
*               : Check client request with security elements formed after decipher process and access rights
*               : Pass attribute and method access right to library to enforce security of response
* Arguments     : void *p_library_descriptor -
*               :    GET/SET/ACTION service descriptor from library
*               : req_type_t req_type -
*               :    Request type (GET/SET/ACTION)
*               : uint8_t req_id -
*               :    Request id, attribute id or method id
*               : p_access_right_t * access_right -
*               :    Access right of the object in associated connection
* Function Calls: R_DLMS_CLASSES_GetAccessRightValue()
* Return Value  : static uint8_t
*               :   Indicate whether the object can be accessed (1) or not (0)
******************************************************************************/
static uint8_t R_DLMS_CLASSES_GetAndCheckAccessRight(
	void			*p_library_descriptor,
	req_type_t		req_type,
	uint8_t			req_id,
	access_right_t 	*p_access_right
	)
{
	uint16_t	count;

	/* For security policy check of request and enforce security of response */
	union {
		void							*p_all;
		CosemGetIndication_Params		*p_get;
		CosemSetIndication_Params		*p_set;
		CosemActionIndication_Params	*p_action;
	} indication_params;
	SecurityOptionList					*p_security_options = NULL;
	ApduDispatchContext					*p_dispatch_context = NULL;
	uint8_t								access_right_value = 0;
	uint8_t								attribute_access_right_value = 0;
	uint8_t								method_access_right_value = 0;
	struct SecurityIndicators
	{
		uint8_t has_aes_gcm_authentication	: 1;	/* AES-GCM 128 authentication on the request */
		uint8_t has_aes_gcm_encryption		: 1;	/* AES-GCM 128 encryption on the request */
		uint8_t has_digital_signature		: 1;	/* Digital signature verification on the request */
		uint8_t reserved					: 5;	/* Reserved (no use) */
	} request_security_indicators = { FALSE, FALSE, FALSE, 0 };

	/*
	* Full access (Read, write...) when not specify access right
	*/
	if (p_access_right == NULL) {
		return TRUE;	/* Full access */
	}

	indication_params.p_all = p_library_descriptor;

	/* Get the access_right_value base on req_type and the req_id */
	access_right_value = R_DLMS_CLASSES_GetAccessRightValue(
		req_type,
		req_id,
		p_access_right
	);

	/* Get security option list from DLMS Library and access right for attribute and method */
	if (req_type == REQ_TYPE_GET) {
		attribute_access_right_value = access_right_value;
		if (indication_params.p_all != NULL &&
			indication_params.p_get->p_dispatch_context != NULL) {
			p_dispatch_context = indication_params.p_get->p_dispatch_context;
		}
	}
	else if (req_type == REQ_TYPE_SET) {
		attribute_access_right_value = access_right_value;
		if (indication_params.p_all != NULL &&
			indication_params.p_set->p_dispatch_context != NULL) {
			p_dispatch_context = indication_params.p_set->p_dispatch_context;
		}
	}
	else if (req_type == REQ_TYPE_ACTION) {
		method_access_right_value = access_right_value;
		if (indication_params.p_all != NULL &&
			indication_params.p_action->p_dispatch_context != NULL) {
			p_dispatch_context = indication_params.p_action->p_dispatch_context;
		}
	}

	/* Build security indicator of the request */
	if (p_dispatch_context != NULL &&
		p_dispatch_context->p_additional_params != NULL) {
		p_security_options = &p_dispatch_context->p_additional_params->security_options;
		for (count = 0; count < p_security_options->usage; count++) {
			if (p_security_options->elements[count].security_control.bits.authentication == TRUE) {
				request_security_indicators.has_aes_gcm_authentication = TRUE;
			}
			if (p_security_options->elements[count].security_control.bits.encryption == TRUE) {
				request_security_indicators.has_aes_gcm_encryption = TRUE;
			}
			if (p_security_options->elements[count].protection_type == PROTECTION_GENERAL_SIGNING) {
				request_security_indicators.has_digital_signature = TRUE;
			}
		}
	}

	/* Check basic right of read/write/acess with access right */
	if (req_type == REQ_TYPE_GET) {
		ASSERT_TRUE_RET_VAL((attribute_access_right_value & OBIS_AR_ATTR_READ) == 0, FALSE);
	}
	else if (req_type == REQ_TYPE_SET) {
		ASSERT_TRUE_RET_VAL((attribute_access_right_value & OBIS_AR_ATTR_WRITE) == 0, FALSE);
	}
	else if (req_type == REQ_TYPE_ACTION) {
		ASSERT_TRUE_RET_VAL((method_access_right_value & OBIS_AR_METHOD_ACCESS) == 0, FALSE);
	}

	/*
	 * Class 15 - Version 0, 1, 2, 3
	 *
	 * Common for attr and method (bit 2,3,4) are indicators of
	 * (authentication, encryption, digital signature) of request
	 */
	ASSERT_TRUE_RET_VAL(
		(access_right_value & 0x04) != 0 &&
		request_security_indicators.has_aes_gcm_authentication == FALSE,
		FALSE
	);
	ASSERT_TRUE_RET_VAL(
		(access_right_value & 0x08) != 0 &&
		request_security_indicators.has_aes_gcm_encryption == FALSE,
		FALSE
	);
	ASSERT_TRUE_RET_VAL(
		(access_right_value & 0x10) != 0 &&
		request_security_indicators.has_digital_signature == FALSE,
		FALSE
	);

	/* Bring the attribute access right and method access right to DLMS Library to enforce security of response */
	if (p_dispatch_context != NULL) {
		p_dispatch_context->attribute_access_right = attribute_access_right_value;
		p_dispatch_context->method_access_right = method_access_right_value;
	}

	return (TRUE);
}
/******************************************************************************
* Function Name : R_DLMS_CLASSES_EncodeFixedString
* Interface     : uint16_t R_DLMS_CLASSES_EncodeFixedString(
*               :     MandatoryString out_data,
*               :     attr_type_t type        ,
*               :     FixedString * p_object  ,
*               : );
* Description   : 
* Arguments     : MandatoryString out_data:
*               : attr_type_t type        :
*               : FixedString * p_object  :
* Function Calls: 
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_CLASSES_EncodeFixedString(
	MandatoryString out_data,
	attr_type_t type,
	FixedString *p_object
)
{
	if (p_object != NULL) {
		return R_DLMS_CLASSES_EncodeCommonType(
			out_data.p_content,
			out_data.length,
			type,
			p_object->p_content,
			p_object->length
		);
	}

	return 0;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DecodeFixedString
* Interface     : uint16_t R_DLMS_CLASSES_DecodeFixedString(
*               :     FixedString * p_object ,
*               :     attr_type_t type       ,
*               :     MandatoryString in_data,
*               : );
* Description   : 
* Arguments     : FixedString * p_object :
*               : attr_type_t type       :
*               : MandatoryString in_data:
* Function Calls: 
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_CLASSES_DecodeFixedString(
	FixedString *p_object,
	attr_type_t type,
	MandatoryString in_data
)
{
	if (p_object != NULL) {
		return R_DLMS_CLASSES_DecodeCommonType(
			p_object->p_content,
			p_object->length,
			type,
			in_data.p_content,
			in_data.length
		);
	}

	return 0;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_EncodeVariantString
* Interface     : uint16_t R_DLMS_CLASSES_EncodeVariantString(
*               :     MandatoryString out_data,
*               :     Data_Tag data_type      ,
*               :     VariantString * p_object,
*               : );
* Description   : 
* Arguments     : MandatoryString out_data:
*               : Data_Tag data_type      :
*               : VariantString * p_object:
* Function Calls: 
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_CLASSES_EncodeVariantString(
	MandatoryString out_data,
	Data_Tag data_type,
	VariantString *p_object
)
{
	if (p_object != NULL &&
		(data_type == TAG_DATA_BIT_STRING ||
		 data_type == TAG_DATA_OCTET_STRING ||
		 data_type == TAG_DATA_VISIBLE_STRING ||
		 data_type == TAG_DATA_UTF8_STRING))
	{
		return R_DLMS_CLASSES_EncodeCommonType(
			out_data.p_content,
			out_data.length,
			data_type,
			p_object->p_content,
			p_object->length
		);
	}

	return 0;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DecodeVariantString
* Interface     : uint16_t R_DLMS_CLASSES_DecodeVariantString(
*               :     VariantString * p_object,
*               :     Data_Tag data_type      ,
*               :     MandatoryString in_data ,
*               : );
* Description   : 
* Arguments     : VariantString * p_object:
*               : Data_Tag data_type      :
*               : MandatoryString in_data :
* Function Calls: 
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_CLASSES_DecodeVariantString(
	VariantString	*p_object,
	Data_Tag		data_type,
	MandatoryString in_data
)
{
	uint16_t  decoded_length = 0;	/* Decoded length, to return the used length */
	uint16_t  item_length = 0;		/* Item length in the in_data.p_content */
	uint16_t  temp_len;

	/* Check input parameter */
	if (in_data.p_content == NULL || in_data.length == 0)
	{
		return (decoded_length);	/* Not decode anything */
	}

	/* Check the data type */
	if (*in_data.p_content++ != data_type) {
		return (decoded_length);
	}

	/* Decode buffer base on select of type */
	switch (data_type)
	{
		/* Optimized for variant size */
		case TAG_DATA_BIT_STRING:
		case TAG_DATA_OCTET_STRING:
		case TAG_DATA_VISIBLE_STRING:
		case TAG_DATA_UTF8_STRING:
			if (in_data.length >= 2)
			{
				/* Get the item length */
				temp_len = R_BER_LengthDecode(in_data.p_content, &item_length);

				if (p_object != NULL) {
					p_object->length = item_length;
				}

				in_data.p_content += temp_len;

				if (data_type == TAG_DATA_BIT_STRING) {
					item_length += 7;
					item_length /= 8;
				}


				decoded_length = item_length + temp_len + 1;

				if (item_length > 0) {
					if (p_object != NULL &&
						p_object->p_content != NULL &&
						p_object->alloc_size >= item_length)
					{
						memcpy(p_object->p_content, in_data.p_content, item_length);
					}
					else {
						decoded_length = 0;		/* Error on writing to output memory */
					}
				}
			}
			break;

		/* Error on selection */
		default:
			/* Do nothing */
			break;
	}

	ASSERT_TRUE_RET_ZERO(decoded_length > in_data.length);

	return (decoded_length);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_EncodeAbstractFixedArray
* Interface     : uint16_t R_DLMS_CLASSES_EncodeAbstractFixedArray(
*               :     MandatoryString out_data      ,
*               :     AbstractFixedArray * p_object ,
*               :     fp_obj_encoder_func fp_encoder,
*               :     uint16_t element_size         ,
*               : );
* Description   : 
* Arguments     : MandatoryString out_data      :
*               : AbstractFixedArray * p_object :
*               : fp_obj_encoder_func fp_encoder:
*               : uint16_t element_size         :
* Function Calls: 
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_CLASSES_EncodeAbstractFixedArray(
	MandatoryString out_data,
	AbstractFixedArray *p_object,
	fp_obj_encoder_func fp_encoder,
	uint16_t element_size
)
{
	uint16_t		length;
	uint16_t		index, reentrant_index;
	uint8_t			u8;
	uint8_t			*p_head = out_data.p_content;
	MandatoryString old_out_data;
	
	/* Check input parameter */
	ASSERT_TRUE_RET_ZERO(
		fp_encoder == NULL || element_size == 0 ||
		out_data.p_content == NULL || out_data.length == 0 ||
		p_object == NULL
	);

	if (g_classes_complex_distributor_current_assc_id < DLMS_MAX_ASSOCIATION_SUPPORT &&
		g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count > 0 &&
		g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count <= CLASSES_ENCODER_SESSION_MAX_REENTRANT)
	{
		/* Get reentrant index of current encoder call */
		reentrant_index = g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count - 1;
		
		/* Get index of current attribute distribution */
		index = g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].element_index[reentrant_index];
		
		/* Encode array tag, length if first element */
		if (index == 0) {
			OBIS_ENCODE_ARRAY_TYPE_DEF(u8, out_data, p_object->length);
		}
		
		/* Encode elements when out_data enough buffer to store */
		old_out_data = out_data;
		while (index < p_object->length) {
			ASSERT_TRUE_RET_ZERO(p_object->p_content == NULL);
			length = (*fp_encoder)(out_data, (uint8_t *)p_object->p_content + index * element_size);
			if (length == 0 || length > out_data.length) {
				break;
			}
			OBIS_ADVANCE_BUFFER(out_data, length);
			index++;
			g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].element_index[reentrant_index]++;
		}
		
		/* Return 0 if no element encoded, not enough buffer for encoding of 1 array element */ 
		if (p_object->length > 0 && old_out_data.p_content == out_data.p_content) {
			return 0;
		}
		
		/* Mark partial encoding as TRUE when not all elements encoded else FALSE */
		if (index < p_object->length) {
			g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].partial[reentrant_index] = TRUE;
		}
		else {
			g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].partial[reentrant_index] = FALSE;
		}
	}
	else {
		/*
		 * Fatal error, no entrance of distributor complex type but call encoder of complex type, or,
		 * Reach max entrance, maybe due to recursive calls of distribution in encode attribute
		 */
		g_classes_array_encoder_fatal_error = TRUE;
	}
	
	return (uint16_t)(out_data.p_content - p_head);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DecodeAbstractFixedArray
* Interface     : uint16_t R_DLMS_CLASSES_DecodeAbstractFixedArray(
*               :     AbstractFixedArray * p_object ,
*               :     MandatoryString in_data       ,
*               :     fp_obj_decoder_func fp_decoder,
*               :     uint16_t element_size         ,
*               : );
* Description   : 
* Arguments     : AbstractFixedArray * p_object :
*               : MandatoryString in_data       :
*               : fp_obj_decoder_func fp_decoder:
*               : uint16_t element_size         :
* Function Calls: 
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_CLASSES_DecodeAbstractFixedArray(
	AbstractFixedArray *p_object,
	MandatoryString in_data,
	fp_obj_decoder_func fp_decoder,
	uint16_t element_size
)
{
	uint16_t	length;
	uint16_t	count;
	uint8_t		u8;
	uint8_t		*p_head = in_data.p_content;

	/* Check input parameter */
	ASSERT_TRUE_RET_ZERO(
		fp_decoder == NULL || element_size == 0 ||
		in_data.p_content == NULL || in_data.length == 0 ||
		p_object == NULL
	);

	length = p_object->length;
	OBIS_DECODE_ARRAY_TYPE_DEF(u8, &p_object->length, length, in_data);
	for (count = 0; count < p_object->length; count++) {
		ASSERT_TRUE_RET_ZERO(p_object->p_content == NULL);
		length = (*fp_decoder)((uint8_t *)p_object->p_content + count * element_size, in_data);
		ASSERT_TRUE_RET_ZERO(length == 0 || length > in_data.length);
		OBIS_ADVANCE_BUFFER(in_data, length);
	}

	return (uint16_t)(in_data.p_content - p_head);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_EncodeAbstractVariantArray
* Interface     : uint16_t R_DLMS_CLASSES_EncodeAbstractVariantArray(
*               :     MandatoryString out_data       ,
*               :     AbstractVariantArray * p_object,
*               :     fp_obj_encoder_func fp_encoder ,
*               :     uint16_t element_size          ,
*               : );
* Description   : 
* Arguments     : MandatoryString out_data       :
*               : AbstractVariantArray * p_object:
*               : fp_obj_encoder_func fp_encoder :
*               : uint16_t element_size          :
* Function Calls: 
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_CLASSES_EncodeAbstractVariantArray(
	MandatoryString out_data,
	AbstractVariantArray *p_object,
	fp_obj_encoder_func fp_encoder,
	uint16_t element_size
)
{
	uint16_t		length;
	uint16_t		reentrant_index;
	uint16_t		loop_index, element_index;
	uint8_t			u8;
	uint8_t			*p_head = out_data.p_content;
	MandatoryString old_out_data;
	
	/* Check input parameter */
	ASSERT_TRUE_RET_ZERO(
		fp_encoder == NULL || element_size == 0 ||
		out_data.p_content == NULL || out_data.length == 0 ||
		p_object == NULL
	);

	if (g_classes_complex_distributor_current_assc_id < DLMS_MAX_ASSOCIATION_SUPPORT &&
		g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count > 0 &&
		g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count <= CLASSES_ENCODER_SESSION_MAX_REENTRANT)
	{
		/* Get reentrant index of current encoder call */
		reentrant_index = g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count - 1;
		
		/* Get index of current attribute distribution */
		loop_index = g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].loop_index[reentrant_index];
		element_index = g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].element_index[reentrant_index];
		
		/* Encode array tag, length if first element */
		if (element_index == 0) {
			OBIS_ENCODE_ARRAY_TYPE_DEF(u8, out_data, p_object->length);
		}

		/* Encode elements when out_data enough buffer to store */
		old_out_data = out_data;
		while (loop_index < p_object->alloc_size && element_index < p_object->length)
		{
			if (p_object->p_active == NULL ||
				p_object->p_active[loop_index] == TRUE) {
				ASSERT_TRUE_RET_ZERO(p_object->p_content == NULL);
				length = (*fp_encoder)(out_data, (uint8_t *)p_object->p_content + loop_index * element_size);
				if (length == 0 || length > out_data.length) {
					break;
				}
				OBIS_ADVANCE_BUFFER(out_data, length);
				element_index++;
				g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].element_index[reentrant_index]++;
			}

			loop_index++;
			g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].loop_index[reentrant_index]++;
		}
		
		/* Return 0 if no element encoded, not enough buffer for encoding of 1 array element */ 
		if (p_object->length > 0 && old_out_data.p_content == out_data.p_content) {
			return 0;
		}
		
		/* Mark partial encoding as TRUE when not all elements encoded else FALSE */
		if (element_index < p_object->length) {
			g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].partial[reentrant_index] = TRUE;
		}
		else {
			g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].partial[reentrant_index] = FALSE;
		}
	}
	else {
		/*
		 * Fatal error, no entrance of distributor complex type but call encoder of complex type, or,
		 * Reach max entrance, maybe due to recursive calls of distribution in encode attribute
		 */
		g_classes_array_encoder_fatal_error = TRUE;
	}
	
	return (uint16_t)(out_data.p_content - p_head);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DecodeAbstractVariantArray
* Interface     : uint16_t R_DLMS_CLASSES_DecodeAbstractVariantArray(
*               :     AbstractVariantArray * p_object,
*               :     MandatoryString in_data        ,
*               :     fp_obj_decoder_func fp_decoder ,
*               :     uint16_t element_size          ,
*               : );
* Description   : 
* Arguments     : AbstractVariantArray * p_object:
*               : MandatoryString in_data        :
*               : fp_obj_decoder_func fp_decoder :
*               : uint16_t element_size          :
* Function Calls: 
* Return Value  : uint16_t
******************************************************************************/
uint16_t R_DLMS_CLASSES_DecodeAbstractVariantArray(
	AbstractVariantArray *p_object,
	MandatoryString in_data,
	fp_obj_decoder_func fp_decoder,
	uint16_t element_size
)
{
	uint16_t	length;
	uint16_t	count;
	uint8_t		u8;
	uint8_t		*p_head = in_data.p_content;

	/* Check input parameter */
	ASSERT_TRUE_RET_ZERO(
		fp_decoder == NULL || element_size == 0 ||
		in_data.p_content == NULL || in_data.length == 0 ||
		p_object == NULL
	);

	if (p_object->p_active != NULL) {
		memset(p_object->p_active, FALSE, p_object->alloc_size);
	}
	OBIS_DECODE_ARRAY_TYPE_DEF(u8, &p_object->length, p_object->alloc_size, in_data);
	for (count = 0; count < p_object->length; count++) {
		ASSERT_TRUE_RET_ZERO(p_object->p_content == NULL);
		length = (*fp_decoder)((uint8_t *)p_object->p_content + count * element_size, in_data);
		ASSERT_TRUE_RET_ZERO(length == 0 || length > in_data.length);
		OBIS_ADVANCE_BUFFER(in_data, length);
		if (p_object->p_active != NULL) {
			p_object->p_active[count] = TRUE;
		}
	}

	return (uint16_t)(in_data.p_content - p_head);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_CreateDynamicObject
* Interface     : void * R_DLMS_CLASSES_CreateDynamicObject(
*               :     distributor_params_t * p_params,
*               :     void * p_object                ,
*               :     uint16_t object_size           ,
*               :     uint16_t option,
*               : );
* Description   : Create a object on dymanic malloc buffer
* Arguments     : distributor_params_t * p_params:
*               : void * p_object                :
*               : uint16_t object_size           :
*               : uint16_t options               :
* Return Value  : void *
******************************************************************************/
void *R_DLMS_CLASSES_CreateObject(
	distributor_params_t *p_params,
	void *p_object,
	uint16_t object_size,
	uint16_t options
)
{
	uint8_t *p_clone_obj = (uint8_t *)p_object;

	ASSERT_TRUE_RET_NULL(
		p_params == NULL ||
		OBIS_MALLOC_IS_NULL(p_params) ||
		OBIS_MALLOC_REMAIN_SIZE(p_params) == 0 ||
		object_size == 0
	);

	p_clone_obj = OBIS_MALLOC_GET_POINTER(p_params);
	if (p_object != NULL)
	{
		if (options & OBIS_MALLOC_OPTION_MEMLINK) {
			OBIS_MALLOC_MEMLINK_RET_NULL(p_params, p_object, p_clone_obj, object_size);
		}
		if (options & OBIS_MALLOC_OPTION_CLONE) {
			memcpy(p_clone_obj, p_object, object_size);
		}
	}

	OBIS_MALLOC_ADVANCE_BUFFER(p_params, object_size);

	return p_clone_obj;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_CreateFixedArray
* Interface     : AbstractFixedArray * R_DLMS_CLASSES_CreateFixedArray(
*               :     distributor_params_t * p_params,
*               :     AbstractFixedArray * p_object  ,
*               :     uint16_t element_size          ,
*               :     uint16_t options               ,
*               : );
* Description   : Create a fixed array on dynamic buffer
* Arguments     : distributor_params_t * p_params:
*               : AbstractFixedArray * p_object  :
*               : uint16_t element_size          :
*               : uint16_t options               :
* Return Value  : AbstractFixedArray *
******************************************************************************/
AbstractFixedArray *R_DLMS_CLASSES_CreateFixedArray(
	distributor_params_t *p_params,
	AbstractFixedArray *p_object,
	uint16_t element_size,
	uint16_t options
)
{
	uint16_t			bytes_length;
	uint8_t				*p_alloc, *p_head;
	AbstractFixedArray	*p_clone_obj = p_object;	/* Default is construct */

	ASSERT_TRUE_RET_NULL(
		p_params == NULL || p_object == NULL ||
		OBIS_MALLOC_IS_NULL(p_params) ||
		OBIS_MALLOC_REMAIN_SIZE(p_params) == 0 ||
		element_size == 0
	);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	if (options & OBIS_MALLOC_OPTION_CREATENEW) {
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, AbstractFixedArray, p_alloc);
		p_clone_obj->length = p_object->length;
	}
	bytes_length = p_clone_obj->length;
	if (options & OBIS_MALLOC_OPTION_BITSTRING) {
		bytes_length += 7;
		bytes_length /= 8;
	}
	p_clone_obj->p_content = p_alloc;
	p_alloc += bytes_length * element_size;
	if ((options & OBIS_MALLOC_OPTION_MEMLINK) && p_object != p_clone_obj) {
		OBIS_MALLOC_MEMLINK_RET_NULL(
			p_params,
			p_object->p_content,
			p_clone_obj->p_content,
			bytes_length * element_size
		);
	}
	if ((options & OBIS_MALLOC_OPTION_CLONE) && p_object != p_clone_obj) {
		memcpy(p_clone_obj->p_content, p_object->p_content, bytes_length * element_size);
	}
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_CreateVariantArray
* Interface     : AbstractVariantArray * R_DLMS_CLASSES_CreateVariantArray(
*               :     distributor_params_t * p_params,
*               :     AbstractVariantArray * p_object,
*               :     uint16_t element_size          ,
*               :     uint16_t options               ,
*               : );
* Description   : 
* Arguments     : distributor_params_t * p_params:
*               : AbstractVariantArray * p_object:
*               : uint16_t element_size          :
*               : uint16_t options               :
* Return Value  : AbstractVariantArray *
******************************************************************************/
AbstractVariantArray *R_DLMS_CLASSES_CreateVariantArray(
	distributor_params_t *p_params,
	AbstractVariantArray *p_object,
	uint16_t element_size,
	uint16_t options
)
{
	uint16_t				bytes_length;
	uint8_t					*p_alloc, *p_head;
	AbstractVariantArray	*p_clone_obj = p_object;	/* Default is construct */

	ASSERT_TRUE_RET_NULL(
		p_params == NULL || p_object == NULL ||
		OBIS_MALLOC_IS_NULL(p_params) ||
		OBIS_MALLOC_REMAIN_SIZE(p_params) == 0 ||
		element_size == 0
	);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	if (options & OBIS_MALLOC_OPTION_CREATENEW) {
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, AbstractVariantArray, p_alloc);
		p_clone_obj->alloc_size = p_object->alloc_size;
	}
	bytes_length = p_clone_obj->alloc_size;
	if (options & OBIS_MALLOC_OPTION_BITSTRING) {
		bytes_length += 7;
		bytes_length /= 8;
	}
	p_clone_obj->p_content = p_alloc;
	p_alloc += bytes_length * element_size;
	p_clone_obj->p_active = p_alloc;
	p_alloc += p_object->alloc_size;
	if ((options & OBIS_MALLOC_OPTION_MEMLINK) && p_object != p_clone_obj) {
		OBIS_MALLOC_MEMLINK_RET_NULL(p_params, (uint8_t *)&p_object->length  , (uint8_t *)&p_clone_obj->length  , sizeof(p_object->length));
		OBIS_MALLOC_MEMLINK_RET_NULL(p_params, (uint8_t *)p_object->p_content, (uint8_t *)p_clone_obj->p_content, bytes_length * element_size);
		if (p_object->p_active != NULL) {
			OBIS_MALLOC_MEMLINK_RET_NULL(p_params, p_object->p_active, p_clone_obj->p_active, p_object->alloc_size);
		}
	}
	if ((options & OBIS_MALLOC_OPTION_CLONE) && p_object != p_clone_obj) {
		p_clone_obj->length = p_object->length;
		memcpy(p_clone_obj->p_content, p_object->p_content, bytes_length * element_size);
		memcpy(p_clone_obj->p_active , p_object->p_active , p_object->alloc_size);
	}
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_CreateFixedString
* Interface     : FixedString * R_DLMS_CLASSES_CreateFixedString(
*               :     distributor_params_t * p_params,
*               :     FixedString * p_object         ,
*               :     uint16_t options               ,
*               : );
* Description   : 
* Arguments     : distributor_params_t * p_params:
*               : FixedString * p_object         :
*               : uint16_t options               :
* Return Value  : FixedString *
******************************************************************************/
FixedString *R_DLMS_CLASSES_CreateFixedString(
	distributor_params_t *p_params,
	FixedString *p_object,
	uint16_t options
)
{
	return (FixedString *)R_DLMS_CLASSES_CreateFixedArray(
		p_params,
		(AbstractFixedArray *)p_object,
		sizeof(uint8_t),
		options
	);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_CreateVariantString
* Interface     : VariantString * R_DLMS_CLASSES_CreateVariantString(
*               :     distributor_params_t * p_params,
*               :     VariantString * p_object       ,
*               :     uint16_t options               ,
*               : );
* Description   : 
* Arguments     : distributor_params_t * p_params:
*               : VariantString * p_object       :
*               : uint16_t options               :
* Function Calls: 
* Return Value  : VariantString *
******************************************************************************/
VariantString *R_DLMS_CLASSES_CreateVariantString(
	distributor_params_t *p_params,
	VariantString *p_object,
	uint16_t options
)
{
	uint16_t		bytes_length;
	uint8_t			*p_alloc, *p_head;
	VariantString	*p_clone_obj = p_object;	/* Default is construct */

	ASSERT_TRUE_RET_NULL(
		p_params == NULL || p_object == NULL ||
		OBIS_MALLOC_IS_NULL(p_params) ||
		OBIS_MALLOC_REMAIN_SIZE(p_params) == 0
	);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	if (options & OBIS_MALLOC_OPTION_CREATENEW) {
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, VariantString, p_alloc);
		p_clone_obj->alloc_size = p_object->alloc_size;
	}
	bytes_length = p_clone_obj->alloc_size;
	if (options & OBIS_MALLOC_OPTION_BITSTRING) {
		bytes_length += 7;
		bytes_length /= 8;
	}
	p_clone_obj->p_content = p_alloc;
	p_alloc += bytes_length;
	if ((options & OBIS_MALLOC_OPTION_MEMLINK) && p_object != p_clone_obj) {
		OBIS_MALLOC_MEMLINK_RET_NULL(p_params, (uint8_t *)&p_object->length, (uint8_t *)&p_clone_obj->length, sizeof(p_object->length));
		OBIS_MALLOC_MEMLINK_RET_NULL(p_params, (uint8_t *)p_object->p_content, (uint8_t *)p_clone_obj->p_content, bytes_length);
	}
	if ((options & OBIS_MALLOC_OPTION_CLONE) && p_object != p_clone_obj) {
		p_clone_obj->length = p_object->length;
		memcpy(p_clone_obj->p_content, p_object->p_content, bytes_length);
	}
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_CreateChoiceAndMemlink
* Interface     : choice_t * R_DLMS_CLASSES_CreateChoiceAndMemlink(
*               :     distributor_params_t * p_params,
*               :     choice_t * p_object            ,
*               :     uint16_t options               ,
*               : );
* Description   : 
* Arguments     : distributor_params_t * p_params:
*               : choice_t * p_object            :
*               : uint16_t options               :
* Function Calls: 
* Return Value  : choice_t *
******************************************************************************/
choice_t *R_DLMS_CLASSES_CreateChoice(
	distributor_params_t *p_params,
	choice_t *p_object,
	uint16_t options
)
{
	uint16_t	bytes_length;
	uint8_t		*p_alloc, *p_head;
	choice_t	*p_clone_obj = p_object;	/* Default is construct */

	ASSERT_TRUE_RET_NULL(
		p_params == NULL || p_object == NULL ||
		OBIS_MALLOC_IS_NULL(p_params) ||
		OBIS_MALLOC_REMAIN_SIZE(p_params) == 0
	);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	if (options & OBIS_MALLOC_OPTION_CREATENEW) {
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, choice_t, p_alloc);
		p_clone_obj->choice.type = p_object->choice.type;
		p_clone_obj->choice.size = p_object->choice.size;
	}
	bytes_length = p_object->choice.size;
	if (p_object->choice.type == TAG_DATA_BIT_STRING) {
		bytes_length += 7;
		bytes_length /= 8;
	}
	p_clone_obj->buffer = p_alloc;
	p_alloc += bytes_length;
	if ((options & OBIS_MALLOC_OPTION_MEMLINK) && p_object != p_clone_obj) {
		OBIS_MALLOC_MEMLINK_RET_NULL(p_params, (uint8_t *)p_object->buffer, (uint8_t *)p_clone_obj->buffer, bytes_length);
	}
	if ((options & OBIS_MALLOC_OPTION_CLONE) && p_object != p_clone_obj) {
		memcpy(p_clone_obj->buffer, p_object->buffer, bytes_length);
	}
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeComplexType
* Interface     : void R_DLMS_CLASSES_DistributeComplexType(
*               :     distributor_params_t * p_params,
*               :     fp_obj_encoder_func fp_encoder ,
*               :     fp_obj_decoder_func fp_decoder ,
*               :     fp_obj_redirect_t fp_redirect  ,
*               :     void * p_object                ,
*               : );
* Description   : 
* Arguments     : distributor_params_t * p_params:
*               : fp_obj_encoder_func fp_encoder :
*               : fp_obj_decoder_func fp_decoder :
*               : fp_obj_redirect_t fp_redirect  :
*               : void * p_object                :
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeComplexType(
	distributor_params_t *p_params,
	fp_obj_encoder_func fp_encoder,
	fp_obj_decoder_func fp_decoder,
	fp_obj_redirect_t	fp_redirect,
	void *p_object
)
{
	void	 *p_origin_object = p_object;
	uint16_t decoded_length;
	uint16_t reentrant_index;

	if (p_params != NULL)
	{
		g_classes_complex_distributor_current_assc_id = p_params->connected_assc_id;
	
		if (p_params->req_type == REQ_TYPE_GET) {
			ASSERT_TRUE_RET(p_object == NULL);
			if (g_classes_complex_distributor_current_assc_id < DLMS_MAX_ASSOCIATION_SUPPORT &&
				g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count < CLASSES_ENCODER_SESSION_MAX_REENTRANT &&
				fp_encoder != NULL) {
				/*
				 * Share information to abstract encoders (AbstractFixedArrayEncoder, AbstractVariantArrayEncoder)
				 * Mark current connected assc id, reset loop index and element index to 0, increase reentrant count for nested call of encoder if recursive
				 */
				reentrant_index = g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count;
				g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count++;	/* Next entrance if nested in (*fp_encoder) call */
				if (p_params->service_type.get == COSEM_GET_REQUEST_NORMAL) {
					g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].loop_index[reentrant_index] = 0;
					g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].element_index[reentrant_index] = 0;
				}
				*p_params->p_out_encoded_len = (*fp_encoder)(
					p_params->out_data,
					p_object
				);
				if (*p_params->p_out_encoded_len > 0) {
					OBIS_DATA_ACCESS_RESULT(
						p_params->result,
						VAL_DATA_ACCESS_RESULT_SUCCESS,
						g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].partial[reentrant_index]
					);
					OBIS_DISTRIBUTION_SUCCESS(p_params->result);
				}
				else {
					OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
				}
				g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count--;
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
		else if (p_params->req_type == REQ_TYPE_SET) {
			if (fp_decoder != NULL) {
				if (fp_redirect != NULL) {
					p_object = (*fp_redirect)(p_params, p_object);
				}
				ASSERT_TRUE_RET(p_object == NULL);
				if (p_origin_object != p_object) {
					p_params->service_params.created = TRUE;
				}

				decoded_length = (*fp_decoder)(p_object, p_params->in_data);
				if (decoded_length > 0) {
					if (p_params->service_params.created == TRUE) {
						p_params->service_params.decode_success = TRUE;
					}
					OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
					OBIS_DISTRIBUTION_SUCCESS(p_params->result);
				}
				else {
					OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
				}
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
	}
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeBasicType
* Interface     : None R_DLMS_CLASSES_DistributeBasicType(
*               :     distributor_params_t * p_params,
*               :     void * p_object                ,
*               :     uint16_t size                  ,
*               : );
* Description   : 
* Arguments     : distributor_params_t * p_params:
*               : void * p_object                :
*               : uint16_t size                  :
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeBasicType(
	distributor_params_t *p_params,
	attr_type_t type,
	void *p_object,
	uint16_t size
)
{
	void	 *p_origin_object = p_object;
	uint16_t decoded_length;

	if (p_params != NULL)
	{
		if (p_params->req_type == REQ_TYPE_GET) {
			*p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
				p_params->out_data.p_content,
				p_params->out_data.length,
				type,
				(uint8_t *)p_object,
				size
			);
			if (*p_params->p_out_encoded_len > 0) {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
				OBIS_DISTRIBUTION_SUCCESS(p_params->result);
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
		else if (p_params->req_type == REQ_TYPE_SET) {

			/*
			 * clone object buffer to malloc buffer of distributor service
			 * and register a memcpy call at the end of class distribution
			 */
			p_object = R_DLMS_CLASSES_CreateObject(
				p_params,
				p_object,
				size,
				OBIS_MALLOC_OPTION_CREATENEW |
				OBIS_MALLOC_OPTION_MEMLINK |
				OBIS_MALLOC_OPTION_CLONE
			);
			ASSERT_TRUE_RET(p_object == NULL);
			if (p_origin_object != p_object) {
				p_params->service_params.created = TRUE;
			}

			decoded_length = R_DLMS_CLASSES_DecodeCommonType(
				p_object,
				size,
				type,
				p_params->in_data.p_content,
				p_params->in_data.length
			);
			if (decoded_length > 0) {
				if (p_params->service_params.created == TRUE) {
					p_params->service_params.decode_success = TRUE;
				}
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
				OBIS_DISTRIBUTION_SUCCESS(p_params->result);
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
	}
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeFixedString
* Interface     : None R_DLMS_CLASSES_DistributeFixedString(
*               :     distributor_params_t * p_params,
*               :     attr_type_t type               ,
*               :     FixedString * p_object         ,
*               : );
* Description   : 
* Arguments     : distributor_params_t * p_params:
*               : attr_type_t type               :
*               : FixedString * p_object         :
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeFixedString(
	distributor_params_t *p_params,
	attr_type_t type,
	FixedString *p_object
)
{
	VariantString	*p_variant_string = NULL;
	uint16_t		decoded_length = 0;
	uint16_t        string_size;
	VariantString	var_string = {
		p_object->p_content,
		p_object->length,
		p_object->length
	};

	if (p_params != NULL)
	{
		if (p_params->req_type == REQ_TYPE_GET) {

			ASSERT_TRUE_RET(p_object == NULL);
			R_DLMS_CLASSES_DistributeVariantString(p_params, type, &var_string);
		}
		else if (p_params->req_type == REQ_TYPE_SET) {

			/*
			 * Client can input any string length, 0 byte, 4 bytes, n bytes, 
			 * need to decode the client input string as a variant-length-string.
			 *
			 * SET value to attribute now not use attribute pointer to update value by memlinks anymore.
			 * User function is called after decode of client input string, so a new object is always created
			 * in temporary buffer (malloc buffer).
			 */
			R_BER_LengthDecode(p_params->in_data.p_content + 1, &string_size);
			if (string_size < OBIS_MALLOC_REMAIN_SIZE(p_params))
			{
				p_variant_string = R_DLMS_CLASSES_CreatNew_Octetstring(p_params, string_size);
			}
			
			if (p_variant_string != NULL) {
				decoded_length = R_DLMS_CLASSES_DecodeVariantString(p_variant_string, type, p_params->in_data);
				p_params->service_params.created = TRUE;
			}

			if (decoded_length > 0) {
				if (p_params->service_params.created == TRUE) {
					p_params->service_params.decode_success = TRUE;
				}
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
				OBIS_DISTRIBUTION_SUCCESS(p_params->result);
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
	}
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeVariantString
* Interface     : None R_DLMS_CLASSES_DistributeVariantString(
*               :     distributor_params_t * p_params,
*               :     attr_type_t type               ,
*               :     VariantString * p_object       ,
*               : );
* Description   : 
* Arguments     : distributor_params_t * p_params:
*               : attr_type_t type               :
*               : VariantString * p_object       :
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeVariantString(
	distributor_params_t *p_params,
	attr_type_t type,
	VariantString *p_object
)
{
	void	 *p_origin_object = p_object;
	uint16_t decoded_length;
	uint16_t remaining_malloc_size;
	
	if (p_params != NULL)
	{
		if (p_params->req_type == REQ_TYPE_GET) {

			ASSERT_TRUE_RET(p_object == NULL);
			*p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
				p_params->out_data.p_content,
				p_params->out_data.length,
				type,
				p_object->p_content,
				p_object->length
			);
			if (*p_params->p_out_encoded_len > 0) {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
				OBIS_DISTRIBUTION_SUCCESS(p_params->result);
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
		else if (p_params->req_type == REQ_TYPE_SET) {

			/*
			 * clone object buffer to malloc buffer of distributor service
			 * and register a memcpy call at the end of class distribution
			 */
			p_object = R_DLMS_CLASSES_RedirectVariantString(
				p_params,
				p_object,
				(type == TAG_DATA_BIT_STRING ? OBIS_MALLOC_OPTION_BITSTRING : OBIS_MALLOC_OPTION_NONE)
			);
			if(p_object == NULL)
			{
				remaining_malloc_size = OBIS_MALLOC_REMAIN_SIZE(p_params) - 10;
				p_object = R_DLMS_CLASSES_CreatNew_Octetstring(p_params, remaining_malloc_size);
			}
			else
			{

			}
			if (p_origin_object != p_object) {
				p_params->service_params.created = TRUE;
			}

			decoded_length = R_DLMS_CLASSES_DecodeVariantString(p_object, type, p_params->in_data);
			if (decoded_length > 0 && p_object->length <= p_object->alloc_size) {
				if (p_params->service_params.created == TRUE) {
					p_params->service_params.decode_success = TRUE;
				}
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
				OBIS_DISTRIBUTION_SUCCESS(p_params->result);
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
	}
}
/******************************************************************************
* Function Name : R_DLMS_CLASSES_Distribute_ArrayofStructure
* Interface     : void R_DLMS_CLASSES_Distribute_ArrayofStructure(
*               :     distributor_params_t * p_params,
*               :     fp_obj_encoder_func fp_encoder ,
*               :     fp_obj_decoder_func fp_decoder ,
*               :     fp_obj_redirect_t fp_redirect  ,
*               :     void * p_object                ,
*               : );
* Description   : 
* Arguments     : distributor_params_t * p_params:
*               : fp_obj_encoder_func fp_encoder :
*               : fp_obj_decoder_func fp_decoder :
*               : fp_obj_redirect_t fp_redirect  :
*               : void * p_object                :
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Distribute_ArrayofStructure(
	distributor_params_t 				*p_params,
	fp_obj_encoder_func 				fp_encoder,
	fp_obj_decoder_func 				fp_decoder,
	fp_obj_structure_array_redirect_t	fp_redirect,
	void *p_object
)
{
	void	 *p_origin_object = p_object;
	uint16_t decoded_length;
	uint16_t reentrant_index;
	uint16_t array_length_from_client_set;
	uint8_t * p_head = p_params->in_data.p_content;
	if (p_params != NULL)
	{
		g_classes_complex_distributor_current_assc_id = p_params->connected_assc_id;
	
		if (p_params->req_type == REQ_TYPE_GET) {
			ASSERT_TRUE_RET(p_object == NULL);
			if (g_classes_complex_distributor_current_assc_id < DLMS_MAX_ASSOCIATION_SUPPORT &&
				g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count < CLASSES_ENCODER_SESSION_MAX_REENTRANT &&
				fp_encoder != NULL) {
				/*
				 * Share information to abstract encoders (AbstractFixedArrayEncoder, AbstractVariantArrayEncoder)
				 * Mark current connected assc id, reset loop index and element index to 0, increase reentrant count for nested call of encoder if recursive
				 */
				reentrant_index = g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count;
				g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count++;	/* Next entrance if nested in (*fp_encoder) call */
				if (p_params->service_type.get == COSEM_GET_REQUEST_NORMAL) {
					g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].loop_index[reentrant_index] = 0;
					g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].element_index[reentrant_index] = 0;
				}
				*p_params->p_out_encoded_len = (*fp_encoder)(
					p_params->out_data,
					p_object
				);
				if (*p_params->p_out_encoded_len > 0) {
					OBIS_DATA_ACCESS_RESULT(
						p_params->result,
						VAL_DATA_ACCESS_RESULT_SUCCESS,
						g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].partial[reentrant_index]
					);
					OBIS_DISTRIBUTION_SUCCESS(p_params->result);
				}
				else {
					OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
				}
				g_classes_array_encoder_session[g_classes_complex_distributor_current_assc_id].reentrant_count--;
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
		else if (p_params->req_type == REQ_TYPE_SET) {
			if (fp_decoder != NULL) {
				/* Get length of array */
				p_head++;
				R_BER_LengthDecode(p_head, &array_length_from_client_set);	
				if (fp_redirect != NULL) {
					p_object = (*fp_redirect)(p_params, p_object, array_length_from_client_set);
				}
				ASSERT_TRUE_RET(p_object == NULL);
				if (p_origin_object != p_object) {
					p_params->service_params.created = TRUE;
				}

				decoded_length = (*fp_decoder)(p_object, p_params->in_data);
				if (decoded_length > 0) {
					if (p_params->service_params.created == TRUE) {
						p_params->service_params.decode_success = TRUE;
					}
					OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
					OBIS_DISTRIBUTION_SUCCESS(p_params->result);
				}
				else {
					OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
				}
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
	}
}

OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeBoolean				, TAG_DATA_BOOLEAN				, uint8_t		, sizeof(uint8_t	) )			/* Encoder function for type boolean */
OBIS_DECLARE_VARIANT_STRING_ENCODER_FUNC	( R_DLMS_CLASSES_EncodeBitString			, TAG_DATA_BIT_STRING												  )			/* Encoder function for type bit-string */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeDoubleLong			, TAG_DATA_DOUBLE_LONG			, int32_t		, sizeof(int32_t	) )			/* Encoder function for type double-long */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeDoubleLongUnsigned	, TAG_DATA_DOUBLE_LONG_UNSIGNED	, uint32_t		, sizeof(uint32_t	) )			/* Encoder function for type double-long-unsigned */
OBIS_DECLARE_VARIANT_STRING_ENCODER_FUNC	( R_DLMS_CLASSES_EncodeOctetString			, TAG_DATA_OCTET_STRING												  )			/* Encoder function for type octet-string */
OBIS_DECLARE_VARIANT_STRING_ENCODER_FUNC	( R_DLMS_CLASSES_EncodeVisibleString		, TAG_DATA_VISIBLE_STRING											  )			/* Encoder function for type visible-string */
OBIS_DECLARE_VARIANT_STRING_ENCODER_FUNC	( R_DLMS_CLASSES_EncodeUtf8String			, TAG_DATA_UTF8_STRING												  )			/* Encoder function for type utf8-string */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeBcd					, TAG_DATA_BCD					, int8_t		, sizeof(int8_t		) )			/* Encoder function for type bcd */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeInteger				, TAG_DATA_INTEGER				, int8_t		, sizeof(int8_t		) )			/* Encoder function for type integer */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeLong					, TAG_DATA_LONG					, int16_t		, sizeof(int16_t	) )			/* Encoder function for type long */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeUnsigned				, TAG_DATA_UNSIGNED				, uint8_t		, sizeof(uint8_t	) )			/* Encoder function for type unsigned */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeLongUnsigned			, TAG_DATA_LONG_UNSIGNED		, uint16_t		, sizeof(uint16_t	) )			/* Encoder function for type long-unsigned */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeLong64				, TAG_DATA_LONG64				, int64_t		, sizeof(int64_t	) )			/* Encoder function for type long64 */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeLong64Unsigned		, TAG_DATA_LONG64_UNSIGNED		, uint64_t		, sizeof(uint64_t	) )			/* Encoder function for type long64-unsigned */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeEnum					, TAG_DATA_ENUM					, uint8_t		, sizeof(uint8_t	) )			/* Encoder function for type enum */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeFloat32				, TAG_DATA_FLOAT32				, float32_t		, sizeof(float32_t	) )			/* Encoder function for type float32 */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeFloat64				, TAG_DATA_FLOAT64				, double64_t	, sizeof(double64_t	) )			/* Encoder function for type float64 */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeDateTime				, TAG_DATA_DATE_TIME			, date_time_t	, sizeof(date_time_t) )			/* Encoder function for type date-time */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeDateTimeAsOctetString, TAG_DATA_OCTET_STRING			, date_time_t	, sizeof(date_time_t) )			/* Encoder function for type date-time as OctetString */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeDate					, TAG_DATA_DATE					, date_t		, sizeof(date_t		) )			/* Encoder function for type date */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeDateAsOctetString	, TAG_DATA_OCTET_STRING			, date_t		, sizeof(date_t		) )			/* Encoder function for type date as OctetString */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeTime					, TAG_DATA_TIME					, time_t		, sizeof(time_t		) )			/* Encoder function for type time */
OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC		( R_DLMS_CLASSES_EncodeTimeAsOctetString	, TAG_DATA_OCTET_STRING			, time_t		, sizeof(time_t		) )			/* Encoder function for type time as OctetString */

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeChoice, choice_t)
{
	if (p_object != NULL) {
		return R_DLMS_CLASSES_EncodeCommonType(
			out_data.p_content,
			out_data.length,
			p_object->choice.type,
			(uint8_t *)p_object->buffer,
			p_object->choice.size
		);
	}

	return 0;
}

OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeBoolean				, TAG_DATA_BOOLEAN				, uint8_t		, sizeof(uint8_t	) )			/* Decoder function for type boolean */
OBIS_DECLARE_VARIANT_STRING_DECODER_FUNC	( R_DLMS_CLASSES_DecodeBitString			, TAG_DATA_BIT_STRING												  )			/* Decoder function for type bit-string */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeDoubleLong			, TAG_DATA_DOUBLE_LONG			, int32_t		, sizeof(int32_t	) )			/* Decoder function for type double-long */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeDoubleLongUnsigned	, TAG_DATA_DOUBLE_LONG_UNSIGNED	, uint32_t		, sizeof(uint32_t	) )			/* Decoder function for type double-long-unsigned */
OBIS_DECLARE_VARIANT_STRING_DECODER_FUNC	( R_DLMS_CLASSES_DecodeOctetString			, TAG_DATA_OCTET_STRING												  )			/* Decoder function for type octet-string */
OBIS_DECLARE_VARIANT_STRING_DECODER_FUNC	( R_DLMS_CLASSES_DecodeVisibleString		, TAG_DATA_VISIBLE_STRING											  )			/* Decoder function for type visible-string */
OBIS_DECLARE_VARIANT_STRING_DECODER_FUNC	( R_DLMS_CLASSES_DecodeUtf8String			, TAG_DATA_UTF8_STRING												  )			/* Decoder function for type utf8-string */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeBcd					, TAG_DATA_BCD					, int8_t		, sizeof(int8_t		) )			/* Decoder function for type bcd */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeInteger				, TAG_DATA_INTEGER				, int8_t		, sizeof(int8_t		) )			/* Decoder function for type integer */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeLong					, TAG_DATA_LONG					, int16_t		, sizeof(int16_t	) )			/* Decoder function for type long */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeUnsigned				, TAG_DATA_UNSIGNED				, uint8_t		, sizeof(uint8_t	) )			/* Decoder function for type unsigned */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeLongUnsigned			, TAG_DATA_LONG_UNSIGNED		, uint16_t		, sizeof(uint16_t	) )			/* Decoder function for type long-unsigned */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeLong64				, TAG_DATA_LONG64				, int64_t		, sizeof(int64_t	) )			/* Decoder function for type long64 */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeLong64Unsigned		, TAG_DATA_LONG64_UNSIGNED		, uint64_t		, sizeof(uint64_t	) )			/* Decoder function for type long64-unsigned */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeEnum					, TAG_DATA_ENUM					, uint8_t		, sizeof(uint8_t	) )			/* Decoder function for type enum */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeFloat32				, TAG_DATA_FLOAT32				, float32_t		, sizeof(float32_t	) )			/* Decoder function for type float32 */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeFloat64				, TAG_DATA_FLOAT64				, double64_t	, sizeof(double64_t	) )			/* Decoder function for type float64 */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeDateTime				, TAG_DATA_DATE_TIME			, date_time_t	, sizeof(date_time_t) )			/* Decoder function for type date-time */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeDateTimeAsOctetString, TAG_DATA_OCTET_STRING			, date_time_t	, sizeof(date_time_t) )			/* Decoder function for type date-time as OctetString */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeDate					, TAG_DATA_DATE					, date_t		, sizeof(date_t		) )			/* Decoder function for type date */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeDateAsOctetString	, TAG_DATA_OCTET_STRING			, date_t		, sizeof(date_t		) )			/* Decoder function for type date as OctetString */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeTime					, TAG_DATA_TIME					, time_t		, sizeof(time_t		) )			/* Decoder function for type time */
OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC		( R_DLMS_CLASSES_DecodeTimeAsOctetString	, TAG_DATA_OCTET_STRING			, time_t		, sizeof(time_t		) )			/* Decoder function for type time as OctetString */

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeChoice, choice_t)
{
	if (p_object != NULL) {
		return R_DLMS_CLASSES_DecodeCommonType(
			(uint8_t *)p_object->buffer,
			p_object->choice.size,
			p_object->choice.type,
			in_data.p_content,
			in_data.length
		);
	}

	return 0;
}

/* ----------------------------------
 * Fixed array encoders & decoder
 * ----------------------------------*/
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayBoolean				, FixedArrayUint8_t			, R_DLMS_CLASSES_EncodeBoolean				)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayBitString				, FixedArrayBitString		, R_DLMS_CLASSES_EncodeBitString			)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayDoubleLong				, FixedArrayInt32_t			, R_DLMS_CLASSES_EncodeDoubleLong			)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayDoubleLongUnsigned		, FixedArrayUint32_t		, R_DLMS_CLASSES_EncodeDoubleLongUnsigned	)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayOctetString			, FixedArrayOctetString		, R_DLMS_CLASSES_EncodeOctetString			)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayVisibleString			, FixedArrayVisibleString	, R_DLMS_CLASSES_EncodeVisibleString		)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayUtf8String				, FixedArrayUtf8String		, R_DLMS_CLASSES_EncodeUtf8String			)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayBcd					, FixedArrayInt8_t			, R_DLMS_CLASSES_EncodeBcd					)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayInteger				, FixedArrayInt8_t			, R_DLMS_CLASSES_EncodeInteger				)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayLong					, FixedArrayInt16_t			, R_DLMS_CLASSES_EncodeLong					)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayUnsigned				, FixedArrayUint8_t			, R_DLMS_CLASSES_EncodeUnsigned				)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayLongUnsigned			, FixedArrayUint16_t		, R_DLMS_CLASSES_EncodeLongUnsigned			)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayLong64					, FixedArrayInt64_t			, R_DLMS_CLASSES_EncodeLong64				)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayLong64Unsigned			, FixedArrayUint64_t		, R_DLMS_CLASSES_EncodeLong64Unsigned		)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayEnum					, FixedArrayUint8_t			, R_DLMS_CLASSES_EncodeEnum					)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayFloat32				, FixedArrayFloat32_t		, R_DLMS_CLASSES_EncodeFloat32				)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayFloat64				, FixedArrayDouble64_t		, R_DLMS_CLASSES_EncodeFloat64				)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayDateTime				, FixedArrayDateTime_t		, R_DLMS_CLASSES_EncodeDateTime				)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayDateTimeAsOctetString	, FixedArrayDateTime_t		, R_DLMS_CLASSES_EncodeDateTimeAsOctetString)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayDate					, FixedArrayDate_t			, R_DLMS_CLASSES_EncodeDate					)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayDateAsOctetString		, FixedArrayDate_t			, R_DLMS_CLASSES_EncodeDateAsOctetString	)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayTime					, FixedArrayTime_t			, R_DLMS_CLASSES_EncodeTime					)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayTimeAsOctetString		, FixedArrayTime_t			, R_DLMS_CLASSES_EncodeTimeAsOctetString	)
OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeFixedArrayChoice					, FixedArrayChoice_t		, R_DLMS_CLASSES_EncodeChoice				)

OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayBoolean				, FixedArrayUint8_t			, R_DLMS_CLASSES_DecodeBoolean				)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayBitString				, FixedArrayBitString		, R_DLMS_CLASSES_DecodeBitString			)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayDoubleLong				, FixedArrayInt32_t			, R_DLMS_CLASSES_DecodeDoubleLong			)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayDoubleLongUnsigned		, FixedArrayUint32_t		, R_DLMS_CLASSES_DecodeDoubleLongUnsigned	)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayOctetString			, FixedArrayOctetString		, R_DLMS_CLASSES_DecodeOctetString			)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayVisibleString			, FixedArrayVisibleString	, R_DLMS_CLASSES_DecodeVisibleString		)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayUtf8String				, FixedArrayUtf8String		, R_DLMS_CLASSES_DecodeUtf8String			)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayBcd					, FixedArrayInt8_t			, R_DLMS_CLASSES_DecodeBcd					)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayInteger				, FixedArrayInt8_t			, R_DLMS_CLASSES_DecodeInteger				)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayLong					, FixedArrayInt16_t			, R_DLMS_CLASSES_DecodeLong					)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayUnsigned				, FixedArrayUint8_t			, R_DLMS_CLASSES_DecodeUnsigned				)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayLongUnsigned			, FixedArrayUint16_t		, R_DLMS_CLASSES_DecodeLongUnsigned			)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayLong64					, FixedArrayInt64_t			, R_DLMS_CLASSES_DecodeLong64				)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayLong64Unsigned			, FixedArrayUint64_t		, R_DLMS_CLASSES_DecodeLong64Unsigned		)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayEnum					, FixedArrayUint8_t			, R_DLMS_CLASSES_DecodeEnum					)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayFloat32				, FixedArrayFloat32_t		, R_DLMS_CLASSES_DecodeFloat32				)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayFloat64				, FixedArrayDouble64_t		, R_DLMS_CLASSES_DecodeFloat64				)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayDateTime				, FixedArrayDateTime_t		, R_DLMS_CLASSES_DecodeDateTime				)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayDateTimeAsOctetString	, FixedArrayDateTime_t		, R_DLMS_CLASSES_DecodeDateTimeAsOctetString)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayDate					, FixedArrayDate_t			, R_DLMS_CLASSES_DecodeDate					)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayDateAsOctetString		, FixedArrayDate_t			, R_DLMS_CLASSES_DecodeDateAsOctetString	)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayTime					, FixedArrayTime_t			, R_DLMS_CLASSES_DecodeTime					)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayTimeAsOctetString		, FixedArrayTime_t			, R_DLMS_CLASSES_DecodeTimeAsOctetString	)
OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeFixedArrayChoice					, FixedArrayChoice_t		, R_DLMS_CLASSES_DecodeChoice				)

/* ----------------------------------
 * Variant array encoders & decoder
 * ----------------------------------*/
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayBoolean				, VariantArrayUint8_t		, R_DLMS_CLASSES_EncodeBoolean				)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayBitString				, VariantArrayBitString		, R_DLMS_CLASSES_EncodeBitString			)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayDoubleLong				, VariantArrayInt32_t		, R_DLMS_CLASSES_EncodeDoubleLong			)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayDoubleLongUnsigned		, VariantArrayUint32_t		, R_DLMS_CLASSES_EncodeDoubleLongUnsigned	)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayOctetString			, VariantArrayOctetString	, R_DLMS_CLASSES_EncodeOctetString			)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayVisibleString			, VariantArrayVisibleString	, R_DLMS_CLASSES_EncodeVisibleString		)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayUtf8String				, VariantArrayUtf8String	, R_DLMS_CLASSES_EncodeUtf8String			)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayBcd					, VariantArrayInt8_t		, R_DLMS_CLASSES_EncodeBcd					)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayInteger				, VariantArrayInt8_t		, R_DLMS_CLASSES_EncodeInteger				)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayLong					, VariantArrayInt16_t		, R_DLMS_CLASSES_EncodeLong					)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayUnsigned				, VariantArrayUint8_t		, R_DLMS_CLASSES_EncodeUnsigned				)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayLongUnsigned			, VariantArrayUint16_t		, R_DLMS_CLASSES_EncodeLongUnsigned			)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayLong64					, VariantArrayInt64_t		, R_DLMS_CLASSES_EncodeLong64				)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayLong64Unsigned			, VariantArrayUint64_t		, R_DLMS_CLASSES_EncodeLong64Unsigned		)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayEnum					, VariantArrayUint8_t		, R_DLMS_CLASSES_EncodeEnum					)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayFloat32				, VariantArrayFloat32_t		, R_DLMS_CLASSES_EncodeFloat32				)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayFloat64				, VariantArrayDouble64_t	, R_DLMS_CLASSES_EncodeFloat64				)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayDateTime				, VariantArrayDateTime_t	, R_DLMS_CLASSES_EncodeDateTime				)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayDateTimeAsOctetString	, VariantArrayDateTime_t	, R_DLMS_CLASSES_EncodeDateTimeAsOctetString)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayDate					, VariantArrayDate_t		, R_DLMS_CLASSES_EncodeDate					)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayDateAsOctetString		, VariantArrayDate_t		, R_DLMS_CLASSES_EncodeDateAsOctetString	)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayTime					, VariantArrayTime_t		, R_DLMS_CLASSES_EncodeTime					)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayTimeAsOctetString		, VariantArrayTime_t		, R_DLMS_CLASSES_EncodeTimeAsOctetString	)
OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(R_DLMS_CLASSES_EncodeVariantArrayChoice					, VariantArrayChoice_t		, R_DLMS_CLASSES_EncodeChoice				)

OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayBoolean				, VariantArrayUint8_t		, R_DLMS_CLASSES_DecodeBoolean				)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayBitString				, VariantArrayBitString		, R_DLMS_CLASSES_DecodeBitString			)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayDoubleLong				, VariantArrayInt32_t		, R_DLMS_CLASSES_DecodeDoubleLong			)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayDoubleLongUnsigned		, VariantArrayUint32_t		, R_DLMS_CLASSES_DecodeDoubleLongUnsigned	)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayOctetString			, VariantArrayOctetString	, R_DLMS_CLASSES_DecodeOctetString			)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayVisibleString			, VariantArrayVisibleString	, R_DLMS_CLASSES_DecodeVisibleString		)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayUtf8String				, VariantArrayUtf8String	, R_DLMS_CLASSES_DecodeUtf8String			)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayBcd					, VariantArrayInt8_t		, R_DLMS_CLASSES_DecodeBcd					)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayInteger				, VariantArrayInt8_t		, R_DLMS_CLASSES_DecodeInteger				)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayLong					, VariantArrayInt16_t		, R_DLMS_CLASSES_DecodeLong					)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayUnsigned				, VariantArrayUint8_t		, R_DLMS_CLASSES_DecodeUnsigned				)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayLongUnsigned			, VariantArrayUint16_t		, R_DLMS_CLASSES_DecodeLongUnsigned			)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayLong64					, VariantArrayInt64_t		, R_DLMS_CLASSES_DecodeLong64				)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayLong64Unsigned			, VariantArrayUint64_t		, R_DLMS_CLASSES_DecodeLong64Unsigned		)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayEnum					, VariantArrayUint8_t		, R_DLMS_CLASSES_DecodeEnum					)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayFloat32				, VariantArrayFloat32_t		, R_DLMS_CLASSES_DecodeFloat32				)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayFloat64				, VariantArrayDouble64_t	, R_DLMS_CLASSES_DecodeFloat64				)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayDateTime				, VariantArrayDateTime_t	, R_DLMS_CLASSES_DecodeDateTime				)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayDateTimeAsOctetString	, VariantArrayDateTime_t	, R_DLMS_CLASSES_DecodeDateTimeAsOctetString)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayDate					, VariantArrayDate_t		, R_DLMS_CLASSES_DecodeDate					)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayDateAsOctetString		, VariantArrayDate_t		, R_DLMS_CLASSES_DecodeDateAsOctetString	)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayTime					, VariantArrayTime_t		, R_DLMS_CLASSES_DecodeTime					)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayTimeAsOctetString		, VariantArrayTime_t		, R_DLMS_CLASSES_DecodeTimeAsOctetString	)
OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(R_DLMS_CLASSES_DecodeVariantArrayChoice					, VariantArrayChoice_t		, R_DLMS_CLASSES_DecodeChoice				)

/* ----------------------------------
 * Fixed array redirect functions
 * ----------------------------------*/
OBIS_DECLARE_FIXED_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectFixedArray1Byte				, FixedArrayUint8_t			, uint8_t		)
OBIS_DECLARE_FIXED_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectFixedArray2Byte				, FixedArrayUint16_t		, uint16_t		)
OBIS_DECLARE_FIXED_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectFixedArray4Byte				, FixedArrayUint32_t		, uint32_t		)
OBIS_DECLARE_FIXED_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectFixedArray8Byte				, FixedArrayUint64_t		, uint64_t		)
OBIS_DECLARE_FIXED_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectFixedArrayDateTime			, FixedArrayDateTime_t		, date_time_t	)
OBIS_DECLARE_FIXED_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectFixedArrayDate				, FixedArrayDate_t			, date_t		)
OBIS_DECLARE_FIXED_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectFixedArrayTime				, FixedArrayTime_t			, time_t		)
FixedArrayVariantString *R_DLMS_CLASSES_RedirectFixedArrayVariantStringWithBitStringIndicator(
	distributor_params_t *p_params,
	FixedArrayVariantString *p_object,
	uint8_t is_element_bitstring
)
{
	uint16_t				count, bytes_length;
	FixedArrayVariantString	*p_clone_obj;
	uint8_t					*p_alloc, *p_head;

	ASSERT_TRUE_RET_NULL(p_params == NULL || p_object == NULL || OBIS_MALLOC_IS_NULL(p_params));

	p_clone_obj = (FixedArrayVariantString *)R_DLMS_CLASSES_CreateFixedArray(
		p_params,
		(AbstractFixedArray *)p_object,
		sizeof(VariantString),
		OBIS_MALLOC_OPTION_CREATENEW |
		OBIS_MALLOC_OPTION_CLONE
	);
	ASSERT_TRUE_RET_NULL(p_clone_obj == NULL);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);	
	for (count = 0; count < p_object->length; count++)
	{
		bytes_length = p_object->p_content[count].alloc_size;
		if (is_element_bitstring == TRUE) {
			bytes_length += 7;
			bytes_length /= 8;
		}
		OBIS_MALLOC_ASSIGN_VARIANT_STRING(p_clone_obj->p_content + count, bytes_length, p_alloc);
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_MEMLINK_RET_NULL(
			p_params,
			(uint8_t *)&p_object->p_content[count].length,
			(uint8_t *)&p_clone_obj->p_content[count].length,
			sizeof(uint16_t)
		);
		p_clone_obj->p_content[count].length = p_object->p_content[count].length;
		OBIS_MALLOC_MEMLINK_RET_NULL(
			p_params,
			(uint8_t *)p_object->p_content[count].p_content,
			(uint8_t *)p_clone_obj->p_content[count].p_content,
			bytes_length
		);
		memcpy(p_clone_obj->p_content[count].p_content, p_object->p_content[count].p_content, bytes_length);
	}
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectFixedArrayVariantString, FixedArrayVariantString)
{
	return R_DLMS_CLASSES_RedirectFixedArrayVariantStringWithBitStringIndicator(
		p_params, p_object, FALSE
	);
}
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectFixedArrayBitString, FixedArrayVariantString)
{
	return R_DLMS_CLASSES_RedirectFixedArrayVariantStringWithBitStringIndicator(
		p_params, p_object, TRUE
	);
}
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectFixedArrayChoice, FixedArrayChoice_t)
{
	uint16_t			count, bytes_length;
	FixedArrayChoice_t	*p_clone_obj;
	uint8_t				*p_alloc, *p_head;

	ASSERT_TRUE_RET_NULL(p_params == NULL || p_object == NULL || OBIS_MALLOC_IS_NULL(p_params));

	p_clone_obj = (FixedArrayChoice_t	*)R_DLMS_CLASSES_CreateFixedArray(
		p_params,
		(AbstractFixedArray *)p_object,
		sizeof(choice_t),
		OBIS_MALLOC_OPTION_CREATENEW |
		OBIS_MALLOC_OPTION_CLONE
	);
	ASSERT_TRUE_RET_NULL(p_clone_obj == NULL);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	for (count = 0; count < p_object->length; count++) {
		bytes_length = p_object->p_content[count].choice.size;
		if (p_object->p_content[count].choice.type == TAG_DATA_BIT_STRING) {
			bytes_length += 7;
			bytes_length /= 8;
		}
		p_clone_obj->p_content[count].buffer = p_alloc;
		p_alloc += bytes_length;
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_MEMLINK_RET_NULL(
			p_params,
			(uint8_t *)p_object->p_content[count].buffer,
			(uint8_t *)p_clone_obj->p_content[count].buffer,
			bytes_length
		);
		memcpy(p_clone_obj->p_content[count].buffer, p_object->p_content[count].buffer, bytes_length);
	}
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}

OBIS_DECLARE_VARIANT_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectVariantArray1Byte			, VariantArrayUint8_t		, uint8_t		)
OBIS_DECLARE_VARIANT_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectVariantArray2Byte			, VariantArrayUint16_t		, uint16_t		)
OBIS_DECLARE_VARIANT_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectVariantArray4Byte			, VariantArrayUint32_t		, uint32_t		)
OBIS_DECLARE_VARIANT_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectVariantArray8Byte			, VariantArrayUint64_t		, uint64_t		)
OBIS_DECLARE_VARIANT_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectVariantArrayDateTime		, VariantArrayDateTime_t	, date_time_t	)
OBIS_DECLARE_VARIANT_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectVariantArrayDate			, VariantArrayDate_t		, date_t		)
OBIS_DECLARE_VARIANT_ARRAY_REDIRECT_FUNC(R_DLMS_CLASSES_RedirectVariantArrayTime			, VariantArrayTime_t		, time_t		)
VariantArrayVariantString *R_DLMS_CLASSES_RedirectVariantArrayVariantStringWithBitStringIndicator(
	distributor_params_t *p_params,
	VariantArrayVariantString *p_object,
	uint8_t is_element_bitstring
)
{
	uint16_t					count, bytes_length;
	VariantArrayVariantString	*p_clone_obj;
	uint8_t						*p_alloc, *p_head;

	ASSERT_TRUE_RET_NULL(p_params == NULL || p_object == NULL || OBIS_MALLOC_IS_NULL(p_params));
	
	p_clone_obj = (VariantArrayVariantString *)R_DLMS_CLASSES_CreateVariantArray(
		p_params,
		(AbstractVariantArray *)p_object,
		sizeof(VariantString),
		OBIS_MALLOC_OPTION_CREATENEW |
		OBIS_MALLOC_OPTION_CLONE
	);
	ASSERT_TRUE_RET_NULL(p_clone_obj == NULL);
	OBIS_MALLOC_MEMLINK_RET_NULL(
		p_params,
		(uint8_t *)&p_object->length,
		(uint8_t *)&p_clone_obj->length,
		sizeof(uint16_t)
	);
	if (p_object->p_active != NULL) {
		OBIS_MALLOC_MEMLINK_RET_NULL(
			p_params,
			p_object->p_active,
			p_clone_obj->p_active,
			p_object->alloc_size
		);
	}

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	for (count = 0; count < p_object->alloc_size; count++)
	{
		bytes_length = p_object->p_content[count].alloc_size;
		if (is_element_bitstring == TRUE) {
			bytes_length += 7;
			bytes_length /= 8;
		}
		OBIS_MALLOC_ASSIGN_VARIANT_STRING(p_clone_obj->p_content + count, bytes_length, p_alloc);
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_MEMLINK_RET_NULL(
			p_params,
			(uint8_t *)&p_object->p_content[count].length,
			(uint8_t *)&p_clone_obj->p_content[count].length,
			sizeof(uint16_t)
		);
		p_clone_obj->p_content[count].length = p_object->p_content[count].length;
		OBIS_MALLOC_MEMLINK_RET_NULL(
			p_params,
			(uint8_t *)p_object->p_content[count].p_content,
			(uint8_t *)p_clone_obj->p_content[count].p_content,
			bytes_length
		);
		memcpy(p_clone_obj->p_content[count].p_content, p_object->p_content[count].p_content, bytes_length);
	}
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectVariantArrayBitString, VariantArrayVariantString)
{
	return R_DLMS_CLASSES_RedirectVariantArrayVariantStringWithBitStringIndicator(
		p_params, p_object, TRUE
	);
}
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectVariantArrayVariantString, VariantArrayVariantString)
{
	return R_DLMS_CLASSES_RedirectVariantArrayVariantStringWithBitStringIndicator(
		p_params, p_object, FALSE
	);
}
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectVariantArrayChoice, VariantArrayChoice_t)
{
	uint16_t				count, bytes_length;
	VariantArrayChoice_t	*p_clone_obj;
	uint8_t					*p_alloc, *p_head;

	ASSERT_TRUE_RET_NULL(p_params == NULL || p_object == NULL || OBIS_MALLOC_IS_NULL(p_params));
	p_clone_obj = (VariantArrayChoice_t *)R_DLMS_CLASSES_CreateVariantArray(
		p_params,
		(AbstractVariantArray *)p_object,
		sizeof(choice_t),
		OBIS_MALLOC_OPTION_CREATENEW |
		OBIS_MALLOC_OPTION_CLONE
	);
	ASSERT_TRUE_RET_NULL(p_clone_obj == NULL);
	OBIS_MALLOC_MEMLINK_RET_NULL(p_params, (uint8_t *)&p_object->length, (uint8_t *)&p_clone_obj->length, sizeof(uint16_t));
	if (p_object->p_active != NULL) {
		OBIS_MALLOC_MEMLINK_RET_NULL(p_params, p_object->p_active, p_clone_obj->p_active, p_object->alloc_size);
	}

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	for (count = 0; count < p_object->alloc_size; count++) {
		bytes_length = p_object->p_content[count].choice.size;
		if (p_object->p_content[count].choice.type == TAG_DATA_BIT_STRING) {
			bytes_length += 7;
			bytes_length /= 8;
		}
		p_clone_obj->p_content[count].buffer = p_alloc;
		p_alloc += bytes_length;
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_MEMLINK_RET_NULL(
			p_params,
			(uint8_t *)p_object->p_content[count].buffer,
			(uint8_t *)p_clone_obj->p_content[count].buffer,
			bytes_length
		);
		memcpy(p_clone_obj->p_content[count].buffer, p_object->p_content[count].buffer, bytes_length);
	}
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}

OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_Redirect_ChoiceAttribute, choice_t)
{
	choice_t *p_choice = R_DLMS_CLASSES_RedirectChoice(
		p_params,
		(choice_t *)p_object,
		(p_object->choice.type == TAG_DATA_BIT_STRING ? OBIS_MALLOC_OPTION_BITSTRING : OBIS_MALLOC_OPTION_NONE)
	);

	if (R_DLMS_CLASSES_IsBufferWritable((uint8_t *)p_object))
	{
		p_object->buffer = p_choice->buffer;
		p_object->choice.size = p_choice->choice.size;
		p_object->choice.type = p_choice->choice.type;
	}
	return p_choice;
}
/* ----------------------------------
 * Create new object for fixed aray
 * ----------------------------------*/
FixedArrayUint16_t * R_DLMS_CLASSES_CreatNew_FixedArray_LongUnsigned(distributor_params_t *p_params, uint16_t array_size)
{
	FixedArrayUint16_t *p_clone;
	uint8_t * p_alloc, * p_head;

	/* Create allocate */
	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone, FixedArrayUint16_t, p_alloc);
	OBIS_MALLOC_ASSIGN_FIXED_ARRAY(p_clone, array_size, uint16_t, p_alloc);

	/* Check allocate */
	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone;
}
FixedString * R_DLMS_CLASSES_CreatNew_Fixedstring(distributor_params_t *p_params, uint16_t string_size)
{
	FixedString *p_clone;
	uint8_t * p_alloc, * p_head;

	/* Create allocate */
	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone, FixedString, p_alloc);
	OBIS_MALLOC_ASSIGN_FIXED_STRING(p_clone, string_size, p_alloc);

	/* Check allocate */
	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone;
}
/* ----------------------------------
 * Create new object for variant aray
 * ----------------------------------*/
BitString * R_DLMS_CLASSES_CreatNew_Bitstring(distributor_params_t *p_params, uint16_t string_size)//string_size: number bits
{
	BitString *p_clone;
	uint8_t * p_alloc, * p_head;
	uint16_t length_byte;

	/* Create allocate */
	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone, BitString, p_alloc);

	if(string_size % 8 == 0)
	{
		length_byte = string_size / 8;
	}
	else
	{
		length_byte = (string_size / 8) + 1;
	}
	OBIS_MALLOC_ASSIGN_VARIANT_STRING(p_clone, length_byte, p_alloc);
	p_clone->alloc_size = string_size;//bit number size

	/* Check allocate */
	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone;
}
OctetString * R_DLMS_CLASSES_CreatNew_Octetstring(distributor_params_t *p_params, uint16_t string_size)
{
	OctetString *p_clone;
	uint8_t * p_alloc, * p_head;

	/* Create allocate */
	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone, OctetString, p_alloc);
	OBIS_MALLOC_ASSIGN_VARIANT_STRING(p_clone, string_size, p_alloc);

	/* Check allocate */
	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone;
}
VariantArrayUint32_t * R_DLMS_CLASSES_CreatNew_VariantArray_DoubleLongUnsigned(distributor_params_t *p_params, uint16_t array_size)
{
	VariantArrayUint32_t *p_clone;
	uint8_t * p_alloc, * p_head;

	/* Create allocate */
	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone, VariantArrayUint32_t, p_alloc);
	OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone, array_size, uint32_t, p_alloc);
	p_clone->p_active = NULL;
	/* Check allocate */
	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone;
}

/* Create object array OctetString */
VariantArrayOctetString *R_DLMS_CLASSES_CreatNew_VariantArrayOctetString(distributor_params_t *p_params, VariantArrayOctetString *p_object, uint16_t array_size, uint16_t string_element_length)
{
	VariantArrayOctetString *p_clone;
	uint8_t *p_alloc, *p_head;
	uint16_t count;

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
	OBIS_MALLOC_ASSIGN_OBJECT(p_clone, VariantArrayOctetString, p_alloc);
	OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone, array_size, OctetString, p_alloc);
	for (count = 0; count < array_size; count++)
	{
		/* Each element is logical name octet string (length = 6) */
		OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone->p_content[count], string_element_length, p_alloc);
		p_clone->p_content[count].length = string_element_length;
	}
	p_clone->p_active = NULL;
	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone;
}
/* ----------------------------------
 * Distributor of basic types
 * ----------------------------------*/
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeBoolean				, TAG_DATA_BOOLEAN				, uint8_t		, sizeof(uint8_t	) )			/* Distributor function for type boolean */
OBIS_DECLARE_VARIANT_STRING_DISTRIBUTOR_FUNC( R_DLMS_CLASSES_DistributeBitString			, TAG_DATA_BIT_STRING												  )			/* Distributor function for type bit-string */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeDoubleLong			, TAG_DATA_DOUBLE_LONG			, int32_t		, sizeof(int32_t	) )			/* Distributor function for type double-long */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeDoubleLongUnsigned	, TAG_DATA_DOUBLE_LONG_UNSIGNED	, uint32_t		, sizeof(uint32_t	) )			/* Distributor function for type double-long-unsigned */
OBIS_DECLARE_VARIANT_STRING_DISTRIBUTOR_FUNC( R_DLMS_CLASSES_DistributeOctetString			, TAG_DATA_OCTET_STRING												  )			/* Distributor function for type octet-string */
OBIS_DECLARE_VARIANT_STRING_DISTRIBUTOR_FUNC( R_DLMS_CLASSES_DistributeVisibleString		, TAG_DATA_VISIBLE_STRING											  )			/* Distributor function for type visible-string */
OBIS_DECLARE_VARIANT_STRING_DISTRIBUTOR_FUNC( R_DLMS_CLASSES_DistributeUtf8String			, TAG_DATA_UTF8_STRING												  )			/* Distributor function for type utf8-string */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeBcd					, TAG_DATA_BCD					, int8_t		, sizeof(int8_t		) )			/* Distributor function for type bcd */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeInteger				, TAG_DATA_INTEGER				, int8_t		, sizeof(int8_t		) )			/* Distributor function for type integer */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeLong					, TAG_DATA_LONG					, int16_t		, sizeof(int16_t	) )			/* Distributor function for type long */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeUnsigned				, TAG_DATA_UNSIGNED				, uint8_t		, sizeof(uint8_t	) )			/* Distributor function for type unsigned */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeLongUnsigned			, TAG_DATA_LONG_UNSIGNED		, uint16_t		, sizeof(uint16_t	) )			/* Distributor function for type long-unsigned */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeLong64				, TAG_DATA_LONG64				, int64_t		, sizeof(int64_t	) )			/* Distributor function for type long64 */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeLong64Unsigned		, TAG_DATA_LONG64_UNSIGNED		, uint64_t		, sizeof(uint64_t	) )			/* Distributor function for type long64-unsigned */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeEnum					, TAG_DATA_ENUM					, uint8_t		, sizeof(uint8_t	) )			/* Distributor function for type enum */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeFloat32				, TAG_DATA_FLOAT32				, float32_t		, sizeof(float32_t	) )			/* Distributor function for type float32 */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeFloat64				, TAG_DATA_FLOAT64				, double64_t	, sizeof(double64_t	) )			/* Distributor function for type float64 */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeDateTime				, TAG_DATA_DATE_TIME			, date_time_t	, sizeof(date_time_t) )			/* Distributor function for type date-time */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeDateTimeAsOctetString, TAG_DATA_OCTET_STRING			, date_time_t	, sizeof(date_time_t) )			/* Distributor function for type date-time as OctetString */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeDate					, TAG_DATA_DATE					, date_t		, sizeof(date_t		) )			/* Distributor function for type date */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeDateAsOctetString	, TAG_DATA_OCTET_STRING			, date_t		, sizeof(date_t		) )			/* Distributor function for type date as OctetString */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeTime					, TAG_DATA_TIME					, time_t		, sizeof(time_t		) )			/* Distributor function for type time */
OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC	( R_DLMS_CLASSES_DistributeTimeAsOctetString	, TAG_DATA_OCTET_STRING			, time_t		, sizeof(time_t		) )			/* Distributor function for type time as OctetString */

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeChoice
* Interface     : distributor_params_t R_DLMS_CLASSES_DistributeChoice(
*               :     distributor_params_t * p_params,
*               :     choice_t * p_object           ,
*               : );
* Description   : Distribution of choice_t type
* Arguments     : distributor_params_t * p_params : Distribution params
*               : choice_t * p_object             : Choice data type
* Return Value  : distributor_params_t
******************************************************************************/
void R_DLMS_CLASSES_DistributeChoice(
	distributor_params_t *p_params,
	choice_t *p_object
)
{
	void		*p_origin_object = p_object;
	uint16_t	decoded_length;

	if (p_params != NULL)
	{
		if (p_params->req_type == REQ_TYPE_GET) {

			ASSERT_TRUE_RET(p_object == NULL);
			*p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
				p_params->out_data.p_content,
				p_params->out_data.length,
				p_object->choice.type,
				(uint8_t *)p_object->buffer,
				p_object->choice.size
			);
			if (*p_params->p_out_encoded_len > 0) {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
				OBIS_DISTRIBUTION_SUCCESS(p_params->result);
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
		else if (p_params->req_type == REQ_TYPE_SET) {

			/*
			 * clone object buffer to malloc buffer of distributor service
			 * and register a memcpy call at the end of class distribution
			 */
			if(p_object->choice.type == TAG_DATA_STRUCTURE || p_object->choice.type == TAG_DATA_ARRAY)
			{
				p_params->service_params.decode_success = TRUE;
				return;
			}
			p_object = R_DLMS_CLASSES_RedirectChoice(
				p_params,
				p_object,
				(p_object->choice.type == TAG_DATA_BIT_STRING ? OBIS_MALLOC_OPTION_BITSTRING : OBIS_MALLOC_OPTION_NONE)
			);
			ASSERT_TRUE_RET(p_object == NULL);
			if (p_origin_object != p_object) {
				p_params->service_params.created = TRUE;
			}
			if(p_object->choice.type == TAG_DATA_BIT_STRING ||
			   p_object->choice.type == TAG_DATA_OCTET_STRING ||
			   p_object->choice.type == TAG_DATA_VISIBLE_STRING ||
			   p_object->choice.type == TAG_DATA_UTF8_STRING)
			{				   
				R_BER_LengthDecode(p_params->in_data.p_content + 1, (uint16_t *)&p_object->choice.size);
			}
			else
			{
				
			}
			decoded_length = R_DLMS_CLASSES_DecodeCommonType(
				p_object->buffer,
				p_object->choice.size,
				p_object->choice.type,
				p_params->in_data.p_content,
				p_params->in_data.length
			);
			if (decoded_length > 0) {
				if (p_params->service_params.created == TRUE) {
					p_params->service_params.decode_success = TRUE;
				}
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
				OBIS_DISTRIBUTION_SUCCESS(p_params->result);
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
			}
		}
	}
}

/* ----------------------------------
 * Distributor of Fixed array types
 * ----------------------------------*/
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayBoolean				, FixedArrayUint8_t			, R_DLMS_CLASSES_EncodeFixedArrayBoolean				, R_DLMS_CLASSES_DecodeFixedArrayBoolean				, R_DLMS_CLASSES_RedirectFixedArray1Byte			)		/* Distribute for FixedArray of boolean */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayBitString			, FixedArrayBitString		, R_DLMS_CLASSES_EncodeFixedArrayBitString				, R_DLMS_CLASSES_DecodeFixedArrayBitString				, R_DLMS_CLASSES_RedirectFixedArrayBitString		)		/* Distribute for FixedArray of bit-string */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayDoubleLong			, FixedArrayInt32_t			, R_DLMS_CLASSES_EncodeFixedArrayDoubleLong				, R_DLMS_CLASSES_DecodeFixedArrayDoubleLong				, R_DLMS_CLASSES_RedirectFixedArray4Byte			)		/* Distribute for FixedArray of double-long */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayDoubleLongUnsigned	, FixedArrayUint32_t		, R_DLMS_CLASSES_EncodeFixedArrayDoubleLongUnsigned		, R_DLMS_CLASSES_DecodeFixedArrayDoubleLongUnsigned		, R_DLMS_CLASSES_RedirectFixedArray4Byte			)		/* Distribute for FixedArray of double-long-unsigned */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayOctetString			, FixedArrayOctetString		, R_DLMS_CLASSES_EncodeFixedArrayOctetString			, R_DLMS_CLASSES_DecodeFixedArrayOctetString			, R_DLMS_CLASSES_RedirectFixedArrayVariantString	)		/* Distribute for FixedArray of octet-string */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayVisibleString		, FixedArrayVisibleString	, R_DLMS_CLASSES_EncodeFixedArrayVisibleString			, R_DLMS_CLASSES_DecodeFixedArrayVisibleString			, R_DLMS_CLASSES_RedirectFixedArrayVariantString	)		/* Distribute for FixedArray of visible-string */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayUtf8String			, FixedArrayUtf8String		, R_DLMS_CLASSES_EncodeFixedArrayUtf8String				, R_DLMS_CLASSES_DecodeFixedArrayUtf8String				, R_DLMS_CLASSES_RedirectFixedArrayVariantString	)		/* Distribute for FixedArray of utf8-string */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayBcd					, FixedArrayInt8_t			, R_DLMS_CLASSES_EncodeFixedArrayBcd					, R_DLMS_CLASSES_DecodeFixedArrayBcd					, R_DLMS_CLASSES_RedirectFixedArray1Byte			)		/* Distribute for FixedArray of bcd */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayInteger				, FixedArrayInt8_t			, R_DLMS_CLASSES_EncodeFixedArrayInteger				, R_DLMS_CLASSES_DecodeFixedArrayInteger				, R_DLMS_CLASSES_RedirectFixedArray1Byte			)		/* Distribute for FixedArray of integer */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayLong					, FixedArrayInt16_t			, R_DLMS_CLASSES_EncodeFixedArrayLong					, R_DLMS_CLASSES_DecodeFixedArrayLong					, R_DLMS_CLASSES_RedirectFixedArray2Byte			)		/* Distribute for FixedArray of long */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayUnsigned				, FixedArrayUint8_t			, R_DLMS_CLASSES_EncodeFixedArrayUnsigned				, R_DLMS_CLASSES_DecodeFixedArrayUnsigned				, R_DLMS_CLASSES_RedirectFixedArray1Byte			)		/* Distribute for FixedArray of unsigned */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayLongUnsigned			, FixedArrayUint16_t		, R_DLMS_CLASSES_EncodeFixedArrayLongUnsigned			, R_DLMS_CLASSES_DecodeFixedArrayLongUnsigned			, R_DLMS_CLASSES_RedirectFixedArray2Byte			)		/* Distribute for FixedArray of long-unsigned */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayLong64				, FixedArrayInt64_t			, R_DLMS_CLASSES_EncodeFixedArrayLong64					, R_DLMS_CLASSES_DecodeFixedArrayLong64					, R_DLMS_CLASSES_RedirectFixedArray8Byte			)		/* Distribute for FixedArray of long64 */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayLong64Unsigned		, FixedArrayUint64_t		, R_DLMS_CLASSES_EncodeFixedArrayLong64Unsigned			, R_DLMS_CLASSES_DecodeFixedArrayLong64Unsigned			, R_DLMS_CLASSES_RedirectFixedArray8Byte			)		/* Distribute for FixedArray of long64-unsigned */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayEnum					, FixedArrayUint8_t			, R_DLMS_CLASSES_EncodeFixedArrayEnum					, R_DLMS_CLASSES_DecodeFixedArrayEnum					, R_DLMS_CLASSES_RedirectFixedArray1Byte			)		/* Distribute for FixedArray of enum */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayFloat32				, FixedArrayFloat32_t		, R_DLMS_CLASSES_EncodeFixedArrayFloat32				, R_DLMS_CLASSES_DecodeFixedArrayFloat32				, R_DLMS_CLASSES_RedirectFixedArray4Byte			)		/* Distribute for FixedArray of float32 */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayFloat64				, FixedArrayDouble64_t		, R_DLMS_CLASSES_EncodeFixedArrayFloat64				, R_DLMS_CLASSES_DecodeFixedArrayFloat64				, R_DLMS_CLASSES_RedirectFixedArray8Byte			)		/* Distribute for FixedArray of float64 */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayDateTime				, FixedArrayDateTime_t		, R_DLMS_CLASSES_EncodeFixedArrayDateTime				, R_DLMS_CLASSES_DecodeFixedArrayDateTime				, R_DLMS_CLASSES_RedirectFixedArrayDateTime			)		/* Distribute for FixedArray of date-time */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayDateTimeAsOctetString, FixedArrayDateTime_t		, R_DLMS_CLASSES_EncodeFixedArrayDateTimeAsOctetString	, R_DLMS_CLASSES_DecodeFixedArrayDateTimeAsOctetString	, R_DLMS_CLASSES_RedirectFixedArrayDateTime			)		/* Distribute for FixedArray of date-time as OctetString */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayDate					, FixedArrayDate_t			, R_DLMS_CLASSES_EncodeFixedArrayDate					, R_DLMS_CLASSES_DecodeFixedArrayDate					, R_DLMS_CLASSES_RedirectFixedArrayDate				)		/* Distribute for FixedArray of date */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayDateAsOctetString	, FixedArrayDate_t			, R_DLMS_CLASSES_EncodeFixedArrayDateAsOctetString		, R_DLMS_CLASSES_DecodeFixedArrayDateAsOctetString		, R_DLMS_CLASSES_RedirectFixedArrayDate				)		/* Distribute for FixedArray of date as OctetString */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayTime					, FixedArrayTime_t			, R_DLMS_CLASSES_EncodeFixedArrayTime					, R_DLMS_CLASSES_DecodeFixedArrayTime					, R_DLMS_CLASSES_RedirectFixedArrayTime				)		/* Distribute for FixedArray of time */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayTimeAsOctetString	, FixedArrayTime_t			, R_DLMS_CLASSES_EncodeFixedArrayTimeAsOctetString		, R_DLMS_CLASSES_DecodeFixedArrayTimeAsOctetString		, R_DLMS_CLASSES_RedirectFixedArrayTime				)		/* Distribute for FixedArray of time as OctetString */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeFixedArrayChoice				, FixedArrayChoice_t		, R_DLMS_CLASSES_EncodeFixedArrayChoice					, R_DLMS_CLASSES_DecodeFixedArrayChoice					, R_DLMS_CLASSES_RedirectFixedArrayChoice			)		/* Distribute for FixedArray of choice_t */

 /* ----------------------------------
  * Distributor of Variant array types
  * ----------------------------------*/
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayBoolean				, VariantArrayUint8_t		, R_DLMS_CLASSES_EncodeVariantArrayBoolean					, R_DLMS_CLASSES_DecodeVariantArrayBoolean					, R_DLMS_CLASSES_RedirectVariantArray1Byte			)		/* Distribute for VariantArray of boolean */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayBitString				, VariantArrayBitString		, R_DLMS_CLASSES_EncodeVariantArrayBitString				, R_DLMS_CLASSES_DecodeVariantArrayBitString				, R_DLMS_CLASSES_RedirectVariantArrayBitString		)		/* Distribute for VariantArray of bit-string */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayDoubleLong				, VariantArrayInt32_t		, R_DLMS_CLASSES_EncodeVariantArrayDoubleLong				, R_DLMS_CLASSES_DecodeVariantArrayDoubleLong				, R_DLMS_CLASSES_RedirectVariantArray4Byte			)		/* Distribute for VariantArray of double-long */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayDoubleLongUnsigned		, VariantArrayUint32_t		, R_DLMS_CLASSES_EncodeVariantArrayDoubleLongUnsigned		, R_DLMS_CLASSES_DecodeVariantArrayDoubleLongUnsigned		, R_DLMS_CLASSES_RedirectVariantArray4Byte			)		/* Distribute for VariantArray of double-long-unsigned */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayOctetString			, VariantArrayOctetString	, R_DLMS_CLASSES_EncodeVariantArrayOctetString				, R_DLMS_CLASSES_DecodeVariantArrayOctetString				, R_DLMS_CLASSES_RedirectVariantArrayVariantString	)		/* Distribute for VariantArray of octet-string */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayVisibleString			, VariantArrayVisibleString	, R_DLMS_CLASSES_EncodeVariantArrayVisibleString			, R_DLMS_CLASSES_DecodeVariantArrayVisibleString			, R_DLMS_CLASSES_RedirectVariantArrayVariantString	)		/* Distribute for VariantArray of visible-string */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayUtf8String				, VariantArrayUtf8String	, R_DLMS_CLASSES_EncodeVariantArrayUtf8String				, R_DLMS_CLASSES_DecodeVariantArrayUtf8String				, R_DLMS_CLASSES_RedirectVariantArrayVariantString	)		/* Distribute for VariantArray of utf8-string */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayBcd					, VariantArrayInt8_t		, R_DLMS_CLASSES_EncodeVariantArrayBcd						, R_DLMS_CLASSES_DecodeVariantArrayBcd						, R_DLMS_CLASSES_RedirectVariantArray1Byte			)		/* Distribute for VariantArray of bcd */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayInteger				, VariantArrayInt8_t		, R_DLMS_CLASSES_EncodeVariantArrayInteger					, R_DLMS_CLASSES_DecodeVariantArrayInteger					, R_DLMS_CLASSES_RedirectVariantArray1Byte			)		/* Distribute for VariantArray of integer */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayLong					, VariantArrayInt16_t		, R_DLMS_CLASSES_EncodeVariantArrayLong						, R_DLMS_CLASSES_DecodeVariantArrayLong						, R_DLMS_CLASSES_RedirectVariantArray2Byte			)		/* Distribute for VariantArray of long */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayUnsigned				, VariantArrayUint8_t		, R_DLMS_CLASSES_EncodeVariantArrayUnsigned					, R_DLMS_CLASSES_DecodeVariantArrayUnsigned					, R_DLMS_CLASSES_RedirectVariantArray1Byte			)		/* Distribute for VariantArray of unsigned */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayLongUnsigned			, VariantArrayUint16_t		, R_DLMS_CLASSES_EncodeVariantArrayLongUnsigned				, R_DLMS_CLASSES_DecodeVariantArrayLongUnsigned				, R_DLMS_CLASSES_RedirectVariantArray2Byte			)		/* Distribute for VariantArray of long-unsigned */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayLong64					, VariantArrayInt64_t		, R_DLMS_CLASSES_EncodeVariantArrayLong64					, R_DLMS_CLASSES_DecodeVariantArrayLong64					, R_DLMS_CLASSES_RedirectVariantArray8Byte			)		/* Distribute for VariantArray of long64 */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayLong64Unsigned			, VariantArrayUint64_t		, R_DLMS_CLASSES_EncodeVariantArrayLong64Unsigned			, R_DLMS_CLASSES_DecodeVariantArrayLong64Unsigned			, R_DLMS_CLASSES_RedirectVariantArray8Byte			)		/* Distribute for VariantArray of long64-unsigned */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayEnum					, VariantArrayUint8_t		, R_DLMS_CLASSES_EncodeVariantArrayEnum						, R_DLMS_CLASSES_DecodeVariantArrayEnum						, R_DLMS_CLASSES_RedirectVariantArray1Byte			)		/* Distribute for VariantArray of enum */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayFloat32				, VariantArrayFloat32_t		, R_DLMS_CLASSES_EncodeVariantArrayFloat32					, R_DLMS_CLASSES_DecodeVariantArrayFloat32					, R_DLMS_CLASSES_RedirectVariantArray4Byte			)		/* Distribute for VariantArray of float32 */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayFloat64				, VariantArrayDouble64_t	, R_DLMS_CLASSES_EncodeVariantArrayFloat64					, R_DLMS_CLASSES_DecodeVariantArrayFloat64					, R_DLMS_CLASSES_RedirectVariantArray8Byte			)		/* Distribute for VariantArray of float64 */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayDateTime				, VariantArrayDateTime_t	, R_DLMS_CLASSES_EncodeVariantArrayDateTime					, R_DLMS_CLASSES_DecodeVariantArrayDateTime					, R_DLMS_CLASSES_RedirectVariantArrayDateTime		)		/* Distribute for VariantArray of date-time */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayDateTimeAsOctetString	, VariantArrayDateTime_t	, R_DLMS_CLASSES_EncodeVariantArrayDateTimeAsOctetString	, R_DLMS_CLASSES_DecodeVariantArrayDateTimeAsOctetString	, R_DLMS_CLASSES_RedirectVariantArrayDateTime		)		/* Distribute for VariantArray of date-time as OctetString */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayDate					, VariantArrayDate_t		, R_DLMS_CLASSES_EncodeVariantArrayDate						, R_DLMS_CLASSES_DecodeVariantArrayDate						, R_DLMS_CLASSES_RedirectVariantArrayDate			)		/* Distribute for VariantArray of date */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayDateAsOctetString		, VariantArrayDate_t		, R_DLMS_CLASSES_EncodeVariantArrayDateAsOctetString		, R_DLMS_CLASSES_DecodeVariantArrayDateAsOctetString		, R_DLMS_CLASSES_RedirectVariantArrayDate			)		/* Distribute for VariantArray of date as OctetString */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayTime					, VariantArrayTime_t		, R_DLMS_CLASSES_EncodeVariantArrayTime						, R_DLMS_CLASSES_DecodeVariantArrayTime						, R_DLMS_CLASSES_RedirectVariantArrayTime			)		/* Distribute for VariantArray of time */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayTimeAsOctetString		, VariantArrayTime_t		, R_DLMS_CLASSES_EncodeVariantArrayTimeAsOctetString		, R_DLMS_CLASSES_DecodeVariantArrayTimeAsOctetString		, R_DLMS_CLASSES_RedirectVariantArrayTime			)		/* Distribute for VariantArray of time as OctetString */
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC (R_DLMS_CLASSES_DistributeVariantArrayChoice					, VariantArrayChoice_t		, R_DLMS_CLASSES_EncodeVariantArrayChoice					, R_DLMS_CLASSES_DecodeVariantArrayChoice					, R_DLMS_CLASSES_RedirectVariantArrayChoice			)		/* Distribute for VariantArray of choice_t */

 /* ----------------------------------
  * Support function
  * ----------------------------------*/
 /******************************************************************************
* Function Name : R_DLMS_convert_ipv6_bytes_to_string
* Interface     : uint8_t R_DLMS_convert_ipv6_bytes_to_string(
*               :     FixedString * p_ip_address_in_out,
*               : );
* Description   : convert Ipv6 form byte array to acci string Ip format
* Arguments     : distributor_params_t *p_params: contents paras of service turn
*               : FixedString * p_ip_address_in_out: content input value of 16 bytes of IP as octet string
* Function Calls: 
* Return Value  : static void
******************************************************************************/
uint8_t R_DLMS_convert_ipv6_bytes_to_string(FixedString * p_ip_address_in_out)
{
	IpAddress				ip_address_base;
	FixedString 			IPv6_String;
	IpAddressPtr  			p_ip_address = &ip_address_base;
    uint8_t                 result = FALSE;
    uint8_t                 *p_alloc, *p_head;
	uint8_t					ip_string[48];

    /* Check input IP address, not checking p_params pointer */
	if (p_ip_address_in_out->p_content == NULL || p_ip_address_in_out->length != 16)
	{
		return FALSE;
	}
	else
	{

	}
	p_ip_address->p_addr = p_ip_address_in_out->p_content;
	p_ip_address->size = 16;
    /* Capture current malloc head */

	IPv6_String.length = 48;
	IPv6_String.p_content = &ip_string[0];
    /* Start conversion (actual length will be override */
    result = R_DLMS_ConvertIpAddressToString(
		IPv6_String.p_content,
        &IPv6_String.length,
        p_ip_address
    );

    /* Return the allocated and convert buffer */
    if (result == TRUE) 
	{
		p_ip_address_in_out->length = IPv6_String.length;
		memcpy(p_ip_address_in_out->p_content, IPv6_String.p_content, IPv6_String.length);
    }
    else 
	{

    }
	return result;
}
 /******************************************************************************
* Function Name : R_DLMS_convert_ipv6_array_bytes_to_string
* Interface     : uint8_t R_DLMS_convert_ipv6_array_bytes_to_string(
*               :     VariantArrayOctetString * p_ip_address_array_in_out,
*               : );
* Description   : convert Ipv6 form byte array to acci string Ip format
* Arguments     : distributor_params_t *p_params: contents paras of service turn
*               : VariantArrayOctetString * p_ip_address_array_in_out: content input array of value of 16 bytes of IP as octet string
* Function Calls: 
* Return Value  : static void
******************************************************************************/
uint8_t R_DLMS_convert_ipv6_array_bytes_to_string(VariantArrayOctetString * p_ip_address_array_in_out)
{
	IpAddress				ip_address_base;
	OctetString 			IPv6_String;
	IpAddressPtr  			p_ip_address = &ip_address_base;
	uint8_t                 result = FALSE;
	uint8_t                 *p_alloc, *p_head;
	uint16_t                i;
	uint8_t					ip_string[48];

	if (p_ip_address_array_in_out->length == 0)
	{
		/* Always true if array has no ip, reply array with 0 element */
		return TRUE;
	}
	else
	{

	}
	for (i = 0; i < p_ip_address_array_in_out->length; i++)
	{
		if (p_ip_address_array_in_out->p_content[i].p_content == NULL || p_ip_address_array_in_out->p_content[i].length != 16)
		{
			return FALSE;
		}
		p_ip_address->p_addr = p_ip_address_array_in_out->p_content[i].p_content;
		p_ip_address->size = 16;
		/* Capture current malloc head */

		IPv6_String.length = 48;
		IPv6_String.alloc_size = 48;
		IPv6_String.p_content = &ip_string[0];
		/* Start conversion (actual length will be override */
		result = R_DLMS_ConvertIpAddressToString(
			IPv6_String.p_content,
			&IPv6_String.length,
			p_ip_address
		);

		/* Return the allocated and convert buffer */
		if (result == TRUE)
		{
			p_ip_address_array_in_out->p_content[i].length = IPv6_String.length;
			memcpy(p_ip_address_array_in_out->p_content[i].p_content, IPv6_String.p_content, IPv6_String.length);
		}
		else
		{
			return FALSE;
		}
	}
	result = TRUE;
	/* Check input IP address, not checking p_params pointer */
	return result;
}
/******************************************************************************
* Function Name : R_DLMS_CLASSES_AbstractDistributor
* Interface     : static void R_DLMS_CLASSES_AbstractDistributor(
*               :     fp_distributor_t derived_func  ,
*               :     distributor_params_t * p_params,
*               : );
* Description   : 
* Arguments     : fp_distributor_t derived_func  :
*               : distributor_params_t * p_params:
* Function Calls: 
* Return Value  : static void
******************************************************************************/
static void R_DLMS_CLASSES_AbstractDistributor(fp_distributor_t derived_func, distributor_params_t *p_params)
{
	/* In default, the distribution is handled at here */
	p_params->handled = TRUE;

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		/* Default return code is error */
		OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED, FALSE);
		OBIS_DISTRIBUTION_FAILED(p_params->result);

		switch (p_params->descriptor.attr.attribute_id)
		{
			case 0:	/* Attr0 */
				/* No support, error return */
				break;

			case 1:	/* logical name (GET only), set service will cause error */
				if (p_params->req_type == REQ_TYPE_GET) {
					*p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
						p_params->out_data.p_content,
						p_params->out_data.length,
						TAG_DATA_OCTET_STRING,
						p_params->descriptor.attr.instance_id,
						6
					);
					if (*p_params->p_out_encoded_len > 0) {
						OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
						OBIS_DISTRIBUTION_SUCCESS(p_params->result);
					}
				}
				break;

			default:
				p_params->handled = FALSE;		/* Forward next call */
				break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION) {
		
		/* Default return code is error */
		OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED, FALSE);
		OBIS_DISTRIBUTION_FAILED(p_params->result);

		p_params->handled = FALSE;		/* Forward next call */
	}
	else {
		/* Do nothing, stop and should be error */
	}

	/* Overwrite result by derived func on each class if params is not handled */
	if (p_params->handled == FALSE) {
		if (derived_func != NULL) {
			(*derived_func)(p_params);
		}
	}
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass
* Interface     : void R_DLMS_CLASSES_DistributeClass(
*               :     fp_distributor_t fp_class_func ,
*               :     fp_distributor_t fp_user_func  ,
*               :     distributor_params_t * p_params,
*               : );
* Description   : Distribute a class by its abstract & user functions
* Arguments     : fp_distributor_t fp_class_func : Abstract function of target class
*               : fp_distributor_t fp_user_func  : User function of target class
*               : distributor_params_t * p_params: Distributor params
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass(
	fp_distributor_t fp_class_func,
	fp_distributor_t fp_user_func,
	distributor_params_t *p_params
)
{
	uint16_t count;

	/* Make default result as success */
	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET) {
		p_params->result.result.data_access = VAL_DATA_ACCESS_RESULT_SUCCESS;
	}
	else if (p_params->req_type == REQ_TYPE_ACTION) {
		p_params->result.result.action = VAL_ACTION_RESULT_SUCCESS;
	}
	
	/* User distribution first */
    if (fp_user_func != NULL) {
		if (p_params->handled == FALSE) {
			p_params->distributor_state = DIST_BEFORE_CLASS_FUNCTION;
			(*fp_user_func)(p_params);
		}
    }

	/* Terminate distribution flow if user function return error */
	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET) {
		if (p_params->result.result.data_access != VAL_DATA_ACCESS_RESULT_SUCCESS) {
			OBIS_DISTRIBUTION_FAILED(p_params->result);
			return;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION) {
		if (p_params->result.result.action != VAL_ACTION_RESULT_SUCCESS) {
			OBIS_DISTRIBUTION_FAILED(p_params->result);
			return;
		}
	}

	/*
	 * From here, abstract class distributor of each class take care
	 * On GET service, class function will do encode of object buffer, then send to client.
	 * On SET and ACTION service, class function do decode of service parameters and put into
	 * p_params->service_params, prepare to set into object buffer or provide decoded params
	 * to ACTION service call under user state.
	 */
    if (fp_class_func != NULL) {
		if (p_params->handled == FALSE) {
			p_params->distributor_state = DIST_UNDER_CLASS_FUNCTION;
			(*fp_class_func)(p_params);
		}
    }

	/* Terminate distribution flow if user function return error */
	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET) {
		if (p_params->result.result.data_access != VAL_DATA_ACCESS_RESULT_SUCCESS) {
			OBIS_DISTRIBUTION_FAILED(p_params->result);
			return;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION) {
		if (p_params->result.result.action != VAL_ACTION_RESULT_SUCCESS) {
			OBIS_DISTRIBUTION_FAILED(p_params->result);
			return;
		}
	}

	/*
	 * After that, user distribution again as confirmation
	 * At this state, user function can do a validity check on SET or ACTION service params
	 * If p_params->sync_set_params is set to FALSE, the copying process of temporary service params
	 * into object buffer will be discarded.
	 */
    if (fp_user_func != NULL) {
		if (p_params->handled == FALSE) {
			p_params->distributor_state = DIST_AFTER_CLASS_FUNCTION;
			(*fp_user_func)(p_params);
		}
    }

	/* Terminate distribution flow if user function return error */
	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET) {
		if (p_params->result.result.data_access != VAL_DATA_ACCESS_RESULT_SUCCESS) {
			OBIS_DISTRIBUTION_FAILED(p_params->result);
			return;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION) {
		if (p_params->result.result.action != VAL_ACTION_RESULT_SUCCESS) {
			OBIS_DISTRIBUTION_FAILED(p_params->result);
			return;
		}
    }

	/* Sync buffer */
	if ((p_params->req_type == REQ_TYPE_SET || p_params->req_type == REQ_TYPE_ACTION) &&
		p_params->result.success == TRUE &&
		p_params->service_params.sync == TRUE &&
		p_params->service_params.memlinks.p_content != NULL)
	{
		for (count = 0; count < p_params->service_params.memlinks.length; count++) {
			if (p_params->service_params.memlinks.p_content[count].dest != NULL &&
				R_DLMS_CLASSES_IsBufferWritable(p_params->service_params.memlinks.p_content[count].dest) == TRUE)
			{
				memcpy(
					p_params->service_params.memlinks.p_content[count].dest,
					p_params->service_params.memlinks.p_content[count].src,
					p_params->service_params.memlinks.p_content[count].size
				);
			}
			else {
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
				return;
			}
		}
	}
	
	OBIS_DISTRIBUTION_SUCCESS(p_params->result);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_IsBufferWritable
* Interface     : uint8_t R_DLMS_CLASSES_IsBufferWritable(uint8_t *p_buffer)
* Description   :
* Arguments     : uint8_t * p_buffer:
* Function Calls:
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_CLASSES_IsBufferWritable(uint8_t *p_buffer)
{
	if ((uint16_t)p_buffer >= ram_start_addr && (uint16_t)p_buffer <= ram_end_addr) {
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_RegisterMemcpyLink
* Interface     : uint8_t R_DLMS_CLASSES_RegisterMemcpyLink(
*               :     distributor_params_t * p_params,
*               :     uint8_t * dest                 ,
*               :     uint8_t * src                  ,
*               :     uint16_t size                  ,
*               : );
* Description   : Register a memcpy link to current service request
* Arguments     : distributor_params_t * p_params: Current service request params
*               : uint8_t * dest                 : Dest address of buffer to write data in
*               : uint8_t * src                  : Src address of data
*               : uint16_t size                  : Size of data
* Return Value  : uint8_t
******************************************************************************/
uint8_t R_DLMS_CLASSES_RegisterMemcpyLink(distributor_params_t *p_params, uint8_t *dest, uint8_t *src, uint16_t size)
{
	memlinks_t *links;

	if (p_params == NULL || src == dest || size == 0) {
		return FALSE;
	}

	links = &p_params->service_params.memlinks;

	if (links->p_content != NULL &&
		links->length < links->alloc_size)
	{
		links->p_content[links->length].src  = src;
		links->p_content[links->length].dest = dest;
		links->p_content[links->length].size = size;
		links->length++;
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_IsFixedStringEqual
* Interface     : uint8_t R_DLMS_CLASSES_IsFixedStringEqual(FixedString *dest, FixedString *src)
* Description   : Check if 2 FixedString objects are equal
* Arguments     : FixedString * dest: Destination fixed string
*               : FixedString * src : Source fixed string
* Return Value  : uint8_t, TRUE or FALSE
******************************************************************************/
uint8_t R_DLMS_CLASSES_IsFixedStringEqual(FixedString *dest, FixedString *src)
{
	if (dest == NULL || src == NULL) {
		return FALSE;
	}

	if (dest->length == src->length && memcmp(dest->p_content, src->p_content, dest->length) == 0) {
		return TRUE;
	}

	return FALSE;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_IsVariantStringEqual
* Interface     : uint8_t R_DLMS_CLASSES_IsVariantStringEqual(VariantString *dest, VariantString *src)
* Description   : Check if 2 VariantString objects are equal
* Arguments     : VariantString * dest: Destination fixed string
*               : VariantString * src : Source fixed string
* Return Value  : uint8_t, TRUE or FALSE
******************************************************************************/
uint8_t R_DLMS_CLASSES_IsVariantStringEqual(VariantString *dest, VariantString *src)
{
	/*
	 * Cast to (FixedString *) is safe since first 2 elements of
	 * VariantString are same as FixedString declaration
	 */
	return R_DLMS_CLASSES_IsFixedStringEqual((FixedString *)dest, (FixedString *)src);
}

/******************************************************************************
* Function Name : r_dlms_classes_cosem_prepare_pre_establish_aa_session
* Interface     : void r_dlms_classes_cosem_prepare_pre_establish_aa_session(
*               :     MgmtChannel mgmt_channel,
*               :     ChannelType channel_type,
*               :     int16_t assc_id
*               : );
* Description   : Prepare an AA connection session by default value of association
*               : defined in r_dlms_config.c
* Arguments     : MgmtChannel mgmt_channel :
*               : ChannelType channel_type :
*               : int16_t assc_id          :
* Function Calls:
* Return Value  : None
******************************************************************************/
void r_dlms_classes_cosem_prepare_pre_establish_aa_session(
	MgmtChannel mgmt_channel,
	ChannelType	channel_type,
	int16_t assc_id
)
{
	int16_t pre_establish_assc_id = R_DLMS_GetPreEstablishedAsscBeingCall(mgmt_channel);
	
	if (pre_establish_assc_id != -1 &&
		pre_establish_assc_id == assc_id &&
		assc_id < OBIS_NUMBER_OF_ASSOCIATION &&
		gp_asscs[assc_id] != NULL)
	{
		g_classes_assc_connection_session[assc_id].connected_assc_id = assc_id;
		g_classes_assc_connection_session[assc_id].mgmt_channel_id = mgmt_channel;
		g_classes_assc_connection_session[assc_id].negotiated_conformance.bytes.bytes0 = gp_asscs[assc_id]->conformance_byte0;
		g_classes_assc_connection_session[assc_id].negotiated_conformance.bytes.bytes1 = gp_asscs[assc_id]->conformance_byte1;
		g_classes_assc_connection_session[assc_id].negotiated_conformance.bytes.bytes2 = gp_asscs[assc_id]->conformance_byte2;
		if (channel_type == CHANNEL_TYPE_HDLC) {
			g_classes_assc_connection_session[assc_id].client_sap = gp_asscs[assc_id]->remote_mac_addr;
		}
		else if (channel_type == CHANNEL_TYPE_TCP || channel_type == CHANNEL_TYPE_UDP) {
			g_classes_assc_connection_session[assc_id].client_sap = gp_asscs[assc_id]->remote_wport;
		}
		else {
			g_classes_assc_connection_session[assc_id].client_sap = 0;
		}
		g_classes_assc_connection_session[assc_id].server_sap = 0;
		g_classes_assc_connection_session[assc_id].p_assc_config = gp_asscs[assc_id];
		g_classes_assc_connection_session[assc_id].client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;
		g_classes_assc_connection_session[assc_id].negotiated_client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;
		g_classes_assc_connection_session[assc_id].CtoS.p_content = NULL;
		g_classes_assc_connection_session[assc_id].CtoS.length = 0;
		g_classes_assc_connection_session[assc_id].dedicated_key.p_content = NULL;
		g_classes_assc_connection_session[assc_id].dedicated_key.length = 0;
		g_classes_assc_connection_session[assc_id].hls_restrict_mode = FALSE;
	}
}

#if defined(DLMS_LIB_VERSION) && (DLMS_LIB_VERSION == LIB_V2_2)
/******************************************************************************
* Function Name : R_DLMS_CLASSES_DecodeObject
* Interface     : uint8_t R_DLMS_CLASSES_DecodeObject(
*               :     st_Cosem_Attr_Desc *cosem_attr_desc,
*               :     uint8_t *pdata,
*               :     uint16_t service_code
*               : );
* Description   : Decode object attribute and method
* Arguments     : st_Cosem_Attr_Desc * cosem_attr_desc -
*               :     COSEM Attribute Descriptor
*               : uint8_t * pdata                   -
*               :     Data pointer, in case of SET/ACTION service
*               : uint16_t service_code             -
*               :     Service code of the request
* Function Calls: R_DLMS_CLASSES_CompareObisCode()
*               : R_DLMS_CLASSES_GetAndCheckAccessRight()
*               : (decoded class)->fp_distributor()
* Return Value  : uint8_t
******************************************************************************/
distributor_result_t R_DLMS_CLASSES_DecodeObject(
	uint8_t				connected_assc_id,
	req_type_t			req_type,
	descriptor_t		*p_descriptor,
	selective_access_t	*p_selective_access,
	service_type_t		*p_service_type,
	void				*p_library_descriptor,
	MandatoryString		in_data,
	MandatoryString		out_data,
	uint16_t			*p_encoded_length
)
{
	uint8_t 						child_index;				/* Child index on child row */
	uint16_t						count;						/* Common for for loop */

	/* Distributor function result for GET/SET/ACTION services */
	distributor_result_t			result = OBIS_DISTRIBUTION_DEFAULT_VALUE;

	master_record_t					*p_master_record;			/* Pointer to master record in g_MasterTable */
	child_record_t					*p_child_record = NULL;		/* Pointer to child record in a specified master record */
	uint16_t						child_record_size;			/* Size of child record (to be cloned into RAM) */

	/* Params for GET/SET/ACTION class distributor function */
	distributor_params_t			distributor_params;			/* Distributor params */
	uint8_t							*p_malloc_buffer = NULL;	/* Malloc buffer shared to child record clone, service params and memlinks */

	/* Vars to check if DEK is used in pass 3 of HLS authentication */
	uint16_t						found_dek_used_in_pass3 = FALSE;
	CosemActionIndication_Params	*p_action_indication_params = NULL;
	SecurityOptionList				*p_security_options = NULL;

	memset(&distributor_params, 0, sizeof(distributor_params_t));

	/*
	 * Find in master table first,
	 * if not found master list, the object is undefine
	 */
	/* Access the master table */
	p_master_record = (master_record_t *)(g_classes_master_table + (uint16_t)g_dlms_master_class_indexes[p_descriptor->all.class_id]);
	if (p_master_record == NULL ||
		p_master_record->child_list_size == NULL ||
		p_master_record->child_list_pointer == NULL ||
		(p_master_record->child_list_size != NULL &&
		*p_master_record->child_list_size == 0))
	{
		/* Not found the object */
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/*
	* Check attr id and method id to be in range defined in master table
	*/
	if (req_type == REQ_TYPE_GET || req_type == REQ_TYPE_SET) {
		if (p_descriptor->attr.attribute_id > p_master_record->number_attrs) {
			/* Not found the object attr */
			OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);
			OBIS_DISTRIBUTION_FAILED(result);
			return result;
		}
	}
	else if (req_type == REQ_TYPE_ACTION) {
		if (p_descriptor->method.method_id > p_master_record->number_methods) {
			/* Not found the object method */
			OBIS_ACTION_RESULT(result, VAL_ACTION_RESULT_OBJECT_UNDEFINED, FALSE);
			OBIS_DISTRIBUTION_FAILED(result);
			return result;
		}
	}
	else {
		/* Not found the object */
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/* Check wheter the connected association (0.0.40.0.0.255) is request or not */
	if (R_DLMS_CLASSES_CompareObisCode(p_descriptor->all.instance_id, (uint8_t *)"\x00\x00\x28\x00\x00\xFF") == TRUE)
	{
		/* Get the record of current connected assc id in master list */
		child_index = connected_assc_id;
		/*
		 * TODO: Buffer check for odd and even data alignment on below code
		 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
		 */
		p_child_record = (child_record_t *)(void *)(
			((uint8_t *)p_master_record->child_list_pointer) +
			(child_index * p_master_record->child_item_size)
		);
		child_record_size = p_master_record->child_item_size;
	}
	else
	{
		/*
		* If found master record, next find OBIS object in child table by
		* visibility, obis code, access right.
		*/
		for (child_index = 0; child_index < *p_master_record->child_list_size; child_index++)
		{
			/* Get the child item */
			/*
			 * TODO: Buffer check for odd and even data alignment on below code
			 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
			 */
			p_child_record = (child_record_t *)(void *)(
				((uint8_t *)p_master_record->child_list_pointer) +
				(child_index * p_master_record->child_item_size)
			);
			child_record_size = p_master_record->child_item_size;

			/*
			* Check the object by the current connected association
			*/
			if (

				/* found object? */
				p_child_record != NULL &&

				/* Visible? */
				(p_child_record->p_access_right == NULL ||
				 (p_child_record->p_access_right != NULL &&
				  (
					 (	g_classes_access_right_none.attributes.length >=
							p_child_record->p_access_right[connected_assc_id].attributes.length &&
						memcmp(
							g_classes_access_right_none.attributes.p_list,
							p_child_record->p_access_right[connected_assc_id].attributes.p_list,
							p_child_record->p_access_right[connected_assc_id].attributes.length) != 0 ) ||

					 (
						g_classes_access_right_none.methods.length >=
							p_child_record->p_access_right[connected_assc_id].methods.length &&
						memcmp(
							g_classes_access_right_none.methods.p_list,
							p_child_record->p_access_right[connected_assc_id].methods.p_list,
							p_child_record->p_access_right[connected_assc_id].methods.length) != 0 )
				  )
				 )
				) &&

				/* Match OBIS code? */
				R_DLMS_CLASSES_CompareObisCode(p_child_record->logical_name, p_descriptor->all.instance_id) == TRUE

				)
			{
				break;
			}
		}

		/* If not found, return error */
		if (child_index >= *p_master_record->child_list_size)
		{
			OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);				/* Object not found */
			OBIS_DISTRIBUTION_FAILED(result);
			return result;
		}
	}

		/*
		 * Check the access right for the current connected association
	* Bring the attribute access right and method access right to Library to enforce security of response message
		 * Grant full access when access right pointer is NULL
		 */
		if (p_child_record->p_access_right != NULL &&
		R_DLMS_CLASSES_GetAndCheckAccessRight(
			p_library_descriptor,
				req_type,
				p_descriptor->all.item_id,
				&p_child_record->p_access_right[connected_assc_id]
			) == FALSE)
		{
			OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED, FALSE);		/* Violate scope */
			OBIS_DISTRIBUTION_FAILED(result);
			return result;
		}

	/*
	 * Restrict the access to reply_to_HLS_authentication of Association LN object
	 * when HLS authentication is required in current connected association
	 */
	if (g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID2_HIGH_SECURITY ||
		g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID3_HIGH_SECURITY_MD5 ||
		g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID4_HIGH_SECURITY_SHA1 ||
		g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID5_HIGH_SECURITY_GMAC ||
		g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID6_HIGH_SECURITY_SHA256 ||
		g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID7_HIGH_SECURITY_ECDSA)
	{
		/* Not finish authentication and try to access to other than reply_to_HLS_authentication? */
		if (g_classes_assc_connection_session[connected_assc_id].hls_restrict_mode == TRUE)
		{
			if (req_type != REQ_TYPE_ACTION)
			{
				OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED, FALSE);		/* Violate scope */
				OBIS_DISTRIBUTION_FAILED(result);
				return result;
			}
			else if (p_descriptor->method.method_id != 1)	/* reply_to_HLS_authentication(data) method */
			{
				OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED, FALSE);		/* Violate scope */
				OBIS_DISTRIBUTION_FAILED(result);
				return result;
			}
			else
			{
				/* 
				 * CTT 3.0 require that in pass 3 (invoke of reply_to_HLS_authentication(data)), DEK should not be used.
				 * Else, T_APPL_OPEN_3 will be FAILED. Following code rejects access to that method if DEK is used, in pass 3.
				 */
				if (p_library_descriptor != NULL) {
					p_action_indication_params = (CosemActionIndication_Params *)p_library_descriptor;
					if (p_action_indication_params->p_dispatch_context != NULL &&
						p_action_indication_params->p_dispatch_context->p_additional_params != NULL)
					{
						/*
						 * Get list of security options (output) after deciphering process and
						 * search on all elements if DEK is used.
						 */
						p_security_options = &p_action_indication_params->p_dispatch_context->p_additional_params->security_options;

						found_dek_used_in_pass3 = FALSE;
						for (count = 0; count < p_security_options->usage; count++) {
							if (p_security_options->elements[count].protection_type == PROTECTION_DED_CIPHERING ||
								p_security_options->elements[count].protection_type == PROTECTION_GENERAL_DED_CIPHERING)
							{
								found_dek_used_in_pass3 = TRUE;
								break;
							}
						}

						if (found_dek_used_in_pass3 == TRUE) {
							OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);		/* Temporary failure */
							OBIS_DISTRIBUTION_FAILED(result);
							return result;
						}
					}
				}
			}
		}
	}

	/* Create a share dynamic buffer for child record clone, service buffer and memlinks */
	p_malloc_buffer = (uint8_t *)R_DLMS_Malloc(child_record_size + CLASSES_TEMPORARY_BUFFER_SIZE + sizeof(memlink_t) * CLASSES_MEMLINKS_MAX_ITEMS);
	if (p_malloc_buffer == NULL) {
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT, FALSE);	/* Fatal error, malloc fail */
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/* Clone p_child_record for user distributor to use */
	memcpy(p_malloc_buffer, p_child_record, child_record_size);
	/*
	* TODO: Buffer check for odd and even data alignment on below code
	* Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
	*/
	p_child_record = (child_record_t *)(void *)p_malloc_buffer;

	/*
	* Make input params for distributor func
	*/
	distributor_params.master_index				= p_descriptor->all.class_id;	/* [In] Id of the row in master list */
	distributor_params.child_index				= child_index;					/* [In] Id of the row in child list */
	distributor_params.p_child_record			= p_child_record;				/* [In] Child record of calling object */
	distributor_params.connected_assc_id		= connected_assc_id;			/* [In] Connected assc id of the current request */
	distributor_params.p_assc_session =
		&g_classes_assc_connection_session[connected_assc_id];					/* [In] Connected assc session of the current request */
	distributor_params.req_type					= req_type;						/* [In] Request type (GET/SET/ACTION) */
	if (p_service_type != NULL) {
		distributor_params.service_type			= *p_service_type;				/* [In] Service type */
	}
	if (p_descriptor != NULL) {
		distributor_params.descriptor			= *p_descriptor;				/* [In] Descriptor of attr or method */
	}
	if (p_selective_access != NULL) {
		distributor_params.selective_access		= *p_selective_access;			/* [In] Selective access params for GET/SET service */
	}
	distributor_params.p_library_descriptor		= p_library_descriptor;			/* [In] Library Descriptor (GET/SET/ACTION), refer to r_dlms_application.h for details.
																				 *      NULL is passed into this param in some cases */
	distributor_params.in_data					= in_data;						/* [In] Data from library in case of SET/ACTION */
	/* Guarantee response PDU size smaller or equal to Client Max PDU size */
	if (g_classes_assc_connection_session[connected_assc_id].client_max_pdu_size != 0 &&	/* 0 means no limit PDU size */
		g_classes_assc_connection_session[connected_assc_id].client_max_pdu_size >= 12 &&	/* 1-11 reserved */
		(g_classes_assc_connection_session[connected_assc_id].client_max_pdu_size - 64) < out_data.length)
	{
		out_data.length = g_classes_assc_connection_session[connected_assc_id].client_max_pdu_size - 64;
	}
	g_classes_assc_connection_session[connected_assc_id].negotiated_client_max_pdu_size = out_data.length;
		
	distributor_params.out_data					= out_data;						/* [Out] Output buffer for encoded data */
	distributor_params.p_out_encoded_len		= p_encoded_length;				/* [Out] Actual output buffer length for encoded data */
	distributor_params.distributor_state		= DIST_UNDER_CLASS_FUNCTION;	/* [In] Distribution state of current params (before or under or after class function) */
	distributor_params.handled					= FALSE;						/* [In, Out] Indicate that the service req (GET/SET/ACTION) is already handled and no need subsequence call */

	/* Service param dyn buffer on heap */
	distributor_params.service_params.malloc.p_content = p_malloc_buffer + child_record_size;
	distributor_params.service_params.malloc.length = 0;
	distributor_params.service_params.malloc.alloc_size = CLASSES_TEMPORARY_BUFFER_SIZE;
	
	/*
	 * memlinks
	 * TODO: Buffer check for odd and even data alignment on below code
	 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
	 */
	distributor_params.service_params.memlinks.p_content = (memlink_t *)(void *)(p_malloc_buffer + child_record_size + CLASSES_TEMPORARY_BUFFER_SIZE);
	distributor_params.service_params.memlinks.length = 0;
	distributor_params.service_params.memlinks.alloc_size = CLASSES_MEMLINKS_MAX_ITEMS;
	
	distributor_params.service_params.sync				= TRUE;					/* [In, Out] Indicates that temporary params on SET or ACTION service will be copied to object defined buffer thru memlinks */
	distributor_params.service_params.created			= FALSE;				/* [Out] Indicates that an object of service params has been created on dynamic buffer */
	distributor_params.service_params.decode_success	= FALSE;				/* [Out] Indicates that var in malloc is decode successful & ready to use on user distributor */
	distributor_params.result							= result;				/* [In, Out] Distribution result, flow from user distributor thru class function */

	/* Distribution by Abstract Distributor */
	R_DLMS_CLASSES_AbstractDistributor(p_master_record->fp_distributor, &distributor_params);

	/* Diag max usage */
	if (g_dlms_diag_memlinks_max_usage < distributor_params.service_params.memlinks.length) {
		g_dlms_diag_memlinks_max_usage = distributor_params.service_params.memlinks.length;
	}
	if (g_dlms_diag_malloc_temporary_buffer_max_usage < distributor_params.service_params.malloc.length) {
		g_dlms_diag_malloc_temporary_buffer_max_usage = distributor_params.service_params.malloc.length;
	}

	/* Free malloc buffer */
	if (p_malloc_buffer != NULL) {
		R_DLMS_Free(p_malloc_buffer);
		p_malloc_buffer = NULL;
	}

	return (distributor_params.result);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_EncodeDataAttributeInternally
* Interface     : uint8_t R_DLMS_CLASSES_EncodeDataAttributeInternally(
*               :     uint8_t               connected_assc_id,
*               :     req_type_t            req_type,
*               :     descriptor_t          *p_descriptor,
*               :     selective_access_t    *p_selective_access,
*               :     service_type_t        *p_service_type,
*               :     void                  *p_library_descriptor,
*               :     MandatoryString       in_data,
*               :     MandatoryString       out_data,
*               :     uint16_t              *p_encoded_length
*               : );
* Description   : Internally encode object attribute REGARDLESS OF THE ACCESS RIGHT
*               : This function is cloned from R_DLMS_CLASSES_DecodeObject function
* Function Calls: R_DLMS_CLASSES_CompareObisCode()
*               : (decoded class)->fp_distributor()
* Return Value  : distributor_result_t result
******************************************************************************/
distributor_result_t R_DLMS_CLASSES_EncodeDataAttributeInternally(
	uint8_t				connected_assc_id,
	req_type_t			req_type,
	descriptor_t		*p_descriptor,
	selective_access_t	*p_selective_access,
	service_type_t		*p_service_type,
	void				*p_library_descriptor,
	MandatoryString		in_data,
	MandatoryString		out_data,
	uint16_t			*p_encoded_length
)
{
	uint8_t 						child_index;				/* Child index on child row */
	uint16_t						count;						/* Common for for loop */

	/* Distributor function result for GET/SET/ACTION services */
	distributor_result_t			result = OBIS_DISTRIBUTION_DEFAULT_VALUE;

	master_record_t					*p_master_record;			/* Pointer to master record in g_MasterTable */
	child_record_t					*p_child_record = NULL;		/* Pointer to child record in a specified master record */
	uint16_t						child_record_size;			/* Size of child record (to be cloned into RAM) */

	/* Params for GET/SET/ACTION class distributor function */
	distributor_params_t			distributor_params;			/* Distributor params */
	uint8_t							*p_malloc_buffer = NULL;	/* Malloc buffer shared to child record clone, service params and memlinks */

	memset(&distributor_params, 0, sizeof(distributor_params_t));

	/* Load pre-defined configuration of pre-establish AA to association connection session */
	if (connected_assc_id < OBIS_NUMBER_OF_ASSOCIATION &&
		gp_asscs[connected_assc_id] != NULL &&
		gp_asscs[connected_assc_id]->pre_established == TRUE)
	{
		g_classes_assc_connection_session[connected_assc_id].connected_assc_id = connected_assc_id;
		g_classes_assc_connection_session[connected_assc_id].negotiated_conformance.bytes.bytes0 = gp_asscs[connected_assc_id]->conformance_byte0;
		g_classes_assc_connection_session[connected_assc_id].negotiated_conformance.bytes.bytes1 = gp_asscs[connected_assc_id]->conformance_byte1;
		g_classes_assc_connection_session[connected_assc_id].negotiated_conformance.bytes.bytes2 = gp_asscs[connected_assc_id]->conformance_byte2;
		g_classes_assc_connection_session[connected_assc_id].p_assc_config = gp_asscs[connected_assc_id];
		g_classes_assc_connection_session[connected_assc_id].client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;
		g_classes_assc_connection_session[connected_assc_id].negotiated_client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;
		g_classes_assc_connection_session[connected_assc_id].CtoS.p_content = NULL;
		g_classes_assc_connection_session[connected_assc_id].CtoS.length = 0;
		g_classes_assc_connection_session[connected_assc_id].dedicated_key.p_content = NULL;
		g_classes_assc_connection_session[connected_assc_id].dedicated_key.length = 0;
		g_classes_assc_connection_session[connected_assc_id].hls_restrict_mode = FALSE;
	}
	
	/* Check if Class of object is existed in Master table */
	p_master_record = (master_record_t *)(g_classes_master_table + (uint16_t)g_dlms_master_class_indexes[p_descriptor->all.class_id]);
	if (p_master_record == NULL ||
		p_master_record->child_list_size == NULL ||
		p_master_record->child_list_pointer == NULL ||
		(p_master_record->child_list_size != NULL &&
		*p_master_record->child_list_size == 0))
	{
		/* Not found the class */
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/*
	* Check attr id and method id to be in range defined in master table
	*/
	if (req_type != REQ_TYPE_GET || p_descriptor->attr.attribute_id > p_master_record->number_attrs) {
		/* Not found the object attr */
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/*
	* Find OBIS object in child table by obis code.
	*/
	for (child_index = 0; child_index < *p_master_record->child_list_size; child_index++)
	{
		/* Get the child item */
		/*
		 * TODO: Buffer check for odd and even data alignment on below code
		 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
		 */
		p_child_record = (child_record_t *)(void *)(
			((uint8_t *)p_master_record->child_list_pointer) +
			(child_index * p_master_record->child_item_size)
		);
		child_record_size = p_master_record->child_item_size;

		/*
		* Check the object by the current connected association
		*/
		if (
				/* found object? */
				(p_child_record != NULL) &&
				/* Match OBIS code? */
				(R_DLMS_CLASSES_CompareObisCode(p_child_record->logical_name, p_descriptor->all.instance_id) == TRUE)
			)
		{
			break;
		}
	}

	/* If not found, return error */
	if (child_index >= *p_master_record->child_list_size)
	{
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);				/* Object not found */
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/* Create a share dynamic buffer for child record clone, service buffer and memlinks */
	p_malloc_buffer = (uint8_t *)R_DLMS_Malloc(child_record_size + CLASSES_TEMPORARY_BUFFER_SIZE + sizeof(memlink_t) * CLASSES_MEMLINKS_MAX_ITEMS);
	if (p_malloc_buffer == NULL) {
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT, FALSE);	/* Fatal error, malloc fail */
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/* Clone p_child_record for user distributor to use */
	memcpy(p_malloc_buffer, p_child_record, child_record_size);
	/*
	* TODO: Buffer check for odd and even data alignment on below code
	* Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
	*/
	p_child_record = (child_record_t *)(void *)p_malloc_buffer;

	/*
	* Make input params for distributor func
	*/
	distributor_params.master_index				= p_descriptor->all.class_id;	/* [In] Id of the row in master list */
	distributor_params.child_index				= child_index;					/* [In] Id of the row in child list */
	distributor_params.p_child_record			= p_child_record;				/* [In] Child record of calling object */
	distributor_params.connected_assc_id		= connected_assc_id;			/* [In] Connected assc id of the current request */
	distributor_params.p_assc_session =
		&g_classes_assc_connection_session[connected_assc_id];					/* [In] Connected assc session of the current request */
	distributor_params.req_type					= req_type;						/* [In] Request type (GET/SET/ACTION) */
	if (p_service_type != NULL) {
		distributor_params.service_type			= *p_service_type;				/* [In] Service type */
	}
	if (p_descriptor != NULL) {
		distributor_params.descriptor			= *p_descriptor;				/* [In] Descriptor of attr or method */
	}
	if (p_selective_access != NULL) {
		distributor_params.selective_access		= *p_selective_access;			/* [In] Selective access params for GET/SET service */
	}
	distributor_params.p_library_descriptor		= p_library_descriptor;			/* [In] Library Descriptor (GET/SET/ACTION), refer to r_dlms_application.h for details.
																				 *      NULL is passed into this param in some cases */
	distributor_params.in_data					= in_data;						/* [In] Data from library in case of SET/ACTION */
	distributor_params.out_data					= out_data;						/* [Out] Output buffer for encoded data */
	distributor_params.p_out_encoded_len		= p_encoded_length;				/* [Out] Actual output buffer length for encoded data */
	distributor_params.distributor_state		= DIST_UNDER_CLASS_FUNCTION;	/* [In] Distribution state of current params (before or under or after class function) */
	distributor_params.handled					= FALSE;						/* [In, Out] Indicate that the service req (GET/SET/ACTION) is already handled and no need subsequence call */

	/* Service param dyn buffer on heap */
	distributor_params.service_params.malloc.p_content = p_malloc_buffer + child_record_size;
	distributor_params.service_params.malloc.length = 0;
	distributor_params.service_params.malloc.alloc_size = CLASSES_TEMPORARY_BUFFER_SIZE;
	
	/*
	 * memlinks
	 * TODO: Buffer check for odd and even data alignment on below code
	 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
	 */
	distributor_params.service_params.memlinks.p_content = (memlink_t *)(void *)(p_malloc_buffer + child_record_size + CLASSES_TEMPORARY_BUFFER_SIZE);
	distributor_params.service_params.memlinks.length = 0;
	distributor_params.service_params.memlinks.alloc_size = CLASSES_MEMLINKS_MAX_ITEMS;
	
	distributor_params.service_params.sync				= TRUE;					/* [In, Out] Indicates that temporary params on SET or ACTION service will be copied to object defined buffer thru memlinks */
	distributor_params.service_params.created			= FALSE;				/* [Out] Indicates that an object of service params has been created on dynamic buffer */
	distributor_params.service_params.decode_success	= FALSE;				/* [Out] Indicates that var in malloc is decode successful & ready to use on user distributor */
	distributor_params.result							= result;				/* [In, Out] Distribution result, flow from user distributor thru class function */

	/* Distribution by Abstract Distributor */
	R_DLMS_CLASSES_AbstractDistributor(p_master_record->fp_distributor, &distributor_params);

	/* Free malloc buffer */
	if (p_malloc_buffer != NULL) {
		R_DLMS_Free(p_malloc_buffer);
		p_malloc_buffer = NULL;
	}

	return (distributor_params.result);
}

/* --------------------------------------------------------
* Functions to link with library
* --------------------------------------------------------
*/
/******************************************************************************
* Function Name : r_dlms_classes_cosem_get_indication
* Interface     : None r_dlms_classes_cosem_get_indication(
*               :     MgmtChannel mgmt_channel            ,
*               :     CosemGetIndication_Params * p_params,
*               : );
* Description   :
* Arguments     : MgmtChannel mgmt_channel            :
*               : CosemGetIndication_Params * p_params:
* Function Calls:
* Return Value  : None
******************************************************************************/
void r_dlms_classes_cosem_get_indication(MgmtChannel mgmt_channel, CosemGetIndication_Params *p_params)
{
	/* Params for COSEM-Get-Response */
	CosemGetResponse_Params res_params;
	GetDataResult			get_data_result;

	/* Params for Classes functions */
	uint8_t					out_data_buffer[CLASSES_DISTRIBUTION_BUFFER_SIZE];					/* APDU to store buffer */
	MandatoryString			in_data = { NULL, 0 };												/* Input data string */
	MandatoryString			out_data = { out_data_buffer, CLASSES_DISTRIBUTION_BUFFER_SIZE };	/* Output buffer string */
	uint16_t				encoded_len = 0;													/* Actual output buffer length for encoded data */
	distributor_result_t	class_func_result = OBIS_DISTRIBUTION_DEFAULT_VALUE;				/* Class function result */

	/* Association management */
	ChannelType				channel_type = CHANNEL_TYPE_NONE;
	int16_t					assc_id = -1;

	/* Check if current channel is connected or not */
	assc_id = R_DLMS_GetConnectedAsscId(mgmt_channel);
	if (assc_id == -1) {
		return;
	}

	/* Get current channel type of the connected channel */
	channel_type = R_MGMT_GetChannelType(mgmt_channel);

	/*
	 * In case of service call in pre-establish AA, an AA connection session is prepared
	 * by default value of association defined in r_dlms_config.c
	 */
	r_dlms_classes_cosem_prepare_pre_establish_aa_session(mgmt_channel, channel_type, assc_id);
	
	memset(&res_params, 0, sizeof(CosemGetResponse_Params));
	memset(&get_data_result, 0, sizeof(GetDataResult));
	res_params.invoke_id = p_params->invoke_id;
	res_params.priority = p_params->priority;
	res_params.p_dispatch_context = p_params->p_dispatch_context;
	res_params.service_class = SERVICE_CLASS_CONFIRMED;

	switch (p_params->request_type)
	{
		case COSEM_GET_REQUEST_NORMAL:
			memcpy(
				&g_classes_assc_connection_session[assc_id].get_service_attr_desc,
				&p_params->cosem_attr_descriptor.p_list[0].cosem_attribute_descriptor,
				sizeof(CosemAttributeDescriptor)
			);

			class_func_result = R_DLMS_CLASSES_DecodeObject(
				assc_id,
				REQ_TYPE_GET,
				(descriptor_t *)(&(p_params->cosem_attr_descriptor.p_list[0].cosem_attribute_descriptor)),
				(selective_access_t *)(&(p_params->cosem_attr_descriptor.p_list[0].access_selection)),
				(service_type_t *)(&(p_params->request_type)),
				p_params,
				in_data,
				out_data,
				&encoded_len
			);

			break;

		case COSEM_GET_REQUEST_NEXT:
			class_func_result = R_DLMS_CLASSES_DecodeObject(
				assc_id,
				REQ_TYPE_GET,
				(descriptor_t *)(&(g_classes_assc_connection_session[assc_id].get_service_attr_desc)),
				NULL,
				(service_type_t *)(&(p_params->request_type)),
				p_params,
				in_data,
				out_data,
				&encoded_len
			);

			break;

		/* TODO : Support Get with list, below code is no response to Client */
		case COSEM_GET_REQUEST_WITH_LIST:
			return;

		default:
			return;
	}

	/* Class function return SUCCESS? */
	if (class_func_result.success == TRUE && 
		class_func_result.result.data_access == VAL_DATA_ACCESS_RESULT_SUCCESS)
	{
		/* Continous partial? */
		
		if (class_func_result.partial == TRUE) {
			/*
			 * Check with negotiated conformance bits before proceed the block transfer to client, if bit "get with block transfer" not enable
			 * in negotiated conformance bits, return error when client do GET service but encoded APDU in meter is too long.
			 */
			if (g_classes_assc_connection_session[assc_id].negotiated_conformance.bits.block_transfer_with_get == TRUE) {
				res_params.response_type = COSEM_GET_RESPONSE_ONE_BLOCK;
				res_params.result.data_block_g.block_number = g_classes_assc_connection_session[assc_id].get_service_block_number + 1;
				res_params.result.data_block_g.last_block = FALSE;
				res_params.result.data_block_g.result_tag = TAG_DATABLOCK_G_RESULT_RAW_DATA;
				res_params.result.data_block_g.result.raw_data.p_content = out_data_buffer;
				res_params.result.data_block_g.result.raw_data.length = encoded_len;
				g_classes_assc_connection_session[assc_id].get_service_block_number++;
			}
			else {
				/* Raise error "data block unavailable" to client */
				res_params.response_type = COSEM_GET_RESPONSE_NORMAL;
				get_data_result.result_tag = TAG_GET_ACCESS_RESULT_DATA_ACCESS_RESULT;
				get_data_result.result.data_access_result = VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE;
				res_params.result.get_data_result.p_list = &get_data_result;
				res_params.result.get_data_result.length = 1;
			}
		}
		/* Stop partial? */
		else if (g_classes_assc_connection_session[assc_id].get_service_is_block_response == TRUE) {
			res_params.response_type = COSEM_GET_RESPONSE_LAST_BLOCK;
			res_params.result.data_block_g.block_number = g_classes_assc_connection_session[assc_id].get_service_block_number + 1;
			res_params.result.data_block_g.last_block = TRUE;
			res_params.result.data_block_g.result_tag = TAG_DATABLOCK_G_RESULT_RAW_DATA;
			res_params.result.data_block_g.result.raw_data.p_content = out_data_buffer;
			res_params.result.data_block_g.result.raw_data.length = encoded_len;
			g_classes_assc_connection_session[assc_id].get_service_block_number++;
		}
		else {
			res_params.response_type = COSEM_GET_RESPONSE_NORMAL;
			get_data_result.result_tag = TAG_GET_ACCESS_RESULT_DATA;
			get_data_result.result.data.p_content = out_data_buffer;
			get_data_result.result.data.length = encoded_len;
			res_params.result.get_data_result.p_list = &get_data_result;
			res_params.result.get_data_result.length = 1;
		}
	}
	else {
		res_params.response_type = COSEM_GET_RESPONSE_NORMAL;
		get_data_result.result_tag = TAG_GET_ACCESS_RESULT_DATA_ACCESS_RESULT;
		get_data_result.result.data_access_result = class_func_result.result.data_access;
		res_params.result.get_data_result.p_list = &get_data_result;
		res_params.result.get_data_result.length = 1;
	}

	/* Block response status */
	if (g_classes_assc_connection_session[assc_id].negotiated_conformance.bits.block_transfer_with_get == TRUE) {
		g_classes_assc_connection_session[assc_id].get_service_is_block_response = class_func_result.partial;
	}
	else {
		g_classes_assc_connection_session[assc_id].get_service_is_block_response = FALSE;
	}

	/* Only reply to confirmed service on HDLC profile or TCP/UDP with confirm bit is set */
	if (channel_type == CHANNEL_TYPE_HDLC ||
		((channel_type == CHANNEL_TYPE_UDP || channel_type == CHANNEL_TYPE_TCP) &&
		 p_params->service_class == SERVICE_CLASS_CONFIRMED)) {
		R_COSEM_GET_Response(mgmt_channel, &res_params);
	}
}

/******************************************************************************
* Function Name : r_dlms_classes_cosem_set_indication
* Interface     : None r_dlms_classes_cosem_set_indication(
*               :     MgmtChannel mgmt_channel            ,
*               :     CosemSetIndication_Params * p_params,
*               : );
* Description   :
* Arguments     : MgmtChannel mgmt_channel                 :
*               : CosemSetIndication_Params * p_params:
* Function Calls:
* Return Value  : None
******************************************************************************/
void r_dlms_classes_cosem_set_indication(MgmtChannel mgmt_channel, CosemSetIndication_Params *p_params)
{
	/* Params for COSEM-Set-Response */
	CosemSetResponse_Params res_params;
	DataAccessResult_Value	data_access_result_list[COSEM_SET_LIST_MAX_SIZE];

	/* Params for Classes functions */
	MandatoryString			out_data = { NULL, 0 };										/* Output buffer string */
	uint16_t				encoded_len = 0;											/* Actual output buffer length for encoded data */
	distributor_result_t	class_func_result = OBIS_DISTRIBUTION_DEFAULT_VALUE;		/* Class function result */
	
	/* Association management */
	ChannelType				channel_type = CHANNEL_TYPE_NONE;
	int16_t					assc_id = -1;
	uint16_t				count;

	/* Check if current channel is connected or not */
	assc_id = R_DLMS_GetConnectedAsscId(mgmt_channel);
	if (assc_id == -1) {
		return;
	}

	/* Get current channel type of the connected channel */
	channel_type = R_MGMT_GetChannelType(mgmt_channel);

	/*
	 * In case of service call in pre-establish AA, an AA connection session is prepared
	 * by default value of association defined in r_dlms_config.c
	 */
	r_dlms_classes_cosem_prepare_pre_establish_aa_session(mgmt_channel, channel_type, assc_id);
	
	memset(&res_params, 0, sizeof(CosemSetResponse_Params));
	res_params.invoke_id = p_params->invoke_id;
	res_params.priority = p_params->priority;
	res_params.p_dispatch_context = p_params->p_dispatch_context;
	res_params.service_class = SERVICE_CLASS_CONFIRMED;

	/* Response normal is default */
	res_params.response_type = COSEM_SET_RESPONSE_NORMAL;
	data_access_result_list[0] = VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED;
	res_params.result.p_list = data_access_result_list;
	res_params.result.length = 1;

	switch (p_params->request_type)
	{
		case COSEM_SET_REQUEST_NORMAL:
			class_func_result = R_DLMS_CLASSES_DecodeObject(
				assc_id,
				REQ_TYPE_SET,
				(descriptor_t *)(&(p_params->cosem_attr_descriptor.p_list[0].cosem_attribute_descriptor)),
				(selective_access_t *)(&(p_params->cosem_attr_descriptor.p_list[0].access_selection)),
				(service_type_t *)(&(p_params->request_type)),
				p_params,
				p_params->data.p_list[0],
				out_data,
				&encoded_len
			);
			data_access_result_list[0] = class_func_result.result.data_access;
			break;

		/* TODO, below code is no response to Client */
		case COSEM_SET_REQUEST_FIRST_BLOCK:
			return;

		/* TODO, below code is no response to Client */
		case COSEM_SET_REQUEST_ONE_BLOCK:
			return;

		/* TODO, below code is no response to Client */
		case COSEM_SET_REQUEST_LAST_BLOCK:
			return;

		case COSEM_SET_REQUEST_WITH_LIST:

			for (count = 0; count < p_params->cosem_attr_descriptor.length; count++) {
				data_access_result_list[count] = VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED;
				class_func_result = R_DLMS_CLASSES_DecodeObject(
					assc_id,
					REQ_TYPE_SET,
					(descriptor_t *)(&(p_params->cosem_attr_descriptor.p_list[count].cosem_attribute_descriptor)),
					(selective_access_t *)(&(p_params->cosem_attr_descriptor.p_list[count].access_selection)),
					(service_type_t *)(&(p_params->request_type)),
					p_params,
					p_params->data.p_list[count],
					out_data,
					&encoded_len
				);
				data_access_result_list[count] = class_func_result.result.data_access;
			}

			res_params.response_type = COSEM_SET_RESPONSE_WITH_LIST;
			res_params.result.length = p_params->cosem_attr_descriptor.length;

			break;

		/* TODO, below code is no response to Client */
		case COSEM_SET_REQUEST_FIRST_BLOCK_WITH_LIST:
			return;

		default:
			return;
	}

	/* Only reply to confirmed service on HDLC profile or TCP/UDP with confirm bit is set */
	if (channel_type == CHANNEL_TYPE_HDLC ||
		((channel_type == CHANNEL_TYPE_UDP || channel_type == CHANNEL_TYPE_TCP) &&
		p_params->service_class == SERVICE_CLASS_CONFIRMED)) {
		R_COSEM_SET_Response(mgmt_channel, &res_params);
	}

	/* Set indication to object layer */
	R_DLMS_OBJECTS_CosemSetIndication(mgmt_channel, p_params);
}

/******************************************************************************
* Function Name : r_dlms_classes_cosem_action_indication
* Interface     : None r_dlms_classes_cosem_action_indication(
*               :     MgmtChannel mgmt_channel               ,
*               :     CosemActionIndication_Params * p_params,
*               : );
* Description   :
* Arguments     : MgmtChannel mgmt_channel               :
*               : CosemActionIndication_Params * p_params:
* Function Calls:
* Return Value  : None
******************************************************************************/
void r_dlms_classes_cosem_action_indication(MgmtChannel mgmt_channel, CosemActionIndication_Params *p_params)
{
	/* Params for COSEM-Action-Response */
	CosemActionResponse_Params		res_params;
	ActionResponseWithOptionalData	action_response_list[COSEM_ACTION_LIST_MAX_SIZE];
	
	/* Params for Classes functions */
	uint8_t					out_data_buffer[CLASSES_DISTRIBUTION_BUFFER_SIZE];					/* APDU to store buffer */
	MandatoryString			out_data = { out_data_buffer, CLASSES_DISTRIBUTION_BUFFER_SIZE };	/* Output buffer string */
	uint16_t				encoded_len = 0;													/* Actual output buffer length for encoded data */
	distributor_result_t	class_func_result = OBIS_DISTRIBUTION_DEFAULT_VALUE;				/* Class function result */

	/* Association management */
	ChannelType				channel_type = CHANNEL_TYPE_NONE;
	int16_t					assc_id = -1;
	uint16_t				count;

	/* Check if current channel is connected or not */
	assc_id = R_DLMS_GetConnectedAsscId(mgmt_channel);
	if (assc_id == -1) {
		return;
	}

	/* Get current channel type of the connected channel */
	channel_type = R_MGMT_GetChannelType(mgmt_channel);

	/*
	 * In case of service call in pre-establish AA, an AA connection session is prepared
	 * by default value of association defined in r_dlms_config.c
	 */
	r_dlms_classes_cosem_prepare_pre_establish_aa_session(mgmt_channel, channel_type, assc_id);
	
	memset(&res_params, 0, sizeof(CosemActionResponse_Params));
	memset(&action_response_list, 0, sizeof(ActionResponseWithOptionalData)* COSEM_ACTION_LIST_MAX_SIZE);
	res_params.invoke_id = p_params->invoke_id;
	res_params.priority = p_params->priority;
	res_params.p_dispatch_context = p_params->p_dispatch_context;
	res_params.service_class = SERVICE_CLASS_CONFIRMED;

	/* Response normal is default */
	res_params.response_type = COSEM_ACTION_RESPONSE_NORMAL;
	action_response_list[0].result = VAL_ACTION_RESULT_OBJECT_UNDEFINED;
	action_response_list[0].return_parameters.use = FALSE;
	res_params.action_response.p_list = action_response_list;
	res_params.action_response.length = 1;

	switch (p_params->request_type)
	{
		case COSEM_ACTION_REQUEST_NORMAL:
			class_func_result = R_DLMS_CLASSES_DecodeObject(
				assc_id,
				REQ_TYPE_ACTION,
				(descriptor_t *)(&(p_params->cosem_method_descriptor.p_list[0])),
				NULL,
				(service_type_t *)(&(p_params->request_type)),
				p_params,
				p_params->method_invocation_parameters.p_list[0],
				out_data,
				&encoded_len
			);
			action_response_list[0].result = class_func_result.result.action;
			if (class_func_result.result.action == VAL_ACTION_RESULT_SUCCESS && encoded_len > 0) {
				action_response_list[0].return_parameters.use = TRUE;
				action_response_list[0].return_parameters.get_data_result.result_tag = TAG_GET_ACCESS_RESULT_DATA;
				action_response_list[0].return_parameters.get_data_result.result.data.p_content = out_data_buffer;
				action_response_list[0].return_parameters.get_data_result.result.data.length = encoded_len;
			}
			break;

		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_NEXT:
			return;
		
		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_FIRST_BLOCK:
			return;
		
		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_ONE_BLOCK:
			return;
		
		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_LAST_BLOCK:
			return;

		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_WITH_LIST:
			return;

		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_WITH_LIST_AND_FIRST_BLOCK:
			return;

		default:
			return;
	}

	/* Only reply to confirmed service on HDLC profile or TCP/UDP with confirm bit is set */
	if (channel_type == CHANNEL_TYPE_HDLC ||
		((channel_type == CHANNEL_TYPE_UDP || channel_type == CHANNEL_TYPE_TCP) &&
		p_params->service_class == SERVICE_CLASS_CONFIRMED)) {
		R_COSEM_ACTION_Response(mgmt_channel, &res_params);
	}

	/* Action indication to object layer (for the new key activation if any) */
	R_DLMS_OBJECTS_CosemActionIndication(mgmt_channel, p_params);
}
#else
/******************************************************************************
* Function Name : R_DLMS_CLASSES_DecodeObject
* Interface     : uint8_t R_DLMS_CLASSES_DecodeObject(
*               :     st_Cosem_Attr_Desc *cosem_attr_desc,
*               :     uint8_t *pdata,
*               :     uint16_t service_code
*               : );
* Description   : Decode object attribute and method
* Arguments     : st_Cosem_Attr_Desc * cosem_attr_desc -
*               :     COSEM Attribute Descriptor
*               : uint8_t * pdata                   -
*               :     Data pointer, in case of SET/ACTION service
*               : uint16_t service_code             -
*               :     Service code of the request
* Function Calls: R_DLMS_CLASSES_CompareObisCode()
*               : R_DLMS_CLASSES_GetAndCheckAccessRight()
*               : (decoded class)->fp_distributor()
* Return Value  : uint8_t
******************************************************************************/
distributor_result_t R_DLMS_CLASSES_DecodeObject(
	uint8_t				connected_assc_id,
	req_type_t			req_type,
	descriptor_t		*p_descriptor,
	selective_access_t	*p_selective_access,
	service_type_t		*p_service_type,
	void				*p_library_descriptor,
	MandatoryString		in_data,
	MandatoryString		out_data,
	uint16_t			*p_encoded_length
)
{
	uint8_t 						child_index;				/* Child index on child row */
	uint16_t						count;						/* Common for for loop */

	/* Distributor function result for GET/SET/ACTION services */
	distributor_result_t			result = OBIS_DISTRIBUTION_DEFAULT_VALUE;

	master_record_t					*p_master_record;			/* Pointer to master record in g_MasterTable */
	child_record_t					*p_child_record = NULL;		/* Pointer to child record in a specified master record */
	uint16_t						child_record_size;			/* Size of child record (to be cloned into RAM) */

	/* Params for GET/SET/ACTION class distributor function */
	distributor_params_t			distributor_params;			/* Distributor params */

	/* Stack buffer for child record clone 64 is maximum size of a child_record_t type and all derived type */
	uint8_t							child_record_buffer[64];
	memlink_t						memlinks[CLASSES_MEMLINKS_MAX_ITEMS];

	/* OBIS layer temporary buffer share among distribution */
	uint8_t							obis_temp_buffer[CLASSES_TEMPORARY_BUFFER_SIZE];

	/* Vars to check if DEK is used in pass 3 of HLS authentication */
	uint16_t						found_dek_used_in_pass3 = FALSE;
	CosemActionIndication_Params	*p_action_indication_params = NULL;
	SecurityOptionList				*p_security_options = NULL;

	memset(&distributor_params, 0, sizeof(distributor_params_t));

	/*
	 * Find in master table first,
	 * if not found master list, the object is undefine
	 */
	/* Access the master table */
	p_master_record = (master_record_t *)(g_classes_master_table + (uint16_t)g_dlms_master_class_indexes[p_descriptor->all.class_id]);
	if (p_master_record == NULL ||
		p_master_record->child_list_size == NULL ||
		p_master_record->child_list_pointer == NULL ||
		(p_master_record->child_list_size != NULL &&
		*p_master_record->child_list_size == 0))
	{
		/* Not found the object */
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/*
	* Check attr id and method id to be in range defined in master table
	*/
	if (req_type == REQ_TYPE_GET || req_type == REQ_TYPE_SET) {
		if (p_descriptor->attr.attribute_id > p_master_record->number_attrs) {
			/* Not found the object attr */
			OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);
			OBIS_DISTRIBUTION_FAILED(result);
			return result;
		}
	}
	else if (req_type == REQ_TYPE_ACTION) {
		if (p_descriptor->method.method_id > p_master_record->number_methods) {
			/* Not found the object method */
			OBIS_ACTION_RESULT(result, VAL_ACTION_RESULT_OBJECT_UNDEFINED, FALSE);
			OBIS_DISTRIBUTION_FAILED(result);
			return result;
		}
	}
	else {
		/* Not found the object */
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/* Check wheter the connected association (0.0.40.0.0.255) is request or not */
	if (R_DLMS_CLASSES_CompareObisCode(p_descriptor->all.instance_id, (uint8_t *)"\x00\x00\x28\x00\x00\xFF") == TRUE)
	{
		/* Get the record of current connected assc id in master list */
		child_index = connected_assc_id;
		/*
		 * TODO: Buffer check for odd and even data alignment on below code
		 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
		 */
		p_child_record = (child_record_t *)(void *)(
			((uint8_t *)p_master_record->child_list_pointer) +
			(child_index * p_master_record->child_item_size)
		);
		child_record_size = p_master_record->child_item_size;
	}
	else
	{
		/*
		* If found master record, next find OBIS object in child table by
		* visibility, obis code, access right.
		*/
		for (child_index = 0; child_index < *p_master_record->child_list_size; child_index++)
		{
			/* Get the child item */
			/*
			 * TODO: Buffer check for odd and even data alignment on below code
			 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
			 */
			p_child_record = (child_record_t *)(void *)(
				((uint8_t *)p_master_record->child_list_pointer) +
				(child_index * p_master_record->child_item_size)
			);
			child_record_size = p_master_record->child_item_size;

			/*
			* Check the object by the current connected association
			*/
			if (

				/* found object? */
				p_child_record != NULL &&

				/* Visible? */
				(p_child_record->p_access_right == NULL ||
				 (p_child_record->p_access_right != NULL &&
				  (
					 (	g_classes_access_right_none.attributes.length >=
							p_child_record->p_access_right[connected_assc_id].attributes.length &&
						memcmp(
							g_classes_access_right_none.attributes.p_list,
							p_child_record->p_access_right[connected_assc_id].attributes.p_list,
							p_child_record->p_access_right[connected_assc_id].attributes.length) != 0 ) ||

					 (
						g_classes_access_right_none.methods.length >=
							p_child_record->p_access_right[connected_assc_id].methods.length &&
						memcmp(
							g_classes_access_right_none.methods.p_list,
							p_child_record->p_access_right[connected_assc_id].methods.p_list,
							p_child_record->p_access_right[connected_assc_id].methods.length) != 0 )
				  )
				 )
				) &&

				/* Match OBIS code? */
				R_DLMS_CLASSES_CompareObisCode(p_child_record->logical_name, p_descriptor->all.instance_id) == TRUE

				)
			{
				break;
			}
		}

		/* If not found, return error */
		if (child_index >= *p_master_record->child_list_size)
		{
			OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);				/* Object not found */
			OBIS_DISTRIBUTION_FAILED(result);
			return result;
		}
	}

		/*
		 * Check the access right for the current connected association
	* Bring the attribute access right and method access right to Library to enforce security of response message
		 * Grant full access when access right pointer is NULL
		 */
		if (p_child_record->p_access_right != NULL &&
		R_DLMS_CLASSES_GetAndCheckAccessRight(
			p_library_descriptor,
				req_type,
				p_descriptor->all.item_id,
				&p_child_record->p_access_right[connected_assc_id]
			) == FALSE)
		{
			OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED, FALSE);		/* Violate scope */
			OBIS_DISTRIBUTION_FAILED(result);
			return result;
		}

	/*
	 * Restrict the access to reply_to_HLS_authentication of Association LN object
	 * when HLS authentication is required in current connected association
	 */
	if (g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID2_HIGH_SECURITY ||
		g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID3_HIGH_SECURITY_MD5 ||
		g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID4_HIGH_SECURITY_SHA1 ||
		g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID5_HIGH_SECURITY_GMAC ||
		g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID6_HIGH_SECURITY_SHA256 ||
		g_classes_assc_connection_session[connected_assc_id].p_assc_config->mechanism_id == MECHANISM_ID7_HIGH_SECURITY_ECDSA)
	{
		/* Not finish authentication and try to access to other than reply_to_HLS_authentication? */
		if (g_classes_assc_connection_session[connected_assc_id].hls_restrict_mode == TRUE)
		{
			if (req_type != REQ_TYPE_ACTION)
			{
				OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED, FALSE);		/* Violate scope */
				OBIS_DISTRIBUTION_FAILED(result);
				return result;
			}
			else if (p_descriptor->method.method_id != 1)	/* reply_to_HLS_authentication(data) method */
			{
				OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED, FALSE);		/* Violate scope */
				OBIS_DISTRIBUTION_FAILED(result);
				return result;
			}
			else
			{
				/* 
				 * CTT 3.0 require that in pass 3 (invoke of reply_to_HLS_authentication(data)), DEK should not be used.
				 * Else, T_APPL_OPEN_3 will be FAILED. Following code rejects access to that method if DEK is used, in pass 3.
				 */
				if (p_library_descriptor != NULL) {
					p_action_indication_params = (CosemActionIndication_Params *)p_library_descriptor;
					if (p_action_indication_params->p_dispatch_context != NULL &&
						p_action_indication_params->p_dispatch_context->p_additional_params != NULL)
					{
						/*
						 * Get list of security options (output) after deciphering process and
						 * search on all elements if DEK is used.
						 */
						p_security_options = &p_action_indication_params->p_dispatch_context->p_additional_params->security_options;

						found_dek_used_in_pass3 = FALSE;
						for (count = 0; count < p_security_options->usage; count++) {
							if (p_security_options->elements[count].protection_type == PROTECTION_DED_CIPHERING ||
								p_security_options->elements[count].protection_type == PROTECTION_GENERAL_DED_CIPHERING)
							{
								found_dek_used_in_pass3 = TRUE;
								break;
							}
						}

						if (found_dek_used_in_pass3 == TRUE) {
							OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);		/* Temporary failure */
							OBIS_DISTRIBUTION_FAILED(result);
							return result;
						}
					}
				}
			}
		}
	}

	if (child_record_size > 64)
	{
		/* Child record is too big to clone */
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	memcpy(child_record_buffer, p_child_record, child_record_size);
	
	/*
	* TODO: Buffer check for odd and even data alignment on below code
	* Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
	*/
	p_child_record = (child_record_t *)(void *)child_record_buffer;

	/*
	* Make input params for distributor func
	*/
	distributor_params.master_index				= p_descriptor->all.class_id;	/* [In] Id of the row in master list */
	distributor_params.child_index				= child_index;					/* [In] Id of the row in child list */
	distributor_params.p_child_record			= p_child_record;				/* [In] Child record of calling object */
	distributor_params.connected_assc_id		= connected_assc_id;			/* [In] Connected assc id of the current request */
	distributor_params.p_assc_session =
		&g_classes_assc_connection_session[connected_assc_id];					/* [In] Connected assc session of the current request */
	distributor_params.req_type					= req_type;						/* [In] Request type (GET/SET/ACTION) */
	if (p_service_type != NULL) {
		distributor_params.service_type			= *p_service_type;				/* [In] Service type */
	}
	if (p_descriptor != NULL) {
		distributor_params.descriptor			= *p_descriptor;				/* [In] Descriptor of attr or method */
	}
	if (p_selective_access != NULL) {
		distributor_params.selective_access		= *p_selective_access;			/* [In] Selective access params for GET/SET service */
	}
	distributor_params.p_library_descriptor		= p_library_descriptor;			/* [In] Library Descriptor (GET/SET/ACTION), refer to r_dlms_application.h for details.
																				 *      NULL is passed into this param in some cases */
	distributor_params.in_data					= in_data;						/* [In] Data from library in case of SET/ACTION */
	/* Guarantee response PDU size smaller or equal to Client Max PDU size */
	if (g_classes_assc_connection_session[connected_assc_id].client_max_pdu_size != 0 &&	/* 0 means no limit PDU size */
		g_classes_assc_connection_session[connected_assc_id].client_max_pdu_size >= 12 &&	/* 1-11 reserved */
		(g_classes_assc_connection_session[connected_assc_id].client_max_pdu_size - 64) < out_data.length)
	{
		out_data.length = g_classes_assc_connection_session[connected_assc_id].client_max_pdu_size - 64;
	}
	g_classes_assc_connection_session[connected_assc_id].negotiated_client_max_pdu_size = out_data.length;
	distributor_params.out_data					= out_data;						/* [Out] Output buffer for encoded data */
	distributor_params.p_out_encoded_len		= p_encoded_length;				/* [Out] Actual output buffer length for encoded data */
	distributor_params.distributor_state		= DIST_UNDER_CLASS_FUNCTION;	/* [In] Distribution state of current params (before or under or after class function) */
	distributor_params.handled					= FALSE;						/* [In, Out] Indicate that the service req (GET/SET/ACTION) is already handled and no need subsequence call */

	/* Service param dyn buffer on heap */
	distributor_params.service_params.malloc.p_content = obis_temp_buffer;
	distributor_params.service_params.malloc.length = 0;
	distributor_params.service_params.malloc.alloc_size = CLASSES_TEMPORARY_BUFFER_SIZE;
	
	/*
	 * memlinks
	 * TODO: Buffer check for odd and even data alignment on below code
	 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
	 */
 	distributor_params.service_params.memlinks.p_content = &memlinks[0];
	distributor_params.service_params.memlinks.length = 0;
	distributor_params.service_params.memlinks.alloc_size = CLASSES_MEMLINKS_MAX_ITEMS;
	
	distributor_params.service_params.sync				= TRUE;					/* [In, Out] Indicates that temporary params on SET or ACTION service will be copied to object defined buffer thru memlinks */
	distributor_params.service_params.created			= FALSE;				/* [Out] Indicates that an object of service params has been created on dynamic buffer */
	distributor_params.service_params.decode_success	= FALSE;				/* [Out] Indicates that var in malloc is decode successful & ready to use on user distributor */
	distributor_params.result							= result;				/* [In, Out] Distribution result, flow from user distributor thru class function */

	/* Distribution by Abstract Distributor */
	R_DLMS_CLASSES_AbstractDistributor(p_master_record->fp_distributor, &distributor_params);

	/* Diag max usage */
	if (g_dlms_diag_memlinks_max_usage < distributor_params.service_params.memlinks.length) {
		g_dlms_diag_memlinks_max_usage = distributor_params.service_params.memlinks.length;
	}
	if (g_dlms_diag_malloc_temporary_buffer_max_usage < distributor_params.service_params.malloc.length) {
		g_dlms_diag_malloc_temporary_buffer_max_usage = distributor_params.service_params.malloc.length;
	}

	return (distributor_params.result);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_EncodeDataAttributeInternally
* Interface     : uint8_t R_DLMS_CLASSES_EncodeDataAttributeInternally(
*               :     uint8_t               connected_assc_id,
*               :     req_type_t            req_type,
*               :     descriptor_t          *p_descriptor,
*               :     selective_access_t    *p_selective_access,
*               :     service_type_t        *p_service_type,
*               :     void                  *p_library_descriptor,
*               :     MandatoryString       in_data,
*               :     MandatoryString       out_data,
*               :     uint16_t              *p_encoded_length
*               : );
* Description   : Internally encode object attribute REGARDLESS OF THE ACCESS RIGHT
*               : This function is cloned from R_DLMS_CLASSES_DecodeObject function
* Function Calls: R_DLMS_CLASSES_CompareObisCode()
*               : (decoded class)->fp_distributor()
* Return Value  : distributor_result_t result
******************************************************************************/
distributor_result_t R_DLMS_CLASSES_EncodeDataAttributeInternally(
	uint8_t				connected_assc_id,
	req_type_t			req_type,
	descriptor_t		*p_descriptor,
	selective_access_t	*p_selective_access,
	service_type_t		*p_service_type,
	void				*p_library_descriptor,
	MandatoryString		in_data,
	MandatoryString		out_data,
	uint16_t			*p_encoded_length,
	malloc_buffer_t		*p_malloc_buffer
)
{
	uint8_t 						child_index;				/* Child index on child row */
	uint16_t						count;						/* Common for for loop */

	/* Distributor function result for GET/SET/ACTION services */
	distributor_result_t			result = OBIS_DISTRIBUTION_DEFAULT_VALUE;

	master_record_t					*p_master_record;			/* Pointer to master record in g_MasterTable */
	child_record_t					*p_child_record = NULL;		/* Pointer to child record in a specified master record */
	uint16_t						child_record_size;			/* Size of child record (to be cloned into RAM) */

	/* Params for GET/SET/ACTION class distributor function */
	distributor_params_t			distributor_params;			/* Distributor params */

	/* Stack buffer for child record clone 64 is maximum size of a child_record_t type and all derived type */
	uint8_t							child_record_buffer[64];
	memlink_t						memlinks[CLASSES_MEMLINKS_MAX_ITEMS];

	memset(&distributor_params, 0, sizeof(distributor_params_t));
	
	/* Load pre-defined configuration of pre-establish AA to association connection session */
	if (connected_assc_id < OBIS_NUMBER_OF_ASSOCIATION &&
		gp_asscs[connected_assc_id] != NULL &&
		gp_asscs[connected_assc_id]->pre_established == TRUE)
	{
		g_classes_assc_connection_session[connected_assc_id].connected_assc_id = connected_assc_id;
		g_classes_assc_connection_session[connected_assc_id].negotiated_conformance.bytes.bytes0 = gp_asscs[connected_assc_id]->conformance_byte0;
		g_classes_assc_connection_session[connected_assc_id].negotiated_conformance.bytes.bytes1 = gp_asscs[connected_assc_id]->conformance_byte1;
		g_classes_assc_connection_session[connected_assc_id].negotiated_conformance.bytes.bytes2 = gp_asscs[connected_assc_id]->conformance_byte2;
		g_classes_assc_connection_session[connected_assc_id].p_assc_config = gp_asscs[connected_assc_id];
		g_classes_assc_connection_session[connected_assc_id].client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;
		g_classes_assc_connection_session[connected_assc_id].negotiated_client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;
		g_classes_assc_connection_session[connected_assc_id].CtoS.p_content = NULL;
		g_classes_assc_connection_session[connected_assc_id].CtoS.length = 0;
		g_classes_assc_connection_session[connected_assc_id].dedicated_key.p_content = NULL;
		g_classes_assc_connection_session[connected_assc_id].dedicated_key.length = 0;
		g_classes_assc_connection_session[connected_assc_id].hls_restrict_mode = FALSE;
	}

	/* Check if Class of object is existed in Master table */
	p_master_record = (master_record_t *)(g_classes_master_table + (uint16_t)g_dlms_master_class_indexes[p_descriptor->all.class_id]);
	if (p_master_record == NULL ||
		p_master_record->child_list_size == NULL ||
		p_master_record->child_list_pointer == NULL ||
		(p_master_record->child_list_size != NULL &&
		*p_master_record->child_list_size == 0))
	{
		/* Not found the class */
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/*
	* Check attr id and method id to be in range defined in master table
	*/
	if (req_type != REQ_TYPE_GET || p_descriptor->attr.attribute_id > p_master_record->number_attrs) {
		/* Not found the object attr */
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/*
	* Find OBIS object in child table by obis code.
	*/
	for (child_index = 0; child_index < *p_master_record->child_list_size; child_index++)
	{
		/* Get the child item */
		/*
		 * TODO: Buffer check for odd and even data alignment on below code
		 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
		 */
		p_child_record = (child_record_t *)(void *)(
			((uint8_t *)p_master_record->child_list_pointer) +
			(child_index * p_master_record->child_item_size)
		);
		child_record_size = p_master_record->child_item_size;

		/*
		* Check the object by the current connected association
		*/
		if (
				/* found object? */
				(p_child_record != NULL) &&
				/* Match OBIS code? */
				(R_DLMS_CLASSES_CompareObisCode(p_child_record->logical_name, p_descriptor->all.instance_id) == TRUE)
			)
		{
			break;
		}
	}

	/* If not found, return error */
	if (child_index >= *p_master_record->child_list_size)
	{
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE);				/* Object not found */
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	if (child_record_size > 64)
	{
		/* Child record is too big to clone */
		OBIS_DATA_ACCESS_RESULT(result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);
		OBIS_DISTRIBUTION_FAILED(result);
		return result;
	}

	/* Clone p_child_record for user distributor to use */
	memcpy(child_record_buffer, p_child_record, child_record_size);

	/*
	* TODO: Buffer check for odd and even data alignment on below code
	* Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
	*/
 	p_child_record = (child_record_t *)(void *)child_record_buffer;

	/*
	* Make input params for distributor func
	*/
	distributor_params.master_index				= p_descriptor->all.class_id;	/* [In] Id of the row in master list */
	distributor_params.child_index				= child_index;					/* [In] Id of the row in child list */
	distributor_params.p_child_record			= p_child_record;				/* [In] Child record of calling object */
	distributor_params.connected_assc_id		= connected_assc_id;			/* [In] Connected assc id of the current request */
	distributor_params.p_assc_session =
		&g_classes_assc_connection_session[connected_assc_id];					/* [In] Connected assc session of the current request */
	distributor_params.req_type					= req_type;						/* [In] Request type (GET/SET/ACTION) */
	if (p_service_type != NULL) {
		distributor_params.service_type			= *p_service_type;				/* [In] Service type */
	}
	if (p_descriptor != NULL) {
		distributor_params.descriptor			= *p_descriptor;				/* [In] Descriptor of attr or method */
	}
	if (p_selective_access != NULL) {
		distributor_params.selective_access		= *p_selective_access;			/* [In] Selective access params for GET/SET service */
	}
	distributor_params.p_library_descriptor		= p_library_descriptor;			/* [In] Library Descriptor (GET/SET/ACTION), refer to r_dlms_application.h for details.
																				 *      NULL is passed into this param in some cases */
	distributor_params.in_data					= in_data;						/* [In] Data from library in case of SET/ACTION */
	distributor_params.out_data					= out_data;						/* [Out] Output buffer for encoded data */
	distributor_params.p_out_encoded_len		= p_encoded_length;				/* [Out] Actual output buffer length for encoded data */
	distributor_params.distributor_state		= DIST_UNDER_CLASS_FUNCTION;	/* [In] Distribution state of current params (before or under or after class function) */
	distributor_params.handled					= FALSE;						/* [In, Out] Indicate that the service req (GET/SET/ACTION) is already handled and no need subsequence call */

	/* Service param dyn buffer on heap */
	if (p_malloc_buffer != NULL) {
		distributor_params.service_params.malloc = *p_malloc_buffer;
	}
	
	/*
	 * memlinks
	 * TODO: Buffer check for odd and even data alignment on below code
	 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
	 */
	distributor_params.service_params.memlinks.p_content = &memlinks[0];
	distributor_params.service_params.memlinks.length = 0;
	distributor_params.service_params.memlinks.alloc_size = CLASSES_MEMLINKS_MAX_ITEMS;
	
	distributor_params.service_params.sync				= TRUE;					/* [In, Out] Indicates that temporary params on SET or ACTION service will be copied to object defined buffer thru memlinks */
	distributor_params.service_params.created			= FALSE;				/* [Out] Indicates that an object of service params has been created on dynamic buffer */
	distributor_params.service_params.decode_success	= FALSE;				/* [Out] Indicates that var in malloc is decode successful & ready to use on user distributor */
	distributor_params.result							= result;				/* [In, Out] Distribution result, flow from user distributor thru class function */

	/* Distribution by Abstract Distributor */
	R_DLMS_CLASSES_AbstractDistributor(p_master_record->fp_distributor, &distributor_params);

	return (distributor_params.result);
}

/* --------------------------------------------------------
* Functions to link with library
* --------------------------------------------------------
*/
/******************************************************************************
* Function Name : r_dlms_classes_cosem_get_indication
* Interface     : None r_dlms_classes_cosem_get_indication(
*               :     MgmtChannel mgmt_channel            ,
*               :     CosemGetIndication_Params * p_params,
*               : );
* Description   :
* Arguments     : MgmtChannel mgmt_channel            :
*               : CosemGetIndication_Params * p_params:
* Function Calls:
* Return Value  : None
******************************************************************************/
void r_dlms_classes_cosem_get_indication(MgmtChannel mgmt_channel, CosemGetIndication_Params *p_params)
{
	/* Params for COSEM-Get-Response */
	CosemGetResponse_Params res_params;
	GetDataResult			get_data_result;

	/* Params for Classes functions */
	MandatoryString			in_data = { NULL, 0 };												/* Input data string */
	MandatoryString			out_data = { NULL, 0 };												/* Output buffer string */
	uint16_t				encoded_len = 0;													/* Actual output buffer length for encoded data */
	distributor_result_t	class_func_result = OBIS_DISTRIBUTION_DEFAULT_VALUE;				/* Class function result */

	/* Association management */
	ChannelType				channel_type = CHANNEL_TYPE_NONE;
	int16_t					assc_id = -1;

	/* Check if current channel is connected or not */
	assc_id = R_DLMS_GetConnectedAsscId(mgmt_channel);
	if (assc_id == -1) {
		return;
	}

	/* Check if temporary buffer is created in DLMS Library */
	if (p_params->p_dispatch_context == NULL ||
		p_params->p_dispatch_context->tbuf.p_content == NULL ||
		p_params->p_dispatch_context->tbuf.length < CLASSES_DISTRIBUTION_BUFFER_SIZE) {
		return;
	}
	else {
		/* Link with temporary buffer shared from DLMS Library */
		out_data.p_content = p_params->p_dispatch_context->tbuf.p_content;
		out_data.length = CLASSES_DISTRIBUTION_BUFFER_SIZE;
	}
	
	/* Get current channel type of the connected channel */
	channel_type = R_MGMT_GetChannelType(mgmt_channel);

	/*
	 * In case of service call in pre-establish AA, an AA connection session is prepared
	 * by default value of association defined in r_dlms_config.c
	 */
	r_dlms_classes_cosem_prepare_pre_establish_aa_session(mgmt_channel, channel_type, assc_id);
	
	memset(&res_params, 0, sizeof(CosemGetResponse_Params));
	memset(&get_data_result, 0, sizeof(GetDataResult));
	res_params.invoke_id = p_params->invoke_id;
	res_params.priority = p_params->priority;
	res_params.p_dispatch_context = p_params->p_dispatch_context;
	res_params.service_class = SERVICE_CLASS_CONFIRMED;

	switch (p_params->request_type)
	{
		case COSEM_GET_REQUEST_NORMAL:
			memcpy(
				&g_classes_assc_connection_session[assc_id].get_service_attr_desc,
				&p_params->cosem_attr_descriptor.p_list[0].cosem_attribute_descriptor,
				sizeof(CosemAttributeDescriptor)
			);

			class_func_result = R_DLMS_CLASSES_DecodeObject(
				assc_id,
				REQ_TYPE_GET,
				(descriptor_t *)(&(p_params->cosem_attr_descriptor.p_list[0].cosem_attribute_descriptor)),
				(selective_access_t *)(&(p_params->cosem_attr_descriptor.p_list[0].access_selection)),
				(service_type_t *)(&(p_params->request_type)),
				p_params,
				in_data,
				out_data,
				&encoded_len
			);

			break;

		case COSEM_GET_REQUEST_NEXT:
			class_func_result = R_DLMS_CLASSES_DecodeObject(
				assc_id,
				REQ_TYPE_GET,
				(descriptor_t *)(&(g_classes_assc_connection_session[assc_id].get_service_attr_desc)),
				NULL,
				(service_type_t *)(&(p_params->request_type)),
				p_params,
				in_data,
				out_data,
				&encoded_len
			);

			break;

		/* TODO : Support Get with list, below code is no response to Client */
		case COSEM_GET_REQUEST_WITH_LIST:
			return;

		default:
			return;
	}

	/* Class function return SUCCESS? */
	if (class_func_result.success == TRUE && 
		class_func_result.result.data_access == VAL_DATA_ACCESS_RESULT_SUCCESS)
	{
		/* Continous partial? */
		if (class_func_result.partial == TRUE) {
			/*
			 * Check with negotiated conformance bits before proceed the block transfer to client, if bit "get with block transfer" not enable
			 * in negotiated conformance bits, return error when client do GET service but encoded APDU in meter is too long.
			 */
			if (g_classes_assc_connection_session[assc_id].negotiated_conformance.bits.block_transfer_with_get == TRUE) {
				res_params.response_type = COSEM_GET_RESPONSE_ONE_BLOCK;
				res_params.result.data_block_g.block_number = g_classes_assc_connection_session[assc_id].get_service_block_number + 1;
				res_params.result.data_block_g.last_block = FALSE;
				res_params.result.data_block_g.result_tag = TAG_DATABLOCK_G_RESULT_RAW_DATA;
				res_params.result.data_block_g.result.raw_data.p_content = out_data.p_content;
				res_params.result.data_block_g.result.raw_data.length = encoded_len;
				g_classes_assc_connection_session[assc_id].get_service_block_number++;
			}
			else {
				/* Raise error "data block unavailable" to client */
				res_params.response_type = COSEM_GET_RESPONSE_NORMAL;
				get_data_result.result_tag = TAG_GET_ACCESS_RESULT_DATA_ACCESS_RESULT;
				get_data_result.result.data_access_result = VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE;
				res_params.result.get_data_result.p_list = &get_data_result;
				res_params.result.get_data_result.length = 1;
			}
		}
		/* Stop partial? */
		else if (g_classes_assc_connection_session[assc_id].get_service_is_block_response == TRUE) {
			res_params.response_type = COSEM_GET_RESPONSE_LAST_BLOCK;
			res_params.result.data_block_g.block_number = g_classes_assc_connection_session[assc_id].get_service_block_number + 1;
			res_params.result.data_block_g.last_block = TRUE;
			res_params.result.data_block_g.result_tag = TAG_DATABLOCK_G_RESULT_RAW_DATA;
			res_params.result.data_block_g.result.raw_data.p_content = out_data.p_content;
			res_params.result.data_block_g.result.raw_data.length = encoded_len;
			g_classes_assc_connection_session[assc_id].get_service_block_number++;
		}
		else {
			res_params.response_type = COSEM_GET_RESPONSE_NORMAL;
			get_data_result.result_tag = TAG_GET_ACCESS_RESULT_DATA;
			get_data_result.result.data.p_content = out_data.p_content;
			get_data_result.result.data.length = encoded_len;
			res_params.result.get_data_result.p_list = &get_data_result;
			res_params.result.get_data_result.length = 1;
		}
	}
	else {
		res_params.response_type = COSEM_GET_RESPONSE_NORMAL;
		get_data_result.result_tag = TAG_GET_ACCESS_RESULT_DATA_ACCESS_RESULT;
		get_data_result.result.data_access_result = class_func_result.result.data_access;
		res_params.result.get_data_result.p_list = &get_data_result;
		res_params.result.get_data_result.length = 1;
	}

	/* Block response status */
	if (g_classes_assc_connection_session[assc_id].negotiated_conformance.bits.block_transfer_with_get == TRUE) {
		g_classes_assc_connection_session[assc_id].get_service_is_block_response = class_func_result.partial;
	}
	else {
		g_classes_assc_connection_session[assc_id].get_service_is_block_response = FALSE;
	}

	/* Only reply to confirmed service on HDLC profile or TCP/UDP with confirm bit is set */
	if (channel_type == CHANNEL_TYPE_HDLC ||
		((channel_type == CHANNEL_TYPE_UDP || channel_type == CHANNEL_TYPE_TCP) &&
		 p_params->service_class == SERVICE_CLASS_CONFIRMED)) {
		R_COSEM_GET_Response(mgmt_channel, &res_params);
	}
}

/******************************************************************************
* Function Name : r_dlms_classes_cosem_set_indication
* Interface     : None r_dlms_classes_cosem_set_indication(
*               :     MgmtChannel mgmt_channel            ,
*               :     CosemSetIndication_Params * p_params,
*               : );
* Description   :
* Arguments     : MgmtChannel mgmt_channel                 :
*               : CosemSetIndication_Params * p_params:
* Function Calls:
* Return Value  : None
******************************************************************************/
void r_dlms_classes_cosem_set_indication(MgmtChannel mgmt_channel, CosemSetIndication_Params *p_params)
{
	/* Params for COSEM-Set-Response */
	CosemSetResponse_Params res_params;
	DataAccessResult_Value	data_access_result_list[COSEM_SET_LIST_MAX_SIZE];

	/* Params for Classes functions */
	MandatoryString			out_data = { NULL, 0 };										/* Output buffer string */
	uint16_t				encoded_len = 0;											/* Actual output buffer length for encoded data */
	distributor_result_t	class_func_result = OBIS_DISTRIBUTION_DEFAULT_VALUE;		/* Class function result */
	
	/* Association management */
	ChannelType				channel_type = CHANNEL_TYPE_NONE;
	int16_t					assc_id = -1;
	uint16_t				count;

	/* Check if current channel is connected or not */
	assc_id = R_DLMS_GetConnectedAsscId(mgmt_channel);
	if (assc_id == -1) {
		return;
	}

	/* Get current channel type of the connected channel */
	channel_type = R_MGMT_GetChannelType(mgmt_channel);

	/*
	 * In case of service call in pre-establish AA, an AA connection session is prepared
	 * by default value of association defined in r_dlms_config.c
	 */
	r_dlms_classes_cosem_prepare_pre_establish_aa_session(mgmt_channel, channel_type, assc_id);
	
	memset(&res_params, 0, sizeof(CosemSetResponse_Params));
	res_params.invoke_id = p_params->invoke_id;
	res_params.priority = p_params->priority;
	res_params.p_dispatch_context = p_params->p_dispatch_context;
	res_params.service_class = SERVICE_CLASS_CONFIRMED;

	/* Response normal is default */
	res_params.response_type = COSEM_SET_RESPONSE_NORMAL;
	data_access_result_list[0] = VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED;
	res_params.result.p_list = data_access_result_list;
	res_params.result.length = 1;

	switch (p_params->request_type)
	{
		case COSEM_SET_REQUEST_NORMAL:
			class_func_result = R_DLMS_CLASSES_DecodeObject(
				assc_id,
				REQ_TYPE_SET,
				(descriptor_t *)(&(p_params->cosem_attr_descriptor.p_list[0].cosem_attribute_descriptor)),
				(selective_access_t *)(&(p_params->cosem_attr_descriptor.p_list[0].access_selection)),
				(service_type_t *)(&(p_params->request_type)),
				p_params,
				p_params->data.p_list[0],
				out_data,
				&encoded_len
			);
			data_access_result_list[0] = class_func_result.result.data_access;
			break;

		/* TODO, below code is no response to Client */
		case COSEM_SET_REQUEST_FIRST_BLOCK:
			return;

		/* TODO, below code is no response to Client */
		case COSEM_SET_REQUEST_ONE_BLOCK:
			return;

		/* TODO, below code is no response to Client */
		case COSEM_SET_REQUEST_LAST_BLOCK:
			return;

		case COSEM_SET_REQUEST_WITH_LIST:

			for (count = 0; count < p_params->cosem_attr_descriptor.length; count++) {
				data_access_result_list[count] = VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED;
				class_func_result = R_DLMS_CLASSES_DecodeObject(
					assc_id,
					REQ_TYPE_SET,
					(descriptor_t *)(&(p_params->cosem_attr_descriptor.p_list[count].cosem_attribute_descriptor)),
					(selective_access_t *)(&(p_params->cosem_attr_descriptor.p_list[count].access_selection)),
					(service_type_t *)(&(p_params->request_type)),
					p_params,
					p_params->data.p_list[count],
					out_data,
					&encoded_len
				);
				data_access_result_list[count] = class_func_result.result.data_access;
			}

			res_params.response_type = COSEM_SET_RESPONSE_WITH_LIST;
			res_params.result.length = p_params->cosem_attr_descriptor.length;

			break;

		/* TODO, below code is no response to Client */
		case COSEM_SET_REQUEST_FIRST_BLOCK_WITH_LIST:
			return;

		default:
			return;
	}

	/* Only reply to confirmed service on HDLC profile or TCP/UDP with confirm bit is set */
	if (channel_type == CHANNEL_TYPE_HDLC ||
		((channel_type == CHANNEL_TYPE_UDP || channel_type == CHANNEL_TYPE_TCP) &&
		p_params->service_class == SERVICE_CLASS_CONFIRMED)) {
		R_COSEM_SET_Response(mgmt_channel, &res_params);
	}

	/* Set indication to object layer */
	R_DLMS_OBJECTS_CosemSetIndication(mgmt_channel, p_params);
}

/******************************************************************************
* Function Name : r_dlms_classes_cosem_action_indication
* Interface     : None r_dlms_classes_cosem_action_indication(
*               :     MgmtChannel mgmt_channel               ,
*               :     CosemActionIndication_Params * p_params,
*               : );
* Description   :
* Arguments     : MgmtChannel mgmt_channel               :
*               : CosemActionIndication_Params * p_params:
* Function Calls:
* Return Value  : None
******************************************************************************/
void r_dlms_classes_cosem_action_indication(MgmtChannel mgmt_channel, CosemActionIndication_Params *p_params)
{
	/* Params for COSEM-Action-Response */
	CosemActionResponse_Params		res_params;
	ActionResponseWithOptionalData	action_response_list[COSEM_ACTION_LIST_MAX_SIZE];
	
	/* Params for Classes functions */
	MandatoryString			out_data = { NULL, 0 };												/* Output buffer string */
	uint16_t				encoded_len = 0;													/* Actual output buffer length for encoded data */
	distributor_result_t	class_func_result = OBIS_DISTRIBUTION_DEFAULT_VALUE;				/* Class function result */

	/* Association management */
	ChannelType				channel_type = CHANNEL_TYPE_NONE;
	int16_t					assc_id = -1;
	uint16_t				count;

	/* Check if current channel is connected or not */
	assc_id = R_DLMS_GetConnectedAsscId(mgmt_channel);
	if (assc_id == -1) {
		return;
	}

	/* Check if temporary buffer is created in DLMS Library */
	if (p_params->p_dispatch_context == NULL ||
		p_params->p_dispatch_context->tbuf.p_content == NULL ||
		p_params->p_dispatch_context->tbuf.length < CLASSES_DISTRIBUTION_BUFFER_SIZE) {
		return;
	}
	else {
		/* Link with temporary buffer shared from DLMS Library */
		out_data.p_content = p_params->p_dispatch_context->tbuf.p_content;
		out_data.length = CLASSES_DISTRIBUTION_BUFFER_SIZE;
	}

	/* Get current channel type of the connected channel */
	channel_type = R_MGMT_GetChannelType(mgmt_channel);

	/*
	 * In case of service call in pre-establish AA, an AA connection session is prepared
	 * by default value of association defined in r_dlms_config.c
	 */
	r_dlms_classes_cosem_prepare_pre_establish_aa_session(mgmt_channel, channel_type, assc_id);
	
	memset(&res_params, 0, sizeof(CosemActionResponse_Params));
	memset(&action_response_list, 0, sizeof(ActionResponseWithOptionalData)* COSEM_ACTION_LIST_MAX_SIZE);
	res_params.invoke_id = p_params->invoke_id;
	res_params.priority = p_params->priority;
	res_params.p_dispatch_context = p_params->p_dispatch_context;
	res_params.service_class = SERVICE_CLASS_CONFIRMED;

	/* Response normal is default */
	res_params.response_type = COSEM_ACTION_RESPONSE_NORMAL;
	action_response_list[0].result = VAL_ACTION_RESULT_OBJECT_UNDEFINED;
	action_response_list[0].return_parameters.use = FALSE;
	res_params.action_response.p_list = action_response_list;
	res_params.action_response.length = 1;

	switch (p_params->request_type)
	{
		case COSEM_ACTION_REQUEST_NORMAL:
			class_func_result = R_DLMS_CLASSES_DecodeObject(
				assc_id,
				REQ_TYPE_ACTION,
				(descriptor_t *)(&(p_params->cosem_method_descriptor.p_list[0])),
				NULL,
				(service_type_t *)(&(p_params->request_type)),
				p_params,
				p_params->method_invocation_parameters.p_list[0],
				out_data,
				&encoded_len
			);
			action_response_list[0].result = class_func_result.result.action;
			if (class_func_result.result.action == VAL_ACTION_RESULT_SUCCESS && encoded_len > 0) {
				action_response_list[0].return_parameters.use = TRUE;
				action_response_list[0].return_parameters.get_data_result.result_tag = TAG_GET_ACCESS_RESULT_DATA;
 				action_response_list[0].return_parameters.get_data_result.result.data.p_content = out_data.p_content;
				action_response_list[0].return_parameters.get_data_result.result.data.length = encoded_len;
			}
			break;

		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_NEXT:
			return;
		
		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_FIRST_BLOCK:
			return;
		
		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_ONE_BLOCK:
			return;
		
		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_LAST_BLOCK:
			return;

		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_WITH_LIST:
			return;

		/* TODO, below code is no response to Client */
		case COSEM_ACTION_REQUEST_WITH_LIST_AND_FIRST_BLOCK:
			return;

		default:
			return;
	}

	/* Only reply to confirmed service on HDLC profile or TCP/UDP with confirm bit is set */
	if (channel_type == CHANNEL_TYPE_HDLC ||
		((channel_type == CHANNEL_TYPE_UDP || channel_type == CHANNEL_TYPE_TCP) &&
		p_params->service_class == SERVICE_CLASS_CONFIRMED)) {
		R_COSEM_ACTION_Response(mgmt_channel, &res_params);
	}

	/* Action indication to object layer (for the new key activation if any) */
	R_DLMS_OBJECTS_CosemActionIndication(mgmt_channel, p_params);
}

#endif//defined(DLMS_LIB_VERSION) && (DLMS_LIB_VERSION == LIB_V2_2)


/******************************************************************************
* Function Name : r_dlms_classes_lp_assc_opening
* Interface     : None r_dlms_classes_lp_assc_opening(
*               :     AsscChannel assc                      ,
*               :     uint8_t * accepted                    ,
*               :     const AssociationCfg * p_assc_cfg     ,
*               :     CosemOpenIndication_Params * p_params ,
*               :     CosemOpenResponse_Params *p_res_params,
*               : );
* Description   : 
* Arguments     : AsscChannel assc                          :
*               : uint8_t * accepted                        :
*               : const AssociationCfg * p_assc_cfg         :
*               : CosemOpenIndication_Params * p_req_params :
*               : CosemOpenResponse_Params *p_res_params    :
* Function Calls: 
* Return Value  : None
******************************************************************************/
void r_dlms_classes_lp_assc_opening(
	AsscChannel assc,
	uint8_t *accepted,
	const AssociationCfg *p_assc_cfg,
	CosemOpenIndication_Params *p_req_params,
	CosemOpenResponse_Params *p_res_params
)
{
	R_DLMS_CLASSES_Class15AsscOpening(assc, accepted, p_assc_cfg, p_req_params, p_res_params);

	/* Assert Client PDU size must >= value in CLASSES_CLIENT_MIN_PDU_SIZE macro, else reject AARQ */
	if (*accepted == TRUE)
	{
		if (p_req_params->proposed_xdlms_context.client_max_receive_pdu_size != 0 &&	/* 0 means no limit PDU size */
			p_req_params->proposed_xdlms_context.client_max_receive_pdu_size >= 12 &&	/* 1-11, reserved */
			p_req_params->proposed_xdlms_context.client_max_receive_pdu_size < CLASSES_CLIENT_MIN_PDU_SIZE)
		{
			/* Reject AARQ with ConfirmServiceError PDU which carrying "proposed PDU size too short" error code */
			*accepted = FALSE;
			p_res_params->failure_type.associate_source_diag_choice_tag = TAG_ACSE_SERVICE_USER;
			p_res_params->failure_type.diag_detail_code = VAL_ASCE_SERVICE_USER_NOREASON;
			p_res_params->xdlms_initiate_error.confirm_service_error_choice_tag = TAG_CONFIRM_SERVICE_ERR_INITIATEERROR;
			p_res_params->xdlms_initiate_error.service_error_choice_tag = TAG_SERVICE_ERR_INITIATE;
			p_res_params->xdlms_initiate_error.error_detail_code = VAL_INITIATE_PDU_SIZE_TOO_SHORT;
		}
	}
}

/******************************************************************************
* Function Name : r_dlms_classes_lp_assc_open
* Interface     : None r_dlms_classes_lp_assc_open(
*               :     AsscChannel assc                      ,
*               :     uint16_t client_sap                   ,
*               :     uint16_t server_sap                   ,
*               :     const AssociationCfg * p_assc_cfg     ,
*               :     MgmtChannel mgmt_channel              ,
*               :     ConformanceBits negotiated_conformance,
*               :     uint16_t client_max_pdu_size          ,
*               :     MandatoryString CtoS                  ,
*               :     MandatoryString dedicated_key         ,
*               : );
* Description   : 
* Arguments     : AsscChannel assc                      :
*               : uint16_t client_sap                   :
*               : uint16_t server_sap                   :
*               : const AssociationCfg * p_assc_cfg     :
*               : MgmtChannel mgmt_channel              :
*               : ConformanceBits negotiated_conformance:
*               : uint16_t client_max_pdu_size          :
*               : MandatoryString CtoS                  :
*               : MandatoryString dedicated_key         :
* Function Calls: 
* Return Value  : None
******************************************************************************/
void r_dlms_classes_lp_assc_open(
	AsscChannel assc,
	uint16_t client_sap,
	uint16_t server_sap,
	const AssociationCfg *p_assc_cfg,
	MgmtChannel mgmt_channel,
	ConformanceBits negotiated_conformance,
	uint16_t client_max_pdu_size,
	MandatoryString CtoS,
	MandatoryString dedicated_key
)
{
	g_classes_assc_connection_session[assc].connected_assc_id = assc;
	g_classes_assc_connection_session[assc].mgmt_channel_id = mgmt_channel;
	g_classes_assc_connection_session[assc].client_sap = client_sap;
	g_classes_assc_connection_session[assc].server_sap = server_sap;
	g_classes_assc_connection_session[assc].p_assc_config = p_assc_cfg;
	g_classes_assc_connection_session[assc].negotiated_conformance = negotiated_conformance;
	g_classes_assc_connection_session[assc].client_max_pdu_size = client_max_pdu_size;
	g_classes_assc_connection_session[assc].negotiated_client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;
	g_classes_assc_connection_session[assc].CtoS = CtoS;
	g_classes_assc_connection_session[assc].dedicated_key = dedicated_key;
	if (p_assc_cfg->mechanism_id == MECHANISM_ID2_HIGH_SECURITY ||
		p_assc_cfg->mechanism_id == MECHANISM_ID3_HIGH_SECURITY_MD5 ||
		p_assc_cfg->mechanism_id == MECHANISM_ID4_HIGH_SECURITY_SHA1 ||
		p_assc_cfg->mechanism_id == MECHANISM_ID5_HIGH_SECURITY_GMAC ||
		p_assc_cfg->mechanism_id == MECHANISM_ID6_HIGH_SECURITY_SHA256 ||
		p_assc_cfg->mechanism_id == MECHANISM_ID7_HIGH_SECURITY_ECDSA) {
		g_classes_assc_connection_session[assc].hls_restrict_mode = TRUE;
	}
	else {
		g_classes_assc_connection_session[assc].hls_restrict_mode = FALSE;
	}
	g_classes_assc_connection_session[assc].get_service_is_block_response = FALSE;
	g_classes_assc_connection_session[assc].get_service_block_number = 0;
	memset(&g_classes_assc_connection_session[assc].get_service_attr_desc, 0, sizeof(descriptor_t));
	memset(&g_classes_array_encoder_session[assc], 0, sizeof(EncoderSession));
	
	R_DLMS_CLASSES_Class01AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class03AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class04AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class07AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class08AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class09AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class15AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class18AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class20AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class22AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class23AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class40AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class41AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class45AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class48AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class64AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class70AsscOpened(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class71AsscOpened(&g_classes_assc_connection_session[assc]);

	R_DLMS_OBJECTS_AsscOpened(&g_classes_assc_connection_session[assc]);
}

/******************************************************************************
* Function Name : r_dlms_classes_lp_assc_close
* Interface     : None r_dlms_classes_lp_assc_close(
*               :     AsscChannel assc                 ,
*               :     const AssociationCfg * p_assc_cfg,
*               :     MgmtChannel mgmt_channel         ,
*               : );
* Description   :
* Arguments     : AsscChannel assc                 :
*               : const AssociationCfg * p_assc_cfg:
*               : MgmtChannel mgmt_channel         :
* Function Calls:
* Return Value  : None
******************************************************************************/
void r_dlms_classes_lp_assc_close(
	AsscChannel assc,
	const AssociationCfg *p_assc_cfg,
	MgmtChannel mgmt_channel
)
{
	R_DLMS_OBJECTS_AsscClosing(&g_classes_assc_connection_session[assc]);

	R_DLMS_CLASSES_Class01AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class03AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class04AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class07AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class08AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class09AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class15AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class18AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class20AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class22AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class23AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class40AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class41AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class45AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class48AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class64AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class70AsscClosing(&g_classes_assc_connection_session[assc]);
	R_DLMS_CLASSES_Class71AsscClosing(&g_classes_assc_connection_session[assc]);

	memset(&g_classes_assc_connection_session[assc], 0, sizeof(AsscConnectionSession));
	g_classes_assc_connection_session[assc].client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;
	g_classes_assc_connection_session[assc].negotiated_client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;
	
	memset(&g_classes_array_encoder_session[assc], 0, sizeof(EncoderSession));
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Init
* Interface     : void R_DLMS_CLASSES_Init()
* Description   : Initialize for Classes
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Init(void)
{
	uint16_t assc;
	
	g_classes_array_encoder_fatal_error = FALSE;
	g_classes_complex_distributor_current_assc_id = 0;
	
	for (assc = 0; assc < DLMS_MAX_ASSOCIATION_SUPPORT; assc++) {
		memset(&g_classes_assc_connection_session[assc], 0, sizeof(AsscConnectionSession));
		g_classes_assc_connection_session[assc].client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;
		g_classes_assc_connection_session[assc].negotiated_client_max_pdu_size = CLASSES_DEFAULT_MAX_SEND_PDU_SIZE;	
	}
	memset(g_classes_array_encoder_session, 0, sizeof(EncoderSession) * DLMS_MAX_ASSOCIATION_SUPPORT);

	/* Register GET, SET and ACTION callback (library processed) */
	R_DLMS_RegisterAsscGetIndication(r_dlms_classes_cosem_get_indication);
	R_DLMS_RegisterAsscSetIndication(r_dlms_classes_cosem_set_indication);
	R_DLMS_RegisterAsscActionIndication(r_dlms_classes_cosem_action_indication);

	/* Register COSEM OPEN, RELEASE callback (library processed) */
	R_DLMS_RegisterAsscOpeningIndication(r_dlms_classes_lp_assc_opening);
	R_DLMS_RegisterAsscOpenIndication(r_dlms_classes_lp_assc_open);
	R_DLMS_RegisterAsscCloseIndication(r_dlms_classes_lp_assc_close);

	/* Init for all sub classes */
	R_DLMS_CLASSES_Class01Init();
	R_DLMS_CLASSES_Class03Init();
	R_DLMS_CLASSES_Class04Init();
	R_DLMS_CLASSES_Class07Init();
	R_DLMS_CLASSES_Class08Init();
	R_DLMS_CLASSES_Class09Init();
	R_DLMS_CLASSES_Class15Init();
	R_DLMS_CLASSES_Class18Init();
	R_DLMS_CLASSES_Class20Init();
	R_DLMS_CLASSES_Class22Init();
	R_DLMS_CLASSES_Class23Init();
	R_DLMS_CLASSES_Class40Init();
	R_DLMS_CLASSES_Class41Init();
	R_DLMS_CLASSES_Class45Init();
	R_DLMS_CLASSES_Class48Init();
	R_DLMS_CLASSES_Class64Init();
	R_DLMS_CLASSES_Class70Init();
	R_DLMS_CLASSES_Class71Init();

}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_PollingProcessing
* Interface     : void R_DLMS_CLASSES_PollingProcessing()
* Description   : Polling processing for Classes
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_PollingProcessing(void)
{
	R_DLMS_CLASSES_Class01PollingProcessing();
	R_DLMS_CLASSES_Class03PollingProcessing();
	R_DLMS_CLASSES_Class04PollingProcessing();
	R_DLMS_CLASSES_Class07PollingProcessing();
	R_DLMS_CLASSES_Class08PollingProcessing();
	R_DLMS_CLASSES_Class09PollingProcessing();
	R_DLMS_CLASSES_Class15PollingProcessing();
	R_DLMS_CLASSES_Class18PollingProcessing();
	R_DLMS_CLASSES_Class20PollingProcessing();
	R_DLMS_CLASSES_Class22PollingProcessing();
	R_DLMS_CLASSES_Class23PollingProcessing();
	R_DLMS_CLASSES_Class40PollingProcessing();
	R_DLMS_CLASSES_Class41PollingProcessing();
	R_DLMS_CLASSES_Class45PollingProcessing();
	R_DLMS_CLASSES_Class48PollingProcessing();
	R_DLMS_CLASSES_Class64PollingProcessing();
	R_DLMS_CLASSES_Class70PollingProcessing();
	R_DLMS_CLASSES_Class71PollingProcessing();

}