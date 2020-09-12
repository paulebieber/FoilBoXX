
#Populate a CMake variable with the sources
FILE(GLOB headers "Windows/*.h" "*.h")
FILE(GLOB src "Windows/*.cpp" "*.cpp")

target_sources(FoilBoXX PRIVATE ${src} ${headers})

add_subdirectory(Airfoil Airfoil)
add_subdirectory(XfoilSession XfoilSession)
add_subdirectory(SplineFunctions SplineFunctions)
add_subdirectory(QwtCustomPlot QwtCustomPlot)

target_include_directories(FoilBoXX PRIVATE "." "Windows")
