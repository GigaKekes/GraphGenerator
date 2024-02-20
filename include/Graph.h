#ifndef GRGEN_INCL_GRAPH
#define GRGEN_INCL_GRAPH 

#include <vector>
#include "dataStructures.h"

class Graph
{
  std::vector<Edge> edges;
  std::vector<Vertex> vertexes;
  int numOfVertexes;
  int idealSpread;

  Graph(std::vector<Edge> edges, int numOfVertexes, int idealSpread) : edges(edges), numOfVertexes(numOfVertexes), idealSpread(idealSpread) :
  {

  };
  
};

#endif // GRGEN_INCL_GRAPH 
