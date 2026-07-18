#include "Student.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
	if(argc != 2) {
		fprintf(stderr, "\nUsage: %s <positive-seed>\n\n", argv[0]);
		return 1;
	}
	unsigned int seed = atoi(argv[1]);
	if(seed == 0) {
		fprintf(stderr, "Error: wrong seed %s\n", argv[1]);
		return 2;
	}

	srand(seed);
	unsigned int ncourses = rand()%15;
	Student* itai = StudentCreate("John", "123456789");
	for(unsigned int i=0; i<ncourses; i++)
		StudentSetGrade(itai, rand()%100, rand()%101);

	for(Course i=0; i<MAX_COURSES; i++) {
		Grade g = StudentGetGrade(itai, i);
		if(g != NO_GRADE)
			printf("John\'s grade in %u is %u\n", i, g);
	}
	StudentDestroy(itai);

	return 0;
}
