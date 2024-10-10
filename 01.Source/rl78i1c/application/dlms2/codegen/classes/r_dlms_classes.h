/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_classes.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef _R_DLMS_CLASSES_H
#define _R_DLMS_CLASSES_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_library_process.h"
#include "r_dlms_config.h"

/******************************************************************************
Macro definitions
******************************************************************************/

#define ASSERT_TRUE_BREAK(condition)				{ if ((condition)) { break; } }
#define ASSERT_TRUE_RET_VAL(condition, val)			{ if ((condition)) { return (val); } }
#define ASSERT_TRUE_RET_NULL(condition)				ASSERT_TRUE_RET_VAL(condition, NULL)
#define ASSERT_TRUE_RET_DIST_RESULT(condition)		ASSERT_TRUE_RET(condition)

/* Object visibility */
#define OBIS_AR_OBJ_IS_INVISIBLE 			(0)			/* Object is invisible         */
#define OBIS_AR_OBJ_IS_VISIBLE 				(1)			/* Object is visible           */

/*
 * Indicate to select the mechanism to support current association
 * TRUE : Replace current connected assc by 0.0.40.0.0.255 (current connected assc is invisible), or;
 * FALSE: Duplicate the current connected assc to 0.0.40.0.0.255 (current connected assc is visible)
 */
 #define SUPPORT_CURRENT_ASSC_AS_REPLACEMENT			(FALSE)

/*
 * For attributes access right encoding, attribute access_mode, bitwise
 */

#define OBIS_AR_ATTR_MAX_QUANTITY_SUPPORT		(64)		/* Please select value larger than 0 */
#if CLASS_15_VERSION == 0
#define OBIS_AR_ATTR_NO_ACCESS					(0x00)		/* No access                                                                 */
#define OBIS_AR_ATTR_READ						(0x01)		/* read-access                                                               */
#define OBIS_AR_ATTR_WRITE						(0x02)		/* Write access                                                              */
#define OBIS_AR_ATTR_AUTHEN_REQUEST				(0x00)		/* (0, no support, CLASS_15_VERSION v1, v2, v3 have) authenticated request   */
#define OBIS_AR_ATTR_ENCRYPTED_REQUEST			(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) encrypted request               */
#define OBIS_AR_ATTR_DIGITAL_SIGNED_REQUEST		(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) digitally signed request        */
#define OBIS_AR_ATTR_AUTHEN_RESPONSE			(0x00)		/* (0, no support, CLASS_15_VERSION v1, v2, v3 have) authenticated response  */
#define OBIS_AR_ATTR_ENCRYPTED_RESPONSE			(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) encrypted response              */
#define OBIS_AR_ATTR_DIGITAL_SIGNED_RESPONSE	(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) digitally signed response       */
#elif CLASS_15_VERSION == 1 || CLASS_15_VERSION == 2
#define OBIS_AR_ATTR_NO_ACCESS					(0x00)		/* No access                                                                 */
#define OBIS_AR_ATTR_READ						(0x01)		/* read-access                                                               */
#define OBIS_AR_ATTR_WRITE						(0x02)		/* Write access                                                              */
#define OBIS_AR_ATTR_AUTHEN_REQUEST				(0x04)		/* authenticated request                                                     */
#define OBIS_AR_ATTR_ENCRYPTED_REQUEST			(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) encrypted request               */
#define OBIS_AR_ATTR_DIGITAL_SIGNED_REQUEST		(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) digitally signed request        */
#define OBIS_AR_ATTR_AUTHEN_RESPONSE			(0x20)		/* authenticated response                                                    */
#define OBIS_AR_ATTR_ENCRYPTED_RESPONSE			(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) encrypted response              */
#define OBIS_AR_ATTR_DIGITAL_SIGNED_RESPONSE	(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) digitally signed response       */
#elif CLASS_15_VERSION == 3
#define OBIS_AR_ATTR_NO_ACCESS					(0x00)		/* No access                         */
#define OBIS_AR_ATTR_READ						(0x01)		/* read-access                       */
#define OBIS_AR_ATTR_WRITE						(0x02)		/* Write access                      */
#define OBIS_AR_ATTR_AUTHEN_REQUEST				(0x04)		/* authenticated request             */
#define OBIS_AR_ATTR_ENCRYPTED_REQUEST			(0x08)		/* encrypted request                 */
#define OBIS_AR_ATTR_DIGITAL_SIGNED_REQUEST		(0x10)		/* digitally signed request          */
#define OBIS_AR_ATTR_AUTHEN_RESPONSE			(0x20)		/* authenticated response            */
#define OBIS_AR_ATTR_ENCRYPTED_RESPONSE			(0x40)		/* encrypted response                */
#define OBIS_AR_ATTR_DIGITAL_SIGNED_RESPONSE	(0x80)		/* digitally signed response         */
#endif

/*
 * For method access right encoding, method access_mode, bitwise
 */
#define OBIS_AR_METHOD_MAX_QUANTITY_SUPPORT		(64)		/* Please select value larger than 0 */
#if CLASS_15_VERSION == 0
#define OBIS_AR_METHOD_NO_ACCESS				(0x00)		/* No access                                                                   */
#define OBIS_AR_METHOD_ACCESS					(0x01)		/* access                                                                      */
#define OBIS_AR_METHOD_AUTHEN_REQUEST			(0x00)		/* (0, no support, CLASS_15_VERSION v1, v2, v3 have) authenticated request     */
#define OBIS_AR_METHOD_ENCRYPTED_REQUEST		(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) encrypted request                 */
#define OBIS_AR_METHOD_DIGITAL_SIGNED_REQUEST	(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) digitally signed request          */
#define OBIS_AR_METHOD_AUTHEN_RESPONSE			(0x00)		/* (0, no support, CLASS_15_VERSION v1, v2, v3 have) authenticated response    */
#define OBIS_AR_METHOD_ENCRYPTED_RESPONSE		(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) encrypted response                */
#define OBIS_AR_METHOD_DIGITAL_SIGNED_RESPONSE	(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) digitally signed response         */
#elif CLASS_15_VERSION == 1 || CLASS_15_VERSION == 2
#define OBIS_AR_METHOD_NO_ACCESS				(0x00)		/* No access                                                                   */
#define OBIS_AR_METHOD_ACCESS					(0x01)		/* access                                                                      */
#define OBIS_AR_METHOD_AUTHEN_REQUEST			(0x04)		/* authenticated request                                                       */
#define OBIS_AR_METHOD_ENCRYPTED_REQUEST		(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) encrypted request                 */
#define OBIS_AR_METHOD_DIGITAL_SIGNED_REQUEST	(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) digitally signed request          */
#define OBIS_AR_METHOD_AUTHEN_RESPONSE			(0x20)		/* authenticated response                                                      */
#define OBIS_AR_METHOD_ENCRYPTED_RESPONSE		(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) encrypted response                */
#define OBIS_AR_METHOD_DIGITAL_SIGNED_RESPONSE	(0x00)		/* (0, no support, CLASS_15_VERSION v3 have) digitally signed response         */
#elif CLASS_15_VERSION == 3
#define OBIS_AR_METHOD_NO_ACCESS				(0x00)		/* No access                         */
#define OBIS_AR_METHOD_ACCESS					(0x01)		/* access                            */
#define OBIS_AR_METHOD_AUTHEN_REQUEST			(0x04)		/* authenticated request             */
#define OBIS_AR_METHOD_ENCRYPTED_REQUEST		(0x08)		/* encrypted request                 */
#define OBIS_AR_METHOD_DIGITAL_SIGNED_REQUEST	(0x10)		/* digitally signed request          */
#define OBIS_AR_METHOD_AUTHEN_RESPONSE			(0x20)		/* authenticated response            */
#define OBIS_AR_METHOD_ENCRYPTED_RESPONSE		(0x40)		/* encrypted response                */
#define OBIS_AR_METHOD_DIGITAL_SIGNED_RESPONSE	(0x80)		/* digitally signed response         */
#endif

/* For choice_t type */
#define CHOICE_NULL_DATA				{TAG_DATA_NULL_DATA             ,    0}		/* Null data (no data)                                */
#define CHOICE_BOOLEAN					{TAG_DATA_BOOLEAN               ,    1}		/* Boolean                                            */
#define CHOICE_BIT_STRING(size)			{TAG_DATA_BIT_STRING            , size}		/* An ordered sequence of boolean values              */
#define CHOICE_DOUBLE_LONG				{TAG_DATA_DOUBLE_LONG           ,    4}		/* Integer32                                          */
#define CHOICE_DOUBLE_LONG_UNSIGNED		{TAG_DATA_DOUBLE_LONG_UNSIGNED  ,    4}		/* Unsigned32                                         */
#define CHOICE_OCTET_STRING(size)		{TAG_DATA_OCTET_STRING          , size}		/* An ordered sequence of octets (8 bit bytes)        */
#define CHOICE_VISIBLE_STRING(size)		{TAG_DATA_VISIBLE_STRING        , size}		/* An ordered sequence of ASCII characters            */
#define CHOICE_UTF8_STRING(size)		{TAG_DATA_UTF8_STRING           , size}		/* An ordered sequence of characters encoded as UTF-8 */
#define CHOICE_BCD						{TAG_DATA_BCD                   ,    1}		/* Binary coded decimal                               */
#define CHOICE_INTEGER					{TAG_DATA_INTEGER               ,    1}		/* Integer8                                           */
#define CHOICE_LONG						{TAG_DATA_LONG                  ,    2}		/* Integer16                                          */
#define CHOICE_UNSIGNED					{TAG_DATA_UNSIGNED              ,    1}		/* Unsigned8                                          */
#define CHOICE_LONG_UNSIGNED			{TAG_DATA_LONG_UNSIGNED         ,    2}		/* Unsigned16                                         */
#define CHOICE_LONG64					{TAG_DATA_LONG64                ,    8}		/* Integer64                                          */
#define CHOICE_LONG64_UNSIGNED			{TAG_DATA_LONG64_UNSIGNED       ,    8}		/* Unsigned64                                         */
#define CHOICE_ENUM						{TAG_DATA_ENUM                  ,    1}		/* The elements of the enumeration type               */
#define CHOICE_FLOAT32					{TAG_DATA_FLOAT32               ,    4}		/* OCTET STRING (SIZE(4))                             */
#define CHOICE_FLOAT64					{TAG_DATA_FLOAT64               ,    8}		/* OCTET STRING (SIZE(8))                             */
#define CHOICE_DATE_TIME				{TAG_DATA_DATE_TIME             ,   12}		/* OCTET STRING (SIZE(12))                            */
#define CHOICE_DATE						{TAG_DATA_DATE                  ,    5}		/* OCTET STRING (SIZE(5))                             */
#define CHOICE_TIME						{TAG_DATA_TIME                  ,    4}		/* OCTET STRING (SIZE(4))                             */
#define CHOICE_ARRAY					{TAG_DATA_ARRAY                 ,   -1}		/* The elements of the array                          */
#define CHOICE_STRUCTURE				{TAG_DATA_STRUCTURE             ,   -1}		/* The elements of the structure                      */
#define CHOICE_COMPACT_ARRAY			{TAG_DATA_COMPACT_ARRAY         ,   -1}		/* The elements of the compact array                  */

/* For choice_t */
#define CHOICE(choice, buffer)			{choice, buffer}

#if !defined(OBIS_AR_ATTR_MAX_QUANTITY_SUPPORT)
#error "Please select number of attrs to be support for access right definition on macro OBIS_AR_ATTR_MAX_QUANTITY_SUPPORT"
#elif OBIS_AR_ATTR_MAX_QUANTITY_SUPPORT == 0
#error "Please set value larger than 0 on macro OBIS_AR_ATTR_MAX_QUANTITY_SUPPORT"
#endif /* Accessright: max number of attrs support */

#if !defined(OBIS_AR_METHOD_MAX_QUANTITY_SUPPORT)
#error "Please select number of attrs to be support for access right definition on macro OBIS_AR_METHOD_MAX_QUANTITY_SUPPORT"
#elif OBIS_AR_METHOD_MAX_QUANTITY_SUPPORT == 0
#error "Please set value larger than 0 on macro OBIS_AR_METHOD_MAX_QUANTITY_SUPPORT"
#endif

/* Set data access result (GET/SET) to distributor result */
#define		OBIS_DATA_ACCESS_RESULT(result_var, access_result_val, partial_val)	{	 \
	(result_var).result.data_access = access_result_val;							 \
	(result_var).partial = partial_val;												 \
}

/* Set ACTION result to distributor result */
#define		OBIS_ACTION_RESULT(result_var, action_result_val, partial_val)	{	 \
	(result_var).result.action = action_result_val;								 \
	(result_var).partial = partial_val;											 \
}

/* Mark distribution as success */
#define		OBIS_DISTRIBUTION_SUCCESS(result_var)	{ (result_var).success = TRUE; }

/* Mark distribution as failed */
#define		OBIS_DISTRIBUTION_FAILED(result_var)	{ (result_var).success = FALSE; }

/* Default value of distribution result */
#define		OBIS_DISTRIBUTION_DEFAULT_VALUE			{ VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED, FALSE, FALSE }

/*---------------------------------------------------------------------------
 * Redirect Encode and Decode function of APDU Common Data Type to OBIS layer
 * ---------------------------------------------------------------------------
 */

/* Encode a basic type */
#define		R_DLMS_CLASSES_EncodeCommonType		R_APDU_EncodeCommonType

/* Decode a basic type */
#define		R_DLMS_CLASSES_DecodeCommonType		R_APDU_DecodeCommonType

/* Advance buffer by a size */
#define		OBIS_ADVANCE_BUFFER(buf, size)		{	\
	buf.p_content += size;							\
	buf.length -= size;								\
}

/* -------------------------------------------
 * Encode/Decode macros for type distributor
 * -------------------------------------------
 */

/* Encode complex type header */
#define		OBIS_ENCODE_COMPLEX_TYPE_HEADER(buf, complex_type)	{	\
	ASSERT_TRUE_RET_ZERO(buf.length == 0);							\
	*buf.p_content++ = complex_type;								\
	buf.length--;													\
}

/* Decode complex type header */
#define		OBIS_DECODE_COMPLEX_TYPE_HEADER(encoded_buf, complex_type)	   {	\
	ASSERT_TRUE_RET_ZERO(encoded_buf.length == 0);								\
	ASSERT_TRUE_RET_ZERO(*encoded_buf.p_content++ != complex_type);				\
	encoded_buf.length--;														\
}

/* Encode length then advance buffer into buf */
#define		OBIS_ENCODE_LENGTH_THEN_ADVANCE_BUF(u8, buf, length_val) {		\
	u8 = R_BER_LengthEncode(buf.p_content, length_val);						\
	ASSERT_TRUE_RET_ZERO(u8 == 0 || u8 > buf.length);						\
	OBIS_ADVANCE_BUFFER(buf, u8);											\
}

/* Decode length then advance buffer into encoded_buf */
#define		OBIS_DECODE_LENGTH_THEN_ADVANCE_BUF(u8, p_length, encoded_buf) {	\
	u8 = R_BER_LengthDecode(encoded_buf.p_content, p_length);					\
	ASSERT_TRUE_RET_ZERO(u8 == 0 || u8 > encoded_buf.length);					\
	OBIS_ADVANCE_BUFFER(encoded_buf, u8);										\
}

/* Encode structure type header */
#define		OBIS_ENCODE_STRUCTURE_TYPE_HEADER(buf)				OBIS_ENCODE_COMPLEX_TYPE_HEADER(buf, TAG_DATA_STRUCTURE)

/* Decode structure type header */
#define		OBIS_DECODE_STRUCTURE_TYPE_HEADER(encoded_buf)		OBIS_DECODE_COMPLEX_TYPE_HEADER(encoded_buf, TAG_DATA_STRUCTURE)

/* Encode array type header */
#define		OBIS_ENCODE_ARRAY_TYPE_HEADER(buf)					OBIS_ENCODE_COMPLEX_TYPE_HEADER(buf, TAG_DATA_ARRAY)

/* Decode array type header */
#define		OBIS_DECODE_ARRAY_TYPE_HEADER(encoded_buf)			OBIS_DECODE_COMPLEX_TYPE_HEADER(encoded_buf, TAG_DATA_ARRAY)

/* Encode stucture type definition */
#define		OBIS_ENCODE_STRUCTURE_TYPE_DEF(u8, buf, num_elements) {			\
	OBIS_ENCODE_STRUCTURE_TYPE_HEADER(buf);									\
	OBIS_ENCODE_LENGTH_THEN_ADVANCE_BUF(u8, buf, num_elements);				\
}

/* Decode structure type definition */
#define		OBIS_DECODE_STRUCTURE_TYPE_DEF(u8, p_num_elements, expected_num_elements, encoded_buf)	{	\
	OBIS_DECODE_STRUCTURE_TYPE_HEADER(encoded_buf);														\
	OBIS_DECODE_LENGTH_THEN_ADVANCE_BUF(u8, p_num_elements, encoded_buf);								\
	ASSERT_TRUE_RET_ZERO(*(p_num_elements) != expected_num_elements);									\
}

/* Encode array type definition */
#define		OBIS_ENCODE_ARRAY_TYPE_DEF(u8, buf, array_length) {			\
	OBIS_ENCODE_ARRAY_TYPE_HEADER(buf);									\
	OBIS_ENCODE_LENGTH_THEN_ADVANCE_BUF(u8, buf, array_length);			\
}

/* Decode array type definition */
#define		OBIS_DECODE_ARRAY_TYPE_DEF(u8, p_array_length, aloc_size, encoded_buf)	{			\
	OBIS_DECODE_ARRAY_TYPE_HEADER(encoded_buf);													\
	OBIS_DECODE_LENGTH_THEN_ADVANCE_BUF(u8, p_array_length, encoded_buf);						\
	ASSERT_TRUE_RET_ZERO(*(p_array_length) > aloc_size);										\
}

/* Encode a type then advance buffer */
#define		OBIS_ENCODE_THEN_ADVANCE_BUF(u16, buf, tag, p_value, value_length) {							\
	u16 = R_DLMS_CLASSES_EncodeCommonType(buf.p_content, buf.length, tag, p_value, value_length);			\
	ASSERT_TRUE_RET_ZERO(u16 == 0 || u16 > buf.length);														\
	OBIS_ADVANCE_BUFFER(buf, u16);																			\
}

/* Decode a type then advance buffer */
#define		OBIS_DECODE_THEN_ADVANCE_BUF(u16, p_value, value_length, tag, encoded_buf) {							\
	u16 = R_DLMS_CLASSES_DecodeCommonType(p_value, value_length, tag, encoded_buf.p_content, encoded_buf.length);	\
	ASSERT_TRUE_RET_ZERO(u16 == 0 || u16 > encoded_buf.length);														\
	OBIS_ADVANCE_BUFFER(encoded_buf, u16);																			\
}

/* Decode a variant string then advance buffer */
#define		OBIS_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(u16, p_variant_string, tag, encoded_buf) {			\
	u16 = R_DLMS_CLASSES_DecodeVariantString(p_variant_string, tag, encoded_buf);							\
	ASSERT_TRUE_RET_ZERO(u16 == 0 || u16 > encoded_buf.length);												\
	OBIS_ADVANCE_BUFFER(encoded_buf, u16);																	\
}

/* Encode a type by its encoder func and object pointer */
#define		OBIS_ENCODE_TYPE_BY_FUNC(u16, func, buf, p_object) {		\
	u16 = func(buf, p_object);											\
	ASSERT_TRUE_RET_ZERO(u16 == 0 || u16 > buf.length);					\
	OBIS_ADVANCE_BUFFER(buf, u16);										\
}

/* Decode a type by its decoder function and object pointer */
#define		OBIS_DECODE_TYPE_BY_FUNC(u16, func, p_object, encoded_buf) {	\
	u16 = func(p_object, encoded_buf);										\
	ASSERT_TRUE_RET_ZERO(u16 == 0 || u16 > encoded_buf.length);				\
	OBIS_ADVANCE_BUFFER(encoded_buf, u16);									\
}


/* -------------------------------------------
 * Macros for redirect function
 * -------------------------------------------
 */

/* Decode complex type header */
#define	OBIS_REDIRECT_ADVANCE_HEADER(encoded_buf) {							\
	if(encoded_buf.length > 0) {											\
		encoded_buf.length--;												\
	}																		\
}

#define	OBIS_REDIRECT_ADVANCE_LENGTH(u8, p_length, encoded_buf) {			\
	u8 = R_BER_LengthDecode(encoded_buf.p_content, p_length);				\
	OBIS_ADVANCE_BUFFER(encoded_buf, u8);									\
}

/* Decode structure type header */
#define OBIS_REDIRECT_ADVANCE_STRUCTURE_TYPE_HEADER(encoded_buf)		OBIS_REDIRECT_ADVANCE_HEADER(encoded_buf)
#define OBIS_REDIRECT_ADVANCE_ARRAY_TYPE_HEADER(encoded_buf)			OBIS_REDIRECT_ADVANCE_HEADER(encoded_buf)

#define OBIS_REDIRECT_ADVANCE_STRUCTURE_TYPE_DEF(u8, p_num_elements, encoded_buf) {			\
	OBIS_REDIRECT_ADVANCE_STRUCTURE_TYPE_HEADER(encoded_buf); 								\
	OBIS_REDIRECT_ADVANCE_LENGTH(u8, p_num_elements, encoded_buf); 							\
}
#define OBIS_REDIRECT_ADVANCE_ARRAY_TYPE_DEF(u8, p_array_length, encoded_buf) {				\
	OBIS_REDIRECT_ADVANCE_ARRAY_TYPE_HEADER(encoded_buf); 									\
	OBIS_REDIRECT_ADVANCE_LENGTH(u8, p_array_length, encoded_buf); 							\
}

#define OBIS_REDIRECT_ADVANCE_COMMON_TYPE(common_type, encoded_buf) {						\
	OBIS_REDIRECT_ADVANCE_HEADER(encoded_buf);												\
	OBIS_ADVANCE_BUFFER(encoded_buf, sizeof(common_type));									\
}

#define OBIS_REDIRECT_ADVANCE_VARIANT_STRING(u16, p_array_length, encoded_buf)	{			\
	OBIS_REDIRECT_ADVANCE_ARRAY_TYPE_DEF(u8, p_array_length, encoded_buf); 					\
	if (*p_array_length == 0 || *p_array_length > encoded_buf.length) {						\
		OBIS_ADVANCE_BUFFER(encoded_buf, *p_array_length);									\
	}																						\
}

/* ------------------------------------------------------------------------------
 * Encode/Decode macros for class distributor (direct return if fail)
 * ------------------------------------------------------------------------------
 */

/* Encode complex type header */
#define		OBIS_DIST_ENCODE_COMPLEX_TYPE_HEADER(buf, complex_type)	{		\
	ASSERT_TRUE_RET_DIST_RESULT(buf.length == 0);							\
	*buf.p_content++ = complex_type;										\
	buf.length--;															\
}

/* Decode complex type header */
#define		OBIS_DIST_DECODE_COMPLEX_TYPE_HEADER(encoded_buf, complex_type)	   {		\
	ASSERT_TRUE_RET_DIST_RESULT(encoded_buf.length == 0);								\
	ASSERT_TRUE_RET_DIST_RESULT(*encoded_buf.p_content++ != complex_type);				\
	encoded_buf.length--;																\
}

/* Encode length then advance buffer into buf */
#define		OBIS_DIST_ENCODE_LENGTH_THEN_ADVANCE_BUF(u8, buf, length_val) {				\
	u8 = R_BER_LengthEncode(buf.p_content, length_val);									\
	ASSERT_TRUE_RET_DIST_RESULT(u8 == 0 || u8 > buf.length);							\
	OBIS_ADVANCE_BUFFER(buf, u8);														\
}

/* Decode length then advance buffer into encoded_buf */
#define		OBIS_DIST_DECODE_LENGTH_THEN_ADVANCE_BUF(u8, p_length, encoded_buf) {		\
	u8 = R_BER_LengthDecode(encoded_buf.p_content, p_length);							\
	ASSERT_TRUE_RET_DIST_RESULT(u8 == 0 || u8 > encoded_buf.length);					\
	OBIS_ADVANCE_BUFFER(encoded_buf, u8);												\
}

/* Encode structure type header */
#define		OBIS_DIST_ENCODE_STRUCTURE_TYPE_HEADER(buf)				OBIS_DIST_ENCODE_COMPLEX_TYPE_HEADER(buf, TAG_DATA_STRUCTURE)

/* Decode structure type header */
#define		OBIS_DIST_DECODE_STRUCTURE_TYPE_HEADER(encoded_buf)		OBIS_DIST_DECODE_COMPLEX_TYPE_HEADER(encoded_buf, TAG_DATA_STRUCTURE)

/* Encode array type header */
#define		OBIS_DIST_ENCODE_ARRAY_TYPE_HEADER(buf)					OBIS_DIST_ENCODE_COMPLEX_TYPE_HEADER(buf, TAG_DATA_ARRAY)

/* Decode array type header */
#define		OBIS_DIST_DECODE_ARRAY_TYPE_HEADER(encoded_buf)			OBIS_DIST_DECODE_COMPLEX_TYPE_HEADER(encoded_buf, TAG_DATA_ARRAY)

/* Encode stucture type definition */
#define		OBIS_DIST_ENCODE_STRUCTURE_TYPE_DEF(u8, buf, num_elements) {			\
	OBIS_DIST_ENCODE_STRUCTURE_TYPE_HEADER(buf);									\
	OBIS_DIST_ENCODE_LENGTH_THEN_ADVANCE_BUF(u8, buf, num_elements);				\
}

/* Decode structure type definition */
#define		OBIS_DIST_DECODE_STRUCTURE_TYPE_DEF(u8, p_num_elements, expected_num_elements, encoded_buf)	{	\
	OBIS_DIST_DECODE_STRUCTURE_TYPE_HEADER(encoded_buf);													\
	OBIS_DIST_DECODE_LENGTH_THEN_ADVANCE_BUF(u8, p_num_elements, encoded_buf);								\
	ASSERT_TRUE_RET_DIST_RESULT(*(p_num_elements) != expected_num_elements);								\
}

/* Encode array type definition */
#define		OBIS_DIST_ENCODE_ARRAY_TYPE_DEF(u8, buf, array_length) {			\
	OBIS_DIST_ENCODE_ARRAY_TYPE_HEADER(buf);									\
	OBIS_DIST_ENCODE_LENGTH_THEN_ADVANCE_BUF(u8, buf, array_length);			\
}

/* Decode array type definition */
#define		OBIS_DIST_DECODE_ARRAY_TYPE_DEF(u8, p_array_length, aloc_size, encoded_buf)	{			\
	OBIS_DIST_DECODE_ARRAY_TYPE_HEADER(encoded_buf);												\
	OBIS_DIST_DECODE_LENGTH_THEN_ADVANCE_BUF(u8, p_array_length, encoded_buf);						\
	ASSERT_TRUE_RET_DIST_RESULT(*(p_array_length) > aloc_size);										\
}

/* Encode a type then advance buffer */
#define		OBIS_DIST_ENCODE_THEN_ADVANCE_BUF(u16, buf, tag, p_value, value_length) {							\
	u16 = R_DLMS_CLASSES_EncodeCommonType(buf.p_content, buf.length, tag, p_value, value_length);				\
	ASSERT_TRUE_RET_DIST_RESULT(u16 == 0 || u16 > buf.length);													\
	OBIS_ADVANCE_BUFFER(buf, u16);																				\
}

/* Decode a type then advance buffer */
#define		OBIS_DIST_DECODE_THEN_ADVANCE_BUF(u16, p_value, value_length, tag, encoded_buf) {						\
	u16 = R_DLMS_CLASSES_DecodeCommonType(p_value, value_length, tag, encoded_buf.p_content, encoded_buf.length);	\
	ASSERT_TRUE_RET_DIST_RESULT(u16 == 0 || u16 > encoded_buf.length);												\
	OBIS_ADVANCE_BUFFER(encoded_buf, u16);																			\
}

/* Decode a variant string then advance buffer */
#define		OBIS_DIST_DECODE_VARIANT_STRING_THEN_ADVANCE_BUF(u16, p_variant_string, tag, encoded_buf) {			\
	u16 = R_DLMS_CLASSES_DecodeVariantString(p_variant_string, tag, encoded_buf);								\
	ASSERT_TRUE_RET_DIST_RESULT(u16 == 0 || u16 > encoded_buf.length);											\
	OBIS_ADVANCE_BUFFER(encoded_buf, u16);																		\
}

/* Encode a type by its encoder func and object pointer */
#define		OBIS_DIST_ENCODE_TYPE_BY_FUNC(u16, func, buf, p_object) {		\
	u16 = func(buf, p_object);												\
	ASSERT_TRUE_RET_DIST_RESULT(u16 == 0 || u16 > buf.length);				\
	OBIS_ADVANCE_BUFFER(buf, u16);											\
}

/* Decode a type by its decoder function and object pointer */
#define		OBIS_DIST_DECODE_TYPE_BY_FUNC(u16, func, p_object, encoded_buf) {	\
	u16 = func(p_object, encoded_buf);											\
	ASSERT_TRUE_RET_DIST_RESULT(u16 == 0 || u16 > encoded_buf.length);			\
	OBIS_ADVANCE_BUFFER(encoded_buf, u16);										\
}

/* --------------------------------------------------------
 * Macros for declaration of type encoder/decoder function
 * --------------------------------------------------------
 */

/* Declare a type encoder function prototype */
#define		OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(func_name, data_type)										\
	uint16_t func_name(MandatoryString out_data, data_type *p_object)

/* Declare a type decoder function prototype */
#define		OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(func_name, data_type)										\
	uint16_t func_name(data_type *p_object, MandatoryString in_data)

/* Declare a type encoder function params */
#define		OBIS_DECLARE_TYPE_ENCODER_FUNC_PARAMS															\
	uint16_t	u16, length;						/* Output of common encoding API */						\
	uint8_t		u8;									/* Common for length encode */							\
	uint8_t		*p_head = out_data.p_content;		/* Temp pointer for length calc */

/* Declare a type decoder function params */
#define		OBIS_DECLARE_TYPE_DECODER_FUNC_PARAMS															\
	uint16_t	u16, length;						/* Output of common decoding API */						\
	uint8_t		u8;									/* Common for length decode */							\
	uint8_t		*p_head = in_data.p_content;		/* Temp pointer for length calc */						

/* Type encoder function params check statement */
#define		OBIS_TYPE_ENCODER_FUNC_PARAMS_CHECK()															\
	/* Check input parameter */																				\
	ASSERT_TRUE_RET_ZERO(																					\
		out_data.p_content == NULL ||																		\
		out_data.length == 0 ||																				\
		p_object == NULL																					\
	);

/* Type decoder function params check statement */
#define		OBIS_TYPE_DECODER_FUNC_PARAMS_CHECK()															\
	/* Check input parameter */																				\
	ASSERT_TRUE_RET_ZERO(																					\
		p_object == NULL ||																					\
		in_data.p_content == NULL ||																		\
		in_data.length == 0																					\
	);

/* Type encoder function return statement */
#define		OBIS_TYPE_ENCODER_FUNC_RET()																	\
	return (uint16_t)(out_data.p_content - p_head);

/* Type decoder function return statement */
#define		OBIS_TYPE_DECODER_FUNC_RET()																	\
	return (uint16_t)(in_data.p_content - p_head);

/* Declare a basic type encoder function */
#define		OBIS_DECLARE_BASIC_TYPE_ENCODER_FUNC(func_name, tag, data_type, size)							\
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(func_name, data_type)													\
{																											\
	return R_DLMS_CLASSES_EncodeCommonType(																	\
		out_data.p_content,																					\
		out_data.length,																					\
		tag,																								\
		(uint8_t *)p_object,																				\
		size																								\
	);																										\
}

/* Declare a basic type decoder function */
#define		OBIS_DECLARE_BASIC_TYPE_DECODER_FUNC(func_name, tag, data_type, size)							\
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(func_name, data_type)													\
{																											\
	return R_DLMS_CLASSES_DecodeCommonType(																	\
		(uint8_t *)p_object,																				\
		size,																								\
		tag,																								\
		in_data.p_content,																					\
		in_data.length																						\
	);																										\
}																											\

/* Declare a fixed string encoder function */
#define		OBIS_DECLARE_FIXED_STRING_ENCODER_FUNC(func_name, tag)											\
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(func_name, FixedString)												\
{																											\
	return R_DLMS_CLASSES_EncodeFixedString(out_data, tag, p_object);										\
}

/* Declare a fixed string decoder function */
#define		OBIS_DECLARE_FIXED_STRING_DECODER_FUNC(func_name, tag)											\
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(func_name, FixedString)												\
{																											\
	return R_DLMS_CLASSES_DecodeFixedString(p_object, tag, in_data);										\
}

/* Declare a variant string encoder function */
#define		OBIS_DECLARE_VARIANT_STRING_ENCODER_FUNC(func_name, tag)										\
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(func_name, VariantString)												\
{																											\
	return R_DLMS_CLASSES_EncodeVariantString(out_data, tag, p_object);										\
}

/* Declare a variant string decoder function */
#define		OBIS_DECLARE_VARIANT_STRING_DECODER_FUNC(func_name, tag)										\
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(func_name, VariantString)												\
{																											\
	return R_DLMS_CLASSES_DecodeVariantString(p_object, tag, in_data);										\
}

/* Declare a encoder function of a fixed array of object */
#define		OBIS_DECLARE_FIXED_ARRAY_ENCODER_FUNC(func_name, fixed_array_data_type, element_enc_func)		\
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(func_name, fixed_array_data_type)										\
{																											\
	return R_DLMS_CLASSES_EncodeAbstractFixedArray(															\
		out_data,																							\
		(AbstractFixedArray *)p_object,																		\
		(fp_obj_encoder_func)element_enc_func,																\
		sizeof(*p_object->p_content)																		\
	);																										\
}

/* Declare a decoder function of a fixed array of object */
#define		OBIS_DECLARE_FIXED_ARRAY_DECODER_FUNC(func_name, fixed_array_data_type, element_dec_func)		\
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(func_name, fixed_array_data_type)										\
{																											\
	return R_DLMS_CLASSES_DecodeAbstractFixedArray(															\
		(AbstractFixedArray *)p_object,																		\
		in_data,																							\
		(fp_obj_decoder_func)element_dec_func,																\
		sizeof(*p_object->p_content)																		\
	);																										\
}

/* Declare a encoder function of a variant array of object */
#define		OBIS_DECLARE_VARIANT_ARRAY_ENCODER_FUNC(func_name, variant_array_data_type, element_enc_func)	\
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(func_name, variant_array_data_type)									\
{																											\
	return R_DLMS_CLASSES_EncodeAbstractVariantArray(														\
		out_data,																							\
		(AbstractVariantArray *)p_object,																	\
		(fp_obj_encoder_func)element_enc_func,																\
		sizeof(*p_object->p_content)																		\
	);																										\
}

/* Declare a decoder function of a variant array of object */
#define		OBIS_DECLARE_VARIANT_ARRAY_DECODER_FUNC(func_name, variant_array_data_type, element_dec_func)	\
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(func_name, variant_array_data_type)									\
{																											\
	return R_DLMS_CLASSES_DecodeAbstractVariantArray(														\
		(AbstractVariantArray *)p_object,																	\
		in_data,																							\
		(fp_obj_decoder_func)element_dec_func,																\
		sizeof(*p_object->p_content)																		\
	);																										\
}

/* --------------------------------------------------------
 * Encode/Decode macros for declaration of type distributor
 * --------------------------------------------------------
 */

/* Declare a type distributor function prototype */
#define		OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(func_name, data_type)										\
	void func_name(distributor_params_t *p_params, data_type *p_object)

/* Declare a basic type distributor function */
#define		OBIS_DECLARE_BASIC_TYPE_DISTRIBUTOR_FUNC(func_name, tag, data_type, size)							\
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(func_name, data_type)													\
{																												\
	R_DLMS_CLASSES_DistributeBasicType(p_params, tag, p_object, size);											\
}

/* Declare a fixed string distributor function */
#define		OBIS_DECLARE_FIXED_STRING_DISTRIBUTOR_FUNC(func_name, tag)											\
	OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(func_name, FixedString)											\
{																												\
	R_DLMS_CLASSES_DistributeFixedString(p_params, tag, p_object);												\
}

/* Declare a variant string distributor function */
#define		OBIS_DECLARE_VARIANT_STRING_DISTRIBUTOR_FUNC(func_name, tag)										\
	OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(func_name, VariantString)											\
{																												\
	R_DLMS_CLASSES_DistributeVariantString(p_params, tag, p_object);											\
}

/* Declare a distributor function of a complex type */
#define		OBIS_DECLARE_COMPLEX_TYPE_DISTRIBUTOR_FUNC(func_name, data_type, enc_func, dec_func, redirect_func)	\
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(func_name, data_type)													\
{																												\
	R_DLMS_CLASSES_DistributeComplexType(																		\
		p_params,																								\
		(fp_obj_encoder_func)enc_func,																			\
		(fp_obj_decoder_func)dec_func,																			\
		(fp_obj_redirect_t)redirect_func,																		\
		p_object																								\
	);																											\
}
#define		OBIS_DECLARE_STRUCTURE_ARRAY_DISTRIBUTOR_FUNC(func_name, data_type, enc_func, dec_func, redirect_func)	\
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(func_name, data_type)													\
{																												\
	R_DLMS_CLASSES_Distribute_ArrayofStructure(																		\
		p_params,																								\
		(fp_obj_encoder_func)enc_func,																			\
		(fp_obj_decoder_func)dec_func,																			\
		(fp_obj_structure_array_redirect_t)redirect_func,																		\
		p_object																								\
	);																											\
}
/* -----------------------------------------------------------------
 * Macros to create objects and memlink on dymanic buffer (malloc)
 * -----------------------------------------------------------------
 */

/* Make zero for malloc buffer on distributor params, from current position with specified size */
#define		OBIS_MALLOC_MAKE_ZERO(p_params, size)		{													   \
	if (size <= (p_params->service_params.malloc.alloc_size - p_params->service_params.malloc.length)) {	   \
		memset(p_params->service_params.malloc.p_content + p_params->service_params.malloc.length, 0, size);   \
	}																										   \
}

/* Make zero for malloc buffer on distributor params, from current position till end */
#define		OBIS_MALLOC_MAKE_ZERO_ALL(p_params)		{														   \
	if (p_params->service_params.malloc.length < p_params->service_params.malloc.alloc_size) {				   \
		memset(																								   \
			p_params->service_params.malloc.p_content + p_params->service_params.malloc.length, 0,			   \
			p_params->service_params.malloc.alloc_size - p_params->service_params.malloc.length				   \
		);																									   \
	}																										   \
}

/* Check if malloc buffer on distribution params is empty */
#define		OBIS_MALLOC_IS_NULL(p_params)		(		   \
	p_params->service_params.malloc.p_content == NULL ||   \
	p_params->service_params.malloc.alloc_size == 0		   \
)

/* Get current malloc buffer pointer on distribution params */
#define		OBIS_MALLOC_GET_POINTER(p_params)	(		   \
	p_params->service_params.malloc.p_content +			   \
	p_params->service_params.malloc.length				   \
)

/* Get remain size of malloc buffer on distribution params */
#define		OBIS_MALLOC_REMAIN_SIZE(p_params)	(		   \
	p_params->service_params.malloc.alloc_size -		   \
	p_params->service_params.malloc.length				   \
)

/* Advance the malloc buffer on distribution params with a desized size */
#define		OBIS_MALLOC_ADVANCE_BUFFER(p_params, size)	{  \
	p_params->service_params.malloc.length += size;		   \
}

/* ---------------------
 * Macros for memlink
 * ---------------------
 */

/* Assign memlink (dest, src, size) to distribution params */
#define		OBIS_MALLOC_MEMLINK(p_params, dest, src, size)	\
	R_DLMS_CLASSES_RegisterMemcpyLink(p_params, dest, src, size)

/* Assign memlink (dest, src, size) to distribution params, break if fail */
#define		OBIS_MALLOC_MEMLINK_BREAK(p_params, dest, src, size)	{		  \
	if (OBIS_MALLOC_MEMLINK(p_params, dest, src, size) == FALSE) { break; }	  \
}

/* Assign memlink (dest, src, size) to distribution params, return if fail */
#define		OBIS_MALLOC_MEMLINK_RET(p_params, dest, src, size)		{		  \
	if (OBIS_MALLOC_MEMLINK(p_params, dest, src, size) == FALSE) { return; }  \
}

/* Assign memlink (dest, src, size) to distribution params, return (val) if fail */
#define		OBIS_MALLOC_MEMLINK_RET_VAL(p_params, dest, src, size, val)	{		   \
	if (OBIS_MALLOC_MEMLINK(p_params, dest, src, size) == FALSE) { return val; }   \
}

/* Assign memlink (dest, src, size) to distribution params, return NULL if fail */
#define		OBIS_MALLOC_MEMLINK_RET_NULL(p_params, dest, src, size)				\
	OBIS_MALLOC_MEMLINK_RET_VAL(p_params, dest, src, size, NULL)

/* ----------------------------------------
 * Macros to create object & its memlink
 * ----------------------------------------
 */

#define		OBIS_MALLOC_OPTION_NONE			0x00
#define		OBIS_MALLOC_OPTION_CREATENEW	0x01
#define		OBIS_MALLOC_OPTION_BITSTRING	0x02
#define		OBIS_MALLOC_OPTION_CLONE		0x04
#define		OBIS_MALLOC_OPTION_MEMLINK		0x08

/* Assign object on malloc buffer (allocated buffer is kept untouch) */
/*
 * TODO: Buffer check for odd and even data alignment on below code
 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
 */
#define		OBIS_MALLOC_ASSIGN_OBJECT(p_object_var, object_type, p_alloc)	{	\
	p_object_var = (object_type *)(void *)p_alloc;								\
	p_alloc += sizeof(object_type);												\
}

/* Assign the content of the fixed array create on malloc buffer */
/*
 * TODO: Buffer check for odd and even data alignment on below code
 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
 */
#define		OBIS_MALLOC_ASSIGN_FIXED_ARRAY(p_fixed_array, array_size, element_type, p_alloc) {	\
	(p_fixed_array)->p_content = (element_type *)(void *)p_alloc;								\
	(p_fixed_array)->length = array_size;														\
	p_alloc += sizeof(element_type) * array_size;												\
}

/* Assign the content of the variant array create on malloc buffer */
/*
 * TODO: Buffer check for odd and even data alignment on below code
 * Currently, warning W0523082 is suppressed on CCRL as structure packing is not apply, pointer is always in even
 */
#define		OBIS_MALLOC_ASSIGN_VARIANT_ARRAY(p_variant_array, array_size, element_type, p_alloc) {	\
	(p_variant_array)->p_content = (element_type *)(void *)p_alloc;									\
	(p_variant_array)->length = 0;																	\
	(p_variant_array)->alloc_size = array_size;														\
	p_alloc += sizeof(element_type) * array_size;													\
	(p_variant_array)->p_active = p_alloc;															\
	p_alloc += (array_size % 2) + array_size;														\
}

/* Construct the content of the fixed string create on malloc buffer */
#define		OBIS_MALLOC_ASSIGN_FIXED_STRING(p_fixed_string, size, p_alloc)	OBIS_MALLOC_ASSIGN_FIXED_ARRAY(p_fixed_string, size, uint8_t, p_alloc)

/* Construct the content of the variant string create on malloc buffer */
#define		OBIS_MALLOC_ASSIGN_VARIANT_STRING(p_var_string, size, p_alloc)	{	\
	(p_var_string)->p_content = p_alloc;										\
	(p_var_string)->length = 0;													\
	(p_var_string)->alloc_size = size;											\
	p_alloc += size + (size % 2);												\
}

/* ----------------------------------------
 * Macros to declare redirect functions
 * ----------------------------------------
 */

/* Redirect (clone) a FixedString object */
#define		R_DLMS_CLASSES_RedirectFixedString(p_params, p_object, options)			\
	R_DLMS_CLASSES_CreateFixedString(												\
		p_params,																	\
		p_object,																	\
		(options) |																	\
		OBIS_MALLOC_OPTION_CREATENEW |												\
		OBIS_MALLOC_OPTION_MEMLINK |												\
		OBIS_MALLOC_OPTION_CLONE													\
	)

/* Redirect (clone) a VariantString object */
#define		R_DLMS_CLASSES_RedirectVariantString(p_params, p_object, options)		\
	R_DLMS_CLASSES_CreateVariantString(												\
		p_params,																	\
		p_object,																	\
		(options) |																	\
		OBIS_MALLOC_OPTION_CREATENEW |												\
		OBIS_MALLOC_OPTION_MEMLINK |												\
		OBIS_MALLOC_OPTION_CLONE													\
	)

/* Redirect (clone) a Choice object */
#define		R_DLMS_CLASSES_RedirectChoice(p_params, p_object, options)				\
	R_DLMS_CLASSES_CreateChoice(													\
		p_params,																	\
		p_object,																	\
		(options) |																	\
		OBIS_MALLOC_OPTION_CREATENEW |												\
		OBIS_MALLOC_OPTION_MEMLINK |												\
		OBIS_MALLOC_OPTION_CLONE													\
	)

#define R_DLMS_CLASSES_RedirectBoolean(p_params, p_object)				R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(uint8_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define	R_DLMS_CLASSES_RedirectBitString(p_params, p_object)			R_DLMS_CLASSES_CreateVariantString(p_params, p_object, OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE | OBIS_MALLOC_OPTION_BITSTRING)
#define R_DLMS_CLASSES_RedirectDoubleLong(p_params, p_object)			R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(int32_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_object)	R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(uint32_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectOctetString(p_params, p_object)			R_DLMS_CLASSES_CreateVariantString(p_params, p_object, OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectVisibleString(p_params, p_object)		R_DLMS_CLASSES_CreateVariantString(p_params, p_object, OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectUtf8String(p_params, p_object)			R_DLMS_CLASSES_CreateVariantString(p_params, p_object, OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectBcd(p_params, p_object)					R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(int8_t	    ), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectInteger(p_params, p_object)				R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(int8_t	    ), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectLong(p_params, p_object)					R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(int16_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectUnsigned(p_params, p_object)				R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(uint8_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_object)			R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(uint16_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectLong64(p_params, p_object)				R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(int64_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectLong64Unsigned(p_params, p_object)		R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(uint64_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectEnum(p_params, p_object)					R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(uint8_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectFloat32(p_params, p_object)				R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(float32_t	), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectFloat64(p_params, p_object)				R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(double64_t	), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectDateTime(p_params, p_object)				R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(date_time_t	), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectDate(p_params, p_object)					R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(date_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)
#define R_DLMS_CLASSES_RedirectTime(p_params, p_object)					R_DLMS_CLASSES_CreateObject(p_params, p_object, sizeof(time_t		), OBIS_MALLOC_OPTION_CREATENEW | OBIS_MALLOC_OPTION_MEMLINK | OBIS_MALLOC_OPTION_CLONE)

#define R_DLMS_CLASSES_NEW_ATTRIBUTE(p_params, attribute_type)			R_DLMS_CLASSES_CreateObject(p_params, NULL, sizeof(attribute_type), OBIS_MALLOC_OPTION_CREATENEW)
#define R_DLMS_CLASSES_NEW_OBJECT(p_params, object_type)				R_DLMS_CLASSES_CreateObject(p_params, NULL, sizeof(object_type), OBIS_MALLOC_OPTION_CREATENEW)
#define R_DLMS_CLASSES_NEW_BOOLEAN(p_params)							R_DLMS_CLASSES_NEW_OBJECT(p_params, uint8_t)
#define	R_DLMS_CLASSES_NEW_BITSTRING(p_params)							R_DLMS_CLASSES_CreateVariantString(p_params, NULL, OBIS_MALLOC_OPTION_CREATENEW  | OBIS_MALLOC_OPTION_BITSTRING)
#define R_DLMS_CLASSES_NEW_DOUBLELONG(p_params)							R_DLMS_CLASSES_NEW_OBJECT(p_params, int32_t)
#define R_DLMS_CLASSES_NEW_DOUBLELONGUNSIGNED(p_params)					R_DLMS_CLASSES_NEW_OBJECT(p_params, uint32_t)
#define R_DLMS_CLASSES_NEW_OCTETSTRING(p_params)						R_DLMS_CLASSES_CreateVariantString(p_params, NULL, OBIS_MALLOC_OPTION_CREATENEW)
#define R_DLMS_CLASSES_NEW_VISIBLESTRING(p_params)						R_DLMS_CLASSES_CreateVariantString(p_params, NULL, OBIS_MALLOC_OPTION_CREATENEW)
#define R_DLMS_CLASSES_NEW_UTF8STRING(p_params)							R_DLMS_CLASSES_CreateVariantString(p_params, NULL, OBIS_MALLOC_OPTION_CREATENEW)
#define R_DLMS_CLASSES_NEW_BCD(p_params)								R_DLMS_CLASSES_NEW_OBJECT(p_params, int8_t)
#define R_DLMS_CLASSES_NEW_INTEGER(p_params)							R_DLMS_CLASSES_NEW_OBJECT(p_params, int8_t)
#define R_DLMS_CLASSES_NEW_LONG(p_params)								R_DLMS_CLASSES_NEW_OBJECT(p_params, int16_t)
#define R_DLMS_CLASSES_NEW_UNSIGNED(p_params)							R_DLMS_CLASSES_NEW_OBJECT(p_params, uint8_t)
#define R_DLMS_CLASSES_NEW_LONGUNSIGNED(p_params)						R_DLMS_CLASSES_NEW_OBJECT(p_params, uint16_t)
#define R_DLMS_CLASSES_NEW_LONG64(p_params)								R_DLMS_CLASSES_NEW_OBJECT(p_params, int64_t)
#define R_DLMS_CLASSES_NEW_LONG64UNSIGNED(p_params)						R_DLMS_CLASSES_NEW_OBJECT(p_params, uint64_t)
#define R_DLMS_CLASSES_NEW_ENUM(p_params)								R_DLMS_CLASSES_NEW_OBJECT(p_params, uint8_t)
#define R_DLMS_CLASSES_NEW_FLOAT32(p_params)							R_DLMS_CLASSES_NEW_OBJECT(p_params, float32_t)
#define R_DLMS_CLASSES_NEW_FLOAT64(p_params)							R_DLMS_CLASSES_NEW_OBJECT(p_params, double64_t)
#define R_DLMS_CLASSES_NEW_DATETIME(p_params)							R_DLMS_CLASSES_NEW_OBJECT(p_params, date_time_t)
#define R_DLMS_CLASSES_NEW_DATE(p_params)								R_DLMS_CLASSES_NEW_OBJECT(p_params, date_t)
#define R_DLMS_CLASSES_NEW_TIME(p_params)								R_DLMS_CLASSES_NEW_OBJECT(p_params, time_t)

/* Declare a redirect (object clone) function header */
#define		OBIS_DECLARE_REDIRECT_FUNC_HEADER(func_name, data_type)							\
	data_type *func_name(distributor_params_t *p_params, data_type *p_object)

/* Declare a redirect (clone) function of an object */
#define		OBIS_DECLARE_REDIRECT_FUNC(func_name, data_type)								\
OBIS_DECLARE_REDIRECT_FUNC_HEADER(func_name, data_type)										\
{																							\
	return (data_type *)R_DLMS_CLASSES_CreateObject(										\
		p_params,																			\
		p_object,																			\
		sizeof(data_type),																	\
		OBIS_MALLOC_OPTION_CREATENEW | 														\
		OBIS_MALLOC_OPTION_MEMLINK | 														\
		OBIS_MALLOC_OPTION_CLONE															\
	);																						\
}

/* Declare a fixed array redirect (clone) function */
#define		OBIS_DECLARE_FIXED_ARRAY_REDIRECT_FUNC(func_name, data_type, element_type)		\
OBIS_DECLARE_REDIRECT_FUNC_HEADER(func_name, data_type)										\
{																							\
	return (data_type *)R_DLMS_CLASSES_CreateFixedArray(									\
		p_params,																			\
		(AbstractFixedArray *)p_object,														\
		sizeof(element_type),																\
		OBIS_MALLOC_OPTION_CREATENEW | 														\
		OBIS_MALLOC_OPTION_MEMLINK | 														\
		OBIS_MALLOC_OPTION_CLONE															\
	);																						\
}

/* Declare a variant array redirect (clone) function */
#define		OBIS_DECLARE_VARIANT_ARRAY_REDIRECT_FUNC(func_name, data_type, element_type)	\
OBIS_DECLARE_REDIRECT_FUNC_HEADER(func_name, data_type)										\
{																							\
	return (data_type *)R_DLMS_CLASSES_CreateVariantArray(									\
		p_params,																			\
		(AbstractVariantArray *)p_object,													\
		sizeof(element_type),																\
		OBIS_MALLOC_OPTION_CREATENEW | 														\
		OBIS_MALLOC_OPTION_MEMLINK | 														\
		OBIS_MALLOC_OPTION_CLONE															\
	);																						\
}
/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum tag_master_table_class_index_t
{
	MASTER_TABLE_INDEX_CLASS_01 = 0,
	MASTER_TABLE_INDEX_CLASS_03 = 1,
	MASTER_TABLE_INDEX_CLASS_04 = 2,
	MASTER_TABLE_INDEX_CLASS_07 = 3,
	MASTER_TABLE_INDEX_CLASS_08 = 4,
	MASTER_TABLE_INDEX_CLASS_09 = 5,
	MASTER_TABLE_INDEX_CLASS_15 = 6,
	MASTER_TABLE_INDEX_CLASS_18 = 7,
	MASTER_TABLE_INDEX_CLASS_20 = 8,
	MASTER_TABLE_INDEX_CLASS_22 = 9,
	MASTER_TABLE_INDEX_CLASS_23 = 10,
	MASTER_TABLE_INDEX_CLASS_40 = 11,
	MASTER_TABLE_INDEX_CLASS_41 = 12,
	MASTER_TABLE_INDEX_CLASS_45 = 13,
	MASTER_TABLE_INDEX_CLASS_48 = 14,
	MASTER_TABLE_INDEX_CLASS_64 = 15,
	MASTER_TABLE_INDEX_CLASS_70 = 16,
	MASTER_TABLE_INDEX_CLASS_71 = 17,
	MASTER_TABLE_INDEX_RESERVE = 255
} e_master_table_class_index_t;

/* Declare a variant array */
#define OBIS_DECLARE_VARIANT_ARRAY(element_type, var_name)					   \
struct tag ## var_name														   \
{																			   \
	element_type	*p_content;		/* Buffer location */					   \
	uint16_t		length;			/* Current length (usage) of buffer */	   \
	uint8_t			*p_active;		/* Indicates item is active or not */	   \
	uint16_t		alloc_size;		/* Alloc size */						   \
} var_name

/* Abstract variant array */
typedef OBIS_DECLARE_VARIANT_ARRAY(void, AbstractVariantArray);

/* Declare a fixed array */
#define OBIS_DECLARE_FIXED_ARRAY(element_type, var_name)					   \
struct tag ## var_name														   \
{																			   \
	element_type	*p_content;		/* Buffer location */					   \
	uint16_t		length;			/* Length of buffer */					   \
} var_name

/* Abstract fixed array */
typedef OBIS_DECLARE_FIXED_ARRAY(void, AbstractFixedArray);

/* Fixed size string */
typedef OBIS_DECLARE_FIXED_ARRAY(uint8_t, FixedString);

/* Variant string */
typedef struct tagVariantString
{
	uint8_t		*p_content;		/* Buffer location */
	uint16_t	length;			/* Current length (usage) of buffer */
	uint16_t	alloc_size;		/* Alloc size */
} VariantString;

/* Malloc buffer string */
typedef VariantString malloc_buffer_t;

/* Bit string (VariantString) */
#define BitString VariantString

/* Octet string (VariantString) */
#define OctetString VariantString

/* Visible string (VariantString) */
#define VisibleString VariantString

/* Utf8 string (VariantString) */
#define Utf8String VariantString

/* Redirect Data_Tag as attr_type_t on OBIS layer */
typedef Data_Tag attr_type_t;

/* Choice type */
typedef struct tag_choice_t
{
	struct tag_choice {
		attr_type_t	type;		/* Type of the choice   */
		int16_t		size;		/* Size of choosen type */
	} choice;
	void *buffer;				/* Buffer of choosen type */
} choice_t;

/* Date time type */
typedef struct tag_date_time_t
{
	uint8_t year_high;                    /* HI and LO of year. Interpreted as long-unsigned,   */
	uint8_t year_low;                     /* Range is 0 -> 0xFFFF-1. 0xFFFF mean not specified. */
	uint8_t month;                        /* Month. Interpreted as unsigned. 1...12             */
	uint8_t day_of_month;                 /* Day. Interpreted as unsigned. 1...31               */
	uint8_t day_of_week;                  /* Week. Interpreted as unsigned. 1...7               */
	uint8_t hour;                         /* Hour. Interpreted as unsigned. 0...23              */
	uint8_t minute;                       /* Minute. Interpreted as unsigned. 0...59            */
	uint8_t second;                       /* Hour. Interpreted as unsigned. 0...59              */
	uint8_t hundredths;                   /* Hundredths. Interpreted as unsigned. 0...99        */
	uint8_t deviation_high;               /* Interpreted as long,                               */
	uint8_t deviation_low;                /* Range -720 -> 720, in minutes of local time to GMT.*/
	uint8_t clock_status;                 /* The clock status for date time value.              */
} date_time_t;

/* Date type */
typedef struct tag_date_t
{
	uint8_t year_high;                    /* HI and LO of year. Interpreted as long-unsigned,   */
	uint8_t year_low;                     /* Range is 0 -> 0xFFFF-1. 0xFFFF mean not specified. */
	uint8_t month;                        /* Month. Interpreted as unsigned. 1...12             */
	uint8_t day_of_month;                 /* Day. Interpreted as unsigned. 1...31               */
	uint8_t day_of_week;                  /* Week. Interpreted as unsigned. 1...7               */
} date_t;

/* Time type */
typedef struct time_t
{
	uint8_t hour;                         /* Hour. Interpreted as unsigned. 0...23              */
	uint8_t minute;                       /* Minute. Interpreted as unsigned. 0...59            */
	uint8_t second;                       /* Hour. Interpreted as unsigned. 0...59              */
	uint8_t hundredths;                   /* Hundredths. Interpreted as unsigned. 0...99        */
} time_t;

/*******************************************************
Common types for classes
********************************************************/

typedef OBIS_DECLARE_FIXED_ARRAY(VariantString, FixedArrayVariantString);
typedef OBIS_DECLARE_FIXED_ARRAY(uint8_t, FixedArrayUint8_t);
typedef OBIS_DECLARE_FIXED_ARRAY(int8_t, FixedArrayInt8_t);
typedef OBIS_DECLARE_FIXED_ARRAY(int16_t, FixedArrayInt16_t);
typedef OBIS_DECLARE_FIXED_ARRAY(uint16_t, FixedArrayUint16_t);
typedef OBIS_DECLARE_FIXED_ARRAY(int32_t, FixedArrayInt32_t);
typedef OBIS_DECLARE_FIXED_ARRAY(uint32_t, FixedArrayUint32_t);
typedef OBIS_DECLARE_FIXED_ARRAY(int64_t, FixedArrayInt64_t);
typedef OBIS_DECLARE_FIXED_ARRAY(uint64_t, FixedArrayUint64_t);
typedef OBIS_DECLARE_FIXED_ARRAY(float32_t, FixedArrayFloat32_t);
typedef OBIS_DECLARE_FIXED_ARRAY(double64_t, FixedArrayDouble64_t);
typedef FixedArrayVariantString FixedArrayBitString;
typedef FixedArrayVariantString FixedArrayOctetString;
typedef FixedArrayVariantString FixedArrayVisibleString;
typedef FixedArrayVariantString FixedArrayUtf8String;
typedef OBIS_DECLARE_FIXED_ARRAY(date_time_t, FixedArrayDateTime_t);
typedef OBIS_DECLARE_FIXED_ARRAY(date_t, FixedArrayDate_t);
typedef OBIS_DECLARE_FIXED_ARRAY(time_t, FixedArrayTime_t);
typedef OBIS_DECLARE_FIXED_ARRAY(choice_t, FixedArrayChoice_t);

typedef OBIS_DECLARE_VARIANT_ARRAY(VariantString, VariantArrayVariantString);
typedef OBIS_DECLARE_VARIANT_ARRAY(uint8_t, VariantArrayUint8_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(int8_t, VariantArrayInt8_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(int16_t, VariantArrayInt16_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(uint16_t, VariantArrayUint16_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(int32_t, VariantArrayInt32_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(uint32_t, VariantArrayUint32_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(int64_t, VariantArrayInt64_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(uint64_t, VariantArrayUint64_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(float32_t, VariantArrayFloat32_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(double64_t, VariantArrayDouble64_t);
typedef VariantArrayVariantString VariantArrayBitString;
typedef VariantArrayVariantString VariantArrayOctetString;
typedef VariantArrayVariantString VariantArrayVisibleString;
typedef VariantArrayVariantString VariantArrayUtf8String;
typedef OBIS_DECLARE_VARIANT_ARRAY(date_time_t, VariantArrayDateTime_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(date_t, VariantArrayDate_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(time_t, VariantArrayTime_t);
typedef OBIS_DECLARE_VARIANT_ARRAY(choice_t, VariantArrayChoice_t);

/* Access right */
typedef struct tag_access_right_t
{
	struct tag_attributes {
		uint8_t *p_list;
		uint16_t length;
	} attributes;

	struct tag_methods {
		uint8_t *p_list;
		uint16_t length;
	} methods;

} access_right_t;

/* child record for 1 object definition */
typedef struct tag_child_record_t
{
	uint8_t			logical_name[6];	/* Logical name (OBIS code) of the object. */
	access_right_t	*p_access_right;	/* Access right definition for 1 object    */
} child_record_t;

/* Request type enumeration (GET/SET/ACTION) */
typedef enum tag_req_type_t
{
	REQ_TYPE_GET = 0,		/* GET request     */
	REQ_TYPE_SET = 1,		/* SET request     */
	REQ_TYPE_ACTION = 2,    /* ACTION request  */
} req_type_t;

/* Distributor state */
typedef enum tag_distributor_state_t
{
	DIST_BEFORE_CLASS_FUNCTION = 0,		/* Distribution before class function is called */
	DIST_UNDER_CLASS_FUNCTION,			/* Distribution under processing on class function */
	DIST_AFTER_CLASS_FUNCTION,			/* Distribution after class function is called */
} distributor_state_t;

/* Detail service type of GET/SET/ACTION service call (NORMAL/NEXT/LIST...) */
typedef union tag_service_type_t
{
	CosemGetRequestType		get;
	CosemSetRequestType		set;
	CosemActionRequestType	action;
} service_type_t;

/* GET/SET/ACTION service descriptor */
typedef union tag_descriptor_t
{
	CosemAttributeDescriptor	attr;
	CosemMethodDescriptor		method;

	struct
	{
		uint16_t 	class_id;
		uint8_t		instance_id[6];
		uint8_t		item_id;
	} all;
} descriptor_t;

/* Selective access params */
typedef OptionalSelectiveAccessDescriptor selective_access_t;

/* A session of association connection */
typedef struct tagAsscConnectionSession
{
	AsscChannel				connected_assc_id;					/* Current connected assc id of this connection session */
	MgmtChannel				mgmt_channel_id;					/* Current mgmt channel that associated with this connection session */
	uint16_t				client_sap;							/* Client SAP that connected to this association session */
	uint16_t				server_sap;							/* Server SAP that connected to this association session */
	const AssociationCfg	*p_assc_config;						/* Configuration of association */
	ConformanceBits			negotiated_conformance;				/* After Association is openned. Store ConformanceBits. */
	uint16_t				client_max_pdu_size;				/* After Association is openned. Store Client Max Pdu Size. */
	uint16_t				negotiated_client_max_pdu_size;		/* After Association is openned. Store Client Max Pdu Size after adjust with OBIS capability on encode & send PDU. */
	MandatoryString			CtoS;								/* After Association is openned. Store CtoS send from Client */
	MandatoryString			dedicated_key;						/* After Association is openned. Store dedicated key send from client */
	uint8_t					hls_restrict_mode;					/* Inidicates that current connected association need to pass reply_to_HLS_authentication() method for full access */
	uint8_t					get_service_is_block_response;		/* Inidicates currently is in block transfer or not */
	uint32_t				get_service_block_number;			/* Current block number of the last GET service NORMAL */
	descriptor_t			get_service_attr_desc;				/* Attribute descriptor of the last GET service NORMAL */
} AsscConnectionSession;

/* Output result for each Services : GET/SET/ACTION */
typedef struct tag_distributor_result_t
{
	union {
		DataAccessResult_Value	data_access;
		ActionResult_Value		action;
	} result;
	uint8_t		partial;
	uint8_t		success;
} distributor_result_t;

/* A structure link for complex type encoder/decoder function */
typedef struct tag_structure_link_t
{
	attr_type_t type;
	uint8_t		*ptr;
	uint16_t	size;
} structure_link_t;

/* A structure offset for complex type encoder/decoder function */
typedef struct tag_structure_offset_t
{
	attr_type_t type;
	uint8_t		*ptr;
	uint16_t	size;
} structure_offset_t;

/* A link of memcpy request */
typedef struct tag_memlink_t
{
	uint8_t		*dest;
	uint8_t		*src;
	uint16_t	size;
} memlink_t;

/* memlink, used to copy a region of memory from cloned object into real object */
typedef struct tag_memlinks_t
{
	memlink_t	*p_content;		/* Buffer location */
	uint16_t	length;			/* Current length (usage) of buffer */
	uint16_t	alloc_size;		/* Alloc size */
} memlinks_t;

/* Params input for each distributor function : GET/SET/ACTION */
typedef struct tag_distributor_params_t
{
	uint16_t  				master_index;			/* [In] Id of the row in master list */
	uint16_t  				child_index;			/* [In] Id of the row in child list */
	child_record_t			*p_child_record;		/* [In] Child record of calling object */
	uint8_t					connected_assc_id;		/* [In] Connected assc id of the current request */
	AsscConnectionSession	*p_assc_session;		/* [In] Connected assc session of the current request */
	req_type_t				req_type;				/* [In] Request type (GET/SET/ACTION) */
	service_type_t			service_type;			/* [In] Service type */
	descriptor_t			descriptor;				/* [In] Descriptor of attr or method */
	selective_access_t		selective_access;		/* [In] Selective access params for GET/SET service */
	void					*p_library_descriptor;	/* [In] Library Descriptor (GET/SET/ACTION), refer to r_dlms_application.h for details.
													 *      NULL is passed into this param in some cases */
	MandatoryString			in_data;				/* [In] Data from library in case of SET/ACTION */
	MandatoryString			out_data;				/* [Out] Output buffer for encoded data */
	uint16_t				*p_out_encoded_len;		/* [Out] Actual output buffer length for encoded data */
	distributor_state_t		distributor_state;		/* [In] Distribution state of current params (before or under or after class function) */
	uint8_t					handled;				/* [In, Out] Indicates that the service req (GET/SET/ACTION) is already handled and no need subsequence call */
	struct tag_service_params {
		malloc_buffer_t		malloc;					/* [In, Out] Temporary buffer of service parametes decoded from SET or ACTION service, will be clean when exit class service call */
		memlinks_t			memlinks;				/* [In, Out] Links of memcpy requests, to do memory copy from malloc buffer to object defined buffer */
		uint8_t				created;				/* [Out] Indicates that an object of service params has been created on dynamic buffer */
		uint8_t				decode_success;			/* [Out] Indicates that object in malloc is decode successful & ready to use on user distributor */
		uint8_t				sync;					/* [In, Out] Indicates that temporary params on SET or ACTION service will be copied to object defined buffer thru memlinks */
	} service_params;								/* [In, Out] Service parameters */
	distributor_result_t	result;					/* [In, Out] Distribution result, flow from user distributor thru class function */
} distributor_params_t;

/* A function pointer type for Class Distributor : GET/SET/ACTION */
typedef void (*fp_distributor_t) (distributor_params_t *p_params);

/* Object encoder function */
typedef uint16_t (*fp_obj_encoder_func)(MandatoryString out_data, void *p_object);

/* Object decoder function */
typedef uint16_t (*fp_obj_decoder_func)(void *p_object, MandatoryString in_data);

/* Object redirect (structure clone) function prototype */
typedef void *(*fp_obj_redirect_t)(distributor_params_t *p_params, void *p_object);
typedef void *(*fp_obj_structure_array_redirect_t)(distributor_params_t *p_params, void *p_object, uint16_t size);

/* A row of a master table */
typedef struct tag_master_record_t
{
	uint8_t					class_version;       /* Version of the class                               */
	uint8_t					number_attrs;        /* Number of attributes of the class, as in Blue Book */
	uint8_t					number_methods;      /* Number of methods of the class, as in Blue Book    */
	fp_distributor_t		fp_distributor;		 /* Distributor function of class				       */
	uint16_t				*child_list_size;    /* Size of the child-list                             */
	child_record_t			*child_list_pointer; /* Child-list pointer                                 */
	uint16_t				child_item_size;	 /* Child item size                                    */
} master_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const uint16_t						g_classes_total_number_objects;
extern const uint16_t						g_classes_total_number_objects_each_assc[OBIS_NUMBER_OF_ASSOCIATION];
extern const uint16_t						g_classes_max_number_of_attrs;
extern const uint16_t						g_classes_max_number_of_methods;
extern const master_record_t				g_classes_master_table[];
extern const uint16_t						g_classes_total_master_table_elements;
extern AsscConnectionSession				g_classes_assc_connection_session[DLMS_MAX_ASSOCIATION_SUPPORT];
extern const access_right_t					g_classes_access_right_none;
extern const e_master_table_class_index_t	g_dlms_master_class_indexes[];
extern const uint16_t						g_biggest_class_id_number;

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* ---------------
 * Utility APIs
 * ---------------
 */

/* Compare 2 OBIS code (5 head bytes only) whether equal (TRUE) or not (FALSE) */
uint8_t R_DLMS_CLASSES_CompareObisCode(uint8_t *obis_code, uint8_t *input_code);

/* ----------------------------
 * APIs for CLASSES component
 * ----------------------------
 */

/* Initialize of classes */
void R_DLMS_CLASSES_Init(void);

/* Polling process for all classes */
void R_DLMS_CLASSES_PollingProcessing(void);

/* -------------------------------------------
 * APIs for encode/decode of fixed string
 * -------------------------------------------
 */

/* Encode fixed string */
uint16_t R_DLMS_CLASSES_EncodeFixedString(
	MandatoryString out_data,
	attr_type_t type,
	FixedString *p_object
);

/* Decode fixed string */
uint16_t R_DLMS_CLASSES_DecodeFixedString(
	FixedString *p_object,
	attr_type_t type,
	MandatoryString in_data
);

/* -------------------------------------------
 * APIs for encode/decode of variant string
 * -------------------------------------------
 */

/* Encode variant array */
uint16_t R_DLMS_CLASSES_EncodeVariantString(
	MandatoryString out_data,
	Data_Tag data_type,
	VariantString *p_object
);

/* Decode variant array */
uint16_t R_DLMS_CLASSES_DecodeVariantString(
	VariantString *p_object,
	Data_Tag data_type,
	MandatoryString in_data
);

/* -----------------------------------------------
 * APIs for encode/decode of abstract fixed array
 * -----------------------------------------------
 */

 /* Encode abstract fixed array */
uint16_t R_DLMS_CLASSES_EncodeAbstractFixedArray(
	MandatoryString out_data,
	AbstractFixedArray *p_object,
	fp_obj_encoder_func fp_encoder,
	uint16_t element_size
);

/* Decode abstract fixed array */
uint16_t R_DLMS_CLASSES_DecodeAbstractFixedArray(
	AbstractFixedArray *p_object,
	MandatoryString in_data,
	fp_obj_decoder_func fp_decoder,
	uint16_t element_size
);

/* --------------------------------------------------
 * APIs for encode/decode of abstract variant array
 * --------------------------------------------------
 */

 /* Encode abstract variant array */
uint16_t R_DLMS_CLASSES_EncodeAbstractVariantArray(
	MandatoryString out_data,
	AbstractVariantArray *p_object,
	fp_obj_encoder_func fp_encoder,
	uint16_t element_size
);

/* Decode abstract variant array */
uint16_t R_DLMS_CLASSES_DecodeAbstractVariantArray(
	AbstractVariantArray *p_object,
	MandatoryString in_data,
	fp_obj_decoder_func fp_decoder,
	uint16_t element_size
);

/* -----------------------------------------------
 * APIs for creation of object (malloc) & memlink
 * -----------------------------------------------
 */

/* Create object (basic type) on dymamic buffer of distribution params */
void *R_DLMS_CLASSES_CreateObject(
	distributor_params_t *p_params,
	void *p_object,
	uint16_t object_size,
	uint16_t options
);

/* Create AbstractFixedArray on dymamic buffer of distribution params */
AbstractFixedArray *R_DLMS_CLASSES_CreateFixedArray(
	distributor_params_t *p_params,
	AbstractFixedArray *p_object,
	uint16_t element_size,
	uint16_t options
);

/* Create AbstractVariantArray on dymamic buffer of distribution params */
AbstractVariantArray *R_DLMS_CLASSES_CreateVariantArray(
	distributor_params_t *p_params,
	AbstractVariantArray *p_object,
	uint16_t element_size,
	uint16_t options
);

/* Create FixedString on dymamic buffer of distribution params */
FixedString *R_DLMS_CLASSES_CreateFixedString(
	distributor_params_t *p_params,
	FixedString *p_object,
	uint16_t options
);

/* Create VariantString on dymamic buffer of distribution params */
VariantString *R_DLMS_CLASSES_CreateVariantString(
	distributor_params_t *p_params,
	VariantString *p_object,
	uint16_t options
);

/* Create choice_t on dymamic buffer of distribution params */
choice_t *R_DLMS_CLASSES_CreateChoice(
	distributor_params_t *p_params,
	choice_t *p_object,
	uint16_t options
);

/* -----------------------------------------------
 * APIs for creation new object (malloc)
 * -----------------------------------------------
 */
 /* Fixed array */
FixedArrayUint16_t * R_DLMS_CLASSES_CreatNew_FixedArray_LongUnsigned(distributor_params_t *p_params, uint16_t array_size);
FixedString * R_DLMS_CLASSES_CreatNew_Fixedstring(distributor_params_t *p_params, uint16_t string_size);

/* Variant array */
BitString * R_DLMS_CLASSES_CreatNew_Bitstring(distributor_params_t *p_params, uint16_t string_size);
OctetString * R_DLMS_CLASSES_CreatNew_Octetstring(distributor_params_t *p_params, uint16_t string_size);
VariantArrayUint32_t * R_DLMS_CLASSES_CreatNew_VariantArray_DoubleLongUnsigned(distributor_params_t *p_params, uint16_t array_size);
VariantArrayOctetString *R_DLMS_CLASSES_CreatNew_VariantArrayOctetString(distributor_params_t *p_params, VariantArrayOctetString *p_object, uint16_t array_size, uint16_t string_element_length);

/* -----------------------------------------------
 * APIs for attribute distribution
 * -----------------------------------------------
 */

/* Distributor of basic type */
void R_DLMS_CLASSES_DistributeBasicType(
	distributor_params_t *p_params,
	attr_type_t type,
	void *p_object,
	uint16_t size
);

/* Distribute fixed string */
void R_DLMS_CLASSES_DistributeFixedString(
	distributor_params_t *p_params,
	attr_type_t type,
	FixedString *p_object
);

/* Distribute variant string */
void R_DLMS_CLASSES_DistributeVariantString(
	distributor_params_t *p_params,
	attr_type_t type,
	VariantString *p_object
);

/* Distribute complex type */
void R_DLMS_CLASSES_DistributeComplexType(
	distributor_params_t *p_params,
	fp_obj_encoder_func fp_encoder,
	fp_obj_decoder_func fp_decoder,
	fp_obj_redirect_t	fp_redirect,
	void *p_object
);
void R_DLMS_CLASSES_Distribute_ArrayofStructure(
	distributor_params_t 				*p_params,
	fp_obj_encoder_func 				fp_encoder,
	fp_obj_decoder_func 				fp_decoder,
	fp_obj_structure_array_redirect_t	fp_redirect,
	void *p_object
);

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeBoolean, uint8_t);						/* Encoder for type boolean */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeBitString, BitString);					/* Encoder for type bit-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeDoubleLong, int32_t);					/* Encoder for type double-long */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeDoubleLongUnsigned, uint32_t);			/* Encoder for type double-long-unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeOctetString, OctetString);				/* Encoder for type octet-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVisibleString, VisibleString);			/* Encoder for type visible-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeUtf8String, Utf8String);					/* Encoder for type utf8-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeBcd, int8_t);							/* Encoder for type bcd */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeInteger, int8_t);						/* Encoder for type integer */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeLong, int16_t);							/* Encoder for type long */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeUnsigned, uint8_t);						/* Encoder for type unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeLongUnsigned, uint16_t);					/* Encoder for type long-unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeLong64, int64_t);						/* Encoder for type long64 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeLong64Unsigned, uint64_t);				/* Encoder for type long64-unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeEnum, uint8_t);							/* Encoder for type enum */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFloat32, float32_t);						/* Encoder for type float32 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFloat64, double64_t);					/* Encoder for type float64 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeDateTime, date_time_t);					/* Encoder for type date-time */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeDateTimeAsOctetString, date_time_t);		/* Encoder for type date-time as OctetString */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeDate, date_t);							/* Encoder for type date */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeDateAsOctetString, date_t);				/* Encoder for type date as OctetString */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeTime, time_t);							/* Encoder for type time */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeTimeAsOctetString, time_t);				/* Encoder for type time as OctetString */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeChoice, choice_t);						/* Encoder for type choice_t */

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeBoolean, uint8_t);						/* Decoder for type boolean */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeBitString, BitString);					/* Decoder for type bit-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeDoubleLong, int32_t);					/* Decoder for type double-long */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeDoubleLongUnsigned, uint32_t);			/* Decoder for type double-long-unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeOctetString, OctetString);				/* Decoder for type octet-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVisibleString, VisibleString);			/* Decoder for type visible-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeUtf8String, Utf8String);					/* Decoder for type utf8-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeBcd, int8_t);							/* Decoder for type bcd */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeInteger, int8_t);						/* Decoder for type integer */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeLong, int16_t);							/* Decoder for type long */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeUnsigned, uint8_t);						/* Decoder for type unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeLongUnsigned, uint16_t);					/* Decoder for type long-unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeLong64, int64_t);						/* Decoder for type long64 */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeLong64Unsigned, uint64_t);				/* Decoder for type long64-unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeEnum, uint8_t);							/* Decoder for type enum */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFloat32, float32_t);						/* Decoder for type float32 */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFloat64, double64_t);					/* Decoder for type float64 */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeDateTime, date_time_t);					/* Decoder for type date-time */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeDateTimeAsOctetString, date_time_t);		/* Decoder for type date-time as OctetString */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeDate, date_t);							/* Decoder for type date */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeDateAsOctetString, date_t);				/* Decoder for type date as OctetString */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeTime, time_t);							/* Decoder for type time */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeTimeAsOctetString, time_t);				/* Decoder for type time as OctetString */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeChoice, choice_t);						/* Decoder for type choice_t */

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayBoolean, FixedArrayUint8_t);						/* Encoder for FixedArray of boolean */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayBitString, FixedArrayBitString);					/* Encoder for FixedArray of bit-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayDoubleLong, FixedArrayInt32_t);					/* Encoder for FixedArray of double-long */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayDoubleLongUnsigned, FixedArrayUint32_t);			/* Encoder for FixedArray of double-long-unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayOctetString, FixedArrayOctetString);				/* Encoder for FixedArray of octet-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayVisibleString, FixedArrayVisibleString);			/* Encoder for FixedArray of visible-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayUtf8String, FixedArrayUtf8String);					/* Encoder for FixedArray of utf8-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayBcd, FixedArrayInt8_t);							/* Encoder for FixedArray of bcd */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayInteger, FixedArrayInt8_t);						/* Encoder for FixedArray of integer */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayLong, FixedArrayInt16_t);							/* Encoder for FixedArray of long */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayUnsigned, FixedArrayUint8_t);						/* Encoder for FixedArray of unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayLongUnsigned, FixedArrayUint16_t);					/* Encoder for FixedArray of long-unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayLong64, FixedArrayInt64_t);						/* Encoder for FixedArray of long64 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayLong64Unsigned, FixedArrayUint64_t);				/* Encoder for FixedArray of long64-unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayEnum, FixedArrayUint8_t);							/* Encoder for FixedArray of enum */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayFloat32, FixedArrayFloat32_t);						/* Encoder for FixedArray of float32 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayFloat64, FixedArrayDouble64_t);					/* Encoder for FixedArray of float64 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayDateTime, FixedArrayDateTime_t);					/* Encoder for FixedArray of date-time */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayDateTimeAsOctetString, FixedArrayDateTime_t);		/* Encoder for FixedArray of date-time as OctetString */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayDate, FixedArrayDate_t);							/* Encoder for FixedArray of date */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayDateAsOctetString, FixedArrayDate_t);				/* Encoder for FixedArray of date as OctetString */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayTime, FixedArrayTime_t);							/* Encoder for FixedArray of time */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayTimeAsOctetString, FixedArrayTime_t);				/* Encoder for FixedArray of time as OctetString */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeFixedArrayChoice, FixedArrayChoice_t);						/* Encoder for FixedArray of choice_t */

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayBoolean, FixedArrayUint8_t);						/* Decoder for FixedArray of boolean */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayBitString, FixedArrayBitString);					/* Decoder for FixedArray of bit-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayDoubleLong, FixedArrayInt32_t);					/* Decoder for FixedArray of double-long */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayDoubleLongUnsigned, FixedArrayUint32_t);			/* Decoder for FixedArray of double-long-unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayOctetString, FixedArrayOctetString);				/* Decoder for FixedArray of octet-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayVisibleString, FixedArrayVisibleString);			/* Decoder for FixedArray of visible-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayUtf8String, FixedArrayUtf8String);					/* Decoder for FixedArray of utf8-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayBcd, FixedArrayInt8_t);							/* Decoder for FixedArray of bcd */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayInteger, FixedArrayInt8_t);						/* Decoder for FixedArray of integer */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayLong, FixedArrayInt16_t);							/* Decoder for FixedArray of long */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayUnsigned, FixedArrayUint8_t);						/* Decoder for FixedArray of unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayLongUnsigned, FixedArrayUint16_t);					/* Decoder for FixedArray of long-unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayLong64, FixedArrayInt64_t);						/* Decoder for FixedArray of long64 */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayLong64Unsigned, FixedArrayUint64_t);				/* Decoder for FixedArray of long64-unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayEnum, FixedArrayUint8_t);							/* Decoder for FixedArray of enum */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayFloat32, FixedArrayFloat32_t);						/* Decoder for FixedArray of float32 */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayFloat64, FixedArrayDouble64_t);					/* Decoder for FixedArray of float64 */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayDateTime, FixedArrayDateTime_t);					/* Decoder for FixedArray of date-time */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayDateTimeAsOctetString, FixedArrayDateTime_t);		/* Decoder for FixedArray of date-time as OctetString */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayDate, FixedArrayDate_t);							/* Decoder for FixedArray of date */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayDateAsOctetString, FixedArrayDate_t);				/* Decoder for FixedArray of date as OctetString */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayTime, FixedArrayTime_t);							/* Decoder for FixedArray of time */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayTimeAsOctetString, FixedArrayTime_t);				/* Decoder for FixedArray of time as OctetString */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeFixedArrayChoice, FixedArrayChoice_t);						/* Decoder for FixedArray of choice_t */

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayBoolean, VariantArrayUint8_t);						/* Encoder for VariantArray of boolean */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayBitString, VariantArrayBitString);					/* Encoder for VariantArray of bit-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayDoubleLong, VariantArrayInt32_t);					/* Encoder for VariantArray of double-long */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayDoubleLongUnsigned, VariantArrayUint32_t);			/* Encoder for VariantArray of double-long-unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayOctetString, VariantArrayOctetString);				/* Encoder for VariantArray of octet-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayVisibleString, VariantArrayVisibleString);			/* Encoder for VariantArray of visible-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayUtf8String, VariantArrayUtf8String);					/* Encoder for VariantArray of utf8-string */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayBcd, VariantArrayInt8_t);							/* Encoder for VariantArray of bcd */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayInteger, VariantArrayInt8_t);						/* Encoder for VariantArray of integer */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayLong, VariantArrayInt16_t);							/* Encoder for VariantArray of long */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayUnsigned, VariantArrayUint8_t);						/* Encoder for VariantArray of unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayLongUnsigned, VariantArrayUint16_t);					/* Encoder for VariantArray of long-unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayLong64, VariantArrayInt64_t);						/* Encoder for VariantArray of long64 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayLong64Unsigned, VariantArrayUint64_t);				/* Encoder for VariantArray of long64-unsigned */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayEnum, VariantArrayUint8_t);							/* Encoder for VariantArray of enum */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayFloat32, VariantArrayFloat32_t);						/* Encoder for VariantArray of float32 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayFloat64, VariantArrayDouble64_t);					/* Encoder for VariantArray of float64 */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayDateTime, VariantArrayDateTime_t);					/* Encoder for VariantArray of date-time */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayDateTimeAsOctetString, VariantArrayDateTime_t);		/* Encoder for VariantArray of date-time as OctetString */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayDate, VariantArrayDate_t);							/* Encoder for VariantArray of date */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayDateAsOctetString, VariantArrayDate_t);				/* Encoder for VariantArray of date as OctetString */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayTime, VariantArrayTime_t);							/* Encoder for VariantArray of time */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayTimeAsOctetString, VariantArrayTime_t);				/* Encoder for VariantArray of time as OctetString */
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeVariantArrayChoice, VariantArrayChoice_t);						/* Encoder for VariantArray of choice_t */

OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayBoolean, VariantArrayUint8_t);						/* Decoder for VariantArray of boolean */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayBitString, VariantArrayBitString);					/* Decoder for VariantArray of bit-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayDoubleLong, VariantArrayInt32_t);					/* Decoder for VariantArray of double-long */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayDoubleLongUnsigned, VariantArrayUint32_t);			/* Decoder for VariantArray of double-long-unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayOctetString, VariantArrayOctetString);				/* Decoder for VariantArray of octet-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayVisibleString, VariantArrayVisibleString);			/* Decoder for VariantArray of visible-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayUtf8String, VariantArrayUtf8String);					/* Decoder for VariantArray of utf8-string */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayBcd, VariantArrayInt8_t);							/* Decoder for VariantArray of bcd */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayInteger, VariantArrayInt8_t);						/* Decoder for VariantArray of integer */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayLong, VariantArrayInt16_t);							/* Decoder for VariantArray of long */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayUnsigned, VariantArrayUint8_t);						/* Decoder for VariantArray of unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayLongUnsigned, VariantArrayUint16_t);					/* Decoder for VariantArray of long-unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayLong64, VariantArrayInt64_t);						/* Decoder for VariantArray of long64 */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayLong64Unsigned, VariantArrayUint64_t);				/* Decoder for VariantArray of long64-unsigned */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayEnum, VariantArrayUint8_t);							/* Decoder for VariantArray of enum */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayFloat32, VariantArrayFloat32_t);						/* Decoder for VariantArray of float32 */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayFloat64, VariantArrayDouble64_t);					/* Decoder for VariantArray of float64 */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayDateTime, VariantArrayDateTime_t);					/* Decoder for VariantArray of date-time */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayDateTimeAsOctetString, VariantArrayDateTime_t);		/* Decoder for VariantArray of date-time as OctetString*/
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayDate, VariantArrayDate_t);							/* Decoder for VariantArray of date */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayDateAsOctetString, VariantArrayDate_t);				/* Decoder for VariantArray of date OctetString */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayTime, VariantArrayTime_t);							/* Decoder for VariantArray of time */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayTimeAsOctetString, VariantArrayTime_t);				/* Decoder for VariantArray of time OctetString */
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeVariantArrayChoice, VariantArrayChoice_t);						/* Decoder for VariantArray of choice_t */

OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeBoolean, uint8_t);					/* Distribute type boolean */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeBitString, BitString);				/* Distribute type bit-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeDoubleLong, int32_t);				/* Distribute type double-long */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeDoubleLongUnsigned, uint32_t);		/* Distribute type double-long-unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeOctetString, OctetString);			/* Distribute type octet-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVisibleString, VisibleString);		/* Distribute type visible-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeUtf8String, Utf8String);				/* Distribute type utf8-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeBcd, int8_t);						/* Distribute type bcd */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeInteger, int8_t);					/* Distribute type integer */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeLong, int16_t);						/* Distribute type long */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeUnsigned, uint8_t);					/* Distribute type unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeLongUnsigned, uint16_t);				/* Distribute type long-unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeLong64, int64_t);					/* Distribute type long64 */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeLong64Unsigned, uint64_t);			/* Distribute type long64-unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeEnum, uint8_t);						/* Distribute type enum */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFloat32, float32_t);					/* Distribute type float32 */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFloat64, double64_t);				/* Distribute type float64 */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeDateTime, date_time_t);				/* Distribute type date-time */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeDateTimeAsOctetString, date_time_t);	/* Distribute type date-time as OctetString */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeDate, date_t);						/* Distribute type date */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeDateAsOctetString, date_t);			/* Distribute type date as OctetString */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeTime, time_t);						/* Distribute type time */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeTimeAsOctetString, time_t);			/* Distribute type time as OctetString */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeChoice, choice_t);					/* Distribute type choice_t */

OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayBoolean, FixedArrayUint8_t);						/* Distribute for FixedArray of boolean */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayBitString, FixedArrayBitString);					/* Distribute for FixedArray of bit-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayDoubleLong, FixedArrayInt32_t);					/* Distribute for FixedArray of double-long */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayDoubleLongUnsigned, FixedArrayUint32_t);			/* Distribute for FixedArray of double-long-unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayOctetString, FixedArrayOctetString);				/* Distribute for FixedArray of octet-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayVisibleString, FixedArrayVisibleString);			/* Distribute for FixedArray of visible-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayUtf8String, FixedArrayUtf8String);					/* Distribute for FixedArray of utf8-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayBcd, FixedArrayInt8_t);							/* Distribute for FixedArray of bcd */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayInteger, FixedArrayInt8_t);						/* Distribute for FixedArray of integer */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayLong, FixedArrayInt16_t);							/* Distribute for FixedArray of long */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayUnsigned, FixedArrayUint8_t);						/* Distribute for FixedArray of unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayLongUnsigned, FixedArrayUint16_t);					/* Distribute for FixedArray of long-unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayLong64, FixedArrayInt64_t);						/* Distribute for FixedArray of long64 */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayLong64Unsigned, FixedArrayUint64_t);				/* Distribute for FixedArray of long64-unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayEnum, FixedArrayUint8_t);							/* Distribute for FixedArray of enum */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayFloat32, FixedArrayFloat32_t);						/* Distribute for FixedArray of float32 */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayFloat64, FixedArrayDouble64_t);					/* Distribute for FixedArray of float64 */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayDateTime, FixedArrayDateTime_t);					/* Distribute for FixedArray of date-time */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayDateTimeAsOctetString, FixedArrayDateTime_t);		/* Distribute for FixedArray of date-time as OctetString */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayDate, FixedArrayDate_t);							/* Distribute for FixedArray of date */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayDateAsOctetString, FixedArrayDate_t);				/* Distribute for FixedArray of date as OctetString */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayTime, FixedArrayTime_t);							/* Distribute for FixedArray of time */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayTimeAsOctetString, FixedArrayTime_t);				/* Distribute for FixedArray of time as OctetString */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeFixedArrayChoice, FixedArrayChoice_t);						/* Distribute for FixedArray of choice_t */

OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayBoolean, VariantArrayUint8_t);						/* Distribute for VariantArray of boolean */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayBitString, VariantArrayBitString);					/* Distribute for VariantArray of bit-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayDoubleLong, VariantArrayInt32_t);					/* Distribute for VariantArray of double-long */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayDoubleLongUnsigned, VariantArrayUint32_t);			/* Distribute for VariantArray of double-long-unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayOctetString, VariantArrayOctetString);				/* Distribute for VariantArray of octet-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayVisibleString, VariantArrayVisibleString);			/* Distribute for VariantArray of visible-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayUtf8String, VariantArrayUtf8String);					/* Distribute for VariantArray of utf8-string */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayBcd, VariantArrayInt8_t);							/* Distribute for VariantArray of bcd */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayInteger, VariantArrayInt8_t);						/* Distribute for VariantArray of integer */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayLong, VariantArrayInt16_t);							/* Distribute for VariantArray of long */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayUnsigned, VariantArrayUint8_t);						/* Distribute for VariantArray of unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayLongUnsigned, VariantArrayUint16_t);					/* Distribute for VariantArray of long-unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayLong64, VariantArrayInt64_t);						/* Distribute for VariantArray of long64 */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayLong64Unsigned, VariantArrayUint64_t);				/* Distribute for VariantArray of long64-unsigned */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayEnum, VariantArrayUint8_t);							/* Distribute for VariantArray of enum */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayFloat32, VariantArrayFloat32_t);						/* Distribute for VariantArray of float32 */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayFloat64, VariantArrayDouble64_t);					/* Distribute for VariantArray of float64 */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayDateTime, VariantArrayDateTime_t);					/* Distribute for VariantArray of date-time */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayDateTimeAsOctetString, VariantArrayDateTime_t);		/* Distribute for VariantArray of date-time as OctetString */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayDate, VariantArrayDate_t);							/* Distribute for VariantArray of date */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayDateAsOctetString, VariantArrayDate_t);				/* Distribute for VariantArray of date as OctetString */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayTime, VariantArrayTime_t);							/* Distribute for VariantArray of time */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayTimeAsOctetString, VariantArrayTime_t);				/* Distribute for VariantArray of time as OctetString */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeVariantArrayChoice, VariantArrayChoice_t);						/* Distribute for VariantArray of choice_t */
/* Delcare for redirect choice type */
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_Redirect_ChoiceAttribute, choice_t);
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectVariantArrayVariantString, VariantArrayVariantString);
void R_DLMS_QuickAck_DataAccessResult (
	distributor_params_t *p_params, 
	uint8_t result,
	DataAccessResult_Value error_code
);

void R_DLMS_QuickAck_ActionResult (
	distributor_params_t *p_params, 
	uint8_t result,
	ActionResult_Value error_code
);

/* Distribute a class object with its abstract class distributor and user distributor function */
void R_DLMS_CLASSES_DistributeClass(
	fp_distributor_t fp_class_func,
	fp_distributor_t fp_user_func,
	distributor_params_t *p_params
);

/* Check if target memory location is writable (RAM) */
uint8_t	R_DLMS_CLASSES_IsBufferWritable(uint8_t *p_buffer);

/* Register a memlink into distributor params */
uint8_t R_DLMS_CLASSES_RegisterMemcpyLink(distributor_params_t *p_params, uint8_t *dest, uint8_t *src, uint16_t size);

/* Check if 2 FixedString objects are equal */
uint8_t R_DLMS_CLASSES_IsFixedStringEqual(FixedString *dest, FixedString *src);

/* Check if 2 VariantString objects are equal */
uint8_t R_DLMS_CLASSES_IsVariantStringEqual(VariantString *dest, VariantString *src);

/* Decode a class object */
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
);

/* Internally encode data of attribute regardless of the access right */
distributor_result_t R_DLMS_CLASSES_EncodeDataAttributeInternally(
	uint8_t				connected_assc_id,
	req_type_t			req_type,
	descriptor_t		*p_descriptor,
	selective_access_t	*p_selective_access,
	service_type_t		*p_service_type,
	void				*p_library_descriptor,
	MandatoryString		in_data,
	MandatoryString		out_data,
#if defined(DLMS_LIB_VERSION) && (DLMS_LIB_VERSION == LIB_V2_2)
	uint16_t			*p_encoded_length
#else
	uint16_t			*p_encoded_length,
	malloc_buffer_t		*p_malloc_buffer
#endif//defined(DLMS_LIB_VERSION) && (DLMS_LIB_VERSION == LIB_V2_2)
);

/* Support functions */
uint8_t R_DLMS_convert_ipv6_bytes_to_string(FixedString * p_ip_address_in_out);
uint8_t R_DLMS_convert_ipv6_array_bytes_to_string(VariantArrayOctetString * p_ip_address_array_in_out);

/* Invoke distribution of a object internally */
#define R_DLMS_CLASSES_InvokeDistribution	R_DLMS_CLASSES_EncodeDataAttributeInternally

#endif /* _R_DLMS_CLASSES_H */

