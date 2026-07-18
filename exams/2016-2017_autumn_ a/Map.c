#include "Map.h"
#include <string.h>

typedef struct Node* Node;

struct Node {
	Key k;
	Value v;
	Node next;
};

struct Map {
	Node head;
	unsigned int size;
	Value (*cpy)(Value);
	void (*fre)(Value);
};


Map	MapCreate(Element (*cpy)(Element), void (*fre)(Element)) {
	
	Map m = (Map) malloc(sizeof(struct Map));
	
	m->size = 0;
	m->head = NULL;
	m->cpy = cpy;
	m->fre = fre;
	
	return m;
}


bool MapAdd(Map m, Key k, Value v) {
	
	for(unsigned int i=0; i<MapSize(m); i++) {
		if (!strcmp(MapGetKey(m, i), k)) return false;
	}
	
	Node new_head = (Node) malloc(sizeof(struct Node));
	// if !new_head...
	
	//strcpy(new_head->k, k);
	new_head->k = strdup(k);
	new_head->v = (Value) m->cpy(v);
	new_head->next = m->head;
	
	m->head = new_head;
	
	return true;
}
