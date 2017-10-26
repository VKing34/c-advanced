#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"jval.h"
#include"jrb.h"

typedef JRB graph;

void menu()
{
  printf("---------------------------------------------------------\n");
  printf("\t\t JRB - Graph\n");
  printf("---------------------------------------------------------\n");
  printf("1. BFS\n 2. DFS\n 3. Find out the shortest path\n 0. Quit\nChooe one option: ");
}

void addEdge(graph root, Jval v1, Jval v2)
{

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
}

int checkAdjacent(graph root, Jval v1, Jval v2)
{
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

void getAdjacent(graph root, Jval vertice)
{
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
  

void freeGraph(JRB root)
{
  JRB node;
  jrb_traverse(node, root)
    {
      jrb_free_tree(jval_v(node->val));
    }
}

void bfs(graph root, Jval)
{
  
}


void case1(graph root)
{
  Jval s;
  printf("Enter vertice: ");
  scanf("%d", &s.i);
  bfs(root, s);
  
}

void case2(graph root)
{
  int s;
  printf("Enter vertice: ");
  scanf("%d", &s);
  dfs(root, s);
  
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
	  
	  case1(groot);
	  break;
	case 2:
	  
	  case2(groot);
	  break;
	case 3:
	  
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
