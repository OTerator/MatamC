#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

typedef struct Map* Map;
typedef char* Key;
typedef struct Value* Value;


Map				MapCreate(Value (*cpy)(Value), void (*fre)(Value));

void			MapDestroy(Map map);

bool			MapPutItem(Map map, Key key, Value val);

//	Returns the value associated with the key or NULL if key is not in map.
Value			MapRemove(Map map, Key key);

Value			MapGetValue(Map map, Key key);

unsigned int	MapGetSize(Map map);

Key				MapGetKeyByIndex(Map map, unsigned int index);

#endif