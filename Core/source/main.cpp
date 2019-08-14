/**
 * Lumi Game Creator - version 0.0.1
 * --------------------------------------------------------
 * Report bugs and download new versions at https://github.com/tfcat/lumigamecreator
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
#include <stdio.h>
#include <filesystem.h>
#include <objectasset.h>
#include <luamanager.h>
#include <configmanager.h>
#include <objectdatabase.h>
#include <lualibrary.h>
#include <windowmanager.h>
#undef main

void run_game();

int main(int, char*[]) {
  try {
    run_game();
  } catch (const std::exception& e) {
    printf("Error in run_game: %s\n", e.what());
  }
}

void run_game() {
  ConfigManager  conf = FileSystem::load_config();
  WindowManager  window_manager(&conf);
  InputManager   input_manager;
  ObjectDatabase obj_database;
  SpriteDatabase spr_database;
  AudioDatabase  audio_database;
  LuaManager     lmanager;
  RoomManager    room_manager;

  if(lmanager.load_object_code(&obj_database) != LUA_OK)
      window_manager.bluescreen(lmanager.get_error(&obj_database));

  lmanager.load_library(&obj_database, &window_manager, &spr_database, &input_manager, &audio_database, &room_manager);

  // run initial room creation code
  if(lmanager.execute(room_manager.get_current_room()->get_creation_code()) != LUA_OK)
    window_manager.bluescreen(lmanager.get_error(&obj_database));

  SDL_Event e;
  int until_bluescreen = 100;
  while(window_manager.is_open()) {
      Uint32 ticks = SDL_GetTicks();
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) window_manager.close();
        input_manager.process_events(&e);
      }

      // process stuff
      if(lmanager.run_update_function() != LUA_OK)
        window_manager.bluescreen(lmanager.get_error(&obj_database));

      // until_bluescreen -= 1;
      std::string err("This is a fake bluescreen error. This is a fake bluescreen error. This is a fake bluescreen error. This is a fake bluescreen error.");
      if(until_bluescreen <= 0) window_manager.bluescreen(err);

      window_manager.set_camera_position(
            lmanager.get_global_double("camera_x"),
            lmanager.get_global_double("camera_y"));

      //draw
      window_manager.clear();
      room_manager.draw_backgrounds(&window_manager);

      if(lmanager.run_draw_function() != LUA_OK)
        window_manager.bluescreen(lmanager.get_error(&obj_database));

      // vsync
      // TODO: replace "60" with FPS.
      Uint32 delay = (1000/60) - (SDL_GetTicks() - ticks);
      if(delay > (1000/60)) delay = (1000/60);
      SDL_Delay(delay);

      room_manager.draw_tiles(&window_manager);

      window_manager.display();

      input_manager.clear_pressed_keys();
  }
}

