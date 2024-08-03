#include "Graph.h"
#include "Utils.h"
#include <random>

Graph::Graph(const Params& params) {
    initialize(params);
    createPayoffs();
    populateParents();
}

void Graph::initialize(const Params& params) {
    arma::umat edges(params.num_nodes * (params.num_nodes - 1), 2); 
    int idx = 0;
    for (int i = 0; i < params.num_nodes; ++i) {
        for (int j = 0; j < params.num_nodes; ++j) {
            if (i != j) { // Avoid self-loops
                edges(idx, 0) = i;
                edges(idx, 1) = j;
                idx++;
            }
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    
    arma::vec weights(edges.n_rows);
    for (arma::uword i = 0; i < weights.n_elem; ++i) {
        weights[i] = beta_distribution(params.edge_mean, params.edge_var, gen);
    }
    arma::uvec pruned_indices = arma::find(weights >= P(params, "edge_threshold"));
    arma::umat pruned_edges = edges.rows(pruned_indices);
    arma::vec pruned_weights = weights.elem(pruned_indices);

    adjMat = arma::mat(params.num_nodes, params.num_nodes, arma::fill::zeros);
    for (arma::uword i = 0; i < pruned_edges.n_rows; ++i) {
        adjMat(pruned_edges(i, 0), pruned_edges(i, 1)) = pruned_weights(i);
    }
}

/* void Graph::createPayoffs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    node_payoffs = arma::vec(adjMat.n_cols);
    for (arma::uword i = 0; i < node_payoffs.n_elem; ++i) {
        node_payoffs(i) = dist(gen);
    }
} */

/* void Graph::createPayoffs() {
    arma::vec colSums = arma::sum(adjMat, 0).t();
    node_payoffs = colSums / arma::accu(colSums);
} */

void Graph::createPayoffs() {
    node_payoffs = arma::ones(adjMat.n_cols);
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