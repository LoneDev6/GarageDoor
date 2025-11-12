@echo off
setlocal enabledelayedexpansion

REM === CONFIG ===
set "FFMPEG=ffmpeg"
set "FFPROBE=ffprobe"

echo ============================================
echo Converting all BMP files in "%cd%"
echo to pixel format rgb555le (skipping if already)
echo ============================================
echo.

for /r %%F in (*.bmp) do (
    echo Processing: %%~fF

    REM Ottieni il pixel format con ffprobe
    for /f "tokens=2 delims=," %%A in ('"%FFPROBE%" -v error -select_streams v:0 -show_entries stream=pix_fmt -of csv=p=0 "%%~fF" 2^>nul') do (
        set "PIX=%%A"
    )

    if /i "!PIX!"=="rgb555le" (
        echo Already rgb555le, skipping
    ) else (
        "%FFMPEG%" -y -i "%%~fF" -pix_fmt rgb555le -vcodec bmp "%%~dpnF_tmp.bmp" >nul 2>&1
        if exist "%%~dpnF_tmp.bmp" (
            del /q "%%~fF"
            ren "%%~dpnF_tmp.bmp" "%%~nxF"
            echo Converted successfully
        ) else (
            echo Failed to convert
        )
    )
)

echo.
echo All done!
pause
