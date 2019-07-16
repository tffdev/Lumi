#pragma once
#include <SFML/Graphics.hpp>
#include <mathlibrary.h>

class TextureAsset
{
public:
    TextureAsset(std::string path);
    sf::Texture* get_texture_data();
    Vector2<unsigned int> get_size();
private:
    sf::Texture texture;
    std::string path;
    bool loaded = false;
};
