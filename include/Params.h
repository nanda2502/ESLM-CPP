#ifndef PARAMS_H
#define PARAMS_H

#include <map>
#include <string>

struct Params {
    std::map<std::string, double> params;
};

#define P(params, key) (params.params.at(key))

#endif // PARAMS_H