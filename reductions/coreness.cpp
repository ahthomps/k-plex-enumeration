#include <iostream>
#include <vector>

#include "coreness.h"
#include "../tools/linked_list.h"

CorenessReduction::CorenessReduction(std::vector<std::vector<int>> *adj) :
    _adj(*adj)
{
    _N = _adj.size();
    nodes_status.resize(_N, true);
    nodes_degree.resize(_N, 0);
    get_nodes_by_deg();
}

CorenessReduction::~CorenessReduction() {
    // for (LinkedList *p_llist : nodes_priority) delete p_llist;
}

void CorenessReduction::get_nodes_by_deg() {
    nodes_by_deg.resize(_N, {});
    for (size_t node = 0; node < _adj.size(); node++) {
        size_t degree = _adj[node].size();
        nodes_by_deg[degree].push_back(static_cast<int>(node));
        nodes_degree[node] = degree;
    }
}

// void CorenessReduction::get_nodes_priority() {
//     nodes_priority.clear();
//     for (size_t i = 0; i < _N; i++) {
//         LinkedList *p_llist = new LinkedList;
//         nodes_priority.push_back(p_llist);
//     }
//     for (size_t node = 0; node < _adj.size(); node++) {
//         size_t degree = _adj[node].size();
//         nodes_priority[degree].add(static_cast<int>);
//         nodes_degree[node] = degree;
//     }
// }

void CorenessReduction::print_nodes_by_degree() {
    for (size_t i = 0; i < nodes_by_deg.size(); i++) {
        std::cout << i << ": ";
        for (int v : nodes_by_deg[i]) std::cout << v << ",";
        std::cout << std::endl;
    }
}

void CorenessReduction::adjust_neighbors(int node_to_remove) {
    for (int v : _adj[node_to_remove]) {
        if (!nodes_status[v]) continue;

        size_t old_degree = nodes_degree[v];

        size_t index_v = 0;
        for (int u : nodes_by_deg[old_degree]) {
            if (u == v) break;
            index_v++;
        }
        nodes_by_deg[old_degree][index_v] = nodes_by_deg[old_degree][nodes_by_deg[old_degree].size() - 1];
        nodes_by_deg[old_degree].pop_back();

        nodes_by_deg[old_degree - 1].push_back(v);
        nodes_degree[v] = nodes_degree[v] - 1;
    }
}

std::vector<bool>* CorenessReduction::reduce(size_t clique_size, size_t k_plex_num) {
    size_t min_degree = clique_size - k_plex_num;
    size_t current_degree = 0;

    while (current_degree != min_degree) {
        std::vector<int> &nodes = nodes_by_deg[current_degree];

        if (nodes.empty()) {
            current_degree++;
            continue;
        }

        while (!nodes.empty()) {
            int node_to_remove = nodes[0];
            adjust_neighbors(node_to_remove);
            nodes[0] = nodes[nodes.size() - 1];
            nodes.pop_back();
            nodes_status[node_to_remove] = false;
        }

        current_degree = 0;
    }

    return &nodes_status;
}

void CorenessReduction::print_removed_nodes() {
    for (size_t i = 0; i < _N; i++) {
        if (!nodes_status[i]) std::cout << i << std::endl;
    }
}
