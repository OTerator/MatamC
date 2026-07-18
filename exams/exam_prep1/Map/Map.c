#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "LinkedList.h"

typedef struct Pair* Pair;
struct Pair {
	Key key;
	Value val;
};

struct Map {
	LinkedList	pairs;	// LL of Pair structs.
	Value (*cpy)(Value);
	void (*fre)(Value);
};


Map		MapCreate(Value (*cpy)(Value), void (*fre)(Value)) {
	
	Map map = (Map) malloc(sizeof(struct Map));
	
	map->pairs = LLCreate();	/* Element of LL is Pair, either cpy&fre functions go here or the user manages as wills. */
	
	map->cpy = cpy;
	map->fre = fre;
	
	return map;
}


bool	MapPutItem(Map map, Key key, Value val) {
	
	if (!map) return false;
	
	
	// for (unsigned int i=0; i<LLSize(map->pairs); i++) {
	// 	Pair curr = (Pair)LLGet(map->pairs, i);
	// 	if (curr->key == key) return false;
	// }
	
	// (!) Itay says we can use these:
	for (unsigned int i=0; i<LLSize(map->pairs); i++) {
		if (strcmp(key, MapGetKeyByIndex(map, i)) == 0) return false;
	}
	
	// if we got here, key is not in any pair from map->pairs.
	
	Pair newPair = (Pair) malloc(sizeof(struct Pair));
	// if !newPair exit...
	
	newPair->key = (Key)malloc(strlen(key) + 1); // +1 for '\0' !
	strcpy(newPair->key, key);
	newPair->val = map->cpy(val);
	
	LLAdd(map->pairs, 0, newPair);
	return true;
}

