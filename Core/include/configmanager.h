#pragma once
#include <string>
#include <mathlibrary.h>

/**
 * @brief The Color class creates RGBA values given a unsigned int referring to a 32-bit color.
 */
class Color {
public:
  Color(unsigned int color_hex = 0) {
    r = (color_hex >> 24) % 0x100;
    g = (color_hex >> 16) % 0x100;
    b = (color_hex >> 8) % 0x100;
    a = (color_hex >> 0) % 0x100;
  }
  int r,g,b,a;
};

class ConfigManager {
public:
    ConfigManager(std::string window_title, unsigned int windowsize_x, unsigned int windowsize_y, unsigned int window_draw_color, double scale = 1);
    std::string get_window_title();
    Vector2<unsigned int> get_window_size();
    Color get_window_draw_color();
    bool get_fullscreen();
    void set_fullscreen(bool);
    double get_scale();
private:
    std::string window_title;
    Color window_draw_color;
    Vector2<unsigned int> window_size;
    double scale;
    bool fullscreen;
};
