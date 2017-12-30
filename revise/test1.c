#include <string.h>
#include"dirgraph.h"




void size(char *filename)
{
	int n, m, count=0;
	char tmp[99];
	FILE *f = fopen(filename, "r");
	if(f == NULL)
	{
		printf("File %s does not exist!\n", filename);
		return;
	}
	fscanf(f, "%d\n", &n);
	printf("%d\n", n);
	while(count != n)
	{
		fscanf(f, "%[^\n]\n", tmp);
		count++;
	}
	fscanf(f,"%d\n", &m);
	printf("Number of URLs: %d\nNumber of superlinks: %d\n", n, m);

	fclose(f);
}

void read_file(Graph g, char *filename)
{
	FILE *f = fopen(filename, "r");
	if(f == NULL)
	{
		printf("File %s does not exist!\n", filename);
		return;
	}

	int n, m, count=0, v1, v2;
	char url[99];

	fscanf(f, "%d\n", &n);
	while(count != n)
	{
		fscanf(f, "%s %d\n", url, &v1);
		// printf("%s %d\n", url, v1);
		addVertex(g, v1, url);
		count++;
	}

	fscanf(f, "%d\n", &m);
	count = 0;
	while(count != m)
	{
		fscanf(f, "%d %d\n", &v1, &v2);
		addEdge(g, v1, v2, 1);
		count++;
	}

	fclose(f);
}

void out(char *filename, int id)
{
	Graph g = createGraph();
	read_file(g, filename);
	JRB node, adj;
	adj = adjVertex(g, id);
	if(adj)
	{
		jrb_traverse(node, adj)
		{
			printf("%d\t%s\n", jval_i(node->key), getVerName(g, jval_i(node->key)));
		}
	}
	else
	{
		printf("The website (id: %d) does not have any link.\n", id);
	}
}


int inde(Graph g, int v)
{
	JRB node, node1, adj;
	int total=0;
		
	jrb_traverse(node, g.edges)
	{
		adj = (JRB)jval_v(node->val);
		jrb_traverse(node1, adj)
		{
			if(jval_i(node1->key) == v)
			{
				total++;
			}
		}
	}
	return total;
	
}

void maxin(char *filename)
{
	Graph g = createGraph();
	read_file(g, filename);
	attribute a;
	JRB node;
	int MAX=0;
	int v;
	jrb_traverse(node, g.vertices)
	{
		a = getAttribute(node);
	
		a->distance = inde(g, jval_i(node->key));
		// printf("%d\t%d\n",jval_i(node->key), jval_i(node->key));
		// printf("%d\n", a->distance);
		if(MAX < a->distance)
		{
			MAX = a->distance;
			v = jval_i(node->key);
		}
	}

	printf("The website has the most in-links: %s (id: %d)\n", getVerName(g, v), v);

}

void selfref(char *filename)
{
	Graph g = createGraph();
	read_file(g, filename);
	JRB node, node1, adj;
	jrb_traverse(node, g.edges)
	{
		adj = adjVertex(g, jval_i(node->key));
		if(adj)
		{
			jrb_traverse(node1, adj)
			{
				if(jval_i(node1->key) == jval_i(node->key))
				{
					printf("The website %s has a link pointing to itself.\n", getVerName(g, jval_i(node->key)));
					return;
				}
			}
		}
	}
	printf("OK!\n");	
}

void BFS_of_k(Graph g, int start, int k)
{
	Dllist q;
  	JRB v;
  	attribute a;
  	int ver, n, i, count=0;
  	int adj[99];
  
  	// mark all as unvisited
  	jrb_traverse(v, g.vertices)
    {
      a = getAttribute(v);
      a->visited = 0;
    }
    //  v = jrb_find_int(g.vertices, start);
	//  a = getAttribute(v);
	a = verAttribute(g, start);
  	a->visited = 1;

  	// init a queue
  	q = new_dllist();
  	enqueue(q, start);

  	while(count != k)
  	{
  		ver = dequeue(q);

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
	     		printf("%s\n", getVerName(g, adj[i]));
	     	}
	   	}
	   	count++;
  	}
}

void list(char *filename, int id, int k)
{
	Graph g = createGraph();
	read_file(g, filename);

	BFS_of_k(g, id, k);

}


int main(int argc, char *argv[])
{
	if(argc > 5)
	{
		printf("Wrong syntax!!!\n");
		return 1;
	}

	if(strcmp(argv[1], "about") == 0)
	{
		printf("The exam for advanced programming C HK2 - 2014 - 2015.\n");
		return 0;
	}

	if(strcmp(argv[1], "size") == 0)
	{
		if(argc != 3)
		{
			printf("Wrong syntax!!!\n");
			return 1;
		}
		size(argv[2]);
		return 0;
	}

	if(strcmp(argv[1],"out") == 0)
	{

		if(argc != 4)
		{
			printf("Wrong syntax!!!\n");
			return 1;
		}

		out(argv[2], atoi(argv[3]));
		return 0;
	}

	if(strcmp(argv[1], "maxin") == 0)
	{
		if(argc != 3)
		{
			printf("Wrong syntax!!!\n");
			return 1;
		}
		maxin(argv[2]);
		return 0;
	}

	if(strcmp(argv[1], "selfref") == 0)
	{
		if(argc != 3)
		{
			printf("Wrong syntax!!!\n");
			return 1;
		}
		selfref(argv[2]);
		return 0;
	}

	if(strcmp(argv[1],"list") == 0)
	{

		if(argc != 5)
		{
			printf("Wrong syntax!!!\n");
			return 1;
		}

		list(argv[2], atoi(argv[3]), atoi(argv[4]));
		return 0;
	}

	
	printf("Wrong syntax!!!\n");
	return 0;
}

// gcc -g -o test1 test1.c dirgraph.c libfdr.a && ./test1 