# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/lh2debug/clion-2017.1.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/lh2debug/clion-2017.1.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lh2debug/code/LevelDBSNAPPY

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lh2debug/code/LevelDBSNAPPY/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/version_set_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/version_set_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/version_set_test.dir/flags.make

CMakeFiles/version_set_test.dir/db/version_set_test.cc.o: CMakeFiles/version_set_test.dir/flags.make
CMakeFiles/version_set_test.dir/db/version_set_test.cc.o: ../db/version_set_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lh2debug/code/LevelDBSNAPPY/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/version_set_test.dir/db/version_set_test.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/version_set_test.dir/db/version_set_test.cc.o -c /home/lh2debug/code/LevelDBSNAPPY/db/version_set_test.cc

CMakeFiles/version_set_test.dir/db/version_set_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/version_set_test.dir/db/version_set_test.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lh2debug/code/LevelDBSNAPPY/db/version_set_test.cc > CMakeFiles/version_set_test.dir/db/version_set_test.cc.i

CMakeFiles/version_set_test.dir/db/version_set_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/version_set_test.dir/db/version_set_test.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lh2debug/code/LevelDBSNAPPY/db/version_set_test.cc -o CMakeFiles/version_set_test.dir/db/version_set_test.cc.s

CMakeFiles/version_set_test.dir/db/version_set_test.cc.o.requires:

.PHONY : CMakeFiles/version_set_test.dir/db/version_set_test.cc.o.requires

CMakeFiles/version_set_test.dir/db/version_set_test.cc.o.provides: CMakeFiles/version_set_test.dir/db/version_set_test.cc.o.requires
	$(MAKE) -f CMakeFiles/version_set_test.dir/build.make CMakeFiles/version_set_test.dir/db/version_set_test.cc.o.provides.build
.PHONY : CMakeFiles/version_set_test.dir/db/version_set_test.cc.o.provides

CMakeFiles/version_set_test.dir/db/version_set_test.cc.o.provides.build: CMakeFiles/version_set_test.dir/db/version_set_test.cc.o


# Object files for target version_set_test
version_set_test_OBJECTS = \
"CMakeFiles/version_set_test.dir/db/version_set_test.cc.o"

# External object files for target version_set_test
version_set_test_EXTERNAL_OBJECTS =

version_set_test: CMakeFiles/version_set_test.dir/db/version_set_test.cc.o
version_set_test: CMakeFiles/version_set_test.dir/build.make
version_set_test: libleveldb-testharness.a
version_set_test: libleveldb_static.a
version_set_test: CMakeFiles/version_set_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lh2debug/code/LevelDBSNAPPY/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable version_set_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/version_set_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/version_set_test.dir/build: version_set_test

.PHONY : CMakeFiles/version_set_test.dir/build

CMakeFiles/version_set_test.dir/requires: CMakeFiles/version_set_test.dir/db/version_set_test.cc.o.requires

.PHONY : CMakeFiles/version_set_test.dir/requires

CMakeFiles/version_set_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/version_set_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/version_set_test.dir/clean

CMakeFiles/version_set_test.dir/depend:
	cd /home/lh2debug/code/LevelDBSNAPPY/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lh2debug/code/LevelDBSNAPPY /home/lh2debug/code/LevelDBSNAPPY /home/lh2debug/code/LevelDBSNAPPY/cmake-build-debug /home/lh2debug/code/LevelDBSNAPPY/cmake-build-debug /home/lh2debug/code/LevelDBSNAPPY/cmake-build-debug/CMakeFiles/version_set_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/version_set_test.dir/depend

