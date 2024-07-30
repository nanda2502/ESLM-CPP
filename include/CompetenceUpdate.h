#ifndef CompetenceUpdate_H
#define CompetenceUpdate_H

#include <armadillo>
#include "Graph.h"
#include "Agents.h"

/**
 * Updates the competences of agents based on their chosen nodes and the graph structure.
 *
 * This function iterates over each agent and updates their competence values for their chosen nodes.
 * The update is based on the competences of the parent nodes of the chosen node, the edge weights from
 * the parent nodes to the chosen node, and the agent's node weight for the chosen node.
 *
 * The new competence for the chosen node is calculated using the formula:
 * New competence on node = Current competence on node + ((sum of competences of all parent nodes * edge weight from parent to chosen child node) * node weight)
 *
 * @param agents Reference to the AgentData object containing agent competences, edge weights, and node weights.
 * @param choices An arma::ivec containing the chosen nodes for each agent. The index corresponds to the agent, and the value corresponds to the chosen node.
 * @param graph Reference to the Graph object containing the adjacency matrix and parent node information.
 */
void updateCompetences(Agents& agents, const arma::ivec& learning_choices, const Graph& graph);

#endif // CompetenceUpdate_H