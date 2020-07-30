#include <iostream>
#include <vector>
#include <iterator>

#include "../tools/linked_list.h"

#ifndef CORENESS_H_
#define CORENESS_H_

class CorenessReduction {
    public:
        std::vector<std::vector<int>>& _adj;
        size_t _N;
        std::vector<bool> nodes_status;
        std::vector<size_t> nodes_degree;
        // std::vector<LinkedList::iterator> nodes_location;

        CorenessReduction(std::vector<std::vector<int>> *adj);
        ~CorenessReduction();

        std::vector<bool>* reduce(size_t clique_size, size_t k_plex_num=1);
        void adjust_neighbors(int node_to_remove);

        void print_nodes_by_degree();
        void print_removed_nodes();

    private:
        std::vector<std::vector<int>> nodes_by_deg;
        // std::vector<LinkedList*> nodes_priority;

        void get_nodes_by_deg();
        // void get_nodes_priority();
};

#endif
