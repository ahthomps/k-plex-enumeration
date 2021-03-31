#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <unordered_map>

#include "../tools/definitions.h"
#include "../tools/timer.h"

#ifndef CORENESS_H_
#define CORENESS_H_

class CorenessReduction {
    public:
        CorenessReduction(std::vector<std::vector<int>> *adj, std::vector<bool> *nodes_status, std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, timer &t, double time_limit);
        ~CorenessReduction();

        bool bruteforce_reduce(size_t const clique_size, size_t const kplex);
        bool reduce(size_t const clique_size, size_t const kplex);


    private:
        std::vector<std::vector<int>>& _adj;
        std::vector<bool>& _nodes_status;
        std::unordered_map<std::pair<int, int>, bool, pair_hash> &_edges_status;
        size_t _N;
        double _time_limit;
        timer &_t;
        std::vector<int> _degree;

        std::vector<std::list<int>> _outer;
        std::vector<std::list<int>::iterator> _locater;

};

#endif
