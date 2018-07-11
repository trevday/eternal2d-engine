#include "GameWorld.hpp"

GameWorld::GameWorld() {}

void GameWorld::Update() {
  for (auto it = objects.begin(); it != objects.end(); ++it) {
    if ((*it)->IsActive()) {
      (*it)->Update();
    }
  }
}

std::vector<std::shared_ptr<GameObject>> GameWorld::GetActiveObjects() const {
  std::vector<std::shared_ptr<GameObject>> active;
  for (auto it = objects.begin(); it != objects.end(); ++it) {
    if ((*it)->IsActive()) {
      active.push_back(*it);
    }
  }
  return active;
}

void GameWorld::RegisterObject(std::shared_ptr<GameObject> obj) {
  objects.push_back(obj);
}
