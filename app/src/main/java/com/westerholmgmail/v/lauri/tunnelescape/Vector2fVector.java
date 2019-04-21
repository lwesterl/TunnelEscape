/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.westerholmgmail.v.lauri.tunnelescape;

public class Vector2fVector {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Vector2fVector(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Vector2fVector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        WorldWrapperModuleJNI.delete_Vector2fVector(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Vector2fVector() {
    this(WorldWrapperModuleJNI.new_Vector2fVector__SWIG_0(), true);
  }

  public Vector2fVector(long n) {
    this(WorldWrapperModuleJNI.new_Vector2fVector__SWIG_1(n), true);
  }

  public long size() {
    return WorldWrapperModuleJNI.Vector2fVector_size(swigCPtr, this);
  }

  public long capacity() {
    return WorldWrapperModuleJNI.Vector2fVector_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    WorldWrapperModuleJNI.Vector2fVector_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return WorldWrapperModuleJNI.Vector2fVector_isEmpty(swigCPtr, this);
  }

  public void clear() {
    WorldWrapperModuleJNI.Vector2fVector_clear(swigCPtr, this);
  }

  public void add(Vector2f x) {
    WorldWrapperModuleJNI.Vector2fVector_add(swigCPtr, this, Vector2f.getCPtr(x), x);
  }

  public Vector2f get(int i) {
    return new Vector2f(WorldWrapperModuleJNI.Vector2fVector_get(swigCPtr, this, i), false);
  }

  public void set(int i, Vector2f val) {
    WorldWrapperModuleJNI.Vector2fVector_set(swigCPtr, this, i, Vector2f.getCPtr(val), val);
  }

}
