CFLAGS = -std=c++11 -O3

.PHONY: all

all: main

main: optimized/graph_io.o optimized/bronKerbosch.o optimized/kplex.o optimized/kplex.o optimized/coreness.o optimized/MemoryManager.o optimized/Algorithm.o optimized/Tools.o optimized/DegeneracyTools.o optimized/DegeneracyAlgorithm.o optimized/cliqueness.o optimized/triangle.o optimized/four_cliques.o tools/config.h main.cpp
	g++ optimized/graph_io.o optimized/bronKerbosch.o optimized/kplex.o optimized/coreness.o optimized/MemoryManager.o optimized/Algorithm.o optimized/Tools.o optimized/DegeneracyTools.o optimized/DegeneracyAlgorithm.o optimized/cliqueness.o optimized/triangle.o optimized/four_cliques.o  main.cpp $(CFLAGS) -o main

optimized/kplex.o: optimized/bronKerbosch.o tools/graph_tools.h kPlex/kplex.h kPlex/kplex.cpp
	g++ kPlex/kplex.cpp -c $(CFLAGS) -o optimized/kplex.o

optimized/bronKerbosch.o: bronKerbosch/bronKerbosch.cpp bronKerbosch/bronKerbosch.h
	g++ bronKerbosch/bronKerbosch.cpp -c $(CFLAGS) -o optimized/bronKerbosch.o

optimized/graph_io.o: graph_access/graph_io.cpp graph_access/graph_io.h graph_access/graph_access.h
	g++ graph_access/graph_io.cpp -c $(CFLAGS) -o optimized/graph_io.o

optimized/coreness.o: reductions/coreness.cpp reductions/coreness.h
	g++ reductions/coreness.cpp -c $(CFLAGS) -o optimized/coreness.o

optimized/cliqueness.o: reductions/cliqueness.cpp reductions/cliqueness.h
	g++ reductions/cliqueness.cpp -c $(CFLAGS) -o optimized/cliqueness.o

optimized/triangle.o: reductions/triangle.cpp reductions/triangle.h
	g++ reductions/triangle.cpp -c $(CFLAGS) -o optimized/triangle.o

optimized/four_cliques.o: reductions/four_cliques.cpp reductions/four_cliques.h
	g++ reductions/four_cliques.cpp -c $(CFLAGS) -o optimized/four_cliques.o

optimized/MemoryManager.o: quick-cliques/MemoryManager.cpp quick-cliques/MemoryManager.h
	g++ quick-cliques/MemoryManager.cpp -Winline -O2 -std=c++11 -g -DALLOW_ALLOC_ZERO_BYTES -c -o optimized/MemoryManager.o

optimized/Algorithm.o: quick-cliques/Algorithm.cpp quick-cliques/Algorithm.h
	g++ quick-cliques/Algorithm.cpp -Winline -O2 -std=c++11 -g -DALLOW_ALLOC_ZERO_BYTES -c -o optimized/Algorithm.o

optimized/Tools.o: quick-cliques/Tools.cpp quick-cliques/Tools.h
	g++ quick-cliques/Tools.cpp -Winline -O2 -std=c++11 -g -DALLOW_ALLOC_ZERO_BYTES -c -o optimized/Tools.o

optimized/DegeneracyTools.o: quick-cliques/DegeneracyTools.cpp quick-cliques/DegeneracyTools.h
	g++ quick-cliques/DegeneracyTools.cpp -Winline -O2 -std=c++11 -g -DALLOW_ALLOC_ZERO_BYTES -c -o optimized/DegeneracyTools.o

optimized/DegeneracyAlgorithm.o: quick-cliques/DegeneracyAlgorithm.cpp quick-cliques/DegeneracyAlgorithm.h
	g++ quick-cliques/DegeneracyAlgorithm.cpp -Winline -O2 -std=c++11 -g -DALLOW_ALLOC_ZERO_BYTES -c -o optimized/DegeneracyAlgorithm.o