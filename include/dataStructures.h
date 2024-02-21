#ifndef GRGEN_INCL_DATASTRUCT 
#define GRGEN_INCL_DATASTRUCT

typedef struct Vertex
{
  double x, y;
  Vertex(double x, double y) : x(x), y(y){}
  Vertex() {}
} Vertex;

typedef struct Edge
{
  int u, v;
  Edge(int u, int v) : u(u), v(v){}
  Edge() {} 
} Edge;

#endif // GRGEN_INCL_GRAPH 

