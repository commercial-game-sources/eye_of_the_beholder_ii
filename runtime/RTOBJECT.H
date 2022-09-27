//
//  Run-time object management
//

#ifndef RTOBJECT_H
#define RTOBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
   UWORD slot;       // object list index
   ULONG name;       // code object name
   UWORD size;       // size of instance data (unused in text files)
}
CDESC;               // static context descriptor

#define SF_TXT 1     // text savetype
#define SF_BIN 0     // binary savetype
                  
extern UBYTE objflags[NUM_OBJECTS];
extern HRES objlist[NUM_OBJECTS];

extern BYTE lvlmap[LVL_X][LVL_Y];
extern WORD lvlobj[3][LVL_X][LVL_Y];

void cdecl init_object_list(void);

void cdecl restore_range(BYTE *filename, ULONG first, ULONG last, ULONG restoring);
LONG cdecl save_range(BYTE *filename, ULONG filetype, ULONG first, ULONG last);
void cdecl translate_file(BYTE *TXT_filename, BYTE *BIN_filename, ULONG first,
   ULONG last);

LONG cdecl create_object(LONG argcnt, ULONG name);
LONG cdecl create_program(LONG argcnt, LONG index, ULONG name);
LONG cdecl destroy_object(LONG argcnt, LONG index);

#ifdef __cplusplus
}
#endif

#endif

