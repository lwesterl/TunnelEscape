/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.westerholmgmail.v.lauri.tunnelescape;

public class Vector2fDeque {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Vector2fDeque(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Vector2fDeque obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        ShapeModuleJNI.delete_Vector2fDeque(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public boolean empty() {
    return ShapeModuleJNI.Vector2fDeque_empty(swigCPtr, this);
  }

  public Vector2fDeque() {
    this(ShapeModuleJNI.new_Vector2fDeque__SWIG_0(), true);
  }

  public Vector2fDeque(long size, Vector2f value) {
    this(ShapeModuleJNI.new_Vector2fDeque__SWIG_1(size, Vector2f.getCPtr(value), value), true);
  }

  public Vector2fDeque(long size) {
    this(ShapeModuleJNI.new_Vector2fDeque__SWIG_2(size), true);
  }

  public Vector2fDeque(Vector2fDeque arg0) {
    this(ShapeModuleJNI.new_Vector2fDeque__SWIG_3(Vector2fDeque.getCPtr(arg0), arg0), true);
  }

  public void assign(long n, Vector2f value) {
    ShapeModuleJNI.Vector2fDeque_assign(swigCPtr, this, n, Vector2f.getCPtr(value), value);
  }

  public void swap(Vector2fDeque x) {
    ShapeModuleJNI.Vector2fDeque_swap(swigCPtr, this, Vector2fDeque.getCPtr(x), x);
  }

  public long size() {
    return ShapeModuleJNI.Vector2fDeque_size(swigCPtr, this);
  }

  public long max_size() {
    return ShapeModuleJNI.Vector2fDeque_max_size(swigCPtr, this);
  }

  public void resize(long n, Vector2f c) {
    ShapeModuleJNI.Vector2fDeque_resize__SWIG_0(swigCPtr, this, n, Vector2f.getCPtr(c), c);
  }

  public void resize(long n) {
    ShapeModuleJNI.Vector2fDeque_resize__SWIG_1(swigCPtr, this, n);
  }

  public Vector2f front() {
    return new Vector2f(ShapeModuleJNI.Vector2fDeque_front(swigCPtr, this), false);
  }

  public Vector2f back() {
    return new Vector2f(ShapeModuleJNI.Vector2fDeque_back(swigCPtr, this), false);
  }

  public void push_front(Vector2f x) {
    ShapeModuleJNI.Vector2fDeque_push_front(swigCPtr, this, Vector2f.getCPtr(x), x);
  }

  public void push_back(Vector2f x) {
    ShapeModuleJNI.Vector2fDeque_push_back(swigCPtr, this, Vector2f.getCPtr(x), x);
  }

  public void pop_front() {
    ShapeModuleJNI.Vector2fDeque_pop_front(swigCPtr, this);
  }

  public void pop_back() {
    ShapeModuleJNI.Vector2fDeque_pop_back(swigCPtr, this);
  }

  public void clear() {
    ShapeModuleJNI.Vector2fDeque_clear(swigCPtr, this);
  }

  public Vector2f getitem(int i) {
    return new Vector2f(ShapeModuleJNI.Vector2fDeque_getitem(swigCPtr, this, i), false);
  }

  public void setitem(int i, Vector2f x) {
    ShapeModuleJNI.Vector2fDeque_setitem(swigCPtr, this, i, Vector2f.getCPtr(x), x);
  }

  public void delitem(int i) {
    ShapeModuleJNI.Vector2fDeque_delitem(swigCPtr, this, i);
  }

  public Vector2fDeque getslice(int i, int j) {
    return new Vector2fDeque(ShapeModuleJNI.Vector2fDeque_getslice(swigCPtr, this, i, j), true);
  }

  public void setslice(int i, int j, Vector2fDeque v) {
    ShapeModuleJNI.Vector2fDeque_setslice(swigCPtr, this, i, j, Vector2fDeque.getCPtr(v), v);
  }

  public void delslice(int i, int j) {
    ShapeModuleJNI.Vector2fDeque_delslice(swigCPtr, this, i, j);
  }

}