#include "hitboxasset.h"

HitboxAsset::HitboxAsset(int shape, int offsetx, int offsety, int sizex, int sizey)
  : shape(shape),
    offset(offsetx, offsety),
    size(sizex, sizey) {}

sf::Vector2i HitboxAsset::get_size() {
  return size;
}

sf::Vector2i HitboxAsset::get_offset() {
  return offset;
}
