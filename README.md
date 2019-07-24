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

Compiling Core Engine
--------------------------------------------------------

This project is built using the QtCreator IDE and qmake build system!

* Download the `SDL2` and `lua5.3` development libraries.
* Edit Core/engine.pro so that INCLUDEPATH/DEPENDPATH and LIBS point to your own include/lib directories.
* Open `Core.pro` in QtCreator with any valid configuration and Build!
* (Windows) Copy the SDL2.dll and Lua5.3.dll files into the build directory.
* Run from QtCreator

0.0.1 Core Roadmap
--------------------------------------------------------
0.0.1 result will:
* display a window adhering to settings in config.xml
* have unique objects that run/can run predefined Lua code on every frame
* let objects detect user input
* let objects draw sprites onto the screen
* let objects play sounds

Implement basic, unoptimised versions of all listed modules:
- [x] FileSystem (to-be virtual file system)
- [x] LuaLibrary

- [x] LuaManager
- [x] ConfigManager
- [x] WindowManager
- [x] InputManager
- [ ] RoomManager

- [x] ObjectDatabase
- [x] SpriteDatabase
- [x] AudioDatabase
- [x] BackgroundDatabase
- [x] RoomDatabase
- [x] TilesetDatabase

- [x] ObjectAsset
- [x] SpriteAsset
- [x] TextureAsset
- [x] HitboxAsset
- [x] AudioAsset
- [x] BackgroundAsset
- [x] RoomAsset
- [x] TilesetAsset

Game folder structure (for now):
```
📁
┕━ game.exe (our core executable)
┕━ data (in future, will be a single custom file)
	┕━ main.lua (all Lua logicstuffs. hard-coded in future?)
	┕━ config.xml (window config, general game settings etc)
	┕━ objects.xml
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
