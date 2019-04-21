%module WorldWrapperModule

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

%template (PairDeque) std::deque<Pair>;
