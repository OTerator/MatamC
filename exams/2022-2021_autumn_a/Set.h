#ifndef SET_H
#define SET_H

typedef struct Set* Set;
typedef void* Element;

Set SetCreate(Element (*cpy)(Element), void (*fre)(Element), bool (*cmp)(Element, Element));

void 			SetDestroy(Set);
void 			SetAdd(Set, Element);
void 			SetRemove(Set, Element);
unsigned int 	SetSize(Set);
Element 		SetFind(Set, Element);
Element 		SetFirst(Set);
Element 		SetNext(Set);

#endif //SET_H