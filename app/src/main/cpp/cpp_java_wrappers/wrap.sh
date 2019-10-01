#! /bin/bash
echo "This wraps WorldWrapper C++ implementations to java"
echo
swig -c++ -java -package games.tunnelescape.tunnelescape -outdir ../../java/games/tunnelescape/tunnelescape/ WorldWrapper.i
