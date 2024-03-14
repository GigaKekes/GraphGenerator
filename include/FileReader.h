#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "dataStructures.h"

typedef struct BMPConfig
{
  int offset;
  int width;
  int height;
  BMPConfig() {offset = 54; width=2000; height=2000;}
} BMPConfig; 

typedef struct ForceDirectedGraphConfig
{
  int iterations;
  ForceDirectedGraphConfig() {iterations = 1000;}
} ForceDirectedGraphConfig; 

class FileReader 
{
private:
  BMPConfig bmpConfig;
  ForceDirectedGraphConfig fdaConfig;
  int numVertexes;
  int numEdges;
public:
  FileReader();
  std::vector<Edge>GetEdgesFromInputFile(char* path);
  BMPConfig GetBMPConfig();
  int GetNumVertexes();
  int GetNumEdges();
  ForceDirectedGraphConfig GetForceDirectedConfig();

private:
  void ParseConfig();
}; 
