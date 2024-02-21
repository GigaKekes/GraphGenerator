#include <GraphVisualizer.h>

GraphVisualizer::GraphVisualizer(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges, int width, int height)
: vertices(vertices), edges(edges), width(width), height(height) {}

void GraphVisualizer::visualize(const std::string& filename) 
{
  std::ofstream bmpFile(filename, std::ios::binary);

  if (!bmpFile.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  // BMP header
  writeBMPHeader(bmpFile);

  // BMP data
  drawEdges(bmpFile);
  drawVertices(bmpFile);

  bmpFile.close();
}


void GraphVisualizer::writeBMPHeader(std::ofstream& bmpFile) {
  // BMP File Header
  const char* header = "BM";
  bmpFile.write(header, 2);

  int fileSize = 54 + 3 * width * height;
  bmpFile.write(reinterpret_cast<const char*>(&fileSize), 4);

  int reserved = 0;
  bmpFile.write(reinterpret_cast<const char*>(&reserved), 4);

  int dataOffset = 54;
  bmpFile.write(reinterpret_cast<const char*>(&dataOffset), 4);

  // BMP Info Header
  int infoHeaderSize = 40;
  bmpFile.write(reinterpret_cast<const char*>(&infoHeaderSize), 4);

  bmpFile.write(reinterpret_cast<const char*>(&width), 4);
  bmpFile.write(reinterpret_cast<const char*>(&height), 4);

  short planes = 1;
  bmpFile.write(reinterpret_cast<const char*>(&planes), 2);

  short bitsPerPixel = 24; // 3 bytes per pixel (RGB)
  bmpFile.write(reinterpret_cast<const char*>(&bitsPerPixel), 2);

  int compression = 0;
  bmpFile.write(reinterpret_cast<const char*>(&compression), 4);

  int imageSize = 3 * width * height;
  bmpFile.write(reinterpret_cast<const char*>(&imageSize), 4);

  int xPixelsPerMeter = 2835; // Standard 72 dpi
  bmpFile.write(reinterpret_cast<const char*>(&xPixelsPerMeter), 4);

  int yPixelsPerMeter = 2835; // Standard 72 dpi
  bmpFile.write(reinterpret_cast<const char*>(&yPixelsPerMeter), 4);

  int totalColors = 0;
  bmpFile.write(reinterpret_cast<const char*>(&totalColors), 4);

  int importantColors = 0;
  bmpFile.write(reinterpret_cast<const char*>(&importantColors), 4);
}

void GraphVisualizer::drawEdges(std::ofstream& bmpFile) 
{
  for (const Edge& edge : edges) {
    unsigned char colors[3] = {255,0,0};
    drawLine(bmpFile, vertices[edge.u].x, vertices[edge.u].y, vertices[edge.v].x, vertices[edge.v].y, colors);
  }
}

void GraphVisualizer::drawVertices(std::ofstream& bmpFile) {
  for (const Vertex& vertex : vertices) {
    unsigned char colors[3] = {255,0,0};
    drawCircle(bmpFile, static_cast<int>(vertex.x), static_cast<int>(vertex.y), 10, colors);
  }
}

void GraphVisualizer::drawLine(std::ofstream& bmpFile, int x1, int y1, int x2, int y2, const unsigned char color[3]) 
{
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);

  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;

  int err = dx - dy;

  while (true) 
  {
    setPixel(bmpFile, x1, y1, color);

    if (x1 == x2 && y1 == y2) 
    {
      break;
    }

    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }

    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  }
}

void GraphVisualizer::drawCircle(std::ofstream& bmpFile, int cx, int cy, int radius, const unsigned char color[3]) 
{
  for (int x = cx - radius; x <= cx + radius; ++x) {
    for (int y = cy - radius; y <= cy + radius; ++y) {
      if (pow(x - cx, 2) + pow(y - cy, 2) <= pow(radius, 2)) {
        setPixel(bmpFile, x, y, color);
      }
    }
  }
}

void GraphVisualizer::setPixel(std::ofstream& bmpFile, int x, int y, const unsigned char color[3]) 
{
  if (x >= 0 && x < width && y >= 0 && y < height) {
    bmpFile.seekp(54 + 3 * (width * (height - y - 1) + x));
    bmpFile.write((char *)&color, 3);
  }
}
