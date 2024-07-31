#ifndef Payoffs_H
#define Payoffs_H

#include <armadillo>
#include "Agents.h"

struct PayoffData {
    arma::imat choices;
    arma::mat payoffs;

    PayoffData(const Params& params);

    void saveToCSV(int argc, char* argv[]);
};

/**
 * Determines the actions for each agent either randomly (if time is 0)
 * or based on historical payoffs, with recent payoffs weighted more heavily.
 *
 * @param seed An integer seed for the random number generator.
 * @param time The current time step in the simulation.
 * @param data Reference to the PayoffData object containing historical payoff information.
 * @param params Reference to the Params object containing simulation parameters.
 * @return An arma::ivec containing the selected actions for each agent.
 */
arma::ivec chooseActions(int time_step, PayoffData& data, const Params& params);

/**
 * Updates the `PayoffData` object by recording the choices and
 * calculating the payoffs based on the agents' competencies.
 *
 * @param time_step The current time step in the simulation.
 * @param choices An arma::ivec containing the chosen actions for each agent.
 * @param agents Reference to the Agents object containing agent competencies.
 * @param payoffData Reference to the PayoffData object to be updated.
 */
void updatePayoffs(int time_step, const arma::ivec& choices, const Agents& agents, PayoffData& payoffData);

#endif // Payoffs_H