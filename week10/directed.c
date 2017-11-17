#include"directed.h"


Graph createGraph()
{
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  return g;
}

void addVertex(Graph g, int id, Jval name)
{
  JRB node, node1, tree;
  node = jrb_find_int(g.vertices, id);
  if(node == NULL)
    {
      jrb_insert_int(g.vertices, id, name);
    }
  else {
    printf("The vertex exists!!!\n");
    return;
  }
  node1 = jrb_find_int(g.edges, id);
  if(node1 == NULL)
    {
      tree = make_jrb();
      jrb_insert_int(g.edges, id, new_jval_v(tree));
    }
}

void addEdge(Graph g, int v1, int v2)
{
  JRB node, node2;
  node = jrb_find_int(g.edges, v1);
  if(node == NULL)
    {
      printf("The vertex %d does not exist!!!\n", v1);
      return;
    }
  node2 = jrb_find_int(g.edges, v2);
  if(node2 == NULL)
    {
      printf("The vertex %d does not exist!!!\n", v2);
      return;
    }
  if(jrb_find_int((JRB)jval_v(node->val), v2) == NULL)
    {
      jrb_insert_int((JRB)jval_v(node->val), v2, new_jval_i(1));
    }
}

Jval getVertex(Graph g, int id)
{
  JRB node;
  node = jrb_find_int(g.vertices, id);
  if(node == NULL)
    {
      printf("The vertex does not exist!!!\n");
      node->val.s = NULL;
    }
  return node->val;
}

JRB adjVertex(Graph g, int v)
{
  JRB node;
  node = jrb_find_int(g.edges, v);
  if(node == NULL)
    return NULL;
  return (JRB)jval_v(node->val);
}

int hasEdge(Graph g, int v1, int v2)
{
  JRB adj1 , tnode1, tnode2, adj2;

  adj1 = adjVertex(g, v1);
  jrb_traverse(tnode1, adj1)
    {
      if( v2 == jval_i(tnode1->key))
	{
	  return 1;
	}
      
    }

  adj2 = adjVertex(g, v2);
  jrb_traverse(tnode2, adj2)
    {
      if(v1 == jval_i(tnode2->key))
	{
	  return 1;
	}
    }
  
  return 0;
  
}

int indegree(Graph g, int v, int *output)
{
  JRB node, node1, adj;
  int total =0;
  if(jrb_find_int(g.edges, v) == NULL)
    return 0;
  jrb_traverse(node, g.edges)
    {
      adj = (JRB)jval_v(node->val);
      jrb_traverse(node1, adj)
	{
	  if(jval_i(node1->key) == v)
	    {
	      output[total++] = jval_i(node->key);
	    }
	}
    }
  return total;
}

int outdegree(Graph g, int v, int *output)
{
  JRB node, adj;
  int total =0;
  if(jrb_find_int(g.edges, v) == NULL)
    return total;
  adj = adjVertex(g, v);
  jrb_traverse(node, adj)
    {
      output[total++] = jval_i(node->key);
    }
  return total;
}

int isCyclicUtil(Graph g, int node, int *visited, int *stack)
{
  int u;
  JRB temp, adj;
  visited[node] = 1;
  stack[node] = 1;
  adj = adjVertex(g, node);
  jrb_traverse(temp, adj)
    {
      u = jval_i(temp->key);
      if(visited[u] == 0)
	{
	  if(isCyclicUtil(g, u, visited, stack) == 1)
	    {
	      return 1;
	    }
	}
      else if(stack[u] == 1)
	{
	  return 1;
	}
    }
  stack[node] = 0;
  return 0;
  
}


int DAG(Graph g)
{
  JRB temp;
  int stack[max] = {0};
  int visited[max] = {0};
  int node;

  jrb_traverse(temp, g.edges)
    {
      node = jval_i(temp->key);
      if(visited[node] == 0)
	{
	  if (isCyclicUtil(g, node, visited, stack) == 1)
	    return 1;
	}
    }
  return 0;   // return 0 if DAG, return 1 if not DAG
}


void dropGraph(Graph g)
{
  JRB node;

  jrb_traverse(node, g.edges)
    {
      jrb_free_tree((JRB)jval_v(node->val));
    }
  jrb_free_tree(g.edges);
  jrb_free_tree(g.vertices);
}

int main()
{
  Graph g = createGraph();
  /* addVertex(g, 0, new_jval_s("V0")); */
  /* addVertex(g, 1, new_jval_s("V1")); */
  /* addVertex(g, 2, new_jval_s("V2")); */
  /* addVertex(g, 3, new_jval_s("V3")); */
  /* /\* addVertex(g, 4, new_jval_s("V4")); *\/ */
  /* /\* addVertex(g, 5, new_jval_s("V5")); *\/ */
  /* addEdge(g, 0, 1); */
  /* addEdge(g, 1, 2); */
  /* addEdge(g, 2, 3); */
  /* addEdge(g, 1, 3); */
  /* /\* addEdge(g, 3, 4); *\/ */
  addVertex(g, 0, new_jval_s("CS102"));
  addVertex(g, 1, new_jval_s("CS140"));
  addVertex(g, 2, new_jval_s("CS160"));
  addVertex(g, 3, new_jval_s("CS302"));
  addVertex(g, 4, new_jval_s("CS311"));
  addVertex(g, 5, new_jval_s("MATH300"));
  addEdge(g, 0, 1);
  addEdge(g, 0, 2);
  addEdge(g, 1, 3);
  addEdge(g, 5, 4);
  addEdge(g, 3, 4);



  printf("%s\n", jval_s(getVertex(g, 1)));
  int arr[max];
  int total = indegree(g, 4, arr);
  for(int i =0; i < total; i++)
    {
      printf("%d\t", arr[i]);
    }
  printf("\n");
 

  if(DAG(g) == 1)
    printf("not DAG!\n");
  else {
    printf("DAG!\n" );
  }
  dropGraph(g);
  return 0;
}


/* gcc -o dir directed.c libfdr.a && ./dir */
