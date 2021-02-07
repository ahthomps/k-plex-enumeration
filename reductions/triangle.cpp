#include <iostream>
#include <vector>
#include <list>
#include <cmath>


#include "triangle.h"


TriangleReduction::TriangleReduction(std::vector<std::vector<int>> *adj, std::vector<bool> *nodes_status) :
    _adj(*adj), _nodes_status(*nodes_status)
{
    _N = _adj.size();
    _triangles.resize(_N, 0);
    _used.set_fast_set(_N);
}

TriangleReduction::~TriangleReduction() {}

void TriangleReduction::print_total_num_triangles() {
    size_t count = 0;
    for (size_t u : _triangles) count += u;
    std::cout << "count: " << count << std::endl;
}

void TriangleReduction::clear_triangles() {
    _triangles.clear();
    _triangles.resize(_N, 0);
}

void TriangleReduction::count_triangles() {
    std::cout << "counting triangles..." << std::endl;
    for (int u = 0; u < int(_N); u++) {
        std::vector<int> u_neighborhood = _adj[u];
        if (!_nodes_status[u] || u_neighborhood.empty()) continue;
        for (size_t i = 0; i < u_neighborhood.size() - 1; i++) {
            int v = u_neighborhood[i];
            if (!_nodes_status[v] || v < u) continue;
            _used.clear();
            for (int w : _adj[v]) _used.add(w);
            for (size_t j = i + 1; j < u_neighborhood.size(); j++) {
                int w = u_neighborhood[j];
                if (!_nodes_status[w] || !_used.get(w)) continue;
                _triangles[u]++;
                _triangles[v]++;
                _triangles[w]++;
            }
        }
    }
    std::cout << ".... done!" << std::endl;
}

void TriangleReduction::count_triangles_containing_vertex(int const u) {
    assert(_nodes_status[u]);
    _triangles[u] = 0;
    std::vector<int> u_neighborhood = _adj[u];
    if (u_neighborhood.empty()) return;
    for (size_t i = 0; i < u_neighborhood.size() - 1; i++) {
        int v = u_neighborhood[i];
        if (!_nodes_status[v]) continue;
        _used.clear();
        for (int w : _adj[v]) _used.add(w);
        for (size_t j = i + 1; j < u_neighborhood.size(); j++) {
            int w = u_neighborhood[j];
            if (_nodes_status[w] && _used.get(w)) _triangles[u]++;
        }
    }
}

void TriangleReduction::bruteforce_count_triangles() {
    for (int u = 0; u < int(_N); u++) {
        count_triangles_containing_vertex(u);
    }
}

bool TriangleReduction::reduction_helper(size_t min_triangles, FastSet &need_updating) {
    bool reduced = false;
    need_updating.clear();

    for (size_t v = 0; v < _N; v++) {
        if (!_nodes_status[v] || _triangles[v] >= min_triangles) continue;
        _nodes_status[v] = false;
        _triangles[v] = 0;
        reduced = true;
        if (need_updating.get(v)) need_updating.remove(v);
        for (int u : _adj[v]) if (_nodes_status[u] && !need_updating.get(u)) need_updating.add(u);  
    }

    return reduced;
}

void TriangleReduction::reduce(size_t const k, size_t const m) {
    size_t min_triangles = ceil((m - k) * (m - 2 * k) / 2);
    // std::cout << min_triangles << std::endl;
    count_triangles();

    FastSet need_updating;
    need_updating.set_fast_set(_N);

    std::cout << "reducing..." << std::endl;
    while (reduction_helper(min_triangles, need_updating)) 
        for (size_t v = 0; v < _N; v++) if (need_updating.get(v)) count_triangles_containing_vertex(v);

    std::cout << std::endl << ".... done!" << std::endl;
}





