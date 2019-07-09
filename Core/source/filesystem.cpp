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
    if(!file_exists(DATA_PATH + filename)) return std::string();
    std::ifstream stream(DATA_PATH + filename);
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

std::vector<ObjectAsset*> FileSystem::load_objects() {
    pugi::xml_document document;
    std::vector<ObjectAsset*> object_vector;
    document.load_string(FileSystem::load_object_file().c_str());

    for(pugi::xml_node obj_xml : document.children("object")) {
        object_vector.push_back(new ObjectAsset(
                                    obj_xml.child("name").text().as_string(),
                                    obj_xml.child("sprite").text().as_string()));
    }

    return object_vector;
}
