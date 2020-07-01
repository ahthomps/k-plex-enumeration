#include <iostream>
#include <vector>

#include "../bronKerbosch/bronKerbosch.h"
#include "../tools/fast_set.h"

#ifndef KPLEX_H_
#define KPLEX_H_

class KPlex {

  public:
    bool reportOneNearClique = false;
    size_t one_near_cliques_counter = 0;

    KPlex(std::vector<std::vector<int>> &adj);
    ~KPlex();

    void OneNearCliques();

  private:
    std::vector<std::vector<int>> _adj;
    FastSet used;
    size_t _N;

    BronKerbosch* maximal_clique_algo;

};

#endif
