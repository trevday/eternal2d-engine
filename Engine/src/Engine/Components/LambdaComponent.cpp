#include "LambdaComponent.hpp"

LambdaComponent::LambdaComponent(std::function<void(GameObject&)> func) : fun(func) {}

void LambdaComponent::Update() {fun(*gameObject.lock());}