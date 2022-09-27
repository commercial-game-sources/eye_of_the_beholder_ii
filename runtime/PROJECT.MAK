###############################################################
#                                                             #
#                                                             #
#  MAKEFILE for Eye III/32 development                        #
#  1-Sep-93 John Lemberger                                    #
#                                                             #
#  Execute with Watcom WMAKE                                  #
#                                                             #
#  Requires Watcom C 9.0, MASM 6.00B                          #
#                                                             #
###############################################################

.EXTENSIONS: .tpl .asc
.ERASE

#
# DOS environment variable TMP holds path of temporary directory
# (should be RAMDISK for speed)
#

TEMPDIR = $%TMP

#
# Implicit rules
#

.asm.obj:
   ml /c /I..\..\386fx\light $*.asm

.c.obj: .AUTODEPEND
   wcc386p /w9 /4r /oeatx /zq /s /i=..\..\386fx\light /i=..\..\386fx\sound /i=.. $*.c

.obj.exe:
   @echo system dos4g                         >$TEMPDIR\$^&.lnk
   @echo n $TEMPDIR\$^&                      >>$TEMPDIR\$^&.lnk
   @for %i in ($($^&_objects)) do @echo f %i >>$TEMPDIR\$^&.lnk
   @echo op symfile=$^&                      >>$TEMPDIR\$^&.lnk
   @echo op map=$TEMPDIR\$^&.map             >>$TEMPDIR\$^&.lnk
   @echo op stack=16k                        >>$TEMPDIR\$^&.lnk
   wlink @$TEMPDIR\$^&.lnk
#  c:\tools\4gwpro\4gwbind c:\tools\4gwpro\4gwpro.exe $TEMPDIR\$^& $^& -V
   copy $TEMPDIR\$^&.exe $^&.exe

#--------------------------------------
#
# Target list
#
#--------------------------------------

all: interp.exe bshape.exe .SYMBOLIC

#--------------------------------------
#
# AESOP
#
#--------------------------------------

interp_objects =                       &
  interp.obj                           &
   rtres.obj                           &
   rtsystem.obj                        &
   rtlink.obj                          &
   rtcode.obj                          &
   rtobject.obj                        &
   xfer.obj                            &
   gil2vfx.obj                         &
   event.obj                           &
   intrface.obj                        &
   graphics.obj                        &
   eye.obj                             &
   mouse.obj                           &
   sound32.obj                         &
   mod32.obj                           &
   modsnd32.obj                        &
   gil2vfxa.obj                        &
   rt.obj                              &
   ..\..\386fx\light\dllload.obj       &
   ..\..\386fx\sound\ail32.obj         &
   ..\..\386fx\light\vfxa.obj          &
   ..\..\386fx\light\vfx3d.obj

interp.exe: $(interp_objects) project.mak

#--------------------------------------
#
# BSHAPE
#
#--------------------------------------

bshape_objects =                       &
   bshape.obj                          &
   bshapea.obj                         &
   ..\..\386fx\light\vfxa.obj               

bshape.exe: $(bshape_objects) project.mak
   @echo system dos4g                         >$TEMPDIR\$^&.lnk
   @echo n $^&                               >>$TEMPDIR\$^&.lnk
   @for %i in ($($^&_objects)) do @echo f %i >>$TEMPDIR\$^&.lnk
   @echo op stub=wstub.exe, symfile=$^&      >>$TEMPDIR\$^&.lnk
   wlink @$TEMPDIR\$^&.lnk

