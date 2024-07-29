#include "Assortment.h"


arma::umat Assortment::createAssortment(const Agents& agents, const Params& params) {
    arma::uvec sorted_indices = arma::sort_index(agents.ages);
    int group_size = params.n / params.m;
    arma::umat result(params.m, group_size);
    for (int i = 0; i < params.m; ++i) {
        result.row(i) = sorted_indices.subvec(i * group_size, (i + 1) * group_size - 1).t();
    }
    return result;
}