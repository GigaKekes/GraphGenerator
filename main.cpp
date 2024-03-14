#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <string>
#include <algorithm>

#include <dataStructures.h>
#include <ForceDirectedGraph.h>
#include <GraphVisualizer.h>
#include <FileReader.h>

using namespace std;


int main(int argc, char* argv[]) 
{

  FileReader filereada;

  ForceDirectedGraphConfig fdaConfig = filereada.GetForceDirectedConfig();
  BMPConfig bmpConfig = filereada.GetBMPConfig();
  vector<Edge> edges = filereada.GetEdgesFromInputFile(argv[1]); 
  int numVertexes = filereada.GetNumVertexes();

  ForceDirectedGraph graph(edges, numVertexes, std::min(bmpConfig.width, bmpConfig.height));
  graph.fruchtermanReingold(fdaConfig.iterations);
  graph.printLayout();

  GraphVisualizer graphVisualizer(graph.getVertexes(), edges, bmpConfig.width, bmpConfig.height);
  graphVisualizer.visualize("Graph_Visualization.bmp");
  return 0;
}
