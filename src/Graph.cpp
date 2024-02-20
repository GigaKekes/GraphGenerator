#include <Graph.h>

#include <ctime>
#include <stdlib.h>

#include <dataStructures.h>


Graph::Graph(std::vector<edge> edges, int numOfVertexes, int idealSize) : edges(edges), numOfVertexes(numOfVertexes), idealSize(idealSize)
{
  srand(time(NULL));
  for (int i = 0; i < numOfVertexes; ++i) 
  {
    vertex vertex;
    vertex.x = static_cast<double>(rand() % idealSize);
    vertex.y = static_cast<double>(rand() % idealSize);
    vertexes.push_back(vertex);
  }
};

Graph::Graph()
{

}


