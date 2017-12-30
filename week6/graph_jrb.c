#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jval.h"
#include"jrb.h"
#include"dllist.h"
#define max 99

typedef JRB graph;


void menu()
{
  printf("---------------------------------------------------------\n");
  printf("\t\t JRB - Graph\n");
  printf("---------------------------------------------------------\n");
  printf(" 1. Add Edge\n 2. Check 2 adjacent vertices\n 3. Get all adjacent vertices of one vertices\n 4. BFS\n 5. DFS\n 6. Drop the graph\n 0. Quit\nChoose one option:  ");
}

/* int addVer(graph root, jval vertice) */
/* { */
/*   JRB node, value; */
/*   node = jrb_find_int(root, vertice); */
/*   if(node == NULL) */
/*     { */
/*       value = make_jrb(); */
/*       jrb_insert_int(root, vertice, new_jval_v(value)); */
/*       return 0; */
/*     } */
/*   return 1; */
/* } */

void addEdge(graph root)
{
  Jval v1, v2;
  printf("Enter vertice 1: "); scanf("%d", &v1.i);
  while(getchar()!='\n');
  printf("Enter vertice 2: "); scanf("%d", &v2.i);
  while(getchar()!='\n');
  JRB node1, node2;
  node1 = jrb_find_int(root, v1.i);
  node2 = jrb_find_int(root, v2.i);
  
  if(node1 == NULL && node2 == NULL)
    {
      JRB tree = make_jrb();
      jrb_insert_int(root, v1.i, new_jval_v(tree));
      jrb_insert_int(tree, v2.i, new_jval_i(1));
      
      JRB tree1 = make_jrb();
      jrb_insert_int(root, v2.i, new_jval_v(tree1));
      jrb_insert_int(tree1, v1.i, new_jval_i(1));
      
    }
  else if(node1 != NULL && node2 == NULL)
    {
       JRB tree = jval_v(node1->val);
       jrb_insert_int(tree, v2.i, new_jval_v(1));

       JRB tree1 = make_jrb();
       jrb_insert_int(root, v2.i, new_jval_v(tree1));
       jrb_insert_int(tree1, v1.i, new_jval_i(1));
    }
  else if(node1 == NULL && node2 != NULL)
    {
      JRB tree = make_jrb();
      jrb_insert_int(root, v1.i, new_jval_v(tree));
      jrb_insert_int(tree, v2.i, new_jval_i(1));

      JRB tree1 = jval_v(node2->val);
      jrb_insert_int(tree1, v1.i, new_jval_v(1));
      
    }
  else {
    JRB tree = jval_v(node1->val);
    jrb_insert_int(tree, v2.i, new_jval_v(1));

    JRB tree1 = jval_v(node2->val);
    jrb_insert_int(tree1, v1.i, new_jval_v(1));
     
  }
  printf("Add successful !!!\n");
}

int checkAdjacent(graph root,int *k)
{
  if( *k == 1)
    {
      char answer;
     
      printf("The graph was dropped!!!\nDo you want to continue?(y/Y or n/N)\n"); scanf("%c", &answer);
      while(getchar()!='\n');
      if(answer == 'y' || answer == 'Y')
	{
	  root = make_jrb();
	  printf("Because the graph has just created so there no connections!!!\n");
	  *k = 2;
	}
      return 0;
    }
  Jval v1, v2;
  printf("Enter vertice 1: "); scanf("%d", &v1.i);
  while(getchar()!='\n');
  printf("Enter vertice 2: "); scanf("%d", &v2.i);
  JRB node;
  node = jrb_find_int(root, v1.i);
  if(node == NULL)
    {
      return 0;
    }
  JRB tree = jval_v(node->val);
  if(jrb_find_int(tree, v2.i) == NULL)
    return 0;
  return 1;  
}

void getAdjacent(graph root)
{
  Jval vertice;
  printf("Enter vertice: "); scanf("%d", &vertice.i);
  JRB node;
  node = jrb_find_int(root, vertice.i);

  if(node == NULL)
    {
      printf("There is no %d\n", vertice.i);
      return;
    }
  JRB tree = jval_v(node->val);
  JRB temp;
  int count = 0;
  int output[max];
  jrb_traverse(temp, tree)
    {
      output[count++] = jval_i(temp->key);
    };
  if(count == 0)
    {
      printf("%d does have any connection!!!\n", vertice.i);
      
    }
  else {
    printf("%d connnected with: \n", vertice.i);
    for(int i = 0; i< count ; i++)
      {
	printf("%d\t", output[i]);
      }
  }
  printf("\n\n");
}

void printVertice(int v)
{
  printf("%d \t", v);
  
}

JRB findVertice(JRB g, Jval v)
{
  JRB node;
  node = jrb_find_int(g, v.i);
  if(node == NULL)
    return NULL;
  return (JRB)jval_v(node->val);
  
}

void BFS(JRB g, int start, int stop, void (*func)(int ) )
{
  Dllist q, node;
  int u ,v ;
  JRB adj, temp;
  // set all unvisited
  int visited[max] = {0};
  
  // initialize an empty queue
  q = new_dllist();

  // Enqueue(q, start)
  dll_append(q, new_jval_i(start));

  // while q is not empty 
  while(!dll_empty(q))
    {
      // u = Dequeue(q)
      node = dll_first(q);
      u = jval_i(node->val);
      dll_delete_node(node);
      
      
      // print the vertice
      if(visited[u] == 0)
	func(u);
      visited[u] = 1;
      
   
      if(u == stop)
	{
	  return;
	}
      adj = findVertice(g, new_jval_i(u));
      
      jrb_traverse(temp, adj)
	{
	  v = jval_i(temp->key);
	  if(visited[v] == 0)
	    {
	      
	      dll_append(q, new_jval_i(v));
	    }
	};
	
    }
  free_dllist(q);
}

void DFS(JRB g, int start, int stop, void (*func)(int ))
{
  Dllist stack, node;
  int u, v;
  JRB adj, temp;

  // set all unvisited
  int visited[max] = {0};

  // initialize an empty stack
  stack = new_dllist();

  dll_prepend(stack, new_jval_i(start));
  while(!dll_empty(stack))
    {
      node = dll_first(stack);
      u = jval_i(node->val);
      dll_delete_node(node);

      if(visited[u] == 0)
	     func(u);
      
      visited[u] = 1;

      if(u == stop)
	{
	  return;
	}

      adj = findVertice(g, new_jval_i(u));
     
      jrb_traverse(temp, adj)
	{
	  v = jval_i(temp->key);
	  if(visited[v] == 0)
	    {
	      dll_prepend(stack, new_jval_i(v));
	    }
	};
	
    }
  free_dllist(stack);
}

void freeGraph(JRB root)
{
  JRB node;
  jrb_traverse(node, root)
    {
      jrb_free_tree(jval_v(node->val));
    }
}





int main()
{
  int choose=99;
  graph groot;
  int check=0;
  groot = make_jrb();
  while(choose != 0)
    {
      menu();
      scanf("%d", &choose);
      while(getchar()!='\n');
      switch(choose)
	{
	case 0:
	  break;
	case 1:
	  addEdge(groot);
	  break;
	case 2:
	 
	  if(checkAdjacent(groot, &check) == 0)
	    {
	   
	      if(check == 0)
		printf("Not adjacent!!!\n");
	    }
	  else{
	    printf("Adjacent !\n");
	  }
	  /* printf("%d\n", check); */
	  break;
	case 3:
	  
	  getAdjacent(groot);
	  break;
	case 4:
	  BFS(groot, 2, -1, printVertice);
	  printf("\n");
	  break;

	case 5:
	  DFS(groot, 2, -1, printVertice);
	  printf("\n");
	  break;
	case 6:
	  freeGraph(groot);
	  check = 1;
	  printf("Drop successfull !\n");
	  break;
	default:
	  printf("Invalid input!!!\n Please try again!\n");
	  break;
	}
    }
  
  freeGraph(groot);
  jrb_free_tree(groot);
  return 0;
}

/* gcc -o graph_jrb graph_jrb.c libfdr.a && ./graph_jrb */
