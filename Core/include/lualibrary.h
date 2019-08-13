#pragma once
#include <luamanager.h>

namespace LuaLibrary {
    [[ noreturn ]] void throw_db_error();
    void check_errors(lua_State* L);

    int lua_library_test(lua_State* L);

    int luma_system_test(lua_State* L);
    int luma_system_get_asset_id(lua_State* L);
    int luma_system_instance_create(lua_State* L);
    int luma_system_process_in_environment(lua_State*);

    int lua_draw_sprite(lua_State*);
    int lua_set_room(lua_State*);
    int lua_key_down(lua_State*);
    int lua_key_released(lua_State*);
    int lua_key_pressed(lua_State*);

    int lua_audio_play(lua_State*);
    int lua_audio_stop(lua_State*);
};
