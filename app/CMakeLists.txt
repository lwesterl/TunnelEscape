# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             physics-lib

             # Sets the library as a shared library.
             SHARED
             #STATIC

             # Provides a relative path to your source file(s).
             # src/main/cpp/native-lib.cpp
        src/main/cpp/physics/Vector2.cpp
        src/main/cpp/physics/Vector2_wrap.cxx
        src/main/cpp/physics/Rect.cpp
        src/main/cpp/physics/Rect_wrap.cxx
        src/main/cpp/physics/Shape.cpp
        src/main/cpp/physics/Shape_wrap.cxx
        src/main/cpp/physics/PhysicsProperties.cpp
        src/main/cpp/physics/PhysicsProperties_wrap.cxx
        src/main/cpp/physics/PhysicsObject.cpp
        src/main/cpp/physics/DynamicObject.cpp
        src/main/cpp/physics/StaticObject.cpp
        src/main/cpp/physics/PhysicsGrid.cpp
        src/main/cpp/physics/PhysicsWorld.cpp
        src/main/cpp/physics/CollisionDetection.cpp
        src/main/cpp/cpp_java_wrappers/WorldWrapper.cpp
        src/main/cpp/cpp_java_wrappers/WorldWrapper_wrap.cxx

        )
include_directories(
        src/main/cpp/physics/Vector2.hpp
        src/main/cpp/physics/Rect.hpp
        src/main/cpp/physics/Shape.hpp
        src/main/cpp/physics/PhysicsProperties.hpp
        src/main/cpp/physics/PhysicsObject.hpp
        src/main/cpp/physics/DynamicObject.hpp
        src/main/cpp/physics/StaticObject.hpp
        src/main/cpp/physics/PhysicsGrid.hpp
        src/main/cpp/physics/PhysicsWorld.hpp
        src/main/cpp/physics/CollisionDetection.hpp
        src/main/cpp/cpp_java_wrappers/WorldWrapper.hpp
)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                        physics-lib
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )