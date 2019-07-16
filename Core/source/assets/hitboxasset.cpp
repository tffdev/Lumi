#include "hitboxasset.h"

HitboxAsset::HitboxAsset(int shape, int offsetx, int offsety, int sizex, int sizey)
  : shape(shape),
    offset(offsetx, offsety),
    size(sizex, sizey) {}

Vector2<int> HitboxAsset::get_size() {
  return size;
}

Vector2<int> HitboxAsset::get_offset() {
  return offset;
}
