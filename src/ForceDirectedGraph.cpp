#include <ForceDirectedGraph.h>

#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

#include <dataStructures.h>


ForceDirectedGraph::ForceDirectedGraph(std::vector<Edge> edges, int numOfVertexes, int idealSize) 
{
  k = sqrt((double)(idealSize*idealSize) / numOfVertexes);
  temperature = idealSize / 10.0;
  this->idealSize = idealSize;
  this->numOfVertexes = numOfVertexes;

  srand(time(NULL));
  for (int i = 0; i < numOfVertexes; ++i) 
  {
    Vertex vertex;
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

    std::vector<Vertex> attractiveForces = FRComputeAttractiveForces();


    std::cout << "\nCalc " << i << " repulcive forces" << std::endl;

    std::vector<Vertex> repulsiveForces = FRComputeRepulsiveForces();

    std::cout << "\nUpdating Positions" << std::endl;

    // Update vertex positions based on attractiveForces
    Update(attractiveForces, repulsiveForces);

    std::cout <<'\n'<< i << " succsesful" << std::endl;

    // Decrease the temperature to simulate cooling
    temperature *= kCooling;

  }
}




void ForceDirectedGraph::printLayout() 
{
  for (int i = 0; i < vertexes.size(); ++i) 
  {
    std::cout << "Vertex " << i+1 << ": x=" << vertexes[i].x << ", y=" << vertexes[i].y << std::endl;
  }
}

std::vector<Vertex> ForceDirectedGraph::getVertexes()
{
  return vertexes;
}

std::vector<Vertex> ForceDirectedGraph::FRComputeAttractiveForces() 
{
  std::vector<Vertex> forces;
  for (size_t i = 0; i < vertexes.size(); i++) {
    forces.push_back(Vertex(0.0, 0.0));
  }

  for (auto edge : edges) {
    double dx = vertexes[edge.v].x - vertexes[edge.u].x;
    double dy = vertexes[edge.v].y - vertexes[edge.u].y;
    double distance = sqrt(dx * dx + dy * dy);
    double force = distance * distance / k;



    forces[edge.u].x += force * dx / distance;
    forces[edge.u].y += force * dy / distance;
    forces[edge.v].x -= force * dx / distance;
    forces[edge.v].y -= force * dy / distance;

  }

  for (size_t i = 0; i < vertexes.size(); i++) {
    if(std::isnan(forces[i].x)) forces[i].x = 0;
    if(std::isnan(forces[i].y)) forces[i].y = 0;
  }

  for (size_t i = 0; i < vertexes.size(); i++) {
    std::cout << forces[i].x << " " << forces[i].y << std::endl;
  }
  return forces;  
}

std::vector<Vertex> ForceDirectedGraph::FRComputeRepulsiveForces() 
{

  std::vector<Vertex> repulsiveForces;
  for (size_t i = 0; i < vertexes.size(); i++) {
    repulsiveForces.push_back(Vertex(0.0, 0.0));
  }

  for (int i = 0; i < vertexes.size(); ++i) {
    for (int j = 0; j < vertexes.size(); ++j) {
      if (i != j) {
        double dx = vertexes[j].x - vertexes[i].x;
        double dy = vertexes[j].y - vertexes[i].y;
        double distance = sqrt(dx * dx + dy * dy);
        double force = k * k / distance;

        repulsiveForces[i].x -= force * dx / distance;
        repulsiveForces[i].y -= force * dy / distance;
      }
    }
  }

  for (size_t i = 0; i < vertexes.size(); i++) {
    if(std::isnan(repulsiveForces[i].x)) repulsiveForces[i].x = 0;
    if(std::isnan(repulsiveForces[i].y)) repulsiveForces[i].y = 0;
  } 
  for (size_t i = 0; i < vertexes.size(); i++) {
    std::cout << repulsiveForces[i].x << " " << repulsiveForces[i].y << std::endl;
  }


  return repulsiveForces;
}

void ForceDirectedGraph::Update(const std::vector<Vertex>& attractiveForces, const std::vector<Vertex>& repulsiveForces) 
{
  int maxDistortion = 0;
  int maxNegDiviation = 0;

  for (int i = 0; i < vertexes.size(); ++i) {
    double displacement = sqrt(attractiveForces[i].x * attractiveForces[i].x + attractiveForces[i].y * attractiveForces[i].y)
      / sqrt(repulsiveForces[i].x * repulsiveForces[i].x + repulsiveForces[i].y * repulsiveForces[i].y);

    displacement = std::min(displacement, temperature);

    // Update vertex positions with bounds checking
    vertexes[i].x = vertexes[i].x + (attractiveForces[i].x + repulsiveForces[i].x) * displacement;
    vertexes[i].y = vertexes[i].y + (attractiveForces[i].y + repulsiveForces[i].y) * displacement;
    std::cout << vertexes[i].x << ' ' << vertexes[i].y << std::endl;

    if(vertexes[i].x > idealSize || vertexes[i].y > idealSize) maxDistortion = fmax(maxDistortion, fmax(vertexes[i].x, vertexes[i].y));
    if(vertexes[i].x < 0 || vertexes[i].y < 0) maxNegDiviation = abs(fmin(maxNegDiviation, fmin(vertexes[i].x, vertexes[i].y)));
  }
  if(maxNegDiviation != 0)
  {
    for(int i = 0; i < vertexes.size(); ++i)
    {
      vertexes[i].x += maxNegDiviation;
      vertexes[i].y += maxNegDiviation;
    }
    maxDistortion += maxNegDiviation;
  }
  if(maxDistortion != 0)
  {
    for(int i = 0; i < vertexes.size(); ++i)
    {
      vertexes[i].x = vertexes[i].x  * idealSize / (maxDistortion*1.05);
      vertexes[i].y = vertexes[i].y  * idealSize / (maxDistortion*1.05);
    }
  }
}
