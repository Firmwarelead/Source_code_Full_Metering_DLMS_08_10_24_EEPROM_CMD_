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
* File Name    : r_dlms_class20.c
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
#include "r_dlms_class20.h"
#include "r_dlms_objects.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

VariantString *R_DLMS_CLASSES_RedirectClass20_Calender_Name(distributor_params_t *p_params, VariantString *p_object, uint16_t size)
{
	VariantString *p_clone;
	uint8_t * p_alloc, * p_head;

	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone, VariantString, p_alloc);
		OBIS_MALLOC_ASSIGN_VARIANT_STRING(p_clone, size, p_alloc);

		/* Check allocate */
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone = R_DLMS_CLASSES_RedirectVariantString(p_params, p_object, OBIS_MALLOC_OPTION_CREATENEW);
	}

	return p_clone;
}
/// Atrribute 3 Array of Season Profile Table
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass20_SeasonProfile, class20_season_profile_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 3);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, p_object->season_profile_name.p_content, p_object->season_profile_name.length);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)&p_object->season_start, sizeof(date_time_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, p_object->week_profile_name.p_content, p_object->week_profile_name.length);
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass20_SeasonProfile, class20_season_profile_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 3, in_data);
	{
		OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(length, &p_object->season_profile_name, TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->season_start, sizeof(date_time_t), TAG_DATA_OCTET_STRING, in_data);
		OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(length, &p_object->week_profile_name, TAG_DATA_OCTET_STRING, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}

class20_season_profile_array_t *R_DLMS_CLASSES_RedirectClass20_SeasonProfileTable(distributor_params_t *p_params, class20_season_profile_array_t *p_object, uint16_t size)
{
	class20_season_profile_array_t	*p_clone_obj;
	uint8_t							*p_alloc, *p_head;
	uint16_t						count;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);
	
	

	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class20_season_profile_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone_obj, size, class20_season_profile_t, p_alloc);
		for (count = 0; count < size; count++)
		{
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->p_content[count].season_profile_name, CLASS20_SUPPORT_MAX_SEASON_NAME, p_alloc);
			// DATE TIME no need
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->p_content[count].week_profile_name, CLASS20_SUPPORT_MAX_WEEK_NAME, p_alloc);
		}
		p_clone_obj->p_active = NULL;
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone_obj = (class20_season_profile_array_t *)R_DLMS_CLASSES_CreateVariantArray(
			p_params,
			(AbstractVariantArray *)p_object,
			sizeof(class20_season_profile_t),
			OBIS_MALLOC_OPTION_CREATENEW
		);
		ASSERT_TRUE_RET_NULL(p_clone_obj == NULL);
	}

	return p_clone_obj;

}

OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass20_SeasonProfileTable,
	class20_season_profile_array_t,
	R_DLMS_CLASSES_EncodeClass20_SeasonProfile
);

OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass20_SeasonProfileTable,
	class20_season_profile_array_t,
	R_DLMS_CLASSES_DecodeClass20_SeasonProfile
);

OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass20_SeasonProfileTable,
	class20_season_profile_array_t,
	R_DLMS_CLASSES_EncodeClass20_SeasonProfileTable,
	R_DLMS_CLASSES_DecodeClass20_SeasonProfileTable,
	R_DLMS_CLASSES_RedirectClass20_SeasonProfileTable
);



// Attribute 4 Array of week profile table
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass20_WeekProfile, class20_week_profile_table_t)
{
	uint16_t	count;
	uint16_t	decode_length;

	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 8);
	{
		decode_length = R_DLMS_CLASSES_EncodeOctetString(out_data, &p_object->week_profile_name);
		OBIS_ADVANCE_BUFFER(out_data, decode_length);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, &p_object->Monday, 1);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, &p_object->Tuesday, 1);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, &p_object->Wednesday, 1);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, &p_object->Thursday, 1);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, &p_object->Friday, 1);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, &p_object->Saturday, 1);
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, &p_object->Sunday, 1);
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass20_WeekProfile, class20_week_profile_table_t)
{
	uint16_t	count;
	uint16_t	decode_length;

	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 8, in_data);
	{
		decode_length = R_DLMS_CLASSES_DecodeOctetString( &p_object->week_profile_name, in_data);
		OBIS_ADVANCE_BUFFER(in_data, decode_length);
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, &p_object->Monday,		1, TAG_DATA_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, &p_object->Tuesday,		1, TAG_DATA_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, &p_object->Wednesday,		1, TAG_DATA_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, &p_object->Thursday,		1, TAG_DATA_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, &p_object->Friday,		1, TAG_DATA_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, &p_object->Saturday,		1, TAG_DATA_UNSIGNED, in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, &p_object->Sunday,		1, TAG_DATA_UNSIGNED, in_data);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}


class20_week_profile_table_array_t *R_DLMS_CLASSES_RedirectClass20_WeekProfileTable(distributor_params_t *p_params, class20_week_profile_table_array_t *p_object, uint16_t size)
{
	class20_week_profile_table_array_t	*p_clone_obj;
	VariantString						*p_clone, *p_src;
	uint8_t								offsets[4];
	uint8_t								*p_alloc, *p_head;
	uint16_t							count, i;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);

	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class20_week_profile_table_array_t, p_alloc);
		
		OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone_obj, size, class20_week_profile_table_t, p_alloc);
		for (i = 0; i < size; i++)
		{
			OBIS_MALLOC_ASSIGN_VARIANT_STRING(&p_clone_obj->p_content[i].week_profile_name, CLASS20_SUPPORT_MAX_LENGTH_WEEK_NAME, p_alloc);
		}
		p_clone_obj->p_active = NULL;

		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone_obj = (class20_week_profile_table_array_t *)R_DLMS_CLASSES_CreateVariantArray(
			p_params,
			(AbstractVariantArray *)p_object,
			sizeof(class20_week_profile_table_array_t),
			OBIS_MALLOC_OPTION_CREATENEW
		);
		ASSERT_TRUE_RET_NULL(p_clone_obj == NULL);

		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
		for (count = 0; count < p_object->alloc_size; count++) {
			p_clone_obj->p_content[count].week_profile_name = *((VariantString *)R_DLMS_CLASSES_CreateVariantString(
				p_params,
				(VariantString *)&p_object->p_content[count].week_profile_name,
				OBIS_MALLOC_OPTION_CREATENEW |
				OBIS_MALLOC_OPTION_CLONE |
				OBIS_MALLOC_OPTION_MEMLINK
			));

		}
	}

	return p_clone_obj;

}

OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass20_WeekProfileTable,
	class20_week_profile_table_array_t,
	R_DLMS_CLASSES_EncodeClass20_WeekProfile
);

OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass20_WeekProfileTable,
	class20_week_profile_table_array_t,
	R_DLMS_CLASSES_DecodeClass20_WeekProfile
);

OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass20_WeekProfileTable,
	class20_week_profile_table_array_t,
	R_DLMS_CLASSES_EncodeClass20_WeekProfileTable,
	R_DLMS_CLASSES_DecodeClass20_WeekProfileTable,
	R_DLMS_CLASSES_RedirectClass20_WeekProfileTable
);



/// Attribute 5 Array of Day profile table
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass20_DayProfile, class20_day_profile_table_t)
{
	uint16_t	count;
	class20_day_profile_action_t * p_action;

	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(u16, out_data, TAG_DATA_UNSIGNED, &p_object->day_id, 1);
		OBIS_ENCODE_ARRAY_TYPE_DEF(u8, out_data, p_object->day_schedule.length);
		for (count = 0; count < p_object->day_schedule.length; count++) {
			p_action = p_object->day_schedule.p_content + count;
			OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 3);
			{
				OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)&p_action->start_time, sizeof(time_t));
				OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_OCTET_STRING, (uint8_t *)&p_action->script_logical_name, 6);
				OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, (uint8_t *)&p_action->script_selector, sizeof(uint16_t));
			}
		}
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass20_DayAction, class20_day_profile_action_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 3, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_object->start_time, 			sizeof(time_t),			TAG_DATA_OCTET_STRING, 	in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_object->script_logical_name, 	6,						TAG_DATA_OCTET_STRING, 	in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_object->script_selector, 		sizeof(uint16_t), 		TAG_DATA_LONG_UNSIGNED, in_data);
	}
	OBIS_TYPE_DECODER_FUNC_RET();
}

OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass20_DayActionTable,
	class20_day_profile_action_array_t,
	R_DLMS_CLASSES_DecodeClass20_DayAction
);

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass20_DayProfile, class20_day_profile_table_t)
{
	uint16_t	count;
	class20_day_profile_action_t * p_action;
	uint16_t	u16_length;

	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(u16, (uint8_t *)&p_object->day_id, 2 , TAG_DATA_UNSIGNED, in_data);
		u16_length = R_DLMS_CLASSES_DecodeClass20_DayActionTable(
			&p_object->day_schedule,
			in_data
		);
		OBIS_ADVANCE_BUFFER(in_data, u16_length);
	}

	OBIS_TYPE_DECODER_FUNC_RET();
}

OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass20_DayProfileTable,
	class20_day_profile_table_array_t,
	R_DLMS_CLASSES_EncodeClass20_DayProfile
);

OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass20_DayProfileTable,
	class20_day_profile_table_array_t,
	R_DLMS_CLASSES_DecodeClass20_DayProfile
);

class20_day_profile_table_array_t *R_DLMS_CLASSES_RedirectClass20_DayProfileTable(distributor_params_t *p_params, class20_day_profile_table_array_t *p_object, uint16_t size_day_profile_table, uint16_t size_max_day_schedule)
{
	class20_day_profile_table_array_t	*p_clone_obj;
	uint8_t								*p_alloc, *p_head;
	uint16_t							count, i;

	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);

	if (p_object == NULL)
	{
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class20_day_profile_table_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone_obj, size_day_profile_table, class20_day_profile_table_t, p_alloc);
		for (i = 0; i < size_day_profile_table; i++)
		{
			OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(&p_clone_obj->p_content[i].day_schedule, size_max_day_schedule, class20_day_profile_action_t, p_alloc);
			p_clone_obj->p_content[i].day_schedule.p_active = NULL;
		}
		p_clone_obj->p_active = NULL;
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone_obj = (class20_day_profile_table_array_t *)R_DLMS_CLASSES_CreateFixedArray(
			p_params,
			(AbstractFixedArray *)p_object,
			sizeof(class20_day_profile_table_t),
			OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE
		);
	}

	return p_clone_obj;

}
class20_day_profile_table_array_t *R_DLMS_CLASSES_RedirectClass20_DayProfileTable_EstimateDayScheduleSize(distributor_params_t *p_params, class20_day_profile_table_array_t *p_object, uint16_t size_day_profile_table)
{
	class20_day_profile_table_array_t	*p_clone_obj;
	uint8_t								*p_alloc, *p_head;
	uint16_t							count, i;
	uint16_t							max_schedule_array_size;
	uint16_t a =sizeof(class20_day_profile_action_t);
	ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);

	if (p_object == NULL)
	{
		max_schedule_array_size = OBIS_MALLOC_REMAIN_SIZE(p_params);
		p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
		OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class20_day_profile_table_array_t, p_alloc);
		OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone_obj, size_day_profile_table, class20_day_profile_table_t, p_alloc);
		max_schedule_array_size += (uint16_t)p_head;
		max_schedule_array_size -= (uint16_t)p_alloc;
        max_schedule_array_size -= (size_day_profile_table % 2) + size_day_profile_table;
		max_schedule_array_size = max_schedule_array_size/(sizeof(class20_day_profile_action_t) + 1);
		max_schedule_array_size = max_schedule_array_size/size_day_profile_table;
		for (i = 0; i < size_day_profile_table; i++)
		{
			OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(&p_clone_obj->p_content[i].day_schedule, max_schedule_array_size, class20_day_profile_action_t, p_alloc);
			p_clone_obj->p_content[i].day_schedule.p_active = NULL;
		}
		p_clone_obj->p_active = NULL;
		ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
		OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
	}
	else
	{
		p_clone_obj = (class20_day_profile_table_array_t *)R_DLMS_CLASSES_CreateFixedArray(
			p_params,
			(AbstractFixedArray *)p_object,
			sizeof(class20_day_profile_table_t),
			OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE
		);
	}

	return p_clone_obj;

}
OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass20_DayProfileTable,
	class20_day_profile_table_array_t,
	R_DLMS_CLASSES_EncodeClass20_DayProfileTable,
	R_DLMS_CLASSES_DecodeClass20_DayProfileTable,
    R_DLMS_CLASSES_RedirectClass20_DayProfileTable_EstimateDayScheduleSize
);

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class20Init
* Interface     : void R_DLMS_CLASSES_Class20Init(void)
* Description   : Initialize class 20
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class20Init(void)
{
	/* Put init code of class 20 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class20PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class20PollingProcessing(void)
* Description   : Polling process of class 20
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class20PollingProcessing(void)
{
	/* Put polling processing code of class 20 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class20AsscOpened
* Interface     : void R_DLMS_CLASSES_Class20AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 20
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class20AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 20 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class20AsscClosing
* Interface     : void R_DLMS_CLASSES_Class20AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 20
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class20AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 20 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass20
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass20(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 20
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass20(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass20,
		R_DLMS_OBJECTS_Class20Distributor,
		p_params
	);
}


/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass20
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass20(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 20
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass20(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class20_child_record_t	*p_class20_obj = (class20_child_record_t *)p_params->p_child_record;
	
	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
			//  1. logical_name(static) octet - string					
			//	2. calendar_name_active(static) octet - string
			//	3. season_profile_active(static) array
			//	4. week_profile_table_active(static) array
			//	5. day_profile_table_active(static) array
			//	6. calendar_name_passive(static) octet - string
			//	7. season_profile_passive(static) array
			//	8. week_profile_table_passive(static) array
			//	9. day_profile_table_passive(static) array
			//	10. activate_passive_calendar_time(static) octet - string

            /* TODO : Put process code for each attrs of class 20 here, start from attr2 */
			case 2: /* calendar_name_active */
				R_DLMS_CLASSES_DistributeVariantString(p_params, TAG_DATA_OCTET_STRING, p_class20_obj->p_calendar_name_active);
				break;
			case 3: /* season_profile_active */
				R_DLMS_CLASSES_DistributeClass20_SeasonProfileTable(p_params, p_class20_obj->p_season_profile_active);
				break;
			case 4: /* week_profile_table_active */
				R_DLMS_CLASSES_DistributeClass20_WeekProfileTable(p_params, p_class20_obj->p_week_profile_table_active);
				break;
			case 5: /* day_profile_table_active */
				R_DLMS_CLASSES_DistributeClass20_DayProfileTable(p_params, p_class20_obj->p_day_profile_table_active);
				break;

			case 6: /* calendar_name_passive */
				R_DLMS_CLASSES_DistributeVariantString(p_params, TAG_DATA_OCTET_STRING, p_class20_obj->p_calendar_name_passive);
				break;
			case 7: /* season_profile_passive */
				R_DLMS_CLASSES_DistributeClass20_SeasonProfileTable(p_params, p_class20_obj->p_season_profile_passive);
				break;
			case 8: /* week_profile_table_passive */
				R_DLMS_CLASSES_DistributeClass20_WeekProfileTable(p_params, p_class20_obj->p_week_profile_table_passive);
				break;
			case 9: /* day_profile_table_passive */
				R_DLMS_CLASSES_DistributeClass20_DayProfileTable(p_params, p_class20_obj->p_day_profile_table_passive);
				break;

			case 10: /* activate_passive_calendar_time */
				R_DLMS_CLASSES_DistributeDateTimeAsOctetString(p_params, p_class20_obj->p_activate_passive_calendar_time);
				break;

			default:
				break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
        switch (p_params->descriptor.method.method_id)
		{
            /* TODO : Put process code for each method of class 20 here, start from method1 */
			case 1:	
				break;

			default:
				break;
		}
	}
}
