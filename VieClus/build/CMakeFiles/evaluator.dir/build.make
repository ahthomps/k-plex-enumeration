# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/almathompson/Research/k-plex-enumeration/VieClus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/almathompson/Research/k-plex-enumeration/VieClus/build

# Include any dependencies generated for this target.
include CMakeFiles/evaluator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/evaluator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/evaluator.dir/flags.make

CMakeFiles/evaluator.dir/app/evaluator.cpp.o: CMakeFiles/evaluator.dir/flags.make
CMakeFiles/evaluator.dir/app/evaluator.cpp.o: ../app/evaluator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/evaluator.dir/app/evaluator.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/evaluator.dir/app/evaluator.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/app/evaluator.cpp

CMakeFiles/evaluator.dir/app/evaluator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evaluator.dir/app/evaluator.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/app/evaluator.cpp > CMakeFiles/evaluator.dir/app/evaluator.cpp.i

CMakeFiles/evaluator.dir/app/evaluator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evaluator.dir/app/evaluator.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/app/evaluator.cpp -o CMakeFiles/evaluator.dir/app/evaluator.cpp.s

# Object files for target evaluator
evaluator_OBJECTS = \
"CMakeFiles/evaluator.dir/app/evaluator.cpp.o"

# External object files for target evaluator
evaluator_EXTERNAL_OBJECTS = \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libeval.dir/extern/KaHIP/lib/data_structure/graph_hierarchy.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libeval.dir/extern/KaHIP/lib/io/graph_io.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libeval.dir/extern/KaHIP/lib/tools/quality_metrics.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libeval.dir/extern/KaHIP/lib/tools/random_functions.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libeval.dir/extern/KaHIP/lib/partition/coarsening/matching/matching.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libeval.dir/extern/KaHIP/lib/partition/coarsening/clustering/node_ordering.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libeval.dir/extern/KaHIP/lib/partition/coarsening/clustering/size_constraint_label_propagation.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libeval.dir/lib/logging/bexception.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libeval.dir/extern/argtable3-3.0.3/argtable3.c.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libpadygrcl.dir/lib/clustering/louvainmethod.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libpadygrcl.dir/lib/clustering/labelpropagation.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libpadygrcl.dir/lib/clustering/neighborhood.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libpadygrcl.dir/lib/clustering/coarsening/contractor.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libpadygrcl.dir/lib/clustering/coarsening/coarsening.cpp.o" \
"/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libpadygrcl.dir/lib/tools/modularitymetric.cpp.o"

evaluator: CMakeFiles/evaluator.dir/app/evaluator.cpp.o
evaluator: CMakeFiles/libeval.dir/extern/KaHIP/lib/data_structure/graph_hierarchy.cpp.o
evaluator: CMakeFiles/libeval.dir/extern/KaHIP/lib/io/graph_io.cpp.o
evaluator: CMakeFiles/libeval.dir/extern/KaHIP/lib/tools/quality_metrics.cpp.o
evaluator: CMakeFiles/libeval.dir/extern/KaHIP/lib/tools/random_functions.cpp.o
evaluator: CMakeFiles/libeval.dir/extern/KaHIP/lib/partition/coarsening/matching/matching.cpp.o
evaluator: CMakeFiles/libeval.dir/extern/KaHIP/lib/partition/coarsening/clustering/node_ordering.cpp.o
evaluator: CMakeFiles/libeval.dir/extern/KaHIP/lib/partition/coarsening/clustering/size_constraint_label_propagation.cpp.o
evaluator: CMakeFiles/libeval.dir/lib/logging/bexception.cpp.o
evaluator: CMakeFiles/libeval.dir/extern/argtable3-3.0.3/argtable3.c.o
evaluator: CMakeFiles/libpadygrcl.dir/lib/clustering/louvainmethod.cpp.o
evaluator: CMakeFiles/libpadygrcl.dir/lib/clustering/labelpropagation.cpp.o
evaluator: CMakeFiles/libpadygrcl.dir/lib/clustering/neighborhood.cpp.o
evaluator: CMakeFiles/libpadygrcl.dir/lib/clustering/coarsening/contractor.cpp.o
evaluator: CMakeFiles/libpadygrcl.dir/lib/clustering/coarsening/coarsening.cpp.o
evaluator: CMakeFiles/libpadygrcl.dir/lib/tools/modularitymetric.cpp.o
evaluator: CMakeFiles/evaluator.dir/build.make
evaluator: /usr/local/Cellar/open-mpi/4.1.0/lib/libmpi.dylib
evaluator: /usr/local/Cellar/gcc/10.2.0_4/lib/gcc/10/libgomp.dylib
evaluator: CMakeFiles/evaluator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable evaluator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/evaluator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/evaluator.dir/build: evaluator

.PHONY : CMakeFiles/evaluator.dir/build

CMakeFiles/evaluator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/evaluator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/evaluator.dir/clean

CMakeFiles/evaluator.dir/depend:
	cd /Users/almathompson/Research/k-plex-enumeration/VieClus/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/almathompson/Research/k-plex-enumeration/VieClus /Users/almathompson/Research/k-plex-enumeration/VieClus /Users/almathompson/Research/k-plex-enumeration/VieClus/build /Users/almathompson/Research/k-plex-enumeration/VieClus/build /Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/evaluator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/evaluator.dir/depend

