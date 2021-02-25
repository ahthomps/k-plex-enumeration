#include <iostream>
#include <vector>
#include <list>

#include "coreness.h"

CorenessReduction::CorenessReduction(std::vector<std::vector<int>> *adj, std::vector<bool> *nodes_status) :
    _adj(*adj), _nodes_status(*nodes_status)
{
    _N = _adj.size();
    _vertices_by_deg.resize(_N);
    _vertex_locater.resize(_N);
    _degree.resize(_N);

    for (size_t i = 0; i < _N; i++) {
        size_t deg = 0;
        for (int v : _adj[i]) if (_nodes_status[i]) deg++;
        _degree[i] = deg;
        _vertices_by_deg[_degree[i]].push_front(static_cast<int>(i));
        _vertex_locater[i] = _vertices_by_deg[_degree[i]].begin();
    }
}

CorenessReduction::~CorenessReduction() {}

bool CorenessReduction::reduce(size_t const clique_size, size_t const kplex) {
    size_t const min_degree = clique_size - kplex;
    size_t current_degree = 0;
    bool reduced = false;

    while (current_degree < min_degree) {
        if (!_vertices_by_deg[current_degree].empty()) {
            int const vertex = _vertices_by_deg[current_degree].front();
            _vertices_by_deg[current_degree].erase(_vertex_locater[vertex]);
            _degree[vertex] = -1;
            _nodes_status[vertex] = false;
            reduced = true;

            std::vector<int> const &vertex_neighborhood = _adj[vertex];
            for (int const neighbor : vertex_neighborhood) {
                if (_degree[neighbor] == -1) continue;
                _vertices_by_deg[_degree[neighbor]].erase(_vertex_locater[neighbor]);
                _degree[neighbor]--;

                if (_degree[neighbor] == -1) {
                    _nodes_status[neighbor] = false;
                    continue;
                }
                _vertices_by_deg[_degree[neighbor]].push_front(neighbor);
                _vertex_locater[neighbor] = _vertices_by_deg[_degree[neighbor]].begin();
            }
            current_degree = 0;
        }
        else current_degree++;
    }

    return reduced;
}
