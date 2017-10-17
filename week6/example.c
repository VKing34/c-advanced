#include<stdio.h>
#include<stdlib.h>
#include"graph.h"
int main()
{
  graph g;
  g = createGraph(10);
  addEdge(g, 1, 3);
  addEdge(g, 2, 3);
  addEdge(g, 4, 6);
  addEdge(g, 2, 7);
  addEdge(g, 9, 2);

  if(adjacent(g, 3, 2) == 1)
    printf("Y\n");
  int result, output[10];
  result = getAdjacentVertices(g, 2, output);
  printf("How many are adjacent vertices connected to 2?\n%d\n", result);
  for(int i =0; i < result; i++)
    {
      printf("%d\t", output[i]);
    }
  printf("\n");
  dropGraph(g);
  
  return 0;

    
}


// -*- compile-command: "gcc -o ex example.c graph.c" -*-
