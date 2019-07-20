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
  bool audio_id_exists(unsigned long long id);
  bool audio_exists(std::string name);
  unsigned long long get_assets_size();
  unsigned long long get_audio_id(std::string name);
  void play_audio(unsigned long long id, bool loop = false);
  void stop_audio(unsigned long long id);
private:
  unsigned long long channel_currently_playing[MAX_CHANNELS];
  std::map<std::string, unsigned long long> audio_map;
  std::vector<AudioAsset*> audio_assets;
  unsigned int channel_step;
};
