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


int main(int argc, char* argv[]) 
{
  ifstream inputFile(argv[1]);

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
    edges.push_back(edge);
  }
  inputFile.close();
  

  int idealSize = 2000;

  ForceDirectedGraph graph(edges, numVertexes, idealSize);
  graph.fruchtermanReingold(3000);
  graph.printLayout();

  GraphVisualizer graphVisualizer(graph.getVertexes(), edges, idealSize, idealSize);
  graphVisualizer.visualize("Graph_Visualization.bmp");
  return 0;
}
