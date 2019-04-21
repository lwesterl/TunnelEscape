#! /bin/bash
echo "Generating wrapper for C++ implementations"
echo "Using swig and interface files"
echo
swig -c++ -java -package com.westerholmgmail.v.lauri.tunnelescape -outdir ../../java/com/westerholmgmail/v/lauri/tunnelescape/ Vector2.i
swig -c++ -java -package com.westerholmgmail.v.lauri.tunnelescape -outdir ../../java/com/westerholmgmail/v/lauri/tunnelescape/ Rect.i
swig -c++ -java -package com.westerholmgmail.v.lauri.tunnelescape -outdir ../../java/com/westerholmgmail/v/lauri/tunnelescape/ Shape.i
swig -c++ -java -package com.westerholmgmail.v.lauri.tunnelescape -outdir ../../java/com/westerholmgmail/v/lauri/tunnelescape/ PhysicsProperties.i
echo
echo "Remember to erase unnecessary setPosition method from PhysicsProperties.java (leave line 79 and remove the other one)"
