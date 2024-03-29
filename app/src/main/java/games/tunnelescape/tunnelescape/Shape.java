/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package games.tunnelescape.tunnelescape;

public class Shape {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Shape(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Shape obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        ShapeModuleJNI.delete_Shape(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Shape() {
    this(ShapeModuleJNI.new_Shape__SWIG_0(), true);
  }

  public Shape(float width, float height) {
    this(ShapeModuleJNI.new_Shape__SWIG_1(width, height), true);
  }

  public Shape(Shape shape) {
    this(ShapeModuleJNI.new_Shape__SWIG_2(Shape.getCPtr(shape), shape), true);
  }

  public Shape getPointer() {
    long cPtr = ShapeModuleJNI.Shape_getPointer(swigCPtr, this);
    return (cPtr == 0) ? null : new Shape(cPtr, false);
  }

  public Vector2f getCenter() {
    return new Vector2f(ShapeModuleJNI.Shape_getCenter(swigCPtr, this), false);
  }

  public Vector2fDeque getFrame() {
    return new Vector2fDeque(ShapeModuleJNI.Shape_getFrame(swigCPtr, this), false);
  }

  public Vector2f getMin() {
     return ShapeModuleJNI.Shape_getMin(swigCPtr, this);
}

  public Vector2f getMax() {
     return ShapeModuleJNI.Shape_getMax(swigCPtr, this);
}

  public float getArea() {
    return ShapeModuleJNI.Shape_getArea(swigCPtr, this);
  }

  public int getEdges() {
    return ShapeModuleJNI.Shape_getEdges(swigCPtr, this);
  }

  public Vector2fVector getAxis() {
    return new Vector2fVector(ShapeModuleJNI.Shape_getAxis(swigCPtr, this), false);
  }

  public float getWidth() {
    return ShapeModuleJNI.Shape_getWidth(swigCPtr, this);
  }

  public float getHeight() {
    return ShapeModuleJNI.Shape_getHeight(swigCPtr, this);
  }

}
