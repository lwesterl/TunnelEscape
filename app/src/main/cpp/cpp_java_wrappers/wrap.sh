#! /bin/bash
echo "This wraps WorldWrapper C++ implementations to java"
echo
swig -c++ -java -package com.westerholmgmail.v.lauri.tunnelescape -outdir ../../java/com/westerholmgmail/v/lauri/tunnelescape/ WorldWrapper.i
