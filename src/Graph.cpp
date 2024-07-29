#include "Graph.h"

Graph::Graph(const Params& params, int seed) {
    initialize(params, seed);
    createPayoffs();
    populateParents();
}

void Graph::initialize(const Params& params, int seed) {
    arma::umat edges(params.num_nodes * (params.num_nodes - 1) / 2, 2);
    int idx = 0;
    for (int i = 1; i <= params.num_nodes; ++i) {
        for (int j = i + 1; j <= params.num_nodes; ++j) {
            edges(idx, 0) = i - 1;
            edges(idx, 1) = j - 1;
            idx++;
        }
    }

    std::mt19937 gen(seed);

    arma::vec weights(edges.n_rows);
    for (arma::uword i = 0; i < weights.n_elem; ++i) {
        weights[i] = beta_distribution(params.edge_alpha, params.edge_beta, gen);
    }

    arma::uvec pruned_indices = arma::find(weights >= params.edge_threshold);
    arma::umat pruned_edges = edges.rows(pruned_indices);
    arma::vec pruned_weights = weights.elem(pruned_indices);

    adjMat = arma::mat(params.num_nodes, params.num_nodes, arma::fill::zeros);
    for (arma::uword i = 0; i < pruned_edges.n_rows; ++i) {
        adjMat(pruned_edges(i, 0), pruned_edges(i, 1)) = pruned_weights(i);
    }
}

void Graph::createPayoffs() {
    arma::vec colSums = arma::sum(adjMat, 0).t();
    node_payoffs = colSums / arma::accu(colSums);
}

void Graph::populateParents() {
    for (arma::uword i = 0; i < adjMat.n_cols; ++i) {
        arma::uvec parent_indices = arma::find(adjMat.col(i) > 0);
        if (!parent_indices.empty()) {
            parents[i] = parent_indices;
        }
    }
}

arma::umat Graph::getParents(const arma::uvec& children) const {
    arma::umat parentMatrix(children.n_elem, adjMat.n_rows, arma::fill::zeros);
    for (arma::uword i = 0; i < children.n_elem; ++i) {
        int child = children(i);
        if (parents.find(child) != parents.end()) {
            arma::uvec parent_list = parents.at(child);
            parentMatrix.row(i).cols(0, parent_list.n_elem - 1) = parent_list.t();
        }
    }
    return parentMatrix;
}