#ifndef LAMBDACOMPONENT_HPP
#define LAMBDACOMPONENT_HPP

#include <functional>

#include "Component.hpp"

/** A class for adding a function to the given component's update loop */
class LambdaComponent : public Component {
 public:

  /** Construts a new lambda component */
  LambdaComponent(/** The function to be called when updating */
                  std::function<void(GameObject&)> fun);

  virtual void Update();

 private:
  /** The function to be called when updating */
  std::function<void(GameObject&)> fun;
};

#endif