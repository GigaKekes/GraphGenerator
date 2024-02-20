#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>

#include "include/dataStructures.h"
//#include <Graph.h>

using namespace std;


int main() 
{
  ifstream inputFile("/home/dmitry/Programs/Projects/Assignment/GraphGenerator/test2.txt");
  
  if (!inputFile.is_open())
  {
      cerr << "Error opening input file." << endl;   
      return 1;
  }
    
  int numVertexes, numEdges;
  inputFile >> numVertexes >> numEdges;

  vector<edge> edges;
  for (int i = 0; i < numEdges; ++i) 
  {
      edge edge;
      inputFile >> edge.u >> edge.v;
      edge.u--;
      edge.v--;    
      edges.push_back(edge);
  }
  
  inputFile.close();


  //Graph graph(edges, numVertexes, 2000); 
  return 0;
}
