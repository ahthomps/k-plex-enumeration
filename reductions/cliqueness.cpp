#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include "cliqueness.h"
#include "../bronKerbosch/bronKerbosch.h"
#include "../tools/config.h"
#include "../quick-cliques/Algorithm.h"
#include "../quick-cliques/DegeneracyAlgorithm.h"

CliquenessReduction::CliquenessReduction(std::vector<std::vector<int>> *adj, std::vector<bool> *nodes_status, std::unordered_map<std::pair<int, int>, bool, pair_hash> &edges_status, timer &t, double time_limit) :
    _adj(*adj), _nodes_status(*nodes_status), _edges_status(edges_status), _time_limit(time_limit), _t(t)
{
    _N = _adj.size();
    _max_clq.resize(_N, 1);
}

void CliquenessReduction::integrated_quick_clqs() {
    std::vector<std::list<int>> adj;
    for (std::vector<int> old_lst : _adj) {
        std::list<int> new_list;
        for (int v : old_lst) new_list.push_back(v);
        adj.push_back(new_list);
    }
    Algorithm *pAlgorithm = new DegeneracyAlgorithm(adj);
    pAlgorithm->AddCallBack(_update_largest_quick_clique);
    pAlgorithm->SetQuiet(true);

    std::list<std::list<int>> cliques;
    pAlgorithm->Run(cliques, _nodes_status);
    delete pAlgorithm;
}

void CliquenessReduction::get_maximum_cliques_quick_clqs(std::string &filename, std::function<void(std::vector<int>&)> callback) {

    std::string script =  "\n#/bin/bash \n./../quick-cliques/bin/qc --algorithm=degeneracy --table --input-file=../k-plex-enumeration/" +
    filename + " >> quick-cliques_output.txt";

    std::system(script.c_str());

    std::ifstream infile;
    infile.open("quick-cliques_output.txt");

    std::string line;
    std::string current_line;

    getline(infile, line);

    std::vector<std::vector<int>> maximal_cliques;

    while (true) {
        current_line.swap(line);
        if (!getline(infile, line)) break;
        std::vector<int> clq;
        std::string v;
        std::stringstream ss(current_line); 
        while (getline(ss, v, ' ')) {
            clq.push_back(std::stoi(v) - 1);
        }
        callback(clq);
    }

    std::remove("quick-cliques_output.txt");
}

void CliquenessReduction::get_maximum_cliques_bronkerbosh(std::function<bool(std::vector<std::vector<int>> const *, std::vector<int>, std::vector<int>, std::vector<int>)> callback) {
    BronKerbosch maxclq_algo(&_adj, &_nodes_status);
    maxclq_algo.solve(_update_largest_clique_first);
}


bool CliquenessReduction::reduce(double const clique_size, double const kplex) {
    size_t min_clique_size = std::ceil(clique_size / kplex);
    bool reduced = false;

    integrated_quick_clqs();

    for (size_t v = 0; v < _max_clq.size(); v++) {
        if (_t.elapsed() > _time_limit) break;
        if (_nodes_status[v] && _max_clq[v] < min_clique_size) {
            _nodes_status[v] = false;
            reduced = true;

            for (int u : _adj[v]) {
                std::pair<int, int> vu_edge;
                if (v < u) vu_edge = std::make_pair(v, u);
                else vu_edge = std::make_pair(u, v);

                _edges_status.at(vu_edge) = false;
            }
        }
    }
    return reduced;
}

bool CliquenessReduction::exhuastive_reduce(double const clique_size, double const kplex) {

    bool reduced = true;
    while (reduced) {
        reduced = reduce(clique_size, kplex);
        _max_clq.resize(_N, 1);
    }
    return reduced;
}

bool CliquenessReduction::reduce_old(double const clique_size, double const kplex) {
    size_t min_clique_size = std::ceil(clique_size / kplex);
    bool reduced = false;

    get_maximum_cliques_bronkerbosh(_update_largest_clique_first);

    // std::cout << _max_clq_size << std::endl;

    for (size_t i = 0; i < _max_clq.size(); i++) {
        if (_max_clq[i] < min_clique_size) {
            _nodes_status[i] = false;
            reduced = true;
        }
    }
    return reduced;
}
