
#Add Dlib Submodule
add_subdirectory(dlib)

#Add armadillo Submodule
add_subdirectory(armadillo)

#Add qwt (no CMakeLists.txt given)
add_library(qwt SHARED)
FILE(GLOB qwt_headers "qwt/src/*.h")
FILE(GLOB qwt_src "qwt/src/*.cpp")
target_sources(qwt PRIVATE ${qwt_src} ${qwt_headers})
target_link_libraries(qwt PUBLIC Qt5::Core Qt5::Widgets Qt5::Gui Qt5::PrintSupport Qt5::Concurrent Qt5::OpenGL Qt5::Svg Qt5::Xml)
target_include_directories(qwt PUBLIC qwt/src)

#Add xfoil-cpp (no CMakeLists.txt given)
add_library(xfoil-cpp SHARED)
target_sources(xfoil-cpp PRIVATE "xfoil-cpp/XFoil.cpp")
target_include_directories(xfoil-cpp PUBLIC "xfoil-cpp/")
