; Copyright (C) 2014 Renesas Electronics Corporation
; RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
; This program must be used solely for the purpose for which
; it was furnished by Renesas Electronics Corporation. No part of this
; program may be reproduced or disclosed to others, in any
; form, without the prior written permission of Renesas Electronics
; Corporation.

;   NOTE       : THIS IS A TYPICAL EXAMPLE.

$IFNDEF __RENESAS_VERSION__
__RENESAS_VERSION__ .EQU    0x01000000
$ENDIF

$INCLUDE "bl_config.inc"

    .public _bl_start
$IF (WARMBOOT == 1)
    .public _bl_bswap_start
$ENDIF

;-----------------------------------------------------------------------------
;   RAM section
;-----------------------------------------------------------------------------
.SECTION .dataR, DATA
;.SECTION .sdataR, DATA
; .SECTION .datafR, DATAF
; .SECTION .textfR, TEXTF

;-----------------------------------------------------------------------------
;   Prefetch for execute on RAM (10bytes)
;-----------------------------------------------------------------------------
$IF (WARMBOOT == 1)
.SECTION Prefetch_FSL, TEXTF
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
.SECTION Prefetch, TEXTF
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
$ENDIF
    
SETUP_CPU_REGISTERS .MACRO
	;--------------------------------------------------
	; setting register bank
	;--------------------------------------------------
;	SEL	RB0

	;--------------------------------------------------
	; setting mirror area
	;--------------------------------------------------
;	ONEB    !PMC		; mirror area = 10000-1FFFFH

	;--------------------------------------------------
	; setting the stack pointer
	;--------------------------------------------------
    MOVW	SP, #COMMON_STACK_END_ADDR

.ENDM

;-----------------------------------------------------------------------------
;   startup
;-----------------------------------------------------------------------------
.SECTION .text, TEXT

_bl_start:
    SETUP_CPU_REGISTERS         ;Macro call due to SP setting
    CALL    !!_bl_stack_init
    CALL    !!_bl_section_init
    CALL    !!_bl_startup
    CALL    !!(METROLOGY_BRANCH_TABLE + 0x00)    ;Metrology entry
$IF (WARMBOOT == 1)
    CLRB    !_g_bl_bankswap_startup
$ENDIF
    BR      !!_app_run

$IF (WARMBOOT == 1)
_bl_bswap_start:
    SETUP_CPU_REGISTERS         ;Macro call due to SP setting
    ; Stack already initialized
    ; Bootloader section already initialized
    ; Metrology still running
    ONEB    !_g_bl_bankswap_startup
    BR      !!_app_run
$ENDIF

_bl_stack_init:
	;--------------------------------------------------
	; initializing stack area
	;--------------------------------------------------
    MOVW    AX, #COMMON_STACK_END_ADDR
    SUBW    AX, #COMMON_STACK_SIZE
	CALL	!!_bl_stkinit

    RET

_bl_section_init:
    ;--------------------------------------------------
    ; initializing BSS
    ;--------------------------------------------------
    ; clear external variables which doesn't have initial value (near)
    MOVW    HL,#LOWW(STARTOF(.bss))
    MOVW    AX,#LOWW(STARTOF(.bss) + SIZEOF(.bss))
    BR  $.L2_BSS
.L1_BSS:
    MOV [HL+0],#0
    INCW    HL
.L2_BSS:
    CMPW    AX,HL
    BNZ $.L1_BSS

    ;--------------------------------------------------
    ; ROM data copy
    ;--------------------------------------------------
    ; copy external variables having initial value (near)
    MOV ES,#HIGHW(STARTOF(.data))
    MOVW    BC,#LOWW(SIZEOF(.data))
    BR  $.L2_DATA
.L1_DATA:
    DECW    BC
    MOV A,ES:LOWW(STARTOF(.data))[BC]
    MOV LOWW(STARTOF(.dataR))[BC],A
.L2_DATA:
    CLRW    AX
    CMPW    AX,BC
    BNZ $.L1_DATA
    
$IF (WARMBOOT == 1)
    ; romization for FSL_RCD
    MOV ES,#HIGHW(STARTOF(FSL_RCD))
    MOVW    BC,#LOWW(SIZEOF(FSL_RCD))
    BR  $.L2_FSL_RCD
.L1_FSL_RCD:
    DECW    BC
    MOV A,ES:LOWW(STARTOF(FSL_RCD))[BC]
    MOV LOWW(STARTOF(FSL_RCDR))[BC],A
.L2_FSL_RCD:
    CLRW    AX
    CMPW    AX,BC
    BNZ $.L1_FSL_RCD

    ;--------------------------------------------------
    ; initialize prefetch area (for FSL library, which using alignment 2 bytes)
    ;--------------------------------------------------
    MOVW    HL,#LOWW(STARTOF(Prefetch_FSL))
    MOVW    AX,#LOWW(STARTOF(Prefetch_FSL) + SIZEOF(Prefetch_FSL))
    BR  $.L2_Prefetch_FSL
.L1_Prefetch_FSL:
    MOV [HL+0],#0
    INCW    HL
.L2_Prefetch_FSL:
    CMPW    AX,HL
    BNZ $.L1_Prefetch_FSL
$ENDIF

    RET

_app_run:
    ;--------------------------------------------------
    ; Force linking Symbol
    ;--------------------------------------------------
    CALL    !!_BL_ForceLinking

    ;--------------------------------------------------
    ; call main function
    ;--------------------------------------------------
    CALL    !!_bl_main ; bl_main();
    
    ;--------------------------------------------------
    ; branch to user application reset vector
    ;--------------------------------------------------
    BR      !!(USER_BRANCH_TABLE + 0x00)
    
    ;--------------------------------------------------
    ; call exit function
    ;--------------------------------------------------
    CLRW    AX      ; exit(0)
_exit:
    BR  $_exit
    
;-----------------------------------------------------------------------------
;   section
;-----------------------------------------------------------------------------
$IF (__RENESAS_VERSION__ >= 0x01010000)
.SECTION .RLIB, TEXTF
.L_section_RLIB:
.SECTION .SLIB, TEXTF
.L_section_SLIB:
$ENDIF
.SECTION .textf, TEXTF
.L_section_textf:
;.SECTION .const, CONST
;.L_section_const:
.SECTION .constf, CONSTF
.L_section_constf:
.SECTION .data, DATA
.L_section_data:
;.SECTION .dataf, DATAF
;.L_section_dataf:
;.SECTION .sdata, SDATA
;.L_section_sdata:
.SECTION .bss, BSS
.L_section_bss:
;.SECTION .bssf, BSSF
;.L_section_bssf:
;.SECTION .sbss, SBSS
;.L_section_sbss:
