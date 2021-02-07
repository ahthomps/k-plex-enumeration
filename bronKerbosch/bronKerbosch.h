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
    bool _find_level_sets = false;
    size_t _clique_counter = 0;

    BronKerbosch(std::vector<std::vector<int>> const *adj, Config &config, std::vector<bool> const *nodes_status, size_t min_size=1);

    size_t get_clique_counter();

    void solve(std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> check=([](std::vector<std::vector<int>> const * adj, std::vector<int> R, std::vector<int> level_set_one, std::vector<int> level_set_two) -> bool {return true;}), bool find_level_sets=false);
    void solve_on(std::vector<int> &P, std::vector<int> R,
                  std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> check=([](std::vector<std::vector<int>> const * adj, std::vector<int> R, std::vector<int> level_set_one, std::vector<int> level_set_two) -> bool {return true;}), bool find_level_sets=false);

  private:

    const std::vector<std::vector<int>>& _adj;
    const std::vector<bool>& _nodes_status;
    FastSet _used;
    size_t _N;
    size_t _min_size;

    void solve_recursion(std::vector<int> &P, std::vector<int> &R, std::vector<int> &X, std::vector<int> const &level_set_one, std::vector<int> const &level_set_two, std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> check);
    void get_pivot_non_neighbors(std::vector<int> const &P, std::vector<int> const &X, std::vector<int> &pivot_non_neighbors);
};

#endif
