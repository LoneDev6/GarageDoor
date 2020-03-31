![](https://img.shields.io/github/stars/LoneDev6/GarageDoor.svg) ![](https://img.shields.io/github/forks/LoneDev6/GarageDoor.svg) ![](https://img.shields.io/github/issues/LoneDev6/GarageDoor.svg)
# GarageDoor

First translation hack for the Japanese videogame [GARAGE: Bad Dream Adventure  ｢ガラージュ｣](https://lostmediaarchive.fandom.com/wiki/Garage:_Bad_Dream_Adventure_(Limited_Release_1999_Japanese_Point-and-Click_Game) "GARAGE: Bad Dream Adventure  ｢ガラージュ｣")


### Features

- Intercept and translate game text at runtime
- Dump text to a file at runtime
- Translate text without restarting the game
- Game textures injection

### How to contribute
- Clone the repo
- Copy and paste everything into your Garage game root folder (replace files if needed)
- Run `GarageDoor.exe`
- Play the game and when you find an untraslated text the program will dump it and add it to the file `translation.ini`
- Edit the file `translation.ini` (no need to restart or close the game) and translate the new text (default value `OOOOOOOO_TRANSLATE_ME_OOOOOOOOO`)
- Be sure not to break the .ini file removing `=` symbol, `[Phrases] `and `[Settings]`

## Contributors
- [LoneDev](https://github.com/LoneDev6 "LoneDev")
- nosamu
- TOMYSSHADOW
