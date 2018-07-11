#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <memory>
#include "SDLSoundWrapper.hpp"

/**
 * This class manages the sounds of our game as a
 * singleton.
 */
class SoundManager {
 public:
  /** Initializes the SoundManager */
  bool init();

  /** Shuts down the SoundManager */
  void shutdown();

  /** The singleton instance of the SoundManager */
  static SoundManager& instance();

  /** Plays the given sound the given number of times */
  static void PlaySound(/** The sound to be played */
                        std::shared_ptr<SDLSoundWrapper> sound,
                        /** The number of times the sound should be played */
                        int times);

  /** Stop the compiler from generating methods to copy the object */
  SoundManager(const SoundManager&) = delete;

  /** Stop the compiler from generating methods to copy the object */
  SoundManager& operator=(const SoundManager&) = delete;

 private:
  /** Constructs a SoundManager */
  SoundManager();

  /** Destructs a SoundManager */
  ~SoundManager();
};

#endif
