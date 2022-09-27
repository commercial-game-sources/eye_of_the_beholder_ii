@echo off
call setset bcc
..\msmake aesop.mak
call setset w95
..\wmake /h /f project.mak
..\wmake /h /f project.mak bshape.exe
..\msmake art.mak
..\arc /c50 eye

