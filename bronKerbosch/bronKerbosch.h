#include <iostream>
#include <vector>

#include "../tools/fast_set.h"

#ifndef BRONKERBOSCH_H_
#define BRONKERBOSCH_H_

class BronKerbosch {

  public:

    bool reportClique = false;
    int cliqueCounter = 0;

    BronKerbosch(std::vector<std::vector<int>> &_connected);

    void solve();
    void solveOn(std::vector<int> &P);

  private:

    std::vector<std::vector<int>> connected;
    FastSet used;
    size_t N;

    void solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X);
    // void getCandidates(std::vector<int> const &P, std::vector<int> const &X, std::vector<bool> const &P_bool, std::vector<bool> &candidates, size_t &num_candidates);
    void getCandidates(std::vector<int> const &P, std::vector<int> const &X, std::vector<int> &disconnections);
    // void getCandidates(std::vector<int> const &P, std::vector<int> const &X, std::vector<bool> &candidates, size_t &num_candidates);


};

#endif
