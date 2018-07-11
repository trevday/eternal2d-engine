#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <SDL2/SDL.h>
#include <map>
#include "Vector2.hpp"

static const unsigned int N_KEY_INPUTS = 1024;
static const unsigned int N_BUTTON_INPUTS = 6;

enum class Input {
    LEFT_MOUSE, RIGHT_MOUSE, MIDDLE_MOUSE,

    LEFT, RIGHT, UP, DOWN,
    ATTACK_LEFT, ATTACK_RIGHT, ATTACK_UP, ATTACK_DOWN,
    JUMP,
    ACTION_1, ACTION_2, ACTION_3, ACTION_4,
    UTIL_1, UTIL_2, UTIL_3,
    ENTER,
    QUIT
};

/** Maps SDL inputs to our input system */
static const std::map<SDL_Keycode, Input> INPUT_MAP = {
    {SDLK_LEFT, Input::LEFT},     
    {SDLK_a, Input::LEFT},          
    {SDLK_RIGHT, Input::RIGHT},
    {SDLK_d, Input::RIGHT}, 
    {SDLK_UP, Input::UP},     
    {SDLK_w, Input::UP},          
    {SDLK_DOWN, Input::DOWN},
    {SDLK_s, Input::DOWN}, 

    {SDLK_j, Input::ATTACK_LEFT}, 
    {SDLK_l, Input::ATTACK_RIGHT}, 
    {SDLK_k, Input::ATTACK_DOWN},
    {SDLK_i, Input::ATTACK_UP},
    
    {SDLK_SPACE, Input::JUMP},  

    {SDLK_q, Input::ACTION_1},
    {SDLK_e, Input::ACTION_2},
    {SDLK_r, Input::ACTION_3},
    {SDLK_f, Input::ACTION_4},
    
    {SDLK_z, Input::UTIL_1},
    {SDLK_x, Input::UTIL_2},
    {SDLK_c, Input::UTIL_3},

    {SDLK_RETURN, Input::ENTER},
    {SDLK_ESCAPE, Input::QUIT}
};

static const std::map<int, Input> MOUSE_BUTTON_MAP = {
    {SDL_BUTTON_LEFT, Input::LEFT_MOUSE}, 
    {SDL_BUTTON_MIDDLE, Input::MIDDLE_MOUSE}, 
    {SDL_BUTTON_RIGHT, Input::RIGHT_MOUSE} 
};

/**
 * This class manages the inputs of our game as a
 * singleton.
 */
class InputManager {
 public:
  /** The singleton instance of the InputManager */
  static InputManager& instance();

  /** Polls for input from the keyboard */
  void PollInput();

  /**
   * Gets whether or not the given input was just pressed
   * @return Whether or not the given input was just pressed
   */
  static bool GetActionPressed(/** The input to be checked */
                               Input action);

  /**
   * Gets whether or not the given input is held
   * @return Whether or not the given input is held
   */
  static bool GetActionHeld(/** The input to be checked */
                            Input action);

  /**
   * Gets whether or not the game should quit
   * @return Whether or not the game should quit
   */
  bool ShouldQuit() const;

  /**
   * Gets the position of the most recent mouse event.
   * @return the position of the most recent mouse event.
   */
  static Vector2 GetMousePos();

  /** Stop the compiler from generating methods to copy the object */
  InputManager(const InputManager&) = delete;

  /** Stop the compiler from generating methods to copy the object */
  InputManager& operator=(const InputManager&) = delete;

 private:
  /** Constructs an InputManager */
  InputManager();

  /** Destructs an InputManager */
  ~InputManager();

  /** Array of inputs that are currently held down */
  std::map<Input, bool> inputHeld;

  /** Array of inputs that were just pressed */
  std::map<Input, bool> inputPressed;

  /** Whether or not the game should quit */
  bool quitFlag;

  /** Resets the inputPressed map to falses each frame */
  void ClearPresses();

  /** Called when an up event is registered for an input */
  void UpEvent(Input input);
  /** Called when a down event is registered for an input */
  void DownEvent(Input input);

  /** Location of the last mouse event */
  Vector2 mousePos;
};

#endif
