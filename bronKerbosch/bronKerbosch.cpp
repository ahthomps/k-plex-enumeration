#include <iostream>
#include <vector>

#include "bronKerbosch.h"
#include "../tools/fast_set.h"

BronKerbosch::BronKerbosch(std::vector<std::vector<int>> &adj) {
  _adj.swap(adj);
  _N = _adj.size();
  used.set_fast_set(_N);
}

void BronKerbosch::solve() {
  std::vector<int> P;
  std::vector<int> R;
  std::vector<int> X;
  for (int i = 0; i < (int) _N; i++) P.push_back(i);

  cliqueCounter = 0;

  solve_recursion(P, R, X);
}

void BronKerbosch::solveOn(std::vector<int> &P) {
  std::vector<int> R;
  std::vector<int> X;

  cliqueCounter = 0;

  solve_recursion(P, R, X);
}

void BronKerbosch::solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X) {
  if (P.size() == 0 && X.size() == 0) {
    cliqueCounter++;
    if (reportClique) {
      for (int r : R) std::cout << r << ", ";
      std::cout << std::endl;
    }
    return;
  }
  if (P.size() == 0) return;

  std::vector<int> disconnections;
  getDisconnections(P, X, disconnections);

  size_t P_index;
  for (int sel : disconnections) {

    used.clear();
    for (int neighbor : _adj[sel]) used.add(neighbor);

    std::vector<int> new_X;
    std::vector<int> new_P;
    for (size_t i = 0; i < P.size() || i < X.size(); i++) {
      // find the index of the current candidate and build new_P
      if (i < P.size()) {
        if (P[i] == sel) P_index = i;
        if (used.get(P[i])) new_P.push_back(P[i]);
      }
      // build new_X
      if (i < X.size()) if (used.get(X[i])) new_X.push_back(X[i]);
    }

    R.push_back(sel);

    solve_recursion(new_P, R, new_X);

    P[P_index] = P[P.size() - 1];
    P[P.size() - 1] = sel;

    R.pop_back();
    X.push_back(sel);
    P.pop_back();
  }
}

void BronKerbosch::getDisconnections(std::vector<int> const &P, std::vector<int> const &X, std::vector<int> &disconnections) {

  std::vector<std::vector<int> const *> List_PandX{&P, &X};
  int counter, max_connections, fixp;
  max_connections = -1;

  used.clear();
  for (int p : P) used.add(p);

  for (std::vector<int> const *S : List_PandX) {
    for (int node : *S) {
      counter = 0;
      for (int neighbor : _adj[node]) if (used.get(neighbor)) counter++;
      if (counter > max_connections) {
        max_connections = counter;
        fixp = node;
      }
    }
  }

  used.clear();
  for (int v : _adj[fixp]) used.add(v);

  for (int v : P) if (!used.get(v)) disconnections.push_back(v);
}
