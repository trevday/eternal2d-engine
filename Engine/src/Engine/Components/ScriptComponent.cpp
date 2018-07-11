#include "ScriptComponent.hpp"

#include <pybind11/eval.h>

#include "PyScriptWrapper.hpp"

ScriptComponent::ScriptComponent(const std::string& module,
                                 const std::string& pyClass)
    // save for serialization later
    : className(pyClass), moduleName(module) {}

void ScriptComponent::Init() {
  // Get module file
  pybind11::module script = pybind11::module::import(moduleName.c_str());
  // Get specific class and call constructor
  pybind11::object sc = script.attr(pybind11::cast(className))();
  // Set up the wrapper
  pybind11::cast<std::shared_ptr<PyScriptWrapper>>(sc)->SetScriptComponent(
      gameObject.lock()->GetComponent<ScriptComponent>());
  wrapper_ = sc;

  // Call the python init
  wrapper_.attr("Init")();
}

void ScriptComponent::Update() { wrapper_.attr("Update")(); }
