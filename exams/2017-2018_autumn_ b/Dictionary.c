#include "Dictionary.h"
#include "BSTree.h"
#include <string.h>

// we'll create a BST of the Nodes:
typedef struct Node* Node;

struct Node {
	const char* word;
	const char* meaning;
};

struct Dict {
	BSTree t;
};


// Element comes from BSTree.h 
bool str_cmp(Element e1, Element e2) {
	const char* str1 = (Node)(e1);
	const char* str2 = (Node)(e2);
	return (bool)(strcmp(e1->word, e2->word) > 0);
}



Dict CreateDictionary() {
	
	Dict d = (Dict) malloc(sizeof(struct Dict));
	d->t = BSTCreate(str_cmp);
	
	return d;
}


bool DictAdd(Dict d, const char* word, const char* meaning) {
	
	Node pair = (Node)malloc(sizeof(struct Node));
	
	pair->word = strdup(word);
	pair->meaning = strdup(meaning);
	
	if (BSTSearchNode(d->t, pair) {
		free(pair->word);
		free(pair->meaning);
		free(pair);
		return false;
	}
	
	BSTAddNode(BSTree, pair);
	return true;
}
