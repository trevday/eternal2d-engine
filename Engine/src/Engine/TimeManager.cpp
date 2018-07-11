#include "TimeManager.hpp"

#include <SDL2/SDL.h>
#include <algorithm>

TimeManager::TimeManager() {}
TimeManager::~TimeManager() {}

TimeManager& TimeManager::instance() {
  static TimeManager instance;

  return instance;
}

unsigned int TimeManager::DeltaTime() {
  return TimeManager::instance().lastDelta_;
}

void TimeManager::StablizeFramerate() {
  unsigned int timeTaken = SDL_GetTicks() - lastTick_;
  if (timeTaken < TICKS_PER_FRAME) {
    SDL_Delay(TICKS_PER_FRAME - timeTaken);
  }
  lastDelta_ = SDL_GetTicks() - lastTick_;
  lastTick_ = SDL_GetTicks();
}