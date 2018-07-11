#include <pybind11/embed.h>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "Button.hpp"
#include "CameraComponent.hpp"
#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
#include "PyScriptWrapper.hpp"
#include "TimeManager.hpp"
#include "AnimationRenderComponent.hpp"

PYBIND11_EMBEDDED_MODULE(core, m) {
  // Utility Classes
  pybind11::class_<SDL_Color>(m, "Color")
      .def(pybind11::init<>())
      .def(pybind11::init<uint8, uint8, uint8>())
      .def(pybind11::init<uint8, uint8, uint8, uint8>())
      .def_readwrite("r", &SDL_Color::r)
      .def_readwrite("g", &SDL_Color::g)
      .def_readwrite("b", &SDL_Color::b)
      .def_readwrite("a", &SDL_Color::a);
  pybind11::class_<SDL_Rect>(m, "Rect")
      .def(pybind11::init<>())
      .def(pybind11::init<int, int, int, int>())
      .def_readwrite("x", &SDL_Rect::x)
      .def_readwrite("y", &SDL_Rect::y)
      .def_readwrite("w", &SDL_Rect::w)
      .def_readwrite("h", &SDL_Rect::h);
  pybind11::class_<Vector2>(m, "Vector2")
      .def(pybind11::init<>())
      .def(pybind11::init<int, int>())
      .def_readwrite("x", &Vector2::x)
      .def_readwrite("y", &Vector2::y);

  // Time
  m.def("DeltaTime", &TimeManager::DeltaTime);
  // GameObject stuff
  pybind11::class_<GameObject, std::shared_ptr<GameObject>>(m, "GameObject")
      .def("Create", &GameObject::Create)
      .def("Create", &GameObject::CreateStandard)
      .def("AddComponent", &GameObject::AddComponent<RenderComponent>,
           pybind11::return_value_policy::reference)
      .def("AddComponent", &GameObject::AddComponent<CameraComponent>,
           pybind11::return_value_policy::reference)
      .def("AddComponent", &GameObject::AddComponent<Button>,
           pybind11::return_value_policy::reference)
      .def("AddComponent", &GameObject::AddComponent<PhysicsComponent>,
           pybind11::return_value_policy::reference)
      .def("GetRenderComponent", &GameObject::GetComponent<RenderComponent>,
           pybind11::return_value_policy::reference)
      .def("GetCameraComponent", &GameObject::GetComponent<CameraComponent>,
           pybind11::return_value_policy::reference)
      .def("GetButtonComponent", &GameObject::GetComponent<Button>,
           pybind11::return_value_policy::reference)
      .def("GetPhysicsComponent", &GameObject::GetComponent<PhysicsComponent>,
           pybind11::return_value_policy::reference)
      .def_readwrite("position", &GameObject::position)
      .def_readwrite("scale", &GameObject::scale);

  pybind11::class_<PyScriptWrapper, std::shared_ptr<PyScriptWrapper>>(
      m, "ScriptBase")
      .def(pybind11::init<>())
      .def("GetGameObject", &PyScriptWrapper::GetGameObject,
           pybind11::return_value_policy::reference);

  pybind11::class_<Animation>(m, "Animation")
      .def(pybind11::init<const std::string &, unsigned int, unsigned int,
                          unsigned int, unsigned int, unsigned int,
                          unsigned int, unsigned int>());
}
