#include "include/configmanager.h"

ConfigManager::ConfigManager(std::string window_title, unsigned int windowsize_x, unsigned int windowsize_y, unsigned int window_drawcolor, double scale)
  : window_title(window_title),
    window_draw_color(Color(window_drawcolor)),
    window_size(windowsize_x, windowsize_y),
    scale(scale),
    fullscreen(false){}

Vector2<unsigned int> ConfigManager::get_window_size() {
  return window_size;
}

/**
Color ConfigManager::get_window_draw_color() {
  return window_draw_color;
}

std::string ConfigManager::get_window_title() {
  return window_title;
}

bool ConfigManager::get_fullscreen() {
  return fullscreen;
}
void ConfigManager::set_fullscreen(bool set) {
  fullscreen = set;
}

double ConfigManager::get_scale() {
  return scale;
}
