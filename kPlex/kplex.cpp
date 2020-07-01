#include <iostream>
#include <vector>

#include "kplex.h"
#include "../tools/fast_set.h"
#include "../bronKerbosch/bronKerbosch.h"

KPlex::KPlex(std::vector<std::vector<int>> &adj) {
  _adj.swap(adj);
  _N = _adj.size();
  used.set_fast_set(_N);

  std::vector<std::vector<int>> adj_copy = _adj;
  maximal_clique_algo = new BronKerbosch(adj_copy);
  maximal_clique_algo->reportClique = reportOneNearClique;
}

KPlex::~KPlex() {
  delete maximal_clique_algo;
}

void KPlex::OneNearCliques() {

  for (int node1 = 0; node1 < _adj.size() - 1; node1++) {
    used.clear();
    for (int v : _adj[node1]) used.add(v);
    for (int node2 = node1 + 1; node2 < _adj.size(); node2++) {

      if (used.get(node2)) continue;

      // find common neighbors
      std::vector<int> common_neighbors;
      for (int v : _adj[node2]) if (used.get(v)) common_neighbors.push_back(v);

      if (common_neighbors.size() == 0) one_near_cliques_counter++;
      else {
        maximal_clique_algo->solveOn(common_neighbors);
        one_near_cliques_counter += maximal_clique_algo->cliqueCounter;
      }
    }
  }
}
