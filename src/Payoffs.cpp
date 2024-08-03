#include "Agents.h"
#include <random>
#include "Payoffs.h"

PayoffData::PayoffData(const Params& params)
    : choices(params.n, params.t),
      payoffs(params.n, params.t) {}

void PayoffData::saveToCSV(int argc, char* argv[]) {
    std::ostringstream oss;
    for (int i = 1; i < argc; ++i) {
        oss << argv[i];
        if (i < argc - 1) {
            oss << "_";
        }
    }
    std::string base_filename = oss.str();
    std::string payoffs_filename = "../data/payoffs_" + base_filename + ".csv";
    payoffs.save(payoffs_filename, arma::csv_ascii);
}

arma::ivec chooseActions(int time_step, PayoffData& data, const Params& params) {
   
    if (time_step == 0) {
        arma::ivec choices(params.n);
        std::uniform_int_distribution<> dist(0, params.num_nodes - 1);
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int i = 0; i < params.n; ++i) {
            choices[i] = dist(gen);
        }
        return choices;
    } else {
        arma::mat weighted_payoffs = data.payoffs.cols(0, time_step - 1);
        arma::rowvec time_factors = arma::regspace<arma::rowvec>(time_step, -1, time_step - weighted_payoffs.n_cols + 1);
        weighted_payoffs.each_row() /= time_factors;

        arma::mat summed_payoffs = arma::zeros<arma::mat>(params.n, params.num_nodes);
        for (arma::uword j = 0; j < weighted_payoffs.n_cols; ++j) {
            for (arma::uword i = 0; i < params.n; ++i) {
                int node_id = data.choices(i, j);
                summed_payoffs(i, node_id) += weighted_payoffs(i, j);
            }
        }

        for (arma::uword i = 0; i < params.n; ++i) {
            double row_sum = arma::sum(summed_payoffs.row(i));
            summed_payoffs.row(i) /= row_sum;
        }

        //odds are determined partially by historical data and partially by a uniform distribution
        double uniform_prob = 1.0 / params.num_nodes;
        for (arma::uword i = 0; i < summed_payoffs.n_rows; ++i) {
            for (arma::uword j = 0; j < summed_payoffs.n_cols; ++j) {
                summed_payoffs(i, j) = params.experience_bias * summed_payoffs(i, j) + (1 - params.experience_bias) * uniform_prob;
            }
        }

        arma::ivec choices(params.n);
        std::uniform_real_distribution<> dist(0.0, 1.0);
        std::random_device rd;
        std::mt19937 gen(rd());

        for (arma::uword i = 0; i < params.n; ++i) {
            double rand_val = dist(gen);
            double cumulative_prob = 0.0;
            for (arma::uword j = 0; j < summed_payoffs.n_cols; ++j) {
                cumulative_prob += summed_payoffs(i, j);
                if (rand_val <= cumulative_prob) {
                    choices[i] = j;
                    break;
                }
            }
        }
        return choices;
    }
}

void updatePayoffs(int time_step, const arma::ivec& choices, const Agents& agents, PayoffData& payoffData) {
    arma::uvec indices = arma::regspace<arma::uvec>(0, choices.n_elem - 1) * agents.competences.n_cols + arma::conv_to<arma::uvec>::from(choices);
    arma::vec competence_values = agents.competences.elem(indices);
    payoffData.choices.col(time_step) = choices;
    payoffData.payoffs.col(time_step) = competence_values % arma::conv_to<arma::vec>::from(choices);
}