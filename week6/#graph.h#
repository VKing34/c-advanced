#include<stdio.h>
#include<stdlib.h>

typedef struct
{
  int *matrix;
  int sizemax;
} graph;

graph createGraph(int sizemax);
void addEdge(graph g, int v1, int v2);
int adjacent(graph g, int v1, int v2);
int getAdjacentVertices(graph g, int vertex, int *output);
void dropGraph(graph g);
