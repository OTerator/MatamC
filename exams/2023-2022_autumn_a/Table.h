#ifndef TABLE_H
#define TABLE_H

typedef struct Table* Table
typedef void* Element;

Table			TCreate(Element (*cpy)(Element), void (*fre)(Element), int (*cmp)(Element, Element));

void			TDestroy(Table t);

void			TAddColumn(Table t);

void			TAddRows(Table t, unsigned int n);

Element			TGet(unsigned int y, unsigned int x);

Element			TAt(Table t, unsigned int y, unsigned int x);

void			TPut(Table t, Element e, unsigned int y, unsigned int x);	// uses cpy and fre.

unsigned int	TCount(Table t, Element e);		// will use cmp.

#endif