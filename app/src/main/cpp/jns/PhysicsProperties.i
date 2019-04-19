%module PhysicsPropertiesModule

%typemap(jstype) Vector2f "com.westerholmgmail.v.lauri.tunnelescape.Vector2f";
%typemap(jtype) Vector2f "com.westerholmgmail.v.lauri.tunnelescape.Vector2f";
%typemap(jni) Vector2f "jobject";

%typemap(javaout) Vector2f {
     return $jnicall;
}
%typemap(out) Vector2f {
    jclass jVectClass = jenv->FindClass("com/westerholmgmail/v/lauri/tunnelescape/Vector2f");
    jmethodID jVectConstructor = jenv->GetMethodID(jVectClass, "<init>", "(FF)V");
    jobject jVect = jenv->NewObject(jVectClass, jVectConstructor, $1.getX(), $1.getY());
    $result = jVect;
}



%{
#include "PhysicsProperties.hpp"
%}

%include "PhysicsProperties.hpp"
%include "Vector2.hpp"

%template (Vector2f) Vector2<float>;
%template (Vector2i) Vector2<int>;
