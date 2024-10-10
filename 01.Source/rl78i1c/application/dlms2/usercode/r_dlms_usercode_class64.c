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
* File Name    : r_dlms_usercode_class64.c
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
#include "r_dlms_usercode_class64.h"
#include "r_dlms_security.h"

/* User application */
#include "r_dlms_app.h"
#include "r_dlms_security.h"
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

const dlms_securitykey_memmap_t * p_storage_map_keys[4] = 
{
	&backup_key_list[SECURITY_KEYLIST_ID_SHARED_GUK],//Unicast key = 0
	&backup_key_list[SECURITY_KEYLIST_ID_SHARED_GBK],//Broadcast key = 1
	&backup_key_list[SECURITY_KEYLIST_ID_SHARED_GUK],//Authentication key = 2, Authentication and unicast point to 1 key
	&backup_key_list[SECURITY_KEYLIST_ID_SHARED_MK]//Master key = 3
};

/* User code function */
/**********************************************************************************************************************
 * Function Name: global_key_transfer_action      
 * Description  : this is common function to execute transfer action
 * Arguments    : p_params - service parameters
 *                p_data_from_client - pointer of data is sent from client to write keys to meter
 * Return Value : uint8_t                     
 **********************************************************************************************************************/
 static uint8_t global_key_transfer_action(distributor_params_t * p_params,
 								        class64_key_unwrapped_transfer_data_array_t * p_data_from_client)
 {
	int  i;

	for(i = 0; i < p_data_from_client->length; i++)
	{
		if(p_data_from_client->p_content[i].key_id > 4)
		{
			/* Report that set keys fail */
			return VAL_ACTION_RESULT_READ_WRITE_DENIED;									
		}
		/* Write new key to storage */
		if(R_DLMS_Security_KeyBackup(
			p_data_from_client->p_content[i].key_unwrapped.p_content,
			p_data_from_client->p_content[i].key_unwrapped.length,
			(dlms_securitykey_memmap_t *)p_storage_map_keys[p_data_from_client->p_content[i].key_id]) == RLT_SUCCESS)
		{

		}
		else
		{
			/* Report that set keys fail */
			return VAL_ACTION_RESULT_READ_WRITE_DENIED;	
		}
		
	}
	/* If pass all, this action executed successfully */
	return VAL_DATA_ACCESS_RESULT_SUCCESS;		
 }
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

/******************************************************************************
* Function Name : R_DLMS_USER_ic64_init
* Interface     : void R_DLMS_USER_ic64_init(
*               :     void
*               : );
* Description   : THis function to init data for key
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_DLMS_USER_ic64_init(void)
{

}
/******************************************************************************
* Function Name : R_DLMS_Security_FetchAllNewKey
* Interface     : void R_DLMS_Security_FetchAllNewKey(
*               :     void
*               : );
* Description   : This function was call when new keys are activated
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_DLMS_Security_FetchAllNewKey(void)
{
	/* READ CAREFULLY UNDER COMMENT BEFORE CODING
	* This function will be called after responding that your new keys were activated successfully.
	* It mean that meter will send report that activation was successfull then this function will be call.
	* Please set up this fucntion that all new keys which was recieved from client that its will be applied in next transaction.
	* It mean next transaction will use these new keys for security context.
	* TODO:
	*     Step 1: read keys which was saved when action 02 was called.(usually from memory).
	*	  Step 2: assign read keys to security context follow as (update new keys to current flow keys)
	*	  CAUTION: length of key is 16 bytes (declared type: uint8_t[16])
	* This is generated following your configuration in Associations in GUI.
	* Security context 0(representation object: 0.0.43.0.2.255): declared global variable: g_assc0_security_context	
	* +---------------------------------+-------------------------------------------+
	* | Key type						| declared global variable					|
	* +---------------------------------+-------------------------------------------+
	* | global unicast encryption key	| g_assc_shared_global_unicast_key          |
	* | global broadcast encryption key | g_assc_shared_global_broadcast_key        |
	* | authentication key				| g_assc_shared_global_unicast_key          |
	* | master key (KEK)				| g_assc_shared_master_key                  |
	* +---------------------------------+-------------------------------------------+
	* Security context 1(representation object: 0.0.43.0.3.255): declared global variable: g_assc1_security_context	
	* +---------------------------------+-------------------------------------------+
	* | Key type						| declared global variable					|
	* +---------------------------------+-------------------------------------------+
	* | global unicast encryption key	| g_assc_shared_global_unicast_key          |
	* | global broadcast encryption key | g_assc_shared_global_broadcast_key        |
	* | authentication key				| g_assc_shared_global_unicast_key          |
	* | master key (KEK)				| g_assc_shared_master_key                  |
	* +---------------------------------+-------------------------------------------+
	* Security context 2(representation object: 0.0.43.0.4.255): declared global variable: g_assc2_security_context	
	* +---------------------------------+-------------------------------------------+
	* | Key type						| declared global variable					|
	* +---------------------------------+-------------------------------------------+
	* | global unicast encryption key	| g_assc_shared_global_unicast_key          |
	* | global broadcast encryption key | g_assc_shared_global_broadcast_key        |
	* | authentication key				| g_assc_shared_global_unicast_key          |
	* | master key (KEK)				| g_assc_shared_master_key                  |
	* +---------------------------------+-------------------------------------------+
	* Security context 3(representation object: 0.0.43.0.5.255): declared global variable: g_assc3_security_context	
	* +---------------------------------+-------------------------------------------+
	* | Key type						| declared global variable					|
	* +---------------------------------+-------------------------------------------+
	* | global unicast encryption key	| g_assc_shared_global_unicast_key          |
	* | global broadcast encryption key | g_assc_shared_global_broadcast_key        |
	* | authentication key				| g_assc_shared_global_unicast_key          |
	* | master key (KEK)				| g_assc_shared_master_key                  |
	* +---------------------------------+-------------------------------------------+
	* SUMMARY: from these tables, you need to fetch for under keys: 
	*    g_assc_shared_global_unicast_key
	*    g_assc_shared_global_broadcast_key
	*    g_assc_shared_master_key

	* Example: uint8_t[16] master_key_fetch;
	*		   master_key_fetch = ReadKey(3);
	*			<note: 3	    : key_id master key,
	*			       ReadKey	: function which is built in your application,
	*						      it have function is read key from memory where you save keys when action 02 is called>
	*			g_master_key = master_key_fetch;
	*			<note: g_master_key: name of declared global variable key, refer to above table>
	* This is example of one key, so please implement for all keys in SUMMARY
	*/
	uint8_t i;

	for (i = SECURITY_KEYLIST_ID_SHARED_MK; i <= SECURITY_KEYLIST_ID_IHD_AK; i++)
	{
		if (i < backup_key_list_size)
		{
			R_DLMS_Security_RestoreAt(i);
		}
	}
}

/******************************************************************************
* Function Name : R_DLMS_Security_Server_System_Title_Init
* Interface     : void R_DLMS_Security_Server_System_Title_Init(
*               :     void
*               : );
* Description   : This function to init data for server sytem tile
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_DLMS_Security_Server_System_Title_Init(void)
{
	/* READ UNDER COMMENT CAREFULLY BEFORE CODING
	* To be invoked:        R_DLMS_USER_Init()
	* Functional:           set data to server system title data for meter when init. Usually, this data combine ID flag(3 characters) and serial number(5 characters)
	*						ID flag: code which is registed with DLMS Association.
	*						Serial number: order number of product or code which manufacturer decided.
	* TODO: assign value which must contain 8 characters to server system title variable.
	* This server system title variable name is used on r_dlms_config.c
	* This is list of server title which is used in security contexts:
	* Security ID: 0, Obis code: 0.0.43.0.2.255:
	* 	Variable name: g_server_system_title
	* Security ID: 1, Obis code: 0.0.43.0.3.255:
	* 	Variable name: g_server_system_title
	* Security ID: 2, Obis code: 0.0.43.0.4.255:
	* 	Variable name: g_server_system_title
	* Security ID: 3, Obis code: 0.0.43.0.5.255:
	* 	Variable name: g_server_system_title

	* Example that your meter need read serial number from memory and set to server system title;
	*          uint8_t Id_flag[3] = MANUFACTURER_ID_FLAG;
	*		   uint8_t serial_number[5] = ReadSerialNumber();
	*                  <note MANUFACTURER_ID_FLAG  : contain string 3 element(ex:"REN");
	*                  <note ReadSerialNumber	   : function which is built in your application,that get serial number(ex:EEPROM or data flash).
	*                                                Ex: Value of read serial_number = "00001">
	*			memcpy(&g_server_system_title[0], &Id_flag[0], 3);
	*           memcpy(&g_server_system_title[3], &serial_number[0], 5);
	*			<note: g_server_system_title: name of declared global variable of server system title, refer to above table>
	*           <note: finish function, reusult g_server_system_title = "REN00001">
	*/

	/* Start user code here */
	/* This was established in R_DLMS_App_Init() in r_dlms_app.c */
	/* End user code here */
}



/******************************************************************************
* Description   : Object name		: Security Setup_Push
*				  Object index		: 00
*				  Class				: 64
*				  Attribute order	: 2
*				  Attribute name	: security policy
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programable
******************************************************************************/
/*
* This 'set' was implemented by GUI.
* Please refer to \dlms2\codegen\objects\r_dlms_objects64.c.
* Inside R_DLMS_OBJECTS_Class64Distributor(function)
*   -> else if(p_params->req_type == REQ_TYPE_SET)
*      -> switch (p_params->descriptor.attr.attribute_id) case 2:
*         -> switch(p_params->child_index(index object)) case 00:
*/

/******************************************************************************
* Description   : Object name		: Security Setup_Push
*				  Object index		: 00
*				  Class				: 64
*				  Method order		: 1
*				  Method name		: security activate
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programable
******************************************************************************/
/*
* This action was implemented by GUI.
* Please refer to \dlms2\codegen\objects\r_dlms_objects64.c.
* Inside R_DLMS_OBJECTS_Class64Distributor(function)
*   -> else if (p_params->req_type == REQ_TYPE_ACTION)
*      -> switch (p_params->descriptor.method.method_id) case 1:
*         -> switch(p_params->child_index(index object)) case 00:
*/ 

/******************************************************************************
* Function Name : R_DLMS_USER_ic64_obj00_meth02_action
* Description   : Object name       : Security Setup_Push
*                 Object index      : 00
*                 Class             : 64
*                 Method order      : 02
*                 Method name       : global_key_transfer
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Programable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  class64_key_unwrapped_transfer_data_array_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic64_obj00_meth02_action(distributor_params_t * p_params, class64_key_unwrapped_transfer_data_array_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Updates one or more global keys. The data parameter includes wrapped key data.
	* Key data include the key identifiers and the keys themselves.
	* class64_key_transfer_data_t::= structure
	* {
	*             key_id: enum: (0) global unicast encryption key,
	*                           (1) global broadcast encryption key,
	*                           (2) authentication key
	*                           (3) master key (KEK)
	*
	*             key_unwrapped: octet - string
	* }
	* The key wrap algorithm is as specified by the security suite.
	* In suites 0, 1, and 2 the AES key wrap algorithm is used.
	* The KEK is the master key.
	* If the unwrapping of the key(s) is successful,
	*  the result of the method invocation is success.
	* If the unwrapping of the key(s) is not successful,
	*  the method invocation fails and an appropriate reason for the failure shall be sent back.
	* The keys are not changed.
	* The new keys are activated immediately after result of the method invocation is sent back with result = success.
	* Notice that this rule equally applies to all keys, including the master key.
	* 
	* Meter code format
	* class64_key_unwrapped_transfer_data_array_t
	* {
	*     class64_key_unwrapped_transfer_data_t  * p_content;  / element content /
	*     uint16_t                                 length;      / Length of array/
	* }
	* class64_key_unwrapped_transfer_data_t
	* {
	*     uint8_t key_id;
	*     OctetString key_unwrapped;
	* }
	* p_data_from_client::= Array ::= class64_key_unwrapped_transfer_data_array_t
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
	global_key_transfer_action(p_params, p_data_from_client);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Description   : Object name		: Security Setup_FWU
*				  Object index		: 01
*				  Class				: 64
*				  Attribute order	: 2
*				  Attribute name	: security policy
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programable
******************************************************************************/
/*
* This 'set' was implemented by GUI.
* Please refer to \dlms2\codegen\objects\r_dlms_objects64.c.
* Inside R_DLMS_OBJECTS_Class64Distributor(function)
*   -> else if(p_params->req_type == REQ_TYPE_SET)
*      -> switch (p_params->descriptor.attr.attribute_id) case 2:
*         -> switch(p_params->child_index(index object)) case 01:
*/

/******************************************************************************
* Description   : Object name		: Security Setup_FWU
*				  Object index		: 01
*				  Class				: 64
*				  Method order		: 1
*				  Method name		: security activate
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programable
******************************************************************************/
/*
* This action was implemented by GUI.
* Please refer to \dlms2\codegen\objects\r_dlms_objects64.c.
* Inside R_DLMS_OBJECTS_Class64Distributor(function)
*   -> else if (p_params->req_type == REQ_TYPE_ACTION)
*      -> switch (p_params->descriptor.method.method_id) case 1:
*         -> switch(p_params->child_index(index object)) case 01:
*/ 

/******************************************************************************
* Function Name : R_DLMS_USER_ic64_obj01_meth02_action
* Description   : Object name       : Security Setup_FWU
*                 Object index      : 01
*                 Class             : 64
*                 Method order      : 02
*                 Method name       : global_key_transfer
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Programable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  class64_key_unwrapped_transfer_data_array_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic64_obj01_meth02_action(distributor_params_t * p_params, class64_key_unwrapped_transfer_data_array_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Updates one or more global keys. The data parameter includes wrapped key data.
	* Key data include the key identifiers and the keys themselves.
	* class64_key_transfer_data_t::= structure
	* {
	*             key_id: enum: (0) global unicast encryption key,
	*                           (1) global broadcast encryption key,
	*                           (2) authentication key
	*                           (3) master key (KEK)
	*
	*             key_unwrapped: octet - string
	* }
	* The key wrap algorithm is as specified by the security suite.
	* In suites 0, 1, and 2 the AES key wrap algorithm is used.
	* The KEK is the master key.
	* If the unwrapping of the key(s) is successful,
	*  the result of the method invocation is success.
	* If the unwrapping of the key(s) is not successful,
	*  the method invocation fails and an appropriate reason for the failure shall be sent back.
	* The keys are not changed.
	* The new keys are activated immediately after result of the method invocation is sent back with result = success.
	* Notice that this rule equally applies to all keys, including the master key.
	* 
	* Meter code format
	* class64_key_unwrapped_transfer_data_array_t
	* {
	*     class64_key_unwrapped_transfer_data_t  * p_content;  / element content /
	*     uint16_t                                 length;      / Length of array/
	* }
	* class64_key_unwrapped_transfer_data_t
	* {
	*     uint8_t key_id;
	*     OctetString key_unwrapped;
	* }
	* p_data_from_client::= Array ::= class64_key_unwrapped_transfer_data_array_t
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
	global_key_transfer_action(p_params, p_data_from_client);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Description   : Object name		: Security Setup_Meter Reader
*				  Object index		: 02
*				  Class				: 64
*				  Attribute order	: 2
*				  Attribute name	: security policy
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
******************************************************************************/
/*
* This 'set' was implemented by GUI.
* Please refer to \dlms2\codegen\objects\r_dlms_objects64.c.
* Inside R_DLMS_OBJECTS_Class64Distributor(function)
*   -> else if(p_params->req_type == REQ_TYPE_SET)
*      -> switch (p_params->descriptor.attr.attribute_id) case 2:
*         -> switch(p_params->child_index(index object)) case 02:
*/

/******************************************************************************
* Description   : Object name		: Security Setup_Meter Reader
*				  Object index		: 02
*				  Class				: 64
*				  Method order		: 1
*				  Method name		: security activate
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
******************************************************************************/
/*
* This action was implemented by GUI.
* Please refer to \dlms2\codegen\objects\r_dlms_objects64.c.
* Inside R_DLMS_OBJECTS_Class64Distributor(function)
*   -> else if (p_params->req_type == REQ_TYPE_ACTION)
*      -> switch (p_params->descriptor.method.method_id) case 1:
*         -> switch(p_params->child_index(index object)) case 02:
*/ 

/******************************************************************************
* Function Name : R_DLMS_USER_ic64_obj02_meth02_action
* Description   : Object name       : Security Setup_Meter Reader
*                 Object index      : 02
*                 Class             : 64
*                 Method order      : 02
*                 Method name       : global_key_transfer
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  class64_key_unwrapped_transfer_data_array_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic64_obj02_meth02_action(distributor_params_t * p_params, class64_key_unwrapped_transfer_data_array_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Updates one or more global keys. The data parameter includes wrapped key data.
	* Key data include the key identifiers and the keys themselves.
	* class64_key_transfer_data_t::= structure
	* {
	*             key_id: enum: (0) global unicast encryption key,
	*                           (1) global broadcast encryption key,
	*                           (2) authentication key
	*                           (3) master key (KEK)
	*
	*             key_unwrapped: octet - string
	* }
	* The key wrap algorithm is as specified by the security suite.
	* In suites 0, 1, and 2 the AES key wrap algorithm is used.
	* The KEK is the master key.
	* If the unwrapping of the key(s) is successful,
	*  the result of the method invocation is success.
	* If the unwrapping of the key(s) is not successful,
	*  the method invocation fails and an appropriate reason for the failure shall be sent back.
	* The keys are not changed.
	* The new keys are activated immediately after result of the method invocation is sent back with result = success.
	* Notice that this rule equally applies to all keys, including the master key.
	* 
	* Meter code format
	* class64_key_unwrapped_transfer_data_array_t
	* {
	*     class64_key_unwrapped_transfer_data_t  * p_content;  / element content /
	*     uint16_t                                 length;      / Length of array/
	* }
	* class64_key_unwrapped_transfer_data_t
	* {
	*     uint8_t key_id;
	*     OctetString key_unwrapped;
	* }
	* p_data_from_client::= Array ::= class64_key_unwrapped_transfer_data_array_t
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
	global_key_transfer_action(p_params, p_data_from_client);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

/******************************************************************************
* Description   : Object name		: Security Setup_Utility Setting
*				  Object index		: 03
*				  Class				: 64
*				  Attribute order	: 2
*				  Attribute name	: security policy
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
******************************************************************************/
/*
* This 'set' was implemented by GUI.
* Please refer to \dlms2\codegen\objects\r_dlms_objects64.c.
* Inside R_DLMS_OBJECTS_Class64Distributor(function)
*   -> else if(p_params->req_type == REQ_TYPE_SET)
*      -> switch (p_params->descriptor.attr.attribute_id) case 2:
*         -> switch(p_params->child_index(index object)) case 03:
*/

/******************************************************************************
* Description   : Object name		: Security Setup_Utility Setting
*				  Object index		: 03
*				  Class				: 64
*				  Method order		: 1
*				  Method name		: security activate
*                 Association access: {2, Utility Setting}; ; 
*                 Group object		: Programmable
******************************************************************************/
/*
* This action was implemented by GUI.
* Please refer to \dlms2\codegen\objects\r_dlms_objects64.c.
* Inside R_DLMS_OBJECTS_Class64Distributor(function)
*   -> else if (p_params->req_type == REQ_TYPE_ACTION)
*      -> switch (p_params->descriptor.method.method_id) case 1:
*         -> switch(p_params->child_index(index object)) case 03:
*/ 

/******************************************************************************
* Function Name : R_DLMS_USER_ic64_obj03_meth02_action
* Description   : Object name       : Security Setup_Utility Setting
*                 Object index      : 03
*                 Class             : 64
*                 Method order      : 02
*                 Method name       : global_key_transfer
*                 Association access: {2, Utility Setting}; ;
*                 Group object		: Programmable
* Arguments     : distributor_params_t  * p_params -
*                   Contains all INPUT and OUTPUT of client and system.
*				  class64_key_unwrapped_transfer_data_array_t * p_data_from_client - INPUT
*					Contains input data from client.					
* Return Value  : uint8_t - result of get attribute
******************************************************************************/
uint8_t R_DLMS_USER_ic64_obj03_meth02_action(distributor_params_t * p_params, class64_key_unwrapped_transfer_data_array_t * p_data_from_client)
{
	//uint8_t result = VAL_ACTION_RESULT_OTHER_REASON;
	/*************************************************************************
	* Updates one or more global keys. The data parameter includes wrapped key data.
	* Key data include the key identifiers and the keys themselves.
	* class64_key_transfer_data_t::= structure
	* {
	*             key_id: enum: (0) global unicast encryption key,
	*                           (1) global broadcast encryption key,
	*                           (2) authentication key
	*                           (3) master key (KEK)
	*
	*             key_unwrapped: octet - string
	* }
	* The key wrap algorithm is as specified by the security suite.
	* In suites 0, 1, and 2 the AES key wrap algorithm is used.
	* The KEK is the master key.
	* If the unwrapping of the key(s) is successful,
	*  the result of the method invocation is success.
	* If the unwrapping of the key(s) is not successful,
	*  the method invocation fails and an appropriate reason for the failure shall be sent back.
	* The keys are not changed.
	* The new keys are activated immediately after result of the method invocation is sent back with result = success.
	* Notice that this rule equally applies to all keys, including the master key.
	* 
	* Meter code format
	* class64_key_unwrapped_transfer_data_array_t
	* {
	*     class64_key_unwrapped_transfer_data_t  * p_content;  / element content /
	*     uint16_t                                 length;      / Length of array/
	* }
	* class64_key_unwrapped_transfer_data_t
	* {
	*     uint8_t key_id;
	*     OctetString key_unwrapped;
	* }
	* p_data_from_client::= Array ::= class64_key_unwrapped_transfer_data_array_t
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
	global_key_transfer_action(p_params, p_data_from_client);
	/* End user code here */
	/* Return result of this, please check again result value */
	return VAL_ACTION_RESULT_SUCCESS;
}

