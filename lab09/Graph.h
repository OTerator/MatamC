#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>


/* All Graph instances are undirected. */
typedef struct Graph* Graph;
typedef unsigned int Node;


Graph    GraphCreate(unsigned int node_count);

void     GraphDestroy(Graph g);

void     GraphAddEdge(Graph g, Node i, Node j, int weight);

void     GraphRemoveEdge(Graph g, Node i, Node j);

int      GraphEdgeWeight(Graph g, Node i, Node j);

bool     GraphNeighbors(Graph g, Node i, Node j);


#endif