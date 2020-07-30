#include <iostream>
#include <vector>
#include <string>

#include "tools/timer.h"
#include "tools/config.h"
#include "tools/linked_list.h"
#include "graph_access/graph_io.h"
#include "bronKerbosch/bronKerbosch.h"
#include "kPlex/kplex.h"

#include "reductions/coreness.h"

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

  CorenessReduction coreness(&adj);
  // std::vector<bool>* p_nodes_status = coreness.reduce(2);
  std::vector<bool>* p_nodes_status = NULL;
  // std::cout << p_nodes_status << std::endl;
  // exit(0);

  // std::cout << "1: ";
  // for (int v : adj[1]) std::cout << v << ", ";
  // std::cout << std::endl;
  // std::cout << "4: ";
  // for (int v : adj[4]) std::cout << v << ", ";
  // std::cout << std::endl;
  // std::cout << "42: ";
  // for (int v : adj[42]) std::cout << v << ", ";
  // std::cout << std::endl;
  // std::cout << "328: ";
  // for (int v : adj[328]) std::cout << v << ", ";
  // std::cout << std::endl;
  //
  // return 1;

  timer t;

  if (config.TEST && !config.RPT_CLQ) {
      std::cout << "must add '--RPT_CLQ' flag when testing" << std::endl;
      exit(0);
  }
  if (config.MAX_CLQ && config.WRT_3PLX) {
      KPlex kplex(&adj, config);
      kplex.get_maximal_cliques_wrt_three_plexes();
      if (!config.TEST) std::cout << filename << " " << kplex.get_kplex_counter() << " " << t.elapsed() << std::endl;
  }
  else if (config.MAX_CLQ) {
    BronKerbosch algo(&adj, config, p_nodes_status);
    algo.solve();
    if (!config.TEST) std::cout << filename << " " << algo.get_clique_counter() << " " << t.elapsed() << std::endl;
  }

  else {
    KPlex kplex(&adj, config);
    if (config.TWOPLX) {
      kplex.get_two_plexes();
    }
    else if (config.CONN_ONE_NR_CLQ) {
      kplex.get_one_near_cliques_connected();
    }
    else if (config.ONE_NR_CLQ && config.WRT_3PLX) {
        kplex.get_one_near_cliques_wrt_three_plexes();
    }
    else if (config.ONE_NR_CLQ) {
      kplex.get_one_near_cliques();
    }
    else if (config.TWO_NR_CLQ) {
      kplex.get_two_near_cliques();
    }
    else if (config.THREEPLX) {
        kplex.get_three_plexes();
    }
    else if (config.CONN_TWO_NR_CLQ) {
        kplex.get_two_near_cliques_connected();
    }
    if (!config.TEST) {
        std::cout << filename << " " << kplex.get_kplex_counter() << " " << t.elapsed() << std::endl;
    }
  }

  return 0;
}
