/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */


#ifndef SWIGJAVA
#define SWIGJAVA
#endif



#ifdef __cplusplus
/* SwigValueWrapper is described in swig.swg */
template<typename T> class SwigValueWrapper {
  struct SwigMovePointer {
    T *ptr;
    SwigMovePointer(T *p) : ptr(p) { }
    ~SwigMovePointer() { delete ptr; }
    SwigMovePointer& operator=(SwigMovePointer& rhs) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = rhs.ptr; rhs.ptr = 0; return *this; }
  } pointer;
  SwigValueWrapper& operator=(const SwigValueWrapper<T>& rhs);
  SwigValueWrapper(const SwigValueWrapper<T>& rhs);
public:
  SwigValueWrapper() : pointer(0) { }
  SwigValueWrapper& operator=(const T& t) { SwigMovePointer tmp(new T(t)); pointer = tmp; return *this; }
  operator T&() const { return *pointer.ptr; }
  T *operator&() { return pointer.ptr; }
};

template <typename T> T SwigValueInit() {
  return T();
}
#endif

/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if defined(__GNUC__)
#  if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#    ifndef GCC_HASCLASSVISIBILITY
#      define GCC_HASCLASSVISIBILITY
#    endif
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif

/* Deal with Apple's deprecated 'AssertMacros.h' from Carbon-framework */
#if defined(__APPLE__) && !defined(__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES)
# define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
#endif

/* Intel's compiler complains if a variable which was never initialised is
 * cast to void, which is a common idiom which we use to indicate that we
 * are aware a variable isn't used.  So we just silence that warning.
 * See: https://github.com/swig/swig/issues/192 for more discussion.
 */
#ifdef __INTEL_COMPILER
# pragma warning disable 592
#endif


/* Fix for jlong on some versions of gcc on Windows */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
  typedef long long __int64;
#endif

/* Fix for jlong on 64-bit x86 Solaris */
#if defined(__x86_64)
# ifdef _LP64
#   undef _LP64
# endif
#endif

#include <jni.h>
#include <stdlib.h>
#include <string.h>


/* Support for throwing Java exceptions */
typedef enum {
  SWIG_JavaOutOfMemoryError = 1, 
  SWIG_JavaIOException, 
  SWIG_JavaRuntimeException, 
  SWIG_JavaIndexOutOfBoundsException,
  SWIG_JavaArithmeticException,
  SWIG_JavaIllegalArgumentException,
  SWIG_JavaNullPointerException,
  SWIG_JavaDirectorPureVirtual,
  SWIG_JavaUnknownError
} SWIG_JavaExceptionCodes;

typedef struct {
  SWIG_JavaExceptionCodes code;
  const char *java_exception;
} SWIG_JavaExceptions_t;


static void SWIGUNUSED SWIG_JavaThrowException(JNIEnv *jenv, SWIG_JavaExceptionCodes code, const char *msg) {
  jclass excep;
  static const SWIG_JavaExceptions_t java_exceptions[] = {
    { SWIG_JavaOutOfMemoryError, "java/lang/OutOfMemoryError" },
    { SWIG_JavaIOException, "java/io/IOException" },
    { SWIG_JavaRuntimeException, "java/lang/RuntimeException" },
    { SWIG_JavaIndexOutOfBoundsException, "java/lang/IndexOutOfBoundsException" },
    { SWIG_JavaArithmeticException, "java/lang/ArithmeticException" },
    { SWIG_JavaIllegalArgumentException, "java/lang/IllegalArgumentException" },
    { SWIG_JavaNullPointerException, "java/lang/NullPointerException" },
    { SWIG_JavaDirectorPureVirtual, "java/lang/RuntimeException" },
    { SWIG_JavaUnknownError,  "java/lang/UnknownError" },
    { (SWIG_JavaExceptionCodes)0,  "java/lang/UnknownError" }
  };
  const SWIG_JavaExceptions_t *except_ptr = java_exceptions;

  while (except_ptr->code != code && except_ptr->code)
    except_ptr++;

  jenv->ExceptionClear();
  excep = jenv->FindClass(except_ptr->java_exception);
  if (excep)
    jenv->ThrowNew(excep, msg);
}


/* Contract support */

#define SWIG_contract_assert(nullreturn, expr, msg) if (!(expr)) {SWIG_JavaThrowException(jenv, SWIG_JavaIllegalArgumentException, msg); return nullreturn; } else


#include "PhysicsProperties.hpp"


#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1GravityX_1set(JNIEnv *jenv, jclass jcls, jfloat jarg1) {
  float arg1 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (float)jarg1; 
  PhysicsProperties::GravityX = arg1;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1GravityX_1get(JNIEnv *jenv, jclass jcls) {
  jfloat jresult = 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  result = (float)PhysicsProperties::GravityX;
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1GravityY_1set(JNIEnv *jenv, jclass jcls, jfloat jarg1) {
  float arg1 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (float)jarg1; 
  PhysicsProperties::GravityY = arg1;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1GravityY_1get(JNIEnv *jenv, jclass jcls) {
  jfloat jresult = 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  result = (float)PhysicsProperties::GravityY;
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1SizeScale_1set(JNIEnv *jenv, jclass jcls, jfloat jarg1) {
  float arg1 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (float)jarg1; 
  PhysicsProperties::SizeScale = arg1;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1SizeScale_1get(JNIEnv *jenv, jclass jcls) {
  jfloat jresult = 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  result = (float)PhysicsProperties::SizeScale;
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1DefaultElasticity_1get(JNIEnv *jenv, jclass jcls) {
  jfloat jresult = 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  result = (float)PhysicsProperties::DefaultElasticity;
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1ResistanceInterval_1get(JNIEnv *jenv, jclass jcls) {
  jlong jresult = 0 ;
  unsigned int result;
  
  (void)jenv;
  (void)jcls;
  result = (unsigned int)PhysicsProperties::ResistanceInterval;
  jresult = (jlong)result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_new_1PhysicsProperties_1_1SWIG_10(JNIEnv *jenv, jclass jcls) {
  jlong jresult = 0 ;
  PhysicsProperties *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  result = (PhysicsProperties *)new PhysicsProperties();
  *(PhysicsProperties **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_new_1PhysicsProperties_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jfloat jarg1, jfloat jarg2, jboolean jarg3) {
  jlong jresult = 0 ;
  float arg1 ;
  float arg2 ;
  bool arg3 ;
  PhysicsProperties *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (float)jarg1; 
  arg2 = (float)jarg2; 
  arg3 = jarg3 ? true : false; 
  result = (PhysicsProperties *)new PhysicsProperties(arg1,arg2,arg3);
  *(PhysicsProperties **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_new_1PhysicsProperties_1_1SWIG_12(JNIEnv *jenv, jclass jcls, jfloat jarg1, jfloat jarg2) {
  jlong jresult = 0 ;
  float arg1 ;
  float arg2 ;
  PhysicsProperties *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (float)jarg1; 
  arg2 = (float)jarg2; 
  result = (PhysicsProperties *)new PhysicsProperties(arg1,arg2);
  *(PhysicsProperties **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1getPointer(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  PhysicsProperties *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (PhysicsProperties *)(arg1)->getPointer();
  *(PhysicsProperties **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1setPosition(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f arg2 ;
  Vector2f *argp2 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  argp2 = *(Vector2f **)&jarg2; 
  if (!argp2) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null Vector2f");
    return ;
  }
  arg2 = *argp2; 
  (arg1)->setPosition(arg2);
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1movePosition(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f arg2 ;
  Vector2f *argp2 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  argp2 = *(Vector2f **)&jarg2; 
  if (!argp2) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Attempt to dereference null Vector2f");
    return ;
  }
  arg2 = *argp2; 
  (arg1)->movePosition(arg2);
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1applyResistance(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jfloat jarg2) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float arg2 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = (float)jarg2; 
  (arg1)->applyResistance(arg2);
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1setDensity(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jfloat jarg2, jfloat jarg3, jboolean jarg4) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float arg2 ;
  float arg3 ;
  bool arg4 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = (float)jarg2; 
  arg3 = (float)jarg3; 
  arg4 = jarg4 ? true : false; 
  (arg1)->setDensity(arg2,arg3,arg4);
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1velocity_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f *arg2 = (Vector2f *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = *(Vector2f **)&jarg2; 
  if (arg1) (arg1)->velocity = *arg2;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1velocity_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (Vector2f *)& ((arg1)->velocity);
  *(Vector2f **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1collision_1velocity_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f *arg2 = (Vector2f *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = *(Vector2f **)&jarg2; 
  if (arg1) (arg1)->collision_velocity = *arg2;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1collision_1velocity_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (Vector2f *)& ((arg1)->collision_velocity);
  *(Vector2f **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1acceloration_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f *arg2 = (Vector2f *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = *(Vector2f **)&jarg2; 
  if (arg1) (arg1)->acceloration = *arg2;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1acceloration_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (Vector2f *)& ((arg1)->acceloration);
  *(Vector2f **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1position_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f *arg2 = (Vector2f *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = *(Vector2f **)&jarg2; 
  if (arg1) (arg1)->position = *arg2;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1position_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (Vector2f *)& ((arg1)->position);
  *(Vector2f **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1origin_1transform_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f *arg2 = (Vector2f *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = *(Vector2f **)&jarg2; 
  if (arg1) (arg1)->origin_transform = *arg2;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1origin_1transform_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  Vector2f *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (Vector2f *)& ((arg1)->origin_transform);
  *(Vector2f **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1angle_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jfloat jarg2) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float arg2 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = (float)jarg2; 
  if (arg1) (arg1)->angle = arg2;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1angle_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jfloat jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (float) ((arg1)->angle);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1density_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jfloat jarg2) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float arg2 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = (float)jarg2; 
  if (arg1) (arg1)->density = arg2;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1density_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jfloat jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (float) ((arg1)->density);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1elasticity_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jfloat jarg2) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float arg2 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = (float)jarg2; 
  if (arg1) (arg1)->elasticity = arg2;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1elasticity_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jfloat jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (float) ((arg1)->elasticity);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1inverse_1mass_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jfloat jarg2) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float arg2 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = (float)jarg2; 
  if (arg1) (arg1)->inverse_mass = arg2;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1inverse_1mass_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jfloat jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (float) ((arg1)->inverse_mass);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1resistance_1factor_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jfloat jarg2) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float arg2 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = (float)jarg2; 
  if (arg1) (arg1)->resistance_factor = arg2;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1resistance_1factor_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jfloat jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (float) ((arg1)->resistance_factor);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1resistance_1counter_1set(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  unsigned int arg2 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  arg2 = (unsigned int)jarg2; 
  if (arg1) (arg1)->resistance_counter = arg2;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_PhysicsProperties_1resistance_1counter_1get(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  unsigned int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(PhysicsProperties **)&jarg1; 
  result = (unsigned int) ((arg1)->resistance_counter);
  jresult = (jlong)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_delete_1PhysicsProperties(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  PhysicsProperties *arg1 = (PhysicsProperties *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(PhysicsProperties **)&jarg1; 
  delete arg1;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_new_1Vector2f_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jfloat jarg1, jfloat jarg2) {
  jlong jresult = 0 ;
  float arg1 ;
  float arg2 ;
  Vector2< float > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (float)jarg1; 
  arg2 = (float)jarg2; 
  result = (Vector2< float > *)new Vector2< float >(arg1,arg2);
  *(Vector2< float > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_new_1Vector2f_1_1SWIG_11(JNIEnv *jenv, jclass jcls) {
  jlong jresult = 0 ;
  Vector2< float > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  result = (Vector2< float > *)new Vector2< float >();
  *(Vector2< float > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_new_1Vector2f_1_1SWIG_12(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  Vector2< float > *arg1 = 0 ;
  Vector2< float > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< float > **)&jarg1;
  if (!arg1) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Vector2< float > const & reference is null");
    return 0;
  } 
  result = (Vector2< float > *)new Vector2< float >((Vector2< float > const &)*arg1);
  *(Vector2< float > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2f_1getPointer(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  Vector2< float > *arg1 = (Vector2< float > *) 0 ;
  Vector2< float > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< float > **)&jarg1; 
  result = (Vector2< float > *)(arg1)->getPointer();
  *(Vector2< float > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2f_1getX(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jfloat jresult = 0 ;
  Vector2< float > *arg1 = (Vector2< float > *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< float > **)&jarg1; 
  result = (float)((Vector2< float > const *)arg1)->getX();
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2f_1getY(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jfloat jresult = 0 ;
  Vector2< float > *arg1 = (Vector2< float > *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< float > **)&jarg1; 
  result = (float)((Vector2< float > const *)arg1)->getY();
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2f_1update(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jfloat jarg2, jfloat jarg3) {
  Vector2< float > *arg1 = (Vector2< float > *) 0 ;
  float arg2 ;
  float arg3 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< float > **)&jarg1; 
  arg2 = (float)jarg2; 
  arg3 = (float)jarg3; 
  (arg1)->update(arg2,arg3);
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2f_1normalize(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  Vector2< float > *arg1 = (Vector2< float > *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< float > **)&jarg1; 
  (arg1)->normalize();
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2f_1dotProduct(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  jfloat jresult = 0 ;
  Vector2< float > *arg1 = (Vector2< float > *) 0 ;
  Vector2< float > *arg2 = 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(Vector2< float > **)&jarg1; 
  arg2 = *(Vector2< float > **)&jarg2;
  if (!arg2) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Vector2< float > const & reference is null");
    return 0;
  } 
  result = (float)((Vector2< float > const *)arg1)->dotProduct((Vector2< float > const &)*arg2);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2f_1rotate(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jfloat jarg2) {
  jlong jresult = 0 ;
  Vector2< float > *arg1 = (Vector2< float > *) 0 ;
  float arg2 ;
  Vector2< float > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< float > **)&jarg1; 
  arg2 = (float)jarg2; 
  result = (Vector2< float > *) &(arg1)->rotate(arg2);
  *(Vector2< float > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2f_1getAngle(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jfloat jresult = 0 ;
  Vector2< float > *arg1 = (Vector2< float > *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< float > **)&jarg1; 
  result = (float)((Vector2< float > const *)arg1)->getAngle();
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2f_1getLength(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jfloat jresult = 0 ;
  Vector2< float > *arg1 = (Vector2< float > *) 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< float > **)&jarg1; 
  result = (float)((Vector2< float > const *)arg1)->getLength();
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_dotProduct_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  jfloat jresult = 0 ;
  Vector2< float > *arg1 = 0 ;
  Vector2< float > *arg2 = 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(Vector2< float > **)&jarg1;
  if (!arg1) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Vector2< float > const & reference is null");
    return 0;
  } 
  arg2 = *(Vector2< float > **)&jarg2;
  if (!arg2) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Vector2< float > const & reference is null");
    return 0;
  } 
  result = (float)dotProduct((Vector2< float > const &)*arg1,(Vector2< float > const &)*arg2);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_delete_1Vector2f(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  Vector2< float > *arg1 = (Vector2< float > *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Vector2< float > **)&jarg1; 
  delete arg1;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_new_1Vector2i_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jint jarg1, jint jarg2) {
  jlong jresult = 0 ;
  int arg1 ;
  int arg2 ;
  Vector2< int > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = (int)jarg1; 
  arg2 = (int)jarg2; 
  result = (Vector2< int > *)new Vector2< int >(arg1,arg2);
  *(Vector2< int > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_new_1Vector2i_1_1SWIG_11(JNIEnv *jenv, jclass jcls) {
  jlong jresult = 0 ;
  Vector2< int > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  result = (Vector2< int > *)new Vector2< int >();
  *(Vector2< int > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_new_1Vector2i_1_1SWIG_12(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  Vector2< int > *arg1 = 0 ;
  Vector2< int > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< int > **)&jarg1;
  if (!arg1) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Vector2< int > const & reference is null");
    return 0;
  } 
  result = (Vector2< int > *)new Vector2< int >((Vector2< int > const &)*arg1);
  *(Vector2< int > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2i_1getPointer(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jlong jresult = 0 ;
  Vector2< int > *arg1 = (Vector2< int > *) 0 ;
  Vector2< int > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< int > **)&jarg1; 
  result = (Vector2< int > *)(arg1)->getPointer();
  *(Vector2< int > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2i_1getX(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jint jresult = 0 ;
  Vector2< int > *arg1 = (Vector2< int > *) 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< int > **)&jarg1; 
  result = (int)((Vector2< int > const *)arg1)->getX();
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2i_1getY(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jint jresult = 0 ;
  Vector2< int > *arg1 = (Vector2< int > *) 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< int > **)&jarg1; 
  result = (int)((Vector2< int > const *)arg1)->getY();
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2i_1update(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3) {
  Vector2< int > *arg1 = (Vector2< int > *) 0 ;
  int arg2 ;
  int arg3 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< int > **)&jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (int)jarg3; 
  (arg1)->update(arg2,arg3);
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2i_1normalize(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  Vector2< int > *arg1 = (Vector2< int > *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< int > **)&jarg1; 
  (arg1)->normalize();
}


SWIGEXPORT jfloat JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2i_1dotProduct(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  jfloat jresult = 0 ;
  Vector2< int > *arg1 = (Vector2< int > *) 0 ;
  Vector2< int > *arg2 = 0 ;
  float result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(Vector2< int > **)&jarg1; 
  arg2 = *(Vector2< int > **)&jarg2;
  if (!arg2) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Vector2< int > const & reference is null");
    return 0;
  } 
  result = (float)((Vector2< int > const *)arg1)->dotProduct((Vector2< int > const &)*arg2);
  jresult = (jfloat)result; 
  return jresult;
}


SWIGEXPORT jlong JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2i_1rotate(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2) {
  jlong jresult = 0 ;
  Vector2< int > *arg1 = (Vector2< int > *) 0 ;
  int arg2 ;
  Vector2< int > *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< int > **)&jarg1; 
  arg2 = (int)jarg2; 
  result = (Vector2< int > *) &(arg1)->rotate(arg2);
  *(Vector2< int > **)&jresult = result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2i_1getAngle(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jint jresult = 0 ;
  Vector2< int > *arg1 = (Vector2< int > *) 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< int > **)&jarg1; 
  result = (int)((Vector2< int > const *)arg1)->getAngle();
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_Vector2i_1getLength(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  jint jresult = 0 ;
  Vector2< int > *arg1 = (Vector2< int > *) 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(Vector2< int > **)&jarg1; 
  result = (int)((Vector2< int > const *)arg1)->getLength();
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_dotProduct_1_1SWIG_12(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_) {
  jint jresult = 0 ;
  Vector2< int > *arg1 = 0 ;
  Vector2< int > *arg2 = 0 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  arg1 = *(Vector2< int > **)&jarg1;
  if (!arg1) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Vector2< int > const & reference is null");
    return 0;
  } 
  arg2 = *(Vector2< int > **)&jarg2;
  if (!arg2) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "Vector2< int > const & reference is null");
    return 0;
  } 
  result = (int)dotProduct((Vector2< int > const &)*arg1,(Vector2< int > const &)*arg2);
  jresult = (jint)result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_westerholmgmail_v_lauri_tunnelescape_PhysicsPropertiesModuleJNI_delete_1Vector2i(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  Vector2< int > *arg1 = (Vector2< int > *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(Vector2< int > **)&jarg1; 
  delete arg1;
}


#ifdef __cplusplus
}
#endif

