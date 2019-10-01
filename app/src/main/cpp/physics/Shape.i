%module ShapeModule

%typemap(jstype) Vector2f "Vector2f";
%typemap(jtype) Vector2f "Vector2f";
%typemap(jni) Vector2f "jobject";

%typemap(javaout) Vector2f {
     return $jnicall;
}
%typemap(out) Vector2f {
    jclass jVectClass = jenv->FindClass("games/tunnelescape/tunnelescape/Vector2f");
    jmethodID jVectConstructor = jenv->GetMethodID(jVectClass, "<init>", "(FF)V");
    jobject jVect = jenv->NewObject(jVectClass, jVectConstructor, $1.getX(), $1.getY());
    $result = jVect;
}

%{
#include "Shape.hpp"
%}


%include "Vector2.hpp"
%include "Shape.hpp"
%include "std_vector.i"
%include "std_deque.i"

%template (Vector2f) Vector2<float>;
%template (Vector2fDeque) std::deque<Vector2f>;
%template (Vector2fVector) std::vector<Vector2f>;
