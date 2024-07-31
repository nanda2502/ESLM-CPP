#ifndef GRAPH_H
#define GRAPH_H

#include <armadillo>
#include "Params.h"

class Graph {
public:
    arma::mat adjMat;
    arma::vec node_payoffs;
    arma::field<arma::uvec> parents;

    Graph(const Params& params);
    
    /**
     * Retrieves the parents of the specified children in the graph.
     *
     * @param children The vector of child node IDs for which to retrieve the parents.
     * @return A field of vectors, where each vector contains the parent IDs of the corresponding child node.
     */
    arma::field<arma::uvec> getParents(const arma::uvec& children) const;
private:
    void initialize(const Params& params);
    void createPayoffs();
    void populateParents();
};

#endif // GRAPH_H