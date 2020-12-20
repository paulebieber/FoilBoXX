cmake_minimum_required(VERSION 3.17)
project(FoilBoXX)
set(CMAKE_CXX_STANDARD 11)

# version
add_definitions( -DFOILBOXX_VERSION_STRING="0.6.1" )
add_definitions( -DDYNAMIC_ARCH=TRUE )

#resources for Qt-Pictures
set(RESOURCES resources/resources.qrc)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_AUTOUIC_SEARCH_PATHS ./UI)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# find Qt5 and required components
list(APPEND CMAKE_PREFIX_PATH "~/Qt5.9.9/5.9.9/gcc_64/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH C:\\Qt\\Qt5.9.9\\5.9.9\\mingw53_32\\)
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets PrintSupport Svg Xml Concurrent OpenGL)

# OpenBlas
#list(APPEND CMAKE_PREFIX_PATH C:\\Users\\Paul\\OpenBLAS\\build) #Windows Machines
#set(BLAS_LIBRARIES C:\\Users\\Paul\\OpenBLAS\\build)
#find_package(OpenBLAS REQUIRED)
find_package(BLAS REQUIRED)

#qwt
add_subdirectory(external)

add_executable(FoilBoXX ${RESOURCES})
add_subdirectory(src) # Adds all headers and sources located in /src to executable,
# like defined in src/CMakeLists, also sets include Directories

target_link_libraries(FoilBoXX Airfoil XfoilSession SplineFunctions QwtCustomPlot)

target_link_libraries(FoilBoXX
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui)
