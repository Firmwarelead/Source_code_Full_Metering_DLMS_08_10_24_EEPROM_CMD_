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
* File Name    : r_dlms_objects.c
* Version OCG  : 1.0.7 - Arp 20 2023 - d0ac0fea860855c7f58887c28dbc077146b8333f
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 24/04/2023 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_config.h"
#include "r_dlms_objects.h"
#include "r_dlms_user.h"
#include "r_dlms_usercode_class64.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
AsscConnectionSession * gp_dlms_CurrentSection = NULL;
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
uint8_t g_dlms_security_is_key_tranferred = FALSE;
/******************************************************************************
Private global variables and functions
******************************************************************************/

/* Attribute access right pattern 1 : attr 1 read only, other full access (rw) */
/*
* Default access right
*/

/* Asign none all value */
const uint8_t g_objects_access_right_attr_none_all[24] = {
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr1  */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr2  */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr3  */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr4  */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr5  */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr6  */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr7  */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr8  */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr9  */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr10 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr11 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr12 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr13 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr14 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr15 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr16 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr17 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr18 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr19 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr20 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr21 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr22 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr23 */
	OBIS_AR_ATTR_NO_ACCESS,		/* Attr24 */
};
const uint8_t g_objects_access_right_method_none_all[16] = {
	OBIS_AR_METHOD_NO_ACCESS,		/* Method1  */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method2  */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method3  */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method4  */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method5  */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method6  */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method7  */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method8  */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method9  */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method10 */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method11 */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method12 */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method13 */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method14 */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method15 */
	OBIS_AR_METHOD_NO_ACCESS,		/* Method16 */
};

#define AR_NONE_ALL	 			{									\
	{ (uint8_t *)g_objects_access_right_attr_none_all, sizeof(g_objects_access_right_attr_none_all) },		\
	{ (uint8_t *)g_objects_access_right_method_none_all, sizeof(g_objects_access_right_method_none_all) },		\
}
const access_right_t			g_classes_access_right_none = AR_NONE_ALL;

/* Define access right for method */
/* Define access right for method group 00 */
const uint8_t g_objects_access_right_method_00[] = {
	OBIS_AR_METHOD_NO_ACCESS,                        	/* Method00  */
	OBIS_AR_METHOD_NO_ACCESS,                        	/* Method01  */
	OBIS_AR_METHOD_NO_ACCESS,                        	/* Method02  */
	OBIS_AR_METHOD_NO_ACCESS,                        	/* Method03  */
	OBIS_AR_METHOD_NO_ACCESS,                        	/* Method04  */
	OBIS_AR_METHOD_NO_ACCESS,                        	/* Method05  */
};



/* Define access right for method group 01 */
const uint8_t g_objects_access_right_method_01[] = {
	OBIS_AR_METHOD_ACCESS,                           	/* Method00  */
	OBIS_AR_METHOD_ACCESS,                           	/* Method01  */
	OBIS_AR_METHOD_NO_ACCESS,                        	/* Method02  */
	OBIS_AR_METHOD_NO_ACCESS,                        	/* Method03  */
};



/* Define access right for method group 02 */
const uint8_t g_objects_access_right_method_02[] = {
	OBIS_AR_METHOD_ACCESS,                           	/* Method00  */
	OBIS_AR_METHOD_ACCESS,                           	/* Method01  */
	OBIS_AR_METHOD_ACCESS,                           	/* Method02  */
	OBIS_AR_METHOD_ACCESS,                           	/* Method03  */
};





/* Define access right for attribute */
/* Define access right for 00 Attribute */
const uint8_t g_objects_access_right_attr_00[] = {
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr00  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr01  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr02  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr03  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr04  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr05  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr06  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr07  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr08  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr09  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr10  */
};



/* Define access right for 01 Attribute */
const uint8_t g_objects_access_right_attr_01[] = {
	OBIS_AR_ATTR_READ,                               	/* Attr00  */
	OBIS_AR_ATTR_READ,                               	/* Attr01  */
	OBIS_AR_ATTR_READ,                               	/* Attr02  */
	OBIS_AR_ATTR_READ,                               	/* Attr03  */
	OBIS_AR_ATTR_READ,                               	/* Attr04  */
	OBIS_AR_ATTR_READ,                               	/* Attr05  */
	OBIS_AR_ATTR_READ,                               	/* Attr06  */
	OBIS_AR_ATTR_READ,                               	/* Attr07  */
	OBIS_AR_ATTR_READ,                               	/* Attr08  */
	OBIS_AR_ATTR_READ,                               	/* Attr09  */
	OBIS_AR_ATTR_READ,                               	/* Attr10  */
};



/* Define access right for 02 Attribute */
const uint8_t g_objects_access_right_attr_02[] = {
	OBIS_AR_ATTR_READ,                               	/* Attr00  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr01  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr02  */
	OBIS_AR_ATTR_READ,                               	/* Attr03  */
	OBIS_AR_ATTR_READ,                               	/* Attr04  */
	OBIS_AR_ATTR_READ,                               	/* Attr05  */
	OBIS_AR_ATTR_READ,                               	/* Attr06  */
	OBIS_AR_ATTR_READ,                               	/* Attr07  */
	OBIS_AR_ATTR_READ,                               	/* Attr08  */
};



/* Define access right for 03 Attribute */
const uint8_t g_objects_access_right_attr_03[] = {
	OBIS_AR_ATTR_READ,                               	/* Attr00  */
	OBIS_AR_ATTR_READ,                               	/* Attr01  */
	OBIS_AR_ATTR_READ,                               	/* Attr02  */
	OBIS_AR_ATTR_READ,                               	/* Attr03  */
	OBIS_AR_ATTR_READ,                               	/* Attr04  */
	OBIS_AR_ATTR_READ,                               	/* Attr05  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr06  */
	OBIS_AR_ATTR_READ,                               	/* Attr07  */
	OBIS_AR_ATTR_READ,                               	/* Attr08  */
};



/* Define access right for 04 Attribute */
const uint8_t g_objects_access_right_attr_04[] = {
	OBIS_AR_ATTR_READ,                               	/* Attr00  */
	OBIS_AR_ATTR_READ,                               	/* Attr01  */
	OBIS_AR_ATTR_READ,                               	/* Attr02  */
	OBIS_AR_ATTR_READ,                               	/* Attr03  */
	OBIS_AR_ATTR_READ,                               	/* Attr04  */
	OBIS_AR_ATTR_READ,                               	/* Attr05  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr06  */
	OBIS_AR_ATTR_READ,                               	/* Attr07  */
	OBIS_AR_ATTR_NO_ACCESS,                          	/* Attr08  */
};



/* Define access right for 05 Attribute */
const uint8_t g_objects_access_right_attr_05[] = {
	OBIS_AR_ATTR_READ,                               	/* Attr00  */
	OBIS_AR_ATTR_READ,                               	/* Attr01  */
	OBIS_AR_ATTR_READ,                               	/* Attr02  */
	OBIS_AR_ATTR_READ,                               	/* Attr03  */
	OBIS_AR_ATTR_READ,                               	/* Attr04  */
	OBIS_AR_ATTR_READ,                               	/* Attr05  */
	OBIS_AR_ATTR_WRITE,                              	/* Attr06  */
	OBIS_AR_ATTR_READ,                               	/* Attr07  */
	OBIS_AR_ATTR_READ,                               	/* Attr08  */
};



/* Define access right for 06 Attribute */
const uint8_t g_objects_access_right_attr_06[] = {
	OBIS_AR_ATTR_READ,                               	/* Attr00  */
	OBIS_AR_ATTR_READ,                               	/* Attr01  */
	OBIS_AR_ATTR_READ,                               	/* Attr02  */
	OBIS_AR_ATTR_READ,                               	/* Attr03  */
	OBIS_AR_ATTR_READ,                               	/* Attr04  */
	OBIS_AR_ATTR_READ,                               	/* Attr05  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr06  */
	OBIS_AR_ATTR_READ,                               	/* Attr07  */
	OBIS_AR_ATTR_READ,                               	/* Attr08  */
};



/* Define access right for 07 Attribute */
const uint8_t g_objects_access_right_attr_07[] = {
	OBIS_AR_ATTR_READ,                               	/* Attr00  */
	OBIS_AR_ATTR_READ,                               	/* Attr01  */
	OBIS_AR_ATTR_READ,                               	/* Attr02  */
	OBIS_AR_ATTR_READ,                               	/* Attr03  */
	OBIS_AR_ATTR_READ,                               	/* Attr04  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr05  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr06  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr07  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr08  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr09  */
};



/* Define access right for 08 Attribute */
const uint8_t g_objects_access_right_attr_08[] = {
	OBIS_AR_ATTR_READ,                               	/* Attr00  */
	OBIS_AR_ATTR_READ,                               	/* Attr01  */
	OBIS_AR_ATTR_READ,                               	/* Attr02  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr03  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr04  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr05  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr06  */
	OBIS_AR_ATTR_READ,                               	/* Attr07  */
	OBIS_AR_ATTR_READ,                               	/* Attr08  */
	OBIS_AR_ATTR_READ,                               	/* Attr09  */
	OBIS_AR_ATTR_READ,                               	/* Attr10  */
};



/* Define access right for 09 Attribute */
const uint8_t g_objects_access_right_attr_09[] = {
	OBIS_AR_ATTR_READ,                               	/* Attr00  */
	OBIS_AR_ATTR_READ,                               	/* Attr01  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr02  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr03  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr04  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr05  */
	OBIS_AR_ATTR_READ | OBIS_AR_ATTR_WRITE,          	/* Attr06  */
};





/* Define access right group */
/* Access right pattern for AR_00 */
#define AR_00 {\
	{ (uint8_t *)g_objects_access_right_attr_00, sizeof(g_objects_access_right_attr_00) },\
	{ (uint8_t *)g_objects_access_right_method_00, sizeof(g_objects_access_right_method_00) },\
}
/* Access right pattern for AR_01 */
#define AR_01 {\
	{ (uint8_t *)g_objects_access_right_attr_01, sizeof(g_objects_access_right_attr_01) },\
	{ (uint8_t *)g_objects_access_right_method_00, sizeof(g_objects_access_right_method_00) },\
}
/* Access right pattern for AR_02 */
#define AR_02 {\
	{ (uint8_t *)g_objects_access_right_attr_02, sizeof(g_objects_access_right_attr_02) },\
	{ (uint8_t *)g_objects_access_right_method_00, sizeof(g_objects_access_right_method_00) },\
}
/* Access right pattern for AR_03 */
#define AR_03 {\
	{ (uint8_t *)g_objects_access_right_attr_01, sizeof(g_objects_access_right_attr_01) },\
	{ (uint8_t *)g_objects_access_right_method_01, sizeof(g_objects_access_right_method_01) },\
}
/* Access right pattern for AR_04 */
#define AR_04 {\
	{ (uint8_t *)g_objects_access_right_attr_03, sizeof(g_objects_access_right_attr_03) },\
	{ (uint8_t *)g_objects_access_right_method_00, sizeof(g_objects_access_right_method_00) },\
}
/* Access right pattern for AR_05 */
#define AR_05 {\
	{ (uint8_t *)g_objects_access_right_attr_04, sizeof(g_objects_access_right_attr_04) },\
	{ (uint8_t *)g_objects_access_right_method_00, sizeof(g_objects_access_right_method_00) },\
}
/* Access right pattern for AR_06 */
#define AR_06 {\
	{ (uint8_t *)g_objects_access_right_attr_05, sizeof(g_objects_access_right_attr_05) },\
	{ (uint8_t *)g_objects_access_right_method_01, sizeof(g_objects_access_right_method_01) },\
}
/* Access right pattern for AR_07 */
#define AR_07 {\
	{ (uint8_t *)g_objects_access_right_attr_05, sizeof(g_objects_access_right_attr_05) },\
	{ (uint8_t *)g_objects_access_right_method_00, sizeof(g_objects_access_right_method_00) },\
}
/* Access right pattern for AR_08 */
#define AR_08 {\
	{ (uint8_t *)g_objects_access_right_attr_06, sizeof(g_objects_access_right_attr_06) },\
	{ (uint8_t *)g_objects_access_right_method_01, sizeof(g_objects_access_right_method_01) },\
}
/* Access right pattern for AR_09 */
#define AR_09 {\
	{ (uint8_t *)g_objects_access_right_attr_01, sizeof(g_objects_access_right_attr_01) },\
	{ (uint8_t *)g_objects_access_right_method_02, sizeof(g_objects_access_right_method_02) },\
}
/* Access right pattern for AR_10 */
#define AR_10 {\
	{ (uint8_t *)g_objects_access_right_attr_07, sizeof(g_objects_access_right_attr_07) },\
	{ (uint8_t *)g_objects_access_right_method_01, sizeof(g_objects_access_right_method_01) },\
}
/* Access right pattern for AR_11 */
#define AR_11 {\
	{ (uint8_t *)g_objects_access_right_attr_08, sizeof(g_objects_access_right_attr_08) },\
	{ (uint8_t *)g_objects_access_right_method_00, sizeof(g_objects_access_right_method_00) },\
}
/* Access right pattern for AR_12 */
#define AR_12 {\
	{ (uint8_t *)g_objects_access_right_attr_09, sizeof(g_objects_access_right_attr_09) },\
	{ (uint8_t *)g_objects_access_right_method_01, sizeof(g_objects_access_right_method_01) },\
}
/* Access right pattern for AR_13 */
#define AR_13 {\
	{ (uint8_t *)g_objects_access_right_attr_08, sizeof(g_objects_access_right_attr_08) },\
	{ (uint8_t *)g_objects_access_right_method_01, sizeof(g_objects_access_right_method_01) },\
}


/* Define access right table */
const access_right_t g_objects_access_right_table[][OBIS_NUMBER_OF_ASSOCIATION] =
{
 /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
 /*RowID  |   Access Right Definition                                                                                                                                               */
 /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
 /*                           Public Client                 Meter Reader                  Utility Setting               Push                          Firmware upgrade              */
 /* 00 */  {                     AR_00,                         AR_01,                         AR_01,                         AR_00,                         AR_00,                          },
 /* 01 */  {                     AR_00,                         AR_01,                         AR_01,                         AR_00,                         AR_01,                          },
 /* 02 */  {                     AR_01,                         AR_01,                         AR_01,                         AR_01,                         AR_01,                          },
 /* 03 */  {                     AR_01,                         AR_01,                         AR_01,                         AR_00,                         AR_01,                          },
 /* 04 */  {                     AR_00,                         AR_01,                         AR_02,                         AR_00,                         AR_00,                          },
 /* 05 */  {                     AR_01,                         AR_01,                         AR_01,                         AR_01,                         AR_00,                          },
 /* 06 */  {                     AR_00,                         AR_01,                         AR_03,                         AR_00,                         AR_00,                          },
 /* 07 */  {                     AR_01,                         AR_01,                         AR_02,                         AR_01,                         AR_01,                          },
 /* 08 */  {                     AR_00,                         AR_01,                         AR_03,                         AR_00,                         AR_01,                          },
 /* 09 */  {                     AR_04,                         AR_05,                         AR_05,                         AR_00,                         AR_00,                          },
 /* 10 */  {                     AR_00,                         AR_04,                         AR_06,                         AR_00,                         AR_03,                          },
 /* 11 */  {                     AR_00,                         AR_01,                         AR_07,                         AR_00,                         AR_00,                          },
 /* 12 */  {                     AR_00,                         AR_05,                         AR_08,                         AR_00,                         AR_00,                          },
 /* 13 */  {                     AR_00,                         AR_04,                         AR_04,                         AR_01,                         AR_00,                          },
 /* 14 */  {                     AR_00,                         AR_01,                         AR_09,                         AR_00,                         AR_09,                          },
 /* 15 */  {                     AR_00,                         AR_01,                         AR_10,                         AR_00,                         AR_00,                          },
 /* 16 */  {                     AR_00,                         AR_01,                         AR_11,                         AR_00,                         AR_00,                          },
 /* 17 */  {                     AR_00,                         AR_01,                         AR_11,                         AR_00,                         AR_11,                          },
 /* 18 */  {                     AR_00,                         AR_01,                         AR_12,                         AR_01,                         AR_00,                          },
 /* 19 */  {                     AR_00,                         AR_01,                         AR_13,                         AR_00,                         AR_00,                          },
};
/******************************************************************************
* Function Name : R_DLMS_OBJECTS_Init
* Interface     : void R_DLMS_OBJECTS_Init()
* Description   : Initialize for Objects component & all derived objects
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_Init(void)
{
	g_dlms_security_is_key_tranferred = FALSE;
	R_DLMS_USER_Init();
}

/******************************************************************************
* Function Name : R_DLMS_OBJECTS_PollingProcessing
* Interface     : void R_DLMS_OBJECTS_PollingProcessing()
* Description   : Polling processing for Objects component & all derived objects
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_PollingProcessing(void)
{
	R_DLMS_USER_PollingProcessing();
}

/******************************************************************************
* Function Name : R_DLMS_OBJECTS_AsscOpened
* Interface     : void R_DLMS_OBJECTS_AsscOpened(AsscConnectionSession *p_assc_session)
* Description   :
* Arguments     : AsscConnectionSession * p_assc_session:
* Function Calls:
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_AsscOpened(AsscConnectionSession *p_assc_session)
{
	R_DLMS_USER_AsscOpened(p_assc_session);
}

/******************************************************************************
* Function Name : R_DLMS_OBJECTS_AsscClosing
* Interface     : void R_DLMS_OBJECTS_AsscClosing(AsscConnectionSession *p_assc_session)
* Description   :
* Arguments     : AsscConnectionSession * p_assc_session:
* Function Calls:
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_AsscClosing(AsscConnectionSession *p_assc_session)
{
	R_DLMS_USER_AsscClosing(p_assc_session);
}


/******************************************************************************
* Function Name : R_DLMS_OBJECTS_CosemSetIndication
* Interface     : void R_DLMS_OBJECTS_CosemSetIndication(MgmtChannel mgmt_channel, CosemSetIndication_Params *p_params)
* Description   : Indication of SET after meter response to Client
* Arguments     : MgmtChannel mgmt_channel             : Mgmt channel that SET service is called
*               : CosemSetIndication_Params * p_params : Distribution params of SET service
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_CosemSetIndication(MgmtChannel mgmt_channel, CosemSetIndication_Params *p_params)
{
	R_DLMS_OBJECTS_Class64CosemSetIndication(mgmt_channel, p_params);
}

/******************************************************************************
* Function Name : R_DLMS_OBJECTS_CosemActionIndication
* Interface     : void R_DLMS_OBJECTS_CosemActionIndication(MgmtChannel mgmt_channel, CosemActionIndication_Params *p_params)
* Description   : Indication of action after meter response to Client
* Arguments     : MgmtChannel mgmt_channel               : Mgmt channel that action is called
*               : CosemActionIndication_Params * p_params: Distribution params of action
* Return Value  : None
******************************************************************************/
void R_DLMS_OBJECTS_CosemActionIndication(MgmtChannel mgmt_channel, CosemActionIndication_Params *p_params)
{
	R_DLMS_OBJECTS_Class64CosemActionIndication(mgmt_channel, p_params);
}
