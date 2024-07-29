#ifndef ASSORTMENT_H
#define ASSORTMENT_H

#include "Agents.h"
#include "Types.h"
#include <vector>
#include <armadillo>

struct Assortment {
    static arma::umat createAssortment(const Agents& agents, const Params& params);
};

#endif // ASSORTMENT_H