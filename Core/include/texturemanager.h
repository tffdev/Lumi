#pragma once
#include <textureasset.h>
#include <map>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();
    void insert(std::string path);
    bool has_texture(std::string);
    TextureAsset& get_texture(std::string);
    int get_textures_size();
    void destroy_all();
private:
    std::map<std::string, TextureAsset*> textures;
};
