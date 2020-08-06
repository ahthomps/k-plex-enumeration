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
    bool TWO_NR_CLQ = false;
    bool TEST = false;
    bool WRT_3PLX = false;
    bool THREEPLX = false;
    bool CONN_TWO_NR_CLQ = false;
    bool CONNECTED = false;
    bool CLQNESS = false;
    bool CORNESS = false;

    size_t kplexNum = 1;

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
        std::string two_nr_clq = "--2NRCLQ";
        std::string test_ = "--TEST";
        std::string wrt_three_plex = "--WRT3PLX";
        std::string three_plex = "--3PLX";
        std::string conn_two_nr_clq = "--CONN2NRCLQ";
        std::string conn_threeplx = "--CONN3PLX";
        std::string cliqueness = "--CLQNESS";
        std::string coreness = "--CORNESS";
        std::string reduce = "--RDCE";

        for (int i = 1; i < argn; i++) {
          if (argv[i] == max_clq) MAX_CLQ = true;
          else if (argv[i] == twoplx) {
              TWOPLX = true;
              kplexNum = 2;
          }
          else if (argv[i] == conn_twoplx) {
            TWOPLX = true;
            CONNECTED = true;
            kplexNum = 2;
          }
          else if (argv[i] == conn_threeplx) {
              THREEPLX = true;
              CONNECTED = true;
              kplexNum = 3;
          }
          else if (argv[i] == rpt_clq) RPT_CLQ = true;
          else if (argv[i] == one_nr_clq) ONE_NR_CLQ = true;
          else if (argv[i] == conn_one_nr_clq) {
            ONE_NR_CLQ = true;
            CONN_ONE_NR_CLQ = true;
          }
          else if (argv[i] == two_nr_clq) TWO_NR_CLQ = true;
          else if (argv[i] == test_) {
              TEST = true;
              RPT_CLQ = true;
          }
          else if (argv[i] == wrt_three_plex) {
              WRT_3PLX = true;
          }
          else if (argv[i] == three_plex) {
              THREEPLX = true;
              kplexNum = 3;
          }
          else if (argv[i] == conn_two_nr_clq) {
              CONN_TWO_NR_CLQ = true;
          }
          else if (argv[i] == cliqueness) {
              CLQNESS = true;
          }
          else if (argv[i] == coreness) {
              CORNESS = true;
          }
          else if (argv[i] == reduce) {
              CLQNESS = true;
              CORNESS = true;
          }
        }
      }
    }
};

#endif
