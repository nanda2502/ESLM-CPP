#ifndef GRAPH_H
#define GRAPH_H

#include <Types.h>
#include <tuple>
#include <random>
#include <unordered_map>
#include <armadillo>
#include "Utils.h"

class Graph {
public:
    arma::mat adjMat;
    arma::vec node_payoffs;
    std::unordered_map<int, arma::uvec> parents;

    Graph(const Params& params, int seed);

private:
    void initialize(const Params& params, int seed);
    void createPayoffs();
    void populateParents();

public:
    arma::umat getParents(const arma::uvec& children) const;
};

#endif // GRAPH_H