#include "TextRenderComponent.hpp"

#include "RenderManager.hpp"
#include "ResourceManager.hpp"

TextRenderComponent::TextRenderComponent(SDL_Color color)
    : RenderComponent(), color(color) {
  font = ResourceManager::instance().LoadFont(FONT_PATH, 512);
}

TextRenderComponent::TextRenderComponent(SDL_Color color, std::string text)
    : TextRenderComponent(color) {
  ChangeText(text);
}

void TextRenderComponent::ChangeText(const std::string newText) {
  if (newText == "") {
    return;
  }
  SDL_Surface* textSurface =
      TTF_RenderText_Solid(font->GetFont(), newText.c_str(), color);
  if (textSurface == NULL) {
    SDL_Log("Failed to allocate text surface: %s", newText.c_str());
    return;
  }

  SDL_Texture* t = SDL_CreateTextureFromSurface(
      RenderManager::instance().GetRenderer(), textSurface);

  texture = std::shared_ptr<SDLTextureWrapper>(new SDLTextureWrapper(t));

  SDL_FreeSurface(textSurface);
}