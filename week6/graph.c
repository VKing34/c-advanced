#include<stdio.h>
#include<stdlib.h>
#include"graph.h"

graph createGraph(int sizemax)
{
  graph g;
  g.sizemax = sizemax;
  g.matrix = (int*)malloc(sizeof(int) *sizemax*sizemax);
 
  if(!g.matrix)
    printf("Memory is over!!!\n");
  return g;
}

void addEdge(graph g, int v1, int v2)
{
  int x = v1*g.sizemax + v2;
  int y = v2*g.sizemax + v1;
  g.matrix[x] = 1;
  g.matrix[y] = 1;
}

int adjacent(graph g, int v1, int v2)
{
  return g.matrix[v1*g.sizemax + v2] || g.matrix[v2 * g.sizemax + v1];
}

int getAdjacentVertices(graph g, int vertex, int *output)
{
  int i = 0, count = 0;
 
  for(i = 0; i < g.sizemax; i++)
    {
      if(adjacent(g, vertex, i) == 1)
	{
	  output[count++] = i;
	  
	}
    }
  return count;
}

void dropGraph(graph g)
{
  free(g.matrix);
  g.sizemax = 0;
}
