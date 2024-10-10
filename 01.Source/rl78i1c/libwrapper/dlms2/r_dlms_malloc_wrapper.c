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
/* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************	
* File Name    : r_dlms_mallc_wrapper.c
* Version      : 1.00
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL
* H/W Platform : None
* Description  : Malloc wrapper for DLMS Library
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 16.08.2018
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "wrp_app_ext.h"
#include "r_dlms_malloc_wrapper.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
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

/******************************************************************************
* Function Name : R_DLMS_Malloc
* Interface     : void *R_DLMS_Malloc(uint16_t size)
* Description   : Create a memory area with specific size
* Arguments     : uint16_t size: Requested size of memory to be created
* Return Value  : void *, returned memory buffer pointer
******************************************************************************/
void *R_DLMS_Malloc(uint16_t size)
{
    return WRP_EXT_Heap_Malloc(size);
}

/******************************************************************************
* Function Name : R_DLMS_Free
* Interface     : void R_DLMS_Free(void *memory)
* Description   : Free the memory area that created by malloc()
* Arguments     : void * memory: Pointer of area that memory created by malloc()
* Return Value  : None
******************************************************************************/
void R_DLMS_Free(void *memory)
{
    WRP_EXT_Heap_Free(memory);
}