#include "RenderComponent.hpp"

#include "GameObject.hpp"
#include "RenderManager.hpp"

RenderComponent::RenderComponent() {}

void RenderComponent::Update() {}

void RenderComponent::Render() {
  SDL_Rect dest = gameObject.lock()->ScreenRegion();
  if (texture->GetTex() != NULL) {
    SDL_Rect* src;
    if (!renderSrc) {
      src = NULL;
    } else {
      src = renderSrc.get();
    }
    if (SDL_RenderCopyEx(RenderManager::instance().GetRenderer(),
                         texture->GetTex(), src, &dest, 0, NULL,
                         renderFlip) < 0) {
      SDL_Log("Failed to render at: %d %d", dest.x, dest.y);
    }
  }
}