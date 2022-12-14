//????????????????????????????????????????????????????????????????????????????
//??                                                                        ??
//??  RTSYSTEM.C                                                            ??
//??                                                                        ??
//??  AESOP runtime system-level services                                   ??
//??                                                                        ??
//??  Version: 1.00 of 6-May-92 -- Initial version                          ??
//??                                                                        ??
//??  Project: Extensible State-Object Processor (AESOP/16)                 ??
//??   Author: John Miles                                                   ??
//??                                                                        ??
//??  C source compatible with IBM PC ANSI C/C++ implementations            ??
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

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dos.h>
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <errno.h>
#include <sys\stat.h>

#include "vfx.h"
#include "ail32.h"
#include "gil2vfx.h"

#include "defs.h"
#include "shared.h"
#include "rtsystem.h"
#include "rtmsg.h"
#include "rtres.h"
#include "rt.h"
#include "rtcode.h"
#include "intrface.h"
#include "event.h"
#include "sound.h"
#include "graphics.h"

void breakpoint(void);
#pragma aux breakpoint = "int 3";

ULONG headroom;
ULONG checksum;
ULONG init;

WORD disk_err;

void cdecl mem_init(void)
{
   headroom = init = mem_avail();

   checksum = 0L;
}

void cdecl mem_shutdown(void)
{
   ULONG end;

   end = mem_avail();

   if ((init != end) || (checksum != 0L))
      {
//    abend(MSG_UH);    (unbalanced heap normal in flat-model version)
      }
}

ULONG cdecl mem_avail(void)
{
   union REGS inregs,outregs;
   ULONG memarray[12];

   inregs.x.eax = 0x0500;
   inregs.x.edi = (ULONG) memarray;
   int386(0x31,&inregs,&outregs);

   return memarray[0];
}

ULONG cdecl mem_headroom(void)
{
   return headroom;
}

void *cdecl mem_alloc(ULONG bytes)
{
   ULONG left;
   void *ptr;

   ptr = (void *) malloc(bytes);

   left = mem_avail();
   if (left < headroom) headroom = left;

   if (ptr == NULL)
      abend(MSG_OODM);

   checksum ^= (ULONG) ptr;

   return ptr;
}

BYTE *cdecl str_alloc(BYTE *str)
{
   BYTE *ptr;

   ptr = mem_alloc(strlen(str)+1);
   strcpy(ptr,str);

   return ptr;
}

void cdecl mem_free(void *ptr)
{
   checksum ^= (ULONG) ptr;

   free(ptr);
}

/***************************************************/
//
// Convert string to number, returning -1 if not valid numeric
// string
//
// Skip leading whitespace; handles unary -/+ operators
//
// Accepts binary numbers with '0b' prefix,
// hexadecimal numbers with '0x' prefix; decimal numbers
// handled via atol() library function for speed
// 
// Accepts single ASCII characters with '\'' prefix
// 
/***************************************************/

LONG cdecl ascnum(BYTE *string)
{
   LONG i,j,len,base,neg,chr;
   LONG total;

   while (isspace(*string)) string++;

   neg = 0;
   switch (*string)
      {
      case '-': neg = 1; string++; break;
      case '+':          string++; break;
      }

   if (*string == '\'')
      return (LONG) (*(string+1));

   switch (*(UWORD *) string)
      {
      case 'x0': base = 16; string += 2; break;
      case 'b0': base = 2;  string += 2; break;
      default:   base = 10; break;
      }

   if (base == 10)
      if (isdigit(*string))
         return neg ? -atol(string) : atol(string);
      else
         return -1;

   total = 0L;
   len = strlen(string);

   for (i=0;i<len;i++)
      {
      chr = toupper(string[i]);

      for (j=0;j<base;j++)
         if (chr == "0123456789ABCDEF"[j])
            {
            total = (total * base) + j;
            break;
            }

      if (j==base) return -1;
      }

   return total;
}

/***************************************************/
//
// AESOP interpreter opcode fault handler
//
/***************************************************/

void cdecl opcode_fault(void *PC, void *stk)
{
   abend(MSG_IAO,*(unsigned char *) PC,PC,stk);
}

/***************************************************/
//
// Abnormal program termination handler
//
// Give debugger a chance to return to the failing function, else
// shut everything down gracefully and exit to DOS
//
/***************************************************/

void cdecl abend(BYTE *msg, ...)
{
   va_list argptr;
   WORD recover;
   WORD x,y;

   curpos(&x,&y);
   if (y > 25)
      locate(0,0);

   if (msg != NULL)
      {
      printf("Error: ");

      va_start(argptr,msg);
      vprintf(msg,argptr);
      va_end(argptr);
      printf("\n");

      if (envval(0,"AESOP_DIAG") == 1)
         printf(MSG_MIE,current_msg,current_index,current_event_type);
      }

   recover = 0;

   breakpoint();

   if (!recover)
      {
      shutdown_sound();
      shutdown_interface();
      AIL_shutdown("Abend");
      GIL2VFX_shutdown_driver();

      exit(1);
      }
}

/***************************************************/
//
// Open a text file for reading/writing
//
/***************************************************/

TF_class *cdecl TF_construct(BYTE *filename, WORD oflag)
{
   TF_class *TF;
   WORD file;
   HRES hbuf;

   if (oflag == TF_WRITE)
      oflag = O_CREAT | O_TRUNC | O_WRONLY;
   else
      oflag = O_RDONLY;

   file = open(filename,oflag | O_BINARY,S_IREAD | S_IWRITE);
   if (file == -1) return NULL;

   hbuf = RTR_alloc(RTR,TF_BUFSIZE,DA_FIXED | DA_PRECIOUS);
   if (hbuf == -1U) return NULL;

   TF = mem_alloc(sizeof(TF_class));

   TF->file = file;
   TF->hbuf = hbuf;
   TF->buffer = RTR_addr(TF->hbuf);
   TF->p = 0;
   TF->mode = oflag;
   TF->len = filelength(file);
   TF->pos = 0L;

   if (!(oflag & O_WRONLY))
      read(TF->file,TF->buffer,TF_BUFSIZE);

   return TF;
}

/***************************************************/
//
// Close text file/dealloc buffer
//
// Return 0 if write attempt failed
//
/***************************************************/

WORD cdecl TF_destroy(TF_class *TF)
{
   WORD e,f;

   e = f = TF->p;

   if ((TF->mode & O_WRONLY) && (TF->p != 0))
      e = write(TF->file,TF->buffer,TF->p);

   close(TF->file);

   RTR_free(RTR,TF->hbuf);
   mem_free(TF);

   return (e == f);
}

/***************************************************/
//
// Write character to text file
//
// Return 0 if write attempt failed
//
/***************************************************/

WORD cdecl TF_wchar(TF_class *TF, BYTE ch)
{
   TF->buffer[TF->p++] = ch;

   if (TF->p == TF_BUFSIZE)
      {
      TF->p = 0;
      if (write(TF->file,TF->buffer,TF_BUFSIZE) != TF_BUFSIZE) return 0;
      }

   return 1;
}

/***************************************************/
//
// Read character from text file
//
// Return 0 if EOF reached
//
/***************************************************/

BYTE cdecl TF_rchar(TF_class *TF)
{
   if (TF->pos >= TF->len)
      return 0;

   ++TF->pos;

   if (TF->p != TF_BUFSIZE)
      return TF->buffer[TF->p++];

   read(TF->file,TF->buffer,TF_BUFSIZE);
   
   TF->p = 1;
   return TF->buffer[0];
}

/***************************************************/
//
// Read text file line into buffer
//
// \r's are skipped
// \n's are truncated, replaced with \0
//
// Blank lines are ignored
//
// Return 0 if EOF reached
//
/***************************************************/

WORD cdecl TF_readln(TF_class *TF, BYTE *buffer, WORD maxlen)
{
   WORD b,c;

   do
      {
      b = 0;

      while (b != maxlen-1)
         {
         c = TF_rchar(TF);

         if (c == '\n') break;
         if (c == '\r') continue;

         buffer[b++] = c;

         if (!c) return 0;
         }

      if (b == maxlen-1)
         while ((c = TF_rchar(TF)) != '\n')
            if (!c) return 0;

      buffer[b] = 0;
      }
   while (!strlen(buffer));

   return 1;
}

/***************************************************/
//
// Write buffer line to text file
// Return 0 if write attempt failed
//
// \r\n added at end of each buffer line
//
/***************************************************/

WORD cdecl TF_writeln(TF_class *TF, BYTE *buffer)
{
   WORD b,c;

   b = 0;

   while ((c = buffer[b++]) != 0)
      if (!TF_wchar(TF,c)) return 0;

   TF_wchar(TF,'\r');
   return TF_wchar(TF,'\n');
}

/***************************************************/
//
// Delete a file
//
// Return 0 if file did not exist, -1 if deletion failed,
// else 1 if deleted OK
//
/***************************************************/

WORD cdecl delete_file(BYTE *filename)
{
   if (!unlink(filename))
      return 1;

   if (errno == ENOENT)
      return 0;

   return -1;
}

/***************************************************/
//
// Copy a file
//
// Return 0 if source file not found, -1 if copy error occurred,
// else 1 if copied OK
//
/***************************************************/

WORD cdecl copy_file(BYTE *src_filename, BYTE *dest_filename)
{
   HRES hbuf;
   BYTE *buffer;
   WORD status;
   WORD s,d,n;

   s = open(src_filename,O_RDONLY | O_BINARY);

   if (s==-1)
      return 0;

   d = open(dest_filename,O_BINARY | O_CREAT | O_TRUNC | O_WRONLY,
      S_IREAD | S_IWRITE);

   if (d==-1)
      {
      close(s);
      return -1;
      }

   hbuf = RTR_alloc(RTR,TF_BUFSIZE,DA_FIXED | DA_PRECIOUS);
   if (hbuf == -1U)
      {
      close(s);
      close(d);
      return -1;
      }

   buffer = RTR_addr(hbuf);
   status = 1;

   while ((n = read(s,buffer,TF_BUFSIZE)) != 0)
      {
      if (n == -1)
         {
         status = -1;
         break;
         }

      if (write(d,buffer,n) != n)
         {
         status = -1;
         break;
         }
      }

   close(s);
   close(d);

   RTR_free(RTR,hbuf);

   return status;
}

/****************************************************************************/
//
// Determine the size in bytes of a file
//
/****************************************************************************/

LONG file_size(BYTE *filename)
{
   WORD handle;
   ULONG len;

   disk_err = 0;

   handle = open(filename,O_RDONLY | O_BINARY);
   if (handle==-1)
      {
      disk_err = FILE_NOT_FOUND;
      return -1L;
      }

   len = filelength(handle);
   if (len==-1L) disk_err = CANT_READ_FILE;

   close(handle);
   return len;
}

/****************************************************************************/
//
// Read a file directly into memory
//
/****************************************************************************/

BYTE *cdecl read_file(BYTE *filename, void *dest)
{
   WORD i,handle;
   ULONG len;
   BYTE *buf, *mem;

   disk_err = 0;

   len = file_size(filename);
   if (len==-1L)
      {
      disk_err = FILE_NOT_FOUND;
      return NULL;
      }

   buf = mem = (dest==NULL)? mem_alloc(len) : dest;

   if (buf==NULL)
      {
      disk_err = OUT_OF_MEMORY;
      return NULL;
      }

   handle = open(filename,O_RDONLY | O_BINARY);
   if (handle==-1)
      {
      mem_free(mem);
      disk_err = FILE_NOT_FOUND;
      return NULL;
      }

   while (len >= DOS_BUFFSIZE)
      {
      i = read(handle,buf,DOS_BUFFSIZE);
      if (i != (WORD) DOS_BUFFSIZE)
         {
         mem_free(mem);
         disk_err = CANT_READ_FILE;
         return NULL;
         }
      len -= DOS_BUFFSIZE;
      buf = add_ptr(buf,DOS_BUFFSIZE);
      }

   i = read(handle,buf,(UWORD) len);
   if (i != (UWORD) len)
      {
      mem_free(mem);
      disk_err = CANT_READ_FILE;
      return NULL;
      }

   close(handle);
   return mem;   
}
   
/****************************************************************************/
//
// Write a binary file to disk
// 
/****************************************************************************/

WORD cdecl write_file(BYTE *filename, void *buf, ULONG len)
{
   WORD i,handle;

   disk_err = 0;

   handle = open(filename,O_CREAT | O_RDWR | O_TRUNC | O_BINARY,
      S_IREAD | S_IWRITE);
   if (handle==-1)
      {
      disk_err = CANT_WRITE_FILE;
      return 0;
      }

   while (len >= DOS_BUFFSIZE)
      {
      i = write(handle,buf,DOS_BUFFSIZE);
      if (i == -1)
         {
         disk_err = CANT_WRITE_FILE;
         return 0;
         }
      if (i != (WORD) DOS_BUFFSIZE)
         {
         disk_err = DISK_FULL;
         return 0;
         }
      len -= DOS_BUFFSIZE;
      buf = add_ptr(buf,DOS_BUFFSIZE);
      }

   i = write(handle,buf,(UWORD) len);
   if (i == -1)
      {
      disk_err = CANT_WRITE_FILE;
      return 0;
      }
   if (i != (UWORD) len)
      {
      disk_err = DISK_FULL;
      return 0;
      }

   close(handle);
   
   return 1;
}

/****************************************************************************/
//
// Append binary data to an existing file
//
/****************************************************************************/

WORD cdecl append_file(BYTE *filename, void *buf, ULONG len)
{
   WORD i,handle;

   disk_err = 0;

   handle = open(filename,O_APPEND | O_RDWR | O_BINARY);
   if (handle==-1)
      {
      disk_err = FILE_NOT_FOUND;
      return 0;
      }

   while (len >= DOS_BUFFSIZE)
      {
      i = write(handle,buf,DOS_BUFFSIZE);
      if (i == -1)
         {
         disk_err = CANT_WRITE_FILE;
         return 0;
         }
      if (i != (WORD) DOS_BUFFSIZE)
         {
         disk_err = DISK_FULL;
         return 0;
         }
      len -= DOS_BUFFSIZE;
      buf = add_ptr(buf,DOS_BUFFSIZE);
      }

   i = write(handle,buf,(UWORD) len);
   if (i == -1)
      {
      disk_err = CANT_WRITE_FILE;
      return 0;
      }
   if (i != (UWORD) len)
      {
      disk_err = DISK_FULL;
      return 0;
      }

   close(handle);
   
   return 1;
}

/****************************************************************************/
//
// Get file's timestamp
//
/****************************************************************************/

ULONG cdecl file_time(BYTE *filename)
{
   union REGS in,out;
   WORD handle;

   handle = open(filename,O_RDONLY);

   if (handle==-1) return 0L;

   in.w.ax = 0x5700;
   in.w.bx = handle;
   intdos(&in,&out);

   close(handle);

   return (ULONG) out.w.cx + ((ULONG) out.w.dx << 16);
}

/****************************************************************************/
//
// Position text cursor
//
/****************************************************************************/

void cdecl locate(WORD x, WORD y)
{
   union REGS inregs,outregs;

   inregs.h.bh = 0x00;
   inregs.h.ah = 0x02;
   inregs.h.dh = y;
   inregs.h.dl = x;
   int386(0x10,&inregs,&outregs);
}

/****************************************************************************/
//
// Get text cursor location
//
/****************************************************************************/

void cdecl curpos(WORD *x, WORD *y)
{
   union REGS inregs,outregs;

   inregs.h.ah = 0x0f;
   int386(0x10,&inregs,&outregs);

   inregs.h.bh = outregs.h.bh; inregs.h.ah = 0x03;
   int386(0x10,&inregs,&outregs);
   *x = outregs.h.dl; *y =outregs.h.dh;
}


