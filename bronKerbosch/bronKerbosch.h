#include <iostream>
#include <vector>

#include "../tools/fast_set.h"

#ifndef BRONKERBOSCH_H_
#define BRONKERBOSCH_H_

class BronKerbosch {

  public:

    bool reportClique = false;
    int cliqueCounter = 0;

    BronKerbosch(std::vector<std::vector<int>> &adj);

    void solve();
    void solveOn(std::vector<int> &P);

  private:

    std::vector<std::vector<int>> _adj;
    FastSet used;
    size_t _N;

    void solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X);
    void getDisconnections(std::vector<int> const &P, std::vector<int> const &X, std::vector<int> &disconnections);


};

#endif
