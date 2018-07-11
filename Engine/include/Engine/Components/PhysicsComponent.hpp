#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

#include "Component.hpp"
#include "Vector2.hpp"

#include <Box2D/Box2D.h>
#include <vector>

/** The body type of a given physics component */
enum class BodyType { DYNAMIC, STATIC, KINEMATIC };

/** A wrapper class for a Box2D Body */
struct b2BodyWrapper {
  /** Constructs a Box2D body wrapper */
  b2BodyWrapper(/** The Box2D body of this wrapper */
                b2Body* body);
  /** Destructs a Box2D body wrapper */
  ~b2BodyWrapper();

  /** The Box2D body of this wrapper */
  b2Body* body;
};

/** A component that generates physics for a GameObject */
class PhysicsComponent : public Component {
 public:
  /** Constructs a new physics component */
  PhysicsComponent(/** The body type of this physics component */
                   BodyType type, 
                   /** List of points to define the shape of this component */
                   std::vector<Vector2> points, 
                   /** The density of this physics component */
                   float32 density,
                   /** The friction of this physics component */
                   float32 friction, 
                   /** The restitution of this physics component */
                   float32 restitution,
                   /** Whether or not this physics component is managed by physics */
                   bool managedByPhysics);

  /** Constructs a new physics component */
  PhysicsComponent(/** The body type of this physics component */
                   BodyType type, 
                   /** The width of this physics component */
                   float32 width, 
                   /** The height of this physics component */
                   float32 height,
                   /** The density of this physics component */
                   float32 density, 
                   /** The friction of this physics component */
                   float32 friction, 
                   /** The restitution of this physics component */
                   float32 restitution,
                   /** Whether or not this physics component is managed by physics */
                   bool managedByPhysics);

  void Init() override;

  void Update() override;

  /** Applies the given force to the given point relative to this object */
  void ApplyForce(/** The force to be applied. */
                  Vector2 force, 
                  /** The point the force will be applied to. */
                  Vector2 point);

  /** Applies the given force to the center of this object */
  void ApplyForceToCenter(/** The force to be applied. */
                          Vector2 force);

  /** 
   * Gets the linear velocity of this object. 
   * @return The linear velocity of this object. 
   */
  Vector2 GetLinearVelocity();

  /** 
   * Sets the linear velocity of this object. 
   */
  void SetLinearVelocity(/** The linear velocity to be set */
                         Vector2 linear);

  /** Sets the active state of the body of this physics component */
  void SetActive(/** Whether or not the body is active */
                 bool active);


  /** Sets whether this physics component is managed by physics */
  void SetManagedByPhysics(/** Whether or not this physics component is managed by physics */
                           bool managed);

 private:
  /** Sets up the Box2D body of this physics component with the given characteristics */
  void SetupBodyWithShape(/** The body type of the Box2D body. */
                          BodyType type, 
                          /** The shape of the Box2D body. */
                          b2Shape* shape, 
                          /** The density of the Box2D body. */
                          float32 density,
                          /** The friction of the Box2D body. */
                          float32 friction, 
                          /** The restitution of the Box2D body. */
                          float32 restitution);

  /** The Box2D body of this physics component */
  std::shared_ptr<b2BodyWrapper> body;

  /** Whether or not this physics component is managed by physics */
  bool managedByPhysics;

  /** The scale of the physics relative to the world size */
  const float physicsScale = 200.0;
};

#endif