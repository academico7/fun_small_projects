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
CMAKE_SOURCE_DIR = /mnt/c/repo/fun_small_projects/task_runner

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/repo/fun_small_projects/task_runner/build/debug

# Include any dependencies generated for this target.
include tst/CMakeFiles/unit_tests.dir/depend.make

# Include the progress variables for this target.
include tst/CMakeFiles/unit_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tst/CMakeFiles/unit_tests.dir/flags.make

tst/CMakeFiles/unit_tests.dir/task_runner_test.cpp.o: tst/CMakeFiles/unit_tests.dir/flags.make
tst/CMakeFiles/unit_tests.dir/task_runner_test.cpp.o: ../../tst/task_runner_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/repo/fun_small_projects/task_runner/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tst/CMakeFiles/unit_tests.dir/task_runner_test.cpp.o"
	cd /mnt/c/repo/fun_small_projects/task_runner/build/debug/tst && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_tests.dir/task_runner_test.cpp.o -c /mnt/c/repo/fun_small_projects/task_runner/tst/task_runner_test.cpp

tst/CMakeFiles/unit_tests.dir/task_runner_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/task_runner_test.cpp.i"
	cd /mnt/c/repo/fun_small_projects/task_runner/build/debug/tst && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/repo/fun_small_projects/task_runner/tst/task_runner_test.cpp > CMakeFiles/unit_tests.dir/task_runner_test.cpp.i

tst/CMakeFiles/unit_tests.dir/task_runner_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/task_runner_test.cpp.s"
	cd /mnt/c/repo/fun_small_projects/task_runner/build/debug/tst && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/repo/fun_small_projects/task_runner/tst/task_runner_test.cpp -o CMakeFiles/unit_tests.dir/task_runner_test.cpp.s

# Object files for target unit_tests
unit_tests_OBJECTS = \
"CMakeFiles/unit_tests.dir/task_runner_test.cpp.o"

# External object files for target unit_tests
unit_tests_EXTERNAL_OBJECTS =

tst/unit_tests: tst/CMakeFiles/unit_tests.dir/task_runner_test.cpp.o
tst/unit_tests: tst/CMakeFiles/unit_tests.dir/build.make
tst/unit_tests: src/libtask_runner_lib.so
tst/unit_tests: lib/libgtest_maind.a
tst/unit_tests: lib/libgtestd.a
tst/unit_tests: tst/CMakeFiles/unit_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/repo/fun_small_projects/task_runner/build/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable unit_tests"
	cd /mnt/c/repo/fun_small_projects/task_runner/build/debug/tst && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tst/CMakeFiles/unit_tests.dir/build: tst/unit_tests

.PHONY : tst/CMakeFiles/unit_tests.dir/build

tst/CMakeFiles/unit_tests.dir/clean:
	cd /mnt/c/repo/fun_small_projects/task_runner/build/debug/tst && $(CMAKE_COMMAND) -P CMakeFiles/unit_tests.dir/cmake_clean.cmake
.PHONY : tst/CMakeFiles/unit_tests.dir/clean

tst/CMakeFiles/unit_tests.dir/depend:
	cd /mnt/c/repo/fun_small_projects/task_runner/build/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/repo/fun_small_projects/task_runner /mnt/c/repo/fun_small_projects/task_runner/tst /mnt/c/repo/fun_small_projects/task_runner/build/debug /mnt/c/repo/fun_small_projects/task_runner/build/debug/tst /mnt/c/repo/fun_small_projects/task_runner/build/debug/tst/CMakeFiles/unit_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tst/CMakeFiles/unit_tests.dir/depend

