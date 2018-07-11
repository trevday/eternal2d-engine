#include "Component.hpp"

void Component::SetParentGameObject(std::weak_ptr<GameObject> g) {
  gameObject = g;
}

void Component::Init() {}

std::shared_ptr<GameObject> Component::GetGameObject() {
  return gameObject.lock();
}