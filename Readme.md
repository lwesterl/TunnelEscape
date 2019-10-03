# TunnelEscape
![alt text][logo]

[logo]: ./app/src/main/res/drawable/tunnelescape_title_small.png "TunnelEscape logo"

## Documentation
To create documentation
```
sudo apt-get install doxygen graphviz
doxygen
```
See doc/html/index.html for doxygen docs

## Development
Use [Android Studio](https://developer.android.com/studio) to build and test the app

## Libraries & technologies
- Android SDK
  - Min v. 21
- [PhysicsEngine](https://github.com/lwesterl/PhysicsEngine)
  - Integrated to the app using [SWIG](http://www.swig.org/)
  - Compiled to a native lib, physicslib
- [ScoreServer](https://github.com/lwesterl/ScoreServer)
  - To save and display scores
- [JUnit](https://junit.org/junit5/) for testing
- [Tensorflow](https://www.tensorflow.org/) for AIPlayer machine learning
- [Doxygen](http://www.doxygen.nl/) for inline documentation
- [Qt5](https://doc.qt.io/qt-5/) for the LevelEditor


## Demo
<a href="https://tunnelescape.games/static/media/TunnelEscape_video.bab32620.mp4" target="_blank"><img src="https://tunnelescape.games/static/media/level3_image1.2b7b368b.png"
alt="IMAGE ALT TEXT HERE" width="400" height="200" border="10" /></a>
