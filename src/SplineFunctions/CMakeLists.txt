cmake_minimum_required(VERSION 3.14)

project(SplineFunctions)

add_library(SplineFunctions STATIC src/SplineFunctions.cpp)

target_link_libraries(SplineFunctions PUBLIC armadillo PRIVATE dlib::dlib)

target_include_directories(SplineFunctions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(test)
