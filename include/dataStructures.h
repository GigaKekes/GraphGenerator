#ifndef GRGEN_INCL_DATASTRUCT 
#define GRGEN_INCL_DATASTRUCT

typedef struct Vertex
{
  double x, y;
  Vertex(double x, double y) : x(x), y(y){}
  Vertex() {}
} vertex;

typedef struct Edge
{
  int u, v;
  Edge(int u, int v) : u(u), v(v){}
  Edge() {} 
} edge;

#endif // GRGEN_INCL_GRAPH 

