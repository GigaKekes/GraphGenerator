#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>

#include <dataStructures.h>
#include <ForceDirectedGraph.h>
#include <GraphVisualizer.h>

using namespace std;


int main() 
{
  ifstream inputFile("/home/dmitry/Programs/Projects/Assignment/GraphGenerator/test.txt");

  if (!inputFile.is_open())
  {
    cerr << "Error opening input file." << endl;   
    return 1;
  }

  int numVertexes, numEdges;
  inputFile >> numVertexes >> numEdges;

  vector<Edge> edges;
  for (int i = 0; i < numEdges; ++i) 
  {
    Edge edge;
    inputFile >> edge.u >> edge.v;
    edge.u--;
    edge.v--;    
    edges.push_back(edge);
  }

  inputFile.close();

  ForceDirectedGraph graph(edges, numVertexes, 2000);
  graph.fruchtermanReingold();
  graph.printLayout();

  GraphVisualizer graphVisualizer(graph.getVertexes(), edges, 2000, 2000);
  graphVisualizer.visualize("Graph_Visualization.bmp");
  return 0;
}
