#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <unordered_map>
#include <ctime>

#include "tools/timer.h"
#include "tools/config.h"
#include "tools/linked_list.h"
#include "tools/graph_tools.h"
#include "graph_access/graph_io.h"

#include "reductions/coreness.h"
#include "reductions/cliqueness.h"
#include "reductions/triangle.h"
#include "reductions/four_cliques.h"
#include "faplex/EnuBundle.h"
// #include "reductions/zhou.h"


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

std::string run_faplex(std::string const &reduced_graph_name, Config const &config) {
    // c is for when you want to print out all kplexes, z is for when you are just running faplex 

    std::string bin_filename = reduced_graph_name.substr(0, reduced_graph_name.rfind(".graph")) + ".bin";
    std::string script =  "\n#/bin/bash \n./faplex/examples/toBin " + reduced_graph_name;

    unsigned int k = static_cast<unsigned int>(config.k);
    unsigned int q = static_cast<unsigned int>(config.q);
    unsigned long int ftime = static_cast<unsigned long int>(config.ftime);

    std::system(script.c_str());

    EnuBundle enbundle;
    enbundle.readBinaryGraph(bin_filename.c_str());
    std::pair<unsigned int, double> faplex_ouput;
    faplex_ouput = enbundle.enumPlex(k, q, ftime, 1, 1, 0, 1);

    std::string output = std::to_string(faplex_ouput.first) + " " + std::to_string(faplex_ouput.second) + " ";

    return output;
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
    cliqueness.reduce(config.q, config.k);
    // cliqueness.exhuastive_reduce(config.q, config.k);
    double cliqueness_time = t.elapsed();
    size_t cliqueness_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    double conte_time = coreness_time + cliqueness_time;
    size_t conte_kernel = cliqueness_kernel;

    std::string output = (std::to_string(coreness_kernel) + " " + std::to_string(coreness_time) + " " +
                          std::to_string(cliqueness_kernel) + " " + std::to_string(cliqueness_time) + " ");
    // std::string output = (std::to_string(conte_kernel) + " " + std::to_string(conte_time) + " ");

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

    double conte_time = coreness_time + cliqueness_time;
    size_t conte_kernel = cliqueness_kernel;

    TriangleReduction triangle(adj, nodes_status);
    triangle.reduce(config.k, config.q);
    double triangle_time = t.elapsed();
    size_t triangle_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    FourCliquesReduction fourcliques(adj, nodes_status);
    fourcliques.reduce(config.k, config.q);
    double fourcliques_time = t.elapsed();
    size_t fourcliques_kernel = count_remaining_nodes(nodes_status);

    // std::string output = (std::to_string(coreness_kernel) + " " + std::to_string(coreness_time) + " " +
    //                       std::to_string(cliqueness_kernel) + " " + std::to_string(cliqueness_time) + " " +
    //                       std::to_string(triangle_kernel) + " " + std::to_string(triangle_time) + " " +
    //                       std::to_string(fourcliques_kernel) + " " + std::to_string(fourcliques_time) + " ");
    std::string output = (std::to_string(conte_kernel) + " " + std::to_string(conte_time) + " " +
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

std::string run_edge_based_reductions(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, Config &config) {

    // std::vector<std::unordered_map<int, bool>> edges_status(adj.size());
    // for (int v = 0; v < (int) adj.size(); v++)
    //     for (int w : adj[v]) {
    //         if (nodes_status[v] && nodes_status[w]) {
    //             edges_status[v][w] = true;
    //         }
    //         else {
    //             edges_status[v][w] = false;
    //         }
    //     }

    // std::unordered_map<std::pair<int, int>, bool, pair_hash> edges_status_new;
    // for (int v = 0; v < (int) adj.size(); v++) {
    //     for (int w : adj[v]) {
    //         if (w < v) continue;
    //         std::pair<int, int> edge(v, w);
    //         if (nodes_status[v] && nodes_status[w])
    //             edges_status_new[edge] = true;
    //         else edges_status_new[edge] = false;
    //     }
    // }

    timer t;

    TriangleReduction triangle(adj, nodes_status);
    // size_t triangle_edges_reduced = triangle.edge_reduce_new(edges_status_new, config.k, config.q);
    size_t triangle_edges_reduced = triangle.edge_reduce_new2(edges_status, config.k, config.q);
    double triangle_time = t.elapsed();
    size_t triangle_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    FourCliquesReduction fourcliques(adj, nodes_status);
    // size_t fourcliques_edges_reduced = fourcliques.edge_reduce(edges_status, config.k, config.q);
    size_t fourcliques_edges_reduced = fourcliques.edge_reduce_new2(edges_status, config.k, config.q);
    double fourcliques_time = t.elapsed();
    size_t fourcliques_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    std::string output = (std::to_string(triangle_edges_reduced) + " " + std::to_string(triangle_kernel) + " " + std::to_string(triangle_time) + " " +
                          std::to_string(fourcliques_edges_reduced) + " " + std::to_string(fourcliques_kernel) + " " + std::to_string(fourcliques_time) + " ");

    return output;
}

std::string run_vertex_triangles_red(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, Config &config) {

    timer t;

    TriangleReduction triangle(adj, nodes_status);
    triangle.reduce(config.k, config.q);
    double triangle_time = t.elapsed();
    size_t triangle_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    std::string output = (std::to_string(triangle_kernel) + " " + std::to_string(triangle_time) + " ");
    return output;
}

std::string run_edge_triangles_red(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, Config &config) {

    timer t;

    TriangleReduction triangle_edge(adj, nodes_status);
    size_t triangle_edge_edges_reduced = triangle_edge.edge_reduce_new2(edges_status, config.k, config.q);
    double triangle_edge_time = t.elapsed();
    size_t triangle_edge_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    std::string output = (std::to_string(triangle_edge_edges_reduced) + " " + std::to_string(triangle_edge_kernel) + " " + std::to_string(triangle_edge_time) + " ");
    return output;
}

std::string run_vertex_4clq_red(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, Config &config) {

    timer t;

    FourCliquesReduction fourcliques(adj, nodes_status);
    fourcliques.reduce(config.k, config.q);
    double fourcliques_time = t.elapsed();
    size_t fourcliques_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    std::string output = (std::to_string(fourcliques_kernel) + " " + std::to_string(fourcliques_time) + " ");
    return output;
}

std::string run_edge_4clq_red(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, Config &config) {

    timer t;  

    FourCliquesReduction fourcliques_edge(adj, nodes_status);
    size_t fourcliques_edge_edges_reduced = fourcliques_edge.edge_reduce_new2(edges_status, config.k, config.q);
    double fourcliques_edge_time = t.elapsed();
    size_t fourcliques_edge_kernel = count_remaining_nodes(nodes_status);
    t.restart();

    std::string output = (std::to_string(fourcliques_edge_edges_reduced) + " " + std::to_string(fourcliques_edge_kernel) + " " + std::to_string(fourcliques_edge_time) + " ");
    return output;
}

std::string write_G_prime(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, bool const edgesub, std::string const &reduced_graph_name) {

    GraphTools graph_tools;
    std::vector<std::vector<int>> new_adj;
    if (edgesub)
        graph_tools.subgraph(adj, nodes_status, edges_status, new_adj);
    else graph_tools.subgraph(adj, nodes_status, new_adj);

    graph_access G_prime;
    graph_io::readGraphAdj(G_prime, new_adj);

    std::string output = std::to_string(G_prime.number_of_nodes()) + " " + std::to_string(G_prime.number_of_edges()) + " ";

    graph_io::writeGraph(G_prime, reduced_graph_name);

    return output;
}


void build_edges_status(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status) {
    edges_status.clear();
        for (int v = 0; v < (int) adj.size(); v++) {
            for (int w : adj[v]) {
                if (w < v) continue;
                std::pair<int, int> edge(v, w);
                if (nodes_status[v] && nodes_status[w])
                    edges_status[edge] = true;
                else edges_status[edge] = false;
            }
        }
}

void vertex_versus_edge_experiments(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, Config &config, std::string &result) {
    // run all old reductions and new edge based reductions
    if (config.expr == 0) {
        result += run_reductions(adj, nodes_status, config);
        build_edges_status(adj, nodes_status, edges_status);
        result += run_edge_based_reductions(adj, nodes_status, edges_status, config);
    }
    // run conte then just vertex based triangles
    else if (config.expr == 1) {
        result += run_conte_reductions(adj, nodes_status, config);
        build_edges_status(adj, nodes_status, edges_status);
        result += run_vertex_triangles_red(adj, nodes_status, config);
    }
    // run conte then just edge based triangles
    else if (config.expr == 2) {
        result += run_conte_reductions(adj, nodes_status, config);
        build_edges_status(adj, nodes_status, edges_status);
        result += run_edge_triangles_red(adj, nodes_status, edges_status, config);
    }
    // run conte then just vertex based 4clqs
    else if (config.expr == 3) {
        result += run_conte_reductions(adj, nodes_status, config);
        build_edges_status(adj, nodes_status, edges_status);
        result += run_vertex_4clq_red(adj, nodes_status, config);
    }
    // run conte then just edge based 4clqs
    else if (config.expr == 4) { 
        result += run_conte_reductions(adj, nodes_status, config);
        build_edges_status(adj, nodes_status, edges_status);
        result += run_edge_4clq_red(adj, nodes_status, edges_status, config);
    }
    // run conte and vertex-basaed reductions
    else if (config.expr == 5) {
        result += run_reductions(adj, nodes_status, config);
        build_edges_status(adj, nodes_status, edges_status);
    }
    // run conte and edge-based reductions
    else if (config.expr == 6) {
        result += run_conte_reductions(adj, nodes_status, config);
        build_edges_status(adj, nodes_status, edges_status);
        result += run_edge_based_reductions(adj, nodes_status, edges_status, config);
    }
}

void all_zhou_graphs_experiments(std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status, std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, Config &config, std::string &result) {
    // run conte and edge-based reductions
    if (config.expr == 0) {
        result += run_conte_reductions(adj, nodes_status, config);
        build_edges_status(adj, nodes_status, edges_status);
        result += run_edge_based_reductions(adj, nodes_status, edges_status, config);
    }
    else if (config.expr == 1) {
        result += run_conte_reductions(adj, nodes_status, config);
        build_edges_status(adj, nodes_status, edges_status);
    }
    else if (config.expr == 2) {
        build_edges_status(adj, nodes_status, edges_status);
        result += run_edge_based_reductions(adj, nodes_status, edges_status, config);
    }
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
    size_t slash_pos = filename.rfind('/');
    size_t dot_graph_pos = filename.rfind('.');
    std::string short_filename;
    if (slash_pos >= filename.size()) short_filename = filename.substr(0, dot_graph_pos);
    else short_filename = filename.substr(slash_pos + 1, dot_graph_pos - slash_pos - 1);

    std::string header = short_filename + " " + std::to_string(config.k) + " " + std::to_string(config.q) + " " + std::to_string(G.number_of_nodes()) + " " + std::to_string(G.number_of_edges()) + " ";
    std::string reduced_graph_name = "reduced" + std::to_string(config.expr) + "-" + short_filename + "_" + std::to_string(config.k) + "_" + std::to_string(config.q) + ".graph";


    std::vector<bool> nodes_status(adj.size(), true);
    std::unordered_map<std::pair<int, int>, bool, pair_hash> edges_status;

    timer t;

    std::string result;

    all_zhou_graphs_experiments(adj, nodes_status, edges_status, config, result);     

    // std::string result = run_reductions(adj, nodes_status, config);
    // result += run_edge_based_reductions(adj, nodes_status, config);
    double total_red_time = t.elapsed();
    result += write_G_prime(adj, nodes_status, edges_status, config.edgesub, reduced_graph_name);
    result += std::to_string(total_red_time) + " ";

    if (config.faplex) {
        result += run_faplex(reduced_graph_name, config);
        std::cout << header << result << std::endl;;
    }
    else
        std::cout << header << result;

    return 0;
}

