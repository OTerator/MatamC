#ifndef LINKEDLIST_h
#define LINKEDLIST_h
#define MEM_ALLOCATION_ERROR 1

typedef void* Element;
typedef struct LinkedList* LinkedList;

/* Return an empty list. 
   - Each added element is the same given one but not a copy (!): 
      therefore it will have the same address (and allocation) in memory, 
      hence to why the provider of said element is also the one responsible of freeing the element.
   (This module used to take:  a function that creates a new element (cpy)  , a function that free elements (fre) ).
*/
LinkedList      LLCreate();

/* Destroys a list: only the struct of the list and its nodes are being freed, since no elements were copied,
   it is the responsibily of the user to free as needed. */
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

/* Recieves a LL and returns the Element of the first Node in the LL.
   if LL is empty, returns NULL. (the value of ll wouldn't be changed, hence it will always point to the same LL)
   Note: This method must be in use in order to initialize iterations with LLNext. if it is not used, usage of LLNext() will immediately return NULL.
   more uses of this method will reset the iterating of LLNext back to the start of the LL. 
   */ 
Element         LLFirst(const LinkedList ll);

/* Returnes the next Element in the LL, if we are done iterating over all LL Elements, return NULL
   [this method is meant to be used in a for-each loop - example: for(Element e=LLFirst(ll); !e; e=LLNext(ll)) ]
   The pointer to ll should never be changed (hence it will always point to the same LL) while using this method (in a loop),
   if changed, the behavior of this function will be undefined and may induce bugs/runtime errors (!)
   if used in a for-each statement, do not nest with the same LL, this implementation is similar to an iterator but with a restart button in every use = (LLFirst) 
   Note: a call to LLFirst must be made before using this method for each iterating sequence over a LinkedList. if a call to LLFirst hasn't been made, this method 
   will return NULL immediately.  
   */
Element         LLNext(const LinkedList ll);

#endif