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
include CMakeFiles/libclustering.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libclustering.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libclustering.dir/flags.make

CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.o: ../lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp

CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp > CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.i

CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp -o CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.s

CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.o: ../lib/parallel_mh_clustering/population_clustering.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/parallel_mh_clustering/population_clustering.cpp

CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/parallel_mh_clustering/population_clustering.cpp > CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.i

CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/parallel_mh_clustering/population_clustering.cpp -o CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.s

CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.o: ../lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp

CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp > CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.i

CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp -o CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.s

CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.o: ../lib/tools/graph_communication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/tools/graph_communication.cpp

CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/tools/graph_communication.cpp > CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.i

CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/tools/graph_communication.cpp -o CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.s

CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.o: ../lib/clustering/louvainmethod.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/louvainmethod.cpp

CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/louvainmethod.cpp > CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.i

CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/louvainmethod.cpp -o CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.s

CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.o: ../lib/clustering/labelpropagation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/labelpropagation.cpp

CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/labelpropagation.cpp > CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.i

CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/labelpropagation.cpp -o CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.s

CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.o: ../lib/clustering/neighborhood.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/neighborhood.cpp

CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/neighborhood.cpp > CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.i

CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/neighborhood.cpp -o CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.s

CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.o: ../lib/clustering/coarsening/coarsening.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/coarsening/coarsening.cpp

CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/coarsening/coarsening.cpp > CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.i

CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/coarsening/coarsening.cpp -o CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.s

CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.o: ../lib/clustering/coarsening/contractor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/coarsening/contractor.cpp

CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/coarsening/contractor.cpp > CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.i

CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/clustering/coarsening/contractor.cpp -o CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.s

CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.o: ../lib/logging/bexception.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/logging/bexception.cpp

CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/logging/bexception.cpp > CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.i

CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/logging/bexception.cpp -o CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.s

CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.o: ../lib/tools/modularitymetric.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/tools/modularitymetric.cpp

CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/tools/modularitymetric.cpp > CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.i

CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/tools/modularitymetric.cpp -o CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.s

CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.o: CMakeFiles/libclustering.dir/flags.make
CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.o: ../lib/tools/mpi_tools.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.o"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.o -c /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/tools/mpi_tools.cpp

CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.i"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/tools/mpi_tools.cpp > CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.i

CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.s"
	/usr/local/bin/g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/almathompson/Research/k-plex-enumeration/VieClus/lib/tools/mpi_tools.cpp -o CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.s

libclustering: CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/parallel_mh_async_clustering.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/population_clustering.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/parallel_mh_clustering/exchange/exchanger_clustering.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/tools/graph_communication.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/clustering/louvainmethod.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/clustering/labelpropagation.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/clustering/neighborhood.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/clustering/coarsening/coarsening.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/clustering/coarsening/contractor.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/logging/bexception.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/tools/modularitymetric.cpp.o
libclustering: CMakeFiles/libclustering.dir/lib/tools/mpi_tools.cpp.o
libclustering: CMakeFiles/libclustering.dir/build.make

.PHONY : libclustering

# Rule to build all files generated by this target.
CMakeFiles/libclustering.dir/build: libclustering

.PHONY : CMakeFiles/libclustering.dir/build

CMakeFiles/libclustering.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libclustering.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libclustering.dir/clean

CMakeFiles/libclustering.dir/depend:
	cd /Users/almathompson/Research/k-plex-enumeration/VieClus/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/almathompson/Research/k-plex-enumeration/VieClus /Users/almathompson/Research/k-plex-enumeration/VieClus /Users/almathompson/Research/k-plex-enumeration/VieClus/build /Users/almathompson/Research/k-plex-enumeration/VieClus/build /Users/almathompson/Research/k-plex-enumeration/VieClus/build/CMakeFiles/libclustering.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libclustering.dir/depend

