#include <iostream>
#include <vector>
#include <functional>

#include "bronKerbosch.h"
#include "../tools/fast_set.h"
#include "../tools/config.h"

BronKerbosch::BronKerbosch(std::vector<std::vector<int>> const *adj, Config &config) :
  _adj(*adj)
{
  _N = _adj.size();
  _used.set_fast_set(_N);

  _report_clique = config.RPT_CLQ;
}

void BronKerbosch::level_set_one_check(std::vector<int> const &level_set_one, std::vector<int> const &R)  {
  for (int const v : level_set_one) {
    _used.clear();
    for (int const v_neighbor : _adj[v]) _used.add(v_neighbor);
    size_t missing_edges = 0;

    for (int const u : R) if (!_used.get(u)) missing_edges++;

    if (missing_edges != 1) std::cout << "missing_edges: " << missing_edges << std::endl;
  }
}

size_t BronKerbosch::get_clique_counter() {
  return _clique_counter;
}

void BronKerbosch::solve(std::function<bool(std::vector<std::vector<int>>const *, std::vector<int>, std::vector<int>)> check) {
  std::vector<int> P;
  for (int i = 0; i < static_cast<int>(_N); i++) P.push_back(i);

  solve_on(P, check);
}

void BronKerbosch::solve_on(std::vector<int> &P, std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>)> check) {
  std::vector<int> R;
  std::vector<int> X;
  std::vector<int> level_set_one;

  _clique_counter = 0;

  solve_recursion(P, R, X, level_set_one, check);
}

void BronKerbosch::solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X, std::vector<int> const &level_set_one, std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>)> check) {
  if (P.empty() && X.empty() && check(&_adj, R, level_set_one)) {
    // if (level_set_one.size() != 0 && R.size() > 1) {
    //   std::cout << "level set one size: " << level_set_one.size() << " R size: " << R.size() << std::endl;
    //   for (int v : level_set_one) std::cout << v << ", ";
    //   std::cout << std::endl;
    //   for (int v : R) std::cout << v << ", ";
    //   std::cout << std::endl;
    //   level_set_one_check(level_set_one, R);
    //   exit(0);
    // }

    _clique_counter++;
    if (_report_clique) {
      for (int const r : R) std::cout << r << ", ";
      std::cout << std::endl;
    }
    return;
  }
  if (P.empty()) return;

  // std::cout << "top" << std::endl;

  std::vector<int> pivot_non_neighbors;
  get_pivot_non_neighbors(P, X, pivot_non_neighbors);

  size_t pivot_nn_index = 0;
  for (int const pivot_nn : pivot_non_neighbors) {
    _used.clear();
    for (int const neighbor : _adj[pivot_nn]) _used.add(neighbor);

    std::vector<int> new_level_set_one;
    if (_find_level_set_one) for (int const v : level_set_one) if (_used.get(v)) new_level_set_one.push_back(v);

    std::vector<int> new_X, new_P;
    for (size_t i = 0; i < P.size(); i++) {
      if (P[i] == pivot_nn) pivot_nn_index = i;
      else if (_used.get(P[i])) new_P.push_back(P[i]);
      else if (_find_level_set_one) new_level_set_one.push_back(P[i]);
    }
    for (size_t i = 0; i < X.size(); i++) {
      if (_used.get(X[i])) new_X.push_back(X[i]);
      else if (_find_level_set_one && X[i] != pivot_nn) new_level_set_one.push_back(X[i]);
    }

    // level_set_one_check(new_level_set_one, R);

    R.push_back(pivot_nn);

    solve_recursion(new_P, R, new_X, new_level_set_one, check);

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
