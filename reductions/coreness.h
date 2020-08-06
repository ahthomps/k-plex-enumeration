#include <iostream>
#include <vector>
#include <iterator>
#include <list>

#ifndef CORENESS_H_
#define CORENESS_H_

class CorenessReduction {
    public:
        std::vector<std::vector<int>>& _adj;
        std::vector<bool>& _nodes_status;
        size_t _N;
        std::vector<int> _degree;

        CorenessReduction(std::vector<std::vector<int>> *adj, std::vector<bool> *nodes_status);
        ~CorenessReduction();

        void reduce(size_t const clique_size, size_t const kplex);


    private:
        std::vector<std::list<int>> _vertices_by_deg;
        std::vector<std::list<int>::iterator> _vertex_locater;

};

#endif
