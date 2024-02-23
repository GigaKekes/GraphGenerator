#include <vector>

#include "dataStructures.h"
#include "Graph.h"

class ForceDirectedGraph : Graph{

private:
  const double kCooling = 0.85;
  double k; // Constant for force calculation
  double temperature; // Temperature for the simulation
  std::vector<Edge> edges;
public:
  ForceDirectedGraph(std::vector<Edge> edges, int numOfVertexes, int idealSize);
  void fruchtermanReingold(int iterations);
  void printLayout();
  std::vector<Vertex> getVertexes();
private:
  void inshape();

private:
};
