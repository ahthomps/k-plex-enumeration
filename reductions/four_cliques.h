#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <tuple>

#include "../tools/graph_tools.h"
#include "triangle.h"

#ifndef FOURCLIQUES_H_
#define FOURCLIQUES_H_

class FourCliquesReduction {
    public:
        std::vector<std::vector<int>>& _adj;
        std::vector<bool>& _nodes_status;
        size_t _N;
        std::vector<size_t> *_four_cliques;

        FourCliquesReduction(std::vector<std::vector<int>>& adj, std::vector<bool>& nodes_status);
        ~FourCliquesReduction();

        size_t get_total_num_four_cliques();
        
        void count_4clqs();  
        void bruteforce_count_4clqs();

        bool reduce(size_t const k, size_t const m);

        std::vector<std::unordered_map<int, size_t>> edge_count_4clqs(std::vector<std::unordered_map<int, bool>> const &edges_status);
        size_t edge_reduce(std::vector<std::unordered_map<int, bool>> &edges_status, double const k, double const q);

        std::unordered_map<std::pair<int, int>, size_t, pair_hash> edge_count_4clqs_new(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status);
        std::unordered_map<std::pair<int, int>, size_t, pair_hash> bruteforce_edge_count_4clqs(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status);
        size_t edge_reduce_new(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, size_t const k, size_t const q);


    private:
        FastSet _used;
        GraphTools _graph_tools;

        TriangleReduction *_triangles;

        size_t count_four_cliques_containing_vertex(int v, FastSet &used_too);
        size_t count_4clqs_containing_edge(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, int const v, int const u);

        bool reduction_helper(size_t min_four_cliques, FastSet &need_updating);
        size_t edge_reduce_helper(std::vector<std::unordered_map<int, bool>> &edges_status, double const min_four_cliques);
        size_t edge_reduce_helper_new(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, std::unordered_map<std::pair<int, int>, size_t, pair_hash> &edge_4clqs, std::vector<std::pair<int, int>> &need_updating, std::unordered_map<std::pair<int, int>, bool, pair_hash> &already_needs_updating, size_t const min_four_cliques);


};

#endif
