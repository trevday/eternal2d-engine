#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "LocaleManager.hpp"

PYBIND11_EMBEDDED_MODULE(translation, m) {
  m.def("Lookup", &LocaleManager::Lookup);
}