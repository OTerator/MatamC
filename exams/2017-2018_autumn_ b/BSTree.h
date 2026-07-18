#ifndef BSTREE_H
#define BSTREE_H

typedef struct BSTree* BSTree;
typedef void* Element;



BSTree BSTCreate(bool (*is_greater)(Element, Elemenet));

void BSTDestroy(BSTree);

BSTree BSTAddNode(BSTree, Element);

BSTREE BSTRemoveNode(BSTree, Element);

bool BSTSearchNode(BSTree, Element);

Element* BSTinorder(BSTree);

#endif