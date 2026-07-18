#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Element cpy_int(Element e) {
    int* new_Int = (int*) malloc(sizeof(int));
    if(!new_Int) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n", __FILE__, __LINE__, sizeof(int));
        exit(-1);
    }
    *new_Int = *(int*)e;
    return new_Int;
}


void free_int(Element e) {
    free(e);
}

/*******************************************************************************/

// Element cpy_str(Element e) {

//     char** new_Str = (char**) malloc(strlen(e));
//     if (!new_Str) {
//         fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n", __FILE__, __LINE__, strlen(e));
//         exit(-1);
//     }
//     *new_Str = *(char**)e;
//     return new_Str;
// }


// void free_str(Element e) {
//     free(e);
// }

/*******************************************************************************/

int main() {
    LinkedList ll = LLCreate(cpy_int, free_int);
    for(int i=0; i<=10; i++)
        LLAdd(ll, 0, &i);

    while(LLSize(ll) > 0) {
        int* e = (int*) LLRemove(ll, 0);
        printf("%d\n", *e);
        free_int(e);
    }

    LLDestroy(ll);


    // LinkedList ll = LLCreate(cpy_str, free_str);
    
    // LLAdd(ll, 0, "abc");
    // LLAdd(ll, 0, "def");
    // LLAdd(ll, 0, "ghi");
    // LLAdd(ll, 0, "jk");
    // LLAdd(ll, 0, "kmnop");
    // LLAdd(ll, 0, "q");
    // LLAdd(ll, 0, "rst");
    // LLAdd(ll, 0, "uvwxyz");

    // while(LLSize(ll) > 0) {
    //     char* e = (char*) LLRemove(ll, 0);
    //     printf("%s\n", e);
    //     free_str(e);
    // }

    // LLDestroy(ll);

	return 0;
}