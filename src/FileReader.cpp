#include <FileReader.h>

FileReader::FileReader()
{
  ParseConfig();
}

std::vector<Edge> FileReader::GetEdgesFromInputFile(char* path)
{
  std::ifstream inputFile(path);

  if (!inputFile.is_open())
  {
    throw std::invalid_argument("Failed to open input file");
  }

  inputFile >> numVertexes >> numEdges;

  std::vector<Edge> edges;
  for (int i = 0; i < numEdges; ++i) 
  {
    Edge edge;
    inputFile >> edge.u >> edge.v;
    edges.push_back(edge);
  }
  inputFile.close();
  return edges;
}

BMPConfig FileReader::GetBMPConfig()
{
 return bmpConfig;
}

ForceDirectedGraphConfig FileReader::GetForceDirectedConfig()
{
  return fdaConfig;
}

int FileReader::GetNumVertexes()
{
  return numVertexes;
}
int FileReader::GetNumEdges()
{
  return numEdges;
}

void FileReader::ParseConfig()
{

  std::ifstream confFile ("../userConfig.conf");
  if (!confFile.is_open())
  {
    throw std::invalid_argument("Failed to open config file");
  }

  std::string line;

  while(getline(confFile, line))
  {
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
    if(line[0] == '#' || line.empty()) continue;
    
    
    auto delimiterPos = line.find("=");
    auto name = line.substr(0, delimiterPos);
    auto value = line.substr(delimiterPos + 1);

    if(name == "fruchtermanReinglodIterations")
    {
      fdaConfig.iterations = std::stoi(value);
      break;
    }
    else if(name == "offset")
    {
      bmpConfig.offset = std::stoi(value);
      break;
    }
    else if(name == "width")
    {
      bmpConfig.width = std::stoi(value);
      break;
    }
    else if(name == "height")
    {
      bmpConfig.height = std::stoi(value);
      break;
    }
  }
}