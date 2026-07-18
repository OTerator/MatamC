#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int num_items(const char* str, char delimiter) {
	if (!str) return 0;

	unsigned int num_words = 1;
	
	for (; *str; str++) {
		if (*str == delimiter) num_words++;
	}
	
	return num_words;
}


char** split(const char* str, char delimiter) {
	if (!str) return NULL;
	
	unsigned int numItems = num_items(str, delimiter);
	
	char** strings = (char**) malloc(sizeof(char*) * numItems);
	
	const char* p = str;	// p is essentially like end, and str becomes start.
	for (unsigned int i=0; i<numItems; i++) {
		// advance p and j to delimiter
		unsigned int j=0;
		for (; (*p != delimiter) && (*p != '\0'); j++, p++)
			;	// now p=delimiter, j=size strlen.
		char* new_s = (char*) malloc(sizeof(char)*(j+1));
		strncpy(new_s, str, j);
		new_s[j] = '\0';
		*(strings+i) = new_s;	// same as strings[i]
		if (*p) p++;	// discard the delimiter.
		str = p; // move on to the next word in the sequence.
	}
	
	return strings;
}