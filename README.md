# GarageDoor

First translation hack for the Japanese videogame [GARAGE: Bad Dream Adventure  ｢ガラージュ｣](https://lostmediaarchive.fandom.com/wiki/Garage:_Bad_Dream_Adventure_(Limited_Release_1999_Japanese_Point-and-Click_Game) "GARAGE: Bad Dream Adventure  ｢ガラージュ｣").\
Allows launch on modern and old non-Japanese Windows systems while applying necessary compatibility settings, injecting translation DLLs and patching images at runtime.

This was tested on **Windows XP** and **Windows 11**, but it should work on all other versions after **Windows XP** as well.

### Features

- Translate game texts at runtime
- Dump game texts to a file at runtime
- Replace game images at runtime

# 💿 How to install the original game

1. Download [7zip](https://www.7-zip.org/download.html)
2. Download and open [`garage.7z`](https://archive.org/download/GarageBadDreamAdventure/garage.7z)
3. Extract `garage.img.ecm`
4. Download [ECM Tools](https://archive.org/download/ECMToolsV1.0/ECM%20Tools%20v1.0.zip)
5. Drag and drop `garage.img.ecm` into `unecm.exe`
7. Wait the program to finish and obtain `garage.img` from the same folder
8. Download [WinCDEmu Portable](https://wincdemu.sysprogs.org/portable/) and run it
9. Drag and drop `garage.img` into the program
10. Find the mounted virtual CD Drive in "*Computer*" and open "*CD Drive (D:) GARAGE*"
11. Highlight everything in the file, then copy it to a new folder called `Garage` (you can create it anywhere you want)
12. Click on "*Uninstall Driver*" and close **WinCDEmu**
13. You can delete all previously downloaded files except the `Garage` folder

# 💾 How to install the english patch
1. Download latest **GarageDoor** from the [releases](https://github.com/LoneDev6/GarageDoor/releases).
2. Extract contents into the root of your **Garage** game folder
3. Run `GarageDoor.exe`

## Running on Windows 7 and Later

Simply launch `GarageDoor.exe`.

## Running on Non-Japanese Windows XP

1. Open 'Control Panel' > 'Regional and Language Options'.
2. Go to the 'Languages' tab.
3. Check 'Install files for East Asian languages'.
4. Insert a Windows XP installation CD (a Japanese CD may be required).
5. Complete the installation and restart your computer.
6. Go to the 'Advanced' tab.
7. Set 'Language for non-Unicode programs' to 'Japanese'.
8. Restart your computer.

If needed, extract `I386/SR3.CAB` to access required files. You can copy the contents to a USB drive instead of burning a CD.

# Director Patch

This patch updates images at runtime.

## Requirements

You need the following xtras:
- `BMP Import Export.x32`
- `MIX32.X32`
- `budapi.x32`

# Translating the game

## Translating Texts

- To extract the original texts use [DirectorCastRipper](https://github.com/n0samu/DirectorCastRipper)
- Select all the files that are inside `dir_data`
- Enable `TXT` under `Export Formats`
- Delete any text file that you do not need to translate or edit
- Copy and paste the `delete_all_csv.bat` and run it from the `Exports` folder
- Copy the contents of the `Exports` folder to the `dir_data/patch/` folder

Copy and paste the script `fix_cast_ripper_txts.py` and `fix_cast_ripper_txts.bat` into the `Exports` folder and run `fix_cast_ripper_txts.bat` (RUN IT ONLY ONE TIME!).\
This script is used to make the txt readable and editable.

When editing files via Notepad++ or VSCode, on the bottom right, make sure you see `SHIFT-JIS`.

Save your file.

NOTE: Some texts are translated using the `tranlation.ini` file, in case some were hardcoded in the game code and were unreplaceable editing the `.txt` files (for example items obtainment and usage messages).

### FAQ

#### Special texts files rules

Use `＠` to separate dialogues into different boxes.\
Example:
```
Your adaptation level has dropped. You should fix that soon.
You’d better go to the Adjustment Clinic.＠
There’s a sign in front of your house that says “Outer Loop Entrance,” right?
```

Each dialog box supports only 4 lines.

Do not exceed the top line length otherwise messages would start a new line but (game bug) would have little distance from the top line.\
Use this as reference (max length: ~53 characters):\
`-- --------------------------------------------------`.

Do not translate or edit texts after `#` and `~` as they are special tags used by the game.\
Example: `#Index 'オープニング 02'`

You can edit texts after `--`, these are comments used as reference for future readers and are useful to understand where the dialogue happens and who is talking.\
Example: `-- ----------オープニング----------`

If you see blank boxes, you probably made a mistake on saving, the encoding is broken or something else. Get a clean file from the game and re-do your translation.

## Translating Images

- Same steps as the `TXT` export, but select `BMP`
- Delete any text file that you do not need to translate or edit
- Copy and paste the `delete_all_csv.bat` and run it from the `Exports` folder
- Copy the contents of the `Exports` folder to the `dir_data/patch/` folder

### Saving Edited Images

You can edit images with any editor. If the game fails to recognize your BMP files or crashes, try one of these solutions:

- Run the `fix_bmps.bat` script: copy it into the folder containing your edited images and execute it.
- Open your BMP files in Paint.NET and resave them with these settings:
  - 16-bit color depth
  - Median Cut palette
  - Convert to sRGB color profile

If the white background does not appear correctly in-game, reopen the image, manually erase the background, fill it with white, and save it again.

## Other Tips

If you encounter issues or the file does not exist, create an empty `dir_data\patch\log.txt`.

### Game Crash

Crashes may be caused by too many failed image replacements filling the log. Use the BAT file to fix them if needed (requires ffmpeg).

# Developers

[Here](README_DEV.MD) you can find some info about how to build all this stuff yourself.

# Final notes

This logic work fine with any other **Director** game, but this was coded for <em>『ガラージュ』 Garage: Bad Dream Adventure</em> which was made using **Macromedia Director 6**.

-------

## Contributors
### 💻Development and reverse engineering
- [LoneDev](https://github.com/LoneDev6)

### 📕Translations
- [LoneDev](https://github.com/LoneDev6)
- [Morgan](https://www.youtube.com/channel/UClroPL_xY9RGlMbQJIMiiIw)
- FELON
- Saint

### 🎥Director 6 images patch
- [LoneDev](https://github.com/LoneDev6)
- [TOMYSSHADOW](https://github.com/tomysshadow)
- [nosamu](https://github.com/n0samu)