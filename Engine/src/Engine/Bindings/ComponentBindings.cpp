#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

#include "GameObject.hpp"
#include "AnimationRenderComponent.hpp"
#include "Button.hpp"
#include "CameraComponent.hpp"
#include "ImageRenderComponent.hpp"
#include "PhysicsComponent.hpp"
#include "RectRenderComponent.hpp"
#include "RenderComponent.hpp"
#include "TextRenderComponent.hpp"

PYBIND11_EMBEDDED_MODULE(components, m) {
  // Components
  pybind11::class_<CameraComponent, std::shared_ptr<CameraComponent>>(
      m, "CameraComponent")
      .def(pybind11::init<>())
      .def(pybind11::init<SDL_Rect>())
      .def(pybind11::init<SDL_Rect, SDL_Rect>())
      .def("SetActive", &CameraComponent::SetActive)
      .def("SetCaptureArea", &CameraComponent::SetCaptureArea);
  pybind11::class_<Button, std::shared_ptr<Button>>(m, "ButtonComponent")
      .def(pybind11::init<std::function<void(GameObject &)>>());

  pybind11::class_<PhysicsComponent, std::shared_ptr<PhysicsComponent>>(
      m, "PhysicsComponent")
      .def(pybind11::init<BodyType, std::vector<Vector2>, float32, float32,
                          float32, bool>())
      .def(pybind11::init<BodyType, float32, float32, float32, float32, float32,
                          bool>())
      .def("ApplyForce", &PhysicsComponent::ApplyForce)
      .def("ApplyForceToCenter", &PhysicsComponent::ApplyForceToCenter)
      .def("GetLinearVelocity", &PhysicsComponent::GetLinearVelocity)
      .def("SetLinearVelocity", &PhysicsComponent::SetLinearVelocity)
      .def("SetActive", &PhysicsComponent::SetActive)
      .def("SetManagedByPhysics", &PhysicsComponent::SetManagedByPhysics);

  // Render Components
  pybind11::class_<RenderComponent, std::shared_ptr<RenderComponent>>(
      m, "RenderComponent")
      .def(pybind11::init<>());

  pybind11::class_<AnimationRenderComponent, RenderComponent,
                   std::shared_ptr<AnimationRenderComponent>>(
      m, "AnimationRenderComponent")
      .def(pybind11::init<std::unordered_map<unsigned int, Animation>>())
      .def("SwitchState", &AnimationRenderComponent::SwitchState,
           "Switches the current animation state", pybind11 ::arg("state"));

  pybind11::class_<RectRenderComponent, RenderComponent,
                   std::shared_ptr<RectRenderComponent>>(m,
                                                         "RectRenderComponent")
      .def(pybind11::init<SDL_Color>());

  pybind11::class_<TextRenderComponent, RenderComponent,
                   std::shared_ptr<TextRenderComponent>>(m,
                                                         "TextRenderComponent")
      .def(pybind11::init<SDL_Color>())
      .def(pybind11::init<SDL_Color, std::string>())
      .def("ChangeText", &TextRenderComponent::ChangeText);

  pybind11::class_<ImageRenderComponent, RenderComponent,
                   std::shared_ptr<ImageRenderComponent>>(
      m, "ImageRenderComponent")
      .def(pybind11::init<const std::string &>());
}