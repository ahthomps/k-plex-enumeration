#include <iostream>
#include <vector>

#ifndef BRONKERBOSCH_H_
#define BRONKERBOSCH_H_

class BronKerbosch {

  public:

    bool reportClique = false;
    int cliqueCounter = 0;

    BronKerbosch(std::vector<std::vector<int>> &_connected);

    void solve();
    void solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X);

  private:

    std::vector<std::vector<int>> connected;
    size_t N;

    bool edge(int p, int q);
};

#endif
