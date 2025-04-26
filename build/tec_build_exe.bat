@echo off
setlocal enabledelayedexpansion

set "filename=%~1"
set "basename=%~n1"

tec "%filename%"

ml64 /c "%basename%.asm"

link "%basename%.obj" /subsystem:console ^
  /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64" ^
  /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\ucrt\x64" ^
  /libpath:"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\lib\x64" ^
  /defaultlib:kernel32.lib ^
  /defaultlib:msvcrt.lib ^
  /defaultlib:legacy_stdio_definitions.lib

endlocal