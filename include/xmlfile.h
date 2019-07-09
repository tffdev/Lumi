#pragma once
#include <string>
#include <pugixml.hpp>
#include <filesystem.h>
#include <stdio.h>
#include <vector>


namespace XMLLoader{
    std::vector<int> load_objects(std::string filename);
    std::vector<int> load_sprites(std::string filename);
    std::vector<int> load_backgrounds(std::string filename);
};

