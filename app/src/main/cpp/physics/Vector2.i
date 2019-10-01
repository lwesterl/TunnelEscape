%module Vector2

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
#include "Vector2.hpp"
%}
%include "Vector2.hpp"

%template (Vector2f) Vector2<float>;
%template (Vector2i) Vector2<int>;


%rename(equals) Vector2<T>::operator==(const Vector2<T>& vect1) const;
%rename(greaterThan) Vector2<T>::operator>(const Vector2<T>& vect) const;
%rename(smallerThan) Vector2<T>::operator<(const Vector2<T>& vect) const;
%rename(vectorMultiplication) Vector2<T>::operator*(const Vector2<T>& vect1) const;
%rename(multiplication) Vector2<T>::operator*(T multiplier) const;
%rename(vectorAddition) Vector2<T>::operator+(const Vector2<T>& vect1);
%rename(vectorSubstraction) Vector2<T>::operator-(const Vector2<T>& vect);
