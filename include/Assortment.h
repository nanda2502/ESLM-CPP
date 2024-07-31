#ifndef ASSORTMENT_H
#define ASSORTMENT_H

#include <armadillo>
#include "Agents.h"
#include "Params.h"


struct Assortment {
    static arma::umat createAssortment(const Agents& agents, const Params& params); 

private:
    static arma::umat ageBased(const Agents& agents, const Params& params);
    static arma::umat randomDynamic(const Agents& agents, const Params& params);
    static arma::umat randomStatic(const Agents& agents, const Params& params);
    static std::unordered_map<std::tuple<const Agents*, const Params*, int>, arma::umat> memo;
};
#endif // ASSORTMENT_H