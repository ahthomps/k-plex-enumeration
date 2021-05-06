#include <iostream>
#include <vector>

#include "faplex/args.hxx"
#include "kplex_enum.h"

int main(int argn, char **argv) {

    std::string file_path;
    size_t k;
    size_t q;
    double time_limit;
    // size_t expr;
    bool conte;
    bool v_tri;
    bool v_4clq;
    bool e_tri;
    bool e_4clq;
    bool zhou;

    args::ArgumentParser parser("AlmaPlex ;), a software for enumerating kplex\n");

    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    args::Group required(parser, "", args::Group::Validators::All);

    args::ValueFlag<std::string> File(parser, "benchmark", "Path to benchmark", {'f', "file"}, "");

    args::ValueFlag<size_t> K(parser, "para k", "The parameter k", {'k', "k"}, 2);

    args::ValueFlag<size_t> Q(parser, "Lower Bound", "The lower bound of the size of kplex", {'q', "q"}, 12);

    // args::ValueFlag<size_t> Experiment(parser, "Experiment Number", "The the number experiment that you want to run", {'e', "e"}, 0);

    args::ValueFlag<size_t> Conte(parser, "Run Conte", "Run Conte's reductions", {"conte"}, 1);

    args::ValueFlag<size_t> V_Tri(parser, "Run V-Triangle", "Run the vertex-based triangle reduction", {"v-tri"}, 0);

    args::ValueFlag<size_t> V_4clq(parser, "Run V-4clq", "Run the vertex-based 4-clique reduction", {"v-4clq"}, 0);

    args::ValueFlag<size_t> E_Tri(parser, "Run E-Triangle", "Run the edge-based triangle reduction", {"e-tri"}, 0);

    args::ValueFlag<size_t> E_4clq(parser, "Run E-4clq", "Run the edge-based 4-clique reduction", {"e-4clq"}, 0);

    args::ValueFlag<size_t> Zhou(parser, "Run Zhou", "The parameter that decides if you want to run Zhou's algorithm", {'z', "z"}, 1);

    args::ValueFlag<double> TimeLimit(parser, "Time limitation", "The cut down time in second", {'t', "time"}, 2000);

    try {
        parser.ParseCLI(argn, argv);
    } catch (args::Help) {
        std::cout << parser;
        return 0;
    } catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 0;
    } catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 0;
    }

    file_path = args::get(File);
    k = args::get(K);
    q = args::get(Q);
    time_limit = args::get(TimeLimit);
    // expr = args::get(Experiment);
    conte = args::get(Conte);
    v_tri = args::get(V_Tri);
    v_4clq = args::get(V_4clq);
    e_tri = args::get(E_Tri);
    e_4clq = args::get(E_4clq);
    zhou = args::get(Zhou);

    KPlexEnum kplex_enum;
    kplex_enum.read_graph(file_path);
    kplex_enum.configure(k, q, time_limit, conte, v_tri, v_4clq, e_tri, e_4clq, zhou);
    kplex_enum.run();

    return 0;
}