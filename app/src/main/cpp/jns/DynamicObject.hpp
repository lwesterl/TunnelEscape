/**
  *   @file DynamicObject.hpp
  *   @author Lauri Westerholm
  *   @brief Header for DynamicObject
  */

#pragma once

#include "PhysicsObject.hpp"
#include <limits>

#define ABS(a) ((a) > 0 ? (a) : -(a)) /**< Macro for abs, use carefully */


/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {

  /**
    *   @class DynamicObject
    *   @brief PhysicsWorld dynamic object, inherits PhysicsObject
    */
    class DynamicObject: public PhysicsObject
    {
      public:

        /**
          *   @brief Empty constructor
          */
        DynamicObject();

        /**
          *   @brief Constructor for DynamicObject
          *   @param shape Shape which matches to the DynamicObject
          *   @param density 2D density of the object
          */
        DynamicObject(Shape *shape, float density);

        /**
          *   @brief Set force for DynamicObject
          *   @see PhysicsObject setForce
          *   @details force changes the acceloration value in PhysicsProperties of the object
          *   @param force force to be set for the object
          */
        virtual void setForce(Vector2f force) override;

        /**
          *   @brief Set velocity for DynamicObject
          *   @see PhysicsObject setVelocity
          *   @details velocity replaces old velocity value in PhysicsProperties of the object
          *   @param velocity velocity to be set for the object
          */
        virtual void setVelocity(Vector2f velocity) override;

        /**
          *   @brief Implementation of collisionAction from PhysicsObjects
          *   @details pushes DynamicObject avoid from other object by position_change
          *   @todo Physics could be tuned. The implementation isn't that trustworthy,
          *   there may be still be cases when it doesn't work properly
          */
        virtual void collisionAction(Vector2f position_change, struct CollisionDetails& collisionDetails) override;

        /**
          *   @brief Implementation of updatePhysics from PhysicObject
          *   @details Updates DynamicObject PhysicsProperties, physics, based
          *   on elapsed_time
          *   @param elapsed_time time elapsed from the last update (in seconds)
          *   @remark Gravity needs to be high value to make objects fall fast ->
          *   some scaling number could be used to make more realistic gravity values
          *   suitable
          */
        virtual void updatePhysics(float elapsed_time) override;

        /**
          *   @brief Set collision action direction, implemented from the base class
          *   @param direction new collision_direction, this method will normalize direction
          */
        virtual void setCollisionDirection(Vector2f direction) override;

        /**
          *   @brief Get previous DynamicObject position, implemented form the base class
          *   @return prev position with origin_transform removed
          */
        virtual Vector2f getPrevPosition() override;


      private:
        Vector2f inverse_direction; /**< Vector pointing to the opposite direction than current movement */
        Vector2f collision_direction; /**< Unit vector which tells direction for collision action */
        Vector2f prevPosition; /**< Stores previous position for the DynamicObject */
        bool alreadyCollided; /**< Whether object is already collided during this update cycle */
        unsigned updatesFromPrevCollision; /**< Tells basically how many updates ago object collided last time so that it's position wasn't reverted to prevPosition */

    };

}// end of namespace pe
