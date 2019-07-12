#include "luamanager.h"
#include <lualibrary.h>

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
    this->execute("__luma_system:push_instances()");
    for(InstanceAsset* instance : L->object_database->get_all_instances()) {
        LuaLibrary::run_string_in_environment(L, instance->get_id(), "__luma_system:try_running(update)");
    }
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

void LuaManager::assign_state_containers(ObjectDatabase* objdatabase, WindowManager* window_manager) {
    L->object_database = objdatabase;
    L->window_manager = window_manager;
}

void LuaManager::load_library(ObjectDatabase* object_database, WindowManager* window_manager) {
    // Register Lua state variablse
    assign_state_containers(object_database, window_manager);

    // Register global functions
    register_function(LuaLibrary::lua_library_test, "lua_library_test");

    // Register __luma_system functions
    register_luma_system_function(LuaLibrary::luma_system_test, "luma_system_test");
    register_luma_system_function(LuaLibrary::luma_system_instance_create, "instance_create");
    register_luma_system_function(LuaLibrary::luma_system_get_object_id, "get_object_id");
}
