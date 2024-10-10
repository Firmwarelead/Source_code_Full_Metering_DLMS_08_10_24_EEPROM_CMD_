/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_storage.h
* Version      : 1.00
* Description  :
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 08.01.2018 New created
******************************************************************************/

#ifndef _R_DLMS_APPS_H
#define _R_DLMS_APPS_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "typedef.h"
#include "r_dlms_classes.h"
#include "r_dlms_storage.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/***************************************************************
*    DLMS Application configures
****************************************************************/

/* Below macro to enable/disable Renesas DLMS Applications */

#define R_DLMS_APP_NAMEPLATE_ENABLE						(TRUE)
/* APPLICATIONS --------------------------------------- ENABLE */
/* Push */

/* Historic data */

/* Block load survey */
#define R_DLMS_APPS_LOADSURVEY_BLOCKLOAD_ENABLE			(TRUE)
#define R_DLMS_APPS_LOADSURVEY_DAILY_ENABLE				(TRUE)

/* Billing */
#define R_DLMS_APPS_LOADSURVEY_BILLING_ENABLE			(TRUE)

/* Communication profiles */

/* Event checking */
#define R_DLMS_APPS_EVENT_POLLING_ENABLE				(TRUE)

/* CONNECT/DISCONNECT CONTROL */
#define R_DLMS_APPS_LOADCONTROL_ENABLE					(TRUE)
#define R_DLMS_APPS_LIMITTER_ENABLE						(TRUE)

/* Scheduler */
#define R_DLMS_APPS_SCHEDULER_ENABLE					(TRUE)

/* Security */
#define R_DLMS_APPS_SECURITY_STORAGE_ENABLE				(TRUE)


#define R_DLMS_APPS_MALLOC_USING                        (FALSE)
/************************************************************/

#define APP_ERROR_RETURN(check)			{ if ( (check) != (RLT_SUCCESS)) { return (RLT_ERR);} }

#define NOT_SPECIFIED (0xFF)
#define DATE_TIME_NOT_SPECIFIED				{					\
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												NOT_SPECIFIED,  \
												0x80, 			\
												0x00, 			\
												NOT_SPECIFIED	\
											}

/******************************************************************************
Typedef definitions
******************************************************************************/
/*
 * RETURN ERROR CODE
 */
typedef enum tag_dlms_app_return_error_code_t
{
	RLT_SUCCESS = 0					,
	RLT_ERR							,
	RLT_ERR_STORAGE_ERROR			,
	RLT_ERR_ACCESS_FAIL				,
	RLT_ERR_READ_FAIL				,
	RLT_ERR_WRITE_FAIL				,
	RLT_ERR_NULL					,
	RLT_ERR_OBJECT_NOT_FOUND		,
	RLT_ERR_EMPTY					,
	RLT_ERR_INVALID_PARAMETER		,
	RLT_ERR_INVALID_FUNC			,
	RLT_ERR_INVALID_DATA			,
	RLT_ERR_NOT_ENOUGH_MEM			,
	RLT_ERR_CRC						,
	RLT_ERR_OPERATION_IN_PROGRESS	,
	RLT_ERR_OPERATION_CORRUPTED		,
	RLT_ERR_DATA_CORRUPTED			,
	RLT_ERR_INIT					,
	RLT_ERR_NOT_FOUND				,
	RLT_ERR_STORAGE_NOT_FORMATTED	,
	RLT_ERR_STORAGE_FAULT			,
	RLT_ERR_STORAGE_WEAK_PASSWORD	,
	RLT_OTHER = 255					,
} dlms_app_return_error_code_t;


typedef struct tag_st_app_smo_t
{
	uint8_t len;
	uint8_t buffer[128];
} st_app_smo_t;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

uint8_t R_DLMS_Backup_SMO1(st_app_smo_t *p_message);
uint8_t R_DLMS_Backup_SMO2(st_app_smo_t *p_message);
st_app_smo_t R_DLMS_Restore_SMO1(void);
st_app_smo_t R_DLMS_Restore_SMO2(void);

void R_DLMS_App_Format(void);
void R_DLMS_App_IntervalCounter (void);

void R_DLMS_App_Init (void);
void R_DLMS_App_PollingProcessing (void);

#endif /* _R_DLMS_APPS_H */
