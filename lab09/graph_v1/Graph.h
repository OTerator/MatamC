#define GRAPH_H
#ifndef GRAPH_H
#include <stdbool.h>


/* All Graph instances are undirected. */
typedef struct Graph* Graph;
typedef int Node;


Graph    GraphCreate(unsigned int nodes);

void     GraphDestroy(Graph g);

void     GraphAddEdge(Graph g, int weight, Node i, Node j);

void     GraphRemoveEdge(Graph g, Node i, Node j);

int      GraphEdgeWeight(Graph g, Node i, Node j);

bool     GraphNeighbors(Graph g, Node i, Node j);


#endif