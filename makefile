.PHONY: all

all: main


main: graph_io.o bronKerbosch.o main.cpp
	g++ graph_io.o bronKerbosch.o main.cpp -std=c++11 -Werror=all -o main

bronKerbosch.o: bronKerbosch.cpp bronKerbosch.h
	g++ bronKerbosch.cpp -c -std=c++11

graph_io.o: graph_access/graph_io.cpp graph_access/graph_io.h graph_access/graph_access.h graph_access/definitions.h graph_access/macros_assertions.h graph_access/macros_common.h
	g++ graph_access/graph_io.cpp -c -std=c++11
