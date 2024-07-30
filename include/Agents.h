#ifndef AGENTS_H
#define AGENTS_H


#include <tuple>
#include <random>
#include <unordered_map>
#include <armadillo>
#include "Graph.h"
#include "Utils.h"
#include "Params.h"

class Agents {
public:
    arma::cube edge_weights;
    arma::mat node_weights;
    arma::mat competences;
    arma::ivec ages;

    Agents(const Graph& graph, const Params& params, int seed);

private:
    void initialize(const Graph& graph, const Params& params, int seed);
};

#endif // AGENTS_H