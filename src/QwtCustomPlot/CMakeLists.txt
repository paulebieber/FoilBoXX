cmake_minimum_required(VERSION 3.14)
project(QwtCustomPlot)

add_library(QwtCustomPlot STATIC src/QwtCustomPlot.cpp include/QwtCustomPlot.h)
target_include_directories(QwtCustomPlot PUBLIC include)

target_link_libraries(QwtCustomPlot PUBLIC qwt)
