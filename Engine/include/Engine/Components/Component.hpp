#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

// Forward declaration
class GameObject;

/**
 * Class representing a component of a GameObject
 */
class Component {
 public:
  /** Sets the given GameObject as this component's parent */
  void SetParentGameObject(/** The GameObject to be assigned as this component's
                              parent */
                           std::weak_ptr<GameObject> g);

  /** Initializes this component */
  virtual void Init();

  /** Updates this component */
  virtual void Update() = 0;

  /**
   * Gets a shared ptr reference to this component's GameObject
   * @return A shared ptr reference to this component's GameObject
   */
  std::shared_ptr<GameObject> GetGameObject();

 protected:
  /** This component's parent GameObject */
  std::weak_ptr<GameObject> gameObject;
};

#endif