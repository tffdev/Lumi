#include "include/engine.h"

LumiEngine::LumiEngine() : conf(FileSystem::load_config()), window_manager(&conf) {}

void LumiEngine::run() {
  if(lmanager.load_object_code(&obj_database) != LUA_OK)
      window_manager.bluescreen(lmanager.get_error(&obj_database));

  lmanager.load_library(&obj_database, &window_manager, &spr_database, &input_manager, &audio_database, &room_manager);

  // So it initialises current room width/height
  lmanager.execute("set_room(" + std::to_string(room_manager.get_default_room_id()) + ")");

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
