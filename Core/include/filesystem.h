#pragma once
#include <string>
#include <fstream>
#include <pugixml.hpp>
#include <vector>
#include <objectasset.h>
#include <configmanager.h>
#include <sstream>
#include <spriteasset.h>
#include <audioasset.h>
#include <backgroundasset.h>
#include <tilesetasset.h>
#include <roomasset.h>
#include <tilesetdatabase.h>
#include <backgrounddatabase.h>

#define DATA_PATH "../data/"

#define OBJECT_PATH "objects.xml"
#define SPRITE_PATH "sprites.xml"
#define CONFIG_PATH "config.xml"
#define AUDIO_PATH "sounds.xml"
#define BACKGROUND_PATH "backgrounds.xml"
#define TILESET_PATH "tilesets.xml"
#define ROOMS_PATH "rooms.xml"

#define DEBUG_BITMAP_FONT_LOCATION "lumi/debug_bitmap_font.png"

/**
 * FileSystem currently reads directly from the OS's regular file system.
 * In future, this will be an intemediary layer that accesses a compressed
 * (and possibly encrypted) resources file to protect developer's code and assets.
 */

namespace FileSystem {
    ConfigManager                 load_config();
    std::vector<ObjectAsset*>     load_objects();
    std::vector<AudioAsset*>      load_sounds();
    std::vector<SpriteAsset*>     load_sprites();
    std::vector<TextureAsset*>    load_textures();
    std::vector<BackgroundAsset*> load_backgrounds();
    std::vector<TilesetAsset*>    load_tilesets();
    std::vector<RoomAsset*>       load_rooms(TilesetDatabase*, BackgroundDatabase*);

    std::string get_default_room_name();
    unsigned int hex_string_to_uint(std::string str);
    bool file_exists(std::string filename);
    std::string read_file(std::string filename, bool binary = false);
}
