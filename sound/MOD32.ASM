;ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл                                                                         лл
;лл  MOD32.ASM                                                              лл
;лл                                                                         лл
;лл  Four-channel digital mixer                                             лл
;лл                                                                         лл
;лл  Version 1.00 of 26-Feb-93: Initial version for Eye III                 лл
;лл          1.01 of 14-Sep-93: 32-bit version for AESOP/32                 лл
;лл                                                                         лл
;лл  Project: Eye III                                                       лл
;лл  Authors: John W. Ratcliff, John Miles                                  лл
;лл                                                                         лл
;лл  80386 ASM source compatible with MASM V6.0 or later                    лл
;лл                                                                         лл
;лл  C function prototypes in MOD32.H                                       лл
;лл                                                                         лл
;ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл                                                                         лл
;лл  Copyright (C) 1992, 1993 John W. Ratcliff                              лл
;лл                                                                         лл
;лл  Permission granted for use only in AESOP/32 applications               лл
;лл                                                                         лл
;ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл

                OPTION SCOPED           ;Enable local labels

                .386                    ;Enable 386 instruction set
                .MODEL FLAT,C           ;Flat memory model with C calls

                ;
                ;Equates
                ;

CHANNELS        equ 4                   ;Number of physical channels

                ;
                ;Macros
                ;

REP_MOVSB       MACRO
                push ecx
                and ecx,3
                rep movsb
                pop ecx
                shr ecx,2
                rep movsd
                ENDM

REP_STOSB       MACRO
                push ecx
                and ecx,3
                rep stosb
                pop ecx
                shr ecx,2
                rep stosd
                ENDM

                ;
                ;Sound channel structure
                ;

MODSPEC         STRUC

sound           dd ?            ;segment of sound mod. (on paragraph boundary!)
sndloc          dd ?            ;Offset portion, currently at.
sndlen          dd ?            ;Length of this mod sample.
silence         dd ?            ;Amount of silence, between samples.
silout          dd ?            ;Number of silence samples remaining from before.
oneshot         dd ?            ;True if sample is one shot.
trigger         dd ?            ;True if sample is to be triggered.
buff            dd ?            ;address of buffer stream being built.
bufflen         dd ?            ;Length of output buffer.
emshandle       dd ?            ;(Unused)

MODSPEC         ENDS

                ;
                ;Global data
                ;

                .DATA

WorkMod         MODSPEC <>      ;Working modspec area, current mod.

div_3           LABEL BYTE      ;Table of (n / 3), n=[0,255*3]
INDEX           = 0
                REPT 256
                db INDEX
                db INDEX
                db INDEX
INDEX           = INDEX + 1
                ENDM

                ;
                ;Code
                ;

                .CODE

                ASSUME eax:NOTHING
                ASSUME ebx:NOTHING
                ASSUME edi:NOTHING
                ASSUME esi:NOTHING

;****************************************************************************
BuildModStream  PROC C USES ebx esi edi es,\
                MODS:DWORD

                cld
                push ds
                pop es

                mov esi,[MODS]                  ;make working copy of MOD
                mov edi,OFFSET WorkMod          ;structure
                mov ecx,SIZE WorkMod
                REP_MOVSB

                mov ebx,WorkMod.sound           ;get base input location
                add ebx,WorkMod.sndlen          ;EBX -> end of input +1

                mov esi,WorkMod.sndloc          ;ESI -> current input location

                mov edi,WorkMod.buff            ;EDI -> buffer being built

                mov ecx,WorkMod.bufflen         ;ECX = len of output stream

                cmp WorkMod.trigger,0           ;channel active?
                je __empty                      ;no

                cmp WorkMod.oneshot,0           ;is this a one-shot sample?
                je __not_oneshot                ;no

__empty:        push edi
                push ecx

                mov al,80h                      ;(unsigned PCM silence byte)

                ALIGN 4
__build_null:   mov [edi],al                    ;build null buffer
                add edi,CHANNELS                ;skip to next entry
                dec ecx
                jnz __build_null

                pop ecx
                pop edi

                cmp WorkMod.trigger,0           ;channel active?
                je __done                       ;no, we're done

__not_oneshot:

                ;
                ;ESI ->source mod address
                ;EDI ->destination buffer address
                ;ECX = number of bytes in destination buffer to fill
                ;EBX = ending mod offset
                ;

__silence_test: mov edx,WorkMod.silout          ;any silence remaining?
                or edx,edx
                jz __silence_done               ;no, send data directly

                mov al,80h                      ;else write silence

                ALIGN 4
__do_silence:   mov [edi],al                    ;build null buffer
                add edi,CHANNELS                ;skip to next entry
                dec edx
                jz __silence_done
                dec ecx
                jnz __do_silence
           
                mov WorkMod.silout,edx          ;update silence remaining
                jmp __done

__silence_done: mov WorkMod.silout,0            ;mark silence finished
                xor eax,eax                     ;zero EAX

                ALIGN 4
__write_chan:   mov al,[esi]                    ;get source byte
                inc esi                         ;advance source index
                mov [edi],al                    ;store it
                add edi,CHANNELS
                cmp esi,ebx                     ;past end of mod?
                je __wrap                       ;yes
                dec ecx
                jnz __write_chan
                jmp __done

__wrap:         mov esi,WorkMod.sound           ;restore base address

                mov eax,WorkMod.silence
                mov WorkMod.silout,eax

                cmp WorkMod.oneshot,1
                jne __silence_test

                mov WorkMod.trigger,0

__done:         mov ebx,[MODS]                  ;update user copy of mod

                mov eax,WorkMod.silout
                mov [ebx].MODSPEC.silout,eax    ;silence remaining

                mov [ebx].MODSPEC.sndloc,esi    ;current mod location

                mov eax,WorkMod.trigger
                mov [ebx].MODSPEC.trigger,eax

                ret
BuildModStream  ENDP

;****************************************************************************
ModSilence      PROC C USES ebx esi edi es,\
                MOD1:DWORD,DEST:DWORD

                cld
                push ds
                pop es

                mov esi,[MOD1]
                mov ecx,[esi].MODSPEC.bufflen

                mov edi,[DEST]

                mov eax,80808080h               ;(unsigned PCM silence)
                REP_STOSB

                ret
ModSilence      ENDP

;****************************************************************************
MergeMod1       PROC C USES ebx esi edi es,\
                MOD1:DWORD,DEST:DWORD

                cld
                push ds
                pop es

                mov esi,[MOD1]
                mov ecx,[esi].MODSPEC.bufflen

                jcxz __exit

                mov edi,[DEST]
                mov esi,[esi].MODSPEC.buff

__OK:           mov al,[esi]
                mov [edi],al

                inc edi
                add esi,CHANNELS

                dec ecx
                jnz __OK

__exit:         ret
MergeMod1       ENDP

;****************************************************************************
MergeMod2       PROC C USES ebx esi edi es,\
                MOD1:DWORD,DEST:DWORD

                cld
                push ds
                pop es

                mov esi,[MOD1]
                mov ecx,[esi].MODSPEC.bufflen

                jcxz __exit

                mov edi,[DEST]
                mov esi,[esi].MODSPEC.buff

                xor ax,ax
                xor dx,dx

__OK:           mov al,[esi]            ;get all 2 channels of data
                mov dl,[esi+1]
                
                add ax,dx               ;do average
                shr ax,1

                mov [edi],al            ;store result

                add si,CHANNELS         ;advance source
                inc edi                 ;advance dest

                dec ecx                 ;...for all samples
                jnz __OK

__exit:         ret
MergeMod2       ENDP

;****************************************************************************
MergeMod3       PROC C USES ebx esi edi es,\
                MOD1:DWORD,DEST:DWORD

                cld
                push ds
                pop es

                mov esi,[MOD1]
                mov ecx,[esi].MODSPEC.bufflen

                jcxz __exit

                mov edi,[DEST]
                mov esi,[esi].MODSPEC.buff

                xor ax,ax
                xor dx,dx

__OK:           mov ebx,[esi]           ;get all 3 channels of data
                mov eax,OFFSET div_3    ;div_3 table base address

                mov dl,bl               ;sum low byte
                add eax,edx

                mov dl,bh               ;sum high byte
                add eax,edx

                shr ebx,16              ;shift to next word

                mov dl,bl               ;sum low byte
                add eax,edx

                mov al,[eax]            ;divide by 3
                mov [edi],al            ;store result

                add esi,CHANNELS        ;advance source
                inc edi                 ;advance dest

                dec ecx                 ;...for all samples
                jnz __OK

__exit:         ret
MergeMod3       ENDP

;****************************************************************************
MergeMod4       PROC C USES ebx esi edi es,\
                MOD1:DWORD,DEST:DWORD

                cld
                push ds
                pop es

                mov esi,[MOD1]
                mov ecx,[esi].MODSPEC.bufflen

                jcxz __exit

                mov edi,[DEST]
                mov esi,[esi].MODSPEC.buff

                xor ax,ax
                xor dx,dx

__OK:           mov ebx,[esi]           ;get all 3 channels of data
                xor eax,eax             ;zero accumulator

                mov dl,bl               ;sum low byte
                add eax,edx

                mov dl,bh               ;sum high byte
                add eax,edx

                shr ebx,16              ;shift to next word

                mov dl,bl               ;sum low byte
                add eax,edx

                mov dl,bh               ;sum high byte
                add eax,edx

                shr eax,2               ;divide by 4
                mov [edi],al            ;store result

                add esi,CHANNELS        ;advance source
                inc edi                 ;advance dest

                dec ecx                 ;...for all samples
                jnz __OK

__exit:         ret
MergeMod4       ENDP
                END

