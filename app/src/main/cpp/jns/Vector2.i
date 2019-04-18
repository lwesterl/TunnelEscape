%module Vector2
%{
#include "Vector2.hpp"
%}

%include "Vector2.hpp"
%rename(equals) Vector2<T>::operator==(const Vector2<T>& vect1) const;
%rename(greaterThan) Vector2<T>::operator>(const Vector2<T>& vect) const;
%rename(smallerThan) Vector2<T>::operator<(const Vector2<T>& vect) const;
%rename(vectorMultiplication) Vector2<T>::operator*(const Vector2<T>& vect1) const;
%rename(multiplication) Vector2<T>::operator*(T multiplier) const;
%rename(vectorAddition) Vector2<T>::operator+(const Vector2<T>& vect1);
%rename(vectorSubstraction) Vector2<T>::operator-(const Vector2<T>& vect);

%template (Vector2f) pe::Vector2<float>;
%template (Vector2i) pe::Vector2<int>;
