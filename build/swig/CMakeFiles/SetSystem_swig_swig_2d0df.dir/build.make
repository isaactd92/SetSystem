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
include swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/depend.make

# Include the progress variables for this target.
include swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/progress.make

# Include the compile flags for this target's objects.
include swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/flags.make

swig/SetSystem_swig_swig_2d0df.cpp: ../swig/SetSystem_swig.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/tagged_stream_block.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/gnuradio.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/realtime.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/block.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/block_detail.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/constants.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/sync_block.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/gr_shared_ptr.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/block_gateway.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/sync_interpolator.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/gr_types.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/basic_block.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/gr_ctrlport.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/io_signature.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/top_block.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/gr_extras.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/message.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/tags.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/msg_handler.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/runtime_swig.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/msg_queue.i
swig/SetSystem_swig_swig_2d0df.cpp: swig/SetSystem_swig_doc.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/buffer.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/gr_swig_block_magic.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/hier_block2.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/runtime_swig_doc.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/feval.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/sync_decimator.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/gr_logger.i
swig/SetSystem_swig_swig_2d0df.cpp: ../swig/SetSystem_swig.i
swig/SetSystem_swig_swig_2d0df.cpp: /usr/local/include/gnuradio/swig/prefs.i
swig/SetSystem_swig_swig_2d0df.cpp: swig/SetSystem_swig.tag
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/cmake -E copy /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig_swig_2d0df.cpp.in /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig_swig_2d0df.cpp

swig/SetSystem_swig_doc.i: swig/SetSystem_swig_doc_swig_docs/xml/index.xml
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating python docstrings for SetSystem_swig_doc"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/docs/doxygen && /usr/bin/python2 -B /home/itupac/OutOfTree-gnuradio/gr-SetSystem/docs/doxygen/swig_doc.py /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig_doc_swig_docs/xml /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig_doc.i

swig/SetSystem_swig.tag: swig/_SetSystem_swig_swig_tag
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating SetSystem_swig.tag"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && ./_SetSystem_swig_swig_tag
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/cmake -E touch /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig.tag

swig/SetSystem_swig_doc_swig_docs/xml/index.xml: swig/_SetSystem_swig_doc_tag
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating doxygen xml for SetSystem_swig_doc docs"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && ./_SetSystem_swig_doc_tag
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/doxygen /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig_doc_swig_docs/Doxyfile

swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o: swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/flags.make
swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o: swig/SetSystem_swig_swig_2d0df.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o -c /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig_swig_2d0df.cpp

swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.i"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig_swig_2d0df.cpp > CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.i

swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.s"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swig_swig_2d0df.cpp -o CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.s

swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o.requires:

.PHONY : swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o.requires

swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o.provides: swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o.requires
	$(MAKE) -f swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/build.make swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o.provides.build
.PHONY : swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o.provides

swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o.provides.build: swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o


# Object files for target SetSystem_swig_swig_2d0df
SetSystem_swig_swig_2d0df_OBJECTS = \
"CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o"

# External object files for target SetSystem_swig_swig_2d0df
SetSystem_swig_swig_2d0df_EXTERNAL_OBJECTS =

swig/SetSystem_swig_swig_2d0df: swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o
swig/SetSystem_swig_swig_2d0df: swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/build.make
swig/SetSystem_swig_swig_2d0df: swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable SetSystem_swig_swig_2d0df"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SetSystem_swig_swig_2d0df.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Swig source"
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/cmake -E make_directory /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && /usr/bin/swig3.0 -python -fvirtual -modern -keyword -w511 -module SetSystem_swig -I/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig -I/home/itupac/OutOfTree-gnuradio/gr-SetSystem/swig -I/usr/local/include/gnuradio/swig -I/usr/include/python2.7 -I/usr/include/python2.7 -outdir /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig -c++ -I/home/itupac/OutOfTree-gnuradio/gr-SetSystem/lib -I/home/itupac/OutOfTree-gnuradio/gr-SetSystem/include -I/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/lib -I/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/include -I/usr/include -I/usr/include -I/usr/local/include -I/home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig -I/home/itupac/OutOfTree-gnuradio/gr-SetSystem/swig -I/usr/local/include/gnuradio/swig -I/usr/include/python2.7 -I/usr/include/python2.7 -o /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/SetSystem_swigPYTHON_wrap.cxx /home/itupac/OutOfTree-gnuradio/gr-SetSystem/swig/SetSystem_swig.i

# Rule to build all files generated by this target.
swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/build: swig/SetSystem_swig_swig_2d0df

.PHONY : swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/build

swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/requires: swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/SetSystem_swig_swig_2d0df.cpp.o.requires

.PHONY : swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/requires

swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/clean:
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig && $(CMAKE_COMMAND) -P CMakeFiles/SetSystem_swig_swig_2d0df.dir/cmake_clean.cmake
.PHONY : swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/clean

swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/depend: swig/SetSystem_swig_swig_2d0df.cpp
swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/depend: swig/SetSystem_swig_doc.i
swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/depend: swig/SetSystem_swig.tag
swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/depend: swig/SetSystem_swig_doc_swig_docs/xml/index.xml
	cd /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/itupac/OutOfTree-gnuradio/gr-SetSystem /home/itupac/OutOfTree-gnuradio/gr-SetSystem/swig /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig /home/itupac/OutOfTree-gnuradio/gr-SetSystem/build/swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : swig/CMakeFiles/SetSystem_swig_swig_2d0df.dir/depend

