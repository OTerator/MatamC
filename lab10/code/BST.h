#ifndef BST_H
#define BST_H
#include <stdbool.h>

/*
 * A binary search tree (BST) implementation.
 */

typedef void* Element;
typedef struct Tree* Tree;

/* cmp shout return a value that is:
 <0 if the first element is smaller than the second
 >0 if the first element is larger than the second
 =0 if the two elements are equal
*/
Tree BSTCreate(Element (*cpy)(Element), void (*fre)(Element), int (*cmp)(Element, Element));

// Frees all memory allocated for the tree, including all its elements
void BSTDestroy(Tree tree);

// Returns true if the key is in the tree, false otherwise
bool BSTSearch(Tree tree, Element key);

// Adds the key to the tree. if it is already present, another copy will be added to the left (smaller than or equal to)
void BSTAdd(Tree tree, Element key);	// cmp, cpy

// Removes the key from the tree if it is present, otherwise does nothing
void BSTRemove(Tree tree, Element key);

/********* You need to implement the following functions *********/

// In-order traversal printing of the tree's elements
void BSTinorder(Tree tree, void (*print)(Element));

// Returns the height of the tree
unsigned int BSTHeight(Tree tree);

// Returns the number of nodes in the tree
unsigned int BSTNumNodes(Tree tree);

// Returns a deep copy of the source tree
Tree BSTClone(const Tree src);

#endif // BST_H
