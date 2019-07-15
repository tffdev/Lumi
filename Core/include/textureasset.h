#pragma once
#include <SFML/Graphics.hpp>

class TextureAsset
{
public:
    TextureAsset(std::string path);
    sf::Texture* get_texture_data();
    sf::Vector2u get_size();
private:
    sf::Texture texture;
    std::string path;
    bool loaded = false;
};
