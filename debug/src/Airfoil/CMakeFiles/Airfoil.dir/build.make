# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/paul/FoilBoXX

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paul/FoilBoXX/debug

# Include any dependencies generated for this target.
include src/Airfoil/CMakeFiles/Airfoil.dir/depend.make

# Include the progress variables for this target.
include src/Airfoil/CMakeFiles/Airfoil.dir/progress.make

# Include the compile flags for this target's objects.
include src/Airfoil/CMakeFiles/Airfoil.dir/flags.make

src/Airfoil/CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.o: src/Airfoil/CMakeFiles/Airfoil.dir/flags.make
src/Airfoil/CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.o: src/Airfoil/Airfoil_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/FoilBoXX/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Airfoil/CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.o"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.o -c /home/paul/FoilBoXX/debug/src/Airfoil/Airfoil_autogen/mocs_compilation.cpp

src/Airfoil/CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.i"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/FoilBoXX/debug/src/Airfoil/Airfoil_autogen/mocs_compilation.cpp > CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.i

src/Airfoil/CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.s"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/FoilBoXX/debug/src/Airfoil/Airfoil_autogen/mocs_compilation.cpp -o CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.s

src/Airfoil/CMakeFiles/Airfoil.dir/src/Airfoil.cpp.o: src/Airfoil/CMakeFiles/Airfoil.dir/flags.make
src/Airfoil/CMakeFiles/Airfoil.dir/src/Airfoil.cpp.o: ../src/Airfoil/src/Airfoil.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/FoilBoXX/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/Airfoil/CMakeFiles/Airfoil.dir/src/Airfoil.cpp.o"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Airfoil.dir/src/Airfoil.cpp.o -c /home/paul/FoilBoXX/src/Airfoil/src/Airfoil.cpp

src/Airfoil/CMakeFiles/Airfoil.dir/src/Airfoil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Airfoil.dir/src/Airfoil.cpp.i"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/FoilBoXX/src/Airfoil/src/Airfoil.cpp > CMakeFiles/Airfoil.dir/src/Airfoil.cpp.i

src/Airfoil/CMakeFiles/Airfoil.dir/src/Airfoil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Airfoil.dir/src/Airfoil.cpp.s"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/FoilBoXX/src/Airfoil/src/Airfoil.cpp -o CMakeFiles/Airfoil.dir/src/Airfoil.cpp.s

src/Airfoil/CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.o: src/Airfoil/CMakeFiles/Airfoil.dir/flags.make
src/Airfoil/CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.o: ../src/Airfoil/src/NoseBezier.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/FoilBoXX/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/Airfoil/CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.o"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.o -c /home/paul/FoilBoXX/src/Airfoil/src/NoseBezier.cpp

src/Airfoil/CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.i"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/FoilBoXX/src/Airfoil/src/NoseBezier.cpp > CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.i

src/Airfoil/CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.s"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/FoilBoXX/src/Airfoil/src/NoseBezier.cpp -o CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.s

src/Airfoil/CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.o: src/Airfoil/CMakeFiles/Airfoil.dir/flags.make
src/Airfoil/CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.o: ../src/Airfoil/src/ShapeFunction.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/FoilBoXX/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/Airfoil/CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.o"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.o -c /home/paul/FoilBoXX/src/Airfoil/src/ShapeFunction.cpp

src/Airfoil/CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.i"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/FoilBoXX/src/Airfoil/src/ShapeFunction.cpp > CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.i

src/Airfoil/CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.s"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/FoilBoXX/src/Airfoil/src/ShapeFunction.cpp -o CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.s

src/Airfoil/CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.o: src/Airfoil/CMakeFiles/Airfoil.dir/flags.make
src/Airfoil/CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.o: ../src/Airfoil/src/BernsteinShape.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paul/FoilBoXX/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/Airfoil/CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.o"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.o -c /home/paul/FoilBoXX/src/Airfoil/src/BernsteinShape.cpp

src/Airfoil/CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.i"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paul/FoilBoXX/src/Airfoil/src/BernsteinShape.cpp > CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.i

src/Airfoil/CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.s"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paul/FoilBoXX/src/Airfoil/src/BernsteinShape.cpp -o CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.s

# Object files for target Airfoil
Airfoil_OBJECTS = \
"CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/Airfoil.dir/src/Airfoil.cpp.o" \
"CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.o" \
"CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.o" \
"CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.o"

# External object files for target Airfoil
Airfoil_EXTERNAL_OBJECTS =

src/Airfoil/libAirfoil.so: src/Airfoil/CMakeFiles/Airfoil.dir/Airfoil_autogen/mocs_compilation.cpp.o
src/Airfoil/libAirfoil.so: src/Airfoil/CMakeFiles/Airfoil.dir/src/Airfoil.cpp.o
src/Airfoil/libAirfoil.so: src/Airfoil/CMakeFiles/Airfoil.dir/src/NoseBezier.cpp.o
src/Airfoil/libAirfoil.so: src/Airfoil/CMakeFiles/Airfoil.dir/src/ShapeFunction.cpp.o
src/Airfoil/libAirfoil.so: src/Airfoil/CMakeFiles/Airfoil.dir/src/BernsteinShape.cpp.o
src/Airfoil/libAirfoil.so: src/Airfoil/CMakeFiles/Airfoil.dir/build.make
src/Airfoil/libAirfoil.so: /usr/lib/libQt5Core.so.5.15.0
src/Airfoil/libAirfoil.so: src/SplineFunctions/libSplineFunctions.so
src/Airfoil/libAirfoil.so: external/dlib/dlib/libdlib.a
src/Airfoil/libAirfoil.so: external/armadillo/libarmadillo.so.9.900.2
src/Airfoil/libAirfoil.so: /usr/lib/liblapack.so
src/Airfoil/libAirfoil.so: /usr/lib/libSM.so
src/Airfoil/libAirfoil.so: /usr/lib/libICE.so
src/Airfoil/libAirfoil.so: /usr/lib/libX11.so
src/Airfoil/libAirfoil.so: /usr/lib/libXext.so
src/Airfoil/libAirfoil.so: /usr/lib/libgif.so
src/Airfoil/libAirfoil.so: /usr/lib/libpng.so
src/Airfoil/libAirfoil.so: /usr/lib/libz.so
src/Airfoil/libAirfoil.so: /usr/lib/libjpeg.so
src/Airfoil/libAirfoil.so: /usr/lib/libopenblas.so
src/Airfoil/libAirfoil.so: /usr/lib/libsqlite3.so
src/Airfoil/libAirfoil.so: src/Airfoil/CMakeFiles/Airfoil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paul/FoilBoXX/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX shared library libAirfoil.so"
	cd /home/paul/FoilBoXX/debug/src/Airfoil && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Airfoil.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Airfoil/CMakeFiles/Airfoil.dir/build: src/Airfoil/libAirfoil.so

.PHONY : src/Airfoil/CMakeFiles/Airfoil.dir/build

src/Airfoil/CMakeFiles/Airfoil.dir/clean:
	cd /home/paul/FoilBoXX/debug/src/Airfoil && $(CMAKE_COMMAND) -P CMakeFiles/Airfoil.dir/cmake_clean.cmake
.PHONY : src/Airfoil/CMakeFiles/Airfoil.dir/clean

src/Airfoil/CMakeFiles/Airfoil.dir/depend:
	cd /home/paul/FoilBoXX/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paul/FoilBoXX /home/paul/FoilBoXX/src/Airfoil /home/paul/FoilBoXX/debug /home/paul/FoilBoXX/debug/src/Airfoil /home/paul/FoilBoXX/debug/src/Airfoil/CMakeFiles/Airfoil.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Airfoil/CMakeFiles/Airfoil.dir/depend

