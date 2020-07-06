#include <iostream>
#include <vector>
#include <functional>

#include "../bronKerbosch/bronKerbosch.h"
#include "../tools/fast_set.h"

#ifndef KPLEX_H_
#define KPLEX_H_

class KPlex {

  public:
    bool _report_one_near_clique = false;
    bool _enumerate_connected_two_plex = true;
    size_t _kplex_counter = 0;

    KPlex(std::vector<std::vector<int>> const *adj);
    ~KPlex();

    size_t get_kplex_counter();

    void get_two_plexes();
    void get_one_near_cliques();
    void get_one_near_cliques_connected();

  private:
    const std::vector<std::vector<int>>& _adj;
    FastSet _used;
    size_t _N;

    BronKerbosch* _maximal_clique_algo;

};

#endif
