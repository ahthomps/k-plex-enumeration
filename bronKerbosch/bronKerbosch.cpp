#include <iostream>
#include <vector>
#include <functional>

#include "bronKerbosch.h"
#include "../tools/fast_set.h"
#include "../tools/config.h"

BronKerbosch::BronKerbosch(std::vector<std::vector<int>> const *adj, Config &config, std::vector<bool> const *p_nodes_status) :
  _adj(*adj), _p_nodes_status(p_nodes_status)
{
  _N = _adj.size();
  _used.set_fast_set(_N);

  _report_clique = config.RPT_CLQ;
}

size_t BronKerbosch::get_clique_counter() {
  return _clique_counter;
}

void BronKerbosch::solve(std::function<bool(std::vector<std::vector<int>>const *, std::vector<int>, std::vector<int>, std::vector<int>)> check, bool find_level_sets) {
    std::vector<int> P;
    if (_p_nodes_status != NULL) {
        for (size_t i = 0; i < _N; i++) {
            if ((*_p_nodes_status)[i]) P.push_back(static_cast<int>(i));
        }
    }
    else {
        for (int i = 0; i < static_cast<int>(_N); i++) P.push_back(i);
    }
    std::vector<int> R;

    solve_on(P, R, check, find_level_sets);
}

void BronKerbosch::solve_on(std::vector<int> &P, std::vector<int> R, std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> check, bool find_level_sets) {
  std::vector<int> X;
  std::vector<int> level_set_one;
  std::vector<int> level_set_two;
  _find_level_sets = find_level_sets;

  if (_find_level_sets && !R.empty()) {
      // find all vertices missing one edge to R
      _used.clear();
      for (int const r : R) _used.add(r);

      std::vector<int> missing_one_edge;
      for (int const clique_node : {R[0], R[1]}) {
          for (int const clique_node_neighbor : _adj[clique_node]) {
              if (_used.get(clique_node_neighbor)) continue;
              size_t neighbors_in_clique = 0;
              for (int const neighbor : _adj[clique_node_neighbor]) if (_used.get(neighbor)) neighbors_in_clique++;
              if (R.size() - 1 == neighbors_in_clique) missing_one_edge.push_back(clique_node_neighbor);
          }
      }
      _used.clear();
      for (int const v : missing_one_edge) {
          if (!_used.get(v)) {
              _used.add(v);
              level_set_one.push_back(v);
          }
      }
  }

  _clique_counter = 0;

  solve_recursion(P, R, X, level_set_one, level_set_two, check);
}

void BronKerbosch::solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X, std::vector<int> const &level_set_one, std::vector<int> const &level_set_two, std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> check) {
    if (P.empty() && X.empty() && !R.empty() && check(&_adj, R, level_set_one, level_set_two)) {
        _clique_counter++;
        if (_report_clique) {
            std::cout << ' ';
            for (int const r : R) std::cout << r << ',';
            std::cout << ' ' << std::endl;
        }
        return;
    }
    if (P.empty()) return;

    std::vector<int> pivot_non_neighbors;
    get_pivot_non_neighbors(P, X, pivot_non_neighbors);

    size_t pivot_nn_index = 0;
    for (int const pivot_nn : pivot_non_neighbors) {
        _used.clear();
        for (int const neighbor : _adj[pivot_nn]) _used.add(neighbor);

        std::vector<int> new_level_set_one;
        std::vector<int> new_level_set_two;
        if (_find_level_sets) {
            for (int const v : level_set_one) {
                if (_used.get(v)) new_level_set_one.push_back(v);
                else new_level_set_two.push_back(v);
            }
            for (int const v : level_set_two) if (_used.get(v)) new_level_set_two.push_back(v);
        }

        std::vector<int> new_X, new_P;
        for (size_t i = 0; i < P.size(); i++) {
            if (P[i] == pivot_nn) pivot_nn_index = i;
            else if (_used.get(P[i])) new_P.push_back(P[i]);
            else if (_find_level_sets) new_level_set_one.push_back(P[i]);
        }
        for (size_t i = 0; i < X.size(); i++) {
            if (_used.get(X[i])) new_X.push_back(X[i]);
            else if (_find_level_sets && X[i] != pivot_nn) new_level_set_one.push_back(X[i]);
        }

        R.push_back(pivot_nn);

        solve_recursion(new_P, R, new_X, new_level_set_one, new_level_set_two, check);

        P[pivot_nn_index] = P[P.size() - 1];
        P.pop_back();

        R.pop_back();
        X.push_back(pivot_nn);
    }
}

void BronKerbosch::get_pivot_non_neighbors(std::vector<int> const &P, std::vector<int> const &X, std::vector<int> &pivot_non_neighbors) {

  int counter = 0, max_connections = -1, fixp = 0;

  _used.clear();
  for (int p : P) _used.add(p);

  for (std::vector<int> const *S : {&P, &X}) {
    for (int const node : *S) {
      counter = 0;
      for (int const neighbor : _adj[node]) if (_used.get(neighbor)) counter++;
      if (counter > max_connections) {
        max_connections = counter;
        fixp = node;
      }
    }
  }

  _used.clear();
  for (int const v : _adj[fixp]) _used.add(v);

  for (int const p : P) if (!_used.get(p)) pivot_non_neighbors.push_back(p);
}
