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
* File Name    : r_dlms_usercode_class07.c
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

#include <string.h>
#include <stddef.h>
#include "r_dlms_usercode_class07.h"
#include "r_dlms_class03.h"
#include "r_dlms_class04.h"

/* User application */
#include "r_loadsurvey.h"
#include "r_dlms_app.h"
#include "event.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

typedef struct tag_class07_obj_frame_format_t
{
	uint8_t		tag;
	uint16_t	p_offset;
	uint16_t	size;
} class07_obj_frame_format_t;

typedef struct tag_class07_obj_one_entry_descriptor_t
{
	uint8_t 					*p_data;
	class07_obj_frame_format_t 	*p_frame_format;
	uint16_t					frame_format_size;
	uint16_t					from_value;
	uint16_t					to_value;
	uint64_t					column_selected;
	uint16_t 					*p_encoded_value_index;
	uint8_t (* fn_buff_fill)(uint16_t, uint16_t , void*);
	void (* fn_by_range_filter)(class07_range_descriptor_t*, uint16_t* , uint16_t*, uint16_t*);
} class07_obj_one_entry_descriptor_t;

typedef struct tag_Billing_profile_Obj00_DLMSEntry_t
{
	uint8_t billing_date_import_mode[12];
	float32_t average_power_factor_for_billing_period;
	float32_t cumulative_energy_kwh_import;
	float32_t cumulative_energy_kwh_for_tz1;
	float32_t cumulative_energy_kwh_for_tz2;
	float32_t cumulative_energy_kwh_for_tz3;
	float32_t cumulative_energy_kwh_for_tz4;
	float32_t cumulative_energy_kwh_for_tz5;
	float32_t cumulative_energy_kwh_for_tz6;
	float32_t cumulative_energy_kvah_import;
	float32_t cumulative_energy_kvah_for_tz1;
	float32_t cumulative_energy_kvah_for_tz2;
	float32_t cumulative_energy_kvah_for_tz3;
	float32_t cumulative_energy_kvah_for_tz4;
	float32_t cumulative_energy_kvah_for_tz5;
	float32_t cumulative_energy_kvah_for_tz6;
	float32_t max_demand_kw;
	date_time_t max_demand_kw_capture_time;
	float32_t max_demand_kva;
	date_time_t max_demand_kva_capture_time;
	uint32_t billing_power_on_duration_in_mins;
	float32_t cummulative_energy_kwh_export;
	float32_t cummulative_energy_kvah_export;

} Billing_profile_Obj00_DLMSEntry_t;

typedef struct tag_Block_Load_Profile_Obj02_DLMSEntry_t
{
	date_time_t date_and_time;
	float32_t average_voltage;
	float32_t block_energy_kwh_import;
	float32_t block_energy_kvah_import;
	float32_t block_energy_kwh_export;
	float32_t block_energy_kvah_export;
	float32_t average_current;

} Block_Load_Profile_Obj02_DLMSEntry_t;

typedef struct tag_Daily_Load_Profile_Obj04_DLMSEntry_t
{
	date_time_t date_and_time;
	float32_t cumulative_energy_kwh_export;
	float32_t cumulative_energy_kvah_export;
	float32_t cumulative_energy_kwh_import;
	float32_t cumulative_energy_kvah_import;

} Daily_Load_Profile_Obj04_DLMSEntry_t;

typedef struct tag_Event_profile_Control_Obj07_DLMSEntry_t
{
	date_time_t date_and_time_of_event;
	uint16_t event_code;

} Event_profile_Control_Obj07_DLMSEntry_t;

typedef struct tag_Event_profile_Current_Obj08_DLMSEntry_t
{
	date_time_t date_and_time_of_event;
	uint16_t event_code;
	float32_t current;
	float32_t voltage;
	float32_t power_factor;
	float32_t cumulative_energy_kwh;
	uint32_t cumulative_tamper_count;

} Event_profile_Current_Obj08_DLMSEntry_t;

typedef struct tag_Event_profile_non_roll_over_Obj09_DLMSEntry_t
{
	date_time_t date_and_time_of_event;
	uint16_t event_code;

} Event_profile_non_roll_over_Obj09_DLMSEntry_t;

typedef struct tag_Event_profile_Other_Obj10_DLMSEntry_t
{
	date_time_t date_and_time_of_event;
	uint16_t event_code;
	float32_t current;
	float32_t voltage;
	float32_t power_factor;
	float32_t cumulative_energy_kwh;
	uint32_t cumulative_tamper_count;

} Event_profile_Other_Obj10_DLMSEntry_t;

typedef struct tag_Event_profile_Power_Obj11_DLMSEntry_t
{
	date_time_t date_and_time_of_event;
	uint16_t event_code;

} Event_profile_Power_Obj11_DLMSEntry_t;

typedef struct tag_Event_profile_Trans_Obj12_DLMSEntry_t
{
	date_time_t date_and_time_of_event;
	uint16_t event_code;

} Event_profile_Trans_Obj12_DLMSEntry_t;

typedef struct tag_Event_profile_Voltage_Obj13_DLMSEntry_t
{
	date_time_t date_and_time_of_event;
	uint16_t event_code;
	float32_t current;
	float32_t voltage;
	float32_t power_factor;
	float32_t cumulative_energy_kwh;
	uint32_t cumulative_tamper_count;

} Event_profile_Voltage_Obj13_DLMSEntry_t;

typedef struct tag_event_params_short
{
	date_time_t date_and_time;
	uint16_t event_code;

} st_common_event_params_short_t;

typedef struct tag_tag_event_params_long
{
	date_time_t date_and_time;
	uint16_t event_code;
	float32_t current;
	float32_t voltage;
	float32_t power_factor;
	float32_t cumulative_energy_kwh;
	uint32_t cumulative_tamper_count;
} st_common_event_params_long_t;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/* User code variable */


/* User code function */
uint8_t R_DLMS_USER_ic07_obj00_att02_CopyToBuffer_UserCode(uint16_t child_index, uint16_t entry_index, void * p_entry_buf);
/* Common function for this class */
uint8_t COLUMN_CHECK_BIT_VALUE_CLASS07(uint64_t array_bit, uint8_t bit_position);
void COLUMN_SET_BIT(uint8_t *p_array_of_bits, uint16_t len, uint16_t bit_position);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_Encode_OneEntry_Class07, class07_obj_one_entry_descriptor_t);
uint16_t R_DLMS_CLASSES_Distribute_OneEntry_Class07(distributor_params_t *p_params, class07_obj_one_entry_descriptor_t *p_object);
void R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(distributor_params_t *p_params, uint16_t entries_in_used, class07_obj_one_entry_descriptor_t *p_descriptor);
/* Get, set, action user function */

void R_MakeBuffer_RealTime_SupportBlockTransfer_Class07(distributor_params_t *p_params);

uint8_t R_DLMS_USER_ic07_obj02_att02_CopyToBuffer_UserCode(uint16_t child_index, uint16_t entry_index, void * p_entry_buf);

uint8_t R_DLMS_USER_ic07_obj04_att02_CopyToBuffer_UserCode(uint16_t child_index, uint16_t entry_index, void * p_entry_buf);

uint8_t R_DLMS_USER_ic07_obj07_att02_CopyToBuffer_UserCode(uint16_t child_index, uint16_t entry_index, void * p_entry_buf);

uint8_t R_DLMS_USER_ic07_obj08_att02_CopyToBuffer_UserCode(uint16_t child_index, uint16_t entry_index, void * p_entry_buf);

uint8_t R_DLMS_USER_ic07_obj09_att02_CopyToBuffer_UserCode(uint16_t child_index, uint16_t entry_index, void * p_entry_buf);

uint8_t R_DLMS_USER_ic07_obj10_att02_CopyToBuffer_UserCode(uint16_t child_index, uint16_t entry_index, void * p_entry_buf);

uint8_t R_DLMS_USER_ic07_obj11_att02_CopyToBuffer_UserCode(uint16_t child_index, uint16_t entry_index, void * p_entry_buf);

uint8_t R_DLMS_USER_ic07_obj12_att02_CopyToBuffer_UserCode(uint16_t child_index, uint16_t entry_index, void * p_entry_buf);

uint8_t R_DLMS_USER_ic07_obj13_att02_CopyToBuffer_UserCode(uint16_t child_index, uint16_t entry_index, void * p_entry_buf);


/******************************************************************************
Private global variables and functions
******************************************************************************/
/**********************************************************************
***********************************************************************
*******************     PRIVATE GLOBAL VARIABLES       ****************
***********************************************************************
***********************************************************************
* Declare detail value to assign to Exported global variables if      *
* that is complex data type (struct or array)                         *
**********************************************************************/

/**********************************************************************************************************************
 * Function Name: event_short_params_get      
 * Description  : this is common function to get data of event contains date time and event code(short event params)
 * Arguments    : event_type - type event would like to get data
 *                entry_index - entry index would like to get data
 *                p_output - pointer of parameters need to get   
 * Return Value : void                     
 **********************************************************************************************************************/
 static void event_short_params_get(EVENT_TYPE_T event_type,
                                    uint16_t entry_index,
								    st_common_event_params_short_t * p_output)
 {
	EVENT_PARAMS_T   event_parameters;
	/* Get event record from event application */
	event_parameters = R_EVENT_GetEntry(event_type, entry_index);
	/* Pass data for date time - using convert date time format from RTC to DLMS date time */
	R_DLMS_RTC_Convert_RTC2DateTime2(&p_output->date_and_time, (rtc_counter_value_t *)&event_parameters.captured_time);
	/* Pass event code */
	p_output->event_code = event_parameters.code;
 }

 /**********************************************************************************************************************
 * Function Name: event_long_params_get      
 * Description  : this is common function to get data of event contains date time and event code(short event params)
 * Arguments    : event_type - type event would like to get data
 *                entry_index - entry index would like to get data
 *                p_output - pointer of parameters need to get   
 * Return Value : void                     
 **********************************************************************************************************************/
 static void event_long_params_get(EVENT_TYPE_T event_type, uint16_t entry_index, 
                                  st_common_event_params_long_t * p_output)
 {
	EVENT_PARAMS_T   event_parameters;
	/* Get event record from event application */
	event_parameters = R_EVENT_GetEntry(event_type, entry_index);
	/* Pass data for date time - using convert date time format from RTC to DLMS date time */
	R_DLMS_RTC_Convert_RTC2DateTime2(&p_output->date_and_time, (rtc_counter_value_t *)&event_parameters.captured_time);
	/* Pass event code */
	p_output->event_code = event_parameters.code;
	/* Pass event energy params */
	p_output->current = event_parameters.current;
	p_output->voltage = event_parameters.voltage;
	p_output->power_factor = event_parameters.PF;
	p_output->cumulative_energy_kwh = event_parameters.ActiveEnergyImport;
	p_output->cumulative_tamper_count = event_parameters.TamperCounter;
 }

/******************************************************************************
* Function Name : R_DLMS_CompareDateTime
* Description   : 
* Arguments     : date_time_t timeA - time input A,
                  date_time_t timeB - time input B,
* Return Value  : int8_t -     +1: timeA > timeB, 0: timeA = timeB, -1: timeA < timeB
******************************************************************************/
static int8_t R_DLMS_CompareDateTime(date_time_t timeA, date_time_t timeB)
{
	uint8_t * p_timeA = (uint8_t *)&timeA;
	uint8_t * p_timeB = (uint8_t *)&timeB;
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		if(i==4)
		{
			continue;
		}
		if(p_timeA[i] < p_timeB[i])
		{
			/* time A < time B at element i => time A < time B */
			return -1;
		}
		else if(p_timeA[i] > p_timeB[i])
		{
			/* time A > time B at element i => time A > time B */
			return 1;
		}
		else
		{
			/* Continue check if element of time A and B equal */
		}
	}
	return 0;
}

uint8_t g_is_use_column_selected = FALSE;

uint8_t COLUMN_CHECK_BIT_VALUE_CLASS07 (
	uint64_t array_bit, uint8_t bit_position
)
{
	uint8_t *p_array_of_bits = (uint8_t *)(void *)&array_bit;
	uint16_t array_len = sizeof(uint64_t);
	
	if (bit_position > array_len * 8)
	{
		return 0;
	}

	return p_array_of_bits[bit_position/8] & (1<<(bit_position%8));
}

void COLUMN_SET_BIT(uint8_t *p_array_of_bits, uint16_t len, uint16_t bit_position)
{
	if (bit_position < len * 8)
	{
		p_array_of_bits[bit_position/8] |= (1<<(bit_position%8));
	}
}



OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_Encode_OneEntry_Class07, class07_obj_one_entry_descriptor_t)
{
	uint8_t * p_entry_data;
	uint16_t value_pos;
	uint8_t number_element = 0;
	uint64_t column_selected;
	uint16_t count_encoded = 0;


	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	column_selected = p_object->column_selected;
	/* Structure, 3 elements */
	/* Check if the current encoded element is from value, we need to encode header of structure buffer first */
	/* Else the last encode for one entry have not finished yet, continue encoding, no open header for structure */
	if(*p_object->p_encoded_value_index == p_object->from_value)
	{
		/* For encoding header maybe we need 3 byte(if length > 255) => we reserve for 3 that make sure encode successfully */
		if(out_data.length < 3)
		{
			return 0;
		}
		for (value_pos = p_object->from_value; value_pos <= p_object->to_value; value_pos++)
		{
			if ((g_is_use_column_selected == FALSE) || COLUMN_CHECK_BIT_VALUE_CLASS07(column_selected, value_pos ))
			{
				number_element++;
			}
		}
		OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, number_element );

	}
	{
		for ( value_pos = *p_object->p_encoded_value_index; value_pos <= p_object->to_value; value_pos++ )
		{
			if ((g_is_use_column_selected == FALSE) || COLUMN_CHECK_BIT_VALUE_CLASS07(column_selected, value_pos ))
			{
				/* 
				* To encode one element we need 1 byte tag + (0 or 1 or 2) bytes for length + value size bytes value,
				* so we need (3(tag + length) + value size) bytes for encode 
				*/
				if(out_data.length > (p_object->p_frame_format[value_pos].size + 3))
				{
					p_entry_data = (uint8_t *)p_object->p_data + p_object->p_frame_format[value_pos].p_offset;
					OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, (Data_Tag)p_object->p_frame_format[value_pos].tag, p_entry_data, p_object->p_frame_format[value_pos].size);
					count_encoded++;
				}
				else
				{
					/* If the first element have not encoded, return 0 to pass to next that header of structure will encode together with first element*/
					if(count_encoded != 0)
					{
						break;
					}
					else
					{
						return 0;
					}
					
				}
				
			}
		}
		*p_object->p_encoded_value_index = value_pos;

	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

uint16_t R_DLMS_CLASSES_Distribute_OneEntry_Class07(distributor_params_t *p_params, class07_obj_one_entry_descriptor_t *p_object)
{
	uint16_t u16_length = 0;

	if (p_params == NULL ||
		p_object == NULL)
		{
			return u16_length;
		}
	
	if (p_params->req_type == REQ_TYPE_GET)
	{
		u16_length = R_DLMS_CLASSES_Encode_OneEntry_Class07(p_params->out_data, p_object);
		/* out_data need to update */
		p_params->out_data.length -= u16_length; 
		p_params->out_data.p_content += u16_length;
	}
		
	return u16_length;
	
}

/* Below variable is created to support async block transfer and simultaneous connect of 2 channel
 * 
 * Simultaneous connections are:
 *      HDLC Assc 32, TCP/UDP Assc 48 or
 *      HDLC Assc 48, TCP/UDP Assc 32
*/

typedef struct tag_st_usercode_class07_block_transfer_data_t
{
    uint16_t current_obj;
    uint16_t current_element;
    uint16_t total_obj;
    uint16_t from_entry;
    uint16_t to_entry;
    uint16_t from_value;
    uint16_t to_value;
    uint64_t column_sel;
    uint8_t is_use_col_sel;
    uint8_t block_transfer;
} st_usercode_class07_block_transfer_data_t;

/* To support async block transfer */
st_usercode_class07_block_transfer_data_t async_transfer_data[DLMS_MAX_ASSOCIATION_SUPPORT];

/******************************************************************************
* Function Name : R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07
* Interface     : void R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07 (
* distributor_params_t					*p_params,
* uint16_t								entries_in_used,
* class07_obj_one_entry_descriptor_t	*p_descriptor)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
	distributor_params_t				*p_params,
	uint16_t							entries_in_used,
	class07_obj_one_entry_descriptor_t	*p_descriptor
)
{
	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
	uint8_t i, j ;
	uint8_t *p_head;
	class07_child_record_t	*p_class07_obj = (class07_child_record_t *)p_params->p_child_record;

	class07_obj_def_t *p_capture_obj_meter;
	class07_obj_def_t *p_capture_obj_req;

	/* To support selective access */
	class07_entry_descriptor_t *p_entry_descriptor;
	class07_range_descriptor_t *p_range_descriptor;

	date_time_t from_date_time;
	date_time_t to_date_time;

	uint16_t total_entries;

	p_head = p_params->out_data.p_content;

	if (p_params->service_type.get == COSEM_GET_REQUEST_NORMAL)
	{
		if ( p_params->selective_access.use == TRUE )
		{
			if (p_params->service_params.decode_success != TRUE)
			{
				return;
			}
			if ( p_params->selective_access.access_selector == 1)			/* range_descriptor */
			{
				p_range_descriptor = (class07_range_descriptor_t *)(void *)p_params->service_params.malloc.p_content;
			
				p_descriptor->fn_by_range_filter (
					p_range_descriptor,
					&async_transfer_data[p_params->connected_assc_id].from_entry, 
					&async_transfer_data[p_params->connected_assc_id].to_entry,
					&total_entries
				);

				async_transfer_data[p_params->connected_assc_id].column_sel = 0;
				if (p_range_descriptor->p_array_selected_value->length == 0)
				{
					async_transfer_data[p_params->connected_assc_id].is_use_col_sel = FALSE;
				}
				else
				{
					async_transfer_data[p_params->connected_assc_id].is_use_col_sel = TRUE;
					for (i = 0; i < p_class07_obj->p_capture_objects->length; i++)
					{
						p_capture_obj_meter = &p_class07_obj->p_capture_objects->p_content[i];
						for (j = 0; j < p_range_descriptor->p_array_selected_value->length; j++)
						{
							p_capture_obj_req = &p_range_descriptor->p_array_selected_value->p_content[j];
							if (p_capture_obj_meter->class_id == p_capture_obj_req->class_id)
							if (p_capture_obj_meter->data_index == p_capture_obj_req->data_index)
							if (p_capture_obj_meter->attribute_index == p_capture_obj_req->attribute_index)
							if (memcmp(p_capture_obj_req->logical_name.p_content, p_capture_obj_meter->logical_name.p_content, 6) == 0)
							{
								COLUMN_SET_BIT((uint8_t *)(void *)&async_transfer_data[p_params->connected_assc_id].column_sel, sizeof(uint64_t), i);
								break;
							}
						}
					}
				}

				async_transfer_data[p_params->connected_assc_id].from_value = 0;
				async_transfer_data[p_params->connected_assc_id].to_value = 0;
			}
			else//By entry
			{
				p_entry_descriptor = (class07_entry_descriptor_t *)(void *)p_params->service_params.malloc.p_content;
				async_transfer_data[p_params->connected_assc_id].from_entry = p_entry_descriptor->from_entry;
				async_transfer_data[p_params->connected_assc_id].from_value = p_entry_descriptor->from_value;
				async_transfer_data[p_params->connected_assc_id].to_entry = p_entry_descriptor->to_entry;
				async_transfer_data[p_params->connected_assc_id].to_value = p_entry_descriptor->to_value;
				async_transfer_data[p_params->connected_assc_id].is_use_col_sel = FALSE;
                
                if (((async_transfer_data[p_params->connected_assc_id].from_entry > async_transfer_data[p_params->connected_assc_id].to_entry) && 
                     (async_transfer_data[p_params->connected_assc_id].to_entry != 0)) || 
                     (entries_in_used == 0))
				{
					async_transfer_data[p_params->connected_assc_id].total_obj = 0;
					total_entries = 0;
				}
				else
				{
					async_transfer_data[p_params->connected_assc_id].total_obj = entries_in_used - async_transfer_data[p_params->connected_assc_id].from_entry + 1;
					if (async_transfer_data[p_params->connected_assc_id].total_obj > entries_in_used)
					{
						async_transfer_data[p_params->connected_assc_id].total_obj = entries_in_used;
					}
					total_entries = async_transfer_data[p_params->connected_assc_id].total_obj;
				}
			}
			
			/* entries_descriptor */
			{
				if (async_transfer_data[p_params->connected_assc_id].to_value == 0)
				{
					async_transfer_data[p_params->connected_assc_id].to_value = p_descriptor->frame_format_size;
				}
				if (((async_transfer_data[p_params->connected_assc_id].to_entry == 0) && (p_params->selective_access.access_selector == 2)) || 
                    (async_transfer_data[p_params->connected_assc_id].to_entry > entries_in_used))
				{
					async_transfer_data[p_params->connected_assc_id].to_entry = entries_in_used;
				}

				DECREASE_SELECTIVE_VALUE(async_transfer_data[p_params->connected_assc_id].from_value);
				DECREASE_SELECTIVE_VALUE(async_transfer_data[p_params->connected_assc_id].to_value);
				if ( p_params->selective_access.access_selector == 2 )
				{
					DECREASE_SELECTIVE_VALUE(async_transfer_data[p_params->connected_assc_id].from_entry);
					DECREASE_SELECTIVE_VALUE(async_transfer_data[p_params->connected_assc_id].to_entry);
				}


				if (total_entries == 0)
				{
                    async_transfer_data[p_params->connected_assc_id].current_obj = 0xFFFF;
					async_transfer_data[p_params->connected_assc_id].total_obj = 0;
				}
                else
                {
					async_transfer_data[p_params->connected_assc_id].total_obj = async_transfer_data[p_params->connected_assc_id].to_entry - async_transfer_data[p_params->connected_assc_id].from_entry + 1;
                    async_transfer_data[p_params->connected_assc_id].current_obj = async_transfer_data[p_params->connected_assc_id].from_entry;
                }
			}
		}
		else
		{
			async_transfer_data[p_params->connected_assc_id].current_obj = 0;
			async_transfer_data[p_params->connected_assc_id].total_obj = entries_in_used;
			async_transfer_data[p_params->connected_assc_id].to_entry = entries_in_used;
			async_transfer_data[p_params->connected_assc_id].from_entry = 0;
			async_transfer_data[p_params->connected_assc_id].to_value = p_descriptor->frame_format_size;
			async_transfer_data[p_params->connected_assc_id].from_value = 0;
			async_transfer_data[p_params->connected_assc_id].is_use_col_sel = FALSE;

			if (entries_in_used == 0) 
			{
				async_transfer_data[p_params->connected_assc_id].current_obj = 0xFFFF;
			}
			
			DECREASE_SELECTIVE_VALUE(async_transfer_data[p_params->connected_assc_id].to_entry);
			DECREASE_SELECTIVE_VALUE(async_transfer_data[p_params->connected_assc_id].to_value);
		}

		async_transfer_data[p_params->connected_assc_id].current_element = async_transfer_data[p_params->connected_assc_id].from_value;
		OBIS_DIST_ENCODE_ARRAY_TYPE_DEF(u8, p_params->out_data, async_transfer_data[p_params->connected_assc_id].total_obj);
	}
    else
    {
		
    }

	p_descriptor->from_value = async_transfer_data[p_params->connected_assc_id].from_value;
	p_descriptor->to_value = async_transfer_data[p_params->connected_assc_id].to_value;
	p_descriptor->column_selected = async_transfer_data[p_params->connected_assc_id].column_sel;
	p_descriptor->p_encoded_value_index = &async_transfer_data[p_params->connected_assc_id].current_element;
	while(async_transfer_data[p_params->connected_assc_id].current_obj <= async_transfer_data[p_params->connected_assc_id].to_entry)
	{

		p_descriptor->fn_buff_fill(p_params->child_index ,async_transfer_data[p_params->connected_assc_id].current_obj, (void *)p_descriptor->p_data);
        g_is_use_column_selected = async_transfer_data[p_params->connected_assc_id].is_use_col_sel;
		u16 = R_DLMS_CLASSES_Distribute_OneEntry_Class07(p_params, p_descriptor);
		if(async_transfer_data[p_params->connected_assc_id].current_element > async_transfer_data[p_params->connected_assc_id].to_value)
		{
			async_transfer_data[p_params->connected_assc_id].current_element = async_transfer_data[p_params->connected_assc_id].from_value;
		}
		else
		{
			break;
		}
		async_transfer_data[p_params->connected_assc_id].current_obj++;
	}

	// RETURN
	if (async_transfer_data[p_params->connected_assc_id].current_obj <= async_transfer_data[p_params->connected_assc_id].to_entry)
	{
		*p_params->p_out_encoded_len = (uint16_t)(p_params->out_data.p_content - p_head);
		if (*p_params->p_out_encoded_len > 0) {
			OBIS_DATA_ACCESS_RESULT( p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, TRUE );
			OBIS_DISTRIBUTION_SUCCESS(p_params->result);
		}
	}
	else
	{
		*p_params->p_out_encoded_len = (uint16_t)(p_params->out_data.p_content - p_head);
		if (*p_params->p_out_encoded_len > 0) {
			OBIS_DATA_ACCESS_RESULT( p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, FALSE );
			OBIS_DISTRIBUTION_SUCCESS(p_params->result);
		}
		async_transfer_data[p_params->connected_assc_id].current_obj = 0;
		async_transfer_data[p_params->connected_assc_id].total_obj = 0;
	}
}

/******************************************************************************
* Function Name : R_MakeBuffer_RealTime_SupportBlockTransfer_Class07
* Interface     : void R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(distributor_params_t *p_params)
* Description   : use for encode realtime data capture objects  buffer.
* Arguments     : distributor_params_t *p_params
* Return Value  : void
******************************************************************************/
void R_MakeBuffer_RealTime_SupportBlockTransfer_Class07(distributor_params_t *p_params)
{
	/* Common vars for OBIS encoders macros */
	uint8_t		u8;
	uint16_t	u16;
	/* Pointer to the prepared buffer (APDU) from r_dlms_classes.c (malloc), to do direct encoding */
	uint8_t		*p_head;

	/* For selective access (client extra request), for filtering */

	class07_entry_descriptor_t	*p_entry_descriptor;
	class07_range_descriptor_t	*p_range_descriptor;

	/* Point to the current class 07 object that request to get "buffer" attr  */
	class07_child_record_t	*p_class07_obj = (class07_child_record_t *)p_params->p_child_record;

	if (p_params == NULL)
	{
		/* "ScopeAccessViolated" error is returned to Client */
		OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE, FALSE);
		OBIS_DISTRIBUTION_FAILED(p_params->result);
		return;	/* System error or no entry to get buffer */
	}

	/* Point to the prepared buffer (APDU) from r_dlms_classes.c (malloc) */
	p_head = p_params->out_data.p_content;

	/* Get request normal called? */
	if (p_params->service_type.get == COSEM_GET_REQUEST_NORMAL)
	{
		/*
		* In default,
		*   From first data index (0), to max data index (p_class07_obj->p_capture_objects->length - 1)
		*   From entry 0 to last entry in used, index start at 0
		*   No block transfer
		*/
		async_transfer_data[p_params->connected_assc_id].from_value = 0;
		async_transfer_data[p_params->connected_assc_id].to_value = p_class07_obj->p_capture_objects->length - 1;
		async_transfer_data[p_params->connected_assc_id].block_transfer = FALSE;

		/*
		* Decode selective access params (sent from Client, if any), update table selector again
		* p_params->service_params.decode_success is used to indicate if selective access params
		* is decoded successfully on r_dlms_classes.c or not.
		*
		*   from_value, to_value
		*/
		if (p_params->selective_access.use == TRUE)
		{
			/* Not support selective access by range now! TODO */
			if (p_params->selective_access.access_selector == 1)
			{
				/* "ScopeAccessViolated" error is returned to Client */
				OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED, FALSE);
				OBIS_DISTRIBUTION_FAILED(p_params->result);
				return;
			}
			else if (p_params->selective_access.access_selector == 2)
			{
				p_entry_descriptor = (class07_entry_descriptor_t *)(void *)p_params->service_params.malloc.p_content;

				/* from_entry and from_value should start from 1 */
				if (p_entry_descriptor->from_value < 1 ||
					p_entry_descriptor->to_value > p_class07_obj->p_capture_objects->length)
				{
					/* "TemporaryFailure" error is returned to Client */
					OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);
					OBIS_DISTRIBUTION_FAILED(p_params->result);
					return;
				}

				/*
				* Update again for (from_value, to_value),
				* indexing from Client start from 1, need -1
				*/
				

				/*
				* Update again for (from_value, to_value),
				* indexing from Client start from 1, need -1
				*/
				async_transfer_data[p_params->connected_assc_id].from_value = p_entry_descriptor->from_value - 1;
				if (p_entry_descriptor->to_value != 0) {
					async_transfer_data[p_params->connected_assc_id].to_value = p_entry_descriptor->to_value - 1;
				}
			}
		}
	}

	/* Validate again if ranges are valid */
	if (async_transfer_data[p_params->connected_assc_id].from_value > async_transfer_data[p_params->connected_assc_id].to_value)
	{
		/* "TemporaryFailure" error is returned to Client */
		OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);
		OBIS_DISTRIBUTION_FAILED(p_params->result);
		return;
	}

	/*
	* -----------------
	* Direct encoding
	* -----------------
	* Array (N entries to be encoded)
	* {
	*    // Entry 0
	*    Structure (M elements, equivalent to [from_value, to_value] columns)
	*    {
	*         // Column 0 (from_value)
	*         // Invoke to R_DLMS_CLASSES_InvokeDistribution(...)
	*         // to do encode of each attr requested on capture_objects by the { known OBIS code and attr index }
	*
	*         // Column 1
	*
	*         ...
	*
	*         // Column M-1 (to_value)
	*    },
	*
	*    // Entry 1
	*    ...
	*
	*    // Entry N-1
	* }
	*
	*/

	/* Encode Array header on Get-Request-Normal call */
	if (p_params->service_type.get == COSEM_GET_REQUEST_NORMAL)
	{
		/* Direct encode, Array(N entries to be encoded) header */
		/* For realtime data, just have 1 entry to encode */
		OBIS_DIST_ENCODE_ARRAY_TYPE_DEF(u8, p_params->out_data, 1);
		OBIS_DIST_ENCODE_STRUCTURE_TYPE_DEF(u8, p_params->out_data, (async_transfer_data[p_params->connected_assc_id].to_value - async_transfer_data[p_params->connected_assc_id].from_value + 1));
	}

	/*
	* Loop to do direct encode of all entries on this class 07 object
	* "Async" (block transfer is checked inside the loop.
	*
	* Assume that one row need max 100 bytes to encode :D
	*/
	/*
		 * ----------------------------------------
		 * Encode Entries[from_entry]
		 * ----------------------------------------
		 * Structure (M elements, equalivant to [from_value, to_value] columns)
		 */
	{
		/* To do encode to prepared buffer (APDU) */
		const MandatoryString attr_in_buffer = {NULL, 0};
		MandatoryString attr_out_buffer;
		distributor_result_t attr_out_buffer_encode_result;
		uint16_t attr_out_buffer_encode_length;

		/* To search the range [from_value, to_value] */
		//uint16_t data_index;
		class07_obj_def_t *p_captured_object;

		/* For R_DLMS_CLASSES_InvokeDistribution() call */
		descriptor_t descriptor;
		selective_access_t selective_access;
		service_type_t service_type;

		for (;
			 async_transfer_data[p_params->connected_assc_id].from_value <= async_transfer_data[p_params->connected_assc_id].to_value;
			 async_transfer_data[p_params->connected_assc_id].from_value++)
		{
			/* Get the object that represent data for the request column */
			p_captured_object = p_class07_obj->p_capture_objects->p_content + async_transfer_data[p_params->connected_assc_id].from_value;

			/* Point to current location on prepared buffer (APDU) from r_dlms_classes.c (malloc) */
			attr_out_buffer = p_params->out_data;

			/* Setup param to invoke R_DLMS_CLASSES_InvokeDistribution() on classes to get out the attr buffer */
			descriptor.attr.class_id = p_captured_object->class_id;			   /* Class ID */
			descriptor.attr.attribute_id = p_captured_object->attribute_index; /* Attr ID */
			memcpy((uint8_t *)descriptor.attr.instance_id,					   /* OBIS Code */
				   (uint8_t *)p_captured_object->logical_name.p_content,
				   p_captured_object->logical_name.length);
			selective_access.use = 0;					 /* No use of selective access */
			service_type.get = COSEM_GET_REQUEST_NORMAL; /* Get-Request-Normal */

			/* Call to R_DLMS_CLASSES_InvokeDistribution() on r_dlms_classes to get out attr buffer */
			attr_out_buffer_encode_result = R_DLMS_CLASSES_InvokeDistribution(
				p_params->connected_assc_id,
				REQ_TYPE_GET,
				&descriptor,
				&p_params->selective_access,
				&service_type,
				p_params->p_library_descriptor,
				attr_in_buffer,
				attr_out_buffer,
#if defined(DLMS_LIB_VERSION) && (DLMS_LIB_VERSION == LIB_V2_2)
				(uint16_t *)&attr_out_buffer_encode_length);
#else
				(uint16_t *)&attr_out_buffer_encode_length,
				&p_params->service_params.malloc
				);
#endif//defined(DLMS_LIB_VERSION) && (DLMS_LIB_VERSION == LIB_V2_2)


			if (attr_out_buffer_encode_result.result.data_access == VAL_DATA_ACCESS_RESULT_SUCCESS &&
				attr_out_buffer_encode_result.success == TRUE &&
				attr_out_buffer_encode_length > 0)
			{
				/* Cut buffer if out data length over, waiting for next shift*/
				if(p_params->out_data.length < attr_out_buffer_encode_length)
				{
					break;
				}
				/* Advance to next location on p_params->out_data to do direct encode */
				OBIS_ADVANCE_BUFFER(p_params->out_data, attr_out_buffer_encode_length);
			}
			else /* Break out and wait for encoding next block */
			{
				break;
			}
		}
	}

	/* Get total bytes encoded */
	*p_params->p_out_encoded_len = (uint16_t)(p_params->out_data.p_content - p_head);

	/* Something wrong with encoding? */
	if (*p_params->p_out_encoded_len == 0) 
	{
		OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE, FALSE);
		OBIS_DISTRIBUTION_FAILED(p_params->result);
		return;
	}

	/* Finished encoding of all entries? */
	if (async_transfer_data[p_params->connected_assc_id].from_value > async_transfer_data[p_params->connected_assc_id].to_value) {
		async_transfer_data[p_params->connected_assc_id].block_transfer = FALSE;
	}
	else {
		async_transfer_data[p_params->connected_assc_id].block_transfer = TRUE;
	}

	/* Return to OBIS and DLMS Library */
	OBIS_DATA_ACCESS_RESULT(p_params->result, VAL_DATA_ACCESS_RESULT_SUCCESS, async_transfer_data[p_params->connected_assc_id].block_transfer);
	OBIS_DISTRIBUTION_SUCCESS(p_params->result);
	return;
}



/***********************************************************************************************************
* Object name:      Billing profile
* Object number:    00
* Object obis code: 1.0.98.1.0.255
***********************************************************************************************************/


const class07_obj_frame_format_t g_class07_frame_format_Billing_profile_Obj00[] = 
{
	{ TAG_DATA_OCTET_STRING, offsetof(Billing_profile_Obj00_DLMSEntry_t, billing_date_import_mode), 12}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, average_power_factor_for_billing_period), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kwh_import), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kwh_for_tz1), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kwh_for_tz2), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kwh_for_tz3), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kwh_for_tz4), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kwh_for_tz5), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kwh_for_tz6), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kvah_import), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kvah_for_tz1), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kvah_for_tz2), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kvah_for_tz3), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kvah_for_tz4), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kvah_for_tz5), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cumulative_energy_kvah_for_tz6), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, max_demand_kw), 4}, 
	{ TAG_DATA_OCTET_STRING, offsetof(Billing_profile_Obj00_DLMSEntry_t, max_demand_kw_capture_time), 12}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, max_demand_kva), 4}, 
	{ TAG_DATA_OCTET_STRING, offsetof(Billing_profile_Obj00_DLMSEntry_t, max_demand_kva_capture_time), 12}, 
	{ TAG_DATA_DOUBLE_LONG_UNSIGNED, offsetof(Billing_profile_Obj00_DLMSEntry_t, billing_power_on_duration_in_mins), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cummulative_energy_kwh_export), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Billing_profile_Obj00_DLMSEntry_t, cummulative_energy_kvah_export), 4}, 

};
const uint8_t g_class07_frame_format_Billing_profile_Obj00_size = sizeof(g_class07_frame_format_Billing_profile_Obj00) / sizeof(class07_obj_frame_format_t);

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj00_att02_CopyToBuffer
* Description   : Object name		: Billing profile
*				  Logical name		: 1.0.98.1.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : uint16_t child_index -
*                   This is index this object in child record.
*				  uint16_t entry_index -
*					This is index
*				  void	*p_entry_buff -
*					
* Return Value  : uint8_t - TRUE executes successfully, else is FALSE
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj00_att02_CopyToBuffer_UserCode(
	uint16_t child_index,
	uint16_t entry_index,
	void	*p_entry_buff
)
{
	/* This function use to assign value for each entry */
	/* Please assign your value of each element of capture object */
	
	Billing_profile_Obj00_DLMSEntry_t *p_buff = (Billing_profile_Obj00_DLMSEntry_t *)p_entry_buff;
	r_billing_t billing_entry;

    uint32_t entry_in_use;
    uint8_t get_result;
	

	if (p_entry_buff == NULL)
	{
		return FALSE;
	}


	/* Add check entry index < number entry of your capture object table */
	/* Start user code */
	/* TODO - User code need to implement here */

	/* End of user code */


	/* Start user code */
	/* Get entry at entry index */
    R_BILLING_GetEntryInUse(&entry_in_use);
    if (entry_index >= entry_in_use)
	{
		get_result = R_BILLING_Get_CurrentCycleBillingParameters(&billing_entry);
	}
	else
	{
		get_result = R_BILLING_GetEntryByIndex(entry_index, &billing_entry);
	}

	if (get_result)
	{

	}
	else
	{
		return FALSE;
	}

	/* Convert and pass for date time import */
	R_DLMS_RTC_Convert_RTC2DateTime2((date_time_t *)&p_buff->billing_date_import_mode, (rtc_counter_value_t *)&billing_entry.CaptureTime);

	p_buff->average_power_factor_for_billing_period = billing_entry.AveragePowerFactor;
	p_buff->cumulative_energy_kwh_import = billing_entry.CumulativeEnergykWh;
	p_buff->cumulative_energy_kwh_for_tz1 = billing_entry.CumulativeEnergykWh_TZ1;
	p_buff->cumulative_energy_kwh_for_tz2 = billing_entry.CumulativeEnergykWh_TZ2;
	p_buff->cumulative_energy_kwh_for_tz3 = billing_entry.CumulativeEnergykWh_TZ3;
	p_buff->cumulative_energy_kwh_for_tz4 = billing_entry.CumulativeEnergykWh_TZ4;
	p_buff->cumulative_energy_kwh_for_tz5 = billing_entry.CumulativeEnergykWh_TZ5;
	p_buff->cumulative_energy_kwh_for_tz6 = billing_entry.CumulativeEnergykWh_TZ6;
	p_buff->cumulative_energy_kvah_import = billing_entry.CumulativeEnergykVAh;
	p_buff->cumulative_energy_kvah_for_tz1 = billing_entry.CumulativeEnergykVAh_TZ1;
	p_buff->cumulative_energy_kvah_for_tz2 = billing_entry.CumulativeEnergykVAh_TZ2;
	p_buff->cumulative_energy_kvah_for_tz3 = billing_entry.CumulativeEnergykVAh_TZ3;
	p_buff->cumulative_energy_kvah_for_tz4 = billing_entry.CumulativeEnergykVAh_TZ4;
	p_buff->cumulative_energy_kvah_for_tz5 = billing_entry.CumulativeEnergykVAh_TZ5;
	p_buff->cumulative_energy_kvah_for_tz6 = billing_entry.CumulativeEnergykVAh_TZ6;
	p_buff->max_demand_kw = billing_entry.MDkW;
	R_DLMS_RTC_Convert_RTC2DateTime2((date_time_t *)&p_buff->max_demand_kw_capture_time, (rtc_counter_value_t *)&billing_entry.MDkWDateTime);
	p_buff->max_demand_kva = billing_entry.MDkVA;
	R_DLMS_RTC_Convert_RTC2DateTime2((date_time_t *)&p_buff->max_demand_kva_capture_time, (rtc_counter_value_t *)&billing_entry.MDkVADateTime);
	p_buff->billing_power_on_duration_in_mins = billing_entry.PowerONduration;
	p_buff->cummulative_energy_kwh_export = billing_entry.CumulativeEnergykWh_Export;
	p_buff->cummulative_energy_kvah_export = billing_entry.CumulativeEnergykVAh_Export;
	/* End of user code */

    return TRUE;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj00_att02_ConvertRtcRangeToIndex_UserCode
* Description   : Object name		: Billing profile
*				  Logical name		: 1.0.98.1.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
* Arguments     : class07_range_descriptor_t *p_range_request - Input
*                   This is RTC range request by Client.
*				  uint16_t *p_out_from_entry - Output
*					This is index of the first entry match RTC start time
*				  uint16_t *p_out_to_entry - Output
*					This is index of the last entry match RTC end time
*				  void	*p_out_total_entries - Output
*                   Total entry found from [StartTime to EndTime]
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic07_obj00_att02_ConvertRtcRangeToIndex_UserCode(
	class07_range_descriptor_t *p_range_request,
	uint16_t *p_out_from_entry_index,
	uint16_t *p_out_to_entry_index,
    uint16_t *p_out_total_entries
)
{
    uint32_t entry_index_start;
    uint32_t entry_index_end;
    uint8_t is_found_start = FALSE;
    uint8_t is_found_end = FALSE;
	distributor_params_t * p_params = NULL;

	Billing_profile_Obj00_DLMSEntry_t entry_get;
	uint32_t entries_in_use;
	uint16_t i;
	int8_t result;

	R_DLMS_USER_ic07_obj00_att07_get(p_params, &entries_in_use);
    /* 
     *  +----------------------------------+------------------------+
     *  |  Client request                  | Output                 |
     *  |  (Date time value)               | (Index value)          |
     *  | ---------------------------------+------------------------|
     *  | p_range_request->p_from_value    | p_out_from_entry       |
     *  | p_range_request->p_to_value      | p_out_to_entry         |
     *  |                                  | total entry found      |
     *  +-----------------------------------------------------------+
     */
   
    /* 
     * Request from client
     *
     * range_descriptor ::= structure           | Eg:
     * {                                        |       Class   LN              AttbIndex  DataIndex(Option)
     *      restricting_object                  |       08      A.B.C.D.E.F     02         00
     *      from_value                          | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      to_value                            | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      selected_value                      | All column
     * }   
     */

	/* Check input */
	if(p_range_request->p_from_value->choice.size != 12 && p_range_request->p_to_value->choice.size != 12)
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
        *p_out_total_entries = 0;
		return;
	}
	/* Check to value with the first entry */
	/* Get first entry to check time */
	R_DLMS_USER_ic07_obj00_att02_CopyToBuffer_UserCode(0, 0, &entry_get);
	if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.billing_date_import_mode,
						       *(date_time_t *)p_range_request->p_to_value->buffer) > 0)
	{
		/* If date time of entry is bigger than 'to value', return to range is out of value */
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
		return;
	}
	/* find start and end position */
	for(i = 0; i < entries_in_use; i++)
	{
		/* Get entry to check time */
		R_DLMS_USER_ic07_obj00_att02_CopyToBuffer_UserCode(0, i, &entry_get);

		if(is_found_start == FALSE)
		{
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.billing_date_import_mode,
									   *(date_time_t *)p_range_request->p_from_value->buffer) >= 0)
			{
				entry_index_start = i;
				is_found_start = TRUE;
			}
		}
		else
		{
			result = R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.billing_date_import_mode,
									   *(date_time_t *)p_range_request->p_to_value->buffer);
			if (result > 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = i - 1;
				is_found_end = TRUE;
				break;
			}
			else if(result ==0)
			{
				/* If date time of entry is equal 'to value', the end index is this index */
				entry_index_end = i;
				is_found_end = TRUE;
				break;
			}
			else
			{}
		}
		
	}
	/* If found start entry and not found end entry, check for 'to value' that it is over than the biggest */
	if(is_found_start == TRUE && is_found_end == FALSE)
	{
			/* If 'to value' bigger than the last entry, set to value to biggest entry index */
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.billing_date_import_mode,
						              *(date_time_t *)p_range_request->p_to_value->buffer) < 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = entries_in_use - 1;
				is_found_end = TRUE;
			}
	}
	if (entry_index_end < entry_index_start || (is_found_start == FALSE) || (is_found_end == FALSE))
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
	}
	else
	{
		*p_out_from_entry_index = entry_index_start;
		*p_out_to_entry_index = entry_index_end;
		*p_out_total_entries = (entry_index_end - entry_index_start) + 1;
	}
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj00_att02_get
* Description   : Object name		: Billing profile
*				  Logical name		: 1.0.98.1.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*				  Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj00_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* *IMPORTANT INFORMATION* */
	/* This is selective access, you need to create ENCODE FUNCTION by manual */
	/* This attribute does not support for automatic encoding */

	/* Start user code here */
	Billing_profile_Obj00_DLMSEntry_t temp_buffer;
	uint8_t is_rollover;
	class07_obj_one_entry_descriptor_t frame_format;
	uint32_t entries_in_use;

	
	/* Set value entries in use */
	R_DLMS_USER_ic07_obj00_att07_get(p_params, &entries_in_use);

	frame_format.p_frame_format = (class07_obj_frame_format_t *)g_class07_frame_format_Billing_profile_Obj00;
	frame_format.frame_format_size = g_class07_frame_format_Billing_profile_Obj00_size;
	frame_format.p_data = (uint8_t *)&temp_buffer;
	frame_format.fn_buff_fill = R_DLMS_USER_ic07_obj00_att02_CopyToBuffer_UserCode;
	frame_format.fn_by_range_filter = R_DLMS_USER_ic07_obj00_att02_ConvertRtcRangeToIndex_UserCode;
	R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
		p_params,
		entries_in_use,
		&frame_format);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



/*******************************************************************************
* Variable name: g_dlms_ic07_obj00_att03_capture_objects
* Object name: Billing profile
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj00_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj00_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj00_billing_date_import_mode[6] 	 = { 0, 0, 0, 1, 2, 255 };
const uint8_t g_OBIS_CaptureObj00_average_power_factor_for_billing_period[6] 	 = { 1, 0, 13, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kwh_import[6] 	 = { 1, 0, 1, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz1[6] 	 = { 1, 0, 1, 8, 1, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz2[6] 	 = { 1, 0, 1, 8, 2, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz3[6] 	 = { 1, 0, 1, 8, 3, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz4[6] 	 = { 1, 0, 1, 8, 4, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz5[6] 	 = { 1, 0, 1, 8, 5, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz6[6] 	 = { 1, 0, 1, 8, 6, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kvah_import[6] 	 = { 1, 0, 9, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz1[6] 	 = { 1, 0, 9, 8, 1, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz2[6] 	 = { 1, 0, 9, 8, 2, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz3[6] 	 = { 1, 0, 9, 8, 3, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz4[6] 	 = { 1, 0, 9, 8, 4, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz5[6] 	 = { 1, 0, 9, 8, 5, 255 };
const uint8_t g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz6[6] 	 = { 1, 0, 9, 8, 6, 255 };
const uint8_t g_OBIS_CaptureObj00_max_demand_kw[6] 	 = { 1, 0, 1, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj00_max_demand_kw_capture_time[6] 	 = { 1, 0, 1, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj00_max_demand_kva[6] 	 = { 1, 0, 9, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj00_max_demand_kva_capture_time[6] 	 = { 1, 0, 9, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj00_billing_power_on_duration_in_mins[6] 	 = { 0, 0, 94, 91, 13, 255 };
const uint8_t g_OBIS_CaptureObj00_cummulative_energy_kwh_export[6] 	 = { 1, 0, 2, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj00_cummulative_energy_kvah_export[6] 	 = { 1, 0, 10, 8, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj00_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_billing_date_import_mode , 6 }, 2 },
	/* 01 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_average_power_factor_for_billing_period , 6 }, 2 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kwh_import , 6 }, 2 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz1 , 6 }, 2 },
	/* 04 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz2 , 6 }, 2 },
	/* 05 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz3 , 6 }, 2 },
	/* 06 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz4 , 6 }, 2 },
	/* 07 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz5 , 6 }, 2 },
	/* 08 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kwh_for_tz6 , 6 }, 2 },
	/* 09 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kvah_import , 6 }, 2 },
	/* 10 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz1 , 6 }, 2 },
	/* 11 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz2 , 6 }, 2 },
	/* 12 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz3 , 6 }, 2 },
	/* 13 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz4 , 6 }, 2 },
	/* 14 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz5 , 6 }, 2 },
	/* 15 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cumulative_energy_kvah_for_tz6 , 6 }, 2 },
	/* 16 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj00_max_demand_kw , 6 }, 2 },
	/* 17 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj00_max_demand_kw_capture_time , 6 }, 5 },
	/* 18 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj00_max_demand_kva , 6 }, 2 },
	/* 19 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj00_max_demand_kva_capture_time , 6 }, 5 },
	/* 20 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_billing_power_on_duration_in_mins , 6 }, 2 },
	/* 21 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cummulative_energy_kwh_export , 6 }, 2 },
	/* 22 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj00_cummulative_energy_kvah_export , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj00_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj00_att03_capture_objects_Element,
	23
};


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj00_att04_get
* Description   : Object name       : Billing profile
*                 Object index      : 00
*                 Class             : 07
*                 Attribute order   : 04
*                 Attribute name    : capture_period
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj00_att04_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	uint32_t link_data = 0;
	/* Set value */
	*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj00_att05_sort_method
* Object name: Billing profile
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj00_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj00_att06_sort_object
* Object name: Billing profile
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj00_att06_sort_object  = 
/* 00 */  { 3, { (uint8_t *)&g_OBIS_CaptureObj00_billing_date_import_mode , 6 }, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj00_att07_get
* Description   : Object name       : Billing profile
*                 Object index      : 00
*                 Class             : 07
*                 Attribute order   : 07
*                 Attribute name    : entries_in_use
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj00_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 5;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_BILLING_GetEntryInUse(p_attribute_get))
	{
        /* Entry in use for billing = Entry in EEPROM + Current billing cycle parameter */
        *p_attribute_get = (*p_attribute_get) + 1;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj00_att08_get
* Description   : Object name       : Billing profile
*                 Object index      : 00
*                 Class             : 07
*                 Attribute order   : 08
*                 Attribute name    : profile_entries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj00_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 5;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_BILLING_GetProfileEntry(p_attribute_get))
	{
        /* Entry in use for billing = Entry in EEPROM + Current billing cycle parameter */
        *p_attribute_get = (*p_attribute_get) + 1;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj00_meth01_action
* Description   : Object name       : Billing profile
*                 Object index      : 00
*                 Class             : 07
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj00_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Clears the buffer.It has no valid entries afterwards;
	* Entries_in_use is zero after this call.
	* This call does not trigger any additional operations on the capture objects.
	* Specifically, it does not reset any attributes captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if(R_BILLING_Reset())
	{

	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj00_meth02_action
* Description   : Object name       : Billing profile
*                 Object index      : 00
*                 Class             : 07
*                 Method order      : 02
*                 Method name       : Capture
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj00_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Copies the values of the objects to capture into the buffer
	*  by reading each capture object.
	* Depending on the sort_method and the actual state of the buffer
	*  this produces a new entry or a replacement for the less significant entry.
	* As long as not all entries are already used,
	*  the entries_in_use attribute will be incremented.
	* This call does not trigger any additional operations within
	*  the capture objects such as capture () or reset ().
	* Note, that if more than one attribute of an object need to be captured,
	*  they have to be defined one by one on the list of capture_objects.
	* If the attribute_index = 0, all attributes are captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Billing Scaler Profile
* Object number:    01
* Object obis code: 1.0.94.91.6.255
***********************************************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj01_att02_get
* Description   : Object name		: Billing Scaler Profile
*				  Logical name		: 1.0.94.91.6.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj01_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* Start user code here */
	R_MakeBuffer_RealTime_SupportBlockTransfer_Class07(p_params);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/*******************************************************************************
* Variable name: g_dlms_ic07_obj01_att03_capture_objects
* Object name: Billing Scaler Profile
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj01_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj01_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj01_billing_date_import_mode[6] 	 = { 0, 0, 0, 1, 2, 255 };
const uint8_t g_OBIS_CaptureObj01_average_power_factor_for_billing_period[6] 	 = { 1, 0, 13, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kwh_import[6] 	 = { 1, 0, 1, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz1[6] 	 = { 1, 0, 1, 8, 1, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz2[6] 	 = { 1, 0, 1, 8, 2, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz3[6] 	 = { 1, 0, 1, 8, 3, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz4[6] 	 = { 1, 0, 1, 8, 4, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz5[6] 	 = { 1, 0, 1, 8, 5, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz6[6] 	 = { 1, 0, 1, 8, 6, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kvah_import[6] 	 = { 1, 0, 9, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz1[6] 	 = { 1, 0, 9, 8, 1, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz2[6] 	 = { 1, 0, 9, 8, 2, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz3[6] 	 = { 1, 0, 9, 8, 3, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz4[6] 	 = { 1, 0, 9, 8, 4, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz5[6] 	 = { 1, 0, 9, 8, 5, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz6[6] 	 = { 1, 0, 9, 8, 6, 255 };
const uint8_t g_OBIS_CaptureObj01_max_demand_kw[6] 	 = { 1, 0, 1, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj01_max_demand_kva[6] 	 = { 1, 0, 9, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj01_billing_power_on_durarion_in_mins[6] 	 = { 0, 0, 94, 91, 13, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kwh_export[6] 	 = { 1, 0, 2, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj01_cumulative_energy_kvah_export[6] 	 = { 1, 0, 10, 8, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj01_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_billing_date_import_mode , 6 }, 3 },
	/* 01 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_average_power_factor_for_billing_period , 6 }, 3 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kwh_import , 6 }, 3 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz1 , 6 }, 3 },
	/* 04 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz2 , 6 }, 3 },
	/* 05 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz3 , 6 }, 3 },
	/* 06 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz4 , 6 }, 3 },
	/* 07 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz5 , 6 }, 3 },
	/* 08 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kwh_for_tz6 , 6 }, 3 },
	/* 09 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kvah_import , 6 }, 3 },
	/* 10 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz1 , 6 }, 3 },
	/* 11 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz2 , 6 }, 3 },
	/* 12 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz3 , 6 }, 3 },
	/* 13 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz4 , 6 }, 3 },
	/* 14 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz5 , 6 }, 3 },
	/* 15 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kvah_for_tz6 , 6 }, 3 },
	/* 16 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj01_max_demand_kw , 6 }, 3 },
	/* 17 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj01_max_demand_kva , 6 }, 3 },
	/* 18 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_billing_power_on_durarion_in_mins , 6 }, 3 },
	/* 19 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kwh_export , 6 }, 3 },
	/* 20 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj01_cumulative_energy_kvah_export , 6 }, 3 },
};

const class07_obj_def_array_t g_dlms_ic07_obj01_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj01_att03_capture_objects_Element,
	21
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj01_att04_capture_period
* Object name: Billing Scaler Profile
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj01_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj01_att05_sort_method
* Object name: Billing Scaler Profile
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj01_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj01_att06_sort_object
* Object name: Billing Scaler Profile
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj01_att06_sort_object  = 
/* 00 */  { 3, { (uint8_t *)&g_OBIS_CaptureObj01_billing_date_import_mode , 6 }, 3 };


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj01_att07_entries_in_use
* Object name: Billing Scaler Profile
* Attribute order: 07
* Attribute name: entries_in_use
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of entries_in_use (class - 07, atrribute - 07)*/
const uint32_t g_dlms_ic07_obj01_att07_entries_in_use  = 1;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj01_att08_profile_entries
* Object name: Billing Scaler Profile
* Attribute order: 08
* Attribute name: profile_entries
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of profile_entries (class - 07, atrribute - 08)*/
const uint32_t g_dlms_ic07_obj01_att08_profile_entries  = 1;




/***********************************************************************************************************
* Object name:      Block Load Profile
* Object number:    02
* Object obis code: 1.0.99.1.0.255
***********************************************************************************************************/


const class07_obj_frame_format_t g_class07_frame_format_Block_Load_Profile_Obj02[] = 
{
	{ TAG_DATA_OCTET_STRING, offsetof(Block_Load_Profile_Obj02_DLMSEntry_t, date_and_time), 12}, 
	{ TAG_DATA_FLOAT32, offsetof(Block_Load_Profile_Obj02_DLMSEntry_t, average_voltage), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Block_Load_Profile_Obj02_DLMSEntry_t, block_energy_kwh_import), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Block_Load_Profile_Obj02_DLMSEntry_t, block_energy_kvah_import), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Block_Load_Profile_Obj02_DLMSEntry_t, block_energy_kwh_export), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Block_Load_Profile_Obj02_DLMSEntry_t, block_energy_kvah_export), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Block_Load_Profile_Obj02_DLMSEntry_t, average_current), 4}, 

};
const uint8_t g_class07_frame_format_Block_Load_Profile_Obj02_size = sizeof(g_class07_frame_format_Block_Load_Profile_Obj02) / sizeof(class07_obj_frame_format_t);

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj02_att02_CopyToBuffer
* Description   : Object name		: Block Load Profile
*				  Logical name		: 1.0.99.1.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : uint16_t child_index -
*                   This is index this object in child record.
*				  uint16_t entry_index -
*					This is index
*				  void	*p_entry_buff -
*					
* Return Value  : uint8_t - TRUE executes successfully, else is FALSE
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj02_att02_CopyToBuffer_UserCode(
	uint16_t child_index,
	uint16_t entry_index,
	void	*p_entry_buff
)
{
	/* This function use to assign value for each entry */
	/* Please assign your value of each element of capture object */
	
	Block_Load_Profile_Obj02_DLMSEntry_t *p_buff = (Block_Load_Profile_Obj02_DLMSEntry_t *)p_entry_buff;
	r_block_load_t blockload_entry;
	uint8_t multiplier;
	uint16_t capture_period = 0;
	/* Asign one by one below variable */
    R_DLMS_RTC_T DLMSRTCValue;
    
	if (p_entry_buff == NULL)
	{
		return FALSE;
	}


	/* Add check entry index < number entry of your capture object table */
	/* Start user code */
	/* TODO - User code need to implement here */

	/* End of user code */

	/*************************************************************************/
	/* date_and_time_linking_data = entry[entry_index].date_and_time */
	/* average_voltage_linking_data = entry[entry_index].average_voltage */
	/* block_energy_kwh_import_linking_data = entry[entry_index].block_energy_kwh_import */
	/* block_energy_kvah_import_linking_data = entry[entry_index].block_energy_kvah_import */
	/* block_energy_kwh_export_linking_data = entry[entry_index].block_energy_kwh_export */
	/* block_energy_kvah_export_linking_data = entry[entry_index].block_energy_kvah_export */
	/* average_current_linking_data = entry[entry_index].average_current */
	/*************************************************************************/

	/* Start user code */
	/* TODO - User code need to implement here */
	/* Get block load entry */
	/* Get block load period */
    R_BLOCKLOAD_GetProfileCapturePeriod(&capture_period);
	/* Calculate divider */
	multiplier = (uint8_t) (capture_period / (15 * 60)); //scale unit for block is 15 minute
	if(R_BLOCKLOAD_GetEntryByIndex(entry_index, multiplier, &blockload_entry) && (multiplier > 0))
	{

	}
	else
	{
		return FALSE;
	}

    blockload_entry.CaptureTime.min += (capture_period / 60);
    if (blockload_entry.CaptureTime.min >= 60)
    {
		blockload_entry.CaptureTime.min = 0;
        blockload_entry.CaptureTime.hour += 1;
        if (blockload_entry.CaptureTime.hour >= 24)
        {
            blockload_entry.CaptureTime.hour = 0;
            
            memcpy(&DLMSRTCValue,&blockload_entry.CaptureTime, sizeof(R_DLMS_RTC_T));
            DLMSRTCValue.Year = (uint8_t)blockload_entry.CaptureTime.year;  /* Get 2 digit only */
            R_DLMS_RTC_Find_NextDay(&DLMSRTCValue);

            blockload_entry.CaptureTime.sec     = DLMSRTCValue.Sec;
            blockload_entry.CaptureTime.min     = DLMSRTCValue.Min;
            blockload_entry.CaptureTime.hour    = DLMSRTCValue.Hour;
            blockload_entry.CaptureTime.day     = DLMSRTCValue.Day;
            blockload_entry.CaptureTime.week    = DLMSRTCValue.Week;
            blockload_entry.CaptureTime.month   = DLMSRTCValue.Month;
            blockload_entry.CaptureTime.year    = DLMSRTCValue.Year;
        }
    }

	/* Convert and pass date time for capture object */
	R_DLMS_RTC_Convert_RTC2DateTime2((date_time_t *)&p_buff->date_and_time, (rtc_counter_value_t *)&blockload_entry.CaptureTime);
	p_buff->average_voltage = blockload_entry.AverageVoltage;
	p_buff->block_energy_kwh_import = blockload_entry.EnergykWhImport;
	p_buff->block_energy_kvah_import = blockload_entry.EnergykVAhImport;
	p_buff->block_energy_kwh_export = blockload_entry.EnergykWhExport;
	p_buff->block_energy_kvah_export = blockload_entry.EnergykVAhExport;
	p_buff->average_current = blockload_entry.AverageCurrent;
	/* End of user code */

	return TRUE;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj02_att02_ConvertRtcRangeToIndex_UserCode
* Description   : Object name		: Block Load Profile
*				  Logical name		: 1.0.99.1.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : class07_range_descriptor_t *p_range_request - Input
*                   This is RTC range request by Client.
*				  uint16_t *p_out_from_entry - Output
*					This is index of the first entry match RTC start time
*				  uint16_t *p_out_to_entry - Output
*					This is index of the last entry match RTC end time
*				  void	*p_out_total_entries - Output
*                   Total entry found from [StartTime to EndTime]
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic07_obj02_att02_ConvertRtcRangeToIndex_UserCode(
	class07_range_descriptor_t *p_range_request,
	uint16_t *p_out_from_entry_index,
	uint16_t *p_out_to_entry_index,
    uint16_t *p_out_total_entries
)
{
    uint32_t entry_index_start;
    uint32_t entry_index_end;
    uint8_t is_found_start = FALSE;
    uint8_t is_found_end = FALSE;
	distributor_params_t * p_params = NULL;

	Block_Load_Profile_Obj02_DLMSEntry_t entry_get;
	uint32_t entries_in_use;
	uint16_t i;
	int8_t result;

	R_DLMS_USER_ic07_obj02_att07_get(p_params, &entries_in_use);
    /* 
     *  +----------------------------------+------------------------+
     *  |  Client request                  | Output                 |
     *  |  (Date time value)               | (Index value)          |
     *  | ---------------------------------+------------------------|
     *  | p_range_request->p_from_value    | p_out_from_entry       |
     *  | p_range_request->p_to_value      | p_out_to_entry         |
     *  |                                  | total entry found      |
     *  +-----------------------------------------------------------+
     */
   
    /* 
     * Request from client
     *
     * range_descriptor ::= structure           | Eg:
     * {                                        |       Class   LN              AttbIndex  DataIndex(Option)
     *      restricting_object                  |       08      A.B.C.D.E.F     02         00
     *      from_value                          | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      to_value                            | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      selected_value                      | All column
     * }   
     */

	/* Check input */
	if(p_range_request->p_from_value->choice.size != 12 && p_range_request->p_to_value->choice.size != 12)
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
        *p_out_total_entries = 0;
		return;
	}
	/* Check to value with the first entry */
	/* Get first entry to check time */
	R_DLMS_USER_ic07_obj02_att02_CopyToBuffer_UserCode(0, 0, &entry_get);
	if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time,
						       *(date_time_t *)p_range_request->p_to_value->buffer) > 0)
	{
		/* If date time of entry is bigger than 'to value', return to range is out of value */
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
		return;
	}
	/* find start and end position */
	for(i = 0; i < entries_in_use; i++)
	{
		/* Get entry to check time */
		R_DLMS_USER_ic07_obj02_att02_CopyToBuffer_UserCode(0, i, &entry_get);

		if(is_found_start == FALSE)
		{
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time,
									   *(date_time_t *)p_range_request->p_from_value->buffer) >= 0)
			{
				entry_index_start = i;
				is_found_start = TRUE;
			}
		}
		else
		{
			result = R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time,
									   *(date_time_t *)p_range_request->p_to_value->buffer);
			if (result > 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = i - 1;
				is_found_end = TRUE;
				break;
			}
			else if(result ==0)
			{
				/* If date time of entry is equal 'to value', the end index is this index */
				entry_index_end = i;
				is_found_end = TRUE;
				break;
			}
			else
			{}
		}
		
	}
	/* If found start entry and not found end entry, check for 'to value' that it is over than the biggest */
	if(is_found_start == TRUE && is_found_end == FALSE)
	{
			/* If 'to value' bigger than the last entry, set to value to biggest entry index */
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time,
						              *(date_time_t *)p_range_request->p_to_value->buffer) < 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = entries_in_use - 1;
				is_found_end = TRUE;
			}
	}
	if (entry_index_end < entry_index_start || (is_found_start == FALSE) || (is_found_end == FALSE))
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
	}
	else
	{
		*p_out_from_entry_index = entry_index_start;
		*p_out_to_entry_index = entry_index_end;
		*p_out_total_entries = (entry_index_end - entry_index_start) + 1;
	}
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj02_att02_get
* Description   : Object name		: Block Load Profile
*				  Logical name		: 1.0.99.1.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*				  Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj02_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* *IMPORTANT INFORMATION* */
	/* This is selective access, you need to create ENCODE FUNCTION by manual */
	/* This attribute does not support for automatic encoding */

	/* Start user code here */
	Block_Load_Profile_Obj02_DLMSEntry_t temp_buffer;
	uint8_t is_rollover;
	class07_obj_one_entry_descriptor_t frame_format;
	uint32_t entries_in_use;
	
	/* Set value entries in use */
	R_DLMS_USER_ic07_obj02_att07_get(p_params, &entries_in_use);

	frame_format.p_frame_format = (class07_obj_frame_format_t *)g_class07_frame_format_Block_Load_Profile_Obj02;
	frame_format.frame_format_size = g_class07_frame_format_Block_Load_Profile_Obj02_size;
	frame_format.p_data = (uint8_t *)&temp_buffer;
	frame_format.fn_buff_fill = R_DLMS_USER_ic07_obj02_att02_CopyToBuffer_UserCode;
	frame_format.fn_by_range_filter = R_DLMS_USER_ic07_obj02_att02_ConvertRtcRangeToIndex_UserCode;
	R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
		p_params,
		entries_in_use,
		&frame_format);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



/*******************************************************************************
* Variable name: g_dlms_ic07_obj02_att03_capture_objects
* Object name: Block Load Profile
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj02_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj02_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj02_date_and_time[6] 	 = { 0, 0, 1, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj02_average_voltage[6] 	 = { 1, 0, 12, 27, 0, 255 };
const uint8_t g_OBIS_CaptureObj02_block_energy_kwh_import[6] 	 = { 1, 0, 1, 29, 0, 255 };
const uint8_t g_OBIS_CaptureObj02_block_energy_kvah_import[6] 	 = { 1, 0, 9, 29, 0, 255 };
const uint8_t g_OBIS_CaptureObj02_block_energy_kwh_export[6] 	 = { 1, 0, 2, 29, 0, 255 };
const uint8_t g_OBIS_CaptureObj02_block_energy_kvah_export[6] 	 = { 1, 0, 10, 29, 0, 255 };
const uint8_t g_OBIS_CaptureObj02_average_current[6] 	 = { 1, 0, 11, 27, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj02_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 8, { (uint8_t *)&g_OBIS_CaptureObj02_date_and_time , 6 }, 2 },
	/* 01 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj02_average_voltage , 6 }, 2 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj02_block_energy_kwh_import , 6 }, 2 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj02_block_energy_kvah_import , 6 }, 2 },
	/* 04 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj02_block_energy_kwh_export , 6 }, 2 },
	/* 05 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj02_block_energy_kvah_export , 6 }, 2 },
	/* 06 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj02_average_current , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj02_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj02_att03_capture_objects_Element,
	7
};


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj02_att04_get
* Description   : Object name       : Block Load Profile
*                 Object index      : 02
*                 Class             : 07
*                 Attribute order   : 04
*                 Attribute name    : capture_period
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj02_att04_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 0;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	uint16_t capture_period;
	if(R_BLOCKLOAD_GetProfileCapturePeriod(&capture_period) == TRUE)
	{
		*p_attribute_get = (uint32_t)capture_period;
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj02_att05_sort_method
* Object name: Block Load Profile
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj02_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj02_att06_sort_object
* Object name: Block Load Profile
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj02_att06_sort_object  = 
/* 00 */  { 8, { (uint8_t *)&g_OBIS_CaptureObj02_date_and_time , 6 }, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj02_att07_get
* Description   : Object name       : Block Load Profile
*                 Object index      : 02
*                 Class             : 07
*                 Attribute order   : 07
*                 Attribute name    : entries_in_use
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj02_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 4;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	uint8_t divider;
	uint16_t capture_period = 0;
	R_BLOCKLOAD_GetProfileCapturePeriod(&capture_period);
	/* Calculate divider */
	divider = (uint8_t)( capture_period / (15 * 60)); //scale unit for block is 15 mi
	if(R_BLOCKLOAD_GetEntryInUse(p_attribute_get, divider) != FALSE && divider > 0)
	{
		
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj02_att08_get
* Description   : Object name       : Block Load Profile
*                 Object index      : 02
*                 Class             : 07
*                 Attribute order   : 08
*                 Attribute name    : profile_entries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj02_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 4;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	uint8_t divider;
	uint16_t capture_period = 0;
	R_BLOCKLOAD_GetProfileCapturePeriod(&capture_period);
	/* Calculate divider */
	divider = (uint8_t) (capture_period / (15 * 60)); //scale unit for block is 15 minute
	if(R_BLOCKLOAD_GetProfileEntry(p_attribute_get, divider) != FALSE && divider > 0)
	{
		
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj02_meth01_action
* Description   : Object name       : Block Load Profile
*                 Object index      : 02
*                 Class             : 07
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj02_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Clears the buffer.It has no valid entries afterwards;
	* Entries_in_use is zero after this call.
	* This call does not trigger any additional operations on the capture objects.
	* Specifically, it does not reset any attributes captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if(R_BLOCKLOAD_Reset())
	{
		
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj02_meth02_action
* Description   : Object name       : Block Load Profile
*                 Object index      : 02
*                 Class             : 07
*                 Method order      : 02
*                 Method name       : Capture
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj02_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Copies the values of the objects to capture into the buffer
	*  by reading each capture object.
	* Depending on the sort_method and the actual state of the buffer
	*  this produces a new entry or a replacement for the less significant entry.
	* As long as not all entries are already used,
	*  the entries_in_use attribute will be incremented.
	* This call does not trigger any additional operations within
	*  the capture objects such as capture () or reset ().
	* Note, that if more than one attribute of an object need to be captured,
	*  they have to be defined one by one on the list of capture_objects.
	* If the attribute_index = 0, all attributes are captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Block Load Scaler Profile
* Object number:    03
* Object obis code: 1.0.94.91.4.255
***********************************************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj03_att02_get
* Description   : Object name		: Block Load Scaler Profile
*				  Logical name		: 1.0.94.91.4.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj03_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* Start user code here */
	R_MakeBuffer_RealTime_SupportBlockTransfer_Class07(p_params);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/*******************************************************************************
* Variable name: g_dlms_ic07_obj03_att03_capture_objects
* Object name: Block Load Scaler Profile
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj03_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj03_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj03_average_voltage[6] 	 = { 1, 0, 12, 27, 0, 255 };
const uint8_t g_OBIS_CaptureObj03_block_energy_kwh_import[6] 	 = { 1, 0, 1, 29, 0, 255 };
const uint8_t g_OBIS_CaptureObj03_block_energy_kvah_import[6] 	 = { 1, 0, 9, 29, 0, 255 };
const uint8_t g_OBIS_CaptureObj03_block_energy_kwh_export[6] 	 = { 1, 0, 2, 29, 0, 255 };
const uint8_t g_OBIS_CaptureObj03_block_energy_kvah_export[6] 	 = { 1, 0, 10, 29, 0, 255 };
const uint8_t g_OBIS_CaptureObj03_average[6] 	 = { 1, 0, 11, 27, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj03_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj03_average_voltage , 6 }, 3 },
	/* 01 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj03_block_energy_kwh_import , 6 }, 3 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj03_block_energy_kvah_import , 6 }, 3 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj03_block_energy_kwh_export , 6 }, 3 },
	/* 04 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj03_block_energy_kvah_export , 6 }, 3 },
	/* 05 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj03_average , 6 }, 3 },
};

const class07_obj_def_array_t g_dlms_ic07_obj03_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj03_att03_capture_objects_Element,
	6
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj03_att04_capture_period
* Object name: Block Load Scaler Profile
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj03_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj03_att05_sort_method
* Object name: Block Load Scaler Profile
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj03_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj03_att06_sort_object
* Object name: Block Load Scaler Profile
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj03_att06_sort_object  = 
/* 00 */  { 3, { (uint8_t *)&g_OBIS_CaptureObj03_average_voltage , 6 }, 3 };


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj03_att07_entries_in_use
* Object name: Block Load Scaler Profile
* Attribute order: 07
* Attribute name: entries_in_use
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of entries_in_use (class - 07, atrribute - 07)*/
const uint32_t g_dlms_ic07_obj03_att07_entries_in_use  = 1;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj03_att08_profile_entries
* Object name: Block Load Scaler Profile
* Attribute order: 08
* Attribute name: profile_entries
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of profile_entries (class - 07, atrribute - 08)*/
const uint32_t g_dlms_ic07_obj03_att08_profile_entries  = 1;




/***********************************************************************************************************
* Object name:      Daily Load Profile
* Object number:    04
* Object obis code: 1.0.99.2.0.255
***********************************************************************************************************/


const class07_obj_frame_format_t g_class07_frame_format_Daily_Load_Profile_Obj04[] = 
{
	{ TAG_DATA_OCTET_STRING, offsetof(Daily_Load_Profile_Obj04_DLMSEntry_t, date_and_time), 12}, 
	{ TAG_DATA_FLOAT32, offsetof(Daily_Load_Profile_Obj04_DLMSEntry_t, cumulative_energy_kwh_export), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Daily_Load_Profile_Obj04_DLMSEntry_t, cumulative_energy_kvah_export), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Daily_Load_Profile_Obj04_DLMSEntry_t, cumulative_energy_kwh_import), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Daily_Load_Profile_Obj04_DLMSEntry_t, cumulative_energy_kvah_import), 4}, 

};
const uint8_t g_class07_frame_format_Daily_Load_Profile_Obj04_size = sizeof(g_class07_frame_format_Daily_Load_Profile_Obj04) / sizeof(class07_obj_frame_format_t);

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj04_att02_CopyToBuffer
* Description   : Object name		: Daily Load Profile
*				  Logical name		: 1.0.99.2.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : uint16_t child_index -
*                   This is index this object in child record.
*				  uint16_t entry_index -
*					This is index
*				  void	*p_entry_buff -
*					
* Return Value  : uint8_t - TRUE executes successfully, else is FALSE
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj04_att02_CopyToBuffer_UserCode(
	uint16_t child_index,
	uint16_t entry_index,
	void	*p_entry_buff
)
{
	/* This function use to assign value for each entry */
	/* Please assign your value of each element of capture object */
	
	Daily_Load_Profile_Obj04_DLMSEntry_t *p_buff = (Daily_Load_Profile_Obj04_DLMSEntry_t *)p_entry_buff;
	r_daily_load_t dailyload_entry;

	/* Asign one by one below variable */
    R_DLMS_RTC_T DLMSRTCValue;

	if (p_entry_buff == NULL)
	{
		return FALSE;
	}


	/* Add check entry index < number entry of your capture object table */
	/* Start user code */
	/* TODO - User code need to implement here */

	/* End of user code */

	/*************************************************************************/
	/* date_and_time_linking_data = entry[entry_index].date_and_time */
	/* cumulative_energy_kwh_export_linking_data = entry[entry_index].cumulative_energy_kwh_export */
	/* cumulative_energy_kvah_export_linking_data = entry[entry_index].cumulative_energy_kvah_export */
	/* cumulative_energy_kwh_import_linking_data = entry[entry_index].cumulative_energy_kwh_import */
	/* cumulative_energy_kvah_import_linking_data = entry[entry_index].cumulative_energy_kvah_import */
	/*************************************************************************/

	/* Start user code */
	/* TODO - User code need to implement here */

	/* End of user code */
	if(R_DAILYLOAD_GetEntryByIndex(entry_index, &dailyload_entry) != 0)
	{

	}
	else
	{
		return FALSE;
	}
    
    if (dailyload_entry.CaptureTime.hour == 24)
    {
        dailyload_entry.CaptureTime.hour = 0;
        memcpy(&DLMSRTCValue,&dailyload_entry.CaptureTime, sizeof(R_DLMS_RTC_T));
        R_DLMS_RTC_Find_NextDay(&DLMSRTCValue);
        
        dailyload_entry.CaptureTime.sec     = DLMSRTCValue.Sec;
        dailyload_entry.CaptureTime.min     = DLMSRTCValue.Min;
        dailyload_entry.CaptureTime.hour    = DLMSRTCValue.Hour;
        dailyload_entry.CaptureTime.day     = DLMSRTCValue.Day;
        dailyload_entry.CaptureTime.week    = DLMSRTCValue.Week;
        dailyload_entry.CaptureTime.month   = DLMSRTCValue.Month;
        dailyload_entry.CaptureTime.year    = DLMSRTCValue.Year;
    }
    
	R_DLMS_RTC_Convert_RTC2DateTime2((date_time_t *)&p_buff->date_and_time, (rtc_counter_value_t *)&dailyload_entry.CaptureTime);


	p_buff->cumulative_energy_kwh_export = dailyload_entry.EnergykWhExport;
	p_buff->cumulative_energy_kvah_export = dailyload_entry.EnergykVAhExport;
	p_buff->cumulative_energy_kwh_import = dailyload_entry.EnergykWhImport;
	p_buff->cumulative_energy_kvah_import = dailyload_entry.EnergykVAhImport;

	return TRUE;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj04_att02_ConvertRtcRangeToIndex_UserCode
* Description   : Object name		: Daily Load Profile
*				  Logical name		: 1.0.99.2.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
* Arguments     : class07_range_descriptor_t *p_range_request - Input
*                   This is RTC range request by Client.
*				  uint16_t *p_out_from_entry - Output
*					This is index of the first entry match RTC start time
*				  uint16_t *p_out_to_entry - Output
*					This is index of the last entry match RTC end time
*				  void	*p_out_total_entries - Output
*                   Total entry found from [StartTime to EndTime]
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic07_obj04_att02_ConvertRtcRangeToIndex_UserCode(
	class07_range_descriptor_t *p_range_request,
	uint16_t *p_out_from_entry_index,
	uint16_t *p_out_to_entry_index,
    uint16_t *p_out_total_entries
)
{
    uint32_t entry_index_start;
    uint32_t entry_index_end;
    uint8_t is_found_start = FALSE;
    uint8_t is_found_end = FALSE;
	distributor_params_t * p_params = NULL;

	Daily_Load_Profile_Obj04_DLMSEntry_t entry_get;
	uint32_t entries_in_use;
	uint16_t i;
	int8_t result;

	R_DLMS_USER_ic07_obj04_att07_get(p_params, &entries_in_use);
    /* 
     *  +----------------------------------+------------------------+
     *  |  Client request                  | Output                 |
     *  |  (Date time value)               | (Index value)          |
     *  | ---------------------------------+------------------------|
     *  | p_range_request->p_from_value    | p_out_from_entry       |
     *  | p_range_request->p_to_value      | p_out_to_entry         |
     *  |                                  | total entry found      |
     *  +-----------------------------------------------------------+
     */
   
    /* 
     * Request from client
     *
     * range_descriptor ::= structure           | Eg:
     * {                                        |       Class   LN              AttbIndex  DataIndex(Option)
     *      restricting_object                  |       08      A.B.C.D.E.F     02         00
     *      from_value                          | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      to_value                            | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      selected_value                      | All column
     * }   
     */

	/* Check input */
	if(p_range_request->p_from_value->choice.size != 12 && p_range_request->p_to_value->choice.size != 12)
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
        *p_out_total_entries = 0;
		return;
	}
	/* Check to value with the first entry */
	/* Get first entry to check time */
	R_DLMS_USER_ic07_obj04_att02_CopyToBuffer_UserCode(0, 0, &entry_get);
	if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time,
						       *(date_time_t *)p_range_request->p_to_value->buffer) > 0)
	{
		/* If date time of entry is bigger than 'to value', return to range is out of value */
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
		return;
	}
	/* find start and end position */
	for(i = 0; i < entries_in_use; i++)
	{
		/* Get entry to check time */
		R_DLMS_USER_ic07_obj04_att02_CopyToBuffer_UserCode(0, i, &entry_get);

		if(is_found_start == FALSE)
		{
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time,
									   *(date_time_t *)p_range_request->p_from_value->buffer) >= 0)
			{
				entry_index_start = i;
				is_found_start = TRUE;
			}
		}
		else
		{
			result = R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time,
									   *(date_time_t *)p_range_request->p_to_value->buffer);
			if (result > 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = i - 1;
				is_found_end = TRUE;
				break;
			}
			else if(result ==0)
			{
				/* If date time of entry is equal 'to value', the end index is this index */
				entry_index_end = i;
				is_found_end = TRUE;
				break;
			}
			else
			{}
		}
		
	}
	/* If found start entry and not found end entry, check for 'to value' that it is over than the biggest */
	if(is_found_start == TRUE && is_found_end == FALSE)
	{
			/* If 'to value' bigger than the last entry, set to value to biggest entry index */
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time,
						              *(date_time_t *)p_range_request->p_to_value->buffer) < 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = entries_in_use - 1;
				is_found_end = TRUE;
			}
	}
	if (entry_index_end < entry_index_start || (is_found_start == FALSE) || (is_found_end == FALSE))
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
	}
	else
	{
		*p_out_from_entry_index = entry_index_start;
		*p_out_to_entry_index = entry_index_end;
		*p_out_total_entries = (entry_index_end - entry_index_start) + 1;
	}
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj04_att02_get
* Description   : Object name		: Daily Load Profile
*				  Logical name		: 1.0.99.2.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*				  Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj04_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* *IMPORTANT INFORMATION* */
	/* This is selective access, you need to create ENCODE FUNCTION by manual */
	/* This attribute does not support for automatic encoding */

	/* Start user code here */
	Daily_Load_Profile_Obj04_DLMSEntry_t temp_buffer;
	uint8_t is_rollover;
	class07_obj_one_entry_descriptor_t frame_format;
	uint32_t entries_in_use;

	
	/* Set value entries in use */
	R_DLMS_USER_ic07_obj04_att07_get(p_params, &entries_in_use);

	frame_format.p_frame_format = (class07_obj_frame_format_t *)g_class07_frame_format_Daily_Load_Profile_Obj04;
	frame_format.frame_format_size = g_class07_frame_format_Daily_Load_Profile_Obj04_size;
	frame_format.p_data = (uint8_t *)&temp_buffer;
	frame_format.fn_buff_fill = R_DLMS_USER_ic07_obj04_att02_CopyToBuffer_UserCode;
	frame_format.fn_by_range_filter = R_DLMS_USER_ic07_obj04_att02_ConvertRtcRangeToIndex_UserCode;
	R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
		p_params,
		entries_in_use,
		&frame_format);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



/*******************************************************************************
* Variable name: g_dlms_ic07_obj04_att03_capture_objects
* Object name: Daily Load Profile
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj04_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj04_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj04_date_and_time[6] 	 = { 0, 0, 1, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj04_cumulative_energy_kwh_export[6] 	 = { 1, 0, 2, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj04_cumulative_energy_kvah_export[6] 	 = { 1, 0, 10, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj04_cumulative_energy_kwh_import[6] 	 = { 1, 0, 1, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj04_cumulative_energy_kvah_import[6] 	 = { 1, 0, 9, 8, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj04_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 8, { (uint8_t *)&g_OBIS_CaptureObj04_date_and_time , 6 }, 2 },
	/* 01 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj04_cumulative_energy_kwh_export , 6 }, 2 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj04_cumulative_energy_kvah_export , 6 }, 2 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj04_cumulative_energy_kwh_import , 6 }, 2 },
	/* 04 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj04_cumulative_energy_kvah_import , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj04_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj04_att03_capture_objects_Element,
	5
};


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj04_att04_get
* Description   : Object name       : Daily Load Profile
*                 Object index      : 04
*                 Class             : 07
*                 Attribute order   : 04
*                 Attribute name    : capture_period
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj04_att04_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 0;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	/* Set value */
	*((uint32_t *)p_attribute_get) = 86400;//24h*60m*60s
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj04_att05_sort_method
* Object name: Daily Load Profile
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj04_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj04_att06_sort_object
* Object name: Daily Load Profile
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj04_att06_sort_object  = 
/* 00 */  { 8, { (uint8_t *)&g_OBIS_CaptureObj04_date_and_time , 6 }, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj04_att07_get
* Description   : Object name       : Daily Load Profile
*                 Object index      : 04
*                 Class             : 07
*                 Attribute order   : 07
*                 Attribute name    : entries_in_use
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj04_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 3;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_DAILYLOAD_GetEntryInUse(p_attribute_get))
	{
		
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj04_att08_get
* Description   : Object name       : Daily Load Profile
*                 Object index      : 04
*                 Class             : 07
*                 Attribute order   : 08
*                 Attribute name    : profile_entries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj04_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 3;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_DAILYLOAD_GetProfileEntry(p_attribute_get))
	{
		
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj04_meth01_action
* Description   : Object name       : Daily Load Profile
*                 Object index      : 04
*                 Class             : 07
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj04_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Clears the buffer.It has no valid entries afterwards;
	* Entries_in_use is zero after this call.
	* This call does not trigger any additional operations on the capture objects.
	* Specifically, it does not reset any attributes captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if(R_DAILYLOAD_Reset())
	{
		
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj04_meth02_action
* Description   : Object name       : Daily Load Profile
*                 Object index      : 04
*                 Class             : 07
*                 Method order      : 02
*                 Method name       : Capture
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj04_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Copies the values of the objects to capture into the buffer
	*  by reading each capture object.
	* Depending on the sort_method and the actual state of the buffer
	*  this produces a new entry or a replacement for the less significant entry.
	* As long as not all entries are already used,
	*  the entries_in_use attribute will be incremented.
	* This call does not trigger any additional operations within
	*  the capture objects such as capture () or reset ().
	* Note, that if more than one attribute of an object need to be captured,
	*  they have to be defined one by one on the list of capture_objects.
	* If the attribute_index = 0, all attributes are captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Daily Load Scaler Profile
* Object number:    05
* Object obis code: 1.0.94.91.5.255
***********************************************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj05_att02_get
* Description   : Object name		: Daily Load Scaler Profile
*				  Logical name		: 1.0.94.91.5.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj05_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* Start user code here */
	R_MakeBuffer_RealTime_SupportBlockTransfer_Class07(p_params);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/*******************************************************************************
* Variable name: g_dlms_ic07_obj05_att03_capture_objects
* Object name: Daily Load Scaler Profile
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj05_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj05_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj05_cumulative_energy_kwh_export[6] 	 = { 1, 0, 2, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj05_cumulative_energy_kvah_export[6] 	 = { 1, 0, 10, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj05_cumulative_energy_kwh_import[6] 	 = { 1, 0, 1, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj05_cumulative_energy_kvah_import[6] 	 = { 1, 0, 9, 8, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj05_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj05_cumulative_energy_kwh_export , 6 }, 3 },
	/* 01 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj05_cumulative_energy_kvah_export , 6 }, 3 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj05_cumulative_energy_kwh_import , 6 }, 3 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj05_cumulative_energy_kvah_import , 6 }, 3 },
};

const class07_obj_def_array_t g_dlms_ic07_obj05_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj05_att03_capture_objects_Element,
	4
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj05_att04_capture_period
* Object name: Daily Load Scaler Profile
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj05_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj05_att05_sort_method
* Object name: Daily Load Scaler Profile
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj05_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj05_att06_sort_object
* Object name: Daily Load Scaler Profile
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj05_att06_sort_object  = 
/* 00 */  { 3, { (uint8_t *)&g_OBIS_CaptureObj05_cumulative_energy_kwh_export , 6 }, 3 };


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj05_att07_entries_in_use
* Object name: Daily Load Scaler Profile
* Attribute order: 07
* Attribute name: entries_in_use
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of entries_in_use (class - 07, atrribute - 07)*/
const uint32_t g_dlms_ic07_obj05_att07_entries_in_use  = 1;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj05_att08_profile_entries
* Object name: Daily Load Scaler Profile
* Attribute order: 08
* Attribute name: profile_entries
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of profile_entries (class - 07, atrribute - 08)*/
const uint32_t g_dlms_ic07_obj05_att08_profile_entries  = 1;




/***********************************************************************************************************
* Object name:      Event Scaler Profile
* Object number:    06
* Object obis code: 1.0.94.91.7.255
***********************************************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj06_att02_get
* Description   : Object name		: Event Scaler Profile
*				  Logical name		: 1.0.94.91.7.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj06_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* Start user code here */
	R_MakeBuffer_RealTime_SupportBlockTransfer_Class07(p_params);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/*******************************************************************************
* Variable name: g_dlms_ic07_obj06_att03_capture_objects
* Object name: Event Scaler Profile
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj06_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj06_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj06_current[6] 	 = { 1, 0, 94, 91, 14, 255 };
const uint8_t g_OBIS_CaptureObj06_voltage[6] 	 = { 1, 0, 12, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj06_power_factor[6] 	 = { 1, 0, 13, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj06_cumulative_energy_kwh[6] 	 = { 1, 0, 1, 8, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj06_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj06_current , 6 }, 3 },
	/* 01 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj06_voltage , 6 }, 3 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj06_power_factor , 6 }, 3 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj06_cumulative_energy_kwh , 6 }, 3 },
};

const class07_obj_def_array_t g_dlms_ic07_obj06_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj06_att03_capture_objects_Element,
	4
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj06_att04_capture_period
* Object name: Event Scaler Profile
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj06_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj06_att05_sort_method
* Object name: Event Scaler Profile
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj06_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj06_att06_sort_object
* Object name: Event Scaler Profile
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj06_att06_sort_object  = 
/* 00 */  { 3, { (uint8_t *)&g_OBIS_CaptureObj06_current , 6 }, 3 };


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj06_att07_entries_in_use
* Object name: Event Scaler Profile
* Attribute order: 07
* Attribute name: entries_in_use
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of entries_in_use (class - 07, atrribute - 07)*/
const uint32_t g_dlms_ic07_obj06_att07_entries_in_use  = 1;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj06_att08_profile_entries
* Object name: Event Scaler Profile
* Attribute order: 08
* Attribute name: profile_entries
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of profile_entries (class - 07, atrribute - 08)*/
const uint32_t g_dlms_ic07_obj06_att08_profile_entries  = 1;




/***********************************************************************************************************
* Object name:      Event profile Control
* Object number:    07
* Object obis code: 0.0.99.98.6.255
***********************************************************************************************************/


const class07_obj_frame_format_t g_class07_frame_format_Event_profile_Control_Obj07[] = 
{
	{ TAG_DATA_OCTET_STRING, offsetof(Event_profile_Control_Obj07_DLMSEntry_t, date_and_time_of_event), 12}, 
	{ TAG_DATA_LONG_UNSIGNED, offsetof(Event_profile_Control_Obj07_DLMSEntry_t, event_code), 2}, 

};
const uint8_t g_class07_frame_format_Event_profile_Control_Obj07_size = sizeof(g_class07_frame_format_Event_profile_Control_Obj07) / sizeof(class07_obj_frame_format_t);

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj07_att02_CopyToBuffer
* Description   : Object name		: Event profile Control
*				  Logical name		: 0.0.99.98.6.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : uint16_t child_index -
*                   This is index this object in child record.
*				  uint16_t entry_index -
*					This is index
*				  void	*p_entry_buff -
*					
* Return Value  : uint8_t - TRUE executes successfully, else is FALSE
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj07_att02_CopyToBuffer_UserCode(
	uint16_t child_index,
	uint16_t entry_index,
	void	*p_entry_buff
)
{
	/* This function use to assign value for each entry */
	/* Please assign your value of each element of capture object */
	
	//Event_profile_Control_Obj07_DLMSEntry_t *p_buff = (Event_profile_Control_Obj07_DLMSEntry_t *)p_entry_buff;
	
	/* Asign one by one below variable */
	// date_time_t date_and_time_of_event_linking_data;
	// uint16_t event_code_linking_data;
	if (p_entry_buff == NULL)
	{
		return FALSE;
	}


	/* Add check entry index < number entry of your capture object table */
	/* Start user code */
	/* TODO - User code need to implement here */
	if(entry_index > CONTROL_EVENTS_MAX_ENTRIES)
	{
		return FALSE;
	}
	/* End of user code */

	/*************************************************************************/
	/* date_and_time_of_event_linking_data = entry[entry_index].date_and_time_of_event */
	/* event_code_linking_data = entry[entry_index].event_code */
	/*************************************************************************/

	/* Start user code */
	/* TODO - User code need to implement here */
	event_short_params_get(EVENT_TYPE_CONTROL_EVENTS, 
	                      entry_index, 
						  (st_common_event_params_short_t *)p_entry_buff);
	/* End of user code */



    return TRUE;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj07_att02_ConvertRtcRangeToIndex_UserCode
* Description   : Object name		: Event profile Control
*				  Logical name		: 0.0.99.98.6.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
* Arguments     : class07_range_descriptor_t *p_range_request - Input
*                   This is RTC range request by Client.
*				  uint16_t *p_out_from_entry - Output
*					This is index of the first entry match RTC start time
*				  uint16_t *p_out_to_entry - Output
*					This is index of the last entry match RTC end time
*				  void	*p_out_total_entries - Output
*                   Total entry found from [StartTime to EndTime]
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic07_obj07_att02_ConvertRtcRangeToIndex_UserCode(
	class07_range_descriptor_t *p_range_request,
	uint16_t *p_out_from_entry_index,
	uint16_t *p_out_to_entry_index,
    uint16_t *p_out_total_entries
)
{
    uint32_t entry_index_start;
    uint32_t entry_index_end;
    uint8_t is_found_start = FALSE;
    uint8_t is_found_end = FALSE;
	distributor_params_t * p_params = NULL;

	Event_profile_Control_Obj07_DLMSEntry_t entry_get;
	uint32_t entries_in_use;
	uint16_t i;
	int8_t result;

	R_DLMS_USER_ic07_obj07_att07_get(p_params, &entries_in_use);
    /* 
     *  +----------------------------------+------------------------+
     *  |  Client request                  | Output                 |
     *  |  (Date time value)               | (Index value)          |
     *  | ---------------------------------+------------------------|
     *  | p_range_request->p_from_value    | p_out_from_entry       |
     *  | p_range_request->p_to_value      | p_out_to_entry         |
     *  |                                  | total entry found      |
     *  +-----------------------------------------------------------+
     */
   
    /* 
     * Request from client
     *
     * range_descriptor ::= structure           | Eg:
     * {                                        |       Class   LN              AttbIndex  DataIndex(Option)
     *      restricting_object                  |       08      A.B.C.D.E.F     02         00
     *      from_value                          | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      to_value                            | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      selected_value                      | All column
     * }   
     */

	/* Check input */
	if(p_range_request->p_from_value->choice.size != 12 && p_range_request->p_to_value->choice.size != 12)
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
        *p_out_total_entries = 0;
		return;
	}
	/* Check to value with the first entry */
	/* Get first entry to check time */
	R_DLMS_USER_ic07_obj07_att02_CopyToBuffer_UserCode(0, 0, &entry_get);
	if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						       *(date_time_t *)p_range_request->p_to_value->buffer) > 0)
	{
		/* If date time of entry is bigger than 'to value', return to range is out of value */
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
		return;
	}
	/* find start and end position */
	for(i = 0; i < entries_in_use; i++)
	{
		/* Get entry to check time */
		R_DLMS_USER_ic07_obj07_att02_CopyToBuffer_UserCode(0, i, &entry_get);

		if(is_found_start == FALSE)
		{
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_from_value->buffer) >= 0)
			{
				entry_index_start = i;
				is_found_start = TRUE;
			}
		}
		else
		{
			result = R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_to_value->buffer);
			if (result > 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = i - 1;
				is_found_end = TRUE;
				break;
			}
			else if(result ==0)
			{
				/* If date time of entry is equal 'to value', the end index is this index */
				entry_index_end = i;
				is_found_end = TRUE;
				break;
			}
			else
			{}
		}
		
	}
	/* If found start entry and not found end entry, check for 'to value' that it is over than the biggest */
	if(is_found_start == TRUE && is_found_end == FALSE)
	{
			/* If 'to value' bigger than the last entry, set to value to biggest entry index */
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						              *(date_time_t *)p_range_request->p_to_value->buffer) < 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = entries_in_use - 1;
				is_found_end = TRUE;
			}
	}
	if (entry_index_end < entry_index_start || (is_found_start == FALSE) || (is_found_end == FALSE))
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
	}
	else
	{
		*p_out_from_entry_index = entry_index_start;
		*p_out_to_entry_index = entry_index_end;
		*p_out_total_entries = (entry_index_end - entry_index_start) + 1;
	}
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj07_att02_get
* Description   : Object name		: Event profile Control
*				  Logical name		: 0.0.99.98.6.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*				  Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj07_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* *IMPORTANT INFORMATION* */
	/* This is selective access, you need to create ENCODE FUNCTION by manual */
	/* This attribute does not support for automatic encoding */

	/* Start user code here */
	Event_profile_Control_Obj07_DLMSEntry_t temp_buffer;
	uint8_t is_rollover;
	class07_obj_one_entry_descriptor_t frame_format;
	uint32_t entries_in_use;

	
	/* Set value entries in use */
	R_DLMS_USER_ic07_obj07_att07_get(p_params, &entries_in_use);

	frame_format.p_frame_format = (class07_obj_frame_format_t *)g_class07_frame_format_Event_profile_Control_Obj07;
	frame_format.frame_format_size = g_class07_frame_format_Event_profile_Control_Obj07_size;
	frame_format.p_data = (uint8_t *)&temp_buffer;
	frame_format.fn_buff_fill = R_DLMS_USER_ic07_obj07_att02_CopyToBuffer_UserCode;
	frame_format.fn_by_range_filter = R_DLMS_USER_ic07_obj07_att02_ConvertRtcRangeToIndex_UserCode;
	R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
		p_params,
		entries_in_use,
		&frame_format);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



/*******************************************************************************
* Variable name: g_dlms_ic07_obj07_att03_capture_objects
* Object name: Event profile Control
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj07_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj07_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj07_date_and_time_of_event[6] 	 = { 0, 0, 1, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj07_event_code[6] 	 = { 0, 0, 96, 11, 6, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj07_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 8, { (uint8_t *)&g_OBIS_CaptureObj07_date_and_time_of_event , 6 }, 2 },
	/* 01 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj07_event_code , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj07_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj07_att03_capture_objects_Element,
	2
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj07_att04_capture_period
* Object name: Event profile Control
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj07_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj07_att05_sort_method
* Object name: Event profile Control
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj07_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj07_att06_sort_object
* Object name: Event profile Control
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj07_att06_sort_object  = 
/* 00 */  { 8, { (uint8_t *)&g_OBIS_CaptureObj07_date_and_time_of_event , 6 }, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj07_att07_get
* Description   : Object name       : Event profile Control
*                 Object index      : 07
*                 Class             : 07
*                 Attribute order   : 07
*                 Attribute name    : entries_in_use
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj07_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 2;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_EntriesInUseGet(EVENT_TYPE_CONTROL_EVENTS, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj07_att08_get
* Description   : Object name       : Event profile Control
*                 Object index      : 07
*                 Class             : 07
*                 Attribute order   : 08
*                 Attribute name    : profile_entries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj07_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 2;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_ProfileEntriesGet(EVENT_TYPE_CONTROL_EVENTS, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj07_meth01_action
* Description   : Object name       : Event profile Control
*                 Object index      : 07
*                 Class             : 07
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj07_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Clears the buffer.It has no valid entries afterwards;
	* Entries_in_use is zero after this call.
	* This call does not trigger any additional operations on the capture objects.
	* Specifically, it does not reset any attributes captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if(R_EVENT_ResetLog(EVENT_TYPE_CONTROL_EVENTS))
	{
							
	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;									
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj07_meth02_action
* Description   : Object name       : Event profile Control
*                 Object index      : 07
*                 Class             : 07
*                 Method order      : 02
*                 Method name       : Capture
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj07_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Copies the values of the objects to capture into the buffer
	*  by reading each capture object.
	* Depending on the sort_method and the actual state of the buffer
	*  this produces a new entry or a replacement for the less significant entry.
	* As long as not all entries are already used,
	*  the entries_in_use attribute will be incremented.
	* This call does not trigger any additional operations within
	*  the capture objects such as capture () or reset ().
	* Note, that if more than one attribute of an object need to be captured,
	*  they have to be defined one by one on the list of capture_objects.
	* If the attribute_index = 0, all attributes are captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Event profile Current
* Object number:    08
* Object obis code: 0.0.99.98.1.255
***********************************************************************************************************/


const class07_obj_frame_format_t g_class07_frame_format_Event_profile_Current_Obj08[] = 
{
	{ TAG_DATA_OCTET_STRING, offsetof(Event_profile_Current_Obj08_DLMSEntry_t, date_and_time_of_event), 12}, 
	{ TAG_DATA_LONG_UNSIGNED, offsetof(Event_profile_Current_Obj08_DLMSEntry_t, event_code), 2}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Current_Obj08_DLMSEntry_t, current), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Current_Obj08_DLMSEntry_t, voltage), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Current_Obj08_DLMSEntry_t, power_factor), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Current_Obj08_DLMSEntry_t, cumulative_energy_kwh), 4}, 
	{ TAG_DATA_DOUBLE_LONG_UNSIGNED, offsetof(Event_profile_Current_Obj08_DLMSEntry_t, cumulative_tamper_count), 4}, 

};
const uint8_t g_class07_frame_format_Event_profile_Current_Obj08_size = sizeof(g_class07_frame_format_Event_profile_Current_Obj08) / sizeof(class07_obj_frame_format_t);

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj08_att02_CopyToBuffer
* Description   : Object name		: Event profile Current
*				  Logical name		: 0.0.99.98.1.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : uint16_t child_index -
*                   This is index this object in child record.
*				  uint16_t entry_index -
*					This is index
*				  void	*p_entry_buff -
*					
* Return Value  : uint8_t - TRUE executes successfully, else is FALSE
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj08_att02_CopyToBuffer_UserCode(
	uint16_t child_index,
	uint16_t entry_index,
	void	*p_entry_buff
)
{
	/* This function use to assign value for each entry */
	/* Please assign your value of each element of capture object */
	
	//Event_profile_Current_Obj08_DLMSEntry_t *p_buff = (Event_profile_Current_Obj08_DLMSEntry_t *)p_entry_buff;
	/* Declare event parameters are defined by application */

	if (p_entry_buff == NULL)
	{
		return FALSE;
	}


	/* Add check entry index < number entry of your capture object table */
	/* Start user code */
	/* TODO - User code need to implement here */
	if(entry_index > CURRENT_EVENTS_MAX_ENTRIES)
	{
		return FALSE;
	}
	/* End of user code */

	/*************************************************************************/
	/* date_and_time_of_event_linking_data = entry[entry_index].date_and_time_of_event */
	/* event_code_linking_data = entry[entry_index].event_code */
	/* current_linking_data = entry[entry_index].current */
	/* voltage_linking_data = entry[entry_index].voltage */
	/* power_factor_linking_data = entry[entry_index].power_factor */
	/* cumulative_energy_kwh_linking_data = entry[entry_index].cumulative_energy_kwh */
	/* cumulative_tamper_count_linking_data = entry[entry_index].cumulative_tamper_count */
	/*************************************************************************/

	/* Start user code */
	/* TODO - User code need to implement here */

	/* End of user code */
	/* Get event record from event application */
	event_long_params_get(EVENT_TYPE_CURRENT_RELATED, 
	                      entry_index, 
						  (st_common_event_params_long_t *)p_entry_buff);

	/* End of user code */


    return TRUE;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj08_att02_ConvertRtcRangeToIndex_UserCode
* Description   : Object name		: Event profile Current
*				  Logical name		: 0.0.99.98.1.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
* Arguments     : class07_range_descriptor_t *p_range_request - Input
*                   This is RTC range request by Client.
*				  uint16_t *p_out_from_entry - Output
*					This is index of the first entry match RTC start time
*				  uint16_t *p_out_to_entry - Output
*					This is index of the last entry match RTC end time
*				  void	*p_out_total_entries - Output
*                   Total entry found from [StartTime to EndTime]
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic07_obj08_att02_ConvertRtcRangeToIndex_UserCode(
	class07_range_descriptor_t *p_range_request,
	uint16_t *p_out_from_entry_index,
	uint16_t *p_out_to_entry_index,
    uint16_t *p_out_total_entries
)
{
    uint32_t entry_index_start;
    uint32_t entry_index_end;
    uint8_t is_found_start = FALSE;
    uint8_t is_found_end = FALSE;
	distributor_params_t * p_params = NULL;

	Event_profile_Current_Obj08_DLMSEntry_t entry_get;
	uint32_t entries_in_use;
	uint16_t i;
	int8_t result;

	R_DLMS_USER_ic07_obj08_att07_get(p_params, &entries_in_use);
    /* 
     *  +----------------------------------+------------------------+
     *  |  Client request                  | Output                 |
     *  |  (Date time value)               | (Index value)          |
     *  | ---------------------------------+------------------------|
     *  | p_range_request->p_from_value    | p_out_from_entry       |
     *  | p_range_request->p_to_value      | p_out_to_entry         |
     *  |                                  | total entry found      |
     *  +-----------------------------------------------------------+
     */
   
    /* 
     * Request from client
     *
     * range_descriptor ::= structure           | Eg:
     * {                                        |       Class   LN              AttbIndex  DataIndex(Option)
     *      restricting_object                  |       08      A.B.C.D.E.F     02         00
     *      from_value                          | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      to_value                            | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      selected_value                      | All column
     * }   
     */

	/* Check input */
	if(p_range_request->p_from_value->choice.size != 12 && p_range_request->p_to_value->choice.size != 12)
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
        *p_out_total_entries = 0;
		return;
	}
	/* Check to value with the first entry */
	/* Get first entry to check time */
	R_DLMS_USER_ic07_obj08_att02_CopyToBuffer_UserCode(0, 0, &entry_get);
	if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						       *(date_time_t *)p_range_request->p_to_value->buffer) > 0)
	{
		/* If date time of entry is bigger than 'to value', return to range is out of value */
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
		return;
	}
	/* find start and end position */
	for(i = 0; i < entries_in_use; i++)
	{
		/* Get entry to check time */
		R_DLMS_USER_ic07_obj08_att02_CopyToBuffer_UserCode(0, i, &entry_get);

		if(is_found_start == FALSE)
		{
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_from_value->buffer) >= 0)
			{
				entry_index_start = i;
				is_found_start = TRUE;
			}
		}
		else
		{
			result = R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_to_value->buffer);
			if (result > 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = i - 1;
				is_found_end = TRUE;
				break;
			}
			else if(result ==0)
			{
				/* If date time of entry is equal 'to value', the end index is this index */
				entry_index_end = i;
				is_found_end = TRUE;
				break;
			}
			else
			{}
		}
		
	}
	/* If found start entry and not found end entry, check for 'to value' that it is over than the biggest */
	if(is_found_start == TRUE && is_found_end == FALSE)
	{
			/* If 'to value' bigger than the last entry, set to value to biggest entry index */
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						              *(date_time_t *)p_range_request->p_to_value->buffer) < 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = entries_in_use - 1;
				is_found_end = TRUE;
			}
	}
	if (entry_index_end < entry_index_start || (is_found_start == FALSE) || (is_found_end == FALSE))
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
	}
	else
	{
		*p_out_from_entry_index = entry_index_start;
		*p_out_to_entry_index = entry_index_end;
		*p_out_total_entries = (entry_index_end - entry_index_start) + 1;
	}
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj08_att02_get
* Description   : Object name		: Event profile Current
*				  Logical name		: 0.0.99.98.1.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*				  Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj08_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* *IMPORTANT INFORMATION* */
	/* This is selective access, you need to create ENCODE FUNCTION by manual */
	/* This attribute does not support for automatic encoding */

	/* Start user code here */
	Event_profile_Current_Obj08_DLMSEntry_t temp_buffer;
	uint8_t is_rollover;
	class07_obj_one_entry_descriptor_t frame_format;
	uint32_t entries_in_use;

	
	/* Set value entries in use */
	R_DLMS_USER_ic07_obj08_att07_get(p_params, &entries_in_use);

	frame_format.p_frame_format = (class07_obj_frame_format_t *)g_class07_frame_format_Event_profile_Current_Obj08;
	frame_format.frame_format_size = g_class07_frame_format_Event_profile_Current_Obj08_size;
	frame_format.p_data = (uint8_t *)&temp_buffer;
	frame_format.fn_buff_fill = R_DLMS_USER_ic07_obj08_att02_CopyToBuffer_UserCode;
	frame_format.fn_by_range_filter = R_DLMS_USER_ic07_obj08_att02_ConvertRtcRangeToIndex_UserCode;
	R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
		p_params,
		entries_in_use,
		&frame_format);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



/*******************************************************************************
* Variable name: g_dlms_ic07_obj08_att03_capture_objects
* Object name: Event profile Current
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj08_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj08_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj08_date_and_time_of_event[6] 	 = { 0, 0, 1, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj08_event_code[6] 	 = { 0, 0, 96, 11, 1, 255 };
const uint8_t g_OBIS_CaptureObj08_current[6] 	 = { 1, 0, 94, 91, 14, 255 };
const uint8_t g_OBIS_CaptureObj08_voltage[6] 	 = { 1, 0, 12, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj08_power_factor[6] 	 = { 1, 0, 13, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj08_cumulative_energy_kwh[6] 	 = { 1, 0, 1, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj08_cumulative_tamper_count[6] 	 = { 0, 0, 94, 91, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj08_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 8, { (uint8_t *)&g_OBIS_CaptureObj08_date_and_time_of_event , 6 }, 2 },
	/* 01 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj08_event_code , 6 }, 2 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj08_current , 6 }, 2 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj08_voltage , 6 }, 2 },
	/* 04 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj08_power_factor , 6 }, 2 },
	/* 05 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj08_cumulative_energy_kwh , 6 }, 2 },
	/* 06 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj08_cumulative_tamper_count , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj08_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj08_att03_capture_objects_Element,
	7
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj08_att04_capture_period
* Object name: Event profile Current
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj08_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj08_att05_sort_method
* Object name: Event profile Current
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj08_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj08_att06_sort_object
* Object name: Event profile Current
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj08_att06_sort_object  = 
/* 00 */  { 8, { (uint8_t *)&g_OBIS_CaptureObj08_date_and_time_of_event , 6 }, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj08_att07_get
* Description   : Object name       : Event profile Current
*                 Object index      : 08
*                 Class             : 07
*                 Attribute order   : 07
*                 Attribute name    : entries_in_use
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj08_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	// uint32_t link_data = 1;
	// /* Set value */
	// *((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_EntriesInUseGet(EVENT_TYPE_CURRENT_RELATED, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj08_att08_get
* Description   : Object name       : Event profile Current
*                 Object index      : 08
*                 Class             : 07
*                 Attribute order   : 08
*                 Attribute name    : profile_entries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj08_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	// uint32_t link_data = 1;
	// /* Set value */
	// *((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_ProfileEntriesGet(EVENT_TYPE_CURRENT_RELATED, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj08_meth01_action
* Description   : Object name       : Event profile Current
*                 Object index      : 08
*                 Class             : 07
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj08_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Clears the buffer.It has no valid entries afterwards;
	* Entries_in_use is zero after this call.
	* This call does not trigger any additional operations on the capture objects.
	* Specifically, it does not reset any attributes captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if(R_EVENT_ResetLog(EVENT_TYPE_CURRENT_RELATED))
	{
								
	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;										
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj08_meth02_action
* Description   : Object name       : Event profile Current
*                 Object index      : 08
*                 Class             : 07
*                 Method order      : 02
*                 Method name       : Capture
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj08_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Copies the values of the objects to capture into the buffer
	*  by reading each capture object.
	* Depending on the sort_method and the actual state of the buffer
	*  this produces a new entry or a replacement for the less significant entry.
	* As long as not all entries are already used,
	*  the entries_in_use attribute will be incremented.
	* This call does not trigger any additional operations within
	*  the capture objects such as capture () or reset ().
	* Note, that if more than one attribute of an object need to be captured,
	*  they have to be defined one by one on the list of capture_objects.
	* If the attribute_index = 0, all attributes are captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Event profile non roll over
* Object number:    09
* Object obis code: 0.0.99.98.5.255
***********************************************************************************************************/


const class07_obj_frame_format_t g_class07_frame_format_Event_profile_non_roll_over_Obj09[] = 
{
	{ TAG_DATA_OCTET_STRING, offsetof(Event_profile_non_roll_over_Obj09_DLMSEntry_t, date_and_time_of_event), 12}, 
	{ TAG_DATA_LONG_UNSIGNED, offsetof(Event_profile_non_roll_over_Obj09_DLMSEntry_t, event_code), 2}, 

};
const uint8_t g_class07_frame_format_Event_profile_non_roll_over_Obj09_size = sizeof(g_class07_frame_format_Event_profile_non_roll_over_Obj09) / sizeof(class07_obj_frame_format_t);

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj09_att02_CopyToBuffer
* Description   : Object name		: Event profile non roll over
*				  Logical name		: 0.0.99.98.5.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : uint16_t child_index -
*                   This is index this object in child record.
*				  uint16_t entry_index -
*					This is index
*				  void	*p_entry_buff -
*					
* Return Value  : uint8_t - TRUE executes successfully, else is FALSE
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj09_att02_CopyToBuffer_UserCode(
	uint16_t child_index,
	uint16_t entry_index,
	void	*p_entry_buff
)
{
	/* This function use to assign value for each entry */
	/* Please assign your value of each element of capture object */
	
	Event_profile_non_roll_over_Obj09_DLMSEntry_t *p_buff = (Event_profile_non_roll_over_Obj09_DLMSEntry_t *)p_entry_buff;
	
	/* Asign one by one below variable */
	// date_time_t date_and_time_of_event_linking_data;
	// uint16_t event_code_linking_data;


	if (p_entry_buff == NULL)
	{
		return FALSE;
	}


	/* Add check entry index < number entry of your capture object table */
	/* Start user code */
	/* TODO - User code need to implement here */

	if(entry_index > NON_ROLLOVER_EVENTS_MAX_ENTRIES)
	{
		return FALSE;
	}
	/* End of user code */

	/*************************************************************************/
	/* date_and_time_of_event_linking_data = entry[entry_index].date_and_time_of_event */
	/* event_code_linking_data = entry[entry_index].event_code */
	/*************************************************************************/

	/* Start user code */
	/* TODO - User code need to implement here */
	event_short_params_get(EVENT_TYPE_NON_ROLLOVER_EVENTS, 
	                      entry_index, 
						  (st_common_event_params_short_t *)p_entry_buff);


    return TRUE;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj09_att02_ConvertRtcRangeToIndex_UserCode
* Description   : Object name		: Event profile non roll over
*				  Logical name		: 0.0.99.98.5.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
* Arguments     : class07_range_descriptor_t *p_range_request - Input
*                   This is RTC range request by Client.
*				  uint16_t *p_out_from_entry - Output
*					This is index of the first entry match RTC start time
*				  uint16_t *p_out_to_entry - Output
*					This is index of the last entry match RTC end time
*				  void	*p_out_total_entries - Output
*                   Total entry found from [StartTime to EndTime]
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic07_obj09_att02_ConvertRtcRangeToIndex_UserCode(
	class07_range_descriptor_t *p_range_request,
	uint16_t *p_out_from_entry_index,
	uint16_t *p_out_to_entry_index,
    uint16_t *p_out_total_entries
)
{
    uint32_t entry_index_start;
    uint32_t entry_index_end;
    uint8_t is_found_start = FALSE;
    uint8_t is_found_end = FALSE;
	distributor_params_t * p_params = NULL;

	Event_profile_non_roll_over_Obj09_DLMSEntry_t entry_get;
	uint32_t entries_in_use;
	uint16_t i;
	int8_t result;

	R_DLMS_USER_ic07_obj09_att07_get(p_params, &entries_in_use);
    /* 
     *  +----------------------------------+------------------------+
     *  |  Client request                  | Output                 |
     *  |  (Date time value)               | (Index value)          |
     *  | ---------------------------------+------------------------|
     *  | p_range_request->p_from_value    | p_out_from_entry       |
     *  | p_range_request->p_to_value      | p_out_to_entry         |
     *  |                                  | total entry found      |
     *  +-----------------------------------------------------------+
     */
   
    /* 
     * Request from client
     *
     * range_descriptor ::= structure           | Eg:
     * {                                        |       Class   LN              AttbIndex  DataIndex(Option)
     *      restricting_object                  |       08      A.B.C.D.E.F     02         00
     *      from_value                          | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      to_value                            | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      selected_value                      | All column
     * }   
     */

	/* Check input */
	if(p_range_request->p_from_value->choice.size != 12 && p_range_request->p_to_value->choice.size != 12)
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
        *p_out_total_entries = 0;
		return;
	}
	/* Check to value with the first entry */
	/* Get first entry to check time */
	R_DLMS_USER_ic07_obj09_att02_CopyToBuffer_UserCode(0, 0, &entry_get);
	if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						       *(date_time_t *)p_range_request->p_to_value->buffer) > 0)
	{
		/* If date time of entry is bigger than 'to value', return to range is out of value */
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
		return;
	}
	/* find start and end position */
	for(i = 0; i < entries_in_use; i++)
	{
		/* Get entry to check time */
		R_DLMS_USER_ic07_obj09_att02_CopyToBuffer_UserCode(0, i, &entry_get);

		if(is_found_start == FALSE)
		{
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_from_value->buffer) >= 0)
			{
				entry_index_start = i;
				is_found_start = TRUE;
			}
		}
		else
		{
			result = R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_to_value->buffer);
			if (result > 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = i - 1;
				is_found_end = TRUE;
				break;
			}
			else if(result ==0)
			{
				/* If date time of entry is equal 'to value', the end index is this index */
				entry_index_end = i;
				is_found_end = TRUE;
				break;
			}
			else
			{}
		}
		
	}
	/* If found start entry and not found end entry, check for 'to value' that it is over than the biggest */
	if(is_found_start == TRUE && is_found_end == FALSE)
	{
			/* If 'to value' bigger than the last entry, set to value to biggest entry index */
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						              *(date_time_t *)p_range_request->p_to_value->buffer) < 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = entries_in_use - 1;
				is_found_end = TRUE;
			}
	}
	if (entry_index_end < entry_index_start || (is_found_start == FALSE) || (is_found_end == FALSE))
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
	}
	else
	{
		*p_out_from_entry_index = entry_index_start;
		*p_out_to_entry_index = entry_index_end;
		*p_out_total_entries = (entry_index_end - entry_index_start) + 1;
	}
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj09_att02_get
* Description   : Object name		: Event profile non roll over
*				  Logical name		: 0.0.99.98.5.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*				  Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj09_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* *IMPORTANT INFORMATION* */
	/* This is selective access, you need to create ENCODE FUNCTION by manual */
	/* This attribute does not support for automatic encoding */

	/* Start user code here */
	Event_profile_non_roll_over_Obj09_DLMSEntry_t temp_buffer;
	uint8_t is_rollover;
	class07_obj_one_entry_descriptor_t frame_format;
	uint32_t entries_in_use;

	
	/* Set value entries in use */
	R_DLMS_USER_ic07_obj09_att07_get(p_params, &entries_in_use);

	frame_format.p_frame_format = (class07_obj_frame_format_t *)g_class07_frame_format_Event_profile_non_roll_over_Obj09;
	frame_format.frame_format_size = g_class07_frame_format_Event_profile_non_roll_over_Obj09_size;
	frame_format.p_data = (uint8_t *)&temp_buffer;
	frame_format.fn_buff_fill = R_DLMS_USER_ic07_obj09_att02_CopyToBuffer_UserCode;
	frame_format.fn_by_range_filter = R_DLMS_USER_ic07_obj09_att02_ConvertRtcRangeToIndex_UserCode;
	R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
		p_params,
		entries_in_use,
		&frame_format);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



/*******************************************************************************
* Variable name: g_dlms_ic07_obj09_att03_capture_objects
* Object name: Event profile non roll over
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj09_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj09_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj09_date_and_time_of_event[6] 	 = { 0, 0, 1, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj09_event_code[6] 	 = { 0, 0, 96, 11, 5, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj09_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 8, { (uint8_t *)&g_OBIS_CaptureObj09_date_and_time_of_event , 6 }, 2 },
	/* 01 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj09_event_code , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj09_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj09_att03_capture_objects_Element,
	2
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj09_att04_capture_period
* Object name: Event profile non roll over
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj09_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj09_att05_sort_method
* Object name: Event profile non roll over
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj09_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj09_att06_sort_object
* Object name: Event profile non roll over
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj09_att06_sort_object  = 
/* 00 */  { 8, { (uint8_t *)&g_OBIS_CaptureObj09_date_and_time_of_event , 6 }, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj09_att07_get
* Description   : Object name       : Event profile non roll over
*                 Object index      : 09
*                 Class             : 07
*                 Attribute order   : 07
*                 Attribute name    : entries_in_use
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj09_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	// uint32_t link_data = 1;
	// /* Set value */
	// *((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_EntriesInUseGet(EVENT_TYPE_NON_ROLLOVER_EVENTS, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj09_att08_get
* Description   : Object name       : Event profile non roll over
*                 Object index      : 09
*                 Class             : 07
*                 Attribute order   : 08
*                 Attribute name    : profile_entries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj09_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	// uint32_t link_data = 1;
	// /* Set value */
	// *((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_ProfileEntriesGet(EVENT_TYPE_NON_ROLLOVER_EVENTS, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj09_meth01_action
* Description   : Object name       : Event profile non roll over
*                 Object index      : 09
*                 Class             : 07
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj09_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Clears the buffer.It has no valid entries afterwards;
	* Entries_in_use is zero after this call.
	* This call does not trigger any additional operations on the capture objects.
	* Specifically, it does not reset any attributes captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if(R_EVENT_ResetLog(EVENT_TYPE_NON_ROLLOVER_EVENTS))
	{
								
	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;									
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj09_meth02_action
* Description   : Object name       : Event profile non roll over
*                 Object index      : 09
*                 Class             : 07
*                 Method order      : 02
*                 Method name       : Capture
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj09_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Copies the values of the objects to capture into the buffer
	*  by reading each capture object.
	* Depending on the sort_method and the actual state of the buffer
	*  this produces a new entry or a replacement for the less significant entry.
	* As long as not all entries are already used,
	*  the entries_in_use attribute will be incremented.
	* This call does not trigger any additional operations within
	*  the capture objects such as capture () or reset ().
	* Note, that if more than one attribute of an object need to be captured,
	*  they have to be defined one by one on the list of capture_objects.
	* If the attribute_index = 0, all attributes are captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Event profile Other
* Object number:    10
* Object obis code: 0.0.99.98.4.255
***********************************************************************************************************/


const class07_obj_frame_format_t g_class07_frame_format_Event_profile_Other_Obj10[] = 
{
	{ TAG_DATA_OCTET_STRING, offsetof(Event_profile_Other_Obj10_DLMSEntry_t, date_and_time_of_event), 12}, 
	{ TAG_DATA_LONG_UNSIGNED, offsetof(Event_profile_Other_Obj10_DLMSEntry_t, event_code), 2}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Other_Obj10_DLMSEntry_t, current), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Other_Obj10_DLMSEntry_t, voltage), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Other_Obj10_DLMSEntry_t, power_factor), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Other_Obj10_DLMSEntry_t, cumulative_energy_kwh), 4}, 
	{ TAG_DATA_DOUBLE_LONG_UNSIGNED, offsetof(Event_profile_Other_Obj10_DLMSEntry_t, cumulative_tamper_count), 4}, 

};
const uint8_t g_class07_frame_format_Event_profile_Other_Obj10_size = sizeof(g_class07_frame_format_Event_profile_Other_Obj10) / sizeof(class07_obj_frame_format_t);

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj10_att02_CopyToBuffer
* Description   : Object name		: Event profile Other
*				  Logical name		: 0.0.99.98.4.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : uint16_t child_index -
*                   This is index this object in child record.
*				  uint16_t entry_index -
*					This is index
*				  void	*p_entry_buff -
*					
* Return Value  : uint8_t - TRUE executes successfully, else is FALSE
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj10_att02_CopyToBuffer_UserCode(
	uint16_t child_index,
	uint16_t entry_index,
	void	*p_entry_buff
)
{
	/* This function use to assign value for each entry */
	/* Please assign your value of each element of capture object */
	
	Event_profile_Other_Obj10_DLMSEntry_t *p_buff = (Event_profile_Other_Obj10_DLMSEntry_t *)p_entry_buff;
	
	/* Asign one by one below variable */


	if (p_entry_buff == NULL)
	{
		return FALSE;
	}


	/* Add check entry index < number entry of your capture object table */
	/* Start user code */
	/* TODO - User code need to implement here */

	/* End of user code */

	/*************************************************************************/
	/* date_and_time_of_event_linking_data = entry[entry_index].date_and_time_of_event */
	/* event_code_linking_data = entry[entry_index].event_code */
	/* current_linking_data = entry[entry_index].current */
	/* voltage_linking_data = entry[entry_index].voltage */
	/* power_factor_linking_data = entry[entry_index].power_factor */
	/* cumulative_energy_kwh_linking_data = entry[entry_index].cumulative_energy_kwh */
	/* cumulative_tamper_count_linking_data = entry[entry_index].cumulative_tamper_count */
	/*************************************************************************/

	/* Start user code */
	if(entry_index > OTHER_EVENTS_MAX_ENTRIES)
	{
		return FALSE;
	}
	/* End of user code */

	/*************************************************************************/
	/* date_and_time_of_event_linking_data = entry[entry_index].date_and_time_of_event */
	/* event_code_linking_data = entry[entry_index].event_code */
	/*************************************************************************/

	/* Start user code */
	/* TODO - User code need to implement here */

	/* End of user code */
	/* Get event record from event application */
	event_long_params_get(EVENT_TYPE_OTHERS, 
	                      entry_index, 
						  (st_common_event_params_long_t *)p_entry_buff);


    return TRUE;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj10_att02_ConvertRtcRangeToIndex_UserCode
* Description   : Object name		: Event profile Other
*				  Logical name		: 0.0.99.98.4.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
* Arguments     : class07_range_descriptor_t *p_range_request - Input
*                   This is RTC range request by Client.
*				  uint16_t *p_out_from_entry - Output
*					This is index of the first entry match RTC start time
*				  uint16_t *p_out_to_entry - Output
*					This is index of the last entry match RTC end time
*				  void	*p_out_total_entries - Output
*                   Total entry found from [StartTime to EndTime]
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic07_obj10_att02_ConvertRtcRangeToIndex_UserCode(
	class07_range_descriptor_t *p_range_request,
	uint16_t *p_out_from_entry_index,
	uint16_t *p_out_to_entry_index,
    uint16_t *p_out_total_entries
)
{
    uint32_t entry_index_start;
    uint32_t entry_index_end;
    uint8_t is_found_start = FALSE;
    uint8_t is_found_end = FALSE;
	distributor_params_t * p_params = NULL;

	Event_profile_Other_Obj10_DLMSEntry_t entry_get;
	uint32_t entries_in_use;
	uint16_t i;
	int8_t result;

	R_DLMS_USER_ic07_obj10_att07_get(p_params, &entries_in_use);
    /* 
     *  +----------------------------------+------------------------+
     *  |  Client request                  | Output                 |
     *  |  (Date time value)               | (Index value)          |
     *  | ---------------------------------+------------------------|
     *  | p_range_request->p_from_value    | p_out_from_entry       |
     *  | p_range_request->p_to_value      | p_out_to_entry         |
     *  |                                  | total entry found      |
     *  +-----------------------------------------------------------+
     */
   
    /* 
     * Request from client
     *
     * range_descriptor ::= structure           | Eg:
     * {                                        |       Class   LN              AttbIndex  DataIndex(Option)
     *      restricting_object                  |       08      A.B.C.D.E.F     02         00
     *      from_value                          | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      to_value                            | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      selected_value                      | All column
     * }   
     */

	/* Check input */
	if(p_range_request->p_from_value->choice.size != 12 && p_range_request->p_to_value->choice.size != 12)
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
        *p_out_total_entries = 0;
		return;
	}
	/* Check to value with the first entry */
	/* Get first entry to check time */
	R_DLMS_USER_ic07_obj10_att02_CopyToBuffer_UserCode(0, 0, &entry_get);
	if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						       *(date_time_t *)p_range_request->p_to_value->buffer) > 0)
	{
		/* If date time of entry is bigger than 'to value', return to range is out of value */
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
		return;
	}
	/* find start and end position */
	for(i = 0; i < entries_in_use; i++)
	{
		/* Get entry to check time */
		R_DLMS_USER_ic07_obj10_att02_CopyToBuffer_UserCode(0, i, &entry_get);

		if(is_found_start == FALSE)
		{
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_from_value->buffer) >= 0)
			{
				entry_index_start = i;
				is_found_start = TRUE;
			}
		}
		else
		{
			result = R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_to_value->buffer);
			if (result > 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = i - 1;
				is_found_end = TRUE;
				break;
			}
			else if(result ==0)
			{
				/* If date time of entry is equal 'to value', the end index is this index */
				entry_index_end = i;
				is_found_end = TRUE;
				break;
			}
			else
			{}
		}
		
	}
	/* If found start entry and not found end entry, check for 'to value' that it is over than the biggest */
	if(is_found_start == TRUE && is_found_end == FALSE)
	{
			/* If 'to value' bigger than the last entry, set to value to biggest entry index */
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						              *(date_time_t *)p_range_request->p_to_value->buffer) < 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = entries_in_use - 1;
				is_found_end = TRUE;
			}
	}
	if (entry_index_end < entry_index_start || (is_found_start == FALSE) || (is_found_end == FALSE))
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
	}
	else
	{
		*p_out_from_entry_index = entry_index_start;
		*p_out_to_entry_index = entry_index_end;
		*p_out_total_entries = (entry_index_end - entry_index_start) + 1;
	}
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj10_att02_get
* Description   : Object name		: Event profile Other
*				  Logical name		: 0.0.99.98.4.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*				  Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj10_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* *IMPORTANT INFORMATION* */
	/* This is selective access, you need to create ENCODE FUNCTION by manual */
	/* This attribute does not support for automatic encoding */

	/* Start user code here */
	Event_profile_Other_Obj10_DLMSEntry_t temp_buffer;
	uint8_t is_rollover;
	class07_obj_one_entry_descriptor_t frame_format;
	uint32_t entries_in_use;

	
	/* Set value entries in use */
	R_DLMS_USER_ic07_obj10_att07_get(p_params, &entries_in_use);

	frame_format.p_frame_format = (class07_obj_frame_format_t *)g_class07_frame_format_Event_profile_Other_Obj10;
	frame_format.frame_format_size = g_class07_frame_format_Event_profile_Other_Obj10_size;
	frame_format.p_data = (uint8_t *)&temp_buffer;
	frame_format.fn_buff_fill = R_DLMS_USER_ic07_obj10_att02_CopyToBuffer_UserCode;
	frame_format.fn_by_range_filter = R_DLMS_USER_ic07_obj10_att02_ConvertRtcRangeToIndex_UserCode;
	R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
		p_params,
		entries_in_use,
		&frame_format);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



/*******************************************************************************
* Variable name: g_dlms_ic07_obj10_att03_capture_objects
* Object name: Event profile Other
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj10_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj10_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj10_date_and_time_of_event[6] 	 = { 0, 0, 1, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj10_event_code[6] 	 = { 0, 0, 96, 11, 4, 255 };
const uint8_t g_OBIS_CaptureObj10_current[6] 	 = { 1, 0, 94, 91, 14, 255 };
const uint8_t g_OBIS_CaptureObj10_voltage[6] 	 = { 1, 0, 12, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj10_power_factor[6] 	 = { 1, 0, 13, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj10_cumulative_energy_kwh[6] 	 = { 1, 0, 1, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj10_cumulative_tamper_count[6] 	 = { 0, 0, 94, 91, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj10_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 8, { (uint8_t *)&g_OBIS_CaptureObj10_date_and_time_of_event , 6 }, 2 },
	/* 01 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj10_event_code , 6 }, 2 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj10_current , 6 }, 2 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj10_voltage , 6 }, 2 },
	/* 04 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj10_power_factor , 6 }, 2 },
	/* 05 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj10_cumulative_energy_kwh , 6 }, 2 },
	/* 06 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj10_cumulative_tamper_count , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj10_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj10_att03_capture_objects_Element,
	7
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj10_att04_capture_period
* Object name: Event profile Other
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj10_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj10_att05_sort_method
* Object name: Event profile Other
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj10_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj10_att06_sort_object
* Object name: Event profile Other
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj10_att06_sort_object  = 
/* 00 */  { 8, { (uint8_t *)&g_OBIS_CaptureObj10_date_and_time_of_event , 6 }, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj10_att07_get
* Description   : Object name       : Event profile Other
*                 Object index      : 10
*                 Class             : 07
*                 Attribute order   : 07
*                 Attribute name    : entries_in_use
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj10_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	// uint32_t link_data = 1;
	// /* Set value */
	// *((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_EntriesInUseGet(EVENT_TYPE_OTHERS, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj10_att08_get
* Description   : Object name       : Event profile Other
*                 Object index      : 10
*                 Class             : 07
*                 Attribute order   : 08
*                 Attribute name    : profile_entries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj10_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 1;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_ProfileEntriesGet(EVENT_TYPE_OTHERS, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj10_meth01_action
* Description   : Object name       : Event profile Other
*                 Object index      : 10
*                 Class             : 07
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj10_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Clears the buffer.It has no valid entries afterwards;
	* Entries_in_use is zero after this call.
	* This call does not trigger any additional operations on the capture objects.
	* Specifically, it does not reset any attributes captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if(R_EVENT_ResetLog(EVENT_TYPE_OTHERS))
	{
									
	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;									
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj10_meth02_action
* Description   : Object name       : Event profile Other
*                 Object index      : 10
*                 Class             : 07
*                 Method order      : 02
*                 Method name       : Capture
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj10_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Copies the values of the objects to capture into the buffer
	*  by reading each capture object.
	* Depending on the sort_method and the actual state of the buffer
	*  this produces a new entry or a replacement for the less significant entry.
	* As long as not all entries are already used,
	*  the entries_in_use attribute will be incremented.
	* This call does not trigger any additional operations within
	*  the capture objects such as capture () or reset ().
	* Note, that if more than one attribute of an object need to be captured,
	*  they have to be defined one by one on the list of capture_objects.
	* If the attribute_index = 0, all attributes are captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Event profile Power
* Object number:    11
* Object obis code: 0.0.99.98.2.255
***********************************************************************************************************/


const class07_obj_frame_format_t g_class07_frame_format_Event_profile_Power_Obj11[] = 
{
	{ TAG_DATA_OCTET_STRING, offsetof(Event_profile_Power_Obj11_DLMSEntry_t, date_and_time_of_event), 12}, 
	{ TAG_DATA_LONG_UNSIGNED, offsetof(Event_profile_Power_Obj11_DLMSEntry_t, event_code), 2}, 

};
const uint8_t g_class07_frame_format_Event_profile_Power_Obj11_size = sizeof(g_class07_frame_format_Event_profile_Power_Obj11) / sizeof(class07_obj_frame_format_t);

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj11_att02_CopyToBuffer
* Description   : Object name		: Event profile Power
*				  Logical name		: 0.0.99.98.2.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : uint16_t child_index -
*                   This is index this object in child record.
*				  uint16_t entry_index -
*					This is index
*				  void	*p_entry_buff -
*					
* Return Value  : uint8_t - TRUE executes successfully, else is FALSE
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj11_att02_CopyToBuffer_UserCode(
	uint16_t child_index,
	uint16_t entry_index,
	void	*p_entry_buff
)
{
	/* This function use to assign value for each entry */
	/* Please assign your value of each element of capture object */
	
	Event_profile_Power_Obj11_DLMSEntry_t *p_buff = (Event_profile_Power_Obj11_DLMSEntry_t *)p_entry_buff;
	
	/* Asign one by one below variable */


	if (p_entry_buff == NULL)
	{
		return FALSE;
	}


	/* Add check entry index < number entry of your capture object table */
	/* Start user code */
	/* TODO - User code need to implement here */
	if(entry_index > POWER_EVENTS_MAX_ENTRIES)
	{
		return FALSE;
	}
	/* End of user code */

	/*************************************************************************/
	/* date_and_time_of_event_linking_data = entry[entry_index].date_and_time_of_event */
	/* event_code_linking_data = entry[entry_index].event_code */
	/*************************************************************************/

	/* Start user code */
	/* TODO - User code need to implement here */
	event_short_params_get(EVENT_TYPE_POWER_RELATED, 
	                      entry_index, 
						  (st_common_event_params_short_t *)p_entry_buff);


    return TRUE;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj11_att02_ConvertRtcRangeToIndex_UserCode
* Description   : Object name		: Event profile Power
*				  Logical name		: 0.0.99.98.2.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
* Arguments     : class07_range_descriptor_t *p_range_request - Input
*                   This is RTC range request by Client.
*				  uint16_t *p_out_from_entry - Output
*					This is index of the first entry match RTC start time
*				  uint16_t *p_out_to_entry - Output
*					This is index of the last entry match RTC end time
*				  void	*p_out_total_entries - Output
*                   Total entry found from [StartTime to EndTime]
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic07_obj11_att02_ConvertRtcRangeToIndex_UserCode(
	class07_range_descriptor_t *p_range_request,
	uint16_t *p_out_from_entry_index,
	uint16_t *p_out_to_entry_index,
    uint16_t *p_out_total_entries
)
{
    uint32_t entry_index_start;
    uint32_t entry_index_end;
    uint8_t is_found_start = FALSE;
    uint8_t is_found_end = FALSE;
	distributor_params_t * p_params = NULL;

	Event_profile_Power_Obj11_DLMSEntry_t entry_get;
	uint32_t entries_in_use;
	uint16_t i;
	int8_t result;

	R_DLMS_USER_ic07_obj11_att07_get(p_params, &entries_in_use);
    /* 
     *  +----------------------------------+------------------------+
     *  |  Client request                  | Output                 |
     *  |  (Date time value)               | (Index value)          |
     *  | ---------------------------------+------------------------|
     *  | p_range_request->p_from_value    | p_out_from_entry       |
     *  | p_range_request->p_to_value      | p_out_to_entry         |
     *  |                                  | total entry found      |
     *  +-----------------------------------------------------------+
     */
   
    /* 
     * Request from client
     *
     * range_descriptor ::= structure           | Eg:
     * {                                        |       Class   LN              AttbIndex  DataIndex(Option)
     *      restricting_object                  |       08      A.B.C.D.E.F     02         00
     *      from_value                          | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      to_value                            | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      selected_value                      | All column
     * }   
     */

	/* Check input */
	if(p_range_request->p_from_value->choice.size != 12 && p_range_request->p_to_value->choice.size != 12)
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
        *p_out_total_entries = 0;
		return;
	}
	/* Check to value with the first entry */
	/* Get first entry to check time */
	R_DLMS_USER_ic07_obj11_att02_CopyToBuffer_UserCode(0, 0, &entry_get);
	if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						       *(date_time_t *)p_range_request->p_to_value->buffer) > 0)
	{
		/* If date time of entry is bigger than 'to value', return to range is out of value */
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
		return;
	}
	/* find start and end position */
	for(i = 0; i < entries_in_use; i++)
	{
		/* Get entry to check time */
		R_DLMS_USER_ic07_obj11_att02_CopyToBuffer_UserCode(0, i, &entry_get);

		if(is_found_start == FALSE)
		{
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_from_value->buffer) >= 0)
			{
				entry_index_start = i;
				is_found_start = TRUE;
			}
		}
		else
		{
			result = R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_to_value->buffer);
			if (result > 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = i - 1;
				is_found_end = TRUE;
				break;
			}
			else if(result ==0)
			{
				/* If date time of entry is equal 'to value', the end index is this index */
				entry_index_end = i;
				is_found_end = TRUE;
				break;
			}
			else
			{}
		}
		
	}
	/* If found start entry and not found end entry, check for 'to value' that it is over than the biggest */
	if(is_found_start == TRUE && is_found_end == FALSE)
	{
			/* If 'to value' bigger than the last entry, set to value to biggest entry index */
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						              *(date_time_t *)p_range_request->p_to_value->buffer) < 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = entries_in_use - 1;
				is_found_end = TRUE;
			}
	}
	if (entry_index_end < entry_index_start || (is_found_start == FALSE) || (is_found_end == FALSE))
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
	}
	else
	{
		*p_out_from_entry_index = entry_index_start;
		*p_out_to_entry_index = entry_index_end;
		*p_out_total_entries = (entry_index_end - entry_index_start) + 1;
	}
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj11_att02_get
* Description   : Object name		: Event profile Power
*				  Logical name		: 0.0.99.98.2.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*				  Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj11_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* *IMPORTANT INFORMATION* */
	/* This is selective access, you need to create ENCODE FUNCTION by manual */
	/* This attribute does not support for automatic encoding */

	/* Start user code here */
	Event_profile_Power_Obj11_DLMSEntry_t temp_buffer;
	uint8_t is_rollover;
	class07_obj_one_entry_descriptor_t frame_format;
	uint32_t entries_in_use;

	
	/* Set value entries in use */
	R_DLMS_USER_ic07_obj11_att07_get(p_params, &entries_in_use);

	frame_format.p_frame_format = (class07_obj_frame_format_t *)g_class07_frame_format_Event_profile_Power_Obj11;
	frame_format.frame_format_size = g_class07_frame_format_Event_profile_Power_Obj11_size;
	frame_format.p_data = (uint8_t *)&temp_buffer;
	frame_format.fn_buff_fill = R_DLMS_USER_ic07_obj11_att02_CopyToBuffer_UserCode;
	frame_format.fn_by_range_filter = R_DLMS_USER_ic07_obj11_att02_ConvertRtcRangeToIndex_UserCode;
	R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
		p_params,
		entries_in_use,
		&frame_format);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



/*******************************************************************************
* Variable name: g_dlms_ic07_obj11_att03_capture_objects
* Object name: Event profile Power
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj11_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj11_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj11_date_and_time_of_event[6] 	 = { 0, 0, 1, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj11_event_code[6] 	 = { 0, 0, 96, 11, 2, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj11_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 8, { (uint8_t *)&g_OBIS_CaptureObj11_date_and_time_of_event , 6 }, 2 },
	/* 01 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj11_event_code , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj11_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj11_att03_capture_objects_Element,
	2
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj11_att04_capture_period
* Object name: Event profile Power
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj11_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj11_att05_sort_method
* Object name: Event profile Power
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj11_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj11_att06_sort_object
* Object name: Event profile Power
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj11_att06_sort_object  = 
/* 00 */  { 8, { (uint8_t *)&g_OBIS_CaptureObj11_date_and_time_of_event , 6 }, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj11_att07_get
* Description   : Object name       : Event profile Power
*                 Object index      : 11
*                 Class             : 07
*                 Attribute order   : 07
*                 Attribute name    : entries_in_use
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj11_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 1;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_EntriesInUseGet(EVENT_TYPE_POWER_RELATED, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj11_att08_get
* Description   : Object name       : Event profile Power
*                 Object index      : 11
*                 Class             : 07
*                 Attribute order   : 08
*                 Attribute name    : profile_entries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj11_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 1;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_ProfileEntriesGet(EVENT_TYPE_POWER_RELATED, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj11_meth01_action
* Description   : Object name       : Event profile Power
*                 Object index      : 11
*                 Class             : 07
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj11_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Clears the buffer.It has no valid entries afterwards;
	* Entries_in_use is zero after this call.
	* This call does not trigger any additional operations on the capture objects.
	* Specifically, it does not reset any attributes captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if(R_EVENT_ResetLog(EVENT_TYPE_POWER_RELATED))
	{
								
	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj11_meth02_action
* Description   : Object name       : Event profile Power
*                 Object index      : 11
*                 Class             : 07
*                 Method order      : 02
*                 Method name       : Capture
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj11_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Copies the values of the objects to capture into the buffer
	*  by reading each capture object.
	* Depending on the sort_method and the actual state of the buffer
	*  this produces a new entry or a replacement for the less significant entry.
	* As long as not all entries are already used,
	*  the entries_in_use attribute will be incremented.
	* This call does not trigger any additional operations within
	*  the capture objects such as capture () or reset ().
	* Note, that if more than one attribute of an object need to be captured,
	*  they have to be defined one by one on the list of capture_objects.
	* If the attribute_index = 0, all attributes are captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Event profile Trans
* Object number:    12
* Object obis code: 0.0.99.98.3.255
***********************************************************************************************************/


const class07_obj_frame_format_t g_class07_frame_format_Event_profile_Trans_Obj12[] = 
{
	{ TAG_DATA_OCTET_STRING, offsetof(Event_profile_Trans_Obj12_DLMSEntry_t, date_and_time_of_event), 12}, 
	{ TAG_DATA_LONG_UNSIGNED, offsetof(Event_profile_Trans_Obj12_DLMSEntry_t, event_code), 2}, 

};
const uint8_t g_class07_frame_format_Event_profile_Trans_Obj12_size = sizeof(g_class07_frame_format_Event_profile_Trans_Obj12) / sizeof(class07_obj_frame_format_t);

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj12_att02_CopyToBuffer
* Description   : Object name		: Event profile Trans
*				  Logical name		: 0.0.99.98.3.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : uint16_t child_index -
*                   This is index this object in child record.
*				  uint16_t entry_index -
*					This is index
*				  void	*p_entry_buff -
*					
* Return Value  : uint8_t - TRUE executes successfully, else is FALSE
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj12_att02_CopyToBuffer_UserCode(
	uint16_t child_index,
	uint16_t entry_index,
	void	*p_entry_buff
)
{
	/* This function use to assign value for each entry */
	/* Please assign your value of each element of capture object */
	
	Event_profile_Trans_Obj12_DLMSEntry_t *p_buff = (Event_profile_Trans_Obj12_DLMSEntry_t *)p_entry_buff;
	
	/* Asign one by one below variable */
	date_time_t date_and_time_of_event_linking_data;
	uint16_t event_code_linking_data;


	if (p_entry_buff == NULL)
	{
		return FALSE;
	}


	/* Add check entry index < number entry of your capture object table */
	/* Start user code */
	/* TODO - User code need to implement here */
	if(entry_index > TRANS_EVENTS_MAX_ENTRIES)
	{
		return FALSE;
	}
	/* End of user code */

	/*************************************************************************/
	/* date_and_time_of_event_linking_data = entry[entry_index].date_and_time_of_event */
	/* event_code_linking_data = entry[entry_index].event_code */
	/*************************************************************************/

	/* Start user code */
	/* TODO - User code need to implement here */
	event_short_params_get(EVENT_TYPE_TRANSACTION_RELATED, 
	                      entry_index, 
						  (st_common_event_params_short_t *)p_entry_buff);


    return TRUE;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj12_att02_ConvertRtcRangeToIndex_UserCode
* Description   : Object name		: Event profile Trans
*				  Logical name		: 0.0.99.98.3.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
* Arguments     : class07_range_descriptor_t *p_range_request - Input
*                   This is RTC range request by Client.
*				  uint16_t *p_out_from_entry - Output
*					This is index of the first entry match RTC start time
*				  uint16_t *p_out_to_entry - Output
*					This is index of the last entry match RTC end time
*				  void	*p_out_total_entries - Output
*                   Total entry found from [StartTime to EndTime]
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic07_obj12_att02_ConvertRtcRangeToIndex_UserCode(
	class07_range_descriptor_t *p_range_request,
	uint16_t *p_out_from_entry_index,
	uint16_t *p_out_to_entry_index,
    uint16_t *p_out_total_entries
)
{
    uint32_t entry_index_start;
    uint32_t entry_index_end;
    uint8_t is_found_start = FALSE;
    uint8_t is_found_end = FALSE;
	distributor_params_t * p_params = NULL;

	Event_profile_Trans_Obj12_DLMSEntry_t entry_get;
	uint32_t entries_in_use;
	uint16_t i;
	int8_t result;

	R_DLMS_USER_ic07_obj12_att07_get(p_params, &entries_in_use);
    /* 
     *  +----------------------------------+------------------------+
     *  |  Client request                  | Output                 |
     *  |  (Date time value)               | (Index value)          |
     *  | ---------------------------------+------------------------|
     *  | p_range_request->p_from_value    | p_out_from_entry       |
     *  | p_range_request->p_to_value      | p_out_to_entry         |
     *  |                                  | total entry found      |
     *  +-----------------------------------------------------------+
     */
   
    /* 
     * Request from client
     *
     * range_descriptor ::= structure           | Eg:
     * {                                        |       Class   LN              AttbIndex  DataIndex(Option)
     *      restricting_object                  |       08      A.B.C.D.E.F     02         00
     *      from_value                          | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      to_value                            | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      selected_value                      | All column
     * }   
     */

	/* Check input */
	if(p_range_request->p_from_value->choice.size != 12 && p_range_request->p_to_value->choice.size != 12)
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
        *p_out_total_entries = 0;
		return;
	}
	/* Check to value with the first entry */
	/* Get first entry to check time */
	R_DLMS_USER_ic07_obj12_att02_CopyToBuffer_UserCode(0, 0, &entry_get);
	if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						       *(date_time_t *)p_range_request->p_to_value->buffer) > 0)
	{
		/* If date time of entry is bigger than 'to value', return to range is out of value */
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
		return;
	}
	/* find start and end position */
	for(i = 0; i < entries_in_use; i++)
	{
		/* Get entry to check time */
		R_DLMS_USER_ic07_obj12_att02_CopyToBuffer_UserCode(0, i, &entry_get);

		if(is_found_start == FALSE)
		{
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_from_value->buffer) >= 0)
			{
				entry_index_start = i;
				is_found_start = TRUE;
			}
		}
		else
		{
			result = R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_to_value->buffer);
			if (result > 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = i - 1;
				is_found_end = TRUE;
				break;
			}
			else if(result ==0)
			{
				/* If date time of entry is equal 'to value', the end index is this index */
				entry_index_end = i;
				is_found_end = TRUE;
				break;
			}
			else
			{}
		}
		
	}
	/* If found start entry and not found end entry, check for 'to value' that it is over than the biggest */
	if(is_found_start == TRUE && is_found_end == FALSE)
	{
			/* If 'to value' bigger than the last entry, set to value to biggest entry index */
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						              *(date_time_t *)p_range_request->p_to_value->buffer) < 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = entries_in_use - 1;
				is_found_end = TRUE;
			}
	}
	if (entry_index_end < entry_index_start || (is_found_start == FALSE) || (is_found_end == FALSE))
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
	}
	else
	{
		*p_out_from_entry_index = entry_index_start;
		*p_out_to_entry_index = entry_index_end;
		*p_out_total_entries = (entry_index_end - entry_index_start) + 1;
	}
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj12_att02_get
* Description   : Object name		: Event profile Trans
*				  Logical name		: 0.0.99.98.3.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*				  Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj12_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* *IMPORTANT INFORMATION* */
	/* This is selective access, you need to create ENCODE FUNCTION by manual */
	/* This attribute does not support for automatic encoding */

	/* Start user code here */
	Event_profile_Trans_Obj12_DLMSEntry_t temp_buffer;
	uint8_t is_rollover;
	class07_obj_one_entry_descriptor_t frame_format;
	uint32_t entries_in_use;

	
	/* Set value entries in use */
	R_DLMS_USER_ic07_obj12_att07_get(p_params, &entries_in_use);

	frame_format.p_frame_format = (class07_obj_frame_format_t *)g_class07_frame_format_Event_profile_Trans_Obj12;
	frame_format.frame_format_size = g_class07_frame_format_Event_profile_Trans_Obj12_size;
	frame_format.p_data = (uint8_t *)&temp_buffer;
	frame_format.fn_buff_fill = R_DLMS_USER_ic07_obj12_att02_CopyToBuffer_UserCode;
	frame_format.fn_by_range_filter = R_DLMS_USER_ic07_obj12_att02_ConvertRtcRangeToIndex_UserCode;
	R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
		p_params,
		entries_in_use,
		&frame_format);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



/*******************************************************************************
* Variable name: g_dlms_ic07_obj12_att03_capture_objects
* Object name: Event profile Trans
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj12_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj12_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj12_date_and_time_of_event[6] 	 = { 0, 0, 1, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj12_event_code[6] 	 = { 0, 0, 96, 11, 3, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj12_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 8, { (uint8_t *)&g_OBIS_CaptureObj12_date_and_time_of_event , 6 }, 2 },
	/* 01 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj12_event_code , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj12_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj12_att03_capture_objects_Element,
	2
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj12_att04_capture_period
* Object name: Event profile Trans
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj12_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj12_att05_sort_method
* Object name: Event profile Trans
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj12_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj12_att06_sort_object
* Object name: Event profile Trans
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj12_att06_sort_object  = 
/* 00 */  { 8, { (uint8_t *)&g_OBIS_CaptureObj12_date_and_time_of_event , 6 }, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj12_att07_get
* Description   : Object name       : Event profile Trans
*                 Object index      : 12
*                 Class             : 07
*                 Attribute order   : 07
*                 Attribute name    : entries_in_use
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj12_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 1;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_EntriesInUseGet(EVENT_TYPE_TRANSACTION_RELATED, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj12_att08_get
* Description   : Object name       : Event profile Trans
*                 Object index      : 12
*                 Class             : 07
*                 Attribute order   : 08
*                 Attribute name    : profile_entries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj12_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 1;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_ProfileEntriesGet(EVENT_TYPE_TRANSACTION_RELATED, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj12_meth01_action
* Description   : Object name       : Event profile Trans
*                 Object index      : 12
*                 Class             : 07
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj12_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Clears the buffer.It has no valid entries afterwards;
	* Entries_in_use is zero after this call.
	* This call does not trigger any additional operations on the capture objects.
	* Specifically, it does not reset any attributes captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if(R_EVENT_ResetLog(EVENT_TYPE_TRANSACTION_RELATED))
	{
									
	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;										
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj12_meth02_action
* Description   : Object name       : Event profile Trans
*                 Object index      : 12
*                 Class             : 07
*                 Method order      : 02
*                 Method name       : Capture
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj12_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Copies the values of the objects to capture into the buffer
	*  by reading each capture object.
	* Depending on the sort_method and the actual state of the buffer
	*  this produces a new entry or a replacement for the less significant entry.
	* As long as not all entries are already used,
	*  the entries_in_use attribute will be incremented.
	* This call does not trigger any additional operations within
	*  the capture objects such as capture () or reset ().
	* Note, that if more than one attribute of an object need to be captured,
	*  they have to be defined one by one on the list of capture_objects.
	* If the attribute_index = 0, all attributes are captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Event profile Voltage
* Object number:    13
* Object obis code: 0.0.99.98.0.255
***********************************************************************************************************/


const class07_obj_frame_format_t g_class07_frame_format_Event_profile_Voltage_Obj13[] = 
{
	{ TAG_DATA_OCTET_STRING, offsetof(Event_profile_Voltage_Obj13_DLMSEntry_t, date_and_time_of_event), 12}, 
	{ TAG_DATA_LONG_UNSIGNED, offsetof(Event_profile_Voltage_Obj13_DLMSEntry_t, event_code), 2}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Voltage_Obj13_DLMSEntry_t, current), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Voltage_Obj13_DLMSEntry_t, voltage), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Voltage_Obj13_DLMSEntry_t, power_factor), 4}, 
	{ TAG_DATA_FLOAT32, offsetof(Event_profile_Voltage_Obj13_DLMSEntry_t, cumulative_energy_kwh), 4}, 
	{ TAG_DATA_DOUBLE_LONG_UNSIGNED, offsetof(Event_profile_Voltage_Obj13_DLMSEntry_t, cumulative_tamper_count), 4}, 

};
const uint8_t g_class07_frame_format_Event_profile_Voltage_Obj13_size = sizeof(g_class07_frame_format_Event_profile_Voltage_Obj13) / sizeof(class07_obj_frame_format_t);

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj13_att02_CopyToBuffer
* Description   : Object name		: Event profile Voltage
*				  Logical name		: 0.0.99.98.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer
* Arguments     : uint16_t child_index -
*                   This is index this object in child record.
*				  uint16_t entry_index -
*					This is index
*				  void	*p_entry_buff -
*					
* Return Value  : uint8_t - TRUE executes successfully, else is FALSE
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj13_att02_CopyToBuffer_UserCode(
	uint16_t child_index,
	uint16_t entry_index,
	void	*p_entry_buff
)
{
	/* This function use to assign value for each entry */
	/* Please assign your value of each element of capture object */
	
	//Event_profile_Voltage_Obj13_DLMSEntry_t *p_buff = (Event_profile_Voltage_Obj13_DLMSEntry_t *)p_entry_buff;
	
	/* Asign one by one below variable */



	if (p_entry_buff == NULL)
	{
		return FALSE;
	}


	/* Add check entry index < number entry of your capture object table */
	/* Start user code */
	/* TODO - User code need to implement here */
	if(entry_index > VOLTAGE_EVENTS_MAX_ENTRIES)
	{
		return FALSE;
	}
	/* End of user code */

	/*************************************************************************/
	/* date_and_time_of_event_linking_data = entry[entry_index].date_and_time_of_event */
	/* event_code_linking_data = entry[entry_index].event_code */
	/* current_linking_data = entry[entry_index].current */
	/* voltage_linking_data = entry[entry_index].voltage */
	/* power_factor_linking_data = entry[entry_index].power_factor */
	/* cumulative_energy_kwh_linking_data = entry[entry_index].cumulative_energy_kwh */
	/* cumulative_tamper_count_linking_data = entry[entry_index].cumulative_tamper_count */
	/*************************************************************************/

	/* Start user code */
	/* TODO - User code need to implement here */

	/* End of user code */
	/* Get event record from event application */
	event_long_params_get(EVENT_TYPE_VOLTAGE_RELATED, 
	                      entry_index, 
						  (st_common_event_params_long_t *)p_entry_buff);


    return TRUE;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj13_att02_ConvertRtcRangeToIndex_UserCode
* Description   : Object name		: Event profile Voltage
*				  Logical name		: 0.0.99.98.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
* Arguments     : class07_range_descriptor_t *p_range_request - Input
*                   This is RTC range request by Client.
*				  uint16_t *p_out_from_entry - Output
*					This is index of the first entry match RTC start time
*				  uint16_t *p_out_to_entry - Output
*					This is index of the last entry match RTC end time
*				  void	*p_out_total_entries - Output
*                   Total entry found from [StartTime to EndTime]
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_ic07_obj13_att02_ConvertRtcRangeToIndex_UserCode(
	class07_range_descriptor_t *p_range_request,
	uint16_t *p_out_from_entry_index,
	uint16_t *p_out_to_entry_index,
    uint16_t *p_out_total_entries
)
{
    uint32_t entry_index_start;
    uint32_t entry_index_end;
    uint8_t is_found_start = FALSE;
    uint8_t is_found_end = FALSE;
	distributor_params_t * p_params = NULL;

	Event_profile_Voltage_Obj13_DLMSEntry_t entry_get;
	uint32_t entries_in_use;
	uint16_t i;
	int8_t result;

	R_DLMS_USER_ic07_obj13_att07_get(p_params, &entries_in_use);
    /* 
     *  +----------------------------------+------------------------+
     *  |  Client request                  | Output                 |
     *  |  (Date time value)               | (Index value)          |
     *  | ---------------------------------+------------------------|
     *  | p_range_request->p_from_value    | p_out_from_entry       |
     *  | p_range_request->p_to_value      | p_out_to_entry         |
     *  |                                  | total entry found      |
     *  +-----------------------------------------------------------+
     */
   
    /* 
     * Request from client
     *
     * range_descriptor ::= structure           | Eg:
     * {                                        |       Class   LN              AttbIndex  DataIndex(Option)
     *      restricting_object                  |       08      A.B.C.D.E.F     02         00
     *      from_value                          | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      to_value                            | (Octe) (Len) (Data)
     *                                          |    09    12   <DateTimeData>
     *      selected_value                      | All column
     * }   
     */

	/* Check input */
	if(p_range_request->p_from_value->choice.size != 12 && p_range_request->p_to_value->choice.size != 12)
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
        *p_out_total_entries = 0;
		return;
	}
	/* Check to value with the first entry */
	/* Get first entry to check time */
	R_DLMS_USER_ic07_obj13_att02_CopyToBuffer_UserCode(0, 0, &entry_get);
	if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						       *(date_time_t *)p_range_request->p_to_value->buffer) > 0)
	{
		/* If date time of entry is bigger than 'to value', return to range is out of value */
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
		return;
	}
	/* find start and end position */
	for(i = 0; i < entries_in_use; i++)
	{
		/* Get entry to check time */
		R_DLMS_USER_ic07_obj13_att02_CopyToBuffer_UserCode(0, i, &entry_get);

		if(is_found_start == FALSE)
		{
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_from_value->buffer) >= 0)
			{
				entry_index_start = i;
				is_found_start = TRUE;
			}
		}
		else
		{
			result = R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
									   *(date_time_t *)p_range_request->p_to_value->buffer);
			if (result > 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = i - 1;
				is_found_end = TRUE;
				break;
			}
			else if(result ==0)
			{
				/* If date time of entry is equal 'to value', the end index is this index */
				entry_index_end = i;
				is_found_end = TRUE;
				break;
			}
			else
			{}
		}
		
	}
	/* If found start entry and not found end entry, check for 'to value' that it is over than the biggest */
	if(is_found_start == TRUE && is_found_end == FALSE)
	{
			/* If 'to value' bigger than the last entry, set to value to biggest entry index */
			if (R_DLMS_CompareDateTime(*(date_time_t *)&entry_get.date_and_time_of_event,
						              *(date_time_t *)p_range_request->p_to_value->buffer) < 0)
			{
				/* If date time of entry is bigger than 'to value', the end index is before of this index */
				entry_index_end = entries_in_use - 1;
				is_found_end = TRUE;
			}
	}
	if (entry_index_end < entry_index_start || (is_found_start == FALSE) || (is_found_end == FALSE))
	{
		*p_out_from_entry_index = 0;
		*p_out_to_entry_index = 0;
		*p_out_total_entries = 0;
	}
	else
	{
		*p_out_from_entry_index = entry_index_start;
		*p_out_to_entry_index = entry_index_end;
		*p_out_total_entries = (entry_index_end - entry_index_start) + 1;
	}
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj13_att02_get
* Description   : Object name		: Event profile Voltage
*				  Logical name		: 0.0.99.98.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ;
*				  Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj13_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* *IMPORTANT INFORMATION* */
	/* This is selective access, you need to create ENCODE FUNCTION by manual */
	/* This attribute does not support for automatic encoding */

	/* Start user code here */
	Event_profile_Voltage_Obj13_DLMSEntry_t temp_buffer;
	uint8_t is_rollover;
	class07_obj_one_entry_descriptor_t frame_format;
	uint32_t entries_in_use;

	
	/* Set value entries in use */
	R_DLMS_USER_ic07_obj13_att07_get(p_params, &entries_in_use);

	frame_format.p_frame_format = (class07_obj_frame_format_t *)g_class07_frame_format_Event_profile_Voltage_Obj13;
	frame_format.frame_format_size = g_class07_frame_format_Event_profile_Voltage_Obj13_size;
	frame_format.p_data = (uint8_t *)&temp_buffer;
	frame_format.fn_buff_fill = R_DLMS_USER_ic07_obj13_att02_CopyToBuffer_UserCode;
	frame_format.fn_by_range_filter = R_DLMS_USER_ic07_obj13_att02_ConvertRtcRangeToIndex_UserCode;
	R_MakeBuffer_HistoricalData_SupportBlockTransfer_Class07(
		p_params,
		entries_in_use,
		&frame_format);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}



/*******************************************************************************
* Variable name: g_dlms_ic07_obj13_att03_capture_objects
* Object name: Event profile Voltage
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj13_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj13_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj13_date_and_time_of_event[6] 	 = { 0, 0, 1, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj13_event_code[6] 	 = { 0, 0, 96, 11, 0, 255 };
const uint8_t g_OBIS_CaptureObj13_current[6] 	 = { 1, 0, 94, 91, 14, 255 };
const uint8_t g_OBIS_CaptureObj13_voltage[6] 	 = { 1, 0, 12, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj13_power_factor[6] 	 = { 1, 0, 13, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj13_cumulative_energy_kwh[6] 	 = { 1, 0, 1, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj13_cumulative_tamper_count[6] 	 = { 0, 0, 94, 91, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj13_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 8, { (uint8_t *)&g_OBIS_CaptureObj13_date_and_time_of_event , 6 }, 2 },
	/* 01 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj13_event_code , 6 }, 2 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj13_current , 6 }, 2 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj13_voltage , 6 }, 2 },
	/* 04 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj13_power_factor , 6 }, 2 },
	/* 05 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj13_cumulative_energy_kwh , 6 }, 2 },
	/* 06 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj13_cumulative_tamper_count , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj13_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj13_att03_capture_objects_Element,
	7
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj13_att04_capture_period
* Object name: Event profile Voltage
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj13_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj13_att05_sort_method
* Object name: Event profile Voltage
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj13_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj13_att06_sort_object
* Object name: Event profile Voltage
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj13_att06_sort_object  = 
/* 00 */  { 8, { (uint8_t *)&g_OBIS_CaptureObj13_date_and_time_of_event , 6 }, 2 };


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj13_att07_get
* Description   : Object name       : Event profile Voltage
*                 Object index      : 13
*                 Class             : 07
*                 Attribute order   : 07
*                 Attribute name    : entries_in_use
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj13_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 1;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_EntriesInUseGet(EVENT_TYPE_VOLTAGE_RELATED, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj13_att08_get
* Description   : Object name       : Event profile Voltage
*                 Object index      : 13
*                 Class             : 07
*                 Attribute order   : 08
*                 Attribute name    : profile_entries
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj13_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint32_t(double-long-unsigned)
	*********************************************/

	/**************************************************************
	This is enum of return result value. 
	Default is VAL_DATA_ACCESS_RESULT_OTHER_REASON
	 typedef enum																																					*
	 {																																								*
	 	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,																									*
	 	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,																									*
	 	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,																									*
	 	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,																									*
	 	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,																									*
	 	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,																									*
	 	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,																									*
	 	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,																									*
	 	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,																									*
	 	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,																									*
	  	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,																									*
	 } DataAccessResult_Value;	
	***************************************************************/
	/* Attribute setting generated code */
	/* Please refer this code to custom for your application */
	/* Assign link data here */
	//uint32_t link_data = 1;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	if(R_EVENT_ProfileEntriesGet(EVENT_TYPE_VOLTAGE_RELATED, p_attribute_get))
	{

	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj13_meth01_action
* Description   : Object name       : Event profile Voltage
*                 Object index      : 13
*                 Class             : 07
*                 Method order      : 01
*                 Method name       : Reset
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj13_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Clears the buffer.It has no valid entries afterwards;
	* Entries_in_use is zero after this call.
	* This call does not trigger any additional operations on the capture objects.
	* Specifically, it does not reset any attributes captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */
	if(R_EVENT_ResetLog(EVENT_TYPE_VOLTAGE_RELATED))
	{
								
	}
	else
	{
		return VAL_ACTION_RESULT_TYPE_UNMATCHED;									
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj13_meth02_action
* Description   : Object name       : Event profile Voltage
*                 Object index      : 13
*                 Class             : 07
*                 Method order      : 02
*                 Method name       : Capture
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj13_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Copies the values of the objects to capture into the buffer
	*  by reading each capture object.
	* Depending on the sort_method and the actual state of the buffer
	*  this produces a new entry or a replacement for the less significant entry.
	* As long as not all entries are already used,
	*  the entries_in_use attribute will be incremented.
	* This call does not trigger any additional operations within
	*  the capture objects such as capture () or reset ().
	* Note, that if more than one attribute of an object need to be captured,
	*  they have to be defined one by one on the list of capture_objects.
	* If the attribute_index = 0, all attributes are captured.
	* p_data_from_client ::= integer(0)->NOT REQUIREMENT.
	*************************************************************************/


	/**************************************************************
	This is enum of return result value. 
	Default is VAL_ACTION_RESULT_OTHER_REASON
	* typedef enum																															 *
	* {																																		 *
	* 	VAL_ACTION_RESULT_SUCCESS 						= 0   ,																				 *
	* 	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,																				 *
	* 	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,																				 *
	* 	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,																				 *
	* 	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,																				 *
	* 	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,																				 *
	* 	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,																				 *
	* 	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,																				 *
	* 	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,																				 *
	* 	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,																				 *
	* 	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,																				 *
	* } ActionResult_Value;																													 *
	
	*****************************************************************/
	/* Start user code here */

	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}


/***********************************************************************************************************
* Object name:      Instant parameters snapshot
* Object number:    14
* Object obis code: 1.0.94.91.0.255
***********************************************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj14_att02_get
* Description   : Object name		: Instant parameters snapshot
*				  Logical name		: 1.0.94.91.0.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj14_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* Start user code here */
	R_MakeBuffer_RealTime_SupportBlockTransfer_Class07(p_params);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/*******************************************************************************
* Variable name: g_dlms_ic07_obj14_att03_capture_objects
* Object name: Instant parameters snapshot
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj14_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj14_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj14_date_and_time[6] 	 = { 0, 0, 1, 0, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_voltage[6] 	 = { 1, 0, 12, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_phase_current[6] 	 = { 1, 0, 11, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_neutral_current[6] 	 = { 1, 0, 91, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_signed_power_factor[6] 	 = { 1, 0, 13, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_frequency[6] 	 = { 1, 0, 14, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_apparent_power_kwa[6] 	 = { 1, 0, 9, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_active_power_kw[6] 	 = { 1, 0, 1, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_cumulative_energy_kwh_import[6] 	 = { 1, 0, 1, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_cumulative_energy_kvah_import[6] 	 = { 1, 0, 9, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_maximum_demand_kw[6] 	 = { 1, 0, 1, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_maximum_demand_kw_capture_time[6] 	 = { 1, 0, 1, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_maximum_demand_kva[6] 	 = { 1, 0, 9, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_maximum_demand_kva_capture_time[6] 	 = { 1, 0, 9, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_cumulative_power_on_duration_in_min[6] 	 = { 0, 0, 94, 91, 14, 255 };
const uint8_t g_OBIS_CaptureObj14_cumulative_tamper_count[6] 	 = { 0, 0, 94, 91, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_cumulative_billing_count[6] 	 = { 0, 0, 0, 1, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_cummulative_programming_count[6] 	 = { 0, 0, 96, 2, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_cummulative_energy_kwh_export[6] 	 = { 1, 0, 2, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_cummulative_energy_kvah_export[6] 	 = { 1, 0, 10, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj14_load_limit_function[6] 	 = { 0, 0, 96, 3, 10, 255 };
const uint8_t g_OBIS_CaptureObj14_load_switch_status[6] 	 = { 0, 0, 17, 0, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj14_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 8, { (uint8_t *)&g_OBIS_CaptureObj14_date_and_time , 6 }, 2 },
	/* 01 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_voltage , 6 }, 2 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_phase_current , 6 }, 2 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_neutral_current , 6 }, 2 },
	/* 04 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_signed_power_factor , 6 }, 2 },
	/* 05 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_frequency , 6 }, 2 },
	/* 06 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_apparent_power_kwa , 6 }, 2 },
	/* 07 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_active_power_kw , 6 }, 2 },
	/* 08 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_cumulative_energy_kwh_import , 6 }, 2 },
	/* 09 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_cumulative_energy_kvah_import , 6 }, 2 },
	/* 10 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj14_maximum_demand_kw , 6 }, 2 },
	/* 11 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj14_maximum_demand_kw_capture_time , 6 }, 5 },
	/* 12 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj14_maximum_demand_kva , 6 }, 2 },
	/* 13 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj14_maximum_demand_kva_capture_time , 6 }, 5 },
	/* 14 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_cumulative_power_on_duration_in_min , 6 }, 2 },
	/* 15 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj14_cumulative_tamper_count , 6 }, 2 },
	/* 16 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj14_cumulative_billing_count , 6 }, 2 },
	/* 17 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj14_cummulative_programming_count , 6 }, 2 },
	/* 18 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_cummulative_energy_kwh_export , 6 }, 2 },
	/* 19 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj14_cummulative_energy_kvah_export , 6 }, 2 },
	/* 20 */  	{ 70, { (uint8_t *)&g_OBIS_CaptureObj14_load_limit_function , 6 }, 2 },
	/* 21 */  	{ 71, { (uint8_t *)&g_OBIS_CaptureObj14_load_switch_status , 6 }, 3 },
};

const class07_obj_def_array_t g_dlms_ic07_obj14_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj14_att03_capture_objects_Element,
	22
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj14_att04_capture_period
* Object name: Instant parameters snapshot
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj14_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj14_att05_sort_method
* Object name: Instant parameters snapshot
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj14_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj14_att06_sort_object
* Object name: Instant parameters snapshot
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj14_att06_sort_object  = 
/* 00 */  { 8, { (uint8_t *)&g_OBIS_CaptureObj14_date_and_time , 6 }, 2 };


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj14_att07_entries_in_use
* Object name: Instant parameters snapshot
* Attribute order: 07
* Attribute name: entries_in_use
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of entries_in_use (class - 07, atrribute - 07)*/
const uint32_t g_dlms_ic07_obj14_att07_entries_in_use  = 1;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj14_att08_profile_entries
* Object name: Instant parameters snapshot
* Attribute order: 08
* Attribute name: profile_entries
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of profile_entries (class - 07, atrribute - 08)*/
const uint32_t g_dlms_ic07_obj14_att08_profile_entries  = 1;




/***********************************************************************************************************
* Object name:      Instant Scaler Profile
* Object number:    15
* Object obis code: 1.0.94.91.3.255
***********************************************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj15_att02_get
* Description   : Object name		: Instant Scaler Profile
*				  Logical name		: 1.0.94.91.3.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj15_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* Start user code here */
	R_MakeBuffer_RealTime_SupportBlockTransfer_Class07(p_params);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/*******************************************************************************
* Variable name: g_dlms_ic07_obj15_att03_capture_objects
* Object name: Instant Scaler Profile
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj15_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj15_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj15_voltage[6] 	 = { 1, 0, 12, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_phase_current[6] 	 = { 1, 0, 11, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_neutral_current[6] 	 = { 1, 0, 91, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_signed_power_factor[6] 	 = { 1, 0, 13, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_frequency_hz[6] 	 = { 1, 0, 14, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_apparent_power_kva[6] 	 = { 1, 0, 9, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_active_power_kw[6] 	 = { 1, 0, 1, 7, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_cumulative_energy_kwh_import[6] 	 = { 1, 0, 1, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_cumulative_energy_kvah_import[6] 	 = { 1, 0, 9, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_maximum_demand_kw[6] 	 = { 1, 0, 1, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_maximum_demand__kva[6] 	 = { 1, 0, 9, 6, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_cumulative_power_on_durarion_in_min[6] 	 = { 0, 0, 94, 91, 14, 255 };
const uint8_t g_OBIS_CaptureObj15_cumulative_energy_kwh_export[6] 	 = { 1, 0, 2, 8, 0, 255 };
const uint8_t g_OBIS_CaptureObj15_cumulative_energy_kvah_export[6] 	 = { 1, 0, 10, 8, 0, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj15_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_voltage , 6 }, 3 },
	/* 01 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_phase_current , 6 }, 3 },
	/* 02 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_neutral_current , 6 }, 3 },
	/* 03 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_signed_power_factor , 6 }, 3 },
	/* 04 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_frequency_hz , 6 }, 3 },
	/* 05 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_apparent_power_kva , 6 }, 3 },
	/* 06 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_active_power_kw , 6 }, 3 },
	/* 07 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_cumulative_energy_kwh_import , 6 }, 3 },
	/* 08 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_cumulative_energy_kvah_import , 6 }, 3 },
	/* 09 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj15_maximum_demand_kw , 6 }, 3 },
	/* 10 */  	{ 4, { (uint8_t *)&g_OBIS_CaptureObj15_maximum_demand__kva , 6 }, 3 },
	/* 11 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_cumulative_power_on_durarion_in_min , 6 }, 3 },
	/* 12 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_cumulative_energy_kwh_export , 6 }, 3 },
	/* 13 */  	{ 3, { (uint8_t *)&g_OBIS_CaptureObj15_cumulative_energy_kvah_export , 6 }, 3 },
};

const class07_obj_def_array_t g_dlms_ic07_obj15_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj15_att03_capture_objects_Element,
	14
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj15_att04_capture_period
* Object name: Instant Scaler Profile
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj15_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj15_att05_sort_method
* Object name: Instant Scaler Profile
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj15_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj15_att06_sort_object
* Object name: Instant Scaler Profile
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj15_att06_sort_object  = 
/* 00 */  { 3, { (uint8_t *)&g_OBIS_CaptureObj15_voltage , 6 }, 3 };


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj15_att07_entries_in_use
* Object name: Instant Scaler Profile
* Attribute order: 07
* Attribute name: entries_in_use
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of entries_in_use (class - 07, atrribute - 07)*/
const uint32_t g_dlms_ic07_obj15_att07_entries_in_use  = 1;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj15_att08_profile_entries
* Object name: Instant Scaler Profile
* Attribute order: 08
* Attribute name: profile_entries
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of profile_entries (class - 07, atrribute - 08)*/
const uint32_t g_dlms_ic07_obj15_att08_profile_entries  = 1;




/***********************************************************************************************************
* Object name:      Name Plate Profile
* Object number:    16
* Object obis code: 0.0.94.91.10.255
***********************************************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_USER_ic07_obj16_att02_get
* Description   : Object name		: Name Plate Profile
*				  Logical name		: 0.0.94.91.10.255
*				  Class				: 07
*				  Attribute order	: 02
*				  Attribute name	: buffer 
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object      : None
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj16_att02_get(distributor_params_t *p_params, class07_buffer_array_t *p_attribute_get)
{
	/* Start user code here */
	R_MakeBuffer_RealTime_SupportBlockTransfer_Class07(p_params);
	/* End user code here */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}


/*******************************************************************************
* Variable name: g_dlms_ic07_obj16_att03_capture_objects
* Object name: Name Plate Profile
* Attribute order: 03
* Attribute name: capture objects
* Association access: {1, Meter Reader}; {2, Utility Setting};  
* Group object		: None
* TODO: need to assign value of under constant array
* class07_obj_def_array_t g_dlms_ic07_obj16_att03_capture_objects = {[1], [2]}
* [1] - &g_dlms_ic07_obj16_att03_capture_objects_Element[]
* [2] - length of array
*******************************************************************************/
const uint8_t g_OBIS_CaptureObj16_meter_serial_number[6] 	 = { 0, 0, 96, 1, 0, 255 };
const uint8_t g_OBIS_CaptureObj16_device_id[6] 	 = { 0, 0, 96, 1, 2, 255 };
const uint8_t g_OBIS_CaptureObj16_manufacture_name[6] 	 = { 0, 0, 96, 1, 1, 255 };
const uint8_t g_OBIS_CaptureObj16_firmware_version[6] 	 = { 1, 0, 0, 2, 0, 255 };
const uint8_t g_OBIS_CaptureObj16_meter_type[6] 	 = { 0, 0, 94, 91, 9, 255 };
const uint8_t g_OBIS_CaptureObj16_category[6] 	 = { 0, 0, 94, 91, 11, 255 };
const uint8_t g_OBIS_CaptureObj16_current_rating[6] 	 = { 0, 0, 94, 91, 12, 255 };
const uint8_t g_OBIS_CaptureObj16_year_of_manufacture[6] 	 = { 0, 0, 96, 1, 4, 255 };

const class07_obj_def_t 		g_dlms_ic07_obj16_att03_capture_objects_Element[] = 
{
	/* 00 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj16_meter_serial_number , 6 }, 2 },
	/* 01 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj16_device_id , 6 }, 2 },
	/* 02 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj16_manufacture_name , 6 }, 2 },
	/* 03 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj16_firmware_version , 6 }, 2 },
	/* 04 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj16_meter_type , 6 }, 2 },
	/* 05 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj16_category , 6 }, 2 },
	/* 06 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj16_current_rating , 6 }, 2 },
	/* 07 */  	{ 1, { (uint8_t *)&g_OBIS_CaptureObj16_year_of_manufacture , 6 }, 2 },
};

const class07_obj_def_array_t g_dlms_ic07_obj16_att03_capture_objects =
{
	(class07_obj_def_t *)&g_dlms_ic07_obj16_att03_capture_objects_Element,
	8
};


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj16_att04_capture_period
* Object name: Name Plate Profile
* Attribute order: 04
* Attribute name: capture_period
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of capture_period (class - 07, atrribute - 04)*/
const uint32_t g_dlms_ic07_obj16_att04_capture_period  = 0;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj16_att05_sort_method
* Object name: Name Plate Profile
* Attribute order: 05
* Attribute name: sort_method
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
class07_sort_method_t
{
    FIFO = 1,
    LIFO,
    LARGEST,
    SMALLEST,
    NEAREST_TO_ZERO,
    FAREST_FROM_ZERO
};
*********************************************/


/* Declare for variable of sort_method (class - 07, atrribute - 05)*/
const class07_sort_method_t g_dlms_ic07_obj16_att05_sort_method  = FIFO;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj16_att06_sort_object
* Object name: Name Plate Profile
* Attribute order: 06
* Attribute name: sort_object
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
FixedStringlogical_name:: =
{
    uint8        *logical_name_content;//logical_name_content :: uint8_t[6]
    uint16_t     length; 
};
class07_obj_def_t
{
     uint16_t           class_id;          / Class ID /
     FixedString        logical_name;      / The logical name /
     uint8_t            attribute_index;   / Atrribute index /
     uint16_t           data_index;        / Data index /
} ;
*********************************************/


/* Declare for variable of sort_object (class - 07, atrribute - 06)*/
const class07_obj_def_t g_dlms_ic07_obj16_att06_sort_object  = 
/* 00 */  { 1, { (uint8_t *)&g_OBIS_CaptureObj16_meter_serial_number , 6 }, 2 };


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj16_att07_entries_in_use
* Object name: Name Plate Profile
* Attribute order: 07
* Attribute name: entries_in_use
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of entries_in_use (class - 07, atrribute - 07)*/
const uint32_t g_dlms_ic07_obj16_att07_entries_in_use  = 1;


/*******************************************************************************
* Class ID: 07
* Variable name: g_dlms_ic07_obj16_att08_profile_entries
* Object name: Name Plate Profile
* Attribute order: 08
* Attribute name: profile_entries
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: None
*******************************************************************************/
/*********************************************
Data type:uint32_t(double-long-unsigned)
*********************************************/


/* Declare for variable of profile_entries (class - 07, atrribute - 08)*/
const uint32_t g_dlms_ic07_obj16_att08_profile_entries  = 1;




