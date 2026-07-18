#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************/
typedef struct Node*  Node;
struct Node {
    Element e;
    Node next;
};

struct LinkedList {
    Node head;      
    Node current;   // is used for iterations, to initialize this variable the user must call LLNext() which sets it to the head, and from there LLNext() is used to iterate, at most until the end of the LL to meet NULL again.
};

/*******************************************************************************/
LinkedList      LLCreate() {
    LinkedList ll = (LinkedList)calloc(1, sizeof(struct LinkedList));
    if(!ll) {
        fprintf(stderr, "%s/%u: failed to allocate %zu bytes\n\n", __FILE__, __LINE__, sizeof(struct LinkedList));
        //exit(-1);
        return NULL;    // gets captured in the HashTable module, and from there passed to main to exit in MEM_ALLOCATION_ERROR or let the user decide otherwise.
    }
        
    return ll;
}

/*******************************************************************************/
void            LLDestroy(LinkedList ll) {
    while(ll->head) {
        // Element e = no more use
        LLRemove(ll, 0);
        //ll->fre(e);
    }
    
    free(ll);
}

/*******************************************************************************/
unsigned int    LLSize(LinkedList ll) {
    int n = 0;
    Node node = ll->head;
    while(node) {
        n++;
        node = node->next;
    }
    
    return n;
}

/*******************************************************************************/
void      LLAdd(LinkedList ll, unsigned int index, Element element) {
    // This is an error
    if(index > LLSize(ll)) {
        fprintf(stderr, "Error in %s/LLAdd: illegal index %u, list size is only %u\n\n", __FILE__, index, LLSize(ll));
        exit(-1);
    }

    // Create the new node
    Node new_node = (Node)malloc(sizeof(struct Node));
    if(!new_node) {
        fprintf(stderr, "%s/%u: failed to allocate %zu bytes\n\n", __FILE__, __LINE__, sizeof(struct Node));
        exit(MEM_ALLOCATION_ERROR);
    }
    new_node->e = element;

    // If need to place the new node at the top of the list - do it
    if(index == 0) {
        new_node->next = ll->head;
        ll->head = new_node;
    }
    // Otherwise always keep a pointer to the node before where we are supposed
    // to insert the node and insert it
    else {
        Node prev = ll->head;
        for(unsigned int i=1; i<index; i++, prev=prev->next)
            ;
        new_node->next = prev->next;
        prev->next = new_node;
    }
}

/*******************************************************************************/
Element         LLRemove(LinkedList ll, unsigned int index) {
    if(index == 0) {
        if(ll->head) {
            Element e = ll->head->e;
            Node node = ll->head;
            ll->head = ll->head->next;
            free(node);
            return e;
        }
        return NULL;
    }
    
    Node prev = ll->head, curr = ll->head->next;
    unsigned int n = 1;

    for(; n!=index && curr; n++, prev=curr, curr=curr->next)
        ;

    if(!curr)
        return NULL;
    
    Element e = curr->e;
    prev->next = curr->next;
    free(curr);

    return e;
}

/*******************************************************************************/
Element         LLFirst(const LinkedList ll) {
    if (!ll || !ll->head) {
        return NULL;
    }

    // Default - current pointer for iterations. "LL Implements Iterable" oop style
    ll->current = ll->head;

    return ll->head->e;
}


/*******************************************************************************/
Element         LLNext(const LinkedList ll) {
    if (!ll || !ll->current || !ll->current->next) {  // check previous or new current (iterator-hasNext)
        return NULL;
    }

    // update current - iterator-next
    ll->current = ll->current->next;

    return ll->current->e;
}