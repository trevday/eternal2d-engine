#include "SoundManager.hpp"

#include <SDL2/SDL.h>

SoundManager::SoundManager() {}
SoundManager::~SoundManager() {}

SoundManager& SoundManager::instance() {
  static SoundManager instance;

  return instance;
}

bool SoundManager::init() {
  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
    SDL_Log("Mixer could not initialize! Mixer Error: %s", Mix_GetError());
    return false;
  }
  return true;
}

void SoundManager::shutdown() { Mix_CloseAudio(); }

void SoundManager::PlaySound(std::shared_ptr<SDLSoundWrapper> sound,
                             int times) {
  Mix_PlayChannel(-1, sound->GetChunk(), times);
}
