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
* File Name    : bl_flash.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : ROM Self Flash functions
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <string.h>
#include "bl_header.h"
#include "fsl.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_FLASH_Prepare
 * Description  : Call functions:
 *                  FSL_Init
 *                  FSL_Open
 *                  FSL_PrepareFunctions
 *                  FSL_PrepareExtFunctions
 * Arguments    : p_fsl_descriptor: in pointer (accept up to far) to descriptor structure on user code
 * Return Value : uint16_t: error code of the below
 *                  BL_OK: normals, means FSL_Init sucessfully
 *                  BL_ERROR_FUNC_FSL_Init | fsl_u08: error on FSL_Init
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
uint16_t BL_FLASH_Prepare(void)
{
    uint16_t bl_status;
    fsl_u08 fsl_status;
    fsl_descriptor_t fsl_descriptor;
    
    fsl_descriptor.fsl_flash_voltage_u08 = 0x01;    /* Wide-voltage */
    fsl_descriptor.fsl_auto_status_check_u08 = 1;   /* Auto check */
    
    /* Calculate current CPU frequency for fsl descriptor fsl_frequency_u08 */
    /* FRQSEL3, fMX is not supported, only either fPLL or fOCO for fMAIN  */
    if (MCKC & 0x80 == 0x80)
    {
        /* fPLL used for fMAIN */
        fsl_descriptor.fsl_frequency_u08 = 32;
    }
    else
    {
        /* fOCO used for fMAIN */
        if (0) {}
        else if (HOCODIV == 0x00)
        {
            fsl_descriptor.fsl_frequency_u08 = 24;
        }
        else if (HOCODIV == 0x01)
        {
            fsl_descriptor.fsl_frequency_u08 = 12;
        }
        else if (HOCODIV == 0x02)
        {
            fsl_descriptor.fsl_frequency_u08 = 6;
        }
        else if (HOCODIV == 0x03)
        {
            fsl_descriptor.fsl_frequency_u08 = 3;
        }
        else if (HOCODIV == 0x04)
        {
            fsl_descriptor.fsl_frequency_u08 = 3;
        }
        else
        {
            /* Unsupported value, fall to max frequency for this MCU */
            fsl_descriptor.fsl_frequency_u08 = 32;
        }
    }

    /* Starting the FSL: Init --> Open --> PrepareFunctions*/
    fsl_status = FSL_Init(&fsl_descriptor);
    if (fsl_status != FSL_OK) 
    {
        bl_status = BL_ERROR_FUNC_FSL_Init | fsl_status;
    }
    else 
    {
        bl_status = BL_OK;

        FSL_Open();
        FSL_PrepareFunctions();
        /* Though PrepareExt only used for advanced function, but called it also for simplifying code flow */
        FSL_PrepareExtFunctions();
    }

    return bl_status;
}
/***********************************************************************************************************************
 End of function BL_FLASH_Prepare
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_FLASH_CleanUp
 * Description  : Call to FSL_Close
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
void BL_FLASH_CleanUp(void)
{
    /* Close FSL operation */
    FSL_Close();
}
/***********************************************************************************************************************
 End of function BL_FLASH_CleanUp
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: bl_flash_write_data_to_erased_flash
* Description  : Helper function to write flash block data
*              : Note:
*              :        size <= 1024 (one device flash block size)
*              :        addr and size in units of 4 (else write failed)
*              : Each write of FSL_Write is maximum 256 bytes only.
*              : This API split data into each max 256 bytes, so maximum 4 loop is expected
* Arguments    : uint32_t addr, uint8_t * buffer, uint16_t size
* Return Value : uint8_t: fsl_status
***********************************************************************************************************************/
static uint8_t bl_flash_write_data_to_erased_flash(uint32_t addr, uint8_t * buffer, uint16_t size)
{
    fsl_write_t flash_write_info;
    fsl_u08 fsl_status;
    uint16_t write_size;

    /* Write directly */
    while(size > 0)
    {
        write_size = MAX_NUMBER_OF_BYTE_EACH_WRITE - (uint16_t)(addr % MAX_NUMBER_OF_BYTE_EACH_WRITE);
        if (write_size > size)
        {
            write_size = size;
        }

        flash_write_info.fsl_word_count_u08 = write_size / DEVICE_FLASH_WRITE_WORD_SIZE;
        flash_write_info.fsl_data_buffer_p_u08 = buffer;
        flash_write_info.fsl_destination_address_u32 = addr;
        
        fsl_status = FSL_Write(&flash_write_info);
        
        if (fsl_status != FSL_OK)
        {
            break;
        }

        size    -= write_size;
        buffer      += write_size;
        addr        += write_size;
    }
    
    return fsl_status;
}

/***********************************************************************************************************************
 * Function Name: BL_FLASH_BankProgramming
 * Description  : Execute bank programming function (for device supported bank programming only)
 *                The input address will auto shifted to rewrite bank region (+ bl_properties_t.device.bank_size)
 *                Max 16bit calculation range, this API will split into chunk within 1 flash block (1024 bytes)
 *                Internal 2 type of operation:  Fast-write operation and RMEW operation (read-modify-erase-write)
 *                  Condition for trying fast-write:
 *                      + Both address and size must be in units of 4 bytes
 *                      + Data within writing area must be all FFs (state after erased for RL78 flash)
 *                  Fast-write: any write-verify failure during fast-write will fall back to RMEW
 *                  RMEW: contain 4 operations
 *                      + Read back content of current block into temporary buffer (1024 bytes)
 *                      + Modify the content based on address on the buffer block
 *                      + Write entire buffer content to flash
 *                      + Verify write state again
 *                  Any failure in operation of RMEW will return immediately with error code
 *                  Common for either operation : content in write area is read back and compare byte-by-byte
 * Arguments    : addr: ROM address to write new content (note, address will shifted to rewrite bank region)
 *              : buffer: content to write to ROM address in rewrite bank
 *              : size: size of write content
 * Return Value : uint16_t: error code of the below
 *                  BL_OK: normals, means all operations sucessfully, ensure written ROM content same as input buffer
 *                  BL_ERROR_NULL_POINTER: buffer is NULL
 *                  BL_ERROR_ZERO_SIZE: size is zero
 *                  BL_ERROR_ADDRESS_RANGE: addr + size > bl_properties_t.device.bank_size
 *                  BL_ERROR_FUNC_FSL_Init | fsl_u08: error on FSL_Init
 *                  BL_ERROR_FUNC_FSL_Erase | fsl_status: error on FSL_Erase
 *                  BL_ERROR_FUNC_FSL_Write | fsl_status: error on FSL_Write
 *                  BL_ERROR_FUNC_FSL_IVerify | fsl_status: error on FSL_IVerify
 *                  BL_ERROR_DATA_CORRUPT: read back written ROM content not same as input buffer
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
uint16_t BL_FLASH_BankProgramming(uint32_t addr, uint8_t * buffer, uint16_t size)
{
    /* Open large enough buffer for read-modify-erase-write cycle within 1 FLASH block */
    uint8_t work_buffer[DEVICE_FLASH_BLOCK_SIZE];
    fsl_u08 fsl_status;
    uint16_t bl_status;
    uint16_t i, write_size, write_pos, block_index;
    uint8_t is_area_blank, is_rmew;

    /* Check user buffer */
    if (buffer == NULL)
    {
        return BL_ERROR_NULL_POINTER;
    }
    /* Stop if size is zero */
    if (size == 0)
    {
        return BL_ERROR_ZERO_SIZE;
    }

    /* Check the address range if still within 1 bank */
    if( (addr + size) > g_bl_properties.device.bank_size )
    {
        return BL_ERROR_ADDRESS_RANGE;
    }

    /* Shift address to programming bank */
    addr += g_bl_properties.device.bank_size;

    /* Enable bank programming */
    FLMWEN = 1U;
    BANKPGEN = 1U;
    FLMWEN = 0U;
    
    /* Prepare need to be success for further code below */
    bl_status = BL_FLASH_Prepare();
    if (bl_status != BL_OK) { return bl_status; }

    /* Any failure will mark bl_status to error */
    bl_status = BL_OK;
    while (size > 0)
    {
        /* Operation is on 1 device flash block, get the remainder */
        write_size = DEVICE_FLASH_BLOCK_SIZE - (uint16_t)(addr % DEVICE_FLASH_BLOCK_SIZE);
        if (write_size > size)
        {
            write_size = size;
        }

        block_index = addr / DEVICE_FLASH_BLOCK_SIZE;
        write_pos = addr % DEVICE_FLASH_BLOCK_SIZE;

        /* 
         * FAST WRITING:
         *  Normally read-modify-erase-write, but routine below attempt to write directly withou read-modify-erase
         *  This will save time and limit the number of erase cycle in use case:
         *      . Block erased
         *      . Write is divde to multiple time within that block
         *      . If write is only 1 byte, this will save 1023 block erase
        */
        /* Both addr and write_size is in units of 4 ? */
        if ( ((addr % 4) == 0) && ((write_size % 4) == 0) )
        {
            /* Try simple blank check by reading if write area is 0xFF (value after erased) */
            is_area_blank = 1;
            for (i = 0; i < write_size; i++) 
            {
                /* 0xFF is erased state */
                if ( *((uint8_t FAR_PTR *)(addr + i)) != 0xFF)
                {
                    is_area_blank = 0;
                    break;
                }
            }

            /* Possible to write directly? */
            if (is_area_blank == 1)
            {
                /* Write directly from input buffer and addr */
                fsl_status = bl_flash_write_data_to_erased_flash(addr, buffer, write_size);

                if (fsl_status == FSL_OK)
                {
                    /* Direct write looks ok, verify it again */
                    fsl_status= FSL_IVerify(block_index);
                    if (fsl_status == FSL_OK)
                    {
                        /* Verify success, skip rmew for this write block */
                        is_rmew = 0;
                    }
                    else
                    {
                        /* Verify failed, try RMEW */
                        is_rmew = 1;
                    }
                }
                else
                {
                    /* Write failed, try RMEW */
                    is_rmew = 1;
                }
            }
            else
            {
                /* Areas is not blank, try RMEW */
                is_rmew = 1;
            }
        }
        else
        {
            /* Both address and length is not in units of 4, need to RMEW */
            is_rmew = 1;
        }
        
        /* Need to do Read-Modify-Erase-Write cycle? */
        if (is_rmew == 1)
        {
            /* Read the whole block */
            BL_memcpy_nf(work_buffer, (void FAR_PTR *)((uint32_t)block_index * DEVICE_FLASH_BLOCK_SIZE), DEVICE_FLASH_BLOCK_SIZE);

            /* Modify write area */
            for (i = 0; i < write_size; i++)
            {
                work_buffer[write_pos+i] = buffer[i];
            }

            /* Erase the whole block */
            fsl_status = FSL_Erase(block_index);
            if (fsl_status != FSL_OK)
            {
                /* RMEW cycle failed, force exit function */
                bl_status = BL_ERROR_FUNC_FSL_Erase | fsl_status;
                break;
            }

            /* Write modified-buffer to whole block */
            fsl_status = bl_flash_write_data_to_erased_flash((uint32_t)block_index * DEVICE_FLASH_BLOCK_SIZE, work_buffer, DEVICE_FLASH_BLOCK_SIZE);
            if (fsl_status != FSL_OK) 
            {
                /* RMEW cycle failed, force exit function */
                bl_status = BL_ERROR_FUNC_FSL_Write | fsl_status;
                break;
            }

            /* Verify rewritten block */
            fsl_status = FSL_IVerify(block_index);
            if (fsl_status != FSL_OK)
            {
                /* RMEW cycle failed, force exit function */
                bl_status = BL_ERROR_FUNC_FSL_IVerify | fsl_status;
                break;
            }
        }
            
        /* Verify content of rewritten block with input data */
        if (BL_memcmp_nf(buffer, (const void FAR_PTR *)addr, write_size) != 0)
        {
            /* RMEW cycle failed, force exit function */
            bl_status = BL_ERROR_DATA_CORRUPT;
            break;
        }

        size -= write_size;
        addr += write_size;
        buffer += write_size;
    }

    BL_FLASH_CleanUp();

    /* Disable bank programming */
    FLMWEN = 1U;
    BANKPGEN = 0U;
    FLMWEN = 0U;
    
    /* Write success */
    return bl_status;
}

/***********************************************************************************************************************
 * Function Name: BL_FLASH_GetBootFlag
 * Description  : Get boot flag utility function, call to BL_FLASH_GetBootFlag
 * Arguments    : p_boot_flag: pointer to return boot flag
 * Return Value : uint16_t: error code of the below
 *                  BL_OK: normals, means buffer input pointer point to has boot flag info
 *                  BL_ERROR_NULL_POINTER: p_boot_flag_u08 is NULL
 *                  BL_ERROR_FUNC_FSL_Init | fsl_u08: error on FSL_Init
 *                  BL_ERROR_FUNC_FSL_GetBootFlag | fsl_u08: error on FSL_GetBootFlag
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
uint16_t BL_FLASH_GetBootFlag(uint8_t * p_boot_flag)
{
    uint16_t bl_status;
    fsl_u08 fsl_status;

    if (p_boot_flag == NULL) 
    {
        return BL_ERROR_NULL_POINTER;
    }
    
    bl_status = BL_FLASH_Prepare();
    if (bl_status != BL_OK) { return bl_status; }

    fsl_status = FSL_GetBootFlag(p_boot_flag);
    if (fsl_status != FSL_OK)
    {
        bl_status = BL_ERROR_FUNC_FSL_GetBootFlag | fsl_status;
    }

    BL_FLASH_CleanUp();
    
    return bl_status;
}
/***********************************************************************************************************************
 End of function BL_FLASH_GetBootFlag
***********************************************************************************************************************/
