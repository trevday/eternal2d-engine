#include "SDLSoundWrapper.hpp"

SDLSoundWrapper::SDLSoundWrapper(Mix_Chunk* ch) : chunk(ch) {}

SDLSoundWrapper::~SDLSoundWrapper() { Mix_FreeChunk(chunk); }

Mix_Chunk* SDLSoundWrapper::GetChunk() const { return chunk; }