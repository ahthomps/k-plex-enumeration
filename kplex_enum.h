#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "tools/timer.h"
#include "tools/graph_tools.h"
#include "graph_access/graph_io.h"
#include "reductions/coreness.h"
#include "reductions/cliqueness.h"
#include "reductions/triangle.h"
#include "reductions/four_cliques.h"
#include "faplex/EnuBundle.h"

#ifndef KPLEX_ENUM_H_
#define KPLEX_ENUM_H_


class KPlexEnum {
public:

	KPlexEnum() {};
    ~KPlexEnum() {};

    void read_graph(std::string filename);

    void run(size_t k, size_t q, double time_limit, size_t expr, bool zhou);

private:
    size_t _k;
    size_t _q;
    double _time_limit;

    std::vector<std::vector<int>> _adj;
    size_t _N;
    std::vector<bool> _nodes_status;
    std::unordered_map<std::pair<int, int>, bool, pair_hash> _edges_status;

    std::string _header;
    std::string _result;

    timer _t;

    size_t build_subgraph(std::vector<std::vector<int>> &subgraph_adj);

    void experiment(size_t expr);

    void run_conte_and_edge_based();

    void run_conte();

    void run_only_zhou();

    void run_coreness();

    void run_cliqueness();

    void run_vertex_based_triangles();

    void run_vertex_based_four_cliques();

    void run_edge_based_triangles();

    void run_edge_based_four_cliques();

    void run_zhou(std::vector<std::vector<int>> &adj, size_t edge_count);
};

#endif