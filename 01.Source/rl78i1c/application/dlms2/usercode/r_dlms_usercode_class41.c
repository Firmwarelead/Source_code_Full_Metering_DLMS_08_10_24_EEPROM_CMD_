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
* File Name    : r_dlms_usercode_class41.c
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
#include "r_dlms_usercode_class41.h"


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
* Object name:      TCP Setup 0
* Object number:    00
* Object obis code: 0.0.25.0.0.255
***********************************************************************************************************/

/*******************************************************************************
* Class ID: 41
* Variable name: g_dlms_ic41_obj00_att02_tcp_udp_port
* Object name: TCP Setup 0
* Attribute order: 02
* Attribute name: tcp_udp_port
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Communication
*******************************************************************************/
/*********************************************
Data type:uint16_t(long-unsigned)
*********************************************/


/* Declare for variable of tcp_udp_port (class - 41, atrribute - 02)*/
const uint16_t g_dlms_ic41_obj00_att02_tcp_udp_port  = 4059;


/******************************************************************************
* Description   : Object name		: TCP Setup 0
*				  Object index		: 00
*				  Class				: 41
*				  Attribute order	: 3
*				  Attribute name	: IP reference
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Communication
******************************************************************************/
/*
* This value is gotten from TCP-UDP configuration inside r_dlm_config.c
*/


/*******************************************************************************
* Class ID: 41
* Variable name: g_dlms_ic41_obj00_att04_MSS
* Object name: TCP Setup 0
* Attribute order: 04
* Attribute name: MSS
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Communication
*******************************************************************************/
/*********************************************
Data type:uint16_t(long-unsigned)
*********************************************/


/* Declare for variable of MSS (class - 41, atrribute - 04)*/
const uint16_t g_dlms_ic41_obj00_att04_MSS  = 576;

#if defined(CLASS41_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE) && (CLASS41_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE == TRUE)
/* INFO: above macro is off, this attribute "GET" by above const variable, if above macro is enable, this attribute use get by user function */
/******************************************************************************
* Function Name : R_DLMS_USER_ic41_obj00_att04_get
* Description   : Object name       : TCP Setup 0
*                 Object index      : 00
*                 Class             : 41
*                 Attribute order   : 04
*                 Attribute name    : MSS
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Communication
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_get - OUTPUT
*                   Contains output data to send to client.
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic41_obj00_att04_get(distributor_params_t * p_params, uint16_t * p_attribute_get)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;

	/*********************************************
	Data type:uint16_t(long-unsigned)
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
	uint16_t link_data = 576;
	/* Set value */
	*((uint16_t *)p_attribute_get) = link_data;

	/* Start user code here */
	/* End user code here */

	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*
 * !!!IMPORTANT INFO: access right for "SET" of this attribute is off, If this code enable, please check and change access right.
 * !!!IMPORTANT INFO: And, this attribute "GET" by constant variable, please enable get user code function macro: CLASS41_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE too.
 */
#if defined(CLASS41_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE) && (CLASS41_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE == TRUE)
/******************************************************************************
* Function Name : R_DLMS_USER_ic41_obj00_att04_set
* Description   : Object name       : TCP Setup 0
*                 Object index      : 00
*                 Class             : 41
*                 Attribute order   : 04
*                 Attribute name    : MSS
*                 Association access: ; 
*                 Group object		: Communication
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*                 uint16_t * p_attribute_set - INTPUT
*                   Contains intput data to save setting from client to meter.
* Return Value  : uint8_t - result of set attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic41_obj00_att04_set(distributor_params_t * p_params, uint16_t * p_attribute_set)
{
	//uint8_t result = VAL_DATA_ACCESS_RESULT_OTHER_REASON;
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
	/*********************************************
	Data type:uint16_t(long-unsigned)
	*********************************************/


	
	/* Start user code here */
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;
}
#endif

/*******************************************************************************
* Class ID: 41
* Variable name: g_dlms_ic41_obj00_att05_nb_of_sim_conn
* Object name: TCP Setup 0
* Attribute order: 05
* Attribute name: nb_of_sim_conn
* Association access: {1, Meter Reader}; {2, Utility Setting}; ;
* Group object		: Communication
*******************************************************************************/
/*********************************************
Data type:uint8_t(unsigned)
*********************************************/


/* Declare for variable of nb_of_sim_conn (class - 41, atrribute - 05)*/
const uint8_t g_dlms_ic41_obj00_att05_nb_of_sim_conn  = 1;


/******************************************************************************
* Description   : Object name		: TCP Setup 0
*				  Object index		: 00
*				  Class				: 41
*				  Attribute order	: 6
*				  Attribute name	: inactivity time out
*                 Association access: {1, Meter Reader}; {2, Utility Setting}; ; 
*                 Group object		: Communication
******************************************************************************/
/*
* This value is gotten from TCP-UDP configuration inside r_dlm_config.c
*/




