#include "include/spriteasset.h"

SpriteAsset::SpriteAsset(TextureAsset& texture, std::vector<SubimageRect*> rects, HitboxAsset hitbox):
  texture(texture),
  hitbox(hitbox) {
  // TODO: Better way of managing the subimage size?
  size.x = rects[0]->get_rect().width;
  size.y = rects[0]->get_rect().height;

  // Create sprites from SubimageRect vector
  for(SubimageRect* rect : rects) {
      sf::Sprite sprite;
      sprite.setPosition(0, 0);
      sprite.setTexture(*texture.get_texture_data());
      sprite.setTextureRect(rect->get_rect());
      subimages.push_back(sprite);
    }
}

sf::Vector2i SpriteAsset::get_subimage_size() {
  return size;
}

sf::Sprite SpriteAsset::get_sprite(double subimage) {
  // Wraparound in the case of subimage number being
  // bigger than the subimage array.
  // Only load texture if get_sprite is called
  unsigned long long subimage_int = static_cast<unsigned long long>(subimage);
  subimage_int %= subimages.size();
  sf::Sprite spr = subimages.at(subimage_int);
  return spr;
}
