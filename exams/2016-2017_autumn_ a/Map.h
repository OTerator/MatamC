#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

typedef struct Map* Map;
typedef const char* Key;
typedef void* Value;


Map				MapCreate(Value (*cpy)(Value), void (*fre)(Value));

void			MapDestory(Map m);

bool			MapAdd(Map m, Key k, Value v);

Value			MapRemove(Map m, Key k);

Value			MapGetVal(Map m, Key k);

unsigned int	MapSize(Map m);

// 1 < i < MapSize.
Key				MapGetKey(Map m, unsigned int i);

#endif