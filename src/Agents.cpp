#include "Agents.h"

Agents::Agents(const Graph& graph, const Params& params, int seed) {
    initialize(graph, params, seed);
}

void Agents::initialize(const Graph& graph, const Params& params, int seed) {
    int num_nodes = graph.adjMat.n_cols;
    int n = params.n;

    arma::vec indegree = arma::sum(graph.adjMat, 0).t();
    arma::vec normalized_indegree = indegree / arma::accu(indegree);
    arma::vec avg_competence = 1.0 - normalized_indegree;

    competences.set_size(n, num_nodes);
    std::mt19937 gen(seed);

    for (arma::uword i = 0; i < num_nodes; ++i) {
        double mean = avg_competence(i);
        for (arma::uword j = 0; j < n; ++j) {
            competences(j, i) = beta_distribution(mean, params.competences_var, gen);
        }
    }

    node_weights.set_size(n, num_nodes);
    for (arma::uword i = 0; i < num_nodes; ++i) {
        for (arma::uword j = 0; j < n; ++j) {
            node_weights(j, i) = 2 * beta_distribution(params.node_mean, params.node_var, gen);
        }
    }

    edge_weights.set_size(n, num_nodes, num_nodes);
    for (arma::uword slice = 0; slice < n; ++slice) {
        for (arma::uword i = 0; i < num_nodes; ++i) {
            for (arma::uword j = 0; j < num_nodes; ++j) {
                double mean = graph.adjMat(i, j);
                edge_weights(slice, i, j) = beta_distribution(mean, params.edge_var, gen);
            }
        }
    }

    ages.set_size(n);
    std::uniform_real_distribution<double> uniform_dist(0.0, 1.0);
    for (arma::uword i = 0; i < n; ++i) {
        double competence_sum = arma::accu(competences.row(i));
        double random_component = uniform_dist(gen);
        double cor_age_competence = params.cor_age_competence;
        ages(i) = static_cast<int>((cor_age_competence * competence_sum + (1 - cor_age_competence) * random_component) * 100);
    }
}

