#include <iostream>
#include <vector>

#include "bronKerbosch.h"
#include "../tools/fast_set.h"

BronKerbosch::BronKerbosch(std::vector<std::vector<int>> &_connected) {
  connected.swap(_connected);
  N = connected.size();
  used.set_fast_set(N);
}

void BronKerbosch::solve() {
  std::vector<int> P;
  std::vector<int> R;
  std::vector<int> X;
  for (int i = 0; i < (int) N; i++) P.push_back(i);

  solve_recursion(P, R, X);
}

void BronKerbosch::solveOn(std::vector<int> &P) {
  std::vector<int> R;
  std::vector<int> X;

  cliqueCounter = 0;

  solve_recursion(P, R, X);
}

// void BronKerbosch::solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X) {
//   if (P.size() == 0 && X.size() == 0) {
//     cliqueCounter++;
//     if (reportClique) {
//       for (int r : R) std::cout << r << ", ";
//       std::cout << std::endl;
//     }
//     return;
//   }
//   if (P.size() == 0) return;
//
//   // Is it bad that I initialize a N-sized vector each time?
//   // Can't be an attribute of BronKerbosch because each changing on
//   // each recursion.
//   // possible solution -- could use a FastSet type thing where if some vertex v is in P
//   //  then P[v] = P[v]++ so you would keep
//   std::vector<bool> P_bool(N, false);
//   std::vector<bool> X_bool(N, false);
//   for (int p : P) P_bool[p] = true;
//   for (int x : X) X_bool[x] = true;
//
//   // same here?
//   std::vector<bool> candidates(N, false);
//   size_t num_candidates;
//   getCandidates(P, X, P_bool, candidates, num_candidates);
//
//   int candidate;
//   size_t P_index = 0;
//   for (size_t _ = num_candidates; _ > 0; _--) {
//
//     // need this (can't just have a vector of candidates) because
//     //  1. you need to be able to easily remove candidate from P
//     //  2. you can't save indices because P is changing!
//     while (!candidates[P[P_index]]) P_index++;    // only looks through P once
//
//     candidate = P[P_index];
//     P[P_index] = P[P.size() - 1];
//     P[P.size() - 1] = candidate;
//
//     std::vector<int> new_X;
//     std::vector<int> new_P;
//     for (int neighbor : connected[candidate]) {
//       if (X_bool[neighbor]) new_X.push_back(neighbor);
//       if (P_bool[neighbor]) new_P.push_back(neighbor);
//     }
//
//     R.push_back(candidate);
//
//     solve_recursion(new_P, R, new_X);
//
//     R.pop_back();
//     X.push_back(candidate);
//     P.pop_back();
//
//     P_bool[candidate] = false;
//     X_bool[candidate] = true;
//   }
// }

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
  getCandidates(P, X, disconnections);

  size_t P_index;
  for (int sel : disconnections) {

    used.clear();
    for (int neighbor : connected[sel]) used.add(neighbor);

    std::vector<int> new_X;
    std::vector<int> new_P;
    for (size_t i = 0; i < P.size(); i++) {
      if (P[i] == sel) P_index = i;
      if (used.get(P[i])) new_P.push_back(P[i]);
    }
    for (int x : X) if (used.get(x)) new_X.push_back(x);

    P[P_index] = P[P.size() - 1];
    P[P.size() - 1] = sel;

    R.push_back(sel);

    solve_recursion(new_P, R, new_X);

    R.pop_back();
    X.push_back(sel);
    P.pop_back();
  }
}

void BronKerbosch::getCandidates(std::vector<int> const &P, std::vector<int> const &X, std::vector<int> &disconnections) {

  std::vector<std::vector<int> const *> List_PandX{&P, &X};
  int counter, max_connections, fixp;
  max_connections = -1;

  used.clear();
  for (int p : P) used.add(p);

  for (std::vector<int> const *S : List_PandX) {
    for (int node : *S) {
      counter = 0;
      for (int neighbor : connected[node]) if (used.get(neighbor)) counter++;
      if (counter > max_connections) {
        max_connections = counter;
        fixp = node;
      }
    }
  }

  used.clear();
  for (int v : connected[fixp]) used.add(v);

  for (int v : P) if (!used.get(v)) disconnections.push_back(v);
}
