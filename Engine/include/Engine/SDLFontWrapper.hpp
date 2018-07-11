#ifndef SDL_FONT_WRAPPER_HPP
#define SDL_FONT_WRAPPER_HPP

#include <SDL2/SDL_ttf.h>

/**
 * A wrapper class for TTF_Fonts
 */
class SDLFontWrapper {
 public:
  
  /** Constructs an SDLFontWrapper */
  SDLFontWrapper(/** The TTF_Font to be wrapped */
                 TTF_Font* f);
 
  /** Destructs an SDLFontWrapper */
  ~SDLFontWrapper();

  /**
   * Gets the font of this wrapper.
   * @return The font
   */
  TTF_Font* GetFont() const;

 private:
  
  /** The wrapped TTF_Font */
  TTF_Font* font;
};

#endif
