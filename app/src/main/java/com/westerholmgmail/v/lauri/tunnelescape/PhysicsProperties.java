/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.westerholmgmail.v.lauri.tunnelescape;

public class PhysicsProperties {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected PhysicsProperties(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PhysicsProperties obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        PhysicsPropertiesModuleJNI.delete_PhysicsProperties(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static void setGravityX(float value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_GravityX_set(value);
  }

  public static float getGravityX() {
    return PhysicsPropertiesModuleJNI.PhysicsProperties_GravityX_get();
  }

  public static void setGravityY(float value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_GravityY_set(value);
  }

  public static float getGravityY() {
    return PhysicsPropertiesModuleJNI.PhysicsProperties_GravityY_get();
  }

  public static void setSizeScale(float value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_SizeScale_set(value);
  }

  public static float getSizeScale() {
    return PhysicsPropertiesModuleJNI.PhysicsProperties_SizeScale_get();
  }

  public PhysicsProperties() {
    this(PhysicsPropertiesModuleJNI.new_PhysicsProperties__SWIG_0(), true);
  }

  public PhysicsProperties(float density, float area, boolean static_object) {
    this(PhysicsPropertiesModuleJNI.new_PhysicsProperties__SWIG_1(density, area, static_object), true);
  }

  public PhysicsProperties(float density, float area) {
    this(PhysicsPropertiesModuleJNI.new_PhysicsProperties__SWIG_2(density, area), true);
  }

  public PhysicsProperties getPointer() {
    long cPtr = PhysicsPropertiesModuleJNI.PhysicsProperties_getPointer(swigCPtr, this);
    return (cPtr == 0) ? null : new PhysicsProperties(cPtr, false);
  }

  public void setPosition(Vector2f pos) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_setPosition(swigCPtr, this, Vector2f.getCPtr(pos), pos);
  }

  public void movePosition(Vector2f move) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_movePosition(swigCPtr, this, Vector2f.getCPtr(move), move);
  }

  public void applyResistance(float elapsed_time) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_applyResistance(swigCPtr, this, elapsed_time);
  }

  public void setDensity(float density, float area, boolean static_object) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_setDensity(swigCPtr, this, density, area, static_object);
  }

  public void setVelocity(Vector2f value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_velocity_set(swigCPtr, this, Vector2f.getCPtr(value), value);
  }

  public Vector2f getVelocity() {
    long cPtr = PhysicsPropertiesModuleJNI.PhysicsProperties_velocity_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Vector2f(cPtr, false);
  }

  public void setCollision_velocity(Vector2f value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_collision_velocity_set(swigCPtr, this, Vector2f.getCPtr(value), value);
  }

  public Vector2f getCollision_velocity() {
    long cPtr = PhysicsPropertiesModuleJNI.PhysicsProperties_collision_velocity_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Vector2f(cPtr, false);
  }

  public void setAcceloration(Vector2f value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_acceloration_set(swigCPtr, this, Vector2f.getCPtr(value), value);
  }

  public Vector2f getAcceloration() {
    long cPtr = PhysicsPropertiesModuleJNI.PhysicsProperties_acceloration_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Vector2f(cPtr, false);
  }

  public Vector2f getPosition() {
    long cPtr = PhysicsPropertiesModuleJNI.PhysicsProperties_position_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Vector2f(cPtr, false);
  }

  public void setOrigin_transform(Vector2f value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_origin_transform_set(swigCPtr, this, Vector2f.getCPtr(value), value);
  }

  public Vector2f getOrigin_transform() {
    long cPtr = PhysicsPropertiesModuleJNI.PhysicsProperties_origin_transform_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Vector2f(cPtr, false);
  }

  public void setAngle(float value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_angle_set(swigCPtr, this, value);
  }

  public float getAngle() {
    return PhysicsPropertiesModuleJNI.PhysicsProperties_angle_get(swigCPtr, this);
  }

  public void setDensity(float value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_density_set(swigCPtr, this, value);
  }

  public float getDensity() {
    return PhysicsPropertiesModuleJNI.PhysicsProperties_density_get(swigCPtr, this);
  }

  public void setElasticity(float value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_elasticity_set(swigCPtr, this, value);
  }

  public float getElasticity() {
    return PhysicsPropertiesModuleJNI.PhysicsProperties_elasticity_get(swigCPtr, this);
  }

  public void setInverse_mass(float value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_inverse_mass_set(swigCPtr, this, value);
  }

  public float getInverse_mass() {
    return PhysicsPropertiesModuleJNI.PhysicsProperties_inverse_mass_get(swigCPtr, this);
  }

  public void setResistance_factor(float value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_resistance_factor_set(swigCPtr, this, value);
  }

  public float getResistance_factor() {
    return PhysicsPropertiesModuleJNI.PhysicsProperties_resistance_factor_get(swigCPtr, this);
  }

  public void setResistance_counter(long value) {
    PhysicsPropertiesModuleJNI.PhysicsProperties_resistance_counter_set(swigCPtr, this, value);
  }

  public long getResistance_counter() {
    return PhysicsPropertiesModuleJNI.PhysicsProperties_resistance_counter_get(swigCPtr, this);
  }

  public final static float DefaultElasticity = PhysicsPropertiesModuleJNI.PhysicsProperties_DefaultElasticity_get();
  public final static long ResistanceInterval = PhysicsPropertiesModuleJNI.PhysicsProperties_ResistanceInterval_get();
}
