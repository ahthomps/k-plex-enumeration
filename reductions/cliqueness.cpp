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

CliquenessReduction::CliquenessReduction(std::vector<std::vector<int>> *adj, Config &config, std::vector<bool> *nodes_status) :
    _adj(*adj), _config(config), _nodes_status(*nodes_status)
{
    _N = _adj.size();
    _max_clq.resize(_N, 1);
}

void CliquenessReduction::get_maximum_cliques(std::string &filename, std::function<void(std::vector<int>&)> callback) {

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
            clq.push_back(std::stoi(v));
        }
        callback(clq);
    }

    // for (std::vector<int> line : maximal_cliques) {
    //  for (int v : line) {
    //      std::cout << v << " ";
    //  }
    //  std::cout << std::endl;u
    // }

    std::remove("quick-cliques_output.txt");
}

bool CliquenessReduction::reduce(size_t const kplex) {
    // BronKerbosch maxclq_algo(&_adj, _config, &_nodes_status);
    // maxclq_algo.solve(_update_largest_clique);
    // bool reduced = false;

    // size_t min_clique_size = std::ceil(_max_clq_size / kplex);

    // for (size_t i = 0; i < _max_clq.size(); i++) {
    //     if (_max_clq[i] < min_clique_size) {
    //         _nodes_status[i] = false;
    //         reduced = true;
    //     }
    // }
    return false;
}

bool CliquenessReduction::reduce(size_t const clique_size, size_t const kplex, std::string &filename) {
    size_t min_clique_size = std::ceil((double) clique_size / kplex);
    bool reduced = false;

    // BronKerbosch maxclq_algo(&_adj, _config, &_nodes_status);
    // maxclq_algo.solve(_update_largest_clique);

    get_maximum_cliques(filename, _update_largest_clique);
    // std::cout << _max_clq_size << std::endl;

    for (size_t i = 0; i < _max_clq.size(); i++) {
        if (_max_clq[i] < min_clique_size) {
            _nodes_status[i] = false;
            reduced = true;
        }
    }
    return reduced;
}

bool CliquenessReduction::reduce_old(size_t const clique_size, size_t const kplex) {
    size_t min_clique_size = std::ceil((double) clique_size / kplex);
    bool reduced = false;

    BronKerbosch maxclq_algo(&_adj, _config, &_nodes_status);
    maxclq_algo.solve(_update_largest_clique_first);

    // std::cout << _max_clq_size << std::endl;

    for (size_t i = 0; i < _max_clq.size(); i++) {
        if (_max_clq[i] < min_clique_size) {
            _nodes_status[i] = false;
            reduced = true;
        }
    }
    return reduced;
}
