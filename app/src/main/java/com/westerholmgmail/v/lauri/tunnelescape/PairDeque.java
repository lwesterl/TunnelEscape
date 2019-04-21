/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.westerholmgmail.v.lauri.tunnelescape;

public class PairDeque {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected PairDeque(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PairDeque obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        WorldWrapperModuleJNI.delete_PairDeque(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public boolean empty() {
    return WorldWrapperModuleJNI.PairDeque_empty(swigCPtr, this);
  }

  public PairDeque() {
    this(WorldWrapperModuleJNI.new_PairDeque__SWIG_0(), true);
  }

  public PairDeque(long size, Pair value) {
    this(WorldWrapperModuleJNI.new_PairDeque__SWIG_1(size, Pair.getCPtr(value), value), true);
  }

  public PairDeque(long size) {
    this(WorldWrapperModuleJNI.new_PairDeque__SWIG_2(size), true);
  }

  public PairDeque(PairDeque arg0) {
    this(WorldWrapperModuleJNI.new_PairDeque__SWIG_3(PairDeque.getCPtr(arg0), arg0), true);
  }

  public void assign(long n, Pair value) {
    WorldWrapperModuleJNI.PairDeque_assign(swigCPtr, this, n, Pair.getCPtr(value), value);
  }

  public void swap(PairDeque x) {
    WorldWrapperModuleJNI.PairDeque_swap(swigCPtr, this, PairDeque.getCPtr(x), x);
  }

  public long size() {
    return WorldWrapperModuleJNI.PairDeque_size(swigCPtr, this);
  }

  public long max_size() {
    return WorldWrapperModuleJNI.PairDeque_max_size(swigCPtr, this);
  }

  public void resize(long n, Pair c) {
    WorldWrapperModuleJNI.PairDeque_resize__SWIG_0(swigCPtr, this, n, Pair.getCPtr(c), c);
  }

  public void resize(long n) {
    WorldWrapperModuleJNI.PairDeque_resize__SWIG_1(swigCPtr, this, n);
  }

  public Pair front() {
    return new Pair(WorldWrapperModuleJNI.PairDeque_front(swigCPtr, this), false);
  }

  public Pair back() {
    return new Pair(WorldWrapperModuleJNI.PairDeque_back(swigCPtr, this), false);
  }

  public void push_front(Pair x) {
    WorldWrapperModuleJNI.PairDeque_push_front(swigCPtr, this, Pair.getCPtr(x), x);
  }

  public void push_back(Pair x) {
    WorldWrapperModuleJNI.PairDeque_push_back(swigCPtr, this, Pair.getCPtr(x), x);
  }

  public void pop_front() {
    WorldWrapperModuleJNI.PairDeque_pop_front(swigCPtr, this);
  }

  public void pop_back() {
    WorldWrapperModuleJNI.PairDeque_pop_back(swigCPtr, this);
  }

  public void clear() {
    WorldWrapperModuleJNI.PairDeque_clear(swigCPtr, this);
  }

  public Pair getitem(int i) {
    return new Pair(WorldWrapperModuleJNI.PairDeque_getitem(swigCPtr, this, i), false);
  }

  public void setitem(int i, Pair x) {
    WorldWrapperModuleJNI.PairDeque_setitem(swigCPtr, this, i, Pair.getCPtr(x), x);
  }

  public void delitem(int i) {
    WorldWrapperModuleJNI.PairDeque_delitem(swigCPtr, this, i);
  }

  public PairDeque getslice(int i, int j) {
    return new PairDeque(WorldWrapperModuleJNI.PairDeque_getslice(swigCPtr, this, i, j), true);
  }

  public void setslice(int i, int j, PairDeque v) {
    WorldWrapperModuleJNI.PairDeque_setslice(swigCPtr, this, i, j, PairDeque.getCPtr(v), v);
  }

  public void delslice(int i, int j) {
    WorldWrapperModuleJNI.PairDeque_delslice(swigCPtr, this, i, j);
  }

}
