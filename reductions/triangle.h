#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <tuple>
#include <unordered_map>

#include "../tools/graph_tools.h"

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

class TriangleReduction {

    public:
        std::vector<std::vector<int>>& _adj;
        std::vector<bool>& _nodes_status;
        size_t _N;
        std::vector<size_t> *_triangles;

        TriangleReduction(std::vector<std::vector<int>>& adj, std::vector<bool>& nodes_status);
        TriangleReduction(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, std::vector<size_t>* four_cliques);
        ~TriangleReduction();

        size_t get_total_num_triangles();

        size_t chiba_count_triangles(std::vector<size_t> const &degeneracy_ordering,
                                     std::vector<int> const &nodeID_to_degeneracy_mapping,
                                     std::vector<std::vector<int>> &shadow_adj);

        void count_triangles();
        void count_triangles_containing_vertex(int const u);
        void bruteforce_count_triangles();

        bool reduce(size_t const k, size_t const m);

        size_t count_triangles_containing_edge(std::vector<std::unordered_map<int, bool>> const &edges_status, int const v, int const u);
        std::vector<std::unordered_map<int, size_t>> edge_count_triangles(std::vector<std::unordered_map<int, bool>> const &edges_status);
        bool edge_reduce(std::vector<std::unordered_map<int, bool>> &edges_status, size_t const k, size_t const q);

    private:
        FastSet _used;
        GraphTools _graph_tools;
        bool is_sub_call = false;

        // std::vector<size_t> _degrees;
        // std::vector<std::list<int>> _outer;
        // std::vector<std::list<int>::iterator> _locator;

        bool reduction_helper(size_t min_triangles, FastSet &needs_updating);

        // void get_degeneracy_ordering(std::vector<int> &nodes_list,
        //                              std::vector<size_t> &degeneracy_ordering,
        //                              std::vector<int> &nodeID_to_degeneracy_mapping,
        //                              std::vector<std::vector<int>> &shadow_adj);
};

#endif
