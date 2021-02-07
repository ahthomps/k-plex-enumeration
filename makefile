.PHONY: all

all: main

main: optimized/graph_io.o optimized/bronKerbosch.o optimized/kplex.o optimized/kplex.o optimized/coreness.o optimized/cliqueness.o optimized/triangle.o tools/config.h main.cpp
	g++ optimized/graph_io.o optimized/bronKerbosch.o optimized/kplex.o optimized/coreness.o optimized/cliqueness.o optimized/triangle.o main.cpp -O3 -std=c++11 -o main

optimized/kplex.o: optimized/bronKerbosch.o tools/graph_tools.h kPlex/kplex.h kPlex/kplex.cpp
	g++ kPlex/kplex.cpp -c -std=c++11 -O3 -o optimized/kplex.o

optimized/bronKerbosch.o: bronKerbosch/bronKerbosch.cpp bronKerbosch/bronKerbosch.h
	g++ bronKerbosch/bronKerbosch.cpp -c -std=c++11 -O3 -o optimized/bronKerbosch.o

optimized/graph_io.o: graph_access/graph_io.cpp graph_access/graph_io.h graph_access/graph_access.h
	g++ graph_access/graph_io.cpp -c -std=c++11 -O3 -o optimized/graph_io.o

optimized/coreness.o: reductions/coreness.cpp reductions/coreness.h
	g++ reductions/coreness.cpp -c -std=c++11 -O3 -o optimized/coreness.o

optimized/cliqueness.o: reductions/cliqueness.cpp reductions/cliqueness.h
	g++ reductions/cliqueness.cpp -c -std=c++11 -O3 -o optimized/cliqueness.o

optimized/triangle.o: reductions/triangle.cpp reductions/triangle.h
	g++ reductions/triangle.cpp -c -std=c++11 -O3 -o optimized/triangle.o
