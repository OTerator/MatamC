#include "LinkedList.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>


struct Queue {
   LinkedList ll;
};



Queue QueueCreate(Element (*cpy)(Element), void (*fre)(Element)) {

   Queue q = (Queue)malloc(sizeof(struct Queue));
   if (!q) return NULL;

   q->ll = LLCreate(cpy, fre);
   if (!q->ll) {
      free(q);
      return NULL;
   }

   
   return q;
}

void QueueDestroy(Queue q) {
   if (!q) return;
   
   LLDestroy(q->ll);
   free(q);
}

void QueuePush(Queue q, Element e) {
   if (!q || e == NULL) return;

   LLAdd(q->ll, LLSize(q->ll), e);
}
Element QueueEnqueue(Queue q);


Element QueueDequeue(Queue q) {
   if (!q) return;

   return LLRemove(q->ll, LLSize(q->ll));
}

bool QueueIsEmpty(Queue q) {
   if (!q) return true;
   return (LLSize(q->ll) == 0);
}


