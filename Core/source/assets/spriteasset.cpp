#include "include/spriteasset.h"

SpriteAsset::SpriteAsset(std::string& name, TextureAsset& texture, std::vector<SubimageRect*> rects, HitboxAsset hitbox):
  subimages(rects),
  texture(texture),
  hitbox(hitbox),
  name(name) {
  // TODO: Better way of managing the subimage size?
  size.x = rects[0]->get_rect().width;
  size.y = rects[0]->get_rect().height;
}

Vector2<int> SpriteAsset::get_subimage_size() {
  return size;
}

SubimageRect* SpriteAsset::get_subimage(double subimage) {
  unsigned long long subimage_int = static_cast<unsigned long long>(subimage);

  // Wraparound in the case of subimage number being
  // bigger than the subimage array.
  SubimageRect* spr = subimages.at(subimage_int % subimages.size());
  return spr;
}

std::string SpriteAsset::get_name() {
  return name;
}

GLuint SpriteAsset::get_texture_id() {
  return texture.get_texture_id();
}

Vector2<unsigned int> SpriteAsset::get_texture_size() {
  return texture.get_size();
}
