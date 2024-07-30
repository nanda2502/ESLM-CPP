#include "Payoffs.h"
#include "LearningDecision.h"
#include "competenceUpdate.h"
#include "Graph.h"
#include "Agents.h"
#include "Assortment.h"
#include "RunSimulation.h"
#include <cstdlib>


Params createParams(int argc, char* argv[]) {
    Params params;
    params.params["t"] = std::atoi(argv[2]);
    params.params["num_nodes"] = std::atoi(argv[3]);
    params.params["n"] = std::atoi(argv[4]);
    params.params["m"] = std::atoi(argv[5]);
    params.params["edge_mean"] = std::atof(argv[6]);
    params.params["edge_var"] = std::atof(argv[7]);
    params.params["edge_threshold"] = std::atof(argv[8]);
    params.params["payoffs_mean"] = std::atof(argv[9]);
    params.params["competences_sd"] = std::atof(argv[10]);
    params.params["node_mean"] = std::atof(argv[11]);
    params.params["node_var"] = std::atof(argv[12]);
    params.params["agent_edge_sd"] = std::atof(argv[13]);
    params.params["cor_age_competence"] = std::atof(argv[14]);
    params.params["experience_bias"] = std::atof(argv[15]);
    params.params["assortment"] = std::atoi(argv[16]);
    params.params["strategy"] = std::atoi(argv[17]);

    return params;
}

int main(int argc, char* argv[]) {
    int seed = std::atoi(argv[1]);
    Params params = createParams(argc, argv); 
    Graph graph(params, seed);
    Agents agents(graph, params, seed);
    PayoffData payoff_data(params);
    

    runSimulation(seed, payoff_data, agents, graph, params);
 
    payoff_data.saveToCSV(argc, argv);
    return 0;
}
