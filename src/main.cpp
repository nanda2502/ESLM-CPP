#include "Payoffs.h"
#include "Graph.h"
#include "Agents.h"
#include "RunSimulation.h"
#include "Params.h"
#include <cstdlib>




int main(int argc, char* argv[]) {
    Params params = createParams(argc, argv); 
    Graph graph(params);
    Agents agents(graph, params);
    PayoffData payoff_data(params);
    

    runSimulation(payoff_data, agents, graph, params);
 
    payoff_data.saveToCSV(argc, argv);
    return 0;
}
