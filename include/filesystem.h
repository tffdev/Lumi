#pragma once
#include <string>
#include <fstream>

#define DATA_PATH "data/"
#define OBJECT_PATH "data/test_data/note.xml"

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
}
