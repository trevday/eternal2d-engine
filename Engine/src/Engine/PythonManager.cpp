#include "PythonManager.hpp"

#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "FilePaths.hpp"

PythonManager& PythonManager::instance() {
  static PythonManager instance;

  return instance;
}

void PythonManager::init() {
  pybind11::initialize_interpreter();
  pybind11::module::import("sys").attr("path").attr("append")(FullAssetsPath() +
                                                              "Scripts/");
}

void PythonManager::shutdown() { pybind11::finalize_interpreter(); }

PythonManager::PythonManager() {}

PythonManager::~PythonManager() {}