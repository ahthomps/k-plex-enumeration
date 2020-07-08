#include <iostream>
#include <vector>
#include <functional>

#include "../tools/fast_set.h"
#include "../tools/config.h"

#ifndef BRONKERBOSCH_H_
#define BRONKERBOSCH_H_

class BronKerbosch {

  public:

    bool _report_clique = false;
    bool _find_level_set_one = true;
    size_t _clique_counter = 0;

    BronKerbosch(std::vector<std::vector<int>> const *adj, Config &config);

    size_t get_clique_counter();

    void solve(std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>)> check=([](std::vector<std::vector<int>> const * adj, std::vector<int> R, std::vector<int> level_set_one) -> bool {return true;}));
    void solve_on(std::vector<int> &P,
                  std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>)> check=([](std::vector<std::vector<int>> const * adj, std::vector<int> R, std::vector<int> level_set_one) -> bool {return true;}));

  private:

    void level_set_one_check(std::vector<int> const &level_set_one, std::vector<int> const &R);

    const std::vector<std::vector<int>>& _adj;
    FastSet _used;
    size_t _N;

    void solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X, std::vector<int> const &level_set_one, std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>)> check);
    void get_pivot_non_neighbors(std::vector<int> const &P, std::vector<int> const &X, std::vector<int> &pivot_non_neighbors);


};

#endif
