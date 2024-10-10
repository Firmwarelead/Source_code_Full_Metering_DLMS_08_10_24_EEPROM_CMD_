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
* File Name    : bl_operation.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : APIs control operation of bootloader
***********************************************************************************************************************/

#ifndef __BL_OPERATION_H
#define __BL_OPERATION_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"        /* GSCE Standard Typedef */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tagBootLoaderProperties
{
    struct tagDeviceInfo
    {
        uint32_t rom_size;
        uint32_t bank_size;
    } device;
    struct tagUserAppArea
    {
        uint32_t start_addr;
        uint32_t branch_addr;
        uint32_t entry_addr;
        uint32_t end_addr;
    } user_app;

    struct tagEntryAddress
    {
        void (FAR_FUNC *bl_bswap)(void);
    } entry_func;
    
} bl_properties_t;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Shortcut to BL_memcpy_nf call to do section romizing using rom section and ram section name */
#define BL_ROMIZING_SECTION(rom_sec,ram_sec)        BL_memcpy_nf(\
                                                        (void * NEAR_PTR)__sectop(ram_sec),\
                                                        __sectop(rom_sec), \
                                                        (uint32_t)__secend(rom_sec) - (uint32_t)__sectop(rom_sec)\
                                                    )

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_memcpy_nf
 * Description  : Do memcpy to NEAR destination address from FAR source address
 *              : Can copy across 64k boundary
 * Arguments    : dest: NEAR destination address
 *              : src: FAR source address
 *              : size: copy size
 * Return Value : void NEAR_PTR * last dest after copied
 **********************************************************************************************************************/
void NEAR_PTR * BL_memcpy_nf(
    void NEAR_PTR * dest, 
    const void FAR_PTR * src, 
    uint16_t size
);

/***********************************************************************************************************************
 * Function Name: BL_memcmp_nf
 * Description  : Do memcmp between lhs NEAR address with rhs FAR address
 *              : Can compare across 64k boundary
 * Arguments    : lhs: NEAR lhs address
 *              : rhs: FAR rhs address
 *              : size: compare size
 * Return Value : int: subtract result of first byte that not mach beween lhs and rhs buffer
 **********************************************************************************************************************/
int BL_memcmp_nf(
    void NEAR_PTR * lhs, 
    const void FAR_PTR * rhs, 
    uint16_t size
);

/***********************************************************************************************************************
 * Function Name: BL_OPERATION_RequestUserReset
 * Description  : Inform an intentional reset from user
 * Arguments    : void
 * Return Value : void
 **********************************************************************************************************************/
void BL_OPERATION_RequestUserReset(void);

#endif /* __BL_OPERATION_H */
