#ifndef DICTIONARY_H
#define DICTIONARY_H



typedef struct Dictionary* Dictionary;
typedef char* Word;
typedef char* Definition;


Dictionary     DictCreate();

void           DictDestroy(Dictionary dict);

void           DictPut(Dictionary dict, Word word, Definition defi);

Definition     DictGetDefinitionOf(Dictionary dict, Word word);

unsigned int   DictStartsWith(Dictionary dict, char* substring, char*** arr); // Address (*) of an arr (*) of strings (*) (3)

unsigned int   DictWordCount(Dictionary dict);


#endif   // DICTIONARY_H