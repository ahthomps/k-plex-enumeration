#include <iostream>
#include <string>
#include <sstream>

#ifndef CONFIG_H_
#define CONFIG_H_

class Config {

    public:

    size_t k = 1;     // k-plex number
    size_t q = 1;     // minimum kplex size
    size_t expr = 0;
    bool edgesub = false;

    Config(int argn, char **argv) {

        std::string set_q = "--q=";
        std::string set_k = "--k=";
        std::string set_expr = "--expr=";
        std::string set_edge_sub = "--edgesub";


        for (int i = 1; i < argn; i++) {
            std::string argv_i = argv[i];

	        if (argv_i.find('=') != std::string::npos) {
				       std::string first_part;
				for (size_t i = 0; i <= argv_i.find('='); i++) {
					first_part.push_back(argv_i[i]);
				}
				std::string second_part;
				for (size_t i = argv_i.find('=') + 1; i < argv_i.size(); i++) {
					second_part.push_back(argv_i[i]);
				}
				std::istringstream iss(second_part);
				size_t value;
				iss >> value;
				if (!first_part.compare(set_q)) {
					q = value;
	            }
	            else if (!first_part.compare(set_k)) k = value;
	            else if (!first_part.compare(set_expr)) expr = value;
			}
			else if (argv_i == set_edge_sub) edgesub = true;
      	} 
    }
};

#endif
