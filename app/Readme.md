# app
Contains the Android Studio project itself

## Requirements

- Android Studio
- SWIG (needed if one wants to modify the physicslib)
```
sudo apt-get install swig
```

(SWIG related shell scripts work in GNU/Linux)


## Project structure

### src
Contains code and all assets

1. **androidTest**
  - Subdirectories contain _InstrumentedTests_ which basically test the native library, physisclib

2. **main**
  - assets
    - Images
    - Levels (created with LevelEditor)
    - TensorFlow lite model
  - cpp (\*.i = SWIG interface files and \*.cxx = SWIG generated C++ files)
    - cpp_java_wrappers
      - WorldWrapper class and matching SWIG related files
      - WorldWrapper is the class which creates an interface between Java and C++ methods
      - _wrap.sh_ creates Java classes using SWIG (pre-created)
    - physics
      - Physics library, PhysicsEngine, and also matching SWIG related files
      - _wrap_physics.sh_ creates Java classes using SWIG (pre-created)
  - java
    - Java files
    - Physics related files in games.tunnelescape.tunnelescape are automatically created by SWIG
  - res
    - Drawable resources
    - Layouts
    - String constants related to layouts

3. **test**
  - Basically empty

### Build files
1. **build.gradle**
  - Main build configuration file
2. **CMakeList.txt**
  - CMake configuration for the physicslib
