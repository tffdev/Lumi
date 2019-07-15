#include <stdio.h>
#include <filesystem.h>
#include <objectasset.h>
#include <luamanager.h>
#include <configmanager.h>
#include <objectdatabase.h>
#include <lualibrary.h>
#include <windowmanager.h>
/**
 * Luma Game Creator - version 0.0.1
 * --------------------------------------------------------
 * Report bugs and download new versions at https://github.com/tfcat/lumagamecreator
 * Copyright (C) 2019-2019, by Daniel Brier (danbrierly@gmail.com)
 *
 *
 * This library is distributed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

int main(int, char*[]) {
  ObjectDatabase obj_database;
  LuaManager lmanager;
  ConfigManager conf = FileSystem::load_config();
  WindowManager window_manager(&conf, true);
  lmanager.load_library(&obj_database, &window_manager);

  lmanager.execute("instance_create(objTest)");
  lmanager.execute("instance_create(objTest3)");
  lmanager.execute("instance_create(objTest)");
  lmanager.execute("instance_create(objTest2)");

  while(window_manager.is_open()) {
      sf::Event e;
      while(window_manager.poll_events(e)){
          if(e.type == sf::Event::Closed) window_manager.close();
        }
      lmanager.run_update_function();

      window_manager.clear();
      lmanager.run_draw_function();
      window_manager.display();
    }
}

