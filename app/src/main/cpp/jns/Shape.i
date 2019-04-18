%module ShapeModule
%{
#include "Shape.hpp"
%}

%include "Vector2.hpp"
%include "Shape.hpp"
%include "std_vector.i"
%include "std_deque.i"

%template (Vector2f) pe::Vector2<float>;
%template (Vector2fDeque) std::deque<pe::Vector2f>;
%template (Vector2fVector) std::vector<pe::Vector2f>;
