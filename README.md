![](https://img.shields.io/github/stars/LoneDev6/GarageDoor.svg) ![](https://img.shields.io/github/forks/LoneDev6/GarageDoor.svg) ![](https://img.shields.io/github/issues/LoneDev6/GarageDoor.svg)
# GarageDoor

First translation hack for the Japanese videogame [GARAGE: Bad Dream Adventure  ｢ガラージュ｣](https://lostmediaarchive.fandom.com/wiki/Garage:_Bad_Dream_Adventure_(Limited_Release_1999_Japanese_Point-and-Click_Game) "GARAGE: Bad Dream Adventure  ｢ガラージュ｣")


[Join the Discord server](https://discord.gg/AWtvKs4)

### Features

- Intercept and translate game text at runtime
- Dump game texts to a file at runtime
- Translate text without restarting the game
- Game images recognition and replace at runtime

# :warning:**Only compatible with**
- Windows 7
- Windows 8
- Windows 10

# 💿 How to install the game
1. Download a [preinstalled copy of Garage](https://mega.nz/file/IVkSXIhL#9VRrAMpZBww-voY6N8zvz4z29poUVlMGll3m6fPs2J4)
2. Download [7zip](https://www.7-zip.org/download.html)
3. Right click on `Garage_pre_installed.7z` and select `7zip->Extract in "Garage_pre_installed\"`

Now you have the complete Japanese game extracted. Now read the next step.

# 💾 How to install the english patch
1. Download [latest GarageEnglishPatch](https://mega.nz/file/NBkDFagI#_FTZ-RPG-bAafelRs0dnG7HmNL0FBTDYZcH-gI1N2JI)
2. Extract contents into your **Garage** installation (right click on `GarageEnglishPatch.7z` and select `7zip->Extract in "Garage_pre_installed\"`)
3. Run `GarageOpener.exe`

![](https://i.imgur.com/Vcr7JJv.png)

### Changing the games aspect ratio for Windows OS (optional, may cause issues)
1. Right click on `Garage.exe`
2. Click on Properties
3. Click on Compatibility
4. Check the "Run in 640x480 screen resolution" & "Disable fullscreen optimizations" options
5. Click Apply

-------

# How to contribute
###### Skip this if you're not interested
#### Texts
- Run `GarageOpener.exe` and check `Developer/translator mode`
- Play the game and when you find an untraslated text the program will copy it and add it to the file `translation.ini`
- Edit the file `translation.ini` (no need to restart or close the game) and translate the new text (default value `NOT_TRANSLATED_TEXT`)
- Be sure not to break the .ini file removing `=` symbol, `[Phrases] `and `[Settings]`
- If you want you can submit a pull request so I can merge your translations with the main ones

#### Images
- open `assets_new` folder
- create your own folder to organize everything better, for example name it `various`, or use the `unknown` folder which already exists.
- take a COMPLETE screenshot of the scene, must be `642x482` PRECISELY with no X-Y shifting.
- open it using `GIMP`, remove as much details as possible and keep only the details that caracterize the scene, to allow my tool to recognize that scene.
- **IMPORTANT:** be sure not to keep the 1 pixel borders in the image (make them transparent), I mean the gray borders.
- for this image you can use transparent or green (0, 255, 0) background, but transparent is better
- save the png file
- create a new folder inside your own folder (`various` or `unknown` or...) and call it `translated`
- create a new png file with the same name of your previous file
- edit the initial screenshot translating the parts you want
- delete the useless parts which are not translated and keep only the texts areas
- save it in the `translated` folder (as I said before it must have the same name as the first file)
###### NOTES:
1. if you set the game to run with lower colors please disable it in properties of `Garage.exe` file.
2. this tool was highly tested and works on `Windows 10 19041.264`, I don't know if it works fine on other Windows versions. Tested on `i7 4790k CPU`.
3. I know the image replace has 5-6ms of delay, don't report that since I cannot fix this 
4. there is no need to restart the game each time you edit images. You can just switch back to the game and wait 30 seconds as the tool will rescan the folder for new or edited images.

#### Intro
- Intro texts are images stored in `dir_data\open.swf` file
- You have to edit it file using an extractor like "Flash Decompiler Trillix"

-------

## Contributors
### 💻Development and reverse engineering
- [LoneDev](https://github.com/LoneDev6 "LoneDev")


### 📕Translations
- [LoneDev](https://github.com/LoneDev6 "LoneDev")
- [Morgan](https://www.youtube.com/channel/UClroPL_xY9RGlMbQJIMiiIw)
- FELON
- Saint

### 🎥Director 6 images patch
###### (not used anymore by the patch)
- [LoneDev](https://github.com/LoneDev6 "LoneDev")
- TOMYSSHADOW
- nosamu
