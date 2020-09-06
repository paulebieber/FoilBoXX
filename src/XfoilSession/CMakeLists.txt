cmake_minimum_required(VERSION 3.14)
project(XfoilSession)

add_library(XfoilSession src/XfoilSession.cpp)

target_include_directories(XfoilSession PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(XfoilSession PUBLIC xfoil-cpp armadillo)
