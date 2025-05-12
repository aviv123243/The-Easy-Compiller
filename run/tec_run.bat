@echo off
setlocal

set "filename=%~1"
set "basename=%~n1"

if "%filename%"=="" (
    echo Error: Please provide a .ez file
    echo Usage: tec_run.bat filename.ez
    exit /b 1
)

if not exist "%filename%" (
    echo Error: File "%filename%" not found
    exit /b 1
)

if /i not "%~x1"==".ez" (
    echo Error: File must have .ez extension
    exit /b 1
)

REM echo Building executable from %filename%:
REM echo.
call tec_build_exe.bat "%filename%"

if not exist "%basename%.exe" (
    echo Error: Build failed - executable not created
    exit /b 1
)

"%basename%.exe"
del "%basename%.exe" >nul 2>&1


endlocal