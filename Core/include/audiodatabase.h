#pragma once
#include <SDL2/SDL_mixer.h>
#include <map>
#include <audioasset.h>
#include <vector>

#define MAX_CHANNELS 32
class AudioDatabase {
public:
  AudioDatabase();
  ~AudioDatabase();
  bool audio_id_exists(size_t id);
  bool audio_exists(std::string name);
  size_t get_assets_size();
  size_t get_audio_id(std::string name);
  void play_audio(size_t id, bool loop = false);
  void stop_audio(size_t id);
private:
  size_t channel_currently_playing[MAX_CHANNELS];
  std::map<std::string, size_t> audio_map;
  std::vector<AudioAsset*> audio_assets;
  size_t channel_step;
};
