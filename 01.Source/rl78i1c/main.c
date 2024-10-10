/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : main.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CubeSuite Version 1.5d
* OS           : None
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Main 
* Operation    : Main processing
* Limitations  : None
******************************************************************************
* History : DD.MM.YYYY Version Description
***********************************************************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"           /* CG Macro Driver */
#include "r_cg_wdt.h"                   /* CG WDT Driver */

/* Wrapper/User */

/* MW/Core */
#include "em_core.h"                    /* EM Core APIs */

/* Application */
#include "startup.h"                    /* Startup Header File */
#include "platform.h"                   /* Default Platform Information Header */
#include "key.h"                        /* Key Interface */
#include "config_storage.h"             /* Configuration Storage Header File */
#include "inst_read.h"
#include "event.h"                      /* Event Header File */
#include "em_display.h"                 /* LCD Display Pannel */
#ifdef _DLMS
#include "r_dlms_main.h"				/* DLMS 2.0 */
#endif

#include "powermgmt.h"                  /* Power Management module */
#include "relay.h"
#include "r_meter_cmd.h"
#include "r_max_demand.h"
#include "r_tariff.h"
#include "r_scheduler.h"
#include "r_loadsurvey.h"
#include "r_activity_cal.h"
#include "r_load_ctrl.h"

#include "rtc_compensation.h"			/* RTC Compensation using Temperature Sensor */
#include "relay.h"
/* 
 * CS+ CCRL reload trigger:
 * This is used to reload changes from middlewware 
 * when there's no change on application layer
 * There's no dummy_reload.h file, this just make
 * a "not found" file in dependency list of main.c
 * Hence, trigger re-compile everytime build project
*/
#ifdef DUMMY_FOR_RELOAD
    #include "dummy_reload.h"
#endif

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
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
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

static void R_MAIN_UserInit(void);
/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
    startup();
   RELAY_SwitchOn();//RELAY_ON
 // RELAY_SwitchOff();//RELAY_OFF
    /* Start-up OK */ 
    while (1U)
    {
        /* Power management control */
        POWERMGMT_PollingProcessing();

        if (POWERMGMT_GetMode() == POWERMGMT_MODE1)
        {
            /* Start Thread Scheduling  in Normal Mode or Neutral Missing Mode */
            /* KEY Polling Processing */
            KEY_PollingProcessing();
        
            /* LCD Polling Processing */
            EM_DisplaySequence();
	    KEY_PollingProcessing();
            
            #ifndef __DEBUG
            #ifdef _DLMS
            /* DLMS Communication */
            R_DLMS_MAIN_PollingProcessing();
            #endif /* DLMS */
            #endif /* __DEBUG */
            
            /* STORAGE Polling Processing */
            CONFIG_PollingProcessing();
	        
            /* RELAY Polling Processing */
    	    #ifdef RELAY_CONTROL_ENABLE
            
            /* Load control */
            #if(defined( R_LOAD_CONTROL_ENABLE ) && R_LOAD_CONTROL_ENABLE == TRUE)
            R_LOAD_CTRL_PollingProcess();// mrityunjay
            #endif /* R_LOAD_CONTROL_ENABLE */

            /* Relay on off */
            RELAY_PollingProcessing();
    	    #endif
	
            /* Scheduler Polling Processing */
            R_SCHEDULER_PollingProcessing();

            /* EVENT Polling Processing */
            EVENT_PollingProcessing();
 
	    /* MAX DEMAND Polling Processing */    
	    R_MDM_PollingProcessing();
	    
            /* Activity calendar Polling Processing */
            R_ACT_CAL_PollingProcessing();

	    /* TARIFF Polling Processing */    
	    R_TARIFF_PollingProcessing();

            /* LOADSURVEY Polling Processing */
            R_LOADSURVEY_PollingProcessing();

            /* MeterCmd Polling Processing */
            R_METER_CMD_PollingProcessing();
            
            /* RTC COMPENSATION Polling Processing */
            RTC_COMP_PollingProcessing();
	     /* EEPROM CMD Polling Processing */
	    EEPROM_commands_PollingProcessing();
        }

        R_WDT_Restart();
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */