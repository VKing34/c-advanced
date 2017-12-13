#include"dirgraph.h"

int main()
{
  int n=0, output[20]; 
  JRB v;
  attribute a;

  Graph g = createGraph();
  addVertex(g, 0, "CS102");
  addVertex(g, 1, "CS140");
  addVertex(g, 2, "CS160");
  addVertex(g, 3, "CS302");
  addVertex(g, 4, "CS311");
  addVertex(g, 5, "MATH300");
  addEdge(g, 0, 1,1);
  addEdge(g, 0, 2,1);
  addEdge(g, 1, 3,1);
  addEdge(g, 5, 4,1);
  addEdge(g, 3, 4,1);

  // addEdge(g, 0, 1,1);
  // addEdge(g, 0, 3,1);
  // addEdge(g, 1, 2, 1);
  // addEdge(g, 1, 3, 1);
  // addEdge(g, 3, 2, 1);
  // addEdge(g, 3, 4, 1);
  // addEdge(g, 3, 5, 1);
  // addEdge(g, 4, 5, 1);


  if(DAG(g) == 1)
    {
      printf("Can not make topological sort!!!\n");
      return 1;
    }
   else
   {
   	printf("OK!\n");
   }

  // printf("%s\n", getVerName(g, 1));

  // jrb_traverse(v, g.vertices)
  // {
  //   a = verAttribute(g, jval_i(v->key));
  //   printf("%s\n", a->name);
  // }

  tSort(g, output, &n);


  printf("The topological order:\n");
  for(int i = 0; i< n ; i++)
    {
      printf("%s\n", getVerName(g, output[i]));
    }
    

  dropGraph(g);
  return 0;
}

// gcc -g -o tsort tsort.c dirgraph.c libfdr.a && ./tsort