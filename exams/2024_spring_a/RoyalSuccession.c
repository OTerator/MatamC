#include "RoyalSuccession.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct RoyalSuccession {
	LinkedList succession;
};

Element str_cpy(Element str) {
	return (Element) strdup((const char*)str);
}

RoyalSuccession RSCreate() {
	
	RoyalSuccession rs = (RoyalSuccession) malloc(sizeof(struct RoyalSuccession));
	if (!rs) {
		fprintf(stderr, "failed to alloc %lu bytes in RSCreate\n", sizeof(struct RoyalSuccession));
		exit(1);
	}
	
	rs->succession = LLCreate(str_cpy, free);
	
	return rs;
}


bool 	RSAdd(RoyalSuccession rs, const char* name, unsigned int i) {
	if (!rs || !name || !rs->succession) return false;
	unsigned int num_successors = LLSize(rs->succession);
	if (i > num_successors) return false;	// 0 ≤ i ≤ num_successors
	
	for (unsigned int j=0; j<num_successors; j++) {
		if (!strcmp(name, RSGet(rs, j))) return false;
	}
	
	LLAdd(rs->succession, i, name);
	return true;
}

