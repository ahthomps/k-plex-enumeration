#include "kplex_enum.h"

size_t count_remaining_nodes(std::vector<bool> &nodes_status) {
    size_t count = 0;
    for (bool stat : nodes_status) 
        if (stat)
            count++;
    return count;
}

void KPlexEnum::read_graph(std::string filename) {
    graph_access G;
    graph_io::readGraphWeighted(G, filename);
    _adj = graph_io::buildAdjG(G);
    _N = _adj.size();
    _nodes_status.resize(_N, true);

    for (int v = 0; v < (int) _adj.size(); v++) {
        for (int w : _adj[v]) {
            if (w < v) continue;
            std::pair<int, int> edge(v, w);
            _edges_status[edge] = true;
        }
    }

    _header = "";
    size_t slash_pos = filename.rfind('/');
    size_t dot_graph_pos = filename.rfind('.');
    std::string short_filename;
    if (slash_pos >= filename.size()) short_filename = filename.substr(0, dot_graph_pos);
    else short_filename = filename.substr(slash_pos + 1, dot_graph_pos - slash_pos - 1);
    _header += short_filename + " " + std::to_string(G.number_of_nodes()) + " " + std::to_string(G.number_of_edges()) + " ";
}

void KPlexEnum::run(size_t k, size_t q, double time_limit, size_t expr, bool zhou) {
    _result = "";
    _k = k;
    _q = q;
    _time_limit = time_limit;
    _header += std::to_string(_k) + " " + std::to_string(_q) + " ";

    _t.restart();

    experiment(expr);

    std::vector<std::vector<int>> subgraph_adj;
    size_t edge_count = build_subgraph(subgraph_adj);

    if (zhou) {
        run_zhou(subgraph_adj, edge_count);
        _result += std::to_string(_t.elapsed()) + " ";
    }

    std::cout << _header << _result << std::endl;
}

size_t KPlexEnum::build_subgraph(std::vector<std::vector<int>> &subgraph_adj) {
    GraphTools graph_tools;
    graph_tools.subgraph(_adj, _nodes_status, _edges_status, subgraph_adj);
    size_t node_count = subgraph_adj.size();
    size_t edge_count = 0;
    for (size_t v = 0; v < node_count; v++) 
        edge_count += subgraph_adj[v].size();
    
    _result += std::to_string(node_count) + " " + std::to_string(edge_count) + " " + std::to_string(_t.elapsed()) + " ";

    return edge_count;
}

void KPlexEnum::experiment(size_t expr) {
    if (expr == 0) {
        run_conte_and_edge_based();
    }
    else if (expr == 1)
        run_conte();
    else if (expr == 2) {
        run_coreness();
        run_edge_based_triangles();
        run_edge_based_four_cliques();
    }
    else {
        std::cout << "must enter experiment number in range [0,2]." << std::endl;
        exit(1);
    }
}

void KPlexEnum::run_conte_and_edge_based() {
    run_coreness();
    run_cliqueness();
    run_edge_based_triangles();
    run_edge_based_four_cliques();
}

void KPlexEnum::run_conte() {
    run_coreness();
    run_cliqueness();
}

void KPlexEnum::run_only_zhou() {};

void KPlexEnum::run_coreness() {
    double begin_time = _t.elapsed();
    CorenessReduction coreness(&_adj, &_nodes_status, _edges_status, _t, _time_limit);
    coreness.bruteforce_reduce(_q, _k);
    double coreness_time = _t.elapsed() - begin_time;
    size_t coreness_kernel = count_remaining_nodes(_nodes_status);

    _result += std::to_string(coreness_kernel) + " " + std::to_string(coreness_time) + " ";
}

void KPlexEnum::run_cliqueness() {
    double begin_time = _t.elapsed();
    CliquenessReduction cliqueness(&_adj, &_nodes_status, _edges_status, _t, _time_limit);
    cliqueness.reduce(_q, _k);
    double cliqueness_time = _t.elapsed() - begin_time;
    size_t cliqueness_kernel = count_remaining_nodes(_nodes_status);

    _result += std::to_string(cliqueness_kernel) + " " + std::to_string(cliqueness_time) + " ";
}

void KPlexEnum::run_vertex_based_triangles() {
    double begin_time = _t.elapsed();
    TriangleReduction triangle(_adj, _nodes_status, _t, _time_limit);
    triangle.reduce(_k, _q);
    double triangle_time = _t.elapsed() - begin_time;
    size_t triangle_kernel = count_remaining_nodes(_nodes_status);
    
    _result += std::to_string(triangle_kernel) + " " + std::to_string(triangle_time) + " ";
}

void KPlexEnum::run_vertex_based_four_cliques() {
    double begin_time = _t.elapsed();
    FourCliquesReduction fourcliques(_adj, _nodes_status, _t, _time_limit);
    fourcliques.reduce(_k, _q);
    double fourcliques_time = _t.elapsed() - begin_time;
    size_t fourcliques_kernel = count_remaining_nodes(_nodes_status);

    _result += std::to_string(fourcliques_kernel) + " " + std::to_string(fourcliques_time) + " ";
}

void KPlexEnum::run_edge_based_triangles() {
    double begin_time = _t.elapsed();
    TriangleReduction triangle(_adj, _nodes_status, _t, _time_limit);
    size_t triangle_edges_reduced = triangle.edge_reduce_new2(_edges_status, _k, _q);
    double triangle_time = _t.elapsed() - begin_time;
    size_t triangle_kernel = count_remaining_nodes(_nodes_status);

    _result += std::to_string(triangle_edges_reduced) + " " + std::to_string(triangle_kernel) + " " + std::to_string(triangle_time) + " ";
}

void KPlexEnum::run_edge_based_four_cliques() {
    double begin_time = _t.elapsed();
    FourCliquesReduction fourcliques(_adj, _nodes_status, _t, _time_limit);
    size_t fourcliques_edges_reduced = fourcliques.edge_reduce_new2(_edges_status, _k, _q);
    double fourcliques_time = _t.elapsed() - begin_time;
    size_t fourcliques_kernel = count_remaining_nodes(_nodes_status);

    _result += std::to_string(fourcliques_edges_reduced) + " " + std::to_string(fourcliques_kernel) + " " + std::to_string(fourcliques_time) + " ";
}

void KPlexEnum::run_zhou(std::vector<std::vector<int>> &adj, size_t edge_count) {
    if (adj.size() == 0 || edge_count == 0) {
        _result += "0 0.00";
        return;
    }

    EnuBundle enbundle;
    enbundle.readAdjGraph(adj, edge_count);
    std::tuple<unsigned int, double, unsigned int> faplex_ouput = enbundle.enumPlex(_k, _q, _time_limit - _t.elapsed(), 1, 1, 0, 1);

    _result += std::to_string(std::get<0>(faplex_ouput)) + " " + std::to_string(std::get<1>(faplex_ouput)) + " ";

    if (std::get<2>(faplex_ouput)) 
        _result += "time-exceeded ";
}