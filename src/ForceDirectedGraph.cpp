#include <ForceDirectedGraph.h>
#include <GraphVisualizer.h>

#include <cmath>
#include <ctime>
#include <cwchar>

#include <dataStructures.h>

ForceDirectedGraph::ForceDirectedGraph(std::vector<Edge> edges, int numOfVertexes, int idealSize) 
{
  k = sqrt((double)(idealSize*idealSize) / numOfVertexes);
  temperature = 10.0 * sqrt(vertexes.size());
  this->idealSize = idealSize;
  this->numOfVertexes = numOfVertexes;
  this->edges = edges;

  srand(time(NULL));
  for (int i = 0; i < numOfVertexes; ++i) 
  {
    Vertex vertex;
    vertex.x = static_cast<double>(rand() % idealSize);
    vertex.y = static_cast<double>(rand() % idealSize);
    vertexes.push_back(vertex);
  } 
}

void ForceDirectedGraph::fruchtermanReingold(int iterations)
{
  for(int i = 0; i < iterations; i++)
  {
    // Zeroing force
    Vertex space = {0.0, 0.0};
    std::vector<Vertex> forces(vertexes.size());
    fill(forces.begin(), forces.end(), space);

    // Computing repulcive forces
    for(size_t i = 0; i < vertexes.size(); i++) 
    {
      for(size_t j = i+1; j < vertexes.size(); j++)
      {
        if(i==j) continue;

        double dx = vertexes[i].x - vertexes[j].x;
        double dy = vertexes[i].y - vertexes[j].y;
        double distance = sqrt(dx * dx + dy * dy);

        double repulsion = k*k / distance;

        forces[i].x += repulsion * dx / distance;
        forces[i].y += repulsion * dy / distance;
        forces[j].x -= repulsion * dx / distance;
        forces[j].y -= repulsion * dy / distance;
      } 
    }
    // Computing attractiive forces
    for(auto edge : edges)
    {
      double dx = vertexes[edge.u].x - vertexes[edge.v].x;
      double dy = vertexes[edge.u].y - vertexes[edge.v].y;
      double distance = sqrt(dx * dx + dy * dy);

      double attraction = distance*distance / k;
      
      forces[edge.u].x -= attraction * dx / distance;
      forces[edge.u].y -= attraction * dy / distance;
      forces[edge.v].x += attraction * dx / distance;
      forces[edge.v].y += attraction * dy / distance;  
    }


    // Applying forces on vertexes
    for (size_t i = 0; i < vertexes.size(); i++) 
    {
      double force_norm = sqrt(forces[i].x * forces[i].x + forces[i].y * forces[i].y);
      double scale = std::min(force_norm, temperature);
      
      if(std::isnan(forces[i].x) || std::isnan(forces[i].y))
        continue;
      double movement_x = forces[i].x / force_norm * scale;
      double movement_y = forces[i].y / force_norm * scale;

      vertexes[i].x += movement_x;
      vertexes[i].y += movement_y;
    }

    // Cooling down
    temperature = std::max(1.5, temperature*kCooling);
    if(i < 2)
    {
      std::cout << i;
    printLayout();    
    }
  }
  inshape();

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

void ForceDirectedGraph::inshape()
{
  double maxNegDiv = 0.0;
  double maxDiv = idealSize;
  for(int j = 0; j < vertexes.size(); j++)
  {
    if(vertexes[j].x < 0.0 && abs(vertexes[j].x) > maxNegDiv) maxNegDiv = abs(vertexes[j].x);
    if(vertexes[j].y < 0.0 && abs(vertexes[j].y) > maxNegDiv) maxNegDiv = abs(vertexes[j].y);

    maxDiv = std::max(maxDiv, std::max(vertexes[j].x, vertexes[j].y));
  }


  for(int j = 0; j < vertexes.size(); j++)
  {
    vertexes[j].x += maxNegDiv + idealSize/100;
    vertexes[j].y += maxNegDiv + idealSize/100;
  }
  maxDiv += maxNegDiv + idealSize/100;

  for(int j = 0; j < vertexes.size(); j++)
  {
    vertexes[j].x = vertexes[j].x  * idealSize / (maxDiv*1.05);
    vertexes[j].y = vertexes[j].y  * idealSize / (maxDiv*1.05);
  }
}
