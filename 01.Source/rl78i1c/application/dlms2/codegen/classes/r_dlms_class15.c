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
* File Name    : r_dlms_class15.c
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
#include "r_dlms_class15.h"
#include "r_dlms_objects.h"
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_MD5) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_MD5 == TRUE)
#include "r_md5.h"
#endif
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_SHA1) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_SHA1 == TRUE)
#include "r_sha.h"
#endif
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_AES) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_AES == TRUE)
#include "r_aes_hwip.h"
#endif
#include <string.h>

/******************************************************************************
Macro definitions
******************************************************************************/
/* Challenge size set according to maximum support challenge in dlms library */
#define MAX_CHALLENGE_SIZE                          (64)
/* Max password size is set according to security suite 2 (Green book 8.1 p.183) */
#define MAX_SECRET_KEY_SIZE                         (32)
#define MAX_SYSTEM_TITLE_SIZE						(8)
/* Max authentication buffer: HLS_Secret || SystemTitle-C || SystemTitle-S || StoC || CtoS */
#define MAX_AUTHENTICATION_BUFFER_SIZE              (MAX_SECRET_KEY_SIZE + MAX_SYSTEM_TITLE_SIZE*2 + MAX_CHALLENGE_SIZE*2)


/* Pre checking the authentication buffer size */
#if ((MAX_AUTHENTICATION_BUFFER_SIZE % 16) != 0)
    #error "Something wrong with authentication buffer size, it should be multiple of 16"
#endif

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct tagClass15ObjListSession
{
	uint8_t  is_async_end;			/* Default, Get Service is end */
	int8_t   stage;					/* Encoding stage inside object_list_element structure */
	int8_t   count;					/* Count for duplication of current association object */
	int8_t   attr_id;				/* Current OBIS attribute id */
	int8_t   method_id;				/* Current OBIS method id */
	uint16_t master_id;				/* Current OBIS Master list object */
	uint16_t child_id;				/* Current OBIS Child list object */
} Class15ObjListSession;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/* Import from r_dlms_classes.c */
uint8_t R_DLMS_CLASSES_CheckObjectVisibility(AsscChannel assc_id, uint16_t class_id, uint16_t child_index);
uint8_t R_DLMS_CLASSES_GetAccessRightValue(req_type_t req_type, uint8_t req_id, access_right_t *p_access_right);

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
Class15ObjListSession g_classes_class15_obj_list_session[DLMS_MAX_ASSOCIATION_SUPPORT];

static void R_DLMS_CLASSES_Class15ObjList_AsyncRestart(AsscChannel connected_assc_id);

static uint8_t R_DLMS_CLASSES_Class15ObjList_AsyncStart(
	AsscChannel connected_assc_id,
	AsscChannel req_assc_id
);
static uint8_t R_DLMS_CLASSES_Class15ObjList_AsyncScanNext(
	AsscChannel connected_assc_id,
	AsscChannel req_assc_id
);
static uint8_t R_DLMS_CLASSES_Class15ObjList_AsyncNextPart(AsscChannel connected_assc_id, AsscChannel req_assc_id);
static uint16_t R_DLMS_CLASSES_Class15ObjList_AsyncEncodeObject(
	uint8_t  bfirst,
	AsscChannel req_assc_id,
	uint16_t class_id,
	uint16_t child_index,
	int8_t   *p_attr_id,
	int8_t   *p_method_id,
	int8_t   *p_count,
	int8_t   *p_stage,
	MandatoryString out_data
);

static uint16_t R_DLMS_CLASSES_Class15Aes_DataPadding(
    uint8_t * in_data,
    uint8_t * out_block_data,
    uint16_t in_length
);

static uint16_t R_DLMS_CLASSES_Class15Aes_Ecbenc(
    uint8_t *ptext,
    uint8_t *ctext,
    uint8_t *key,
    uint16_t in_length
);

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class15ObjList_AsyncRestart
* Interface     : static void R_DLMS_CLASSES_Class15ObjList_AsyncRestart(
*               :     AsscChannel connected_assc_id,
*               : );
* Description   : 
* Arguments     : AsscChannel connected_assc_id:
* Function Calls: 
* Return Value  : static void
******************************************************************************/
static void R_DLMS_CLASSES_Class15ObjList_AsyncRestart(AsscChannel connected_assc_id)
{
	if (connected_assc_id >= DLMS_MAX_ASSOCIATION_SUPPORT) {
		return;
	}

	g_classes_class15_obj_list_session[connected_assc_id].is_async_end = TRUE;
	g_classes_class15_obj_list_session[connected_assc_id].master_id = 0;
	g_classes_class15_obj_list_session[connected_assc_id].child_id = 0;
	g_classes_class15_obj_list_session[connected_assc_id].stage = -1;
};

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class15ObjList_AsyncStart
* Interface     : static uint8_t R_DLMS_CLASSES_Class15ObjList_AsyncStart(
*               :     AsscChannel connected_assc_id,
*               :     AsscChannel req_assc_id      ,
*               : );
* Description   : 
* Arguments     : AsscChannel connected_assc_id:
*               : AsscChannel req_assc_id      :
* Function Calls: 
* Return Value  : static uint8_t
******************************************************************************/
static uint8_t R_DLMS_CLASSES_Class15ObjList_AsyncStart(
	AsscChannel connected_assc_id,
	AsscChannel req_assc_id
)
{
	uint8_t b_async_end = FALSE;

	if (connected_assc_id >= DLMS_MAX_ASSOCIATION_SUPPORT ||
		req_assc_id >= DLMS_MAX_ASSOCIATION_SUPPORT) {
		return FALSE;
	}

	/* Initial master and child index */
	g_classes_class15_obj_list_session[connected_assc_id].master_id = 0;
	g_classes_class15_obj_list_session[connected_assc_id].child_id = 0;
	g_classes_class15_obj_list_session[connected_assc_id].stage = -1;

	/* Validate, if fail, scan next */
	b_async_end = R_DLMS_CLASSES_Class15ObjList_AsyncScanNext(
		connected_assc_id,
		req_assc_id
	);

	/* Check whether found the first item or not */
	if (b_async_end == TRUE) {
		return FALSE;	/* Error, not have any object */
	}

	/* OK */
	return TRUE;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class15ObjList_AsyncScanNext
* Interface     : uint8_t R_DLMS_CLASSES_Class15ObjList_AsyncScanNext(
*               :     AsscChannel connected_assc_id,
*               :     AsscChannel req_assc_id      ,
*               : );
* Description   : 
* Arguments     : AsscChannel connected_assc_id:
*               : AsscChannel req_assc_id      :
* Function Calls: Validate, if fail then scan next part of object for in async mode
* Return Value  : uint8_t, TRUE if end of async service
******************************************************************************/
static uint8_t R_DLMS_CLASSES_Class15ObjList_AsyncScanNext(
	AsscChannel connected_assc_id,
	AsscChannel req_assc_id
)
{
	uint8_t bfound = FALSE;
	master_record_t *p_master_record;
	uint16_t master_index;

	if (connected_assc_id >= DLMS_MAX_ASSOCIATION_SUPPORT ||
		req_assc_id >= DLMS_MAX_ASSOCIATION_SUPPORT) {
		return TRUE;
	}
	
	/* Search in all child tables and master table */
	for (;
		g_classes_class15_obj_list_session[connected_assc_id].master_id <= g_biggest_class_id_number;
		g_classes_class15_obj_list_session[connected_assc_id].master_id++, g_classes_class15_obj_list_session[connected_assc_id].child_id = 0
	)
	{
		/* Translate master index */
		master_index = (uint16_t)g_dlms_master_class_indexes[g_classes_class15_obj_list_session[connected_assc_id].master_id];
		/* Checking threshold of master index */
		if (master_index > g_classes_total_master_table_elements)
		{
			continue;
		}
		p_master_record = (master_record_t *)(&g_classes_master_table[master_index]);

		/*
		* Search the row that have object
		* Skip NULL or empty row
		*/
		if (p_master_record->child_list_size == NULL ||
			p_master_record->child_list_pointer == NULL ||
			(p_master_record->child_list_size != NULL &&
			*p_master_record->child_list_size == 0))
		{
			continue;
		}

		/*
		* Check the object in the row until it end
		*/
		for (;
			g_classes_class15_obj_list_session[connected_assc_id].child_id < *p_master_record->child_list_size;
			g_classes_class15_obj_list_session[connected_assc_id].child_id++)
		{
			/* Check whether the current association can access or not */
			if (R_DLMS_CLASSES_CheckObjectVisibility(
					req_assc_id,
					g_classes_class15_obj_list_session[connected_assc_id].master_id,
					g_classes_class15_obj_list_session[connected_assc_id].child_id
				) == OBIS_AR_OBJ_IS_VISIBLE)
			{
				bfound = TRUE;
				break;
			}
		}

		/* break immediately if found object */
		if (bfound == TRUE) {
			break;
		}
	}

	if (bfound == TRUE)
	{
		/* Mark to start at first attribute of object */
		g_classes_class15_obj_list_session[connected_assc_id].stage = 0;
		g_classes_class15_obj_list_session[connected_assc_id].count = 0;
		g_classes_class15_obj_list_session[connected_assc_id].attr_id = 1;
		g_classes_class15_obj_list_session[connected_assc_id].method_id = 1;
	}

	if (g_classes_class15_obj_list_session[connected_assc_id].master_id > g_biggest_class_id_number) {
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class15ObjList_AsyncNextPart
* Interface     : uint8_t R_DLMS_CLASSES_Class15ObjList_AsyncNextPart(
*               :     AsscChannel connected_assc_id,
*               :     AsscChannel req_assc_id      ,
*               : );
* Description   : Get a next object in async mode
* Arguments     : AsscChannel connected_assc_id:
*               : AsscChannel req_assc_id      :
* Return Value  : uint8_t, TRUE if end of async service
******************************************************************************/
static uint8_t R_DLMS_CLASSES_Class15ObjList_AsyncNextPart(AsscChannel connected_assc_id, AsscChannel req_assc_id)
{
    if (connected_assc_id >= DLMS_MAX_ASSOCIATION_SUPPORT ||
		req_assc_id >= DLMS_MAX_ASSOCIATION_SUPPORT) {
		return TRUE;
	}
    
	/* Resume in middle of current object */
	if (g_classes_class15_obj_list_session[connected_assc_id].stage != -1)
	{
		return FALSE;
	}

	/*
	* Next object in the row, then validate, if fail, scan next
	* TRUE is returned, if all row is scanned through
	*/
	g_classes_class15_obj_list_session[connected_assc_id].child_id++;
	return (R_DLMS_CLASSES_Class15ObjList_AsyncScanNext(connected_assc_id, req_assc_id));
}

/******************************************************************************
* Function Name   : R_DLMS_CLASSES_Class15ObjList_AsyncEncodeObject
* Interface       : uint16_t R_DLMS_CLASSES_Class15ObjList_AsyncEncodeObject(
*                 :     uint8_t  bfirst,
*                 :     AsscChannel req_assc_id,
*                 :     uint16_t class_id,
*                 :     uint16_t child_index,
*                 :     int8_t   *p_attr_id,
*                 :     int8_t   *p_method_id,
*                 :     int8_t   *p_count,
*                 :     MandatoryString out_data
*                 : );
* Description     : Get the object_list attribute in asynchronous mode
* Arguments       : uint8_t bfirst
*                 :    - Indicate the call is first object.
*                 : AsscChannel req_assc_id
*                 :    - Number of object of association
*                 : uint16_t class_id
*                 :    - Index of master item
*                 : uint16_t child_index
*                 :    - Index of child item
*                 : int16_t *p_attr_id
*                 :    - Point to attribute id of child item being encoded
*                 : int16_t *p_method_id
*                 :    - Point to method id of child item being encoded
*                 : int8_t *p_stage
*                 :    - Point to encoding stage of object_list_element
*                 : MandatoryString out_data
*                 :    - Buffer to store the output
* Function Calls  : None
* Return Value    : uint16_t, length that encoded into buffer
******************************************************************************/
static uint16_t R_DLMS_CLASSES_Class15ObjList_AsyncEncodeObject(
	uint8_t  bfirst,
	AsscChannel req_assc_id,
	uint16_t class_id,
	uint16_t child_index,
	int8_t   *p_attr_id,
	int8_t   *p_method_id,
	int8_t   *p_count,
	int8_t   *p_stage,
	MandatoryString out_data
)
{
	uint8_t			u8;								/* For encoding macro */
	uint16_t		u16;							/* For encoding macro */
	uint8_t			*p_head = out_data.p_content;	/* For encoding length calc */
	uint16_t		old_length = out_data.length;	/* Old length of output buffer */
	master_record_t	*p_master_record;				/* Master record */
	child_record_t	*p_child_record;				/* Child record */
	access_right_t	*p_child_access_right;			/* Child record access right */
	int8_t			repeat = 1;						/* Repeat count for replacement/duplicate current assoication object */

	uint16_t		master_index;
	/* Argument checking */
	ASSERT_TRUE_RET_ZERO(
		class_id > g_biggest_class_id_number ||
p_attr_id==NULL||p_method_id==NULL||p_count==NULL||p_stage==NULL||
		out_data.p_content == NULL ||
		out_data.length == 0
	);
	/* Translate class_id - master_index */
	master_index = (uint16_t)g_dlms_master_class_indexes[class_id];
	/* Checking threshold of master index */
	ASSERT_TRUE_RET_ZERO(master_index >= g_classes_total_master_table_elements);
	/* Find the child record */
	p_master_record = (master_record_t *)(g_classes_master_table + master_index);
	ASSERT_TRUE_RET_ZERO(
		p_master_record->child_list_size == NULL ||
		*(p_master_record->child_list_size) == 0 ||
		p_master_record->child_list_pointer == NULL
	);
	/*
	 * TODO: Buffer check for odd and even data alignment on below code
	 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
	 */
	p_child_record = (child_record_t *)(void *)(
		((uint8_t *)p_master_record->child_list_pointer) +
		(child_index * p_master_record->child_item_size)
	);
	ASSERT_TRUE_RET_ZERO(p_child_record == NULL);

	/*
	 * Collect all object information now!
	 */

	/* Put the array identifier for first object */
	if (bfirst == TRUE) {
#if defined(SUPPORT_CURRENT_ASSC_AS_REPLACEMENT) && SUPPORT_CURRENT_ASSC_AS_REPLACEMENT == FALSE
		OBIS_ENCODE_ARRAY_TYPE_DEF(u8, out_data, g_classes_total_number_objects_each_assc[req_assc_id] + 1);
#else
		OBIS_ENCODE_ARRAY_TYPE_DEF(u8, out_data, g_classes_total_number_objects_each_assc[req_assc_id]);
#endif
		
	}

	/* Duplicate current association object? */
#if defined(SUPPORT_CURRENT_ASSC_AS_REPLACEMENT) && SUPPORT_CURRENT_ASSC_AS_REPLACEMENT == FALSE
	if (class_id == 15 && child_index == req_assc_id) {
		repeat = 2;
	}
#endif

/* Loop to encode one object */
	while (*p_count >= 0)
	{
		if (*p_stage < 0 || *p_stage > 9)
		{
			break;
		}

		if (*p_stage == 0) {		/* Encode 2 bytes {Tag, 4 elements} */
			if (out_data.length < 2) {
				break;
			}
			else {
				OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 4);																			/* object_list_element (structure) */
				(*p_stage)++;
			}
		}
		if (*p_stage == 1) {		/* Encode 3 bytes {Tag, 2 bytes of class_id} */
			if (out_data.length < 3) {
				break;
			}
			else {
				OBIS_ENCODE_THEN_ADVANCE_BUF(u16, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&class_id, sizeof(uint16_t));				/* class_id(long unsigned) */
				(*p_stage)++;
			}
		}
		if (*p_stage == 2) {		/* Encode 3 bytes {Tag, 2 bytes of class_id} */
			if (out_data.length < 3) {
				break;
			}
			else {
				OBIS_ENCODE_THEN_ADVANCE_BUF(u16, out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_master_record->class_version, sizeof(uint8_t));	/* version (signed) */
				(*p_stage)++;
			}
		}
		if (*p_stage == 3) {		/* Encode 8 bytes {Tag, length, 6 bytes of logical_name} */
			if (out_data.length < 8) {
				break;
			}
			else {
#if defined(SUPPORT_CURRENT_ASSC_AS_REPLACEMENT)				
				if (class_id == 15 && child_index == req_assc_id && *p_count == 0) {
					OBIS_ENCODE_THEN_ADVANCE_BUF(u16, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)"\x00\x00\x28\x00\x00\xFF", 6);				/* logical_name (octet string) */
				}
				else
#endif			
				{
					OBIS_ENCODE_THEN_ADVANCE_BUF(u16, out_data, TAG_DATA_OCTET_STRING, p_child_record->logical_name, 6);						/* logical_name (octet string) */
				}
				(*p_stage)++;
			}
		}
		if (*p_stage == 4) {		/* Encode 2 bytes {Tag, 2 elements} of access_rights */
			if (out_data.length < 2) {
				break;
			}
			else {
				OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);																				/* access_rights (structure) */
				(*p_stage)++;
			}
		}
		if (*p_stage == 5) {		/* Encode 2 bytes {Tag(Array), x elements} of attribute_access array */
			if (out_data.length < 2) {
				break;
			}
			else {
				OBIS_ENCODE_ARRAY_TYPE_DEF(u8, out_data, p_master_record->number_attrs);															/* attribute_access_descriptor : Array of structure */
				if (p_master_record->number_attrs > 0) {
					(*p_stage)++;
				}
				else {
					(*p_stage) = 7;	/* Jump to encode of method_access array */
				}
			}
		}
		if (*p_stage == 6) {		/* Encode 8 bytes of attribute_access_item (structure) */
			if (out_data.length < 8) {
				break;
			}
			else {
				if (p_child_record->p_access_right != NULL) {
					p_child_access_right = &p_child_record->p_access_right[req_assc_id];
				}
				else {
					p_child_access_right = NULL;
				}
				while (out_data.length >= 8 && *p_attr_id <= p_master_record->number_attrs)
				{
					OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 3);																				/* attribute_access_item, {Tag, Number Of Element} */
					{
						OBIS_ENCODE_THEN_ADVANCE_BUF(u16, out_data, TAG_DATA_INTEGER, (uint8_t *)p_attr_id, sizeof(uint8_t));							/* attribute_id, {Tag, Integer} */
						u8 = R_DLMS_CLASSES_GetAccessRightValue(REQ_TYPE_GET, *p_attr_id, p_child_access_right);
#if defined(CLASS_15_VERSION) && (CLASS_15_VERSION == 0)
							u8 &= (OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE);
#else
							u16 = (u8 & (OBIS_AR_ATTR_AUTHEN_REQUEST | OBIS_AR_ATTR_AUTHEN_RESPONSE));
							u8 &= (OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE);
							if (u16 == (OBIS_AR_ATTR_AUTHEN_REQUEST | OBIS_AR_ATTR_AUTHEN_RESPONSE)) {
								u8 += 3;	/* authenticated_read_and_write(6) - read_and_write(3) is 3, offset as 3 */
							}
#endif
						OBIS_ENCODE_THEN_ADVANCE_BUF(u16, out_data, TAG_DATA_ENUM, &u8, sizeof(uint8_t));												/* access_mode, {Tag, Enum} */
						OBIS_ENCODE_ARRAY_TYPE_DEF(u8, out_data, 0);																					/* access_selectors {Array, NULL} */
					}

					/* Next attribute */
					(*p_attr_id)++;
				}
				/* Check to start encoding of method, mask off encoding of attribute */
				if (*p_attr_id > p_master_record->number_attrs) {
					(*p_stage)++;
				}
				
			}
		}
		if (*p_stage == 7) {		/* Encode 2 bytes {Tag(Array), x elements} of method_access array */
			if (out_data.length < 2) {
				break;
			}
			else {
				OBIS_ENCODE_ARRAY_TYPE_DEF(u8, out_data, p_master_record->number_methods);															/* method_access_descriptor : Array of structure */
				if (p_master_record->number_methods > 0) {
					(*p_stage)++;
				}
				else {
					(*p_stage) = 9;	/* Check end */
				}
			}
		}
		if (*p_stage == 8) {		/* Encode 6 bytes of method_access (structure) */
			if (out_data.length < 6) {
				break;
			}
			else {
				if (p_child_record->p_access_right != NULL) {
					p_child_access_right = &p_child_record->p_access_right[req_assc_id];
				}
				else {
					p_child_access_right = NULL;
				}
				while (out_data.length >= 6 && *p_method_id <= p_master_record->number_methods)
				{
					/* Body of array, method_access_item structure, 6 bytes each */
					OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);																				/* method_access_item, {Tag, Number Of Element} */
					{
						OBIS_ENCODE_THEN_ADVANCE_BUF(u16, out_data, TAG_DATA_INTEGER, (uint8_t *)p_method_id, sizeof(uint8_t));							/* method_id, {Tag, Integer} */
						u8 = R_DLMS_CLASSES_GetAccessRightValue(REQ_TYPE_ACTION, *p_method_id, p_child_access_right);									/* method_access_mode, {Tag, Enum} */
#if defined(CLASS_15_VERSION) && (CLASS_15_VERSION == 0)
							u8 &= (OBIS_AR_METHOD_ACCESS);
							OBIS_ENCODE_THEN_ADVANCE_BUF(u16, out_data, TAG_DATA_BOOLEAN, &u8, sizeof(uint8_t));
#else
								u16 = (u8 & (OBIS_AR_METHOD_AUTHEN_REQUEST | OBIS_AR_METHOD_AUTHEN_RESPONSE));
								u8 &= (OBIS_AR_METHOD_ACCESS);
						if (u16 == (OBIS_AR_METHOD_AUTHEN_REQUEST | OBIS_AR_METHOD_AUTHEN_RESPONSE))
						{
									u8 += 1;	/* authenticated_access(2) - access(1) is 1, offset 1 */
								}
							OBIS_ENCODE_THEN_ADVANCE_BUF(u16, out_data, TAG_DATA_ENUM, &u8, sizeof(uint8_t));
#endif
					}

					/* Next method */
					(*p_method_id)++;
				}

				/* Check if finish encoding of all methods, next loop, check end */
				if (*p_method_id > p_master_record->number_methods)
				{
					(*p_stage)++;
				}
			}
		}
		if (*p_stage == 9) {		/* Check end */
			(*p_count)++;
			if (*p_count >= repeat)
			{
				*p_stage = -1;		/* Finish */
				break;
			}
			else
			{
				/* Next loop of p_count */
				(*p_stage) = 0;
				(*p_attr_id) = 1;
				(*p_method_id) = 1;
			}
		}
	}

	/* Re-check the length */
	u16 = (uint16_t)(out_data.p_content - p_head);
	ASSERT_TRUE_RET_ZERO(u16 > old_length);

	/* OK, get the out_buf_len */
	return u16;
}
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_AES) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_AES == TRUE)
/******************************************************************************
* Function Name   : R_DLMS_CLASSES_Class15Aes_DataPadding
* Interface       : uint16_t R_DLMS_CLASSES_Class15Aes_DataPadding(
*                 :     uint8_t * in_data,
*                 :     uint8_t * out_block_data,
*                 :     uint16_t in_length
*                 : );
* Description     : Padding the input data to within 1 block
* Arguments       : uint8_t * in_data
*                 :    - Pointer to input data
*                 : uint8_t * out_block_data
*                 :    - Pointer to output padded data
*                 : uint16_t in_length
*                 :    - Input data length
* Function Calls  : None
* Return Value    : uint16_t, padded length (multiple of AES_BLOCK_SIZE)
******************************************************************************/
static uint16_t R_DLMS_CLASSES_Class15Aes_DataPadding(
    uint8_t * in_data,
    uint8_t * out_block_data,
    uint16_t in_length
)
{
    uint16_t remaining_byte;

    /* Argument checking */
    ASSERT_TRUE_RET_ZERO(in_data == NULL);
    ASSERT_TRUE_RET_ZERO(out_block_data == NULL);
    ASSERT_TRUE_RET_ZERO(in_length == 0);

    /* Limit the number of supporting byte */
    in_length = (in_length > (MAX_AUTHENTICATION_BUFFER_SIZE)) ? (MAX_AUTHENTICATION_BUFFER_SIZE) : in_length;

    /* Copy the input data to output block data */
    memcpy(
        out_block_data,
        in_data,
        in_length
    );
    
    /* Calculate the number of byte need to pad */
    remaining_byte = (in_length % AES_BLOCK_SIZE) ? (AES_BLOCK_SIZE - (in_length % AES_BLOCK_SIZE)) : 0;

    /* Padding method: PKCS7 
        * Padding the remaining bytes within 1 block with number of remaining byte
    */
    memset(
        out_block_data + in_length,
        remaining_byte,
        remaining_byte
    );
    
    return (in_length + remaining_byte);
}

/******************************************************************************
* Function Name   : R_DLMS_CLASSES_Class15Aes_Ecbenc
* Interface       : uint16_t R_DLMS_CLASSES_Class15Aes_Ecbenc(
*                 :     uint8_t *ptext,
*                 :     uint8_t *ctext,
*                 :     uint8_t *key,
*                 :     uint16_t in_length,
*                 : );
* Description     : Pad the input ptext to ctext (padded buffer size is multiple of AES_BLOCK_SIZE)
*                 : Run AES128 encryption in ECB mode on padded buffer with input key
* Arguments       : uint8_t *ptext
*                 :    - Pointer to input plain text
*                 : uint8_t *ctext
*                 :    - Pointer to output cipher text
*                 : uint8_t *key
*                 :    - Pointer to input key (16 bytes)
* Function Calls  : None
* Return Value    : uint16_t, padded length (multiple of AES_BLOCK_SIZE)
******************************************************************************/
static uint16_t R_DLMS_CLASSES_Class15Aes_Ecbenc(
    uint8_t *ptext, 
    uint8_t *ctext,
    uint8_t *key,
    uint16_t in_length
)
{
    uint16_t padded_length;

    /* Argument checking */
    ASSERT_TRUE_RET_ZERO(ptext == NULL);
    ASSERT_TRUE_RET_ZERO(ctext == NULL);
    ASSERT_TRUE_RET_ZERO(key == NULL);
    ASSERT_TRUE_RET_ZERO(in_length == 0);

    /* Padding input data (AES is block processing) 
     * NOTE: used ctext as padding buffer
    */
    padded_length = R_DLMS_CLASSES_Class15Aes_DataPadding(
        ptext,
        ctext,
        in_length
    );

    ASSERT_TRUE_RET_ZERO(padded_length == 0);

    /* Run AES Processing on that block */
    R_Aes_Init();
    R_Aes_128_Ecbenc(
        ctext,
        ctext,
        key,
        (padded_length / AES_BLOCK_SIZE)
    );
    R_Aes_Close();

    return padded_length;
}
#endif//#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_AES) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_AES == TRUE)
#if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass15UserEntry, class15_user_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	/* Structure, 2 elements */
	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, &p_object->id, sizeof(uint8_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_VISIBLE_STRING, p_object->name.p_content, p_object->name.length);
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass15UserEntry, class15_user_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	/* Structure, 2 elements */
	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, &p_object->id, sizeof(uint8_t), TAG_DATA_UNSIGNED, in_data);
		OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(length, &p_object->name, TAG_DATA_VISIBLE_STRING, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}
class15_user_list_t *R_DLMS_CLASSES_RedirectClass15_UserList(distributor_params_t *p_params, class15_user_list_t *p_object, uint16_t size)
{
	class15_user_list_t					*p_clone_obj;
	VariantString						*p_clone, *p_src;
	uint8_t								offsets[4];
	uint8_t								*p_alloc, *p_head;
	uint16_t							count, i;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class15_user_list_t, p_alloc);

	OBIS_MALLOC_ASSIGN_FIXED_ARRAY(p_clone_obj, size, class15_user_t, p_alloc);
	for (i = 0; i < size; i++)
	{
		OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->p_content[i].name, 40, p_alloc);
	}

	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	return p_clone_obj;

}
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_Redirect_Class15_UserEntry, class15_user_t)
{
	class15_user_t			*p_clone_obj;
	uint8_t					*p_alloc, *p_head;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);

	p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

	OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class15_user_t, p_alloc);

	/* Create allocate for p_action_under_threshold*/
	OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->name, 40, p_alloc);

	ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
	OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

	return p_clone_obj;
}
OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass15UserEntry,
	class15_user_t,
	R_DLMS_CLASSES_EncodeClass15UserEntry,
	R_DLMS_CLASSES_DecodeClass15UserEntry,
	R_DLMS_CLASSES_Redirect_Class15_UserEntry
);

OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass15UserArray,
	class15_user_list_t,
	R_DLMS_CLASSES_EncodeClass15UserEntry
);

OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass15UserArray,
	class15_user_list_t,
	R_DLMS_CLASSES_DecodeClass15UserEntry
);

OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass15UserArray,
	class15_user_list_t,
	R_DLMS_CLASSES_EncodeClass15UserArray,
	R_DLMS_CLASSES_DecodeClass15UserArray,
	R_DLMS_CLASSES_RedirectClass15_UserList
);

#endif /* #if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2 */

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class15Init
* Interface     : void R_DLMS_CLASSES_Class15Init(void)
* Description   : Initialize class 15
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class15Init(void)
{
	uint8_t count;

	for (count = 0; count < DLMS_MAX_ASSOCIATION_SUPPORT; count++) {
		R_DLMS_CLASSES_Class15ObjList_AsyncRestart(count);
	}
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class15PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class15PollingProcessing(void)
* Description   : Polling process of class 15
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class15PollingProcessing(void)
{
	/* Put polling processing code of class 15 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class15AsscOpening
* Interface     : None R_DLMS_CLASSES_Class15AsscOpening(
*               :     AsscChannel assc                      ,
*               :     uint8_t * accepted                    ,
*               :     const AssociationCfg * p_assc_cfg     ,
*               :     CosemOpenIndication_Params * p_params ,
*               :     CosemOpenResponse_Params *p_res_params,
*               : );
* Description   : Callback event processing for indication of an
*               : association is opening by Client
* Arguments     : AsscChannel assc -
*               :     Association channel id
*               : uint8_t * accepted -
*               :     Indicator to accept connection or not
*               : const AssociationCfg * p_assc_cfg -
*               :     Configuration page of the requested association
*               : CosemOpenIndication_Params * p_params -
*               :     COSEM Open request params sent from Client
*               : CosemOpenResponse_Params *p_res_params -
*               :     COSEM Open response params being to be sent
*               :     from Server to Client
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class15AsscOpening(
	AsscChannel assc,
	uint8_t *accepted,
	const AssociationCfg *p_assc_cfg,
	CosemOpenIndication_Params *p_req_params,
	CosemOpenResponse_Params *p_res_params
)
{
	uint16_t count;

#if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2
	if (assc < g_objects_child_table_class15_length) {

		/* exist user list? */
		if (g_objects_child_table_class15[assc].p_user_list != NULL &&
			g_objects_child_table_class15[assc].p_user_list->p_content != NULL &&
			g_objects_child_table_class15[assc].p_user_list->length > 0 &&
			g_objects_child_table_class15[assc].p_current_user != NULL)
		{
			/* In default, AA connection is reject */
			*accepted = FALSE;
			p_res_params->failure_type.associate_source_diag_choice_tag = TAG_ACSE_SERVICE_USER;
			p_res_params->failure_type.diag_detail_code = VAL_ASCE_SERVICE_USER_CALLINGAEINVOCATIONNOTREG;
			p_res_params->xdlms_initiate_error.confirm_service_error_choice_tag = TAG_CONFIRM_SERVICE_ERR_INITIATEERROR;
			p_res_params->xdlms_initiate_error.service_error_choice_tag = TAG_SERVICE_ERR_APPLICATION_REFERENCE;
			p_res_params->xdlms_initiate_error.error_detail_code = VAL_APP_REF_OTHER;

			/* Current user is a RAM var? */
			if (R_DLMS_CLASSES_IsBufferWritable((uint8_t *)g_objects_child_table_class15[assc].p_current_user) == TRUE)
			{
			g_objects_child_table_class15[assc].p_current_user->id = 0;
			g_objects_child_table_class15[assc].p_current_user->name.p_content = NULL;
			g_objects_child_table_class15[assc].p_current_user->name.length = 0;

			/* Search for user if exist then put the called_AP_invocation_id equal to id that client requested */
				if (p_req_params->calling_AE_invocation_id.use == TRUE) {
				for (count = 0; count < g_objects_child_table_class15[assc].p_user_list->length; count++) {
						if (p_req_params->calling_AE_invocation_id.value == g_objects_child_table_class15[assc].p_user_list->p_content[count].id) {
						
						/* Found user! */
						*accepted = TRUE;
						*g_objects_child_table_class15[assc].p_current_user = g_objects_child_table_class15[assc].p_user_list->p_content[count];

						/* Stop searching */
						break;
					}
				}
			}
		}
		}
		else {
			*accepted = TRUE;
		}
	}
#endif /* #if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2 */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class15AsscOpened
* Interface     : void R_DLMS_CLASSES_Class15AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 15
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Function Calls:
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class15AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 15 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class15AsscClosing
* Interface     : void R_DLMS_CLASSES_Class15AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 15
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class15AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 15 here */
	R_DLMS_CLASSES_Class15ObjList_AsyncRestart(p_assc_session->connected_assc_id);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass15
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass15(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 15
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass15(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass15,
		R_DLMS_OBJECTS_Class15Distributor,
		p_params
	);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass15
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeAbstractClass15(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 15
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass15(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	uint16_t				encoded_length;
	class15_child_record_t	*p_class15_obj = (class15_child_record_t *)p_params->p_child_record;
	uint8_t					u8;
	uint16_t				u16;
	uint8_t					*p_head;
	uint8_t					*p_alloc, *p_alloc_head;

    /* Common method data */
    uint8_t                 i;
    uint8_t		            data[MAX_AUTHENTICATION_BUFFER_SIZE];       /* concatenated data for authentication */
    uint16_t	            data_length;	                            /* Actual length used on data */

    /* Shared method data */
    union {
        
        struct {
            uint16_t padded_length;
        } aes;
        
        struct {
	        uint8_t	hash_value[16];
        } md5;
        
        struct {
	        uint8_t	hash_value[20];
        } sha1;

        struct{
            uint8_t				iv[12];
            uint8_t	            hash_value[20];
            SCByte				common_sc;
            uint32_t			common_ic;
            MandatoryString		encryption_key;
        } gmac;

        struct {
            uint8_t	hash_value[32];
        } sha256;
        
    } method_data;

	/* Action data */
	class15_action_data_t		action_data;
    
	uint8_t						client_sap = 0;
	uint16_t					server_sap = 0;
	ChannelType					channel_type = CHANNEL_TYPE_NONE;

    /* Initialize method data */
    memset(&method_data, 0, sizeof(method_data));

	/* Get current malloc position */
	p_alloc = p_alloc_head = OBIS_MALLOC_GET_POINTER(p_params);

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			case 2:	/* [local] object_list_type_t *object_list */
				if (p_params->req_type == REQ_TYPE_GET)
				{
					if (p_params->out_data.length < 8) {
						/* Fatal error: PDU too short, need debug here */
						OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT, FALSE);
						OBIS_DISTRIBUTION_FAILED(p_params->result);
						return;
					}
					
					/* First start (re-start) asynchronous get service? */
					if (p_params->service_type.get == COSEM_GET_REQUEST_NORMAL ||
						g_classes_class15_obj_list_session[p_params->connected_assc_id].is_async_end == TRUE)
					{
						/* Mark as async ended to restart */
						g_classes_class15_obj_list_session[p_params->connected_assc_id].is_async_end = TRUE;

						if (R_DLMS_CLASSES_Class15ObjList_AsyncStart(
								p_params->connected_assc_id,
								(AsscChannel)p_params->child_index
							) == FALSE)
						{
							/* Fatal error: does not have any object */
							OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE, FALSE);
							OBIS_DISTRIBUTION_FAILED(p_params->result);
							return;
						}
					}

					/* Prepare to encode object_list */
					*p_params->p_out_encoded_len = 0;

					/* 32 is minimum encoding length of R_DLMS_CLASSES_Class15ObjList_AsyncEncodeObject() function */
					while (p_params->out_data.length >= 8)
					{
						/*
						 * Call to encode 1 object information
						 * And check fatal error.
						 * Checking to end here to prevent error
						 */
						encoded_length = R_DLMS_CLASSES_Class15ObjList_AsyncEncodeObject(
							g_classes_class15_obj_list_session[p_params->connected_assc_id].is_async_end,	/* First object or not */
							p_params->child_index,															/* Id of association */
							g_classes_class15_obj_list_session[p_params->connected_assc_id].master_id,		/* Master row id of object */
							g_classes_class15_obj_list_session[p_params->connected_assc_id].child_id,		/* Child row id of object */
							&g_classes_class15_obj_list_session[p_params->connected_assc_id].attr_id,		/* Point to attribute id of child record being encoded */
							&g_classes_class15_obj_list_session[p_params->connected_assc_id].method_id,		/* Point to method id of child record being encoded */
							&g_classes_class15_obj_list_session[p_params->connected_assc_id].count,			/* Point to counter to loop for current association object */
							&g_classes_class15_obj_list_session[p_params->connected_assc_id].stage,			/* Point to encoding stage of object_list_element */
							p_params->out_data
						);

						if (encoded_length == 0) {
							/* Fatal error: buffer overflow, need debug here */
							g_classes_class15_obj_list_session[p_params->connected_assc_id].is_async_end = TRUE;		/* Mark as async ended */
							OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT, FALSE);
							OBIS_DISTRIBUTION_FAILED(p_params->result);
							return;
						}

						/* Update value for next encoding */
						*p_params->p_out_encoded_len += encoded_length;
						OBIS_ADVANCE_BUFFER(p_params->out_data, encoded_length);

						/* Mark as processing in async */
						g_classes_class15_obj_list_session[p_params->connected_assc_id].is_async_end = FALSE;

						/*
						 * Get the next object in the table,
						 * until end or the next object can be accessed
						 */
						if (R_DLMS_CLASSES_Class15ObjList_AsyncNextPart(p_params->connected_assc_id, p_params->child_index) == TRUE)
						{
							g_classes_class15_obj_list_session[p_params->connected_assc_id].is_async_end = TRUE;		/* Mark as async ended */
							break;
						}
					}
					
					/*
					 * Get the result status here, based on async is end or not
					 */
					OBIS_DATA_ACCESS_RESULT(
						p_params->result,
						VAL_DATA_ACCESS_RESULT_SUCCESS,
						g_classes_class15_obj_list_session[p_params->connected_assc_id].is_async_end == TRUE ? FALSE : TRUE
					);
					OBIS_DISTRIBUTION_SUCCESS(p_params->result);
				}
				else
				{
					/* Do nothing, OBIS code is read only */
				}
				break;

			case 3:	/* [local] associated_partners_type associated_partners_id */
				if (p_params->req_type == REQ_TYPE_GET)
				{
					if (p_class15_obj->p_assc_config != NULL) {

						p_head = p_params->out_data.p_content;

						OBIS_DIST_ENCODE_STRUCTURE_TYPE_DEF(u8, p_params->out_data, 2);
						/* Get current channel type of the connected channel */
						channel_type = R_MGMT_GetChannelType(p_params->p_assc_session->mgmt_channel_id);

						/*
						 * Since current DLMS stack only support Management Logical Device (0x0001),
						 * do direct binding of pre-establish AA with the active communication profile
						 *
						 * TODO: Once meter support multiple Logical Devices, consider to do SAP assignement (class 17 object)
						 */
						if (channel_type == CHANNEL_TYPE_HDLC)
						{
							client_sap = p_class15_obj->p_assc_config->remote_mac_addr;
							server_sap = HDLC_CH0_MAC_ADDR_UPPER;
						}
#if defined(SUPPORT_TCP_PROFILE) && (SUPPORT_TCP_PROFILE == TRUE)
						else if (channel_type == CHANNEL_TYPE_TCP)
						{
							client_sap = (uint8_t)p_class15_obj->p_assc_config->remote_wport;
							server_sap = TCP_PORT0_WPORT;
						}
#endif
#if defined(SUPPORT_UDP_PROFILE) && (SUPPORT_UDP_PROFILE == TRUE)
						else if (channel_type == CHANNEL_TYPE_UDP)
						{
							client_sap = (uint8_t)p_class15_obj->p_assc_config->remote_wport;
							server_sap = UDP_PORT0_WPORT;
						}
#endif							
						else
						{
							/* Error, communication profile is unknown or unsupported */
						}
						OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_INTEGER, &client_sap, sizeof(uint8_t));
						OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&server_sap, sizeof(uint16_t));

						*p_params->p_out_encoded_len = (uint16_t)(p_params->out_data.p_content - p_head);
						if (*p_params->p_out_encoded_len > 0) {
							OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
							OBIS_DISTRIBUTION_SUCCESS(p_params->result);
						}
					}
				}
				else
				{
					/* Do nothing, read only */
				}
				break;

			case 4:	/* [local] context_name_type context_name */
				if (p_params->req_type == REQ_TYPE_GET)
				{
					if (p_class15_obj->p_assc_config != NULL) {

						uint8_t app_context_name[7] = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x00 };
						app_context_name[6] = p_class15_obj->p_assc_config->context_id;

						*p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
							p_params->out_data.p_content,
							p_params->out_data.length,
							TAG_DATA_OCTET_STRING,
							app_context_name,
							7
						);

						if (*p_params->p_out_encoded_len > 0) {
							OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
							OBIS_DISTRIBUTION_SUCCESS(p_params->result);
						}
					}
				}
				else
				{
					/* Do nothing, read only */
				}
				break;

			case 5:	/* [local] xDLMS-context-type xDLMS_context_info */
				if (p_params->req_type == REQ_TYPE_GET)
				{
					if (p_class15_obj->p_assc_config != NULL) {

						ConformanceBits conformance_bits = {
							p_class15_obj->p_assc_config->conformance_byte0,
							p_class15_obj->p_assc_config->conformance_byte1,
							p_class15_obj->p_assc_config->conformance_byte2
						};

						p_head = p_params->out_data.p_content;

						/* Structure, 6 elements */
						OBIS_DIST_ENCODE_STRUCTURE_TYPE_DEF(u8, p_params->out_data, 6);
						{
							/* Conformance bits */
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_BIT_STRING, (uint8_t *)&conformance_bits, sizeof(ConformanceBits) * 8);

							/* max receive pdu size */
							u16 = DLMS_LIB_MAX_APDU_SIZE;
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&u16, sizeof(uint16_t));

							/* max send pdu size */
							u16 = g_classes_assc_connection_session[p_params->child_index].negotiated_client_max_pdu_size;
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&u16, sizeof(uint16_t));

							/* dlms version number */
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_UNSIGNED, (uint8_t *)&p_class15_obj->p_assc_config->dlms_version_number, sizeof(uint8_t));

							/* quality of service (no use) */
							u8 = 0;
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_INTEGER, &u8, sizeof(int8_t));

							/* cyphering_info */
							OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, p_params->out_data, TAG_DATA_OCTET_STRING,
								g_classes_assc_connection_session[p_params->child_index].dedicated_key.p_content,
								g_classes_assc_connection_session[p_params->child_index].dedicated_key.length
							);
						}

						*p_params->p_out_encoded_len = (uint16_t)(p_params->out_data.p_content - p_head);
						if (*p_params->p_out_encoded_len > 0) {
							OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
							OBIS_DISTRIBUTION_SUCCESS(p_params->result);
						}
					}
				}
				else
				{
					/* Do nothing, read only */
				}
				break;

			case 6:	/* [local] mechanism_name_type authentication_mechanism_name */
				if (p_params->req_type == REQ_TYPE_GET)
				{
					if (p_class15_obj->p_assc_config != NULL) {

						uint8_t authentication_mechanism_name[7] = { 0x60, 0x85, 0x74, 0x05, 0x08, 0x02, 0x00 };
						authentication_mechanism_name[6] = p_class15_obj->p_assc_config->mechanism_id;

						*p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
							p_params->out_data.p_content,
							p_params->out_data.length,
							TAG_DATA_OCTET_STRING,
							authentication_mechanism_name,
							7
						);

						if (*p_params->p_out_encoded_len > 0) {
							OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE);
							OBIS_DISTRIBUTION_SUCCESS(p_params->result);
						}
					}
				}
				else
				{
					/* Do nothing, read only */
				}
				break;

			case 7:	/* [local] octet-string LLS_secret, MandatoryString and FixedString are same */
				R_DLMS_CLASSES_DistributeFixedString(p_params, TAG_DATA_OCTET_STRING, (FixedString *)&p_class15_obj->p_assc_config->authentication_value);
				break;

			case 8:	/* [local] enum association_status */
				if (p_params->req_type == REQ_TYPE_GET)
				{
					uint8_t assc_status = 0;	/* Non-associated */

					if (R_DLMS_IsAsscConnected(p_params->child_index)) {
						if (g_classes_assc_connection_session[p_params->child_index].hls_restrict_mode == TRUE) {
							assc_status = 1;	/* association-pending */
						}
						else {
							assc_status = 2;	/* associated */
						}
					}
					else if (p_class15_obj->p_assc_config != NULL &&
							 p_class15_obj->p_assc_config->pre_established == TRUE)
					{
						assc_status = 2; /* associated */
					}

					R_DLMS_CLASSES_DistributeEnum(p_params, &assc_status);
				}
				else
				{
					/* Do nothing, read only */
				}
				break;

#if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 1
			case 9:
				R_DLMS_CLASSES_DistributeFixedString(p_params, TAG_DATA_OCTET_STRING, p_class15_obj->p_security_setup_ref);
				break;
#endif
#if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2
			case 10:
				R_DLMS_CLASSES_DistributeClass15UserArray(p_params, p_class15_obj->p_user_list);
				break;
			case 11:
				R_DLMS_CLASSES_DistributeClass15UserEntry(p_params, p_class15_obj->p_current_user);
				break;
#endif
			default:
				break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
		switch (p_params->descriptor.method.method_id)
		{
			case 1:	/* reply_to_HLS_authentication (data) */

				/* Create malloc buffer for user use (if any) */
				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m1_reply_to_hls_authentication, VariantString, p_alloc);
				OBIS_MALLOC_ASSIGN_VARIANT_STRING(action_data.p_m1_reply_to_hls_authentication, 128, p_alloc);
				OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_alloc_head));
				p_params->service_params.created = TRUE;

				/* Decode buffer from client to get fStoC, store into action_data.p_m1_reply_to_hls_authentication */
				if (R_DLMS_CLASSES_DecodeVariantString(action_data.p_m1_reply_to_hls_authentication, TAG_DATA_OCTET_STRING, p_params->in_data) == 0)
				{
					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
					break;	/* Stop processing since decode error happen on method invocation params */
				}
				else {
					p_params->service_params.decode_success = TRUE;
				}
				
				/*
				* -----------------------------------------------------------------------------------------------------------
				* Information Collection for HLS authentication
				* -----------------------------------------------------------------------------------------------------------
				* HLS method	: p_class15_obj->p_assc_config->mechanism_id
				* key			: p_class15_obj->p_assc_config->authentication_value
				* StoC challenge: p_class15_obj->p_assc_config->StoC
				* CtoS			: g_classes_assc_connection_session[p_params->child_index].CtoS
				* fStoC			: (action_data.p_m1_reply_to_hls_authentication) fStoC, decoded from method invocation params
				* fCtoS			: (local var  ) hash_value, output to p_params->out_data
				*/

				if (FALSE) {
					/* Do nothing, this is to support else if flexible macro code below */
				}
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_AES) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_AES == TRUE)
				else if (p_class15_obj->p_assc_config->mechanism_id == MECHANISM_ID2_HIGH_SECURITY)
				{
                    /* Calculate f(StoC) */
                    method_data.aes.padded_length = R_DLMS_CLASSES_Class15Aes_Ecbenc(
                        p_class15_obj->p_assc_config->StoC.p_content,                               /* ptext */
                        data,                                                                       /* ctext */
                        p_class15_obj->p_assc_config->authentication_value.p_content,               /* key */
                        p_class15_obj->p_assc_config->StoC.length                                   /* length */
                    );

                    if (method_data.aes.padded_length == 0)
                    {
                        break;
                    }

                    /* Check client is authenticated or not: compare with f(StoC) from client */
                    for (i = 0; i < method_data.aes.padded_length; i++)
                    {
                        if (data[i] != action_data.p_m1_reply_to_hls_authentication->p_content[i])
                        {
                            break;
                        }
                    }
                    if (i < method_data.aes.padded_length)
                    {
                        /* not match, break as failure */
                        break;
                    }

                    /* Client is authenticated, processes f(CtoS) send to client */
                    method_data.aes.padded_length = R_DLMS_CLASSES_Class15Aes_Ecbenc(
                        g_classes_assc_connection_session[p_params->child_index].CtoS.p_content,    /* ptext */
                        data,                                                                       /* ctext */
                        p_class15_obj->p_assc_config->authentication_value.p_content,               /* key */
                        g_classes_assc_connection_session[p_params->child_index].CtoS.length        /* length */
                    );

                    if (method_data.aes.padded_length == 0)
                    {
                        break;
                    }

                    data_length = method_data.aes.padded_length;

                    *p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
                        p_params->out_data.p_content,
                        p_params->out_data.length,
                        TAG_DATA_OCTET_STRING,
                        data,
                        data_length
                    );
                    if (*p_params->p_out_encoded_len > 0) {
                        g_classes_assc_connection_session[p_params->child_index].hls_restrict_mode = FALSE;		/* Exist restrict mode on HLS Association */
                        OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SUCCESS, FALSE);
                        OBIS_DISTRIBUTION_SUCCESS(p_params->result);
                    }
				}
#endif
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_MD5) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_MD5 == TRUE)
				else if (p_class15_obj->p_assc_config->mechanism_id == MECHANISM_ID3_HIGH_SECURITY_MD5)
				{
                    uint8_t i;

                    /* Create the f(StoC) again 
                    * f(StoC).p_content = StoC || authentication_value
                    */
                    memcpy(
                        data, 
                        p_class15_obj->p_assc_config->StoC.p_content, 
                        p_class15_obj->p_assc_config->StoC.length
                    );

                    memcpy(
                        data + p_class15_obj->p_assc_config->StoC.length,
                        p_class15_obj->p_assc_config->authentication_value.p_content,
                        p_class15_obj->p_assc_config->authentication_value.length
                    );

                    data_length = p_class15_obj->p_assc_config->StoC.length + \
                        p_class15_obj->p_assc_config->authentication_value.length;

                    R_Md5_CalculateOnce(
                        data,                           /* msg */
                        data_length,                    /* length */
                        method_data.md5.hash_value      /* hash */
                    );

                    /* Verify own f(StoC) with the one that send from client */
                    for (i = 0; i < sizeof(method_data.md5.hash_value); i++)
                    {
                        if (method_data.md5.hash_value[i] != action_data.p_m1_reply_to_hls_authentication->p_content[i])
                        {
                            break;
                        }
                    }
                    if (i < sizeof(method_data.md5.hash_value))
                    {
                        /* MD5 not match, break as failure */
                        break;
                    }

                    /*
                    * If reached here: means verify OK, then make the f(CtoS) and
                    * send back to client
                    */

                    /* Make f(CtoS) (hash_size) then store to p_out_buf */
                    memcpy(
                        data,
                        g_classes_assc_connection_session[p_params->child_index].CtoS.p_content,
                        g_classes_assc_connection_session[p_params->child_index].CtoS.length
                    );

                    memcpy(
                        data + g_classes_assc_connection_session[p_params->child_index].CtoS.length,
                        p_class15_obj->p_assc_config->authentication_value.p_content,
                        p_class15_obj->p_assc_config->authentication_value.length
                    );

                    data_length = g_classes_assc_connection_session[p_params->child_index].CtoS.length + \
                        p_class15_obj->p_assc_config->authentication_value.length;
                    
                    R_Md5_CalculateOnce(
                        data,                           /* msg */
                        data_length,                    /* length */
                        data                            /* hash */
                    );
                    
                    data_length = sizeof(method_data.md5.hash_value);

                    *p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
                        p_params->out_data.p_content,
                        p_params->out_data.length,
                        TAG_DATA_OCTET_STRING,
                        data,
                        data_length
                    );
                    if (*p_params->p_out_encoded_len > 0) {
                        g_classes_assc_connection_session[p_params->child_index].hls_restrict_mode = FALSE;		/* Exist restrict mode on HLS Association */
                        OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SUCCESS, FALSE);
                        OBIS_DISTRIBUTION_SUCCESS(p_params->result);
                    }
				}
#endif
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_SHA1) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_SHA1 == TRUE)
				else if (p_class15_obj->p_assc_config->mechanism_id == MECHANISM_ID4_HIGH_SECURITY_SHA1)
				{
                    uint8_t i;

                    /* Create the f(StoC) again
                    * f(StoC).p_content = StoC || authentication_value
                    */
                    memcpy(
                        data,
                        p_class15_obj->p_assc_config->StoC.p_content,
                        p_class15_obj->p_assc_config->StoC.length
                    );

                    memcpy(
                        data + p_class15_obj->p_assc_config->StoC.length,
                        p_class15_obj->p_assc_config->authentication_value.p_content,
                        p_class15_obj->p_assc_config->authentication_value.length
                    );

                    data_length = p_class15_obj->p_assc_config->StoC.length + \
                        p_class15_obj->p_assc_config->authentication_value.length;

                    R_Sha1_CalculateOnce(
                        data,                           /* msg */
                        data_length,                    /* length */
                        method_data.sha1.hash_value     /* hash */
                    );

                    /* Verify own f(StoC) with the one that send from client */
                    for (i = 0; i < sizeof(method_data.sha1.hash_value); i++)
                    {
                        if (method_data.sha1.hash_value[i] != action_data.p_m1_reply_to_hls_authentication->p_content[i])
                        {
                            break;
                        }
                    }
                    if (i < sizeof(method_data.sha1.hash_value))
                    {
                        /* SHA1 not match, break as failure */
                        break;
                    }

                    /*
                    * If reached here: means verify OK, then make the f(CtoS) and
                    * send back to client
                    */

                    /* Make f(CtoS) (hash_size) then store to data for further encoding */
                    memcpy(
                        data,
                        g_classes_assc_connection_session[p_params->child_index].CtoS.p_content,
                        g_classes_assc_connection_session[p_params->child_index].CtoS.length
                    );

                    memcpy(
                        data + g_classes_assc_connection_session[p_params->child_index].CtoS.length,
                        p_class15_obj->p_assc_config->authentication_value.p_content,
                        p_class15_obj->p_assc_config->authentication_value.length
                    );

                    data_length = g_classes_assc_connection_session[p_params->child_index].CtoS.length + \
                        p_class15_obj->p_assc_config->authentication_value.length;

                    R_Sha1_CalculateOnce(
                        data,                           /* msg */
                        data_length,                    /* length */
                        data                            /* hash */
                    );

                    data_length = sizeof(method_data.sha1.hash_value);

                    *p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
                        p_params->out_data.p_content,
                        p_params->out_data.length,
                        TAG_DATA_OCTET_STRING,
                        data,
                        data_length
                    );
                    if (*p_params->p_out_encoded_len > 0) {
                        g_classes_assc_connection_session[p_params->child_index].hls_restrict_mode = FALSE;		/* Exist restrict mode on HLS Association */
                        OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SUCCESS, FALSE);
                        OBIS_DISTRIBUTION_SUCCESS(p_params->result);
                    }
				}
#endif
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_GMAC) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_GMAC == TRUE)
				else if (p_class15_obj->p_assc_config->mechanism_id == MECHANISM_ID5_HIGH_SECURITY_GMAC)
				{
					/*
					* GMAC verification
					*
					* Data = f(StoC) = SC || FC || Atag, 17 bytes
					* Atag = GMAC(SC || AK || StoC)
					*/

					if (p_class15_obj->p_assc_config->p_security_context == NULL ||
						action_data.p_m1_reply_to_hls_authentication->length != 17)
					{
						/* failure on length */
						break;
					}

					/* ---------------------------------------------------------------------------------------------------
					 * action_data.p_m1_reply_to_hls_authentication->p_content = { SC || IC || GMAC (SC || AK || StoC) }
					 * ---------------------------------------------------------------------------------------------------
					 */

					/* Get IC & SC */
					method_data.gmac.common_sc.byte = *(action_data.p_m1_reply_to_hls_authentication->p_content);
					memcpy(&method_data.gmac.common_ic, action_data.p_m1_reply_to_hls_authentication->p_content + 1, 4);

					/* Make client IV : 8bytes client Sys-T || 4 bytes client FC */
					memcpy(
                        method_data.gmac.iv,
						p_class15_obj->p_assc_config->p_security_context->client_title.p_content,
						p_class15_obj->p_assc_config->p_security_context->client_title.length
					);
					memcpy(
						method_data.gmac.iv + p_class15_obj->p_assc_config->p_security_context->client_title.length,
						action_data.p_m1_reply_to_hls_authentication->p_content + 1,
						4
					);

					/*
					 * Make aad: SC || AK || StoC, store to 'data' var
					 */

					/* Get SC */
					data[0] = *(action_data.p_m1_reply_to_hls_authentication->p_content);
					/* Concat AK */
					memcpy(
						data + (1),
						p_class15_obj->p_assc_config->p_security_context->authentication_key.p_content,
						p_class15_obj->p_assc_config->p_security_context->authentication_key.length
					);
					/* Concat StoC */
					memcpy(
						data + (1 + p_class15_obj->p_assc_config->p_security_context->authentication_key.length),
						p_class15_obj->p_assc_config->StoC.p_content,
						p_class15_obj->p_assc_config->StoC.length
					);
					/* Get total length */
					data_length = (
						1 +
						p_class15_obj->p_assc_config->p_security_context->authentication_key.length +
						p_class15_obj->p_assc_config->StoC.length
					);

					/* Get encryption key */
					if (method_data.gmac.common_sc.bits.keyset == SC_KEYSET_UNICAST) {
                        method_data.gmac.encryption_key = p_class15_obj->p_assc_config->p_security_context->global_unicast_key.key;
					}
					else if (method_data.gmac.common_sc.bits.keyset == SC_KEYSET_BROADCAST) {
                        method_data.gmac.encryption_key = p_class15_obj->p_assc_config->p_security_context->global_broadcast_key.key;
					}
					else {
						break;	/* Can not determine encryption key */
					}

					/* Decrypt to verify the atag from Client processing */
					if (R_DLMS_AES_GCM_Decrypt(
						NULL,
						NULL,
						0,
                        method_data.gmac.encryption_key.p_content,
						action_data.p_m1_reply_to_hls_authentication->p_content + 5,
						12,
                        method_data.gmac.iv,
						12,
						data,
						data_length
						) != 0)
					{
						break;	/* Client atag verification failure */
					}

					/*
					* Prepare & send out the f(CtoS)
					* Data Out = f(CtoS) = SC || FC || Atag, 17 bytes
					* Atag = GMAC(SC || AK || CtoS)
					*/

					/* Make server IV : 8bytes server Sys-T || 4 bytes server FC */
					memcpy(
                        method_data.gmac.iv,
						p_class15_obj->p_assc_config->p_security_context->server_title.p_content, 
						p_class15_obj->p_assc_config->p_security_context->server_title.length
					);
					memcpy(
                        method_data.gmac.iv + p_class15_obj->p_assc_config->p_security_context->server_title.length,
						&method_data.gmac.common_ic,
						4
					);

					/*
					 * Make aad: SC || AK || CtoS, store to 'data' var
					 */

					/* Get SC */
                    data[0] = method_data.gmac.common_sc.byte;
					/* Concat AK */
					memcpy(
						data + (1),
						p_class15_obj->p_assc_config->p_security_context->authentication_key.p_content,
						p_class15_obj->p_assc_config->p_security_context->authentication_key.length
					);
					/* Concat CtoS */
					memcpy(
						data + (1 + p_class15_obj->p_assc_config->p_security_context->authentication_key.length),
						g_classes_assc_connection_session[p_params->child_index].CtoS.p_content,
						g_classes_assc_connection_session[p_params->child_index].CtoS.length
					);
					/* Get total length */
					data_length = (
						1 +
						p_class15_obj->p_assc_config->p_security_context->authentication_key.length +
						g_classes_assc_connection_session[p_params->child_index].CtoS.length
					);

					/* Encrypt to create the atag */
					if (R_DLMS_AES_GCM_Encrypt(
						NULL,
						NULL,
						0,
                        method_data.gmac.encryption_key.p_content,
                        method_data.gmac.hash_value,
						12,
                        method_data.gmac.iv,
						12,
						data,
						data_length
						) != 0)
					{
						break;	/* Create atag failure */
					}

					/*
					* If reached here: means verify OK, then send f(CtoS) to client
					* SC || IC || GMAC (SC || AK || CtoS)
					*/
                    data[0] = method_data.gmac.common_sc.byte;
					memcpy(data + 1, &method_data.gmac.common_ic, 4);
					memcpy(data + 5, method_data.gmac.hash_value, 12);
					data_length = 17;

					*p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
						p_params->out_data.p_content,
						p_params->out_data.length,
						TAG_DATA_OCTET_STRING,
						data,
						data_length
					);
					if (*p_params->p_out_encoded_len > 0) {
						g_classes_assc_connection_session[p_params->child_index].hls_restrict_mode = FALSE;		/* Exist restrict mode on HLS Association */
						OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SUCCESS, FALSE);
						OBIS_DISTRIBUTION_SUCCESS(p_params->result);
					}
				}
				#endif
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_SHA256) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_SHA256 == TRUE)
                else if (p_class15_obj->p_assc_config->mechanism_id == MECHANISM_ID6_HIGH_SECURITY_SHA256)
                {
                    /*
                    * SHA256 verification
                    *
                    * f(StoC) = SHA256 (HLS_Secret || SystemTitle-C || SystemTitle-S || StoC || CtoS)
                    */

                    /* HLS Secret */
                    memcpy(
                        data,
                        p_class15_obj->p_assc_config->authentication_value.p_content,
                        p_class15_obj->p_assc_config->authentication_value.length
                    );

                    data_length = p_class15_obj->p_assc_config->authentication_value.length;

                    /* Client title */
                    memcpy(
                        data + data_length,
                        g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->client_title.p_content,
                        g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->client_title.length
                    );

                    data_length += g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->client_title.length;

                    /* Server title */
                    memcpy(
                        data + data_length,
                        g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->server_title.p_content,
                        g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->server_title.length
                    );

                    data_length += g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->server_title.length;

                    /* StoC */
                    memcpy(
                        data + data_length,
                        p_class15_obj->p_assc_config->StoC.p_content,
                        p_class15_obj->p_assc_config->StoC.length
                    );

                    data_length += p_class15_obj->p_assc_config->StoC.length;

                    /* CtoS */
                    memcpy(
                        data + data_length,
                        g_classes_assc_connection_session[p_params->child_index].CtoS.p_content,
                        g_classes_assc_connection_session[p_params->child_index].CtoS.length
                    );

                    data_length += g_classes_assc_connection_session[p_params->child_index].CtoS.length;

                    R_Sha256_CalculateOnce(
                        data,                           /* msg */
                        data_length,                    /* length */
                        method_data.sha256.hash_value   /* hash */
                    );

                    /* Verify own f(StoC) with the one that send from client */
                    for (i = 0; i < sizeof(method_data.sha256.hash_value); i++)
                    {
                        if (method_data.sha256.hash_value[i] != action_data.p_m1_reply_to_hls_authentication->p_content[i])
                        {
                            break;
                        }
                    }
                    if (i < sizeof(method_data.sha256.hash_value))
                    {
                        /* SHA256 not match, break as failure */
                        break;
                    }

                    /*
                    * If reached here: means verify OK, then make the f(CtoS) and
                    * send back to client
                    */

                    /* Make f(CtoS) = SHA256 (HLS_Secret || SystemTitle-S || SystemTitle-C || CtoS || StoC)
                     * then store to data for further encoding 
                     */
                    /* HLS Secret */
                    memcpy(
                        data,
                        p_class15_obj->p_assc_config->authentication_value.p_content,
                        p_class15_obj->p_assc_config->authentication_value.length
                    );

                    data_length = p_class15_obj->p_assc_config->authentication_value.length;

                    /* Server title */
                    memcpy(
                        data + data_length,
                        g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->server_title.p_content,
                        g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->server_title.length
                    );

                    data_length += g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->server_title.length;

                    /* Client title */
                    memcpy(
                        data + data_length,
                        g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->client_title.p_content,
                        g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->client_title.length
                    );

                    data_length += g_classes_assc_connection_session[p_params->child_index].p_assc_config->p_security_context->client_title.length;

                    /* CtoS */
                    memcpy(
                        data + data_length,
                        g_classes_assc_connection_session[p_params->child_index].CtoS.p_content,
                        g_classes_assc_connection_session[p_params->child_index].CtoS.length
                    );

                    data_length += g_classes_assc_connection_session[p_params->child_index].CtoS.length;

                    /* StoC */
                    memcpy(
                        data + data_length,
                        p_class15_obj->p_assc_config->StoC.p_content,
                        p_class15_obj->p_assc_config->StoC.length
                    );

                    data_length += p_class15_obj->p_assc_config->StoC.length;

                    R_Sha256_CalculateOnce(
                        data,                           /* msg */
                        data_length,                    /* length */
                        data                            /* hash */
                    );

                    data_length = sizeof(method_data.sha256.hash_value);

                    *p_params->p_out_encoded_len = R_DLMS_CLASSES_EncodeCommonType(
                        p_params->out_data.p_content,
                        p_params->out_data.length,
                        TAG_DATA_OCTET_STRING,
                        data,
                        data_length
                    );
                    if (*p_params->p_out_encoded_len > 0) {
                        g_classes_assc_connection_session[p_params->child_index].hls_restrict_mode = FALSE;		/* Exist restrict mode on HLS Association */
                        OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_SUCCESS, FALSE);
                        OBIS_DISTRIBUTION_SUCCESS(p_params->result);
                    }
                }
#endif
				else {
					/* Do nothing, error shall be returned */
				}
				break;

			case 2:	/* change_HLS_secret (data), support to decode action parameter sent from Client only */
				/* Create malloc buffer for user use (if any) */
				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m2_change_hls_secret, VariantString, p_alloc);
				OBIS_MALLOC_ASSIGN_VARIANT_STRING(action_data.p_m2_change_hls_secret, 128, p_alloc);
				OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_alloc_head));
				p_params->service_params.created = TRUE;

				/* Decode buffer from client to get data, store into action_data.p_m2_change_hls_secret */
				if (R_DLMS_CLASSES_DecodeVariantString(action_data.p_m2_change_hls_secret, TAG_DATA_OCTET_STRING, p_params->in_data) == 0)
				{
					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
					break;
				}
				else {
					p_params->service_params.decode_success = TRUE;
				}

				break;

			case 3: /* add_object (data) : No support */
				break;

			case 4: /* delete_object (data) : No support */
				break;

#if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2
			case 5:	/* add_user (data), support to decode action parameter sent from Client only */
			case 6:	/* remove_user (data), support to decode action parameter sent from Client only */

				/*
				 * Create malloc buffer for user use (if any)
				 * Since method 5 and method 6 have the same action parameter (class15_user_t),
				 * just need to create malloc buffer and pointed by action_data.p_m5_add_user.
				 * The action_data.p_m6_remove_user be also pointed by the same malloc location.
				 */
				OBIS_MALLOC_ASSIGN_OBJECT(action_data.p_m5_add_user, class15_user_t, p_alloc);
				OBIS_MALLOC_ASSIGN_VARIANT_STRING(&action_data.p_m5_add_user->name, 128, p_alloc);
				OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_alloc_head));
				p_params->service_params.created = TRUE;

				/* Decode buffer from client to get data, store into action_data.p_m2_change_hls_secret */
				if (R_DLMS_CLASSES_DecodeClass15UserEntry(action_data.p_m5_add_user, p_params->in_data) == 0)
				{
					OBIS_ACTION_RESULT(p_params->result, VAL_ACTION_RESULT_TYPE_UNMATCHED, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
					break;
				}
				else {
					p_params->service_params.decode_success = TRUE;
				}

				break;
#endif /* #if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2 */

			default:
				break;
		}
	}
}
