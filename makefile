.PHONY: all

all: main

main: optimized/graph_io.o optimized/bronKerbosch.o main.cpp
	g++ optimized/graph_io.o optimized/bronKerbosch.o main.cpp -std=c++11 -Werror=all -o main

optimized/bronKerbosch.o: bronKerbosch/bronKerbosch.cpp bronKerbosch/bronKerbosch.h
	g++ bronKerbosch/bronKerbosch.cpp -c -std=c++11 -o optimized/bronKerbosch.o

optimized/graph_io.o: graph_access/graph_io.cpp graph_access/graph_io.h graph_access/graph_access.h
	g++ graph_access/graph_io.cpp -c -std=c++11 -o optimized/graph_io.o
