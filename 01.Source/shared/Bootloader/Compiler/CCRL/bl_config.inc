;=================================================================================================
; Project      = Configuration for bootloader related
; Module       = bl_config.inc
; Device:      = RL78_I1C_512k
;=================================================================================================
; DISCLAIMER
; This software is supplied by Renesas Electronics Corporation and is only
; intended for use with Renesas products. No other uses are authorized. This
; software is owned by Renesas Electronics Corporation and is protected under
; all applicable laws, including copyright laws.
; THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
; THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
; LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
; AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
; TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
; ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
; FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
; ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
; BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
; Renesas reserves the right, without notice, to make changes to this software
; and to discontinue the availability of this software. By using this software,
; you agree to the additional terms and conditions found by accessing the
; following link:
; http://www.renesas.com/disclaimer
;
; Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
;=================================================================================================
; Purpose:
;              common definition for memory range in bootloader used in startup code
;
;=================================================================================================
$IFDEF __BOOT_LOADER_CONFIG_INCLUDED

$ELSE
__BOOT_LOADER_CONFIG_INCLUDED   .SET    1

__USING_BOOTLOADER__            .EQU    1

WARMBOOT                        .SET    1

FAR_BRANCH_VECTOR_TABLE         .EQU    0x000d8
USER_BRANCH_TABLE               .EQU    0x01100
METROLOGY_BRANCH_TABLE          .EQU    0x34c00
COMMON_STACK_SIZE               .EQU    0x1320
COMMON_STACK_END_ADDR           .EQU    0xfe20

$ENDIF