 #include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <unordered_map>
#include <string>
#include <tuple>


#include "triangle.h"
#include "../tools/timer.h"


TriangleReduction::TriangleReduction(std::vector<std::vector<int>>& adj, std::vector<bool>& nodes_status, timer &t, double time_limit) :
    _adj(adj), _nodes_status(nodes_status), _t(t), _time_limit(time_limit)
{
    _N = _adj.size();
    _triangles = new std::vector<size_t>(_N, 0);
    _used.set_fast_set(_N);
 
}

TriangleReduction::TriangleReduction(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, std::vector<size_t>* four_cliques, timer &t, double time_limit) :
    _adj(adj), _nodes_status(nodes_status), _t(t), _time_limit(time_limit)
{
    _N = _adj.size();
    _triangles = four_cliques;
    _used.set_fast_set(_N);
    is_sub_call = true;
}

TriangleReduction::~TriangleReduction() {
    if (!is_sub_call)
        delete _triangles;
}

size_t TriangleReduction::get_total_num_triangles() {
    size_t count = 0;
    for (size_t u : (*_triangles)) count += u;
    return count;
}

size_t TriangleReduction::get_triangles_containing_vertex(int const u) {
    size_t num_triangles = 0;
    std::vector<int> u_neighborhood = _adj[u];
    if (u_neighborhood.empty()) return 0;
    for (size_t i = 0; i < u_neighborhood.size() - 1; i++) {
        int v = u_neighborhood[i];
        if (!_nodes_status[v]) continue;
        _used.clear();
        for (int w : _adj[v]) _used.add(w);
        for (size_t j = i + 1; j < u_neighborhood.size(); j++) {
            int w = u_neighborhood[j];
            if (_nodes_status[w] && _used.get(w)) num_triangles += 1;
        }
    }
    return num_triangles;
}

bool TriangleReduction::is_valid_vertex(size_t const v, size_t const k, size_t const m) {
    return get_triangles_containing_vertex(v) >= ceil(double(m - k) * (m - 2 * k) / 2);
}

void TriangleReduction::bruteforce_count_triangles() {
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
                    _triangles->at(u)++;
                    _triangles->at(v)++;
                    _triangles->at(w)++;
                    if (!(_nodes_status[u] && _nodes_status[v] && _nodes_status[w])) std::cout << "bad" << std::endl;
                }
            }
        }
    }
    return;
    std::unordered_map<std::string, bool> mapping;
    for (int v = 0; v < (int) _N; v++) {
        for (int u : _adj[v]) {
            if (v < u) {
                std::string edge = std::to_string(v) + " " + std::to_string(u);
                mapping[edge] = true;
            }
        }
    }
    for (size_t v = 0; v < _N - 2; v++) {
        for (size_t w = v + 1; w < _N - 1; w++) {
            for (size_t u = w + 1; u < _N; u++){
                std::string vs = std::to_string(v);
                std::string ws = std::to_string(w);
                std::string us = std::to_string(u);
                std::vector<std::string> edges = {vs + " " + ws, vs + " " + us, ws + " " + us};
                bool is_tri = true;
                for (std::string edge : edges) {
                    if (mapping.find(edge) == mapping.end()) {
                        is_tri = false;
                        break;
                    }
                }
                if (is_tri) {
                    _triangles->at(u)++;
                    _triangles->at(v)++;
                    _triangles->at(w)++;
                }
            }
        }
    }
}

size_t TriangleReduction::chiba_count_triangles(std::vector<size_t> const &degeneracy_ordering, std::vector<int> const &nodeID_to_degeneracy_mapping, std::vector<std::vector<int>> &shadow_adj) {
    
    size_t num_triangles = 0;
    for (size_t v : degeneracy_ordering) {
        std::vector<int> &v_neighborhood = shadow_adj[v];
        std::sort(v_neighborhood.begin(), v_neighborhood.end(),
                  [&nodeID_to_degeneracy_mapping] (size_t a, size_t b)
                  {return nodeID_to_degeneracy_mapping[a] < nodeID_to_degeneracy_mapping[b];});
        if (v_neighborhood.size() < 2)
            continue;
        for (size_t i = 0; i < v_neighborhood.size() - 1; i++) {
            int u = v_neighborhood[i];
            // std::cout << "here? " << u  << std::endl;
            // for (int w : shadow_adj[u]) std::cout << u << " ";
            _used.clear();
            for (int w : shadow_adj[u]) {
                _used.add(w);
            }
            // std::cout << "and here..?" << std::endl;
            for (size_t j = i + 1; j < v_neighborhood.size(); j++) {

                int w = v_neighborhood[j];
                // std::cout << "and here?" << std::endl;
                if (_used.get(w)) {
                    _triangles->at(u)++;
                    _triangles->at(v)++;
                    _triangles->at(w)++;
                    num_triangles++;
                }
            }
        }
    }
    return num_triangles;
}

void TriangleReduction::count_triangles() {
    timer t;
    std::vector<std::vector<int>> shadow_adj(_N);
    std::vector<size_t> degeneracy_ordering;
    degeneracy_ordering.reserve(_N);
    std::vector<int> nodeID_to_degeneracy_mapping(_N, -1);

    std::vector<std::tuple<size_t, size_t>> nodes_and_degs; 
    for (size_t v = 0; v < _N; v++) {
        if (!_nodes_status[v]) continue;
        size_t deg = 0;
        for (int u : _adj[v]) if (_nodes_status[u]) deg++; 
        nodes_and_degs.push_back(std::make_tuple(v, deg));
    }
    _graph_tools.get_degeneracy_ordering(_adj, _used, nodes_and_degs, degeneracy_ordering, nodeID_to_degeneracy_mapping, shadow_adj, t);

    chiba_count_triangles(degeneracy_ordering, nodeID_to_degeneracy_mapping, shadow_adj);
}

void TriangleReduction::count_triangles_containing_vertex(int const u) {
    _triangles->at(u) = 0;
    std::vector<int> u_neighborhood = _adj[u];
    if (u_neighborhood.empty()) return;
    for (size_t i = 0; i < u_neighborhood.size() - 1; i++) {
        int v = u_neighborhood[i];
        if (!_nodes_status[v]) continue;
        _used.clear();
        for (int w : _adj[v]) _used.add(w);
        for (size_t j = i + 1; j < u_neighborhood.size(); j++) {
            int w = u_neighborhood[j];
            if (_nodes_status[w] && _used.get(w)) _triangles->at(u)++;
        }
    }
}

bool TriangleReduction::reduction_helper(size_t min_triangles, FastSet &need_updating) {
    bool reduced = false;
    need_updating.clear();

    for (size_t v = 0; v < _N; v++) {
        if (!_nodes_status[v] || _triangles->at(v) >= min_triangles) continue;
        _nodes_status[v] = false;
        _triangles->at(v) = 0;
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
    while (reduction_helper(min_triangles, need_updating) && _t.elapsed() < _time_limit) 
        for (size_t v = 0; v < _N; v++) if (need_updating.get(v)) count_triangles_containing_vertex(v);
        reduced = true;

    return reduced;
} 

//==================================================================================================//


std::vector<std::unordered_map<int, size_t>> TriangleReduction::edge_count_triangles(std::vector<std::unordered_map<int, bool>> const &edges_status) {
    std::vector<std::unordered_map<int, size_t>> edge_triangles(_N);

    for (int v = 0; v < (int) _N - 1; v++) {
        if (!_nodes_status[v]) continue;
         _used.clear();
        for (int u : _adj[v]) {
            if (edges_status[v].at(u))
                _used.add(u);
        }

        for (int w : _adj[v]) {
            edge_triangles[v][w] = 0;
            if (!_nodes_status[w] || !edges_status[v].at(w)) continue;
        
            size_t common_neighborhood_size = 0;
            for (int u : _adj[w]) {
                if (edges_status[w].at(u) && _used.get(u))
                    common_neighborhood_size += 1;
            }
            edge_triangles[v][w] = common_neighborhood_size;
        }
    }

    return edge_triangles;
}


size_t TriangleReduction::edge_reduce_helper(std::vector<std::unordered_map<int, bool>> &edges_status, size_t const min_triangles) {
    size_t num_edges_reduced = 0;

    std::vector<std::unordered_map<int, size_t>> edge_triangles = edge_count_triangles(edges_status);

    for (int v = 0; v < (int) _N - 1; v++) {
        if (!_nodes_status[v]) continue;
        for (int w : _adj[v]) {
            if (edges_status[v].at(w) && edge_triangles[v][w] < min_triangles) {
                edges_status[v].at(w) = false;
                edges_status[w].at(v) = false;
                num_edges_reduced += 1;
            }
        }
    }

    return num_edges_reduced;
}

size_t TriangleReduction::edge_reduce(std::vector<std::unordered_map<int, bool>> &edges_status, size_t const k, size_t const q) {
    bool reduced = false;
    size_t num_edges_reduced = 0;
    size_t current_num_edges_reduced = 0;

    size_t min_triangles = q - (2 * k);

    do {
        current_num_edges_reduced = edge_reduce_helper(edges_status, min_triangles);
        num_edges_reduced += current_num_edges_reduced;
    }
    while (current_num_edges_reduced != 0);

    for (size_t v = 0; v < _N; v++) {
        if (!_nodes_status[v]) continue;
        size_t deg = 0;
        for (int u : _adj[v])
            if (edges_status[v].at(u)) {
                deg += 1;
            }
        // if (deg == 0)
        if (deg < q - k)
            _nodes_status[v] = false;
    }

    return num_edges_reduced;
}

std::unordered_map<std::pair<int, int>, size_t, pair_hash> TriangleReduction::edge_count_triangles_new(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status) {
    std::unordered_map<std::pair<int, int>, size_t, pair_hash> edge_triangles;
    for (int v = 0; v < (int) _adj.size(); v++) {
        if (!_nodes_status[v]) continue;
        for (int u : _adj[v]) {
            if (v < u && edges_status.at(std::make_pair(v, u)))
                edge_triangles[std::make_pair(v, u)] = 0;
        }
    }

    for (int v = 0; v < (int) _adj.size(); v++) {
        if (!_nodes_status[v]) continue;
        _used.clear();
        for (int u : _adj[v]) {
            if (v < u && edges_status.at(std::make_pair(v, u)))
                _used.add(u);
        }

        for (int u : _adj[v]) {
            if (!_used.get(u)) continue;

            for (int w : _adj[u]) {
                if (u < w && _used.get(w) && edges_status.at(std::make_pair(u, w))) {
                    edge_triangles.at(std::make_pair(v, u)) += 1;
                    edge_triangles.at(std::make_pair(v, w)) += 1;
                    edge_triangles.at(std::make_pair(u, w)) += 1;
                }
            }
        }
    }

    return edge_triangles;
}

size_t TriangleReduction::count_triangles_containing_edge(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, int const v, int const u) {
    _used.clear();
    for (int w : _adj[v]) {

        std::pair<int, int> vw_edge;
        if (v < w) vw_edge = std::make_pair(v, w);
        else vw_edge = std::make_pair(w, v);

        if (edges_status.at(vw_edge))
             _used.add(w);
    }

    size_t common_neighborhood_size = 0;
    for (int w : _adj[u]) {

        std::pair<int, int> uw_edge;
        if (u < w) uw_edge = std::make_pair(u, w);
        else uw_edge = std::make_pair(w, u);

        if (edges_status.at(uw_edge) && _used.get(w))
            common_neighborhood_size += 1;
    }

    return common_neighborhood_size;
}

std::unordered_map<std::pair<int, int>, size_t, pair_hash> TriangleReduction::bruteforce_edge_count_triangles(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status) {
    std::unordered_map<std::pair<int, int>, size_t, pair_hash> edge_triangles;
    for (int v = 0; v < (int) _adj.size(); v++) {
        if (!_nodes_status[v]) continue;
        for (int u : _adj[v]) {
            if (v < u && edges_status.at(std::make_pair(v, u)))
                edge_triangles[std::make_pair(v, u)] = 0;
        }
    }

    for (int v = 0; v < (int) _N; v++) {
        for (int u : _adj[v]) {
            if (v < u && edges_status.at(std::make_pair(v, u))) {
                edge_triangles.at(std::make_pair(v, u)) = count_triangles_containing_edge(edges_status, v, u);
            }
        }
    }

    return edge_triangles;
}


size_t TriangleReduction::edge_reduce_helper_new(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, std::unordered_map<std::pair<int, int>, size_t, pair_hash> &edge_triangles, std::vector<std::pair<int, int>> &need_updating, std::unordered_map<std::pair<int, int>, bool, pair_hash> &already_needs_updating, size_t const min_triangles) {

    size_t num_edges_reduced = 0;
    
    for (int v = 0; v < (int) _adj.size(); v++) {
        _used.clear();
        for (int u : _adj[v]) {
            std::pair<int, int> vu_edge;
            if (v < u) vu_edge = std::make_pair(v, u);
            else vu_edge = std::make_pair(u, v);
            if (edges_status.at(vu_edge))
                _used.add(u);
        }
        for (int u : _adj[v]) {
            if (v < u && _used.get(u) && edge_triangles.at(std::make_pair(v, u)) < min_triangles) {
                edges_status.at(std::make_pair(v, u)) = false;
                num_edges_reduced += 1;

                for (int w : _adj[u]) {

                    if (!_used.get(w)) continue;

                    std::pair<int, int> uw_edge;
                    if (u < w) uw_edge = std::make_pair(u, w);
                    else uw_edge = std::make_pair(w, u);
                    if (edges_status.at(uw_edge) && already_needs_updating.find(uw_edge) == already_needs_updating.end()) {
                        need_updating.push_back(uw_edge);
                        already_needs_updating[uw_edge] = true;
                    }

                    std::pair<int, int> vw_edge;
                    if (v < w) vw_edge = std::make_pair(v, w);
                    else vw_edge = std::make_pair(w, v);
                    if (edges_status.at(vw_edge) && already_needs_updating.find(vw_edge) == already_needs_updating.end()) {
                        need_updating.push_back(vw_edge);
                        already_needs_updating[vw_edge] = true;
                    }

                }
            }
        }
    }

    return num_edges_reduced;
}

size_t TriangleReduction::edge_reduce_new(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, size_t const k, size_t const q) {

    size_t min_triangles = q - (2 * k);
    size_t num_edges_reduced = 0;
    size_t current_num_edges_reduced = 0;
    std::vector<std::pair<int, int>> need_updating;
    std::unordered_map<std::pair<int, int>, bool, pair_hash> already_needs_updating;

    // std::unordered_map<std::pair<int, int>, size_t, pair_hash> edge_triangles;

    std::unordered_map<std::pair<int, int>, size_t, pair_hash> edge_triangles = edge_count_triangles_new(edges_status);

    current_num_edges_reduced = edge_reduce_helper_new(edges_status, edge_triangles, need_updating, already_needs_updating, min_triangles);

    while (current_num_edges_reduced > 0) {
        num_edges_reduced += current_num_edges_reduced;
        for (std::pair<int, int> edge : need_updating) {
            edge_triangles.at(edge) = count_triangles_containing_edge(edges_status, edge.first, edge.second);
        }
        need_updating.clear();
        already_needs_updating.clear();
        current_num_edges_reduced = current_num_edges_reduced = edge_reduce_helper_new(edges_status, edge_triangles, need_updating, already_needs_updating, min_triangles);
    }

    // do {
    //     edge_triangles = edge_count_triangles_new(edges_status);
    //     current_num_edges_reduced = edge_reduce_helper_new(edges_status, edge_triangles, need_updating, min_triangles);
    //     num_edges_reduced += current_num_edges_reduced;
    // }
    // while (current_num_edges_reduced != 0);

    for (int v = 0; v < (int) _N; v++) {
        if (!_nodes_status[v]) continue;
        size_t deg = 0;
        for (int u : _adj[v]) {

            std::pair<int, int> vu_edge;
            if (v < u) vu_edge = std::make_pair(v, u);
            else vu_edge = std::make_pair(u, v);

            if (edges_status.at(vu_edge)) {
                deg += 1;
            }
        }
        if (deg < q - k)
            _nodes_status[v] = false;
    }

    return num_edges_reduced;
}

std::pair<int, int> get_edge_pair(int v, int u) {
    std::pair<int, int> edge;
    if (v < u) edge = std::make_pair(v, u);
    else edge = std::make_pair(u, v);

    return edge;
}

size_t TriangleReduction::edge_reduce_helper_new2(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, std::unordered_map<std::pair<int, int>, size_t, pair_hash> &edge_triangles, size_t const min_triangles) {
    size_t num_edges_reduced = 0;

    for (int v = 0; v < (int) _N; v++) {
        if (!_nodes_status[v]) continue;

        _used.clear();
        for (int u : _adj[v]) {
            if (edges_status.at(get_edge_pair(v, u))) {
                _used.add(u);
            }
        }

        for (int u : _adj[v]) {
            std::pair<int, int> vu_edge = get_edge_pair(v, u);
            if (v < u && _used.get(u) && edge_triangles.at(vu_edge) < min_triangles) {
                edges_status.at(vu_edge) = false;
                _used.remove(u);
                num_edges_reduced += 1;

                for (int w : _adj[u]) {
                    if (!_used.get(w)) continue;
                    std::pair<int, int> uw_edge = get_edge_pair(u, w);
                    std::pair<int, int> vw_edge = get_edge_pair(v, w);

                    if (edges_status.at(uw_edge) && edges_status.at(vw_edge)) {
                        edge_triangles.at(uw_edge) -= 1;
                        edge_triangles.at(vw_edge) -= 1;
                    }
                }
            }
        }
    }
    return num_edges_reduced;
}

void TriangleReduction::delete_vertices_update_triangles(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, std::unordered_map<std::pair<int, int>, size_t, pair_hash> &edge_triangles, size_t const k, size_t const q) {
    for (int v = 0; v < (int) _N; v++) {
        if (!_nodes_status[v]) continue;

        _used.clear();
        size_t deg = 0;
        for (int u : _adj[v]) {
            if (edges_status.at(get_edge_pair(v, u))) {
                deg += 1;
                _used.add(u);
            }
        }

        if (deg >= q - k) continue;

        _nodes_status[v] = false;

        for (int u : _adj[v]) {
            if (!_used.get(u)) continue;
            for (int w : _adj[u]) {
                if (w < u || !_used.get(w)) continue;
                if (edges_status.at(get_edge_pair(u, w))) {
                    edge_triangles.at(get_edge_pair(u, w)) -= 1;
                }
            }
        }

        for (int u : _adj[v])
            edges_status.at(get_edge_pair(v, u)) = false;
    }
}

size_t TriangleReduction::edge_reduce_new2(std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, size_t const k, size_t const q) {
    size_t min_triangles = q - (2 * k);
    size_t total_edges_reduced = 0;
    size_t edges_reduced = 0;

    std::unordered_map<std::pair<int, int>, size_t, pair_hash> edge_triangles = edge_count_triangles_new(edges_status);

    // size_t exhaustive_count = 0;

    do {
        // std::cout << "triangle iteration number: " << exhaustive_count << std::endl;
        // exhaustive_count++;

        edges_reduced = edge_reduce_helper_new2(edges_status, edge_triangles, min_triangles);
        total_edges_reduced += edges_reduced;
        delete_vertices_update_triangles(edges_status, edge_triangles, k, q);
    } while (edges_reduced > 0 && _t.elapsed() < _time_limit);

    return total_edges_reduced;

}







