//
//  AESOP runtime ASM calls
//

#ifndef RT_H
#define RT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct                // fundamental stack value structure
{
   ULONG val;
   UWORD type;
}
STKVAL;

enum
{
   TYP_CRES,                  // data type: code resource address
   TYP_SRES,                  // data type: string resource
   TYP_VSHR,                  // data type: short integer variable
   TYP_VLNG,                  // data type: long integer variable
   TYP_SVAR,                  // data type: string variable
};

extern ULONG diag_flag;
extern ULONG current_this;
extern ULONG current_msg;
extern ULONG current_index;

// Pointer and memory block management

#define norm(x) ((void *) (x))
#define add_offset(s,o) ((void *)((ULONG)(s) + (ULONG)(o)))

#define add_ptr(base,offset) ((void *)((ULONG)(base) + (ULONG)(offset)))

#define ptr_dif(top,bot) (((BYTE *)(top) - (BYTE *)(bot)))

#define far_memmove(dest, src, len) ((void *)memmove((dest),(src),(len)))

// Assorted speed-critical .ASM routines

void *cdecl RTD_first(void *dictionary);
void *cdecl RTD_iterate(void *base, void *cur, BYTE **tag, BYTE **def);

BYTE *cdecl RTD_lookup(HRES dictionary, void *key);

// Runtime interpreter calls

void cdecl RT_init(RTR_class *RTR, ULONG stack_size, HRES *objlist);
void cdecl RT_shutdown(void);
void cdecl RT_arguments(void *base, ULONG size);
LONG cdecl RT_execute(ULONG index, ULONG msg_num, ULONG vector);

#ifdef __cplusplus
}
#endif

#endif

