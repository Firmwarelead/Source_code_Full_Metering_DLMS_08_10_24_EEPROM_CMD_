; Copyright (C) 2014 Renesas Electronics Corporation
; RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
; This program must be used solely for the purpose for which
; it was furnished by Renesas Electronics Corporation. No part of this
; program may be reproduced or disclosed to others, in any
; form, without the prior written permission of Renesas Electronics
; Corporation.

;   NOTE       : THIS IS A TYPICAL EXAMPLE.

    .public _em_cstart
    
;-----------------------------------------------------------------------------
;   RAM section
;-----------------------------------------------------------------------------
.SECTION .dataR, DATA
.SECTION .sdataR, DATA
; .SECTION .datafR, DATAF
; .SECTION .textfR, TEXTF

;-----------------------------------------------------------------------------
;   Prefetch for execute on RAM (10bytes)
;-----------------------------------------------------------------------------
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
    
;-----------------------------------------------------------------------------
;   startup
;-----------------------------------------------------------------------------
.SECTION EMText_f, TEXTF

_em_cstart:

    ;--------------------------------------------------
    ; Force linking EM Symbol
    ;--------------------------------------------------
    CALL !!_EM_ForceLinking
    
    ;--------------------------------------------------
    ; hardware initialization
    ;--------------------------------------------------
	CALL	!!_hdwinit

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

    ;--------------------------------------------------
    ; call main function
    ;--------------------------------------------------
    CALL    !!_em_main

    ;--------------------------------------------------
    ; call exit function
    ;--------------------------------------------------
    RET

