#ifndef UTILS_H
#define UTILS_H

#include <random>

/**
 * Generates a random number from a beta distribution.
 * 
 * @param mean The mean of the beta distribution.
 * @param variance The variance of the beta distribution.
 * @param gen The random number generator.
 * @return A random number from the beta distribution.
 */
double beta_distribution(double mean, double variance, std::mt19937& gen);

#endif // UTILS_H