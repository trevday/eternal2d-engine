#include "CameraComponent.hpp"

#include "GameObject.hpp"
#include "RenderManager.hpp"

CameraComponent::CameraComponent()
    : CameraComponent(
          {RenderManager::getWidth() / 2, RenderManager::getHeight() / 2,
           RenderManager::getWidth(), RenderManager::getHeight()}) {}

CameraComponent::CameraComponent(SDL_Rect renderView)
    : CameraComponent(renderView, {0, 0, RenderManager::getWidth(),
                                   RenderManager::getHeight()}) {}

CameraComponent::CameraComponent(SDL_Rect renderView, SDL_Rect renderArea)
    : renderView(renderView), renderArea(renderArea) {}

void CameraComponent::Update() {}

void CameraComponent::Translate(SDL_Rect& dest) {
  // Translation
  dest.x -= renderView.x - renderView.w / 2;
  dest.y -= renderView.y + renderView.h / 2;

  // Size
  dest.x *= ((float)renderArea.w / (float)renderView.w);
  dest.y *= ((float)renderArea.h / (float)renderView.h);
  dest.w *= ((float)renderArea.w / (float)renderView.w);
  dest.h *= ((float)renderArea.h / (float)renderView.h);
}

void CameraComponent::SetActive() {
  RenderManager::SetActiveCamera(
      gameObject.lock()->GetComponent<CameraComponent>());
}

void CameraComponent::SetCaptureArea(SDL_Rect r) { renderView = r; }