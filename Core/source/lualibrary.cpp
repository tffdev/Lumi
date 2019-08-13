#include <lualibrary.h>

namespace LuaLibrary {
  /**
   * Error functions
   */
  [[ noreturn ]] void throw_db_error() {
    throw "Database-dependant Lua library function called when database has not been initialised.";
  }

  /**
   * Testing functions
   */
  int lua_library_test(lua_State* L) {
    lua_pushnumber(L, 42);
    return 1;
  }

  int luma_system_test(lua_State* L) {
    lua_pushnumber(L, 65894);
    return 1;
  }

  /**
   * Luma Library
   */

  /**
   * @brief Gets the ID of an object given the name of the object. `__luma_system:get_object_id("objTest")`
   * @param L The passed Lua state
   * @return [Integer] The ID of the object.
   */
  int luma_system_get_object_id(lua_State* L) {
    std::string name(lua_tostring(L, -1));

    lua_pushstring(L, "object_database");
    lua_gettable(L, LUA_REGISTRYINDEX);
    ObjectDatabase* obj_database = static_cast<ObjectDatabase*>(lua_touserdata(L, -1));

    if(obj_database == nullptr) throw_db_error();

    if(!obj_database->object_name_exists(name)) {
        return 0; // return 0 results == nil
      }

    int id = obj_database->get_object_id(name);
    lua_pushnumber(L, id);
    return 1;
  }


  /**
   * @brief Gets the ID of a sprite given the name of the sprite. `__luma_system:get_sprite_id("sprTest")`
   * @param L The passed Lua state
   * @return [Integer] The ID of the sprite.
   */
  int luma_system_get_asset_id(lua_State* L) {
    std::string name(lua_tostring(L, -1));

    // check object database
    lua_pushstring(L, "object_database");
    lua_gettable(L, LUA_REGISTRYINDEX);
    ObjectDatabase* obj_database = static_cast<ObjectDatabase*>(lua_touserdata(L, -1));
    if(obj_database == nullptr) throw_db_error();
    if(obj_database->object_name_exists(name)) {
      int id = obj_database->get_object_id(name);
      lua_pushnumber(L, id);
      return 1;
    }

    // check sprite database
    lua_pushstring(L, "sprite_database");
    lua_gettable(L, LUA_REGISTRYINDEX);
    SpriteDatabase* spr_database = static_cast<SpriteDatabase*>(lua_touserdata(L, -1));
    if(spr_database == nullptr) throw_db_error();

    if(spr_database->sprite_exists(name)) {
      int id = spr_database->get_sprite_id(name);
      lua_pushnumber(L, id);
      return 1;
    }

    // check audio database
    lua_pushstring(L, "audio_database");
    lua_gettable(L, LUA_REGISTRYINDEX);
    AudioDatabase* audio_database = static_cast<AudioDatabase*>(lua_touserdata(L, -1));
    if(audio_database == nullptr) throw_db_error();
    if(audio_database->audio_exists(name)) {
      // FIX THIS, all IDs should be unsigned long longs
      unsigned long long id = audio_database->get_audio_id(name);
      lua_pushnumber(L, id);
      return 1;
    }

    // check room database
    lua_pushstring(L, "room_manager");
    lua_gettable(L, LUA_REGISTRYINDEX);
    RoomManager* room_manager = static_cast<RoomManager*>(lua_touserdata(L, -1));
    if(room_manager == nullptr) throw_db_error();
    if(room_manager->get_room_database()->room_exists(name)) {
      unsigned long long id = room_manager->get_room_database()->get_room_id(name);
      lua_pushnumber(L, id);
      return 1;
    }

    return 0; // return 0 results == nil
  }

  /**
   * @brief Process a Lua closure using a given table as a
   * first-class environment. `__luma_system:process_in_environment(function, environment)`
   *
   * @param L The passed Lua state
   * @return Nil
   */
  int luma_system_process_in_environment(lua_State* L) {
    if(lua_isnil(L, -2) == 1) return 0;
    lua_setupvalue(L, -2, 1);
    if(lua_pcall(L, 0, 0, 0) != 0)
      throw "Error processing in environment: " + std::string(lua_tostring(L, -1));
    return 0;
  }

  /**
   * Lua global library
   */

  /**
   * @brief Draws a subimage of a sprite at given coordinates onto the window held in the
   * Luastate's WindowManager registry slot. `draw_sprite(sprite_index, sprite_subimage, x, y)`
   * @param L The passed Lua state
   * @return Nil
   */
  int lua_draw_sprite(lua_State* L) {
    unsigned long long sprite_id = static_cast<unsigned long long>(lua_tonumber(L, -4));
    int subimage = static_cast<int>(lua_tonumber(L, -3));
    double x = lua_tonumber(L, -2);
    double y = lua_tonumber(L, -1);

    lua_pushstring(L, "sprite_database");
    lua_gettable(L, LUA_REGISTRYINDEX);
    SpriteDatabase* sprite_database = static_cast<SpriteDatabase*>(lua_touserdata(L, -1));

    lua_pushstring(L, "window_manager");
    lua_gettable(L, LUA_REGISTRYINDEX);
    WindowManager* window_manager = static_cast<WindowManager*>(lua_touserdata(L, -1));

    SpriteAsset* spr = sprite_database->get_sprite_by_id(sprite_id);
    window_manager->draw(spr, subimage, x, y);
    return 0;
  }

  int lua_key_pressed(lua_State* L) {
    std::string keycode = std::string(lua_tostring(L, -1));

    lua_pushstring(L, "input_manager");
    lua_gettable(L, LUA_REGISTRYINDEX);
    InputManager* input_manager = static_cast<InputManager*>(lua_touserdata(L, -1));

    if(input_manager->has_key(keycode)) {
      lua_pushboolean(L, input_manager->get_key_state(keycode).pressed);
      return 1;
    }

    return 0;
  }

  int lua_key_down(lua_State* L) {
    std::string keycode = std::string(lua_tostring(L, -1));

    lua_pushstring(L, "input_manager");
    lua_gettable(L, LUA_REGISTRYINDEX);
    InputManager* input_manager = static_cast<InputManager*>(lua_touserdata(L, -1));

    if(input_manager->has_key(keycode)) {
      lua_pushboolean(L, input_manager->get_key_state(keycode).down);
      return 1;
    }

    return 0;
  }

  int lua_key_released(lua_State* L) {
    std::string keycode = std::string(lua_tostring(L, -1));

    lua_pushstring(L, "input_manager");
    lua_gettable(L, LUA_REGISTRYINDEX);
    InputManager* input_manager = static_cast<InputManager*>(lua_touserdata(L, -1));

    if(input_manager->has_key(keycode)) {
      lua_pushboolean(L, input_manager->get_key_state(keycode).released);
      return 1;
    }

    return 0;
  }

  int lua_audio_play(lua_State* L) {
    if (lua_gettop(L) != 2) {
      return luaL_error(L, "audio_play expcts 2 arguments. (int, bool)");
    }
    unsigned long long id = static_cast<unsigned long long>(lua_tonumber(L, -2));
    bool loop = lua_toboolean(L, -1);

    lua_pushstring(L, "audio_database");
    lua_gettable(L, LUA_REGISTRYINDEX);
    AudioDatabase* audio_database = static_cast<AudioDatabase*>(lua_touserdata(L, -1));

    printf("playing audio id %llu\n", id);
    audio_database->play_audio(id, loop);
    return 0;
  }

  int lua_audio_stop(lua_State* L) {
    if (lua_gettop(L) != 1) {
      return luaL_error(L, "audio_play expcts 1 arguments. (int)");
    }
    unsigned long long id = static_cast<unsigned long long>(lua_tonumber(L, -1));

    lua_pushstring(L, "audio_database");
    lua_gettable(L, LUA_REGISTRYINDEX);
    AudioDatabase* audio_database = static_cast<AudioDatabase*>(lua_touserdata(L, -1));

    printf("stopping audio id %llu\n", id);
    audio_database->stop_audio(id);
    return 0;
  }

  int lua_set_room(lua_State* L) {
    unsigned long long id = static_cast<unsigned long long>(lua_tonumber(L, -1));

    lua_pushstring(L, "room_manager");
    lua_gettable(L, LUA_REGISTRYINDEX);
    RoomManager* room_manager = static_cast<RoomManager*>(lua_touserdata(L, -1));
    if(room_manager == nullptr) throw_db_error();

    // unload/destroy all current entities (excluding persistent entities)
    luaL_dostring(L, "__luma_system:clear_all_instances()");

    // unload all assets (?)

    // set the new room
    room_manager->set_room(id);

    // run room creation code
    printf("creation code: %s\n", room_manager->get_room_database()->get_asset(id)->get_creation_code().c_str());
    if(luaL_dostring(L, room_manager->get_room_database()->get_asset(id)->get_creation_code().c_str()) != LUA_OK) {
      throw "Room creation code invalid";
    }
    return 0;
  }
};
