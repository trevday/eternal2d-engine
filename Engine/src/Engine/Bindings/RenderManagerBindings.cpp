#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "RenderManager.hpp"

PYBIND11_EMBEDDED_MODULE(render, m) {
  m.def("getWidth", &RenderManager::getWidth);
  m.def("getHeight", &RenderManager::getHeight);
  m.def("GetCamera", &RenderManager::GetCamera);
  m.def("SetActiveCamera", &RenderManager::SetActiveCamera);
}
