# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/itupac/OutOfTree-gnuradio/gr-SetSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build

# Include any dependencies generated for this target.
include swig/CMakeFiles/_SetSystem_swig.dir/depend.make

# Include the progress variables for this target.
include swig/CMakeFiles/_SetSystem_swig.dir/progress.make

# Include the compile flags for this target's objects.
include swig/CMakeFiles/_SetSystem_swig.dir/flags.make

swig/SetSystem_swigPYTHON_wrap.cxx: swig/SetSystem_swig_swig_2d0df
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "dummy command to show SetSystem_swig_swig_2d0df dependency of /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swigPYTHON_wrap.cxx"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/cmake -E touch_nocreate /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swigPYTHON_wrap.cxx

swig/SetSystem_swig.py: swig/SetSystem_swig_swig_2d0df
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "dummy command to show SetSystem_swig_swig_2d0df dependency of /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig.py"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/cmake -E touch_nocreate /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig.py

swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o: swig/CMakeFiles/_SetSystem_swig.dir/flags.make
swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o: swig/SetSystem_swigPYTHON_wrap.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Wno-unused-but-set-variable -o CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o -c /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swigPYTHON_wrap.cxx

swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.i"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Wno-unused-but-set-variable -E /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swigPYTHON_wrap.cxx > CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.i

swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.s"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Wno-unused-but-set-variable -S /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swigPYTHON_wrap.cxx -o CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.s

swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o.requires:

.PHONY : swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o.requires

swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o.provides: swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o.requires
	$(MAKE) -f swig/CMakeFiles/_SetSystem_swig.dir/build.make swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o.provides.build
.PHONY : swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o.provides

swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o.provides.build: swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o


# Object files for target _SetSystem_swig
_SetSystem_swig_OBJECTS = \
"CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o"

# External object files for target _SetSystem_swig
_SetSystem_swig_EXTERNAL_OBJECTS =

swig/_SetSystem_swig.so: swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o
swig/_SetSystem_swig.so: swig/CMakeFiles/_SetSystem_swig.dir/build.make
swig/_SetSystem_swig.so: /usr/lib/x86_64-linux-gnu/libpython2.7.so
swig/_SetSystem_swig.so: lib/libgnuradio-SetSystem-1.0.0git.so.0.0.0
swig/_SetSystem_swig.so: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
swig/_SetSystem_swig.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
swig/_SetSystem_swig.so: /usr/local/lib/libgnuradio-runtime.so
swig/_SetSystem_swig.so: /usr/local/lib/libgnuradio-pmt.so
swig/_SetSystem_swig.so: /usr/lib/x86_64-linux-gnu/liblog4cpp.so
swig/_SetSystem_swig.so: swig/CMakeFiles/_SetSystem_swig.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared module _SetSystem_swig.so"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_SetSystem_swig.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
swig/CMakeFiles/_SetSystem_swig.dir/build: swig/_SetSystem_swig.so

.PHONY : swig/CMakeFiles/_SetSystem_swig.dir/build

swig/CMakeFiles/_SetSystem_swig.dir/requires: swig/CMakeFiles/_SetSystem_swig.dir/SetSystem_swigPYTHON_wrap.cxx.o.requires

.PHONY : swig/CMakeFiles/_SetSystem_swig.dir/requires

swig/CMakeFiles/_SetSystem_swig.dir/clean:
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && $(CMAKE_COMMAND) -P CMakeFiles/_SetSystem_swig.dir/cmake_clean.cmake
.PHONY : swig/CMakeFiles/_SetSystem_swig.dir/clean

swig/CMakeFiles/_SetSystem_swig.dir/depend: swig/SetSystem_swigPYTHON_wrap.cxx
swig/CMakeFiles/_SetSystem_swig.dir/depend: swig/SetSystem_swig.py
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/itupac/OutOfTree-gnuradio/gr-SetSystem /home/itupac/OutOfTree-gnuradio/gr-SetSystem/swig /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/CMakeFiles/_SetSystem_swig.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : swig/CMakeFiles/_SetSystem_swig.dir/depend
