#include <iostream>
#include <vector>
#include <functional>

#include "kplex.h"
#include "../tools/fast_set.h"
#include "../tools/config.h"
#include "../tools/graph_tools.h"
#include "../bronKerbosch/bronKerbosch.h"

KPlex::KPlex(std::vector<std::vector<int>> const *adj, Config &config, std::vector<bool> const *nodes_status, size_t min_size) :
    _adj(*adj), _nodes_status(*nodes_status), _min_size(min_size)
{
    _N = _adj.size();
    _used.set_fast_set(_N);
    _enumerate_connected_k_plex = config.CONNECTED;
    _report_clique = config.RPT_CLQ;

    _maximal_clique_algo = new BronKerbosch(&_adj, nodes_status, min_size);
}

KPlex::~KPlex() {
    delete _maximal_clique_algo;
}

size_t KPlex::get_kplex_counter() {
    return _kplex_counter;
}

// ONE-NEAR-CLIQUES

void KPlex::get_one_near_cliques(std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> check, bool find_level_sets) {

    for (size_t node1 = 0; node1 < _adj.size() - 1; node1++) {
        if (!_nodes_status[node1]) continue;

        _used.clear();
        for (int const v : _adj[node1]) _used.add(v);

        for (size_t node2 = node1 + 1; node2 < _adj.size(); node2++) {
            if (!_nodes_status[node2] || _used.get(node2)) continue;

            std::vector<int> common_neighbors = _graph_tools.get_common_neighborhood(_adj, _nodes_status, _used, node2);
            std::vector<int> R = {static_cast<int>(node1), static_cast<int>(node2)};

            if (common_neighbors.empty() && !find_level_sets) {
                if (R.size() >= _min_size) {
                    if (_report_clique) {
                        for (int const v : R) std::cout << v << ',';
                        std::cout << std::endl;
                    }
                    _kplex_counter++;
                }
            }
            else {
                _maximal_clique_algo->solve_on(common_neighbors, R, check, find_level_sets);
                _kplex_counter += _maximal_clique_algo->_clique_counter;
            }
        }
    }
}

void KPlex::get_one_near_cliques_connected(std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> check, bool find_level_sets) {

    for (size_t node = 0; node < _adj.size(); node++) {
        if (!_nodes_status[node]) continue;

        std::vector<int> two_neighborhood_node = _graph_tools.get_two_neighbors(_adj, _nodes_status, _used, node);

        _used.clear();
        for (int const v : _adj[node]) _used.add(v);

        for (int const two_neighbor : two_neighborhood_node) {
            std::vector<int> common_neighbors = _graph_tools.get_common_neighborhood(_adj, _nodes_status, _used, two_neighbor);
            std::vector<int> R = {static_cast<int>(node), two_neighbor};

            if (common_neighbors.empty() && !find_level_sets) {
                if (R.size() >= _min_size) {
                    if (_report_clique) {
                        for (int const v : R) std::cout << v << ',';
                        std::cout << std::endl;
                    }
                    _kplex_counter++;
                }
            }
            else {
                _maximal_clique_algo->solve_on(common_neighbors, R, check, find_level_sets);
                _kplex_counter += _maximal_clique_algo->_clique_counter;
            }
        }
    }
}

// TWO-NEAR-CLIQUES

void KPlex::get_two_near_cliques() {
    std::vector<std::vector<int>> enumerated_two_near_cliques;

    // find all missing edges
    std::vector<std::vector<int>> missing_edges;
    for (int node1 = 0; node1 < static_cast<int>(_adj.size()) - 1; node1++) {
        if (!_nodes_status[node1]) continue;
        _used.clear();
        for (int const v : _adj[node1]) _used.add(v);
        for (int node2 = node1 + 1; node2 < static_cast<int>(_adj.size()); node2++) {
            if (_nodes_status[node2] && !_used.get(node2)) missing_edges.push_back({node1, node2});
        }
    }

    for (size_t i = 0; i < missing_edges.size() - 1; i++) {
        std::vector<int> &missing_edge1 = missing_edges[i];
        std::vector<int> common_neighbors_1 = _graph_tools.get_common_neighborhood(_adj, _nodes_status, _used, missing_edge1[0], missing_edge1[1]);

        for (size_t j = i + 1; j < missing_edges.size(); j++) {
            std::vector<int> &missing_edge2 = missing_edges[j];

            // std::cout << "missing edge 1: " << missing_edge1[0] << ", " << missing_edge1[1]<< "  missing edge 2: " << missing_edge2[0] << ", " << missing_edge2[1] << std::endl;

            if (!_graph_tools.are_valid_2NrClq_missing_edges(_adj, missing_edge1, missing_edge2)) continue;

            // get common neighbors of vertices
            std::vector<int> common_neighbors_2 = _graph_tools.get_common_neighborhood(_adj, _nodes_status, _used, missing_edge2[0], missing_edge2[1]);
            std::vector<int> common_neighbors;
            _used.clear();
            for (int const v : common_neighbors_1) _used.add(v);
            for (int const v : common_neighbors_2) if (_used.get(v)) common_neighbors.push_back(v);

            std::vector<int> R;
            _used.clear();
            for (int const v : {missing_edge1[0], missing_edge1[1], missing_edge2[0], missing_edge2[1]}) {
                if (!_used.get(v)) {
                    _used.add(v);
                    R.push_back(v);
                }
            }

            if (common_neighbors.empty()) {
                if (R.size() >= _min_size) {
                    _kplex_counter++;
                    if (_report_clique) {
                        // std::sort(R.begin(), R.end());
                        for (int const v : R) std::cout << v << ',';
                        std::cout << std::endl;
                    }
                }
            }
            else {
                _maximal_clique_algo->solve_on(common_neighbors, R);
                _kplex_counter += _maximal_clique_algo->_clique_counter;
            }
        }
    }
}

void KPlex::get_two_nr_clqs_conn_missing_edge_in_cmn_nbrhd(std::vector<int> &common_neighbors_1, int node1, int node2) {

    for (size_t i = 0; i < common_neighbors_1.size() - 1; i++) {

        int node3 = common_neighbors_1[i];
        if (node3 < node1) continue;

        for (size_t j = i + 1; j < common_neighbors_1.size(); j++) {
            int node4 = common_neighbors_1[j];
            if (_graph_tools.edge(_adj, node3, node4)) continue;

            std::vector<int> common_neighbors_2 = _graph_tools.get_common_neighborhood(_adj, _nodes_status, _used, node3, node4);

            std::vector<int> common_neighbors;
            _used.clear();
            for (int const v : common_neighbors_1) _used.add(v);
            for (int const v : common_neighbors_2) if (_used.get(v)) common_neighbors.push_back(v);

            std::vector<int> R = {node1, node2, node3, node4};

            if (common_neighbors.empty()) {
                if (R.size() >= _min_size) {
                    _kplex_counter++;
                    if (_report_clique) {
                        for (int const v : R) std::cout << v << ',';
                        std::cout << std::endl;
                    }
                }
            }
            else {
                _maximal_clique_algo->solve_on(common_neighbors, R);
                _kplex_counter += _maximal_clique_algo->_clique_counter;
            }
        }
    }
}

void KPlex::get_two_nr_clqs_conn_missing_edge_with_node1(std::vector<int> &common_neighbors_1, std::vector<int> &node1_two_neighborhood, size_t node2_index, int node1, int node2) {

    // find all pairs of missing missing edges ({node1, node2}, {node1, node3})
    // where node3 is in the two neighborhood of node1, edge(node2, node3), and
    // !N({node1, node2, node3}).empty()

    for (size_t two_neighbor_index = node2_index + 1; two_neighbor_index < node1_two_neighborhood.size(); two_neighbor_index++) {
        int node3 = node1_two_neighborhood[two_neighbor_index];
        if (!_graph_tools.edge(_adj, node2, node3)) continue;

        std::vector<int> common_neighbors;
        _used.clear();
        for (int const v : common_neighbors_1) _used.add(v);
        for (int const v : _adj[node3]) if (_used.get(v)) common_neighbors.push_back(v);

        if (common_neighbors.empty()) continue;

        std::vector<int> R = {node1, node2, node3};
        _maximal_clique_algo->solve_on(common_neighbors, R);
        _kplex_counter += _maximal_clique_algo->_clique_counter;
    }
}

void KPlex::get_two_nr_clqs_conn_missing_edge_with_node2(std::vector<int> &common_neighbors_1, int node1, int node2) {
    std::vector<int> node2_two_neighborhood = _graph_tools.get_two_neighbors(_adj, _nodes_status, _used, node2, node1);
    std::sort(node2_two_neighborhood.begin(), node2_two_neighborhood.end());

    for (int node3 : node2_two_neighborhood) {
        if (!_graph_tools.edge(_adj, node1, node3)) continue;

        std::vector<int> common_neighbors;
        _used.clear();
        for (int const v : common_neighbors_1) _used.add(v);
        for (int const v : _adj[node3]) if (_used.get(v)) common_neighbors.push_back(v);

        if (common_neighbors.empty()) continue;

        std::vector<int> R = {node1, node2, node3};
        _maximal_clique_algo->solve_on(common_neighbors, R);
        _kplex_counter += _maximal_clique_algo->_clique_counter;
    }
}

void KPlex::get_two_near_cliques_connected() {

    for (int node = 0; node < static_cast<int>(_adj.size()); node++) {
        if (!_nodes_status[node]) continue;
        std::vector<int> two_neighborhood = _graph_tools.get_two_neighbors(_adj, _nodes_status, _used, node);
        std::sort(two_neighborhood.begin(), two_neighborhood.end());

        for (size_t two_neighbor_index = 0; two_neighbor_index < two_neighborhood.size(); two_neighbor_index++) {
            int two_neighbor = two_neighborhood[two_neighbor_index];
            std::vector<int> common_neighbors_1 = _graph_tools.get_common_neighborhood(_adj, _nodes_status, _used, node, two_neighbor);
            get_two_nr_clqs_conn_missing_edge_in_cmn_nbrhd(common_neighbors_1, node, two_neighbor);
            get_two_nr_clqs_conn_missing_edge_with_node1(common_neighbors_1, two_neighborhood, two_neighbor_index, node, two_neighbor);
            get_two_nr_clqs_conn_missing_edge_with_node2(common_neighbors_1, node, two_neighbor);
        }
    }
}

void KPlex::get_two_plexes() {

    if (_enumerate_connected_k_plex) {
        _maximal_clique_algo->solve(_level_set_one_check_connected, true);
        _kplex_counter += _maximal_clique_algo->get_clique_counter();
        get_one_near_cliques_connected();
    }
    else {
        _maximal_clique_algo->solve(_level_set_one_check_connected, true);
        _kplex_counter += _maximal_clique_algo->get_clique_counter();
        get_one_near_cliques();
    }
}

void KPlex::get_three_plexes() {

    _maximal_clique_algo->solve(_level_set_two_check, true);
    _kplex_counter += _maximal_clique_algo->get_clique_counter();

    if (_enumerate_connected_k_plex) {
        get_one_near_cliques_connected(_level_set_one_check, true);
        get_two_near_cliques_connected();
    }
    else {
        get_one_near_cliques(_level_set_one_check, true);
        get_two_near_cliques();
    }
}
