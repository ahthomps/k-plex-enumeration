#include <iostream>
#include <vector>
#include <list>

#include "coreness.h"

CorenessReduction::CorenessReduction(std::vector<std::vector<int>> *adj, std::vector<bool> *nodes_status, std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, timer &t, double time_limit) :
    _adj(*adj), _nodes_status(*nodes_status), _edges_status(edges_status), _time_limit(time_limit), _t(t)
{
    _N = _adj.size();
    // _outer.resize(_N);
    // _locater.resize(_N);
    // _degree.resize(_N, -1);

    _outer.resize(_N);
    _locater.resize(_N);
    _degree.resize(_N, -1);

    // for (size_t i = 0; i < _N; i++) {
    //     if (!_nodes_status[i]) continue;
    //     size_t deg = 0;
    //     for (int v : _adj[i]) if (_nodes_status[i]) deg++;
    //     _degree[i] = deg;
    //     _outer[_degree[i]].push_front(static_cast<int>(i));
    //     _locater[i] = _outer[_degree[i]].begin();
    // }
}

CorenessReduction::~CorenessReduction() {}

bool CorenessReduction::bruteforce_reduce(size_t const clique_size, size_t const kplex) {
    // std::cout << "starting coreness reduction (" << _t.elapsed() << ")..." << std::endl;
    size_t const min_degree = clique_size - kplex;

    std::vector<size_t> degrees(_N);
    bool reduced = false;

    do {
        reduced = false;
        for (size_t v = 0; v < _N; v++) {
            if (!_nodes_status[v]) degrees[v] = min_degree + 1;
            size_t deg = 0;
            for (int u : _adj[v]) if (_nodes_status[u]) deg += 1;
            degrees[v] = deg;
        }

        for (size_t v = 0; v < _N; v++) {
            if (_nodes_status[v] && degrees[v] < min_degree) {
                _nodes_status[v] = false;
                reduced = true;
                for (int u : _adj[v]) {
                    std::pair<int, int> vu_edge;
                    if (v < u) vu_edge = std::make_pair(v, u);
                    else vu_edge = std::make_pair(u, v);

                    _edges_status.at(vu_edge) = false;
                }
            }
        }

    } while (reduced && _t.elapsed() < _time_limit);

    // std::cout << "...finishing coreness reduction (" << _t.elapsed() << ")" << std::endl;
    return reduced;
}

bool CorenessReduction::reduce(size_t const clique_size, size_t const kplex) {
    size_t const min_degree = clique_size - kplex;
    size_t current_degree = 0;
    bool reduced = false;

    while (current_degree < min_degree) {
        if (!_outer[current_degree].empty()) {
            int const vertex = _outer[current_degree].front();
            _outer[current_degree].erase(_locater[vertex]);
            _degree[vertex] = -1;
            _nodes_status[vertex] = false;

            for (int u : _adj[vertex]) {
                std::pair<int, int> vu_edge;
                if (vertex < u) vu_edge = std::make_pair(vertex, u);
                else vu_edge = std::make_pair(u, vertex);

                _edges_status.at(vu_edge) = false;
            }

            reduced = true;

            std::vector<int> const &vertex_neighborhood = _adj[vertex];
            for (int const neighbor : vertex_neighborhood) {
                if (_degree[neighbor] == -1) continue;
                _outer[_degree[neighbor]].erase(_locater[neighbor]);
                _degree[neighbor]--;

                if (_degree[neighbor] == -1) {
                    _nodes_status[neighbor] = false;
                    for (int u : _adj[neighbor]) {
                        std::pair<int, int> vu_edge;
                        if (neighbor < u) vu_edge = std::make_pair(neighbor, u);
                        else vu_edge = std::make_pair(u, neighbor);

                        if (_edges_status.at(vu_edge)) {
                            std::cout << "NEED TO MARK" << std::endl;
                        }
                    }
                    continue;
                }
                _outer[_degree[neighbor]].push_front(neighbor);
                _locater[neighbor] = _outer[_degree[neighbor]].begin();
            }
            current_degree = 0;
        }
        else current_degree++;
    }

    return reduced;
}
