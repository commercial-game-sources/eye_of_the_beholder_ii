//
//  Run-time code resources
//

#ifndef RTCODE_H
#define RTCODE_H

#ifdef __cplusplus
extern "C" {
#endif

void cdecl diagnose(LONG argcnt, ULONG dtype, ULONG parm);

typedef void (cdecl *FARPROC)();
extern FARPROC code_resources[];

ULONG cdecl absv(LONG argcnt, LONG val);
ULONG cdecl rnd(LONG argcnt, ULONG low, ULONG high);
LONG cdecl envval(LONG argcnt, BYTE *name);

void cdecl beep(void);

#ifdef __cplusplus
}
#endif

#endif

