#include "Graph.h"

Graph::Graph(const Params& params, int seed) {
    initialize(params, seed);
    createPayoffs();
    populateParents();
}

void Graph::initialize(const Params& params, int seed) {
    arma::umat edges(P(params, "num_nodes") * (P(params, "num_nodes") - 1) / 2, 2);
    int idx = 0;
    for (int i = 1; i <= P(params, "num_nodes"); ++i) {
        for (int j = i + 1; j <= P(params, "num_nodes"); ++j) {
            edges(idx, 0) = i - 1;
            edges(idx, 1) = j - 1;
            idx++;
        }
    }

    std::mt19937 gen(seed);
    
    arma::vec weights(edges.n_rows);
    for (arma::uword i = 0; i < weights.n_elem; ++i) {
        weights[i] = beta_distribution(P(params, "edge_mean"), P(params, "edge_var"), gen);
    }
    arma::uvec pruned_indices = arma::find(weights >= P(params, "edge_threshold"));
    arma::umat pruned_edges = edges.rows(pruned_indices);
    arma::vec pruned_weights = weights.elem(pruned_indices);

    adjMat = arma::mat(P(params, "num_nodes"), P(params, "num_nodes"), arma::fill::zeros);
    for (arma::uword i = 0; i < pruned_edges.n_rows; ++i) {
        adjMat(pruned_edges(i, 0), pruned_edges(i, 1)) = pruned_weights(i);
    }
}

void Graph::createPayoffs() {
    arma::vec colSums = arma::sum(adjMat, 0).t();
    node_payoffs = colSums / arma::accu(colSums);
}

void Graph::populateParents() {
    parents.set_size(adjMat.n_cols);
    for (arma::uword i = 0; i < adjMat.n_cols; ++i) {
        arma::uvec parent_indices = arma::find(adjMat.col(i) > 0);
        if (!parent_indices.empty()) {
            parents(i) = parent_indices;
        }
    }
}

arma::field<arma::uvec> Graph::getParents(const arma::uvec& children) const {
    arma::field<arma::uvec> parentField(children.n_elem);
    for (arma::uword i = 0; i < children.n_elem; ++i) {
        int child = children(i);
        if (!parents(child).is_empty()) {
            parentField(i) = parents(child);
        }
    }
    return parentField;
}