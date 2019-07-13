#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class ConfigManager {
public:
    ConfigManager(std::string window_title, unsigned int windowsize_x, unsigned int windowsize_y, unsigned int window_draw_color);
    std::string get_window_title();
    sf::Vector2u get_window_size();
    sf::Color get_window_draw_color();
    bool get_fullscreen();
    void set_fullscreen(bool);
private:
    std::string window_title;
    sf::Color window_draw_color;
    sf::Vector2u window_size;
    bool fullscreen;
};
