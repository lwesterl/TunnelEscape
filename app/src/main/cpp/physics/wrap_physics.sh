#! /bin/bash
echo "Generating wrapper for C++ implementations"
echo "Using swig and interface files"
echo 
swig -c++ -java -package com.westerholmgmail.v.lauri.tunnelescape -outdir ../../java/com/westerholmgmail/v/lauri/tunnelescape/ Vector2.i
swig -c++ -java -package com.westerholmgmail.v.lauri.tunnelescape -outdir ../../java/com/westerholmgmail/v/lauri/tunnelescape/ Rect.i
swig -c++ -java -package com.westerholmgmail.v.lauri.tunnelescape -outdir ../../java/com/westerholmgmail/v/lauri/tunnelescape/ Shape.i
swig -c++ -java -package com.westerholmgmail.v.lauri.tunnelescape -outdir ../../java/com/westerholmgmail/v/lauri/tunnelescape/ PhysicsProperties.i
echo
echo "Remember to erase unnecessary setPosition method from PhysicsProperties.java (original line 79)"
echo "Also modify PhysicsProperties.java movePosition (original line 84) to:"
echo "PhysicsPropertiesModuleJNI.PhysicsProperties_movePosition(swigCPtr, this, move)"
