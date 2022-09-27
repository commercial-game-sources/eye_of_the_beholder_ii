//
//  Run-time graphics subs
//

#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef __cplusplus
extern "C" {
#endif

extern UBYTE *fade_tables[5][16];
extern UWORD first_color[5];
extern UWORD in_GIL;

//#define MODE_X 1                 // 1 for VGA mode X, 0 for MCGA mode 13h

#define NTW 32                   // # of text windows available

void cdecl dprint(LONG argcnt, BYTE *format, ...);
void cdecl sprint(LONG argcnt, ULONG wndnum, BYTE *format, ...);
void cdecl text_color(LONG argcnt, ULONG wndnum, ULONG current, ULONG new);
void cdecl release_owned_windows(LONG owner);

#ifdef __cplusplus
}
#endif

#endif

