#include "Assortment.h"

arma::umat Assortment::createAssortment(const Agents& agents, const Params& params) {
    if (P(params, "assortment") == 0) {
        return ageBased(agents, params);
    } else if (P(params, "assortment") == 1) {
        return randomStatic(agents, params);
    } else if (P(params, "assortment") == 2) {
        return randomDynamic(agents, params);
    } else {
        throw std::invalid_argument("Invalid assortment type");
    }
}


arma::umat Assortment::ageBased(const Agents& agents, const Params& params) {
    arma::uvec sorted_indices = arma::sort_index(agents.ages);
    int group_size = P(params, "n") / P(params, "m");
    arma::umat result(P(params, "m"), group_size);
    for (int i = 0; i < P(params, "m"); ++i) {
        result.row(i) = sorted_indices.subvec(i * group_size, (i + 1) * group_size - 1).t();
    }
    return result;
}

arma::umat Assortment::randomDynamic(const Agents& agents, const Params& params) {
    arma::uvec shuffled_indices = arma::shuffle(arma::linspace<arma::uvec>(0, P(params, "n") - 1, P(params, "n")));
    int group_size = P(params, "n") / P(params, "m");
    arma::umat result(P(params, "m"), group_size);
    for (int i = 0; i < P(params, "m"); ++i) {
        result.row(i) = shuffled_indices.subvec(i * group_size, (i + 1) * group_size - 1).t();
    }
    return result;
}

arma::umat Assortment::randomStatic(const Agents& agents, const Params& params) {
    static arma::umat result;
    static bool computed = false;
    if (!computed) {
        arma::uvec shuffled_indices = arma::shuffle(arma::linspace<arma::uvec>(0, P(params, "n") - 1, P(params, "n")));
        int group_size = P(params, "n") / P(params, "m");
        result.set_size(P(params, "m"), group_size);
        for (int i = 0; i < P(params, "m"); ++i) {
            result.row(i) = shuffled_indices.subvec(i * group_size, (i + 1) * group_size - 1).t();
        }
        computed = true;
    }
    return result;
}