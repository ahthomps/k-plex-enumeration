#include <iostream>
#include <vector>

#include "bronKerbosch.h"

BronKerbosch::BronKerbosch(std::vector<std::vector<int>> &_connected) {
  connected.swap(_connected);
  N = connected.size();
}

void BronKerbosch::solve() {
  std::vector<int> P(N);
  std::vector<int> R;
  std::vector<int> X;
  for (int i = 0; i < (int) N; i++) P.push_back(i);

  solve_recursion(P, R, X);
}

void BronKerbosch::solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X) {
  if (P.size() == 0 && X.size() == 0) {
    cliqueCounter++;
    if (reportClique) {
      // printClique
    }
    return;
  }
  while (P.size() != 0) {
    int v = P[P.size() - 1];
    // calculate new candidates
    std::vector<int> new_P;
    for (int u : P) {
      if (v == u) continue;
      else if (edge(v, u)) new_P.push_back(u);
    }
    // calculate new not
    std::vector<int> new_X;
    for (int u : X) {
      if (edge(v, u)) new_X.push_back(u);
    }
    // calculate new compsub
    std::vector<int> new_R;
    for (int u : R) new_R.push_back(u);
    new_R.push_back(v);

    solve_recursion(new_P, new_R, new_X);

    P.pop_back();
    X.push_back(v);
  }
}

bool BronKerbosch::edge(int p, int q) {
  for (int r : connected[p]) {
    if (q == r) return true;
    else if (q < r) break;
  }
  return false;
}
