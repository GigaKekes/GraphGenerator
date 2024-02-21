#ifndef GRGEN_INCL_GRAPH
#define GRGEN_INCL_GRAPH 

#include <vector>

#include "dataStructures.h"

class Graph
{
protected:
  std::vector<Edge> edges;
  std::vector<Vertex> vertexes;
  int numOfVertexes;
  int idealSize;
public:
  Graph(std::vector<Edge> edges, int numOfVertexes, int idealSize);
  Graph();

};

#endif // GRGEN_INCL_GRAPH 
