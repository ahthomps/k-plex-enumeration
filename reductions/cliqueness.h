#include <iostream>
#include <vector>
#include <iterator>
#include <list>

#include "../bronKerbosch/bronKerbosch.h"
#include "../tools/config.h"

#ifndef CLIQUENESS_H_
#define CLIQUENESS_H_

class CliquenessReduction {
    public:
        std::vector<std::vector<int>>& _adj;
        Config& _config;
        std::vector<bool>& _nodes_status;
        size_t _N;
        std::vector<int> _max_clq;
        size_t _max_clq_size = 0;

        CliquenessReduction(std::vector<std::vector<int>> *adj, Config &config, std::vector<bool> *nodes_status);
        ~CliquenessReduction() {};

        bool reduce(size_t const clique_size, size_t const kplex, std::string &filename);
        bool reduce(size_t const kplex);
        bool reduce_old(size_t const clique_size, size_t const kplex);

    private:

        void get_maximum_cliques(std::string &filename, std::function<void(std::vector<int>&)> callback);

        std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> _update_largest_clique_first = [&] (std::vector<std::vector<int>> const * p_adj, std::vector<int> R, std::vector<int> level_set_one, std::vector<int> level_set_two) -> bool {
            for (int const v : R) {
                if (_max_clq[v] < int(R.size())) _max_clq[v] = R.size();
                if (_max_clq_size < int(R.size())) _max_clq_size = R.size();
            }
            return true;
        };

        std::function<void(std::vector<int>&)> _update_largest_clique = [&] (std::vector<int> &clq) -> void {
            for (int const v : clq) {
                if (_max_clq[v] < int(clq.size())) _max_clq[v] = clq.size();
                if (_max_clq_size < int(clq.size())) _max_clq_size = clq.size();
            }
        };

};

#endif
