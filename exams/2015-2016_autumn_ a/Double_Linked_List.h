#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

typedef struct DLL* DLL;
typedef void* Element;

DLL		DLLCreate(Element (*cpy)(Element), void (*fre)(Element), bool (*cmp)(Element, Element));

void	DLLDestroy(DLL dll);

void	DLLAdd(DLL dll, Element e);

void 	DLLRemove(DLL dll, Element e);

bool	DLLFind(DLL dll, Element e);

unsigned int DLLSize(DLL dll);

Element DLLGet(DLL dll, unsigned int n);


#endif