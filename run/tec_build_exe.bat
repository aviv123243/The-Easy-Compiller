@echo off
setlocal enabledelayedexpansion

set "filename=%~1"
set "basename=%~n1"

if "%filename%"=="" (
    echo Usage: tec_build_exe.bat filename.ez
    exit /b 1
)

tec "%filename%" 

if errorlevel 1 (
    echo Error: tec failed to generate "%basename%.asm"
    exit /b 1
)

ml64 /c "%basename%.asm" >nul 2>&1
if errorlevel 1 (
    echo Error: ml64 failed to assemble "%basename%.asm"
    exit /b 1
)

link "%basename%.obj" /subsystem:console ^
  /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64" ^
  /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\ucrt\x64" ^
  /libpath:"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\lib\x64" ^
  /defaultlib:kernel32.lib ^
  /defaultlib:msvcrt.lib ^
  /defaultlib:legacy_stdio_definitions.lib >nul 2>&1

if not exist "%basename%.exe" (
    echo Error: link failed to create "%basename%.exe"
    exit /b 1
)

del "%basename%.asm" "%basename%.obj" >nul 2>&1

endlocal
