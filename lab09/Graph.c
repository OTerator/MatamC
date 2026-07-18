#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

// old:
// typedef struct Edge Edge;

// now:
typedef struct Edge* Edge;

struct Edge {
   Node node;              // unsigned int value
   unsigned int weight;    // edge weight
   Edge next;             // has the other node.
};  

/* All Graph instances are undirected. 
   a graph has an Array of Linked Lists for each node - for each edge.
   Each LL is consisted of the Edges connected to its index node.
*/
struct Graph {
   Edge* edges;
   unsigned int node_count;
}; 



Graph    GraphCreate(unsigned int node_count) {
   
   Graph g = (Graph)malloc(sizeof(struct Graph));
   if (!g) {
      fprintf(stderr, "malloc failed at %s.\n", __func__);
      exit(1);
   }

   // list of pointers to Edge Linked Lists, therefore: (node_count)*(8) bytes. one LL pointer in the array for each node.  
   g->edges = (Edge*)calloc(node_count, sizeof(Edge));
   if (!(g->edges)) {
      free(g);
      fprintf(stderr, "malloc failed at %s.\n", __func__);
      exit(1);
   }  // each node's corresponding LL is determined by index, node n has index n; one-one mapping.
   g->node_count = node_count;

   return g;
}



void     GraphDestroy(Graph g) {
   if (!g) {
      return;
   }

   for (unsigned int i=0; i<g->node_count; i++) {
      while(g->edges[i] != NULL) {
         Edge current = g->edges[i];
         g->edges[i] = g->edges[i]->next;
         free(current);
      }
   }

   free(g->edges);   // free the arr of null "LL"s
   free(g);          // free the graph.
}



void     GraphAddEdgeHelper(Graph g, Node i, Node j, int weight) {

   Edge edge = (Edge)malloc(sizeof(struct Edge));
   if (!edge) {
      fprintf(stderr, "malloc failed at %s.\n", __func__);
      exit(1);
   }
   
   edge->node = j;
   edge->next = NULL;
   edge->weight = weight;

   // address holder 
   Edge current = g->edges[i];

   if (g->edges[i] == NULL) {   // This is the first edge in the linked list. we just need to append it
      g->edges[i] = edge;
   } else {          // To reach the tail of the LL.
      while (current->next != NULL) {
         current = current->next;
      }              // From here the current next is NULL, which is the one we want to set:
      current->next = edge;      // Add this edge as the new tail.
   }
}


void     GraphAddEdge(Graph g, Node i, Node j, int weight) {
   
   // We need to repeat the process for each node; made simple by swaping i and j. I've chosen to turn the implementation into the helper to reduce duplicate code
   GraphAddEdgeHelper(g, i, j, weight);
   GraphAddEdgeHelper(g, j, i, weight);
}




Edge    getEdge(Graph g, Node i, Node j) {

   if (!g) {
      fprintf(stderr, "Graph is NULL, %s\n", __func__);
      exit(2);
   }

   // old:
   // Edge current = g->edges[i];
   // while(current != NULL && current->node != j) {
   //    current = current->next;
   // }

   // upgrade:
   Edge curr;
   for (curr = g->edges[i]; (curr) && (curr->node != j); curr = curr->next)
      ;

   return curr;
}



void     GraphRemoveEdgeHelper(Graph g, Node i, Node j) {

   if (!g) {
      fprintf(stderr, "Graph is NULL, %s\n", __func__);
      exit(2);
   }

   Edge current = g->edges[i];
   Edge previous = NULL;
   
   while(current != NULL && current->node != j) {
      previous = current;
      current = current->next;
   }

   // if current is NULL, that means no Edge was found between i and j. 
   if (!current) {
      return;
   }
   // pointer rearrangement
   if (previous == NULL) { // this is the head of the LL, hence there's no previous: 
      g->edges[i] = current->next;
   } else {
      previous->next = current->next;  
   }
   free(current);
}



void     GraphRemoveEdge(Graph g, Node i, Node j) {
   //  if the edge exists, remove it from both LLs:
   GraphRemoveEdgeHelper(g,i,j);
   GraphRemoveEdgeHelper(g,j,i);
}




int      GraphEdgeWeight(Graph g, Node i, Node j) {
   
   Edge ij = getEdge(g, i, j);
   
   return !ij ? 0 : ij->weight;     // if null return 0.
}



bool     GraphNeighbors(Graph g, Node i, Node j) {

   Edge ij = getEdge(g, i, j);

   return (ij != NULL);    // if null- no Edge was found.
}
