@echo off

call ../clenv.bat


::dll 
cl /c add.c  /D _USING_V110_SDK71_ 
link add.obj /dll /def:add.def /out:add.dll


::exe  ��̬dll��ʽ
cl /D _USING_V110_SDK71_ main_dll.c
link add.obj main_dll.obj /out:main_dll.exe


::exe  ��̬lib��ʽ
cl /D _USING_V110_SDK71_ main_lib.c
link add.obj main_lib.obj /out:main_lib.exe


del *.obj
del *.exp
del *.lib

pause



