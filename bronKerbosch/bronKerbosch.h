#include <iostream>
#include <vector>
#include <functional>

#include "../tools/fast_set.h"

#ifndef BRONKERBOSCH_H_
#define BRONKERBOSCH_H_

class BronKerbosch {

  public:

    bool _report_clique = false;
    int _clique_counter = 0;
    int type = 2;

    BronKerbosch(std::vector<std::vector<int>> const *adj);

    void solve(std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>)> check=([](std::vector<std::vector<int>> const * adj, std::vector<int> R) -> bool {return true;}));
    void solve_on(std::vector<int> &P, std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>)> check=([](std::vector<std::vector<int>> const * adj, std::vector<int> R) -> bool {return true;}));

  private:

    const std::vector<std::vector<int>>& _adj;
    FastSet _used;
    size_t _N;

    void solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X, std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>)> check);
    void get_pivot_non_neighbors(std::vector<int> const &P, std::vector<int> const &X, std::vector<int> &pivot_non_neighbors);


};

#endif
