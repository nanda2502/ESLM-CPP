#ifndef LearningDecision_H
#define LearningDecision_H

#include <armadillo>
#include "Payoffs.h"

/**
 * This function simulates social learning in a group of agents. Agents choose what to learn based on 
 * the actions they observed other agents perform in the payoff stage of the current time step. Agents learn
 * their choices based on a specified strategy, which is chosen based on the params.strategy value:
 *
 * @param time The current time step in the simulation.
 * @param data Reference to the PayoffData object containing payoff information.
 * @param groups A matrix where each row represents a group of agent indices.
 * @param params Reference to the Params object containing simulation parameters, including the strategy function.
 * @return An arma::ivec representing the learning choices for all agents. 
 * Indices correspond to agent indices. Values correspond to node indices
 */
arma::ivec learnSocially(int time, const PayoffData& data, const arma::umat& groups, const Params& params);

/**
 * Randomly picks an action to learn from the actions other agents
 * in the group chose in the payoff stage of the current time step
 *
 * @param data The PayoffData object containing the necessary data.
 * @param group The group of individuals for which the strategy is generated.
 * @param time The current time step.
 * @param params The Params object containing additional simulation parameters.
 * @return An arma::ivec representing the learning choices for the group.
 */
arma::ivec randomStrategy(const PayoffData& data, const arma::uvec& group, int time, const Params& params);

/**
 * Picks an action to learn from the actions other agents
 * in the group chose in the payoff stage of the current time step.
 * Actions that were associated with higher payoffs are more likely to be picked. 
 *
 * @param data The PayoffData object containing the necessary data.
 * @param group The group of individuals for which the strategy is generated.
 * @param time The current time step.
 * @param params The Params object containing additional simulation parameters.
 * @return An arma::ivec representing the learning choices for the group. 
 */
arma::ivec payoffBasedStrategy(const PayoffData& data, const arma::uvec& group, int time, const Params& params);

#endif // LearningDecision_H

