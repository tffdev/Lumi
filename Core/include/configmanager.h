#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class ConfigManager {
public:
    ConfigManager(std::string window_title, int windowsize_x, int windowsize_y, unsigned int window_draw_color);
    std::string get_window_title();
    sf::Vector2<int> get_window_size();
    sf::Color get_window_draw_color();
private:
    std::string window_title;
    sf::Color window_draw_color;
    sf::Vector2<int> window_size;
};
