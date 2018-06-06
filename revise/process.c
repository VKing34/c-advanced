#include <string.h>
#include <stdio.h>
#include"dirgraph.h"

void menu()
{
	printf("---------------------------------------------------------\n");
  	printf("\t\t Process \n");
  	printf("---------------------------------------------------------\n");
  	printf(" 1. Read file\n 2. Information of one activity\n 3. \n 4. List the process in order\n 5. Time for finishing one job\n 6. Check DAG\n 7. Quit\nChoose one option: ");
}

void read_file(Graph g)
{
	char filename[30];
	while(getchar()!='\n');
	printf("Enter file name: ");
	scanf("%s", filename);

	FILE *f = fopen(filename, "r");

	if(f == NULL)
	{
		printf("There does exist file %s!!!\n", filename);
		return;
	}

	char c;
	char actname[3];
	int act[15], weight, n;

	while(!feof(f))
	{
		n =0;
		fscanf(f, "%[^ :] ", actname);
		
		sscanf(actname, "%*[^0123456789]%d", &act[n]);
		if(hasVertex(g, act[n]) == 0)
		{
			addVertex(g, act[n], actname);
		}
		printf("%s (%d) : ", actname, act[n]);
		
		while(c != ':')
		{
			c = fgetc(f);
		}
		c = fgetc(f);
		if(c == '\n')
		{
			printf("xuong dong\n");
			continue;
		}
		while(1)
		{
			// if(fscanf(f, "%[^-]-%d", actname, weight) == EOF)
			// {
			// 	printf("\n");
			// 	break;
			// }
			fscanf(f, "%[^-]", actname);
			fgetc(f);
			fscanf(f, "%d", &weight);
			n++;
			sscanf(actname, "%*[^0123456789]%d", &act[n]);
			printf("%s(%d)-%d ", actname, act[n], weight);
			if(hasVertex(g, act[n]) == 0)
			{
			addVertex(g, act[n], actname);
			}
			addEdge(g, act[n], act[0], weight);
			c = fgetc(f);
			if(c == EOF)
			{
				break;
			}
			else if( c == '\n')
			{
				printf("\n");
				break;
			}
		}
	}

	printf("\n");

	printf("Number of vertices: %d\nNumber of edges: %d\n", vertices(g), edges(g));

	fclose(f);
}

int reverse(Graph g, int v)
{
	int num, pre[9], i,total=0;
	attribute a = verAttribute(g, v);
	num = indegree(g, v, pre);

	if(num == 0 && a->visited == 0)
	{
		printf("%s\n", getVerName(g, v));
		a->visited = 1;
		return 1;
	}

	for(i = 0; i< num; i++)
	{
		a = verAttribute(g, pre[i]);
		if(a->visited == 0)
		{
			printf("%s\n", getVerName(g, pre[i]));
			total++;
			a->visited =1;
		}
	}
	
	for(i = 0; i< num; i++)
	{
		total += reverse(g, pre[i]);
	}
	return total;
}

void inform(Graph g)
{
	char actname[3];
	int v, num, pre[9];

	printf("Enter name of the activity: ");
	scanf("%s", actname);

	sscanf(actname, "%*[^0123456789]%d", &v);

	if(hasVertex(g, v) == 0)
	{
		printf("The activity is not in the process!!!\n");
		return ;
	}

	num = indegree(g, v, pre);

	printf("%d activiti(es) before\n", num);
	for(int i =0; i< num; i++)
	{
		printf("%s\n", getVerName(g, pre[i]));
	}

	printf("-----------------------------\n");

	num = reverse(g, v);
	printf("%d\n", num);
	// BFS(g, 1, v, printVertex);
}

int maxso(int old, int new)
{
	if(old > new)
		return old;
	else
		return new;
}

int getDistance(Graph g, int v)
{
	attribute a = verAttribute(g, v);
	if(a)
		return a->distance;
	else
		return -99;
}

// void timetocomplete(Graph g)
// {
// 	char actname[3];
// 	int v, d1, d2;

// 	printf("Enter name of the activity: ");
// 	scanf("%s", actname);

// 	sscanf(actname, "%*[^0123456789]%d", &v);

// 	if(hasVertex(g, v) == 0)
// 	{
// 		printf("The activity is not in the process!!!\n");
// 		return ;
// 	}

// 	attribute a;
// 	JRB node, adj, first, tmp;

// 	jrb_traverse(node, g.vertices)
// 	{
// 		a = verAttribute(g, jval_i(node->key));
// 		a->distance=-99;
// 	}

// 	a = verAttribute(g, 1);
// 	a->distance = 0;

// 	adj = adjVertex(g, 1);
// 	jrb_traverse(node, adj){

// 		a = verAttribute(g, jval_i(node->key));
// 		a->distance = getWeight(g, 1, jval_i(node->key));
// 	}

// 	first = getVertex(g, 1);

// 	jrb_traverse(node, g.vertices)
// 	{
// 		if(node != first)
// 		{
// 			d1 = getDistance(g, jval_i(node->key));
// 			adj = adjVertex(g, jval_i(node->key));
// 			jrb_traverse(tmp, adj)
// 			{
// 				d2 = getDistance(g, jval_i(tmp->key));
// 				a->distance = maxso(d2,d1 + getWeight(g, jval_i(node->key), jval_i(tmp->key)));
// 			}
// 		}
// 	}

// 	printf("Time to complete: %d\n", getDistance(g, v));

// }

void sort(Graph g)
{
	int output[15];
	int total=0;

	tSort(g, output, &total);

	for(int i=0; i<total; i++)
	{
		printf("%s\n", getVerName(g, output[i]));
	}
} 

void checkDAG(Graph g)
{
	if(DAG(g) == 0)
	{
		printf("The topo satisfies.\n");
	}
	else
		printf("The topo does not satisfies!!!\n");
}

int main()
{
	int choose;

	Graph g = createGraph();
	while(choose != 7)
	{
		menu();
		scanf("%d", &choose);
		switch(choose)
		{
			case 1:
			read_file(g);
			break;
			case 2:
			while(getchar()!='\n');
			inform(g);
			break;
			case 3:
			break;
			case 4:
			sort(g);
			break;
			case 5:
			while(getchar()!='\n');
			// timetocomplete(g);

			break;
			case 6:
			checkDAG(g);
			break;
			case 7:
			break;

			default:
			printf("Invalid input!!!\n");
			break;
		}
	}

	dropGraph(g);
	return 0;
}

// gcc -o pro process.c dirgraph.c libfdr.a && ./pro