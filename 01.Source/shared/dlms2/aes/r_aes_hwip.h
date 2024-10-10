/***********************************************************************************************************************
* Copyright (C) 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name	   : r_aes_hwip.h
* Description  : Header file of AES Hardware IP Library.
***********************************************************************************************************************/
#ifndef __r_aes_hwip_h__
#define __r_aes_hwip_h__

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#ifdef __CCRL__
#include "r_stdint.h"
#elif __ICCRL78__
#include <stdint.h>
#endif /* __CCRL__ */
#include "r_dlms_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define AES_KEY128_LEN		(16)		/* 128 bits (16 bytes) */
#define AES_KEY192_LEN		(24)		/* 192 bits (24 bytes) */
#define AES_KEY256_LEN		(32)		/* 256 bits (32 bytes) */
#define AES_BLOCK_SIZE		(16)		/* 128 bits (16 bytes) */
#define AES_IVEC_SIZE		(16)		/* 128 bits (16 bytes) */

#define AES_EKEY128_LEN		(44)		/* 176 bytes (44*4(uint32_t)) */
#define AES_EKEY192_LEN		(52)		/* 208 bytes (52*4(uint32_t)) */
#define AES_EKEY256_LEN		(60)		/* 240 bytes (60*4(uint32_t)) */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/
//extern const mw_version_t R_aes_version;

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
#if defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_AES) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_AES == TRUE)
void R_Aes_Init(void);
void R_Aes_Close(void);

void R_Aes_128_Cbcenc(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint16_t);
void R_Aes_128_Cbcdec(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint16_t);
void R_Aes_128_Ecbenc(uint8_t*, uint8_t*, uint8_t*, uint16_t);
void R_Aes_128_Ecbdec(uint8_t*, uint8_t*,  uint8_t*, uint16_t);

void R_Aes_192_Cbcenc(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint16_t);
void R_Aes_192_Cbcdec(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint16_t);
void R_Aes_192_Ecbenc(uint8_t*, uint8_t*, uint8_t*, uint16_t);
void R_Aes_192_Ecbdec(uint8_t*, uint8_t*,  uint8_t*, uint16_t);

void R_Aes_256_Cbcenc(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint16_t);
void R_Aes_256_Cbcdec(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint16_t);
void R_Aes_256_Ecbenc(uint8_t*, uint8_t*, uint8_t*, uint16_t);
void R_Aes_256_Ecbdec(uint8_t*, uint8_t*,  uint8_t*, uint16_t);
#else
#define R_Aes_Init() 																;
#define R_Aes_Close() 																;

#define R_Aes_128_Cbcenc(a, b, c, d, e) 											;
#define R_Aes_128_Cbcdec(a, b, c, d, e) 											;
#define R_Aes_128_Ecbenc(a, b, c, d) 												;
#define R_Aes_128_Ecbdec(a, b, c, d) 												;

#define R_Aes_192_Cbcenc(a, b, c, d, e)												;
#define R_Aes_192_Cbcdec(a, b, c, d, e)												;
#define R_Aes_192_Ecbenc(a, b, c, d)												;
#define R_Aes_192_Ecbdec(a, b, c, d)												;

#define R_Aes_256_Cbcenc(a, b, c, d, e)												;
#define R_Aes_256_Cbcdec(a, b, c, d, e)												;
#define R_Aes_256_Ecbenc(a, b, c, d) 												;		
#define R_Aes_256_Ecbdec(a, b, c, d) 												;
#endif//defined(CLASS_15_SUPPORT_AUTHENTICATION_BY_AES) && (CLASS_15_SUPPORT_AUTHENTICATION_BY_AES == TRUE)

#endif
