#include"dirgraph.h"
#define enqueue(queue, id) dll_append(queue, new_jval_i(id))
#define push(queue, id) dll_prepend(stack, new_jval_i(id))
#define pop(stack) dequeue(stack)

Graph createGraph()
{
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  return g;
}

Jval setAttribute(char *name)
{
  attribute a = (attribute)malloc(sizeof(attribute));
  if(name)
    {
      char *n = (char*)malloc(strlen(name));
      strcpy(n, name);
      a->name = n;
    }
  else
    a->name = NULL;
  
  a->distance = infinitive_value;

  Jval val = new_jval_v(a);

  return val;
  
}

attribute getAttribute(JRB node)
{
  return ((attribute) jval_v(node->val));
}


void addVertex(Graph g, int v, char *name)
{
  JRB node, node1, tree;
  node = jrb_find_int(g.vertices, v);
  if(node == NULL)
    {
      jrb_insert_int(g.vertices, v, setAttribute(name));
    }
  else
  {
   if(!name)
	  {
		  return;
	  }
	 attribute a = getAttribute(node);
	 if(strcmp(a->name, name))
	 {
	   free(a->name);
	   node->val = setAttribute(name);
	 }
 
  }
//  node1 = jrb_find_int(g.edges, v);
//  if(!node1)
//    {
//      tree = make_jrb();
//      jrb_insert_int(g.edges, v, new_jval_v(tree));
 //   }
}

void addEdge(Graph g, int v1, int v2, int weight)
{
  if(weight < 0)
    {
      printf("Weight must be greater than 0!!!\n");
      return;
    }
  JRB node;
  JRB adjVertices = make_jrb();;
  node = jrb_find_int(g.edges, v1);
  if(node == NULL)
    {
      jrb_insert_int(adjVertices, v2, new_jval_i(weight));
      jrb_insert_int(g.edges, v1, new_jval_v(adjVertices));
      
    }
  else {
    adjVertices = (JRB) jval_v(node->val);
    node = jrb_find_int(adjVertices, v2);
    if(node == NULL)
      {
	     jrb_insert_int(adjVertices, v2, new_jval_i(weight));
      }
  }
}

void insertEdge(Graph g, int v1, int v2, int weight)
{
  addEdge(g, v1, v2, weight);
  addEdge(g, v2, v1, weight);
}

int getWeight(Graph g, int v1, int v2)
{
  if (v1 == v2)
    return 0;
  JRB node1 = jrb_find_int(g.edges, v1);
  JRB node2 = jrb_find_int((JRB)jval_v(node1->val), v2);
  if(node2)
    return jval_i(node2->val);
  else {
    return infinitive_value;
  }
}

void weight_increase(Graph g, int v1, int v2)
{

  JRB node1 = jrb_find_int(g.edges, v1);
  JRB node2 = jrb_find_int((JRB)jval_v(node1->val), v2);
  int w = jval_i(node2->val);
  node2->val = new_jval_i(w+ 1);

  node1 = jrb_find_int(g.edges, v2);
  node2 = jrb_find_int((JRB)jval_v(node1->val), v1);
  node2->val = new_jval_i(w + 1);
}



JRB getVertex(Graph g, int v)
{
  JRB node = jrb_find_int(g.vertices, v);
  if (node)
    return node;
  else {
    return NULL;
  }
}

attribute verAttribute(Graph g, int v)
{
JRB node = getVertex(g, v);
return ((attribute) jval_v(node->val));
}

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
  if(node)
    return (JRB) jval_v(node->val);
  else {
    return NULL;
  }
}


// Return 1 if hasEdge, return 0 if not
int hasEdge(Graph g, int v1, int v2)
{
  JRB adj1 , tnode1;
  // JRB tnode2, adj2;

  adj1 = adjVertex(g, v1);
  if(adj1)
  {
    jrb_traverse(tnode1, adj1)
    {
      if( v2 == jval_i(tnode1->key))
      {
        return 1;
      }
    }
  }

  return 0;

  // else
  // {
  //   return 0;
  // }

  // adj2 = adjVertex(g, v2);
  // if(adj2 != NULL)
  // {
  //   jrb_traverse(tnode2, adj1)
  //   {
  //     if(v1 == jval_i(tnode2->key))
	 //   {
	 //     return 1;
	 //   }
  //   }
  // }
  // else{
  //   return 0;
  // }
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


char *getVerName(Graph g, int v)
{
  attribute a = verAttribute(g, v);
  return a->name;
}



void initSingleSource(Graph g, int s)
{
  JRB node;
  attribute a;
  jrb_traverse(node, g.vertices)
    {
      a = getAttribute(node);
      a->distance = infinitive_value;
      a->pr = NULL;
    }
  node = getVertex(g, s);
  if(node)
    {
      a = getAttribute(node);
      a->distance = 0;
    }
  else {
    printf("ERROR: Vertex %d does not exist\n", s);
    return;
  }
}

void relax(Graph g, int u, int v)
{
  JRB U = getVertex(g, u);
  JRB V = getVertex(g, v);

  attribute u_attrb = getAttribute(U);
  attribute v_attrb = getAttribute(V);

  int w = getWeight(g, u, v);

  if(v_attrb->distance > u_attrb->distance + w)
    {
      v_attrb->distance = u_attrb->distance + w;
      v_attrb->pr = U;
    }
}

JRB getAdjList(Graph g, int v)
{
JRB node = jrb_find_int(g.edges, v);
if(node)
{
return (JRB) jval_v(node->val);
}
else
{
return NULL;
}
}

int getAdjVertices(Graph g, int v, int *output)
{
  JRB node;
  int i =0;
  JRB adj = getAdjList(g, v);
  
  if(!adj)
    {
      return -1;
    }
  
  jrb_traverse(node, adj){
    output[i] = jval_i(node->key);
    i++;
  }
  
  return i;
}

int extractMin(Graph g, Dllist q)
{
  int min = infinitive_value;
  Dllist min_node;
//  JRB v;
  int id;
  Dllist node;
  attribute a;

  dll_traverse(node, q){
//    v = getVertex(g, jval_i(node->val));
//    a = getAttribute(v);
	a = verAttribute(g, jval_i(node->val));
    if(min > a->distance)
      {
	min = a->distance;
	min_node = node;
      }
  }
  
  id = jval_i(min_node->val);
  dll_delete_node(min_node);

  return id;
}

int shortestPath(Graph g, int s, int t, int *path, int *length)
{
  int pre, u, n, j, i=0;
  int weight = 0;
  int adjVertices[100];
  JRB temp;
  
  Dllist q = new_dllist();
  initSingleSource(g, s);
  
  jrb_traverse(temp, g.vertices)
    {
      dll_append(q, temp->key);
    }

  pre = s;
  
  while(!dll_empty(q))
  {
      u = extractMin(g, q);
      
      if(u != pre)
      {
        weight += getWeight(g, pre, u);
      }

      pre = u;
      path[i++] = u;
      if( u == t )
      {
        *length = i;
        return weight;
      }
      n = getAdjVertices(g, u, adjVertices);
      for(j = 0; j < n; j++)
      {
        relax(g, u, adjVertices[j]);
      }
  }

  return weight;
}

int dequeue(Dllist queue)
{
  Dllist first = dll_first(queue);
  int i = jval_i(first->val);
  dll_delete_node(first);
  return i;
}

int printVertex(Graph g, int v)
{
  attribute a;
  //JRB temp;

  //temp = jrb_find_int(g.vertices, v);
  //a = getAttribute(temp);

	a = verAttribute(g, v);

  printf("%d : %s\n", v, a->name);

  return 0;
  
}

void BFS(Graph g, int start, int stop, int (*func)(Graph, int))
{
  Dllist q;
  JRB v;
  attribute a;
  int ver, n, i;
  int adj[99];
  
  // mark all as unvisited
  jrb_traverse(v, g.vertices)
    {
      a = getAttribute(v);
      a->visited = 0;
    }

  func(g, start);

//  v = jrb_find_int(g.vertices, start);
//  a = getAttribute(v);
	a = verAttribute(g, start);
  a->visited = 1;

  // init a queue
  q = new_dllist();
  enqueue(q, start);

  while(!dll_empty(q))
  {
    ver = dequeue(q);

    if(ver == stop)
    {
      return;
    }
      
    n = getAdjVertices(g, ver, adj);
    for(i = 0; i < n; i++)
    {
      //	  v = jrb_find_int(g.vertices, adj[i]);
      //	  a = getAttribute(v);
      a = verAttribute(g, adj[i]);
      if(a->visited == 0)
	    {
	      a->visited = 1;
	      enqueue(q, adj[i]);
	      func(g, adj[i]);
	    }
    }
  }
  
  free_dllist(q);
}

void DFS(Graph g, int start, int stop, int (*func)(Graph, int))
{
  Dllist stack = new_dllist();
  JRB node;
  attribute a;
  int ver, n, i;
  int adj[99];

  jrb_traverse(node, g.vertices)
    {
      a = getAttribute(node);
      a->visited = 0;
    }

  push(stack, start);

  while(!dll_empty(stack))
  {
      ver = pop(stack);

      //    node = jrb_find_int(g.vertices, ver);
      //    a = getAttribute(node);

	   a = verAttribute(g, ver);	

      if(a->visited == 0)
      {
	       a->visited = 1;
	       func(g, ver);
      }

      if(ver == stop)
      {
	       return;
      }

      n = getAdjVertices(g, ver, adj);
      for(i = 0; i< n ; i++)
      {
          //	node = jrb_find_int(g.vertices, adj[i]);
          //	a = getAttribute(node);
	       a = verAttribute(g, adj[i]);
	       if(a->visited == 0)
	       {
	         push(stack, adj[i]);
	       }
      }
  }

  free_dllist(stack);
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

int isCyclicUtil(Graph g, int vertex, attribute a)
{
  int u;
  JRB node, adj;
  attribute a2;

  a->visited = 1;
  a->distance = 1;

  adj = adjVertex(g, vertex);
  if(adj)
  {
    jrb_traverse(node, adj)
    {
      u = jval_i(node->key);
      a2 = verAttribute(g, u);
      if(a2->visited == 0)
      {
        if(isCyclicUtil(g, u, a2) == 1)
          return 1;
      }
      else if(a2->distance == 1)
      {
        return 1;
      }
    }
  }

  a->distance = 0;
  return 0;
}

int DAG(Graph g)
{
  JRB v;
  attribute a;
  int vertex;
  jrb_traverse(v, g.vertices)
  {
    a = getAttribute(v);
    a->visited = 0;
    a->distance = 0;
  }

  jrb_traverse(v, g.vertices)
  {
    a = getAttribute(v);
    if(a->visited == 0)
    {
      if(isCyclicUtil(g, jval_i(v->key), a) == 1)
        return 1;
    }
  }

  return 0;  // return 0 if DAG, retun 1 if not
}

void topoSort(Graph g, int vertex, attribute a, Dllist q)
{
  JRB node, adj;
  int v;
  attribute a2;
  adj = adjVertex(g, vertex);

  a->visited = 1; // Mark the current node as visited

  if(adj)
  { 
    jrb_traverse(node, adj)
    {
      v = jval_i(node->key);
      a2 = verAttribute(g, v);
      // printf("%d : %d : %d : %d\n", vertex, a->visited, v, a2->visited);
      if(a2->visited == 0)
      {
        topoSort(g, v, a2, q);
      }
    }
  }

  dll_prepend(q, new_jval_i(vertex));
}


void tSort(Graph g, int *output, int *total)
{
  Dllist q, node;
  JRB v;
  attribute a;

  q = new_dllist();

  // Mark all as unvisited
  jrb_traverse(v, g.vertices)
  {
    a = getAttribute(v);
    a->visited = 0;
  }

  jrb_traverse(v, g.vertices)
  {
    a = getAttribute(v);
    if(a->visited == 0)
    {
      topoSort(g, jval_i(v->key), a, q);
    }
  }

  while(!dll_empty(q))
  {
    node = dll_first(q);
    output[(*total)++] = jval_i(node->val);
    dll_delete_node(node);
  }
  free_dllist(q);
}

