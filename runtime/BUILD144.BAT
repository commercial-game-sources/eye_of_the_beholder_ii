@echo.
@echo                        ** READ THIS CAREFULLY! **
@echo.
@echo.
@echo This batch file assumes that Eye III's development directory is
@echo D:\AESOP32\DEV\EYE, and that 1.44M floppy disks are to be generated in
@echo drive B:.
@echo.
@echo * At least 10-15M of disk space available?
@echo * .TXT files been converted?
@echo * Quick-start party been transferred?
@echo * Latest SOUND, INSTALL, CHARCOPY obtained from net?
@echo * Extraneous .AD .ADV .CFG .EXE .DAT .RES .DLL files hidden/deleted?
@echo * Temporary (RAMDISK) drive is E:?
@echo * Everything on E: can be safely wiped out of existence?
@echo.
@echo Hit ^C NOW if any of the above is not true.
@pause

cd savegame
call cleanup
cd ..

@rem compact the resource file
..\arc /c0 eye

if exist d:\data1.arj del d:\data1.arj
if exist d:\data2.arj del d:\data2.arj
if exist d:\data3.arj del d:\data3.arj
if exist d:\data4.arj del d:\data4.arj
if exist d:\data5.arj del d:\data5.arj
if exist d:\data1.a00 del d:\data1.a00
if exist d:\data1.a01 del d:\data1.a01
if exist d:\data1.a02 del d:\data1.a02
if exist d:\data1.a03 del d:\data1.a03

del e:*.*

attrib +H bshape.exe

arj a -we: -y -v1360000 d:\data1.a00 *.ad? *.dll *.cfg *.exe *.dat *.res *.drv *.gff eye.bat

attrib -H bshape.exe

cd \
ren data1.a00 data1.arj
ren data1.a01 data2.arj
ren data1.a02 data3.arj
ren data1.a03 data4.arj
cd \aesop32\dev\eye

cd savegame
arj a -we: -e d:\data5.arj *.bin *.tmp savegame.dir

cd ..\chargen
arj a -we: -e d:\data6.arj *.bmp *.col *.cps *.dat *.exe *.fnt *.ovl create.sav

cd ..

echo.
echo.
echo Insert Disk 1
pause
echo.
echo.

call c:\util\qf b:
label b: ASSD1V2_0

copy d:\data1.arj b:

copy install\install.exe b:
copy install\install.144 b:install.nfo
copy install\dearj.exe b:

echo.
echo.
echo Insert Disk 2
pause
echo.
echo.

call c:\util\qf b:
label b: ASSD2V2_0

copy d:\data2.arj b:

echo.
echo.
echo Insert Disk 3
pause
echo.
echo.

call c:\util\qf b:
label b: ASSD3V2_0

copy d:\data3.arj b:

echo.
echo.
echo Insert Disk 4
pause
echo.
echo.

call c:\util\qf b:
label b: ASSD4V2_0

copy d:\data4.arj b:
copy d:\data5.arj b:
copy d:\data6.arj b:
