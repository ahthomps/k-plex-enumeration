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

    void solveFixP();
    void solveFixP_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X);

    void solveFixP_recursion2(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X);

    void testFixP();

  private:

    std::vector<std::vector<int>> connected;
    std::vector<bool> connected_bool;
    size_t N;

    bool edge(int p, int q);
    void getFixP(std::vector<int> &P, std::vector<int> &X, int &fixp, int &nod, int &s);
    void getFixP2(std::vector<int> &P, std::vector<int> &X, std::vector<bool> &P_bool, std::vector<int> &candidates);

};

#endif
