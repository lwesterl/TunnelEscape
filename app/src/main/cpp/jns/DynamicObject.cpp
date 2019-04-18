/**
  *   @file DynamicObject.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for DynamicObject
  */


#include "../include/DynamicObject.hpp"

namespace pe {

  // Empty constructor
  DynamicObject::DynamicObject(): PhysicsObject(),
  alreadyCollided(false), updatesFromPrevCollision(2) {}

  // Constructor
  DynamicObject::DynamicObject(Shape *shape, float density):
  PhysicsObject(shape, density, false, ObjectType::DynamicObject),
  alreadyCollided(false), updatesFromPrevCollision(2) {}

  // setForce implementation
  void DynamicObject::setForce(Vector2f force) {
    force *= physics.inverse_mass; // acceloration caused by the force
    physics.acceloration = physics.acceloration + force;
  }

  // setVelocity implementation
  void DynamicObject::setVelocity(Vector2f velocity) {
    physics.velocity = velocity;
  }

  // collisionAction implementation
  void DynamicObject::collisionAction(Vector2f position_change, struct CollisionDetails& collisionDetails) {
    // move DynamicObject to inverse direction to counter collision
    Vector2f direction_unit_vector = Vector2f(ABS(inverse_direction.getX()), ABS(inverse_direction.getY()));
    direction_unit_vector.normalize();
    // update velocity and acceloration so that DynamicObject bouncess of the object it collided based on elasticity
    if (collisionDetails.dynamic_dynamic_collision) {
      physics.velocity = physics.elasticity * ((getMass() - collisionDetails.opponentMass) / (getMass() + collisionDetails.opponentMass) * physics.collision_velocity +
                         (2 * collisionDetails.opponentMass) / (getMass() + collisionDetails.opponentMass) * collisionDetails.opponentVelocity);
    } else {
      /* collision with StaticObject need to be in own statement because mass
        for StaticObject would be std::numeric_limits<float>::max() and cause
        upredictable multiplication results */
      physics.velocity = - physics.elasticity * physics.collision_velocity;
    }
    physics.acceloration.update(0.f, 0.f); // needs to be inited, all acceloration 'used' during the collision

    if ((!alreadyCollided) || (collisionDetails.dynamic_dynamic_collision)) {
      // take vector length, otherwise at least vertical collision tend to fail (caused by how position_change is calculated)
      physics.position += direction_unit_vector * position_change.getLength() * collision_direction;
      if (!collisionDetails.dynamic_dynamic_collision) {
        alreadyCollided = true;
        updatesFromPrevCollision = 0;
      }
    } else {
      // just return DynamicObject to prev position to reduce glithing
      physics.setPosition(getPrevPosition());
      updatesFromPrevCollision++; // this need to be adjusted to indicate that prevPosition can be again updated
    }
  }

  // updatePhysics implementation
  void DynamicObject::updatePhysics(float elapsed_time) {
    // apply gravity to the object
    if (updatesFromPrevCollision < std::numeric_limits<unsigned>::max()) updatesFromPrevCollision++;
    float delta_x = physics.velocity.getX() * elapsed_time +
    0.5f * (physics.acceloration.getX() + PhysicsProperties::GravityX) * elapsed_time * elapsed_time;
    float delta_y = physics.velocity.getY() * elapsed_time +
    0.5f * (physics.acceloration.getY() + PhysicsProperties::GravityY) * elapsed_time * elapsed_time;
    if (updatesFromPrevCollision > 1) prevPosition = physics.position;
    physics.movePosition(Vector2f(delta_x, delta_y));
    // decrease acceloration and velocity based on physics.resistance_factor
    physics.applyResistance(elapsed_time);
    physics.collision_velocity.update(delta_x / elapsed_time, delta_y / elapsed_time);
    inverse_direction = Vector2f(-delta_x, -delta_y);
    alreadyCollided = false;
  }

  // setCollisionDirection implementation
  void DynamicObject::setCollisionDirection(Vector2f direction) {
    direction.normalize();
    collision_direction = direction;
  }

  // Get previous position
  Vector2f DynamicObject::getPrevPosition() {
    return prevPosition - physics.origin_transform;
  }

}// end of namespace pe
