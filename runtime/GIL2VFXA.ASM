;ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл                                                                         лл
;лл  GIL2VFXA.ASM                                                           лл
;лл                                                                         лл
;лл  VFX compatible GIL routines                                            лл
;лл                                                                         лл
;лл  Version 1.00 of 10-Aug-93: Initial version                             лл
;лл                                                                         лл
;лл  Project: Extensible State-Object Processor (AESOP/32)                  лл
;лл  Authors: John Miles, John Lemberger                                    лл
;лл                                                                         лл
;лл  8086/80386 ASM source compatible with MASM v6.0 or later               лл
;лл  C function prototypes in PFADE.H                                       лл
;лл                                                                         лл
;ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл                                                                         лл
;лл  Copyright (C) 1993 Miles Design, Inc.                                  лл
;лл                                                                         лл
;лл  Miles Design, Inc.                                                     лл
;лл  10926 Jollyville #308                                                  лл
;лл  Austin, TX 78759                                                       лл
;лл  (512) 345-2642 / BBS (512) 454-9990                                    лл
;лл                                                                         лл
;ллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл

                .386P                   ;Enable 386 instruction set
                .MODEL FLAT,C           ;Flat Memory Model and C calling

                INCLUDE vfx.inc

                ;
                ;VGA register equates for XVA manipulation
                ;

SC_INDEX        equ 3c4h
MAP_MASK        equ 02h                 

                ;
                ;BASCALC: DI -> address of point (x,y) in primary window
                ;Disposable: AX (usable as parameter),DX
                ;

BASCALC         MACRO pt_x,pt_y
                LOCAL mul_320,end_calc
                mov edi,pt_x
                sub edi,x1_p1           ;;normalize against parent's left X 
                mov edx,pt_y
                sub edx,y1_p1           ;;normalize against parent's top Y 
                mov eax,width_p1
                cmp eax,320
                je mul_320
                mul edx                 ;;multiply Y by buffer width
                add edi,eax
                jmp end_calc
mul_320:        xchg dl,dh              ;;fast mult for screen or staging page
                add edi,edx               
                shr edx,2                
                add edi,edx             ;;DI=X+320*Y (256*Y+64*Y)
end_calc:     
                ENDM

                ;
                ;BASCALC_2: DI -> address of point (x,y) in secondary window
                ;Disposable: AX,DX
                ;
     
BASCALC_2       MACRO pt_x,pt_y
                LOCAL mul_320,end_calc
                mov edi,pt_x
                sub edi,x1_p2           ;;normalize against parent's left X 
                mov edx,pt_y
                sub edx,y1_p2           ;;normalize against parent's top Y 
                mov eax,width_p2
                cmp eax,320
                je mul_320
                mul edx                 ;;multiply Y by buffer width
                add edi,eax
                jmp end_calc
mul_320:        xchg dl,dh              ;;fast mult for screen or staging page
                add edi,edx               
                shr edx,2                
                add edi,edx             ;;DI=X+320*Y (256*Y+64*Y)
end_calc:     
                ENDM

                ;
                ;SETWND: Copy window and parent to primary window area
                ;Disposable: AX,BX,CX
                ;

SETWND          MACRO handle
                LOCAL find_parent,parent_found
                mov ebx,handle
                mov ecx,[ebx].PANE.x0
                mov x1_1,ecx
                mov eax,[ebx].PANE.y0
                mov y1_1,eax
                mov eax,[ebx].PANE.x1
                mov x2_1,eax
                sub eax,ecx
                inc eax
                mov width_1,eax
                mov eax,[ebx].PANE.y1
                mov y2_1,eax
                sub eax,y1_1
                inc eax
                mov height_1,eax

                mov ebx,[ebx].PANE.win
                mov eax,[ebx].WINDOW.wnd_y0
                mov y1_p1,eax
                mov eax,[ebx].WINDOW.wnd_y1
                mov y2_p1,eax
                sub eax,y1_p1
                inc eax
                mov height_p1,eax
                mov ecx,[ebx].WINDOW.wnd_x0
                mov x1_p1,ecx
                mov eax,[ebx].WINDOW.wnd_x1
                mov x2_p1,eax
                sub eax,ecx
                inc eax
                mov width_p1,eax         
                
                ENDM
                ;
                ;SETWND2: Copy window and parent to primary window area
                ;Disposable: AX,BX,CX
                ;

SETWND2         MACRO handle
                LOCAL find_parent,parent_found
                mov ebx,handle
                mov ecx,[ebx].PANE.x0
                mov x1_2,ecx
                mov eax,[ebx].PANE.y0
                mov y1_2,eax
                mov eax,[ebx].PANE.x1
                mov x2_2,eax
                sub eax,ecx
                inc eax
                mov width_2,eax
                mov eax,[ebx].PANE.y1
                mov y2_2,eax
                sub eax,y1_2
                inc eax
                mov height_2,eax

                mov ebx,[ebx].PANE.win
                mov eax,[ebx].WINDOW.wnd_y0
                mov y1_p2,eax
                mov eax,[ebx].WINDOW.wnd_y1
                mov y2_p2,eax
                sub eax,y1_p2
                inc eax
                mov height_p2,eax
                mov ecx,[ebx].WINDOW.wnd_x0
                mov x1_p2,ecx
                mov eax,[ebx].WINDOW.wnd_x1
                mov x2_p2,eax
                sub eax,ecx
                inc eax
                mov width_p2,eax         
                
                ENDM

                ;
                ;SET_TW: Make locally-accessible copy of current text window
                ;Disposable: CX,ES,SI,DI; sets DF=0
                ;

SET_TW          MACRO
                cld
                mov esi,twptr
                mov edi,OFFSET tw
                mov ecx,(SIZE textwindow)/4
                rep movsd
                IF (SIZE textwindow) AND 2
                movsw
                ENDIF
                IF (SIZE textwindow) AND 1
                movsb
                ENDIF
                ENDM



textwindow      STRUC                   ;Text window structure
window          dd ?                  
htab            dd ?
vtab            dd ?
font            dd ?
delay           dd ?
continueFunct   dd ?
txtbuf          dd ?
txtpnt          dd ?
justify         dd ?
lookaside       db 256 dup (?)
textwindow      ENDS


GIL2VFXA_cout    PROTO C,twpane:PPANE, Char:DWORD

                EXTERN  VFX_wait_vblank_leading:NEAR
                EXTERN  GIL2VFX_char_width:NEAR
                EXTERN  VFX_character_width:NEAR
                EXTERN  GIL2VFX_cout:NEAR
                EXTERN  GIL2VFX_scroll_window:NEAR
                EXTERN  in_BIOS:DWORD
                EXTERN  twptr:PTR
                

;*****************************************************************************

                .CODE

;*****************************************************************************

                PUBLIC  GIL2VFXA_print_buffer
                PUBLIC  GIL2VFXA_cout

                PUBLIC  eop_reached   
                PUBLIC  pending_flag    


;Copy of primary window element
x1_1            dd ?
y1_1            dd ?
x2_1            dd ?
y2_1            dd ?                               
width_1         dd ?
height_1        dd ?

;Copy of primary element's parent
x1_p1           dd ?
y1_p1           dd ?
x2_p1           dd ?
y2_p1           dd ?
width_p1        dd ?                    ;Parent buffer's byte width
height_p1       dd ?                    ;"" height in lines

;Copy of secondary window element
x1_2            dd ?
y1_2            dd ?
x2_2            dd ?
y2_2            dd ?
width_2         dd ?
height_2        dd ?

;Copy of secondary element's parent
x1_p2           dd ?
y1_p2           dd ?
x2_p2           dd ?
y2_p2           dd ?
width_p2        dd ?                    ;Parent buffer's byte width
height_p2       dd ?                    ;"" height in lines

src_ytable      dd 200 dup (?)
dest_ytable     dd 200 dup (?)

twpptr          dd ?
tw              textwindow <>           ;Copy of current text window struct

eop_reached     dd ?
pending_flag    dd ?

pending_lines   dd ?
line_beg        dd ?
line_end        dd ?
w_lin           dd ?
w_win           dd ?
quotient        db ?
remainder       db ?
bmap_height     dd ?   

;*****************************************************************************
GIL2VFXA_print_buffer    PROC C USES es esi edi, \
                twpane:PPANE,LineNum

                mov eax,[twpane]
                mov twpptr,eax

                SET_TW                
                SETWND twpptr

                mov eax,[LineNum]
                mov pending_flag,eax    ;non-zero if pending lines
                dec eax
                mov pending_lines,eax   ;# of lines still pending
                mov eop_reached,0       ;goes true if cout() hits end-of-page

                mov ebx,tw.txtbuf
                push ebp
                xor ebp,ebp

__do_line:      cmp pending_flag,0      ;was linecount parameter nonzero?
                je __update_tw          ;no
                cmp eop_reached,1       ;was end-of-page reached in cout()?
                jae __done              ;yes, terminate buffer dump

__update_tw:    
                SET_TW                  ;update local copy of text window data
                mov esi,ebp
                mov line_beg,ebp

                cmp BYTE PTR [ebx][esi],0
                je __eol_found
__find_eol:     mov al,[esi][ebx]       ;find end of first "word"
                inc esi
                or al,al                ;end of string?
                jz __eol_found
                cmp al,10               ;line feed?
                je __eol_found  
                cmp al,' '              ;space?
                jne __find_eol
                dec esi                 ;yes, back up one
__eol_found:    mov line_end,esi

                mov edi,tw.htab         ;now find bounds of entire line....
                mov esi,ebp
__lscan:        xor eax,eax
                mov al,[ebx][esi]
                or al,al
                jz __end_scan
                cmp al,10
                je __end_scan
                cmp al,' '
                jne __same_word
                mov line_end,esi
__same_word:    inc esi
                push ebx
                push eax
                push tw.font
                call VFX_character_width
                add esp,8
                pop ebx
                add edi,eax
                mov ecx,x2_1
                inc ecx
                cmp edi,ecx
                jg __w_remaining      
                jmp __lscan
__end_scan:     inc esi
                mov line_end,esi
__w_remaining:  mov eax,x2_1
                sub eax,tw.htab
                inc eax                 ;w_win = # of pixels remaining in
                mov w_win,eax           ;window line 
                mov w_lin,0             
                mov esi,line_beg
__sum_chars:    cmp esi,line_end        ;sum total width of line in w_lin
                je __write_line         
                xor eax,eax
                mov al,[ebx][esi]
                push ebx
                push eax
                push tw.font
                call VFX_character_width
                add esp,8
                pop ebx
                add w_lin,eax
                inc esi
                jmp __sum_chars

__write_line:   cmp pending_flag,0      ;line counter active?
                je __not_pending        ;no, continue normally
                cmp pending_lines,0     ;any pending lines?
                je __not_pending        ;no, write this one and continue
                dec pending_lines       ;yes, dec counter and fetch next line
                mov ebp,line_end
                cmp BYTE PTR [ebx][esi-1],0     
                je __done               ;(if there IS a next line)
                jmp __next_line

__not_pending:  mov edi,tw.justify
                shl edi,2
;                and edi,7
                mov esi,line_beg
                jmp output_handlers[edi]

__handler_return:
                mov esi,line_end        ;do cr/lf after line if necessary
                mov ebp,esi
                mov ebx,tw.txtbuf
                mov al,[ebx][esi-1]     ;look at last character printed
                or al,al                ;end of buffer, exit
                je __done
                cmp al,10               
                je __do_line            ;explicit linefeed, already printed
                push ebx
                mov ebx,10
                push ebx
;                push twpptr
;                invoke GIL2VFXA_cout,twpptr,ebx        ;else do line feed
                call GIL2VFX_cout       ;else do line feed
                add esp,4
                pop ebx
__next_line:    mov esi,ebp               
__spc_clip:     cmp BYTE PTR [ebx][esi],' '
                jne __go_nxtlin         ;and skip next line's trailing spaces
                inc esi        
                jmp __spc_clip
__go_nxtlin:    mov ebp,esi
                jmp __do_line

__done:         mov pending_flag,0      ;turn off cout() override flag
                pop ebp
                ret

;-----------------------------------------------------------------------------
out_l:          mov esi,line_beg        ;justify left margin
__do_char:      cmp esi,line_end         
                jae __donel
                mov ebx,tw.txtbuf
                movzx eax,BYTE PTR [ebx][esi]
                or al,al
                jz __donel
                xor ah,ah
                push eax
                call GIL2VFX_cout
                add esp,4
                inc esi
                jmp __do_char
__donel:        jmp __handler_return

;-----------------------------------------------------------------------------
out_c:          mov eax,w_win           ;center line in window
                sub eax,w_lin
                jbe out_l
                cmp BYTE PTR [ebx][esi],0   
                je out_l
                inc eax
                shr eax,1
                mov ebx,twptr
                add [ebx].textwindow.htab,eax
                jmp out_l

;-----------------------------------------------------------------------------
out_r:          mov ecx,x1_1            ;justify right margin
                mov eax,w_lin            
                cmp eax,w_win
                ja __set_htab
                cmp BYTE PTR [ebx][esi],0   
                je __set_htab
                mov ecx,x2_1
                sub ecx,w_lin
                inc ecx
__set_htab:     mov ebx,twptr
                mov [ebx].textwindow.htab,ecx
                jmp out_l

;-----------------------------------------------------------------------------
out_f:          mov eax,w_lin           ;justify both margins
                cmp eax,w_win
                jae out_l
                mov esi,line_end
                cmp BYTE PTR [ebx][esi-1],0
                je out_l
                cmp BYTE PTR [ebx][esi-1],10
                je out_l                ;don't fill last or truncated line
__lead_spc:     mov esi,line_beg
                cmp BYTE PTR [ebx][esi],' '
                jne __first_word
                mov ebx,' '
                push ebx
;                push twpptr
;                invoke GIL2VFXA_cout,twpptr,ebx
                call GIL2VFX_cout
                add esp,4

                mov ebx,' '
                push ebx
                push tw.font
                call VFX_character_width
                add esp,8

                mov ebx,tw.txtbuf
                sub w_lin,eax
                inc line_beg
                jmp __lead_spc
__first_word:   mov esi,line_beg        ;write first word normally...
                movzx eax,BYTE PTR [ebx][esi]
                cmp al,' '
                je __get_pad
                xor ah,ah
                mov edi,eax
                push edi
;                push twpptr
;                invoke GIL2VFXA_cout,twpptr,edi
                call GIL2VFX_cout
                add esp,4

                push edi
                push tw.font
                call VFX_character_width
                add esp,8

                sub w_lin,eax
                mov ebx,tw.txtbuf
                inc line_beg
                jmp __first_word
__get_pad:      mov ebx,twptr           ;get # of pixels left to pad
                mov eax,x2_1
                sub eax,[ebx].textwindow.htab
                inc eax
                sub eax,w_lin
                mov ebx,tw.txtbuf
                xor ecx,ecx
                mov esi,line_beg
__wcount:       cmp esi,line_end        ;get # of words left in line
                jae __calc_pad
                cmp BYTE PTR [ebx][esi],' '
                jne __next_wc
                inc ecx
__next_wc:      inc esi
                jmp __wcount
__calc_pad:     or ecx,ecx
                je out_l
                or ch,ch                        
                jne out_l
                div cl                  ;divide to calculate padding
                mov quotient,al         ;per word
                mov remainder,ah

                mov esi,line_beg         ;dump the line....
__do_charf:     mov ebx,tw.txtbuf
                cmp esi,line_end
                jae __donef
                movzx eax,BYTE PTR [ebx][esi]
                or al,al
                jz __donef
                xor ah,ah
                push eax
                push eax
;                push twpptr
;                invoke GIL2VFXA_cout,twpptr,eax
                call GIL2VFX_cout
                add esp,4

                pop eax
                cmp al,' '              ;end of word?
                jne __next_char
                mov al,quotient         ;yes, bump htab for padding
                mov ebx,twptr
                add [ebx].textwindow.htab,eax
                cmp remainder,0
                je __next_char
                inc [ebx].textwindow.htab
                dec remainder
__next_char:    inc esi
                jmp __do_charf
__donef:        jmp __handler_return

;-----------------------------------------------------------------------------

output_handlers dd out_l,out_r,out_c,out_f

GIL2VFXA_print_buffer    ENDP

;*****************************************************************************
GIL2VFXA_cout    PROC C USES es esi edi, \
                twpane:PPANE, Char

                SET_TW                
                SETWND [twpane]
                
                mov eax,[Char]
                cmp eax,10                      ;line feed?
                je __LF
                cmp eax,13                      ;carriage return?
                je __CR

                mov ebx,tw.font                 ;set BX to index font header
                cmp eax,[ebx].FONT.char_count
                jae __cout_done                 ;invalid character
                mov eax,[ebx].FONT.char_height
                mov bmap_height,eax             ;else init height counter
                
                mov esi,[Char]
                shl esi,2
                add esi,ebx
                mov esi,[esi+16]
                add esi,ebx

                mov ecx,[esi]                   ;get character width
                jcxz __cout_almost_done         ;width = 0, nothing to draw
                add esi,4
                jmp __cout_not_done
__cout_almost_done:
                jmp __cout_done
__cout_not_done:

                mov eax,ecx
                add eax,tw.htab
                dec eax                         ;AX=last pixel column in char
                cmp eax,x2_1                    ;enough room on current line?
                jle __draw_char                 ;yes, draw it

                push ebx                        ;else do cr/lf before printing
                push ecx        
                push esi
                call lfout
                pushf
                SET_TW                          ;refresh local window struct
                popf                            ;with new data
                pop esi                         ;if C=1, user's continueFunc() 
                pop ecx
                pop ebx

                jc __cout_done                  ;returned 0 -- don't print

__draw_char:    
                BASCALC tw.htab,tw.vtab         ;get initial buffer address

                mov edx,ecx                     ;save width counter
;                cmp [ebx].remap_flag,0          ;any font colors remapped?
;                jne __remapped                  ;yes, translate colors...
;
;__unmapped_row: mov eax,edi                     ;no, draw character with 
;                rep movsb                       ;default colors at maximum
;                mov edi,eax                     ;speed...
;                mov ecx,edx
;                add edi,width_p1                ;(typical char width too small
;                dec bmap_height                 ;to make 16-bit move sequence
;                jnz __unmapped_row              ;worthwhile)
;                jmp __adjust_htab

__remapped:     push ebp
                mov ebp,edi                     ;draw remapped character...
                add ebx,OFFSET tw.lookaside     ;DS:BX -> tw's lookaside
                inc ecx                                  
                dec edi
__transparent:  dec ecx                         ;entry point for transparent
                jz __next_remap                 ;pixels
                inc edi
__remap_pixel:  lodsb                           ;get a byte from the font
                xlat                            ;translate with color matrix
                cmp al,255                      ;(color 255 "transparent")
                je __transparent        
                stosb                           ;write translated color
                loop __remap_pixel              
__next_remap:   mov ecx,edx                     ;restore width counter
                add ebp,width_p1
                mov edi,ebp                     ;and target address
                pop ebp
                dec bmap_height
                jnz __remap_pixel               ;go do next row

__adjust_htab:  mov ebx,[twptr]
                add ecx,[ebx].textwindow.htab
                cmp ecx,x2_1                    ;keep htab inside window 
                jl __set_htab                   ;margins
                mov ecx,x2_1
__set_htab:     mov [ebx].textwindow.htab,ecx

                mov esi,[ebx].textwindow.delay
__for_delay:    cmp esi,0
                jz __cout_done
                call VFX_wait_vblank_leading
                dec esi
                jmp __for_delay

__CR:           call crout2
                ret
__LF:           call lfout
__cout_done:    ret
GIL2VFXA_cout    ENDP

;-----------------------------------------------------------------------------
crout2          PROC C                      ;output carriage return alone
                mov esi,twptr
                SETWND [esi].textwindow.window
                mov ecx,x1_1
                xchg [esi].textwindow.htab,ecx  ;return old htab in CX
                ret                         
crout2          ENDP

;-----------------------------------------------------------------------------
lfout           PROC                        ;output cr/lf pair
                call crout2                 ;(for internal use only
                mov ebx,[esi].textwindow.font
                mov eax,[esi].textwindow.vtab
                add eax,[ebx].FONT.char_height
                mov edx,eax                 ;DX=new vtab line if there's room
                add eax,[ebx].FONT.char_height     
                dec eax                     ;AX=bottom Y row of new vtab line
                cmp eax,y2_1
                jle __set_vtab              
                                             
                mov eax,[esi].textwindow.continueFunct
                or eax,0
                jz __scroll_norm            ;function NULL, don't call
                xchg [esi].textwindow.htab,ecx        
                push ecx                    ;set up to call continueFunction()
                call [esi].textwindow.continueFunct
                pop ecx                     ;get new htab (left margin) back
                or eax,eax
                stc                         ;if valid function returns 0, 
                jz __exit_lfout             ;return C=1, vtab/htab unchanged
                mov esi,twptr             
                mov ebx,[esi].textwindow.font   ;else restore regs and htab value
                mov [esi].textwindow.htab,ecx             

__scroll_norm:  cmp pending_flag,0          ;doing a print_buffer(>0) call?
                je __scroll_wnd             ;no, proceed normally
                inc eop_reached             ;yes, signal end-of-page....
                stc                         ;and abort further output
                jmp __exit_lfout 

__scroll_wnd:   mov eax,[ebx].FONT.char_height
                neg eax

                push [ebx].FONT.font_background
                push 0
                push eax
                push 0
                push [esi].textwindow.window
                call GIL2VFX_scroll_window
                add esp,20

                mov esi,twptr
                SETWND [esi].textwindow.window  ;restore window data
                clc                         ;return C=0 if window scrolled 
__exit_lfout:   ret

__set_vtab:     mov [esi].textwindow.vtab,edx      
                clc                         ;return C=0 if no scrolling needed
                ret
lfout           ENDP

                END
