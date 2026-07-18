#include "Table.h"
#include "Array.h"
#include <stdio.h>
#include <stdlib.h>

struct Table {
	Array* cols;
	unsigned int num_cols;
	Element (*cpy)(Element);
	void (*fre)(Element);
	int (*cmp)(Element, Element);
};


Table	TCreate(Element (*cpy)(Element), void (*fre)(Element), int (*cmp)(Element, Element)) {
	
	Table t = (Table) malloc(sizeof(struct Table));
	
	t->cols = NULL;
	t->num_cols = 0;
	t->cpy = cpy;
	t->fre = fre;
	t->cmp = cmp;
	
	return t;
}

unsigned int	TCount(Table t, Element e) {		// will use cmp.
	
	unsigned int count = 0;
	
	for (unsigned int i=0; i<t->num_cols; i++) {
		
		for (unsigned int j=0; j<ArrSize(t->cols[i]); j++) {
			
			if ( !(t->cmp(e, ArrAt(t->cols[i], j))) )	// cmp returns 0 when equal so !0 is 1 and this block executes:
				count++;
		}
	}
	
	return count;
}