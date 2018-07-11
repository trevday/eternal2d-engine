#ifndef TEXT_RENDER_COMPONENT_HPP
#define TEXT_RENDER_COMPONENT_HPP

#include <string>

#include "FilePaths.hpp"
#include "RenderComponent.hpp"
#include "SDLFontWrapper.hpp"

/**
 * A TextRenderComponent class. This represents a simple renderable piece of text within
 * our game, having a font, color, and functionality to change its text.
 */
class TextRenderComponent : public RenderComponent {
 public:
  /** Constructs a TextRenderComponent */
  TextRenderComponent(/** The color of this TextRenderComponent */
                      SDL_Color color);
  /** Constructs a TextRenderComponent */
  TextRenderComponent(/** The color of this TextRenderComponent */
                      SDL_Color color,
                      /** The initial text */
                      std::string text);

  /** Changes the text of this TextRenderComponent */
  void ChangeText(/** The string of text to be changed to */
                  const std::string newText);

 private:
  /** The color of this TextRenderComponent */
  SDL_Color color;

  /** The font of this TextRenderComponent */
  std::shared_ptr<SDLFontWrapper> font;

  /** The font path of this TextRenderComponent */
  const std::string FONT_PATH =
      FullAssetsPath() + "Fonts/raleway/Raleway-Bold.ttf";
};

#endif
