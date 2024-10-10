/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_abnormal_operating.h
* Version      : v1.0
* Description  : 
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 2021.03.29 New creation
***********************************************************************************************************************/

#ifndef _R_ABNORMAL_OPERATING_H
#define _R_ABNORMAL_OPERATING_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"

#include "typedef.h"
#include "compiler.h"

#include "inst_read.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

typedef struct tag_meter_wakeup_data_t
{
    int8_t                  status;         /* 0: Normal, (-1) :  */
    s_capture_em_data_t     snapshot_old;
    s_capture_em_data_t     snapshot_new;
    rtc_counter_value_t     rtc_old;
    rtc_counter_value_t     rtc_new;
} meter_wakeup_data_t;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
extern meter_wakeup_data_t g_meter_wakekup_data;

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
void R_HANDLER_BackupBeforeApplyNewRTCValue(const rtc_counter_value_t *p_rtc_value);
void R_HANDLER_AfterApplyNewRTCValue(void);

void R_HANDLER_BeforeMeterSleep(void);
void R_HANDLER_MeterWakeup(void);

uint8_t R_HANDLER_GetBackupData(s_capture_em_data_t *p_data);

#endif /* _R_ABNORMAL_OPERATING_H */