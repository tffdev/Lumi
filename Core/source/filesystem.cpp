#include "filesystem.h"

bool FileSystem::file_exists(std::string filename) {
    if (FILE *file = fopen((DATA_PATH + filename).c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

std::string FileSystem::read_file(std::string filename) {
    if(!file_exists(DATA_PATH + filename)) throw "File " + filename + " doesn't exist!";
    std::ifstream stream(DATA_PATH + filename);
    std::string str((std::istreambuf_iterator<char>(stream)),
                     std::istreambuf_iterator<char>());
    return str;
}

std::string FileSystem::load_object_file() {
    if(!file_exists(OBJECT_PATH)) throw "Cannot load Object XML file.";
    return read_file(OBJECT_PATH);;
}

std::string FileSystem::load_config_file() {
    if(!file_exists(CONFIG_PATH)) throw "Cannot load Config XML file.";
    return read_file(CONFIG_PATH);
}

std::vector<ObjectAsset*> FileSystem::load_objects() {
    pugi::xml_document document;
    std::vector<ObjectAsset*> object_vector;
    document.load_string(FileSystem::load_object_file().c_str());

    int i = 0;
    for(pugi::xml_node obj_xml : document.children("object")) {
        object_vector.push_back(new ObjectAsset(i,
                                    obj_xml.child("name").text().as_string(),
                                    obj_xml.child("sprite").text().as_string(),
                                    obj_xml.child("code").text().as_string()));
        i++;
    }
    return object_vector;
}

unsigned int FileSystem::hex_string_to_uint(std::string str) {
    unsigned int x;
    std::stringstream ss;
    ss << std::hex << str;
    ss >> x;
    return static_cast<unsigned int>(x);
}

ConfigManager FileSystem::load_config() {
    pugi::xml_document document;
    document.load_string(FileSystem::load_config_file().c_str());

    ConfigManager config_asset(
                document.child("window").child("windowtitle").text().as_string(),
                document.child("window").child("windowsize").child("width").text().as_int(),
                document.child("window").child("windowsize").child("height").text().as_int(),
                hex_string_to_uint(std::string(document.child("window").child("windowdrawcolor").text().as_string()) + "ff")
                );

    return config_asset;
}
