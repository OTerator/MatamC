#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Element* Element;
typedef struct Edge* Edge;

/* An element holds a pointer to the next, hence - will form a Linked list until next_el is null.*/
struct Element {
   Node node;        // int*
   Edge edge_ll;     // pointer to the first Edge in the LL of this node's neighbor edges.
   Element next_el;  // next node's element struct.
}; 

struct Edge {
   Node node;
   unsigned int weight;
   Edge next;        // has the other node.
};  

/* All Graph instances are undirected. 
   a graph has a LL of Elements for each node
   each Element has a LL of the Edges connected to its node.
*/
struct Graph {
   Element head;    // first Element in linked list of Elements for the first node in the graph.
}; 



Graph    GraphCreate(unsigned int nodes) {
   
   Graph g = (Graph)malloc(sizeof(Graph));
   if (!g) {
      fprintf(stderr, "malloc failed at %s.", __func__);
      exit(1);
   }
   
   g->head = (Element)malloc(sizeof(Element));
   if (!(g->head)) {
      fprintf(stderr, "malloc failed at %s.", __func__);
      exit(1);
   }

   Element curr = g->head;
   
   unsigned int i = 0;
   for (; i < nodes; i++) {
      curr->node = i;
      curr->edge_ll = NULL;
      curr->next_el = (Element)malloc(sizeof(Element));
      if (!(curr->next_el)) {
         fprintf(stderr, "malloc failed at %s.", __func__);
         exit(1);
      }
      curr = curr->next_el;
   }

   curr->next_el = NULL;

   return g;
}


void     GraphDestroy(Graph g) {

}


void     GraphAddEdge(Graph g, Node i, Node j, int weight) {

   Edge edge = (Edge)malloc(sizeof(Edge));
   if (!edge) {
      fprintf(stderr, "malloc failed at %s.", __func__);
      exit(1);
   }

   Element current = g->head;
   //    reach the desired element in LL.
   while(current->node != i) {
      current = current->next_el;
   }

   edge->node = j;
   edge->next = NULL;
   edge->weight = weight;

   

}


void     GraphRemoveEdge(Graph g, Node i, Node j) {

}


int      GraphEdgeWeight(Graph g, Node i, Node j) {

}


bool     GraphNeighbors(Graph g, Node i, Node j) {}
