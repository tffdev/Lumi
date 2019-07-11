#include "luamanager.h"

LuaManager::LuaManager() {
    L = luaL_newstate();
    luaL_openlibs(L);
    int err;
    err = luaL_dostring(L, FileSystem::read_file("main.lua").c_str());
    if(err == 1) throw "Error loading main.lua:\n" + std::string(lua_tostring(L, -1));
}

void LuaManager::execute(std::string str) {
    int err = luaL_dostring(L, str.c_str());
    if(err == 1)
        throw "Error executing Lua string:\n" + std::string(lua_tostring(L, -1));
}

int LuaManager::get_global_int(std::string name) {
    lua_getglobal(L, name.c_str());
    return static_cast<int>(lua_tonumber(L, -1));
}

void LuaManager::run_update_function() {
    this->execute("__luma_system:process_update()");
}

void LuaManager::run_draw_function() {
    this->execute("__luma_system:process_draw()");
}

int LuaManager::register_function(lua_CFunction func, std::string name) {
    lua_register(L, name.c_str(), func);
    return 0;
}

int LuaManager::register_luma_system_function(lua_CFunction func, std::string name) {
    lua_getglobal(L, "__luma_system");
    lua_pushstring(L, name.c_str());
    lua_pushcfunction(L, func);
    lua_settable(L, -3);
    return 0;
}

lua_State* LuaManager::get_lua_state() {
    return L;
}

void LuaManager::pass_object_database_into_state(ObjectDatabase* objdatabase) {
    L->object_database = objdatabase;
}

/**
 * @brief Loads all object code into a table of functions.
 * An object's associated code-instantiation function should be ran every time a new object is created.
 * @param obj_database
 */

/**
 * __luma_system.containers.object_code[<object_id>] = function()
 * //////////// code ///////////////
 * end
 * ... repeat for all code
 */
void LuaManager::load_object_instantiation_code(ObjectDatabase* obj_database) {
    for(ObjectAsset* obj : obj_database->get_all_object_assets()) {

        std::string command("\n__luma_system.containers.object_code[" +
                            std::to_string(obj->get_id() + 1) +
                            "] = function()\n" +
                            obj->get_code() +
                            "\nend\n");

        this->execute(command);
    }
}
