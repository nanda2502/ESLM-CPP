#include "Params.h"
#include <cstdlib>


Params createParams(int argc, char* argv[]) {
    Params params;
    params.t = std::atoi(argv[2]);
    params.num_nodes = std::atoi(argv[3]);
    params.n = std::atoi(argv[4]);
    params.m = std::atoi(argv[5]);
    params.edge_mean = std::atof(argv[6]);
    params.edge_var = std::atof(argv[7]);
    params.edge_threshold = std::atof(argv[8]);
    params.payoffs_mean = std::atof(argv[9]);
    params.competences_sd = std::atof(argv[10]);
    params.node_mean = std::atof(argv[11]);
    params.node_var = std::atof(argv[12]);
    params.agent_edge_sd = std::atof(argv[13]);
    params.cor_age_competence = std::atof(argv[14]);
    params.experience_bias = std::atof(argv[15]);
    params.assortment = std::atoi(argv[16]);
    params.strategy = std::atoi(argv[17]);

    return params;
}
