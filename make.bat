@echo off

set CFLAGS=/DGLEW_STATIC /Iinclude /EHsc /O2
set LIBS=/LIBPATH:lib glew32s.lib glfw3.lib opengl32.lib User32.lib Gdi32.lib Shell32.lib msvcrt.lib /NODEFAULTLIB:libcmt.lib

mkdir objs

call :compile escaper
call :compile shader

link objs\*.obj %LIBS% /OUT:a.exe

rmdir /s /q objs

:compile
cl %CFLAGS% /c src\%~1.c /Foobjs\%~1.obj
exit /b 0