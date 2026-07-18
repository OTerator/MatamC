#include <stdio.h>
#include <string.h>

void set_line_length(const char* file, unsigned int n) {
	
	if (n == 0 || !file) {
		fprintf(stderr, "Invalid arguments");
		return;
	}
	
	FILE* fp = fopen(file, "r");
	if (!fp) {
		fprintf(stderr, "failed to open file path.");
		return;
	}
	
	int c;
	for (unsigned int i=1; (c = fgetc(fp)) != EOF; i++) {
		if (c == '\n') c = ' ';
		putchar(c);
		if (!(i%n)) putchar('\n');
	}
	
	fclose(fp);
}


void add_space(char* str, unsigned int n) {
	unsigned int len = strlen(str);
	if (n > len) return;
	
	for (unsigned int i=0; i<=len; i++) {
		//str[len+n+1] = '\0';
		str[len+n-i] = str[len-i];	// from end to start.
	}
}

void add_space(char* str, unsigned int n) {
	unsigned int len = strlen(str);
	if (n > len) return;
	
	// str[len] is '\0'
	for (int i=len; i>=0; i--) {
		str[i+n] = str[i];
	}
}

void remove_space(char* str, unsigned int n) {
	unsigned int len = strlen(str);
	if (n>len) return;
	
	// i <= len to count for '\0'.
	for (int i=0; i<=len-n; i++) {
		str[i] = str[i+n];
	}
}


void sed_s(const char* filename, char* to_replace, char* replacement) {
	
	FILE* fp = fopen(filename, "r");
	if (!fp) return;
	
	char buf[257];	// no need to malloc for 257 bytes.
	int diff = strlen(replacement) - strlen(to_replace);
	
	while (fgets(buf, 256, fp) != NULL) {
		unsigned int i = 0;
		char* p = buf;
		while ( (p = strstr(p, to_replace)) != NULL ) {
			diff>0 ? add_space(p, diff) : remove_space(p, diff);
			strncpy(p, replacement, strlen(replacement));
			p += strlen(replacement);
		}
		printf("%s", line);
	}
	
	fclose(fp);
}