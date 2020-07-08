#include <iostream>
#include <vector>
#include <functional>

#include "kplex.h"
#include "../tools/fast_set.h"
#include "../tools/config.h"
#include "../bronKerbosch/bronKerbosch.h"

KPlex::KPlex(std::vector<std::vector<int>> const *adj, Config &config) :
  _adj(*adj)
{
  _N = _adj.size();
  _used.set_fast_set(_N);
  _enumerate_connected_two_plex = config.CONN_ONE_NR_CLQ;

  _maximal_clique_algo = new BronKerbosch(&_adj, config);
}

KPlex::~KPlex() {
  delete _maximal_clique_algo;
}

size_t KPlex::get_kplex_counter() {
  return _kplex_counter;
}

void KPlex::get_one_near_cliques() {

  for (size_t node1 = 0; node1 < _adj.size() - 1; node1++) {
    _used.clear();
    for (int const v : _adj[node1]) _used.add(v);

    for (size_t node2 = node1 + 1; node2 < _adj.size(); node2++) {

      if (_used.get(node2)) continue;

      std::vector<int> common_neighbors;
      for (int const v : _adj[node2]) if (_used.get(v)) common_neighbors.push_back(v);

      if (common_neighbors.empty()) _kplex_counter++;
      else {

        _maximal_clique_algo->solve_on(common_neighbors);
        _kplex_counter += _maximal_clique_algo->_clique_counter;
      }
    }
  }
}

void KPlex::get_one_near_cliques_connected() {

  for (size_t node = 0; node < _adj.size(); node++) {

      // mark all of the vertices in N[node]
      _used.clear();
      _used.add(node);
      for (int const v : _adj[node]) _used.add(v);

      // get the 2 neighborhood of node
      std::vector<int> two_neighborhood_node;
      for (int const node_neighbor : _adj[node]) {
        for (int const node_2_neighbor : _adj[node_neighbor]) {
          if (_used.get(node_2_neighbor) || node_2_neighbor < node) continue;
          two_neighborhood_node.push_back(node_2_neighbor);
          _used.add(node_2_neighbor);
        }
      }

      _used.clear();
      for (int const v : _adj[node]) _used.add(v);

      for (int const two_neighbor : two_neighborhood_node) {
        std::vector<int> common_neighbors;
        for (int const v : _adj[two_neighbor]) if (_used.get(v)) common_neighbors.push_back(v);

        if (common_neighbors.empty()) _kplex_counter++;
        else {
          _maximal_clique_algo->solve_on(common_neighbors);
          _kplex_counter += _maximal_clique_algo->_clique_counter;
        }
      }
  }
}

void KPlex::get_two_plexes() {

  if (_enumerate_connected_two_plex) get_one_near_cliques_connected();
  else {
    get_one_near_cliques();
  }


  std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>)> bruteforce_check = [&] (std::vector<std::vector<int>> const * p_adj, std::vector<int> R, std::vector<int> level_set_one) -> bool {
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

  std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>)> optimized_check = [&] (std::vector<std::vector<int>> const * p_adj, std::vector<int> R, std::vector<int> level_set_one) -> bool {
    std::vector<std::vector<int>> const &adj = *p_adj;

    if (R.size() < 2) return true;

    _used.clear();
    for (int const r : R) _used.add(r);

    for (int const clique_node : {R[0], R[1]}) {
      for (int const clique_node_neighbor : adj[clique_node]) {
        if (_used.get(clique_node_neighbor)) continue;
        size_t neighbors_in_clique = 0;
        for (int const neighbor : adj[clique_node_neighbor]) if (_used.get(neighbor)) neighbors_in_clique++;
        if (R.size() - 1 == neighbors_in_clique) return false;
      }
    }
    return true;
  };

  std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>)> level_set_one_check = [&] (std::vector<std::vector<int>> const * p_adj, std::vector<int> R, std::vector<int> level_set_one) -> bool {
    return R.size() < 2 || level_set_one.empty();
  };

  _maximal_clique_algo->solve(level_set_one_check);
  _kplex_counter += _maximal_clique_algo->get_clique_counter();
}
