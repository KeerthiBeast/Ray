# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = "/run/media/Keerthi/New Volume/Ray"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/run/media/Keerthi/New Volume/Ray/buildlin"

# Include any dependencies generated for this target.
include CMakeFiles/Ray.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Ray.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Ray.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ray.dir/flags.make

CMakeFiles/Ray.dir/src/main.cpp.o: CMakeFiles/Ray.dir/flags.make
CMakeFiles/Ray.dir/src/main.cpp.o: /run/media/Keerthi/New\ Volume/Ray/src/main.cpp
CMakeFiles/Ray.dir/src/main.cpp.o: CMakeFiles/Ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/run/media/Keerthi/New Volume/Ray/buildlin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Ray.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Ray.dir/src/main.cpp.o -MF CMakeFiles/Ray.dir/src/main.cpp.o.d -o CMakeFiles/Ray.dir/src/main.cpp.o -c "/run/media/Keerthi/New Volume/Ray/src/main.cpp"

CMakeFiles/Ray.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ray.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/run/media/Keerthi/New Volume/Ray/src/main.cpp" > CMakeFiles/Ray.dir/src/main.cpp.i

CMakeFiles/Ray.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ray.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/run/media/Keerthi/New Volume/Ray/src/main.cpp" -o CMakeFiles/Ray.dir/src/main.cpp.s

# Object files for target Ray
Ray_OBJECTS = \
"CMakeFiles/Ray.dir/src/main.cpp.o"

# External object files for target Ray
Ray_EXTERNAL_OBJECTS =

Ray: CMakeFiles/Ray.dir/src/main.cpp.o
Ray: CMakeFiles/Ray.dir/build.make
Ray: CMakeFiles/Ray.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/run/media/Keerthi/New Volume/Ray/buildlin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Ray"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ray.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ray.dir/build: Ray
.PHONY : CMakeFiles/Ray.dir/build

CMakeFiles/Ray.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Ray.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Ray.dir/clean

CMakeFiles/Ray.dir/depend:
	cd "/run/media/Keerthi/New Volume/Ray/buildlin" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/run/media/Keerthi/New Volume/Ray" "/run/media/Keerthi/New Volume/Ray" "/run/media/Keerthi/New Volume/Ray/buildlin" "/run/media/Keerthi/New Volume/Ray/buildlin" "/run/media/Keerthi/New Volume/Ray/buildlin/CMakeFiles/Ray.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Ray.dir/depend

