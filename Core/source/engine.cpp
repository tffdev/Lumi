#include "include/engine.h"

LumiEngine::LumiEngine() {}

void LumiEngine::run() {
  if(lmanager.load_object_code(&obj_database) != LUA_OK)
      window_manager.bluescreen("ERROR LOADING OBJECT CODE", lmanager.get_error(&obj_database));

  lmanager.load_library(&obj_database, &window_manager, &spr_database, &input_manager, &audio_database, &room_manager);

  // Set current room
  lmanager.execute("set_room(" + std::to_string(room_manager.get_default_room_id()) + ")");

  SDL_Event e;
  while(window_manager.is_open()) {
      Uint32 ticks = SDL_GetTicks();
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) window_manager.close();
        input_manager.process_events(&e);
      }

      // process stuff
      if(lmanager.run_update_function() != LUA_OK)
        window_manager.bluescreen("ERROR IN UPDATE FUNCTION", lmanager.get_error(&obj_database));

      window_manager.set_camera_position(
            lmanager.get_global_double("camera_x"),
            lmanager.get_global_double("camera_y"));

      //draw
      window_manager.clear();
      room_manager.draw_backgrounds(&window_manager);

      room_manager.draw_tiles(&window_manager);

      if(lmanager.run_draw_function() != LUA_OK)
        window_manager.bluescreen("ERROR IN DRAW FUNCTION", lmanager.get_error(&obj_database));

      window_manager.display();

      input_manager.clear_pressed_keys();

      // vsync
      // TODO: replace "60" with FPS.
      Uint32 delay = std::max<Uint32>((1000/60) - std::min<Uint32>((SDL_GetTicks() - ticks), 1000/60), 0);
      SDL_Delay(delay);
  }
}
