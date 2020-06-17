#include <iostream>
#include <vector>

#include "bronKerbosch.h"

BronKerbosch::BronKerbosch(std::vector<std::vector<int>> &_connected) {
  connected.swap(_connected);
  N = connected.size();
}

void BronKerbosch::solve() {
  std::vector<int> P;
  std::vector<int> R;
  std::vector<int> X;
  for (int i = 0; i < (int) N; i++) P.push_back(i);

  solve_recursion(P, R, X);
}

void BronKerbosch::solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X) {

  // std::cout << "----" << std::endl << "P: ";
  // for (int i = 0; i < P.size(); i++) std::cout << P[i] << ", ";
  // std::cout << std::endl << "R: ";
  // for (int i = 0; i < R.size(); i++) std::cout << R[i] << ", ";
  // std::cout << std::endl << "X: ";
  // for (int i = 0; i < X.size(); i++) std::cout << X[i] << ", ";
  // std::cout << std::endl;

  if (P.size() == 0 && X.size() == 0) {
    // std::cout << "found" << std::endl;
    cliqueCounter++;
    if (reportClique) {
      std::cout << "clique: ";
      for (int i = 0; i < R.size(); i++) {
        std::cout << R[i] << ", ";
      }
      std::cout << std::endl;
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
  // std::cout << "end" << std::endl;
}

void BronKerbosch::solveFixP() {
  std::vector<int> P;
  std::vector<int> R;
  std::vector<int> X;
  for (int i = 0; i < (int) N; i++) P.push_back(i);

  solveFixP_recursion(P, R, X);
}

void BronKerbosch::solveFixP_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X) {
  int fixp;
  int nod;
  int s;

  getFixP(P, X, fixp, nod, s);

  int p;
  int sel;
  for (int k = nod; k > 0; k--) {

    p = P[s];
    P[s] = P[P.size() - 1];
    P[P.size() - 1] = p;
    sel = p;

    std::vector<int> new_X;
    for (int x : X) if (edge(sel, x)) new_X.push_back(x);

    std::vector<int> new_P;
    for (int p_ : P) if (edge(sel, p_)) new_P.push_back(p_);

    R.push_back(sel);

    if (new_P.size() == 0 && new_X.size() == 0) {
      cliqueCounter++;
      if (reportClique) {
        for (int i = 0; i < R.size(); i++) {
          std::cout << R[i] << ", ";
        }
        std::cout << std::endl;
      }
    }
    else if (new_P.size() != 0) solveFixP_recursion(new_P, R, new_X);

    R.pop_back();
    X.push_back(sel);
    P.pop_back();

    s = 0;
    if (k > 1) while (edge(fixp, P[s])) s++;
  }
}

bool BronKerbosch::edge(int p, int q) {
  for (int r : connected[p]) {
    if (q == r) return true;
    else if (q < r) break;
  }
  return false;
}

void BronKerbosch::testFixP() {
  std::vector<int> P{0,1};
  std::vector<int> X{};
  // for (int i = 0; i < (int) N; i++) P.push_back(i);

  int fixp, nod, s;
  getFixP(P, X, fixp, nod, s);
  std::cout << "fixp: " << fixp << std::endl;
  std::cout << "s: " << s << std::endl << "nod: " << nod << std::endl;
}

void BronKerbosch::getFixP(std::vector<int> &P, std::vector<int> &X, int &fixp, int &nod, int &s) {
  std::vector<std::vector<int>> PandX{P, X};
  int p;
  int count;
  int pos;
  nod = (int) P.size() + 1;
  for (size_t index = 0; index < PandX.size(); index++) {
    std::vector<int> &L = PandX[index];
    for (int i = 0; i < (int) L.size() && nod != 0; i++) {
      p = L[i];
      count = 0;
      for (int j = 0; j < (int) P.size() && count < nod; j++) {
        if (!edge(p, P[j])) {
          // std::cout << "edge: " << p << ", " << P[j] << std::endl;
          count++;
          pos = j;
        }
      }
      if (count < nod) {
        fixp = p;
        nod = count;

        if (index == 1) s = pos;
        else s = i;
      }
    }
  }
}
