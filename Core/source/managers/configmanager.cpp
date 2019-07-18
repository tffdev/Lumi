#include "include/configmanager.h"

/**
 * @brief Create an instance of ConfigManager which contains all information needed to create the game's window and viewport.
 * @param window_title The title of the window.
 * @param windowsize_x The width of the canvas displayed in the window.
 * @param windowsize_y The height of the canvas displayed in the window.
 * @param window_drawcolor The default background color of the window.
 * @param scale The value to multiply the canvas size by to produce the final window size. (Scale factor of 2 will make window 2x the canvas size.)
 */
ConfigManager::ConfigManager(std::string window_title, unsigned int windowsize_x, unsigned int windowsize_y, unsigned int window_drawcolor, double scale)
  : window_title(window_title),
    window_draw_color(Color(window_drawcolor)),
    window_size(windowsize_x, windowsize_y),
    scale(scale),
    fullscreen(false){}

/**
 * @brief Get the size of the window's canvas.
 * @return 2D vector containing the window's canvas size.
 */
Vector2<unsigned int> ConfigManager::get_window_size() {
  return window_size;
}

/**
 * @brief Get the default draw color of the window.
 * @return Color object containing RGBA values.
 */
Color ConfigManager::get_window_draw_color() {
  return window_draw_color;
}

/**
 * @brief Get the default title of the window.
 * @return Window's title as string.
 */
std::string ConfigManager::get_window_title() {
  return window_title;
}

/**
 * @brief Get the fullscreen state of the window.
 * @return True if the window is fullscreen, false otherwise.
 */
bool ConfigManager::get_fullscreen() {
  return fullscreen;
}

/**
 * @brief Set the fullscreen state of the window.
 * @param set Set to true to set window fullscreen, false otherwise.
 */
void ConfigManager::set_fullscreen(bool set) {
  fullscreen = set;
}

/**
 * @brief Get the canvas:window scaling factor.
 * @return The scaling factor as a double.
 */
double ConfigManager::get_scale() {
  return scale;
}
