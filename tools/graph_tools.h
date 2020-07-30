#include <iostream>
#include <vector>
#include <functional>

#include "fast_set.h"

#ifndef GRAPH_TOOLS_H_
#define GRAPH_TOOLS_H_

class GraphTools {

    public:

        GraphTools() {};

        std::vector<int> get_common_neighborhood(std::vector<std::vector<int>> const &adj, FastSet &used, int node1, int node2) {
            std::vector<int> common_neighbors;
            used.clear();
            for (int const v : adj[node2]) used.add(v);
            for (int const v : adj[node1]) {
                if (used.get(v)) common_neighbors.push_back(v);
                else used.remove(v);
            }

            return common_neighbors;
        };

        std::vector<int> get_common_neighborhood(std::vector<std::vector<int>> const &adj, FastSet &used, int node1) {
            std::vector<int> common_neighbors;
            for (int const v : adj[node1]) {
                if (used.get(v)) common_neighbors.push_back(v);
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

        std::vector<int> get_two_neighbors(std::vector<std::vector<int>> const &adj, FastSet &used, int node) {
            // mark all of the vertices in N[node]
            used.clear();
            used.add(node);
            for (int const v : adj[node]) used.add(v);

            // get the 2 neighborhood of node
            std::vector<int> two_neighborhood_node;
            for (int const node_neighbor : adj[node]) {
                for (int const node_2_neighbor : adj[node_neighbor]) {
                    if (node_2_neighbor < node || used.get(node_2_neighbor)) continue;
                    two_neighborhood_node.push_back(node_2_neighbor);
                    used.add(node_2_neighbor);
                }
            }

            return two_neighborhood_node;
        }

        std::vector<int> get_two_neighbors(std::vector<std::vector<int>> const &adj, FastSet &used, int node, int larger_than) {
            // mark all of the vertices in N[node]
            used.clear();
            used.add(node);
            for (int const v : adj[node]) used.add(v);

            // get the 2 neighborhood of node
            std::vector<int> two_neighborhood_node;
            for (int const node_neighbor : adj[node]) {
                for (int const node_2_neighbor : adj[node_neighbor]) {
                    if (node_2_neighbor <= larger_than || used.get(node_2_neighbor)) continue;
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

    private:

};

#endif
