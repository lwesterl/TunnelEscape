/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.westerholmgmail.v.lauri.tunnelescape;

public class Rectf {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Rectf(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Rectf obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        RectJNI.delete_Rectf(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Rectf() {
    this(RectJNI.new_Rectf__SWIG_0(), true);
  }

  public Rectf(Vector2f upper_left, float width, float height) {
    this(RectJNI.new_Rectf__SWIG_1(Vector2f.getCPtr(upper_left), upper_left, width, height), true);
  }

  public Rectf(Rectf rect) {
    this(RectJNI.new_Rectf__SWIG_2(Rectf.getCPtr(rect), rect), true);
  }

  public Rectf getPointer() {
    long cPtr = RectJNI.Rectf_getPointer(swigCPtr, this);
    return (cPtr == 0) ? null : new Rectf(cPtr, false);
  }

  public void setPosition(Vector2f position) {
    RectJNI.Rectf_setPosition(swigCPtr, this, Vector2f.getCPtr(position), position);
  }

  public Vector2f getPosition() {
    return new Vector2f(RectJNI.Rectf_getPosition(swigCPtr, this), true);
  }

  public void setWidth(float width) {
    RectJNI.Rectf_setWidth(swigCPtr, this, width);
  }

  public float getWidth() {
    return RectJNI.Rectf_getWidth(swigCPtr, this);
  }

  public void setHeight(float height) {
    RectJNI.Rectf_setHeight(swigCPtr, this, height);
  }

  public float getHeight() {
    return RectJNI.Rectf_getHeight(swigCPtr, this);
  }

  public void setSize(Vector2f size) {
    RectJNI.Rectf_setSize(swigCPtr, this, Vector2f.getCPtr(size), size);
  }

  public Vector2f getSize() {
    return new Vector2f(RectJNI.Rectf_getSize(swigCPtr, this), true);
  }

  public boolean contains(float x, float y) {
    return RectJNI.Rectf_contains__SWIG_0(swigCPtr, this, x, y);
  }

  public boolean contains(Vector2f point) {
    return RectJNI.Rectf_contains__SWIG_1(swigCPtr, this, Vector2f.getCPtr(point), point);
  }

}
