#pragma once
#include <string>
#include <fstream>
#include <pugixml.hpp>
#include <vector>
#include <objectasset.h>
#include <configmanager.h>
#include <sstream>

#define DATA_PATH "../data/"

#define OBJECT_PATH "objects.xml"
#define CONFIG_PATH "config.xml"

/**
 * FileSystem currently reads directly from the OS's regular file system.
 * In future, this will be an intemediary layer that accesses a compressed
 * (and possibly encrypted) resources file to protect developer's code and assets.
 */

namespace FileSystem {
    std::string load_object_file();
    std::string load_sprite_file();
    std::string load_config_file();
    unsigned int hex_string_to_uint(std::string str);
    bool file_exists(std::string filename);
    std::string read_file(std::string filename);

    ConfigManager load_config();
    std::vector<ObjectAsset*> load_objects();
    std::vector<int> load_sprites();
    std::vector<int> load_backgrounds();
}
