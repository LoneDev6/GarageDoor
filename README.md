![](https://img.shields.io/github/stars/LoneDev6/GarageDoor.svg) ![](https://img.shields.io/github/forks/LoneDev6/GarageDoor.svg) ![](https://img.shields.io/github/issues/LoneDev6/GarageDoor.svg)
# GarageDoor

First translation hack for the Japanese videogame [GARAGE: Bad Dream Adventure  ｢ガラージュ｣](https://lostmediaarchive.fandom.com/wiki/Garage:_Bad_Dream_Adventure_(Limited_Release_1999_Japanese_Point-and-Click_Game) "GARAGE: Bad Dream Adventure  ｢ガラージュ｣")


### Features

- Intercept and translate game text at runtime
- Dump text to a file at runtime
- Translate text without restarting the game
- Game textures injection

# 💿 How to install the game

**Downloading & preparing the game for Windows OS**

1. Download *garage.7z* at <https://archive.org/download/GarageBadDreamAdventure/garage.7z>
2. Open *garage.7z* and move *garage.img.ecm* out of the compressed file.
3. Download Universal Extractor 2 at <http://m.majorgeeks.com/mg/get/universal_extractor_2,1.html>
4. Open *UniExtractRC3.zip* and move the UniExtract folder out of the compressed file
5. Run *UniExtract.exe* and complete the setup
6. Use UniExtract to extract *garage.img.ecm* & create *garage.img*
7. Download WinCDEmu at <https://github.com/sysprogs/WinCDEmu/releases/download/v4.1/WinCDEmu-4.1.exe> and complete the installation setup
8. Once setup is complete, right click on *garage.img*, click on "Select drive letter & mount" & click OK
9. Find your CD Drive and open *CD Drive (?:) GARAGE*
10. Highlight everything in the file, then copy & paste the files to a different uncompressed folder.

# 💾 How to install the patch
- Download [latest release .zip](https://github.com/LoneDev6/GarageDoor/releases/latest) and extract contents into your **Garage** installation folder
- Run `LaunchGame.bat`

#### Note
if you want to try the **experimental textures** translation (that can lead to crashes) download [this repo directly](https://github.com/LoneDev6/GarageDoor/archive/master.zip) and paste the `dir_data` folder inside your **Garage** installation folder

**Changing the games aspect ratio for Windows OS (Optional)**

16. Right click on *Garage.exe*
17. Click on Properties
18. Click on Compatibility
19. Check the "Run in 640x480 screen resolution" & "Disable fullscreen optimizations" options
20. Click Apply


## How to contribute
#### Texts
- **Clone** the repo
- Download the last .zip file from releases
- Copy and paste everything into your Garage game root folder (replace files if needed)
- Run `LaunchGame.bat`
- Play the game and when you find an untraslated text the program will dump it and add it to the file `translation.ini`
- Edit the file `translation.ini` (no need to restart or close the game) and translate the new text (default value `NOT_TRANSLATED_TEXT`)
- Be sure not to break the .ini file removing `=` symbol, `[Phrases] `and `[Settings]`
- If you want you can submit a pull request so I can merge your translations with the main ones

#### Textures (unstable)
Remember that this is experimental and may lead to crashes.
- Use [gimp](https://www.gimp.org/downloads/ "gimp") to open my blank templates in `dir_data/assets`
- Edit them with your better translations
- Export them to `.bmp `
- **Open them with** [paint.net](https://www.getpaint.net/download.html "paint.net") and **save them back again** with 8-bit setting (fixes game crash probably due unsupported bmp)

#### Intro
- Intro texts are images stored in `dir_data\open.swf` file
- You have to edit it file using an extractor like "Flash Decompiler Trillix"

## Contributors
### 💻Development and reverse engineering
- [LoneDev](https://github.com/LoneDev6 "LoneDev")

### 🎥Director 6 images patch
- [LoneDev](https://github.com/LoneDev6 "LoneDev")
- TOMYSSHADOW
- nosamu

### 📕Translations
- [LoneDev](https://github.com/LoneDev6 "LoneDev")
- [Morgan](https://www.youtube.com/channel/UClroPL_xY9RGlMbQJIMiiIw)
- FELON
- Saint


##### Icon
- [LoneDev](https://github.com/LoneDev6 "LoneDev")
- [Vecteezy](https://www.vecteezy.com/free-vector/garage)
