![Luma WIP Logo](https://raw.githubusercontent.com/tfcat/LumaGameCreator/master/promotional/Logo.png)

Luma Game Creator - version 0.0.1
--------------------------------------------------------
Luma Game Creator will a fast and easy
open-source solution for making 2D game prototypes.

Report bugs and download new versions at https://github.com/tfcat/lumagamecreator

Copyright (C) 2019-2019, by Daniel Brier-Allen (danbrierly@gmail.com)

Luma Game Creator is comprised of three main applications:
* **Editor.** An editor that produces XML files containing all information about 
  the code, assets, and entities that a game created in Luma is comprised of.

* **Translator.** An executable that converts the editor's project files into a 
  single custom filetype which contains everything needed to run your game.

* **Core.** An executable that can read Luma's custom game filetypes. The 
  custom filetype will be embedded alongside the core executable so that your game can
  be easily distributed.

Compiling Core
--------------------------------------------------------

This project is built using the QtCreator IDE and qmake build system!

* Download the `SFML` and `lua5.3` development libraries.
* Edit Core/engine.pro so that INCLUDEPATH/DEPENDPATH and LIBS point to your own include/lib directories.
* Open `Core.pro` in QtCreator with any valid configuration and Build!
* (Windows) Copy the SFML and Lua5.3 .dll files into the build directory.
* Run from QtCreator

0.0.1 Core Roadmap
--------------------------------------------------------
0.0.1 result will:
* display a window adhering to settings in config.xml
* have unique objects that run/can run Lua code on creation and on every frame
* have a small API written in C++ which is accessible from Lua
* let objects draw shapes onto the screen
* let objects draw sprite assets onto the screen

Implement basic, unoptimised versions of all listed modules:
- [x] FileSystem (to-be virtual file system)
- [x] LuaManager
- [x] ObjectDatabase
- [x] LuaLibrary
- [x] ConfigManager
- [x] WindowManager
- [ ] ImageDatabase
- [ ] Engine (encapsulates all of the prior)

Data Types:
- [x] ObjectAsset
- [ ] ImageAsset
- [x] InstanceAsset

Game folder structure (for now):
```
📁
┕━ game.exe (our core executable)
┕━ data (in future, will be a single custom file)
	┕━ main.lua (all Lua logicstuffs. hard-coded in future?)
	┕━ config.xml (window config, general game settings etc)
	┕━ objects.xml
	┕━ objects.lua
	┕━ images.xml
	┕━ rooms.xml
	┕━ audio
		┕━ audio.ogg
	┕━ images
		┕━ image.png
	┕━ rooms
		┕━ room0.xml
```

License
--------------------------------------------------------
This library is distributed under the MIT License.

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
