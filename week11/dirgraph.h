#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <limits.h>
#include"jval.h"
#include"dllist.h"
#include"jrb.h"
#define max 99
#define infinitive_value 999
#define infinitive_value 999
#define enqueue(queue, id) dll_append(queue, new_jval_i(id))
#define push(queue, id) dll_prepend(stack, new_jval_i(id))
#define pop(stack) dequeue(stack)

typedef struct{
char *name;
int id;
int visited;
int distance;
JRB pr;
} at;

typedef at* attribute;

typedef struct{
  JRB edges;
  JRB vertices;
} Graph;


Graph createGraph();
void addVertex(Graph g, int id, char *name);
void addEdge(Graph g, int v1, int v2, int weight);
int hasEdge(Graph g, int v1, int v2);
attribute verAttribute(Graph g, int v);
int indegree(Graph g, int v, int *output);
int outdegree(Graph g, int v, int *output);
char *getVerName(Graph g, int v);
int getWeight(Graph g, int v1, int v2);
int getAdjVertices(Graph g, int v, int *output);
int shortestPath(Graph g, int s, int t, int *path, int *length);
int printVertex(Graph g, int v);
void BFS(Graph g, int start, int stop, int (*func)(Graph, int));
void DFS(Graph g, int start, int stop, int (*func)(Graph, int));
void dropGraph(Graph g);
int DAG(Graph g); // return 0 if DAG
void tSort(Graph g, int *output, int *total);

