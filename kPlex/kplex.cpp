#include <iostream>
#include <vector>

#include "kplex.h"
#include "../tools/fast_set.h"
#include "../bronKerbosch/bronKerbosch.h"

KPlex::KPlex(std::vector<std::vector<int>> &_adj) {
  adj.swap(_adj);
  N = adj.size();
  adj_bool.resize(N, false);
  used.set_fast_set(N);
  save_indices.resize(N, -1);
}

void KPlex::OneNearCliques() {

  for (int node1 = 0; node1 < adj.size() - 1; node1++) {
    used.clear();
    for (int v : adj[node1]) used.add(v);
    for (int node2 = node1 + 1; node2 < adj.size(); node2++) {

      if (used.get(node2)) continue;

      // find common neighborhood
      std::vector<int> common_neighbors;
      for (int v : adj[node2]) {
        if (used.get(v)) {                                                      // used.get(v) then v \in N(node1)
          save_indices[v] = common_neighbors.size();
          common_neighbors.push_back(v);
        }
      }
      std::vector<std::vector<int>> common_neighborhood;
      std::vector<int> adj_list;
      for (int v : common_neighbors) {
        adj_list.clear();
        for (int u : adj[v]) if (save_indices[u] != -1) adj_list.push_back(save_indices[u]);
      }

      BronKerbosch maximal_clique_algo(common_neighborhood);
      maximal_clique_algo.reportClique = reportOneNearClique;
      maximal_clique_algo.solve();

      one_near_cliques_counter += maximal_clique_algo.cliqueCounter;

      for (int v : common_neighbors) save_indices[v] = -1;
    }
  }
}
