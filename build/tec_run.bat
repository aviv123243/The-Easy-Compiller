
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

echo Building executable from %filename%...
call tec_build_exe.bat "%filename%"

REM Check if the build was successful
if not exist "%basename%.exe" (
    echo Error: Build failed - executable not created
    exit /b 1
)

"%basename%.exe"


endlocal