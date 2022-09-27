###############################################################
#                                                             #
#  MAKEFILE for AESOP/32 development                          #             
#  12-Sep-93 John Miles                                       #
#                                                             #
#  Execute with Watcom WMAKE                                  #
#                                                             #
#  Requires Watcom C 9.5                                      #
#                                                             #
###############################################################

.ERASE

#
# DOS environment variable TMP holds path of temporary directory
# (should be RAMDISK for speed)
#

TEMPDIR = $%TMP

#
# Implicit rules
#

.c.obj: .AUTODEPEND
   wcc386p -w9 -4r -j -ot $*.c

.obj.exe:
   @echo system x32r                          >$TEMPDIR\$^&.lnk
   @echo n $^&                               >>$TEMPDIR\$^&.lnk
   @for %i in ($($^&_objects)) do @echo f %i >>$TEMPDIR\$^&.lnk
   wlink @$TEMPDIR\$^&.lnk
   x32fix $^&

#
# Target list
#

all: arc.exe   &
     .SYMBOLIC

#
# ARC classes and components
#

ARC_objects =       &
   arc.obj      &
   dict.obj     &
   lexan.obj    &
   preproc.obj  &
   resfile.obj  &
   resource.obj &
   rscomp.obj   &
   sopcomp.obj  &
   mapcomp.obj  &
   palcomp.obj  &
   system.obj

arc.exe: $(ARC_objects) compiler.mak
