#ifndef GRGEN_INCL_GRAPH
#define GRGEN_INCL_GRAPH 

#include <vector>

#include "dataStructures.h"

class Graph
{
private:
  std::vector<edge> edges;
  std::vector<vertex> vertexes;
  int numOfVertexes;
  int idealSpread;
public:
  Graph(std::vector<edge> edges, int numOfVertexes, int idealSpread); 
  
};

#endif // GRGEN_INCL_GRAPH 
