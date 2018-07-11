#include "PhysicsManager.hpp"

#include "TimeManager.hpp"

PhysicsManager::PhysicsManager() {}
PhysicsManager::~PhysicsManager() {}

/** The singleton instance of the PhysicsManager */
PhysicsManager& PhysicsManager::instance() {
  static PhysicsManager instance;
  return instance;
}

void PhysicsManager::init() {
  world = std::shared_ptr<b2World>(new b2World(b2Vec2(0, -9.8)));
}

void PhysicsManager::shutdown() {}

std::shared_ptr<b2World> PhysicsManager::GetWorld() { return instance().world; }

void PhysicsManager::SetGravity(float x, float y) {
  instance().world->SetGravity(b2Vec2(x, y));
}

void PhysicsManager::Step() {
  world->Step((float)(1.0 / 120.0), 8, 3);
}