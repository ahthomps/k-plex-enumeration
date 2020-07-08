#include <iostream>
#include <vector>
#include <string>

#include "tools/timer.h"
#include "tools/config.h"
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

  Config config(argn, argv);

  graph_access G;
  std::string filename = argv[1];
  graph_io::readGraphWeighted(G, filename);
  std::vector<std::vector<int>> adj = buildAdjG(G);

  timer t;

  if (config.MAX_CLQ) {
    BronKerbosch algo(&adj, config);
    algo.solve();
    std::cout << filename << " " << algo.get_clique_counter() << " " << t.elapsed() << std::endl;
  }

  else {
    KPlex kplex(&adj, config);
    if (config.TWOPLX) {
      kplex.get_two_plexes();
    }
    else if (config.CONN_ONE_NR_CLQ) {
      kplex.get_one_near_cliques_connected();
    }
    else if (config.ONE_NR_CLQ) {
      kplex.get_one_near_cliques();
    }
    std::cout << filename << " " << kplex.get_kplex_counter() << " " << t.elapsed() << std::endl;

  }

  return 0;
}
