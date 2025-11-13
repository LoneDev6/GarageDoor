@echo off
chcp 65001 >nul

powershell -NoProfile -Command ^
    "[System.Reflection.Assembly]::LoadWithPartialName('System.Windows.Forms') | Out-Null;" ^
    "$result = [System.Windows.Forms.MessageBox]::Show('This script will convert all .txt files from UTF-8 to Shift-JIS. Do you want to continue?', 'Conversion Warning', 'YesNo', 'Warning');" ^
    "exit ([int]($result -eq 'Yes'))"

if %errorlevel% equ 0 (
    exit /b
)

echo Creating backup...
powershell -NoProfile -Command ^
    "$timestamp = (Get-Date).ToString('yyyyMMdd-HHmmss');" ^
    "$backupDir = 'backup-bat-' + $timestamp;" ^
    "New-Item -ItemType Directory -Force -Path $backupDir | Out-Null;" ^
    "Get-ChildItem -Filter '*.txt' | Copy-Item -Destination $backupDir -Force;" ^
    "Write-Host ('Backup created in: ' + $backupDir)" ^
    ""

echo.
echo Converting all .txt files (UTF-8 to Shift-JIS) recursively (excluding backup-bat-* folders)...
echo.

powershell -NoProfile -Command ^
    "$utf8 = [Text.Encoding]::UTF8; $sjis = [Text.Encoding]::GetEncoding(932);" ^
    "Get-ChildItem -Recurse -Filter '*.txt' | Where-Object { $_.DirectoryName -notmatch 'backup-bat-' } | ForEach-Object {" ^
    "  $f = $_.FullName;" ^
    "  try {" ^
    "    $t = [IO.File]::ReadAllText($f, $utf8);" ^
    "    $b = $sjis.GetBytes($t);" ^
    "    [IO.File]::WriteAllBytes($f, $b);" ^
    "    Write-Host ('Converted: ' + $f)" ^
    "  } catch { Write-Host ('Error: ' + $f) -ForegroundColor Red }" ^
    "}"

echo.
echo Done.
pause
