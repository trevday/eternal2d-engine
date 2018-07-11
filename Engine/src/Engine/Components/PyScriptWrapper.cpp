#include "PyScriptWrapper.hpp"

#include "ScriptComponent.hpp"

#include <iostream>

std::shared_ptr<GameObject> PyScriptWrapper::GetGameObject() {
  return scriptComp.lock()->GetGameObject();
}

void PyScriptWrapper::SetScriptComponent(std::shared_ptr<ScriptComponent> sc) {
  scriptComp = std::weak_ptr<ScriptComponent>(sc);
}
