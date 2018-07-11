#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "InputManager.hpp"

PYBIND11_EMBEDDED_MODULE(input, m) {
  m.def("GetActionPressed", &InputManager::GetActionPressed);
  m.def("GetActionHeld", &InputManager::GetActionHeld);
  m.def("GetMousePos", &InputManager::GetMousePos);

  pybind11::enum_<Input>(m, "inputs")
    .value("LEFT_MOUSE", Input::LEFT_MOUSE)
    .value("RIGHT_MOUSE", Input::RIGHT_MOUSE)
    .value("MIDDLE_MOUSE", Input::MIDDLE_MOUSE)
    .value("LEFT", Input::LEFT)
    .value("RIGHT", Input::RIGHT)
    .value("UP", Input::UP)
    .value("DOWN", Input::DOWN)
    .value("ATTACK_LEFT", Input::ATTACK_LEFT)
    .value("ATTACK_RIGHT", Input::ATTACK_RIGHT)
    .value("ATTACK_UP", Input::ATTACK_UP)
    .value("ATTACK_DOWN", Input::ATTACK_DOWN)
    .value("JUMP", Input::JUMP)
    .value("ACTION_1", Input::ACTION_1)
    .value("ACTION_2", Input::ACTION_2)
    .value("ACTION_3", Input::ACTION_3)
    .value("ACTION_4", Input::ACTION_4)
    .value("UTIL_1", Input::UTIL_1)
    .value("UTIL_2", Input::UTIL_2)
    .value("UTIL_3", Input::UTIL_3)
    .value("ENTER", Input::ENTER)
    .value("QUIT", Input::QUIT);
}
