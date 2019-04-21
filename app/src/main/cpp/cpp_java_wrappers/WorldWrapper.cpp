/**
  *   @file WorldWrapper.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for WorldWrapper class
  */

#include "WorldWrapper.hpp"

// Static wrapper for setting the interval for updating physics
void WorldWrapper::setPhysicsWorldUpdateInterval(float interval) {
   if (interval) PhysicsWorld::setIterationAmount(1.f / interval);
}

// Init static ID, this should be always updated when new object is added and returned to Java implementations
unsigned WorldWrapper::ObjectID = 1;

// Deconstructor
WorldWrapper::~WorldWrapper() {
  delete physicsWorld;
  // now all shapes should be ok to deallocate
  for (auto it = shapes.begin(); it != shapes.end(); ) {
    delete (it->second);
    it = shapes.erase(it);
  }
}

// Update PhysicsWorld periodically
std::deque<Pair> WorldWrapper::update() {
  physicsWorld->update();
  // also return collided objects as list
  std::deque<Pair> pairs;
  std::list<struct Collided>& collided = physicsWorld->getCollided();
  auto getKey = [this] (PhysicsObject* obj) -> unsigned {
                        auto it = objectsToKeys.find(obj);
                        return it != objectsToKeys.end() ? it->second : 0; };
  for (auto& item : collided) {
      Pair pair(getKey(item.first), getKey(item.second));
      pairs.push_back(pair);
  }
  return pairs;
}

// Add object to physicsWorld
unsigned WorldWrapper::addObject(bool static_object, Vector2f pos, float width, float height) {
  Shape *shape = GetShape(width, height);
  PhysicsObject *object;
  if (static_object) {
    object = new StaticObject(shape);
  } else {
    object = new DynamicObject(shape, STD_DENSITY);
  }
  object->setPosition(pos);
  // add object to physicsWorld
  if (physicsWorld->addObject(object)) {
    // add to the maps with correct key
    keysToObjects.emplace(WorldWrapper::ObjectID, object);
    objectsToKeys.emplace(object, WorldWrapper::ObjectID);
    unsigned currentID = WorldWrapper::ObjectID;
    WorldWrapper::ObjectID++;
    return currentID;
  }
  // failed to add object to physicsWorld
  return 0;
}

// Remove object from the world
void WorldWrapper::removeObject(unsigned key) {
  PhysicsObject* object = GetObject(key);
  if (object) {
    // remove object from the maps
    auto it = keysToObjects.find(key);
    if (it != keysToObjects.end()) keysToObjects.erase(it);
    auto it2 = objectsToKeys.find(object);
    if (it2 != objectsToKeys.end()) objectsToKeys.erase(it2);
    // remove from physicsWorld, this also frees the memory
    physicsWorld->removeObject(object);
  }
}

// Set physics values for the object
void WorldWrapper::setObjectPhysicsProperties(unsigned key, float elasticity, float density) {
  PhysicsObject* object = GetObject(key);
  if (object) {
    object->setElasticity(elasticity);
    object->setDensity(density);
  }
}

// Set object collision mask, note: input must be converted to uint8_t
void WorldWrapper::setObjectCollisionMask(unsigned key, unsigned mask) {
  PhysicsObject* object = GetObject(key);
  if (object) {
    object->setCollisionMask(static_cast<uint8_t> (mask));
  }
}

// Set object origin_transform
void WorldWrapper::setObjectOriginTransform(unsigned key, Vector2f transform) {
  PhysicsObject* object = GetObject(key);
  if (object) {
    object->setOriginTransform(transform);
  }
}

// Set force for object
void WorldWrapper::setObjectForce(unsigned key, Vector2f force) {
  PhysicsObject* object = GetObject(key);
  if (object) {
    object->setForce(force);
  }
}

// Set velocity for object
void WorldWrapper::setObjectVelocity(unsigned key, Vector2f velocity) {
  PhysicsObject* object = GetObject(key);
  if (object) {
    object->setVelocity(velocity);
  }
}

// Set object position
void WorldWrapper::setObjectPosition(unsigned key, Vector2f pos) {
  PhysicsObject* object = GetObject(key);
  if (object) {
    object->setPosition(pos);
  }
}

// Get object position and whether object still exists
struct ObjectStatus WorldWrapper::fetchPosition(unsigned key) const {
  struct ObjectStatus status;
  PhysicsObject* object = GetObject(key);
  if (object) {
    status.position = object->getPosition();
  } else {
    status.exists = false;
  }
  return status;
}

// Get correct Shape, private method
Shape* WorldWrapper::GetShape(float width, float height) {
  auto it = shapes.find(Vector2f(width, height));
  if (it == shapes.end()) {
    // inset new Shape
    Shape* new_shape = new Shape(width, height);
    shapes.emplace(Vector2f(width, height), new_shape);
    return new_shape;
  }
  return it->second;
}

// Get correct PhysicsObject, private method
PhysicsObject* WorldWrapper::GetObject(unsigned key) const {
  auto it = keysToObjects.find(key);
  return it != keysToObjects.end() ? it->second : nullptr;
}
