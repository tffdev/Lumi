Lumi Game Creator - version 0.0.1
--------------------------------------------------------
Lumi Game Creator aims to be a fast, cross-platform
open-source solution for making 2D game prototypes.

Feel free to report bugs or ideas in issues!

Lumi Game Creator is comprised of three main applications:
* **Editor.** An editor that produces XML files containing all information about 
  the code, assets, and entities that a game created in Lumi is comprised of.

* **Translator.** An executable that converts the editor's project files into a 
  single custom filetype which contains everything needed to run your game.

* **Core.** An executable that can read Lumi's custom game filetypes. The 
  custom filetype will be embedded alongside the core executable so that your game can be easily distributed and ran on **any machine**.

Roadmap
--------------------------------------------------------
You can see the progress and future plans of this engine
on [this Trello board.](https://trello.com/b/W8TegB7A/lumi).

Please submit an issue if you have any suggestions at all.

Dependencies:
--------------------------------------------------------
* SDL2
* Lua5.3

Core Requirements
--------------------------------------------------------
This project is built using the QtCreator IDE and qmake build system!

Dependencies:
SDL2 and Lua5.3 MinGW 64-bit libraries.

Notes on Testing
--------------------------------------------------------
The release version of the Lumi core detects if a user has 
certain shared libraries, and installs them temporarily if not.
Test cases do not run this code, so make sure the required shared libraries are
accessible in the test executable environment, otherwise all tests will fail.