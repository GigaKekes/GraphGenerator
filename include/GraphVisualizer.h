#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>

#include "dataStructures.h"


class GraphVisualizer {
private:
  std::vector<Vertex> vertices;
  std::vector<Edge> edges;
  int width, height;

public:
  GraphVisualizer(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges, int width, int height);
  void visualize(const std::string& filename);
private:
  void writeBMPHeader(std::ofstream& bmpFile);
  void drawEdges(std::ofstream& bmpFile);
  void drawVertices(std::ofstream& bmpFile);
  void drawLine(std::ofstream& bmpFile, int x1, int y1, int x2, int y2, const unsigned char color[3]);
  void drawCircle(std::ofstream& bmpFile, int cx, int cy, int radius, const unsigned char color[3]);
  void setPixel(std::ofstream& bmpFile, int x, int y, const unsigned char color[3]);
  void writeText(std::ofstream& bmpFile, int x, int y, int id, const unsigned char color[3]);
  void drawDigit(std::ofstream& bmpFile, int x, int y, int digit, const unsigned char color[3]);
};
