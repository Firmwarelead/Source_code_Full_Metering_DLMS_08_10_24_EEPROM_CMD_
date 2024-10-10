/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : em_main.h
* Version      : 1.0
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY  Version  Description
*         : 16.11.2020  1.0  Initial release
***********************************************************************************************************************/

#ifndef __EM_MAIN_H
#define __EM_MAIN_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global Typedef definitions
***********************************************************************************************************************/
typedef struct st_em_startup_diag {
    uint8_t em_init_status;             /* EM_Init status */
    uint8_t config_load_status;         /* Config storage reload from dataflash status (other than 0 means error) */
    uint8_t energy_load_status;         /* Energy storage reload from EEPROM status (other than 0 means error) */
    uint8_t em_start_status;            /* EM_Start status */
} st_em_startup_diag_t;

/***********************************************************************************************************************
External global variables
***********************************************************************************************************************/
extern st_em_startup_diag_t g_em_startup_diag;

/***********************************************************************************************************************
Exported global functions
***********************************************************************************************************************/
void em_startup(void);
void em_main(void);

#endif /* __EM_MAIN_H */
