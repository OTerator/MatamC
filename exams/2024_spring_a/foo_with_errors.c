#include <stdio.h>
char* read(const char* file_name) {
	FILE* fp = fopen(file_name, "r");
	char *arr, *p=arr, c;
	
	while(((c = fgetc(fp)) != NULL)) {
		arr = (char*)realloc(arr, strlen(arr)+1);
		*(p++) = c;
	}
	
	return arr
}

// (foo with errors)
