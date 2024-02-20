#include <vector>

#include "dataStructures.h"
#include "Graph.h"

class ForceDirectedGraph : Graph{

private:
    const double kCooling = 0.9;
    double k; // Constant for force calculation
    double temperature; // Temperature for the simulation
public:
    ForceDirectedGraph(std::vector<Edge> edges, int numOfVertexes, int idealSize);
    void fruchtermanReingold();
    void printLayout();

    std::vector<vertex> getVertexes();
private:
  std::vector<vertex> FRComputeAttractiveForces();
  std::vector<vertex> FRComputeRepulsiveForces();
  void Update(const std::vector<Vertex>& attractiveForces, const std::vector<Vertex>& repulsiveForces);
};
