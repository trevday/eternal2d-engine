#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include <pybind11/pybind11.h>

#include "Component.hpp"

/** A class for attaching python scripts as components. */
class ScriptComponent : public Component {
 public:

  /** Construts a new script component */
  ScriptComponent(/** The name of this script component's python module. */
                  const std::string& module, 
                  /** The name of this script component's python class. */
                  const std::string& pyClass);

  void Init() override;

  void Update() override;

  /** The name of this script component's python module. */
  const std::string moduleName;
  /** The name of this script component's python class. */
  const std::string className;

 private:
  /** The wrapper object for this script component. */
  pybind11::object wrapper_;
};

#endif