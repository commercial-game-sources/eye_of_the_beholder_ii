AESOP decompiler version: 0.850
22nd January 2007
Public domain software made by Mirek Luza (mirekluza@gmail.com)

What's new
----------
The version 0.850 improves the AESOP disassembler. The local variables and parameters use now symbolic names. Also whenever the bytecode uses a direct number which could possibly refer an existing resource, the corresponding comment is added into the disassembly (of course in many cases this will be a wrong guess - the number can be used for different purposes - but I still think it will increase the readability of the disassembler). Some minor fixes in the disassembly were made.
The version 0.800 adds the command for patching of the converted EYE.RES from the "Eye of Beholder 3" so that it does not crash when loading/saving (there is a problem that the original code depends on the shape of 16 bit pointers, minor fix is needed to make it work in AESOP/32 - the fix is done in the code resource "menu" in the message handler "show"). This should make the "Eye of Beholder 3" playable in the AESOP/32 (but more testing is needed).
I also added a command which makes patching of the EOB 3 and the conversion of bitmaps/fonts to the AESOP/32 in one step (instead of using DAESOP three times). But remember that another command is still needed to replace the resource 3 (see later).
The version 0.750 adds support for converting "EOB 3 like" fonts. This menans that that all text is now shown inside the game, further increasing playability. Beware that there are still some problems (e.g. I had crashes when wanting to save game). I must investigate them.
The version 0.700 adds support for converting "EOB 3 like" bitmaps. This means that the "Eye of Beholder 3" is already partially usable in AESOP/32 (not really playable - fonts need to be converted). Also a possibility to create TBL files (for the "Dungeon Hack" engine) was added.
The version 0.660 adds the command line options /r and /rh. This enable to "replace" resources in an existing RES file (so it is possible to change e.g. code/images/music/sound...). The replacement does not remove an old resource physically but rather adds a new resource to the end of the file and changes reference pointing to the old resource so that it points to the new resource.
The version 0.630 adds a usefull command line option /ir. It enables to show more information about resources, their types and for string resources their values.
The version 0.600 adds a lot of new things into the disassembler introduced in DAESOP 0.500. It concerns mainly variables. For most of variables (with exception of local "auto" variables) symbolic names are used. When possible (imported/exported variables), the real names are used. When it is not possible (private static variables, "table" variables), simple symbolic names are made. In future versions of DAESOP this will be done also for local variables.
The tables showing import/export resources were reworked and they now show properly all available items. The problem of not disassembling procedures (instructions JSR/RTS) was fixed.
Various minor things were fixed/improved.

Background
----------
This utility is based on the information from the AESOP documentation and source code (thanks to its author John Miles) and on information from ReWiki(http://rewiki.regengedanken.de/wiki/Main_Page, thanks to Darkstar).

This is simple utility for analyzing AESOP engine RES files. It can also convert the "Eye of Beholder 3" to the AESOP/32 engine. AESOP engine is used in the games "Eye of Beholder 3" and "Dungeon Hack".
Its author John Miles recently released it as public domain including sources and documentation (I mean the engine and the interpreter including sources and documentation - the games themselves were *NOT* released).
All things including this utility (and its future versions) can be downloaded from the following thread:
http://vogons.zetafleet.com/viewtopic.php?t=13168

Also see the following links for information about the AESOP and format of the RES files:
http://rewiki.regengedanken.de/wiki/AESOP/16 
http://rewiki.regengedanken.de/wiki/.RES 
http://rewiki.regengedanken.de/wiki/EYE.RES 

Usage
-----
        DAESOP COMMAND LINE PARAMETERS
        Information:
        daesop /i <res_file> <output_text_file>
        daesop /ir <res_file> <output_text_file>
        daesop /j <res_file> <resource_name> <output_text_file>
        daesop /k <res_file> <resource_number> <output_text_file>
        daesop /ioff <res_file> <offset> <output_text_file>
        daesop /test_old_bitmaps <res_file> <output_text_file>
        Extraction:
        daesop /e <res_file> <resource_name> <output_binary_file>
        daesop /eh <res_file> <resource_name> <output_binary_file>
        daesop /x <res_file> <resource_number> <output_binary_file>
        daesop /xh <res_file> <resource_number> <output_binary_file>
        Conversion:
        daesop /r <res_file> <resource_number> <new_resource_binary> <output_res_file>
        daesop /rh <res_file> <resource_number> <new_resource_binary> <output_res_file>
        daesop /eob3conv <res_file> <output_res_file>
        daesop /create_tbl <res_file> <output_tbl_file>
        daesop /cob <res_file> <output_res_file>
        daesop /convert_old_bitmaps <res_file> <output_res_file>
        daesop /cof <res_file> <output_res_file>
        daesop /convert_old_fonts <res_file> <output_res_file>
        daesop /eob3menupatch <res_file> <output_res_file>

<res_file> is RES file (e.g. EYE.RES from EOB 3)
<output_text_file> text file with some information
<output_binary_file> binary file with an extracted resource
<new_resource_binary> binary file representing the new resource
<output_res_file> the result RES file with the replaced resource or converted bitmaps
<offset> number (decadic or hexadecimal starting by # or 0x)
<output_tbl_file> newly created TBL file (for "Dungeon Hack" engine)

/i  - the program produces a text file with the information about the <res_file>
/ir - the program produces a text file with the information about the resources, including information from special resources 1 and 2 (original names of source files), resource types and for string resources their values
/j  - the program produces a text file with the information about the resource <resource_name>
/k  - the program produces a text file with the information about the resource <resource_number>
/ioff - the program tells what is on the specified offset in the resource file. It is usefull when seeing something interesting in a hexadecimal editor and wanting to know to which resource it belongs.
/test_old_bitmaps - checks all bitmap resources whether they are "EOB 3 like" bitmaps

/e  - the program extracts the resource <resource_name>
/eh - the program extracts the resource <resource_name> including header
/x  - the program extracts the resource <resource_number>
/xh - the program extracts the resource <resource_number> including header

/r  - the problem replaces the specified resource number with the provided resource binary. The provided binary file represents the "new" resource without a resource header. The resource header from the original resource is used (just the length is corrected according the length of the "new" resource). The command does not change the original RES file, but produces its modified copy.
/rh  - the problem replaces the specified resource number with the provided resource binary. The provided binary file represents the "new" resource with a resource header.  The command does not change the original RES file, but produces its modified copy.
/eob3conv - this command patches the EOB 3 (fixing the menu bug which leads to load/save crashes in the AESOP/32) and converts bitmaps and fonts. It has the same effect as using commands /cob, /cof and /eob3menupatch. (Warning: the final effect will be the same, but the result binary can differ a bit in content - resources are added at the end in a different order - but the effect will be the same in both cases).
/create_tbl - create a TBL file for the specified RES file (the "Dungeon Hack" engine needs TBL files)
/cob - converts all "EOB 3 like" bitmaps in the specified file. Ends up immediately if an error is found.
/convert_old_bitmaps - converts all "EOB 3 like" bitmaps in the specified file. Ignores errors (when a bitmap conversion fails, the old bitmap is kept)
/cof - converts all "EOB 3 like" fonts in the specified file. Ends up immediately if an error is found.
/convert_old_fonts - converts all "EOB 3 like" fonts in the specified file. Ignores errors (when a font conversion fails, the old font is kept)
/eob3menupatch - patches the EOB 3 (resource "menu", message handler "show") to work in the AESOP/32. The original code depends on the shape of pointers in the 16 bit mode and crashes in the AESOP/32. Unpatched game crashes when trying to load/save game from menu. The patched game works ok in the AESOP/32.

The header mentioned above is the sequence of 12 bytes at the beginning (it contains encoded length, attributes, date).
The switches /eh /xh extract resource with this header, /e /x without it (so only the resource itself).

The switches /j /k are the most useful for the special AESOP tables (resources 0..4) and for the IMPORT/EXPORT/CODE resources. In these cases they provide some specific information including disassembly for code resources/. For all other resources a hexadecimal dump is produced.
The import resources are the resources <name>.IMPT, the export resources are the resources <name>.EXPT. Every import/export resource has a corresponding code resource <name>.

The replacement command (/r or /rh) does not remove an old resource physically but rather adds a new resource to the end of the file and changes the reference pointing to the old resource so that it points to the new resource. So every usage of /r or /rh increases the size of the file.

The EOB 3 menu patch command (/eob3menupatch) does not patch the old resource itself, but rather makes its copy, patches the copy and  changes the reference pointing to the old resource so that it points to the new resource. So the usage of /eob3menupatch increases the size of the file.

For conversion see the chapter further in this document ("Conversion of RES files").

WARNING: The AESOP resource names are case sensitive! In EOB 3 there are resources "holy symbol" and "Holy symbol".

AESOP disassembler
------------------
When the options /j or /k are used for the code related resources they dissassemble the corresponding code resource (check the resulting text file for the disassembled code). At the moment there is no AESOP assembler (I may do it in future).

Conversion of RES files
-----------------------
The conversion of the RES files between different versions of the AESOP engine includes (sometimes not all steps are necessary):
a) Changing of the table of low level functions (resource 3)
b) Conversion of bitmaps if needed
c) Conversion of fonts if needed
d) Conversion of other things if needed (sound, music)
e) When converting to the "Dungeon Hack" engine, the corresponding TBL file must be created
f) Patching incompatible code

The point a) is easy - extract the resource 3 from a RES file made in the target engine and replace the resource 3 in the source RES file.
The point b) is implemented in DAESOP for the conversion EOB 3 > AESOP/32 (see /cob).
The point c) is implemented in DAESOP for the conversion EOB 3 > AESOP/32 (see /cof).
The point d) is not being handled yet (it is not needed for the EOB 3 > AESOP/32 conversion).
The point e) is implemented in the DAESOP (see create_tbl).
The point f) in DAESOP for the conversion EOB 3 > AESOP/32 (see /eob3menupatch).

For the conversion EOB 3 > AESOP/32 the command /eob3conv was implemented - it makes the work of the original commands /cob, /cof and /eob3menupatch (the points b), c), f) ).

Remember that the target engine should support all those functions used by the source system. For example it is possible to convert the "Eye of Beholder 3" to the "Dungeon Hack" engine (change the resource 3, generate EYE.TBL for EYE.RES), but it has no sense. When running, the game ends up almost immediately complaining about missing function "create_initial_binary_files" which is available in the EOB 3 engine, but not in the DH engine.

Conversion of the "Eye of Beholder 3" to "AESOP/32"
---------------------------------------------------
This partially works already: the game runs, but the texts are missing.
These things are needed:
a) Changing the resource 3
b) Converting bitmaps
c) Converting fonts
d) Patching incompatible code

All these things are supported by DAESOP

rem converts EYE.RES to EYE2.RES usable in AESOP/32
rem rename the result file to EYE.RES and use in AESOP/32
daesop /eob3conv eye.res eye1.res
daesop /xh sample.res 3 3h.bin
daesop /rh eye1.res 3 3h.bin eye2.res

The first command converts bitmaps/fonts and patches one incompatibility (resource "menu", message handler "show" - when unpatched, opening the save/load menu crashes the game in the AESOP/32), the second extracts the resource 3 from a sample AESOP/32 file, the third replaces the old resource 3.
After that the game runs in the AESOP/32 (but beware that there can be problems - this was not extensively tested yet).

The command /eob3conv makes the work of the original commands /cob, /cof and /eob3menupatch. (Warning: the final effect will be the same, but the result binary can differ a bit in content - resources are added at the end in a different order - but the effect will be the same in both cases).

For developers
--------------
The utility was developed in Open Watcom 1.5, but only pure C language is used (so it should be portable). Remember to set the structure alignment to 1.
Warning: Quite a few things in the utility are allocated by malloc(), but not properly freed. Since in normal operating systems the memory is freed when the program ends, it should not be a problem. But I know it is not nice...

History
-------
0.1x  initiall versions (development)
0.20  first release (061014)
0.25  internal version
0.30  second release including resource extraction (061017)
0.31  fixed syntax help
0.35  internal revision (major rewriting, starting to show individuall resource information)
0.36  internal revision: added info about special/import/export/code resources
0.40  third release: added more dumps, resolving names in export tables
0.4x  internal versions
0.50  fourth release (including disassembler)
0.51  minor bugfixes (just making the disassembled code nicer)
0.5x  internal revisions
0.60  fifth release (processing extern/static/table variable references, fixing proedures etc.)
0.6x  internal revisions
0.63  sixth release (/ir command, types of resources, values of string resources)
0.6x  internal revisions
0.66  seventh release: support for /r, /rh commands
0.6x  internal revisions
0.70  8th release: bitmap conversion (EOB 3 > AESOP/32), creation of TBL files
0.7x  internal revisions
0.75  9th release: conversion of fonts added, fixed the resource type detection (palettes, maps)
0.80  10th release: added /eob3menupatch (patching menu bug), /eob3conv (/eob3menupatch + /cof + /cob)
0.8x  internal revisions
0.85  11th release: symbolic names for local variables/parameters, disassembly fixes & comments

Status
------
Anyone can do anything with this code and use it or its parts elsewhere. Just do not complain about my coding style. :-)