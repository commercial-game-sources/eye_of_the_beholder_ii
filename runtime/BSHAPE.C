//лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
//лл                                                                        лл
//лл  BSHAPE.C                                                              лл
//лл                                                                        лл
//лл  386FX shape table creation from GIL compatible bitmaps, utility       лл
//лл                                                                        лл
//лл  Version 0.10 of 10-Dec-92: Created                                    лл
//лл  Version 1.00 of  1-Mar-93: Initial release                            лл
//лл  Version 1.01 of 19-May-93: PCX files require tc parameter             лл
//лл  Version 1.10 of  1-Sep-93: Shape file will have bounds & origin       лл
//лл                                                                        лл
//лл  Project: 386FX Sound & Light(TM)                                      лл
//лл  Authors: John Lemberger, John Miles                                   лл
//лл                                                                        лл
//лл  80386 C source compatible with WATCOM C v9.0 or later                 лл
//лл                                                                        лл
//лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
//лл                                                                        лл
//лл  Copyright (C) 1991, 1992, 1993 Miles Design, Inc.                     лл
//лл                                                                        лл
//лл  Miles Design, Inc.                                                    лл
//лл  10926 Jollyville #308                                                 лл
//лл  Austin, TX 78759                                                      лл
//лл                                                                        лл
//лл  (512) 345-2642 / FAX (512) 338-9630 / BBS (512) 454-9990              лл
//лл                                                                        лл
//лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл

#include <stdio.h>
#include <malloc.h>
#include <dos.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#include "vfx.h"
#include "bshapea.h"

#define  MAX_SHAPES  255

WINDOW window;
PANE pane,pane2;

LONG bkgnd;  
UBYTE *fpic;
LONG fpic_type;
FILE *outfile,*rf,*pf;
RGB palette[256];
LONG file_length;

#define SOURCE             1
#define TOP_LEFT           2
#define BOTTOM_RIGHT       3
#define HOT_SPOT           4
#define TRANSPARENT_COLOR  5
#define SHAPE              6
#define SAVE_COLORS        7

typedef struct
{
   UBYTE keyword;
   BYTE keystr[32];
}
KEYWORD;

KEYWORD keywords[] =
{
   { SOURCE,            "source_file=\0"        },
   { SOURCE,            "sf=\0"                 },
   { SHAPE,             "shape_number=\0"       },
   { SHAPE,             "sn=\0"                 },
   { TOP_LEFT,          "top_left=\0"           },
   { TOP_LEFT,          "tl=\0"                 },
   { BOTTOM_RIGHT,      "bottom_right=\0"       },
   { BOTTOM_RIGHT,      "br=\0"                 },
   { HOT_SPOT,          "hot_spot=\0"           },
   { HOT_SPOT,          "hs=\0"                 },
   { TRANSPARENT_COLOR, "transparent_color=\0"  },
   { TRANSPARENT_COLOR, "tc=\0"                 },
   { SAVE_COLORS,       "save_colors\0"         },
   { SAVE_COLORS,       "sc\0"                  },
   { 0,                 "\0"                    }
};

#define LBM 1
#define PCX 2
#define GIF 3
#define SHP 4

typedef struct
{
   LONG  shape;
   LONG  colors;
}
OFFSET;

typedef struct
{
   BYTE  *source;
   LONG  x0;
   LONG  y0;
   LONG  x1;
   LONG  y1;
   LONG  origin_x;
   LONG  origin_y;
   LONG  transparent;
}
GETSHAPE;

GETSHAPE shape;

LONG frame_color;

/******************************************/
void *load_file(BYTE *filename)
{
   LONG file_handle;
   void *buffer;

   if ( (file_handle=open(filename,O_RDONLY|O_BINARY))==-1L )
      return NULL;
   if ( (file_length=filelength(file_handle))==-1L )
      return NULL;
   if ( (buffer = malloc(file_length))==NULL )
      return NULL;
   if ( read(file_handle,buffer,file_length)==-1L )
      return NULL;
   close(file_handle);

   return buffer;
}

/************************************************************/
void fail(int errcode)
{
   static BYTE errmsgs[][128] =
     {{"Error: Input file must be in .LBM, .PCX, .GIF, or .SHP format"      },
      {"Error: Insufficient memory available"                               },  
      {"Error: Could not open input file"                                   },
      {"Error: Could not open output file"                                  },
      {"Error: Could not write to output file"                              },
      {"Error: Shape number does not exist in shape file"                   },
      {"Error: Could not read response file"                                },
      {"Error: Could not open palette file"                                 },
      {"Error: Coordinate must lie within source image"                     },
      {"Error: Invalid directive in response file"                          },
      {"Error: Transparent color must be given for .SHP or .PCX acquisition"},
      {"Error: Too many shapes for file."}};

   printf("%s\n",errmsgs[errcode]);

   fcloseall();
   exit(errcode+1);
}

/************************************************************/

LONG get_block(PANE *pane, LONG frame_color)
{
   ULONG scrn;

   if ( (frame_color >= 0) && (frame_color <256) )
      {
      if (scrn = scan_block(pane, frame_color))
         {
         --scrn;
                
         shape.x0 = shape.x1 = scrn % (pane->window->x1 - pane->window->x0 + 1);
         shape.y0 = shape.y1 = scrn / (pane->window->x1 - pane->window->x0 + 1);

         while ( VFX_pixel_read(pane, shape.x1+1, shape.y0) == frame_color )
            ++shape.x1;
         while ( VFX_pixel_read(pane, shape.x0, shape.y1+1) == frame_color )
            ++shape.y1;

         if ( ((shape.x1 - shape.x0) <2) || ((shape.y1 - shape.y0) < 2) )
            fail(8);

         shape.x0++;
         shape.x1--;
         shape.y0++;
         shape.y1--;
         return 1;
         }
      }

   shape.x0 = pane->x0;
   shape.y0 = pane->y0;
   shape.x1 = pane->x1;
   shape.y1 = pane->y1;

   return 0;

}

/************************************************************/
LONG read_cmd(char *target)
{
   char *c;
   int i,done=0;

   do
      {
      c = fgets(target,255,rf);

      if (ferror(rf))
         {
         fail(6);
         }

      if (c==NULL)
         {
         return 0;
         }

      for (i=0;i<strlen(target);i++)
         {
         if ((!isalnum(target[i])) && (!ispunct(target[i])))
            {
            target[i] = 0;
            }
         }

      if (!strlen(target))
         {
         continue;
         }

      strlwr(target);
      if (!strncmp(target,"fcolor=",7))
         {
         frame_color = atoi(&target[7]);
         }
      else
         {
         done=1;
         }
      }
   while (!done);

   return 1;

}/************************************************************/
void main(int argc, BYTE *argv[])
{
   LONG i, j, shape_source=0, save_colors;
   LONG shape_size, shape_count, shape_num, offset_fptr;
   LONG resolution,max_x,max_y,minxy;
	UBYTE *window_buffer;
   void *GIF_scratch, *shape_buffer;
   //, *rf;
   OFFSET *offsets;
   LONG *size_ptr;
   BYTE filename[256];
   BYTE infn[256];
   CRGB *rgbcolors;
   LONG color_count;
   ULONG *colors;

   char outfn[256];

   frame_color = 254;

   printf("BSHAPE V1.10                      Copyright (c) 1992, 1993 Miles Design, Inc.\n\n");

   if (argc < 2)
      {
      printf("Usage: BSHAPE bmk_file\n\n");

      printf("where: bmk_file = BMAKE compatible response file\n\n");

      printf("Sample response file:\n\n");

      printf("    outfile.bmp        (VFX-compatible shape file to create)\n");
      printf("    dragon.lbm         (Image file containing framed shapes)\n");
      printf("    fcolor=69          (Changes frame color to 69 from default of 254)\n");
      printf("    unicorn.lbm        (Another image file...)\n");
      printf("    lasergun.lbm       (Last infile to include)\n\n");
      printf("OK to comment cmdfile lines.  No limit to number of infiles.\n");


      exit(1);
      }

   //
   // Open response file, count number of shapes and malloc mem for offsets
   //

   if ((rf = fopen(argv[1],"rt")) == NULL)
      fail(6);

   shape_count=MAX_SHAPES;
//   while ( fgets(lbuffer, 255, rf) != NULL )
//      {
//      if ((ptr = strstr(lbuffer,"\n")) != NULL)
//         *ptr='\0';
//
//      if ((ptr = strstr(lbuffer,"//")) != NULL)
//         *ptr='\0';
//
//      strlwr(lbuffer);
//
//      if ( strstr(lbuffer,".lbm") != NULL ) 
//         shape_count++;
//      }

   //
   // Allocate memory for shape & palette offsets
   //

   if ((offsets=malloc(shape_count*sizeof(OFFSET))) == NULL)
      fail(1);

   fseek(rf, 0L, SEEK_SET);

   //
   // Open output file and initialize header information
   //

   if ( !read_cmd(outfn) ) fail(9);
   if ((outfile = fopen(outfn,"w+b")) == NULL) fail(3);

   if ( fwrite(CURRENT_SHAPE_VERSION, sizeof(long), 1, outfile) < 1)
      fail(4);

   if ( fwrite(&shape_count, sizeof(long), 1, outfile) < 1)
      fail(4);

   offset_fptr=ftell(outfile);

   if (fwrite(offsets, sizeof(OFFSET), shape_count, outfile) < shape_count)
      fail(4);

   //
   // Parse response File
   //

   shape_num = 0;
   window_buffer=NULL;
   fpic=NULL;

   shape.source = &infn;

   while ( read_cmd(shape.source) )
      {
      shape.x0=shape.y0=shape.x1=shape.y1=0;
      shape.origin_x=shape.origin_y=0;
      shape.transparent=-1;
      save_colors=FALSE;

      if (stricmp(filename,shape.source) != 0 )
         {
         strcpy(filename,shape.source);
         if (window_buffer != NULL)
            {
            free(window_buffer);
            window_buffer=NULL;
            }
         if (fpic != NULL)
            {
            free(fpic);
            fpic=NULL;
            }

         //
         // Check for .LBM or .PCX extension
         //

         if ( stricmp(".LBM",&shape.source[strlen(shape.source)-4]) == 0 )
            fpic_type=LBM;
         else if ( stricmp(".PCX",&shape.source[strlen(shape.source)-4]) == 0 )
            fpic_type=PCX;
         else if ( stricmp(".GIF",&shape.source[strlen(shape.source)-4]) == 0 )
            fpic_type=GIF;
         else if ( stricmp(".SHP",&shape.source[strlen(shape.source)-4]) == 0 )
            fpic_type=SHP;
         else
            fail(0);
         
         //
         // Load file
         //

         if ((fpic=load_file(shape.source)) == NULL) fail(2);
         
         //
         // Get resolution of image
         //

         switch (fpic_type)
            {
            case LBM:
               resolution = VFX_ILBM_resolution(fpic);
               VFX_ILBM_palette(fpic, palette);
               break;

            case PCX:
               resolution = VFX_PCX_resolution(fpic);
               VFX_PCX_palette(fpic, file_length, palette);
               break;

            case GIF:
               resolution = VFX_GIF_resolution(fpic);
               VFX_GIF_palette(fpic, palette);
               break;

            case SHP:
               if ( *(fpic+4) <= shape_source )
                  fail(5);

               resolution = VFX_shape_resolution(fpic, shape_source);
               if (VFX_shape_colors(fpic, shape_source ,NULL) > 0)
                  VFX_shape_palette(fpic, shape_source, palette);
               break;

            default:
               fail(0);
            }

         max_x=(resolution>>16)-1;
         max_y=((LONG)(WORD)resolution)-1;
         
         //
         // Set up pane and window
         //

		   if ((window_buffer=
              calloc((resolution>>16)*(resolution&0x0ffff),1)) == NULL)
               fail(1);

		   window.buffer = window_buffer;
		   pane.x0=window.x0 = 0;
		   pane.y0=window.y0 = 0;
		   pane.x1=window.x1 = max_x;
		   pane.y1=window.y1 = max_y;
		   pane.window = &window;
         
         //
         // Draw image
         //

         switch (fpic_type)
            {
            case LBM:
               bkgnd = VFX_ILBM_draw(&pane,fpic);
               break;

            case PCX:
               if (shape.transparent == -1)
                  fail(10);

               VFX_PCX_draw(&pane,fpic);
               break;

            case GIF:
               if ( (GIF_scratch=malloc(GIF_SCRATCH_SIZE))==NULL )
                  fail(3);
               bkgnd = VFX_GIF_draw(&pane,fpic,GIF_scratch);
               free(GIF_scratch);
               break;

            case SHP:
               if (shape.transparent == -1)
                  fail(10);

               minxy=VFX_shape_minxy(fpic, shape_source);
               VFX_pane_wipe(&pane,shape.transparent);
               VFX_shape_draw(&pane,fpic,shape_source,-(minxy>>16),-(minxy<<16>>16));
               break;

            default:
               fail(0);
            }

         if (shape.transparent == -1)
            shape.transparent = bkgnd;
         }

      //
      // Scan shape from bitmap pane
      //

      get_block(&pane, frame_color);
      do
         {
         if (shape.x0<0 || shape.y0<0 || shape.x1>max_x || shape.y1>max_y)
            fail(8);

         if (shape.x0==0 && shape.y0==0 && shape.x1==0 && shape.y1==0)
            {
            shape.x1=max_x;
            shape.y1=max_y;
            }

         pane2.window = &window;
		   pane2.x0 = shape.x0;
   		pane2.y0 = shape.y0;
	   	pane2.x1 = shape.x1;
		   pane2.y1 = shape.y1;

         shape_size=VFX_shape_scan(&pane2, shape.transparent,
            shape.origin_x, shape.origin_y, NULL);

         printf("%s: (%d,%d) - (%d,%d) = %d\n",shape.source,
            shape.x0,shape.y0,shape.x1,shape.y1,
            shape_size);

         if ((shape_buffer=malloc(shape_size))==NULL)
            fail(1);

         shape_size=VFX_shape_scan(&pane2, shape.transparent,
            shape.origin_x, shape.origin_y, shape_buffer);

         size_ptr=(LONG *)shape_buffer;

         //
         // Copy shape color information to shape file
         //
      
         color_count=0;

         if (save_colors)
            {
            color_count = VFX_color_scan(&pane2,NULL);

            if ((colors = malloc(color_count * sizeof(LONG))) == NULL)
               fail(1);
         
            if ((rgbcolors = malloc(color_count * sizeof(CRGB))) == NULL)
               fail(1);

            color_count = VFX_color_scan(&pane2,colors);
      
            for (i=0,j=0;i<color_count;i++)
               {
               if (colors[i] != shape.transparent)
                  {
                  rgbcolors[j].color=colors[i];
                  rgbcolors[j].rgb.r=palette[colors[i]].r;
                  rgbcolors[j].rgb.g=palette[colors[i]].g;
                  rgbcolors[j].rgb.b=palette[colors[i]].b;
                  j++;
                  }
               }
            color_count=j;
            }

         if (color_count > 0)
            {
            offsets[shape_num].colors=ftell(outfile);
            if (fwrite(&color_count,sizeof(color_count),1,outfile) < 1)
               fail(4);
      
            if (fwrite(rgbcolors,sizeof(CRGB),color_count,outfile) < color_count)
               fail(4);
            }
         else
            offsets[shape_num].colors=NULL;

         //
         // Copy shape buffer to shape file
         //

         offsets[shape_num++].shape=ftell(outfile);

         if (shape_num == MAX_SHAPES)
            fail(11);
      
         if (fwrite(shape_buffer, sizeof(UBYTE), shape_size, outfile) < shape_size)
            fail(4);

         fflush(outfile);
      
         if (save_colors)
            {
            free(rgbcolors);
            free(colors);
            }
         free(shape_buffer);

         pane2.x0--;
         pane2.y0--;
         pane2.x1++;
         pane2.y1++;
         VFX_pane_wipe(&pane2, (frame_color^0xff)&0xff);

         } while( get_block(&pane, frame_color) );
      } 

   //
   // Write shape file header to output file
   //

   if (fseek(outfile, offset_fptr, SEEK_SET) != 0)
      fail(4);

   if (fwrite(offsets, sizeof(OFFSET), shape_count, outfile) < shape_count)
      fail(4);

   fflush(outfile);

   free(offsets);
   free(fpic);
   free(window_buffer);

   printf("Compilation successful: %u shape(s) written to '%s'\n",shape_num,
      outfn);

   exit(0);
}


