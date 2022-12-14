//????????????????????????????????????????????????????????????????????????????
//??                                                                        ??
//??  RTMSG.H                                                               ??
//??                                                                        ??
//??  AESOP runtime language-specific definitions                           ??
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

#define MSG_BANNER "AESOP/32 Runtime Host Interpreter V1.00\n\
Copyright (C) 1992, 1993 Miles Design, Inc.  All rights reserved.\n\n"

#define MSG_SYN_1  "Usage: AESOP script_file program_name\n"

#define MSG_NO_DOS "Eye of the Beholder III requires at least 1,500,000 bytes\n\
of available EMS and/or XMS memory."

#define MSG_NO_386 "To run Eye of the Beholder III, your system must be equipped with \n\
an 80386, i486, or (preferably) an Intel Pentium(R) microprocessor."

#define MSG_NO_EMS "Insufficient EMS and/or XMS memory available for sound effects.\n"
#define MSG_NO_PCM "Digitized sound effects will not be available.\n"
#define MSG_NO_XMI "Music initialization failed.\n"
#define MSG_NO_CFG "Bad or missing sound configuration file.\n"
#define MSG_SND_F  "\nPress any key to continue\n"

#define MSG_MMR    "Eye of the Beholder III requires a 100% Microsoft-compatible mouse."

#define MSG_AIL    "Eye of the Beholder "

#define MSG_MIE    "Last message = %d\nLast object = %d\nLast event = %d\n"

#define MSG_SRNF   "Sound resource not found"
#define MSG_OOSSE  "Out of space for sound effects"
#define MSG_TPNF   "Timbre bank %u, patch %u not found"
#define MSG_UH     "Unbalanced heap"
#define MSG_OODM   "Out of DOS memory"
#define MSG_IAO    "Invalid AESOP opcode (%u)\nPC = %p\nSTK = %p\n"
#define MSG_NNSL   "No notification slots left"
#define MSG_COSDR  "Couldn't open savegame directory for reading"
#define MSG_COSDW  "Couldn't open savegame directory for writing"
#define MSG_CWSD   "Couldn't write to savegame directory"
#define MSG_IASS0  "Illegal attempt to save to slot 0"
#define MSG_CNSI   "Could not suspend items"
#define MSG_CNSCL  "Could not suspend current level"
#define MSG_CNSLT  "Could not save level to tempfile"
#define MSG_CNCLT  "Could not create level tempfile"
#define MSG_CNTI   "Could not translate items"
#define MSG_SPLF   "Secondary process launch failure %d"
#define MSG_SRRV   "String resource required by vsprint()"
#define MSG_TBO    "Text buffer overflow"
#define MSG_SRRP   "String resource required by print()"
#define MSG_SRRLS  "String resource required by load_string()"
#define MSG_PONF   "Program object %lu not found"
#define MSG_AILE   "AESOP inheritance limit exceeded"
#define MSG_TTL    "Thunk too large"
#define MSG_MCR    "Missing code resource '%s'"
#define MSG_FPNF   "Friend program %lu not found"
#define MSG_UER    "Unresolved external reference '%s'"
#define MSG_RIF    "Resource script '%s' initialization failed"
#define MSG_SPNF   "Startup program not found"
#define MSG_OMCR   "Object \"%s\" missing; cannot restore %u"
#define MSG_CMCR   "Class '%s' missing; cannot restore"
#define MSG_UVR    "Unresolved variable reference '%s'"
#define MSG_BDIE   "Bad data item entry"
#define MSG_CNOCF  "Could not open context file '%s'"
#define MSG_CFCAE  "Context file corrupt at entry %u"
#define MSG_COOFFT "Couldn't open output file for translation"
#define MSG_COIFFT "Couldn't open input file for translation"
#define MSG_CTCFE  "Couldn't translate context file entry %u"
#define MSG_CWTE   "Couldn't write translated entry %u"
#define MSG_RSTC   "Resource selector table corrupt: d=%p, s=%p, len=%lu"
#define MSG_POR    "Pointer shape %lu out of range"
#define MSG_TFW    "Couldn't assign window; increase MAX_WINDOWS"
#define MSG_TFSW   "Couldn't assign subwindow; increase MAX_PANES"
