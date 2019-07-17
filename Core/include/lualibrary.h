#pragma once
#include <luamanager.h>

namespace LuaLibrary {
    [[ noreturn ]] void throw_db_error();
    int lua_library_test(lua_State* L);

    int luma_system_test(lua_State* L);
    int luma_system_get_object_id(lua_State* L);
    int luma_system_get_sprite_id(lua_State* L);
    int luma_system_instance_create(lua_State* L);
    int luma_system_process_in_environment(lua_State*);

    int lua_draw_sprite(lua_State*);
};
