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
     * Luma system library
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

    int lua_draw_square(lua_State* L) {
        int x = static_cast<int>(lua_tointeger(L, -2));
        int y = static_cast<int>(lua_tointeger(L, -1));

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
};
