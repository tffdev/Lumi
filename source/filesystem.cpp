#include "filesystem.h"

bool FileSystem::file_exists(std::string filename) {
    if (FILE *file = fopen((filename).c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

std::string FileSystem::read_file(std::string filename) {
    if(!file_exists(filename)) return std::string();
    std::ifstream stream(filename);
    std::string str((std::istreambuf_iterator<char>(stream)),
                     std::istreambuf_iterator<char>());
    return str;
}

std::string FileSystem::load_object_file() {
    if(!file_exists(OBJECT_PATH))
        throw "Cannot load Object XML file.";
    std::string file_data = read_file(OBJECT_PATH);
    return file_data;
}
