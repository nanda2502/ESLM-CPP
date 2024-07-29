#include "Utils.h"

double generate_beta(double mean, double variance, std::mt19937& gen) {
    double alpha = mean * ((mean * (1 - mean) / variance) - 1);
    double beta = (1 - mean) * ((mean * (1 - mean) / variance) - 1);
    std::gamma_distribution<> dist_alpha(alpha, 1.0);
    std::gamma_distribution<> dist_beta(beta, 1.0);
    double x = dist_alpha(gen);
    double y = dist_beta(gen);
    return x / (x + y);
}