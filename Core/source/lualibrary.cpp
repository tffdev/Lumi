#include "lualibrary.h"

/**
 * Internal functions
 */
int LuaLibrary::push_environment_to_registry(lua_State* L) {
    return luaL_ref(L, LUA_REGISTRYINDEX);
}

void LuaLibrary::fetch_environment_from_registry(lua_State* L, int index) {
    lua_rawgeti(L, LUA_REGISTRYINDEX, index);
}

void LuaLibrary::remove_environment_from_registry(lua_State* L, int index) {
    luaL_unref(L, LUA_REGISTRYINDEX, index);
}

void LuaLibrary::run_string_in_environment(lua_State* L, int index, std::string command) {
    luaL_loadstring(L, command.c_str());
    LuaLibrary::fetch_environment_from_registry(L, index);
    lua_setupvalue(L, -2, 1);
    if(lua_pcall(L, 0, LUA_MULTRET, 0) != 0)
        throw "Error in run_string_in_instance_environment: " + std::string(lua_tostring(L, -1));
}

int LuaLibrary::create_new_instance_environment(lua_State* L, int x, int y) {
    // Run lua-side event which creates a new
    // object environment and pushes it into the instance table
    // TODO: Replace this with a completely C-only function.
    lua_getglobal(L, "__luma_system");
    lua_getfield(L, -1, "create_new_instance_environment");
    lua_call(L, 0, 1);

    // set the instance's default values
    lua_pushnumber(L, x);
    lua_setfield(L, -2, "x");

    lua_pushnumber(L, y);
    lua_setfield(L, -2, "y");

    int instance_id = LuaLibrary::push_environment_to_registry(L);
    lua_pop(L, 1);

    L->object_database->add_instance(new InstanceAsset(instance_id));
    return instance_id;
}

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
    // __luma_system:get_object_id("objTest") --> 1
    std::string name(lua_tostring(L, -1));
    if(L->object_database == nullptr) throw_db_error();

    if(!L->object_database->object_name_exists(name)) {
        return 0; // return 0 results == nil
    }
    int id = L->object_database->get_object_id(name);
    lua_pushnumber(L, id);
    return 1;
}

int luma_system_instance_create(lua_State* L) {
    /*
     * Create new environment table (with defaults)
     * Within the environment, run object creation code and then run its "init" function
     * push environment into __luma_system.containers.instances_buffer
     */

    int id = static_cast<int>(lua_tointeger(L, -3));
    int x  = static_cast<int>(lua_tointeger(L, -2));
    int y  = static_cast<int>(lua_tointeger(L, -1));

    // Build command: object code then run init
    std::string command(L->object_database->get_object_code(id) + "\n__luma_system:try_running(init)\n");
    // Load command
    if(luaL_loadstring(L, command.c_str()) != 0)
        throw "Error loading object code: " + std::string(lua_tostring(L, -1));

    int instance_id = LuaLibrary::create_new_instance_environment(L, x, y);

    // Fetch instance environment we just made and assign it!
    LuaLibrary::fetch_environment_from_registry(L, instance_id);
    lua_setupvalue(L, -2, 1);

    // Call command
    if(lua_pcall(L, 0, LUA_MULTRET, 0) != 0)
        throw "Error running object code: " + std::string(lua_tostring(L, -1));

    return 0;
}

void LuaLibrary::load_library(LuaManager* lmanager, ObjectDatabase* object_database) {
    // Register Lua state variablse
    lmanager->pass_object_database_into_state(object_database);

    // Register global functions
    lmanager->register_function(lua_library_test, "lua_library_test");

    // Register __luma_system functions
    lmanager->register_luma_system_function(luma_system_test, "luma_system_test");
    lmanager->register_luma_system_function(luma_system_instance_create, "instance_create");
    lmanager->register_luma_system_function(luma_system_get_object_id, "get_object_id");
}
