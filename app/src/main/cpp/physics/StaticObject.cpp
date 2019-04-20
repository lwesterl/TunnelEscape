/**
  *   @file StaticObject.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for StaticObject
  */

#include "StaticObject.hpp"



  // Empty constructor
  StaticObject::StaticObject(): PhysicsObject() {}

  // Constructor
  StaticObject::StaticObject(Shape* shape):
  PhysicsObject(shape, 0.f, true, ObjectType::StaticObject) {}

  // Get previous position
  Vector2f StaticObject::getPrevPosition() {
    return physics.position - physics.origin_transform;
  }


