/**
  *   @file PhysicsProperties.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for PhysicsProperties
  */


#include "../include/PhysicsProperties.hpp"

namespace pe {

  // Member variable initializations
  float PhysicsProperties::GravityX = 0.f;
  float PhysicsProperties::GravityY = 9.81f; // notice direction
  float PhysicsProperties::SizeScale = 0.1f;

  // Empty constructor
  PhysicsProperties::PhysicsProperties(): angle(0.f), density(0.f), elasticity(0.f),
  inverse_mass(0.f), resistance_factor(1.2f), resistance_counter(0) {}

  // Constructor
  PhysicsProperties::PhysicsProperties(float density, float area, bool static_object):
  angle(0.f), density(std::abs(density)), elasticity(PhysicsProperties::DefaultElasticity), resistance_factor(1.2f), resistance_counter(0) {
    CalculateInverseMass(area, static_object);
  }

  // Set position
  void PhysicsProperties::setPosition(Vector2f pos) {
    position = pos + origin_transform;
  }

  // Move position
  void PhysicsProperties::movePosition(Vector2f move) {
    position = position + move;
  }

  // Apply resisting forces
  void PhysicsProperties::applyResistance(float elapsed_time) {
    if (resistance_counter % PhysicsProperties::ResistanceInterval == 0)
    {
      velocity.update(velocity.getX() * (1.f - elapsed_time / resistance_factor),
                      velocity.getY() * (1.f - elapsed_time / resistance_factor));
      acceloration.update(acceloration.getX() * (1.f - elapsed_time / sqrt(resistance_factor)),
                      acceloration.getY() * (1.f - elapsed_time / sqrt(resistance_factor)));
      resistance_counter = 0;
    }
    resistance_counter++;
  }

  // Calculate inverse of the object mass, private method
  void PhysicsProperties::CalculateInverseMass(float area, bool static_object) {
    if (static_object) inverse_mass = 0.f;
    else {
      if ((density != 0.f) && (area != 0.f)) {
        inverse_mass = 1.f / (area * density * PhysicsProperties::SizeScale);
      }
     else inverse_mass = std::numeric_limits<float>::max();
    }
  }

  // Set density
  void PhysicsProperties::setDensity(float density, float area, bool static_object) {
    if (!static_object) this->density = density;
    CalculateInverseMass(area, static_object);
  }


}// end of namespace pe
