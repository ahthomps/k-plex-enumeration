#include <iostream>
#include <vector>
#include <string>

#include "tools/timer.h"
#include "tools/config.h"
#include "tools/linked_list.h"
#include "tools/graph_tools.h"
#include "graph_access/graph_io.h"
#include "bronKerbosch/bronKerbosch.h"
#include "kPlex/kplex.h"

#include "reductions/coreness.h"
#include "reductions/cliqueness.h"
#include "reductions/triangle.h"

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

    std::cout << filename << " " << G.number_of_nodes() << " " << G.number_of_edges() << " ";

    std::vector<bool> nodes_status(adj.size(), true);

    timer t;

    // Testing Triangle Reduction
    // TriangleReduction triangle(&adj, &nodes_status);
    // triangle.chiba_count_triangles();
    // triangle.reduce(config.kplexNum, config.minCliqueSize);

    // double triangles_red_time = t.elapsed();
    // std::cout << count_remaining_nodes(nodes_status) << " " << triangles_red_time << " ";
    // t.restart(); 

    
    // std::cout << t.elapsed() << " ";
    t.restart();
    CliquenessReduction cliqueness(&adj, config, &nodes_status);
    cliqueness.reduce(config.minCliqueSize, config.kplexNum);
    double clqness_red_time = t.elapsed();
    std::cout << count_remaining_nodes(nodes_status) << " ";
    std::cout << clqness_red_time << " ";
    // std::cout << t.elapsed() << std::endl;
    // Reductions reductions(&adj, &nodes_status, &config);
    // reductions.exhaustive_cliqueness_triangles();

    CorenessReduction coreness(&adj, &nodes_status);
    coreness.reduce(config.minCliqueSize, config.kplexNum);
    double corness_red_time = t.elapsed();
    std::cout << count_remaining_nodes(nodes_status) << " ";
    std::cout << corness_red_time << std::endl;

    return 0;

    TriangleReduction triangle2(&adj, &nodes_status);
    triangle2.reduce(config.kplexNum, config.minCliqueSize);

    double conte_red_time = t.elapsed();
    std::cout << count_remaining_nodes(nodes_status) << " " << conte_red_time << " ";
    
    GraphTools graph_tools;
    std::vector<std::vector<int>> new_adj;
    graph_tools.subgraph(adj, nodes_status, new_adj);

    graph_access G_prime;
    graph_io::readGraphAdj(G_prime, new_adj);

    std::string new_graph_name = "reduced.graph";
    graph_io::writeGraph(G_prime, new_graph_name);

    // std::cout << G_prime.number_of_nodes() << " " << G_prime.number_of_edges() << " " << triangles_red_time << " ";


    return 0;
}

int old_main(std::string &filename, Config &config, std::vector<std::vector<int>> &adj, std::vector<bool> &nodes_status) {

    timer t;
    // std::vector<bool>* p_nodes_status = NULL;

    if ((config.CORNESS || config.CLQNESS) && config.minCliqueSize > 1) {

        bool save_RPT_CLQ = config.RPT_CLQ;
        config.set_RPT_CLQ(false);

        if (config.CORNESS) {
            CorenessReduction coreness(&adj, &nodes_status);
            coreness.reduce(config.minCliqueSize, config.kplexNum);
            // coreness.reduce(44, 4);
            // p_nodes_status = &nodes_status;
        }
        if (config.CLQNESS) {
            CliquenessReduction cliqueness(&adj, config, &nodes_status);
            cliqueness.reduce(config.minCliqueSize, config.kplexNum);
            // cliqueness.reduce(4);
            // p_nodes_status = &nodes_status;
        }
        if (config.PRINT_NODES_STATUS) {
            size_t remaining_nodes_counter = 0;
            for (size_t i = 0; i < nodes_status.size(); i++) {
                if (nodes_status[i]) {
                  remaining_nodes_counter++;
                }
                // else std::cout << i << std::endl;
            }
            std::cout << filename << " " << remaining_nodes_counter << " " << t.elapsed() << std::endl;
        }

        config.set_RPT_CLQ(save_RPT_CLQ);
    }

    if (!config.TEST) {
      size_t counter = 0;
      for (size_t i = 0; i < nodes_status.size(); i++) {
          if (nodes_status[i]) {
              counter++;
          }
      }
      std::cout << "nodes remaining after reductions... " << counter << std::endl;
    }

    if (config.TEST && !config.RPT_CLQ) {
        std::cout << "must add '--RPT_CLQ' flag when testing" << std::endl;
        exit(0);
    }
    if (config.MAX_CLQ && config.WRT_3PLX) {
        KPlex kplex(&adj, config, &nodes_status, config.minCliqueSize);
        kplex.get_maximal_cliques_wrt_three_plexes();
        if (!config.TEST) std::cout << filename << " " << kplex.get_kplex_counter() << " " << t.elapsed() << std::endl;
    }
    else if (config.MAX_CLQ) {
        BronKerbosch algo(&adj, config, &nodes_status, config.minCliqueSize);
        algo.solve();
        if (!config.TEST) std::cout << filename << " " << algo.get_clique_counter() << " " << t.elapsed() << std::endl;
    }

    else {
        KPlex kplex(&adj, config, &nodes_status, config.minCliqueSize);
        if (config.TWOPLX) {
            kplex.get_two_plexes();
        }
        else if (config.CONN_ONE_NR_CLQ) {
            kplex.get_one_near_cliques_connected();
        }
        else if (config.ONE_NR_CLQ && config.WRT_3PLX) {
            kplex.get_one_near_cliques_wrt_three_plexes();
        }
        else if (config.ONE_NR_CLQ) {
            kplex.get_one_near_cliques();
        }
        else if (config.TWO_NR_CLQ) {
            kplex.get_two_near_cliques();
        }
        else if (config.THREEPLX) {
            kplex.get_three_plexes();
        }
        else if (config.CONN_TWO_NR_CLQ) {
            kplex.get_two_near_cliques_connected();
        }
        if (!config.TEST) {
            std::cout << filename << " " << kplex.get_kplex_counter() << " " << t.elapsed() << std::endl;
        }
    }

    return 0;
}
