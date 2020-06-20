#include <iostream>
#include <vector>

#include "bronKerbosch.h"

BronKerbosch::BronKerbosch(std::vector<std::vector<int>> &_connected) {
  connected.swap(_connected);
  N = connected.size();
  connected_bool.resize(N, false);
  used.resize(N, false);
}

void BronKerbosch::solve() {
  std::vector<int> P;
  std::vector<int> R;
  std::vector<int> X;
  for (int i = 0; i < (int) N; i++) P.push_back(i);

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

  std::vector<bool> P_bool(N, false);
  std::vector<bool> X_bool(N, false);
  for (int p : P) P_bool[p] = true;
  for (int x : X) X_bool[x] = true;

  std::vector<bool> candidates(N, false);
  size_t num_candidates;
  getCandidates(P, X, P_bool, candidates, num_candidates);

  int p, sel;
  size_t P_index = 0;
  for (size_t _ = num_candidates; _ > 0; _--) {

    while (!candidates[P[P_index]]) P_index++;

    p = P[P_index];
    P[P_index] = P[P.size() - 1];
    P[P.size() - 1] = p;
    sel = p;

    std::vector<int> new_X;
    std::vector<int> new_P;
    for (int neighbor : connected[sel]) {
      if (X_bool[neighbor]) new_X.push_back(neighbor);
      if (P_bool[neighbor]) new_P.push_back(neighbor);
    }

    solve_recursion(new_P, R, new_X);

    R.pop_back();
    X.push_back(sel);
    P.pop_back();

    P_bool[sel] = false;
    X_bool[sel] = true;
  }
}

void BronKerbosch::getCandidates(std::vector<int> const &P, std::vector<int> const &X, std::vector<bool> const &P_bool, std::vector<bool> &candidates, size_t &num_candidates) {

  std::vector<std::vector<int> const *> List_PandX{&P, &X};
  int counter, max_connections, fixp;
  max_connections = -1;

  for (std::vector<int> const *S : List_PandX) {
    for (int node : *S) {
      counter = 0;
      for (int neighbor : connected[node]) if (P_bool[neighbor]) counter++;
      if (counter > max_connections) {
        max_connections = counter;
        fixp = node;
      }
    }
  }

  for (int v : connected[fixp]) connected_bool[v] = true;

  num_candidates = 0;
  for (int v : P) {
    if (!connected_bool[v]) {
      candidates[v] = true;
      num_candidates++;
    }
  }

  for (int v : connected[fixp]) connected_bool[v] = false;


}
