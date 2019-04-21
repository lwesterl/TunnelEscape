%module WorldWrapperModule

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

%typemap(jstype) Pair "com.westerholmgmail.v.lauri.tunnelescape.Pair";
%typemap(jtype) Pair "com.westerholmgmail.v.lauri.tunnelescape.Pair";
%typemap(jni) Pair "jobject";

%typemap(javaout) Pair {
     return $jnicall;
}
%typemap(out) Pair {
    jclass jPairClass = jenv->FindClass("com/westerholmgmail/v/lauri/tunnelescape/Pair");
    jmethodID jPairConstructor = jenv->GetMethodID(jPairClass, "<init>", "(LL)V");
    jobject jPair = jenv->NewObject(jPairClass, jPairConstructor, $1.getFirst(), $1.getSecond());
    $result = jPair;
}

%{
#include "WorldWrapper.hpp"
%}

%include "WorldWrapper.hpp"
%include "../physics/Vector2.hpp"
%include "std_vector.i"
%include "std_deque.i"
%include "std_map.i"

%template (Vector2f) Vector2<float>;
%template (Vector2i) Vector2<int>;

%template (Vector2fDeque) std::deque<Vector2f>;
%template (Vector2fVector) std::vector<Vector2f>;
%template (PairDeque) std::deque<Pair>;
