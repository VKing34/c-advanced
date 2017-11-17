#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"jval.h"
#include"dllist.h"
#include"jrb.h"
#define max 99
#define infinitive_value 999
typedef struct{
  JRB edges;
  JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph g, int id, Jval name);
Jval getVertex(Graph g, int id);
void addEdge(Graph g, int v1, int v2, int weight);
int hasEdge(Graph g, int v1, int v2);
int indegree(Graph g, int v, int *output);
int outdegree(Graph g, int v, int *output);
int getEdgeValue(Graph g, int v1, int v2);  // return -1 if not connected, return >0 if valid
int shortestPath(Graph g, int s, int t, int *path, int *length);
int DAG(Graph g);
void dropGraph(Graph g);

