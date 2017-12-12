#include"dirgraph.h"


int main()
{
  Graph g = createGraph();

  addVertex(g, 1, "a");
  addVertex(g, 2, "b");
  addVertex(g, 3, "c");
  addVertex(g, 4, "d");
  addVertex(g, 5, "e");
  addVertex(g, 6, "f");

  addEdge(g, 1, 2, 4);
  addEdge(g, 1, 3, 2);
  addEdge(g, 3, 2, 1);
  addEdge(g, 2, 4, 5);
  addEdge(g, 3, 4, 5);
  addEdge(g, 3, 5, 8);
  addEdge(g, 4, 5, 2);
  addEdge(g, 4, 6, 6);
  addEdge(g, 5, 6, 3);

  /* printf("Distance from 1 to 1: %d\n", getWeight(g, 1, 1)); */

  int s = 1, t = 6, length, path[100], i;
  int weight;
  weight = shortestPath(g, s, t, path, &length);
  if( weight == infinitive_value)
    {
      printf("No path from %d to %d\n",s, t );
    }
  else {
    printf("Path from %d to %d: ", s, t);
    for(i =  0; i< length; i++)
      {
  	printf("%d\t", path[i]);
      }
    printf("\n");
    printf("Total weight: %d \n", weight);
  } 

  /* addEdge(g, 1, 2, 1); */
  /* addEdge(g, 2, 3, 1); */
  /* addEdge(g, 1, 4, 1); */
  /* addEdge(g, 4, 3, 1); */
  /* addEdge(g, 4, 5, 1); */
  /* addEdge(g, 5, 3, 1); */
  
  BFS(g, 1 , -1, printVertex);
  printf("\n");

  DFS(g, 1, -1, printVertex);
  printf("\n");
  dropGraph(g);
  return 0;
}


/* gcc -o shortest shortest.c dirgraph.c libfdr.a && ./shortest */
