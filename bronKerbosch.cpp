#include <iostream>
#include <vector>

#include "bronKerbosch.h"

BronKerbosch::BronKerbosch(std::vector<std::vector<int>> &_connected) {
  connected.swap(_connected);
  N = connected.size();
  connected_bool.resize(N, false);
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

  solveFixP_recursion2(P, R, X);
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

void BronKerbosch::solveFixP_recursion2(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X) {
  if (P.size() == 0 && X.size() == 0) {
    cliqueCounter++;
    if (reportClique) {
      for (int i = 0; i < R.size(); i++) {
        std::cout << R[i] << ", ";
      }
      std::cout << std::endl;
    }
    return;
  }
  else if (P.size() == 0) return;

  std::vector<bool> P_bool(N, false);
  std::vector<bool> X_bool(N, false);
  for (int p : P) P_bool[p] = true;
  for (int x : X) X_bool[x] = true;

  std::vector<int> candidates;
  getFixP2(P, X, P_bool, candidates);

  int p;
  int sel;
  for (int s : candidates) {

    p = P[s];
    P[s] = P[P.size() - 1];
    P[P.size() - 1] = p;
    sel = p;

    std::vector<int> new_X;
    std::vector<int> new_P;
    for (int neighbor : connected[sel]) {
      if (X_bool[neighbor]) new_X.push_back(neighbor);
      if (P_bool[neighbor]) new_P.push_back(neighbor);
    }

    R.push_back(sel);

    solveFixP_recursion2(new_P, R, new_X);

    R.pop_back();
    X.push_back(sel);
    P.pop_back();

    P_bool[sel] = false;
    X_bool[sel] = true;
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
  std::vector<int> P;
  std::vector<int> X;
  for (int i = 0; i < (int) N; i++) P.push_back(i);

  std::vector<int> candidates;

  std::vector<bool> P_bool(P.size(), false);
  for (int p : P) P_bool[p] = true;

  int fixp, nod, s;
  getFixP2(P, X, P_bool, candidates);
  std::cout << "candidates: ";
  for (int c : candidates) std::cout << c << ", ";
  std::cout << std::endl;
}

void BronKerbosch::getFixP(std::vector<int> &P, std::vector<int> &X, int &fixp, int &nod, int &s) {
  // fix
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

void BronKerbosch::getFixP2(std::vector<int> &P, std::vector<int> &X, std::vector<bool> &P_bool, std::vector<int> &candidates) {

  std::vector<std::vector<int>*> L{&P, &X};
  size_t counter, minnod;
  std::vector<int> disconnections;
  minnod = N + 1;

  for (std::vector<int> *S : L) {
    for (int node : *S) {
      counter = 0;
      disconnections.clear();
      connected_bool[node] = true;
      for (int neighbor : connected[node]) connected_bool[neighbor] = true;
      if (P_bool[node]) disconnections.push_back(node);
      for (int p : P) {
        if (!connected_bool[p]) {
          disconnections.push_back(p);
          counter++;
        }
      }
      if (counter < minnod) {
        candidates = disconnections;
        minnod = counter;
      }
      connected_bool[node] = false;
      for (int neighbor : connected[node]) connected_bool[neighbor] = false;
    }
  }
}
