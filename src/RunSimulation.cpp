#include "Payoffs.h"
#include "LearningDecision.h"
#include "competenceUpdate.h"
#include "Assortment.h"

/**
 * Runs the simulation for a specified number of time steps.
 *
 * This function iterates over the time steps from 0 to params.t. At each time step, it performs the following steps:
 * 1. Gets choices from chooseActions.
 * 2. Updates payoffs using updatePayoffs.
 * 3. Gets learning choices from learnSocially.
 * 4. Updates competences using updateCompetences.
 *
 * @param data Reference to the PayoffData object containing payoff information.
 * @param agents Reference to the AgentData object containing agent information.
 * @param graph Reference to the Graph object containing the graph structure.
 * @param params Reference to the Params object containing simulation parameters.
 */
void runSimulation(PayoffData& data, Agents& agents, Graph& graph, const Params& params) {
    

    for (int time_step = 0; time_step < params.t; ++time_step) {
        arma::umat groups = Assortment::createAssortment(agents, params);
        arma::ivec choices = chooseActions(time_step, data, params);
        updatePayoffs(time_step, choices, agents, data);
        arma::ivec learning_choices = learnSocially(time_step, data, groups, params);
        updateCompetences(agents, learning_choices, graph);
    }
}
