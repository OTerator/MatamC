#include <stdio.h>
#include <stdlib.h>
#include "Array.h"


struct Array {

   Element* data;
   unsigned int size;
   Element (*cpy)(Element);
   void (*fre)(Element);

};



// Create an empty array with no cells
Array ArrCreate(Element (*cpy)(Element), void (*fre)(Element)) {

   Array arr = (Array)malloc(sizeof(struct Array));
   if (!arr)   
      return NULL;

   arr->data = NULL;
   arr->size = 0;
   arr->cpy = cpy;
   arr->fre = fre;

   return arr;
}

// destroy an array
void ArrDestroy(Array arr) {
   if (!arr) 
      return;

   for (unsigned int i=0; i < arr->size; i++) {
      if (arr->data[i]) {
         arr->fre(arr->data[i]);
      }
   }

   free(arr->data);
   free(arr);
}

// Get Array size
unsigned int ArrSize(Array arr) {
   if (!arr)
      return 0;

   return arr->size;
}

// Change the size of the Array
void ArrResize(Array arr, unsigned int new_size) {
   if (!arr || new_size == arr->size)
      return;

   if (new_size < arr->size) {
      for (unsigned int i=new_size; i<arr->size; i++) {
         arr->fre(arr->data[i]);
      }
   }

   // realloc: "no need to tests if mem realloc was successful..."
   arr->data = (Element*)realloc(arr->data, new_size*sizeof(Element));
   if (new_size > arr->size) {
      for (unsigned int i = arr->size; i<new_size; i++) {
         arr->data[i] = NULL;
      }
   }
   
   arr->size = new_size;
}

// Insert an element to position pos in arr
Element ArrPut(Array arr, unsigned int pos, Element e) {
   if (!arr || pos >= arr->size)
      return NULL;

   if (arr->data[pos])
      arr->fre(arr->data[pos]);
   
   arr->data[pos] = arr->cpy(e);
   return arr->data[pos];
}

// Get the element in position pos but leave it in the Array
Element ArrAt(Array arr, unsigned int pos) {
   if (!arr || pos >= arr->size)
      return NULL;

   return arr->data[pos];
}

// Get the element in position pos and remove it from the Array
Element ArrGet(Array arr, unsigned int pos) {
   if (!arr || pos >= arr->size)
      return NULL;

   Element e = arr->data[pos];
   arr->data[pos] = NULL;
   return e;
}