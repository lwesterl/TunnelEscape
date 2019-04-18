/**
  *   @file PhysicsObject.hpp
  *   @author Lauri Westerholm
  *   @brief Header for PhysicsObject
  */


#pragma once

#include "../utils/Vector2.hpp"
#include "../include/Shape.hpp"
#include "../include/PhysicsProperties.hpp"
#include <cmath>
#include <utility>
#include <cstdint>

/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {


  /**
    *   @namespace ObjectType
    *   @brief Used just to avoid namespace collisions between DynamicObject and StaticObject
    */
  namespace ObjectType {

    /**
      *   @enum ObjectType
      *   @brief Tells whether PhysicsObject is DynamicObject or StaticObject
      */
    enum ObjectType {
      DynamicObject, /**< DynamicObject */
      StaticObject  /**< StaticObject */
    };
  } // end of namespace ObjectType

  /**
    *   @struct CollisionDetails
    *   @brief Contain the necessary info about collided objects so that correct
    *   collision results can be calculated in DynamicObject
    *   @remark no need to set oppentVelocity or opponentMass if collision between
    *   DynamicObject and StaticObject
    */
  struct CollisionDetails {
    bool dynamic_dynamic_collision = false; /**< whether collision is between two dynamicObjects, then the other values must be set */
    Vector2f opponentVelocity; /**< opponent collision_velocity, no need to define if collision is between static and dynamic object */
    float opponentMass; /**< mass of the opponent in collision, no need to define if collision is between static and dynamic object */
  };


  /**
    *   @class PhysicsObject
    *   @brief Abstract class for all objects in the PhysicsWorld
    *   @details Class allows to connect an owner object (should be the object used for rest
    *   of the logic, and possibly drawing). Owner object is stored as void pointer and its
    *   type can be stored as int (enum value) for recasting purposes. PhysicsObject won't
    *   delete the owner pointer on deconstructor. This has to be done elsewhere
    */
  class PhysicsObject
  {
    public:
      /**
        *   @brief Empty constructor
        */
        PhysicsObject() {}

      /**
        *   @brief Virtual deconstructor
        */
        virtual ~PhysicsObject() {}

      /**
        *   @brief Constructor
        *   @param shape matching Shape (pass valid Shape, otherwise causes segmentation violation)
        *   @param density tells object 2D density, used in calculating mass
        *   @param static_object tells whether object is static or not
        *   @param type Object type (passed by lower class constructor, DynamicObject / StaticObject)
        *   @details Constructs PhysicsProperties based on the density and Shape. By default all objects collide with
        *   each other, use setCollisionMask() to change this behaviour
        */
      PhysicsObject(Shape *shape, float density, bool static_object, ObjectType::ObjectType type);

      /**
        *   @brief Set force for PhysicObject
        *   @details implemented in lower classes
        *   @param force force to be set for the object
        */
      virtual void setForce(Vector2f force) = 0;

      /**
        *   @brief Set velocity for PhysicObject
        *   @details implemented in lower classes
        *   @param velocity velocity to be set for the object
        */
      virtual void setVelocity(Vector2f velocity) = 0;

      /**
        *   @brief Calculate collision action for the object
        *   @details implemented in lower classes
        *   @param position_change change needed to avoid collision
        *   @param collisionDetails CollisionDetails needed to calculate velocity after collision
        */
      virtual void collisionAction(Vector2f position_change, struct CollisionDetails& collisionDetails) = 0;

      /**
        *   @brief Update objects physics
        *   @details implemented in lower classes
        *   @remark DO NOT call this outside PhysicsWorld
        */
      virtual void updatePhysics(float elapsed_time) = 0;

      /**
        *   @brief Set collision direction
        *   @details implemented in lower classes
        *   @param direction collision direction
        */
      virtual void setCollisionDirection(Vector2f direction) = 0;

      /**
        *   @brief Get object previous position
        *   @details implemented in lower classes
        *   @return previous position
        */
      virtual Vector2f getPrevPosition() = 0;

      /**
        *   @brief Get ObjectType
        *   @return type
        */
      ObjectType::ObjectType getObjectType() const;

      /**
        *   @brief Set owner object
        *   @param owner Owner object casted to void*, use static_cast<void*>
        *   @param type possible object type which may help in recasting (int based enum recommended)
        */
      void setOwner(void* owner, int type=0);

      /**
        *   @brief Get owner
        *   @return owner (void *, must be recasted)
        */
      void* getOwner() const;

      /**
        *   @brief Get owner type
        *   @return owner type stored as an int value
        */
      int getOwnerType() const;

      /**
        *   @brief Get Shape
        *   @return shape (Shape*)
        */
      Shape* getShape() const;

      /**
        *   @brief Get PhysicsProperties of the object
        *   @return physics as reference
        */
      PhysicsProperties& getPhysics();

      /**
        *   @brief Set position for object
        *   @param position new physics.position
        *   @details position is normally calculated in relation to Shape center of mass.
        *   setOriginTransform to choose arbitrary base point for position
        *   @remark If PhysicsObject is added to PhysicsWorld you need to call
        *   PhysicsWorld.update() before you try to remove the PhysicsObject
        */
      void setPosition(Vector2f position);

      /**
        *   @brief Get PhysicsObject position
        *   @return physics.position - origin_transform
        *   @remark This position notifys origin_transform, so returns position in user set coordinates
        */
      Vector2f getPosition() const;

      /**
        *   @brief Get PhysicsObject smallest edge position
        *   @return Shape min + getPosition
        */
      Vector2f getMinPosition() const;

      /**
        *   @brief Get PhysicsObject biggest edge position
        *   @return Shape max + getPosition
        */
      Vector2f getMaxPosition() const;

      /**
        *   @brief Set origin transform
        *   @details PhysicsObject position is normally calculated in relation to shape
        *   center of mass. Use setOriginTransform to move the base point for position related
        *   calculation. e.g. want to move object from its left upper corner, set transform to be
        *   Vector2f from the left upper corner to the shape central.
        *   @param transform positive x values moves object origin to left and positive y values
        *   upwards
        */
      void setOriginTransform(Vector2f transform);

      /**
        *   @brief Get current origin transform
        *   @return physics.origin_transform
        *   @see setOriginTransform
        */
      Vector2f& getOriginTransform();

      /**
        *   @brief Set elasticity for PhysicsObject
        *   @details By default elasticity is set to 0.9 in PhysicsProperties. Use
        *   this to adjust bounciness of the object: higher values -> more bounciness
        */
      void setElasticity(float elasticity);

      /**
        *   @brief Get elasticity of PhysicsObject
        *   @return physics.elasticity
        */
      float getElasticity() const;

      /**
        *   @brief Set PhysicsObject density
        *   @remark Use this method to change density after PhysicsObject is created
        *   This will set density using PhysicsProperties.setDensity()
        *   @param density new density value, abs is taken
        */
      void setDensity(float density);

      /**
        *   @brief Set collision mask
        *   @details 0xFF -> objects won't collide with anything. 0x00 -> objects collides
        *   with everything (default). Objects can't collide with others which have smaller collision_masks
        *   @param mask New collision_mask value
        */
      void setCollisionMask(uint8_t mask);

      /**
        *   @brief Get collision mask
        *   @return collision_mask
        */
      uint8_t getCollisionMask() const;

      /**
        *   @brief Check if moved
        *   @return moved
        */
      inline bool getMoved() {
        return moved;
      }

      /**
        *   @brief Set moved
        */
      inline void setMoved(bool moved) {
        this->moved = moved;
      }

      /**
        *   @brief Get object mass
        *   @details if PhysicsProperties.inverse_mass == 0.f returns
        *   std::numeric_limits<float>::max()
        *   @return 1.f/inverse_mass
        */
      float getMass() const;

      /**
        *   @brief Get object current velocity, this is the velocity used in
        *   collisions
        *   @return physics.collision_velocity
        */
      inline Vector2f getVelocity() const {
        return physics.collision_velocity;
      }

    protected:

      Shape *shape = nullptr; /**< Shape matching PhysicsObject, polygon */
      PhysicsProperties physics;  /**< PhysicsProperties of PhysicsObject */
      std::pair<void*, int> owner; /**< Pair made out of owner object and possible int type used for it */
      uint8_t collision_mask; /**< Value used in collision detection, 0x00 - 0xFF.
      No collisions with objects which have smaller collision_masks. 0xFF -> no collisions at all */
      ObjectType::ObjectType type;  /**< PhysicsObject type, either DynamicObject or StaticObject */
      bool moved; /**< Whether PhysicsObject is moved */


  };
} // end of namespace pe
