#include "CompetenceUpdate.h"

void updateCompetences(Agents& agents, const arma::ivec& learning_choices, const Graph& graph) {
    arma::uword n_agents = learning_choices.n_elem;

    for (arma::uword agent_idx = 0; agent_idx < n_agents; ++agent_idx) {
        int chosen_node = learning_choices(agent_idx);
        arma::uvec parents = graph.getParents(arma::uvec{static_cast<arma::uword>(chosen_node)})(0);

        // Extract parent competences
        arma::vec parent_competences(parents.n_elem);
        for (arma::uword i = 0; i < parents.n_elem; ++i) {
            parent_competences(i) = agents.competences(agent_idx, parents(i));
        }

        // Extract edge weights for the chosen node
        arma::vec edge_weights(parents.n_elem);
        for (arma::uword i = 0; i < parents.n_elem; ++i) {
            edge_weights(i) = agents.edge_weights(agent_idx, parents(i), chosen_node);
        }

        // Compute the sum of competences weighted by edge weights
        double competence_sum = arma::dot(parent_competences, edge_weights);

        // Update the competence for the chosen node
        double updated_competence = agents.competences(agent_idx, chosen_node) + (competence_sum * agents.node_weights(agent_idx, chosen_node));
        agents.competences(agent_idx, chosen_node) = updated_competence;
    }
}