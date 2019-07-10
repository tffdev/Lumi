#include "include/configasset.h"

ConfigAsset::ConfigAsset(std::string window_title, int windowsize_x, int windowsize_y, unsigned int window_drawcolor)
    : window_title(window_title),
      window_draw_color(sf::Color(window_drawcolor)),
      window_size(sf::Vector2i(windowsize_x, windowsize_y)) {
}

sf::Vector2<int> ConfigAsset::get_window_size() {
    return window_size;
}

sf::Color ConfigAsset::get_window_draw_color() {
    return window_draw_color;
}

std::string ConfigAsset::get_window_title() {
    return window_title;
}
