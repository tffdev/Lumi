#include "include/subimagerect.h"

SubimageRect::SubimageRect(int x, int y, int width, int height): rect(x, y, width, height) {}

sf::IntRect SubimageRect::get_rect() {
  return rect;
}
