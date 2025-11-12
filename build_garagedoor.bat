@echo off
setlocal

set "GCC=Z:\GarageDoor\gcc_win98\bin\gcc.exe"
set "WINDRES=Z:\GarageDoor\gcc_win98\bin\windres.exe"

cd /d "%~dp0"

set "SRC=GarageDoor\GarageDoor.c"
set "RC=GarageDoor\GarageDoor.rc"
set "OUTDIR=%CD%\out"
set "OUT=GarageDoor.exe"

echo ===============================
echo GarageDoor Build Script (C version - XP compatible)
echo ===============================

if not exist "%GCC%" (
  echo ERROR: compiler not found at "%GCC%"
  pause
  exit /b 1
)

if not exist "%WINDRES%" (
  echo ERROR: windres not found at "%WINDRES%"
  pause
  exit /b 1
)

if not exist "%SRC%" (
  echo ERROR: source %SRC% not found in %CD%
  pause
  exit /b 1
)

if not exist "%RC%" (
  echo ERROR: resources %RC% not found in %CD%
  pause
  exit /b 1
)

echo(
echo === RESOURCE COMPILATION ===
"%WINDRES%" -i "%RC%" -o "%OUTDIR%\GarageDoor.o"
set "RCERR=%ERRORLEVEL%"
echo resource compilation exit code: %RCERR%
if %RCERR% neq 0 (
  echo ERROR: resource compilation failed
  pause
  exit /b %RCERR%
)

echo(
echo === SOURCE COMPILATION ===
"%GCC%" "%SRC%" "%OUTDIR%\GarageDoor.o" -o "%OUTDIR%\%OUT%" -lkernel32 -lshell32 -luser32
set "CCERR=%ERRORLEVEL%"
echo compile exit code: %CCERR%
if %CCERR% neq 0 (
  echo ERROR: compilation failed
  pause
  exit /b %CCERR%
)

if exist "%OUTDIR%\%OUT%" (
  echo(
  echo SUCCESS: created "%OUTDIR%\%OUT%"
  dir "%OUTDIR%\%OUT%"
  pause
  exit /b 0
) else (
  echo ERROR: "%OUTDIR%\%OUT%" not found after compilation.
  pause
  exit /b 1
)
