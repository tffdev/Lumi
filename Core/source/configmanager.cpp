#include "include/configmanager.h"

ConfigManager::ConfigManager(std::string window_title, int windowsize_x, int windowsize_y, unsigned int window_drawcolor)
    : window_title(window_title),
      window_draw_color(sf::Color(window_drawcolor)),
      window_size(sf::Vector2i(windowsize_x, windowsize_y)) {
}

sf::Vector2<int> ConfigManager::get_window_size() {
    return window_size;
}

sf::Color ConfigManager::get_window_draw_color() {
    return window_draw_color;
}

std::string ConfigManager::get_window_title() {
    return window_title;
}
