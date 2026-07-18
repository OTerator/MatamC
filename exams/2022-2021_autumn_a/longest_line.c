#include <stdio.h>

unsigned int longest_line(const char* fname) {
	
	FILE* fp = fopen(fname, "r");
	
	unsigned int max=0;
	int len=0, c;
	for (; (c=fgetc(fp)) != EOF; len++) {
		if (c=='\n') {
			if ((int)max<len) max=len;
			len=-1;	// -1 to not count \n.
		}
	}
	
	fclose(fp);
	
	if ((int)max<len) max = len;	// in case the last line before EOF didn't have \n.
	
	return max;
}