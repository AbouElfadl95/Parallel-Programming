# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.5/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Omar/Documents/GUC/Projects/Microprocessor/M2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Omar/Documents/GUC/Projects/Microprocessor/M2

# Include any dependencies generated for this target.
include CMakeFiles/micro_proj_M2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/micro_proj_M2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/micro_proj_M2.dir/flags.make

CMakeFiles/micro_proj_M2.dir/Milestone_2.c.o: CMakeFiles/micro_proj_M2.dir/flags.make
CMakeFiles/micro_proj_M2.dir/Milestone_2.c.o: Milestone_2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Omar/Documents/GUC/Projects/Microprocessor/M2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/micro_proj_M2.dir/Milestone_2.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/micro_proj_M2.dir/Milestone_2.c.o   -c /Users/Omar/Documents/GUC/Projects/Microprocessor/M2/Milestone_2.c

CMakeFiles/micro_proj_M2.dir/Milestone_2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/micro_proj_M2.dir/Milestone_2.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Omar/Documents/GUC/Projects/Microprocessor/M2/Milestone_2.c > CMakeFiles/micro_proj_M2.dir/Milestone_2.c.i

CMakeFiles/micro_proj_M2.dir/Milestone_2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/micro_proj_M2.dir/Milestone_2.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Omar/Documents/GUC/Projects/Microprocessor/M2/Milestone_2.c -o CMakeFiles/micro_proj_M2.dir/Milestone_2.c.s

# Object files for target micro_proj_M2
micro_proj_M2_OBJECTS = \
"CMakeFiles/micro_proj_M2.dir/Milestone_2.c.o"

# External object files for target micro_proj_M2
micro_proj_M2_EXTERNAL_OBJECTS =

micro_proj_M2: CMakeFiles/micro_proj_M2.dir/Milestone_2.c.o
micro_proj_M2: CMakeFiles/micro_proj_M2.dir/build.make
micro_proj_M2: /usr/local/Cellar/open-mpi/4.0.2/lib/libmpi.dylib
micro_proj_M2: CMakeFiles/micro_proj_M2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Omar/Documents/GUC/Projects/Microprocessor/M2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable micro_proj_M2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/micro_proj_M2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/micro_proj_M2.dir/build: micro_proj_M2

.PHONY : CMakeFiles/micro_proj_M2.dir/build

CMakeFiles/micro_proj_M2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/micro_proj_M2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/micro_proj_M2.dir/clean

CMakeFiles/micro_proj_M2.dir/depend:
	cd /Users/Omar/Documents/GUC/Projects/Microprocessor/M2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Omar/Documents/GUC/Projects/Microprocessor/M2 /Users/Omar/Documents/GUC/Projects/Microprocessor/M2 /Users/Omar/Documents/GUC/Projects/Microprocessor/M2 /Users/Omar/Documents/GUC/Projects/Microprocessor/M2 /Users/Omar/Documents/GUC/Projects/Microprocessor/M2/CMakeFiles/micro_proj_M2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/micro_proj_M2.dir/depend
