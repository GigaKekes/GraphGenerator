#include <vector>

#include "dataStructures.h"
#include "Graph.h"

class ForceDirectedGraph : Graph{

private:
  const double kCooling = 0.85; // Constant for temperature cooldown
  double k; // Constant for force calculation
  double temperature; // Temperature for the simulation
  std::vector<Edge> edges;
  int idealSize;
  int numOfVertexes;
public:
  ForceDirectedGraph(std::vector<Edge> edges, int numOfVertexes, int idealSize);
  void fruchtermanReingold(int iterations); // Implements Fruchterman-Reingold algorithm
  void printLayout(); // Prints x,y of each vertex
  std::vector<Vertex> getVertexes(); // Returns vertexes
private:
  void inshape(); // Used for scaling the graph so it is inside an image (0 < x,y < idealSize) and relations between vertexes are saved 
};
