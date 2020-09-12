cmake_minimum_required(VERSION 3.18)
project(FoilBoXX)
set(CMAKE_CXX_STANDARD 11)

# version
add_definitions( -DFOILBOXX_VERSION_STRING="0.5.0" )
add_definitions( -DDYNAMIC_ARCH=TRUE )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
#Other Dependencies
#add_subdirectory(external/xfoil-cpp-master)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#OpenBlas
list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\OpenBLAS") #Windows Machines
find_package(BLAS REQUIRED)

# find Qt5 and required components
list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/qt/)
list(APPEND CMAKE_PREFIX_PATH C:\\Qt\\5.14.2\\mingw73_64)
#list(APPEND CMAKE_PREFIX_PATH external/openBLAS/build)

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets PrintSupport Svg Xml Concurrent OpenGL)

set(CMAKE_AUTOUIC_SEARCH_PATHS ./UI)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#qwt
add_subdirectory(external)

#resources for Qt-Pictures
set(RESOURCES resources/resources.qrc)

add_executable(FoilBoXX ${RESOURCES})
add_subdirectory(src) # Adds all headers and sources located in /src to executable,
# like defined in src/CMakeLists, also sets include Directories

target_link_libraries(FoilBoXX Airfoil XfoilSession SplineFunctions QwtCustomPlot)

target_link_libraries(FoilBoXX
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui)
