#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"
#include "Array.h"



/*******************************/
struct Dictionary {
   // private fields (!)
   Array words;
   Array definitions;
   unsigned int items;  // num of words/definitions in the dict.
   unsigned int size;   // arr size of words = arr size of defs.
};


Element strDuplicate(Element e) {
   if (!e) return NULL;
    
   char* src = (char*)e;
    
   char* dest = (char*)malloc(strlen(src) + 1);
    
    
   if (dest) {
      strcpy(dest, src);
   }
    
   return dest;
}

/*******************************/


Dictionary     DictCreate() {

   Dictionary dict = (Dictionary)malloc(sizeof(struct Dictionary));
   if (!dict)
      return NULL;

   Array words = ArrCreate(strDuplicate, free);
   Array defs = ArrCreate(strDuplicate, free);

   dict->words = words;
   dict->definitions = defs;
   dict->items = 0;
   dict->size = 0;


   return dict;
}



// void           DictDestroy(Dictionary dict);

void           DictPut(Dictionary dict, Word word, Definition defi) {

   if (!dict || !word || !defi) {
      return;
   }

   // if word is already there, do nothing.
   for (unsigned int i=0; i<dict->items; i++) {
      if (strcmp(word, (Word)ArrAt(dict->words, i)) == 0) {
         return;
      }
   }

   if (dict->items == dict->size) { // ran out of space

      if (dict->size == 0) {  // first time, empty set.
         dict->size = 2;   // arbitrary choice, will be: 2*2=4 :
      }

      dict->size <<= 1;    // *= 2
      ArrResize(dict->words      , dict->size);
      ArrResize(dict->definitions, dict->size);
   }

   ArrPut(dict->definitions, dict->items, defi);
   ArrPut(dict->words      , dict->items, word);
   dict->items++;
}

// Definition     DictGetDefinitionOf(Dictionary dict, Word word);

// unsigned int   DictStartsWith(Dictionary dict, char* substring, char** arr); 

// unsigned int   DictWordCount(Dictionary dict);




/*******************************/


