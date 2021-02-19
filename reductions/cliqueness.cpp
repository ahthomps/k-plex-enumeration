#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <cmath>

#include "cliqueness.h"
#include "../bronKerbosch/bronKerbosch.h"
#include "../tools/config.h"

CliquenessReduction::CliquenessReduction(std::vector<std::vector<int>> *adj, Config &config, std::vector<bool> *nodes_status) :
    _adj(*adj), _config(config), _nodes_status(*nodes_status)
{
    _N = _adj.size();
    _max_clq.resize(_N, 1);
}

bool CliquenessReduction::reduce(size_t const kplex) {
    BronKerbosch maxclq_algo(&_adj, _config, &_nodes_status);
    maxclq_algo.solve(_update_largest_clique);
    bool reduced = false;

    size_t min_clique_size = std::ceil(_max_clq_size / kplex);

    for (size_t i = 0; i < _max_clq.size(); i++) {
        if (_max_clq[i] < min_clique_size) {
            _nodes_status[i] = false;
            reduced = true;
        }
    }
    return reduced;
}

bool CliquenessReduction::reduce(size_t const clique_size, size_t const kplex) {
    size_t min_clique_size = std::ceil((double) clique_size / kplex);
    bool reduced = false;

    BronKerbosch maxclq_algo(&_adj, _config, &_nodes_status);
    maxclq_algo.solve(_update_largest_clique);

    // std::cout << _max_clq_size << std::endl;

    for (size_t i = 0; i < _max_clq.size(); i++) {
        if (_max_clq[i] < min_clique_size) {
            _nodes_status[i] = false;
            reduced = true;
        }
    }
    return reduced;
}
