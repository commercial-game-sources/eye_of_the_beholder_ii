//
//  Run-time interface subs
//

#ifndef INTRFACE_H
#define INTRFACE_H

#ifdef __cplusplus
extern "C" {
#endif

extern LONG wait_ptr_state;

void cdecl init_interface(void);
void cdecl shutdown_interface(void);
void cdecl standby_cursor(void);
void cdecl resume_cursor(void);
void cdecl lock_mouse(void);
void cdecl unlock_mouse(void);
void cdecl show_mouse(void);
void cdecl hide_mouse(void);
void cdecl copy_mouse(int window);
ULONG cdecl mouse_in_window(LONG argcnt, ULONG wnd);
void cdecl refresh_window(LONG argcnt, ULONG src, ULONG target);

#ifdef __cplusplus
}
#endif

#endif

