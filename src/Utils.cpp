#include "Utils.h"
#include <stdexcept>

double beta_distribution(double mean, double variance, std::mt19937& gen) {
    if (mean <= 0 || mean >= 1) throw std::invalid_argument("Mean must be between 0 and 1");
    if (variance <= 0) throw std::invalid_argument("Variance must be positive");
    
    double common_factor = (mean * (1 - mean) / variance) - 1;
    if (common_factor <= 0) throw std::invalid_argument("Invalid mean/variance combination");

    double alpha = mean * common_factor;
    double beta = (1 - mean) * common_factor;

    std::gamma_distribution<> dist_alpha(alpha, 1.0);
    std::gamma_distribution<> dist_beta(beta, 1.0);
    double x = dist_alpha(gen);
    double y = dist_beta(gen);
    return x / (x + y);
}