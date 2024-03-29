/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package games.tunnelescape.tunnelescape;

public class ObjectStatus {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected ObjectStatus(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ObjectStatus obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        WorldWrapperModuleJNI.delete_ObjectStatus(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setExists(boolean value) {
    WorldWrapperModuleJNI.ObjectStatus_exists_set(swigCPtr, this, value);
  }

  public boolean getExists() {
    return WorldWrapperModuleJNI.ObjectStatus_exists_get(swigCPtr, this);
  }

  public void setPosition(Vector2f value) {
    WorldWrapperModuleJNI.ObjectStatus_position_set(swigCPtr, this, Vector2f.getCPtr(value), value);
  }

  public Vector2f getPosition() {
    long cPtr = WorldWrapperModuleJNI.ObjectStatus_position_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Vector2f(cPtr, false);
  }

  public ObjectStatus() {
    this(WorldWrapperModuleJNI.new_ObjectStatus(), true);
  }

}
