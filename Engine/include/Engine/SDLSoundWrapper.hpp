#ifndef SDL_SOUND_WRAPPER_HPP
#define SDL_SOUND_WRAPPER_HPP

#include <SDL2/SDL_mixer.h>

/**
 * A wrapper class for Mix_Chunks
 */
class SDLSoundWrapper {
 public:
  
  /** Constructs an SDLSoundWrapper */
  SDLSoundWrapper(/** The Mix_Chunk to be wrapped */
                  Mix_Chunk* ch);
  
  /** Destructs an SDLSoundWrapper */
  ~SDLSoundWrapper();

  /**
   * Gets the Mix_Chunk of this wrapper.
   * @return The chunk
   */
  Mix_Chunk* GetChunk() const;

 private:
  
  /** The wrapped Mix_Chunk */
  Mix_Chunk* chunk;
};

#endif
