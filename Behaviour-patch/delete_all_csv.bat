@echo off
setlocal enabledelayedexpansion

set "root=%cd%"

for /r %%F in (*.csv) do (
    set "fp=%%~dpF"
    set "rel=!fp:%root%=!"

    rem Count slashes in the relative path
    set "lvl=0"
    for %%X in ("!rel:\= !" ) do set /a lvl+=1

    rem Check if depth is 1, 2 or 3
    if !lvl! leq 3 (
        del /q "%%F"
    )
)

endlocal
