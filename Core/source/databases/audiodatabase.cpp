#include "include/audiodatabase.h"
#include <filesystem.h>

AudioDatabase::AudioDatabase() {
  audio_assets = FileSystem::load_sounds();
  Mix_AllocateChannels(MAX_CHANNELS);
  for(AudioAsset* asset : audio_assets) {
    audio_map.insert(std::pair<std::string, int>(asset->get_name(), asset->get_id()));
  }
}

AudioDatabase::~AudioDatabase() {
  // Stop all audio from playing
  for (int i = 0; i < MAX_CHANNELS; i++) {
    if(Mix_Playing(i)) {
      Mix_HaltChannel(i);
    }
  }

  for(AudioAsset* asset : audio_assets) {
    delete asset;
  }
}

size_t AudioDatabase::get_assets_size() {
  return audio_assets.size();
}

size_t AudioDatabase::get_audio_id(std::string name) {
  try {
    return audio_map.at(name);
  } catch (...) {
    throw "Can't find sound with name " + name;
  }
}

bool AudioDatabase::audio_id_exists(size_t id) {
  if(id < audio_assets.size()) return true;
  return false;
}

bool AudioDatabase::audio_exists(std::string name) {
  try {
    audio_map.at(name);
    return true;
  } catch (...) {
    return false;
  }
}

void AudioDatabase::play_audio(size_t id, bool loop) {
  AudioAsset* sound_to_play = audio_assets.at(id);
  if(sound_to_play == nullptr) throw "Sound asset is null";
  if(sound_to_play->get_audio() == nullptr) throw "Sound data is null";

  int channel = Mix_PlayChannel(-1, sound_to_play->get_audio(), (loop)?-1:0);
  printf("playing on channel %i\n", channel);
  if(channel == -1) { printf("Channels are full!\n"); return; }
  channel_currently_playing[channel] = sound_to_play->get_id();
}

void AudioDatabase::stop_audio(size_t id) {
  for (int i = 0; i < MAX_CHANNELS; i++) {
    if(channel_currently_playing[i] == id && Mix_Playing(i)) {
      Mix_HaltChannel(i);
    }
  }
}
