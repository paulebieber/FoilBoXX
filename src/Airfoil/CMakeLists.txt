cmake_minimum_required(VERSION 3.14)
project(Airfoil)

add_library(Airfoil
        src/Airfoil.cpp
        src/NoseBezier.cpp
        src/ShapeFunction.cpp
        src/BernsteinShape.cpp)

target_include_directories(Airfoil PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(Airfoil
        PUBLIC
        Qt5::Core
        armadillo
        SplineFunctions
        dlib::dlib)
