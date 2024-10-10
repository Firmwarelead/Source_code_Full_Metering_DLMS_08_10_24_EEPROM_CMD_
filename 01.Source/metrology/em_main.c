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
* Copyright (C) 2015, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : em_main.c
* Version      : 
* Device(s)    : 
* Tool-Chain   : 
* Description  : 
* Creation Date: 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "compiler.h"

/* Metrology */
#include "em_core.h"

/* Bootloader */
#include "bl_main.h"

/* Application */
#include "config_storage.h"
#include "wrp_em_sw_config.h"
#include "platform.h"
#include "eeprom.h"
#include "storage_em.h"
#include "em_main.h"
#include "startup.h"
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
#endif /* DUMMY_FOR_RELOAD */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
st_em_startup_diag_t g_em_startup_diag;
uint8_t g_reset_flag;
uint8_t g_porsr_flag;
uint8_t g_rtcporsr_flag;
/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: config_data_load
 * Description  : Load configuration and calibration data from dataflash 
 * Arguments    : NA
 * Return Value : uint8_t
 **********************************************************************************************************************/
static uint8_t config_data_load(EM_CALIBRATION * p_calib, st_em_setting_t * p_em_setting)
{
    uint8_t init_status;

    /* Assign pointer for phase degree in calib holder value */
    p_calib->sw_phase_correction.i1_phase_degrees = p_em_setting->degree_list_i1;
    p_calib->sw_phase_correction.i2_phase_degrees = p_em_setting->degree_list_i2;

    /* Assign pointer for gain in calib to holder value */
    p_calib->sw_gain.i1_gain_values = p_em_setting->gain_list_i1;
    p_calib->sw_gain.i2_gain_values = p_em_setting->gain_list_i2;
    
    /* Init config */
    init_status = CONFIG_Init(0);

    /* Check device format */
    if (init_status == CONFIG_OK)       /* Initial successful, already formatted */
    {

    }
    /* Initial successful, but not formatted */
    else if (init_status == CONFIG_NOT_FORMATTED)
    {
        /* Format device */
        if (CONFIG_Format() != CONFIG_OK)
        {
            /* When format fail,
             * we need to beak the start-up process here */     
            return CONFIG_ERROR;   /* Format fail */
        }       
        else    /* format ok */
        {

        }
    }

    if (CONFIG_LoadEMCalib(p_calib, &p_em_setting->regs) != CONFIG_OK)
    {
        NOP();
    }
    else
    {
        NOP();
    }

    /* Load data sucessfully */
    return CONFIG_OK;
}

/***********************************************************************************************************************
 * Function Name: em_energy_data_load
 * Description  : Load energy data from storage eeprom to metrology counter 
 * Arguments    : NA
 * Return Value : uint8_t
 **********************************************************************************************************************/
static uint8_t em_energy_data_load(void)
{

    EPR_Init();

    /* Load from eeprom */
    if (STORAGE_EM_Restore() != EM_STORAGE_OK)
    {
        return EM_STORAGE_ERROR;
    }

    return EM_STORAGE_OK;
}

/***********************************************************************************************************************
 * Function Name: em_startup
 * Description  : Startup routine for fixed metrology
 * Arguments    : void
 * Return Value : void
 **********************************************************************************************************************/
void em_startup(void)
{
    EM_CALIBRATION           calib;
    st_em_setting_t          em_hold_setting_value;

    /* Switch to HS later using temperature sensor before metrology started, if not need temperature measurement, no need to enable it */
    if (FLASH_MODE_IS_HS() == 0)
    {
       FLASH_MODE_LS_TO_HS();
       //BL_UpdateFslDescriptor(0, 6);   /* Full speed, 6Mhz */
    }

    /* Init configuration and restore calibration data from dataflash */
    g_em_startup_diag.config_load_status = config_data_load(&calib, &em_hold_setting_value);

    /* Init load data from storage for ADC driver */
    R_DSADC_SetGain(em_hold_setting_value.regs);
    
    /* Init for EM */
    g_em_startup_diag.em_init_status = EM_Init((EM_PLATFORM_PROPERTY FAR_PTR *)&g_EM_DefaultProperty, &calib);
        
    /* Init eeprom and restore EM energy counter from eeprom */
    g_em_startup_diag.energy_load_status = em_energy_data_load();
    
    /* Starting metrology */
    g_em_startup_diag.em_start_status = EM_Start();
}
/***********************************************************************************************************************
 End of function em_startup
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: em_main
 * Description  : Entry function of fixed metrology called from bootloader
 * Arguments    : void
 * Return Value : void
 **********************************************************************************************************************/
void em_main(void)
{
    /* Update driver status flag */
    g_reset_flag = g_bl_resf;
    g_porsr_flag = g_bl_porsr;
    g_rtcporsr_flag = RTCPORSR;

    /* Enable interrupt in main */
    EI();

    em_startup();
}
/***********************************************************************************************************************
 End of function em_main
***********************************************************************************************************************/
