#include "include/audioasset.h"

/**
 * @brief Given the data in the form of a string of bytes, loads a music asset into this instance.
 * @param music_data The music file's data as a string.
 */
AudioAsset::AudioAsset(unsigned long long id, std::string name, std::string& music_data) : id(id), name(name) {
  SDL_RWops* rw = SDL_RWFromMem(&music_data[0], static_cast<int>(music_data.size()));
  audio = Mix_LoadWAV_RW(rw, false);
  if(audio == NULL) throw "Audio is null:" + std::string(Mix_GetError());
}

/**
 * @brief Deallocates music memory on destruction
 */
AudioAsset::~AudioAsset() {
  printf("Freeing music.\n");
  Mix_FreeChunk(audio);
}

/**
 * @brief Get the audio contained in this instance.
 * @return Mix_Music pointer containing the audio.
 */
Mix_Chunk* AudioAsset::get_audio() {
  return audio;
}

std::string AudioAsset::get_name() {
  return name;
}

unsigned long long AudioAsset::get_id() {
  return id;
}
