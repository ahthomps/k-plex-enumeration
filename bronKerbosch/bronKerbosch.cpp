#include <iostream>
#include <vector>

#include "bronKerbosch.h"
#include "../tools/fast_set.h"

BronKerbosch::BronKerbosch(std::vector<std::vector<int>> const *adj) :
  _adj(*adj)
{
  _N = _adj.size();
  _used.set_fast_set(_N);
}

void BronKerbosch::solve(std::function<bool(std::vector<std::vector<int>>const *, std::vector<int>)> check) {
  std::vector<int> P;
  for (int i = 0; i < (int) _N; i++) P.push_back(i);

  solve_on(P, check);
}

void BronKerbosch::solve_on(std::vector<int> &P, std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>)> check) {
  std::vector<int> R;
  std::vector<int> X;

  _clique_counter = 0;

  solve_recursion(P, R, X, check);
}

void BronKerbosch::solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X, std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>)> check) {
  if (P.empty() && X.empty() && check(&_adj, R)) {
    _clique_counter++;
    if (_report_clique) {
      for (int const r : R) std::cout << r << ", ";
      std::cout << std::endl;
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

    std::vector<int> new_X, new_P;
    for (size_t i = 0; i < P.size(); i++) {
      if (P[i] == pivot_nn) pivot_nn_index = i;
      if (_used.get(P[i])) new_P.push_back(P[i]);
    }
    for (size_t i = 0; i < X.size(); i++) if (_used.get(X[i])) new_X.push_back(X[i]);

    R.push_back(pivot_nn);

    solve_recursion(new_P, R, new_X, check);

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
