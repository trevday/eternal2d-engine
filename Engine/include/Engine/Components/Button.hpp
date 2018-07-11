#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>

#include "Component.hpp"

/** A basic button component class */
class Button : public Component {
 public:
  /** Creates a new button that calls the given function */
  Button(/** Function to be called upon click */
          std::function<void(GameObject&)> onClick);

  virtual void Update();

 private:
  /** The function to be called upon click */
  std::function<void(GameObject&)> fun;
};

#endif
