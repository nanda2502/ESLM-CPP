#ifndef AGENTS_H
#define AGENTS_H



#include <armadillo>
#include "Graph.h"
#include "Params.h"

class Agents {
public:
    arma::cube edge_weights;
    arma::mat node_weights;
    arma::mat competences;
    arma::ivec ages;

    Agents(const Graph& graph, const Params& params);

private:
    void initialize(const Graph& graph, const Params& params);
};

#endif // AGENTS_H