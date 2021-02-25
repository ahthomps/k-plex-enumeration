#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <unordered_map>
#include <string>
#include <tuple>


#include "four_cliques.h"
#include "../tools/timer.h"

FourCliquesReduction::FourCliquesReduction(std::vector<std::vector<int>>& adj, std::vector<bool>& nodes_status) :
    _adj(adj), _nodes_status(nodes_status)
{
    _N = _adj.size();
    _four_cliques = new std::vector<size_t>(_N, 0);
    _used.set_fast_set(_N);

    _triangles = new TriangleReduction(adj, nodes_status, _four_cliques);
}

FourCliquesReduction::~FourCliquesReduction() {
	delete _four_cliques;
	delete _triangles;
}

size_t FourCliquesReduction::get_total_num_four_cliques() {
    size_t count = 0;
    for (size_t u : (*_four_cliques)) count += u;
    return count;
}

void FourCliquesReduction::bruteforce_count_4clqs() {
	FastSet used_too;
	used_too.set_fast_set(_N);

	for (int v = 0; v < (int) _N; v++) {
		if (_nodes_status[v])
    		_four_cliques->at(v) = count_four_cliques_containing_vertex(v, used_too);
    }
    return;
    // std::unordered_map<std::string, bool> mapping;
    // for (int v = 0; v < (int) _N; v++) {
    //     for (int u : _adj[v]) {
    //         if (v < u) {
    //             std::string edge = std::to_string(v) + " " + std::to_string(u);
    //             mapping[edge] = true;
    //         }
    //     }
    // }
    // for (size_t v = 0; v < _N - 3; v++) {
    //     for (size_t w = v + 1; w < _N - 2; w++) {
    //         for (size_t u = w + 1; u < _N - 1; u++){
    //             for (size_t x = u + 1; x < _N; x++) {
    //                 std::string vs = std::to_string(v);
    //                 std::string ws = std::to_string(w);
    //                 std::string us = std::to_string(u);
    //                 std::string xs = std::to_string(x);
    //                 std::vector<std::string> edges = {vs + " " + ws, vs + " " + us, vs + " " + xs, ws + " " + us, 
    //                                                   ws + " " + xs, us + " " + xs};
    //                 bool is_tri = true;
    //                 for (std::string edge : edges) {
    //                     if (mapping.find(edge) == mapping.end()) {
    //                         is_tri = false;
    //                         break;
    //                     }
    //                 }
    //                 if (is_tri) {
    //                     _four_cliques->at(u)++;
    //                     _four_cliques->at(v)++;
    //                     _four_cliques->at(w)++;
    //                     _four_cliques->at(x)++;
    //                 }
    //             }
    //         }
    //     }
    // }
}

void FourCliquesReduction::count_4clqs() {
    timer t;
    std::vector<std::vector<int>> shadow_adj(_N);
    std::vector<size_t> degeneracy_ordering;
    degeneracy_ordering.reserve(_N);
    std::vector<int> nodeID_to_degeneracy_mapping(_N, -1);

    // get degeneracy ordering
    std::vector<std::tuple<size_t, size_t>> nodes_and_degs; 
    for (size_t v = 0; v < _N; v++) {
        if (!_nodes_status[v]) continue;
        size_t deg = 0;
        for (int u : _adj[v]) if (_nodes_status[u]) deg++; 
        nodes_and_degs.push_back(std::make_tuple(v, deg));
    }
    _graph_tools.get_degeneracy_ordering(_adj, _used, nodes_and_degs, degeneracy_ordering, nodeID_to_degeneracy_mapping, shadow_adj, t);

    std::vector<std::vector<int>> old_shadow_adj_lists;
    std::vector<int> old_mapping;
    for (size_t v : degeneracy_ordering) {
        _used.clear();
        old_mapping.clear();
        old_shadow_adj_lists.clear();

        std::vector<size_t> v_neighborhood;
        for (int u : shadow_adj[v]) v_neighborhood.push_back((size_t) u);
        // sort N(v) to match degeneracy ordering
        std::sort(v_neighborhood.begin(), v_neighborhood.end(),
                  [&nodeID_to_degeneracy_mapping] (size_t a, size_t b)
                  {return nodeID_to_degeneracy_mapping[a] < nodeID_to_degeneracy_mapping[b];});
        // for each u in N(v) save its old mapping to the original degeneracy ordering and 
        // set its new mapping value to its place in the N(v) degeneracy ordering
        for (size_t i = 0; i < v_neighborhood.size(); i++) {
            size_t u = v_neighborhood[i];
            _used.add(u);
            old_mapping.push_back(nodeID_to_degeneracy_mapping[u]);
            nodeID_to_degeneracy_mapping[u] = (int) i;
        }
        // for each u in N(v) save its old shadow_adj_list and find the new shadow_adj_list which contains only
        // vertices in N(v)
        for (size_t u : v_neighborhood) {
            std::vector<int> u_shadow_adj_list;
            for (int w : shadow_adj[u]) {
                if (_used.get(w)) u_shadow_adj_list.push_back(w);
            }
            old_shadow_adj_lists.push_back(shadow_adj[u]);
            shadow_adj[u] = u_shadow_adj_list;
        }

        // use triangle counting function to count and update triangle counters
        _four_cliques->at(v) += _triangles->chiba_count_triangles(v_neighborhood, nodeID_to_degeneracy_mapping, shadow_adj);

        // set mapping and shadow_adj back to original state
        for (size_t i = 0; i < v_neighborhood.size(); i++) {
            size_t u = v_neighborhood[i];
            shadow_adj[u] = old_shadow_adj_lists[i];
            nodeID_to_degeneracy_mapping[u] = old_mapping[i];
        }

    }
}

size_t FourCliquesReduction::count_four_cliques_containing_vertex(int v, FastSet &used_too) {

	size_t four_cliques_counter = 0;
	std::vector<int> const &v_neighborhood = _adj[v];
	if (v_neighborhood.size() < 3) return four_cliques_counter;
	for (size_t i = 0; i < v_neighborhood.size() - 2; i++) {
		int u = v_neighborhood[i];
		if (!_nodes_status[u]) continue;

		_used.clear();
		for (int w : _adj[u]) _used.add(w);

		for (size_t j = i + 1; j < v_neighborhood.size() - 1; j++) {
			int w = v_neighborhood[j];
			if (!_nodes_status[w] || !_used.get(w)) continue;

			used_too.clear();
			for (int x : _adj[w]) if (_used.get(x)) used_too.add(x);

			for (size_t k = j + 1; k < v_neighborhood.size(); k++) {
				int x = v_neighborhood[k];
				if (_nodes_status[x] && used_too.get(x)) four_cliques_counter += 1;
			}
		}
	}
	return four_cliques_counter;

}

bool FourCliquesReduction::reduction_helper(size_t min_four_cliques, FastSet &need_updating) {
    bool reduced = false;
    need_updating.clear();

    for (size_t v = 0; v < _N; v++) {
        if (!_nodes_status[v] || _four_cliques->at(v) >= min_four_cliques) continue;
        _nodes_status[v] = false;
        _four_cliques->at(v) = 0;
        reduced = true;
        if (need_updating.get(v)) need_updating.remove(v);
        for (int u : _adj[v]) if (_nodes_status[u] && !need_updating.get(u)) need_updating.add(u);  
    }

    return reduced;
}

bool FourCliquesReduction::reduce(size_t const k, size_t const m) {
    size_t min_four_cliques = ceil(double((m - k) * (m - 2 * k) * (m - 3 * k)) / 6);
    bool reduced = false;
    count_4clqs();

    FastSet need_updating;
    need_updating.set_fast_set(_N);

    FastSet used_too;
    used_too.set_fast_set(_N);

    while (reduction_helper(min_four_cliques, need_updating)) 
        for (size_t v = 0; v < _N; v++) if (need_updating.get(v)) _four_cliques->at(v) = count_four_cliques_containing_vertex(v, used_too);
        reduced = true;

    return reduced;
} 


