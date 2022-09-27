//
// AESOP interpreter system services
//

#ifndef RTSYSTEM_H
#define RTSYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#define TF_BUFSIZE 4096    // size of buffer allocated by file functions

typedef struct
{
   HRES hbuf;
   BYTE *buffer;
   WORD p;
   WORD file;
   WORD mode;
   LONG len;
   LONG pos;
}
TF_class;

#define TF_WRITE 0
#define TF_READ  1

#define isnum(x) (((x) == '-') || (((x) >= '0') && ((x) <= '9')))

//
// Universal disk error codes
//

#define NO_ERROR        0
#define IO_ERROR        1
#define OUT_OF_MEMORY   2
#define FILE_NOT_FOUND  3
#define CANT_WRITE_FILE 4
#define CANT_READ_FILE  5
#define DISK_FULL       6

//
// General file management
//

WORD cdecl copy_file(BYTE *src_filename, BYTE *dest_filename);
WORD cdecl delete_file(BYTE *filename);
ULONG cdecl file_time(BYTE *filename);

//
// Text file management
//

TF_class *cdecl TF_construct(BYTE *filename, WORD oflag);
WORD cdecl TF_destroy(TF_class *TF);
WORD cdecl TF_wchar(TF_class *TF, BYTE ch);
BYTE cdecl TF_rchar(TF_class *TF);
WORD cdecl TF_readln(TF_class *TF, BYTE *buffer, WORD maxlen);
WORD cdecl TF_writeln(TF_class *TF, BYTE *buffer);

//
// Binary file management
//

LONG file_size(BYTE *filename);
BYTE *cdecl read_file(BYTE *filename, void *dest);
WORD cdecl write_file(BYTE *filename, void *buf, ULONG len);
WORD cdecl append_file(BYTE *filename, void *buf, ULONG len);

//
// Memory heap management
//

void cdecl mem_init(void);
void cdecl mem_shutdown(void);
ULONG cdecl mem_avail(void);
void *cdecl mem_alloc(ULONG bytes);
BYTE *cdecl str_alloc(BYTE *string);
void cdecl mem_free(void *ptr);
ULONG cdecl mem_headroom(void);

//
// Misc. routines
//

LONG cdecl ascnum(BYTE *string);
void cdecl opcode_fault(void *PC, void *stk);
void cdecl abend(char *msg, ...);
void cdecl curpos(WORD *x, WORD *y);
void cdecl locate(WORD x, WORD y);

#ifdef __cplusplus
}
#endif

#endif

