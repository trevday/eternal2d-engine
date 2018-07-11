#ifndef GAME_WORLD_HPP
#define GAME_WORLD_HPP

#include <vector>

#include "GameObject.hpp"

/**
 * This class represents the game world. It has a list of all the
 * objects the world contains.
 */
class GameWorld {
 public:
  /** Constructs a GameWorld */
  GameWorld();

  /**
   * Updates this world
   */
  void Update();

  /**
   * Gets the list of all active objects in our world
   * @return The list of all active objects
   */
  std::vector<std::shared_ptr<GameObject>> GetActiveObjects() const;

  /** Registers an object in the world */
  void RegisterObject(/** The object to be registered */
                      std::shared_ptr<GameObject> obj);

 private:
  /** The list of all objects in the world */
  std::vector<std::shared_ptr<GameObject>> objects;
};

#endif
