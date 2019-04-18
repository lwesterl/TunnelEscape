/**
  *   @file PhysicsObject.cpp
  *   @author Lauri Westerholm
  *   @brief Source for PhysicsObject
  */

#include "../include/PhysicsObject.hpp"

namespace pe {

  // Constructor
  PhysicsObject::PhysicsObject(Shape *shape, float density, bool static_object, ObjectType::ObjectType type):
  shape(shape), physics(PhysicsProperties(density, shape->getArea(), static_object)), collision_mask(0x00), type(type), moved(false) {}

  // Get ObjectType
  ObjectType::ObjectType PhysicsObject::getObjectType() const {
    return type;
  }

  // Set owner object
  void PhysicsObject::setOwner(void* owner, int type) {
    this->owner = std::make_pair(owner, type);
  }

  // Get owner
  void* PhysicsObject::getOwner() const {
    return owner.first;
  }

  // Get owner type
  int PhysicsObject::getOwnerType() const {
    return owner.second;
  }

  // Get shape
  Shape* PhysicsObject::getShape() const {
    return shape;
  }

  // Get physics
  PhysicsProperties& PhysicsObject::getPhysics() {
    return physics;
  }

  // Set PhysicsObject position in PhysicsWorld
  void PhysicsObject::setPosition(Vector2f position) {
    physics.setPosition(position);
    moved = true;
  }

  // Get PhysicsObject position in PhysicsWorld
  Vector2f PhysicsObject::getPosition() const {
    return physics.position - physics.origin_transform;
  }

  // Get min position in PhysicsWorld
  Vector2f PhysicsObject::getMinPosition() const {
    return getPosition() + shape->getMin();
  }

  // Get max position in PhysicsWorld
  Vector2f PhysicsObject::getMaxPosition() const {
    return getPosition() + shape->getMax();
  }

  // Set origin transform for PhysicsObject
  void PhysicsObject::setOriginTransform(Vector2f transform) {
    physics.origin_transform = transform;
  }

  // Get origin transform of PhysicsObject
  Vector2f& PhysicsObject::getOriginTransform() {
    return physics.origin_transform;
  }

  // Set elasticity of PhysicsObject
  void PhysicsObject::setElasticity(float elasticity) {
    physics.elasticity = std::abs(elasticity);
  }

  // Get elasticity of PhysicsObject
  float PhysicsObject::getElasticity() const {
    return physics.elasticity;
  }

  // Set density
  void PhysicsObject::setDensity(float density) {
    if (type == ObjectType::ObjectType::StaticObject) {
      physics.setDensity(density, shape->getArea(), true);
    }
    else physics.setDensity(density, shape->getArea(), false);

  }
  // Set collision_mask
  void PhysicsObject::setCollisionMask(uint8_t mask) {
    collision_mask = mask;
  }

  // Get collision_mask
  uint8_t PhysicsObject::getCollisionMask() const {
    return collision_mask;
  }

  // Get mass
  float PhysicsObject::getMass() const {
    return physics.inverse_mass ? 1.f / physics.inverse_mass : std::numeric_limits<float>::max();
  }

}// end of namespace pe
