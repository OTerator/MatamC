#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int main(int argc, const char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "\nUsage: %s <non-zero-seed>\n\n", argv[0]);
        return 1;
    }
    int seed = atoi(argv[1]);
    if(!seed) {
        fprintf(stderr, "Error: seed must be a non-zero int and not %s\n\n", argv[1]);
        return 2;
    }

    srand(seed);

    unsigned int num_nodes = rand()%15;

    // Build the graph
    Graph g = GraphCreate(num_nodes);

    for(unsigned i=0; i<num_nodes; i++) {
        for(unsigned j=0; j<i; j++) {
            if(rand()%2) {
                int weight = 1 + rand()%100;
                GraphAddEdge(g, i, j, weight);
            }        
        }    
    }

    // Print neighbors info
    printf("\n*** Graph edge info ***\n");
    for(unsigned i=0; i<num_nodes; i++) {
        printf("\t%u", i);
    }
    printf("\n");

    for(unsigned i=0; i<num_nodes; i++) {
        printf("%u", i);
        for(unsigned j=0; j<num_nodes; j++) {
            printf("\t%d", GraphNeighbors(g, i, j));
        }
        printf("\n");
    }

    // Randomly remove some edges, also some that do not exist 
    for(unsigned i=0; i<num_nodes; i++) {
        for(unsigned j=0; j<i; j++) {
            if(rand()%3 == 0) {
                GraphRemoveEdge(g, i, j);
            }        
        }    
    }

    // Print neighbors info
    printf("\n*** Graph weight info after removing some edges ***\n");
    for(unsigned i=0; i<num_nodes; i++) {
        printf("\t%u", i);
    }
    printf("\n");

    for(unsigned i=0; i<num_nodes; i++) {
        printf("%u", i);
        for(unsigned j=0; j<num_nodes; j++) {
            printf("\t%d", GraphEdgeWeight(g, i, j));
        }
        printf("\n");
    }

    GraphDestroy(g);

    return 0;
}