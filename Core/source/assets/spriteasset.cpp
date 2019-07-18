#include "include/spriteasset.h"

/**
 * @brief Create a sprite asset with an attached texture and subimage rects.
 * @param name Sprite's name as a string.
 * @param texture Sprite's source texture.
 * @param rects Subimage rects of a sprite.
 * @param hitbox The hitbox object to attach to a sprite.
 */
SpriteAsset::SpriteAsset(std::string& name, TextureAsset& texture, std::vector<SubimageRect*> rects, HitboxAsset hitbox):
  subimages(rects),
  texture(texture),
  hitbox(hitbox),
  name(name) {
  // TODO: Better way of managing the subimage size?
  size.x = rects[0]->get_rect().width;
  size.y = rects[0]->get_rect().height;
}

/**
 * @brief Get the width and height of this sprite's subimages.
 * @return Size as a 2D vector.
 */
Vector2<int> SpriteAsset::get_subimage_size() {
  return size;
}

/**
 * @brief Get the rect of a subimage given a subimage index.
 * @param subimage Subimage index.
 * @return A SubimageRect for the given subimage index.
 */
SubimageRect* SpriteAsset::get_subimage(double subimage) {
  unsigned long long subimage_int = static_cast<unsigned long long>(subimage);

  // Wraparound in the case of subimage number being
  // bigger than the subimage array.
  SubimageRect* spr = subimages.at(subimage_int % subimages.size());
  return spr;
}

/**
 * @brief Get the name of this sprite.
 * @return The name of this sprite as a string.
 */
std::string SpriteAsset::get_name() {
  return name;
}

/**
 * @brief Get the ID of the texture attached to this sprite.
 * @return The attached textures's ID as a GLuint.
 */
GLuint SpriteAsset::get_texture_id() {
  return texture.get_texture_id();
}

/**
 * @brief Get the width and height of the attached texture.
 * @return A 2D vector containign the size of the attached texture.
 */
Vector2<unsigned int> SpriteAsset::get_texture_size() {
  return texture.get_size();
}
