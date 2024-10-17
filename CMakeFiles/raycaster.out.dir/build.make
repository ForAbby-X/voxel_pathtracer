# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /projects/perso/raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /projects/perso/raytracer

# Include any dependencies generated for this target.
include CMakeFiles/raycaster.out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/raycaster.out.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/raycaster.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raycaster.out.dir/flags.make

CMakeFiles/raycaster.out.dir/src/random.c.o: CMakeFiles/raycaster.out.dir/flags.make
CMakeFiles/raycaster.out.dir/src/random.c.o: src/random.c
CMakeFiles/raycaster.out.dir/src/random.c.o: CMakeFiles/raycaster.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/perso/raytracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/raycaster.out.dir/src/random.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/raycaster.out.dir/src/random.c.o -MF CMakeFiles/raycaster.out.dir/src/random.c.o.d -o CMakeFiles/raycaster.out.dir/src/random.c.o -c /projects/perso/raytracer/src/random.c

CMakeFiles/raycaster.out.dir/src/random.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raycaster.out.dir/src/random.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /projects/perso/raytracer/src/random.c > CMakeFiles/raycaster.out.dir/src/random.c.i

CMakeFiles/raycaster.out.dir/src/random.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raycaster.out.dir/src/random.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /projects/perso/raytracer/src/random.c -o CMakeFiles/raycaster.out.dir/src/random.c.s

CMakeFiles/raycaster.out.dir/src/map.c.o: CMakeFiles/raycaster.out.dir/flags.make
CMakeFiles/raycaster.out.dir/src/map.c.o: src/map.c
CMakeFiles/raycaster.out.dir/src/map.c.o: CMakeFiles/raycaster.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/perso/raytracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/raycaster.out.dir/src/map.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/raycaster.out.dir/src/map.c.o -MF CMakeFiles/raycaster.out.dir/src/map.c.o.d -o CMakeFiles/raycaster.out.dir/src/map.c.o -c /projects/perso/raytracer/src/map.c

CMakeFiles/raycaster.out.dir/src/map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raycaster.out.dir/src/map.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /projects/perso/raytracer/src/map.c > CMakeFiles/raycaster.out.dir/src/map.c.i

CMakeFiles/raycaster.out.dir/src/map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raycaster.out.dir/src/map.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /projects/perso/raytracer/src/map.c -o CMakeFiles/raycaster.out.dir/src/map.c.s

CMakeFiles/raycaster.out.dir/src/cast_ray.c.o: CMakeFiles/raycaster.out.dir/flags.make
CMakeFiles/raycaster.out.dir/src/cast_ray.c.o: src/cast_ray.c
CMakeFiles/raycaster.out.dir/src/cast_ray.c.o: CMakeFiles/raycaster.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/perso/raytracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/raycaster.out.dir/src/cast_ray.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/raycaster.out.dir/src/cast_ray.c.o -MF CMakeFiles/raycaster.out.dir/src/cast_ray.c.o.d -o CMakeFiles/raycaster.out.dir/src/cast_ray.c.o -c /projects/perso/raytracer/src/cast_ray.c

CMakeFiles/raycaster.out.dir/src/cast_ray.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raycaster.out.dir/src/cast_ray.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /projects/perso/raytracer/src/cast_ray.c > CMakeFiles/raycaster.out.dir/src/cast_ray.c.i

CMakeFiles/raycaster.out.dir/src/cast_ray.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raycaster.out.dir/src/cast_ray.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /projects/perso/raytracer/src/cast_ray.c -o CMakeFiles/raycaster.out.dir/src/cast_ray.c.s

CMakeFiles/raycaster.out.dir/src/render.c.o: CMakeFiles/raycaster.out.dir/flags.make
CMakeFiles/raycaster.out.dir/src/render.c.o: src/render.c
CMakeFiles/raycaster.out.dir/src/render.c.o: CMakeFiles/raycaster.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/perso/raytracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/raycaster.out.dir/src/render.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/raycaster.out.dir/src/render.c.o -MF CMakeFiles/raycaster.out.dir/src/render.c.o.d -o CMakeFiles/raycaster.out.dir/src/render.c.o -c /projects/perso/raytracer/src/render.c

CMakeFiles/raycaster.out.dir/src/render.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raycaster.out.dir/src/render.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /projects/perso/raytracer/src/render.c > CMakeFiles/raycaster.out.dir/src/render.c.i

CMakeFiles/raycaster.out.dir/src/render.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raycaster.out.dir/src/render.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /projects/perso/raytracer/src/render.c -o CMakeFiles/raycaster.out.dir/src/render.c.s

CMakeFiles/raycaster.out.dir/src/main.c.o: CMakeFiles/raycaster.out.dir/flags.make
CMakeFiles/raycaster.out.dir/src/main.c.o: src/main.c
CMakeFiles/raycaster.out.dir/src/main.c.o: CMakeFiles/raycaster.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/perso/raytracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/raycaster.out.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/raycaster.out.dir/src/main.c.o -MF CMakeFiles/raycaster.out.dir/src/main.c.o.d -o CMakeFiles/raycaster.out.dir/src/main.c.o -c /projects/perso/raytracer/src/main.c

CMakeFiles/raycaster.out.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/raycaster.out.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /projects/perso/raytracer/src/main.c > CMakeFiles/raycaster.out.dir/src/main.c.i

CMakeFiles/raycaster.out.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/raycaster.out.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /projects/perso/raytracer/src/main.c -o CMakeFiles/raycaster.out.dir/src/main.c.s

# Object files for target raycaster.out
raycaster_out_OBJECTS = \
"CMakeFiles/raycaster.out.dir/src/random.c.o" \
"CMakeFiles/raycaster.out.dir/src/map.c.o" \
"CMakeFiles/raycaster.out.dir/src/cast_ray.c.o" \
"CMakeFiles/raycaster.out.dir/src/render.c.o" \
"CMakeFiles/raycaster.out.dir/src/main.c.o"

# External object files for target raycaster.out
raycaster_out_EXTERNAL_OBJECTS =

raycaster.out: CMakeFiles/raycaster.out.dir/src/random.c.o
raycaster.out: CMakeFiles/raycaster.out.dir/src/map.c.o
raycaster.out: CMakeFiles/raycaster.out.dir/src/cast_ray.c.o
raycaster.out: CMakeFiles/raycaster.out.dir/src/render.c.o
raycaster.out: CMakeFiles/raycaster.out.dir/src/main.c.o
raycaster.out: CMakeFiles/raycaster.out.dir/build.make
raycaster.out: CMakeFiles/raycaster.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/projects/perso/raytracer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable raycaster.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raycaster.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raycaster.out.dir/build: raycaster.out
.PHONY : CMakeFiles/raycaster.out.dir/build

CMakeFiles/raycaster.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raycaster.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raycaster.out.dir/clean

CMakeFiles/raycaster.out.dir/depend:
	cd /projects/perso/raytracer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /projects/perso/raytracer /projects/perso/raytracer /projects/perso/raytracer /projects/perso/raytracer /projects/perso/raytracer/CMakeFiles/raycaster.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raycaster.out.dir/depend

