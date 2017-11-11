#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"jval.h"
#include"dllist.h"
#include"jrb.h"
#define max 99
typedef struct{
  JRB edges;
  JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph g, int id, Jval name);
Jval getVertex(Graph g, int id);
void addEdge(Graph g, int v1, int v2);
int hasEdge(Graph g, int v1, int v2);
int indegree(Graph g, int v, int *output);
int outdegree(Graph g, int v, int *output);
int DAG(Graph g);
void dropGraph(Graph g);

