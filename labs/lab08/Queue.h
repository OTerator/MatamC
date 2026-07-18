#ifndef QUEUE_h
#define QUEUE_h
#include "LinkedList.h"
#include <stdbool.h>

typedef struct Queue* Queue;

Queue       QueueCreate(Element (*cpy)(Element), void (*fre)(Element));
void        QueueDestroy(Queue);
void        QueuePush(Queue, Element);
Element     QueueEnqueue(Queue);
Element     QueueDequeue(Queue);
bool        QueueIsEmpty(Queue);

#endif

