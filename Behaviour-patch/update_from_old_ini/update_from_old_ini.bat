@echo off
setlocal

echo ===============================
echo   Garage TXT Translator
echo ===============================
echo.

REM Set default folder
set "SRCFOLDER=%~dp0patch"

REM Check folder exists
if not exist "%SRCFOLDER%" (
    echo Folder not found: %SRCFOLDER%
    pause
    exit /b
)

REM Check translation.ini
if not exist "translation.ini" (
    echo translation.ini not found in current folder.
    pause
    exit /b
)

echo Using folder: %SRCFOLDER%
echo Running translator...
python "%~dp0update_from_old_ini.py" "%SRCFOLDER%" "translation.ini"

echo.
echo Done.
pause
