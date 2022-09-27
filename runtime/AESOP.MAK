###############################################################
#                                                             #
#  MAKEFILE for Eye III/32 development                        #
#  1-Sep-93 John Lemberger                                    #
#                                                             #
#  Execute with Watcom WMAKE                                  #
#                                                             #
#  Requires Watcom C 9.0, MASM 6.00B                          #
#                                                             #
###############################################################

#--------------------------------------
#
# ASTUB: Execution stub for AESOP.EXE
#
#--------------------------------------

aesop.exe: aesop.c
   bcc -ml -v aesop.c
