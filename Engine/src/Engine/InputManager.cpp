#include "InputManager.hpp"

InputManager::InputManager() {}
InputManager::~InputManager() {}

InputManager& InputManager::instance() {
  static InputManager instance;

  return instance;
}

void InputManager::PollInput() {
  ClearPresses();

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_WINDOWEVENT && e.window.type == SDL_WINDOWEVENT_CLOSE) {
      inputPressed[Input::QUIT] = true;
    } else if (e.type == SDL_KEYDOWN && INPUT_MAP.find(e.key.keysym.sym) != INPUT_MAP.end()) {
      Input action = INPUT_MAP.find(e.key.keysym.sym)->second;
      inputPressed[action] = true;
      inputHeld[action] = true;
    } else if (e.type == SDL_KEYUP && INPUT_MAP.find(e.key.keysym.sym) != INPUT_MAP.end()) {
      Input action = INPUT_MAP.find(e.key.keysym.sym)->second;
      inputHeld[action] = false;
    } else if (e.type == SDL_MOUSEBUTTONDOWN && MOUSE_BUTTON_MAP.find(e.button.button) != INPUT_MAP.end()) {
      Input action = MOUSE_BUTTON_MAP.find(e.button.button)->second;
      inputPressed[action] = true;
      inputHeld[action] = true;
      mousePos.x = e.button.x;
      mousePos.y = e.button.y;
    } else if (e.type == SDL_MOUSEBUTTONUP && MOUSE_BUTTON_MAP.find(e.button.button) != INPUT_MAP.end()) {
      Input action = MOUSE_BUTTON_MAP.find(e.button.button)->second;
      inputHeld[action] = false;
      mousePos.x = e.button.x;
      mousePos.y = e.button.y;
    } else if (e.type == SDL_MOUSEMOTION) {
      mousePos.x = e.motion.x;
      mousePos.y = e.motion.y;
    }
  }

  if (inputPressed[Input::QUIT] || inputHeld[Input::QUIT]) {
    quitFlag = true;
  }
}

bool InputManager::GetActionPressed(Input action) {
  return instance().inputPressed[action];
}
bool InputManager::GetActionHeld(Input action) {
  return instance().inputHeld[action];
}

bool InputManager::ShouldQuit() const { return quitFlag; }

void InputManager::ClearPresses() {
  for (auto it = inputPressed.begin(); it != inputPressed.end(); it++) {
    it->second = false;
  }
}

Vector2 InputManager::GetMousePos() {
  return instance().mousePos;
}
