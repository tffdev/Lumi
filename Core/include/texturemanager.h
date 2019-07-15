#pragma once
#include <textureasset.h>

class TextureManager
{
public:
    TextureManager();
    void insert(std::string path, TextureAsset);
    bool has_texture(std::string);
    TextureAsset& get_texture(std::string);
private:
    std::map<std::string, TextureAsset> textures;
};
