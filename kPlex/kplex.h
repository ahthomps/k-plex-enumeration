#include <iostream>
#include <vector>

#include "../bronKerbosch/bronKerbosch.h"
#include "../tools/fast_set.h"

#ifndef KPLEX_H_
#define KPLEX_H_

class KPlex {

  public:
    bool _report_one_near_clique = false;
    size_t _one_near_cliques_counter = 0;
    int type = 1;

    KPlex(std::vector<std::vector<int>> const *adj);
    ~KPlex();

    void two_plexes();
    void one_near_cliques();

  private:
    const std::vector<std::vector<int>>& _adj;
    FastSet _used;
    size_t _N;

    BronKerbosch* _maximal_clique_algo;

};

#endif
