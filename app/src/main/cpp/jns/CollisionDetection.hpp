/**
  *   @file CollisionDetection.hpp
  *   @author Lauri Westerholm
  *   @brief Contains collision detection related function definitions
  *   @details functions are under namespace pe::CollisionDetection
  */

#pragma once

#include "../utils/Vector2.hpp"
#include "PhysicsObject.hpp"
#include "PhysicsProperties.hpp"
#include <vector>
#include <deque>
#include <limits>

#define MIN(a, b) ((a) < (b) ? (a) : (b)) /**< Macro for min value */

/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {

  /**
    *   @namespace CollisionDetection
    *   @brief Contains all collision detection related functions
    *   @details These functions should be called periodically from PhysicsWorld
    *   @remark currently no real time collision detection support
    */
  namespace CollisionDetection {

    /**
      *   @struct Projection
      *   @brief Struct used for storing Shape projection results
      */
    struct Projection {
      float min; /**< min projection result */
      float max; /**< max projection result */
    };

    /**
      *   @struct MTV
      *   z@brief Minimum translation vector
      */
    struct MTV {
      Vector2f axis; /**< direction of the translation */
      float amount = std::numeric_limits<float>::max(); /**< size of the translation needed, init to max value */
    };

    /**
      *   @brief Calculate collision between PhysicsObjects
      *   @details Check if objects have collided and apply necessary forces to the
      *   objects to separate them
      *   @param obj1 1st PhysicsObject to be checked
      *   @param obj2 2nd PhysicsObject to be checked
      *   @return true if obj1 and obj2 collided, else false
      *   @remark This is the function which provides interface for collision detection
      *   and should be called from PhysicsWorld
      */
    bool calculateCollision(PhysicsObject* obj1, PhysicsObject* obj2);

    /**
      *   @brief Check if objects are close to each other
      *   @details This functions should tell whether objects could collide with each other.
      *   So it tells whether further calculations need to be made. The idea is to detect
      *   a situation where objects cannot collide asap: then there is no need to make
      *   more precise calculations
      *   @param obj1 1st PhysicObject to be checked
      *   @param obj2 2nd PhysicsObject to be checked
      *   @return true if objects could collide, else false
      */
    bool objectsClose(PhysicsObject* obj1, PhysicsObject* obj2);

    /**
      *   @brief Project Shape on axis
      *   @param axis axis on which Shape is projected. axis must have correct
      *   orientation
      *   @param position Shape position in PhysicsWorld (should be matching PhysicObject position)
      *   @param shape Shape to be projected on axis
      *   @param object_angle rotation angle of the shape (should match to PhysicsObject's
      *   rotation angle in PhysicsProperties)
      *   @return Projection with min and max projection values
      */

    struct Projection ProjectShape(Vector2f axis, Vector2f position, Shape* shape, float object_angle);

    /**
      *   @brief Check whether Projections overlap
      *   @param proj1 1st Projection to check
      *   @param proj2 2nd Projection to check
      *   @return true if Projections overlap, else false
      */
    bool overlap(struct Projection& proj1, struct Projection& proj2);

    /**
      *   @brief Check whether objects can collide
      *   @details collision_masks define if they can collide
      *   @param obj1 1st PhysicsObject to be checked
      *   @param obj2 2nd PhysicsObject to be checked
      *   @return true if objects can collide, otherwise false
      */
    bool canCollide(PhysicsObject* obj1, PhysicsObject* obj2);

    /**
      *   @brief Get result of the collision
      *   @details The list is returned based on ObjectTypes and collision_masks
      *   StaticObjects cannot have collision action. Also, objects can only have action
      *   with objects which have smaller collision_masks
      *   @remark not optimal in terms of performance (copies std::list)
      *   @return deque of objects which should be moved etc as the result
      */
    std::deque<PhysicsObject*> GetCollisionResult(PhysicsObject* obj1, PhysicsObject* obj2);

    /**
      *   @brief Find overlap
      *   @details This should be called after overlapping is confirmed with overlap()
      *   @param proj1 1st Projection
      *   @param proj2 2nd Projection
      *   @return amount of overlap
      */
    inline float FindOverlap(struct Projection& proj1, struct Projection& proj2);

    /**
      *   @brief Store MTV based on the overlap
      *   @param mtv minimum translation vector
      *   @param axis direction of the translation axis
      *   @param proj1 1st Projection
      *   @param proj2 2nd Projection
      */
    struct MTV& StoreMTV(struct MTV& mtv, Vector2f axis, struct Projection& proj1, struct Projection& proj2);

    /**
      *   @brief Collide ojects after collision is detected
      *   @param objects deque of objects that should be collided
      *   @param mtv minimum translation vector
      */
    void collideObjects(std::deque<PhysicsObject*>& objects, struct MTV& mtv);

    /**
      *   @brief Set correct collision direction for objects
      *   @param obj1 1st collided object
      *   @param obj2 2nd collided object
      */
    void setCollisionDirections(PhysicsObject* obj1, PhysicsObject* obj2);

  } // end of namespace CollisionDetection
} // end of namespace pe
