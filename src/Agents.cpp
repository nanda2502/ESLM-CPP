#include "Agents.h"

Agents::Agents(const Graph& graph, const Params& params) {
    initialize(graph, params);
}

void Agents::initialize(const Graph& graph, const Params& params) {
    int num_nodes = graph.adjMat.n_cols;
    int n = params.n;

    arma::vec indegree = arma::sum(graph.adjMat, 0).t();
    arma::vec normalized_indegree = indegree / arma::accu(indegree);
    arma::vec avg_competence = 1.0 - normalized_indegree;

    competences.set_size(n, num_nodes);
    std::random_device rd;
    std::mt19937 gen(rd());
    
    node_weights.set_size(n, num_nodes);
    for (arma::uword i = 0; i < num_nodes; ++i) {
        double mean = avg_competence(i);
        std::normal_distribution<> normal_dist(mean, params.competences_sd);
        
        for (arma::uword j = 0; j < n; ++j) {
            competences(j, i) = normal_dist(gen);
        }
    }

    edge_weights.set_size(n, num_nodes, num_nodes);
    for (arma::uword slice = 0; slice < n; ++slice) {
        for (arma::uword i = 0; i < num_nodes; ++i) {
            for (arma::uword j = 0; j < num_nodes; ++j) {
                double mean = graph.adjMat(i, j);
                if (mean > 0) {  // Only apply Gaussian if there's an edge
                    std::normal_distribution<> dist(mean, params.agent_edge_sd);
                    edge_weights(slice, i, j) = dist(gen);
                } else {
                    edge_weights(slice, i, j) = 0; // No edge, so weight is zero
                }
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

