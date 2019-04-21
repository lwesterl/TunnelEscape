/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.westerholmgmail.v.lauri.tunnelescape;

public class WorldWrapperModuleJNI {
  public final static native double STD_DENSITY_get();
  public final static native void ObjectStatus_exists_set(long jarg1, ObjectStatus jarg1_, boolean jarg2);
  public final static native boolean ObjectStatus_exists_get(long jarg1, ObjectStatus jarg1_);
  public final static native void ObjectStatus_position_set(long jarg1, ObjectStatus jarg1_, long jarg2, Vector2f jarg2_);
  public final static native long ObjectStatus_position_get(long jarg1, ObjectStatus jarg1_);
  public final static native long new_ObjectStatus();
  public final static native void delete_ObjectStatus(long jarg1);
  public final static native long new_Pair__SWIG_0();
  public final static native long new_Pair__SWIG_1(long jarg1, long jarg2);
  public final static native long Pair_getFirst(long jarg1, Pair jarg1_);
  public final static native long Pair_getSecond(long jarg1, Pair jarg1_);
  public final static native void Pair_setFirst(long jarg1, Pair jarg1_, long jarg2);
  public final static native void Pair_setSecond(long jarg1, Pair jarg1_, long jarg2);
  public final static native void delete_Pair(long jarg1);
  public final static native void WorldWrapper_setPhysicsWorldUpdateInterval(float jarg1);
  public final static native long new_WorldWrapper();
  public final static native void delete_WorldWrapper(long jarg1);
  public final static native long WorldWrapper_update(long jarg1, WorldWrapper jarg1_);
  public final static native long WorldWrapper_addObject(long jarg1, WorldWrapper jarg1_, boolean jarg2, com.westerholmgmail.v.lauri.tunnelescape.Vector2f jarg3, float jarg4, float jarg5);
  public final static native void WorldWrapper_setObjectPhysicsProperties(long jarg1, WorldWrapper jarg1_, long jarg2, float jarg3, float jarg4);
  public final static native void WorldWrapper_setObjectCollisionMask(long jarg1, WorldWrapper jarg1_, long jarg2, long jarg3);
  public final static native void WorldWrapper_setObjectOriginTransform(long jarg1, WorldWrapper jarg1_, long jarg2, com.westerholmgmail.v.lauri.tunnelescape.Vector2f jarg3);
  public final static native void WorldWrapper_setObjectForce(long jarg1, WorldWrapper jarg1_, long jarg2, com.westerholmgmail.v.lauri.tunnelescape.Vector2f jarg3);
  public final static native void WorldWrapper_setObjectVelocity(long jarg1, WorldWrapper jarg1_, long jarg2, com.westerholmgmail.v.lauri.tunnelescape.Vector2f jarg3);
  public final static native void WorldWrapper_setObjectPosition(long jarg1, WorldWrapper jarg1_, long jarg2, com.westerholmgmail.v.lauri.tunnelescape.Vector2f jarg3);
  public final static native long WorldWrapper_fetchPosition(long jarg1, WorldWrapper jarg1_, long jarg2);
  public final static native long new_Vector2f__SWIG_0(float jarg1, float jarg2);
  public final static native long new_Vector2f__SWIG_1();
  public final static native long new_Vector2f__SWIG_2(long jarg1, Vector2f jarg1_);
  public final static native long Vector2f_getPointer(long jarg1, Vector2f jarg1_);
  public final static native float Vector2f_getX(long jarg1, Vector2f jarg1_);
  public final static native float Vector2f_getY(long jarg1, Vector2f jarg1_);
  public final static native void Vector2f_update(long jarg1, Vector2f jarg1_, float jarg2, float jarg3);
  public final static native void Vector2f_normalize(long jarg1, Vector2f jarg1_);
  public final static native float Vector2f_dotProduct(long jarg1, Vector2f jarg1_, long jarg2, Vector2f jarg2_);
  public final static native long Vector2f_rotate(long jarg1, Vector2f jarg1_, float jarg2);
  public final static native float Vector2f_getAngle(long jarg1, Vector2f jarg1_);
  public final static native float Vector2f_getLength(long jarg1, Vector2f jarg1_);
  public final static native float dotProduct__SWIG_1(long jarg1, Vector2f jarg1_, long jarg2, Vector2f jarg2_);
  public final static native void delete_Vector2f(long jarg1);
  public final static native long new_Vector2i__SWIG_0(int jarg1, int jarg2);
  public final static native long new_Vector2i__SWIG_1();
  public final static native long new_Vector2i__SWIG_2(long jarg1, Vector2i jarg1_);
  public final static native long Vector2i_getPointer(long jarg1, Vector2i jarg1_);
  public final static native int Vector2i_getX(long jarg1, Vector2i jarg1_);
  public final static native int Vector2i_getY(long jarg1, Vector2i jarg1_);
  public final static native void Vector2i_update(long jarg1, Vector2i jarg1_, int jarg2, int jarg3);
  public final static native void Vector2i_normalize(long jarg1, Vector2i jarg1_);
  public final static native float Vector2i_dotProduct(long jarg1, Vector2i jarg1_, long jarg2, Vector2i jarg2_);
  public final static native long Vector2i_rotate(long jarg1, Vector2i jarg1_, int jarg2);
  public final static native int Vector2i_getAngle(long jarg1, Vector2i jarg1_);
  public final static native int Vector2i_getLength(long jarg1, Vector2i jarg1_);
  public final static native int dotProduct__SWIG_2(long jarg1, Vector2i jarg1_, long jarg2, Vector2i jarg2_);
  public final static native void delete_Vector2i(long jarg1);
  public final static native boolean Vector2fDeque_empty(long jarg1, Vector2fDeque jarg1_);
  public final static native long new_Vector2fDeque__SWIG_0();
  public final static native long new_Vector2fDeque__SWIG_1(long jarg1, long jarg2, Vector2f jarg2_);
  public final static native long new_Vector2fDeque__SWIG_2(long jarg1);
  public final static native long new_Vector2fDeque__SWIG_3(long jarg1, Vector2fDeque jarg1_);
  public final static native void delete_Vector2fDeque(long jarg1);
  public final static native void Vector2fDeque_assign(long jarg1, Vector2fDeque jarg1_, long jarg2, long jarg3, Vector2f jarg3_);
  public final static native void Vector2fDeque_swap(long jarg1, Vector2fDeque jarg1_, long jarg2, Vector2fDeque jarg2_);
  public final static native long Vector2fDeque_size(long jarg1, Vector2fDeque jarg1_);
  public final static native long Vector2fDeque_max_size(long jarg1, Vector2fDeque jarg1_);
  public final static native void Vector2fDeque_resize__SWIG_0(long jarg1, Vector2fDeque jarg1_, long jarg2, long jarg3, Vector2f jarg3_);
  public final static native void Vector2fDeque_resize__SWIG_1(long jarg1, Vector2fDeque jarg1_, long jarg2);
  public final static native long Vector2fDeque_front(long jarg1, Vector2fDeque jarg1_);
  public final static native long Vector2fDeque_back(long jarg1, Vector2fDeque jarg1_);
  public final static native void Vector2fDeque_push_front(long jarg1, Vector2fDeque jarg1_, long jarg2, Vector2f jarg2_);
  public final static native void Vector2fDeque_push_back(long jarg1, Vector2fDeque jarg1_, long jarg2, Vector2f jarg2_);
  public final static native void Vector2fDeque_pop_front(long jarg1, Vector2fDeque jarg1_);
  public final static native void Vector2fDeque_pop_back(long jarg1, Vector2fDeque jarg1_);
  public final static native void Vector2fDeque_clear(long jarg1, Vector2fDeque jarg1_);
  public final static native long Vector2fDeque_getitem(long jarg1, Vector2fDeque jarg1_, int jarg2);
  public final static native void Vector2fDeque_setitem(long jarg1, Vector2fDeque jarg1_, int jarg2, long jarg3, Vector2f jarg3_);
  public final static native void Vector2fDeque_delitem(long jarg1, Vector2fDeque jarg1_, int jarg2);
  public final static native long Vector2fDeque_getslice(long jarg1, Vector2fDeque jarg1_, int jarg2, int jarg3);
  public final static native void Vector2fDeque_setslice(long jarg1, Vector2fDeque jarg1_, int jarg2, int jarg3, long jarg4, Vector2fDeque jarg4_);
  public final static native void Vector2fDeque_delslice(long jarg1, Vector2fDeque jarg1_, int jarg2, int jarg3);
  public final static native long new_Vector2fVector__SWIG_0();
  public final static native long new_Vector2fVector__SWIG_1(long jarg1);
  public final static native long Vector2fVector_size(long jarg1, Vector2fVector jarg1_);
  public final static native long Vector2fVector_capacity(long jarg1, Vector2fVector jarg1_);
  public final static native void Vector2fVector_reserve(long jarg1, Vector2fVector jarg1_, long jarg2);
  public final static native boolean Vector2fVector_isEmpty(long jarg1, Vector2fVector jarg1_);
  public final static native void Vector2fVector_clear(long jarg1, Vector2fVector jarg1_);
  public final static native void Vector2fVector_add(long jarg1, Vector2fVector jarg1_, long jarg2, Vector2f jarg2_);
  public final static native long Vector2fVector_get(long jarg1, Vector2fVector jarg1_, int jarg2);
  public final static native void Vector2fVector_set(long jarg1, Vector2fVector jarg1_, int jarg2, long jarg3, Vector2f jarg3_);
  public final static native void delete_Vector2fVector(long jarg1);
  public final static native boolean PairDeque_empty(long jarg1, PairDeque jarg1_);
  public final static native long new_PairDeque__SWIG_0();
  public final static native long new_PairDeque__SWIG_1(long jarg1, long jarg2, Pair jarg2_);
  public final static native long new_PairDeque__SWIG_2(long jarg1);
  public final static native long new_PairDeque__SWIG_3(long jarg1, PairDeque jarg1_);
  public final static native void delete_PairDeque(long jarg1);
  public final static native void PairDeque_assign(long jarg1, PairDeque jarg1_, long jarg2, long jarg3, Pair jarg3_);
  public final static native void PairDeque_swap(long jarg1, PairDeque jarg1_, long jarg2, PairDeque jarg2_);
  public final static native long PairDeque_size(long jarg1, PairDeque jarg1_);
  public final static native long PairDeque_max_size(long jarg1, PairDeque jarg1_);
  public final static native void PairDeque_resize__SWIG_0(long jarg1, PairDeque jarg1_, long jarg2, com.westerholmgmail.v.lauri.tunnelescape.Pair jarg3);
  public final static native void PairDeque_resize__SWIG_1(long jarg1, PairDeque jarg1_, long jarg2);
  public final static native long PairDeque_front(long jarg1, PairDeque jarg1_);
  public final static native long PairDeque_back(long jarg1, PairDeque jarg1_);
  public final static native void PairDeque_push_front(long jarg1, PairDeque jarg1_, long jarg2, Pair jarg2_);
  public final static native void PairDeque_push_back(long jarg1, PairDeque jarg1_, long jarg2, Pair jarg2_);
  public final static native void PairDeque_pop_front(long jarg1, PairDeque jarg1_);
  public final static native void PairDeque_pop_back(long jarg1, PairDeque jarg1_);
  public final static native void PairDeque_clear(long jarg1, PairDeque jarg1_);
  public final static native long PairDeque_getitem(long jarg1, PairDeque jarg1_, int jarg2);
  public final static native void PairDeque_setitem(long jarg1, PairDeque jarg1_, int jarg2, long jarg3, Pair jarg3_);
  public final static native void PairDeque_delitem(long jarg1, PairDeque jarg1_, int jarg2);
  public final static native long PairDeque_getslice(long jarg1, PairDeque jarg1_, int jarg2, int jarg3);
  public final static native void PairDeque_setslice(long jarg1, PairDeque jarg1_, int jarg2, int jarg3, long jarg4, PairDeque jarg4_);
  public final static native void PairDeque_delslice(long jarg1, PairDeque jarg1_, int jarg2, int jarg3);
}