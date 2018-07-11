#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <unordered_map>
#include "RenderManager.hpp"

#include "Component.hpp"
#include "Vector2.hpp"

/**
 * A GameObject class. This represents a simple object within
 * our game, having a position, dimensions, and an active state.
 */
class GameObject : public std::enable_shared_from_this<GameObject> {
 public:
  /**
   * Creates a GameObject
   * @return the created GameObject
   */
  static std::shared_ptr<GameObject>
  Create(/** The x coordinate of this GameObject */
         int posX,
         /** The y coordinate of this GameObject */
         int posY,
         /** The width of this GameObject */
         int width,
         /** The height of this GameObject */
         int height,
         /** Whether this GameObject should use direct screen coordinates */
         bool isUI = false,
         /** Whether this GameObject should persist througt level load */
         bool isPermanent = false);

  /**
   * Creates a non-UI, non-permanent GameObject
   * @return the created GameObject
   */
  static std::shared_ptr<GameObject>
  CreateStandard(/** The x coordinate of this GameObject */
                 int posX,
                 /** The y coordinate of this GameObject */
                 int posY,
                 /** The width of this GameObject */
                 int width,
                 /** The height of this GameObject */
                 int height);

  /** Updates this GameObject */
  void Update();

  /** The position of this GameObject */
  Vector2 position;

  /** The scale of this GameObject */
  Vector2 scale;

  /**
   * Disables this GameObject
   */
  void Disable();

  /** Enables this GameObject */
  void Enable();

  /**
   * Gets whether this GameObject is active
   * @return The GameObject's active state
   */
  bool IsActive() const;

  /**
   * Gets whether this GameObject is colliding with another
   * @return The GameObject's collision state
   */
  bool IsColliding(/** The GameObject to check for collisions */
                   const GameObject& other) const;

  /**
   * Determines the screen region this object takes up. Uses the active camera.
   * @return An SDL_Rect representing the region of the screen.
   */
  SDL_Rect ScreenRegion();

  /**
   * Gets the first component of type C in the component map or null
   * if none are found.
   * @return The first component found of type C
   */
  template <class C>
  std::shared_ptr<C> GetComponent() {
    static_assert(std::is_base_of<Component, C>::value,
                  "C must derive from Component");

    auto it = componentMap.find(GetTypeID<C>());
    if (it == componentMap.end()) {
      return std::shared_ptr<C>(NULL);
    }
    return std::static_pointer_cast<C>(it->second);
  }

  /**
   * Adds a component of type C to the component map
   * @return A shared pointer reference to this GameObject
   */
  template <class C>
  std::shared_ptr<GameObject> AddComponent(std::shared_ptr<C> comp) {
    static_assert(std::is_base_of<Component, C>::value,
                  "C must derive from Component");

    static_cast<std::shared_ptr<Component>>(comp)->SetParentGameObject(
        std::weak_ptr<GameObject>(shared_from_this()));
    componentMap[GetTypeID<C>()] = comp;
    comp->Init();

    return shared_from_this();
  }

 private:
  /** Constructs a GameObject */
  GameObject(/** The x coordinate of this GameObject */
             int posX,
             /** The y coordinate of this GameObject */
             int posY,
             /** The width of this GameObject */
             int width,
             /** The height of this GameObject */
             int height,
             /** Whether this GameObject should use direct screen coordinates */
             bool isUI);

  /** The map of component ids and components for this GameObject */
  std::unordered_map<int, std::shared_ptr<Component>> componentMap;

  /** Whether or not this GameObject is active */
  bool active;

  /** Whether this GameObject should use direct screen coordinates */
  bool isUI;

  /** The last component id used */
  static int lastTypeID;

  /**
   * Gets a new unused component id
   * @return The new id
   * */
  template <class Key>
  inline static int GetTypeID() {
    static const int id = lastTypeID++;
    return id;
  }
};

#endif