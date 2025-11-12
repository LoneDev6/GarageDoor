# Compiling the launcher and translation DLL

For Windows XP compatibility, install [gcc-for-Windows98](https://github.com/fsb4000/gcc-for-Windows98/). For other systems, any **gcc** compiler should work.

Update the `.bat` files with the correct path to your compiler's `bin` folder.

Run the `.bat` files. The compiled outputs will be in the `out` folder.

# Editing the Director `Behaviour-patch`

You can open the `Behaviour.cst` (unprotected using [ProjectorRays](https://github.com/ProjectorRays/ProjectorRays)) and put the two scripts in 2 new members.\
Then delete the original `Behavior.cct` (`.cct` is protected, `.cst` is unprotected), so that the game would load the new edited one.

Or just edit my `Behaviour.cst` file.

# Editing Intro
- Intro texts are images stored in `dir_data\open.swf` file
- You have to edit it file using an extractor like [JPEXS](https://github.com/jindrapetrik/jpexs-decompiler)

# TODO

- Test if increasing `ExtraMemory` in `Garage.ini` fixes occasional crashes.
- Track patched external casts shared by multiple movies and avoid patching them again if they are still in RAM.