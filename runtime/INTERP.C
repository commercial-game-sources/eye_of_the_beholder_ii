//????????????????????????????????????????????????????????????????????????????
//??                                                                        ??
//??  INTERP.C                                                              ??
//??                                                                        ??
//??  AESOP runtime host interpreter                                        ??
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
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <dos.h>

#include "ail32.h"

#include "defs.h"
#include "shared.h"
#include "rtmsg.h"
#include "rtres.h"
#include "rtsystem.h"
#include "rt.h"
#include "rtlink.h"
#include "rtobject.h"
#include "rtcode.h"
#include "event.h"

//
// Amount of memory to reserve for scaling buffer (64K) + PAGE2 (64K) + misc.
// (22K)
//

#define  WINDOW_SIZE    150000   

//
// Amount of memory to reserve for DLL loading/linking (100K)
// 

#define DLL_HEADROOM    100000

//
// Amount of memory to reserve for miscellaneous malloc() calls (32K)
//

#define MALLOC_HEADROOM 32768

//
// Amount of memory to reserve for AESOP interpreter stack (16K)
//

#define STK_SIZE        16384

//
// Minimum AESOP resource cache size permissible (600K)
//

#define MIN_RES_SIZE    600000

//
// Maximum useful AESOP resource cache size (800K)
//

#define MAX_RES_SIZE    800000

//
// Globals
//

RTR_class *RTR;

HRES HROED;
ULONG heap_size;

BYTE *pathname;

/*************************************************************/
void main(int argc, char *argv[])
{
   BYTE RES_name[256];
   BYTE code_name[256];
   ULONG i;
   ULONG code;
   LONG rtn;

   pathname = argv[0];
   
   setbuf(stdout,NULL);

   ENABLED = 1;

   AIL_startup();
   mem_init();

   if (argc < 3)
      {
      printf(MSG_BANNER);
      printf(MSG_SYN_1);
      abend(NULL);
      }

   strcpy(RES_name,argv[1]);
   for (i=0;i<strlen(RES_name);i++)
      if (RES_name[i] == '.')
         {
         RES_name[i] = 0;
         break;
         }
   strcat(RES_name,".RES");

   strcpy(code_name,argv[2]);

   heap_size = mem_avail()     -
               WINDOW_SIZE     -
               DLL_HEADROOM    -
               MALLOC_HEADROOM -
               STK_SIZE;

   if (heap_size < MIN_RES_SIZE)
      {
      abend(MSG_NO_DOS);
      }

   if (heap_size > MAX_RES_SIZE)
      heap_size = MAX_RES_SIZE;

   RTR = RTR_construct(mem_alloc(heap_size),heap_size,MAX_OBJ_TYPES,RES_name);

   if (RTR==NULL)
      abend(MSG_RIF,RES_name);

   init_object_list();
   init_notify_list();
   init_event_queue();

   RT_init(RTR,STK_SIZE,objlist);

   HROED = RTR_get_resource_handle(RTR,ROED,DA_TEMPORARY | DA_EVANESCENT);
   RTR_lock(RTR,HROED);
   code = ascnum(RTD_lookup(HROED,code_name));
   RTR_unlock(HROED);

   if (code == (ULONG) -1L)
      abend(MSG_SPNF);

   rtn = create_program(1,bootstrap,(ULONG) code);
   rtn = destroy_object(1,rtn);

   for (i=0;i<RTR->nentries;i++)
      {
      ULONG f;

      f = RTR->dir[i].flags;

      if ((f & DA_FREE) && (f & DA_DISCARDED) && (!RTR->dir[i].seg))
         break;
      }

   if (envval(0,"AESOP_DIAG") == 1)
      {
      printf("Entries avail: %u\n",RTR->nentries);
      printf("       In use: %u\n\n",i);

      printf("%u names in use\n",RTR->nd_entries);
      }

   RTR_destroy(RTR,RTR_FREEBASE);
   RT_shutdown();

   mem_shutdown();
   AIL_shutdown(MSG_AIL);

   if (envval(0,"AESOP_DIAG") == 1)
      {
      printf("%lu bytes in heap\n",heap_size);
      printf("%lu bytes left\n",mem_headroom());
      }

   exit(rtn);
}
