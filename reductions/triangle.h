#include <iostream>
#include <vector>
#include <iterator>
#include <list>

#include "../tools/graph_tools.h"

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

class TriangleReduction {
    public:
        std::vector<std::vector<int>>& _adj;
        std::vector<bool>& _nodes_status;
        size_t _N;
        std::vector<size_t> _triangles;

        TriangleReduction(std::vector<std::vector<int>> *adj, std::vector<bool> *nodes_status);
        ~TriangleReduction();

        void print_total_num_triangles();

        void clear_triangles();

        size_t chiba_count_triangles(std::vector<int> *nodes_list=nullptr);
        
        void count_4clqs();
        void bruteforce_count_4clqs();

        void count_triangles();
        void count_triangles_containing_vertex(int const u);
        void count_triangles_containing_edge(int const u, int const v);
        void bruteforce_count_triangles();

        bool reduce(size_t const k, size_t const m);


    private:
        FastSet _used;
        GraphTools _graph_tools;

        std::vector<size_t> _degrees;
        std::vector<std::list<int>> _outer;
        std::vector<std::list<int>::iterator> _locator;

        bool reduction_helper(size_t min_triangles, FastSet &needs_updating);

        void get_degeneracy_ordering(std::vector<int> &nodes_list, std::vector<size_t> &degeneracy_ordering, std::vector<int> &nodeID_to_degeneracy_mapping);
};

#endif
