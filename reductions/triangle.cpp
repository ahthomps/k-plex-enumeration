#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <iterator>


#include "triangle.h"
#include "../tools/timer.h"


TriangleReduction::TriangleReduction(std::vector<std::vector<int>> *adj, std::vector<bool> *nodes_status) :
    _adj(*adj), _nodes_status(*nodes_status)
{
    _N = _adj.size();
    _triangles.resize(_N, 0);
    _used.set_fast_set(_N);

    _degrees.resize(_N, 0);
    _locator.resize(_N);

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

void TriangleReduction::get_degeneracy_ordering(std::vector<int> &nodes_list, std::vector<size_t> &degeneracy_ordering, std::vector<int> &nodeID_to_degeneracy_mapping) {
    _outer.clear();
    _outer.resize(_N);

    // for (int v = 0; v < int(_N); v++) {
    //     size_t deg = _N;
    //     if (_nodes_status[v]) {
    //         deg = 0;
    //         for (int u : _adj[v]) if (_nodes_status[u]) deg += 1;
    //     }
    //     _degrees.push_back(deg);
    //     _outer[deg].push_back(v);
    //     _locator.push_back(std::prev(_outer[deg].end()));
    // }
    _used.clear();
    size_t max_deg = 0;
    for (int v : nodes_list) _used.add(v);
    for (int v : nodes_list) {
        size_t deg = 0;
        for (int u : _adj[v]) if (_used.get(u)) deg += 1;
        _degrees[v] = deg;
        _outer[deg].push_back(v);
        _locator[v] = std::prev(_outer[deg].end());

        if (deg > max_deg) max_deg = deg;
    }

    size_t deg = 0;
    while (deg <= max_deg) {
        if (_outer[deg].empty()) {
            deg += 1;
            continue;
        }
        // find some node in _outer[deg] (easiest is just the last one) and remove it
        int node = _outer[deg].back();                                           // look at the last node in the list
        _outer[deg].pop_back();                                                  // remove the node from the list 
        // _degrees[node] = _N;                                                     // update _degrees so it is invalid
        // _outer[_N].push_back(node);                                              // add it to list of invalid nodes 
        // _locator[node] = std::prev(_outer[_N].end());                             // update _locator to make new location
        _used.remove(node);
        nodeID_to_degeneracy_mapping[node] = degeneracy_ordering.size();        // add node location in mapping
        degeneracy_ordering.push_back(node);

        size_t min_deg = deg;                                                   // keep track of whether or not we need to look at smaller _degrees
        for (int neighbor : _adj[node]) {
            if (!_used.get(neighbor)) continue;                              // if neighbor is invalid skip
            size_t neighbor_deg = _degrees[neighbor];
            if (_outer[neighbor_deg].size() != 1 && _outer[neighbor_deg].back() != neighbor) {    // if neighbor is at the back of the list dont need to swap
                int swap_node = _outer[neighbor_deg].back();
                *_locator[neighbor] = swap_node;
                _locator[swap_node] = _locator[neighbor];

            }
            _outer[neighbor_deg].pop_back();                                     // remove neighbor from current degree list
            neighbor_deg--;                                                     
            _outer[neighbor_deg].push_back(neighbor);                            // add neighbor to new degree list and update iterator/degree
            _locator[neighbor] = std::prev(_outer[neighbor_deg].end());
            _degrees[neighbor] = neighbor_deg;

            if (neighbor_deg < min_deg) min_deg = neighbor_deg;
        }

        deg = min_deg;   
    }

}

size_t TriangleReduction::chiba_count_triangles(std::vector<int> *nodes_list_ptr) {
    std::vector<size_t> degeneracy_ordering;
    degeneracy_ordering.reserve(_N);
    std::vector<int> nodeID_to_degeneracy_mapping(_N, -1);

    timer t;
    std::vector<int> nodes_list;
    if (nodes_list_ptr == nullptr) {
        for (int v = 0; v < int(_N); v++)
            if (_nodes_status[v])
                nodes_list.push_back(v);
    }
    else nodes_list = *nodes_list_ptr;
    // std::cout << "starting degenearcy ..." << std::endl;
    get_degeneracy_ordering(nodes_list, degeneracy_ordering, nodeID_to_degeneracy_mapping);
    // std::cout << t.elapsed() << std::endl;
    
    size_t num_triangles = 0;
    for (size_t v : degeneracy_ordering) {
        std::vector<int> v_neighborhood;
        for (int u : _adj[v]) {
            if (nodeID_to_degeneracy_mapping[u] > nodeID_to_degeneracy_mapping[v]) {
                v_neighborhood.push_back(u);
            }
        }
        if (v_neighborhood.empty())
            continue;
        for (size_t i = 0; i < v_neighborhood.size() - 1; i++) {
            int u = v_neighborhood[i];
            _used.clear();
            for (int w : _adj[u])
                _used.add(w);
            for (size_t j = i + 1; j < v_neighborhood.size(); j++) {
                int w = v_neighborhood[j];
                if (_used.get(w)) {
                    _triangles[u]++;
                    _triangles[v]++;
                    _triangles[w]++;
                    std::cout << u << " " << v << " " << w << std::endl;
                    num_triangles++;
                    if (!(_nodes_status[u] && _nodes_status[v] && _nodes_status[w])) std::cout << "bad " << std::endl;
                }
            }
        }
    }
    return num_triangles;
}

void TriangleReduction::count_triangles() {
    // std::cout << "counting triangles..." << std::endl;
    clear_triangles();
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
                if (_nodes_status[w] && _used.get(w)) {
                    _triangles[u]++;
                    _triangles[v]++;
                    _triangles[w]++;
                    if (!(_nodes_status[u] && _nodes_status[v] && _nodes_status[w])) std::cout << "bad" << std::endl;
                }
            }
        }
    }
}

void TriangleReduction::count_triangles_containing_vertex(int const u) {
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

bool TriangleReduction::reduce(size_t const k, size_t const m) {
    size_t min_triangles = ceil(double(m - k) * (m - 2 * k) / 2);
    bool reduced = false;
    count_triangles();

    FastSet need_updating;
    need_updating.set_fast_set(_N);

    // std::cout << "reducing..." << std::endl;
    while (reduction_helper(min_triangles, need_updating)) 
        for (size_t v = 0; v < _N; v++) if (need_updating.get(v)) count_triangles_containing_vertex(v);
        reduced = true;

    return reduced;
}

void TriangleReduction::count_4clqs() {
    std::vector<size_t> degeneracy_ordering;
    std::vector<int> nodeID_to_degeneracy_mapping(_N, -1);

    // std::vector<size_t> place_holder_triangles(_N, 0);

    std::vector<int> nodes_list;
    for (int v = 0; v < int(_N); v++)
        if (_nodes_status[v])
            nodes_list.push_back(v);
    get_degeneracy_ordering(nodes_list, degeneracy_ordering, nodeID_to_degeneracy_mapping);

    for (int v : degeneracy_ordering) {
        std::vector<int> v_neighborhood;
        for (int u : _adj[v]) {
            if (nodeID_to_degeneracy_mapping[u] > nodeID_to_degeneracy_mapping[v]) {
                v_neighborhood.push_back(u);
            }
        }
        if (v_neighborhood.size() < 3) continue;
        // std::cout << "here" << std::endl;
        _triangles[v] += chiba_count_triangles(&v_neighborhood);
        // std::cout << "done" << std::endl;
    }
    // _triangles = place_holder_triangles;
}

void TriangleReduction::bruteforce_count_4clqs() {
    FastSet _used2;
    _used2.set_fast_set(_N);
    for (size_t u = 0; u < _N; u++) {
        std::vector<int> u_neighborhood = _adj[u];
        if (!_nodes_status[u] || u_neighborhood.size() < 3) continue;
        for (size_t v = 0; v < u_neighborhood.size() - 2; v++) {
            if (!_nodes_status[v] || v < u) continue;
            _used.clear();
            for (int w : _adj[v]) if (_nodes_status[w]) _used.add(w);
            for (size_t w = v + 1; w < u_neighborhood.size() - 1; w++) {
                if (!_used.get(w)) continue;
                _used2.clear();
                for (int x : _adj[w]) if (_nodes_status[w]) _used2.add(x);
                for (size_t x = w + 1; x < u_neighborhood.size(); x++) {
                    if (_used.get(x) && _used2.get(x)) {
                        _triangles[u]++;
                        _triangles[v]++;
                        _triangles[w]++;
                        _triangles[x]++;

                    }
                }
            }
        }
    }
}





