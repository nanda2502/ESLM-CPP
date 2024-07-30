#ifndef ASSORTMENT_H
#define ASSORTMENT_H

#include <vector>
#include <armadillo>
#include "Agents.h"
#include "Params.h"


struct Assortment {
    static arma::umat createAssortment(const Agents& agents, const Params& params, int seed, int time_step); 

private:
    static arma::umat ageBased(const Agents& agents, const Params& params);
    static arma::umat randomDynamic(const Agents& agents, const Params& params, int seed, int time_step);
    static arma::umat randomStatic(const Agents& agents, const Params& params, int seed);
};
#endif // ASSORTMENT_H