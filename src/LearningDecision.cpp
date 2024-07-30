#include "LearningDecision.h"
#include "Agents.h"
#include <iostream>


arma::ivec learnSocially(int time, const PayoffData& data, const arma::umat& groups, const Params& params, int seed) {
    arma::ivec final_choices(static_cast<arma::ivec::elem_type>(P(params, "n")));
    final_choices.fill(-1);

    for (arma::uword group_idx = 0; group_idx < groups.n_rows; ++group_idx) {
        arma::uvec group = groups.row(group_idx).t();
        arma::ivec group_choices;

        double strategy = P(params, "strategy");

        if (strategy == 0) {
            group_choices = randomStrategy(data, group, seed, time, params);
        } else if (strategy == 1) {
            group_choices = payoffBasedStrategy(data, group, seed, time, params);
        } else {
            throw std::invalid_argument("Invalid strategy type");
        }

        for (arma::uword i = 0; i < group.n_elem; ++i) {
            final_choices(group(i)) = group_choices(i);
        }
    }
    return final_choices;
}

arma::ivec randomStrategy(const PayoffData& data, const arma::uvec& group, int seed, int time, const Params& params) {
    std::uniform_int_distribution<> dis(0, P(params, "num_nodes") - 1);
    arma::ivec choices(group.n_elem);
    for (arma::uword i = 0; i < group.n_elem; ++i) {
        std::mt19937 gen(seed + time + i);
        choices(i) = dis(gen);
    }
    return choices;
}

arma::ivec payoffBasedStrategy(const PayoffData& data, const arma::uvec& group, int seed, int time, const Params& params) {
    if (time >= data.payoffs.n_cols) {
        throw std::out_of_range("Time index exceeds the number of columns in payoffs data");
    }

    arma::ivec choices(group.n_elem);
    arma::vec group_payoffs = arma::zeros<arma::vec>(group.n_elem);

    // Extract relevant payoffs for the given group
    for (arma::uword i = 0; i < group.n_elem; ++i) {
        group_payoffs(i) = data.payoffs(group(i), time);
    }
    
    double sum_payoffs = arma::accu(group_payoffs);
    if (sum_payoffs == 0) {
        throw std::logic_error("Sum of payoffs is zero, cannot normalize");
    }
    group_payoffs = group_payoffs / sum_payoffs;

    for (arma::uword i = 0; i < group.n_elem; ++i) {
        std::mt19937 gen(seed + time + i + group(i));
        std::discrete_distribution<> dist(group_payoffs.begin(), group_payoffs.end());
        choices(i) = dist(gen);
    }

    return choices;
}


