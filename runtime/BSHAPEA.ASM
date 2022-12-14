;?????????????????????????????????????????????????????????????????????????????
;??                                                                         ??
;??  BSHAPEA.ASM                                                            ??
;??                                                                         ??
;??  Assembly routines for use with BSHAPE.C                                ??
;??                                                                         ??
;??  Version 1.00 of 10-Aug-93: Initial version                             ??
;??                                                                         ??
;??  Project: Extensible State-Object Processor (AESOP/32)                  ??
;??  Authors: John Lemberger                                                ??
;??                                                                         ??
;??  8086/80386 ASM source compatible with MASM v6.0 or later               ??
;??  C function prototypes in BSHAPEA.H                                     ??
;??                                                                         ??
;?????????????????????????????????????????????????????????????????????????????
;??                                                                         ??
;??  Copyright (C) 1993 Miles Design, Inc.                                  ??
;??                                                                         ??
;??  Miles Design, Inc.                                                     ??
;??  10926 Jollyville #308                                                  ??
;??  Austin, TX 78759                                                       ??
;??  (512) 345-2642 / BBS (512) 454-9990                                    ??
;??                                                                         ??
;?????????????????????????????????????????????????????????????????????????????

                .386P                   ;Enable 386 instruction set
                .MODEL FLAT,C           ;Flat Memory Model and C calling

                INCLUDE vfx.inc

;*****************************************************************************

                .CODE

;*****************************************************************************
                PUBLIC  scan_block
scan_block      PROC C USES es esi edi, \
                Block:PPANE,color

                mov esi,[Block]

                mov esi,[esi].PANE.win

                mov eax,[esi].WINDOW.wnd_x1
                sub eax,[esi].WINDOW.wnd_x0
                inc eax

                mov ebx,[esi].WINDOW.wnd_y1
                sub ebx,[esi].WINDOW.wnd_y0
                inc ebx

                mul ebx

                mov ecx,eax
                mov eax,color
                mov edi,[esi].WINDOW.buffer
                cld

                repne scasb;

                mov eax,0
                cmp ecx,0
                jz __finish
                
                mov eax,edi
                sub eax,[esi].WINDOW.buffer

__finish:
                ret
scan_block      ENDP

;*****************************************************************************
                END
