#pragma once
#include <luamanager.h>

namespace LuaLibrary {
    void load_library(LuaManager* lmanager, ObjectDatabase* object_database);
    int push_environment_to_registry(lua_State* L);
    void fetch_environment_from_registry(lua_State* L, int index);
    void remove_environment_from_registry(lua_State* L, int index);
    int create_new_instance_environment(lua_State* L, int x, int y);
    void run_string_in_environment(lua_State* L, int index, std::string command);
    [[ noreturn ]] void throw_db_error();
    int lua_library_test(lua_State* L);
    int luma_system_test(lua_State* L);
    int luma_system_get_object_id(lua_State* L);
    int luma_system_instance_create(lua_State* L);
    int lua_draw_square(lua_State*);
};
