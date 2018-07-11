#ifndef TIME_MANAGER_HPP
#define TIME_MANAGER_HPP

/** Manages the time and framerate for our game */
class TimeManager {
 public:
  /** The singleton instance of the TimeManager */
  static TimeManager& instance();

  /** Stabilizes the framerate of the game by calling SDL_Delay */
  void StablizeFramerate();

  /*
   * Gets the most recent change in time since the last update tick
   * @return The change in time based on the last update tick
   */
  static unsigned int DeltaTime();
  
  /** Stop the compiler from generating methods to copy the object */
  TimeManager(const TimeManager&) = delete;

  /** Stop the compiler from generating methods to copy the object */
  TimeManager& operator=(const TimeManager&) = delete;

 private:
  /** Constructs a TimeManager */
  TimeManager();

  /** Destructs a TimeManager */
  ~TimeManager();

  /** The last update tick for stabilizing the framerate */
  unsigned int lastTick_ = 0;

  /** The change in time based on the last update tick */
  unsigned int lastDelta_ = 0;

  /** The ticks per frame for stabilizing the framerate */
  unsigned int TICKS_PER_FRAME = 16;  // 16.667
};

#endif