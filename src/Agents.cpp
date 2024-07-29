#include "Agents.h"

Agents::Agents(const Graph* graph, const Params* params, int seed) {
    initialize(graph, params, seed);
}

void Agents::initialize(const Graph* graph, const Params* params, int seed) {
    int num_nodes = graph->adjMat.n_cols;
    int n = params->n;

    arma::vec indegree = arma::sum(graph->adjMat, 0).t();
    arma::vec normalized_indegree = indegree / arma::accu(indegree);
    arma::vec avg_competence = 1.0 - normalized_indegree;

    competences.set_size(n, num_nodes);
    std::mt19937 gen(seed);

    for (arma::uword i = 0; i < num_nodes; ++i) {
        double mean = avg_competence(i);
        double alpha = mean * (mean * (1 - mean) / params->competences_var - 1);
        double beta = (1 - mean) * (mean * (1 - mean) / params->competences_var);

        for (arma::uword j = 0; j < n; ++j) {
            competences(j, i) = beta_distribution(alpha, beta, gen);
        }
    }

    node_weights.set_size(n, num_nodes);
    double node_mean = params->node_mean;
    double node_var = params->node_var;
    double node_alpha = node_mean * (node_mean * (1 - node_mean) / node_var);
    double node_beta = (1 - node_mean) * (node_mean * (1 - node_mean) / node_var);
    for (arma::uword i = 0; i < num_nodes; ++i) {
        for (arma::uword j = 0; j < n; ++j) {
            node_weights(j, i) = 2 * beta_distribution(node_alpha, node_beta, gen);
        }
    }

    edge_weights.set_size(n, num_nodes, num_nodes);
    for (arma::uword slice = 0; slice < n; ++slice) {
        for (arma::uword i = 0; i < num_nodes; ++i) {
            for (arma::uword j = 0; j < num_nodes; ++j) {
                double mean = graph->adjMat(i, j);
                double alpha = mean * (mean * (1 - mean) / params->edge_var - 1);
                double beta = (1 - mean) * (mean * (1 - mean) / params->edge_var);
                edge_weights(slice, i, j) = beta_distribution(alpha, beta, gen);
            }
        }
    }

    ages.set_size(n);
    std::uniform_real_distribution<double> uniform_dist(0.0, 1.0);
    for (arma::uword i = 0; i < n; ++i) {
        double competence_sum = arma::accu(competences.row(i));
        double random_component = uniform_dist(gen);
        ages(i) = static_cast<int>((params->cor_age_competence * competence_sum + (1 - params->cor_age_competence) * random_component) * 100);
    }
}

