#include"directed.h"


Graph createGraph()
{
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  return g;
}

void addVertex(Graph g, int id, Jval parent)
{
  JRB node, node1, tree;
  node = jrb_find_int(g.vertices, id);
  if(node == NULL)
    {
      jrb_insert_int(g.vertices, id, parent);
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

void addEdge(Graph g, int v1, int v2, int weight)
{
  if(weight <= 0)
    {
      printf("Weight must be greater than 0!!!\n");
      return;
    }
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
      jrb_insert_int((JRB)jval_v(node->val), v2, new_jval_i(weight));
    }
}

/* int getParent(Graph g, int id) */
/* { */
/*   JRB node; */
/*   node = jrb_find_int(g.vertices, id); */
/*   if(node == NULL) */
/*     { */
/*       printf("The vertex does not exist!!!\n"); */
/*       return 0; */
/*     } */
/*   return jval_i(node->val); */
/* } */

int getEdgeValue(Graph g, int v1, int v2)
{
  JRB node1, node2;
  node1 = jrb_find_int(g.edges, v1);
  if(node1 == NULL)
    {
      printf("The vertex %d does not exist!!!\n", v1);
      return -1;
    }
  node2 = jrb_find_int((JRB)jval_v(node1->val), v2);
  if(node2 == NULL)
    {
      printf("The vertex %d does not exist!!!\n", v2);
      return -1;
    }
  return jval_i(node2->val);
  
  
    
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

int countNode(Graph g)
{
  int n = 0;
  JRB node;
  jrb_traverse(node, g.vertices){
    n++;
  };
  return n;
}

void initQueue(Graph g, Dllist q)
{
  JRB node;
  Dllist p;
  jrb_traverse(node, g.edges)
    {
      dll_append(q, new_jval_i(jval_i(node->key)));
      p = dll_last(q);
      printf("%d\t", jval_i(p->val));
    };
}

int extractMin(Dllist q, int *distance)
{
  Dllist node, min;
  node = dll_first(q);
  int distanceMin =distance[jval_i(node->val)];
  dll_traverse(node, q)
    {
      if(distance[jval_i(node->val)] <= distanceMin)
	{
	  distanceMin = distance[jval_i(node->val)];
	  min = node;
	}
    }
  
  int exMin = jval_i(min->val);
  dll_delete_node(min);
  return exMin;
}

int getWeight(Graph g, int u, int v)
{
  JRB node1 = jrb_find_int(g.edges, u);
  JRB node2 = jrb_find_int((JRB)jval_v(node1->val), v);
  if(node2 == NULL)
    {
      return infinitive_value;
    }
  return jval_i(node2->val);
}

int getParent(Graph g, int v)
{
  return jval_i((jrb_find_int(g.vertices, v)->val));
}

void setParent(Graph g, int parent, int v)
{
  JRB node = jrb_find_int(g.vertices, v);
  node->val = new_jval_i(parent);
}

void relax(Graph g, int u, int v, int *distance)
{
  if (distance[v] > (distance[u] + getWeight(g, u, v)))
    {
      distance[v] = distance[u] + getWeight(g, u, v);
      setParent(g, u, v);
    }
}


void getPath(Graph g, int s, int t, int *path, int *length)
{
  int node = t;
  path[(*length)] = t;
  while(getParent(g, node) != s)
    {
      path[++(*length)] = getParent(g, node);
    }
  path[++(*length)] = s;
}



int shortestPath(Graph g, int s, int t, int *path, int *length)
{
  JRB node1, node2;
  node1 = jrb_find_int(g.edges, s);
  if(node1 == NULL)
    {
      printf("The vertex %d doesn't exist!\n", s);
      return -1;
    }
  node2 = jrb_find_int(g.edges, t);
  if(node2 == NULL)
    {
      printf("The vertex %d doesn't exist!\n", t);
      return -1;
    }
  int i, u,v;
  JRB adjU, temp;
  int n = countNode(g);
  int distance[n-1];
  for(i =0; i<n; i++)
    {
      distance[i] = infinitive_value;
    }
 
  distance[s] = 0;
  for (i = 0; i<n ; i++)
    {
      printf("%d : %d\n", i, distance[i]);
    }
  
  Dllist pq, p;
  pq = new_dllist();
  initQueue(g, pq);
  /* dll_traverse(p, pq) */
  /*   { */
  /*     printf("%d\t", jval_i(p->val)); */
  /*   } */
  
  while(!dll_empty(pq))
    {
      u = extractMin(pq, distance);
      adjU = adjVertex(g, u);
      jrb_traverse(temp, adjU)
	{
	  v = jval_i(temp->key);
	  relax(g, u, v, distance);
	};
      
    }
  
  getPath(g, s, t, path, length);
  free_dllist(pq);
  return distance[t];
}


void dropGraph(Graph g)
{
  JRB node;

  jrb_traverse(node, g.edges)
    {
      jrb_free_tree((JRB)jval_v(node->val));
    };
  jrb_free_tree(g.edges);
  jrb_free_tree(g.vertices);
}


int main()
{
  Graph g = createGraph();
  
  addVertex(g, 0, new_jval_i(0));
  addVertex(g, 1, new_jval_i(1));
  addVertex(g, 2, new_jval_i(2));
  addVertex(g, 3, new_jval_i(3));
  addVertex(g, 4, new_jval_i(4));
  addVertex(g, 5, new_jval_i(5));
  addEdge(g, 0, 1, 2);
  addEdge(g, 0, 2, 1);
  addEdge(g, 1, 3, 6);
  addEdge(g, 1, 4, 4);
  addEdge(g, 2, 3, 3);
  addEdge(g, 2, 4, 5);
  addEdge(g, 3, 5, 3);
  addEdge(g, 4, 5, 2);
  printf("get parent of 1: %d\n", getParent(g,1));
  Dllist pq, p;
  pq = new_dllist();
  initQueue(g, pq);
  /* p = pq; */
  /* printf("%d\n", jval_i(p->val)); */
  /* dll_traverse(p, pq) */
  /*   { */
  /*     printf("%d\t", jval_i(p->val)); */
  /*   } */
  
  int shortest, length=0, path[99];
  shortest = shortestPath(g, 0, 5, path, &length);

  if(shortest == infinitive_value)
    {
      printf("No path between 0 and 5\n");
    }
  else {
    printf("Path between 0 and 5:\n");
    for(int i = 0; i<length; i++)
      printf("%d\t",path[i]);
    printf("\nTotal weight: %d", shortest);
  }
  
  printf("\n");
  printf("0 -> 2: %d\n", getEdgeValue(g, 0, 2));
  
  dropGraph(g);
  return 0;
  
}

/* gcc -o shortest shortest.c libfdr.a && ./shortest */
