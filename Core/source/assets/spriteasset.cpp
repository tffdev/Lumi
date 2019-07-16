#include "include/spriteasset.h"

SpriteAsset::SpriteAsset(std::string& name, TextureAsset& texture, std::vector<SubimageRect*> rects, HitboxAsset hitbox):
  texture(texture),
  hitbox(hitbox),
  name(name) {
  // TODO: Better way of managing the subimage size?
  size.x = rects[0]->get_rect().width;
  size.y = rects[0]->get_rect().height;

  // Create sprites from SubimageRect vector
  for(SubimageRect* rect : rects) {
      sf::Sprite sprite;
      sprite.setPosition(0, 0);
      sprite.setTexture(*texture.get_texture_data()); // loads in texture
      sprite.setTextureRect(rect->get_rect());
      subimages.push_back(sprite);
    }
}

Vector2<int> SpriteAsset::get_subimage_size() {
  return size;
}

sf::Sprite SpriteAsset::get_subimage(double subimage) {
  unsigned long long subimage_int = static_cast<unsigned long long>(subimage);

  // Wraparound in the case of subimage number being
  // bigger than the subimage array.
  sf::Sprite spr = subimages.at(subimage_int % subimages.size());
  return spr;
}

std::string SpriteAsset::get_name() {
  return name;
}
