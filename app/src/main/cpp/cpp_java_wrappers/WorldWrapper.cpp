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
std::list<struct Pair> WorldWrapper::update() {
  physicsWorld->update();
  // also return collided objects as list
  std::list<struct Pair> pairs;
  std::list<struct Collided>& collided = physicsWorld->getCollided();
  auto getKey = [this] (PhysicsObject* obj) -> unsigned {
                        auto it = objectsToKeys.find(obj);
                        return it != objectsToKeys.end() ? it->second : 0; };
  for (auto& item : collided) {
      struct Pair pair(getKey(item.first), getKey(item.second));
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
