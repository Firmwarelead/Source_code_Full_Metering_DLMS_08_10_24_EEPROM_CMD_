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
* File Name    : r_dlms_usercode_class18.c
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
#include "r_dlms_usercode_class18.h"

/* User application */
#include "r_dlms_fw_upgrade.h"
#include "r_dlms_app.h"

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

/* User code variable */


/* User code function */

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

/***********************************************************************************************************
* Object name:      Image Transfer
* Object number:    00
* Object obis code: 0.0.44.0.0.255
***********************************************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_USER_ic18_obj00_att02_get
* Description   : Object name       : Image Transfer
*                 Object index      : 00
*                 Class             : 18
*                 Attribute order   : 02
*                 Attribute name    : image_block_size
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {4, Firmware upgrade }; ; 
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_att02_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
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
	//uint32_t link_data = 256;
	/* Set value */
	//*((uint32_t *)p_attribute_get) = link_data;

	/* Start user code here */
	*((uint32_t *)p_attribute_get) = IMAGE_BLOCK_TRANSFER_SIZE;
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/* Please update your array size following your setting change by asigning under variable */
/* !!!This value is NUMBER OF BIT(unit: bit) */
/* For image_transferred_blocks_status */
const uint16_t r_dlms_ic18_obj00_att03_image_transferred_blocks_status_bitstring_length = IMAGE_ALLOCATED_SIZE / IMAGE_BLOCK_TRANSFER_SIZE;
/******************************************************************************
* Function Name : R_DLMS_USER_ic18_obj00_att03_get
* Description   : Object name       : Image Transfer
*                 Object index      : 00
*                 Class             : 18
*                 Attribute order   : 03
*                 Attribute name    : image_transferred_blocks_status
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {4, Firmware upgrade }; ; 
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 BitString * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_att03_get(distributor_params_t * p_params, BitString * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	 This is BitString
	 BitString
	 {
	     uint8_t* p_content;
	     uint16_t length;
	     uint16_t alloc_size;
	 }
	 p_content:: uint8_t[], this is array of bytes which contain bit string,
	 please transfer from bits string to bytes array then assign to this.
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
	// uint8_t link_data[] = { 0x00 };
	/* Set length */
	/* !!! If you change link_data, please set again bitstring size in a head of this function */
	// p_attribute_get->length = r_dlms_ic18_obj00_att03_image_transferred_blocks_status_bitstring_length * 8;
	//memcpy(p_attribute_get->p_content, &link_data, r_dlms_ic18_obj00_att03_image_transferred_blocks_status_bitstring_length);

	/* Start user code here */
	if(R_DLMS_FWU_GetImgBlockTransferStatus(p_attribute_get->p_content, &p_attribute_get->length) == RLT_SUCCESS)
	{
		/* Get successfully */
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
* Function Name : R_DLMS_USER_ic18_obj00_att04_get
* Description   : Object name       : Image Transfer
*                 Object index      : 00
*                 Class             : 18
*                 Attribute order   : 04
*                 Attribute name    : image_first_not_transferred_block_number
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {4, Firmware upgrade }; ; 
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint32_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_att04_get(distributor_params_t * p_params, uint32_t * p_attribute_get)
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
	if(R_DLMS_FWU_GetImgFirstNotTransfferedBlock(p_attribute_get) == RLT_SUCCESS)
	{
		/* Get successfully */
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
* Function Name : R_DLMS_USER_ic18_obj00_att05_get
* Description   : Object name       : Image Transfer
*                 Object index      : 00
*                 Class             : 18
*                 Attribute order   : 05
*                 Attribute name    : image_transfer_enabled
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {4, Firmware upgrade }; ; 
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint8_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_att05_get(distributor_params_t * p_params, uint8_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint8_t(boolean)
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
	//uint8_t link_data = TRUE;
	/* Set value */
	//*((uint8_t *)p_attribute_get) = link_data;

	/* Start user code here */
	*((uint8_t *)p_attribute_get) = IMAGE_TRANSFER_ENABLE;
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic18_obj00_att06_get
* Description   : Object name       : Image Transfer
*                 Object index      : 00
*                 Class             : 18
*                 Attribute order   : 06
*                 Attribute name    : image_transfer_status
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {4, Firmware upgrade }; ; 
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 img_transfer_status_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_att06_get(distributor_params_t * p_params, img_transfer_status_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	enum img_transfer_status_t
	{
	    IMG_TRANS_NOT_INITIATED = 0,
	    IMG_TRANS_INITIATED,		
	    IMG_VERIFY_INITIATED,		
	    IMG_VERIFY_SUCCESSFUL,		
	    IMG_VERIFY_FAILED,			
	    IMG_ACTIVATE_INITIATED,		
	    IMG_ACTIVATE_SUCCESSFUL,	
	    IMG_ACTIVATE_FAILED,		
	};
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
	//img_transfer_status_t link_data = IMG_TRANS_NOT_INITIATED;//Please link you enum here, this is just default value.
	//*((img_transfer_status_t *)p_attribute_get) = link_data;
	/* Start user code here */
	if(R_DLMS_FWU_GetImgTransferStatus((uint8_t *)p_attribute_get) == RLT_SUCCESS)
	{
		/* Get successfully */
	}
	else
	{
		return VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED;											
	}
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}

/* Please update your array size following your setting change by asigning under variable */
/* For image_to_activate_info */
const uint16_t r_dlms_ic18_obj00_att07_array_length = 1;
/******************************************************************************
* Function Name : R_DLMS_USER_ic18_obj00_att07_get
* Description   : Object name       : Image Transfer
*                 Object index      : 00
*                 Class             : 18
*                 Attribute order   : 07
*                 Attribute name    : image_to_activate_info
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; {4, Firmware upgrade }; ; 
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 class18_image_to_activate_info_array_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_att07_get(distributor_params_t * p_params, class18_image_to_activate_info_array_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
	/*
	 * Not implemented(default), r_dlms_ic18_obj00_att07_array_length is assigned 0, response is array - 0 element(0100)
	 * Implemented, but r_dlms_ic18_obj00_att07_array_length is assigned 0, response is array - 0 element(0100)
	 */


	/*********************************************
	* This is array of image to activate info
	* class18_image_to_activate_info_t
	* {
	*    uint32_t* p_size;
	*    VariantString identification;
	*    VariantString signature;
	* }
	* VariantString
	* {
	*     uint8_t* p_content; 
	*     uint16_t length;
	*     uint16_t alloc_size;
	* }
	* class18_image_to_activate_info_array_t
	* {
	*       uint8_t* p_content;
	*       uint16_t length;
	* }
	* p_content: this is pointer of variable class18_image_to_activate_info_t[]
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


	/* Element 00 */
	//uint32_t size_link_element00 = 0;
	//uint8_t identification_content_element00_link[] = "None";
	//uint8_t signature_content_element00_link[] = { 0x00 };


	/* Set length for this array */
	//p_attribute_get->length = r_dlms_ic18_obj00_att07_array_length;

	/* Set value for element at 0 */
	//*((uint32_t *)p_attribute_get->p_content[0].p_size) = size_link_element00;
	//memcpy(p_attribute_get->p_content[0].identification.p_content, &identification_content_element00_link, 4);
	//p_attribute_get->p_content[0].identification.length = 4;
	//memcpy(p_attribute_get->p_content[0].signature.p_content, &signature_content_element00_link, 1);
	//p_attribute_get->p_content[0].signature.length = 1;



	/* Start user code here */
	uint8_t result;

	/* Current implementation is supporting one element */
	/* Get for image size */
    result = R_DLMS_FWU_GetImgSize(p_attribute_get->p_content[0].p_size);
	/* Get for image id */
    result |= R_DLMS_FWU_GetImgId(p_attribute_get->p_content[0].identification.p_content, &p_attribute_get->p_content[0].identification.length);
	/* Get for image signature */
    result |= R_DLMS_FWU_GetImgSignature(p_attribute_get->p_content[0].signature.p_content, &p_attribute_get->p_content[0].signature.length);

	/* Check all element is gotten successfully */
	if(result == RLT_SUCCESS)
	{
		/* Get successfully */
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
* Function Name : R_DLMS_USER_ic18_obj00_meth01_action
* Description   : Object name       : Image Transfer
*                 Object index      : 00
*                 Class             : 18
*                 Method order      : 01
*                 Method name       : image_transfer_initiate
*                 Association access: {2, Utility Setting}; {4, Firmware upgrade }; ;
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  class18_image_transfer_inititate_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_meth01_action(distributor_params_t * p_params, class18_image_transfer_inititate_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Initializes the Image transfer process.
	* class18_image_transfer_inititate_t
	* { 
	*     VariantString image_identifier;
	*     uint32_t* p_size;
	* }
	* VariantString
	* {
	*     uint8_t* p_content; 
	*     uint16_t length;
	*     uint16_t alloc_size;
	* }
	* Where:
	*  -image_identifier identifies the Image to be transferred;
	*  -image_size holds the ImageSize, expressed in octets.
	* After a successful invocation of the method the image_transfer_status attribute is set to(1)
	*  and the image_first_not_transferred_block_number is set to 0.Any subsequent invocation of
	*  the method resets the whole Image transfer process and all ImageBlocks need to be transferred again.
	* p_data_from_client::= class18_image_transfer_inititate_t
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

	if (R_DLMS_FWU_ImageTransferInitiate(
			p_data_from_client->image_identifier.p_content,
			p_data_from_client->image_identifier.length,
			p_data_from_client->p_size) == RLT_SUCCESS)
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
* Function Name : R_DLMS_USER_ic18_obj00_meth02_action
* Description   : Object name       : Image Transfer
*                 Object index      : 00
*                 Class             : 18
*                 Method order      : 02
*                 Method name       : image_block_transfer
*                 Association access: {2, Utility Setting}; {4, Firmware upgrade }; ;
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  class18_image_block_transfer_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_meth02_action(distributor_params_t * p_params, class18_image_block_transfer_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Transfers one block of the Image to the server.
	* class18_image_block_transfer_t
	* { 
	*     uint32_t* p_block_no;
	*     VariantString image_block_value;
	* }
	* VariantString
	* {
	*     uint8_t* p_content; 
	*     uint16_t length;
	*     uint16_t alloc_size;
	* }
	* After a successful invocation of the method the corresponding
	*  bit in the image_transferred_blocks_status attribute is set
	*  to 1 and the image_first_not_transferred_block_number attribute is updated.
	* p_data_from_client::= class18_image_block_transfer_t
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
	if (R_DLMS_FWU_ImageBlockTransfer(
        p_data_from_client->p_block_no,
        p_data_from_client->image_block_value.p_content,
        p_data_from_client->image_block_value.length
    ) == RLT_SUCCESS)	
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
* Function Name : R_DLMS_USER_ic18_obj00_meth03_action
* Description   : Object name       : Image Transfer
*                 Object index      : 00
*                 Class             : 18
*                 Method order      : 03
*                 Method name       : image_verify
*                 Association access: {2, Utility Setting}; {4, Firmware upgrade }; ;
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_meth03_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Verifies the integrity of the Image before activation.
	* p_data_from_client ::= integer(int8_t)(0) => ->NOT REQUIREMENT.
	* The result of the invocation of this method may be success, temporary_failure or other_reason.
	* If it is not success, then the result of the verification can be found by retrieving the value of the image_transfer_status attribute.
	* In the case of success, the image_to_activate_info attribute holds the information about the images to activate.
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
	if(R_DLMS_FWU_ImageVerify() == RLT_SUCCESS)
	{
							
	}
	else
	{
		return VAL_ACTION_RESULT_SUCCESS;										
	}
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_USER_ic18_obj00_meth04_action
* Description   : Object name       : Image Transfer
*                 Object index      : 00
*                 Class             : 18
*                 Method order      : 04
*                 Method name       : image_activate
*                 Association access: {2, Utility Setting}; {4, Firmware upgrade }; ;
*                 Group object		: FWU
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  int8_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_meth04_action(distributor_params_t * p_params, int8_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Activates the Image.
	* p_data_from_client ::= integer(int8_t)(0) => ->NOT REQUIREMENT.
	* If the Image transferred has not been verified before, then this is done as part of the Image activation.
	* The result of the invocation of this method may be success, temporary-failure or other-reason.
	* If it is not success, then the result of the activation can be learned by retrieving the value of the image_transfer_status attribute.
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
	if(R_DLMS_FWU_ImageActivate() == RLT_SUCCESS)
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


