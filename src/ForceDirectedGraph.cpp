#include <ForceDirectedGraph.h>

#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

#include <dataStructures.h>


ForceDirectedGraph::ForceDirectedGraph(std::vector<edge> edges, int numOfVertexes, int idealSize) 
{
  k = sqrt((double)(idealSize*idealSize) / numOfVertexes);
  temperature = 1;
  this->idealSize = idealSize;
  this->numOfVertexes = numOfVertexes;

  srand(time(NULL));
  for (int i = 0; i < numOfVertexes; ++i) 
  {
    vertex vertex;
    vertex.x = static_cast<double>(rand() % idealSize);
    vertex.y = static_cast<double>(rand() % idealSize);
    vertexes.push_back(vertex);
  } 
}

void ForceDirectedGraph::fruchtermanReingold()
{
  int iterations = 1000;

  for(int i = 0; i < iterations; ++i) 
  {
    // Compute attractive and repulsive attractiveForces
    std::cout << "\nCalc " << i << " attractive forces" << std::endl;
    
    std::vector<vertex> attractiveForces = FRComputeAttractiveForces();

     
    std::cout << "\nCalc " << i << " repulcive forces" << std::endl;

    std::vector<vertex> repulsiveForces = FRComputeRepulsiveForces();

    std::cout << "\nUpdating Positions" << std::endl;
    
    // Update vertex positions based on attractiveForces
    Update(attractiveForces, repulsiveForces);

    std::cout <<'\n'<< i << " succsesful" << std::endl;
    
    // Decrease the temperature to simulate cooling
    temperature *= kCooling;

  }
}


