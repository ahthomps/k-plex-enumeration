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


    private:
        FastSet _used;
        GraphTools _graph_tools;

        TriangleReduction *_triangles;

        size_t count_four_cliques_containing_vertex(int v, FastSet &used_too);

        bool reduction_helper(size_t min_four_cliques, FastSet &need_updating);
};

#endif