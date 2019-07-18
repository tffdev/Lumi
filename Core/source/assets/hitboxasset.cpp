#include "hitboxasset.h"

/**
 * @brief Create an instance of HitboxAsset. Contains data regarding hitboxes.
 * @param shape Integer referring to the shape of the hitbox as per the enumerator HITBOX_SHAPE.
 * @param offsetx The horizontal distance from the origin of an object to the left side of the hitbox.
 * @param offsety The vertical distance from the origin of an object to the top side of the hitbox.
 * @param sizex The horizontal size of a hitbox.
 * @param sizey The vertical size of a hitbox.
 */
HitboxAsset::HitboxAsset(int shape, int offsetx, int offsety, int sizex, int sizey)
  : shape(shape),
    offset(offsetx, offsety),
    size(sizex, sizey) {}

/**
 * @brief Get the size of a hitbox.
 * @return A 2D vector containing the size values.
 */
Vector2<int> HitboxAsset::get_size() {
  return size;
}

/**
 * @brief Get the offset of the hitbox relative to the object's position.
 * @return A 2D vector containing the offset values.
 */
Vector2<int> HitboxAsset::get_offset() {
  return offset;
}
