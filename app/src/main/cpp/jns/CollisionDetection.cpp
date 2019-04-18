/**
  *   @file CollisionDetection.cpp
  *   @author Lauri Westerholm
  *   @brief Contains implementations relating to CollisionDetection
  */

#include "../include/CollisionDetection.hpp"


namespace pe {

  namespace CollisionDetection {

    // Calculate possible collision between objects
    bool calculateCollision(PhysicsObject* obj1, PhysicsObject* obj2) {

      // check if objects are even relatively close to one another
      if ((!objectsClose(obj1, obj2)) || (!canCollide(obj1, obj2))) return false;

      // objects could collide, calculate possible collisions
      Shape* shape1 = obj1->getShape();
      Shape* shape2 = obj2->getShape();
      struct MTV mtv;
      // for obj1 axis
      std::vector<Vector2f>& axis = shape1->getAxis();
      for (unsigned i = 0; i < axis.size(); i++) {
        // project both Shapes
        struct Projection proj1 = ProjectShape(axis[i], obj1->getPhysics().position, shape1, obj1->getPhysics().angle);
        struct Projection proj2 = ProjectShape(axis[i], obj2->getPhysics().position, shape2, obj2->getPhysics().angle);
        if (! overlap(proj1, proj2)) return false; // one projection which won't overlap is enough
        mtv = StoreMTV(mtv, axis[i], proj1, proj2);
      }
      // for obj2 axis
      axis = shape2->getAxis();
      for (unsigned i = 0; i < axis.size(); i++) {
        // project both Shapes
        struct Projection proj1 = ProjectShape(axis[i], obj1->getPhysics().position, shape1, obj1->getPhysics().angle);
        struct Projection proj2 = ProjectShape(axis[i], obj2->getPhysics().position, shape2, obj2->getPhysics().angle);
        if (! overlap(proj1, proj2)) return false; // one projection which won't overlap is enough
        mtv = StoreMTV(mtv, axis[i], proj1, proj2);
      }
      // all projections overlap, collision detected
      std::deque<PhysicsObject*> collided = GetCollisionResult(obj1, obj2);
      // move collided according to MTV
      collideObjects(collided, mtv);
      return true;
    }

    //  Check if PhysicsObjects are close
    bool objectsClose(PhysicsObject* obj1, PhysicsObject* obj2) {

      PhysicsProperties& physics1 = obj1->getPhysics();
      PhysicsProperties& physics2 = obj2->getPhysics();
      Vector2f min1 = obj1->getShape()->getMin() + physics1.position;
      Vector2f max1 = obj1->getShape()->getMax() + physics1.position;
      Vector2f min2 = obj2->getShape()->getMin() + physics2.position;
      Vector2f max2 = obj2->getShape()->getMax() + physics2.position;

      // check if min and maxes overlap
      if ( ((max1.getX() < min2.getX()) && (max1.getX() + physics1.velocity.getX() < min2.getX())) ||
            ((min1.getX() > max2.getX()) && (min1.getX() + physics1.velocity.getX() > max2.getX())) ) return false;

      if ( ((max1.getY() < min2.getY()) && (max1.getY() + physics1.velocity.getY() < min2.getY())) ||
            ((min1.getY() > max2.getY()) && (min1.getY() + physics1.velocity.getY() > max2.getY())) ) return false;

      return true;
    }

    // Project Shape on axis
    struct Projection ProjectShape(Vector2f axis, Vector2f position, Shape* shape, float object_angle) {
      // init min and max
      float min = std::numeric_limits<float>::max();
      float max = std::numeric_limits<float>::min();
      std::deque<Vector2f> edges = shape->getFrame();
      for (int i = 0; i < shape->getEdges(); i++) {
        // edge[i] is just a static point, position tells where it's relating to PhysicsWorld origin
        Vector2f edge = edges[i] + position;
        edge.rotate(object_angle); // rotate to angle matching PhysicsObject angle
        float dot = dotProduct(axis, edge);
        if (dot < min) min = dot;
        if (dot > max) max = dot;
      }
      struct Projection projection;
      projection.min = min;
      projection.max = max;
      return projection;
    }

    // Check if Projections overlap
    bool overlap(struct Projection& proj1, struct Projection& proj2) {
      return !(proj1.max < proj2.min || proj2.max < proj1.min);
    }

    // Check if objects can collide
    bool canCollide(PhysicsObject* obj1, PhysicsObject* obj2) {
      return ((obj1->getCollisionMask() ^ 0xFF) & (obj2->getCollisionMask() ^ 0xFF)) != 0;
    }

    // Get correct collision result
     std::deque<PhysicsObject*> GetCollisionResult(PhysicsObject* obj1, PhysicsObject* obj2) {
      uint8_t mask1 = obj1->getCollisionMask();
      uint8_t mask2 = obj2->getCollisionMask();
      setCollisionDirections(obj1, obj2);
      std::deque<PhysicsObject*> objects;
      if (obj1->getObjectType() != ObjectType::StaticObject && mask1 <= mask2) {
        objects.push_back(obj1);
      }
      if (obj2->getObjectType() != ObjectType::StaticObject && mask2 <= mask1) {
        objects.push_back(obj2);
      }
      return objects;
    }

    // Find amount of overlap
    inline float FindOverlap(struct Projection& proj1, struct Projection& proj2) {
      return MIN(std::abs(proj1.max - proj2.min), std::abs(proj2.max - proj1.min));
    }

    // Store MTV of overlap
    struct MTV& StoreMTV(struct MTV& mtv, Vector2f axis, struct Projection& proj1, struct Projection& proj2) {

      float overlap = FindOverlap(proj1, proj2);
      if (overlap < mtv.amount) {
        mtv.axis = axis;
        mtv.amount = overlap;
      }
      return mtv;
    }

    // Collide objects based on MTV
    void collideObjects(std::deque<PhysicsObject*>& objects, struct MTV& mtv) {
      struct CollisionDetails collisionDetails[2];
      unsigned size = objects.size();
      if (!size) return;
      if (size == 2) {
        collisionDetails[0].dynamic_dynamic_collision = true; // static objects are not added to objects so there must be two DynamicObjects
        collisionDetails[1].dynamic_dynamic_collision = true;
        collisionDetails[0].opponentVelocity = objects[1]->getVelocity();
        collisionDetails[1].opponentVelocity = objects[0]->getVelocity();
        collisionDetails[0].opponentMass = objects[1]->getMass();
        collisionDetails[1].opponentMass = objects[0]->getMass();
      }
      Vector2f position_change = mtv.axis; // unit vector which tells direction
      position_change *= mtv.amount / static_cast<float>(size);
      for (unsigned i = 0; i < size; i++) {
        objects[i]->collisionAction(position_change, collisionDetails[i]);
      }
    }

    // Set correct collision direction for objecs, this is the dir where object should move after collision
    void setCollisionDirections(PhysicsObject* obj1, PhysicsObject* obj2) {
      if (obj1->getPrevPosition().getX() < obj2->getPrevPosition().getX()) {
        if (obj1->getPrevPosition().getY() < obj2->getPrevPosition().getY()) {
          obj1->setCollisionDirection(Vector2f(-1.f, -1.f));
          obj2->setCollisionDirection(Vector2f(1.f, 1.f));
        } else {
          obj1->setCollisionDirection(Vector2f(-1.f, 1.f));
          obj2->setCollisionDirection(Vector2f(1.f, -1.f));
        }
      } else if (obj1->getPrevPosition().getY() < obj2->getPrevPosition().getY()) {
        obj1->setCollisionDirection(Vector2f(1.f, -1.f));
        obj2->setCollisionDirection(Vector2f(-1.f, 1.f));
      } else {
        obj1->setCollisionDirection(Vector2f(1.f, 1.f));
        obj2->setCollisionDirection(Vector2f(-1.f, -1.f));
      }
    }

  }// end of namespace CollisionDetection
}// end of namespace pe
