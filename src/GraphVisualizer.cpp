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
  for (int i = 0; i < vertices.size(); i++) {
    unsigned char colors[3] = {255,0,0};
    drawCircle(bmpFile, static_cast<int>(vertices[i].x), static_cast<int>(vertices[i].y), 10, colors);
    writeText(bmpFile, static_cast<int>(vertices[i].x), static_cast<int>(vertices[i].y), i);
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
      if ((x - cx)*(x - cx) + (y - cy)*(y - cy) <= radius*radius) {
        setPixel(bmpFile, x, y, color);
      }
    }
  }
}

void GraphVisualizer::writeText(std::ofstream& bmpFile, int x, int y, int id) 
{
  const int charWidth = 12; // Width of each character
  const int charHeight = 16; // Height of each character
  int digit = 0;
  unsigned char textColor[3] = {0, 0, 0}; // Black color for text

  while(id != 0) 
  {
    digit = id % 10;
    for (int i = 0; i < charHeight; ++i) {
      for (int j = 0; j < charWidth; ++j) {
        int pixelX = x + j;
        int pixelY = y - i; // Invert Y for text

        if (pixelX >= 0 && pixelX < width && pixelY >= 0 && pixelY < height) {
          setPixel(bmpFile, pixelX, pixelY, textColor);
        }
      }
    }
    id = id/10;
    x += charWidth;
  }
}


void GraphVisualizer::setPixel(std::ofstream& bmpFile, int x, int y, const unsigned char color[3]) 
{
  if (x >= 0 && x < width && y >= 0 && y < height) {
    int offset = 54;
    int pixels_to_y = width * (height - y - 1);
    int bits_to_pixel = 3 * ( pixels_to_y + x);
    int padding = (width%4)*(height - y - 1);

    bmpFile.seekp(offset + bits_to_pixel + padding);
    bmpFile.write((char *)&color, 3);
  }
}
