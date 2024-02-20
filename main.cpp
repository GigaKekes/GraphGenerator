#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>

#include "include/dataStructures.h"

using namespace std;


int main() 
{
  ifstream inputFile("/home/dmitry/Programs/Projects/Assignment/GraphGenerator/test2.txt");
  
  if (!inputFile.is_open())
  {
      cerr << "Error opening input file." << endl;   
      return 1;
  }
    
  int numVertices, numEdges;
  inputFile >> numVertices >> numEdges;

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

  return 0;
}
