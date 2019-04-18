%module Rect
%{
#include "Rect.hpp"
%}

%include "Vector2.hpp"
%include "Rect.hpp"

%template (Vector2f) pe::Vector2<float>;
%template (Vector2i) pe::Vector2<int>;
%template (Rectf) pe::Rect<float>;
%template (Recti) pe::Rect<int>;
