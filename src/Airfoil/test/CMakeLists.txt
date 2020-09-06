set(name Test)

add_executable(${name} test.cpp ../src/AirfoilPlot.cpp)

target_link_libraries(${name} PRIVATE Airfoil qwt QwtCustomPlot)
