#ifndef LEVELCREATOR_HPP
#define LEVELCREATOR_HPP

#include <memory>
#include <string>
#include <vector>

/**
 * This class loads and creates the levels for our game.
 */
class LevelLoader {
 public:
  /**
   * Loads the level at the given path
   */
  static void LoadLevel(/** The path of the level to be loaded */
                        std::string path);
};

#endif
