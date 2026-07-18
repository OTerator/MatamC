#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

Element cpy_int(Element e) {
    int* new_Int = (int*) malloc(sizeof(int));
    if(!new_Int) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n", __FILE__, __LINE__, sizeof(int));
        exit(-1);
    }
    *new_Int = *(int*)e;
    return new_Int;
}

int main() {
    LinkedList ll = LLCreate(cpy_int, free);
    for(int i=0; i<=10; i++)
        LLAdd(ll, 0, &i);

    while(LLSize(ll) > 0) {
        int* e = (int*)LLRemove(ll, 0);
        printf("%d\n", *e);
        free(e);
    }

    LLDestroy(ll);

	return 0;
}

