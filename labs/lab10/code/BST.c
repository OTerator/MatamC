#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Implementation of a Binary Search Tree (BST) ADT.
 * Tree: stores Elements using user-provided copy, free, and compare functions.
 * Node: internal structure representing each node in the BST.
 */

/******************* Node struct and functions *******************/
typedef struct Node* Node;
struct Node {
	Element key;
	Node left;
	Node right;
};

// Post-order traversal to free all nodes
void NodeDestroyTree(Node node, void (*fre)(Element)) {
	if(!node)
		return;

	NodeDestroyTree(node->left, fre);
	NodeDestroyTree(node->right, fre);
	fre(node->key);
	free(node);
}

bool NodeSearchBST(Node root, Element key, int (*cmp)(Element, Element)){
	if(!root) // Tree is empty
		return false;
	if(cmp(key, root->key) == 0) // Key was found
		return true;
	if(cmp(key, root->key) < 0) // Go left
		return NodeSearchBST(root->left, key, cmp);
	// Go right
	return NodeSearchBST(root->right, key, cmp);
}

// We assume that key is already copied
Node NodeAddBST(Node root, Element key, int (*cmp)(Element, Element), Element (*cpy)(Element)){
	if(!root){
	  	Node new_node = (Node)malloc(sizeof(struct Node));
		new_node->key = cpy(key);
		new_node->left = new_node->right = NULL;
		return new_node;
	}
	if(cmp(key, root->key) <= 0) // Go left
		root->left = NodeAddBST(root->left, key, cmp, cpy);
	else // if(key > (root->key)) // Go right
		root->right = NodeAddBST(root->right, key, cmp, cpy);

	return root;
}

Node NodeRemoveBST(Node root, Element key, int (*cmp)(Element, Element), void (*fre)(Element), Element (*cpy)(Element)){
	if(!root)
		return NULL;

	// This node is not to be deleted
	if(cmp(root->key, key) != 0) {
		if(cmp(key, root->key) < 0) // Go left
			root->left = NodeRemoveBST(root->left, key, cmp, fre, cpy);
		else if(cmp(key, root->key) > 0) // Go right
			root->right = NodeRemoveBST(root->right, key, cmp, fre, cpy);
		return root;
	}
	// else – we need to remove this node – next slide

	// Option 1: trying to remove a leaf
	if(!(root->left) && !(root->right)) {
		fre(root->key);
		free(root);
		return NULL;
	}

	// Option 2: node has only one child
	else if(!(root->left)) {
		Node temp = root->right;
		fre(root->key);
		free(root);
		return temp;
	}
	else if(!(root->right)) {
		Node temp = root->left;
		fre(root->key);
		free(root);
		return temp;
	}

	// Option 3: node has 2 children
	else {
		Node x = root->right;
		// Node* xparent = &(root->right);
		while(x->left) {
			// xparent=&(x->left);
			x=x->left;
		}
		// Dangling Pointer fix:
		// making a deep copy of the successor's key:
		Element tempKey = cpy(x->key);
		// free the current old key:
		fre(root->key);
		// update curr with a new: key
		root->key = tempKey; //= x->key;
		//	recursively remove the successor from the right subtree:
		// *xparent = NodeRemoveBST(x, x->key, cmp, fre);
		root->right = NodeRemoveBST(root->right, x->key, cmp, fre, cpy);
	}

	return root;
}

/******************* Tree struct and functions *******************/
struct Tree {
	Node root;
	Element (*cpy)(Element);
	void (*fre)(Element);
	int (*cmp)(Element, Element);
};

Tree BSTCreate(Element (*cpy)(Element), void (*fre)(Element), int (*cmp)(Element, Element)) {
	Tree tree = (Tree)malloc(sizeof(struct Tree));
	if(!tree) {
		fprintf(stderr, "Error in %s: failed to allocate %lu bytes\n", __func__, sizeof(struct Tree));
		exit(-1);
	}
	tree->root = NULL;
	tree->cpy = cpy;
	tree->fre = fre;
	tree->cmp = cmp;

	return tree;
}

void BSTDestroy(Tree tree) {
	NodeDestroyTree(tree->root, tree->fre);
	free(tree);
}

bool BSTSearch(Tree tree, Element key){
	return NodeSearchBST(tree->root, key, tree->cmp);
}

// Need to make generic and fit struct Tree from here
void BSTAdd(Tree tree, Element key){
	tree->root = NodeAddBST(tree->root, key, tree->cmp, tree->cpy);
}

void BSTRemove(Tree tree, Element key){
	if(!tree)
		return;
	tree->root = NodeRemoveBST(tree->root, key, tree->cmp, tree->fre, tree->cpy);
}





/********* You need to implement the following functions *********/





// in theory every node is a sub tree but not in this code format so a helper func is a must.
void inOrder(Node root, void (*print)(Element)) {
	if (root == NULL) {
		return;
	}

	inOrder(root->left, print);
	print(root->key);		// myPrintln
	// printf("\n");
	inOrder(root->right, print);
}
// In-order traversal printing of the tree's elements
void BSTinorder(Tree tree, void (*print)(Element)) {
	if(tree != NULL) {
		inOrder(tree->root, print);
	}
}





int BSTHeightHelper(Node root) {
	
	if (!root) {	// entering a NULL branch, abort the count by decrementing.
		return -1;
	}

	int left = BSTHeightHelper(root->left);		// count left branches
	int right = BSTHeightHelper(root->right);	// count right branches

	return (left > right ? left : right) + 1;		// return the greater one.
}
// Returns the height of the tree
unsigned int BSTHeight(Tree tree) {
	if(!tree || !tree->root) {
		return 0;
	}

	return (unsigned int)BSTHeightHelper(tree->root);
}





unsigned int numNodes(Node root) {
	if (root) {
		return numNodes(root->left) + numNodes(root->right) + 1;
	}
	return 0;
}
// Returns the number of nodes in the tree
unsigned int BSTNumNodes(Tree tree) {
	if (!tree || !tree->root) {
		return 0;
	}
	return numNodes(tree->root);
}





void CloneHelper(Tree dupe, const Node root) {
	if (!root) {
		return;
	}
	/* In order to use BSTAdd: 
		we have to work from top to bottom and let BSTAdd travel through the nodes each time. 
		(I know this isn't the most optimal solution for complexity, but would rather keep it simple and make use of BSTAdd).
		therefore we have to work in Post-Order:
	*/
	BSTAdd(dupe, root->key); // copy the key.
	// repeat for the left and right branches.
	CloneHelper(dupe, root->left);
	CloneHelper(dupe, root->right);
}
// Returns a deep copy of the source tree
Tree BSTClone(const Tree src) {

	if (!src) {
		return NULL;
	}

	Tree dupe = BSTCreate(src->cpy, src->fre, src->cmp);
	CloneHelper(dupe, src->root);

	// BSTAdd(dupe, src->root->key);
	return dupe;
}