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
* File Name    : r_lcd_config.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CA78K0R
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Declare const array for LCD configuration
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_lcd_config.h"
#include "r_drv_lcd_ext.h"

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
/*
 * Data mapping:
 * This data must be changed when there is any difference on PIN
 * (COM and SEGMENT) connection setting between LCD and MCU
 */
const __far LCD_NUM_MAP g_LCD_NumMap[LCD_NUM_DIGIT] = 
{
    /* Pos   Address Number Type */
    {1,    LCD_RAM_START_ADDRESS + 16 ,  NUM_TYPE_A},
    {2,    LCD_RAM_START_ADDRESS + 17 ,  NUM_TYPE_A},
    {3,    LCD_RAM_START_ADDRESS + 5 ,  NUM_TYPE_A},
    {4,    LCD_RAM_START_ADDRESS + 6 ,  NUM_TYPE_A},
    {5,    LCD_RAM_START_ADDRESS + 8 ,  NUM_TYPE_A},
    {6,    LCD_RAM_START_ADDRESS + 9,    NUM_TYPE_A},
    {7,    LCD_RAM_START_ADDRESS + 10,    NUM_TYPE_A},
    {8,    LCD_RAM_START_ADDRESS + 11,    NUM_TYPE_A},
};

const __far LCD_NUM_TYPE_VALUE g_LCD_NumType[LCD_NUM_DIGIT_CHAR] =                                
{
	/*porting*/
	{0x77},//1011 1110//    { 0xD7 }    , /* '0' - 0* 1101 0111 /  
	{0x12},//0000 0110//    { 0x06 }    , /* '1' - 1* 0000 0110 /
	{0x5D},//0111 1100//    { 0xE3 }    , /* '2' - 2* 1110 0011 /
	{0x5B},//0101 1110//    { 0xA7 }    , /* '3' - 3* 1010 0111 /
	{0x3A},//1100 0110//    { 0x36 }    , /* '4' - 4* 0011 0110 /
	{0x6B},//1101 1010//    { 0xB5 }    , /* '5' - 5* 1011 0101 /
	{0x6F},//1111 1010//    { 0xF5 }    , /* '6' - 6* 1111 0101 /
	{0x52},//0000 1110//    { 0x07 }    , /* '7' - 7* 0000 0111 /
	{0x7F},//1111 1110//    { 0xF7 }    , /* '8' - 8* 1111 0111 /
	{0x7B},//1101 1110//    { 0xB7 }    , /* '9' - 9* 1011 0111 /
	{0x7E},//1110 1110//    { 0x77 }    , /* 'A' - 10* 0111 0111 /  
	{0x2F},//1111 0010//    { 0xF4 }    , /* 'b' - 11* 1111 0100 /
	{0x65},//1011 1000//    { 0xD1 }    , /* 'C' - 12* 1101 0001 /
	{0x1F},//0111 0110//    { 0xE6 }    , /* 'd' - 13* 1110 0110 /
	{0x6D},//1111 1000//    { 0xF1 }    , /* 'E' - 14* 1111 0001 /
	{0x6C},//1110 1000//    { 0x71 }    , /* 'F' - 15* 0111 0001 /
	{0x08},//0100 0000//    { 0x20 }    , /* '-' - 16* 0010 0000 /
	{0x7C},//1110 1100//    { 0x73 }    , /* 'P' - 17* 0111 0011 /
	{0x25},//1011 0000//    { 0xD0 }    , /* 'L' - 18* 1101 0000 /
	{0x76},//1010 1110//    { 0x57 }    , /* 'N' - 19* 0101 0111 /
	{0x01},//0000 0001//    { 0x08 }    , /* na - 20* 0000 1000 /
	{0x37},//1011 0110//    { 0xD6 }    , /* 'U' - 21* 1101 0110 /
    {0x2D},                               /* 't' - 22*/
    {0x0C},                               /* 'r' - 23*/
    {0x3E},                               /* 'H' - 23*/                   // CHANGED ACCORDING TO EXISTING LCD
	/*porting*/
};                              

/* Mapping all special sign of LCD to LCDRAM */
const __far LCD_SIGN_MAP g_LCD_SignMap[LCD_NUM_SIGN] = 
{
	/* Porting*/ 
    /* Number No.   Address   Bit No. */
    {S_31   , LCD_RAM_START_ADDRESS + 4, 4}, /* 00 */              //TAM  sign
    {S_2 , LCD_RAM_START_ADDRESS + 4, 5}, /* 01 */                 // 
    {S_1 , LCD_RAM_START_ADDRESS + 4, 6}, /* 02 */
    {S_3, LCD_RAM_START_ADDRESS + 4, 7}, /* 03 */
    {S_4  , LCD_RAM_START_ADDRESS + 5, 7}, /* 04 */
    {S_30   , LCD_RAM_START_ADDRESS + 6, 7}, /* 05 */
    {S_29  , LCD_RAM_START_ADDRESS + 7, 4}, /* 06 */
    {S_5 , LCD_RAM_START_ADDRESS + 7, 5}, /* 07 */
    {S_6   , LCD_RAM_START_ADDRESS + 7, 6}, /* 08 */
    {S_7  , LCD_RAM_START_ADDRESS + 7 , 7}, /* 09 */
    {S_28  , LCD_RAM_START_ADDRESS + 8 , 7}, /* 10 */ 
    {S_8  , LCD_RAM_START_ADDRESS + 9 , 7}, /* 11 */ 
    {S_27  , LCD_RAM_START_ADDRESS + 10 , 7}, /* 12 */ 
    {S_9    , LCD_RAM_START_ADDRESS + 11 , 7}, /* 13 */ 
    {S_24    , LCD_RAM_START_ADDRESS + 12 , 4}, /* 14 */ 
    {S_25    , LCD_RAM_START_ADDRESS + 12 , 5}, /* 15 */ 
    {S_26   , LCD_RAM_START_ADDRESS + 12 , 6}, /* 16 */ 
    {S_10   , LCD_RAM_START_ADDRESS + 12 , 7}, /* 17 */ 
    {S_33   , LCD_RAM_START_ADDRESS + 13 , 4}, /* 18 */ 
    {S_13   , LCD_RAM_START_ADDRESS + 13 , 5}, /* 19 */ 
    {S_12   , LCD_RAM_START_ADDRESS + 13 , 6}, /* 20 */ 
    {S_11   , LCD_RAM_START_ADDRESS + 13 , 7}, /* 21 */ 
    {S_23   , LCD_RAM_START_ADDRESS + 14 , 4}, /* 22 */ 
    {S_14   , LCD_RAM_START_ADDRESS + 14 , 5}, /* 23 */    
    {S_15   , LCD_RAM_START_ADDRESS + 14 , 6}, /* 24 */
    {S_16   , LCD_RAM_START_ADDRESS + 14, 7}, /* 25 */
    {S_45   , LCD_RAM_START_ADDRESS + 15, 0}, /* 26 */
    {S_44   , LCD_RAM_START_ADDRESS + 15, 1}, /* 27 */
    {S_43   , LCD_RAM_START_ADDRESS + 15, 2}, /* 28 */
    {S_42   , LCD_RAM_START_ADDRESS + 15, 3}, /* 29 */
    {S_40   , LCD_RAM_START_ADDRESS + 15, 4}, /* 30 */
    {S_41   , LCD_RAM_START_ADDRESS + 15, 5}, /* 31 */
    {S_18   , LCD_RAM_START_ADDRESS + 15, 6}, /* 32 */
    {S_17   , LCD_RAM_START_ADDRESS + 15, 7}, 
    {S_0   , LCD_RAM_START_ADDRESS + 16, 7},
    {S_32   , LCD_RAM_START_ADDRESS + 17, 7},
    {S_34   , LCD_RAM_START_ADDRESS + 18, 4},
    {S_22   , LCD_RAM_START_ADDRESS + 18, 5},
    {S_35   , LCD_RAM_START_ADDRESS + 19, 4},
    {S_36   , LCD_RAM_START_ADDRESS + 19, 5},
    {S_38   , LCD_RAM_START_ADDRESS + 20, 4},
    {S_37   , LCD_RAM_START_ADDRESS + 20, 5},
    {S_39   , LCD_RAM_START_ADDRESS + 21, 4},
    {S_21   , LCD_RAM_START_ADDRESS + 21, 5},
    {S_20   , LCD_RAM_START_ADDRESS + 21, 6},
    {S_19   , LCD_RAM_START_ADDRESS + 21, 7},
    {DP_5   , LCD_RAM_START_ADDRESS + 12, 0},
    {DP_6   , LCD_RAM_START_ADDRESS + 12, 1},
    {DP_4   , LCD_RAM_START_ADDRESS + 7, 0},
    {DP_3   , LCD_RAM_START_ADDRESS + 7, 1},
    {DP_2   , LCD_RAM_START_ADDRESS + 7, 2},
    {DP_1   , LCD_RAM_START_ADDRESS + 4, 2},
    {COL_1   , LCD_RAM_START_ADDRESS + 4, 3},
    {COL_2   , LCD_RAM_START_ADDRESS + 7, 3},
    {S_9A   , LCD_RAM_START_ADDRESS + 14, 3},
    {S_9B   , LCD_RAM_START_ADDRESS + 18, 3},
    {S_9C   , LCD_RAM_START_ADDRESS + 18, 1},
    {S_9D   , LCD_RAM_START_ADDRESS + 13, 0},
    {S_9E   , LCD_RAM_START_ADDRESS + 12, 2},
    {S_9F   , LCD_RAM_START_ADDRESS + 12, 3},
    {S_9G1   , LCD_RAM_START_ADDRESS + 13, 2},
    {S_9G2  , LCD_RAM_START_ADDRESS + 18, 2},
    {S_9H   , LCD_RAM_START_ADDRESS + 13, 3},
    {S_9I   , LCD_RAM_START_ADDRESS + 14, 2},
    {S_9J   , LCD_RAM_START_ADDRESS + 13, 1},
    {S_9K   , LCD_RAM_START_ADDRESS + 14, 0},
    {S_9L   , LCD_RAM_START_ADDRESS + 14, 1},
    {S_10A   , LCD_RAM_START_ADDRESS + 20, 3},
    {S_10B   , LCD_RAM_START_ADDRESS + 21, 3},
    {S_10C   , LCD_RAM_START_ADDRESS + 21, 0},
    {S_10D   , LCD_RAM_START_ADDRESS + 19, 0},
    {S_10E   , LCD_RAM_START_ADDRESS + 18, 0},
    {S_10F   , LCD_RAM_START_ADDRESS + 19, 3},
    {S_10G1   , LCD_RAM_START_ADDRESS + 19, 2},
    {S_10G2  , LCD_RAM_START_ADDRESS + 21, 1},
    {S_10H   , LCD_RAM_START_ADDRESS + 20, 2},
    {S_10I   , LCD_RAM_START_ADDRESS + 21, 2},
    {S_10J   , LCD_RAM_START_ADDRESS + 19, 1},
    {S_10K   , LCD_RAM_START_ADDRESS + 20, 0},
    {S_10L   , LCD_RAM_START_ADDRESS + 20, 1},
    
    /* Porting*/
};

const __far LCD_DECIMAL_INFO g_DecInfo  = {5, DP_6};
const __far LCD_DECIMAL_INFO g_DecInfo1 = {4, DP_5};
const __far LCD_DECIMAL_INFO g_DecInfo2 = {3, DP_4};
const __far LCD_DECIMAL_INFO g_DecInfo3 = {2, DP_3};
const __far LCD_DECIMAL_INFO g_DecInfo4 = {1, DP_2};
const __far LCD_DECIMAL_INFO g_DecInfo5 = {0, DP_1};

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
