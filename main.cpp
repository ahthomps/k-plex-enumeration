#include <iostream>
#include <vector>
#include <string>

#include "timer.h"
#include "graph_access/graph_io.h"
#include "bronKerbosch.h"

std::vector<std::vector<int>> buildAdjG(graph_access &G) {
    std::vector<std::vector<int>> adj;
    forall_nodes(G, v) {
        std::vector<int> neighbors;
        forall_out_edges(G, e, v) {
            neighbors.push_back((int) G.getEdgeTarget(e));
        } endfor
        adj.push_back(neighbors);
    } endfor
    return adj;
}

int main(int argn, char **argv) {

  if (argn < 2) {
    std::cout << "Cannot find graph" << std::endl;
    exit(1);
  }

  graph_access G;
  std::string filename = argv[1];
  graph_io::readGraphWeighted(G, filename);
  std::vector<std::vector<int>> connected = buildAdjG(G);

  timer t;

  BronKerbosch algo(connected);
  algo.solveFixP();
  std::cout << filename << " " << algo.cliqueCounter << " " << t.elapsed() << std::endl;

  // algo.testFixP();

  return 0;
}
