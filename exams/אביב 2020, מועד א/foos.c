#include <stdio.h>
#include <string.h>

int findocc(const char* s1, unsigned int n) {
	
	char* nstr[20];
	sprintf(nstr, "%u", n);
	
	unsigned int len_s = strlen(s1);
	unsigned int len_n = strlen(nstr);
	
	if (len_n > len_s) return -1;
	
	for (unsigned int i=0; i<strlen(s1)-len(nstr); i++) {
		if (!strncmp(s1+i, nstr, len_n) return i;
	}
	
	return -1;
}


char* replace(const char* sSource, unsigned int nSearch, unsigned int nReplace) {
	
	int index = findocc(sSource, nSearch);
	
	if (index == -1) {
		char* copy = (char*)malloc(strlen(sSource) + 1);
		copy = strdup(sSource);
		return copy;
	}
	
	char strReplace[20];
    char strSearch[20];
	
	sprintf(strReplace, "%u", nReplace);
    sprintf(strSearch, "%u", nSearch);
	
	int lenReplace = strlen(strReplace);
    int lenSearch = strlen(strSearch);
    int lenSource = strlen(sSource);
	
	int newLen = lenSource - lenSearch + lenReplace;
	
	char* newStr = (char*)malloc(newLen * sizeof(char) + 1);
    if (!newStr) return NULL; // Allocation failed
	
	// copy all identical chars until found occ.
	strncpy(newStr, sSource, index);
	
	//strcat(newStr, strReplace);
	strcpy(newStr + index, nReplace);

    // Step C: Append the suffix (everything after the match)
    // Pointer arithmetic: sSource + index + lenSearch points to the character immediately following the match
   // strcat(newStr, sSource + index + lenSearch);
   strcpy(newStr+index+lenReplace, sSource+i+lenSearch);
   

    return newStr;
	
}