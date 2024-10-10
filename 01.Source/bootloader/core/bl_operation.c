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
* File Name    : bl_operation.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : APIs control operation of bootloader
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "bl_header.h"

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
 * Function Name: BL_memcpy_nf
 * Description  : Do memcpy to NEAR destination address from FAR source address
 *              : Can copy across 64k boundary
 * Arguments    : dest: NEAR destination address
 *              : src: FAR source address
 *              : size: copy size
 * Return Value : void NEAR_PTR * last dest after copied
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
void NEAR_PTR * BL_memcpy_nf(
    void NEAR_PTR * dest, 
    const void FAR_PTR * src, 
    uint16_t size
)
{
    uint16_t dest_addr = (uint16_t)dest;
    uint32_t src_addr = (uint32_t)src;

    /* Compiler note:
    * ((uint8_t NEAR_PTR *)dest)[i] = ((uint8_t FAR_PTR *)src)[i];
    * Currently has issue when address of src cross 64k boundary, ES flag not changed accordingly
    * Same behavior when using _COM_memcpy_ff function
    */
    
    while(size > 0)
    {
        *((uint8_t *)dest_addr++) = *((uint8_t FAR_PTR *)src_addr++);
        size--;
    }

    return (void NEAR_PTR *)dest_addr;
}
/***********************************************************************************************************************
 End of function BL_memcpy_nf
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_memcmp_nf
 * Description  : Do memcmp between lhs NEAR address with rhs FAR address
 *              : Can compare across 64k boundary
 * Arguments    : lhs: NEAR lhs address
 *              : rhs: FAR rhs address
 *              : size: compare size
 * Return Value : int: subtract result of first byte that not mach beween lhs and rhs buffer
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
int BL_memcmp_nf(
    void NEAR_PTR * lhs, 
    const void FAR_PTR * rhs, 
    uint16_t size
)
{
    int result;
    uint16_t dest_addr = (uint16_t)lhs;
    uint32_t src_addr = (uint32_t)rhs;

    while(size > 0)
    {
        result = *((uint8_t *)dest_addr++) - *((uint8_t FAR_PTR *)src_addr++);
        if (result != 0) {
            break;
        }
        size--;
    }

    return result;
}
/***********************************************************************************************************************
 End of function BL_memcmp_nf
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_OPERATION_RequestUserReset
 * Description  : Inform an intentional reset from user
 * Arguments    : void
 * Return Value : void
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
void BL_OPERATION_RequestUserReset(void)
{
    g_bl_info.is_user_reset = 1;
}
/***********************************************************************************************************************
 End of function BL_OPERATION_RequestUserReset
***********************************************************************************************************************/