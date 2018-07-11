#ifndef PY_SCRIPT_WRAPPER
#define PY_SCRIPT_WRAPPER

#include "GameObject.hpp"

class ScriptComponent;

/** A wrapper class for python script components. */
class PyScriptWrapper {
 public:
  /**
   * Gets a shared ptr reference to this component's GameObject
   * @return A shared ptr reference to this component's GameObject
   */
  std::shared_ptr<GameObject> GetGameObject();

  /** Sets the script component for this wrapper */
  void SetScriptComponent(/** The script component to be set */
                          std::shared_ptr<ScriptComponent> sc);

 private:
  /** The script component for this python script wrapper */
  std::weak_ptr<ScriptComponent> scriptComp;
};

#endif