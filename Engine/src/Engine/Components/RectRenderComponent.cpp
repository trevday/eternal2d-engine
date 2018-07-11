#include "RectRenderComponent.hpp"
#include "GameObject.hpp"
#include "RenderManager.hpp"

RectRenderComponent::RectRenderComponent(SDL_Color color) : color(color) {}

void RectRenderComponent::Render() {
  SDL_Rect r = gameObject.lock()->ScreenRegion();
  SDL_SetRenderDrawColor(RenderManager::instance().GetRenderer(), color.r,
                         color.g, color.b, color.a);
  SDL_RenderFillRect(RenderManager::instance().GetRenderer(), &r);
}