//????????????????????????????????????????????????????????????????????????????
//??                                                                        ??
//??  MOUSE.H: C type definitions & mouse API prototypes                    ??
//??                                                                        ??
//??  Source compatible with 32-bit 80386 C/C++                             ??
//??                                                                        ??
//??  V1.00 of  9-Jul-93: Initial release                                   ??
//??                                                                        ??
//??  Project: 386FX Sound & Light(TM)                                      ??
//??   Author: John Miles                                                   ??
//??                                                                        ??
//????????????????????????????????????????????????????????????????????????????
//??                                                                        ??
//??  Copyright (C) 1993 Miles Design, Inc.                                 ??
//??                                                                        ??
//??  Miles Design, Inc.                                                    ??
//??  6702 Cat Creek Trail                                                  ??
//??  Austin, TX 78731                                                      ??
//??                                                                        ??
//??  (512) 345-2642 / FAX (512) 338-9630 / BBS (512) 454-9990              ??
//??                                                                        ??
//????????????????????????????????????????????????????????????????????????????

#ifndef MOUSE_H
#define MOUSE_H

#ifndef VFX_H
#include "vfx.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern LONG mouse_init(LONG xsize, LONG ysize);
extern void mouse_shutdown(void);

extern void mouse_show(void);
extern void mouse_hide(void);
extern void mouse_set_pointer(void *table, LONG shape, LONG uhot_x, LONG uhot_y);

extern void mouse_register_mouse_event_callback(void cdecl (*fn)
   (LONG x, LONG y));
extern void mouse_register_button_event_callback(void cdecl (*fn)
   (LONG left, LONG right, LONG center));
extern void mouse_register_watchdog_callback(LONG cdecl (*fn)
   (RECT *area));

extern void mouse_lock(void);
extern void mouse_unlock(void);
extern void mouse_hold(void);
extern void mouse_release(void);

extern LONG mouse_visible_area(RECT *area);
extern LONG mouse_shape_in_area(RECT *area);

extern void cdecl mouse_serve(void);

extern void mouse_window_refresh(WINDOW *target, LONG x0, LONG y0, 
   LONG x1, LONG y1);

extern void mouse_pane_refresh(PANE *source, PANE *target);

#ifdef __cplusplus
}
#endif

#endif
