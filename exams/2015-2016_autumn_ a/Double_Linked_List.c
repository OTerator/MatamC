#include "Double_Linked_List.h"

typedef struct Node* Node;

struct Node {
	Node previous;
	Element e;
	Node next;
};

struct DLL {
	Node head;
	Element (*cpy)(Element);
	void (*fre)(Element);
	bool (*cmp)(Element, Element)
};



DLL DLLCreate(Element (*cpy)(Element), void (*fre)(Element), bool (*cmp)(Element, Element)) {
	
	DLL dll = (DLL) malloc(sizeof(struct DLL));
	//if !dll...
	
	dll->head = NULL;
	dll->cpy = cpy;
	dll->cmp = cmp;
	dll->fre = fre;
	
	return dll;
}

static Node getNode(DLL dll, Element e) {
	// if !dll !head....
	
	Node curr = dll->head;
	
	while (curr) {
		if (dll->cmp(curr->e, e)) return curr; curr
		curr = curr->next;
	}
	
	return NULL;
}

void DLLRemove(DLL dll, Element e) {
	
	//if (!DLLFind(dll, e)) return;	// not there.
	
	Node node = getNode(dll, e);
	if (!node) return;
	
	if (node->next) {
		node->next->previous = node->previous;
	} // else we are removing the last node, so no one will point to it and the prev will get NULL from node->next.
	
	if (node->previous) {
		node->previous->next = node->next;
	} else { // if no prev, the head is removed:
		dll->head = node->next; // new head, prev NULL alr received.
	}
	
	dll->fre(node->e);
	free(node);
}