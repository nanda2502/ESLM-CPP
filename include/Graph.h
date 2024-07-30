#ifndef GRAPH_H
#define GRAPH_H

#include <random>
#include <armadillo>
#include "Utils.h"
#include "Params.h"

class Graph {
public:
    arma::mat adjMat;
    arma::vec node_payoffs;
    arma::field<arma::uvec> parents;

    Graph(const Params& params, int seed);
    /**
     * Retrieves the parents of the specified children in the graph.
     *
     * @param children The vector of child node IDs for which to retrieve the parents.
     * @return A field of vectors, where each vector contains the parent IDs of the corresponding child node.
     */
    arma::field<arma::uvec> getParents(const arma::uvec& children) const;
private:
    void initialize(const Params& params, int seed);
    void createPayoffs();
    void populateParents();
};

#endif // GRAPH_H