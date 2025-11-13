@echo off
setlocal

set "GXX=Z:\GarageDoor\gcc_win98\bin\gcc.exe"

cd /d "%~dp0"

set "SRC=TextTranslator\Main.cpp"
set "OUT=TextTranslator.dll"
set "OUTDIR=%CD%\out"
set "OBJ=%OUTDIR%\Main.o"

echo ===============================
echo Build script - Working directory: %CD%
echo ===============================

if not exist "%GXX%" (
  echo ERROR: compiler not found at "%GXX%"
  exit /b 1
)

if not exist "%SRC%" (
  echo ERROR: source %SRC% not found in %CD%
  exit /b 1
)

del /q compile_log.txt 2>nul
del /q link_log.txt 2>nul

mkdir "%OUTDIR%" 2>nul

echo(
echo === 1) COMPILATION ===
"%GXX%" -c "%SRC%" -I. -std=gnu++11 -O2 -w -o "%OBJ%" > compile_log.txt 2>&1
set "CCERR=%ERRORLEVEL%"
echo compilation exit code: %CCERR%
if %CCERR% neq 0 (
  echo ERROR: compilation failed
  type compile_log.txt
  exit /b %CCERR%
)

if not exist "%OBJ%" (
  echo ERROR: object %OBJ% not produced.
  exit /b 1
)

echo(
echo === 2) LINK ===
"%GXX%" "%OBJ%" -shared -o "%OUTDIR%\%OUT%" ^
  -static-libstdc++ -static-libgcc -static ^
  -lkernel32 -lshlwapi -lwinmm -lgdi32 -luser32 -lstdc++ ^
  -Wl,--export-all-symbols > link_log.txt 2>&1

set "LINKERR=%ERRORLEVEL%"
echo link exit code: %LINKERR%
if %LINKERR% neq 0 (
  echo ERROR: linking failed
  type link_log.txt
  exit /b %LINKERR%
)

if exist "%OUTDIR%\%OUT%" (
  echo(
  echo SUCCESS: created "%OUTDIR%\%OUT%"
  dir "%OUTDIR%\%OUT%"
  exit /b 0
) else (
  echo ERRORE: non trovato "%OUTDIR%\%OUT%" dopo linking.
  type link_log.txt
  exit /b 1
)
