#include <iostream>
#include <string>

#ifndef CONFIG_H_
#define CONFIG_H_

class Config {

  public:

    bool MAX_CLQ = false;
    bool TWOPLX = false;
    bool RPT_CLQ = false;
    bool ONE_NR_CLQ = false;
    bool CONN_ONE_NR_CLQ = false;

    Config(int argn, char **argv) {
      if (argn == 2) {
        TWOPLX = true;
        CONN_ONE_NR_CLQ = true;
      }
      else {

        std::string max_clq = "--MAXCLQ";
        std::string twoplx = "--2PLX";
        std::string conn_twoplx = "--CONN2PLX";
        std::string rpt_clq = "--RPTCLQ";
        std::string one_nr_clq = "--1NRCLQ";
        std::string conn_one_nr_clq = "--CONN1NRCLQ";

        for (int i = 1; i < argn; i++) {
          if (argv[i] == max_clq) MAX_CLQ = true;
          else if (argv[i] == twoplx) TWOPLX = true;
          else if (argv[i] == conn_twoplx) {
            TWOPLX = true;
            CONN_ONE_NR_CLQ = true;
          }
          else if (argv[i] == rpt_clq) RPT_CLQ = true;
          else if (argv[i] == one_nr_clq) ONE_NR_CLQ = true;
          else if (argv[i] == conn_one_nr_clq) {
            ONE_NR_CLQ = true;
            CONN_ONE_NR_CLQ = true;
          }
        }
      }
    }
};

#endif
