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

  int lua_draw_square(lua_State* L) {
    float x = static_cast<float>(lua_tonumber(L, -2));
    float y = static_cast<float>(lua_tonumber(L, -1));

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(20, 20));
    rect.setFillColor(sf::Color(255,255,255));
    rect.setPosition(x, y);

    lua_pushstring(L, "window_manager");
    lua_gettable(L, LUA_REGISTRYINDEX);
    WindowManager* window_manager = static_cast<WindowManager*>(lua_touserdata(L, -1));
    window_manager->draw(rect);

    return 0;
  }

  int lua_draw_sprite(lua_State* L) {
    unsigned long long sprite_id = static_cast<unsigned long long>(lua_tonumber(L, -4));
    int subimage = static_cast<int>(lua_tonumber(L, -3));
    float x = static_cast<float>(lua_tonumber(L, -2));
    float y = static_cast<float>(lua_tonumber(L, -1));

    //printf("Drawing sprite %llu[%i] at %9.1f:%9.1f\n", sprite_id, subimage, x, y);

    lua_pushstring(L, "sprite_database");
    lua_gettable(L, LUA_REGISTRYINDEX);
    SpriteDatabase* sprite_database = static_cast<SpriteDatabase*>(lua_touserdata(L, -1));

    lua_pushstring(L, "window_manager");
    lua_gettable(L, LUA_REGISTRYINDEX);
    WindowManager* window_manager = static_cast<WindowManager*>(lua_touserdata(L, -1));

    sf::Sprite spr = sprite_database->get_sprite_by_id(sprite_id, subimage);
    spr.setPosition(x, y);
    window_manager->draw(spr);
    return 0;
  }

  int luma_system_process_in_environment(lua_State* L) {
    if(lua_isnil(L, -2) == 1) return 0;
    lua_setupvalue(L, -2, 1);
    if(lua_pcall(L, 0, 0, 0) != 0)
      throw "Error processing in environment: " + std::string(lua_tostring(L, -1));
    return 0;
  }
};
