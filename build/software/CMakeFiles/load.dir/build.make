# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/LightDance-RPi/controller

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/LightDance-RPi/controller/build

# Include any dependencies generated for this target.
include software/CMakeFiles/load.dir/depend.make

# Include the progress variables for this target.
include software/CMakeFiles/load.dir/progress.make

# Include the compile flags for this target's objects.
include software/CMakeFiles/load.dir/flags.make

software/CMakeFiles/load.dir/src/commands/load.cpp.o: software/CMakeFiles/load.dir/flags.make
software/CMakeFiles/load.dir/src/commands/load.cpp.o: ../software/src/commands/load.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/LightDance-RPi/controller/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object software/CMakeFiles/load.dir/src/commands/load.cpp.o"
	cd /home/pi/LightDance-RPi/controller/build/software && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/load.dir/src/commands/load.cpp.o -c /home/pi/LightDance-RPi/controller/software/src/commands/load.cpp

software/CMakeFiles/load.dir/src/commands/load.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/load.dir/src/commands/load.cpp.i"
	cd /home/pi/LightDance-RPi/controller/build/software && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/LightDance-RPi/controller/software/src/commands/load.cpp > CMakeFiles/load.dir/src/commands/load.cpp.i

software/CMakeFiles/load.dir/src/commands/load.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/load.dir/src/commands/load.cpp.s"
	cd /home/pi/LightDance-RPi/controller/build/software && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/LightDance-RPi/controller/software/src/commands/load.cpp -o CMakeFiles/load.dir/src/commands/load.cpp.s

# Object files for target load
load_OBJECTS = \
"CMakeFiles/load.dir/src/commands/load.cpp.o"

# External object files for target load
load_EXTERNAL_OBJECTS =

software/load: software/CMakeFiles/load.dir/src/commands/load.cpp.o
software/load: software/CMakeFiles/load.dir/build.make
software/load: /usr/lib/arm-linux-gnueabihf/libboost_serialization.so
software/load: hardware/libhardware.a
software/load: software/libplayerLIB.a
software/load: software/libStateMachineLIB.a
software/load: software/libplayerLIB.a
software/load: software/libStateMachineLIB.a
software/load: /usr/lib/arm-linux-gnueabihf/libboost_serialization.so
software/load: hardware/libhardware.a
software/load: software/CMakeFiles/load.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/LightDance-RPi/controller/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable load"
	cd /home/pi/LightDance-RPi/controller/build/software && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/load.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
software/CMakeFiles/load.dir/build: software/load

.PHONY : software/CMakeFiles/load.dir/build

software/CMakeFiles/load.dir/clean:
	cd /home/pi/LightDance-RPi/controller/build/software && $(CMAKE_COMMAND) -P CMakeFiles/load.dir/cmake_clean.cmake
.PHONY : software/CMakeFiles/load.dir/clean

software/CMakeFiles/load.dir/depend:
	cd /home/pi/LightDance-RPi/controller/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/LightDance-RPi/controller /home/pi/LightDance-RPi/controller/software /home/pi/LightDance-RPi/controller/build /home/pi/LightDance-RPi/controller/build/software /home/pi/LightDance-RPi/controller/build/software/CMakeFiles/load.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : software/CMakeFiles/load.dir/depend

