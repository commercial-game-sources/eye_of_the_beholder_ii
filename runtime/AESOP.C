/******************************************/
/*                                        */
/* AESOP: AESOP stub program              */
/*                                        */
/* 14-Sep-93 John Miles                   */
/*                                        */
/* Must be compiled with 16-bit ANSI C    */
/*                                        */
/******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <dos.h>
#include <malloc.h>
#include <conio.h>

#define PRO 0     // 1 for DOS/4GW Professional, else 0

struct
{
   char  prg[128];
   char arg1[128];
   char arg2[128];
}
s;

/******************************************/
void main(int argc, char *argv[])
{
   int i,rtn;
   char cmdline[128];
   char *av[16];

   if (getenv("AESOP_DIAG") != NULL)
      {
      if (farcoreleft() < 553384L)
         {
         printf("WARNING: Real-mode character creation program requires 575,000 bytes\n");
         printf("of conventional DOS memory, which is not currently available.\n");
         printf("AESOP_DIAG environment variable is set, permitting game to run anyway.\n");
         printf("However, do NOT select character creation option at main menu!\n\n");
         printf("Press any key to continue...\n");
         getch();
         }
      }
   else
      {
      if (farcoreleft() < 553384L)
         {
         printf("Error: Eye of the Beholder III requires 575,000 bytes of\n");
         printf("conventional DOS memory.\n");

         exit(1);
         }
      }

#if PRO
   av[0] = "INTERP.EXE";
   av[1] = argv[1];
   av[2] = argv[2];
   av[3] = NULL;
#else
   av[0] = "DOS4GW.EXE";
   av[1] = "INTERP.EXE";
   av[2] = argv[1];
   av[3] = argv[2];
   av[4] = NULL;
#endif

   *(unsigned long far *) 0x4fa = ((unsigned long) FP_SEG(&s) * 16L) +
                                   (unsigned long) FP_OFF(&s);

   rtn = spawnvp(P_WAIT,av[0],av);

   if (rtn == -1)
      {
      asm{
         mov ax,3
         int 10h
         }

      printf("Process spawn failure #%u\n",errno);
      exit(1);
      }

   if (rtn == 0)
      {
      exit(0);
      }

   if (rtn == 127)
      {
      putenv("DOS4G=QUIET");

      execl(s.prg,s.prg,s.arg1,s.arg2,NULL);

      asm{
         mov ax,3
         int 10h
         }

      printf("Secondary process launch failure %s %s %s\n",
         s.prg,s.arg1,s.arg2);
      }

   exit(1);
}
