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

# Utility rule file for QwtCustomPlot_autogen.

# Include the progress variables for this target.
include src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen.dir/progress.make

src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/paul/FoilBoXX/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target QwtCustomPlot"
	cd /home/paul/FoilBoXX/debug/src/QwtCustomPlot && /usr/bin/cmake -E cmake_autogen /home/paul/FoilBoXX/debug/src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen.dir/AutogenInfo.json Debug

QwtCustomPlot_autogen: src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen
QwtCustomPlot_autogen: src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen.dir/build.make

.PHONY : QwtCustomPlot_autogen

# Rule to build all files generated by this target.
src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen.dir/build: QwtCustomPlot_autogen

.PHONY : src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen.dir/build

src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen.dir/clean:
	cd /home/paul/FoilBoXX/debug/src/QwtCustomPlot && $(CMAKE_COMMAND) -P CMakeFiles/QwtCustomPlot_autogen.dir/cmake_clean.cmake
.PHONY : src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen.dir/clean

src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen.dir/depend:
	cd /home/paul/FoilBoXX/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paul/FoilBoXX /home/paul/FoilBoXX/src/QwtCustomPlot /home/paul/FoilBoXX/debug /home/paul/FoilBoXX/debug/src/QwtCustomPlot /home/paul/FoilBoXX/debug/src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/QwtCustomPlot/CMakeFiles/QwtCustomPlot_autogen.dir/depend

