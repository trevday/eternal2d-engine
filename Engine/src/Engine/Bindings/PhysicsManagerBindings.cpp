#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "PhysicsManager.hpp"
#include "PhysicsComponent.hpp"

PYBIND11_EMBEDDED_MODULE(physics, m) {
  m.def("SetGravity", &PhysicsManager::SetGravity);

  pybind11::enum_<BodyType>(m, "BodyType")
      .value("DYNAMIC", BodyType::DYNAMIC)
      .value("STATIC", BodyType::STATIC)
      .value("KINEMATIC", BodyType::KINEMATIC);
}