#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdbool.h>

typedef struct Dict* Dict;

// strdup, free, strcmp as its not ADT.
Dict			CreateDictionary();

void 			DestroyDictionary(Dict d);

bool			DictAdd(Dict d, const char* word, const char* meaning);

void			DictRemove(Dict d, const char* word);

const char*		DictGetMeaning(Dict d, const char* word);

unsigned int	DictGetStartsWithArr(Dict d, const char* prefix, char* res[]);

unsigned int	DictSize(Dict d);


#endif