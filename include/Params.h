#ifndef PARAMS_H
#define PARAMS_H

struct Params {
    int t;
    int num_nodes;
    int n;
    int m;
    double edge_mean;
    double edge_var;
    double edge_threshold;
    double payoffs_mean;
    double competences_sd;
    double node_mean;
    double node_var;
    double agent_edge_sd;
    double cor_age_competence;
    double experience_bias;
    int assortment;
    int strategy;
};

Params createParams(int argc, char* argv[]);

#endif // PARAMS_H