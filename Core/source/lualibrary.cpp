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
  int luma_system_get_sprite_id(lua_State* L) {
    std::string name(lua_tostring(L, -1));

    lua_pushstring(L, "sprite_database");
    lua_gettable(L, LUA_REGISTRYINDEX);
    SpriteDatabase* spr_database = static_cast<SpriteDatabase*>(lua_touserdata(L, -1));

    if(spr_database == nullptr) throw_db_error();

    if(!spr_database->sprite_exists(name)) {
      return 0; // return 0 results == nil
    }

    int id = spr_database->get_sprite_id(name);
    lua_pushnumber(L, id);
    return 1;
  }

  /**
   * @brief Draws a subimage of a sprite at given coordinates onto the window held in the
   * Luastate's WindowManager registry slot. `draw_sprite(sprite_index, sprite_subimage, x, y)`
   * @param L The passed Lua state
   * @return Nil
   */
  int lua_draw_sprite(lua_State* L) {
    unsigned long long sprite_id = static_cast<unsigned long long>(lua_tonumber(L, -4));
    int subimage = static_cast<int>(lua_tonumber(L, -3));
    float x = static_cast<float>(lua_tonumber(L, -2));
    float y = static_cast<float>(lua_tonumber(L, -1));

    lua_pushstring(L, "sprite_database");
    lua_gettable(L, LUA_REGISTRYINDEX);
    SpriteDatabase* sprite_database = static_cast<SpriteDatabase*>(lua_touserdata(L, -1));

    lua_pushstring(L, "window_manager");
    lua_gettable(L, LUA_REGISTRYINDEX);
    WindowManager* window_manager = static_cast<WindowManager*>(lua_touserdata(L, -1));

    SpriteAsset* spr = sprite_database->get_sprite_by_id(sprite_id);
    window_manager->draw(spr, subimage, static_cast<int>(x), static_cast<int>(y));
    return 0;
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
};
