#include "textureasset.h"
#include "filesystem.h"

/**
 * @brief Loads a texture from the virtual filesystem, pushes it into video memory (via OpenGL) and stores a reference to that texture.
 * @param path The virtual filesystem path of the texture image.
 */
TextureAsset::TextureAsset(std::string path): path(path) {
  std::string str = FileSystem::read_file(path, true);

  SDL_RWops* rw = SDL_RWFromMem(&str[0], static_cast<int>(str.size()*sizeof(char)));
  SDL_Surface* surface = IMG_Load_RW(rw, false);

  size.x = static_cast<unsigned int>(surface->w);
  size.y = static_cast<unsigned int>(surface->h);

  glGenTextures(1, &texture_id);

  glBindTexture(GL_TEXTURE_2D, texture_id);

  GLuint mode = GL_RGB;
  if(surface->format->BytesPerPixel == 4) mode = GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  SDL_FreeSurface(surface);
}

/**
 * @brief Unallocates the video memory taken up by this texture.
 */
TextureAsset::~TextureAsset() {
  glDeleteTextures(1, &texture_id);
}

/**
 * @brief Get the ID of this texture which is used to refer to this texture via OpenGL.
 * @return The texture's ID as a GLuint.
 */
GLuint TextureAsset::get_texture_id() {
  return texture_id;
}

/**
 * @brief Get the width and height of the attached texture.
 * @return 2D vector containing the size of the attached texture.
 */
Vector2<unsigned int> TextureAsset::get_size() {
  return size;
}
