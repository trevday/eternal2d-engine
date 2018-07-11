#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "SDLFontWrapper.hpp"
#include "SDLSoundWrapper.hpp"
#include "SDLTextureWrapper.hpp"

/**
 * This class manages the resources of our game as a
 * singleton.
 */
class ResourceManager {
 public:
  /** The singleton instance of the ResourceManager */
  static ResourceManager& instance();

  /** Shuts down the ResourceManager, removing all its references to loaded
   * resources **/
  void shutdown();

  /**
   * Loads an image from the given path
   * Uses the stored image if already loaded
   * @return The SDLTextureWrapper of the image
   */
  std::shared_ptr<SDLTextureWrapper> LoadImage(/** The path of the image */
                                               const std::string& path);

  /**
   * Loads a font from the given path in the given textSize
   * Uses the stored font if already loaded
   * @return The SDLFontWrapper of the font
   */
  std::shared_ptr<SDLFontWrapper> LoadFont(/** The path of the font */
                                           const std::string& path,
                                           /** The text size of the font */
                                           int textSize);

  /**
   * Loads a sound from the given path
   * Uses the stored sound if already loaded
   * @return The SDLSoundWrapper of the sound
   */
  static std::shared_ptr<SDLSoundWrapper> LoadSound(/** The path of the sound */
                                                    const std::string& path);

  /** Stop the compiler from generating methods to copy the object */
  ResourceManager(const ResourceManager& m) = delete;

  /** Stop the compiler from generating methods to copy the object */
  void operator=(const ResourceManager& m) = delete;

 private:
  /** Constructs a ResourceManager */
  ResourceManager();

  /** Constructs a ResourceManager */
  ~ResourceManager();

  /** Map of all currently loaded images */
  std::unordered_map<std::string, std::shared_ptr<SDLTextureWrapper>>
      loadedImages;

  /** Map of all currently loaded fonts */
  std::unordered_map<std::string, std::shared_ptr<SDLFontWrapper>> loadedFonts;

  /** Map of all currently loaded sounds */
  std::unordered_map<std::string, std::shared_ptr<SDLSoundWrapper>>
      loadedSounds;
};

#endif
