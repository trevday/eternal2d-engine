#ifndef PHYSICS_MANAGER_HPP
#define PHYSICS_MANAGER_HPP

#include <Box2D/Box2D.h>
#include <memory>

/**
 * This class manages the physics of our game as a singleton.
 */
class PhysicsManager {
 public:
  /** The singleton instance of the PhysicsManager */
  static PhysicsManager& instance();

  /** Initializes the physics manager */
  void init();

  /** Shuts down the physics manager */
  void shutdown();

  /** 
   * Gets the Box2D world of the physics manager.
   * @return The Box2D world of the physics manager.
   */
  static std::shared_ptr<b2World> GetWorld();

  /** Sets the gravity of this physics manager */
  static void SetGravity(/** The x value of the gravity (normally this is 0) */
                         float x, 
                         /** The y value of the gravity (earth gravity is -9.8) */
                         float y);

  /** Initiates a step of the physics simulation for all physics objects in the world */
  void Step();

  /** Stop the compiler from generating methods to copy the object */
  PhysicsManager(const PhysicsManager&) = delete;

  /** Stop the compiler from generating methods to copy the object */
  PhysicsManager& operator=(const PhysicsManager&) = delete;

 private:
  /** Constructs a PhysicsManager */
  PhysicsManager();

  /** Destructs a PhysicsManager */
  ~PhysicsManager();

  /** The Box2D world of this physics manager */
  std::shared_ptr<b2World> world;
};

#endif