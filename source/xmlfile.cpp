#include "xmlfile.h"

std::vector<int> XMLLoader::load_objects(std::string filename) {
    pugi::xml_document document;
    std::vector<int> object_vector;
    document.load_string(FileSystem::read_file(filename).c_str());

    for(pugi::xml_node obj_xml : document.children("object")) {

    }

    return object_vector;
}

//int XMLLoader::size() {
//    int i = 0;
//    for (pugi::xml_node x: document.children()) i++;
//    return i;
//}

//std::string XMLLoader::get(std::string childname) {
//    return document.child(childname.c_str()).text().as_string();
//}

//std::string XMLLoader::get(std::string childname, int index) {
//    int i = 0;
//    for (pugi::xml_node obj_xml: document.children(document.first_child().name())) {
//        if(i == index) {
//            const char* a = obj_xml.child(childname.c_str()).text().as_string();
//            printf("Text as string: %s\n", a);
//            return a;
//        }
//        i++;
//    }
//    return std::string();
//}

