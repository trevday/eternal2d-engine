#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <string>

#include "ConfigParser.hpp"
#include "GameWorld.hpp"

/**
 * This class manages the loading, rendering, and objects
 * of our game as a singleton.
 */
class GameManager {
 public:
  /** The singleton instance of the GameManager */
  static GameManager& instance();

  /** Initializes the GameManager */
  void init();

  /** Shuts down the GameManager, removing its reference to the currently loaded
   * GameWorld and all GameObjects contained within **/
  void shutdown();

  /** Calls to parse the levels and sets shouldLoadLevel true */
  void LoadLevels();

  /** Increments the curLevel and sets shouldLoadLevel true */
  static void LoadNextLevel();

  /** Reloads the level by setting shouldLoadLevel true */
  static void ReloadLevel();

  /**
   * Updates the world and any other gameobjects controlled by
   * the GameManager, and calls to load levels if prompted
   */
  void Update();

  /**
   * Gets the list of all active objects in our GameManager
   * @return The list of all active objects
   */
  static std::vector<std::shared_ptr<GameObject>> GetActiveObjects();

  /** Stop the compiler from generating methods to copy the object */
  GameManager(const GameManager&) = delete;

  /** Stop the compiler from generating methods to copy the object */
  GameManager& operator=(const GameManager&) = delete;

  void RegisterObject(std::shared_ptr<GameObject> obj, bool isPermanent);

 private:
  /** Constructs a GameManager */
  GameManager();

  /** Destructs a GameManager */
  ~GameManager();

  /** Loads the given level path */
  void LoadLevel(/** The path of the level to be loaded */
                 const std::string& path);

  /** The current world for our GameManager */
  std::shared_ptr<GameWorld> curWorld_;

  /** The permanent objects in our GameManager */
  std::vector<std::shared_ptr<GameObject>> permanentObjs_;

  /** The list of level paths for loading assets */
  std::vector<std::string> levelPaths;

  /** The current level */
  int curLevel;

  /** Whether or not the GameManager should load the next level */
  bool shouldLoadLevel;
};

#endif
