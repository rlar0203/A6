# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/build"

# Include any dependencies generated for this target.
include CMakeFiles/A6.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/A6.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/A6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/A6.dir/flags.make

CMakeFiles/A6.dir/src/Image.cpp.o: CMakeFiles/A6.dir/flags.make
CMakeFiles/A6.dir/src/Image.cpp.o: ../src/Image.cpp
CMakeFiles/A6.dir/src/Image.cpp.o: CMakeFiles/A6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/A6.dir/src/Image.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/A6.dir/src/Image.cpp.o -MF CMakeFiles/A6.dir/src/Image.cpp.o.d -o CMakeFiles/A6.dir/src/Image.cpp.o -c "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/src/Image.cpp"

CMakeFiles/A6.dir/src/Image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A6.dir/src/Image.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/src/Image.cpp" > CMakeFiles/A6.dir/src/Image.cpp.i

CMakeFiles/A6.dir/src/Image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A6.dir/src/Image.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/src/Image.cpp" -o CMakeFiles/A6.dir/src/Image.cpp.s

CMakeFiles/A6.dir/src/main.cpp.o: CMakeFiles/A6.dir/flags.make
CMakeFiles/A6.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/A6.dir/src/main.cpp.o: CMakeFiles/A6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/A6.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/A6.dir/src/main.cpp.o -MF CMakeFiles/A6.dir/src/main.cpp.o.d -o CMakeFiles/A6.dir/src/main.cpp.o -c "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/src/main.cpp"

CMakeFiles/A6.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A6.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/src/main.cpp" > CMakeFiles/A6.dir/src/main.cpp.i

CMakeFiles/A6.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A6.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/src/main.cpp" -o CMakeFiles/A6.dir/src/main.cpp.s

# Object files for target A6
A6_OBJECTS = \
"CMakeFiles/A6.dir/src/Image.cpp.o" \
"CMakeFiles/A6.dir/src/main.cpp.o"

# External object files for target A6
A6_EXTERNAL_OBJECTS =

A6: CMakeFiles/A6.dir/src/Image.cpp.o
A6: CMakeFiles/A6.dir/src/main.cpp.o
A6: CMakeFiles/A6.dir/build.make
A6: CMakeFiles/A6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable A6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/A6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/A6.dir/build: A6
.PHONY : CMakeFiles/A6.dir/build

CMakeFiles/A6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/A6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/A6.dir/clean

CMakeFiles/A6.dir/depend:
	cd "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6" "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6" "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/build" "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/build" "/mnt/c/Users/rlar0/Documents/C++_files/CSCE 441/A6/build/CMakeFiles/A6.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/A6.dir/depend

