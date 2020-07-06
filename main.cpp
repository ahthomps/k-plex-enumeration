#include <iostream>
#include <vector>
#include <string>

#include "tools/timer.h"
#include "graph_access/graph_io.h"
#include "bronKerbosch/bronKerbosch.h"
#include "kPlex/kplex.h"


std::vector<std::vector<int>> buildAdjG(graph_access &G) {
    std::vector<std::vector<int>> adj;
    forall_nodes(G, v) {
        std::vector<int> neighbors;
        forall_out_edges(G, e, v) {
            neighbors.push_back(static_cast<int>(G.getEdgeTarget(e)));
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
  std::vector<std::vector<int>> adj = buildAdjG(G);

  timer t;

  // auto square = [&](int i)
  //   {
  //       return i * i;
  //   };
  //
  // std::cout << "Square of 5 is : " << square(5) << std::endl;

  // BronKerbosch algo(&adj);
  // algo.solve();
  // std::cout << filename << " " << algo.get_clique_counter() << " " << t.elapsed() << std::endl;

  // std::cout << filename << " " << adj.size() << std::endl;
  //
  KPlex kplex(&adj);
  kplex.get_two_plexes();
  std::cout << filename << " " << kplex.get_kplex_counter() << " " << t.elapsed() << std::endl;

  return 0;
}
