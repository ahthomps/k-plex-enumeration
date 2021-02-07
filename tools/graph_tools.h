#include <iostream>
#include <vector>
#include <functional>

#include "fast_set.h"

#ifndef GRAPH_TOOLS_H_
#define GRAPH_TOOLS_H_

class GraphTools {

    public:

        GraphTools() {};

        std::vector<int> get_common_neighborhood(std::vector<std::vector<int>> const &adj, std::vector<bool> const &nodes_status, FastSet &used, int node1, int node2) {
            std::vector<int> common_neighbors;
            used.clear();
            for (int const v : adj[node2]) if (nodes_status[v]) used.add(v);
            for (int const v : adj[node1]) {
                if (used.get(v)) common_neighbors.push_back(v);
                else used.remove(v);
            }

            return common_neighbors;
        };

        std::vector<int> get_common_neighborhood(std::vector<std::vector<int>> const &adj, std::vector<bool> const &nodes_status, FastSet &used, int node1) {
            std::vector<int> common_neighbors;
            for (int const v : adj[node1]) {
                if (nodes_status[v] && used.get(v)) common_neighbors.push_back(v);
                else used.remove(v);
            }

            return common_neighbors;
        };

        bool are_valid_2NrClq_missing_edges(std::vector<std::vector<int>> const &adj, std::vector<int> const &edge1, std::vector<int> const &edge2) {

            if (edge1[0] == edge2[0]) return edge(adj, edge1[1], edge2[1]);
            else if (edge1[0] == edge2[1]) return edge(adj, edge1[1], edge2[0]);
            else if (edge1[1] == edge2[0]) return edge(adj, edge1[0], edge2[1]);
            else if (edge1[1] == edge2[1]) return edge(adj, edge1[0], edge2[0]);

            return (edge(adj, edge1[0], edge2[0]) && edge(adj, edge1[0], edge2[1]) &&
                    edge(adj, edge1[1], edge2[0]) && edge(adj, edge1[1], edge2[1]));
        };

        std::vector<int> get_two_neighbors(std::vector<std::vector<int>> const &adj, std::vector<bool> const &nodes_status, FastSet &used, int node) {
            // mark all of the vertices in N[node]
            used.clear();
            used.add(node);
            for (int const v : adj[node]) used.add(v);

            // get the 2 neighborhood of node
            std::vector<int> two_neighborhood_node;
            for (int const node_neighbor : adj[node]) {
                for (int const node_2_neighbor : adj[node_neighbor]) {
                    if (!nodes_status[node_2_neighbor] || node_2_neighbor < node || used.get(node_2_neighbor)) continue;
                    two_neighborhood_node.push_back(node_2_neighbor);
                    used.add(node_2_neighbor);
                }
            }

            return two_neighborhood_node;
        }

        std::vector<int> get_two_neighbors(std::vector<std::vector<int>> const &adj, std::vector<bool> const &nodes_status, FastSet &used, int node, int larger_than) {
            // mark all of the vertices in N[node]
            used.clear();
            used.add(node);
            for (int const v : adj[node]) used.add(v);

            // get the 2 neighborhood of node
            std::vector<int> two_neighborhood_node;
            for (int const node_neighbor : adj[node]) {
                for (int const node_2_neighbor : adj[node_neighbor]) {
                    if (!nodes_status[node_2_neighbor] || node_2_neighbor <= larger_than || used.get(node_2_neighbor)) continue;
                    two_neighborhood_node.push_back(node_2_neighbor);
                    used.add(node_2_neighbor);
                }
            }

            return two_neighborhood_node;
        }

        std::vector<std::vector<int>> get_two_neighbors_grouped(std::vector<std::vector<int>> const &adj, FastSet &used, int node) {
            // mark all of the vertices in N[node]
            used.clear();
            used.add(node);
            for (int const v : adj[node]) used.add(v);

            // get the 2 neighborhood of node
            std::vector<std::vector<int>> two_neighborhood_node;
            for (int const node_neighbor : adj[node]) {
                std::vector<int> group;
                for (int const node_2_neighbor : adj[node_neighbor]) {
                    if (node_2_neighbor < node || used.get(node_2_neighbor)) continue;
                    group.push_back(node_2_neighbor);
                    used.add(node_2_neighbor);
                }
                two_neighborhood_node.push_back(group);
            }

            return two_neighborhood_node;
        }

        bool edge(std::vector<std::vector<int>> const &adj, int node1, int node2) {
            for (int const neighbor : adj[node1]) {
                if (neighbor > node2) break;
                if (neighbor == node2) return true;
            }

            return false;
        }

        void subgraph(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, std::vector<std::vector<int>> &sub_adj) {

            std::vector<int> old_to_new_mapping;
            std::vector<int> new_to_old_mapping;
            old_to_new_mapping.resize(adj.size(), -1);

            int new_NodeID = 0;

            for (int old_NodeID = 0; old_NodeID < (int) adj.size(); old_NodeID++) {
                if (nodes_status[old_NodeID]) {
                    new_to_old_mapping.push_back(old_NodeID);
                    old_to_new_mapping[old_NodeID] = new_NodeID;
                    new_NodeID++;
                }
            }

            sub_adj.clear();
            sub_adj.reserve(new_to_old_mapping.size());

            for (int old_NodeID : new_to_old_mapping) {

                std::vector<int> adj_list;
                std::vector<int> old_NodeID_neighborhood = adj[old_NodeID];

                for (int old_NodeID_neighbor : old_NodeID_neighborhood) {
                    int new_NodeID_neighbor = old_to_new_mapping[old_NodeID_neighbor];

                    if (new_NodeID_neighbor != -1) {
                        adj_list.push_back(new_NodeID_neighbor);
                    }
                }

                std::sort(adj_list.begin(), adj_list.end());
                sub_adj.push_back(adj_list);
            }
        }

    private:

};

#endif
