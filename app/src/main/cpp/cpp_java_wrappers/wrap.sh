#! /bin/bash
echo "This wraps WorldWrapper to java files"
echo
swig -c++ -java -package com.westerholmgmail.v.lauri.tunnelescape -outdir ../../java/com/westerholmgmail/v/lauri/tunnelescape/ WorldWrapper.i
echo
echo "Remember to fix 4 error from WorldWrapper.java where Vector2f should be passed instead of its memory address"
echo "Fix also issue from PairDeque where Pair should be passed rather than its memory address"
