#include "BST.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Add whatever helper functions you need here


Element cpyfoo(Element e) {
    if (!e) {
        return NULL;
    }

    char* dupe = (char*)malloc(strlen((char*)(e)) + 1);     // +1 for '\0'

    if (!dupe) {
        fprintf(stderr, "mem alloc failed.\n");
        exit(1);
    }

    return strcpy(dupe, e);
}


int cmpfoo(Element e1, Element e2) {
    return strcmp((char*)e1, (char*)e2);
}


void myPrintln(Element e) {
    if (!e) {return;}

    printf("%s\n", (char*)e);
}



int main () {
    // char* words[] = {"orange", "banana", "apple", "cherry", "date", "fig", "grape", "elderberry"};

    // 8. Manually reorder the array "words" so that the resulting BST is balanced and its height is minimized
    // char* reordered[] =
    char* words[] = {"elderberry", "cherry", "grape", "banana", "date", "fig", "orange", "apple"};  // one way to balance


    int n = sizeof(words) / sizeof(words[0]);       // n = n*sizeof(words_arr)/sizeof(char*)

    // 1. Creat the BST
    Tree tree = BSTCreate(cpyfoo, free, cmpfoo);

    // 2. Add words to the BST
    for (unsigned int i=0; i<n; i++) {
        BSTAdd(tree, words[i]);
    }

    // 3. Print in-order traversal
    printf("\n*--------------------*\n3. In-Order traversal:\n*--------------------*\n");
    BSTinorder(tree, myPrintln);
    // printf("\n");
    
    // 4. Print height and number of nodes
    printf("\n*--------------------*\n4. Height and number of nodes:\n*--------------------*\n");
    unsigned int height = BSTHeight(tree);
    unsigned int num_nodes = BSTNumNodes(tree);
    printf("Height = %u , Num_nodes = %u\n", height, num_nodes);
    
    // 5. Search for a word
    printf("\n*--------------------*\n5. Word Search:\n*--------------------*\n");
    char* w1 = "fig";
    char* there = BSTSearch(tree, w1) ? "there" : "not there";
    char* w2 = "otter";
    char* not_there = BSTSearch(tree, w2) ? "there" : "not there";
    
    printf("%s is %s, %s is %s.\n", w1, there, w2, not_there);
    
    // 6. Clone the tree and print cloned tree
    Tree dupe = BSTClone(tree);
    printf("\n*--------------------*\n6. Clone:\n*--------------------*\n");
    BSTinorder(dupe, myPrintln);
    // printf("\n");

    // 7. Destroy both trees
    BSTDestroy(dupe);
    BSTDestroy(tree);

    

    return 0;
}