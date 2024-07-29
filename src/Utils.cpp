#include "Utils.h"

double generate_beta(double alpha, double beta, std::mt19937& gen) {
    std::gamma_distribution<> dist_alpha(alpha, 1.0);
    std::gamma_distribution<> dist_beta(beta, 1.0);
    double x = dist_alpha(gen);
    double y = dist_beta(gen);
    return x / (x + y);
}