<p align="center"><img src="https://github.com/tfcat/LumaGameCreator/blob/master/promotional/Lumi_textonly.png?raw=true"></p>

Lumi Game Creator - version 0.0.1
--------------------------------------------------------
Lumi Game Creator will a fast, cross-platform
open-source solution for making 2D game prototypes.

Feel free to report bugs or ideas in issues!

Lumi Game Creator is comprised of three main applications:
* **Editor.** An editor that produces XML files containing all information about 
  the code, assets, and entities that a game created in Lumi is comprised of.

* **Translator.** An executable that converts the editor's project files into a 
  single custom filetype which contains everything needed to run your game.

* **Core.** An executable that can read Lumi's custom game filetypes. The 
  custom filetype will be embedded alongside the core executable so that your game can
  be easily distributed and ran on **any machine**.

Dependencies:
--------------------------------------------------------
* SDL2
* Lua5.3

Compiling Core
--------------------------------------------------------
This project is built using the QtCreator IDE and qmake build system!

* Download the `SDL2` and `lua5.3` development libraries.
* Edit Core/engine.pro so that INCLUDEPATH/DEPENDPATH and LIBS point to your own include/lib directories.
* Open `Core.pro` in QtCreator with any valid configuration and Build!
* (Windows) Copy the SDL2.dll and Lua5.3.dll files into the build directory.
* Run from QtCreator
