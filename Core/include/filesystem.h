#pragma once
#include <string>
#include <fstream>
#include <pugixml.hpp>
#include <vector>
#include <objectasset.h>
#include <configmanager.h>
#include <sstream>
#include <spriteasset.h>
#include <texturedatabase.h>
#include <audioasset.h>
#include <backgroundasset.h>

#define DATA_PATH "../data/"

#define OBJECT_PATH "objects.xml"
#define SPRITE_PATH "sprites.xml"
#define CONFIG_PATH "config.xml"
#define AUDIO_PATH "sounds.xml"
#define BACKGROUND_PATH "backgrounds.xml"

/**
 * FileSystem currently reads directly from the OS's regular file system.
 * In future, this will be an intemediary layer that accesses a compressed
 * (and possibly encrypted) resources file to protect developer's code and assets.
 */

namespace FileSystem {
    std::string load_object_file();
    std::string load_sprite_file();
    std::string load_config_file();
    std::string load_texture_file();
    std::string load_sounds_file();
    std::vector<BackgroundAsset*> load_backgrounds();
    ConfigManager              load_config();
    std::vector<ObjectAsset*>  load_objects();
    std::vector<AudioAsset*>   load_sounds();
    std::vector<SpriteAsset>   load_sprites(TextureDatabase& texture_manager);
    std::vector<TextureAsset*> load_textures();

    unsigned int hex_string_to_uint(std::string str);
    bool file_exists(std::string filename);
    std::string read_file(std::string filename, bool binary = false);
}
