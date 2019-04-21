%module PhysicsPropertiesModule


%{
#include "PhysicsProperties.hpp"
%}

%include "PhysicsProperties.hpp"
%include "Vector2.hpp"

%template (Vector2f) Vector2<float>;
%template (Vector2i) Vector2<int>;
