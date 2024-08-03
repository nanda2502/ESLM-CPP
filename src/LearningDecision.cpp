#include "LearningDecision.h"
#include <random>


arma::ivec learnSocially(int time, const PayoffData& data, const arma::umat& groups, const Params& params) {
    arma::ivec final_choices(static_cast<arma::ivec::elem_type>(params.n));
    final_choices.fill(-1);

    for (arma::uword group_idx = 0; group_idx < groups.n_rows; ++group_idx) {
        arma::uvec group = groups.row(group_idx).t();
        arma::ivec group_choices;

        double strategy = params.strategy;

        if (strategy == 0) {
            group_choices = randomStrategy(data, group, time, params);
        } else if (strategy == 1) {
            group_choices = payoffBasedStrategy(data, group, time, params);
        } else {
            throw std::invalid_argument("Invalid strategy type");
        }

        for (arma::uword i = 0; i < group.n_elem; ++i) {
            final_choices(group(i)) = group_choices(i);
        }
    }
    return final_choices;
}

arma::ivec randomStrategy(const PayoffData& data, const arma::uvec& group, int time, const Params& params) {
    std::uniform_int_distribution<> dis(0, params.num_nodes - 1);
    arma::ivec choices(group.n_elem);
    std::random_device rd;
    std::mt19937 gen(rd());
    for (arma::uword i = 0; i < group.n_elem; ++i) {
        choices(i) = dis(gen);
    }
    return choices;
}

arma::ivec payoffBasedStrategy(const PayoffData& data, const arma::uvec& group, int time, const Params& params) {

    arma::ivec choices(group.n_elem);
    arma::vec group_payoffs = arma::zeros<arma::vec>(group.n_elem);

    for (arma::uword i = 0; i < group.n_elem; ++i) {
        group_payoffs(i) = data.payoffs(group(i), time);
    }
    
    double sum_payoffs = arma::accu(group_payoffs);

    group_payoffs = group_payoffs / sum_payoffs;
    
    std::random_device rd;
    std::mt19937 gen(rd());

    for (arma::uword i = 0; i < group.n_elem; ++i) {
        std::discrete_distribution<> dist(group_payoffs.begin(), group_payoffs.end());
        choices(i) = dist(gen);
    }

    return choices;
}


