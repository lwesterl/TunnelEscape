#! /bin/bash
echo "Generating wrapper for C++ implementations"
echo "Using swig and interface files"
echo
swig -c++ -java -package games.tunnelescape.tunnelescape -outdir ../../java/games/tunnelescape/tunnelescape/ Vector2.i
swig -c++ -java -package games.tunnelescape.tunnelescape -outdir ../../java/games/tunnelescape/tunnelescape/ Rect.i
swig -c++ -java -package games.tunnelescape.tunnelescape -outdir ../../java/games/tunnelescape/tunnelescape/ Shape.i
swig -c++ -java -package games.tunnelescape.tunnelescape -outdir ../../java/games/tunnelescape/tunnelescape/ PhysicsProperties.i
echo
echo "Remember to erase unnecessary setPosition method from PhysicsProperties.java (leave line 79 and remove the other one)"
