/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013, 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_md5.h
* Version      : 
* Device(s)    : 
* Tool-Chain   : 
* Description  : 
* Creation Date:
***********************************************************************************************************************/
#ifndef R_MD5_H
#define R_MD5_H

#ifdef __CCRL__
#include "r_stdint.h"
#elif __ICCRL78__
#include <stdint.h>
#endif /* __CCRL__ */

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/**
* Definition for C++ Compatible code
*/
#ifndef EXTERN_C

#ifdef __cplusplus
#   define EXTERN_C     extern "C"
#else
#   define EXTERN_C
#endif // __cplusplus

#endif

#define R_PROCESS_COMPLETE  (0)
#define R_MD_ERROR_POINTER  (-1)
#define R_MD_ERROR_LENGTH   (-2)

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/
typedef uint32_t R_Md5[22];

/***********************************************************************************************************************
Export variables
***********************************************************************************************************************/
extern const char R_md5_version[];

/***********************************************************************************************************************
Function definitions
***********************************************************************************************************************/
EXTERN_C int8_t R_Md5_Init(void * p_work);
EXTERN_C int8_t R_Md5_Calculate(uint8_t * p_mdat, uint16_t size, void * p_work);
EXTERN_C int8_t R_Md5_GetResult(uint8_t * p_hdat, void * p_work);
EXTERN_C int8_t R_Md5_CalculateOnce(uint8_t * p_mdat, uint16_t size, uint8_t * p_hdat);

#endif /* R_MD5_H */