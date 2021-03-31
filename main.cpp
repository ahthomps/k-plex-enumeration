#include <iostream>
#include <vector>

#include "faplex/args.hxx"
#include "kplex_enum.h"

int main(int argn, char **argv) {

    std::string file_path;
    size_t k;
    size_t q;
    double time_limit;
    size_t expr;
    bool zhou;

    args::ArgumentParser parser("AlmaPlex ;), a software for enumerating kplex\n");

    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    args::Group required(parser, "", args::Group::Validators::All);

    args::ValueFlag<std::string> File(parser, "benchmark", "Path to benchmark", {'f', "file"}, "");

    args::ValueFlag<size_t> K(parser, "para k", "The parameter k", {'k', "k"}, 2);

    args::ValueFlag<size_t> Q(parser, "Lower Bound", "The lower bound of the size of kplex", {'q', "q"}, 12);

    args::ValueFlag<size_t> Experiment(parser, "Experiment Number", "The the number experiment that you want to run", {'e', "e"}, 0);

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
    expr = args::get(Experiment);
    zhou = args::get(Zhou);

    KPlexEnum kplex_enum;
    kplex_enum.read_graph(file_path);
    kplex_enum.run(k, q, time_limit, expr, zhou);

    return 0;
}