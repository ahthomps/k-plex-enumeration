#include <iostream>
#include <vector>
#include <functional>

#include "kplex.h"
#include "../tools/fast_set.h"
#include "../bronKerbosch/bronKerbosch.h"

KPlex::KPlex(std::vector<std::vector<int>> const *adj) :
  _adj(*adj)
{
  _N = _adj.size();
  _used.set_fast_set(_N);

  _maximal_clique_algo = new BronKerbosch(&_adj);
}

KPlex::~KPlex() {
  delete _maximal_clique_algo;
}

void KPlex::one_near_cliques() {

  for (int node1 = 0; node1 < _adj.size() - 1; node1++) {
    _used.clear();
    for (int const v : _adj[node1]) _used.add(v);

    for (int node2 = node1 + 1; node2 < _adj.size(); node2++) {

      if (_used.get(node2)) continue;

      std::vector<int> common_neighbors;
      for (int const v : _adj[node2]) if (_used.get(v)) common_neighbors.push_back(v);

      if (common_neighbors.empty()) _one_near_cliques_counter++;
      else {

        _maximal_clique_algo->solve_on(common_neighbors);
        _one_near_cliques_counter += _maximal_clique_algo->_clique_counter;
      }
    }
  }
}

void KPlex::two_plexes() {

  one_near_cliques();

  std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>)> check1 = [&] (std::vector<std::vector<int>> const * p_adj, std::vector<int> R) -> bool {
    std::vector<std::vector<int>> const &adj = *p_adj;

    if (R.size() < 2) return true;

    _used.clear();
    for (int const r : R) _used.add(r);

    for (size_t node = 0; node < adj.size(); node ++) {
      if (_used.get(node)) continue;
      size_t neighbors_in_clique = 0;
      for (int const neighbor : adj[node]) if (_used.get(neighbor)) neighbors_in_clique++;
      if (R.size() - 1 == neighbors_in_clique) return false;
    }
    return true;
  };

  _maximal_clique_algo->solve(check1);
  _one_near_cliques_counter += _maximal_clique_algo->_clique_counter;
}
