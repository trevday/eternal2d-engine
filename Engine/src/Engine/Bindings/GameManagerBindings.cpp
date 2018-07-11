#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "GameManager.hpp"

PYBIND11_EMBEDDED_MODULE(game, m) {
  m.def("LoadNextLevel", &GameManager::LoadNextLevel);
  m.def("ReloadLevel", &GameManager::ReloadLevel);
  m.def("GetActiveObjects", &GameManager::GetActiveObjects);
}
