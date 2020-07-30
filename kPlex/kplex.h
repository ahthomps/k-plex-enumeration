#include <iostream>
#include <vector>
#include <functional>

#include "../bronKerbosch/bronKerbosch.h"
#include "../tools/fast_set.h"
#include "../tools/config.h"
#include "../tools/graph_tools.h"

#ifndef KPLEX_H_
#define KPLEX_H_

class KPlex {

  public:
    bool _enumerate_connected_k_plex = false;
    size_t _kplex_counter = 0;
    bool _report_clique = false;

    KPlex(std::vector<std::vector<int>> const *adj, Config &config);
    ~KPlex();

    size_t get_kplex_counter();

    void get_one_near_cliques(std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> check=([](std::vector<std::vector<int>> const * adj, std::vector<int> R, std::vector<int> level_set_one, std::vector<int> level_set_two) -> bool {return true;}), bool find_level_sets=false);
    void get_one_near_cliques_connected(std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> check=([](std::vector<std::vector<int>> const * adj, std::vector<int> R, std::vector<int> level_set_one, std::vector<int> level_set_two) -> bool {return true;}), bool find_level_sets=false);

    void get_two_near_cliques();
    void get_two_near_cliques_connected();

    void get_two_plexes();
    void get_three_plexes();

    void get_one_near_cliques_wrt_three_plexes() {
        if (_enumerate_connected_k_plex) get_one_near_cliques_connected(_level_set_one_check, true);
        else get_one_near_cliques(_level_set_one_check, true);
    };
    void get_maximal_cliques_wrt_three_plexes() {
        _maximal_clique_algo->solve(_level_set_two_check, true);
        _kplex_counter += _maximal_clique_algo->get_clique_counter();
    };

  private:
    const std::vector<std::vector<int>>& _adj;
    FastSet _used;
    GraphTools _graph_tools;
    size_t _N;

    BronKerbosch* _maximal_clique_algo;

    void get_two_nr_clqs_conn_missing_edge_in_cmn_nbrhd(std::vector<int> &common_neighbors_1, int node1, int node2);
    void get_two_nr_clqs_conn_missing_edge_with_node1(std::vector<int> &common_neighbors_1, std::vector<int> &node1_two_neighborhood, size_t node2_index, int node1, int node2);
    void get_two_nr_clqs_conn_missing_edge_with_node2(std::vector<int> &common_neighbors_1, int node1, int node2);

    std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> _bruteforce_check = [&] (std::vector<std::vector<int>> const * p_adj, std::vector<int> R, std::vector<int> level_set_one, std::vector<int> level_set_two) -> bool {
        std::vector<std::vector<int>> const &adj = *p_adj;

        if (R.size() < 2) return true;

        _used.clear();
        for (int const r : R) _used.add(r);

        for (size_t node = 0; node < adj.size(); node ++) {
            if (_used.get(node)) continue;
            size_t neighbors_in_clique = 0;
            for (int const neighbor : adj[node]) if (_used.get(neighbor)) neighbors_in_clique++;
            if (R.size() - 1 == neighbors_in_clique) return false;
        }
        return true;
    };

    std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> _optimized_check = [&] (std::vector<std::vector<int>> const * p_adj, std::vector<int> R, std::vector<int> level_set_one, std::vector<int> level_set_two) -> bool {
        std::vector<std::vector<int>> const &adj = *p_adj;

        if (R.size() < 2) return true;

        _used.clear();
        for (int const r : R) _used.add(r);

        for (int const clique_node : {R[0], R[1]}) {
            for (int const clique_node_neighbor : adj[clique_node]) {
                if (_used.get(clique_node_neighbor)) continue;
                size_t neighbors_in_clique = 0;
                for (int const neighbor : adj[clique_node_neighbor]) if (_used.get(neighbor)) neighbors_in_clique++;
                if (R.size() - 1 == neighbors_in_clique) return false;
            }
        }
        return true;
    };

    std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> _level_set_one_check_connected = [&] (std::vector<std::vector<int>> const * p_adj, std::vector<int> R, std::vector<int> level_set_one, std::vector<int> level_set_two) -> bool {
        return R.size() < 2 || level_set_one.empty();
    };

    std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> _level_set_one_check = [&] (std::vector<std::vector<int>> const * p_adj, std::vector<int> R, std::vector<int> level_set_one, std::vector<int> level_set_two) -> bool {
        return level_set_one.empty();
    };

    std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> _level_set_two_check = [&] (std::vector<std::vector<int>> const * p_adj, std::vector<int> R, std::vector<int> level_set_one, std::vector<int> level_set_two) -> bool {
        return (level_set_one.empty() && level_set_two.empty());

    };

};

#endif
