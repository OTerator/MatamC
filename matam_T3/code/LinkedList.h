#ifndef LINKEDLIST_h
#define LINKEDLIST_h

typedef void* Element;
typedef struct LinkedList* LinkedList;

/* Return an empty list. Takes a function that creates a new element (cpy)
   and a functionn that frees it (fre) */
LinkedList      LLCreate(Element (*cpy)(Element), void (*fre)(Element));

/* Destroys a list */
void            LLDestroy(LinkedList ll);

/* Returns the number of elements in a list */
unsigned int    LLSize(LinkedList ll);

/* Adds an element at location index (between 0 to LLSize()). index=0 means that the
   element will be inserted at the beginning of the list, index=1 will place the
   element bbetween the first and second items, and index=LLSize() will place the
   element after the current last element (which will make the new element the last
   one) */
void            LLAdd(LinkedList ll, unsigned int index, Element element);

/* Remove and return an element from the list (index between 0 to LLSize-1) */
Element         LLRemove(LinkedList ll, unsigned int index);

#endif
