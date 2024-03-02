#include <GraphVisualizer.h>
#include <algorithm>
#include <iterator>

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
    unsigned char textColors[3] = {0,255,0};
    drawCircle(bmpFile, static_cast<int>(vertices[i].x), static_cast<int>(vertices[i].y), 10, colors);
    writeText(bmpFile, static_cast<int>(vertices[i].x), static_cast<int>(vertices[i].y), i, textColors);
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

void GraphVisualizer::writeText(std::ofstream& bmpFile, int x, int y, int id, const unsigned char color[3]) {
  // Calculate number of digits
  std::vector<int> digits = {};
  if(id == 0)
  {
    digits.push_back(0);
  }
  else 
  {
    while (id > 0) 
    {
      digits.push_back(id % 10);
      id /= 10;
    }   
  }

  std::reverse(digits.begin(), digits.end()); 

  int charWidth = 3;
  int charSpacing = 5;
  // Write digits sequentially
  for (int i = 0; i < digits.size(); i++) {
    // Draw the current digit
    drawDigit(bmpFile, x + i * (charWidth + charSpacing), y, digits[i], color);
  }
}

// Function to draw a single digit
void GraphVisualizer::drawDigit(std::ofstream& bmpFile, int x, int y, int digit, const unsigned char color[3]) {
  std::vector<std::vector<std::vector<bool>>> nums = {
    { // 0
      {1, 1, 1},
      {1, 0, 1},
      {1, 0, 1},
      {1, 0, 1},
      {1, 1, 1}
    },
    { // 1
      {1, 1, 1},
      {0, 1, 0},
      {0, 1, 0},
      {1, 1, 0},
      {0, 1, 0}
    },
    { // 2
      {1, 1, 1},
      {1, 0, 0},
      {1, 1, 1},
      {0, 0, 1},
      {1, 1, 1}
    },
    { // 3
      {1, 1, 1},
      {0, 0, 1},
      {1, 1, 1},
      {0, 0, 1},
      {1, 1, 1}
    },
    { // 4
      {0, 0, 1},
      {0, 0, 1},
      {1, 1, 1},
      {1, 0, 1},
      {1, 0, 1}
    },
    { // 5
      {1, 1, 1},
      {0, 0, 1},
      {1, 1, 1},
      {1, 0, 0},
      {1, 1, 1}
    },
    { // 6
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1},
      {1, 0, 0},
      {1, 1, 1}
    },
    { // 7
      {0, 0, 1},
      {0, 0, 1},
      {0, 0, 1},
      {0, 0, 1},
      {1, 1, 1}
    },
    { // 8
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1}
    },
    { // 9
      {1, 1, 1},
      {0, 0, 1},
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1}
    }
  };

  for (int i = 0; i < nums[digit].size(); i++) {
    for (int j = 0; j < nums[digit][i].size(); j++){
      if (nums[digit][4-i][j])
        setPixel(bmpFile, x + j, y + i, color);
    }
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
    bmpFile.write((char *)color, 3);
  }
}
