<center>
<img src="https://raw.githubusercontent.com/tfcat/LumaGameCreator/master/promotional/Logo.png">
</center>

# Luma Game Creator - version 0.0.1

Report bugs and download new versions at https://github.com/tfcat/lumagamecreator

Copyright (C) 2019-2019, by Daniel Brier-Allen (danbrierly@gmail.com)

0.0.1 Roadmap
--------------------------------------------------------
End result will:
* display a window adhering to settings in config.xml
* have unique objects that run/can run Lua code on creation and on every frame
* have a small API written in C++ which is accessible from Lua
* let objects draw shapes onto the screen
* let objects draw sprite assets onto the screen

Implement basic, unoptimised versions of all listed modules:
- [x] FileSystem (Virtual file system)
- [ ] XMLLoader
- [ ] LuaManager
- [ ] ObjectManager
- [ ] ConfigManager
- [ ] WindowManager
- [ ] AssetManager

Data Types:
- [ ] ImageAsset
- [x] ObjectAsset

Game folder structure (for now):
```
📁
┕━ game.exe
┕━ data
	┕━ config.xml (window config, general game settings etc)
	┕━ images
		┕━ image.png
	┕━ objects
		┕━ objTest.xml
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
