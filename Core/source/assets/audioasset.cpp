#include "include/audioasset.h"
#include <filesystem.h>

/**
 * @brief Given the data in the form of a string of bytes, loads a music asset into this instance.
 * @param music_data The music file's data as a string.
 */
AudioAsset::AudioAsset(unsigned long long id, std::string name, std::string path) : id(id), name(name), path(path) {
  load_audio();
}

/**
 * @brief Load the audio into memory
 */
void AudioAsset::load_audio() {
  std::string music_data = FileSystem::read_file(path, true);
  SDL_RWops* rw = SDL_RWFromConstMem(&music_data[0], static_cast<int>(music_data.size()));
  audio = Mix_LoadWAV_RW(rw, true);
  if(audio == nullptr) throw "Audio is null:" + std::string(Mix_GetError());
  loaded = true;
}

/**
 * @brief Deallocates music memory on destruction
 */
AudioAsset::~AudioAsset() {
  if(loaded) {
    printf("Freeing music.\n");
    Mix_FreeChunk(audio);
  }
}

/**
 * @brief Get the audio contained in this instance.
 * @return Mix_Music pointer containing the audio.
 */
Mix_Chunk* AudioAsset::get_audio() {
  if(!loaded) load_audio();
  return audio;
}

std::string AudioAsset::get_name() {
  return name;
}

unsigned long long AudioAsset::get_id() {
  return id;
}
