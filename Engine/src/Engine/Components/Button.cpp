#include "Button.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"

Button::Button(std::function<void(GameObject&)> onClick) : fun(onClick) {}

void Button::Update() {
  if (InputManager::instance().GetActionPressed(Input::LEFT_MOUSE)) {
    Vector2 click = InputManager::instance().GetMousePos();
    SDL_Rect box = gameObject.lock()->ScreenRegion();
    if (click.x >= box.x && click.x <= box.x + box.w && click.y >= box.y &&
        click.y <= box.y + box.h) {
      fun(*gameObject.lock());
    }
  }
}
