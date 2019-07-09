#pragma once
#include <string>
#include <fstream>
#include <pugixml.hpp>
#include <vector>
#include <objectasset.h>

#define DATA_PATH "../data/"

#define OBJECT_PATH "objects.xml"

/**
 * FileSystem currently reads directly from the OS's regular file system.
 * In future, this will be an intemediary layer that accesses a compressed
 * (and possibly encrypted) resources file to protect developer's code and assets.
 */

namespace FileSystem {
    std::string load_object_file();
    std::string load_sprite_file();
    bool file_exists(std::string filename);
    std::string read_file(std::string filename);

    std::vector<ObjectAsset*> load_objects();
    std::vector<int> load_sprites();
    std::vector<int> load_backgrounds();
}
