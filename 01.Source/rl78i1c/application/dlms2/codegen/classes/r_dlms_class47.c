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
* File Name    : r_dlms_class47.c
* Version      : 1.00
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Processing for OBIS Class 47
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 27.03.2018 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_library_process.h"
#include "r_dlms_config.h"
#include "r_dlms_classes.h"
#include "r_dlms_class47.h"
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

VariantString *R_DLMS_CLASSES_RedirectClass47_Operator(distributor_params_t *p_params, VariantString *p_object, uint16_t size)
{
    VariantString *p_clone;
    uint8_t * p_alloc, *p_head;

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

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass47_CellInfo, class47_cell_info_type_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

#if CLASS_47_VERSION == 0
	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 4);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, 			(uint8_t *)&p_object->cell_ID, 			sizeof(uint16_t));
#elif CLASS_47_VERSION == 1
	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 7);
	{
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_DOUBLE_LONG_UNSIGNED, 	(uint8_t *)&p_object->cell_ID, 			sizeof(uint32_t));
#endif
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, 			(uint8_t *)&p_object->location_ID, 		sizeof(uint16_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, 				(uint8_t *)&p_object->signal_quality, 	sizeof(uint8_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, 				(uint8_t *)&p_object->ber, 				sizeof(uint8_t));
#if CLASS_47_VERSION == 1
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, 			(uint8_t *)&p_object->mcc, 				sizeof(uint16_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, 			(uint8_t *)&p_object->mnc, 				sizeof(uint16_t));
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_DOUBLE_LONG_UNSIGNED, 	(uint8_t *)&p_object->channel_number, 	sizeof(uint32_t));
#endif
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass47_CellInfo, class47_cell_info_type_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

#if CLASS_47_VERSION == 0
	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 4, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->cell_ID, 		sizeof(uint16_t), 	TAG_DATA_LONG_UNSIGNED, 		in_data);
#elif CLASS_47_VERSION == 1
	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 7, in_data);
	{
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->cell_ID, 		sizeof(uint32_t), 	TAG_DATA_DOUBLE_LONG_UNSIGNED, 	in_data);
#endif
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->location_ID, 	sizeof(uint16_t), 	TAG_DATA_LONG_UNSIGNED, 		in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->signal_quality, 	sizeof(uint8_t), 	TAG_DATA_UNSIGNED, 				in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->ber, 			sizeof(uint8_t), 	TAG_DATA_UNSIGNED, 				in_data);
#if CLASS_47_VERSION == 1
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->mcc, 			sizeof(uint16_t), 	TAG_DATA_LONG_UNSIGNED, 		in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->mnc, 			sizeof(uint16_t), 	TAG_DATA_LONG_UNSIGNED, 		in_data);
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->channel_number, 	sizeof(uint32_t), 	TAG_DATA_DOUBLE_LONG_UNSIGNED, 	in_data);
#endif

	}
	OBIS_TYPE_DECODER_FUNC_RET();
}

OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass47_CellInfo, class47_cell_info_type_t)
{
    class47_cell_info_type_t        *p_clone_obj;
    uint8_t							*p_alloc, *p_head;

    ASSERT_TRUE_RET_VAL(p_params == NULL || OBIS_MALLOC_IS_NULL(p_params), NULL);

    p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);

    OBIS_MALLOC_ASSIGN_OBJECT(p_clone_obj, class47_cell_info_type_t, p_alloc);

    ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
    OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));

    return p_clone_obj;
}

OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass47_CellInfo,
	class47_cell_info_type_t,
	R_DLMS_CLASSES_EncodeClass47_CellInfo,
	R_DLMS_CLASSES_DecodeClass47_CellInfo,
    R_DLMS_CLASSES_RedirectClass47_CellInfo
);

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass47_AdjacentCellInfo, class47_adjacent_cell_info_t)
{
	OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS;
	OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK();

	OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, out_data, 2);
	{
#if CLASS_47_VERSION == 0
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_LONG_UNSIGNED, 			(uint8_t *)&p_object->cell_ID, 			sizeof(uint16_t));
#elif CLASS_47_VERSION == 1
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_DOUBLE_LONG_UNSIGNED, 	(uint8_t *)&p_object->cell_ID, 			sizeof(uint32_t));
#endif
		OBIS_ENCODE_THEN_ADVANCE_BUF(length, out_data, TAG_DATA_UNSIGNED, 				(uint8_t *)&p_object->signal_quality, 	sizeof(uint8_t));
	}

	OBIS_TYPE_ENCODER_FUNC_RET();
}

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass47_AdjacentCellInfo, class47_adjacent_cell_info_t)
{
	OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS;
	OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK();

	OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, &length, 2, in_data);
	{
#if CLASS_47_VERSION == 0
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->cell_ID, 		sizeof(uint16_t), 	TAG_DATA_LONG_UNSIGNED, 		in_data);
#elif CLASS_47_VERSION == 1
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->cell_ID, 		sizeof(uint32_t), 	TAG_DATA_DOUBLE_LONG_UNSIGNED, 	in_data);
#endif
		OBIS_DECODE_THEN_ADVANCE_BUF(length, (uint8_t *)&p_object->signal_quality, 	sizeof(uint8_t), 	TAG_DATA_UNSIGNED, 				in_data);
	}
	OBIS_TYPE_DECODER_FUNC_RET();
}

OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(
	R_DLMS_CLASSES_EncodeClass47_AdjacentCells,			/* Array encode function */
	class47_adjacent_cells_t,							/* Array data type */
	R_DLMS_CLASSES_EncodeClass47_AdjacentCellInfo		/* Element encode function */
);

OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(
	R_DLMS_CLASSES_DecodeClass47_AdjacentCells,			/* Array decode function */
	class47_adjacent_cells_t,							/* Array data type */
	R_DLMS_CLASSES_DecodeClass47_AdjacentCellInfo		/* Element decode function */
);

class47_adjacent_cells_t *R_DLMS_CLASSES_RedirectClass47_AdjacentCells(distributor_params_t *p_params, class47_adjacent_cells_t *p_object, uint16_t array_size)
{
    class47_adjacent_cells_t		*p_clone;
    uint8_t							*p_alloc, *p_head;

    if (p_object == NULL)
    {
        p_head = p_alloc = OBIS_MALLOC_GET_POINTER(p_params);
        OBIS_MALLOC_ASSIGN_OBJECT(p_clone, class47_adjacent_cells_t, p_alloc);
        OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_clone, array_size, class47_adjacent_cell_info_t, p_alloc);
		p_clone->p_active = NULL;
        ASSERT_TRUE_RET_NULL((uint16_t)(p_alloc - p_head) > OBIS_MALLOC_REMAIN_SIZE(p_params));
        OBIS_MALLOC_ADVANCE_BUFFER(p_params, (uint16_t)(p_alloc - p_head));
    }
    else
    {
        p_clone = (class47_adjacent_cells_t *)R_DLMS_CLASSES_CreateVariantArray(
            p_params,
            (AbstractVariantArray *)p_object,
            sizeof(class47_adjacent_cell_info_t),
            OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE);
    }

    return p_clone;
}

OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(
	R_DLMS_CLASSES_DistributeClass47_AdjacentCells,
	class47_adjacent_cells_t,
	R_DLMS_CLASSES_EncodeClass47_AdjacentCells,
	R_DLMS_CLASSES_DecodeClass47_AdjacentCells,
    R_DLMS_CLASSES_RedirectClass47_AdjacentCells
);

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class47Init
* Interface     : void R_DLMS_CLASSES_Class47Init(void)
* Description   : Initialize class 47
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class47Init(void)
{
	/* Put init code of class 47 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class47PollingProcessing
* Interface     : void R_DLMS_CLASSES_Class47PollingProcessing(void)
* Description   : Polling process of class 47
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class47PollingProcessing(void)
{
	/* Put polling processing code of class 47 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class47AsscOpened
* Interface     : void R_DLMS_CLASSES_Class47AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association opened event for class 47
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class47AsscOpened(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc open event on class 47 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_Class47AsscClosing
* Interface     : void R_DLMS_CLASSES_Class47AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association closing event for class 47
* Arguments     : AsscConnectionSession * p_assc_session: Association connection session
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_Class47AsscClosing(AsscConnectionSession *p_assc_session)
{
	/* Put processing code for assc close event on class 47 here */
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeClass47
* Interface     : distributor_result_t R_DLMS_CLASSES_DistributeClass47(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Class distributor link (to master table) for class 47
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeClass47(distributor_params_t *p_params)
{
	R_DLMS_CLASSES_DistributeClass(
		R_DLMS_CLASSES_DistributeAbstractClass47,
		R_DLMS_OBJECTS_Class47Distributor,
		p_params
	);
}

/******************************************************************************
* Function Name : R_DLMS_CLASSES_DistributeAbstractClass47
* Interface     : void R_DLMS_CLASSES_DistributeAbstractClass47(
*               :     distributor_params_t * p_params,
*               : );
* Description   : Abstract class distributor function for class 47
* Arguments     : distributor_params_t * p_params: Distribution params from library
* Return Value  : None
******************************************************************************/
void R_DLMS_CLASSES_DistributeAbstractClass47(distributor_params_t *p_params)
{
	uint16_t				decoded_length;
	class47_child_record_t	*p_class47_obj = (class47_child_record_t *)p_params->p_child_record;

	if (p_params->req_type == REQ_TYPE_GET || p_params->req_type == REQ_TYPE_SET)
	{
		switch (p_params->descriptor.attr.attribute_id)
		{
            /* TODO : Put process code for each attrs of class 47 here, start from attr2 */
			case 2:	/* Network operator */
				R_DLMS_CLASSES_DistributeVisibleString(p_params, p_class47_obj->p_operator);
				break;
			case 3:	/* The registration status of the modem */
				R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class47_obj->p_status);
				break;
			case 4:	/* The current circuit switched status */
				R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class47_obj->p_cs_attachment);
				break;
			case 5:	/* The packet switched status of the modem. */
				R_DLMS_CLASSES_DistributeEnum(p_params, (uint8_t *)p_class47_obj->p_ps_status);
				break;
			case 6: /* Represents the cell information */
				R_DLMS_CLASSES_DistributeClass47_CellInfo(p_params, p_class47_obj->p_cell_info);
				break;
			case 7: /* Represents the cell information */
				R_DLMS_CLASSES_DistributeClass47_AdjacentCells(p_params, p_class47_obj->p_adjacent_cells);
				break;
			case 8: /* Date time */
				R_DLMS_CLASSES_DistributeDateTimeAsOctetString(p_params, p_class47_obj->p_capture_time);
				break;
			default:
				break;
		}
	}
	else if (p_params->req_type == REQ_TYPE_ACTION)
	{
        switch (p_params->descriptor.method.method_id)
		{
            /* TODO : Put process code for each method of class 47 here, start from method1 */
			case 1:	
				break;

			default:
				break;
		}
	}
}

