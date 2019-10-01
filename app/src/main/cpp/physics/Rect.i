%module Rect

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
%typemap(jstype) Vector2i "Vector2i";
%typemap(jtype) Vector2i "Vector2i";
%typemap(jni) Vector2i "jobject";

%typemap(javaout) Vector2i {
     return $jnicall;
}
%typemap(out) Vector2i {
    jclass jVectClass = jenv->FindClass("games/tunnelescape/tunnelescape/Vector2i");
    jmethodID jVectConstructor = jenv->GetMethodID(jVectClass, "<init>", "(II)V");
    jobject jVect = jenv->NewObject(jVectClass, jVectConstructor, $1.getX(), $1.getY());
    $result = jVect;
}


%{
#include "Rect.hpp"
%}

%include "Vector2.hpp"
%include "Rect.hpp"

%template (Vector2f) Vector2<float>;
%template (Vector2i) Vector2<int>;
%template (Rectf) Rect<float>;
%template (Recti) Rect<int>;
