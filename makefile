.PHONY: all

all: main

main: optimized/graph_io.o optimized/bronKerbosch.o optimized/kplex.o optimized/kplex.o optimized/coreness.o tools/config.h main.cpp
	g++ optimized/graph_io.o optimized/bronKerbosch.o optimized/kplex.o optimized/coreness.o main.cpp -O3 -std=c++11 -Werror=all -o main

optimized/kplex.o: optimized/bronKerbosch.o tools/graph_tools.h kPlex/kplex.h kPlex/kplex.cpp
	g++ kPlex/kplex.cpp -c -std=c++11 -O3 -o optimized/kplex.o

optimized/bronKerbosch.o: bronKerbosch/bronKerbosch.cpp bronKerbosch/bronKerbosch.h
	g++ bronKerbosch/bronKerbosch.cpp -c -std=c++11 -O3 -o optimized/bronKerbosch.o

optimized/graph_io.o: graph_access/graph_io.cpp graph_access/graph_io.h graph_access/graph_access.h
	g++ graph_access/graph_io.cpp -c -std=c++11 -O3 -o optimized/graph_io.o

optimized/coreness.o: reductions/coreness.cpp reductions/coreness.h tools/linked_list.h
	g++ reductions/coreness.cpp -c -std=c++11 -O3 -o optimized/coreness.o
