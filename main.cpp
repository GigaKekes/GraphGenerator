#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct Vertex {
    double x, y;
  Vertex() {}
  Vertex(double x, double y) : x(x), y(y) {}
};

struct Edge {
    int u, v;
};

class GraphVisualizer {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    int width, height;

public:
    GraphVisualizer(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges, int width, int height)
        : vertices(vertices), edges(edges), width(width), height(height) {}

    void visualize(const std::string& filename) {
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

private:
    void writeBMPHeader(std::ofstream& bmpFile) {
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

    void drawEdges(std::ofstream& bmpFile) {
        for (const Edge& edge : edges) {
            unsigned char colors[3] = {255,0,0};
            drawLine(bmpFile, vertices[edge.u].x, vertices[edge.u].y, vertices[edge.v].x, vertices[edge.v].y, colors);
        }
    }

    void drawVertices(std::ofstream& bmpFile) {
        for (const Vertex& vertex : vertices) {
            unsigned char colors[3] = {255,0,0};
            drawCircle(bmpFile, static_cast<int>(vertex.x), static_cast<int>(vertex.y), 10, colors);
        }
    }

    void drawLine(std::ofstream& bmpFile, int x1, int y1, int x2, int y2, const unsigned char color[3]) {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);

        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;

        int err = dx - dy;

        while (true) {
            setPixel(bmpFile, x1, y1, color);

            if (x1 == x2 && y1 == y2) {
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

    void drawCircle(std::ofstream& bmpFile, int cx, int cy, int radius, const unsigned char color[3]) {
        for (int x = cx - radius; x <= cx + radius; ++x) {
            for (int y = cy - radius; y <= cy + radius; ++y) {
                if (pow(x - cx, 2) + pow(y - cy, 2) <= pow(radius, 2)) {
                    setPixel(bmpFile, x, y, color);
                }
            }
        }
    }

    void setPixel(std::ofstream& bmpFile, int x, int y, const unsigned char color[3]) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            bmpFile.seekp(54 + 3 * (width * (height - y - 1) + x));
            bmpFile.write((char *)&color, 3);
        }
    }
};
class ForceDirectedGraph {
private:
    const double kCooling = 0.9;
    int width;
    int height;
    int size;
    vector<Vertex> vertices;
    vector<Edge> edges;
    double k; // Constant for force calculation
    double temperature; // Temperature for the simulation
public:
    ForceDirectedGraph(vector<Edge> edges, int numVertices, int width, int height) : k(sqrt((double)(width * height) / numVertices)), temperature(1), 
                                                                                     width(width), height(height), size(fmin(width, height))
    {
        // Initialize vertices with random positions
        srand(time(NULL));
        for (int i = 0; i < numVertices; ++i) {
            Vertex vertex;
            vertex.x = static_cast<double>(rand() % size/2);
            vertex.y = static_cast<double>(rand() % size/2);
            vertices.push_back(vertex);
            cout << "vert " << i+1 << ": x: " << vertex.x << " y: " << vertex.y << endl;
        }

        // Initialize edges
        this->edges = edges;
    }

    void fruchtermanReingold(int iterations) {
        for (int iter = 0; iter < iterations; ++iter) {
            // Compute attractive and repulsive forces
            cout << "\nCalc " << iter << " attractive forces" << endl;
            
            vector<Vertex> attractiveForces = computeAttractiveForces();
            
            cout << "\nCalc " << iter << " repulcive forces" << endl;
            
            vector<Vertex> repulsiveForces = computeRepulsiveForces();

            cout << "\nUpdating Positions" << endl;
            // Update vertex positions based on forces
            updatePositions(attractiveForces, repulsiveForces);

            cout <<'\n'<<iter << " succsesful" << endl;
            // Decrease the temperature to simulate cooling
            temperature *= kCooling;

            //GraphVisualizer visualizer(vertices, edges, 500, 500);
            //visualizer.visualize("graph_visualization" + to_string(iter) + ".bmp");


        }
    }

    void printLayout() {
        for (int i = 0; i < vertices.size(); ++i) {
            cout << "Vertex " << i+1 << ": x=" << vertices[i].x << ", y=" << vertices[i].y << endl;
        }
    }

    vector<Vertex> getVerteces()
    {
      return vertices;
    }

private:
    vector<Vertex> computeAttractiveForces() {
        vector<Vertex> forces;
        for (size_t i = 0; i < vertices.size(); i++) {
          forces.push_back(Vertex(0.0, 0.0));
        }

        for (auto edge : edges) {
            double dx = vertices[edge.v].x - vertices[edge.u].x;
            double dy = vertices[edge.v].y - vertices[edge.u].y;
            double distance = sqrt(dx * dx + dy * dy);
            double force = distance * distance / k;
            

            
            forces[edge.u].x += force * dx / distance;
            forces[edge.u].y += force * dy / distance;
            forces[edge.v].x -= force * dx / distance;
            forces[edge.v].y -= force * dy / distance;

        }

        for (size_t i = 0; i < vertices.size(); i++) {
          if(isnan(forces[i].x)) forces[i].x = 0;
          if(isnan(forces[i].y)) forces[i].y = 0;
        }

        for (size_t i = 0; i < vertices.size(); i++) {
          cout << forces[i].x << " " << forces[i].y << endl;
        }
        return forces;  
    }

    vector<Vertex> computeRepulsiveForces() {

        vector<Vertex> repulsiveForces;
        for (size_t i = 0; i < vertices.size(); i++) {
          repulsiveForces.push_back(Vertex(0.0, 0.0));
        }

        for (int i = 0; i < vertices.size(); ++i) {
            for (int j = 0; j < vertices.size(); ++j) {
                if (i != j) {
                    double dx = vertices[j].x - vertices[i].x;
                    double dy = vertices[j].y - vertices[i].y;
                    double distance = sqrt(dx * dx + dy * dy);
                    double force = k * k / distance;

                    repulsiveForces[i].x -= force * dx / distance;
                    repulsiveForces[i].y -= force * dy / distance;
                }
            }
        }

       for (size_t i = 0; i < vertices.size(); i++) {
          if(isnan(repulsiveForces[i].x)) repulsiveForces[i].x = 0;
          if(isnan(repulsiveForces[i].y)) repulsiveForces[i].y = 0;
        } 
        for (size_t i = 0; i < vertices.size(); i++) {
          cout << repulsiveForces[i].x << " " << repulsiveForces[i].y << endl;
        }
 

        return repulsiveForces;
    }

    void updatePositions(const vector<Vertex>& attractiveForces, const vector<Vertex>& repulsiveForces) {
      int maxDistortion = 0;
      int maxNegDiviation = 0;

      for (int i = 0; i < vertices.size(); ++i) {
        double displacement = sqrt(attractiveForces[i].x * attractiveForces[i].x + attractiveForces[i].y * attractiveForces[i].y)
                             / sqrt(repulsiveForces[i].x * repulsiveForces[i].x + repulsiveForces[i].y * repulsiveForces[i].y);

        displacement = min(displacement, temperature);

        // Update vertex positions with bounds checking
        vertices[i].x = vertices[i].x + (attractiveForces[i].x + repulsiveForces[i].x) * displacement;
        vertices[i].y = vertices[i].y + (attractiveForces[i].y + repulsiveForces[i].y) * displacement;
        cout << vertices[i].x << ' ' << vertices[i].y << endl;
        
        if(vertices[i].x > size || vertices[i].y > size) maxDistortion = fmax(maxDistortion, fmax(vertices[i].x, vertices[i].y));
        if(vertices[i].x < 0 || vertices[i].y < 0) maxNegDiviation = abs(fmin(maxNegDiviation, fmin(vertices[i].x, vertices[i].y)));
        }
        if(maxNegDiviation != 0)
        {
         for(int i = 0; i < vertices.size(); ++i)
          {
            vertices[i].x += maxNegDiviation;
            vertices[i].y += maxNegDiviation;
          }
          maxDistortion += maxNegDiviation;
        }
        if(maxDistortion != 0)
        {
          for(int i = 0; i < vertices.size(); ++i)
          {
            vertices[i].x = vertices[i].x  * size / (maxDistortion*1.05);
            vertices[i].y = vertices[i].y  * size / (maxDistortion*1.05);

          }
        }
    }
};

int main() {
    ifstream inputFile("/home/dmitry/Programs/Projects/Assignment/GraphGenerator/test2.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    int numVertices, numEdges;
    inputFile >> numVertices >> numEdges;

    vector<Edge> edges;
    for (int i = 0; i < numEdges; ++i) {
        Edge edge;
        inputFile >> edge.u >> edge.v;
        edge.u--;
        edge.v--;
    
        edges.push_back(edge);
    }

    inputFile.close();
    
    double width = 5000.0;
    double height = 5000.0;
    int iterations = 100;
    

    ForceDirectedGraph graph(edges, numVertices, width, height);
    graph.fruchtermanReingold(iterations);
    graph.printLayout();
    

    GraphVisualizer visualizer(graph.getVerteces(), edges, width, height);

    // Visualize the graph and save it to a BMP file
    visualizer.visualize("graph_visualization.bmp");


    return 0;
}
