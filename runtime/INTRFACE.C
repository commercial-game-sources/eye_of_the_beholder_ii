//????????????????????????????????????????????????????????????????????????????
//??                                                                        ??
//??  INTRFACE.C                                                            ??
//??                                                                        ??
//??  AESOP user interface code resource handlers for Eye III engine        ??
//??                                                                        ??
//??  Version: 1.00 of 6-May-92 -- Initial version                          ??
//??                                                                        ??
//??  Project: Eye III                                                      ??
//??   Author: John Miles                                                   ??
//??                                                                        ??
//??  C source compatible with Borland C++ v3.0 or later                    ??
//??  Large memory model (16-bit DOS)                                       ??
//??                                                                        ??
//????????????????????????????????????????????????????????????????????????????
//??                                                                        ??
//??  Copyright (C) 1992 Miles Design, Inc.                                 ??
//??                                                                        ??
//??  Miles Design, Inc.                                                    ??
//??  10926 Jollyville #308                                                 ??
//??  Austin, TX 78759                                                      ??
//??  (512) 345-2642 / BBS (512) 454-9990 / FAX (512) 338-9630              ??
//??                                                                        ??
//????????????????????????????????????????????????????????????????????????????

#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "vfx.h"
#include "ail32.h"
#include "gil2vfx.h"
#include "gil2vfxa.h"
#include "mouse.h"

extern VFX_DESC *VFX;

#include "defs.h"
#include "shared.h"
#include "rtsystem.h"
#include "rtmsg.h"
#include "rtres.h"
#include "rtlink.h"
#include "rtcode.h"
#include "rt.h"
#include "intrface.h"
#include "event.h"
#include "graphics.h"

LONG interface_active = 0;

HTIMER htimer;
ULONG volatile heartbeat;
ULONG volatile in_BIOS;

ULONG cur_table;
ULONG cur_number;
LONG cur_hot_X;
LONG cur_hot_Y;

ULONG wait_number;
LONG wait_hot_X;
LONG wait_hot_Y;

ULONG save_number;
LONG save_hot_X;
LONG save_hot_Y;

LONG ptr_valid;
LONG wait_ptr_valid;
LONG wait_ptr_state;

HRES pointer_set;
ULONG pointer_set_entry;
ULONG pointer_num;
ULONG pointer_fade_table;
ULONG pointer_fade_level;
ULONG pointer_scale;
LONG last_cursor_X,last_cursor_Y;
LONG volatile point_X,point_Y;
LONG volatile btn_left,btn_right;
LONG volatile last_X,last_Y;
LONG volatile last_left,last_right;

typedef struct             // DPMI real-mode interrupt structure
{
   LONG edi;
   LONG esi;
   LONG ebp;
   LONG reserved;
   LONG ebx;
   LONG edx;
   LONG ecx;
   LONG eax;
   WORD flags;
   WORD es;
   WORD ds;
   WORD fs;
   WORD gs;
   WORD ip;
   WORD cs;
   WORD sp;
   WORD ss;
}
DPMI_RMI;


/*********************************************************/
void cdecl getkey(void)
{
   while (!find_event(SYS_KEYDOWN,-1L));

   remove_event(SYS_KEYDOWN,-1L,-1);
}

/*********************************************************/
void cdecl add_region_event(LONG type, LONG owner)
{
   WORD nxt;
   ULONG r;
   NREQ *NR;

   DISABLE();

   nxt = NR_first[type];
   while (nxt != -1)
      {
      NR = &NR_list[nxt];
      nxt = NR->next;
      r = NR->parameter;

      if (mouse_in_window(0,r))
         add_event(type,r,owner);
      }

   ENABLE();
}

/*********************************************************/
//
// AIL timer callback routine; check the keyboard buffer
// for incoming characters 60 times per second, and post SYS_TIMER 
// events to the event queue 30 times per second
//
// If a SYS_TIMER message is already in the queue, update its
// "heartbeat" parameter instead of posting a new message
//
// Don't update system heartbeat count while hourglass cursor is
// active
//
// If the keyboard buffer's head and tail pointers do not match,
// at least one character has been typed in the last 1/60 second.  Read
// the scan code and ASCII/extended code directly from the buffer, post
// a SYS_KEYDOWN event, and flush the buffer by manually equating its
// head and tail pointers
//
// Avoid manipulating keyboard buffer during execution of INT 9 handler
// (possible since IRQ 0/INT 8 has higher priority than IRQ 1/INT 9)
//
/*********************************************************/

static void cdecl timer_callback(void)   // Warning: called during IRQ 0
{
   EVENT *EV;
   unsigned key,scan,ascii;
   static UWORD *head =   (UWORD *) 0x41aL;
   static UWORD *tail =   (UWORD *) 0x41cL;
   static UWORD *buffer = (UWORD *) 0x41eL;

   if (ENABLED <= 0) return;

   if (wait_ptr_state <= 0)
      {
      ++heartbeat;

      if (!(heartbeat & 1L))
         if ((EV = find_event(SYS_TIMER,-1)) == NULL)
            add_event(SYS_TIMER,heartbeat >> 1,-1);
         else
            EV->parameter = heartbeat >> 1;
      }

   if ((*head != *tail) && (!in_BIOS))
      {
      key = buffer[((*head) - 0x1e) / 2];
      *head = *tail;

      ascii = key & 0xff;
      scan = key >> 8;

      if ((key == KP_5) || (ascii == 0) || (ascii == 0xe0))
         add_event(SYS_KEYDOWN,key,-1);
      else
         add_event(SYS_KEYDOWN,ascii,-1);
      }
}

/*********************************************************/
static void cdecl mouse_event_handler(LONG px, LONG py)
{
   static LONG entry = 0;
   WORD nxt;
   LONG r;
   NREQ *NR;
   EVENT *EV;

   if (entry) return;
   entry = 1;

   point_X = px;
   point_Y = py;

   if ((EV = find_event(SYS_MOUSEMOVE,-1L)) == NULL)
      add_event(SYS_MOUSEMOVE,((ULONG) point_Y << 16) | (ULONG) point_X,-1);
   else
      EV->parameter = ((ULONG) point_Y << 16) | (ULONG) point_X;

   nxt = NR_first[SYS_ENTER_REGION];
   while (nxt != -1)
      {
      NR = &NR_list[nxt];
      nxt = NR->next;
      r = NR->parameter;

      if (mouse_in_window(0,r))
         {
         if (NR->status & NSX_IN_REGION) continue;

         NR->status |= NSX_IN_REGION;

         add_event(SYS_ENTER_REGION,r,-1);
         }
      else
         NR->status &= (~NSX_IN_REGION);
      }

   nxt = NR_first[SYS_LEAVE_REGION];
   while (nxt != -1)
      {
      NR = &NR_list[nxt];
      nxt = NR->next;
      r = NR->parameter;

      if (!mouse_in_window(0,r))
         {
         if (!(NR->status & NSX_OUT_REGION)) continue;

         NR->status &= (~NSX_OUT_REGION);

         add_event(SYS_LEAVE_REGION,r,-1);
         }
      else
         NR->status |= NSX_OUT_REGION;
      }

   entry = 0;
}
/*********************************************************/
#pragma off (unreferenced)
static void cdecl mouse_button_event_handler(LONG left, LONG right, LONG center)
#pragma on (unreferenced)
{
   static LONG entry = 0;

   if (entry) return;
   entry = 1;

   btn_left = left;
   btn_right = right;

   if (btn_left != last_left)
      {
      add_event(btn_left ? SYS_CLICK : SYS_RELEASE,0,-1);
      add_event(btn_left ? SYS_LEFT_CLICK : SYS_LEFT_RELEASE,0,-1);
      add_region_event(btn_left ?
         SYS_LEFT_CLICK_REGION : SYS_LEFT_RELEASE_REGION,-1);
      add_region_event(btn_left ?
         SYS_CLICK_REGION : SYS_RELEASE_REGION,-1);

      last_left = btn_left;
      }

   if (btn_right != last_right)
      {
      add_event(btn_right ? SYS_CLICK : SYS_RELEASE,0,-1);
      add_event(btn_right ? SYS_RIGHT_CLICK : SYS_RIGHT_RELEASE,0,-1);
      add_region_event(btn_right ?
         SYS_RIGHT_CLICK_REGION : SYS_RIGHT_RELEASE_REGION,-1);
      add_region_event(btn_right ?
         SYS_CLICK_REGION : SYS_RELEASE_REGION,-1);

      last_right = btn_right;
      }

   entry = 0;
}

/*********************************************************/
void cdecl init_interface(void)
{
   union REGS inregs,outregs;

   in_BIOS = 0;
   heartbeat = 0L;

   inregs.w.ax = 0;
   int386(0x33,&inregs,&outregs);

   if (outregs.w.ax == 0xffff)
      {
      pointer_set = -1U;
      pointer_set_entry = -1L;
      ptr_valid = 0;
      wait_ptr_valid = 0;
      wait_ptr_state = 0;

      mouse_init(VFX->scrn_width, VFX->scrn_height);

      mouse_register_mouse_event_callback(mouse_event_handler);
      mouse_register_button_event_callback(mouse_button_event_handler);

      inregs.x.eax = 3;
      int386(0x33,&inregs,&outregs);

      point_X = last_X = last_cursor_X = outregs.w.cx >> 3;
      point_Y = last_Y = last_cursor_Y = outregs.w.dx >> 3;
      btn_left = last_left = outregs.w.bx & 1;
      btn_right = last_right  = outregs.w.bx & 2;
      }
   else
      {
      GIL2VFX_shutdown_driver();
      abend(MSG_MMR);
      }

   htimer = AIL_register_timer(timer_callback);
   AIL_set_timer_frequency(htimer,60);
   AIL_start_timer(htimer);

   interface_active = 1;
}

/*********************************************************/
void cdecl shutdown_interface(void)
{
   union REGS inregs,outregs;

   if (!interface_active) return;
   interface_active = 0;

   AIL_release_timer_handle(htimer);

   hide_mouse();

   mouse_shutdown();

   inregs.w.ax = 0;
   int386(0x33,&inregs,&outregs);

   if (pointer_set != -1U)
      {
      RTR_unlock(pointer_set);
      }
}

/*********************************************************/
void cdecl set_mouse_pointer(LONG argcnt, ULONG table, ULONG number, LONG hot_X,
                             LONG hot_Y, ULONG scale, ULONG fade_table,
                             ULONG fade_level)
{
   ND_entry *entry;

   if ((wait_ptr_state != 0) && (argcnt != 0))
      {
      save_number = number;
      save_hot_X = hot_X;
      save_hot_Y = hot_Y;

      return;
      }

   cur_table = table;
   cur_number = number;
   cur_hot_X = hot_X;
   cur_hot_Y = hot_Y;

   if ((table == pointer_set_entry) &&
       (number == pointer_num) &&
       (scale == pointer_scale) &&
       (fade_table == pointer_fade_table) &&
       (fade_level == pointer_fade_level))
      return;

   if (table != pointer_set_entry)
      {
      if (pointer_set != -1U)
         {
         RTR_unlock(pointer_set);
         }

      if ((entry = RTR_search_name_dir(RTR,table)) == NULL)
         pointer_set = RTR_get_resource_handle(RTR,table,DA_DEFAULT);
      else
         pointer_set = entry->handle;

      RTR_lock(RTR,pointer_set);

      pointer_set_entry = table;
      }

   pointer_num = number;
   pointer_scale = scale;
   pointer_fade_table = fade_table;
   pointer_fade_level = fade_level;

   ptr_valid = 1;

   mouse_set_pointer(RTR_addr(pointer_set),pointer_num,hot_X,hot_Y);
}

/*********************************************************/
#pragma off (unreferenced)
void cdecl set_wait_pointer(LONG argcnt, ULONG number, LONG hot_X, LONG hot_Y)
#pragma on (unreferenced)
{
   if (number == -1L)
      {
      wait_ptr_valid = 0;
      return;

      }

   wait_number = number;
   wait_hot_X = hot_X;
   wait_hot_Y = hot_Y;

   wait_ptr_valid = 1;
}

/*********************************************************/
void cdecl standby_cursor(void)
{
   if (!wait_ptr_valid) return;
   if (!ptr_valid) return;

   ++wait_ptr_state;

   if (wait_ptr_state == 1)
      {
      save_number = cur_number;
      save_hot_X = cur_hot_X;
      save_hot_Y = cur_hot_Y;

      set_mouse_pointer(0,cur_table,wait_number,wait_hot_X,wait_hot_Y,
         pointer_scale,pointer_fade_table,pointer_fade_level);
      }
}

/*********************************************************/
//
// Turn off hourglass cursor
//
/*********************************************************/

void cdecl resume_cursor(void)
{
   if (!wait_ptr_valid) return;
   if (!ptr_valid) return;

   --wait_ptr_state;

   if (wait_ptr_state == 0)
      set_mouse_pointer(0,cur_table,save_number,save_hot_X,save_hot_Y,
         pointer_scale,pointer_fade_table,pointer_fade_level);
}

/*********************************************************/
//
// Disable mouse tracking
//
/*********************************************************/

void cdecl lock_mouse(void)
{
   mouse_lock();
}

/*********************************************************/
//
// Enable normal mouse tracking
// 
// Do a hide/show cycle in case the mouse was moved while locked
// 
/*********************************************************/

void cdecl unlock_mouse(void)
{
   mouse_unlock();
}

/*********************************************************/
void cdecl show_mouse(void)
{
   mouse_show();
}

/*********************************************************/
void cdecl hide_mouse(void)
{
   mouse_hide();
}

/*********************************************************/
ULONG cdecl mouse_XY(void)
{
   ULONG xy;

   DISABLE();

   xy = ((ULONG) point_Y << 16) + point_X;

   ENABLE();

   return xy;
}

/*********************************************************/
//
// Warning: re-entrant
//
/*********************************************************/

#pragma off (unreferenced)
ULONG cdecl mouse_in_window(LONG argcnt, ULONG wnd)
#pragma on (unreferenced)
{
   ULONG stat;

   stat = ((point_X >= GIL2VFX_get_x1(wnd)) &&
           (point_X <= GIL2VFX_get_x2(wnd)) &&
           (point_Y >= GIL2VFX_get_y1(wnd)) &&
           (point_Y <= GIL2VFX_get_y2(wnd)));

   return stat;
}

/*********************************************************/
//
// Wrapper for GIL_copy_window() which handles cursor save/restore
//
// Target must be a subwindow of PAGE1
//
/*********************************************************/

#pragma off (unreferenced)
void cdecl refresh_window(LONG argcnt, ULONG src, ULONG target)
#pragma on (unreferenced)
{
   GIL2VFX_refresh_window(src, target);
}


void intrface_entry()
{
   // wvideo
}

