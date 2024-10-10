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
* File Name    : bl_main.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Bootloader Main processing
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <string.h>
#include "bl_header.h"
#include "fsl.h"

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
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Masking for LVD reset source in RESF registers */
#define LVIRF                               (0x01)

/* Define the maximum number of false reset */
#define BL_MAX_CONTINUOUS_FAULTY_RESET      (5)

#define R_WDT_Restart()                     {WDTE = 0xACU;}

typedef enum tagImageRecoveryStatus
{
    IMAGE_RECOVERY_NONE = 0,
    IMAGE_RECOVERY_SUCCESS,
    IMAGE_RECOVERY_FAIL_HEADER,
    IMAGE_RECOVERY_FAIL_CRC,
    IMAGE_RECOVERY_FAIL_FSL,
} image_recovery_status_t;

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
uint8_t g_bl_resf;
uint8_t g_bl_porsr;
#if (WARMBOOT == 1)
uint8_t g_bl_bankswap_startup;
#endif

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
#ifdef __ICCRL78__

/* Set option bytes */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte0 = 0x7EU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte1 = 0x3FU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte2 = 0xB2U;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte3 = 0x84U;

/* Set security ID */
#pragma location = "SECUID"
__root const uint8_t secuid[10] = 
    {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};

#endif

/* Non-initialized reserved RAM area for bootloader */
#pragma section bss BLNoInit
BL_INFORMATION g_bl_info;
#pragma section

/***********************************************************************************************************************
 * Function Name: bl_startup
 * Description  : Startup up code for bootloader called:
 *              :   After stack init and memory initialization
 *              :   Before metrology initialization
 *              : Note: this only called in POR or soft reset, not from bank swap reset --> interrupts still disabled 
 * Arguments    : void
 * Return Value : void
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
void bl_startup(void)
{
    /* Check and open flash shield window: this additional code guard taken care by user code, not by bootloader lib */
    {
        fsl_fsw_t flash_shield;
        uint16_t user_code_start_block = (((uint32_t)USER_APP_START_ADDRESS + DEVICE_FLASH_BANK_SIZE) / DEVICE_FLASH_BLOCK_SIZE);
        uint16_t user_code_end_block = (((uint32_t)USER_APP_END_ADDRESS + DEVICE_FLASH_BANK_SIZE) / DEVICE_FLASH_BLOCK_SIZE);
        uint8_t psw = __get_psw();

        BL_FLASH_Prepare();
        
        /* Mask IE bit if needed (FlashShieldWindow APIs require no ROM code interrupts executed during operation) */
        if ((psw & 0x80) != 0)
        {
            DI();
        }

        FSL_GetFlashShieldWindow(&flash_shield);

        /* Flash shield setting is non-volatile, if it's set once for this MCU, then no FSL_SetFlashShieldWindow execution */
        if (flash_shield.fsl_start_block_u16 != user_code_start_block ||
            flash_shield.fsl_end_block_u16 != user_code_end_block)
        {
            flash_shield.fsl_start_block_u16 = user_code_start_block;
            flash_shield.fsl_end_block_u16 = user_code_end_block;
            FSL_SetFlashShieldWindow(&flash_shield);
        }

        /* Recover IE bit if needed */
        if ((psw & 0x80) != 0)
        {
            EI();
        }

        BL_FLASH_CleanUp();
    }

    /* Initialize no init variable on PORSR only */
    {
        g_bl_porsr = PORSR;

        /* Check for power on reset */
        if (PORSR == 0)
        {
            /* Initialize the no init area for first time */
            memset(&g_bl_info, 0, sizeof(g_bl_info));
            
            /* Mark as power on reset */
            PORSR = 1;
        }

        /* Get the reset flag */
        g_bl_resf = RESF;
    }
    
    /* Start additional user code: */

    /* End additional user code: */
}
/***********************************************************************************************************************
 End of function bl_startup
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: bl_main
* Description  : Main processing called after:
*              :    After stack init and memory initialization, bl_startup, metrology_entry, 
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void bl_main(void)
{
    /* Although g_bl_info initialized at PORSR, 
     * But changing code on bootloader could cause RAM re-allocated on non-init RAM
     * For safety during developing, temporarily disable RAM parity reset and enable later when read this area
     */
    RPERDIS = 1U;

    /* Start additional user code: */
    {
        image_recovery_status_t recovery_status;
        uint16_t status;
        uint16_t calculated_crc;
        bl_image_header_t rw_bank_header;

        /* Image recovery (by checking faulty reset) */
        /* Check faulty reset */
        if (g_bl_resf != 0x00 && g_bl_resf != LVIRF)
        {
            /* Not normal reset */
            if (g_bl_info.is_user_reset != 1)
            {
                /* Not intentional reset, considered faulty reset */
                if (g_bl_info.reset_count < BL_MAX_CONTINUOUS_FAULTY_RESET)
                {
                    g_bl_info.reset_count++;
                }
                else
                {
                    /* Stop increasing the count, prevent overflow */
                }
            }
            else
            {
                /* Intentional reset, acknowledge the request and clear faulty reset count */
                g_bl_info.is_user_reset = 0;
                g_bl_info.reset_count = 0;
            }
        }
        else
        {
            /* Normal reset: clear faulty reset count */
            g_bl_info.reset_count = 0;
        }
        
        /* Check for image recovery */
        if (g_bl_info.reset_count >= BL_MAX_CONTINUOUS_FAULTY_RESET)
        {
            /* Exceed number of reset, proceed image recovery */

            BL_IMAGE_GetHeaderInfo(&rw_bank_header, BL_IMAGE_REWRITE_BANK);

            /* Checking image header:
             *  If size exceed user partition ROM code size
             *  If hash value looks valid
            */
            if ( (rw_bank_header.user_app_size <= ((uint32_t)USER_APP_END_ADDRESS - USER_APP_START_ADDRESS + 1)) &&
                 ((rw_bank_header.user_app_hash & 0x0000FFFF) != 0x0000 && (rw_bank_header.user_app_hash & 0x0000FFFF) != 0xFFFF) &&
                 (1) )
            {
                
                /* Header looks valid, init and run hash calculator */
                BL_HASHING_CalculateOnce(
                    ((uint32_t)USER_APP_HEADER_ADDRESS + USER_APP_HEADER_SIZE),  //Offset to rewrite bank branch table
                    ((uint32_t)USER_APP_HEADER_ADDRESS + USER_APP_HEADER_SIZE) + (rw_bank_header.user_app_size) - 1,
                    &calculated_crc
                );

                /* Check if calculated hash matched with header image hash value */
                if (calculated_crc == (rw_bank_header.user_app_hash & 0x0000FFFF))
                {
                    /* Matched, swap back image */

                    /* Prepare FSL operation */
                    BL_FLASH_Prepare();
                    
                    /* Invert boot flag (all interrupts disabled), bank not swap until MCU reset */
                    DI();
                    status = FSL_InvertBootFlag();
                    EI();
                    
                    /* Clean up after FSL operations */
                    BL_FLASH_CleanUp();
                    
                    if (status == FSL_OK)
                    {
                        /* Image recovery sucess */

                        /* Mark success image recovery for later assert status for user code */
                        recovery_status = IMAGE_RECOVERY_SUCCESS;
                    }
                    else
                    {
                        /* Swap error, boot flag not change, no image recovery */
                        recovery_status = IMAGE_RECOVERY_FAIL_FSL;
                    }
                }
                else
                {
                    /* Hash verification failed, no image recovery */
                    recovery_status = IMAGE_RECOVERY_FAIL_CRC;
                }
            }
            else
            {
                /* Headers looks not valid, no image recovery */
                recovery_status = IMAGE_RECOVERY_FAIL_HEADER;
            }
        }
        else
        {
            /* Below number of reset, no image recovery */
            recovery_status = IMAGE_RECOVERY_NONE;
        }

        /* Checking to assert update status */
#if (WARMBOOT == 1)
        if (g_bl_bankswap_startup == 1)
        {
            /* Bank swap startup (success firmware upgrade) */
            
            /* Reset faulty reset checking */
            g_bl_resf = 0;
            /* Assert image update success */
            g_bl_info.image_update.value = 0;
            g_bl_info.image_update.details.new_update_info = 1;
            g_bl_info.image_update.details.update_sucess = 1;
        }
        else
#endif /* WARMBOOT == 1 */
        {
            /* Reset startup */
            if (recovery_status == IMAGE_RECOVERY_SUCCESS)
            {
                /* Reset startup, success image recovery */

                /* Reset faulty reset checking */
                g_bl_resf = 0;
                /* Assert image update failed: new image not work */
                g_bl_info.image_update.value = 0;
                g_bl_info.image_update.details.new_update_info = 1;
                g_bl_info.image_update.details.update_failed_new_image_not_work = 1;

                /* Execute software reset to swap bank and clean up all MCU state */
                g_bl_info.is_user_reset = 1;
                #if (RST_CHOICE == 1)
                FSL_ForceReset();
                #elif (RST_CHOICE == 0)
                WDTE = 0; while(1);
                #endif

                /* MCU reset by above code */
                
            }
            else if (recovery_status == IMAGE_RECOVERY_FAIL_HEADER ||
                     recovery_status == IMAGE_RECOVERY_FAIL_CRC ||
                     recovery_status == IMAGE_RECOVERY_FAIL_FSL)
            {
                /* Reset startup, failure image recovery, TODO */
            }
            else if (recovery_status == IMAGE_RECOVERY_NONE)
            {
                /* Reset startup, no image recovery */
            }
            else
            {
                /* Unknown recovery status value */
            }
        }

        /* End additional user code: */
    }

    /* Clear the flag and enable RAM parity reset again */
    RPEF = 0; 
    RPERDIS = 0U;
}

/***********************************************************************************************************************
 * Function Name: BL_IncreaseSoftwareVersion
 * Description  : Sample implementation to increase software version in 3 byte buffer
 * Arguments    : uint8_t * p_version
 * Return Value : void
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
void BL_IncreaseSoftwareVersion(uint8_t * p_version)
{
    uint8_t temp[3+1];      //Padding 1 more byte for easier calculation
    uint16_t i;

    /* Check input pointer */
    if (p_version == NULL)
    {
        return;
    }

    /* Increase version implementation (customizable) */
    /* Sample implementation: 
        * 3 byte, each byte treated as BCD max 0x09
        * Increase LSByte first, then over flow to 
     */

    BL_memcpy_nf(temp, p_version, 3);

    temp[0]++;
    for (i = 0; i < 3; i++) 
    {
        if (temp[i] > 0x09)
        {
            temp[i] = 0;
            temp[i+1]++;

        }
    }

    BL_memcpy_nf(p_version, temp, 3);
}
/***********************************************************************************************************************
 End of function BL_IncreaseSoftwareVersion
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_AcknowledgeImageUpdateStatus
 * Description  : Clear image update status
 * Arguments    : void
 * Return Value : void
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
void BL_AcknowledgeImageUpdateStatus(void)
{
    g_bl_info.image_update.value = 0;
}
/***********************************************************************************************************************
 End of function BL_AcknowledgeImageUpdateStatus
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_GetImageUpdateStatus
 * Description  : Get image update status
 * Arguments    : void
 * Return Value : bl_image_update_status_t
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
bl_image_update_status_t BL_GetImageUpdateStatus(void)
{
    bl_image_update_status_t status;
    
    /* Temporarily disable RAM parity */
    RPERDIS = 1U;

    status = g_bl_info.image_update;
    
    /* Clear the flag and enable RAM parity reset again */
    RPEF = 0; 
    RPERDIS = 0U;

    return status;
}
/***********************************************************************************************************************
 End of function BL_GetImageUpdateStatus
***********************************************************************************************************************/