#ifndef SDL_TEXTURE_WRAPPER_HPP
#define SDL_TEXTURE_WRAPPER_HPP

#include <SDL2/SDL.h>

/**
 * A wrapper class for SDL_Textures
 */
class SDLTextureWrapper {
 public:
  
  /** Constructs an ~SDLTextureWrapper */
  SDLTextureWrapper(/** The SDL_Texture to be wrapped */
                    SDL_Texture* tex);
  
  /** Destructs an ~SDLTextureWrapper */
  ~SDLTextureWrapper();

  /**
   * Gets the SDL_Texture of this wrapper.
   * @return The texture
   */
  SDL_Texture* GetTex() const;

 private:
  
  /** The wrapped SDL_Texture */
  SDL_Texture* tex_;
};

#endif
