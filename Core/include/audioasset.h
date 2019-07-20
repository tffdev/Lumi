#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>

class AudioAsset
{
public:
  AudioAsset(unsigned long long id, std::string name, std::string& music_data);
  ~AudioAsset();
  Mix_Chunk* get_audio();
  std::string get_name();
  unsigned long long get_id();
private:
  unsigned long long id;
  std::string name;
  Mix_Chunk* audio;
};
