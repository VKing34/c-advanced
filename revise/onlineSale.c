#include <string.h>
#include <stdio.h>
#include"dirgraph.h"

void menu()
{
	printf("---------------------------------------------------------\n");
  	printf("\t\t Online Sale \n");
  	printf("---------------------------------------------------------\n");
  	printf(" 1. List of products\n 2. Order history\n 3. Check relation\n 4. Related list\n 5. Check indirected relation\n 6. Quit\nChoose one option: ");
}

void read_file(Graph g)
{
	FILE *f = fopen("products.txt", "r");

	if(f == NULL)
	{
		printf("Can't open products.txt!!!\n");
		exit(1);
	}

	int id;
	char product[100];
	while(1)
	{
		if(fscanf(f, "%d %s\n", &id, product) != EOF)
		{
			addVertex(g, id, product);
		}
		else
			break;
	}

	fclose(f);
}


void list_products(Graph g)
{
	JRB node;

	jrb_traverse(node, g.vertices)
	{
		printf("\nID: %d\nProduct: %s\n", jval_i(node->key), getVerName(g, jval_i(node->key)));
	}
}

void order_history(Graph g)
{
	FILE *f = fopen("orderhistory.txt", "r");

	if(f == NULL)
	{
		printf("Can't open orderhistory.txt!!!\n");
		exit(1);
	}

	int p1, p2, p3;
	char c;

	printf("\n");
	while(!feof(f))
	{
		if(fscanf(f, "%d", &p1) > 0)
		{
			printf("%s ", getVerName(g, p1));
			c = fgetc(f);
			if(c == '\n')
			{
				printf("\n");
				continue;
			}
			else if(c == EOF)
			{
				printf("\n");
				break;
			}

			fscanf(f, "%d", &p2);
			printf("%s ", getVerName(g, p2));

			if(hasEdge(g, p1, p2) == 1)
			{
				weight_increase(g, p1, p2);
			}
			else
			{
				insertEdge(g, p1, p2, 1);
			}

			c = fgetc(f);
			if(c == '\n')
			{
				printf("\n");
				continue;
			}
			else if(c == EOF)
			{
				printf("\n");
				break;
			}

			fscanf(f,"%d", &p3);
			printf("%s ", getVerName(g, p3));

			if(hasEdge(g, p1, p3) == 1)
			{
				weight_increase(g, p1, p3);
			}
			else
			{
				insertEdge(g, p1, p3, 1);
			}

			if(hasEdge(g, p2, p3) == 1)
			{
				weight_increase(g, p2, p3);
			}
			else
			{
				insertEdge(g, p2, p3, 1);
			}

			c = fgetc(f);
			printf("\n");
		}
		else
			break;
	}
	
	printf("\n");
	fclose(f);
}

void check_related(Graph g)
{
	int v1, v2;

	printf("Enter ID of the first product: ");
	scanf("%d", &v1);
	printf("Enter ID of the second product: ");
	scanf("%d", &v2);

	if(v1 == v2)
	{
		printf("The same product!!!\n");
		return;
	}

	if(hasEdge(g, v1, v2) == 1)
	{
		printf("The level of relation between 2 products: %d\n", getWeight(g, v1, v2));
	}
	else
	{
		printf("-1\nNo relation between 2 products!!!\n");
	}
	
}

void related_list(Graph g)
{
	JRB list = make_jrb();
	JRB node, adj;
	int id;

	printf("Enter ID: ");
	scanf("%d", &id);

	adj = adjVertex(g, id);
	if(adj != NULL)
	{
		jrb_traverse(node, adj)
		{
			jrb_insert_int(list, jval_i(node->val), new_jval_i(jval_i(node->key)));
		}
	}
	else
	{
		printf("The product (ID: %d) has no relation\n", id);
		return;
	}

	printf("List of related product(s):");
	jrb_rtraverse(node, list)
	{
		printf(" %s", getVerName(g, jval_i(node->val)));
		if(node != jrb_first(list))
		{
			printf(",");
		}
	}
	printf("\n");
}

int find_depth(Graph g, int start, int stop)
{

	Dllist stack = new_dllist();
  	JRB node;
  	attribute a,b;
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
      
      a = verAttribute(g, ver);	
      if(a->visited == 0)
      {
	       a->visited = 1;
      }

      if(ver == stop)
      {
	    return 1;
      }

      n = getAdjVertices(g, ver, adj);
      for(i = 0; i< n ; i++)
      {
	       a = verAttribute(g, adj[i]);
	       if(adj[i] == stop)
	       {
	       	a->parent = ver;
	       	return 1;
	       }
	       if(a->visited == 0)
	       {
	       	 a->parent = ver;
	         push(stack, adj[i]);
	       }
      }
    }

    free_dllist(stack);
    return 0;
}


void related_path(Graph g)
{
	int start, stop;

	printf("Enter ID of the first product: ");
	scanf("%d", &start);
	printf("Enter ID of the second product: ");
	scanf("%d", &stop);

	if(start == stop)
	{
		printf("The same product!!!\n");
		return;
	}

	if(find_depth(g, start, stop) == 0)
	{
		printf("There's no relation between 2 products\n");
		return;
	}

	Dllist p;
	Dllist stack = new_dllist();

	push(stack, stop);
	attribute a = verAttribute(g, stop);
	int previous;

	while(1)
	{
		previous = a->parent;
		if(previous == start)
		{
			break;
		}
		// printf("%d\n", a->parent);
		push(stack, previous);
		a = verAttribute(g, previous);
	}

	dll_traverse(p, stack)
	{
		printf("%s - ", getVerName(g, jval_i(p->val)));
	}
	printf("%s\n", getVerName(g, start));

	free_dllist(stack);
}

int main()
{
	int choose;
	Graph g = createGraph();

	read_file(g);

	while(choose != 6)
	{
		menu();
		scanf("%d", &choose);
		switch(choose)
		{
			case 1:
			list_products(g);
			break;

			case 2:
			order_history(g);
			break;

			case 3:
			check_related(g);
			break;

			case 4:
			related_list(g);
			break;

			case 5:
			related_path(g);
			break;

			case 6:
			break;

			default:
			printf("Invalid input !!!\nPlease try again\n");
			break;
		}
	}

	dropGraph(g);
	return 0;
}


// gcc -g -o sale onlineSale.c dirgraph.c libfdr.a && ./sale