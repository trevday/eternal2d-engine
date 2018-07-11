#include "PhysicsComponent.hpp"

#include "GameObject.hpp"
#include "PhysicsManager.hpp"

b2BodyWrapper::b2BodyWrapper(b2Body* body) : body(body) {}

b2BodyWrapper::~b2BodyWrapper() {
  PhysicsManager::GetWorld()->DestroyBody(body);
}

void PhysicsComponent::SetupBodyWithShape(BodyType type, b2Shape* shape,
                                          float32 density, float32 friction,
                                          float32 restitution) {
  b2BodyDef bodyDef;
  if (type == BodyType::DYNAMIC) {
    bodyDef.type = b2_dynamicBody;
  } else if (type == BodyType::STATIC) {
    bodyDef.type = b2_staticBody;
  } else {
    bodyDef.type = b2_kinematicBody;
  }

  bodyDef.position.Set(0, 0);

  body = std::make_shared<b2BodyWrapper>(
      PhysicsManager::GetWorld()->CreateBody(&bodyDef));

  b2FixtureDef fixture;
  fixture.shape = shape;
  fixture.density = density;
  fixture.friction = friction;
  fixture.restitution = restitution;
  body->body->CreateFixture(&fixture);
}

PhysicsComponent::PhysicsComponent(BodyType type, std::vector<Vector2> points,
                                   float32 density, float32 friction,
                                   float32 restitution, bool managedByPhysics)
    : managedByPhysics(managedByPhysics) {
  b2Vec2* b2points = new b2Vec2[points.size()];
  for (int i = 0; i < points.size(); ++i) {
    b2points[i] = b2Vec2(points.at(i).x  / physicsScale, points.at(i).y  / physicsScale);
  }
  b2PolygonShape shape;
  shape.Set(b2points, points.size());
  delete [] b2points;

  SetupBodyWithShape(type, &shape, density, friction, restitution);
}

PhysicsComponent::PhysicsComponent(BodyType type,
                                   float32 width, float32 height,
                                   float32 density,
                                   float32 friction, float32 restitution,
                                   bool managedByPhysics)
    : managedByPhysics(managedByPhysics) {
  b2PolygonShape shape;
  shape.SetAsBox((width / 2.0)  / physicsScale, (height / 2.0)  / physicsScale);

  SetupBodyWithShape(type, &shape, density, friction, restitution);
}

void PhysicsComponent::Init() {
  body->body->SetTransform(
      b2Vec2(gameObject.lock()->position.x / physicsScale, gameObject.lock()->position.y / physicsScale), 0);
}

void PhysicsComponent::Update() {
  if (managedByPhysics) {
    gameObject.lock()->position.x = body->body->GetPosition().x * physicsScale;
    gameObject.lock()->position.y = body->body->GetPosition().y * physicsScale;
  }
}

void PhysicsComponent::ApplyForce(Vector2 force, Vector2 point) {
  body->body->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(point.x  / physicsScale, point.y  / physicsScale),
                         true);
}

void PhysicsComponent::ApplyForceToCenter(Vector2 force) {
  body->body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

Vector2 PhysicsComponent::GetLinearVelocity() {
  return Vector2(body->body->GetLinearVelocity().x,
                 body->body->GetLinearVelocity().y);
}

void PhysicsComponent::SetLinearVelocity(Vector2 linear) {
  body->body->SetLinearVelocity(b2Vec2(linear.x, linear.y));
}

void PhysicsComponent::SetActive(bool active) { body->body->SetActive(active); }

void PhysicsComponent::SetManagedByPhysics(bool managed) {
  managedByPhysics = managed;
}