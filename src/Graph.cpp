#include <Graph.h>

#include <ctime>
#include <stdlib.h>

#include <dataStructures.h>


Graph::Graph(std::vector<edge> edges, int numOfVertexes, int idealSpread) : edges(edges), numOfVertexes(numOfVertexes), idealSpread(idealSpread)
{
  srand(time(NULL));
  for (int i = 0; i < numOfVertexes; ++i) 
  {
    vertex vertex;
    vertex.x = static_cast<double>(rand() % idealSpread);
    vertex.y = static_cast<double>(rand() % idealSpread);
    vertexes.push_back(vertex);
  }
};


