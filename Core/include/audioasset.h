#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>

class AudioAsset
{
public:
  AudioAsset(unsigned long long id, std::string name, std::string path);
  ~AudioAsset();
  Mix_Chunk* get_audio();
  std::string get_name();
  unsigned long long get_id();
  void load_audio();
private:
  unsigned long long id;
  std::string name;
  std::string path;
  Mix_Chunk* audio;
  bool loaded = false;
};
