#include "GameObject.hpp"

#include "GameManager.hpp"

int GameObject::lastTypeID = 0;

GameObject::GameObject(int posX, int posY, int width, int height, bool isUI)
    : position(posX, posY), scale(width, height), active(true), isUI(isUI) {}

std::shared_ptr<GameObject> GameObject::Create(int posX, int posY, int width,
                                               int height, bool isUI,
                                               bool isPermanent) {
  std::shared_ptr<GameObject> ga = std::shared_ptr<GameObject>(
      new GameObject(posX, posY, width, height, isUI));
  GameManager::instance().RegisterObject(ga, isPermanent);
  return ga;
}
std::shared_ptr<GameObject> GameObject::CreateStandard(int posX, int posY,
                                                       int width, int height) {
  return Create(posX, posY, width, height, false, false);
}

void GameObject::Update() {
  for (auto it = componentMap.begin(); it != componentMap.end(); ++it) {
    it->second->Update();
  }
}

void GameObject::Disable() { active = false; }

void GameObject::Enable() { active = true; }

bool GameObject::IsActive() const { return active; }

bool GameObject::IsColliding(const GameObject& other) const {
  Vector2 oPos = other.position;
  Vector2 oScale = other.scale;
  return position.x - scale.x / 2 <= oPos.x + oScale.x / 2 &&
         position.x + scale.x / 2 >= oPos.x - oScale.x / 2 &&
         position.y + scale.y / 2 >= oPos.y - oScale.y / 2 &&
         position.y - scale.y / 2 <= oPos.y + oScale.y / 2;
}

SDL_Rect GameObject::ScreenRegion() {
  SDL_Rect dest;
  dest.x = position.x - scale.x / 2;
  dest.w = scale.x;
  dest.h = scale.y;

  if (isUI) {
    dest.y = position.y - scale.y / 2;
  } else {
    dest.y = position.y + scale.y / 2;
    if (RenderManager::GetCamera()) {
      RenderManager::GetCamera()->Translate(dest);
    } else {
      SDL_Log("No camera to render with: Set an active camera");
    }
    dest.y *= -1;
  }
  return dest;
}