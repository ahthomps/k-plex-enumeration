#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <unordered_map>

#include "tools/timer.h"
#include "tools/config.h"
#include "tools/linked_list.h"
#include "tools/graph_tools.h"
#include "graph_access/graph_io.h"

#include "reductions/coreness.h"
#include "reductions/cliqueness.h"
#include "reductions/triangle.h"
#include "reductions/four_cliques.h"


std::vector<std::vector<int>> buildAdjG(graph_access &G) {
    std::vector<std::vector<int>> adj;
    forall_nodes(G, v) {
        std::vector<int> neighbors;
        forall_out_edges(G, e, v) {
            neighbors.push_back(static_cast<int>(G.getEdgeTarget(e)));
        } endfor
        adj.push_back(neighbors);
    } endfor
    return adj;
}

size_t count_remaining_nodes(std::vector<bool> &nodes_status) {
    size_t count = 0;
    for (bool node : nodes_status) if (node) count++;
    return count;
}

std::string run_conte_reductions(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, Config &config) {

    timer t;

    CorenessReduction coreness(&adj, &nodes_status);
    coreness.bruteforce_reduce(config.q, config.k);
    // coreness.reduce(config.q, config.k);
    double coreness_time = t.elapsed();
    size_t coreness_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    CliquenessReduction cliqueness(&adj, &nodes_status);
    // cliqueness.reduce_old(config.q, config.k);
    // cliqueness.reduce(config.q, config.k);
    cliqueness.exhuastive_reduce(config.q, config.k);
    double cliqueness_time = t.elapsed();
    size_t cliqueness_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    std::string output = (std::to_string(coreness_kernel) + " " + std::to_string(coreness_time) + " " +
                          std::to_string(cliqueness_kernel) + " " + std::to_string(cliqueness_time) + " ");
    return output;
}

std::string run_reductions(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, Config &config) {

    timer t;

    CorenessReduction coreness(&adj, &nodes_status);
    coreness.bruteforce_reduce(config.q, config.k);
    // coreness.reduce(config.q, config.k);
    double coreness_time = t.elapsed();
    size_t coreness_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    CliquenessReduction cliqueness(&adj, &nodes_status);
    // cliqueness.reduce_old(config.q, config.k);
    cliqueness.reduce(config.q, config.k);
    // cliqueness.exhuastive_reduce(config.q, config.k);
    double cliqueness_time = t.elapsed();
    size_t cliqueness_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    TriangleReduction triangle(adj, nodes_status);
    triangle.reduce(config.k, config.q);
    double triangle_time = t.elapsed();
    size_t triangle_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    FourCliquesReduction fourcliques(adj, nodes_status);
    fourcliques.reduce(config.k, config.q);
    double fourcliques_time = t.elapsed();
    size_t fourcliques_kernel = count_remaining_nodes(nodes_status);

    std::string output = (std::to_string(coreness_kernel) + " " + std::to_string(coreness_time) + " " +
                          std::to_string(cliqueness_kernel) + " " + std::to_string(cliqueness_time) + " " +
                          std::to_string(triangle_kernel) + " " + std::to_string(triangle_time) + " " +
                          std::to_string(fourcliques_kernel) + " " + std::to_string(fourcliques_time) + " ");
    return output;

}

std::string test_counting_triangles(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status) {
    
    timer t; 

    TriangleReduction triangle(adj, nodes_status);
    triangle.bruteforce_count_triangles();
    double bruteforce_time = t.elapsed();
    size_t bruteforce_count = triangle.get_total_num_triangles();
    t.restart();

    TriangleReduction triangle2(adj, nodes_status);
    triangle2.count_triangles();
    double chiba_time = t.elapsed();
    size_t chiba_count = triangle2.get_total_num_triangles();
    t.restart();

    std::string output = ("bruteforce: " + std::to_string(bruteforce_count) + " " + std::to_string(bruteforce_time) + "\n" +
                          "chiba: " + std::to_string(chiba_count) + " " + std::to_string(chiba_time));
    return output;
}

std::string test_counting_4clqs(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status) {
    
    timer t; 

    FourCliquesReduction fourcliques(adj, nodes_status);
    fourcliques.count_4clqs();
    double chiba_time = t.elapsed();
    size_t chiba_count = fourcliques.get_total_num_four_cliques();
    t.restart();

    std::cout << "done with chiba..." << std::endl;

    FourCliquesReduction fourcliques2(adj, nodes_status);
    fourcliques2.bruteforce_count_4clqs();
    double bruteforce_time = t.elapsed();
    size_t bruteforce_count = fourcliques2.get_total_num_four_cliques();
    t.restart();

    std::string output = ("bruteforce: " + std::to_string(bruteforce_count) + " " + std::to_string(bruteforce_time) + "\n" +
                          "chiba: " + std::to_string(chiba_count) + " " + std::to_string(chiba_time));
    return output;
}

std::string run_4clq_reduction(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, Config &config) {

    timer t;

    FourCliquesReduction fourcliques(adj, nodes_status);
    fourcliques.reduce(config.k, config.q);
    double fourcliques_time = t.elapsed();
    size_t fourcliques_kernel = count_remaining_nodes(nodes_status);

    std::string output = std::to_string(fourcliques_kernel) + " " + std::to_string(fourcliques_time) + " ";

    return output;  
}

std::string run_edge_based_reductions(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, Config &config) {

    std::unordered_map<std::pair<int, int>, bool, pair_hash> edges_status(adj.size());
    for (int v = 0; v < (int) adj.size(); v++)
        for (int w : adj[v]) {
            std::pair<int, int> edge(v, w);
            if (nodes_status[v] && nodes_status[w]) {
                edges_status[edge] = true;
            }
            else {
                edges_status[edge] = false;
            }
        }

    timer t;

    TriangleReduction triangle(adj, nodes_status);
    size_t triangle_edges_reduced = triangle.edge_reduce(edges_status, config.k, config.q);
    double triangle_time = t.elapsed();
    size_t triangle_kernel = count_remaining_nodes(nodes_status);

    FourCliquesReduction fourcliques(adj, nodes_status);
    size_t fourcliques_edges_reduced = fourcliques.edge_reduce(edges_status, config.k, config.q);
    double fourcliques_time = t.elapsed();
    size_t fourcliques_kernel = count_remaining_nodes(nodes_status);

    std::string output = (std::to_string(triangle_edges_reduced) + " " + std::to_string(triangle_kernel) + " " + std::to_string(triangle_time) + " " +
                          std::to_string(fourcliques_edges_reduced) + " " + std::to_string(fourcliques_kernel) + " " + std::to_string(fourcliques_time) + " ");

    return output;
}

void write_G_prime(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status) {

    GraphTools graph_tools;
    std::vector<std::vector<int>> new_adj;
    graph_tools.subgraph(adj, nodes_status, new_adj);

    graph_access G_prime;
    graph_io::readGraphAdj(G_prime, new_adj);

    std::string new_graph_name = "reduced.graph";
    graph_io::writeGraph(G_prime, new_graph_name);

    return;
}

int main(int argn, char **argv) {

    if (argn < 2) {
        std::cout << "Cannot find graph" << std::endl;
        exit(1);
    }

    Config config(argn, argv);

    graph_access G;
    std::string filename = argv[1];
    graph_io::readGraphWeighted(G, filename);
    std::vector<std::vector<int>> adj = buildAdjG(G);

    std::string header = filename + " " + std::to_string(G.number_of_nodes()) + " " + std::to_string(G.number_of_edges()) + " ";

    std::vector<bool> nodes_status(adj.size(), true);

    timer t;

    std::string result = run_reductions(adj, nodes_status, config);
    result += run_edge_based_reductions(adj, nodes_status, config);
    std::cout << header << result;
    write_G_prime(adj, nodes_status);

    return 0;
}

